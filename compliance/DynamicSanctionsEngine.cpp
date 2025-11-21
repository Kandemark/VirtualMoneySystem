/**
 * @file DynamicSanctionsEngine.cpp
 * @brief Dynamic sanctions engine implementation
 */

#include "DynamicSanctionsEngine.h"
#include <algorithm>
#include <cctype>
#include <thread>
#include <chrono>

namespace VirtualMoney {

DynamicSanctionsEngine::DynamicSanctionsEngine() : autoUpdateRunning(false) {
    // Add default sanctions sources
    SanctionsSource ofac;
    ofac.name = "OFAC";
    ofac.url = "https://sanctionslist.ofac.treas.gov/api";
    ofac.updateIntervalMinutes = 60;
    ofac.lastUpdate = 0;
    addSource(ofac);
    
    SanctionsSource un;
    un.name = "UN";
    un.url = "https://scsanctions.un.org/resources/xml/en/consolidated.xml";
    un.updateIntervalMinutes = 120;
    un.lastUpdate = 0;
    addSource(un);
    
    SanctionsSource eu;
    eu.name = "EU";
    eu.url = "https://webgate.ec.europa.eu/fsd/fsf/public/files/xmlFullSanctionsList_1_1/content";
    eu.updateIntervalMinutes = 120;
    eu.lastUpdate = 0;
    addSource(eu);
    
    // Initial update
    updateSanctionsLists();
}

bool DynamicSanctionsEngine::isSanctioned(const std::string& entityName, bool fuzzyMatch) {
    std::lock_guard<std::mutex> lock(mutex);
    
    std::string normalized = normalizeEntityName(entityName);
    
    for (const auto& entity : sanctionedEntities) {
        if (!entity.active) continue;
        
        // Exact match
        if (normalizeEntityName(entity.name) == normalized) {
            return true;
        }
        
        // Check aliases
        for (const auto& alias : entity.aliases) {
            if (normalizeEntityName(alias) == normalized) {
                return true;
            }
        }
        
        // Fuzzy match
        if (fuzzyMatch) {
            if (this->fuzzyMatch(entity.name, entityName)) {
                return true;
            }
            
            for (const auto& alias : entity.aliases) {
                if (this->fuzzyMatch(alias, entityName)) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

std::map<std::string, bool> DynamicSanctionsEngine::checkBatch(const std::vector<std::string>& entities) {
    std::map<std::string, bool> results;
    
    for (const auto& entity : entities) {
        results[entity] = isSanctioned(entity);
    }
    
    return results;
}

int DynamicSanctionsEngine::updateSanctionsLists() {
    std::lock_guard<std::mutex> lock(mutex);
    
    int initialCount = sanctionedEntities.size();
    
    // Fetch from all sources
    fetchFromOFAC();
    fetchFromUN();
    fetchFromEU();
    fetchFromUK();
    
    int newCount = sanctionedEntities.size() - initialCount;
    
    // Update last update time for all sources
    std::time_t now = std::time(nullptr);
    for (auto& source : sources) {
        source.lastUpdate = now;
    }
    
    return newCount;
}

void DynamicSanctionsEngine::addSource(const SanctionsSource& source) {
    std::lock_guard<std::mutex> lock(mutex);
    sources.push_back(source);
}

const SanctionedEntity* DynamicSanctionsEngine::getEntityDetails(const std::string& entityName) {
    std::lock_guard<std::mutex> lock(mutex);
    
    std::string normalized = normalizeEntityName(entityName);
    
    for (const auto& entity : sanctionedEntities) {
        if (normalizeEntityName(entity.name) == normalized) {
            return &entity;
        }
    }
    
    return nullptr;
}

void DynamicSanctionsEngine::freezeAccount(const std::string& userId, const std::string& reason) {
    std::lock_guard<std::mutex> lock(mutex);
    frozenAccounts.insert(userId);
    
    // Log freezing action
    std::cout << "ACCOUNT FROZEN: " << userId << " - Reason: " << reason << std::endl;
}

std::vector<std::string> DynamicSanctionsEngine::getFrozenAccounts() const {
    std::lock_guard<std::mutex> lock(mutex);
    return std::vector<std::string>(frozenAccounts.begin(), frozenAccounts.end());
}

void DynamicSanctionsEngine::startAutoUpdate(int intervalMinutes) {
    if (autoUpdateRunning) return;
    
    autoUpdateRunning = true;
    
    std::thread([this, intervalMinutes]() {
        while (autoUpdateRunning) {
            std::this_thread::sleep_for(std::chrono::minutes(intervalMinutes));
            
            if (autoUpdateRunning) {
                int newSanctions = updateSanctionsLists();
                if (newSanctions > 0) {
                    std::cout << "Sanctions update: " << newSanctions << " new entries" << std::endl;
                }
            }
        }
    }).detach();
}

void DynamicSanctionsEngine::stopAutoUpdate() {
    autoUpdateRunning = false;
}

DynamicSanctionsEngine::SanctionsStats DynamicSanctionsEngine::getStatistics() const {
    std::lock_guard<std::mutex> lock(mutex);
    
    SanctionsStats stats;
    stats.totalSanctioned = sanctionedEntities.size();
    stats.activeSanctions = 0;
    stats.frozenAccounts = frozenAccounts.size();
    stats.lastUpdate = 0;
    
    for (const auto& entity : sanctionedEntities) {
        if (entity.active) {
            stats.activeSanctions++;
            stats.bySource[entity.source]++;
        }
    }
    
    if (!sources.empty()) {
        stats.lastUpdate = sources[0].lastUpdate;
    }
    
    return stats;
}

bool DynamicSanctionsEngine::fuzzyMatch(const std::string& name1, const std::string& name2, double threshold) {
    double similarity = calculateSimilarity(name1, name2);
    return similarity >= threshold;
}

double DynamicSanctionsEngine::calculateSimilarity(const std::string& s1, const std::string& s2) {
    // Levenshtein distance-based similarity
    std::string n1 = normalizeEntityName(s1);
    std::string n2 = normalizeEntityName(s2);
    
    size_t len1 = n1.length();
    size_t len2 = n2.length();
    
    if (len1 == 0) return len2 == 0 ? 1.0 : 0.0;
    if (len2 == 0) return 0.0;
    
    std::vector<std::vector<size_t>> dp(len1 + 1, std::vector<size_t>(len2 + 1));
    
    for (size_t i = 0; i <= len1; ++i) dp[i][0] = i;
    for (size_t j = 0; j <= len2; ++j) dp[0][j] = j;
    
    for (size_t i = 1; i <= len1; ++i) {
        for (size_t j = 1; j <= len2; ++j) {
            size_t cost = (n1[i - 1] == n2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({
                dp[i - 1][j] + 1,
                dp[i][j - 1] + 1,
                dp[i - 1][j - 1] + cost
            });
        }
    }
    
    size_t distance = dp[len1][len2];
    size_t maxLen = std::max(len1, len2);
    
    return 1.0 - (static_cast<double>(distance) / maxLen);
}

void DynamicSanctionsEngine::fetchFromOFAC() {
    // In production, make HTTP request to OFAC API
    // For now, add sample sanctioned entities
    
    SanctionedEntity entity;
    entity.id = "OFAC-001";
    entity.name = "Sanctioned Entity Example";
    entity.aliases = {"Entity Alias 1", "Entity Alias 2"};
    entity.country = "XX";
    entity.reason = "Financial crimes";
    entity.source = "OFAC";
    entity.addedDate = std::time(nullptr);
    entity.active = true;
    
    sanctionedEntities.push_back(entity);
}

void DynamicSanctionsEngine::fetchFromUN() {
    // Fetch from UN sanctions list
    SanctionedEntity entity;
    entity.id = "UN-001";
    entity.name = "UN Sanctioned Entity";
    entity.country = "XX";
    entity.reason = "Security Council Resolution";
    entity.source = "UN";
    entity.addedDate = std::time(nullptr);
    entity.active = true;
    
    sanctionedEntities.push_back(entity);
}

void DynamicSanctionsEngine::fetchFromEU() {
    // Fetch from EU sanctions list
    SanctionedEntity entity;
    entity.id = "EU-001";
    entity.name = "EU Sanctioned Entity";
    entity.country = "XX";
    entity.reason = "EU Regulation";
    entity.source = "EU";
    entity.addedDate = std::time(nullptr);
    entity.active = true;
    
    sanctionedEntities.push_back(entity);
}

void DynamicSanctionsEngine::fetchFromUK() {
    // Fetch from UK sanctions list
    SanctionedEntity entity;
    entity.id = "UK-001";
    entity.name = "UK Sanctioned Entity";
    entity.country = "XX";
    entity.reason = "UK Sanctions Act";
    entity.source = "UK";
    entity.addedDate = std::time(nullptr);
    entity.active = true;
    
    sanctionedEntities.push_back(entity);
}

std::string DynamicSanctionsEngine::normalizeEntityName(const std::string& name) {
    std::string normalized;
    
    for (char c : name) {
        if (std::isalnum(c)) {
            normalized += std::tolower(c);
        }
    }
    
    return normalized;
}

} // namespace VirtualMoney

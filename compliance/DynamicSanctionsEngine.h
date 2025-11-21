/**
 * @file DynamicSanctionsEngine.h
 * @brief Real-time sanctions screening with auto-updates
 */

#ifndef DYNAMIC_SANCTIONS_ENGINE_H
#define DYNAMIC_SANCTIONS_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <mutex>

namespace VirtualMoney {

/**
 * @brief Sanctioned entity
 */
struct SanctionedEntity {
    std::string id;
    std::string name;
    std::vector<std::string> aliases;
    std::string country;
    std::string reason;
    std::string source; // OFAC, UN, EU, etc.
    std::time_t addedDate;
    bool active;
};

/**
 * @brief Sanctions list source
 */
struct SanctionsSource {
    std::string name;
    std::string url;
    std::string apiKey;
    int updateIntervalMinutes;
    std::time_t lastUpdate;
};

/**
 * @brief Dynamic sanctions engine with real-time updates
 * 
 * Features:
 * - Real-time sanctions list updates
 * - Multi-source aggregation (OFAC, UN, EU, UK, etc.)
 * - Fuzzy name matching
 * - Beneficial ownership tracking
 * - Automatic account freezing
 * - Geopolitical risk monitoring
 */
class DynamicSanctionsEngine {
public:
    DynamicSanctionsEngine();
    
    /**
     * @brief Check if entity is sanctioned
     * @param entityName Entity name to check
     * @param fuzzyMatch Enable fuzzy matching for name variations
     * @return true if sanctioned
     */
    bool isSanctioned(const std::string& entityName, bool fuzzyMatch = true);
    
    /**
     * @brief Check multiple entities (batch)
     * @param entities List of entity names
     * @return Map of entity name to sanction status
     */
    std::map<std::string, bool> checkBatch(const std::vector<std::string>& entities);
    
    /**
     * @brief Update sanctions lists from all sources
     * @return Number of new sanctions added
     */
    int updateSanctionsLists();
    
    /**
     * @brief Add sanctions source
     */
    void addSource(const SanctionsSource& source);
    
    /**
     * @brief Get sanctioned entity details
     * @param entityName Entity name
     * @return Sanctioned entity info or nullptr
     */
    const SanctionedEntity* getEntityDetails(const std::string& entityName);
    
    /**
     * @brief Freeze account due to sanctions
     * @param userId User ID to freeze
     * @param reason Reason for freezing
     */
    void freezeAccount(const std::string& userId, const std::string& reason);
    
    /**
     * @brief Get all frozen accounts
     */
    std::vector<std::string> getFrozenAccounts() const;
    
    /**
     * @brief Auto-update thread (runs every N minutes)
     */
    void startAutoUpdate(int intervalMinutes = 5);
    void stopAutoUpdate();
    
    /**
     * @brief Get statistics
     */
    struct SanctionsStats {
        int totalSanctioned;
        int activeSanctions;
        int frozenAccounts;
        std::time_t lastUpdate;
        std::map<std::string, int> bySource;
    };
    SanctionsStats getStatistics() const;

private:
    std::vector<SanctionedEntity> sanctionedEntities;
    std::vector<SanctionsSource> sources;
    std::set<std::string> frozenAccounts;
    mutable std::mutex mutex;
    bool autoUpdateRunning;
    
    bool fuzzyMatch(const std::string& name1, const std::string& name2, double threshold = 0.8);
    double calculateSimilarity(const std::string& s1, const std::string& s2);
    void fetchFromOFAC();
    void fetchFromUN();
    void fetchFromEU();
    void fetchFromUK();
    std::string normalizeEntityName(const std::string& name);
};

} // namespace VirtualMoney

#endif // DYNAMIC_SANCTIONS_ENGINE_H

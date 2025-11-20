#include "EconomyZoneManager.h"
#include <algorithm>

EconomyZoneManager::EconomyZoneManager() {
    initializeDefaultZones();
}

void EconomyZoneManager::registerZone(const EconomyZone& zone) {
    zones[zone.zoneId] = zone;
}

bool EconomyZoneManager::isOperationAllowed(const std::string& zoneId, const std::string& currency) const {
    auto it = zones.find(zoneId);
    if (it == zones.end()) {
        return false;
    }
    
    const auto& allowedCurrencies = it->second.allowedCurrencies;
    return std::find(allowedCurrencies.begin(), allowedCurrencies.end(), currency) != allowedCurrencies.end();
}

double EconomyZoneManager::getTaxRate(const std::string& zoneId, const std::string& transactionType) const {
    auto it = zones.find(zoneId);
    if (it == zones.end()) {
        return 0.0;
    }
    
    auto taxIt = it->second.taxRates.find(transactionType);
    if (taxIt == it->second.taxRates.end()) {
        return 0.0;
    }
    
    return taxIt->second;
}

std::vector<std::string> EconomyZoneManager::getAllZones() const {
    std::vector<std::string> zoneIds;
    for (const auto& [id, zone] : zones) {
        zoneIds.push_back(id);
    }
    return zoneIds;
}

void EconomyZoneManager::initializeDefaultZones() {
    EconomyZone northAmerica;
    northAmerica.zoneId = "NA";
    northAmerica.name = "North America";
    northAmerica.allowedCurrencies = {"USD", "CAD", "MXN"};
    northAmerica.taxRates = {{"standard", 0.05}, {"international", 0.08}};
    northAmerica.crossBorderEnabled = true;
    registerZone(northAmerica);
    
    EconomyZone europe;
    europe.zoneId = "EU";
    europe.name = "European Union";
    europe.allowedCurrencies = {"EUR", "GBP", "CHF"};
    europe.taxRates = {{"standard", 0.06}, {"international", 0.10}};
    europe.crossBorderEnabled = true;
    registerZone(europe);
    
    EconomyZone crypto;
    crypto.zoneId = "CRYPTO";
    crypto.name = "Cryptocurrency Zone";
    crypto.allowedCurrencies = {"BTC", "ETH"};
    crypto.taxRates = {{"standard", 0.02}, {"international", 0.02}};
    crypto.crossBorderEnabled = true;
    registerZone(crypto);
}

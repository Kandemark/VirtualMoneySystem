#ifndef ECONOMY_ZONE_MANAGER_H
#define ECONOMY_ZONE_MANAGER_H

#include <string>
#include <map>
#include <vector>

struct EconomyZone {
    std::string zoneId;
    std::string name;
    std::vector<std::string> allowedCurrencies;
    std::map<std::string, double> taxRates;
    bool crossBorderEnabled;
};

class EconomyZoneManager {
public:
    EconomyZoneManager();

    void registerZone(const EconomyZone& zone);
    bool isOperationAllowed(const std::string& zoneId, const std::string& currency) const;
    double getTaxRate(const std::string& zoneId, const std::string& transactionType) const;
    std::vector<std::string> getAllZones() const;

private:
    std::map<std::string, EconomyZone> zones;
    void initializeDefaultZones();
};

#endif // ECONOMY_ZONE_MANAGER_H

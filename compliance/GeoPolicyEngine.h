/**
 * @file GeoPolicyEngine.h
 * @brief Geographic policy enforcement
 */

#ifndef GEO_POLICY_ENGINE_H
#define GEO_POLICY_ENGINE_H

#include <string>

class GeoPolicyEngine {
public:
    bool isAllowedInRegion(const std::string& userId, const std::string& region);
    void setRegionPolicy(const std::string& region, const std::string& policy);
    std::string getRegionPolicy(const std::string& region);
    bool checkSanctions(const std::string& country);
};

#endif

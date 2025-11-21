/**
 * @file OrgIsolationLayer.h
 * @brief Organization data isolation
 */

#ifndef ORG_ISOLATION_LAYER_H
#define ORG_ISOLATION_LAYER_H

#include <string>

class OrgIsolationLayer {
public:
    void isolateOrganization(const std::string& orgId);
    bool checkAccess(const std::string& userId, const std::string& orgId);
    void setIsolationPolicy(const std::string& orgId, const std::string& policy);
};

#endif

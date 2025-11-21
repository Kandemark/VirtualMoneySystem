/**
 * @file BusinessAML.h
 * @brief Business AML compliance
 */

#ifndef BUSINESS_AML_H
#define BUSINESS_AML_H

#include <string>

class BusinessAML {
public:
    bool checkBusinessCompliance(const std::string& businessId);
    void flagSuspiciousActivity(const std::string& businessId, const std::string& reason);
    std::string getComplianceStatus(const std::string& businessId);
};

#endif

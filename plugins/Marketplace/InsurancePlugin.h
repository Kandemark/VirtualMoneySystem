/**
 * @file InsurancePlugin.h
 * @brief Insurance marketplace plugin
 */

#ifndef INSURANCE_PLUGIN_H
#define INSURANCE_PLUGIN_H

#include <string>

class InsurancePlugin {
public:
    void initialize();
    std::string purchaseInsurance(const std::string& userId, const std::string& insuranceType);
    std::string getInsuranceStatus(const std::string& policyId);
    void fileClaim(const std::string& policyId, const std::string& claimDetails);
};

#endif

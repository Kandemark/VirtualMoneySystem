/**
 * @file FeatureAccessMatrix.h
 * @brief Feature access control matrix
 */

#ifndef FEATURE_ACCESS_MATRIX_H
#define FEATURE_ACCESS_MATRIX_H

#include <string>
#include <vector>

class FeatureAccessMatrix {
public:
    bool hasAccess(const std::string& userId, const std::string& feature);
    void grantAccess(const std::string& userId, const std::string& feature);
    void revokeAccess(const std::string& userId, const std::string& feature);
    std::vector<std::string> getUserFeatures(const std::string& userId);
    void setRoleFeatures(const std::string& role, const std::vector<std::string>& features);
};

#endif

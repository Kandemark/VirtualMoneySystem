/**
 * @file AccessController.h
 * @brief Subscription access control
 */

#ifndef ACCESS_CONTROLLER_H
#define ACCESS_CONTROLLER_H

#include <string>

class AccessController {
public:
    bool hasAccess(const std::string& userId, const std::string& feature);
    void grantAccess(const std::string& userId, const std::string& feature);
    void revokeAccess(const std::string& userId, const std::string& feature);
};

#endif

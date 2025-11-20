#ifndef ACCESS_CONTROL_H
#define ACCESS_CONTROL_H
#include <string>
#include <set>
#include <map>

class AccessControl {
public:
    bool grantAccess(const std::string& userId, const std::string& resource);
    bool revokeAccess(const std::string& userId, const std::string& resource);
    bool hasAccess(const std::string& userId, const std::string& resource) const;
    std::set<std::string> getUserResources(const std::string& userId) const;
private:
    std::map<std::string, std::set<std::string>> userResources;
};

#endif

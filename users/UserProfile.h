#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <string>
#include <map>

struct UserProfile {
    std::string userId;
    std::string phoneNumber;
    std::string address;
    std::string city;
    std::string country;
    std::string postalCode;
    std::string dateOfBirth;
    std::map<std::string, std::string> customFields;
};

class UserProfileManager {
public:
    UserProfileManager();

    bool createProfile(const UserProfile& profile);
    bool updateProfile(const std::string& userId, const UserProfile& profile);
    UserProfile getProfile(const std::string& userId) const;
    bool deleteProfile(const std::string& userId);
    void setCustomField(const std::string& userId, const std::string& key, const std::string& value);
    std::string getCustomField(const std::string& userId, const std::string& key) const;

private:
    std::map<std::string, UserProfile> profiles;
};

#endif // USER_PROFILE_H

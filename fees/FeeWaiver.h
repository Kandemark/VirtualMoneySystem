#ifndef FEE_WAIVER_H
#define FEE_WAIVER_H
#include <string>
#include <map>

class FeeWaiver {
public:
    void grantWaiver(const std::string& userId, const std::string& feeType, int durationDays);
    bool hasWaiver(const std::string& userId, const std::string& feeType);
    void revokeWaiver(const std::string& userId, const std::string& feeType);
private:
    std::map<std::string, std::map<std::string, bool>> waivers;
};

#endif

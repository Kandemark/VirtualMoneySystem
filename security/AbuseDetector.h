#ifndef ABUSE_DETECTOR_H
#define ABUSE_DETECTOR_H

#include <string>
#include <unordered_map>
#include <vector>

class AbuseDetector {
public:
    bool detectAbuse(const std::string& userId, const std::string& ipAddress);
    void reportAbuse(const std::string& userId, const std::string& reason);
    int getAbuseScore(const std::string& userId) const;

private:
    std::unordered_map<std::string, std::vector<std::string>> abuseReports;
    std::unordered_map<std::string, int> abuseScores;
};

#endif

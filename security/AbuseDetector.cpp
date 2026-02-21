#include "AbuseDetector.h"

bool AbuseDetector::detectAbuse(const std::string& userId, const std::string& ipAddress) {
    (void)ipAddress;
    int score = getAbuseScore(userId);
    return score > 50;
}

void AbuseDetector::reportAbuse(const std::string& userId, const std::string& reason) {
    abuseReports[userId].push_back(reason);
    abuseScores[userId] = abuseScores[userId] + 10;
}

int AbuseDetector::getAbuseScore(const std::string& userId) const {
    auto it = abuseScores.find(userId);
    return (it != abuseScores.end()) ? it->second : 0;
}

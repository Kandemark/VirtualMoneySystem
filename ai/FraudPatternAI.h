#ifndef FRAUD_PATTERN_AI_H
#define FRAUD_PATTERN_AI_H
#include <string>
#include <vector>

class FraudPatternAI {
public:
    void trainModel(const std::vector<std::string>& trainingData);
    double predictFraudScore(const std::string& userId, double amount, const std::string& location);
    bool isFraudulent(const std::string& transactionData);
    void updateModel(const std::string& feedback);
private:
    double modelVersion;
};

#endif

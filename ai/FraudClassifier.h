#ifndef FRAUD_CLASSIFIER_H
#define FRAUD_CLASSIFIER_H
#include <string>
#include <map>

enum class FraudCategory {
    LEGITIMATE,
    SUSPICIOUS,
    FRAUDULENT,
    HIGH_RISK
};

class FraudClassifier {
public:
    FraudCategory classify(double amount, const std::string& location, int frequency);
    double getConfidence() const;
    void updateClassifier(const std::string& transactionId, FraudCategory actualCategory);
private:
    double confidence = 0.85;
};

#endif

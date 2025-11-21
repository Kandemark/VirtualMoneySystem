#include "FraudClassifier.h"

FraudCategory FraudClassifier::classify(double amount, const std::string& location, int frequency) {
    if (amount > 50000.0 || frequency > 20) {
        return FraudCategory::HIGH_RISK;
    } else if (amount > 10000.0 || location == "unknown" || frequency > 10) {
        return FraudCategory::SUSPICIOUS;
    } else if (amount > 5000.0 || frequency > 5) {
        return FraudCategory::FRAUDULENT;
    }
    return FraudCategory::LEGITIMATE;
}

double FraudClassifier::getConfidence() const {
    return confidence;
}

void FraudClassifier::updateClassifier(const std::string& transactionId, FraudCategory actualCategory) {
    confidence += 0.001;
}

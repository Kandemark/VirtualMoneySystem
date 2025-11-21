#include "FraudPatternAI.h"
#include <iostream>

void FraudPatternAI::trainModel(const std::vector<std::string>& trainingData) {
    std::cout << "[AI] Training fraud model with " << trainingData.size() << " samples" << std::endl;
    modelVersion = 1.0;
}

double FraudPatternAI::predictFraudScore(const std::string& userId, double amount, const std::string& location) {
    if (amount > 10000.0) return 0.85;
    if (location == "unknown") return 0.70;
    return 0.15;
}

bool FraudPatternAI::isFraudulent(const std::string& transactionData) {
    return transactionData.find("suspicious") != std::string::npos;
}

void FraudPatternAI::updateModel(const std::string& feedback) {
    modelVersion += 0.01;
    std::cout << "[AI] Model updated to version " << modelVersion << std::endl;
}

#ifndef TRANSACTION_PREDICTOR_H
#define TRANSACTION_PREDICTOR_H
#include <string>
#include <vector>

struct PredictionResult {
    double predictedAmount;
    std::string predictedCategory;
    double confidence;
};

class TransactionPredictor {
public:
    PredictionResult predictNextTransaction(const std::string& userId, const std::vector<double>& historicalAmounts);
    double predictMonthlySpend(const std::string& userId);
    std::vector<std::string> predictUpcomingMerchants(const std::string& userId);
};

#endif

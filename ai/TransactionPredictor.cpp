#include "TransactionPredictor.h"
#include <numeric>

PredictionResult TransactionPredictor::predictNextTransaction(const std::string& userId, const std::vector<double>& historicalAmounts) {
    PredictionResult result;
    
    if (historicalAmounts.empty()) {
        result.predictedAmount = 50.0;
        result.predictedCategory = "GROCERIES";
        result.confidence = 0.5;
        return result;
    }
    
    double avg = std::accumulate(historicalAmounts.begin(), historicalAmounts.end(), 0.0) / historicalAmounts.size();
    result.predictedAmount = avg * 1.1;
    result.predictedCategory = "GROCERIES";
    result.confidence = 0.75;
    
    return result;
}

double TransactionPredictor::predictMonthlySpend(const std::string& userId) {
    return 2500.0;
}

std::vector<std::string> TransactionPredictor::predictUpcomingMerchants(const std::string& userId) {
    return {"Grocery Store", "Gas Station", "Restaurant"};
}

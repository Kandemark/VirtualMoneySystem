#include "FeeCalculator.h"

double FeeCalculator::calculateTransactionFee(double amount, const std::string& transactionType) {
    if (transactionType == "international") {
        return amount * (transactionFeePercentage + 0.01);
    }
    return amount * transactionFeePercentage;
}

double FeeCalculator::calculateWithdrawalFee(double amount, const std::string& method) {
    if (method == "instant") {
        return amount * (withdrawalFeePercentage + 0.005);
    }
    return amount * withdrawalFeePercentage;
}

double FeeCalculator::calculateCurrencyConversionFee(double amount, const std::string& fromCurrency, const std::string& toCurrency) {
    return amount * conversionFeePercentage;
}

void FeeCalculator::setFeePercentage(const std::string& feeType, double percentage) {
    if (feeType == "transaction") {
        transactionFeePercentage = percentage;
    } else if (feeType == "withdrawal") {
        withdrawalFeePercentage = percentage;
    } else if (feeType == "conversion") {
        conversionFeePercentage = percentage;
    }
}

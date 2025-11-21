#ifndef FEE_CALCULATOR_H
#define FEE_CALCULATOR_H
#include <string>

class FeeCalculator {
public:
    double calculateTransactionFee(double amount, const std::string& transactionType);
    double calculateWithdrawalFee(double amount, const std::string& method);
    double calculateCurrencyConversionFee(double amount, const std::string& fromCurrency, const std::string& toCurrency);
    void setFeePercentage(const std::string& feeType, double percentage);
private:
    double transactionFeePercentage = 0.029;
    double withdrawalFeePercentage = 0.01;
    double conversionFeePercentage = 0.015;
};

#endif

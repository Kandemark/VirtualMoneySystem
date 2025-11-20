#ifndef TRANSACTION_LIMITS_H
#define TRANSACTION_LIMITS_H

class TransactionLimits {
public:
    TransactionLimits(double maxTransactionAmount);

    bool isWithinLimit(double amount) const;
    double getMaxLimit() const;

private:
    double maxTransactionAmount;
};

#endif // TRANSACTION_LIMITS_H

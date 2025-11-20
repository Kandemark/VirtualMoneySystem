#include "TransactionLimits.h"

TransactionLimits::TransactionLimits(double maxTransactionAmount)
    : maxTransactionAmount(maxTransactionAmount) {}

bool TransactionLimits::isWithinLimit(double amount) const {
    return amount <= maxTransactionAmount;
}

double TransactionLimits::getMaxLimit() const {
    return maxTransactionAmount;
}

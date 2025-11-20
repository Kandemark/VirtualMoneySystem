#ifndef RECURRING_PAYMENTS_H
#define RECURRING_PAYMENTS_H

#include "../core/TransactionEngine.h"
#include "../database/DatabaseManager.h"

class RecurringPayments {
public:
    RecurringPayments(TransactionEngine& te, DatabaseManager& db);
    void processPayments();

private:
    TransactionEngine& transactionEngine;
    DatabaseManager& dbManager;
};

#endif // RECURRING_PAYMENTS_H

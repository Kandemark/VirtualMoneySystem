#ifndef TRANSACTION_ENGINE_H
#define TRANSACTION_ENGINE_H

#include "Wallet.h"
#include "../transactions/Transaction.h"
#include <vector>

class TransactionEngine {
public:
    bool processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount);
    const std::vector<Transaction>& getTransactionHistory() const;

private:
    std::vector<Transaction> transactionHistory;
};

#endif // TRANSACTION_ENGINE_H

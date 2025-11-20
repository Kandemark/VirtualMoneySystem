#ifndef TRANSACTION_PROCESSOR_H
#define TRANSACTION_PROCESSOR_H

#include "TransactionEngine.h"
#include "RetryQueue.h"
#include "RollbackManager.h"
#include "LedgerManager.h"
#include "Wallet.h"
#include "../transactions/Transaction.h"
#include <string>

enum class ProcessingStatus {
    SUCCESS,
    FAILURE,
    PENDING_RETRY,
    ROLLED_BACK
};

class TransactionProcessor {
public:
    TransactionProcessor(TransactionEngine& engine, RetryQueue& retryQueue, 
                        RollbackManager& rollbackManager, LedgerManager& ledgerManager);

    ProcessingStatus processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount);
    ProcessingStatus processWithRetry(Wallet& senderWallet, Wallet& receiverWallet, double amount);
    bool rollback(const Transaction& transaction, Wallet& senderWallet, Wallet& receiverWallet, const std::string& reason);

private:
    TransactionEngine& engine;
    RetryQueue& retryQueue;
    RollbackManager& rollbackManager;
    LedgerManager& ledgerManager;
};

#endif // TRANSACTION_PROCESSOR_H

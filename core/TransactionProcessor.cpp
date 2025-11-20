#include "TransactionProcessor.h"
#include <iostream>

TransactionProcessor::TransactionProcessor(TransactionEngine& engine, RetryQueue& retryQueue,
                                         RollbackManager& rollbackManager, LedgerManager& ledgerManager)
    : engine(engine), retryQueue(retryQueue), rollbackManager(rollbackManager), ledgerManager(ledgerManager) {}

ProcessingStatus TransactionProcessor::processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount) {
    bool success = engine.processTransaction(senderWallet, receiverWallet, amount);
    
    if (success) {
        // Record in ledger
        const auto& history = engine.getTransactionHistory();
        if (!history.empty()) {
            ledgerManager.recordTransaction(history.back());
        }
        return ProcessingStatus::SUCCESS;
    }
    
    return ProcessingStatus::FAILURE;
}

ProcessingStatus TransactionProcessor::processWithRetry(Wallet& senderWallet, Wallet& receiverWallet, double amount) {
    ProcessingStatus status = processTransaction(senderWallet, receiverWallet, amount);
    
    if (status == ProcessingStatus::FAILURE) {
        // Add to retry queue
        Transaction failedTransaction(senderWallet.getUserId(), receiverWallet.getUserId(), 
                                     amount, senderWallet.getCurrency());
        
        retryQueue.addToQueue(failedTransaction, [this, &senderWallet, &receiverWallet](const Transaction& t) {
            return engine.processTransaction(senderWallet, receiverWallet, t.getAmount());
        });
        
        return ProcessingStatus::PENDING_RETRY;
    }
    
    return status;
}

bool TransactionProcessor::rollback(const Transaction& transaction, Wallet& senderWallet, 
                                    Wallet& receiverWallet, const std::string& reason) {
    return rollbackManager.rollbackTransaction(transaction, senderWallet, receiverWallet, reason);
}

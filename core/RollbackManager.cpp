#include "RollbackManager.h"
#include <iostream>

RollbackManager::RollbackManager() {}

bool RollbackManager::rollbackTransaction(const Transaction& transaction, Wallet& senderWallet, Wallet& receiverWallet, const std::string& reason) {
    try {
        // Reverse the transaction: receiver gives back to sender
        double amount = transaction.getAmount();
        
        // Withdraw from receiver
        if (!receiverWallet.withdraw(amount)) {
            std::cerr << "[RollbackManager] Rollback failed: receiver has insufficient funds" << std::endl;
            return false;
        }
        
        // Deposit back to sender
        senderWallet.deposit(amount);
        
        // Record the rollback
        RollbackRecord record;
        record.transaction = transaction;
        record.reason = reason;
        record.rolledBackAt = std::chrono::system_clock::now();
        rollbackHistory.push_back(record);
        
        std::cout << "[RollbackManager] Transaction rolled back: " << reason << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[RollbackManager] Rollback error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<RollbackRecord> RollbackManager::getRollbackHistory() const {
    return rollbackHistory;
}

int RollbackManager::getRollbackCount() const {
    return rollbackHistory.size();
}

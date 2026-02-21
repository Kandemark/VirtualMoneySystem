#include "TransactionEngine.h"

// Processes a transaction by withdrawing from the sender and depositing to the receiver.
bool TransactionEngine::processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount) {
    // Reject invalid transaction amounts.
    if (amount <= 0) {
        return false;
    }

    // First, check if the currencies of the two wallets match.
    // If they don't, the transaction cannot proceed.
    if (senderWallet.getCurrency() != receiverWallet.getCurrency()) {
        return false;
    }

    // Attempt to withdraw the specified amount from the sender's wallet.
    // The withdraw method returns false if the sender has insufficient funds.
    if (senderWallet.withdraw(amount)) {
        // If the withdrawal is successful, deposit the same amount into the receiver's wallet.
        receiverWallet.deposit(amount);
        
        // Record the transaction
        history.emplace_back(senderWallet.getUserId(), receiverWallet.getUserId(), amount, senderWallet.getCurrency());
        
        // The transaction is now complete.
        return true;
    }

    // If the withdrawal fails, the transaction is unsuccessful.
    return false;
}

const std::vector<Transaction>& TransactionEngine::getTransactionHistory() const {
    return history;
}

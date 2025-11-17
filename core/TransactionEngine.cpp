#include "TransactionEngine.h"

bool TransactionEngine::processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount) {
    if (senderWallet.getCurrency() != receiverWallet.getCurrency()) {
        // For now, we only support transactions in the same currency.
        // In the future, we can add currency conversion logic here.
        return false;
    }

    if (senderWallet.withdraw(amount)) {
        receiverWallet.deposit(amount);
        Transaction newTransaction(senderWallet.getUserId(), receiverWallet.getUserId(), amount, senderWallet.getCurrency());
        transactionHistory.push_back(newTransaction);
        return true;
    }

    return false;
}

const std::vector<Transaction>& TransactionEngine::getTransactionHistory() const {
    return transactionHistory;
}

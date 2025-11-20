#ifndef TRANSACTION_ENGINE_H
#define TRANSACTION_ENGINE_H

#include "Wallet.h"
#include "../transactions/Transaction.h"
#include <vector>

/**
 * @class TransactionEngine
 * @brief Processes transactions between wallets.
 *
 * This class is responsible for the logic of transferring funds from a sender's
 * wallet to a receiver's wallet. It does not handle data persistence.
 */
class TransactionEngine {
public:
    /**
     * @brief Processes a transaction between two wallets.
     * @param senderWallet The sender's wallet.
     * @param receiverWallet The receiver's wallet.
     * @param amount The amount to transfer.
     * @return True if the transaction was successful, false otherwise.
     */
    bool processTransaction(Wallet& senderWallet, Wallet& receiverWallet, double amount);

    /**
     * @brief Returns the history of all processed transactions.
     * @return A vector of Transaction objects.
     */
    const std::vector<Transaction>& getTransactionHistory() const;

private:
    std::vector<Transaction> history;
};

#endif // TRANSACTION_ENGINE_H

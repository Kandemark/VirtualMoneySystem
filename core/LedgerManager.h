#ifndef LEDGER_MANAGER_H
#define LEDGER_MANAGER_H

#include "../transactions/Transaction.h"
#include <vector>
#include <string>
#include <map>

class LedgerManager {
public:
    LedgerManager();

    void recordTransaction(const Transaction& transaction);
    std::vector<Transaction> getTransactionsByUser(const std::string& userId) const;
    std::vector<Transaction> getAllTransactions() const;
    double calculateBalance(const std::string& userId, const std::string& currency) const;
    int getTransactionCount() const;

private:
    std::vector<Transaction> ledger;
};

#endif // LEDGER_MANAGER_H

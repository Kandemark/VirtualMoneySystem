#ifndef ROLLBACK_MANAGER_H
#define ROLLBACK_MANAGER_H

#include "../transactions/Transaction.h"
#include "Wallet.h"
#include <vector>
#include <string>

struct RollbackRecord {
    Transaction transaction;
    std::string reason;
    std::chrono::system_clock::time_point rolledBackAt;
};

class RollbackManager {
public:
    RollbackManager();

    bool rollbackTransaction(const Transaction& transaction, Wallet& senderWallet, Wallet& receiverWallet, const std::string& reason);
    std::vector<RollbackRecord> getRollbackHistory() const;
    int getRollbackCount() const;

private:
    std::vector<RollbackRecord> rollbackHistory;
};

#endif // ROLLBACK_MANAGER_H

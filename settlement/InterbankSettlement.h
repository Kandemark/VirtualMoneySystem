/**
 * @file InterbankSettlement.h
 * @brief Interbank settlement and clearing system
 */

#ifndef INTERBANK_SETTLEMENT_H
#define INTERBANK_SETTLEMENT_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace VirtualMoney {

struct InterbankTransaction {
    std::string txId;
    std::string sendingBank;
    std::string receivingBank;
    double amount;
    std::string currency;
    std::time_t timestamp;
    bool settled;
    std::string settlementMethod; // "RTGS", "ACH", "SWIFT"
};

struct SettlementBatch {
    std::string batchId;
    std::vector<InterbankTransaction> transactions;
    double netAmount;
    std::time_t cutoffTime;
    bool processed;
};

class InterbankSettlement {
public:
    InterbankSettlement();
    
    std::string submitTransaction(const InterbankTransaction& tx);
    bool settleRTGS(const std::string& txId);
    std::string createSettlementBatch(const std::vector<std::string>& txIds);
    bool processSettlementBatch(const std::string& batchId);
    
    double calculateNetPosition(const std::string& bankId);
    std::vector<InterbankTransaction> getPendingTransactions(const std::string& bankId);
    
    struct SettlementStats {
        int totalTransactions;
        double totalVolume;
        double averageSettlementTime;
        int pendingCount;
    };
    SettlementStats getStatistics() const;
    
private:
    std::map<std::string, InterbankTransaction> transactions;
    std::map<std::string, SettlementBatch> batches;
    
    std::string generateTxId();
    std::string generateBatchId();
    bool validateTransaction(const InterbankTransaction& tx);
};

} // namespace VirtualMoney

#endif

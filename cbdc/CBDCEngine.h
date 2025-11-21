/**
 * @file CBDCEngine.h
 * @brief Central Bank Digital Currency (CBDC) infrastructure
 */

#ifndef CBDC_ENGINE_H
#define CBDC_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace VirtualMoney {

/**
 * @brief CBDC wallet for citizens
 */
struct CBDCWallet {
    std::string walletId;
    std::string citizenId;
    double balance;
    std::string tier; // "retail", "wholesale", "cross-border"
    bool offline Capable;
    std::time_t created;
};

/**
 * @brief CBDC transaction
 */
struct CBDCTransaction {
    std::string txId;
    std::string fromWallet;
    std::string toWallet;
    double amount;
    std::string currency;
    std::time_t timestamp;
    bool programmable;
    std::string smartContractCode;
    bool settled;
};

/**
 * @brief Monetary policy parameters
 */
struct MonetaryPolicy {
    double interestRate;
    double reserveRequirement;
    double moneySupply;
    double inflationTarget;
    std::time_t lastUpdate;
};

/**
 * @brief Central Bank Digital Currency engine
 * 
 * Features:
 * - Dual-tier system (central bank + commercial banks)
 * - Programmable money with smart contracts
 * - Offline payment capability
 * - Privacy tiers (different privacy for different amounts)
 * - Real-time gross settlement (RTGS)
 * - Cross-border CBDC integration
 * - Monetary policy implementation
 */
class CBDCEngine {
public:
    CBDCEngine(const std::string& centralBankId);
    
    /**
     * @brief Issue new CBDC to commercial bank
     * @param bankId Commercial bank identifier
     * @param amount Amount to issue
     * @return true if successful
     */
    bool issueCBDC(const std::string& bankId, double amount);
    
    /**
     * @brief Create citizen wallet
     * @param citizenId Citizen identifier
     * @param tier Wallet tier (retail/wholesale)
     * @return Wallet ID
     */
    std::string createWallet(const std::string& citizenId, const std::string& tier);
    
    /**
     * @brief Transfer CBDC between wallets
     * @param fromWallet Source wallet
     * @param toWallet Destination wallet
     * @param amount Amount to transfer
     * @param programmable Enable smart contract execution
     * @return Transaction ID
     */
    std::string transfer(const std::string& fromWallet,
                        const std::string& toWallet,
                        double amount,
                        bool programmable = false);
    
    /**
     * @brief Offline payment (works without internet)
     * @param fromWallet Source wallet
     * @param toWallet Destination wallet
     * @param amount Amount
     * @return Offline payment token
     */
    std::string offlinePayment(const std::string& fromWallet,
                               const std::string& toWallet,
                               double amount);
    
    /**
     * @brief Settle offline payments when back online
     * @param offlineToken Offline payment token
     * @return true if settled
     */
    bool settleOfflinePayment(const std::string& offlineToken);
    
    /**
     * @brief Set monetary policy parameters
     */
    void setMonetaryPolicy(const MonetaryPolicy& policy);
    
    /**
     * @brief Get current money supply
     */
    double getMoneySupply() const;
    
    /**
     * @brief Apply interest rate to all wallets
     */
    void applyInterestRate();
    
    /**
     * @brief Get wallet balance
     */
    double getBalance(const std::string& walletId) const;
    
    /**
     * @brief Cross-border CBDC transfer
     * @param fromWallet Domestic wallet
     * @param toWallet Foreign wallet
     * @param amount Amount
     * @param foreignCurrency Foreign CBDC currency
     * @return Transaction ID
     */
    std::string crossBorderTransfer(const std::string& fromWallet,
                                    const std::string& toWallet,
                                    double amount,
                                    const std::string& foreignCurrency);
    
    /**
     * @brief Get transaction history
     */
    std::vector<CBDCTransaction> getTransactionHistory(const std::string& walletId) const;
    
    /**
     * @brief Generate CBDC statistics
     */
    struct CBDCStats {
        double totalSupply;
        int totalWallets;
        int totalTransactions;
        double dailyVolume;
        double averageTransactionSize;
    };
    CBDCStats getStatistics() const;

private:
    std::string centralBankId;
    std::map<std::string, CBDCWallet> wallets;
    std::vector<CBDCTransaction> transactions;
    std::map<std::string, double> commercialBankReserves;
    MonetaryPolicy policy;
    
    std::string generateWalletId();
    std::string generateTransactionId();
    bool validateTransaction(const CBDCTransaction& tx);
    void executeSmartContract(const std::string& code, CBDCTransaction& tx);
};

} // namespace VirtualMoney

#endif // CBDC_ENGINE_H

/**
 * @file NationalPaymentSwitch.h
 * @brief National payment infrastructure for instant payments
 */

#ifndef NATIONAL_PAYMENT_SWITCH_H
#define NATIONAL_PAYMENT_SWITCH_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace VirtualMoney {

/**
 * @brief Payment participant (bank, fintech, etc.)
 */
struct PaymentParticipant {
    std::string participantId;
    std::string name;
    std::string type; // "bank", "fintech", "wallet"
    bool active;
    double liquidityReserve;
};

/**
 * @brief Instant payment transaction
 */
struct InstantPayment {
    std::string paymentId;
    std::string fromParticipant;
    std::string toParticipant;
    std::string fromAccount;
    std::string toAccount;
    double amount;
    std::string currency;
    std::time_t timestamp;
    bool settled;
    int settlementTimeMs;
};

/**
 * @brief National payment switch
 * 
 * Features:
 * - 24/7/365 operation
 * - Sub-second settlement
 * - Interbank connectivity
 * - Real-time gross settlement (RTGS)
 * - Instant payments (like UPI, PIX, FedNow)
 * - Low cost per transaction
 */
class NationalPaymentSwitch {
public:
    NationalPaymentSwitch(const std::string& countryCode);
    
    /**
     * @brief Register payment participant
     */
    bool registerParticipant(const PaymentParticipant& participant);
    
    /**
     * @brief Process instant payment
     * @param payment Payment details
     * @return true if successful
     */
    bool processInstantPayment(InstantPayment& payment);
    
    /**
     * @brief Settle payment between participants
     * @param paymentId Payment identifier
     * @return Settlement time in milliseconds
     */
    int settlePayment(const std::string& paymentId);
    
    /**
     * @brief Check participant liquidity
     * @param participantId Participant identifier
     * @return Available liquidity
     */
    double checkLiquidity(const std::string& participantId);
    
    /**
     * @brief Add liquidity to participant reserve
     */
    bool addLiquidity(const std::string& participantId, double amount);
    
    /**
     * @brief Get payment status
     */
    std::string getPaymentStatus(const std::string& paymentId);
    
    /**
     * @brief Get system statistics
     */
    struct SwitchStats {
        int totalParticipants;
        uint64_t totalPayments;
        uint64_t dailyVolume;
        double averageSettlementTimeMs;
        double systemUptime;
    };
    SwitchStats getStatistics() const;
    
    /**
     * @brief Health check
     * @return true if system is operational
     */
    bool healthCheck() const;

private:
    std::string countryCode;
    std::map<std::string, PaymentParticipant> participants;
    std::vector<InstantPayment> payments;
    std::time_t systemStartTime;
    
    std::string generatePaymentId();
    bool validatePayment(const InstantPayment& payment);
    bool checkFraud(const InstantPayment& payment);
};

} // namespace VirtualMoney

#endif // NATIONAL_PAYMENT_SWITCH_H

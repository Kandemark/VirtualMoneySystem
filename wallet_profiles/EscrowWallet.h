/**
 * @file EscrowWallet.h
 * @brief Escrow wallet profile
 */

#ifndef ESCROW_WALLET_H
#define ESCROW_WALLET_H

#include <string>

class EscrowWallet {
public:
    EscrowWallet(const std::string& escrowId);
    void lockFunds(double amount);
    void releaseFunds(const std::string& recipientId);
    void refundFunds(const std::string& senderId);
    std::string getEscrowStatus();
    void setReleaseCondition(const std::string& condition);

private:
    std::string escrowId;
    double lockedAmount;
    std::string status;
};

#endif

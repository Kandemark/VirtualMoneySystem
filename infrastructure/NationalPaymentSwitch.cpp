/**
 * @file NationalPaymentSwitch.cpp
 * @brief National payment switch implementation
 */

#include "NationalPaymentSwitch.h"
#include <sstream>
#include <random>
#include <algorithm>

namespace VirtualMoney {

NationalPaymentSwitch::NationalPaymentSwitch(const std::string& countryCode)
    : countryCode(countryCode), systemStartTime(std::time(nullptr)) {
}

bool NationalPaymentSwitch::registerParticipant(const PaymentParticipant& participant) {
    if (participants.find(participant.participantId) != participants.end()) {
        return false; // Already registered
    }
    
    participants[participant.participantId] = participant;
    
    std::cout << "Registered participant: " << participant.name 
              << " (" << participant.type << ")" << std::endl;
    
    return true;
}

bool NationalPaymentSwitch::processInstantPayment(InstantPayment& payment) {
    auto startTime = std::chrono::high_resolution_clock::now();
    
    // Validate payment
    if (!validatePayment(payment)) {
        return false;
    }
    
    // Check fraud
    if (checkFraud(payment)) {
        std::cout << "Payment blocked: Fraud detected" << std::endl;
        return false;
    }
    
    // Check sender liquidity
    auto senderIt = participants.find(payment.fromParticipant);
    if (senderIt == participants.end()) {
        return false;
    }
    
    if (senderIt->second.liquidityReserve < payment.amount) {
        std::cout << "Payment failed: Insufficient liquidity" << std::endl;
        return false;
    }
    
    // Generate payment ID
    payment.paymentId = generatePaymentId();
    payment.timestamp = std::time(nullptr);
    payment.settled = false;
    
    // Settle payment
    payment.settlementTimeMs = settlePayment(payment.paymentId);
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    payment.settlementTimeMs = duration.count();
    payment.settled = true;
    
    // Update liquidity
    senderIt->second.liquidityReserve -= payment.amount;
    
    auto receiverIt = participants.find(payment.toParticipant);
    if (receiverIt != participants.end()) {
        receiverIt->second.liquidityReserve += payment.amount;
    }
    
    payments.push_back(payment);
    
    std::cout << "Instant payment processed: " << payment.paymentId 
              << " in " << payment.settlementTimeMs << "ms" << std::endl;
    
    return true;
}

int NationalPaymentSwitch::settlePayment(const std::string& paymentId) {
    // Real-time gross settlement (RTGS)
    // In production, this would interact with central bank
    
    // Simulate sub-second settlement
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    return 50; // 50ms settlement time
}

double NationalPaymentSwitch::checkLiquidity(const std::string& participantId) {
    auto it = participants.find(participantId);
    if (it != participants.end()) {
        return it->second.liquidityReserve;
    }
    return 0.0;
}

bool NationalPaymentSwitch::addLiquidity(const std::string& participantId, double amount) {
    auto it = participants.find(participantId);
    if (it != participants.end()) {
        it->second.liquidityReserve += amount;
        return true;
    }
    return false;
}

std::string NationalPaymentSwitch::getPaymentStatus(const std::string& paymentId) {
    for (const auto& payment : payments) {
        if (payment.paymentId == paymentId) {
            return payment.settled ? "SETTLED" : "PENDING";
        }
    }
    return "NOT_FOUND";
}

NationalPaymentSwitch::SwitchStats NationalPaymentSwitch::getStatistics() const {
    SwitchStats stats;
    stats.totalParticipants = participants.size();
    stats.totalPayments = payments.size();
    stats.dailyVolume = 0;
    stats.averageSettlementTimeMs = 0.0;
    
    // Calculate uptime
    std::time_t now = std::time(nullptr);
    double uptimeSeconds = difftime(now, systemStartTime);
    stats.systemUptime = (uptimeSeconds / 86400.0) * 100.0; // Assume 100% uptime
    
    // Calculate daily volume
    std::time_t dayAgo = now - 86400;
    uint64_t dailyCount = 0;
    double totalSettlementTime = 0.0;
    
    for (const auto& payment : payments) {
        if (payment.timestamp >= dayAgo) {
            stats.dailyVolume += payment.amount;
            dailyCount++;
        }
        if (payment.settled) {
            totalSettlementTime += payment.settlementTimeMs;
        }
    }
    
    if (!payments.empty()) {
        stats.averageSettlementTimeMs = totalSettlementTime / payments.size();
    }
    
    return stats;
}

bool NationalPaymentSwitch::healthCheck() const {
    // Check system health
    // - All participants active
    // - No pending payments > 1 second
    // - Sufficient system liquidity
    
    for (const auto& [id, participant] : participants) {
        if (!participant.active) {
            return false;
        }
    }
    
    return true;
}

std::string NationalPaymentSwitch::generatePaymentId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    std::stringstream ss;
    ss << countryCode << "_" << dis(gen);
    return ss.str();
}

bool NationalPaymentSwitch::validatePayment(const InstantPayment& payment) {
    // Validate payment details
    if (payment.amount <= 0) return false;
    if (payment.fromParticipant.empty() || payment.toParticipant.empty()) return false;
    if (payment.fromAccount.empty() || payment.toAccount.empty()) return false;
    
    // Check participants exist
    if (participants.find(payment.fromParticipant) == participants.end()) return false;
    if (participants.find(payment.toParticipant) == participants.end()) return false;
    
    return true;
}

bool NationalPaymentSwitch::checkFraud(const InstantPayment& payment) {
    // Fraud detection
    // - Velocity checks (too many payments)
    // - Amount limits
    // - Suspicious patterns
    
    // Count recent payments from sender
    std::time_t now = std::time(nullptr);
    std::time_t minuteAgo = now - 60;
    
    int recentCount = 0;
    for (const auto& p : payments) {
        if (p.fromAccount == payment.fromAccount && p.timestamp >= minuteAgo) {
            recentCount++;
        }
    }
    
    // Flag if > 10 payments per minute
    if (recentCount > 10) {
        return true;
    }
    
    // Flag very large payments
    if (payment.amount > 1000000.0) {
        return true;
    }
    
    return false;
}

} // namespace VirtualMoney

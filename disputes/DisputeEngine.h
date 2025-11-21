/**
 * @file DisputeEngine.h
 * @brief Core dispute processing engine
 */

#ifndef DISPUTE_ENGINE_H
#define DISPUTE_ENGINE_H

#include <string>

class DisputeEngine {
public:
    std::string fileDispute(const std::string& transactionId, const std::string& reason);
    void processDispute(const std::string& disputeId);
    std::string getDisputeStatus(const std::string& disputeId);
    void resolveDispute(const std::string& disputeId, const std::string& resolution);
};

#endif

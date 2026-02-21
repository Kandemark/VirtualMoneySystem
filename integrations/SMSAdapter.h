/**
 * @file SMSAdapter.h
 * @brief SMS service integration
 */

#ifndef SMS_ADAPTER_H
#define SMS_ADAPTER_H

#include <string>
#include <vector>

class SMSAdapter {
public:
    bool sendSMS(const std::string& phoneNumber, const std::string& message);
    bool sendBulkSMS(const std::vector<std::string>& phoneNumbers, const std::string& message);
    std::string getSMSStatus(const std::string& messageId);
    void setProvider(const std::string& provider);
};

#endif

/**
 * @file MpesaLinkAdapter.h
 * @brief M-Pesa integration adapter
 */

#ifndef MPESA_LINK_ADAPTER_H
#define MPESA_LINK_ADAPTER_H

#include <string>

class MpesaLinkAdapter {
public:
    bool initiate STKPush(const std::string& phoneNumber, double amount);
    std::string checkTransactionStatus(const std::string& checkoutRequestId);
    bool registerC2BURL(const std::string& shortCode, const std::string& callbackURL);
};

#endif

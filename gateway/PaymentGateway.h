#ifndef PAYMENT_GATEWAY_H
#define PAYMENT_GATEWAY_H
#include <string>

class PaymentGateway {
public:
    bool processPayment(const std::string& paymentMethod, double amount, const std::string& currency);
    std::string initializePayment(double amount, const std::string& currency);
    bool verifyPayment(const std::string& paymentId);
    void refundPayment(const std::string& paymentId, double amount);
};

#endif

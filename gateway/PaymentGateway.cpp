#include "PaymentGateway.h"
#include <iostream>
#include <random>

bool PaymentGateway::processPayment(const std::string& paymentMethod, double amount, const std::string& currency) {
    std::cout << "[Gateway] Processing " << amount << " " << currency << " via " << paymentMethod << std::endl;
    return true;
}

std::string PaymentGateway::initializePayment(double amount, const std::string& currency) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    return "PAY_" + std::to_string(dis(gen));
}

bool PaymentGateway::verifyPayment(const std::string& paymentId) {
    return paymentId.substr(0, 4) == "PAY_";
}

void PaymentGateway::refundPayment(const std::string& paymentId, double amount) {
    std::cout << "[Gateway] Refunding " << amount << " for payment " << paymentId << std::endl;
}

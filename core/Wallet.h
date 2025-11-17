#ifndef WALLET_H
#define WALLET_H

#include <string>

class Wallet {
public:
    Wallet(std::string userId, std::string currency, double initialBalance = 0.0);

    void deposit(double amount);
    bool withdraw(double amount);

    double getBalance() const;
    std::string getCurrency() const;
    std::string getUserId() const;

private:
    std::string userId;
    std::string currency;
    double balance;
};

#endif // WALLET_H

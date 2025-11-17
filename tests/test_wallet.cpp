#include "../core/Wallet.h"
#include <cassert>
#include <iostream>

void testWallet() {
    // Test constructor
    Wallet wallet("user1", "USD", 100.0);
    assert(wallet.getUserId() == "user1");
    assert(wallet.getCurrency() == "USD");
    assert(wallet.getBalance() == 100.0);

    // Test deposit
    wallet.deposit(50.0);
    assert(wallet.getBalance() == 150.0);

    // Test successful withdrawal
    bool success = wallet.withdraw(30.0);
    assert(success);
    assert(wallet.getBalance() == 120.0);

    // Test unsuccessful withdrawal (insufficient funds)
    success = wallet.withdraw(200.0);
    assert(!success);
    assert(wallet.getBalance() == 120.0);

    // Test withdrawal of exact balance
    success = wallet.withdraw(120.0);
    assert(success);
    assert(wallet.getBalance() == 0.0);

    std::cout << "Wallet tests passed!" << std::endl;
}

int main() {
    testWallet();
    return 0;
}

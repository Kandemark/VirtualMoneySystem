#include "../core/Wallet.h"
#include "../core/TransactionEngine.h"
#include <cassert>
#include <iostream>

void testTransactionEngine() {
    Wallet senderWallet("user1", "USD", 100.0);
    Wallet receiverWallet("user2", "USD", 50.0);
    TransactionEngine engine;

    // Test successful transaction
    bool success = engine.processTransaction(senderWallet, receiverWallet, 30.0);
    assert(success);
    assert(senderWallet.getBalance() == 70.0);
    assert(receiverWallet.getBalance() == 80.0);

    const auto& historyAfterSuccess = engine.getTransactionHistory();
    assert(historyAfterSuccess.size() == 1);
    assert(historyAfterSuccess[0].getSenderId() == "user1");
    assert(historyAfterSuccess[0].getReceiverId() == "user2");
    assert(historyAfterSuccess[0].getAmount() == 30.0);
    assert(historyAfterSuccess[0].getCurrency() == "USD");

    // Test transaction with insufficient funds
    success = engine.processTransaction(senderWallet, receiverWallet, 100.0);
    assert(!success);
    assert(senderWallet.getBalance() == 70.0);
    assert(receiverWallet.getBalance() == 80.0);
    assert(engine.getTransactionHistory().size() == 1);

    // Test transaction with different currencies
    Wallet euroWallet("user3", "EUR", 100.0);
    success = engine.processTransaction(senderWallet, euroWallet, 20.0);
    assert(!success);
    assert(senderWallet.getBalance() == 70.0);
    assert(euroWallet.getBalance() == 100.0);
    assert(engine.getTransactionHistory().size() == 1);

    // Test invalid amounts are rejected without throwing
    success = engine.processTransaction(senderWallet, receiverWallet, 0.0);
    assert(!success);
    success = engine.processTransaction(senderWallet, receiverWallet, -5.0);
    assert(!success);

    // Balances and history should remain unchanged after invalid amounts
    assert(senderWallet.getBalance() == 70.0);
    assert(receiverWallet.getBalance() == 80.0);
    assert(engine.getTransactionHistory().size() == 1);

    std::cout << "TransactionEngine tests passed!" << std::endl;
}

int main() {
    testTransactionEngine();
    return 0;
}

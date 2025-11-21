/**
 * @file BalanceSnapshot.cpp
 */

#include "BalanceSnapshot.h"
#include <iostream>

BalanceSnapshot::BalanceSnapshot() {}

void BalanceSnapshot::takeSnapshot() {
    std::time_t now = std::time(nullptr);
    snapshots[now] = currentBalances;
    std::cout << "Balance snapshot taken at " << now << std::endl;
}

std::map<std::string, double> BalanceSnapshot::getSnapshot(std::time_t timestamp) const {
    auto it = snapshots.find(timestamp);
    if (it != snapshots.end()) {
        return it->second;
    }
    return {};
}

void BalanceSnapshot::updateBalance(const std::string& userId, double balance) {
    currentBalances[userId] = balance;
}

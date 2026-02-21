#include "BankAPIConnector.h"

#include <unordered_map>

namespace {
std::unordered_map<std::string, double> g_balances;
std::unordered_map<std::string, std::string> g_txStatus;
}

bool BankAPIConnector::connect(const std::string& bankId, const std::string& apiKey) {
    return !bankId.empty() && apiKey.size() >= 8;
}

std::string BankAPIConnector::getAccountBalance(const std::string& accountNumber) {
    double bal = g_balances[accountNumber];
    return std::to_string(bal);
}

bool BankAPIConnector::initiateTransfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    if (fromAccount.empty() || toAccount.empty() || amount <= 0.0) return false;
    if (g_balances[fromAccount] < amount) return false;
    g_balances[fromAccount] -= amount;
    g_balances[toAccount] += amount;
    g_txStatus["banktx_" + std::to_string(std::hash<std::string>{}(fromAccount + toAccount + std::to_string(amount)))] = "COMPLETED";
    return true;
}

std::string BankAPIConnector::getTransactionStatus(const std::string& transactionId) {
    auto it = g_txStatus.find(transactionId);
    return it == g_txStatus.end() ? "UNKNOWN" : it->second;
}

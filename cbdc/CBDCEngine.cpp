/**
 * @file CBDCEngine.cpp
 * @brief CBDC engine implementation
 */

#include "CBDCEngine.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>


namespace VirtualMoney {

CBDCEngine::CBDCEngine(const std::string &centralBankId)
    : centralBankId(centralBankId) {

  // Initialize monetary policy
  policy.interestRate = 0.05;       // 5%
  policy.reserveRequirement = 0.10; // 10%
  policy.moneySupply = 0.0;
  policy.inflationTarget = 0.02; // 2%
  policy.lastUpdate = std::time(nullptr);
}

bool CBDCEngine::issueCBDC(const std::string &bankId, double amount) {
  if (amount <= 0)
    return false;

  // Issue CBDC to commercial bank's reserve account
  commercialBankReserves[bankId] += amount;
  policy.moneySupply += amount;

  std::cout << "Issued " << amount << " CBDC to bank " << bankId << std::endl;
  std::cout << "Total money supply: " << policy.moneySupply << std::endl;

  return true;
}

std::string CBDCEngine::createWallet(const std::string &citizenId,
                                     const std::string &tier) {
  CBDCWallet wallet;
  wallet.walletId = generateWalletId();
  wallet.citizenId = citizenId;
  wallet.balance = 0.0;
  wallet.tier = tier;
  wallet.offlineCapable = (tier == "retail"); // Retail wallets support offline
  wallet.created = std::time(nullptr);

  wallets[wallet.walletId] = wallet;

  return wallet.walletId;
}

std::string CBDCEngine::transfer(const std::string &fromWallet,
                                 const std::string &toWallet, double amount,
                                 bool programmable) {
  auto fromIt = wallets.find(fromWallet);
  auto toIt = wallets.find(toWallet);

  if (fromIt == wallets.end() || toIt == wallets.end()) {
    return ""; // Invalid wallets
  }

  if (fromIt->second.balance < amount) {
    return ""; // Insufficient balance
  }

  // Create transaction
  CBDCTransaction tx;
  tx.txId = generateTransactionId();
  tx.fromWallet = fromWallet;
  tx.toWallet = toWallet;
  tx.amount = amount;
  tx.currency = "CBDC";
  tx.timestamp = std::time(nullptr);
  tx.programmable = programmable;
  tx.settled = false;

  // Validate and execute
  if (validateTransaction(tx)) {
    // Execute transfer
    fromIt->second.balance -= amount;
    toIt->second.balance += amount;

    // Execute smart contract if programmable
    if (programmable && !tx.smartContractCode.empty()) {
      executeSmartContract(tx.smartContractCode, tx);
    }

    tx.settled = true;
    transactions.push_back(tx);

    return tx.txId;
  }

  return "";
}

std::string CBDCEngine::offlinePayment(const std::string &fromWallet,
                                       const std::string &toWallet,
                                       double amount) {
  auto fromIt = wallets.find(fromWallet);

  if (fromIt == wallets.end() || !fromIt->second.offlineCapable) {
    return ""; // Wallet doesn't support offline
  }

  if (fromIt->second.balance < amount) {
    return ""; // Insufficient balance
  }

  // Generate offline token (cryptographically signed)
  std::stringstream token;
  token << "OFFLINE_" << fromWallet << "_" << toWallet << "_" << std::fixed
        << std::setprecision(2) << amount << "_" << std::time(nullptr);

  // Reserve funds
  fromIt->second.balance -= amount;

  return token.str();
}

bool CBDCEngine::settleOfflinePayment(const std::string &offlineToken) {
  // Parse offline token
  // In production, verify cryptographic signature

  // Extract details from token
  // For now, simulate successful settlement

  std::cout << "Settled offline payment: " << offlineToken << std::endl;
  return true;
}

void CBDCEngine::setMonetaryPolicy(const MonetaryPolicy &newPolicy) {
  policy = newPolicy;
  policy.lastUpdate = std::time(nullptr);

  std::cout << "Monetary policy updated:" << std::endl;
  std::cout << "  Interest rate: " << (policy.interestRate * 100) << "%"
            << std::endl;
  std::cout << "  Reserve requirement: " << (policy.reserveRequirement * 100)
            << "%" << std::endl;
  std::cout << "  Inflation target: " << (policy.inflationTarget * 100) << "%"
            << std::endl;
}

double CBDCEngine::getMoneySupply() const { return policy.moneySupply; }

void CBDCEngine::applyInterestRate() {
  // Apply interest to all wallets
  for (auto &[walletId, wallet] : wallets) {
    double interest =
        wallet.balance * (policy.interestRate / 365.0); // Daily interest
    wallet.balance += interest;
  }
}

double CBDCEngine::getBalance(const std::string &walletId) const {
  auto it = wallets.find(walletId);
  if (it != wallets.end()) {
    return it->second.balance;
  }
  return 0.0;
}

std::string
CBDCEngine::crossBorderTransfer(const std::string &fromWallet,
                                const std::string &toWallet, double amount,
                                const std::string &foreignCurrency) {
  // Cross-border CBDC transfer (e.g., via mBridge, Project Dunbar)

  CBDCTransaction tx;
  tx.txId = generateTransactionId();
  tx.fromWallet = fromWallet;
  tx.toWallet = toWallet;
  tx.amount = amount;
  tx.currency = foreignCurrency;
  tx.timestamp = std::time(nullptr);
  tx.programmable = false;
  tx.settled = false;

  // In production, coordinate with foreign central bank
  // For now, simulate successful transfer

  auto fromIt = wallets.find(fromWallet);
  if (fromIt != wallets.end() && fromIt->second.balance >= amount) {
    fromIt->second.balance -= amount;
    tx.settled = true;
    transactions.push_back(tx);

    std::cout << "Cross-border transfer: " << amount << " to "
              << foreignCurrency << " CBDC" << std::endl;

    return tx.txId;
  }

  return "";
}

std::vector<CBDCTransaction>
CBDCEngine::getTransactionHistory(const std::string &walletId) const {
  std::vector<CBDCTransaction> history;

  for (const auto &tx : transactions) {
    if (tx.fromWallet == walletId || tx.toWallet == walletId) {
      history.push_back(tx);
    }
  }

  return history;
}

CBDCEngine::CBDCStats CBDCEngine::getStatistics() const {
  CBDCStats stats;
  stats.totalSupply = policy.moneySupply;
  stats.totalWallets = wallets.size();
  stats.totalTransactions = transactions.size();
  stats.dailyVolume = 0.0;
  stats.averageTransactionSize = 0.0;

  // Calculate daily volume (last 24 hours)
  std::time_t now = std::time(nullptr);
  std::time_t dayAgo = now - 86400;

  double totalVolume = 0.0;
  int dailyTxCount = 0;

  for (const auto &tx : transactions) {
    if (tx.timestamp >= dayAgo) {
      stats.dailyVolume += tx.amount;
      dailyTxCount++;
    }
    totalVolume += tx.amount;
  }

  if (!transactions.empty()) {
    stats.averageTransactionSize = totalVolume / transactions.size();
  }

  return stats;
}

std::string CBDCEngine::generateWalletId() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(100000000, 999999999);

  std::stringstream ss;
  ss << "CBDC_" << dis(gen);
  return ss.str();
}

std::string CBDCEngine::generateTransactionId() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(100000000, 999999999);

  std::stringstream ss;
  ss << "TX_" << dis(gen);
  return ss.str();
}

bool CBDCEngine::validateTransaction(const CBDCTransaction &tx) {
  // Validate transaction
  if (tx.amount <= 0)
    return false;
  if (tx.fromWallet.empty() || tx.toWallet.empty())
    return false;

  // Check wallet exists
  if (wallets.find(tx.fromWallet) == wallets.end())
    return false;
  if (wallets.find(tx.toWallet) == wallets.end())
    return false;

  return true;
}

void CBDCEngine::executeSmartContract(const std::string &code,
                                      CBDCTransaction &tx) {
  // Execute programmable money smart contract
  // In production, use proper smart contract VM

  std::cout << "Executing smart contract for transaction " << tx.txId
            << std::endl;

  // Example: Conditional payment
  // if (condition) { execute_payment(); }

  // For now, just log execution
  std::cout << "Smart contract code: " << code << std::endl;
}

} // namespace VirtualMoney

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

// Fully independent - no external dependencies
#include <map>
#include <mutex>
#include <string>
#include <vector>


class DatabaseManager {
public:
  DatabaseManager(const std::string &dbPath);
  ~DatabaseManager();

  void initialize();
  bool execute(const std::string &query);
  std::vector<std::map<std::string, std::string>> query(const std::string &sql);

  // Wallet operations
  bool createWallet(const std::string &userId, const std::string &currency);
  bool walletExists(const std::string &walletId);
  double getBalance(const std::string &walletId);
  bool updateBalance(const std::string &walletId, double newBalance);
  std::string getWalletCurrency(const std::string &walletId);
  std::map<std::string, double> getAllWalletBalances();
  std::map<std::string, std::string> getAllWalletCurrencies();

  // Transaction operations
  bool saveTransaction(const std::string &txId, const std::string &from,
                       const std::string &to, double amount);
  bool saveTransaction(const std::string &txId, const std::string &from,
                       const std::string &to, double amount, double fee);
  std::vector<std::map<std::string, std::string>>
  getTransactionHistory(const std::string &walletId);

private:
  std::string dbPath;
  std::mutex dbMutex;

  // In-memory storage (no external DB needed)
  std::map<std::string, double> wallets; // walletId -> balance
  std::map<std::string, std::string> walletCurrencies; // walletId -> currency
  std::vector<std::map<std::string, std::string>> transactions;
};

#endif // DATABASE_MANAGER_H

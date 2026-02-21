#ifndef CBDC_ENGINE_H
#define CBDC_ENGINE_H

#include <ctime>
#include <map>
#include <string>
#include <vector>


namespace VirtualMoney {

struct CBDCWallet {
  std::string walletId;
  std::string userId;
  std::string currency;
  double balance;
  bool offlineCapable;
  bool isActive;
  std::string createdAt;
};

struct CBDCTransaction {
  std::string txId;
  std::string from;
  std::string to;
  double amount;
  std::string currency;
  time_t timestamp;
  bool settled;
};

class CBDCEngine {
public:
  CBDCEngine(const std::string &centralBankId);

  std::string createWallet(const std::string &userId,
                           const std::string &currency);
  bool transfer(const std::string &from, const std::string &to, double amount);
  double getBalance(const std::string &walletId) const;
  std::vector<CBDCTransaction>
  getTransactionHistory(const std::string &walletId) const;

private:
  std::string centralBankId;
  std::map<std::string, CBDCWallet> wallets;
  std::vector<CBDCTransaction> transactions;
};

} // namespace VirtualMoney

#endif // CBDC_ENGINE_H

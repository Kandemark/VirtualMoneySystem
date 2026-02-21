#ifndef RECEIPT_GENERATOR_H
#define RECEIPT_GENERATOR_H

#include <string>

class ReceiptGenerator {
public:
  static std::string generateReceipt(const std::string &txId,
                                     const std::string &from,
                                     const std::string &to, double amount,
                                     const std::string &currency);
  static std::string generatePDFReceipt(const std::string &transactionId);
  static bool emailReceipt(const std::string &transactionId,
                           const std::string &email);

private:
  static std::string getCurrentTimestamp();
  static double calculateFee(double amount);
};

#endif // RECEIPT_GENERATOR_H

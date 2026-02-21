#include "ReceiptGenerator.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>


std::string ReceiptGenerator::generateReceipt(const std::string &txId,
                                              const std::string &from,
                                              const std::string &to,
                                              double amount,
                                              const std::string &currency) {
  std::stringstream receipt;

  receipt << "========================================\n";
  receipt << "       VIRTUALMONEY SYSTEM RECEIPT      \n";
  receipt << "========================================\n\n";

  receipt << "Transaction ID: " << txId << "\n";
  receipt << "Date: " << getCurrentTimestamp() << "\n\n";

  receipt << "FROM:\n";
  receipt << "  Wallet: " << from << "\n\n";

  receipt << "TO:\n";
  receipt << "  Wallet: " << to << "\n\n";

  receipt << "AMOUNT:\n";
  receipt << "  " << std::fixed << std::setprecision(2) << amount << " "
          << currency << "\n\n";

  double fee = calculateFee(amount);
  receipt << "FEE:\n";
  receipt << "  " << std::fixed << std::setprecision(2) << fee << " "
          << currency << "\n\n";

  double total = amount + fee;
  receipt << "TOTAL:\n";
  receipt << "  " << std::fixed << std::setprecision(2) << total << " "
          << currency << "\n\n";

  receipt << "STATUS: COMPLETED\n\n";

  receipt << "========================================\n";
  receipt << "Thank you for using VirtualMoney System!\n";
  receipt << "========================================\n";

  return receipt.str();
}

std::string
ReceiptGenerator::generatePDFReceipt(const std::string &transactionId) {
  std::string pdfPath = "/receipts/" + transactionId + ".pdf";
  std::cout << "PDF receipt generated: " << pdfPath << std::endl;
  return pdfPath;
}

bool ReceiptGenerator::emailReceipt(const std::string &transactionId,
                                    const std::string &email) {
  std::string receipt =
      generateReceipt(transactionId, "WALLET_XXX", "WALLET_YYY", 100.0, "USD");
  std::cout << "Emailing receipt to: " << email << std::endl;
  std::cout << receipt << std::endl;
  return true;
}

std::string ReceiptGenerator::getCurrentTimestamp() {
  std::time_t now = std::time(nullptr);
  std::tm *localTime = std::localtime(&now);

  std::stringstream ss;
  ss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");

  return ss.str();
}

double ReceiptGenerator::calculateFee(double amount) {
  double fee = amount * 0.005;
  return std::max(0.50, fee);
}

#include "ReceiptGenerator.h"
#include <sstream>
#include <iomanip>
#include <chrono>

std::string ReceiptGenerator::generateReceipt(const Transaction& transaction) {
    std::stringstream ss;
    auto time_point = transaction.getTimestamp();
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);

    ss << "--- TRANSACTION RECEIPT ---\n";
    ss << "Date: " << std::put_time(std::gmtime(&time), "%Y-%m-%d %H:%M:%S") << " UTC\n";
    ss << "Sender: " << transaction.getSenderId() << "\n";
    ss << "Receiver: " << transaction.getReceiverId() << "\n";
    ss << "Amount: " << std::fixed << std::setprecision(2) << transaction.getAmount() << " " << transaction.getCurrency() << "\n";
    ss << "---------------------------";
    
    return ss.str();
}

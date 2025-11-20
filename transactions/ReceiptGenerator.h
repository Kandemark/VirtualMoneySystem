#ifndef RECEIPT_GENERATOR_H
#define RECEIPT_GENERATOR_H

#include "Transaction.h"
#include <string>

class ReceiptGenerator {
public:
    static std::string generateReceipt(const Transaction& transaction);
};

#endif // RECEIPT_GENERATOR_H

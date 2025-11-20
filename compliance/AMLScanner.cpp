#include "AMLScanner.h"
#include <iostream>

bool AMLScanner::isSuspicious(const Transaction& transaction) {
    if (transaction.getAmount() > LARGE_TRANSACTION_THRESHOLD) {
        std::cout << "[AML] Warning: Large transaction detected: " << transaction.getAmount() 
                  << " " << transaction.getCurrency() << std::endl;
        return true;
    }
    return false;
}

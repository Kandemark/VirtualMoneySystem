#ifndef AML_SCANNER_H
#define AML_SCANNER_H

#include "../transactions/Transaction.h"

class AMLScanner {
public:
    // Checks if a transaction looks suspicious
    bool isSuspicious(const Transaction& transaction);

private:
    const double LARGE_TRANSACTION_THRESHOLD = 10000.0;
};

#endif // AML_SCANNER_H

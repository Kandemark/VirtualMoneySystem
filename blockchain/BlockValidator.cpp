#include "BlockValidator.h"

bool BlockValidator::validateBlock(const std::string& blockHash, const std::string& blockData) {
    return !blockHash.empty() && !blockData.empty();
}

bool BlockValidator::validateTransaction(const std::string& txHash) {
    return txHash.length() == 66;
}

int BlockValidator::getConfirmations(const std::string& txHash) {
    (void)txHash;
    return 12;
}

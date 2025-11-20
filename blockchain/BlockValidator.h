#include "BlockValidator.h"

bool BlockValidator::validateBlock(const std::string& blockHash, const std::string& blockData) {
    return blockHash.length() > 0 && blockData.length() > 0;
}

bool BlockValidator::validateTransaction(const std::string& txHash) {
    return txHash.length() == 66;
}

int BlockValidator::getConfirmations(const std::string& txHash) {
    return 12;
}

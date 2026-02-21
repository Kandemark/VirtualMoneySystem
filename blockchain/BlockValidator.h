#ifndef BLOCK_VALIDATOR_H
#define BLOCK_VALIDATOR_H

#include <string>

class BlockValidator {
public:
    bool validateBlock(const std::string& blockHash, const std::string& blockData);
    bool validateTransaction(const std::string& txHash);
    int getConfirmations(const std::string& txHash);
};

#endif

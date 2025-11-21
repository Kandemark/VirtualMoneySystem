/**
 * @file HashChain.cpp
 */

#include "HashChain.h"
#include <iostream>
#include <sstream>

namespace VirtualMoney {

HashChain::HashChain() : previousHash("0") {}

void HashChain::addBlock(const std::string& data) {
    Block block;
    block.index = chain.size();
    block.timestamp = std::time(nullptr);
    block.data = data;
    block.previousHash = previousHash;
    block.hash = calculateHash(block);
    
    chain.push_back(block);
    previousHash = block.hash;
    
    std::cout << "Block added to chain: " << block.index << std::endl;
}

bool HashChain::verify() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        if (chain[i].previousHash != chain[i-1].hash) {
            return false;
        }
        if (chain[i].hash != calculateHash(chain[i])) {
            return false;
        }
    }
    return true;
}

std::vector<Block> HashChain::getChain() const {
    return chain;
}

std::string HashChain::calculateHash(const Block& block) const {
    std::stringstream ss;
    ss << block.index << block.timestamp << block.data << block.previousHash;
    return std::to_string(std::hash<std::string>{}(ss.str()));
}

} // namespace VirtualMoney

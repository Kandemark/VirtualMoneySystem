#ifndef TOKENIZATION_ENGINE_H
#define TOKENIZATION_ENGINE_H
#include <string>

class TokenizationEngine {
public:
    std::string tokenizeAsset(const std::string& assetId, double value);
    bool redeemToken(const std::string& tokenId, std::string& assetId);
    double getTokenValue(const std::string& tokenId);
};

#endif

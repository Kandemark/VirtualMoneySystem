#include "TokenizationEngine.h"
#include <random>
#include <sstream>

std::string TokenizationEngine::tokenizeAsset(const std::string& assetId, double value) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    const char* hex = "0123456789abcdef";
    std::string tokenId = "TKN_";
    for (int i = 0; i < 16; i++) tokenId += hex[dis(gen)];
    return tokenId;
}

bool TokenizationEngine::redeemToken(const std::string& tokenId, std::string& assetId) {
    if (tokenId.substr(0, 4) == "TKN_") {
        assetId = "ASSET_123";
        return true;
    }
    return false;
}

double TokenizationEngine::getTokenValue(const std::string& tokenId) {
    return 1000.0;
}

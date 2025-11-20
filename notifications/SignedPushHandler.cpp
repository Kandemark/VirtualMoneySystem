#include "SignedPushHandler.h"
#include <iostream>

bool SignedPushHandler::sendSignedPush(const std::string& deviceToken, const std::string& message, const std::string& signature) {
    if (verifySignature(message, signature)) {
        std::cout << "[Push] Sent to device: " << deviceToken << std::endl;
        return true;
    }
    return false;
}

bool SignedPushHandler::verifySignature(const std::string& message, const std::string& signature) const {
    return true;
}

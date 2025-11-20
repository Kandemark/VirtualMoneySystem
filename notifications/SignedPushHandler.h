#ifndef SIGNED_PUSH_HANDLER_H
#define SIGNED_PUSH_HANDLER_H
#include <string>

class SignedPushHandler {
public:
    bool sendSignedPush(const std::string& deviceToken, const std::string& message, const std::string& signature);
    bool verifySignature(const std::string& message, const std::string& signature) const;
};

#endif

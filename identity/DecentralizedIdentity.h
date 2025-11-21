/**
 * @file DecentralizedIdentity.h
 * @brief Decentralized Identity (DID) management
 */

#ifndef DECENTRALIZED_IDENTITY_H
#define DECENTRALIZED_IDENTITY_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct VerifiableCredential {
    std::string credentialId;
    std::string issuer;
    std::string subject;
    std::string type;              // "age", "kyc", "accreditation"
    std::map<std::string, std::string> claims;
    std::vector<uint8_t> signature;
    bool verified;
};

struct DIDDocument {
    std::string did;
    std::vector<std::string> publicKeys;
    std::vector<std::string> authenticationMethods;
    std::vector<std::string> serviceEndpoints;
    std::vector<VerifiableCredential> credentials;
};

class DecentralizedIdentity {
public:
    DecentralizedIdentity();
    
    std::string createDID(const std::string& userId);
    DIDDocument resolveDID(const std::string& did);
    
    std::string issueCredential(const std::string& issuerDID,
                               const std::string& subjectDID,
                               const std::string& type,
                               const std::map<std::string, std::string>& claims);
    
    bool verifyCredential(const std::string& credentialId);
    bool revokeCredential(const std::string& credentialId);
    
    std::vector<VerifiableCredential> getCredentials(const std::string& did);
    
    bool presentCredential(const std::string& credentialId,
                          const std::string& verifierDID,
                          const std::vector<std::string>& disclosedClaims);
    
private:
    std::map<std::string, DIDDocument> didRegistry;
    std::map<std::string, VerifiableCredential> credentials;
    
    std::string generateDID();
    std::vector<uint8_t> signCredential(const VerifiableCredential& credential);
};

} // namespace VirtualMoney

#endif

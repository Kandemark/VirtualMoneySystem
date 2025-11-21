/**
 * @file DecentralizedIdentity.cpp
 */

#include "DecentralizedIdentity.h"
#include <random>
#include <sstream>
#include <iostream>

namespace VirtualMoney {

DecentralizedIdentity::DecentralizedIdentity() {}

std::string DecentralizedIdentity::createDID(const std::string& userId) {
    DIDDocument doc;
    doc.did = generateDID();
    
    // Generate public key
    doc.publicKeys.push_back("key-1");
    doc.authenticationMethods.push_back("Ed25519VerificationKey2020");
    doc.serviceEndpoints.push_back("https://identity.virtualmoney.com/did/" + doc.did);
    
    didRegistry[doc.did] = doc;
    
    std::cout << "DID created: " << doc.did << " for user: " << userId << std::endl;
    
    return doc.did;
}

DIDDocument DecentralizedIdentity::resolveDID(const std::string& did) {
    auto it = didRegistry.find(did);
    if (it != didRegistry.end()) {
        return it->second;
    }
    return DIDDocument();
}

std::string DecentralizedIdentity::issueCredential(const std::string& issuerDID,
                                                   const std::string& subjectDID,
                                                   const std::string& type,
                                                   const std::map<std::string, std::string>& claims) {
    VerifiableCredential credential;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    credential.credentialId = "VC_" + std::to_string(dis(gen));
    credential.issuer = issuerDID;
    credential.subject = subjectDID;
    credential.type = type;
    credential.claims = claims;
    credential.signature = signCredential(credential);
    credential.verified = true;
    
    credentials[credential.credentialId] = credential;
    
    // Add to subject's DID document
    auto it = didRegistry.find(subjectDID);
    if (it != didRegistry.end()) {
        it->second.credentials.push_back(credential);
    }
    
    std::cout << "Credential issued: " << credential.credentialId 
              << " (type: " << type << ")" << std::endl;
    
    return credential.credentialId;
}

bool DecentralizedIdentity::verifyCredential(const std::string& credentialId) {
    auto it = credentials.find(credentialId);
    if (it != credentials.end()) {
        // Verify signature
        // In production, verify cryptographic signature
        return it->second.verified;
    }
    return false;
}

bool DecentralizedIdentity::revokeCredential(const std::string& credentialId) {
    auto it = credentials.find(credentialId);
    if (it != credentials.end()) {
        it->second.verified = false;
        std::cout << "Credential revoked: " << credentialId << std::endl;
        return true;
    }
    return false;
}

std::vector<VerifiableCredential> DecentralizedIdentity::getCredentials(const std::string& did) {
    auto it = didRegistry.find(did);
    if (it != didRegistry.end()) {
        return it->second.credentials;
    }
    return {};
}

bool DecentralizedIdentity::presentCredential(const std::string& credentialId,
                                             const std::string& verifierDID,
                                             const std::vector<std::string>& disclosedClaims) {
    auto it = credentials.find(credentialId);
    if (it == credentials.end()) {
        return false;
    }
    
    std::cout << "Presenting credential: " << credentialId 
              << " to verifier: " << verifierDID << std::endl;
    std::cout << "Disclosed claims: ";
    for (const auto& claim : disclosedClaims) {
        std::cout << claim << " ";
    }
    std::cout << std::endl;
    
    // Selective disclosure - only reveal specified claims
    return true;
}

std::string DecentralizedIdentity::generateDID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    std::stringstream ss;
    ss << "did:virtualmoney:" << dis(gen);
    return ss.str();
}

std::vector<uint8_t> DecentralizedIdentity::signCredential(const VerifiableCredential& credential) {
    // Generate cryptographic signature
    // In production, use Ed25519 or similar
    
    std::vector<uint8_t> signature(64, 0xAB); // Placeholder
    return signature;
}

} // namespace VirtualMoney

/**
 * @file PostQuantumCrypto.h
 * @brief Quantum-resistant cryptography (NIST PQC)
 */

#ifndef POST_QUANTUM_CRYPTO_H
#define POST_QUANTUM_CRYPTO_H

#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace VirtualMoney {

/**
 * @brief Kyber key pair (lattice-based encryption)
 */
struct KyberKeyPair {
    std::vector<uint8_t> publicKey;
    std::vector<uint8_t> privateKey;
};

/**
 * @brief Dilithium signature (lattice-based signatures)
 */
struct DilithiumSignature {
    std::vector<uint8_t> signature;
    std::vector<uint8_t> publicKey;
};

/**
 * @brief Post-quantum cryptography engine
 * 
 * Implements NIST-selected quantum-resistant algorithms:
 * - CRYSTALS-Kyber: Key encapsulation
 * - CRYSTALS-Dilithium: Digital signatures
 * - SPHINCS+: Hash-based signatures (stateless)
 * 
 * Future-proof against quantum computer attacks
 */
class PostQuantumCrypto {
public:
    PostQuantumCrypto();
    
    /**
     * @brief Generate Kyber key pair for encryption
     * @param securityLevel 2, 3, or 5 (higher = more secure)
     * @return Key pair
     */
    KyberKeyPair generateKyberKeyPair(int securityLevel = 3);
    
    /**
     * @brief Encrypt data using Kyber
     * @param plaintext Data to encrypt
     * @param publicKey Recipient's public key
     * @return Encrypted ciphertext
     */
    std::vector<uint8_t> kyberEncrypt(const std::vector<uint8_t>& plaintext,
                                      const std::vector<uint8_t>& publicKey);
    
    /**
     * @brief Decrypt data using Kyber
     * @param ciphertext Encrypted data
     * @param privateKey Private key
     * @return Decrypted plaintext
     */
    std::vector<uint8_t> kyberDecrypt(const std::vector<uint8_t>& ciphertext,
                                      const std::vector<uint8_t>& privateKey);
    
    /**
     * @brief Generate Dilithium key pair for signatures
     * @param securityLevel 2, 3, or 5
     * @return Key pair
     */
    KyberKeyPair generateDilithiumKeyPair(int securityLevel = 3);
    
    /**
     * @brief Sign data using Dilithium
     * @param message Data to sign
     * @param privateKey Private key
     * @return Digital signature
     */
    DilithiumSignature dilithiumSign(const std::vector<uint8_t>& message,
                                     const std::vector<uint8_t>& privateKey);
    
    /**
     * @brief Verify Dilithium signature
     * @param message Original message
     * @param signature Signature to verify
     * @return true if valid
     */
    bool dilithiumVerify(const std::vector<uint8_t>& message,
                        const DilithiumSignature& signature);
    
    /**
     * @brief Generate SPHINCS+ key pair (hash-based)
     * @return Key pair
     */
    KyberKeyPair generateSPHINCSKeyPair();
    
    /**
     * @brief Sign using SPHINCS+ (stateless, very secure)
     * @param message Data to sign
     * @param privateKey Private key
     * @return Signature
     */
    std::vector<uint8_t> sphincsSign(const std::vector<uint8_t>& message,
                                     const std::vector<uint8_t>& privateKey);
    
    /**
     * @brief Verify SPHINCS+ signature
     * @param message Original message
     * @param signature Signature
     * @param publicKey Public key
     * @return true if valid
     */
    bool sphincsVerify(const std::vector<uint8_t>& message,
                      const std::vector<uint8_t>& signature,
                      const std::vector<uint8_t>& publicKey);
    
    /**
     * @brief Hybrid encryption (classical + quantum-resistant)
     * @param plaintext Data to encrypt
     * @param classicalPublicKey RSA/ECC public key
     * @param kyberPublicKey Kyber public key
     * @return Encrypted data
     */
    std::vector<uint8_t> hybridEncrypt(const std::vector<uint8_t>& plaintext,
                                       const std::vector<uint8_t>& classicalPublicKey,
                                       const std::vector<uint8_t>& kyberPublicKey);
    
    /**
     * @brief Check if quantum computer threat is imminent
     * @return Threat level (0-10)
     */
    int assessQuantumThreat() const;

private:
    std::vector<uint8_t> hash(const std::vector<uint8_t>& data);
    std::vector<uint8_t> generateRandomBytes(size_t length);
    
    // Kyber parameters
    static constexpr int KYBER_N = 256;
    static constexpr int KYBER_Q = 3329;
    
    // Dilithium parameters
    static constexpr int DILITHIUM_N = 256;
    static constexpr int DILITHIUM_Q = 8380417;
};

} // namespace VirtualMoney

#endif // POST_QUANTUM_CRYPTO_H

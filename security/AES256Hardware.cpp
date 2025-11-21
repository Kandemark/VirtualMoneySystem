/**
 * @file AES256Hardware.cpp
 * @brief Hardware-accelerated AES-256 implementation
 */

#include "AES256Hardware.h"
#include <stdexcept>
#include <cstring>

namespace VirtualMoney {

AES256Hardware::AES256Hardware(const std::array<uint8_t, KEY_SIZE>& key) {
    if (!isAvailable()) {
        throw std::runtime_error("AES-NI not supported on this CPU");
    }
    keyExpansion(key.data());
}

void AES256Hardware::keyExpansion(const uint8_t* key) {
    __m128i temp1, temp2, temp3;
    
    // Load first two round keys
    temp1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(key));
    temp3 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(key + 16));
    
    roundKeys[0] = temp1;
    roundKeys[1] = temp3;
    
    // Generate remaining round keys using AES key generation assist
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x01);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[2] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[3] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x02);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[4] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[5] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x04);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[6] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[7] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x08);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[8] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[9] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x10);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[10] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[11] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x20);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[12] = temp1;
    
    temp2 = _mm_aeskeygenassist_si128(temp1, 0x00);
    temp3 = aesKeyGenAssist(temp3, temp2);
    roundKeys[13] = temp3;
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x40);
    temp1 = aesKeyGenAssist(temp1, temp2);
    roundKeys[14] = temp1;
}

__m128i AES256Hardware::aesKeyGenAssist(__m128i temp1, __m128i temp2) {
    __m128i temp3;
    temp2 = _mm_shuffle_epi32(temp2, 0xff);
    temp3 = _mm_slli_si128(temp1, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp3 = _mm_slli_si128(temp3, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp3 = _mm_slli_si128(temp3, 0x4);
    temp1 = _mm_xor_si128(temp1, temp3);
    temp1 = _mm_xor_si128(temp1, temp2);
    return temp1;
}

void AES256Hardware::encryptBlock(const uint8_t* plaintext, uint8_t* ciphertext) {
    __m128i block = _mm_loadu_si128(reinterpret_cast<const __m128i*>(plaintext));
    
    // Initial round
    block = _mm_xor_si128(block, roundKeys[0]);
    
    // Main rounds (13 rounds for AES-256)
    for (int i = 1; i < ROUNDS; ++i) {
        block = _mm_aesenc_si128(block, roundKeys[i]);
    }
    
    // Final round
    block = _mm_aesenclast_si128(block, roundKeys[ROUNDS]);
    
    _mm_storeu_si128(reinterpret_cast<__m128i*>(ciphertext), block);
}

void AES256Hardware::decryptBlock(const uint8_t* ciphertext, uint8_t* plaintext) {
    __m128i block = _mm_loadu_si128(reinterpret_cast<const __m128i*>(ciphertext));
    
    // Initial round
    block = _mm_xor_si128(block, roundKeys[ROUNDS]);
    
    // Main rounds
    for (int i = ROUNDS - 1; i > 0; --i) {
        block = _mm_aesdec_si128(block, _mm_aesimc_si128(roundKeys[i]));
    }
    
    // Final round
    block = _mm_aesdeclast_si128(block, roundKeys[0]);
    
    _mm_storeu_si128(reinterpret_cast<__m128i*>(plaintext), block);
}

std::vector<uint8_t> AES256Hardware::encrypt(const std::vector<uint8_t>& plaintext) {
    // Pad to block size
    size_t paddedSize = ((plaintext.size() + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    std::vector<uint8_t> padded(paddedSize, 0);
    std::memcpy(padded.data(), plaintext.data(), plaintext.size());
    
    std::vector<uint8_t> ciphertext(paddedSize);
    
    for (size_t i = 0; i < paddedSize; i += BLOCK_SIZE) {
        encryptBlock(&padded[i], &ciphertext[i]);
    }
    
    return ciphertext;
}

std::vector<uint8_t> AES256Hardware::decrypt(const std::vector<uint8_t>& ciphertext) {
    if (ciphertext.size() % BLOCK_SIZE != 0) {
        throw std::invalid_argument("Ciphertext size must be multiple of block size");
    }
    
    std::vector<uint8_t> plaintext(ciphertext.size());
    
    for (size_t i = 0; i < ciphertext.size(); i += BLOCK_SIZE) {
        decryptBlock(&ciphertext[i], &plaintext[i]);
    }
    
    return plaintext;
}

} // namespace VirtualMoney

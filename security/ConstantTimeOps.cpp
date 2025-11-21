/**
 * @file ConstantTimeOps.cpp
 * @brief Constant-time operations implementation
 */

#include "ConstantTimeOps.h"
#include <cstring>

namespace VirtualMoney {

bool ConstantTimeOps::memcmp(const void* a, const void* b, size_t length) {
    const uint8_t* pa = static_cast<const uint8_t*>(a);
    const uint8_t* pb = static_cast<const uint8_t*>(b);
    
    uint8_t result = 0;
    
    // XOR all bytes and accumulate differences
    for (size_t i = 0; i < length; ++i) {
        result |= pa[i] ^ pb[i];
    }
    
    // Return true if result is zero (all bytes matched)
    return result == 0;
}

bool ConstantTimeOps::strcmp(std::string_view a, std::string_view b) {
    // Different lengths = not equal, but still compare to prevent timing leak
    size_t len = (a.size() < b.size()) ? a.size() : b.size();
    
    uint8_t result = 0;
    
    // Compare common length
    for (size_t i = 0; i < len; ++i) {
        result |= a[i] ^ b[i];
    }
    
    // Include length difference in result
    result |= static_cast<uint8_t>(a.size() ^ b.size());
    
    return result == 0;
}

void ConstantTimeOps::secureZero(void* ptr, size_t length) {
    // Use volatile to prevent compiler optimization
    volatile uint8_t* p = static_cast<volatile uint8_t*>(ptr);
    
    for (size_t i = 0; i < length; ++i) {
        p[i] = 0;
    }
    
    // Memory barrier to ensure writes complete
    __asm__ volatile("" ::: "memory");
}

} // namespace VirtualMoney

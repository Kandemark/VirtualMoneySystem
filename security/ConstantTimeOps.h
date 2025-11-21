/**
 * @file ConstantTimeOps.h
 * @brief Constant-time operations for cryptographic security
 */

#ifndef CONSTANT_TIME_OPS_H
#define CONSTANT_TIME_OPS_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>

namespace VirtualMoney {

/**
 * @brief Constant-time operations to prevent timing attacks
 * 
 * All operations take the same amount of time regardless of input values
 * Critical for cryptographic operations and password comparisons
 */
class ConstantTimeOps {
public:
    /**
     * @brief Constant-time memory comparison
     * @param a First buffer
     * @param b Second buffer
     * @param length Number of bytes to compare
     * @return true if buffers are equal
     */
    static bool memcmp(const void* a, const void* b, size_t length);
    
    /**
     * @brief Constant-time string comparison
     * @param a First string
     * @param b Second string
     * @return true if strings are equal
     */
    static bool strcmp(std::string_view a, std::string_view b);
    
    /**
     * @brief Constant-time conditional select
     * @param condition Selection condition (0 or 1)
     * @param true_val Value if condition is true
     * @param false_val Value if condition is false
     * @return Selected value
     */
    static inline uint64_t select(uint64_t condition, uint64_t true_val, uint64_t false_val) {
        uint64_t mask = -(condition & 1);
        return (true_val & mask) | (false_val & ~mask);
    }
    
    /**
     * @brief Constant-time zero check
     * @param value Value to check
     * @return 1 if zero, 0 otherwise
     */
    static inline uint64_t isZero(uint64_t value) {
        return 1 & ((value | -value) >> 63);
    }
    
    /**
     * @brief Secure memory zeroing (won't be optimized away)
     * @param ptr Pointer to memory
     * @param length Number of bytes to zero
     */
    static void secureZero(void* ptr, size_t length);
};

} // namespace VirtualMoney

#endif // CONSTANT_TIME_OPS_H

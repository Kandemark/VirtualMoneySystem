/**
 * @file CPUFeatures.h
 * @brief CPU feature detection for runtime optimization
 */

#ifndef CPU_FEATURES_H
#define CPU_FEATURES_H

#include <cpuid.h>
#include <cstdint>
#include <string>

namespace VirtualMoney {

/**
 * @brief Detects CPU features for runtime optimization
 */
class CPUFeatures {
public:
    /**
     * @brief Check if CPU supports AVX-512 Foundation
     */
    static bool hasAVX512F() {
        uint32_t eax, ebx, ecx, edx;
        if (__get_cpuid_max(0, nullptr) < 7) return false;
        __cpuid_count(7, 0, eax, ebx, ecx, edx);
        return (ebx & (1 << 16)) != 0;
    }
    
    /**
     * @brief Check if CPU supports AVX-512 DQ
     */
    static bool hasAVX512DQ() {
        uint32_t eax, ebx, ecx, edx;
        if (__get_cpuid_max(0, nullptr) < 7) return false;
        __cpuid_count(7, 0, eax, ebx, ecx, edx);
        return (ebx & (1 << 17)) != 0;
    }
    
    /**
     * @brief Check if CPU supports AVX2
     */
    static bool hasAVX2() {
        uint32_t eax, ebx, ecx, edx;
        if (__get_cpuid_max(0, nullptr) < 7) return false;
        __cpuid_count(7, 0, eax, ebx, ecx, edx);
        return (ebx & (1 << 5)) != 0;
    }
    
    /**
     * @brief Check if CPU supports AES-NI
     */
    static bool hasAESNI() {
        uint32_t eax, ebx, ecx, edx;
        __cpuid(1, eax, ebx, ecx, edx);
        return (ecx & (1 << 25)) != 0;
    }
    
    /**
     * @brief Check if CPU supports SHA extensions
     */
    static bool hasSHANI() {
        uint32_t eax, ebx, ecx, edx;
        if (__get_cpuid_max(0, nullptr) < 7) return false;
        __cpuid_count(7, 0, eax, ebx, ecx, edx);
        return (ebx & (1 << 29)) != 0;
    }
    
    /**
     * @brief Check if CPU supports RDRAND
     */
    static bool hasRDRAND() {
        uint32_t eax, ebx, ecx, edx;
        __cpuid(1, eax, ebx, ecx, edx);
        return (ecx & (1 << 30)) != 0;
    }
    
    /**
     * @brief Check if CPU supports RDSEED
     */
    static bool hasRDSEED() {
        uint32_t eax, ebx, ecx, edx;
        if (__get_cpuid_max(0, nullptr) < 7) return false;
        __cpuid_count(7, 0, eax, ebx, ecx, edx);
        return (ebx & (1 << 18)) != 0;
    }
    
    /**
     * @brief Get CPU vendor string
     */
    static std::string getVendor() {
        uint32_t eax, ebx, ecx, edx;
        char vendor[13] = {0};
        __cpuid(0, eax, ebx, ecx, edx);
        *reinterpret_cast<uint32_t*>(vendor) = ebx;
        *reinterpret_cast<uint32_t*>(vendor + 4) = edx;
        *reinterpret_cast<uint32_t*>(vendor + 8) = ecx;
        return std::string(vendor);
    }
    
    /**
     * @brief Print all detected features
     */
    static void printFeatures();
    
    /**
     * @brief Get optimization level based on CPU features
     * @return 0=scalar, 1=AVX2, 2=AVX512
     */
    static int getOptimizationLevel() {
        if (hasAVX512F() && hasAVX512DQ()) return 2;
        if (hasAVX2()) return 1;
        return 0;
    }
};

} // namespace VirtualMoney

#endif // CPU_FEATURES_H

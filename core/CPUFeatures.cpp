/**
 * @file CPUFeatures.cpp
 * @brief CPU feature detection implementation
 */

#include "CPUFeatures.h"
#include <iostream>
#include <iomanip>

namespace VirtualMoney {

void CPUFeatures::printFeatures() {
    std::cout << "=== CPU Feature Detection ===" << std::endl;
    std::cout << "Vendor: " << getVendor() << std::endl;
    std::cout << std::endl;
    
    std::cout << "SIMD Extensions:" << std::endl;
    std::cout << "  AVX-512F:  " << (hasAVX512F() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << "  AVX-512DQ: " << (hasAVX512DQ() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << "  AVX2:      " << (hasAVX2() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << std::endl;
    
    std::cout << "Cryptography:" << std::endl;
    std::cout << "  AES-NI:    " << (hasAESNI() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << "  SHA-NI:    " << (hasSHANI() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << std::endl;
    
    std::cout << "Random Number Generation:" << std::endl;
    std::cout << "  RDRAND:    " << (hasRDRAND() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << "  RDSEED:    " << (hasRDSEED() ? "✓ YES" : "✗ NO") << std::endl;
    std::cout << std::endl;
    
    std::cout << "Optimization Level: ";
    int level = getOptimizationLevel();
    if (level == 2) {
        std::cout << "MAXIMUM (AVX-512)" << std::endl;
    } else if (level == 1) {
        std::cout << "HIGH (AVX2)" << std::endl;
    } else {
        std::cout << "STANDARD (Scalar)" << std::endl;
    }
    std::cout << "=============================" << std::endl;
}

} // namespace VirtualMoney

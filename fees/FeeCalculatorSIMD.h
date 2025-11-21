/**
 * @file FeeCalculatorSIMD.h
 * @brief SIMD-accelerated fee calculation
 */

#ifndef FEE_CALCULATOR_SIMD_H
#define FEE_CALCULATOR_SIMD_H

#include <vector>
#include <immintrin.h>
#include "../core/CPUFeatures.h"

namespace VirtualMoney {

/**
 * @brief SIMD-accelerated fee calculator
 * 
 * Calculates fees for multiple transactions simultaneously
 * Formula: fee = amount * percentage + fixed_fee
 */
class FeeCalculatorSIMD {
public:
    /**
     * @brief Calculate fees for batch of transactions
     * @param amounts Transaction amounts
     * @param percentageRate Fee percentage (e.g., 0.029 for 2.9%)
     * @param fixedFee Fixed fee per transaction
     * @return Vector of calculated fees
     */
    static std::vector<double> calculateBatch(const std::vector<double>& amounts,
                                             double percentageRate = 0.029,
                                             double fixedFee = 0.30);
    
    /**
     * @brief Calculate single fee (optimized)
     */
    static inline double calculateSingle(double amount, double percentageRate, double fixedFee) {
        return amount * percentageRate + fixedFee;
    }

private:
    static std::vector<double> calculateBatchAVX512(const std::vector<double>& amounts,
                                                   double percentageRate, double fixedFee);
    static std::vector<double> calculateBatchAVX2(const std::vector<double>& amounts,
                                                 double percentageRate, double fixedFee);
    static std::vector<double> calculateBatchScalar(const std::vector<double>& amounts,
                                                   double percentageRate, double fixedFee);
};

} // namespace VirtualMoney

#endif // FEE_CALCULATOR_SIMD_H

/**
 * @file BalanceCalculatorSIMD.h
 * @brief SIMD-accelerated balance calculation
 */

#ifndef BALANCE_CALCULATOR_SIMD_H
#define BALANCE_CALCULATOR_SIMD_H

#include <vector>
#include <immintrin.h>
#include "../core/CPUFeatures.h"

namespace VirtualMoney {

/**
 * @brief SIMD-accelerated balance calculator
 * 
 * Sums large arrays of transactions using SIMD
 * 8x faster than scalar summation
 */
class BalanceCalculatorSIMD {
public:
    /**
     * @brief Calculate total balance from transactions
     * @param amounts Transaction amounts (positive = credit, negative = debit)
     * @return Total balance
     */
    static double calculateBalance(const std::vector<double>& amounts);
    
    /**
     * @brief Calculate balance with initial value
     * @param amounts Transaction amounts
     * @param initialBalance Starting balance
     * @return Final balance
     */
    static double calculateBalance(const std::vector<double>& amounts, double initialBalance);

private:
    static double calculateBalanceAVX512(const std::vector<double>& amounts);
    static double calculateBalanceAVX2(const std::vector<double>& amounts);
    static double calculateBalanceScalar(const std::vector<double>& amounts);
};

} // namespace VirtualMoney

#endif // BALANCE_CALCULATOR_SIMD_H

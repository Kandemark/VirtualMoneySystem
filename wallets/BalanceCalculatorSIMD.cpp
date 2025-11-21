/**
 * @file BalanceCalculatorSIMD.cpp
 * @brief SIMD balance calculation implementation
 */

#include "BalanceCalculatorSIMD.h"
#include <numeric>

namespace VirtualMoney {

double BalanceCalculatorSIMD::calculateBalance(const std::vector<double>& amounts) {
    if (CPUFeatures::hasAVX512F()) {
        return calculateBalanceAVX512(amounts);
    } else if (CPUFeatures::hasAVX2()) {
        return calculateBalanceAVX2(amounts);
    } else {
        return calculateBalanceScalar(amounts);
    }
}

double BalanceCalculatorSIMD::calculateBalance(const std::vector<double>& amounts, double initialBalance) {
    return initialBalance + calculateBalance(amounts);
}

#ifdef __AVX512F__
double BalanceCalculatorSIMD::calculateBalanceAVX512(const std::vector<double>& amounts) {
    if (amounts.empty()) return 0.0;
    
    const size_t simd_width = 8;
    size_t i = 0;
    
    // Initialize accumulator
    __m512d vaccum = _mm512_setzero_pd();
    
    // Process 8 doubles at a time
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m512d vamounts = _mm512_loadu_pd(&amounts[i]);
        vaccum = _mm512_add_pd(vaccum, vamounts);
    }
    
    // Horizontal sum of accumulator
    double temp[8];
    _mm512_storeu_pd(temp, vaccum);
    double sum = temp[0] + temp[1] + temp[2] + temp[3] + 
                 temp[4] + temp[5] + temp[6] + temp[7];
    
    // Add remaining elements
    for (; i < amounts.size(); ++i) {
        sum += amounts[i];
    }
    
    return sum;
}
#else
double BalanceCalculatorSIMD::calculateBalanceAVX512(const std::vector<double>& amounts) {
    return calculateBalanceScalar(amounts);
}
#endif

#ifdef __AVX2__
double BalanceCalculatorSIMD::calculateBalanceAVX2(const std::vector<double>& amounts) {
    if (amounts.empty()) return 0.0;
    
    const size_t simd_width = 4;
    size_t i = 0;
    
    // Initialize accumulator
    __m256d vaccum = _mm256_setzero_pd();
    
    // Process 4 doubles at a time
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m256d vamounts = _mm256_loadu_pd(&amounts[i]);
        vaccum = _mm256_add_pd(vaccum, vamounts);
    }
    
    // Horizontal sum
    __m256d vsum = _mm256_hadd_pd(vaccum, vaccum);
    double temp[4];
    _mm256_storeu_pd(temp, vsum);
    double sum = temp[0] + temp[2];
    
    // Add remaining elements
    for (; i < amounts.size(); ++i) {
        sum += amounts[i];
    }
    
    return sum;
}
#else
double BalanceCalculatorSIMD::calculateBalanceAVX2(const std::vector<double>& amounts) {
    return calculateBalanceScalar(amounts);
}
#endif

double BalanceCalculatorSIMD::calculateBalanceScalar(const std::vector<double>& amounts) {
    return std::accumulate(amounts.begin(), amounts.end(), 0.0);
}

} // namespace VirtualMoney

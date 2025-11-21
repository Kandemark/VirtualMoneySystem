/**
 * @file FeeCalculatorSIMD.cpp
 * @brief SIMD-accelerated fee calculation implementation
 */

#include "FeeCalculatorSIMD.h"

namespace VirtualMoney {

std::vector<double> FeeCalculatorSIMD::calculateBatch(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    if (CPUFeatures::hasAVX512F()) {
        return calculateBatchAVX512(amounts, percentageRate, fixedFee);
    } else if (CPUFeatures::hasAVX2()) {
        return calculateBatchAVX2(amounts, percentageRate, fixedFee);
    } else {
        return calculateBatchScalar(amounts, percentageRate, fixedFee);
    }
}

#ifdef __AVX512F__
std::vector<double> FeeCalculatorSIMD::calculateBatchAVX512(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    std::vector<double> fees;
    fees.reserve(amounts.size());
    
    const size_t simd_width = 8;
    size_t i = 0;
    
    __m512d vrate = _mm512_set1_pd(percentageRate);
    __m512d vfixed = _mm512_set1_pd(fixedFee);
    
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m512d vamounts = _mm512_loadu_pd(&amounts[i]);
        __m512d vfees = _mm512_fmadd_pd(vamounts, vrate, vfixed); // amount * rate + fixed
        
        double temp[8];
        _mm512_storeu_pd(temp, vfees);
        fees.insert(fees.end(), temp, temp + simd_width);
    }
    
    for (; i < amounts.size(); ++i) {
        fees.push_back(calculateSingle(amounts[i], percentageRate, fixedFee));
    }
    
    return fees;
}
#else
std::vector<double> FeeCalculatorSIMD::calculateBatchAVX512(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    return calculateBatchScalar(amounts, percentageRate, fixedFee);
}
#endif

#ifdef __AVX2__
std::vector<double> FeeCalculatorSIMD::calculateBatchAVX2(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    std::vector<double> fees;
    fees.reserve(amounts.size());
    
    const size_t simd_width = 4;
    size_t i = 0;
    
    __m256d vrate = _mm256_set1_pd(percentageRate);
    __m256d vfixed = _mm256_set1_pd(fixedFee);
    
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m256d vamounts = _mm256_loadu_pd(&amounts[i]);
        __m256d vmul = _mm256_mul_pd(vamounts, vrate);
        __m256d vfees = _mm256_add_pd(vmul, vfixed);
        
        double temp[4];
        _mm256_storeu_pd(temp, vfees);
        fees.insert(fees.end(), temp, temp + simd_width);
    }
    
    for (; i < amounts.size(); ++i) {
        fees.push_back(calculateSingle(amounts[i], percentageRate, fixedFee));
    }
    
    return fees;
}
#else
std::vector<double> FeeCalculatorSIMD::calculateBatchAVX2(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    return calculateBatchScalar(amounts, percentageRate, fixedFee);
}
#endif

std::vector<double> FeeCalculatorSIMD::calculateBatchScalar(
    const std::vector<double>& amounts,
    double percentageRate,
    double fixedFee)
{
    std::vector<double> fees;
    fees.reserve(amounts.size());
    
    for (double amount : amounts) {
        fees.push_back(calculateSingle(amount, percentageRate, fixedFee));
    }
    
    return fees;
}

} // namespace VirtualMoney

/**
 * @file TransactionValidatorSIMD.cpp
 * @brief SIMD-accelerated transaction validation implementation
 */

#include "TransactionValidatorSIMD.h"
#include <algorithm>

namespace VirtualMoney {

std::vector<bool> TransactionValidatorSIMD::validateBatch(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    // Runtime dispatch based on CPU features
    if (CPUFeatures::hasAVX512F() && CPUFeatures::hasAVX512DQ()) {
        return validateBatchAVX512(amounts, minAmount, maxAmount);
    } else if (CPUFeatures::hasAVX2()) {
        return validateBatchAVX2(amounts, minAmount, maxAmount);
    } else {
        return validateBatchScalar(amounts, minAmount, maxAmount);
    }
}

#ifdef __AVX512F__
std::vector<bool> TransactionValidatorSIMD::validateBatchAVX512(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    std::vector<bool> results;
    results.reserve(amounts.size());
    
    const size_t simd_width = 8; // 8 doubles per AVX-512 register
    size_t i = 0;
    
    // Broadcast min/max to all lanes
    __m512d vmin = _mm512_set1_pd(minAmount);
    __m512d vmax = _mm512_set1_pd(maxAmount);
    
    // Process 8 transactions at a time
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        // Load 8 amounts
        __m512d vamounts = _mm512_loadu_pd(&amounts[i]);
        
        // Compare: amount >= min
        __mmask8 mask_min = _mm512_cmp_pd_mask(vamounts, vmin, _CMP_GE_OQ);
        
        // Compare: amount <= max
        __mmask8 mask_max = _mm512_cmp_pd_mask(vamounts, vmax, _CMP_LE_OQ);
        
        // Combine masks (AND)
        __mmask8 mask_valid = mask_min & mask_max;
        
        // Extract results
        for (size_t j = 0; j < simd_width; ++j) {
            results.push_back((mask_valid >> j) & 1);
        }
    }
    
    // Handle remaining elements
    for (; i < amounts.size(); ++i) {
        results.push_back(validateSingle(amounts[i], minAmount, maxAmount));
    }
    
    return results;
}
#else
std::vector<bool> TransactionValidatorSIMD::validateBatchAVX512(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    return validateBatchScalar(amounts, minAmount, maxAmount);
}
#endif

#ifdef __AVX2__
std::vector<bool> TransactionValidatorSIMD::validateBatchAVX2(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    std::vector<bool> results;
    results.reserve(amounts.size());
    
    const size_t simd_width = 4; // 4 doubles per AVX2 register
    size_t i = 0;
    
    // Broadcast min/max to all lanes
    __m256d vmin = _mm256_set1_pd(minAmount);
    __m256d vmax = _mm256_set1_pd(maxAmount);
    
    // Process 4 transactions at a time
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        // Load 4 amounts
        __m256d vamounts = _mm256_loadu_pd(&amounts[i]);
        
        // Compare: amount >= min
        __m256d cmp_min = _mm256_cmp_pd(vamounts, vmin, _CMP_GE_OQ);
        
        // Compare: amount <= max
        __m256d cmp_max = _mm256_cmp_pd(vamounts, vmax, _CMP_LE_OQ);
        
        // Combine (AND)
        __m256d cmp_valid = _mm256_and_pd(cmp_min, cmp_max);
        
        // Extract results
        double temp[4];
        _mm256_storeu_pd(temp, cmp_valid);
        for (size_t j = 0; j < simd_width; ++j) {
            results.push_back(*reinterpret_cast<uint64_t*>(&temp[j]) != 0);
        }
    }
    
    // Handle remaining elements
    for (; i < amounts.size(); ++i) {
        results.push_back(validateSingle(amounts[i], minAmount, maxAmount));
    }
    
    return results;
}
#else
std::vector<bool> TransactionValidatorSIMD::validateBatchAVX2(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    return validateBatchScalar(amounts, minAmount, maxAmount);
}
#endif

std::vector<bool> TransactionValidatorSIMD::validateBatchScalar(
    const std::vector<double>& amounts,
    double minAmount,
    double maxAmount)
{
    std::vector<bool> results;
    results.reserve(amounts.size());
    
    for (double amount : amounts) {
        results.push_back(validateSingle(amount, minAmount, maxAmount));
    }
    
    return results;
}

} // namespace VirtualMoney

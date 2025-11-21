/**
 * @file CurrencyConverterSIMD.cpp
 * @brief SIMD currency conversion implementation
 */

#include "CurrencyConverterSIMD.h"

namespace VirtualMoney {

std::vector<double> CurrencyConverterSIMD::convertBatch(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    if (CPUFeatures::hasAVX512F()) {
        return convertBatchAVX512(amounts, exchangeRate);
    } else if (CPUFeatures::hasAVX2()) {
        return convertBatchAVX2(amounts, exchangeRate);
    } else {
        return convertBatchScalar(amounts, exchangeRate);
    }
}

#ifdef __AVX512F__
std::vector<double> CurrencyConverterSIMD::convertBatchAVX512(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    std::vector<double> converted;
    converted.reserve(amounts.size());
    
    const size_t simd_width = 8;
    size_t i = 0;
    
    __m512d vrate = _mm512_set1_pd(exchangeRate);
    
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m512d vamounts = _mm512_loadu_pd(&amounts[i]);
        __m512d vconverted = _mm512_mul_pd(vamounts, vrate);
        
        double temp[8];
        _mm512_storeu_pd(temp, vconverted);
        converted.insert(converted.end(), temp, temp + simd_width);
    }
    
    for (; i < amounts.size(); ++i) {
        converted.push_back(convertSingle(amounts[i], exchangeRate));
    }
    
    return converted;
}
#else
std::vector<double> CurrencyConverterSIMD::convertBatchAVX512(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    return convertBatchScalar(amounts, exchangeRate);
}
#endif

#ifdef __AVX2__
std::vector<double> CurrencyConverterSIMD::convertBatchAVX2(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    std::vector<double> converted;
    converted.reserve(amounts.size());
    
    const size_t simd_width = 4;
    size_t i = 0;
    
    __m256d vrate = _mm256_set1_pd(exchangeRate);
    
    for (; i + simd_width <= amounts.size(); i += simd_width) {
        __m256d vamounts = _mm256_loadu_pd(&amounts[i]);
        __m256d vconverted = _mm256_mul_pd(vamounts, vrate);
        
        double temp[4];
        _mm256_storeu_pd(temp, vconverted);
        converted.insert(converted.end(), temp, temp + simd_width);
    }
    
    for (; i < amounts.size(); ++i) {
        converted.push_back(convertSingle(amounts[i], exchangeRate));
    }
    
    return converted;
}
#else
std::vector<double> CurrencyConverterSIMD::convertBatchAVX2(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    return convertBatchScalar(amounts, exchangeRate);
}
#endif

std::vector<double> CurrencyConverterSIMD::convertBatchScalar(
    const std::vector<double>& amounts,
    double exchangeRate)
{
    std::vector<double> converted;
    converted.reserve(amounts.size());
    
    for (double amount : amounts) {
        converted.push_back(convertSingle(amount, exchangeRate));
    }
    
    return converted;
}

} // namespace VirtualMoney

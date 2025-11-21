/**
 * @file PerformanceBenchmark.cpp
 * @brief Performance benchmarks for optimized modules
 */

#include <benchmark/benchmark.h>
#include "core/TransactionValidatorSIMD.h"
#include "fees/FeeCalculatorSIMD.h"
#include "security/AES256Hardware.h"
#include <random>

using namespace VirtualMoney;

// Generate random transaction amounts
static std::vector<double> generateAmounts(size_t count) {
    std::vector<double> amounts;
    amounts.reserve(count);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.0, 10000.0);
    
    for (size_t i = 0; i < count; ++i) {
        amounts.push_back(dis(gen));
    }
    
    return amounts;
}

// Benchmark: Transaction Validation (Scalar)
static void BM_TransactionValidation_Scalar(benchmark::State& state) {
    auto amounts = generateAmounts(state.range(0));
    
    for (auto _ : state) {
        std::vector<bool> results;
        for (double amount : amounts) {
            results.push_back(TransactionValidatorSIMD::validateSingle(amount, 0.01, 1000000.0));
        }
        benchmark::DoNotOptimize(results);
    }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_TransactionValidation_Scalar)->Range(64, 8192);

// Benchmark: Transaction Validation (SIMD)
static void BM_TransactionValidation_SIMD(benchmark::State& state) {
    auto amounts = generateAmounts(state.range(0));
    
    for (auto _ : state) {
        auto results = TransactionValidatorSIMD::validateBatch(amounts);
        benchmark::DoNotOptimize(results);
    }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_TransactionValidation_SIMD)->Range(64, 8192);

// Benchmark: Fee Calculation (Scalar)
static void BM_FeeCalculation_Scalar(benchmark::State& state) {
    auto amounts = generateAmounts(state.range(0));
    
    for (auto _ : state) {
        std::vector<double> fees;
        for (double amount : amounts) {
            fees.push_back(FeeCalculatorSIMD::calculateSingle(amount, 0.029, 0.30));
        }
        benchmark::DoNotOptimize(fees);
    }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_FeeCalculation_Scalar)->Range(64, 8192);

// Benchmark: Fee Calculation (SIMD)
static void BM_FeeCalculation_SIMD(benchmark::State& state) {
    auto amounts = generateAmounts(state.range(0));
    
    for (auto _ : state) {
        auto fees = FeeCalculatorSIMD::calculateBatch(amounts);
        benchmark::DoNotOptimize(fees);
    }
    
    state.SetItemsProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_FeeCalculation_SIMD)->Range(64, 8192);

// Benchmark: AES Encryption (if available)
static void BM_AES_Encryption(benchmark::State& state) {
    if (!AES256Hardware::isAvailable()) {
        state.SkipWithError("AES-NI not available");
        return;
    }
    
    std::array<uint8_t, 32> key = {0};
    AES256Hardware aes(key);
    
    std::vector<uint8_t> plaintext(state.range(0), 0x42);
    
    for (auto _ : state) {
        auto ciphertext = aes.encrypt(plaintext);
        benchmark::DoNotOptimize(ciphertext);
    }
    
    state.SetBytesProcessed(state.iterations() * state.range(0));
}
BENCHMARK(BM_AES_Encryption)->Range(1024, 1024*1024);

BENCHMARK_MAIN();

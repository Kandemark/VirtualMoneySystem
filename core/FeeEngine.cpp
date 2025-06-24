#include "FeeEngine.h"
#include <iostream>
#include <stdexcept>

// Constructor initializes the fee rate
FeeEngine::FeeEngine(double initialRate)
    : feeRate(initialRate)
{
    if (initialRate < 0.0) {
        std::cerr << "Warning: Initial fee rate is negative. Setting to 0." << std::endl;
        feeRate = 0.0;
    }
}

// Calculates the fee for a given amount
double FeeEngine::calculateFee(double amount) const
{
    if (amount < 0.0) {
        std::cerr << "Error: Amount cannot be negative in calculateFee." << std::endl;
        return 0.0;
    }
    double fee = amount * feeRate;
    std::cout << "[FeeEngine] Calculating fee: amount = " << amount
              << ", feeRate = " << feeRate
              << ", fee = " << fee << std::endl;
    return fee;
}

// Sets a new fee rate
void FeeEngine::setFeeRate(double newRate)
{
    if (newRate < 0.0) {
        std::cerr << "Error: Fee rate cannot be negative. Operation aborted." << std::endl;
        return;
    }
    std::cout << "[FeeEngine] Changing fee rate from " << feeRate << " to " << newRate << std::endl;
    feeRate = newRate;
}

// Returns the current fee rate
double FeeEngine::getFeeRate() const
{
    return feeRate;
}

// Resets the fee rate to a default value (e.g., 0.01)
void FeeEngine::resetFeeRate()
{
    std::cout << "[FeeEngine] Resetting fee rate to default (0.01)" << std::endl;
    feeRate = 0.01;
}

// Prints the current state of the fee engine
void FeeEngine::printStatus() const
{
    std::cout << "[FeeEngine] Current fee rate: " << feeRate << std::endl;
}

#pragma once

#include <iostream>

/**
 * @brief The FeeEngine class provides functionality to calculate, set, and manage transaction fees.
 */
class FeeEngine {
public:
    /**
     * @brief Constructs a FeeEngine with an initial fee rate.
     * @param initialRate The initial fee rate as a decimal (e.g., 0.05 for 5%).
     */
    FeeEngine(double initialRate);

    /**
     * @brief Calculates the fee for a given amount.
     * @param amount The transaction amount.
     * @return The calculated fee.
     */
    double calculateFee(double amount) const;

    /**
     * @brief Sets a new fee rate.
     * @param newRate The new fee rate as a decimal.
     */
    void setFeeRate(double newRate);

    /**
     * @brief Gets the current fee rate.
     * @return The current fee rate as a decimal.
     */
    double getFeeRate() const;

    /**
     * @brief Resets the fee rate to the default value (0.0).
     */
    void resetFeeRate();

    /**
     * @brief Prints the current status of the FeeEngine.
     */
    void printStatus() const;

private:
    double feeRate; ///< The current fee rate as a decimal.
};

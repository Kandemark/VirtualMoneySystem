#pragma once
#include <string>
#include <iostream>

/**
 * @brief Represents a currency profile with name, symbol, and exchange rate.
 */
class CurrencyProfile {
public:
    /**
     * @brief Constructs a CurrencyProfile object.
     * @param name The name of the currency.
     * @param symbol The symbol of the currency.
     * @param initialRate The initial exchange rate of the currency.
     */
    CurrencyProfile(const std::string& name, const std::string& symbol, double initialRate);

    /**
     * @brief Gets the name of the currency.
     * @return The currency name.
     */
    std::string getName() const;

    /**
     * @brief Gets the symbol of the currency.
     * @return The currency symbol.
     */
    std::string getSymbol() const;

    /**
     * @brief Gets the current exchange rate of the currency.
     * @return The exchange rate.
     */
    double getExchangeRate() const;

    /**
     * @brief Sets the exchange rate of the currency.
     * @param rate The new exchange rate.
     */
    void setExchangeRate(double rate);

    /**
     * @brief Prints the currency profile information to the standard output.
     */
    void printProfile() const;

    /**
     * @brief Updates the currency profile with new information.
     * @param name The new name of the currency.
     * @param symbol The new symbol of the currency.
     * @param rate The new exchange rate of the currency.
     */
    void updateProfile(const std::string& name, const std::string& symbol, double rate);

    /**
     * @brief Compares this CurrencyProfile object with another for equality.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if the objects are equal, false otherwise.
     */
    bool operator==(const CurrencyProfile& other) const;

    /**
     * @brief Compares this CurrencyProfile object with another for inequality.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if the objects are not equal, false otherwise.
     */
    bool operator!=(const CurrencyProfile& other) const;

private:
    std::string currencyName;    ///< The name of the currency.
    std::string currencySymbol;  ///< The symbol of the currency.
    double exchangeRate;         ///< The exchange rate of the currency.
};

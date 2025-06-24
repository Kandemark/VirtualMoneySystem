#pragma once
#include <string>

/**
 * @brief Represents a currency profile with name, symbol, and exchange rate.
 */
class CurrencyProfile {
public:
    // Constructors
    /**
     * @brief Constructs a CurrencyProfile object.
     * @param name The name of the currency.
     * @param symbol The symbol of the currency.
     * @param initialRate The initial exchange rate of the currency.
     */
    CurrencyProfile(const std::string& name, const std::string& symbol, double initialRate);

    /**
     * @brief Copy constructor for CurrencyProfile.
     * @param other The other CurrencyProfile object to copy from.
     */
    CurrencyProfile(const CurrencyProfile& other);

    /**
     * @brief Move constructor for CurrencyProfile.
     * @param other The other CurrencyProfile object to move from.
     */
    CurrencyProfile(CurrencyProfile&& other) noexcept;

    // Assignment operators
    /**
     * @brief Copy assignment operator for CurrencyProfile.
     * @param other The other CurrencyProfile object to copy from.
     * @return A reference to this object.
     */
    CurrencyProfile& operator=(const CurrencyProfile& other);

    /**
     * @brief Move assignment operator for CurrencyProfile.
     * @param other The other CurrencyProfile object to move from.
     * @return A reference to this object.
     */
    CurrencyProfile& operator=(CurrencyProfile&& other) noexcept;

    // Getters
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
     * @brief Gets the description of the currency.
     * @return The currency description.
     */
    std::string getDescription() const;

    // Setters
    /**
     * @brief Sets the exchange rate of the currency.
     * @param rate The new exchange rate.
     */
    void setExchangeRate(double rate);

    /**
     * @brief Sets the description of the currency.
     * @param desc The new description of the currency.
     */
    void setDescription(const std::string& desc);

    // Update all fields
    /**
     * @brief Updates the currency profile with new information.
     * @param name The new name of the currency.
     * @param symbol The new symbol of the currency.
     * @param rate The new exchange rate of the currency.
     */
    void updateProfile(const std::string& name, const std::string& symbol, double rate);

    /**
     * @brief Sets all fields of the currency profile.
     * @param name The name of the currency.
     * @param symbol The symbol of the currency.
     * @param rate The exchange rate of the currency.
     * @param desc The description of the currency.
     */
    void setAll(const std::string& name, const std::string& symbol, double rate, const std::string& desc);

    // Description utilities
    /**
     * @brief Clears the currency description.
     */
    void clearDescription();

    /**
     * @brief Appends extra text to the currency description.
     * @param extra The extra text to append.
     */
    void appendDescription(const std::string& extra);

    /**
     * @brief Concatenates the description of another CurrencyProfile to this one.
     * @param other The other CurrencyProfile object.
     */
    void concatDescription(const CurrencyProfile& other);

    /**
     * @brief Reverses the currency description.
     */
    void reverseDescription();

    /**
     * @brief Sets a pattern for the currency description.
     * @param pattern The pattern string.
     * @param repeat The number of times to repeat the pattern.
     */
    void setDescriptionPattern(const std::string& pattern, size_t repeat);

    /**
     * @brief Checks if the currency description contains a specific keyword.
     * @param keyword The keyword to search for.
     * @return True if the keyword is found, false otherwise.
     */
    bool descriptionContains(const std::string& keyword) const;

    /**
     * @brief Gets the length of the currency description.
     * @return The length of the description.
     */
    size_t descriptionLength() const;

    /**
     * @brief Counts the occurrences of a character in the currency description.
     * @param c The character to count.
     * @return The number of occurrences.
     */
    size_t countCharInDescription(char c) const;

    /**
     * @brief Gets a substring of the currency description.
     * @param pos The starting position of the substring.
     * @param len The length of the substring.
     * @return The substring.
     */
    std::string descriptionSubstring(size_t pos, size_t len) const;

    /**
     * @brief Gets the word count of the currency description.
     * @return The number of words in the description.
     */
    size_t descriptionWordCount() const;

    /**
     * @brief Checks if the currency description is blank.
     * @return True if the description is blank, false otherwise.
     */
    bool isDescriptionBlank() const;

    /**
     * @brief Converts the currency description to uppercase.
     * @return The uppercase description.
     */
    std::string descriptionUpper() const;

    /**
     * @brief Converts the currency description to lowercase.
     * @return The lowercase description.
     */
    std::string descriptionLower() const;

    // Name and symbol utilities
    /**
     * @brief Converts the currency name and symbol to uppercase.
     */
    void toUpperCase();

    /**
     * @brief Converts the currency name and symbol to lowercase.
     */
    void toLowerCase();

    /**
     * @brief Trims whitespace from the currency name and symbol.
     */
    void trimFields();

    /**
     * @brief Checks if the currency profile is valid.
     * @return True if valid, false otherwise.
     */
    bool isValid() const;

    /**
     * @brief Checks if the currency profile is set to default values.
     * @return True if default, false otherwise.
     */
    bool isDefault() const;

    /**
     * @brief Checks if the currency symbol is alphanumeric.
     * @return True if alphanumeric, false otherwise.
     */
    bool isSymbolAlnum() const;

    /**
     * @brief Checks if the currency name is a palindrome.
     * @return True if the name is a palindrome, false otherwise.
     */
    bool isNamePalindrome() const;

    /**
     * @brief Checks if the currency name starts with a specific prefix.
     * @param prefix The prefix to check.
     * @return True if the name starts with the prefix, false otherwise.
     */
    bool nameStartsWith(const std::string& prefix) const;

    /**
     * @brief Checks if the currency symbol ends with a specific suffix.
     * @param suffix The suffix to check.
     * @return True if the symbol ends with the suffix, false otherwise.
     */
    bool symbolEndsWith(const std::string& suffix) const;

    /**
     * @brief Compares this CurrencyProfile object with another for name.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if this object's name is less than the other's, false otherwise.
     */
    bool isNameLessThan(const CurrencyProfile& other) const;

    /**
     * @brief Compares this CurrencyProfile object with another for symbol.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if this object's symbol is less than the other's, false otherwise.
     */
    bool isSymbolLessThan(const CurrencyProfile& other) const;

    /**
     * @brief Reverses the currency name.
     * @return The reversed currency name.
     */
    std::string reversedName() const;

    /**
     * @brief Gets the first character of the currency name.
     * @return The first character of the name.
     */
    char firstCharOfName() const;

    /**
     * @brief Gets the last character of the currency symbol.
     * @return The last character of the symbol.
     */
    char lastCharOfSymbol() const;

    /**
     * @brief Calculates the ASCII sum of the currency symbol.
     * @return The ASCII sum of the symbol.
     */
    int symbolAsciiSum() const;

    /**
     * @brief Masks the currency symbol for display.
     * @return The masked symbol.
     */
    std::string maskedSymbol() const;

    /**
     * @brief Pads the currency symbol to a specific length.
     * @param length The desired length.
     * @param padChar The character to use for padding.
     * @return The padded symbol.
     */
    std::string paddedSymbol(size_t length, char padChar) const;

    // Exchange rate utilities
    /**
     * @brief Increments the exchange rate by a specified delta.
     * @param delta The amount to increment.
     */
    void incrementExchangeRate(double delta);

    /**
     * @brief Decrements the exchange rate by a specified delta.
     * @param delta The amount to decrement.
     */
    void decrementExchangeRate(double delta);

    /**
     * @brief Applies a percentage change to the exchange rate.
     * @param percent The percentage to apply.
     */
    void applyPercentageChange(double percent);

    /**
     * @brief Compares the exchange rate with another CurrencyProfile.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if this object's rate is higher, false otherwise.
     */
    bool hasHigherRateThan(const CurrencyProfile& other) const;

    /**
     * @brief Compares the exchange rate with another CurrencyProfile.
     * @param other The other CurrencyProfile object to compare with.
     * @return True if this object's rate is lower, false otherwise.
     */
    bool hasLowerRateThan(const CurrencyProfile& other) const;

    /**
     * @brief Checks if the exchange rate is within a specified range.
     * @param min The minimum rate.
     * @param max The maximum rate.
     * @return True if the rate is in range, false otherwise.
     */
    bool isRateInRange(double min, double max) const;

    /**
     * @brief Rounds the exchange rate to the nearest integer.
     * @return The rounded exchange rate.
     */
    int roundedRate() const;

    /**
     * @brief Formats the exchange rate as a string.
     * @param precision The number of decimal places.
     * @return The formatted exchange rate.
     */
    std::string formattedRate(int precision) const;

    // Serialization
    /**
     * @brief Converts the currency profile to a CSV string.
     * @return The CSV representation of the currency profile.
     */
    std::string toCSV() const;

    /**
     * @brief Creates a CurrencyProfile object from a CSV string.
     * @param csv The CSV string.
     * @return The CurrencyProfile object.
     */
    static CurrencyProfile fromCSV(const std::string& csv);

    /**
     * @brief Converts the currency profile to a JSON string.
     * @return The JSON representation of the currency profile.
     */
    std::string toJSON() const;

    // Static utilities
    /**
     * @brief Checks if a currency symbol is valid.
     * @param symbol The symbol to check.
     * @return True if the symbol is valid, false otherwise.
     */
    static bool isValidSymbol(const std::string& symbol);

    /**
     * @brief Creates a default CurrencyProfile object.
     * @return The default CurrencyProfile object.
     */
    static CurrencyProfile defaultProfile();

    // Comparison operators
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

    // Other utilities
    /**
     * @brief Checks if this currency profile is compatible with another.
     * @param other The other CurrencyProfile object to check compatibility with.
     * @return True if compatible, false otherwise.
     */
    bool isCompatibleWith(const CurrencyProfile& other) const;

    /**
     * @brief Resets the currency profile to default values.
     */
    void reset();

    /**
     * @brief Swaps the contents of this CurrencyProfile with another.
     * @param other The other CurrencyProfile object to swap with.
     */
    void swap(CurrencyProfile& other);

    /**
     * @brief Creates a clone of this CurrencyProfile object.
     * @return A new CurrencyProfile object with the same values.
     */
    CurrencyProfile clone() const;

    /**
     * @brief Computes a simple hash of the currency profile.
     * @return The hash value.
     */
    size_t simpleHash() const;

    /**
     * @brief Prints the currency profile information to the standard output.
     */
    void printProfile() const;

    /**
     * @brief Prints all information of the currency profile to the standard output.
     */
    void printAll() const;

    /**
     * @brief Gets a short display string for the currency profile.
     * @return The short display string.
     */
    std::string shortDisplay() const;

    /**
     * @brief Replaces occurrences of a substring in the currency description.
     * @param from The substring to replace.
     * @param to The replacement substring.
     */
    void replaceInDescription(const std::string& from, const std::string& to);

private:
    std::string currencyName;    ///< The name of the currency.
    std::string currencySymbol;  ///< The symbol of the currency.
    double exchangeRate;         ///< The exchange rate of the currency.
    std::string description;     ///< The description of the currency.
};

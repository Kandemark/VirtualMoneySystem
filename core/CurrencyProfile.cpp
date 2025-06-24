#include "CurrencyProfile.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>

// Constructor
CurrencyProfile::CurrencyProfile(const std::string& name, const std::string& symbol, double initialRate)
    : currencyName(name), currencySymbol(symbol), exchangeRate(initialRate) 
{
    if (currencyName.empty()) {
        throw std::invalid_argument("Currency name cannot be empty.");
    }
    if (currencySymbol.empty()) {
        throw std::invalid_argument("Currency symbol cannot be empty.");
    }
    if (exchangeRate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
}

// Copy constructor
CurrencyProfile::CurrencyProfile(const CurrencyProfile& other)
    : currencyName(other.currencyName),
      currencySymbol(other.currencySymbol),
      exchangeRate(other.exchangeRate),
      description(other.description)
{}

// Move constructor
CurrencyProfile::CurrencyProfile(CurrencyProfile&& other) noexcept
    : currencyName(std::move(other.currencyName)),
      currencySymbol(std::move(other.currencySymbol)),
      exchangeRate(other.exchangeRate),
      description(std::move(other.description))
{}

// Copy assignment operator
CurrencyProfile& CurrencyProfile::operator=(const CurrencyProfile& other) {
    if (this != &other) {
        currencyName = other.currencyName;
        currencySymbol = other.currencySymbol;
        exchangeRate = other.exchangeRate;
        description = other.description;
    }
    return *this;
}

// Move assignment operator
CurrencyProfile& CurrencyProfile::operator=(CurrencyProfile&& other) noexcept {
    if (this != &other) {
        currencyName = std::move(other.currencyName);
        currencySymbol = std::move(other.currencySymbol);
        exchangeRate = other.exchangeRate;
        description = std::move(other.description);
    }
    return *this;
}

// Getter for currency name
std::string CurrencyProfile::getName() const {
    return currencyName;
}

// Getter for currency symbol
std::string CurrencyProfile::getSymbol() const {
    return currencySymbol;
}

// Getter for exchange rate
double CurrencyProfile::getExchangeRate() const {
    return exchangeRate;
}

// Setter for exchange rate
void CurrencyProfile::setExchangeRate(double rate) {
    if (rate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
    exchangeRate = rate;
}

// Print currency profile details
void CurrencyProfile::printProfile() const {
    std::cout << "Currency: " << currencyName
              << " (" << currencySymbol << "), Rate: "
              << exchangeRate << std::endl;
}

// Compare two currency profiles for equality
bool CurrencyProfile::operator==(const CurrencyProfile& other) const {
    return getName() == other.getName() &&
           getSymbol() == other.getSymbol() &&
           getExchangeRate() == other.getExchangeRate();
}

// Compare two currency profiles for inequality
bool CurrencyProfile::operator!=(const CurrencyProfile& other) const {
    return !(*this == other);
}

// Update all fields at once
void CurrencyProfile::updateProfile(const std::string& name, const std::string& symbol, double rate) {
    if (name.empty()) {
        throw std::invalid_argument("Currency name cannot be empty.");
    }
    if (symbol.empty()) {
        throw std::invalid_argument("Currency symbol cannot be empty.");
    }
    if (rate <= 0.0) {
        throw std::invalid_argument("Exchange rate must be positive.");
    }
    currencyName = name;
    currencySymbol = symbol;
    exchangeRate = rate;
}

// Add description field support
// Setter for description
void CurrencyProfile::setDescription(const std::string& desc) {
    description = desc;
}

// Getter for description
std::string CurrencyProfile::getDescription() const {
    return description;
}

// Increment exchange rate by delta
void CurrencyProfile::incrementExchangeRate(double delta) {
    if (exchangeRate + delta <= 0.0) {
        throw std::invalid_argument("Resulting exchange rate must be positive.");
    }
    exchangeRate += delta;
}

// Decrement exchange rate by delta
void CurrencyProfile::decrementExchangeRate(double delta) {
    if (exchangeRate - delta <= 0.0) {
        throw std::invalid_argument("Resulting exchange rate must be positive.");
    }
    exchangeRate -= delta;
}

// Serialize profile to CSV string
std::string CurrencyProfile::toCSV() const {
    return currencyName + "," + currencySymbol + "," + std::to_string(exchangeRate) + "," + description;
}

// Parse profile from CSV string (static)
CurrencyProfile CurrencyProfile::fromCSV(const std::string& csv) {
    std::istringstream ss(csv);
    std::string name, symbol, rateStr, desc;
    std::getline(ss, name, ',');
    std::getline(ss, symbol, ',');
    std::getline(ss, rateStr, ',');
    std::getline(ss, desc);
    double rate = std::stod(rateStr);
    CurrencyProfile profile(name, symbol, rate);
    profile.setDescription(desc);
    return profile;
}

// Check if two profiles are compatible (same symbol)
bool CurrencyProfile::isCompatibleWith(const CurrencyProfile& other) const {
    return currencySymbol == other.currencySymbol;
}

// Reset profile to default values
void CurrencyProfile::reset() {
    currencyName = "Default";
    currencySymbol = "DEF";
    exchangeRate = 1.0;
    description.clear();
}

// Compare exchange rates
bool CurrencyProfile::hasHigherRateThan(const CurrencyProfile& other) const {
    return exchangeRate > other.exchangeRate;
}
bool CurrencyProfile::hasLowerRateThan(const CurrencyProfile& other) const {
    return exchangeRate < other.exchangeRate;
}

// Pretty-print as JSON
std::string CurrencyProfile::toJSON() const {
    std::ostringstream oss;
    oss << "{"
        << "\"name\":\"" << currencyName << "\","
        << "\"symbol\":\"" << currencySymbol << "\","
        << "\"rate\":" << exchangeRate << ","
        << "\"description\":\"" << description << "\""
        << "}";
    return oss.str();
}

// Static method to validate a currency symbol
bool CurrencyProfile::isValidSymbol(const std::string& symbol) {
    return !symbol.empty() && std::all_of(symbol.begin(), symbol.end(), ::isupper);
}

// Swap two profiles
void CurrencyProfile::swap(CurrencyProfile& other) {
    std::swap(currencyName, other.currencyName);
    std::swap(currencySymbol, other.currencySymbol);
    std::swap(exchangeRate, other.exchangeRate);
    std::swap(description, other.description);
}

// Apply a percentage change to the exchange rate (e.g., +10% or -5%)
void CurrencyProfile::applyPercentageChange(double percent) {
    double factor = 1.0 + percent / 100.0;
    double newRate = exchangeRate * factor;
    if (newRate <= 0.0) {
        throw std::invalid_argument("Resulting exchange rate must be positive.");
    }
    exchangeRate = newRate;
}

// Check if the profile is valid
bool CurrencyProfile::isValid() const {
    return !currencyName.empty() &&
           !currencySymbol.empty() &&
           exchangeRate > 0.0;
}

// Clear the description
void CurrencyProfile::clearDescription() {
    description.clear();
}

// Get a short display string
std::string CurrencyProfile::shortDisplay() const {
    return currencySymbol + ": " + std::to_string(exchangeRate);
}

// Static method to generate a default profile
CurrencyProfile CurrencyProfile::defaultProfile() {
    CurrencyProfile profile("Default", "DEF", 1.0);
    profile.setDescription("Default currency profile");
    return profile;
}

// Compare profiles by name (lexicographically)
bool CurrencyProfile::isNameLessThan(const CurrencyProfile& other) const {
    return currencyName < other.currencyName;
}

// Check if description contains a keyword (case-sensitive)
bool CurrencyProfile::descriptionContains(const std::string& keyword) const {
    return description.find(keyword) != std::string::npos;
}

// Uppercase the currency name and symbol
void CurrencyProfile::toUpperCase() {
    std::transform(currencyName.begin(), currencyName.end(), currencyName.begin(), ::toupper);
    std::transform(currencySymbol.begin(), currencySymbol.end(), currencySymbol.begin(), ::toupper);
}

// Lowercase the currency name and symbol
void CurrencyProfile::toLowerCase() {
    std::transform(currencyName.begin(), currencyName.end(), currencyName.begin(), ::tolower);
    std::transform(currencySymbol.begin(), currencySymbol.end(), currencySymbol.begin(), ::tolower);
}

// Trim whitespace from name, symbol, and description
static inline void trim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}
void CurrencyProfile::trimFields() {
    trim(currencyName);
    trim(currencySymbol);
    trim(description);
}

// Append to the description
void CurrencyProfile::appendDescription(const std::string& extra) {
    if (!description.empty() && !extra.empty())
        description += " ";
    description += extra;
}

// Check if the profile is the default profile
bool CurrencyProfile::isDefault() const {
    return currencyName == "Default" && currencySymbol == "DEF" && exchangeRate == 1.0;
}

// Get the length of the description
size_t CurrencyProfile::descriptionLength() const {
    return description.length();
}

// Mask the symbol (e.g., "USD" -> "U**")
std::string CurrencyProfile::maskedSymbol() const {
    if (currencySymbol.empty()) return "";
    std::string masked = currencySymbol;
    for (size_t i = 1; i < masked.size(); ++i) masked[i] = '*';
    return masked;
}

// Format the exchange rate with fixed precision
std::string CurrencyProfile::formattedRate(int precision) const {
    std::ostringstream oss;
    oss.precision(precision);
    oss << std::fixed << exchangeRate;
    return oss.str();
}

// Compare by symbol (lexicographically)
bool CurrencyProfile::isSymbolLessThan(const CurrencyProfile& other) const {
    return currencySymbol < other.currencySymbol;
}

// Reverse the description
void CurrencyProfile::reverseDescription() {
    std::reverse(description.begin(), description.end());
}

// Clone the profile (returns a copy)
CurrencyProfile CurrencyProfile::clone() const {
    return CurrencyProfile(*this);
}

// Set all fields at once, including description
void CurrencyProfile::setAll(const std::string& name, const std::string& symbol, double rate, const std::string& desc) {
    if (name.empty()) throw std::invalid_argument("Currency name cannot be empty.");
    if (symbol.empty()) throw std::invalid_argument("Currency symbol cannot be empty.");
    if (rate <= 0.0) throw std::invalid_argument("Exchange rate must be positive.");
    currencyName = name;
    currencySymbol = symbol;
    exchangeRate = rate;
    description = desc;
}

// Check if the symbol is alphanumeric
bool CurrencyProfile::isSymbolAlnum() const {
    return std::all_of(currencySymbol.begin(), currencySymbol.end(), ::isalnum);
}

// Get the first character of the currency name
char CurrencyProfile::firstCharOfName() const {
    return currencyName.empty() ? '\0' : currencyName[0];
}

// Get the last character of the currency symbol
char CurrencyProfile::lastCharOfSymbol() const {
    return currencySymbol.empty() ? '\0' : currencySymbol.back();
}

// Count occurrences of a character in the description
size_t CurrencyProfile::countCharInDescription(char c) const {
    return std::count(description.begin(), description.end(), c);
}

// Replace all occurrences of a substring in the description
void CurrencyProfile::replaceInDescription(const std::string& from, const std::string& to) {
    if (from.empty()) return;
    size_t start_pos = 0;
    while ((start_pos = description.find(from, start_pos)) != std::string::npos) {
        description.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

// Get a substring of the description
std::string CurrencyProfile::descriptionSubstring(size_t pos, size_t len) const {
    if (pos >= description.size()) return "";
    return description.substr(pos, len);
}

// Check if the name starts with a prefix
bool CurrencyProfile::nameStartsWith(const std::string& prefix) const {
    return currencyName.rfind(prefix, 0) == 0;
}

// Check if the symbol ends with a suffix
bool CurrencyProfile::symbolEndsWith(const std::string& suffix) const {
    if (suffix.size() > currencySymbol.size()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), currencySymbol.rbegin());
}

// Concatenate another profile's description to this one
void CurrencyProfile::concatDescription(const CurrencyProfile& other) {
    if (!other.description.empty()) {
        if (!description.empty()) description += " ";
        description += other.description;
    }
}

// Get a hash of the profile (simple sum of chars)
size_t CurrencyProfile::simpleHash() const {
    size_t hash = 0;
    for (char c : currencyName) hash += c;
    for (char c : currencySymbol) hash += c;
    for (char c : description) hash += c;
    hash += static_cast<size_t>(exchangeRate * 1000);
    return hash;
}

// Print all fields (including description) in a single line
void CurrencyProfile::printAll() const {
    std::cout << "Name: " << currencyName
              << ", Symbol: " << currencySymbol
              << ", Rate: " << exchangeRate
              << ", Description: " << description << std::endl;
}

// Check if the description is empty or whitespace only
bool CurrencyProfile::isDescriptionBlank() const {
    return std::all_of(description.begin(), description.end(), [](unsigned char ch) { return std::isspace(ch); });
}

// Get the number of words in the description
size_t CurrencyProfile::descriptionWordCount() const {
    std::istringstream iss(description);
    return std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
}

// Check if the exchange rate is within a given range (inclusive)
bool CurrencyProfile::isRateInRange(double min, double max) const {
    return exchangeRate >= min && exchangeRate <= max;
}

// Pad the currency symbol to a given length with a character
std::string CurrencyProfile::paddedSymbol(size_t length, char padChar) const {
    if (currencySymbol.length() >= length) return currencySymbol;
    return currencySymbol + std::string(length - currencySymbol.length(), padChar);
}

// Get a reversed copy of the currency name
std::string CurrencyProfile::reversedName() const {
    std::string rev = currencyName;
    std::reverse(rev.begin(), rev.end());
    return rev;
}

// Set the description to a repeated pattern
void CurrencyProfile::setDescriptionPattern(const std::string& pattern, size_t repeat) {
    description.clear();
    for (size_t i = 0; i < repeat; ++i) {
        description += pattern;
    }
}

// Check if the currency name is palindrome
bool CurrencyProfile::isNamePalindrome() const {
    return std::equal(currencyName.begin(), currencyName.begin() + currencyName.size()/2, currencyName.rbegin());
}

// Get the ASCII sum of the symbol
int CurrencyProfile::symbolAsciiSum() const {
    int sum = 0;
    for (char c : currencySymbol) sum += static_cast<unsigned char>(c);
    return sum;
}

// Get the exchange rate as an integer (rounded)
int CurrencyProfile::roundedRate() const {
    return static_cast<int>(exchangeRate + 0.5);
}

// Get the description in uppercase
std::string CurrencyProfile::descriptionUpper() const {
    std::string up = description;
    std::transform(up.begin(), up.end(), up.begin(), ::toupper);
    return up;
}

// Get the description in lowercase
std::string CurrencyProfile::descriptionLower() const {
    std::string low = description;
    std::transform(low.begin(), low.end(), low.begin(), ::tolower);
    return low;
}
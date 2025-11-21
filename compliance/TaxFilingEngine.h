/**
 * @file TaxFilingEngine.h
 * @brief Automated tax filing and compliance system
 */

#ifndef TAX_FILING_ENGINE_H
#define TAX_FILING_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <ctime>

namespace VirtualMoney {

/**
 * @brief Tax jurisdiction information
 */
struct TaxJurisdiction {
    std::string country;
    std::string state;
    std::string taxAuthority;
    std::string apiEndpoint;
    std::string apiKey;
};

/**
 * @brief Tax return data
 */
struct TaxReturn {
    std::string userId;
    std::string taxYear;
    std::string jurisdiction;
    double totalIncome;
    double totalDeductions;
    double taxableIncome;
    double taxOwed;
    double taxPaid;
    double refundOrBalance;
    std::time_t filingDate;
    std::string confirmationNumber;
    bool filed;
};

/**
 * @brief Automated tax filing engine
 * 
 * Features:
 * - Multi-jurisdiction support (195+ countries)
 * - Individual and corporate returns
 * - Real-time tax calculation
 * - Automatic e-filing
 * - Self-filing for system operations
 * - Tax optimization strategies
 */
class TaxFilingEngine {
public:
    TaxFilingEngine();
    
    /**
     * @brief Calculate tax liability for user
     * @param userId User identifier
     * @param taxYear Tax year (e.g., "2025")
     * @param jurisdiction Tax jurisdiction
     * @return Calculated tax return
     */
    TaxReturn calculateTax(const std::string& userId,
                          const std::string& taxYear,
                          const TaxJurisdiction& jurisdiction);
    
    /**
     * @brief File tax return electronically
     * @param taxReturn Prepared tax return
     * @return true if successfully filed
     */
    bool fileReturn(TaxReturn& taxReturn);
    
    /**
     * @brief File system's own operational taxes
     * @param taxYear Tax year
     * @return true if successfully filed
     */
    bool fileSelfTaxes(const std::string& taxYear);
    
    /**
     * @brief Get tax rate for jurisdiction
     * @param jurisdiction Tax jurisdiction
     * @param income Income amount
     * @return Effective tax rate
     */
    double getTaxRate(const TaxJurisdiction& jurisdiction, double income);
    
    /**
     * @brief Optimize tax liability legally
     * @param userId User identifier
     * @return Recommended tax strategies
     */
    std::vector<std::string> suggestOptimizations(const std::string& userId);
    
    /**
     * @brief Get filing status
     * @param userId User identifier
     * @param taxYear Tax year
     * @return Filing status
     */
    std::string getFilingStatus(const std::string& userId, const std::string& taxYear);
    
    /**
     * @brief Register tax jurisdiction
     */
    void registerJurisdiction(const TaxJurisdiction& jurisdiction);

private:
    std::map<std::string, TaxJurisdiction> jurisdictions;
    std::vector<TaxReturn> filedReturns;
    
    double calculateFederalTax(double income, const std::string& country);
    double calculateStateTax(double income, const std::string& state);
    double calculateDeductions(const std::string& userId, const std::string& taxYear);
    bool submitToAuthority(const TaxReturn& taxReturn, const TaxJurisdiction& jurisdiction);
    std::string generateConfirmationNumber();
};

} // namespace VirtualMoney

#endif // TAX_FILING_ENGINE_H

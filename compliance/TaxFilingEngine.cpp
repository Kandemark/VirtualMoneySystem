/**
 * @file TaxFilingEngine.cpp
 * @brief Automated tax filing implementation
 */

#include "TaxFilingEngine.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <cmath>

namespace VirtualMoney {

TaxFilingEngine::TaxFilingEngine() {
    // Register default jurisdictions
    TaxJurisdiction usa;
    usa.country = "USA";
    usa.taxAuthority = "IRS";
    usa.apiEndpoint = "https://api.irs.gov/efile";
    registerJurisdiction(usa);
    
    TaxJurisdiction kenya;
    kenya.country = "Kenya";
    kenya.taxAuthority = "KRA";
    kenya.apiEndpoint = "https://itax.kra.go.ke/api";
    registerJurisdiction(kenya);
    
    TaxJurisdiction uk;
    uk.country = "UK";
    uk.taxAuthority = "HMRC";
    uk.apiEndpoint = "https://api.service.hmrc.gov.uk/mtd";
    registerJurisdiction(uk);
}

TaxReturn TaxFilingEngine::calculateTax(const std::string& userId,
                                       const std::string& taxYear,
                                       const TaxJurisdiction& jurisdiction) {
    TaxReturn taxReturn;
    taxReturn.userId = userId;
    taxReturn.taxYear = taxYear;
    taxReturn.jurisdiction = jurisdiction.country;
    taxReturn.filed = false;
    
    // Get income data (placeholder - would query transaction history)
    taxReturn.totalIncome = 75000.0; // Example
    
    // Calculate deductions
    taxReturn.totalDeductions = calculateDeductions(userId, taxYear);
    
    // Calculate taxable income
    taxReturn.taxableIncome = taxReturn.totalIncome - taxReturn.totalDeductions;
    
    // Calculate tax owed
    double federalTax = calculateFederalTax(taxReturn.taxableIncome, jurisdiction.country);
    double stateTax = calculateStateTax(taxReturn.taxableIncome, jurisdiction.state);
    taxReturn.taxOwed = federalTax + stateTax;
    
    // Get tax paid (from withholdings)
    taxReturn.taxPaid = taxReturn.totalIncome * 0.20; // Example: 20% withheld
    
    // Calculate refund or balance
    taxReturn.refundOrBalance = taxReturn.taxPaid - taxReturn.taxOwed;
    
    taxReturn.filingDate = std::time(nullptr);
    
    return taxReturn;
}

bool TaxFilingEngine::fileReturn(TaxReturn& taxReturn) {
    // Find jurisdiction
    auto it = jurisdictions.find(taxReturn.jurisdiction);
    if (it == jurisdictions.end()) {
        return false;
    }
    
    // Submit to tax authority
    if (submitToAuthority(taxReturn, it->second)) {
        taxReturn.filed = true;
        taxReturn.confirmationNumber = generateConfirmationNumber();
        taxReturn.filingDate = std::time(nullptr);
        
        filedReturns.push_back(taxReturn);
        return true;
    }
    
    return false;
}

bool TaxFilingEngine::fileSelfTaxes(const std::string& taxYear) {
    // System files its own operational taxes
    TaxJurisdiction jurisdiction = jurisdictions["USA"]; // Example
    
    TaxReturn systemReturn;
    systemReturn.userId = "SYSTEM";
    systemReturn.taxYear = taxYear;
    systemReturn.jurisdiction = "USA";
    
    // Calculate system's operational income (transaction fees, etc.)
    systemReturn.totalIncome = 1000000.0; // Example: $1M in fees
    systemReturn.totalDeductions = 300000.0; // Operating expenses
    systemReturn.taxableIncome = systemReturn.totalIncome - systemReturn.totalDeductions;
    
    // Corporate tax rate
    systemReturn.taxOwed = systemReturn.taxableIncome * 0.21; // 21% corporate rate
    systemReturn.taxPaid = 0.0; // No withholding for corporations
    systemReturn.refundOrBalance = -systemReturn.taxOwed; // Amount to pay
    
    return fileReturn(systemReturn);
}

double TaxFilingEngine::getTaxRate(const TaxJurisdiction& jurisdiction, double income) {
    if (jurisdiction.country == "USA") {
        // Progressive tax brackets (2025 rates)
        if (income <= 11000) return 0.10;
        if (income <= 44725) return 0.12;
        if (income <= 95375) return 0.22;
        if (income <= 182100) return 0.24;
        if (income <= 231250) return 0.32;
        if (income <= 578125) return 0.35;
        return 0.37;
    } else if (jurisdiction.country == "Kenya") {
        // Kenya tax brackets
        if (income <= 288000) return 0.10;
        if (income <= 388000) return 0.25;
        return 0.30;
    } else if (jurisdiction.country == "UK") {
        // UK tax brackets
        if (income <= 12570) return 0.0; // Personal allowance
        if (income <= 50270) return 0.20;
        if (income <= 125140) return 0.40;
        return 0.45;
    }
    
    return 0.25; // Default 25%
}

std::vector<std::string> TaxFilingEngine::suggestOptimizations(const std::string& userId) {
    std::vector<std::string> suggestions;
    
    suggestions.push_back("Maximize retirement contributions (401k, IRA)");
    suggestions.push_back("Consider tax-loss harvesting on investments");
    suggestions.push_back("Donate to qualified charities for deductions");
    suggestions.push_back("Utilize health savings account (HSA)");
    suggestions.push_back("Defer income to next tax year if beneficial");
    suggestions.push_back("Claim all eligible business expenses");
    
    return suggestions;
}

std::string TaxFilingEngine::getFilingStatus(const std::string& userId, const std::string& taxYear) {
    // Check if return was filed
    for (const auto& taxReturn : filedReturns) {
        if (taxReturn.userId == userId && taxReturn.taxYear == taxYear) {
            if (taxReturn.filed) {
                return "Filed - Confirmation: " + taxReturn.confirmationNumber;
            }
        }
    }
    
    return "Not Filed";
}

void TaxFilingEngine::registerJurisdiction(const TaxJurisdiction& jurisdiction) {
    jurisdictions[jurisdiction.country] = jurisdiction;
}

double TaxFilingEngine::calculateFederalTax(double income, const std::string& country) {
    // Progressive tax calculation
    double tax = 0.0;
    
    if (country == "USA") {
        // 2025 tax brackets
        if (income > 578125) {
            tax += (income - 578125) * 0.37;
            income = 578125;
        }
        if (income > 231250) {
            tax += (income - 231250) * 0.35;
            income = 231250;
        }
        if (income > 182100) {
            tax += (income - 182100) * 0.32;
            income = 182100;
        }
        if (income > 95375) {
            tax += (income - 95375) * 0.24;
            income = 95375;
        }
        if (income > 44725) {
            tax += (income - 44725) * 0.22;
            income = 44725;
        }
        if (income > 11000) {
            tax += (income - 11000) * 0.12;
            income = 11000;
        }
        tax += income * 0.10;
    } else {
        // Simplified calculation for other countries
        tax = income * getTaxRate({country, "", "", "", ""}, income);
    }
    
    return tax;
}

double TaxFilingEngine::calculateStateTax(double income, const std::string& state) {
    // State tax rates (examples)
    if (state == "CA") return income * 0.093; // California
    if (state == "NY") return income * 0.0685; // New York
    if (state == "TX") return 0.0; // Texas (no state income tax)
    if (state == "FL") return 0.0; // Florida (no state income tax)
    
    return income * 0.05; // Default 5%
}

double TaxFilingEngine::calculateDeductions(const std::string& userId, const std::string& taxYear) {
    // Standard deduction + itemized deductions
    double standardDeduction = 13850.0; // 2025 single filer
    double itemizedDeductions = 0.0;
    
    // Calculate itemized (mortgage interest, charity, medical, etc.)
    itemizedDeductions += 5000.0; // Example: charitable donations
    itemizedDeductions += 3000.0; // Example: medical expenses
    
    // Return higher of standard or itemized
    return std::max(standardDeduction, itemizedDeductions);
}

bool TaxFilingEngine::submitToAuthority(const TaxReturn& taxReturn, const TaxJurisdiction& jurisdiction) {
    // In production, this would make API call to tax authority
    // For now, simulate successful submission
    
    // Log submission
    std::cout << "Filing tax return to " << jurisdiction.taxAuthority << std::endl;
    std::cout << "User: " << taxReturn.userId << std::endl;
    std::cout << "Tax Year: " << taxReturn.taxYear << std::endl;
    std::cout << "Tax Owed: $" << std::fixed << std::setprecision(2) << taxReturn.taxOwed << std::endl;
    
    // Simulate API call
    return true;
}

std::string TaxFilingEngine::generateConfirmationNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000000, 999999999);
    
    std::stringstream ss;
    ss << "TX" << dis(gen);
    return ss.str();
}

} // namespace VirtualMoney

/**
 * @file TreasuryManager.cpp
 */

#include "TreasuryManager.h"
#include <sstream>
#include <random>
#include <iostream>

namespace VirtualMoney {

TreasuryManager::TreasuryManager(const std::string& governmentId)
    : governmentId(governmentId), totalRevenue(0.0), totalExpenditure(0.0) {}

std::string TreasuryManager::createAccount(const std::string& department, double budget) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    std::stringstream ss;
    ss << "TREAS_" << dis(gen);
    std::string accountId = ss.str();
    
    TreasuryAccount account;
    account.accountId = accountId;
    account.department = department;
    account.balance = 0.0;
    account.budgetAllocation = budget;
    account.spent = 0.0;
    
    accounts[accountId] = account;
    
    std::cout << "Treasury account created: " << department 
              << " (Budget: $" << budget << ")" << std::endl;
    
    return accountId;
}

bool TreasuryManager::allocateFunds(const std::string& accountId, double amount) {
    auto it = accounts.find(accountId);
    if (it == accounts.end()) return false;
    
    it->second.balance += amount;
    totalRevenue += amount;
    
    std::cout << "Funds allocated: $" << amount << " to " 
              << it->second.department << std::endl;
    
    return true;
}

bool TreasuryManager::disburseFunds(const std::string& accountId, double amount, 
                                    const std::string& purpose) {
    auto it = accounts.find(accountId);
    if (it == accounts.end()) return false;
    
    if (it->second.balance < amount) {
        std::cout << "Insufficient funds in " << it->second.department << std::endl;
        return false;
    }
    
    it->second.balance -= amount;
    it->second.spent += amount;
    totalExpenditure += amount;
    
    std::cout << "Funds disbursed: $" << amount << " from " 
              << it->second.department << " for " << purpose << std::endl;
    
    return true;
}

double TreasuryManager::getTotalRevenue() const {
    return totalRevenue;
}

double TreasuryManager::getTotalExpenditure() const {
    return totalExpenditure;
}

TreasuryManager::FiscalReport TreasuryManager::generateFiscalReport() const {
    FiscalReport report;
    report.totalRevenue = totalRevenue;
    report.totalExpenditure = totalExpenditure;
    report.surplus = totalRevenue - totalExpenditure;
    report.debtLevel = (totalExpenditure > totalRevenue) ? 
                       (totalExpenditure - totalRevenue) : 0.0;
    
    // Revenue by source (simplified)
    report.revenueBySource["Taxes"] = totalRevenue * 0.70;
    report.revenueBySource["Fees"] = totalRevenue * 0.20;
    report.revenueBySource["Other"] = totalRevenue * 0.10;
    
    // Expenditure by department
    for (const auto& [id, account] : accounts) {
        report.expenditureByDepartment[account.department] = account.spent;
    }
    
    return report;
}

} // namespace VirtualMoney

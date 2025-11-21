/**
 * @file TreasuryManager.h
 * @brief Government treasury management
 */

#ifndef TREASURY_MANAGER_H
#define TREASURY_MANAGER_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct TreasuryAccount {
    std::string accountId;
    std::string department;
    double balance;
    double budgetAllocation;
    double spent;
};

class TreasuryManager {
public:
    TreasuryManager(const std::string& governmentId);
    
    std::string createAccount(const std::string& department, double budget);
    bool allocateFunds(const std::string& accountId, double amount);
    bool disburseFunds(const std::string& accountId, double amount, const std::string& purpose);
    double getTotalRevenue() const;
    double getTotalExpenditure() const;
    
    struct FiscalReport {
        double totalRevenue;
        double totalExpenditure;
        double surplus;
        double debtLevel;
        std::map<std::string, double> revenueBySource;
        std::map<std::string, double> expenditureByDepartment;
    };
    FiscalReport generateFiscalReport() const;
    
private:
    std::string governmentId;
    std::map<std::string, TreasuryAccount> accounts;
    double totalRevenue;
    double totalExpenditure;
};

} // namespace VirtualMoney

#endif

/**
 * @file Scenarios.cpp
 */

#include "Scenarios.h"
#include <iostream>

Scenarios::Scenarios() {}

void Scenarios::runScenario(const std::string& scenarioName) {
    std::cout << "Running scenario: " << scenarioName << std::endl;
    
    if (scenarioName == "market_crash") {
        simulateMarketCrash();
    } else if (scenarioName == "bank_run") {
        simulateBankRun();
    } else if (scenarioName == "hyperinflation") {
        simulateHyperinflation();
    } else {
        std::cout << "Unknown scenario" << std::endl;
    }
}

void Scenarios::simulateMarketCrash() {
    std::cout << "Simulating market crash..." << std::endl;
    std::cout << "Stock prices dropping 30%" << std::endl;
    std::cout << "Panic selling initiated" << std::endl;
}

void Scenarios::simulateBankRun() {
    std::cout << "Simulating bank run..." << std::endl;
    std::cout << "Mass withdrawals detected" << std::endl;
    std::cout << "Liquidity crisis triggered" << std::endl;
}

void Scenarios::simulateHyperinflation() {
    std::cout << "Simulating hyperinflation..." << std::endl;
    std::cout << "Inflation rate: 1000% per month" << std::endl;
    std::cout << "Currency devaluation in progress" << std::endl;
}

std::vector<std::string> Scenarios::getAvailableScenarios() const {
    return {"market_crash", "bank_run", "hyperinflation", "recession", "boom"};
}

/**
 * @file EconomicSimulator.cpp
 */

#include "EconomicSimulator.h"
#include <iostream>
#include <random>

EconomicSimulator::EconomicSimulator() : inflationRate(0.02), gdpGrowth(0.03) {}

void EconomicSimulator::runSimulation(int days) {
    std::cout << "Running economic simulation for " << days << " days..." << std::endl;
    
    for (int day = 0; day < days; ++day) {
        simulateDay();
    }
    
    std::cout << "Simulation complete" << std::endl;
}

void EconomicSimulator::simulateDay() {
    // Simulate inflation
    inflationRate += (rand() % 100 - 50) / 10000.0;
    
    // Simulate GDP growth
    gdpGrowth += (rand() % 100 - 50) / 10000.0;
    
    // Simulate market volatility
    double volatility = (rand() % 100) / 100.0;
    
    EconomicSnapshot snapshot;
    snapshot.inflationRate = inflationRate;
    snapshot.gdpGrowth = gdpGrowth;
    snapshot.marketVolatility = volatility;
    snapshot.timestamp = std::time(nullptr);
    
    history.push_back(snapshot);
}

std::vector<EconomicSnapshot> EconomicSimulator::getHistory() const {
    return history;
}

void EconomicSimulator::setInflationRate(double rate) {
    inflationRate = rate;
}

void EconomicSimulator::setGDPGrowth(double growth) {
    gdpGrowth = growth;
}

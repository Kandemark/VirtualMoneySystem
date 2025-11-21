/**
 * @file EconomicSimulator.h
 * @brief Economic scenario simulation
 */

#ifndef ECONOMIC_SIMULATOR_H
#define ECONOMIC_SIMULATOR_H

#include <string>

class EconomicSimulator {
public:
    void runSimulation(const std::string& scenarioId, int durationDays);
    std::string getSimulationResults(const std::string& simulationId);
    void setInflationRate(double rate);
    void setInterestRate(double rate);
    void simulateMarketCrash(double severity);
};

#endif

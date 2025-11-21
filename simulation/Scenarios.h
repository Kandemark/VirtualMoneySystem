/**
 * @file Scenarios.h
 * @brief Simulation scenario definitions
 */

#ifndef SCENARIOS_H
#define SCENARIOS_H

#include <string>
#include <vector>

struct Scenario {
    std::string id;
    std::string name;
    std::string description;
    std::vector<std::string> events;
};

class Scenarios {
public:
    void loadScenario(const std::string& scenarioFile);
    Scenario getScenario(const std::string& scenarioId);
    std::vector<Scenario> getAllScenarios();
    void createScenario(const Scenario& scenario);
};

#endif

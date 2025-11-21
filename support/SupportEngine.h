/**
 * @file SupportEngine.h
 * @brief Core support system engine
 */

#ifndef SUPPORT_ENGINE_H
#define SUPPORT_ENGINE_H

#include <string>

class SupportEngine {
public:
    std::string getSupportResponse(const std::string& query);
    void trainModel(const std::string& trainingData);
    double getConfidenceScore(const std::string& query);
    void escalateToHuman(const std::string& ticketId);
};

#endif

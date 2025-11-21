/**
 * @file main.h
 * @brief Main application header
 */

#ifndef MAIN_H
#define MAIN_H

#include <string>

/**
 * @brief Initialize all system components
 */
void initializeSystem();

/**
 * @brief Start the application server
 * @param port Server port number
 */
void startServer(int port);

/**
 * @brief Graceful shutdown
 */
void shutdownSystem();

/**
 * @brief Load configuration
 * @param configPath Path to configuration file
 */
void loadConfiguration(const std::string& configPath);

#endif

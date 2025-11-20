#ifndef CRON_ENGINE_H
#define CRON_ENGINE_H

#include <string>
#include <chrono>

class CronEngine {
public:
    // Simplified cron: checks if the current time matches the cron expression
    // Format: "minute hour day month day_of_week"
    // Supports only specific values or '*'
    static bool isTime(const std::string& cronExpression, std::chrono::system_clock::time_point time);
};

#endif // CRON_ENGINE_H

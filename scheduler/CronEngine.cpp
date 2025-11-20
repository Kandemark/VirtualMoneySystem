#include "CronEngine.h"
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>

bool CronEngine::isTime(const std::string& cronExpression, std::chrono::system_clock::time_point time) {
    std::time_t t = std::chrono::system_clock::to_time_t(time);
    std::tm* tm = std::localtime(&t);

    std::stringstream ss(cronExpression);
    std::string segment;
    std::vector<std::string> parts;

    while (std::getline(ss, segment, ' ')) {
        parts.push_back(segment);
    }

    if (parts.size() != 5) return false;

    // 0: minute, 1: hour, 2: day, 3: month, 4: day_of_week
    int values[] = {tm->tm_min, tm->tm_hour, tm->tm_mday, tm->tm_mon + 1, tm->tm_wday};

    for (size_t i = 0; i < 5; ++i) {
        if (parts[i] != "*" && std::stoi(parts[i]) != values[i]) {
            return false;
        }
    }

    return true;
}

#pragma once

#include <string>

struct EventDefinition {
    std::string eventId;
    std::string eventType;
    std::string payload;
    std::string timestamp;
};

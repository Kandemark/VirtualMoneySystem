#include "AlertPolicy.h"

bool AlertPolicy::shouldAlert(const std::string& eventType, double threshold) const {
    return threshold > 1000.0;
}

void AlertPolicy::setThreshold(const std::string& eventType, double threshold) {
}

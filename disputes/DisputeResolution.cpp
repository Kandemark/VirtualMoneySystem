#include "DisputeResolution.h"
#include <iostream>

std::string DisputeResolution::suggestResolution(const std::string& disputeId) {
    return "Refund 50% of transaction amount";
}

bool DisputeResolution::autoResolve(const std::string& disputeId) {
    std::cout << "[Resolution] Auto-resolving dispute " << disputeId << std::endl;
    return true;
}

void DisputeResolution::escalateToHuman(const std::string& disputeId) {
    std::cout << "[Resolution] Escalating dispute " << disputeId << " to human review" << std::endl;
}

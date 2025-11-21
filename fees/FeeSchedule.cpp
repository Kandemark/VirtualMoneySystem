#include "FeeSchedule.h"

void FeeSchedule::defineFeeSchedule(const std::string& scheduleId, const std::map<std::string, double>& fees) {
    feeSchedules[scheduleId] = fees;
}

double FeeSchedule::getFee(const std::string& scheduleId, const std::string& feeType) {
    auto scheduleIt = feeSchedules.find(scheduleId);
    if (scheduleIt != feeSchedules.end()) {
        auto feeIt = scheduleIt->second.find(feeType);
        if (feeIt != scheduleIt->second.end()) {
            return feeIt->second;
        }
    }
    return 0.0;
}

void FeeSchedule::updateFee(const std::string& scheduleId, const std::string& feeType, double newFee) {
    feeSchedules[scheduleId][feeType] = newFee;
}

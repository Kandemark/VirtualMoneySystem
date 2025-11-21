#ifndef FEE_SCHEDULE_H
#define FEE_SCHEDULE_H
#include <string>
#include <map>

class FeeSchedule {
public:
    void defineFeeSchedule(const std::string& scheduleId, const std::map<std::string, double>& fees);
    double getFee(const std::string& scheduleId, const std::string& feeType);
    void updateFee(const std::string& scheduleId, const std::string& feeType, double newFee);
private:
    std::map<std::string, std::map<std::string, double>> feeSchedules;
};

#endif

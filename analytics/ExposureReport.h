#ifndef EXPOSURE_REPORT_H
#define EXPOSURE_REPORT_H

#include "../database/DatabaseManager.h"
#include <string>
#include <map>

class ExposureReport {
public:
    ExposureReport(DatabaseManager& dbManager);

    std::map<std::string, double> calculateExposureByUser() const;
    double getTotalExposure() const;

private:
    DatabaseManager& dbManager;
};

#endif // EXPOSURE_REPORT_H

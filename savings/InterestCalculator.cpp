#include "InterestCalculator.h"
#include <cmath>

double InterestCalculator::calculateSimpleInterest(double principal, double rate, double years) {
    return principal * (rate / 100.0) * years;
}

double InterestCalculator::calculateCompoundInterest(double principal, double rate, double years, int compoundingFrequency) {
    double r = rate / 100.0;
    double n = static_cast<double>(compoundingFrequency);
    return principal * std::pow(1.0 + (r / n), n * years);
}

double InterestCalculator::calculateAPY(double rate, int compoundingFrequency) {
    double r = rate / 100.0;
    double n = static_cast<double>(compoundingFrequency);
    return (std::pow(1.0 + (r / n), n) - 1.0) * 100.0;
}

#include "SpendClassificationModel.h"
#include <algorithm>

SpendCategory SpendClassificationModel::categorize(const std::string& merchant, double amount, const std::string& description) {
    std::string lowerMerchant = merchant;
    std::transform(lowerMerchant.begin(), lowerMerchant.end(), lowerMerchant.begin(), ::tolower);
    
    if (lowerMerchant.find("grocery") != std::string::npos || lowerMerchant.find("supermarket") != std::string::npos) {
        return SpendCategory::GROCERIES;
    } else if (lowerMerchant.find("movie") != std::string::npos || lowerMerchant.find("theater") != std::string::npos) {
        return SpendCategory::ENTERTAINMENT;
    } else if (lowerMerchant.find("electric") != std::string::npos || lowerMerchant.find("water") != std::string::npos) {
        return SpendCategory::UTILITIES;
    } else if (lowerMerchant.find("gas") != std::string::npos || lowerMerchant.find("uber") != std::string::npos) {
        return SpendCategory::TRANSPORTATION;
    } else if (lowerMerchant.find("hospital") != std::string::npos || lowerMerchant.find("pharmacy") != std::string::npos) {
        return SpendCategory::HEALTHCARE;
    }
    return SpendCategory::OTHER;
}

std::vector<std::pair<SpendCategory, double>> SpendClassificationModel::getCategoryProbabilities(const std::string& transaction) {
    return {
        {SpendCategory::GROCERIES, 0.4},
        {SpendCategory::ENTERTAINMENT, 0.2},
        {SpendCategory::UTILITIES, 0.15},
        {SpendCategory::TRANSPORTATION, 0.15},
        {SpendCategory::HEALTHCARE, 0.05},
        {SpendCategory::OTHER, 0.05}
    };
}

void SpendClassificationModel::trainModel(const std::vector<std::string>& labeledData) {
}

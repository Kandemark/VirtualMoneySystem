#ifndef SPEND_CLASSIFICATION_MODEL_H
#define SPEND_CLASSIFICATION_MODEL_H
#include <string>
#include <vector>

enum class SpendCategory {
    GROCERIES,
    ENTERTAINMENT,
    UTILITIES,
    TRANSPORTATION,
    HEALTHCARE,
    OTHER
};

class SpendClassificationModel {
public:
    SpendCategory categorize(const std::string& merchant, double amount, const std::string& description);
    std::vector<std::pair<SpendCategory, double>> getCategoryProbabilities(const std::string& transaction);
    void trainModel(const std::vector<std::string>& labeledData);
};

#endif

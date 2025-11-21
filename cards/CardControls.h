/**
 * @file CardControls.h
 * @brief Card security controls and restrictions
 */

#ifndef CARD_CONTROLS_H
#define CARD_CONTROLS_H

#include <string>
#include <set>

class CardControls {
public:
    void blockMerchantCategory(const std::string& cardId, const std::string& category);
    void allowMerchantCategory(const std::string& cardId, const std::string& category);
    bool isMerchantAllowed(const std::string& cardId, const std::string& category);
    void setGeoRestriction(const std::string& cardId, const std::string& country);
private:
    std::map<std::string, std::set<std::string>> blockedCategories;
    std::map<std::string, std::set<std::string>> allowedCountries;
};

#endif

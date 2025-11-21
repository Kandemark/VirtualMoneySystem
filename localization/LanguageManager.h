/**
 * @file LanguageManager.h
 * @brief Multi-language support
 */

#ifndef LANGUAGE_MANAGER_H
#define LANGUAGE_MANAGER_H

#include <string>
#include <map>

class LanguageManager {
public:
    std::string translate(const std::string& key, const std::string& language);
    void loadLanguage(const std::string& language, const std::string& translationFile);
    std::vector<std::string> getSupportedLanguages();
    void setDefaultLanguage(const std::string& language);

private:
    std::map<std::string, std::map<std::string, std::string>> translations;
    std::string defaultLanguage = "en";
};

#endif

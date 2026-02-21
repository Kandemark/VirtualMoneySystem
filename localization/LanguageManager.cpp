#include "LanguageManager.h"

#include <fstream>
#include <sstream>

std::string LanguageManager::translate(const std::string& key, const std::string& language) {
    auto langIt = translations.find(language);
    if (langIt != translations.end()) {
        auto keyIt = langIt->second.find(key);
        if (keyIt != langIt->second.end()) return keyIt->second;
    }
    auto defIt = translations.find(defaultLanguage);
    if (defIt != translations.end() && defIt->second.count(key)) return defIt->second.at(key);
    return key;
}

void LanguageManager::loadLanguage(const std::string& language, const std::string& translationFile) {
    std::ifstream in(translationFile);
    std::string line;
    while (std::getline(in, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;
        translations[language][line.substr(0, pos)] = line.substr(pos + 1);
    }
}

std::vector<std::string> LanguageManager::getSupportedLanguages() {
    std::vector<std::string> langs;
    for (const auto& [lang, _] : translations) langs.push_back(lang);
    return langs;
}

void LanguageManager::setDefaultLanguage(const std::string& language) { defaultLanguage = language; }

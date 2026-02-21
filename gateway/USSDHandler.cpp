#include "USSDHandler.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_menus; }

std::string USSDHandler::handleUSSDRequest(const std::string& sessionId, const std::string&, const std::string& input) {
    return "CON " + getMenuResponse(sessionId, input);
}
void USSDHandler::registerMenu(const std::string& menuId, const std::string& menuStructure) { g_menus[menuId] = menuStructure; }
std::string USSDHandler::getMenuResponse(const std::string& menuId, const std::string& selection) {
    auto it = g_menus.find(menuId); if (it == g_menus.end()) return "Menu unavailable"; return it->second + "
Selected:" + selection;
}

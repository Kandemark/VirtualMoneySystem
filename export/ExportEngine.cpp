#include "ExportEngine.h"

#include <algorithm>
#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_handlers; }

std::string ExportEngine::exportData(const std::string& data, const std::string& format, const std::map<std::string, std::string>&) {
    std::string f = format; std::transform(f.begin(), f.end(), f.begin(), ::toupper);
    if (f == "JSON") return "{"data":"" + data + ""}";
    if (f == "CSV") return data;
    if (f == "PDF") return "PDF:" + data;
    return "";
}

void ExportEngine::registerFormat(const std::string& format, const std::string& handler) { g_handlers[format] = handler; }

std::vector<std::string> ExportEngine::getSupportedFormats() {
    std::vector<std::string> out = {"CSV", "PDF", "JSON"};
    for (const auto& [k, _] : g_handlers) out.push_back(k);
    return out;
}

#include "DataExportManager.h"

#include <unordered_map>

namespace { std::unordered_map<std::string, std::string> g_jobs; std::unordered_map<std::string, std::vector<std::string>> g_userJobs; }

std::string DataExportManager::requestExport(const std::string& userId, const std::string& dataType, const std::string& format) {
    const std::string id = "export_" + std::to_string(std::hash<std::string>{}(userId + dataType + format));
    g_jobs[id] = "READY";
    g_userJobs[userId].push_back(id);
    return id;
}
std::string DataExportManager::getExportStatus(const std::string& jobId) { return g_jobs.count(jobId)?g_jobs[jobId]:"NOT_FOUND"; }
std::string DataExportManager::downloadExport(const std::string& jobId) { return g_jobs.count(jobId)?("exports/"+jobId+".dat"):""; }
std::vector<std::string> DataExportManager::listExports(const std::string& userId) { return g_userJobs[userId]; }

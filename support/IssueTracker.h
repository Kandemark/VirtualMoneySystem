/**
 * @file IssueTracker.h
 * @brief Track and manage system issues
 */

#ifndef ISSUE_TRACKER_H
#define ISSUE_TRACKER_H

#include <string>
#include <vector>

struct Issue {
    std::string issueId;
    std::string title;
    std::string description;
    std::string severity;
    std::string status;
};

class IssueTracker {
public:
    std::string reportIssue(const std::string& title, const std::string& description, const std::string& severity);
    Issue getIssue(const std::string& issueId);
    void updateIssueStatus(const std::string& issueId, const std::string& status);
    std::vector<Issue> getOpenIssues();
    void resolveIssue(const std::string& issueId);
};

#endif

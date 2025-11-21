/**
 * @file IssueTracker.cpp
 */

#include "IssueTracker.h"
#include <iostream>

IssueTracker::IssueTracker() {}

std::string IssueTracker::reportIssue(const std::string& title, const std::string& description) {
    std::string issueId = "ISSUE_" + std::to_string(issues.size() + 1);
    
    Issue issue;
    issue.issueId = issueId;
    issue.title = title;
    issue.description = description;
    issue.status = "open";
    issue.priority = "normal";
    
    issues[issueId] = issue;
    
    std::cout << "Issue reported: " << issueId << " - " << title << std::endl;
    
    return issueId;
}

bool IssueTracker::updateStatus(const std::string& issueId, const std::string& status) {
    auto it = issues.find(issueId);
    if (it != issues.end()) {
        it->second.status = status;
        std::cout << "Issue " << issueId << " status updated to: " << status << std::endl;
        return true;
    }
    return false;
}

std::vector<Issue> IssueTracker::getOpenIssues() const {
    std::vector<Issue> openIssues;
    for (const auto& [id, issue] : issues) {
        if (issue.status == "open") {
            openIssues.push_back(issue);
        }
    }
    return openIssues;
}

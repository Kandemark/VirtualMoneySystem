/**
 * @file DistributedCluster.cpp
 */

#include "DistributedCluster.h"
#include <algorithm>
#include <iostream>

namespace VirtualMoney {

DistributedCluster::DistributedCluster(const std::string& nodeId) 
    : myNodeId(nodeId), leaderId("") {}

bool DistributedCluster::addNode(const ClusterNode& node) {
    nodes[node.nodeId] = node;
    std::cout << "Node added: " << node.nodeId << std::endl;
    if (nodes.size() == 1) electLeader();
    return true;
}

bool DistributedCluster::removeNode(const std::string& nodeId) {
    nodes.erase(nodeId);
    if (nodeId == leaderId) electLeader();
    return true;
}

void DistributedCluster::electLeader() {
    if (nodes.empty()) return;
    leaderId = nodes.begin()->first;
    nodes[leaderId].isLeader = true;
    std::cout << "Leader elected: " << leaderId << std::endl;
}

bool DistributedCluster::distributeTransaction(const std::string& txData) {
    if (nodes.empty()) return false;
    
    // Round-robin distribution
    static size_t nextNode = 0;
    auto it = nodes.begin();
    std::advance(it, nextNode % nodes.size());
    nextNode++;
    
    std::cout << "Transaction distributed to: " << it->first << std::endl;
    return true;
}

std::vector<ClusterNode> DistributedCluster::getActiveNodes() const {
    std::vector<ClusterNode> active;
    for (const auto& [id, node] : nodes) {
        if (node.active) active.push_back(node);
    }
    return active;
}

} // namespace VirtualMoney

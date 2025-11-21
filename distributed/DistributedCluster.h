/**
 * @file DistributedCluster.h
 * @brief Distributed processing for horizontal scaling
 */

#ifndef DISTRIBUTED_CLUSTER_H
#define DISTRIBUTED_CLUSTER_H

#include <string>
#include <vector>
#include <map>

namespace VirtualMoney {

struct ClusterNode {
    std::string nodeId;
    std::string ipAddress;
    int port;
    bool isLeader;
    bool active;
    double cpuUsage;
    double memoryUsage;
};

class DistributedCluster {
public:
    DistributedCluster(const std::string& nodeId);
    
    bool addNode(const ClusterNode& node);
    bool removeNode(const std::string& nodeId);
    void electLeader();
    bool distributeTransaction(const std::string& txData);
    std::vector<ClusterNode> getActiveNodes() const;
    
private:
    std::string myNodeId;
    std::map<std::string, ClusterNode> nodes;
    std::string leaderId;
};

} // namespace VirtualMoney

#endif

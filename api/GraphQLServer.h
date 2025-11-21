/**
 * @file GraphQLServer.h
 * @brief GraphQL API server for flexible queries
 */

#ifndef GRAPHQL_SERVER_H
#define GRAPHQL_SERVER_H

#include <string>
#include <map>
#include <vector>
#include <functional>

namespace VirtualMoney {

struct GraphQLQuery {
    std::string query;
    std::map<std::string, std::string> variables;
};

struct GraphQLResponse {
    std::string data;
    std::vector<std::string> errors;
};

class GraphQLServer {
public:
    GraphQLServer(int port);
    
    /**
     * @brief Start GraphQL server
     */
    void start();
    
    /**
     * @brief Execute GraphQL query
     */
    GraphQLResponse executeQuery(const GraphQLQuery& query);
    
    /**
     * @brief Register resolver
     */
    void registerResolver(const std::string& typeName, 
                         const std::string& fieldName,
                         std::function<std::string(const std::map<std::string, std::string>&)> resolver);
    
    /**
     * @brief Get schema
     */
    std::string getSchema();
    
private:
    int port;
    bool running;
    std::map<std::string, std::map<std::string, std::function<std::string(const std::map<std::string, std::string>&)>>> resolvers;
    
    void initializeSchema();
    std::string parseQuery(const std::string& query);
    std::string resolveField(const std::string& typeName, const std::string& fieldName, const std::map<std::string, std::string>& args);
};

} // namespace VirtualMoney

#endif

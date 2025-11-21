/**
 * @file ContractEngine.h
 * @brief Smart contract execution engine
 */

#ifndef CONTRACT_ENGINE_H
#define CONTRACT_ENGINE_H

#include <string>
#include <map>

/**
 * @brief Executes smart contracts
 */
class ContractEngine {
public:
    /**
     * @brief Deploy contract
     * @param contractCode Contract code
     * @param params Deployment parameters
     * @return Contract ID
     */
    std::string deployContract(const std::string& contractCode, const std::map<std::string, std::string>& params);
    
    /**
     * @brief Execute contract
     * @param contractId Contract identifier
     * @param method Method to call
     * @param args Method arguments
     * @return Execution result
     */
    std::string executeContract(const std::string& contractId, const std::string& method, const std::map<std::string, std::string>& args);
    
    /**
     * @brief Get contract state
     * @param contractId Contract identifier
     * @return Contract state
     */
    std::map<std::string, std::string> getContractState(const std::string& contractId);

private:
    std::map<std::string, std::string> contracts;
};

#endif

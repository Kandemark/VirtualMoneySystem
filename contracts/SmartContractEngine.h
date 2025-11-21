/**
 * @file SmartContractEngine.h
 * @brief Smart contract execution engine
 */

#ifndef SMART_CONTRACT_ENGINE_H
#define SMART_CONTRACT_ENGINE_H

#include <string>
#include <vector>
#include <map>
#include <functional>

namespace VirtualMoney {

struct SmartContract {
    std::string contractId;
    std::string code;
    std::string language;        // "javascript", "lua", "wasm"
    std::map<std::string, std::string> state;
    bool active;
};

class SmartContractEngine {
public:
    SmartContractEngine();
    
    std::string deployContract(const std::string& code, const std::string& language);
    bool executeContract(const std::string& contractId, 
                        const std::map<std::string, std::string>& params);
    bool callFunction(const std::string& contractId, 
                     const std::string& functionName,
                     const std::vector<std::string>& args);
    
    std::map<std::string, std::string> getContractState(const std::string& contractId);
    bool updateContractState(const std::string& contractId, 
                            const std::string& key, 
                            const std::string& value);
    
    bool pauseContract(const std::string& contractId);
    bool resumeContract(const std::string& contractId);
    
private:
    std::map<std::string, SmartContract> contracts;
    
    std::string generateContractId();
    bool validateCode(const std::string& code, const std::string& language);
    bool executeSandboxed(const std::string& code);
};

} // namespace VirtualMoney

#endif

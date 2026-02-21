#include "ContractEngine.h"

std::string ContractEngine::deployContract(const std::string& contractCode, const std::map<std::string, std::string>& params) {
    if (contractCode.empty()) return "";
    const std::string id = "contract_" + std::to_string(std::hash<std::string>{}(contractCode + std::to_string(params.size())));
    contracts[id] = contractCode;
    return id;
}

std::string ContractEngine::executeContract(const std::string& contractId, const std::string& method, const std::map<std::string, std::string>& args) {
    if (contracts.find(contractId) == contracts.end()) return "";
    return "executed:" + method + ":args=" + std::to_string(args.size());
}

std::map<std::string, std::string> ContractEngine::getContractState(const std::string& contractId) {
    std::map<std::string, std::string> state;
    auto it = contracts.find(contractId);
    if (it == contracts.end()) return state;
    state["contractId"] = contractId;
    state["codeHash"] = std::to_string(std::hash<std::string>{}(it->second));
    state["status"] = "active";
    return state;
}

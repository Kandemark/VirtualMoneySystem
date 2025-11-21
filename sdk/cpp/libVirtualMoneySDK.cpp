/**
 * @file libVirtualMoneySDK.cpp - Main SDK library
 */

#include <iostream>

extern "C" {
    void* vms_init(const char* apiKey) {
        std::cout << "VirtualMoney SDK initialized" << std::endl;
        return nullptr;
    }
    
    void vms_cleanup(void* handle) {
        std::cout << "VirtualMoney SDK cleaned up" << std::endl;
    }
    
    const char* vms_create_wallet(void* handle, const char* userId) {
        return "WALLET_123";
    }
    
    double vms_get_balance(void* handle, const char* walletId) {
        return 1000.0;
    }
}

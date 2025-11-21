/**
 * @file generate_keys.cpp - Utility to generate encryption keys
 */

#include <iostream>
#include <random>
#include <iomanip>

void generateKey(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    
    std::cout << "Generated key: ";
    for (int i = 0; i < length; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "VirtualMoney Key Generator" << std::endl;
    generateKey(32); // 256-bit key
    return 0;
}

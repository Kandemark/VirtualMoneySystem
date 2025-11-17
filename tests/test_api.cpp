#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>
#include <signal.h>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void testWalletAPI() {
    // Create wallet
    std::string response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"currency\":\"USD\"}' http://localhost:18080/wallet/create");
    assert(response.find("\"balance\":0") != std::string::npos);

    // Get balance
    response = exec("curl -s http://localhost:18080/wallet/testuser/balance");
    assert(response.find("\"balance\":0") != std::string::npos);

    // Deposit
    response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"amount\":100}' http://localhost:18080/wallet/deposit");
    assert(response.find("\"balance\":100") != std::string::npos);

    // Get balance again
    response = exec("curl -s http://localhost:18080/wallet/testuser/balance");
    assert(response.find("\"balance\":100") != std::string::npos);

    // Withdraw
    response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"amount\":50}' http://localhost:18080/wallet/withdraw");
    assert(response.find("\"balance\":50") != std::string::npos);

    // Get balance again
    response = exec("curl -s http://localhost:18080/wallet/testuser/balance");
    assert(response.find("\"balance\":50") != std::string::npos);

    std::cout << "Wallet API tests passed!" << std::endl;
}

void testTransactionAPI() {
    // Create wallets for sender and receiver
    exec("curl -s -X POST -d '{\"userId\":\"sender\", \"currency\":\"USD\"}' http://localhost:18080/wallet/create");
    exec("curl -s -X POST -d '{\"userId\":\"receiver\", \"currency\":\"USD\"}' http://localhost:18080/wallet/create");

    // Deposit to sender's wallet
    exec("curl -s -X POST -d '{\"userId\":\"sender\", \"amount\":100}' http://localhost:18080/wallet/deposit");

    // Create a transaction
    std::string response = exec("curl -s -X POST -d '{\"senderId\":\"sender\", \"receiverId\":\"receiver\", \"amount\":70}' http://localhost:18080/transaction/create");
    assert(response.find("Transaction successful") != std::string::npos);

    // Verify balances
    response = exec("curl -s http://localhost:18080/wallet/sender/balance");
    assert(response.find("\"balance\":30") != std::string::npos);
    response = exec("curl -s http://localhost:18080/wallet/receiver/balance");
    assert(response.find("\"balance\":70") != std::string::npos);

    std::cout << "Transaction API tests passed!" << std::endl;
}

int main() {
    // Start the server in the background
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execl("./VirtualMoneySystem", "VirtualMoneySystem", (char*)NULL);
        perror("execl failed");
        exit(1); // Should not be reached
    } else {
        // Parent process
        sleep(2); // Give the server some time to start

        try {
            testWalletAPI();
            testTransactionAPI();
        } catch (const std::exception& e) {
            std::cerr << "Test failed: " << e.what() << std::endl;
            kill(pid, SIGTERM);
            return 1;
        }

        // Stop the server
        kill(pid, SIGTERM);
    }

    return 0;
}

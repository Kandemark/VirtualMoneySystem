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
#include <sys/wait.h>
#include <fcntl.h>

int port = 18080;

std::string exec(const char* cmd_format) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), cmd_format, port);

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
    std::string response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"currency\":\"USD\"}' http://localhost:%d/wallet/create");
    assert(response.find("\"balance\":0") != std::string::npos);

    // Get balance
    response = exec("curl -s http://localhost:%d/wallet/testuser/balance");
    assert(response.find("\"balance\":0") != std::string::npos);

    // Deposit
    response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"amount\":100}' http://localhost:%d/wallet/deposit");
    assert(response.find("\"balance\":100") != std::string::npos);

    // Get balance again
    response = exec("curl -s http://localhost:%d/wallet/testuser/balance");
    assert(response.find("\"balance\":100") != std::string::npos);

    // Withdraw
    response = exec("curl -s -X POST -d '{\"userId\":\"testuser\", \"amount\":50}' http://localhost:%d/wallet/withdraw");
    assert(response.find("\"balance\":50") != std::string::npos);

    // Get balance again
    response = exec("curl -s http://localhost:%d/wallet/testuser/balance");
    assert(response.find("\"balance\":50") != std::string::npos);

    std::cout << "Wallet API tests passed!" << std::endl;
}

void testTransactionAPI() {
    // Create wallets for sender and receiver
    exec("curl -s -X POST -d '{\"userId\":\"sender\", \"currency\":\"USD\"}' http://localhost:%d/wallet/create");
    exec("curl -s -X POST -d '{\"userId\":\"receiver\", \"currency\":\"USD\"}' http://localhost:%d/wallet/create");

    // Deposit to sender's wallet
    exec("curl -s -X POST -d '{\"userId\":\"sender\", \"amount\":100}' http://localhost:%d/wallet/deposit");

    // Create a transaction
    std::string response = exec("curl -s -X POST -d '{\"senderId\":\"sender\", \"receiverId\":\"receiver\", \"amount\":70}' http://localhost:%d/transaction/create");
    assert(response.find("Transaction successful") != std::string::npos);

    // Verify balances
    response = exec("curl -s http://localhost:%d/wallet/sender/balance");
    assert(response.find("\"balance\":30") != std::string::npos);
    response = exec("curl -s http://localhost:%d/wallet/receiver/balance");
    assert(response.find("\"balance\":70") != std::string::npos);

    std::cout << "Transaction API tests passed!" << std::endl;
}

void testHistoryAPI() {
    // Create wallets for history test
    exec("curl -s -X POST -d '{\"userId\":\"userA\", \"currency\":\"USD\"}' http://localhost:%d/wallet/create");
    exec("curl -s -X POST -d '{\"userId\":\"userB\", \"currency\":\"USD\"}' http://localhost:%d/wallet/create");

    // Deposit to userA's wallet
    exec("curl -s -X POST -d '{\"userId\":\"userA\", \"amount\":200}' http://localhost:%d/wallet/deposit");

    // Create a transaction from userA to userB
    exec("curl -s -X POST -d '{\"senderId\":\"userA\", \"receiverId\":\"userB\", \"amount\":50}' http://localhost:%d/transaction/create");

    // Get userA's history and verify the transaction is present
    std::string responseA = exec("curl -s http://localhost:%d/wallet/userA/history");
    assert(responseA.find("\"senderId\":\"userA\"") != std::string::npos);
    assert(responseA.find("\"receiverId\":\"userB\"") != std::string::npos);
    assert(responseA.find("\"amount\":50") != std::string::npos);

    // Get userB's history and verify the transaction is present
    std::string responseB = exec("curl -s http://localhost:%d/wallet/userB/history");
    assert(responseB.find("\"senderId\":\"userA\"") != std::string::npos);
    assert(responseB.find("\"receiverId\":\"userB\"") != std::string::npos);
    assert(responseB.find("\"amount\":50") != std::string::npos);

    std::cout << "History API tests passed!" << std::endl;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    // Clean up any previous database file to ensure a clean state for the test.
    remove("vms.db");
    remove("server.log");

    // Start the server in the background
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: Redirect stderr to a log file and execute the server.
        int fd = open("server.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 2); // Redirect stderr
        close(fd);
        char port_str[10];
        snprintf(port_str, sizeof(port_str), "%d", port);
        execl("./VirtualMoneySystem", "VirtualMoneySystem", port_str, (char*)NULL);
        perror("execl failed"); // If execl returns, an error occurred.
        exit(1);
    } else if (pid > 0) {
        // Parent process: Give the server time to start up.
        sleep(2);

        try {
            // Run the tests.
            testWalletAPI();
            testTransactionAPI();
            testHistoryAPI();
        } catch (const std::exception& e) {
            std::cerr << "Test failed: " << e.what() << std::endl;
            kill(pid, SIGKILL); // Terminate the server process immediately.
            waitpid(pid, NULL, 0); // Wait for the child to exit.
            remove("vms.db"); // Clean up the database file.
            return 1;
        }

        // Stop the server and clean up.
        kill(pid, SIGKILL);
        waitpid(pid, NULL, 0);
        remove("vms.db");
    } else {
        // Fork failed.
        perror("fork failed");
        return 1;
    }

    return 0;
}

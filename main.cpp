#include "core/Wallet.h"
#include "core/TransactionEngine.h"
#include "database/DatabaseManager.h"
#include "scheduler/JobScheduler.h"
#include "scheduler/RecurringPayments.h"
#include "api/RESTServer.h"
#include "api/WalletEndpoints.h"
#include "analytics/TransactionStats.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

// Use a single, global DatabaseManager instance for the entire application.
DatabaseManager dbManager("vms.db");
// A mutex to protect access to the shared DatabaseManager from multiple threads.
std::mutex dbMutex;

// The TransactionEngine will process transactions.
TransactionEngine transactionEngine;

int main()
{
    // Initialize the database once, before the server starts.
    try {
        dbManager.initialize();
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to initialize database: " << e.what() << std::endl;
        return 1;
    }

    // Initialize Scheduler
    JobScheduler scheduler;
    RecurringPayments recurringPayments(transactionEngine, dbManager);

    // Schedule recurring payment checks every 60 seconds
    scheduler.schedule([&recurringPayments]() {
        recurringPayments.processPayments();
    }, 60);

    scheduler.start();

    // Initialize Analytics
    TransactionStats transactionStats(transactionEngine);

        if (dbManager.getWallet(userId)) {
            return crow::response(409, "{\"error\": \"Wallet for this user already exists\"}");
        }

        Wallet newWallet(userId, currency);
        if (!dbManager.createWallet(newWallet)) {
            return crow::response(500, "{\"error\": \"Failed to create wallet in database\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["currency"] = currency;
        response["balance"] = newWallet.getBalance();

        return crow::response(201, response);
    });

    // Endpoint to get a wallet's balance.
    CROW_ROUTE(app, "/wallet/<string>/balance")
    ([](const std::string& userId){
        std::lock_guard<std::mutex> lock(dbMutex);
        auto wallet = dbManager.getWallet(userId);
        if (!wallet) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["currency"] = wallet->getCurrency();
        response["balance"] = wallet->getBalance();

        return crow::response(200, response);
    });

    // Endpoint to deposit funds.
    CROW_ROUTE(app, "/wallet/deposit").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing userId or amount\"}");
        }

        std::string userId = body["userId"].s();
        double amount = body["amount"].d();

        std::lock_guard<std::mutex> lock(dbMutex);

        auto walletOpt = dbManager.getWallet(userId);
        if (!walletOpt) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }
        Wallet wallet = *walletOpt;

        try {
            wallet.deposit(amount);
        } catch (const std::invalid_argument& e) {
            return crow::response(400, std::string("{\"error\": \"") + e.what() + "\"}");
        }

        if (!dbManager.updateWalletBalance(userId, wallet.getBalance())) {
            return crow::response(500, "{\"error\": \"Failed to update wallet balance\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["balance"] = wallet.getBalance();

        return crow::response(200, response);
    });

    // Endpoint to withdraw funds.
    CROW_ROUTE(app, "/wallet/withdraw").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing userId or amount\"}");
        }

        std::string userId = body["userId"].s();
        double amount = body["amount"].d();

        std::lock_guard<std::mutex> lock(dbMutex);

        auto walletOpt = dbManager.getWallet(userId);
        if (!walletOpt) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }
        Wallet wallet = *walletOpt;

        try {
            if (!wallet.withdraw(amount)) {
                return crow::response(400, "{\"error\": \"Insufficient funds\"}");
            }
        } catch (const std::invalid_argument& e) {
            return crow::response(400, std::string("{\"error\": \"") + e.what() + "\"}");
        }

        if (!dbManager.updateWalletBalance(userId, wallet.getBalance())) {
            return crow::response(500, "{\"error\": \"Failed to update wallet balance\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["balance"] = wallet.getBalance();

        return crow::response(200, response);
    });

    // Endpoint to create a transaction.
    // This now also saves the transaction to the database.
    CROW_ROUTE(app, "/transaction/create").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("senderId") || !body.has("receiverId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing senderId, receiverId, or amount\"}");
        }

        std::string senderId = body["senderId"].s();
        std::string receiverId = body["receiverId"].s();
        double amount = body["amount"].d();

        std::lock_guard<std::mutex> lock(dbMutex);

        auto senderWalletOpt = dbManager.getWallet(senderId);
        auto receiverWalletOpt = dbManager.getWallet(receiverId);

        if (!senderWalletOpt || !receiverWalletOpt) {
            return crow::response(404, "{\"error\": \"Sender or receiver wallet not found\"}");
        }

        Wallet senderWallet = *senderWalletOpt;
        Wallet receiverWallet = *receiverWalletOpt;

        if (transactionEngine.processTransaction(senderWallet, receiverWallet, amount)) {
            // If the transaction is successful, update both wallets in the database
            // and create a new transaction record.
            dbManager.updateWalletBalance(senderId, senderWallet.getBalance());
            dbManager.updateWalletBalance(receiverId, receiverWallet.getBalance());

            Transaction newTransaction(senderId, receiverId, amount, senderWallet.getCurrency());
            dbManager.createTransaction(newTransaction);

            return crow::response(200, "{\"status\": \"Transaction successful\"}");
        } else {
            return crow::response(400, "{\"error\": \"Transaction failed. Check for sufficient funds or matching currencies.\"}");
        }
    });
    // Initialize API
    WalletEndpoints walletEndpoints(dbManager, transactionEngine, dbMutex, transactionStats);
    RESTServer server(walletEndpoints);

    // Endpoint to get a user's transaction history.
    CROW_ROUTE(app, "/wallet/<string>/history")
    ([](const std::string& userId){
        std::lock_guard<std::mutex> lock(dbMutex);

        auto history = dbManager.getTransactionHistory(userId);

        crow::json::wvalue::list response_list;
        for (const auto& tx : history) {
            crow::json::wvalue tx_json;
            tx_json["senderId"] = tx.getSenderId();
            tx_json["receiverId"] = tx.getReceiverId();
            tx_json["amount"] = tx.getAmount();
            tx_json["currency"] = tx.getCurrency();

            auto time_point = tx.getTimestamp();
            std::time_t time = std::chrono::system_clock::to_time_t(time_point);
            std::stringstream ss;
            ss << std::put_time(std::gmtime(&time), "%Y-%m-%d %H:%M:%S");
            tx_json["timestamp"] = ss.str();

            response_list.push_back(tx_json);
        }

        return crow::response(crow::json::wvalue(response_list));
    });

    // Use a random port to avoid "Address already in use" errors in tests.
    srand(time(0));
    int port = 10000 + (rand() % 10000);
    
    server.run(port);
    
    // Stop scheduler on exit (though app.run() blocks)
    scheduler.stop();
}

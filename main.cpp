#include "crow.h"
#include "core/Wallet.h"
#include "core/TransactionEngine.h"
#include <iostream>
#include <unordered_map>
#include <memory>

// In-memory storage for wallets, keyed by userId
std::unordered_map<std::string, std::shared_ptr<Wallet>> wallets;
// Transaction engine to process transactions
TransactionEngine transactionEngine;

int main()
{
    crow::SimpleApp app;

    // Endpoint to create a new wallet
    CROW_ROUTE(app, "/wallet/create").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("currency")) {
            return crow::response(400, "{\"error\": \"Missing userId or currency\"}");
        }

        std::string userId = body["userId"].s();
        std::string currency = body["currency"].s();

        if (wallets.find(userId) != wallets.end()) {
            return crow::response(409, "{\"error\": \"Wallet for this user already exists\"}");
        }

        wallets[userId] = std::make_shared<Wallet>(userId, currency);

        crow::json::wvalue response;
        response["userId"] = userId;
        response["currency"] = currency;
        response["balance"] = wallets[userId]->getBalance();

        return crow::response(201, response);
    });

    // Endpoint to get a wallet's balance
    CROW_ROUTE(app, "/wallet/<string>/balance")
    ([](const std::string& userId){
        if (wallets.find(userId) == wallets.end()) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["currency"] = wallets[userId]->getCurrency();
        response["balance"] = wallets[userId]->getBalance();

        return crow::response(200, response);
    });

    // Endpoint to deposit funds
    CROW_ROUTE(app, "/wallet/deposit").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing userId or amount\"}");
        }

        std::string userId = body["userId"].s();
        double amount = body["amount"].d();

        if (wallets.find(userId) == wallets.end()) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }

        try {
            wallets[userId]->deposit(amount);
        } catch (const std::invalid_argument& e) {
            return crow::response(400, std::string("{\"error\": \"") + e.what() + "\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["balance"] = wallets[userId]->getBalance();

        return crow::response(200, response);
    });

    // Endpoint to withdraw funds
    CROW_ROUTE(app, "/wallet/withdraw").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing userId or amount\"}");
        }

        std::string userId = body["userId"].s();
        double amount = body["amount"].d();

        if (wallets.find(userId) == wallets.end()) {
            return crow::response(404, "{\"error\": \"Wallet not found\"}");
        }

        try {
            if (!wallets[userId]->withdraw(amount)) {
                return crow::response(400, "{\"error\": \"Insufficient funds\"}");
            }
        } catch (const std::invalid_argument& e) {
            return crow::response(400, std::string("{\"error\": \"") + e.what() + "\"}");
        }

        crow::json::wvalue response;
        response["userId"] = userId;
        response["balance"] = wallets[userId]->getBalance();

        return crow::response(200, response);
    });

    // Endpoint to create a transaction
    CROW_ROUTE(app, "/transaction/create").methods("POST"_method)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("senderId") || !body.has("receiverId") || !body.has("amount")) {
            return crow::response(400, "{\"error\": \"Missing senderId, receiverId, or amount\"}");
        }

        std::string senderId = body["senderId"].s();
        std::string receiverId = body["receiverId"].s();
        double amount = body["amount"].d();

        if (wallets.find(senderId) == wallets.end() || wallets.find(receiverId) == wallets.end()) {
            return crow::response(404, "{\"error\": \"Sender or receiver wallet not found\"}");
        }

        if (transactionEngine.processTransaction(*wallets[senderId], *wallets[receiverId], amount)) {
            return crow::response(200, "{\"status\": \"Transaction successful\"}");
        } else {
            return crow::response(400, "{\"error\": \"Transaction failed. Check for sufficient funds or matching currencies.\"}");
        }
    });

    app.port(18080).multithreaded().run();
}

#include "WalletEndpoints.h"
#include <iomanip>
#include <sstream>

WalletEndpoints::WalletEndpoints(DatabaseManager& db, TransactionEngine& te, std::mutex& mtx, TransactionStats& stats)
    : dbManager(db), transactionEngine(te), dbMutex(mtx), transactionStats(stats) {}

void WalletEndpoints::registerRoutes(crow::SimpleApp& app) {
    
    // Analytics Endpoint
    CROW_ROUTE(app, "/analytics/transactions")
    ([this](){
        crow::json::wvalue response;
        response["total_count"] = transactionStats.getTotalCount();
        
        auto volumes = transactionStats.getTotalVolume();
        crow::json::wvalue volJson;
        for (const auto& [currency, amount] : volumes) {
            volJson[currency] = amount;
        }
        response["total_volume"] = std::move(volJson);
        
        return crow::response(200, response);
    });

    // Create Wallet
    CROW_ROUTE(app, "/wallet/create").methods("POST"_method)
    ([this](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("userId") || !body.has("currency")) {
            return crow::response(400, "{\"error\": \"Missing userId or currency\"}");
        }

        std::string userId = body["userId"].s();
        std::string currency = body["currency"].s();

        if (!kycValidator.validateUserId(userId)) {
            return crow::response(400, "{\"error\": \"Invalid User ID format\"}");
        }

        std::lock_guard<std::mutex> lock(dbMutex);

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

    // Get Balance
    CROW_ROUTE(app, "/wallet/<string>/balance")
    ([this](const std::string& userId){
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

    // Deposit
    CROW_ROUTE(app, "/wallet/deposit").methods("POST"_method)
    ([this](const crow::request& req){
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

    // Withdraw
    CROW_ROUTE(app, "/wallet/withdraw").methods("POST"_method)
    ([this](const crow::request& req){
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
    
    // Transfer (Transaction)
    CROW_ROUTE(app, "/transaction/create").methods("POST"_method)
    ([this](const crow::request& req){
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
            dbManager.updateWalletBalance(senderId, senderWallet.getBalance());
            dbManager.updateWalletBalance(receiverId, receiverWallet.getBalance());
            
            // Persist transaction
            Transaction newTransaction(senderId, receiverId, amount, senderWallet.getCurrency());
            dbManager.createTransaction(newTransaction);

            // AML Check
            amlScanner.isSuspicious(newTransaction);
            
            return crow::response(200, "{\"status\": \"Transaction successful\"}");
        } else {
            return crow::response(400, "{\"error\": \"Transaction failed. Check for sufficient funds or matching currencies.\"}");
        }
    });

    // Transaction History
    CROW_ROUTE(app, "/wallet/<string>/history")
    ([this](const std::string& userId){
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
}

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "sqlite3.h"
#include "../core/Wallet.h"
#include <string>
#include <memory>
#include <optional>

/**
 * @class DatabaseManager
 * @brief Handles all interactions with the SQLite database.
 *
 * This class is responsible for opening and closing the database connection,
 * creating the necessary tables, and managing all data persistence for
 * wallets and transactions.
 */
class DatabaseManager {
public:
    /**
     * @brief Constructs a DatabaseManager object.
     * @param dbPath The file path to the SQLite database.
     */
    DatabaseManager(const std::string& dbPath);

    /**
     * @brief Destroys the DatabaseManager object and closes the database connection.
     */
    ~DatabaseManager();

    /**
     * @brief Initializes the database by creating the required tables if they don't exist.
     */
    void initialize();

    /**
     * @brief Creates a new wallet in the database.
     * @param wallet The Wallet object to create.
     * @return True if the wallet was created successfully, false otherwise.
     */
    bool createWallet(const Wallet& wallet);

    /**
     * @brief Retrieves a wallet from the database.
     * @param userId The ID of the user whose wallet to retrieve.
     * @return An optional containing the Wallet object if found, otherwise an empty optional.
     */
    std::optional<Wallet> getWallet(const std::string& userId);

    /**
     * @brief Updates the balance of an existing wallet in the database.
     * @param userId The ID of the user whose wallet to update.
     * @param newBalance The new balance for the wallet.
     * @return True if the update was successful, false otherwise.
     */
    bool updateWalletBalance(const std::string& userId, double newBalance);

private:
    sqlite3* db; // The SQLite database connection handle.
};

#endif // DATABASE_MANAGER_H

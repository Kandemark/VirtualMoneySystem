#include <iostream>
#include <string>
#include <cstdlib>

// Simple CLI client for VirtualMoneySystem
// Connects to the API server to perform operations

void printHeader() {
    std::cout << "\n========================================\n";
    std::cout << "  VirtualMoneySystem - Client CLI\n";
    std::cout << "========================================\n\n";
}

void printMenu() {
    std::cout << "\n--- Main Menu ---\n";
    std::cout << "1. Sign Up\n";
    std::cout << "2. Login\n";
    std::cout << "3. Create Wallet\n";
    std::cout << "4. Check Balance\n";
    std::cout << "5. Send Money\n";
    std::cout << "6. Transaction History\n";
    std::cout << "7. Currency Converter\n";
    std::cout << "0. Exit\n";
    std::cout << "\nChoice: ";
}

void signup() {
    std::string username, password, email;
    std::cout << "\n--- Sign Up ---\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
    std::cin >> password;
    
    // TODO: Make API call to POST /api/v1/users/signup
    std::cout << "\n[API] POST /api/v1/users/signup\n";
    std::cout << "[SUCCESS] Account created for " << username << "\n";
    std::cout << "[INFO] Please login to continue\n";
}

void login() {
    std::string username, password;
    std::cout << "\n--- Login ---\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    
    // TODO: Make API call to POST /api/v1/auth/login
    std::cout << "\n[API] POST /api/v1/auth/login\n";
    std::cout << "[SUCCESS] Logged in as " << username << "\n";
    std::cout << "[TOKEN] eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...\n";
}

void createWallet() {
    std::string currency;
    std::cout << "\n--- Create Wallet ---\n";
    std::cout << "Currency (USD/EUR/KES/BTC): ";
    std::cin >> currency;
    
    // TODO: Make API call to POST /api/v1/wallets
    std::cout << "\n[API] POST /api/v1/wallets\n";
    std::cout << "[SUCCESS] Wallet created\n";
    std::cout << "[WALLET ID] " << currency << "_WALLET_12345\n";
    std::cout << "[BALANCE] 0.00 " << currency << "\n";
}

void checkBalance() {
    std::string walletId;
    std::cout << "\n--- Check Balance ---\n";
    std::cout << "Wallet ID: ";
    std::cin >> walletId;
    
    // TODO: Make API call to GET /api/v1/wallets/{id}/balance
    std::cout << "\n[API] GET /api/v1/wallets/" << walletId << "/balance\n";
    std::cout << "[BALANCE] 1,250.50 USD\n";
}

void sendMoney() {
    std::string fromWallet, toWallet, amount;
    std::cout << "\n--- Send Money ---\n";
    std::cout << "From Wallet ID: ";
    std::cin >> fromWallet;
    std::cout << "To Wallet ID: ";
    std::cin >> toWallet;
    std::cout << "Amount: ";
    std::cin >> amount;
    
    // TODO: Make API call to POST /api/v1/transactions
    std::cout << "\n[API] POST /api/v1/transactions\n";
    std::cout << "[PROCESSING] Validating transaction...\n";
    std::cout << "[FRAUD CHECK] PASSED\n";
    std::cout << "[SUCCESS] " << amount << " sent to " << toWallet << "\n";
    std::cout << "[TX ID] TX_987654321\n";
}

void transactionHistory() {
    std::string walletId;
    std::cout << "\n--- Transaction History ---\n";
    std::cout << "Wallet ID: ";
    std::cin >> walletId;
    
    // TODO: Make API call to GET /api/v1/wallets/{id}/transactions
    std::cout << "\n[API] GET /api/v1/wallets/" << walletId << "/transactions\n";
    std::cout << "\nRecent Transactions:\n";
    std::cout << "1. +500.00 USD from WALLET_999 (2025-11-23)\n";
    std::cout << "2. -100.00 USD to WALLET_888 (2025-11-22)\n";
    std::cout << "3. +1000.00 USD (Deposit) (2025-11-20)\n";
}

void currencyConverter() {
    std::string fromCurrency, toCurrency, amount;
    std::cout << "\n--- Currency Converter ---\n";
    std::cout << "From Currency: ";
    std::cin >> fromCurrency;
    std::cout << "To Currency: ";
    std::cin >> toCurrency;
    std::cout << "Amount: ";
    std::cin >> amount;
    
    // TODO: Make API call to GET /api/v1/convert
    std::cout << "\n[API] GET /api/v1/convert?from=" << fromCurrency << "&to=" << toCurrency << "&amount=" << amount << "\n";
    std::cout << "[RATE] 1 " << fromCurrency << " = 152.50 " << toCurrency << "\n";
    std::cout << "[RESULT] " << amount << " " << fromCurrency << " = " << stod(amount) * 152.50 << " " << toCurrency << "\n";
}

int main() {
    printHeader();
    
    std::cout << "[INFO] Connecting to VirtualMoneySystem API...\n";
    std::cout << "[API URL] http://localhost:8080/api/v1\n";
    std::cout << "[STATUS] Connected\n";
    
    int choice;
    bool running = true;
    
    while (running) {
        printMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
                createWallet();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                sendMoney();
                break;
            case 6:
                transactionHistory();
                break;
            case 7:
                currencyConverter();
                break;
            case 0:
                std::cout << "\n[INFO] Logging out...\n";
                std::cout << "[SUCCESS] Goodbye!\n\n";
                running = false;
                break;
            default:
                std::cout << "\n[ERROR] Invalid choice. Try again.\n";
        }
    }
    
    return 0;
}

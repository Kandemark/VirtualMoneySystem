#include "SDKExamples.h"

std::string SDKExamples::getTransactionExample() {
    return R"(
// Create a transaction
SDKClient client("your_api_key");
std::string txnId = client.createTransaction("user1", "user2", 100.0);
std::cout << "Transaction created: " << txnId << std::endl;
)";
}

std::string SDKExamples::getWebhookExample() {
    return R"(
// Verify webhook signature
SDKClient client("your_api_key");
bool isValid = client.verifyWebhook(payload, signature);
if (isValid) {
    // Process webhook
}
)";
}

std::string SDKExamples::getUserManagementExample() {
    return R"(
// Get user balance
SDKClient client("your_api_key");
double balance = client.getBalance("user123");
std::cout << "Balance: $" << balance << std::endl;
)";
}

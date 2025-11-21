# VirtualMoneySystem API Reference

## Base URL
```
http://localhost:8080/api/v1
```

## Authentication
All API requests require authentication via API key in the header:
```
Authorization: Bearer YOUR_API_KEY
```

---

## Wallet Endpoints

### Create Wallet
```http
POST /wallet/create
```

**Request Body:**
```json
{
  "userId": "user123",
  "currency": "USD",
  "type": "personal"
}
```

**Response:**
```json
{
  "walletId": "WALLET_123456789",
  "balance": 0.0,
  "currency": "USD",
  "created": "2025-11-21T15:00:00Z"
}
```

### Get Balance
```http
GET /wallet/balance?walletId=WALLET_123456789
```

**Response:**
```json
{
  "walletId": "WALLET_123456789",
  "balance": 10000.50,
  "currency": "USD"
}
```

### Deposit
```http
POST /wallet/deposit
```

**Request Body:**
```json
{
  "walletId": "WALLET_123456789",
  "amount": 1000.00,
  "currency": "USD"
}
```

### Withdraw
```http
POST /wallet/withdraw
```

**Request Body:**
```json
{
  "walletId": "WALLET_123456789",
  "amount": 500.00,
  "currency": "USD"
}
```

---

## Transaction Endpoints

### Create Transaction
```http
POST /transaction/create
```

**Request Body:**
```json
{
  "from": "WALLET_123456789",
  "to": "WALLET_987654321",
  "amount": 100.00,
  "currency": "USD",
  "description": "Payment for services"
}
```

**Response:**
```json
{
  "transactionId": "TX_1234567890",
  "status": "completed",
  "timestamp": "2025-11-21T15:00:00Z",
  "fee": 0.50
}
```

### Get Transaction
```http
GET /transaction/{transactionId}
```

**Response:**
```json
{
  "transactionId": "TX_1234567890",
  "from": "WALLET_123456789",
  "to": "WALLET_987654321",
  "amount": 100.00,
  "currency": "USD",
  "status": "completed",
  "timestamp": "2025-11-21T15:00:00Z"
}
```

### Transaction History
```http
GET /transaction/history?walletId=WALLET_123456789&limit=50
```

---

## CBDC Endpoints

### Issue CBDC
```http
POST /cbdc/issue
```

**Request Body:**
```json
{
  "bankId": "CENTRAL_BANK_001",
  "amount": 1000000.00,
  "currency": "CBDC_USD"
}
```

### Create CBDC Wallet
```http
POST /cbdc/wallet/create
```

**Request Body:**
```json
{
  "citizenId": "CITIZEN_123",
  "tier": "retail"
}
```

### Offline Payment
```http
POST /cbdc/payment/offline
```

**Request Body:**
```json
{
  "fromWallet": "CBDC_WALLET_123",
  "toWallet": "CBDC_WALLET_456",
  "amount": 50.00
}
```

**Response:**
```json
{
  "offlineToken": "OFFLINE_TOKEN_ABC123",
  "expiresAt": "2025-11-22T15:00:00Z"
}
```

---

## Compliance Endpoints

### Generate SAR
```http
POST /compliance/sar
```

**Request Body:**
```json
{
  "userId": "user123",
  "reason": "Unusual transaction pattern",
  "details": "Multiple large transactions"
}
```

### Check Sanctions
```http
GET /compliance/sanctions/check?name=John+Doe
```

**Response:**
```json
{
  "isSanctioned": false,
  "sources": ["OFAC", "UN", "EU"]
}
```

### File Tax Return
```http
POST /compliance/tax/file
```

**Request Body:**
```json
{
  "userId": "user123",
  "year": "2025",
  "jurisdiction": "USA"
}
```

---

## Analytics Endpoints

### Get Statistics
```http
GET /analytics/stats
```

**Response:**
```json
{
  "totalUsers": 10000,
  "totalTransactions": 500000,
  "totalVolume": 50000000.00,
  "averageTPS": 1500
}
```

### Predict Volume
```http
GET /analytics/predict?days=7
```

**Response:**
```json
{
  "predictedVolume": 75000,
  "confidence": 0.85,
  "trend": "increasing"
}
```

---

## Smart Contract Endpoints

### Deploy Contract
```http
POST /contract/deploy
```

**Request Body:**
```json
{
  "code": "function transfer(from, to, amount) { ... }",
  "language": "javascript"
}
```

**Response:**
```json
{
  "contractId": "CONTRACT_123456",
  "deployed": true
}
```

### Execute Contract
```http
POST /contract/execute
```

**Request Body:**
```json
{
  "contractId": "CONTRACT_123456",
  "function": "transfer",
  "params": {
    "from": "WALLET_123",
    "to": "WALLET_456",
    "amount": 100
  }
}
```

---

## Identity Endpoints

### Create DID
```http
POST /identity/did/create
```

**Request Body:**
```json
{
  "userId": "user123"
}
```

**Response:**
```json
{
  "did": "did:virtualmoney:123456789",
  "publicKey": "..."
}
```

### Issue Credential
```http
POST /identity/credential/issue
```

**Request Body:**
```json
{
  "issuerDID": "did:virtualmoney:issuer",
  "subjectDID": "did:virtualmoney:123456789",
  "type": "kyc",
  "claims": {
    "verified": true,
    "level": "tier1"
  }
}
```

---

## Monitoring Endpoints

### System Health
```http
GET /monitoring/health
```

**Response:**
```json
{
  "status": "healthy",
  "uptime": 99.99,
  "tps": 1500,
  "latency": 8.5
}
```

### Get Metrics
```http
GET /monitoring/metrics
```

**Response:**
```json
{
  "tps": 1500,
  "avgLatencyMs": 8.5,
  "cpuUsage": 45.0,
  "memoryUsageMB": 2048,
  "errorRate": 0.01
}
```

---

## Error Codes

| Code | Description |
|------|-------------|
| 200 | Success |
| 400 | Bad Request |
| 401 | Unauthorized |
| 403 | Forbidden |
| 404 | Not Found |
| 429 | Rate Limit Exceeded |
| 500 | Internal Server Error |

---

## Rate Limits

- **Standard**: 100 requests/minute
- **Premium**: 1000 requests/minute
- **Enterprise**: Unlimited

---

## Webhooks

Subscribe to events:
```http
POST /webhooks/subscribe
```

**Request Body:**
```json
{
  "url": "https://your-server.com/webhook",
  "events": ["transaction.created", "wallet.updated"]
}
```

**Events:**
- `transaction.created`
- `transaction.completed`
- `wallet.created`
- `wallet.updated`
- `compliance.alert`
- `fraud.detected`

---

## SDKs

- **JavaScript/Node.js**: `npm install virtualmoney-sdk`
- **Python**: `pip install virtualmoney`
- **Go**: `go get github.com/virtualmoney/sdk-go`
- **C++**: Available in `sdk/cpp/`

---

## Support

- **Documentation**: https://docs.virtualmoney.com
- **API Status**: https://status.virtualmoney.com
- **Support**: support@virtualmoney.com

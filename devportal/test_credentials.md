# Test Credentials for VirtualMoneySystem

## API Test Accounts

### Admin Account
- **Username**: `admin@virtualmoney.com`
- **Password**: `Admin123!@#`
- **API Key**: `vms_admin_key_1234567890abcdef`
- **Permissions**: Full system access

### Test User 1 (Personal)
- **Username**: `testuser1@example.com`
- **Password**: `Test123!@#`
- **API Key**: `vms_user1_key_abcdef1234567890`
- **Wallet ID**: `WALLET_123456789`
- **Initial Balance**: $10,000 USD

### Test User 2 (Business)
- **Username**: `business@example.com`
- **Password**: `Business123!@#`
- **API Key**: `vms_business_key_fedcba0987654321`
- **Wallet ID**: `WALLET_987654321`
- **Initial Balance**: $50,000 USD

## Test Endpoints

### Base URL
```
http://localhost:8080/api/v1
```

### Authentication
```bash
curl -H "Authorization: Bearer vms_user1_key_abcdef1234567890" \
     http://localhost:8080/api/v1/wallet/balance
```

### Create Transaction
```bash
curl -X POST http://localhost:8080/api/v1/transaction/create \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer vms_user1_key_abcdef1234567890" \
  -d '{
    "from": "WALLET_123456789",
    "to": "WALLET_987654321",
    "amount": 100.00,
    "currency": "USD"
  }'
```

## Test Data

### Sample Transactions
- Small: $10 - $100
- Medium: $100 - $1,000
- Large: $1,000 - $10,000
- Suspicious: >$10,000 (triggers AML)

### Test Currencies
- USD, EUR, GBP, KES, BTC, ETH

### Test Scenarios
1. **Normal Transfer**: $100 USD between test accounts
2. **Large Transfer**: $15,000 USD (triggers CTR)
3. **Suspicious Pattern**: 10+ transactions in 1 minute
4. **Cross-Currency**: USD to EUR conversion
5. **CBDC Payment**: Offline payment simulation

## Security Notes
⚠️ **These are TEST credentials only**
- Do NOT use in production
- Reset passwords after testing
- Rotate API keys regularly
- Monitor for unauthorized access

## Support
For issues: support@virtualmoney.com

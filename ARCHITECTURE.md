# VirtualMoneySystem - Architecture

## System Overview

```
┌─────────────────────────────────────────────────┐
│         VirtualMoneySystem (Backend)            │
│                                                 │
│  ┌──────────────────────────────────────────┐  │
│  │         REST API Server                  │  │
│  │      (Port 8080-20000)                   │  │
│  │                                          │  │
│  │  Endpoints:                              │  │
│  │  - POST /api/v1/users/signup             │  │
│  │  - POST /api/v1/auth/login               │  │
│  │  - POST /api/v1/wallets                  │  │
│  │  - GET  /api/v1/wallets/{id}/balance     │  │
│  │  - POST /api/v1/transactions             │  │
│  │  - GET  /api/v1/wallets/{id}/transactions│  │
│  │  - GET  /api/v1/convert                  │  │
│  └──────────────────────────────────────────┘  │
│                                                 │
│  Features:                                      │
│  - Multi-user wallets                           │
│  - Transaction processing                       │
│  - Currency conversion                          │
│  - Fraud detection                              │
│  - Compliance (KYC/AML)                         │
│  - Database (SQLite)                            │
└─────────────────────────────────────────────────┘
                      ▲
                      │ HTTP REST API
                      │
        ┌─────────────┼─────────────┐
        │             │             │
        ▼             ▼             ▼
   ┌────────┐   ┌─────────┐   ┌─────────┐
   │  CLI   │   │ Desktop │   │   Web   │
   │ Client │   │   App   │   │   App   │
   └────────┘   └─────────┘   └─────────┘
```

## Components

### Backend (VirtualMoneySystem.exe)
- **Files**: 651 (323 .cpp + 328 .h)
- **Port**: Random (10000-20000 range)
- **Database**: vms.db (SQLite)
- **API**: REST (JSON)

### Clients (Connect via API)

#### 1. CLI Client (VirtualMoneyCLI.exe) ✅ CREATED
- Command-line interface
- Menu-driven operations
- Direct API calls
- Lightweight & fast

#### 2. Desktop App (Future)
- GUI application
- Windows/Mac/Linux
- Real-time updates
- Rich user experience

#### 3. Web App (Future)
- Browser-based
- Progressive Web App
- Mobile responsive
- Cloud deployable

## Usage

### 1. Start Backend
```bash
.\VirtualMoneySystem.exe
```

### 2. Use CLI Client
```bash
.\VirtualMoneyCLI.exe
```

### 3. Operations Available
- Sign Up
- Login
- Create Wallet
- Check Balance
- Send Money
- View Transaction History
- Currency Conversion

## API Communication

All clients communicate with the backend via HTTP:
```
Client → HTTP Request → Backend API → Process → Database
                                    ↓
Client ← HTTP Response ← Backend API ← Result
```

## Security
- JWT authentication
- AES-256 encryption
- Device validation
- Session management
- Fraud detection

## Scalability
- Multi-client support
- Concurrent connections
- Load balancing ready
- Distributed architecture

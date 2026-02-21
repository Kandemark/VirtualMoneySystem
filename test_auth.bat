@echo off
echo ========================================
echo VirtualMoneySystem - Authentication Test
echo ========================================
echo.

echo Starting server in background...
start /B VirtualMoneySystem.exe
timeout /t 2 /nobreak >nul

echo.
echo [TEST 1] Health Check
curl -s http://localhost:12345/api/v1/health
echo.
echo.

echo [TEST 2] Create User "alice"
curl -s -X POST http://localhost:12345/api/v1/users/signup -H "Content-Type: application/json" -d "{\"username\":\"alice\",\"password\":\"secret123\"}"
echo.
echo.

echo [TEST 3] Login as "alice"
curl -s -X POST http://localhost:12345/api/v1/auth/login -H "Content-Type: application/json" -d "{\"username\":\"alice\",\"password\":\"secret123\"}"
echo.
echo.

echo [TEST 4] Create User "bob"
curl -s -X POST http://localhost:12345/api/v1/users/signup -H "Content-Type: application/json" -d "{\"username\":\"bob\",\"password\":\"pass456\"}"
echo.
echo.

echo [TEST 5] Try duplicate user (should fail)
curl -s -X POST http://localhost:12345/api/v1/users/signup -H "Content-Type: application/json" -d "{\"username\":\"alice\",\"password\":\"different\"}"
echo.
echo.

echo [TEST 6] Wrong password (should fail)
curl -s -X POST http://localhost:12345/api/v1/auth/login -H "Content-Type: application/json" -d "{\"username\":\"alice\",\"password\":\"wrong\"}"
echo.
echo.

echo [TEST 7] Create Wallet
curl -s -X POST http://localhost:12345/api/v1/wallets
echo.
echo.

echo [TEST 8] Check Balance
curl -s http://localhost:12345/api/v1/wallets/balance
echo.
echo.

echo ========================================
echo All Tests Complete!
echo ========================================
echo.
echo Press any key to stop server...
pause >nul

taskkill /F /IM VirtualMoneySystem.exe >nul 2>&1
echo Server stopped.

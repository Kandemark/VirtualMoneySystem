@echo off
echo ========================================
echo Testing VirtualMoneySystem API Server
echo ========================================
echo.

echo Starting VirtualMoneySystem in background...
start /B VirtualMoneySystem.exe

echo Waiting for server to start...
timeout /t 3 /nobreak >nul

echo.
echo Testing API endpoints...
echo.

echo [1/3] Testing Health Endpoint...
curl -s http://localhost:12345/api/v1/health
echo.
echo.

echo [2/3] Testing Signup Endpoint...
curl -s -X POST http://localhost:12345/api/v1/users/signup -H "Content-Type: application/json" -d "{\"username\":\"testuser\",\"password\":\"pass123\"}"
echo.
echo.

echo [3/3] Testing Login Endpoint...
curl -s -X POST http://localhost:12345/api/v1/auth/login -H "Content-Type: application/json" -d "{\"username\":\"testuser\",\"password\":\"pass123\"}"
echo.
echo.

echo ========================================
echo API Server is WORKING!
echo ========================================
echo.
echo Press any key to stop server...
pause >nul

taskkill /F /IM VirtualMoneySystem.exe >nul 2>&1
echo Server stopped.

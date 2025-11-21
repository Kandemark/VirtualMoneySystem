# VirtualMoneySystem - Comprehensive Verification Script

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "VirtualMoneySystem - Verification Suite" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

$ErrorCount = 0
$WarningCount = 0
$PassCount = 0

# Test 1: Check directory structure
Write-Host "[TEST 1] Verifying Directory Structure..." -ForegroundColor Yellow

$RequiredDirs = @(
    "api", "audit", "backups", "blockchain", "bootstrap", "cache",
    "cbdc", "compliance", "core", "database", "distributed", "enterprise",
    "gpu", "infrastructure", "ml", "monitoring", "realtime", "resilience",
    "scheduler", "security", "sdk", "social", "trading", "treasury"
)

foreach ($dir in $RequiredDirs) {
    if (Test-Path $dir) {
        Write-Host "  OK $dir" -ForegroundColor Green
        $PassCount++
    } else {
        Write-Host "  FAIL $dir missing" -ForegroundColor Red
        $ErrorCount++
    }
}

Write-Host ""

# Test 2: Check enhancement files
Write-Host "[TEST 2] Verifying Enhancement Files..." -ForegroundColor Yellow

$EnhancementFiles = @(
    "monitoring/HealthCheck.cpp",
    "monitoring/RequestTracker.cpp",
    "cache/RedisCache.cpp",
    "realtime/WebSocketServer.cpp",
    "resilience/CircuitBreaker.cpp",
    "api/GraphQLServer.cpp",
    "enterprise/MultiTenancy.cpp",
    "ml/MLAnalytics.cpp",
    "ml/DeepFraudDetector.cpp",
    "security/BiometricAuth.cpp",
    "sdk/mobile/MobileSDK.cpp",
    "blockchain/MultiChainBridge.cpp",
    "trading/AlgoTradingEngine.cpp",
    "social/SocialTradingPlatform.cpp"
)

foreach ($file in $EnhancementFiles) {
    if (Test-Path $file) {
        $size = (Get-Item $file).Length
        if ($size -gt 100) {
            Write-Host "  OK $file" -ForegroundColor Green
            $PassCount++
        } else {
            Write-Host "  WARN $file too small" -ForegroundColor Yellow
            $WarningCount++
        }
    } else {
        Write-Host "  FAIL $file missing" -ForegroundColor Red
        $ErrorCount++
    }
}

Write-Host ""

# Test 3: Check CMakeLists.txt
Write-Host "[TEST 3] Verifying CMakeLists.txt..." -ForegroundColor Yellow

if (Test-Path "CMakeLists.txt") {
    $content = Get-Content "CMakeLists.txt" -Raw
    
    if ($content -match "mobile_lib") {
        Write-Host "  OK mobile_lib found" -ForegroundColor Green
        $PassCount++
    } else {
        Write-Host "  FAIL mobile_lib not found" -ForegroundColor Red
        $ErrorCount++
    }
    
    if ($content -match "sdk/mobile/MobileSDK.cpp") {
        Write-Host "  OK correct mobile SDK path" -ForegroundColor Green
        $PassCount++
    } else {
        Write-Host "  FAIL incorrect mobile SDK path" -ForegroundColor Red
        $ErrorCount++
    }
} else {
    Write-Host "  FAIL CMakeLists.txt not found" -ForegroundColor Red
    $ErrorCount++
}

Write-Host ""

# Test 4: File count
Write-Host "[TEST 4] File Statistics..." -ForegroundColor Yellow

$cppFiles = (Get-ChildItem -Recurse -Filter "*.cpp" -File | Where-Object { $_.FullName -notmatch "build" }).Count
$hFiles = (Get-ChildItem -Recurse -Filter "*.h" -File | Where-Object { $_.FullName -notmatch "build" }).Count
$totalFiles = $cppFiles + $hFiles

Write-Host "  CPP files: $cppFiles" -ForegroundColor Cyan
Write-Host "  Header files: $hFiles" -ForegroundColor Cyan
Write-Host "  Total: $totalFiles" -ForegroundColor Cyan

if ($totalFiles -ge 110) {
    Write-Host "  OK File count meets target" -ForegroundColor Green
    $PassCount++
} else {
    Write-Host "  WARN File count below 110" -ForegroundColor Yellow
    $WarningCount++
}

Write-Host ""

# Final Summary
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "VERIFICATION SUMMARY" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Passed:  $PassCount" -ForegroundColor Green
Write-Host "Warnings: $WarningCount" -ForegroundColor Yellow
Write-Host "Errors:   $ErrorCount" -ForegroundColor Red
Write-Host "========================================" -ForegroundColor Cyan

if ($ErrorCount -eq 0) {
    Write-Host "SUCCESS - All tests passed!" -ForegroundColor Green
    exit 0
} else {
    Write-Host "FAILED - $ErrorCount errors found" -ForegroundColor Red
    exit 1
}

/**
 * @file AssetMarketEngine.h
 * @brief Multi-asset market abstraction with risk/liquidity spreads
 */

#ifndef ASSET_MARKET_ENGINE_H
#define ASSET_MARKET_ENGINE_H

#include <algorithm>
#include <string>
#include <unordered_map>

class AssetMarketEngine {
public:
    enum class AssetClass {
        Forex,
        Equity,
        Bond,
        Commodity,
        Crypto,
        MoneyMarketFund,
        TreasuryBill
    };

    struct Quote {
        std::string symbol;
        AssetClass assetClass = AssetClass::Forex;
        double bid = 0.0;
        double ask = 0.0;
        double mid = 0.0;
        double spreadBps = 0.0;
        bool tradable = false;
        std::string note;
    };

    AssetMarketEngine() {
        setBasePrice("USDKES", 129.25, AssetClass::Forex);
        setBasePrice("EURUSD", 1.09, AssetClass::Forex);
        setBasePrice("AAPL", 190.0, AssetClass::Equity);
        setBasePrice("GOLD", 2025.0, AssetClass::Commodity);
        setBasePrice("BTCUSD", 62000.0, AssetClass::Crypto);
        setBasePrice("TBILL91D", 0.12, AssetClass::TreasuryBill);
    }

    void setBasePrice(const std::string& symbol, double price, AssetClass cls) {
        if (price <= 0) return;
        basePrices[symbol] = price;
        classes[symbol] = cls;
    }

    Quote getQuote(const std::string& symbol, bool lowLiquidity, bool sanctionsSensitive) const {
        Quote q;
        q.symbol = symbol;
        auto it = basePrices.find(symbol);
        if (it == basePrices.end()) {
            q.note = "unknown_symbol";
            return q;
        }

        q.assetClass = classes.at(symbol);
        const double base = it->second;

        double spreadBps = 12.0;
        if (q.assetClass == AssetClass::Crypto) spreadBps = 35.0;
        if (q.assetClass == AssetClass::Equity) spreadBps = 20.0;
        if (q.assetClass == AssetClass::TreasuryBill) spreadBps = 5.0;

        if (lowLiquidity) spreadBps *= 2.2;
        if (sanctionsSensitive) spreadBps *= 1.5;

        const double spread = base * (spreadBps / 10000.0);
        q.mid = base;
        q.bid = std::max(0.0, base - spread / 2.0);
        q.ask = base + spread / 2.0;
        q.spreadBps = spreadBps;
        q.tradable = !(sanctionsSensitive && q.assetClass == AssetClass::Crypto);
        q.note = q.tradable ? "ok" : "restricted_by_policy";
        return q;
    }

private:
    std::unordered_map<std::string, double> basePrices;
    std::unordered_map<std::string, AssetClass> classes;
};

#endif

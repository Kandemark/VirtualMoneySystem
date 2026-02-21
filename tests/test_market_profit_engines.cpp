#include "../compliance/AssetMarketEngine.h"
#include "../compliance/ProfitOptimizationEngine.h"
#include <cassert>
#include <iostream>

int main() {
    AssetMarketEngine market;

    auto fx = market.getQuote("USDKES", false, false);
    assert(fx.tradable);
    assert(fx.ask > fx.bid);

    auto cryptoRestricted = market.getQuote("BTCUSD", true, true);
    assert(!cryptoRestricted.tradable);
    assert(cryptoRestricted.spreadBps > fx.spreadBps);

    ProfitOptimizationEngine pe;
    ProfitOptimizationEngine::CostProfile cp;
    cp.infraCostPerTx = 0.01;
    cp.complianceCostPerTx = 0.007;
    cp.fraudReserveRate = 0.002;

    auto plan = pe.optimize(2'000'000.0, 12000, cp, true, false);
    assert(plan.recommendedFeeRate >= 0.0025);
    assert(plan.expectedGrossRevenue > 0.0);
    assert(!plan.controls.empty());

    auto publicPlan = pe.optimize(2'000'000.0, 12000, cp, false, true);
    assert(publicPlan.recommendedFeeRate <= plan.recommendedFeeRate);

    std::cout << "Market and profit engine tests passed!" << std::endl;
    return 0;
}

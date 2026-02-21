/**
 * @file ProfitOptimizationEngine.h
 * @brief Revenue and sustainability optimizer for fee/profit strategy
 */

#ifndef PROFIT_OPTIMIZATION_ENGINE_H
#define PROFIT_OPTIMIZATION_ENGINE_H

#include <algorithm>
#include <string>
#include <vector>

class ProfitOptimizationEngine {
public:
    struct CostProfile {
        double infraCostPerTx = 0.01;
        double complianceCostPerTx = 0.005;
        double fraudReserveRate = 0.001;   // 0.1%
        double thirdPartyRate = 0.0;       // pass-through rate
    };

    struct ProfitPlan {
        double recommendedFeeRate = 0.0;   // decimal
        double expectedGrossRevenue = 0.0;
        double expectedCost = 0.0;
        double expectedNetProfit = 0.0;
        double netMargin = 0.0;
        std::vector<std::string> controls;
    };

    ProfitPlan optimize(double monthlyVolume,
                        int txCount,
                        const CostProfile& costs,
                        bool highRisk,
                        bool publicSectorMode) const {
        ProfitPlan p;
        if (monthlyVolume <= 0 || txCount <= 0) {
            p.controls.push_back("invalid_inputs");
            return p;
        }

        double baseFee = 0.006; // 0.6%
        if (highRisk) baseFee += 0.002;
        if (publicSectorMode) baseFee = std::max(0.0025, baseFee - 0.0015);

        // Speed + sustainability clamp.
        p.recommendedFeeRate = std::clamp(baseFee, 0.0025, 0.015);

        p.expectedGrossRevenue = monthlyVolume * p.recommendedFeeRate;
        p.expectedCost = txCount * (costs.infraCostPerTx + costs.complianceCostPerTx)
                       + monthlyVolume * (costs.fraudReserveRate + costs.thirdPartyRate);
        p.expectedNetProfit = p.expectedGrossRevenue - p.expectedCost;
        p.netMargin = p.expectedGrossRevenue > 0 ? (p.expectedNetProfit / p.expectedGrossRevenue) : 0.0;

        if (highRisk) p.controls.push_back("dynamic_fee_buffer");
        if (publicSectorMode) p.controls.push_back("public_service_pricing_cap");
        if (p.netMargin < 0.10) p.controls.push_back("cost_reduction_or_volume_growth_needed");
        if (p.netMargin > 0.60) p.controls.push_back("pricing_fairness_review");
        p.controls.push_back("privacy_preserving_analytics_only");

        return p;
    }
};

#endif

/**
 * @file SystemGovernanceEngine.h
 * @brief Unified policy engine for economic scenarios, compliance, privacy, and accountability
 */

#ifndef SYSTEM_GOVERNANCE_ENGINE_H
#define SYSTEM_GOVERNANCE_ENGINE_H

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class SystemGovernanceEngine {
public:
    enum class ActorType {
        Individual,
        Organization,
        Corporation,
        Sacco,
        Government,
        ThirdPartyProvider
    };

    enum class JurisdictionScope {
        Local,
        National,
        International
    };

    enum class OperatingCondition {
        Normal,
        LowLiquidity,
        HighVolatility,
        Emergency
    };

    struct EntityProfile {
        std::string entityId;
        ActorType actorType = ActorType::Individual;
        std::string countryCode;       // ISO-like (e.g. KE, US)
        JurisdictionScope scope = JurisdictionScope::National;
        bool kycCompleted = false;
        bool amlCleared = false;
        bool pepFlag = false;
        bool regulatorWhitelisted = false;
    };

    struct TransactionContext {
        std::string transactionId;
        std::string currency;
        double amount = 0.0;
        std::string purpose;
        OperatingCondition condition = OperatingCondition::Normal;
        bool crossBorder = false;
        std::optional<std::string> thirdPartyId;
    };

    struct Decision {
        bool allowed = false;
        int riskScore = 100;
        std::vector<std::string> reasons;
        std::vector<std::string> requiredControls;
        std::string privacyPolicy;
        std::string accountabilityTag;
    };

    struct ThirdPartyProfile {
        std::string providerId;
        bool securityCertified = false;
        bool dataProcessingAgreement = false;
        bool sanctionsScreeningEnabled = false;
        int historicalIncidents = 0;
    };

    void registerThirdParty(const ThirdPartyProfile& profile) {
        thirdParties[profile.providerId] = profile;
    }

    void markSanctionedCountry(const std::string& countryCode) {
        sanctionedCountries.insert(normalize(countryCode));
    }

    void markSanctionedEntity(const std::string& entityId) {
        sanctionedEntities.insert(entityId);
    }

    Decision evaluate(const EntityProfile& actor, const TransactionContext& tx) {
        const std::string cacheKey = actor.entityId + "|" + normalize(actor.countryCode) + "|" + tx.currency + "|" + std::to_string(static_cast<int>(actor.actorType)) + "|" + std::to_string(static_cast<int>(tx.condition)) + "|" + (actor.kycCompleted ? "1" : "0") + "|" + (actor.amlCleared ? "1" : "0") + "|" + (actor.pepFlag ? "1" : "0") + "|" + (actor.regulatorWhitelisted ? "1" : "0") + "|" + (tx.crossBorder ? "1" : "0") + "|" + (tx.thirdPartyId.has_value() ? *tx.thirdPartyId : "none");
        auto it = decisionCache.find(cacheKey);
        if (it != decisionCache.end() && tx.amount <= 10000.0) {
            // Fast path for common low/medium-value patterns.
            Decision cached = it->second;
            cached.accountabilityTag = generateAccountabilityTag(actor, tx, cached.riskScore);
            return cached;
        }

        Decision out;
        out.allowed = true;
        out.riskScore = 10;

        if (actor.entityId.empty() || tx.transactionId.empty() || tx.amount <= 0.0) {
            out.allowed = false;
            out.riskScore = 100;
            out.reasons.push_back("invalid_input_context");
            out.requiredControls.push_back("reject_and_alert_ops");
            finalizePolicies(actor, tx, out);
            return out;
        }

        if (sanctionedEntities.count(actor.entityId) > 0 || sanctionedCountries.count(normalize(actor.countryCode)) > 0) {
            out.allowed = false;
            out.riskScore = 100;
            out.reasons.push_back("sanctions_block");
            out.requiredControls.push_back("freeze_and_regulatory_report");
        }

        if (!actor.kycCompleted) {
            out.allowed = false;
            out.riskScore = std::max(out.riskScore, 90);
            out.reasons.push_back("kyc_missing");
            out.requiredControls.push_back("complete_kyc");
        }

        if (!actor.amlCleared) {
            out.allowed = false;
            out.riskScore = std::max(out.riskScore, 92);
            out.reasons.push_back("aml_not_cleared");
            out.requiredControls.push_back("aml_review");
        }

        if (actor.pepFlag) {
            out.riskScore = std::max(out.riskScore, 75);
            out.reasons.push_back("pep_enhanced_due_diligence");
            out.requiredControls.push_back("senior_compliance_approval");
        }

        if (tx.crossBorder || actor.scope == JurisdictionScope::International) {
            out.riskScore = std::max(out.riskScore, 60);
            out.reasons.push_back("cross_border_controls");
            out.requiredControls.push_back("cross_border_screening");
        }

        if (tx.condition == OperatingCondition::LowLiquidity || tx.condition == OperatingCondition::HighVolatility) {
            out.riskScore = std::max(out.riskScore, 55);
            out.reasons.push_back("market_stress_controls");
            out.requiredControls.push_back("dynamic_limiting_and_queueing");
        }

        if (tx.condition == OperatingCondition::Emergency && !actor.regulatorWhitelisted) {
            out.riskScore = std::max(out.riskScore, 80);
            out.reasons.push_back("emergency_mode_restrictions");
            out.requiredControls.push_back("manual_release_protocol");
        }

        applyActorSpecificRules(actor, tx, out);
        applyThirdPartyRules(tx, out);
        applyAmountTiers(tx, out);

        if (out.riskScore >= 95) {
            out.allowed = false;
        }

        finalizePolicies(actor, tx, out);
        if (tx.amount <= 10000.0) {
            decisionCache[cacheKey] = out;
        }
        return out;
    }

    std::string maskSensitive(const std::string& value) const {
        if (value.size() <= 4) return "****";
        return std::string(value.size() - 4, '*') + value.substr(value.size() - 4);
    }

private:
    std::unordered_map<std::string, ThirdPartyProfile> thirdParties;
    std::unordered_set<std::string> sanctionedCountries;
    std::unordered_set<std::string> sanctionedEntities;
    std::unordered_map<std::string, Decision> decisionCache;

    static std::string normalize(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
        return s;
    }

    static void applyActorSpecificRules(const EntityProfile& actor, const TransactionContext& tx, Decision& out) {
        switch (actor.actorType) {
            case ActorType::Individual:
                if (tx.amount > 50000.0) {
                    out.riskScore = std::max(out.riskScore, 70);
                    out.requiredControls.push_back("source_of_funds_check");
                }
                break;
            case ActorType::Organization:
            case ActorType::Corporation:
                out.requiredControls.push_back("beneficial_ownership_verification");
                if (tx.amount > 250000.0) {
                    out.riskScore = std::max(out.riskScore, 82);
                    out.requiredControls.push_back("dual_authorization");
                }
                break;
            case ActorType::Sacco:
                out.requiredControls.push_back("member_ledger_reconciliation");
                break;
            case ActorType::Government:
                out.requiredControls.push_back("public_funds_traceability");
                if (!actor.regulatorWhitelisted) {
                    out.riskScore = std::max(out.riskScore, 65);
                    out.reasons.push_back("government_entity_missing_regulator_whitelist");
                }
                break;
            case ActorType::ThirdPartyProvider:
                out.requiredControls.push_back("third_party_assurance");
                out.riskScore = std::max(out.riskScore, 65);
                break;
        }
    }

    void applyThirdPartyRules(const TransactionContext& tx, Decision& out) const {
        if (!tx.thirdPartyId.has_value()) return;

        auto it = thirdParties.find(*tx.thirdPartyId);
        if (it == thirdParties.end()) {
            out.riskScore = std::max(out.riskScore, 88);
            out.reasons.push_back("unknown_third_party");
            out.requiredControls.push_back("vendor_due_diligence");
            return;
        }

        const ThirdPartyProfile& p = it->second;
        if (!p.securityCertified) {
            out.riskScore = std::max(out.riskScore, 85);
            out.reasons.push_back("third_party_not_security_certified");
            out.requiredControls.push_back("block_until_security_attestation");
        }
        if (!p.dataProcessingAgreement) {
            out.riskScore = std::max(out.riskScore, 87);
            out.reasons.push_back("missing_dpa");
            out.requiredControls.push_back("privacy_legal_approval");
        }
        if (!p.sanctionsScreeningEnabled) {
            out.riskScore = std::max(out.riskScore, 80);
            out.reasons.push_back("third_party_sanctions_blindspot");
            out.requiredControls.push_back("proxy_screening_enforcement");
        }
        if (p.historicalIncidents > 3) {
            out.riskScore = std::max(out.riskScore, 90);
            out.reasons.push_back("high_incident_third_party");
            out.requiredControls.push_back("continuous_monitoring");
        }
    }

    static void applyAmountTiers(const TransactionContext& tx, Decision& out) {
        if (tx.amount > 1000000.0) {
            out.riskScore = std::max(out.riskScore, 93);
            out.requiredControls.push_back("executive_and_compliance_approval");
            out.reasons.push_back("very_large_transaction");
        } else if (tx.amount > 100000.0) {
            out.riskScore = std::max(out.riskScore, 78);
            out.requiredControls.push_back("enhanced_transaction_monitoring");
        }
    }

    static std::string generateAccountabilityTag(const EntityProfile& actor,
                                                 const TransactionContext& tx,
                                                 int riskScore) {
        std::stringstream ss;
        ss << "audit:" << actor.entityId << ':' << tx.transactionId << ':' << riskScore;
        const std::uint64_t h = std::hash<std::string>{}(ss.str());
        std::stringstream hex;
        hex << "acct_" << std::hex << std::setw(16) << std::setfill('0') << h;
        return hex.str();
    }

    static void finalizePolicies(const EntityProfile& actor,
                                 const TransactionContext& tx,
                                 Decision& out) {
        (void)actor;
        out.privacyPolicy = tx.thirdPartyId.has_value()
            ? "strict_data_minimization+tokenization+third_party_dpa_required"
            : "strict_data_minimization+tokenization";

        if (out.riskScore >= 80) {
            out.requiredControls.push_back("full_audit_trail_immutable_logging");
        }

        out.accountabilityTag = generateAccountabilityTag(actor, tx, out.riskScore);
    }
};

#endif // SYSTEM_GOVERNANCE_ENGINE_H

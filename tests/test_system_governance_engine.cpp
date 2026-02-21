#include "../compliance/SystemGovernanceEngine.h"
#include <cassert>
#include <iostream>

int main() {
    SystemGovernanceEngine engine;

    SystemGovernanceEngine::ThirdPartyProfile trusted;
    trusted.providerId = "trusted_gateway";
    trusted.securityCertified = true;
    trusted.dataProcessingAgreement = true;
    trusted.sanctionsScreeningEnabled = true;
    trusted.historicalIncidents = 0;
    engine.registerThirdParty(trusted);

    engine.markSanctionedCountry("KP");
    engine.markSanctionedEntity("blocked_entity");

    SystemGovernanceEngine::EntityProfile individual;
    individual.entityId = "user_1";
    individual.actorType = SystemGovernanceEngine::ActorType::Individual;
    individual.countryCode = "KE";
    individual.kycCompleted = true;
    individual.amlCleared = true;

    SystemGovernanceEngine::TransactionContext tx;
    tx.transactionId = "tx_1";
    tx.currency = "USD";
    tx.amount = 1200.0;
    tx.thirdPartyId = "trusted_gateway";

    auto d1 = engine.evaluate(individual, tx);
    assert(d1.allowed);
    assert(d1.riskScore < 90);
    assert(!d1.accountabilityTag.empty());

    auto masked = engine.maskSensitive("1234567890");
    assert(masked.size() == 10);
    assert(masked.substr(masked.size() - 4) == "7890");

    SystemGovernanceEngine::EntityProfile sanctioned = individual;
    sanctioned.entityId = "blocked_entity";
    auto d2 = engine.evaluate(sanctioned, tx);
    assert(!d2.allowed);
    assert(d2.riskScore >= 95);

    SystemGovernanceEngine::EntityProfile sanctionedCountry = individual;
    sanctionedCountry.countryCode = "KP";
    auto d3 = engine.evaluate(sanctionedCountry, tx);
    assert(!d3.allowed);

    SystemGovernanceEngine::EntityProfile gov = individual;
    gov.actorType = SystemGovernanceEngine::ActorType::Government;
    auto d4 = engine.evaluate(gov, tx);
    assert(!d4.requiredControls.empty());

    std::cout << "System governance engine tests passed!" << std::endl;
    return 0;
}

#include "../contracts/RuleDSLParser.h"
#include "../contracts/ContractEngine.h"
#include "../contracts/SmartFXRules.h"
#include "../contracts/EscrowAccount.h"
#include "../compliance/TaxEngine.h"
#include "../compliance/GeoPolicyEngine.h"
#include "../compliance/IDVerificationService.h"
#include "../compliance/WatchlistScanner.h"
#include "../compliance/RiskFlagger.h"
#include "../disputes/DisputeEngine.h"
#include "../disputes/CaseManager.h"
#include "../export/CSVExporter.h"
#include "../export/PDFGenerator.h"
#include "../gateway/OfflineCommandQueue.h"
#include "../integrations/BankAPIConnector.h"
#include "../integrations/MpesaLinkAdapter.h"
#include "../integrations/SMSAdapter.h"
#include "../plugins/LoyaltyPointsPlugin.h"
#include "../plugins/Marketplace/InsurancePlugin.h"
#include "../platform_clients/SessionSyncService.h"
#include "../policy_matrix/FeatureAccessMatrix.h"
#include "../history/APIUsageLog.h"
#include "../localization/LocaleManager.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <stdexcept>

static void testContracts() {
    RuleDSLParser parser;
    auto parsed = parser.parse("limit=1000;currency=USD");
    assert(parsed["limit"] == "1000");
    assert(parser.validate("a=b"));
    assert(!parser.compile("invalid").size());

    ContractEngine engine;
    auto id = engine.deployContract("code", {{"owner", "u1"}});
    assert(!id.empty());
    auto state = engine.getContractState(id);
    assert(state["status"] == "active");

    SmartFXRules fx;
    fx.setThreshold(100.0);
    assert(fx.applyRules("USD", "EUR", 200.0) > 0.0);

    EscrowAccount escrow;
    auto eid = escrow.createEscrow("b", "s", 10.0);
    assert(!eid.empty());
    assert(escrow.releaseFunds(eid));
    assert(escrow.getStatus(eid) == "released");
}

static void testCompliance() {
    TaxEngine tax;
    tax.setTaxRate("VAT", "KE", 0.16);
    assert(tax.calculateTax(100.0, "VAT", "KE") == 16.0);

    GeoPolicyEngine geo;
    geo.setRegionPolicy("KP", "blocked");
    assert(!geo.isAllowedInRegion("u1", "KP"));
    assert(geo.checkSanctions("IR"));

    IDVerificationService ids;
    assert(ids.verifyID("u1", "123456", "NID"));

    WatchlistScanner wl;
    wl.updateWatchlist("bad_user");
    assert(wl.getWatchlistStatus("bad_user") == "MATCH");

    RiskFlagger rf;
    rf.flagRisk("u1", "aml", 9);
    assert(rf.getRiskLevel("u1") == "HIGH");
}

static void testDisputesAndHistory() {
    DisputeEngine de;
    auto did = de.fileDispute("tx1", "fraud");
    assert(!did.empty());
    de.processDispute(did);
    assert(de.getDisputeStatus(did) == "IN_REVIEW");

    CaseManager cm;
    auto cid = cm.createCase(did, "u1");
    assert(!cid.empty());
    cm.assignCase(cid, "agent1");

    APIUsageLog log;
    for (int i = 0; i < 10; ++i) log.logAPICall("/api/v1/health", "u1", 200);
    auto stats = log.getUsageStats("u1");
    assert(stats["/api/v1/health"] == 10);
    assert(log.getRateLimitRemaining("u1") == 990);
}

static void testExportAndGatewayAndIntegrations() {
    CSVExporter csv;
    const std::string csvFile = "/tmp/smoke.csv";
    assert(csv.exportToCSV({{"1", "2"}}, {"a", "b"}, csvFile));
    assert(std::filesystem::exists(csvFile));

    PDFGenerator pdf;
    auto doc = pdf.createDocument("Smoke");
    pdf.addPage(doc);
    pdf.addText(doc, "Hello", 10, 10);
    const std::string pdfFile = "/tmp/smoke.pdf.txt";
    assert(pdf.saveDocument(doc, pdfFile));

    OfflineCommandQueue q;
    q.queueCommand("sync", "u1");
    assert(!q.getPendingCommands().empty());
    q.processQueue();
    assert(q.getPendingCommands().empty());

    BankAPIConnector bank;
    assert(bank.connect("bankA", "12345678"));

    MpesaLinkAdapter mpesa;
    assert(mpesa.initiateSTKPush("254700000000", 10.0));

    SMSAdapter sms;
    sms.setProvider("twilio");
    assert(sms.sendSMS("+254700000000", "hello"));
}

static void testPluginsAndSessionsAndAccessAndLocale() {
    LoyaltyPointsPlugin lp;
    lp.initialize();
    lp.awardPoints("u1", 100, "purchase");
    assert(lp.getPoints("u1") == 100);
    lp.redeemPoints("u1", 60);
    assert(lp.getPoints("u1") == 40);

    InsurancePlugin ip;
    ip.initialize();
    auto pid = ip.purchaseInsurance("u1", "travel");
    assert(!pid.empty());

    SessionSyncService ss;
    ss.syncSession("u1", "sessA");
    assert(ss.isSessionValid("sessA"));
    ss.invalidateSession("sessA");
    assert(!ss.isSessionValid("sessA"));

    FeatureAccessMatrix fam;
    fam.grantAccess("u1", "transfer");
    assert(fam.hasAccess("u1", "transfer"));

    LocaleManager loc;
    loc.setLocale("en_US");
    assert(loc.getLocale() == "en_US");
    assert(loc.formatCurrency(10.5, "USD").find("USD") != std::string::npos);
}

int main() {
    testContracts();
    testCompliance();
    testDisputesAndHistory();
    testExportAndGatewayAndIntegrations();
    testPluginsAndSessionsAndAccessAndLocale();
    std::cout << "Module smoke tests passed!" << std::endl;
    return 0;
}

import FWCore.ParameterSet.Config as cms


htmhtAnalyzerPAT = cms.untracked.PSet(
    doMCHTMHT  = cms.untracked.bool(False),
    
    genJetTag = cms.untracked.InputTag("ak5GenJets"),
    jetTag    = cms.untracked.InputTag("cleanPatJetsAK5Calo"),
    mhtTag    = cms.untracked.InputTag("patMHTsAK5Calo"),

    debugHTMHT  = cms.untracked.int32(0),
    prefixHTMHT = cms.untracked.string("Calo")
)

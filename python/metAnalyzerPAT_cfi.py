import FWCore.ParameterSet.Config as cms


metAnalyzerPAT = cms.untracked.PSet(
    doMCMET   = cms.untracked.bool(False),
    
    genMETTag = cms.untracked.InputTag("genMetCalo"),
    #genMETTag = cms.untracked.InputTag("genMetCaloAndNonPrompt"),
    #genMETTag = cms.untracked.InputTag("genMetTrue"),
    metTag    = cms.untracked.InputTag("patMETsAK5Calo"),

    debugMET  = cms.untracked.int32(0),
    prefixMET = cms.untracked.string("Calo")
)

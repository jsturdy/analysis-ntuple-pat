import FWCore.ParameterSet.Config as cms


triggerAnalyzerPAT = cms.untracked.PSet(
    getL1Info        = cms.untracked.bool(False),
    l1TriggerResults = cms.untracked.InputTag('gtDigis'),
    #l1TriggerResults = cms.untracked.InputTag('hltL1GtObjectMap'),
    getHLTfromConfig = cms.untracked.bool(False),
    hlTriggerResults = cms.untracked.InputTag('TriggerResults','','REDIGI'),
    debugTriggers  = cms.untracked.int32(0)
)

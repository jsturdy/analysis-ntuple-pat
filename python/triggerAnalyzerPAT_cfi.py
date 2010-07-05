import FWCore.ParameterSet.Config as cms


triggerAnalyzerPAT = cms.untracked.PSet(
    l1TriggerResults = cms.untracked.InputTag('gtDigis'),
    #l1TriggerResults = cms.untracked.InputTag('hltL1GtObjectMap'),
    hlTriggerResults = cms.untracked.InputTag('TriggerResults','','HLT'),
    pathNames      = cms.untracked.vstring('HLT_Jet180','HLT_DiJetAve130','HLT_MET60','HLT_HT200','HLT_HT300_MHT100','HLT_Mu9'),
    debugTriggers  = cms.untracked.int32(0)
)

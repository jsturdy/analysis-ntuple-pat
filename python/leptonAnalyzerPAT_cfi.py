import FWCore.ParameterSet.Config as cms


leptonAnalyzerPAT = cms.untracked.PSet(
    elecMaxEta = cms.untracked.double(5.0),
    elecMaxEt  = cms.untracked.double(15.),
    elecMinEt  = cms.untracked.double(2.5),
    elecRelIso = cms.untracked.double(0.5),

    muonMaxEta = cms.untracked.double(5.0),
    muonMaxEt  = cms.untracked.double(10.),
    muonMinEt  = cms.untracked.double(2.5),
    muonRelIso = cms.untracked.double(0.1),
    
    tauMaxEta = cms.untracked.double(5.),
    tauMaxEt  = cms.untracked.double(9999.),
    tauMinEt  = cms.untracked.double(5.),
    tauRelIso = cms.untracked.double(0.1),
    
    debugLeps = cms.untracked.int32(0),
    
    elecTag   = cms.untracked.InputTag("cleanPatElectrons"),
    muonTag   = cms.untracked.InputTag("cleanPatMuons"),
    tauTag    = cms.untracked.InputTag("cleanPatTaus"),
    prefixLeps = cms.untracked.string("")
)
                 

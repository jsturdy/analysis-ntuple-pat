import FWCore.ParameterSet.Config as cms


photonAnalyzerPAT = cms.untracked.PSet(
    photMaxEta = cms.untracked.double(5.0),
    photMaxEt  = cms.untracked.double(10000.),
    photMinEt  = cms.untracked.double(2.5),
    photRelIso = cms.untracked.double(1.5),
    
    debugPhots = cms.untracked.int32(0),
    
    photTag     = cms.untracked.InputTag("cleanPatPhotons"),
    prefixPhots = cms.untracked.string("")
)
                 

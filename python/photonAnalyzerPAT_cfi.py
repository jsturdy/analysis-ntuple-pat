import FWCore.ParameterSet.Config as cms


photonAnalyzerPAT = cms.untracked.PSet(
    photMaxEta = cms.untracked.double(5.),
    photMaxEt  = cms.untracked.double(10000.),
    photMinEt  = cms.untracked.double(5.),
    photRelIso = cms.untracked.double(1.5),
    
    doMCPhots  = cms.untracked.bool(False),
    debugPhots = cms.untracked.int32(0),
    genPhotTag = cms.untracked.InputTag("genParticles"),
    
    photTag     = cms.untracked.InputTag("cleanPatPhotons"),
    prefixPhots = cms.untracked.string("")
)
                 

import FWCore.ParameterSet.Config as cms


mcTruthAnalyzerPAT = cms.untracked.PSet(
    doMCPhots  = cms.untracked.bool(False),
    debugPhots = cms.untracked.int32(0),
    genParticleTag = cms.untracked.InputTag("genParticles"),
)
                 

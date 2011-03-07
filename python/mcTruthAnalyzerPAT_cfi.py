import FWCore.ParameterSet.Config as cms


mcTruthAnalyzerPAT = cms.untracked.PSet(
    debugTruth = cms.untracked.int32(0),
    genParticleTag = cms.untracked.InputTag("genParticles"),
)
                 

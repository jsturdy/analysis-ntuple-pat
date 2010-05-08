import FWCore.ParameterSet.Config as cms


trackAnalyzerPAT = cms.untracked.PSet(
    doMCTracks = cms.untracked.bool(False),
    trackTag   = cms.untracked.InputTag("generalTracks"),
    debugTrack = cms.untracked.int32(0)
    )

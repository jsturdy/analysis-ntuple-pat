import FWCore.ParameterSet.Config as cms


vertexAnalyzerPAT = cms.untracked.PSet(
    minNVtx    = cms.untracked.int32(1),
    minVtxTrks = cms.untracked.int32(3),
    minVtxNdof = cms.untracked.int32(4),
    maxVtxChi2 = cms.untracked.double(999),
    maxVtxZ    = cms.untracked.double(24.),
    maxVtxRho  = cms.untracked.double(2.),

    vtxTag      = cms.untracked.InputTag("offlinePrimaryVertices"),
    beamspotTag = cms.untracked.InputTag("offlineBeamSpot"),
    debugVtx = cms.untracked.int32(0)
    )

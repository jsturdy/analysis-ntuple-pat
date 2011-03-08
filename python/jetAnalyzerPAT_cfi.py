import FWCore.ParameterSet.Config as cms


jetAnalyzerPAT = cms.untracked.PSet(

    jetMaxEta = cms.untracked.double(5.0),
    jetMinPt  = cms.untracked.double(0.),
    jetMaxEMF = cms.untracked.double(0.99),
    jetMinEMF = cms.untracked.double(0.01),

    #htMaxEta = cms.untracked.double(3.0),
    #htMinPt  = cms.untracked.double(20.),

    doMCJets     = cms.untracked.bool(False),
    genJetTag    = cms.untracked.InputTag("ak5GenJets"),

    usePFJets    = cms.untracked.bool(False),
    useJPTJets   = cms.untracked.bool(False),
    useCaloJets  = cms.untracked.bool(False),
    useTrackJets = cms.untracked.bool(False),

    jetTag    = cms.untracked.InputTag("cleanPatJetsAK5"),
    jetCorTag = cms.untracked.string("AK5Calo"),

    #for overlap counting
    electronPt  = cms.untracked.double(30.),
    electronIso = cms.untracked.double(0.1),
    tauPt       = cms.untracked.double(10.),
    tauIso      = cms.untracked.double(0.1),
    muonPt      = cms.untracked.double(10.),
    muonIso     = cms.untracked.double(0.05),
    photonPt    = cms.untracked.double(10.),
    photonIso   = cms.untracked.double(1.5),
    

    debugJets  = cms.untracked.int32(0),
    prefixJets = cms.untracked.string("")

)

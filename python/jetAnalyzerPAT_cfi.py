import FWCore.ParameterSet.Config as cms


jetAnalyzerPAT = cms.untracked.PSet(

    jetMaxEta = cms.untracked.double(5.0),
    jetMinPt  = cms.untracked.double(30.),
    jetMaxEMF = cms.untracked.double(0.99),
    jetMinEMF = cms.untracked.double(0.01),

    #selJetMaxEta = cms.untracked.vdouble(2.5,3.),
    #selJetMinPt  = cms.untracked.vdouble(50.,50.),
    #selJetMaxEMF = cms.untracked.vdouble(0.95,0.95),
    #selJetMinEMF = cms.untracked.vdouble(0.05,0.05),
    doMCJets     = cms.untracked.bool(False),
    genJetTag    = cms.untracked.InputTag("ak5GenJets"),

    usePFJets    = cms.untracked.bool(False),
    useJPTJets   = cms.untracked.bool(False),
    useCaloJets  = cms.untracked.bool(False),
    useTrackJets = cms.untracked.bool(False),

    jptTag    = cms.untracked.InputTag("cleanPatJetsAK5JPT"),
    jetTag    = cms.untracked.InputTag("cleanPatJetsAK5"),
    #pfJetTag     = cms.untracked.InputTag("cleanPatJetsAK5PF"),
    #caloJetTag   = cms.untracked.InputTag("cleanPatJetsAK5"),
    #trackJetTag  = cms.untracked.InputTag("cleanPatJetsAK5Track"),

    #htTag        = cms.InputTag("htTag"),
    #mhtTag       = cms.InputTag("layer1MHTsAK5"),

    debugJets  = cms.untracked.int32(0),
    prefixJets = cms.untracked.string("")

    )

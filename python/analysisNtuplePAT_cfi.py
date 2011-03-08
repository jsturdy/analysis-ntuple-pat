import FWCore.ParameterSet.Config as cms


from JSturdy.AnalysisNtuplePAT.jetAnalyzerPAT_cfi     import jetAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.metAnalyzerPAT_cfi     import metAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.leptonAnalyzerPAT_cfi  import leptonAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.trackAnalyzerPAT_cfi   import trackAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.triggerAnalyzerPAT_cfi import triggerAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.vertexAnalyzerPAT_cfi  import vertexAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.photonAnalyzerPAT_cfi  import photonAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.mcTruthAnalyzerPAT_cfi import mcTruthAnalyzerPAT
#from JSturdy.AnalysisNtuplePAT.hemisphereAnalyzerPAT_cfi import hemisphereAnalyzerPAT

#global switch for data/mc
doMC      = cms.untracked.bool(True)
debugLevel = cms.untracked.int32(0)


analysisNtuplePAT = cms.EDAnalyzer("AnalysisNtuplePAT",

                                       ############Jet section############
    caloJetParameters     = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(10.),
            doMCJets  = doMC,
            useCaloJets  = cms.untracked.bool(True),
            debugJets = debugLevel,
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5Calo"),
            prefixJets = cms.untracked.string("Calo")
        )
    ),
                                  
    jptJetParameters      = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            useJPTJets   = cms.untracked.bool(True),
            debugJets = debugLevel,
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5JPT"),
            jetCorTag  = cms.untracked.string("AK5JPT"),
            prefixJets = cms.untracked.string("JPT")
        )
    ),
                                  
    pfJetParameters       = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            usePFJets   = cms.untracked.bool(True),
            debugJets = debugLevel,
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5PF"),
            jetCorTag  = cms.untracked.string("AK5PF"),
            prefixJets = cms.untracked.string("PF")
        )
    ),
    pf2patJetParameters       = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            usePFJets   = cms.untracked.bool(True),
            debugJets = debugLevel,
            jetTag     = cms.untracked.InputTag("selectedPatJetsPF"),
            jetCorTag  = cms.untracked.string("AK5PF"),
            prefixJets = cms.untracked.string("PF2PAT")
        )
    ),
                                  
    trackJetParameters    = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            useTrackJets   = cms.untracked.bool(True),
            debugJets = debugLevel,
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5Track"),
            jetCorTag  = cms.untracked.string("AK5Track"),
            prefixJets = cms.untracked.string("Track")
        )
    ),
                                  
                                   ############Lepton section############
    leptonParameters     = cms.untracked.PSet(
        leptonAnalyzerPAT.clone(
            elecTag   = cms.untracked.InputTag("cleanPatElectrons"),
            muonTag   = cms.untracked.InputTag("cleanPatMuons"),
            tauTag    = cms.untracked.InputTag("cleanPatTaus"),
            prefixLeps = cms.untracked.string("")
        )
    ),
                                   ############Photon section############
    photonParameters     = cms.untracked.PSet(
        photonAnalyzerPAT.clone(
            photTag  = cms.untracked.InputTag("cleanPatPhotons"),
            prefixPhots = cms.untracked.string("")
        )
    ),

    #PF section
    pfleptonParameters     = cms.untracked.PSet(
        leptonAnalyzerPAT.clone(
            elecTag   = cms.untracked.InputTag("selectedPatElectronsPF"),
            muonTag   = cms.untracked.InputTag("selectedPatMuonsPF"),
            tauTag    = cms.untracked.InputTag("selectedPatTausPF"),
            prefixLeps = cms.untracked.string("PF")
        )
    ),
    pfphotonParameters     = cms.untracked.PSet(
        photonAnalyzerPAT.clone(
            photTag  = cms.untracked.InputTag("selectedPatPhotonsPF"),
            prefixPhots = cms.untracked.string("PF")
        )
    ),

#############################MC Truth information #####################
    mcTruthParameters     = cms.untracked.PSet(
        mcTruthAnalyzerPAT.clone(
            genParticleTag  = cms.untracked.InputTag("genParticles")
        )
    ),

                                   #############MET section############
    calometParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5Calo"),
            prefixMET = cms.untracked.string("CaloTypeI")
        )
    ),
    calometTypeIIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = cms.untracked.bool(False),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloTypeII"),
            prefixMET = cms.untracked.string("CaloTypeII")
        )
    ),

    pfmetParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetTrue"),
            metTag    = cms.untracked.InputTag("patMETsPF"),
            prefixMET = cms.untracked.string("PF")
        )
    ),

    pfmetTypeIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetTrue"),
            metTag    = cms.untracked.InputTag("patMETsTypeIPF"),
            prefixMET = cms.untracked.string("PFTypeI")
        )
    ),

    tcmetParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = cms.untracked.bool(False),
            metTag    = cms.untracked.InputTag("patMETsTC"),
            prefixMET = cms.untracked.string("TC")
        )
    ),

                                       ############Other information section############
    vertexParameters     = cms.untracked.PSet(
        vertexAnalyzerPAT.clone(
#            debugVertex = debugLevel
        )
    ),
    trackParameters      = cms.untracked.PSet(
        trackAnalyzerPAT.clone(
#            debugTracks = debugLevel
        )
    ),
    triggerParameters    = cms.untracked.PSet(
        triggerAnalyzerPAT.clone(
            debugTriggers = debugLevel
        )
    ),

    debugDiJets = cms.untracked.int32(0),
    doMCTruth   = cms.untracked.bool(False)
)


#makeTheNtuple = cms.Path(analysisNtuplePAT)

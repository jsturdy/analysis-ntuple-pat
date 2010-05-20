import FWCore.ParameterSet.Config as cms


from JSturdy.AnalysisNtuplePAT.jetAnalyzerPAT_cfi import jetAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.metAnalyzerPAT_cfi import metAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.leptonAnalyzerPAT_cfi import leptonAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.trackAnalyzerPAT_cfi import trackAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.triggerAnalyzerPAT_cfi import triggerAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.vertexAnalyzerPAT_cfi import vertexAnalyzerPAT
from JSturdy.AnalysisNtuplePAT.photonAnalyzerPAT_cfi import photonAnalyzerPAT
#from JSturdy.AnalysisNtuplePAT.hemisphereAnalyzerPAT_cfi import hemisphereAnalyzerPAT

#global switch for data/mc
doMC = cms.untracked.bool(False)

analysisNtuplePAT = cms.EDAnalyzer("AnalysisNtuplePAT",

                                       ############Jet section############
    caloJetParameters     = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(10.),
            doMCJets  = doMC,
            useJPTJets   = cms.untracked.bool(True),
            useCaloJets  = cms.untracked.bool(True),
            
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5"),
            prefixJets = cms.untracked.string("Calo")
        )
    ),
                                  
    jptJetParameters      = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            useJPTJets   = cms.untracked.bool(True),
            useCaloJets  = cms.untracked.bool(True),
            
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5JPT"),
            prefixJets = cms.untracked.string("JPT")
        )
    ),
                                  
    pfJetParameters       = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            useJPTJets   = cms.untracked.bool(True),
            useCaloJets  = cms.untracked.bool(True),
            
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5PF"),
            prefixJets = cms.untracked.string("PF")
        )
    ),
                                  
    trackJetParameters    = cms.untracked.PSet(
        jetAnalyzerPAT.clone(
            jetMinPt  = cms.untracked.double(8.),
            doMCJets  = doMC,
            useTrackJets   = cms.untracked.bool(True),
            
            jetTag     = cms.untracked.InputTag("cleanPatJetsAK5Track"),
            prefixJets = cms.untracked.string("Track")
        )
    ),
                                  
#                                   ############HT/MHT section############
#    caloHTMHTParameters     = cms.untracked.PSet(
#        htmhtAnalyzerPAT.clone(
#            jetMaxEta = cms.untracked.double(3.0),
#            jetMinPt  = cms.untracked.double(10.),
#            doMHHTMHT = doMC,
#            jetTag      = cms.untracked.InputTag("cleanPatJetsAK5Calo"),
#            mhtTag      = cms.untracked.InputTag("patMHTsAK5Calo"),
#            prefixHTMHT = cms.untracked.string("Calo")
#        )
#    ),
#                                  
#    jptHTMHTParameters     = cms.untracked.PSet(
#        htmhtAnalyzerPAT.clone(
#            jetMaxEta = cms.untracked.double(3.0),
#            jetMinPt  = cms.untracked.double(10.),
#        
#            jetTag      = cms.untracked.InputTag("cleanPatJetsAK5JPT"),
#            prefixHTMHT = cms.untracked.string("JPT")
#        )
#    ),
#
#    pfHTMHTParameters     = cms.untracked.PSet(
#        htmhtAnalyzerPAT.clone(
#            jetMaxEta = cms.untracked.double(3.0),
#            jetMinPt  = cms.untracked.double(10.),
#        
#            jetTag      = cms.untracked.InputTag("cleanPatJetsAK5PF"),
#            prefixHTMHT = cms.untracked.string("PF")
#        )
#    ),
#
#    trackHTMHTParameters     = cms.untracked.PSet(
#        htmhtAnalyzerPAT.clone(
#            jetMaxEta = cms.untracked.double(3.0),
#            jetMinPt  = cms.untracked.double(10.),
#        
#            jetTag      = cms.untracked.InputTag("cleanPatJetsAK5Track"),
#            prefixHTMHT = cms.untracked.string("Track")
#        )
#    ),

   #hemisphereParameters = cms.untracked.PSet(
   #     hemisphereAnalyzerPAT.clone(
   #     )
   #),
                                   ############Lepton section############
    leptonParameters     = cms.untracked.PSet(
        leptonAnalyzerPAT.clone(
            doMCLeps  = doMC,
            elecTag   = cms.untracked.InputTag("cleanPatElectrons"),
            muonTag   = cms.untracked.InputTag("cleanPatMuons"),
            #tauTag   = cms.untracked.InputTag("cleanPatTaus"),
        )
    ),
    pfleptonParameters     = cms.untracked.PSet(
        leptonAnalyzerPAT.clone(
            doMCLeps  = doMC,
            elecTag   = cms.untracked.InputTag("selectedPatElectronsPF"),
            muonTag   = cms.untracked.InputTag("selectedPatMuonsPF"),
            #tauTag   = cms.untracked.InputTag("selectedPatTausPF"),
        )
    ),
                                   ############Photon section############
    photonParameters     = cms.untracked.PSet(
        photonAnalyzerPAT.clone(
            doMCPhots = doMC,
            photTag  = cms.untracked.InputTag("cleanPatPhotons")
        )
    ),
    pfphotonParameters     = cms.untracked.PSet(
        photonAnalyzerPAT.clone(
            doMCPhots = doMC,
            photTag  = cms.untracked.InputTag("selectedPatPhotonsPF")
        )
    ),

                                   #############MET section############
    calometParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5Calo"),
            prefixMET = cms.untracked.string("Calo")
        )
    ),
    calometOptParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloOpt"),
            prefixMET = cms.untracked.string("CaloOpt")
        )
    ),
    calometTypeIIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloTypeII"),
            prefixMET = cms.untracked.string("CaloTypeII")
        )
    ),
    calometOptTypeIIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloOptTypeII"),
            prefixMET = cms.untracked.string("CaloOptTypeII")
        )
    ),
    calometCleanParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloClean"),
            prefixMET = cms.untracked.string("CaloClean")
        )
    ),
    calometCleanOptParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloCleanOpt"),
            prefixMET = cms.untracked.string("CaloCleanOpt")
        )
    ),
    calometCleanTypeIIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloCleanTypeII"),
            prefixMET = cms.untracked.string("CaloCleanTypeII")
        )
    ),
    calometCleanOptTypeIIParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            doMCMET   = doMC,
            genMETTag = cms.untracked.InputTag("genMetCalo"),
            metTag    = cms.untracked.InputTag("patMETsAK5CaloCleanOptTypeII"),
            prefixMET = cms.untracked.string("CaloCleanOptTypeII")
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

    tcmetParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            metTag    = cms.untracked.InputTag("patMETsTC"),
            prefixMET = cms.untracked.string("TC")
        )
    ),
    tcmetCleanedParameters        = cms.untracked.PSet(
        metAnalyzerPAT.clone(
            metTag    = cms.untracked.InputTag("patMETsTCClean"),
            prefixMET = cms.untracked.string("TCClean")
        )
    ),


                                       ############Other information section############
    vertexParameters     = cms.untracked.PSet(
        vertexAnalyzerPAT.clone(
            
        )
    ),
    trackParameters      = cms.untracked.PSet(
        trackAnalyzerPAT.clone(
        )
    ),
    triggerParameters    = cms.untracked.PSet(
        triggerAnalyzerPAT.clone(
        )
    ),

    debugDiJets = cms.untracked.int32(0)
)


#makeTheNtuple = cms.Path(analysisNtuplePAT)

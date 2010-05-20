import FWCore.ParameterSet.Config as cms

# produce associated jet correction factors in a valuemap
from JSturdy.AnalysisNtuplePAT.jetCorrFactors_cfi import *
myPATJetCorrections = myPATJetCorrFactors.clone()
from JSturdy.AnalysisNtuplePAT.MetType1Corrections_cff import *

# MET correction for JES
#from JSturdy.AnalysisNtuplePAT.MetType1Corrections_cff import *
from JetMETCorrections.Configuration.DefaultJEC_cff import *

# MET correction for Muons
from JetMETCorrections.Type1MET.MuonMETValueMapProducer_cff import *
from JetMETCorrections.Type1MET.MetMuonCorrections_cff import corMetGlobalMuons

###Muon corrections for the JES corrected calo MET objects
myMETJESCorAK5CaloJetMuons          = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJet')
)
myMETJESCorAK5CaloJetMuonsOpt       = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetOpt')
)
myMETJESCorAK5CaloJetMuonsTypeII    = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetTypeII')
)
myMETJESCorAK5CaloJetMuonsOptTypeII = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetOptTypeII')
)

###Muon corrections for the ECAL cleaned and JES corrected calo MET objects
myMETJESCorAK5CaloJetMuonsClean          = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetClean')
)
myMETJESCorAK5CaloJetMuonsCleanOpt       = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetCleanOpt')
)
myMETJESCorAK5CaloJetMuonsCleanTypeII    = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetCleanTypeII')
)
myMETJESCorAK5CaloJetMuonsCleanOptTypeII = corMetGlobalMuons.clone(
    uncorMETInputTag = cms.InputTag('myMETJESCorAK5CaloJetCleanOptTypeII')
)

myMetMuonCorrections = cms.Sequence(
    myMETJESCorAK5CaloJetMuons               *
    myMETJESCorAK5CaloJetMuonsOpt            *
    myMETJESCorAK5CaloJetMuonsClean          *
    myMETJESCorAK5CaloJetMuonsCleanOpt       *
    myMETJESCorAK5CaloJetMuonsTypeII         *
    myMETJESCorAK5CaloJetMuonsOptTypeII      *
    myMETJESCorAK5CaloJetMuonsCleanTypeII    *
    myMETJESCorAK5CaloJetMuonsCleanOptTypeII
)

# default PAT sequence for JetMET corrections before cleaners
myPATJetMETCorrections = cms.Sequence(
    myPATJetCorrections    *
    myMetMuonCorrections
)


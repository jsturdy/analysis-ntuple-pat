import FWCore.ParameterSet.Config as cms


from JSturdy.AnalysisNtuplePAT.analysisNtuplePAT_cfi import *
doAnalysisNtuplePAT = cms.Sequence(
    analysisNtuplePAT
)

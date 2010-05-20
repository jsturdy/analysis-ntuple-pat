import FWCore.ParameterSet.Config as cms

# prepare reco information
from JSturdy.AnalysisNtuplePAT.jetMETCorrections_cff import *

# produce object
from PhysicsTools.PatAlgos.producersLayer1.metProducer_cfi import *
#from JSturdy.AnalysisNtuplePAT.metProducer_cfi import *

makePatMETs = cms.Sequence(
    # reco pre-production
    myPATMETCorrections *
    # pat specifics
    # object production
    patMETs
    )

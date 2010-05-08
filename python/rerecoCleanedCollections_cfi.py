import FWCore.ParameterSet.Config as cms

#reflagrereco.load('Configuration/StandardSequences/Services_cff')
#reflagrereco.load('FWCore/MessageService/MessageLogger_cfi')
#reflagrereco.load('Configuration/StandardSequences/GeometryExtended_cff')
#reflagrereco.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
#reflagrereco.load('Configuration/StandardSequences/Reconstruction_cff')
#reflagrereco.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#reflagrereco.load('Configuration/EventContent/EventContent_cff')

from Configuration.StandardSequences.Services_cff import *
from FWCore.MessageService.MessageLogger_cfi import *
from Configuration.StandardSequences.GeometryExtended_cff import *
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
from Configuration.StandardSequences.Reconstruction_cff import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
from Configuration.EventContent.EventContent_cff import *


################################# Extras ####################################
#-- HCAL reflagging ---------------------------------------------------------#
#HBHE Noise
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
hbheNoise = HBHENoiseFilter.clone()

from JetMETAnalysis.HcalReflagging.hbherechitreflaggerJETMET_cfi import *
hbherecoReflagged = hbherechitreflaggerJETMET.clone(
    debug = cms.int32(0)
)


# HF RecHit reflagger
from JetMETAnalysis.HcalReflagging.HFrechitreflaggerJETMET_cff import *

# implement some python flags possibly

#hfrecoReflagged = HFrechitreflaggerJETMETv1.clone()
#hfrecoReflagged = HFrechitreflaggerJETMETv2.clone()
hfrecoReflagged = HFrechitreflaggerJETMETv3.clone()
#hfrecoReflagged = HFrechitreflaggerJETMETv4.clone()

# do all cloning for the jetmetreco sequence:
towerMaker.hbheInput = cms.InputTag("hbherecoReflagged")
towerMaker.hfInput = cms.InputTag("hfrecoReflagged")


# Need to specify new severity levels to make use of the new flags!
import JetMETAnalysis.HcalReflagging.RemoveAddSevLevel as RemoveAddSevLevel
# Both hf and hbhe reflagging store their new flags in bit 31 (UserDefinedBit31) --
# set this value to 10 so that flagged hits are excluded from the towers
#hcalRecAlgos = RemoveAddSevLevel.AddFlag(hcalRecAlgos,"UserDefinedBit0",10) ##typo?
hcalRecAlgos = RemoveAddSevLevel.AddFlag(hcalRecAlgos,"UserDefinedBit31",10)

#-- ECAL Cleaning - ---------------------------------------------------------#
from RecoEcal.EgammaClusterProducers.ecalRecHitFlags_cfi import *
from RecoEcal.EgammaClusterProducers.hybridSuperClusters_cfi import *
from RecoEgamma.EgammaPhotonProducers.photons_cfi import *

ecalCleaning = hybridSuperClusters.clone(
    RecHitFlagToBeExcluded = cms.vint32(
        ecalRecHitFlag_kFaultyHardware,
        ecalRecHitFlag_kPoorCalib,
        ecalRecHitFlag_kOutOfTime,
        ecalRecHitFlag_kDead
    ),
    RecHitSeverityToBeExcluded = cms.vint32(3,4),
    severityRecHitThreshold    = cms.double(4),
    severitySpikeId            = cms.int32(1),
    severitySpikeThreshold     = cms.double(0.95),
    excludeFlagged             = cms.bool(True)
)



reflagging_step = cms.Sequence(hfrecoReflagged)


rereco_step = cms.Sequence(
    caloTowersRec       *
    (
        recoJets   * #does this include jpt, and pf?
        recoJetIds +
        recoTrackJets
    )     *
    recoJetAssociations *
    metreco
) # re-reco jets and met

#The following sequence is very similar to highlevelreco step in reconstruction.
#However, the PF is removed as it needs input from normal reco
#(see Configuration/StandardSequences/python/Reconstruction_cff.py)
highlevelreco_step = cms.Sequence(
    recoJetAssociations*
    # re-associate to jets
    btagging
)


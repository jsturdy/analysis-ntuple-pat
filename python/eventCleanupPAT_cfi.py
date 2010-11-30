import FWCore.ParameterSet.Config as cms


#-- PKAM Filtering ----------------------------------------------------------#
removePKAM = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

#-- Vertex Filtering --------------------------------------------------------#
primaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
    filter = cms.bool(True)   # otherwise it won't filter the events, just produce an empty vertex collection.
)

#method 2, not sure which is better
primaryVertexFilter2 = cms.EDFilter("GoodVertexFilter",
    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
    minimumNDOF = cms.uint32(4) ,
    maxAbsZ = cms.double(24),
    maxd0 = cms.double(2)
)

#-- HLT PhysicsDelcared Filter ----------------------------------------------#
from HLTrigger.special.hltPhysicsDeclared_cfi import *

physicsDeclared = hltPhysicsDeclared.clone(
    L1GtReadoutRecordTag = 'gtDigis'
)

#HBHE Noise
useHBHEfilter = False

#Reject events with HBHE noise
#if useHBHEfilter == True:
from CommonTools.RecoAlgos.HBHENoiseFilter_cfi import *
hbheNoise = HBHENoiseFilter.clone()
    
# Instead of rejecting the event, add a flag indicating the HBHE noise
#from CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi import *
#hbheNoiseFlag = HBHENoiseFilterResultProducer.clone()

cleanupFilterMC = cms.Sequence(
    removePKAM          +
    primaryVertexFilter +
    hbheNoise           #+
#    hbheNoiseFlag
)

cleanupFilterData = cms.Sequence(
    #l1TechFilter        +
    physicsDeclared     +
    cleanupFilterMC
)
    

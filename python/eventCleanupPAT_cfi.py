import FWCore.ParameterSet.Config as cms

#-- MET Cleaning ------------------------------------------------------------#
cleanTCMET = cms.EDProducer('CleanedTCMETProducer',
    tcmetInputTag     = cms.InputTag("tcMet"),
    caloTowerInputTag = cms.InputTag("towerMaker"),
    ebRechitInputTag  = cms.InputTag("ecalRecHit", "EcalRecHitsEB"),
    eeRechitInputTag  = cms.InputTag("ecalRecHit", "EcalRecHitsEE"),
    jetInputTag       = cms.InputTag("ak5CaloJets"),
    jetIDinputTag     = cms.InputTag("ak5JetID"),
    alias             = cms.string("tcMetCleaned"),
    useHFcorrection   = cms.bool(True),
    useECALcorrection = cms.bool(True),
    useHCALcorrection = cms.bool(True)
)

cleanCaloMET = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("met"),
    alias             = cms.string("metCleaned")
)
cleanCaloMETNoHF = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metNoHF"),
    alias             = cms.string("metNoHFCleaned")
)
cleanCaloMETHO = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metHO"),
    alias             = cms.string("metHOCleaned")
)
cleanCaloMETNoHFHO = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metNoHFHO"),
    alias             = cms.string("metNoHFHOCleaned")
)
cleanCaloMETOpt = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metOpt"),
    alias             = cms.string("metOptCleaned")
)
cleanCaloMETOptNoHF = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metOptNoHF"),
    alias             = cms.string("metOptNoHFCleaned")
)
cleanCaloMETOptHO = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metOptHO"),
    alias             = cms.string("metOptHOCleaned")
)
cleanCaloMETOptNoHFHO = cleanTCMET.clone(
    tcmetInputTag     = cms.InputTag("metOptNoHFHO"),
    alias             = cms.string("metOptNoHFHOCleaned")
)

#-- PKAM Filtering ----------------------------------------------------------#
removePKAM = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(True),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

#-- Vertex Filtering --------------------------------------------------------#
primaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 15 && position.Rho <= 2"), # tracksSize() > 3 for the older cut
    filter = cms.bool(True)   # otherwise it won't filter the events, just produce an empty vertex collection.
)

#method 2, not sure which is better
primaryVertexFilter2 = cms.EDFilter("GoodVertexFilter",
    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
    minimumNDOF = cms.uint32(4) ,
    maxAbsZ = cms.double(15),
    maxd0 = cms.double(2)
)

#-- L1 Tech Trig Filtering --------------------------------------------------#
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskAlgoTrigConfig_cff import *
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import *

l1TechFilter = hltLevel1GTSeed.clone(
    L1TechTriggerSeeding = cms.bool(True),
    L1SeedsLogicalExpression = cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND NOT 43) OR (43 AND NOT 42))')
)


#-- HLT PhysicsDelcared Filter ----------------------------------------------#
from HLTrigger.special.hltPhysicsDeclared_cfi import *

physicsDeclared = hltPhysicsDeclared.clone(
    L1GtReadoutRecordTag = 'gtDigis'
)

##-- HLT Trigger Filter ------------------------------------------------------#

#from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import *
#hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(False)
#hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('(L1_SingleMuBeamHalo OR L1_SingleMuOpen)  AND NOT L1_SingleJet6U')
#
#p = cms.Path ( hltLevel1GTSeed )
#
#
#hltLevel1GTSeed.L1TechTriggerSeeding = cms.bool(True)
#hltLevel1GTSeed.L1SeedsLogicalExpression = cms.string('27 OR  25')
#
#p = cms.Path ( hltLevel1GTSeed )
    

#hltBeamHalo = cms.EDFilter("HLTHighLevel",
#    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
#    HLTPaths = cms.vstring('HLT_CSCBeamHalo','HLT_CSCBeamHaloOverlapRing1','HLT_CSCBeamHaloOverlapRing','HLT_CSCBeamHaloRing2or3'), # provide list of HLT paths (or patterns) you want
#    eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
#    andOr = cms.bool(True),             # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
#    throw = cms.bool(False)    # throw exception on unknown path names
#)

cleanupFilterMC = cms.Sequence(
    removePKAM          +
    primaryVertexFilter #+
    #(
    #    cleanTCMET      +
    #    cleanCaloMET
    #)
)

cleanupFilterData = cms.Sequence(
    cleanupFilterMC     +
    l1TechFilter        +
    physicsDeclared     #+
    #(
    #    cleanTCMET          +
    #    cleanCaloMET
    #)
)
    

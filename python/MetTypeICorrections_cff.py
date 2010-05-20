import FWCore.ParameterSet.Config as cms

# File: MetCorrections.cff
# Author: R. Cavanaugh
# Modified by J. Sturdy
# Date: 17.05.2010
#
# Updated:  Added modules for MET corrections with KT, Siscone jet algorithms

#TypeI corrections on top of calMET
myMETJESCorAK5CaloJet = cms.EDProducer("Type1MET",
                                   inputUncorJetsLabel = cms.string('ak5CaloJets'),
                                   jetEMfracLimit = cms.double(0.9),
                                   metType = cms.string('CaloMET'),
                                   jetPTthreshold = cms.double(20.0),
                                   inputUncorMetLabel = cms.string('met'),
                                   corrector = cms.string('ak5CaloL2L3'),
                                   UscaleA = cms.double(1.2),
                                   UscaleB = cms.double(2.1),
                                   UscaleC = cms.double(0.6),
                                   useTypeII = cms.bool(False),
                                   hasMuonsCorr = cms.bool(False)
                                   )

#TypeI corrections on top of caloMETOpt
myMETJESCorAK5CaloJetOpt = myMETJESCorAK5CaloJet.clone()
myMETJESCorAK5CaloJetOpt.inputUncorMetLabel    = "metOpt"

#TypeII corrections on top of caloMET
myMETJESCorAK5CaloJetTypeII = myMETJESCorAK5CaloJet.clone()
myMETJESCorAK5CaloJetTypeII.useTypeII          = True

#TypeII corrections on top of caloMETOpt
myMETJESCorAK5CaloJetOptTypeII = myMETJESCorAK5CaloJetOpt.clone()
myMETJESCorAK5CaloJetOptTypeII.useTypeII       = True

###ECAL cleaned MET by FGolf
#TypeI corrections on top of cleaned caloMET
myMETJESCorAK5CaloJetClean = myMETJESCorAK5CaloJet.clone()
myMETJESCorAK5CaloJetClean.inputUncorMetLabel     = "metCleaned"

#TypeI corrections on top of cleaned caloMETOpt
myMETJESCorAK5CaloJetCleanOpt = myMETJESCorAK5CaloJet.clone()
myMETJESCorAK5CaloJetCleanOpt.inputUncorMetLabel  = "metOptCleaned"

#TypeII corrections on top of cleaned caloMET
myMETJESCorAK5CaloJetCleanTypeII = myMETJESCorAK5CaloJetClean.clone()
myMETJESCorAK5CaloJetCleanTypeII.useTypeII        = True

#TypeII corrections on top of cleaned caloMETOpt
myMETJESCorAK5CaloJetCleanOptTypeII = myMETJESCorAK5CaloJetCleanOpt.clone()
myMETJESCorAK5CaloJetCleanOptTypeII.useTypeII     = True


myMetTypeICorrections = cms.Sequence(
    myMETJESCorAK5CaloJet          +
    myMETJESCorAK5CaloJetOpt       +
    myMETJESCorAK5CaloJetClean     +
    myMETJESCorAK5CaloJetCleanOpt
)

myMetTypeIICorrections = cms.Sequence(
    myMETJESCorAK5CaloJetTypeII         +
    myMETJESCorAK5CaloJetOptTypeII      +
    myMETJESCorAK5CaloJetCleanTypeII    +
    myMETJESCorAK5CaloJetCleanOptTypeII
)

myMetJESCorrections = cms.Sequence(
    myMetTypeICorrections +
    myMetTypeIICorrections
)

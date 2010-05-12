#
#  SUSY-PAT configuration file
#
#  PAT configuration for the SUSY group - 35X/36X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV8
#

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

#-- Meta data to be logged in DBS ---------------------------------------------
process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.1 $'),
            name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/UserCode/JSturdy/SUSY/AnalysisNtuplePAT/python/SUSY_V8_7TeV_PATtuple.py,v $'),
            annotation = cms.untracked.string('SUSY pattuple definition')
        )

#-- Message Logger ------------------------------------------------------------
process.MessageLogger.categories.append('PATSummaryTables')
process.MessageLogger.cerr.PATSummaryTables = cms.untracked.PSet(
        limit = cms.untracked.int32(-1),
            reportEvery = cms.untracked.int32(1)
            )
process.MessageLogger.cerr.FwkReport.reportEvery = 100

#-- Input Source --------------------------------------------------------------
process.source.fileNames = [
         '/store/relval/CMSSW_3_6_0_pre6/RelValProdTTbar/GEN-SIM-RECO/MC_36Y_V4-v1/0011/82DAA1BE-B344-DF11-A116-00304867C0C4.root'
              #'/store/mc/Spring10/MinBias/GEN-SIM-RECO/START3X_V25B_356ReReco-v1/0007/FE90A396-233C-DF11-8106-002618943898.root'
              #'/store/data/Commissioning10/MinimumBias/RAW-RECO/Apr1Skim_GOODCOLL-v1/0140/E27B88D1-8040-DF11-B3FC-00261894391B.root'
              #'file:/tmp/nmohr/356ReRecoMC.root'
             ]
process.maxEvents.input = 100
# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

#-- Calibration tag -----------------------------------------------------------
# Should match input file's tag
process.GlobalTag.globaltag = 'START36_V4::All'

############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
#Apply SUSYPAT, parameters are: mcInfo, HLT menu, Jet energy corrections, mcVersion ('35x' for 35x samples, empty string for 36X samples),JetCollections
addDefaultSUSYPAT(process,False,'HLT','Spring10','35x',['AK5Track', 'AK5PF','AK5JPT'])
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################


#-- Output module configuration -----------------------------------------------
process.out.fileName = 'SUSYPAT.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS

# Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )

################################## Extras ####################################

#-- Execution path ----------------------------------------------------------#


#del process.outpath
#del process.out

# Analyzer section
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(
        #"7TeV_MinBias_MC.root"
        "7TeV_MinBias_Data.root"
    )
)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

#from JSturdy.DiJetAnalysis.diJetAnalyzer_cff import doDiJetAnalysis
process.load("JSturdy.AnalysisNtuplePAT.analysisNtuplePAT_cff")
#from JSturdy.AnalysisNtuplePAT.eventCleanupPAT_cfi import *
process.load("JSturdy.AnalysisNtuplePAT.eventCleanupPAT_cfi")
#from JSturdy.AnalysisNtuplePAT.rerecoCleanedCollections_cfi import *
process.load("JSturdy.AnalysisNtuplePAT.rerecoCleanedCollections_cfi")



## Full path
#process.pattify = cms.Path(
#    #process.fixedMETSequence          *
#    #process.addTrackJets          *
#    process.seqSUSYDefaultSequence 
#)

#process.p = cms.Path(
#    process.rerecoData             *
#    process.cleanupFilterData      *
#    process.seqSUSYDefaultSequence *
#    process.doAnalysisNtuplePAT
#)

process.schedule = cms.Schedule(
    process.rerecoData,
    process.cleanupFilterData,
    process.seqSUSYDefaultSequence,
    process.doAnalysisNtuplePAT
)

##-- Dump config ------------------------------------------------------------
#file = open('SusyPAT_cfg.py','w')
#file.write(str(process.dumpPython()))
#file.close()



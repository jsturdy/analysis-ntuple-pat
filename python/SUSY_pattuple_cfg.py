#
#  SUSY-PAT configuration file
#
#  PAT configuration for the SUSY group - 35X/36X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV8
#

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

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
addDefaultSUSYPAT(process,False,'HLT','Spring10','',['AK5Track','AK5PF','AK5JPT']) 
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################


#-- Output module configuration -----------------------------------------------
process.out.fileName = 'SUSYPAT.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS

# Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )

#-- Execution path ------------------------------------------------------------


# Full path
process.p = cms.Path( process.susyPatDefaultSequence )
#-- Dump config ------------------------------------------------------------
file = open('SusyPAT_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()

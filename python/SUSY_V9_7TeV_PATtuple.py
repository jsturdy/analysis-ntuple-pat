#
#  SUSY-PAT configuration file
#
#  PAT configuration for the SUSY group - 37X series
#  More information here:
#  https://twiki.cern.ch/twiki/bin/view/CMS/SusyPatLayer1DefV9
#

# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *
isData = False

#-- Meta data to be logged in DBS ---------------------------------------------
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    name = cms.untracked.string('$Source: /cvs_server/repositories/CMSSW/UserCode/JSturdy/SUSY/AnalysisNtuplePAT/python/SUSY_V9_7TeV_PATtuple.py,v $'),
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
    #'file:/tmp/sturdy/Run2010A_Jun9th.root'
    #'file:/tmp/sturdy/TTbarJets-madgraph.root'
    'file:/tmp/sturdy/TTbar-mcatnlo.root'
    #'file:/tmp/sturdy/SUSY-LM9.root'
    #'file:/tmp/sturdy/ZInvisibleJets-madgraph.root'
    #'file:/tmp/sturdy/ZJets-madgraph.root'
    #'file:/tmp/sturdy/Zmumu-Spring10.root'
    ]
process.maxEvents.input = 1000
# Due to problem in production of LM samples: same event number appears multiple times
process.source.duplicateCheckMode = cms.untracked.string('noDuplicateCheck')

#-- Calibration tag -----------------------------------------------------------
# Should match input file's tag
#process.GlobalTag.globaltag = 'GR_R_37X_V6A::All'
#process.GlobalTag.globaltag = 'START3X_V26::All'
process.GlobalTag.globaltag = 'START3X_V26::All'

############################# START SUSYPAT specifics ####################################
from PhysicsTools.Configuration.SUSY_pattuple_cff import addDefaultSUSYPAT, getSUSY_pattuple_outputCommands
#Apply SUSYPAT, parameters are: mcInfo, HLT menu, Jet energy corrections, mcVersion ('35x' for 35x samples, empty string for 36X samples),JetCollections
addDefaultSUSYPAT(process,True,'HLT','Spring10','35x',['AK5Track','AK5JPT','AK5PF']) 
SUSY_pattuple_outputCommands = getSUSY_pattuple_outputCommands( process )
############################## END SUSYPAT specifics ####################################


#-- Output module configuration -----------------------------------------------
#process.out.fileName = 'SUSYPAT_Run2010A_Data.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
#process.out.fileName = 'SUSYPAT_TTbar.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
process.out.fileName = 'SUSYPAT_TTbar-mcanlo.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
#process.out.fileName = 'SUSYPAT_SUSY-LM9.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
#process.out.fileName = 'SUSYPAT_ZInv.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
#process.out.fileName = 'SUSYPAT_ZJets.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS
#process.out.fileName = 'SUSYPAT_Zmumu.root'       # <-- CHANGE THIS TO SUIT YOUR NEEDS

# Custom settings
process.out.splitLevel = cms.untracked.int32(99)  # Turn on split level (smaller files???)
process.out.overrideInputFileSplitLevels = cms.untracked.bool(True)
process.out.dropMetaData = cms.untracked.string('DROPPED')   # Get rid of metadata related to dropped collections
process.out.outputCommands = cms.untracked.vstring('drop *', *SUSY_pattuple_outputCommands )
process.out.selecteEvents = cms.untracked.PSet(SelectEvents = cms.vstring(''))
#-- Execution path ------------------------------------------------------------
#del process.outpath
#del process.out

# Analyzer section
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(
        #"Run2010A_PAT.root"
        #"TTbar_PAT.root"
        "TTbar-mcanlo_PAT.root"
        #"SUSY-LM9_PAT.root"
        #"ZInv_PAT.root"
        #"ZJets_PAT.root"
        #"Zmumu_PAT.root"
    )
)

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )

#from JSturdy.AnalysisNtuplePAT.analysisNtuplePAT_cff import *
#theNtupler = doAnalysisNtuplePAT
process.load("JSturdy.AnalysisNtuplePAT.analysisNtuplePAT_cff")
process.theNtupler = cms.Sequence(process.doAnalysisNtuplePAT)

#from JSturdy.AnalysisNtuplePAT.eventCleanupPAT_cfi import *
process.load("JSturdy.AnalysisNtuplePAT.eventCleanupPAT_cfi")
if isData :
    process.cleanEvents = cms.Sequence(process.cleanupFilterData)
else :
    process.cleanEvents = cms.Sequence(process.cleanupFilterMC)

process.selectClean = cms.Sequence(process.cleanEvents)

process.susyStep = cms.Sequence(process.susyPatDefaultSequence)


process.p = cms.Path(
    process.cleanEvents  *
    process.susyStep     *
    process.theNtupler
)
#process.schedule = cms.Schedule(
#process.p = cms.Schedule(
#    process.selectClean,
#    #process.seqSUSYDefaultSequence,
#    process.susyStep,
#    process.theNtupler#,
#    #process.endpath
#)

#-- Dump config ------------------------------------------------------------
file = open('SusyPAT_cfg.py','w')
file.write(str(process.dumpPython()))
file.close()

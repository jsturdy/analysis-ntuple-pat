#/usr/bin/python

import sys,os
import string
import re
import optparse

inputs = [
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/JetMETTau_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/JetMET_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/Run_2010A_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/Jet_Run2010B-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/Run_2010_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt0to3500\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt0to15\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt15to20\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt20to30\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt30to50\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt50to80\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt80to120\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt120to170\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt170to230\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt230to300\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt300to380\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt380to470\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt470to600\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt600to800\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt800to1000\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt1000to1400\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt1400to1800\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt1800to2200\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt2200to2600\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt2600to3000\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose1PVChecking/QCD_DiJets_Pt3000to3500\");",

    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose2PVChecking/JetMETTau_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose2PVChecking/JetMET_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose2PVChecking/Run_2010A_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose2PVChecking/Jet_Run2010B-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose2PVChecking/Run_2010_Data\");",

    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose3PVChecking/JetMETTau_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose3PVChecking/JetMET_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose3PVChecking/Run_2010A_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose3PVChecking/Jet_Run2010B-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose3PVChecking/Run_2010_Data\");",

    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose4PVChecking/JetMETTau_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose4PVChecking/JetMET_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose4PVChecking/Run_2010A_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose4PVChecking/Jet_Run2010B-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingloose4PVChecking/Run_2010_Data\");",

    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/JetMETTau_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/JetMET_Run2010A-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/Run_2010A_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/Jet_Run2010B-Nov4thReReco\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/Run_2010_Data\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt0to3500\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt0to15\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt15to20\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt20to30\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt30to50\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt50to80\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt80to120\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt120to170\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt170to230\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt230to300\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt300to380\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt380to470\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt470to600\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt600to800\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt800to1000\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt1000to1400\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt1400to1800\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt1800to2200\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt2200to2600\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt2600to3000\");",
    "METResolutionCalculation(\"/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/looseTriggerCheckingstrict1PVChecking/QCD_DiJets_Pt3000to3500\");",
    
    ]

for index,file in enumerate(inputs):
    sourcefilename = "calculationStep_%02d.C"%(index)
    SOURCE = open(sourcefilename,"w")
    SOURCE.write("{\n")
    SOURCE.write("gROOT->ProcessLine(\".L ../METResolutionCalculation_cc.so\");\n")
    SOURCE.write(file)
    SOURCE.write("\n}")
    
    ###Condor steps
    outputname = "submit_calculation_%02d.sub"%(index)
    FILE = open(outputname,"w")
    FILE.write("universe = vanilla\n")
    FILE.write("Executable = condorMETCalculation.csh\n")
    FILE.write("Should_Transfer_Files = YES\n")
    FILE.write("WhenToTransferOutput = ON_EXIT\n")
    FILE.write("Output = calculation_job_%02d.stdout\n"%(index))
    FILE.write("Error  = calculation_job_%02d.stderr\n"%(index))
    FILE.write("Log    = calculation_job_%02d.log\n"%(index))
    FILE.write("notification = never\n")
    FILE.write("Arguments = $(PROCESS) calculationStep_%02d.C\n"%(index))
    FILE.write("Queue 1\n")
    
    FILE.close()
    #if (index < 10):
    cmd = "condor_submit "+outputname
    print (cmd)
    os.system(cmd)
    

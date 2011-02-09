#/usr/bin/python

import sys,os
import string
import re

dir = "/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/feb4th/"
exe = "/uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/METResolution.exe  "

commands = [

"cd "+dir+"jet30u/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/;  cp "+dir+"all/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/QCD_DiJets_Pt1800to2200_00.root .",
"cd "+dir+"jet50u/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/;  cp "+dir+"all/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/QCD_DiJets_Pt1800to2200_00.root .",
"cd "+dir+"jet140u/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt2600to3000/root/; cp "+dir+"all/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt2600to3000/root/QCD_DiJets_Pt2600to3000_00.root .",
"cd "+dir+"jet100u/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/; cp "+dir+"all/strict1PV/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200/root/QCD_DiJets_Pt1800to2200_00.root .",
]

#for job in reversed(commands):
for job in commands:
#for job in range(1):
    cmd = job
    print(cmd)
    os.system(cmd)

#/usr/bin/python

import sys,os
from ROOT import *

steps = [1,2,3,4,5]
samples = [
    "MC/MinBias/Pythia8-MinBias",
    "MC/MinBias/QCD_Pt15",
    
    "Data/July6thRun2010AJetMETTau",
    "Data/June9thMinBiasJetMETTau",
    "Data/June9thRun2010AJetMETTau",
    "Data/Run2010A_Prompt-v4",
    "MC/VectorBosons/Zmumu"
    ]
lumi = 1
xsvals = [
    #QCD MadGraph
    7.126e10,
    8.76215e8,
    #Data
    1,
    1,
    1,
    1,
    #Zmumu
    1300
    ]
effs = [
    #QCD MadGraph
    1.0,
    1.0,
    #Data
    1.0,
    1.0,
    1.0,
    1.0,
    #Zmumu
    1.0
    ]
numGenEvents = [
    #QCD MadGraph
    10764844,
    6190500,
    #Data
    1,
    1,
    1,
    1,
    #Zmumu
    2111268
    ]

fileCount = [
    #MinBias
    5,###53,
    #QCD_Pt15
    5,###53,
    #Data
    14, ###147,
    20, ###209,
    4, ###d4826,
    2, ###26,
    #Zmumu
    2  ###26
    ]

version = ["met", "mht","full"]
jetTag = ["Calo", "JPT", "PF", "Track"]
metTag = ["CaloTypeI", "PF", "TC"]
lepTag = ["", "PF"]
phtTag = ["", "PF"]
analyses = [
    [0,0,0,0],###Calo-TypeI-"" 
    [0,2,0,0],###Calo-TC-""    
    [1,0,0,0],###JPT-TypeI-""  
    [1,2,0,0],###JPT-TC-""     
    [3,0,0,0],###Track-TypeI-""
    [3,2,0,0],###Track-TC-""   
    [2,1,1,0]###PF-PF-PF      
    ]
for step in steps:
    lastinstance = samples[step-1].rfind("/") + 1
    anStep = samples[step-1][lastinstance:]
    #for ana in analyses:
    ana = analyses[0]
    #ver = version[2]
    for ver in version:
        for count in range(fileCount[step-1]+1):
            filename = "runDiJetStudy_%s_%s_j%sm%sl%s_%02dx.C"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count)
            FILE = open(filename,"w")
            FILE.write("{\n")
            FILE.write("\tgROOT->ProcessLine(\".L ./DiJetStudy.so\");\n\n")
            FILE.write("\tTChain* chainA = new TChain(\"analysisNtuplePAT/AllData\");\n")
            path = "/pnfs/cms/WAX/resilient/sturdy07/PAT_V9/%s"%(samples[step-1])
            if ( count==0 ):
                myRan = "_?_?_???"
            else :
                myRan = "_%d?_?_???"%(count)
            FILE.write("\tchainA->Add(\"dcache:%s/*%s.root\");\n"%(path,myRan))
            
            FILE.write("\ttreeA = chainA;\n")
            FILE.write("\tDiJetStudy* diJets;\n")
            FILE.write("\tdiJets = new DiJetStudy(treeA, true, \"%s\",\"%s\",\"%s\",\"%s\");\n"%(jetTag[ana[0]], metTag[ana[01]], lepTag[ana[2]], phtTag[ana[3]]))
            outfilename = "%s_%s_j%sm%sl%s_%02dx.root"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count)
            #FILE.write("\tstring outfilename = \"./%s_%s_%s_%s_%s_%f.root\";\n"%(samples[step],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],step))
            FILE.write("\tdiJets.Loop(\"%s\",\"%s\",%d,%f,%1.2f,%f);\n"%(outfilename,ver,lumi,xsvals[step-1],effs[step-1],numGenEvents[step-1]))
            
            FILE.write("}\n")
            FILE.close()
            
            ###Condor steps
            tmpcondorsub = "/tmp/sturdy/condor_%s_%s_j%sm%sl%s_%02dx.sub"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count)
            FILE = open(tmpcondorsub,"w")
            FILE.write("universe = vanilla\n")
            FILE.write("Executable = /uscms_data/d2/sturdy07/SUSY/CMSSW_3_7_0_patch4/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/condorROOT.csh\n")
            FILE.write("Should_Transfer_Files = YES\n")
            FILE.write("WhenToTransferOutput = ON_EXIT\n")
            FILE.write("Output = diJet_%s_%s_j%sm%sl%s_%02dx_$(Process).stdout\n"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count))
            FILE.write("Error = diJet_%s_%s_j%sm%sl%s_%02dx_$(Process).stderr\n"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count))
            FILE.write("Log = diJet_%s_%s_j%sm%sl%s_%02dx_$(Process).log\n"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count))
            #FILE.write("notify_user = jared.todd.sturdy@cern.ch\n")
            FILE.write("Arguments = $(PROCESS) /uscms_data/d2/sturdy07/SUSY/CMSSW_3_7_0_patch4/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/%s\n"%(filename))
            FILE.write("Queue 1\n")
            
            FILE.close()
            cmd = "condor_submit "+tmpcondorsub
            print(cmd)
            os.system(cmd)

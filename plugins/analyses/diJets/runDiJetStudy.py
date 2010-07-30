#/usr/bin/python

import sys,os
from ROOT import *

steps = [1,2,3,4,5,6,7,12,13,21,22,23,24,25,26,27]
samples = [
    "QCD/MadGraph/Pt50to100-madgraph",
    "QCD/MadGraph/Pt100to250-madgraph",
    "QCD/MadGraph/Pt250to500-madgraph",
    "QCD/MadGraph/Pt500to1000-madgraph",
    "QCD/MadGraph/Pt1000toInf-madgraph",
    "SUSY/LM0",
    "SUSY/LM1",
    "SUSY/LM2",
    "SUSY/LM2mhfeq360",
    "SUSY/LM3",
    "SUSY/LM4",
    "SUSY/LM5",
    "SUSY/LM6",
    "SUSY/LM7",
    "SUSY/LM8",
    "SUSY/LM9",
    "SUSY/LM9t175",
    "SUSY/LM9p",
    "SUSY/LM10",
    "SUSY/LM11",
    "SUSY/LM12",
    "SUSY/LM13",
    "TTbar/TTbarJets-madgraph",
    "VectorBosons/WJets-madgraph",
    "VectorBosons/ZJets-madgraph",
    "VectorBosons/ZInvisibleJets",
    "VectorBosons/Zmumu"
    ]
lumi = 100
xsvals = [
    #QCD MadGraph
    30e6, #30ub
    7e6,
    1.71e5,
    5200,
    83,
    #SUSY
    38.93,
    4.888,
    0.6027,
    0.5010,
    3.438,
    1.879,
    0.4734,
    0.3104,
    1.209,
    0.7300,
    7.134,
    4.241,
    1.653,
    0.04778,
    0.8236,
    4.414,
    6.899,
    #TTbarJets
    95,
    #VectorBosons
    24170,
    2400,
    4500,
    1300
    ]
effs = [
    #QCD MadGraph
    1.0, #0.22,
    1.0, #0.33,
    1.0, #0.21,
    1.0, #0.31,
    1.0, #0.21,
    #SUSY
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    1.0,
    #TTbarJets-madgraph
    1.0, #0.35,
    #VectorBosons-madgraph
    1.0, #0.45,
    1.0, #0.44,
    1.0, #0.45,
    1.0
    ]
numGenEvents = [
    #QCD MadGraph
    220715,
    10875132,
    4913036,
    4234762,
    1661261,
    #SUSY
    207533,
    207273,
    190240,
    246225,
    229750,
    255954,
    242840,
    275950,
    275169,
    217435,
    220000,
    214424,
    219834,
    203818,
    276780,
    208620,
    221800,
    #TTbarJets-madgraph
    1483404,
    #VectorBosons-madgraph
    10068895,
    1084921,
    2110493,
    2111268
    ]

fileCount = [
    ###QCD
    10,###103,
    10,###105,
    10,###102,
    10,###102,
    10,###101,
    ###SUSY
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###25,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###26,
    2, ###25,
    ###TTbar
    10,###101,
    ###VectorBosons
    25,###253,
    5, ###51,
    2, ###26,
    2  ###26
    ]

version = ["met", "mht"]
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
    for ana in analyses:
        for ver in version:
            for count in range(fileCount[step-1]+1):
                filename = "runDiJetStudy_%s_%s_j%sm%sl%s_%02dx.C"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count)
                FILE = open(filename,"w")
                FILE.write("{\n")
                FILE.write("\tgROOT->ProcessLine(\".L ./DiJetStudy.so\");\n\n")
                FILE.write("\tTChain* chainA = new TChain(\"analysisNtuplePAT/AllData\");\n")
                path = "/pnfs/cms/WAX/resilient/sturdy07/PAT_V9/MC/%s"%(samples[step-1])
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
                FILE.write("notify_user = jared.todd.sturdy@cern.ch\n")
                FILE.write("Arguments = $(PROCESS) /uscms_data/d2/sturdy07/SUSY/CMSSW_3_7_0_patch4/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/%s\n"%(filename))
                FILE.write("Queue 1\n")

                FILE.close()
                cmd = "condor_submit "+tmpcondorsub
                print(cmd)
                os.system(cmd)

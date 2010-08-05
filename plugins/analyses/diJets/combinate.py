#/usr/bin/python

import sys,os
from ROOT import *

#steps = [1,2,3,4,5,6,7,12,13,21,22,23,24,25,26,27,28,29,30,31,32]
steps = [1,2,3,4,5,6,7,12,13,21,22,23,24,25,26,27]
samples = [
    "MC/QCD/MadGraph/Pt50to100-madgraph",
    "MC/QCD/MadGraph/Pt100to250-madgraph",
    "MC/QCD/MadGraph/Pt250to500-madgraph",
    "MC/QCD/MadGraph/Pt500to1000-madgraph",
    "MC/QCD/MadGraph/Pt1000toInf-madgraph",
    "MC/SUSY/LM0",
    "MC/SUSY/LM1",
    "MC/SUSY/LM2",
    "MC/SUSY/LM2mhfeq360",
    "MC/SUSY/LM3",
    "MC/SUSY/LM4",
    "MC/SUSY/LM5",
    "MC/SUSY/LM6",
    "MC/SUSY/LM7",
    "MC/SUSY/LM8",
    "MC/SUSY/LM9",
    "MC/SUSY/LM9t175",
    "MC/SUSY/LM9p",
    "MC/SUSY/LM10",
    "MC/SUSY/LM11",
    "MC/SUSY/LM12",
    "MC/SUSY/LM13",
    "MC/TTbar/TTbarJets-madgraph",
    "MC/VectorBosons/WJets-madgraph",
    "MC/VectorBosons/ZJets-madgraph",
    "MC/VectorBosons/ZInvisibleJets",
    "MC/VectorBosons/Zmumu",

    "MC/MinBias/Pythia8-MinBias",
    "MC/MinBias/QCD_Pt15",

    "Data/July6thRun2010AJetMETTau",
    "Data/June9thMinBiasJetMETTau",
    "Data/June9thRun2010AJetMETTau",
    "Data/Run2010A_Prompt-v4"
]

version = ["met", "mht","full"]
jetTag = ["Calo", "JPT", "PF", "Track"]
metTag = ["CaloTypeI", "PF", "TC"]
lepTag = ["", "PF"]
phtTag = ["", "PF"]
anDirs = ["MET_Analysis", "MHT_Analysis", "Full_Analysis"]
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
    #for ver,anDir in zip(version,anDirs):
    ver = version[0]
    anDir = anDirs[0]
    outfilename = "%s/%sJets/%s_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    infilename  = "%s/%sJets/%s_%s_j%sm%sl%s_*.root"%(anDir,jetTag[ana[0]],anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    cmd = "hadd %s  %s"%(outfilename, infilename)
    print(cmd)
    os.system(cmd)
        
#        cmd = "rm   %s"%(infilename)
#        print(cmd)
#        os.system(cmd)
        
backgrounds = [
    "QCD_MadGraph_Pt50toInf",
    "VectorBosons",
    "SM_Background",
    "7TeV_Data"
    ]
#for ana in analyses:
ana = analyses[0]
ver = version[0]
anDir = anDirs[0]
#for ver,anDir in zip(version,anDirs):
qcdoutfilename = "%s/%sJets/%s_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],backgrounds[0],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
infilename  = "%s/%sJets/Pt*to*-madgraph_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
cmd = "hadd %s  %s"%(qcdoutfilename,infilename)
print(cmd)
os.system(cmd)

vboutfilename = "%s/%sJets/%s_%s_j%sm%sl%s.root"             %(anDir,jetTag[ana[0]],backgrounds[1],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
infilename1   = "%s/%sJets/WJets*_%s_j%sm%sl%s.root"         %(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
infilename2   = "%s/%sJets/ZJets*_%s_j%sm%sl%s.root"         %(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
infilename3   = "%s/%sJets/ZInvisibleJets*_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
cmd = "hadd %s  %s %s %s"%(vboutfilename,infilename1,infilename2,infilename3)
print(cmd)
os.system(cmd)

smoutfilename = "%s/%sJets/%s_%s_j%sm%sl%s.root"    %(anDir,jetTag[ana[0]],backgrounds[2],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
infilename    = "%s/%sJets/TTbar*_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
cmd = "hadd %s  %s %s %s"%(smoutfilename,qcdoutfilename,vboutfilename,infilename)
print(cmd)
os.system(cmd)
    
    #dataoutfilename = "%s/%sJets/%s_%s_j%sm%sl%s.root"         %(anDir,jetTag[ana[0]],backgrounds[3],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    #infilename1     = "%s/%sJets/June9thMin*_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    #infilename2     = "%s/%sJets/June9thRun*_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    #infilename3     = "%s/%sJets/July6thRun*_%s_j%sm%sl%s.root"%(anDir,jetTag[ana[0]],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    #cmd = "hadd %s  %s %s %s"%(dataoutfilename,infilename1,infilename2,infilename3)
    #print(cmd)
    #os.system(cmd)

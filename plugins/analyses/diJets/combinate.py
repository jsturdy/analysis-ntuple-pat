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
            outfilename = "%s_%s_j%sm%sl%s.root"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
            infilename  = "%s_%s_j%sm%sl%s_*.root"%(anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
            cmd = "hadd %s  %s"%(outfilename, infilename)
            print(cmd)
            os.system(cmd)
            
            cmd = "rm   %s"%(infilename)
            print(cmd)
            os.system(cmd)

backgrounds = [
    "QCD_MadGraph_Pt50toInf",
    "VectorBosons",
    "SM_Background"
    ]
for ana in analyses:
    for ver in version:
        qcdoutfilename = "%s_%s_j%sm%sl%s.root"%(backgrounds[0],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        infilename  = "Pt*to*-madgraph_%s_j%sm%sl%s.root"%(ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        cmd = "hadd %s  %s"%(qcdoutfilename,infilename)
        print(cmd)
        os.system(cmd)
        
        vboutfilename = "%s_%s_j%sm%sl%s.root"%(backgrounds[1],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        infilename1  = "WJets*_%s_j%sm%sl%s.root"%(ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        infilename2  = "ZJets*_%s_j%sm%sl%s.root"%(ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        infilename3  = "ZInvisibleJets*_%s_j%sm%sl%s.root"%(ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        cmd = "hadd %s  %s %s %s"%(vboutfilename,infilename1,infilename2,infilename3)
        print(cmd)
        os.system(cmd)
        
        smoutfilename = "%s_%s_j%sm%sl%s.root"%(backgrounds[2],ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        infilename  = "TTbar*_%s_j%sm%sl%s.root"%(ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
        cmd = "hadd %s  %s %s %s"%(smoutfilename,qcdoutfilename,vboutfilename,infilename)
        print(cmd)
        os.system(cmd)
        

#!/usr/bin/python

import sys,os
import array

steps = [1,2,3,4,5,6,7,12,13,21,22,23,24,25,26,27,28,29,30,31,32]
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
    2,  ###26
    #MinBias
    5,###53,
    #QCD_Pt15
    5,###53,
    #Data
    14, ###147,
    20, ###209,
    4, ###d4826,
    2 ###26,
]

version = ["met", "mht","full"]
dirs    = ["MET_Analysis", "MHT_Analysis", "Full_Analysis"]
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

prestring    = "Sequential-pre:"
indstring    = "Individual:"
nm1prestring = "N-1:"
poststring   = "Sequential-post:"

#for ana in analyses:
ana = analyses[0]
for dir,ver in zip(dirs,version):
    outfilename = "%s/%s_j%sm%sl%s.cutflow"%(dir,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]])
    OUTFILE = open(outfilename,"w")
    for step in steps:
        lastinstance = samples[step-1].rfind("/") + 1
        anStep = samples[step-1][lastinstance:]
        prevalues = []
        indvalues = []
        nm1prevalues = []
        postvalues = []
        for count in range(fileCount[step-1]+1):
            infilename  = "%s/diJet_%s_%s_j%sm%sl%s_%02dx_0.stdout"%(dir,anStep,ver,jetTag[ana[0]],metTag[ana[1]],lepTag[ana[2]],count)
            RFILE = open(infilename,"r")
            #RFILE.readline()
            found = False
            for line in RFILE:
                tmpline=[]
                tmpline = line.split(' ')
                if (tmpline[0].find('version') > -1):
                    found = True
                    if (count == 0) :
                        print(line)
                        OUTFILE.write(line)
                elif (found):
                    if (tmpline[0].find('Cut') > -1):
                        if (count == 0):
                            print(line)
                            OUTFILE.write(line)
                    else:
                        pos = line.find(':') + 1
                        
                        substr = line[pos:].strip('\n')
                        substr = substr.split('-')
                        if (count == 0):
                            values = substr
                            for i,value in enumerate(substr):
                                print(i)
                                #print(value.strip(' '))
                                values[i] = int(value.strip(' '))
                        else :
                            pos = line.find(':') + 1
                            substr = line[pos:].strip('\n')
                            substr = substr.split('-')
                            print(substr)
                            for i,value in enumerate(substr):
                                print(value.strip(' '))
                                #print(i)
                                values[i] = values[i] + int(value.strip(' '))

                        print (values)

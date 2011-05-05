#/usr/bin/python

import sys,os
import string
import re
import optparse

def main():
    parser = optparse.OptionParser(
        usage='Usage: %prog [-m MODE] [-i INPUTTEXT] [-f INPUTFILE] -o OUTPUTDIR -n NUMJOBS -j JETALGO -e METALGO -l LEPALGO -p PHTALGO',
        description='Example: condorSubmit.py -i  -o rootfiles/ -j 20')
    parser.add_option( '-m', '--mode',      metavar='MODE',      action='store', help='Single file (s) or textfile (t) with list of files (default)' )
    parser.add_option( '-i', '--inputText', metavar='INPUTTEXT', action='store', help='Specifies the input text file listing the .root files. Please use the full path.  Not required for single file mode' )
    parser.add_option( '-f', '--inputFile', metavar='INPUTFILE', action='store', help='Specifies the input root file. Please use the full path.  Required for single file mode' )
    parser.add_option( '-o', '--outputDir', metavar='OUTPUTDIR', action='store', help='Specifies the output directory where the results will be stored. Please use the full path' )
    parser.add_option( '-n', '--numJobs',   metavar='NUMJOBS',   action='store', help='Specifies the number of jobs to break the submission into for list mode (default is 10)' )
    parser.add_option( '-j', '--jetAlg',    metavar='JETALGO',   action='store', help='Specifies the Jet algorithm to use (default is PF2PAT)' )
    parser.add_option( '-e', '--metAlg',    metavar='METALGO',   action='store', help='Specifies the MET algorithm to use (default is PFTypeI)' )
    parser.add_option( '-l', '--lepAlg',    metavar='LEPALGO',   action='store', help='Specifies the Lepton algorithm to use (default is PF)' )
    parser.add_option( '-p', '--phtAlg',    metavar='PHTALGO',   action='store', help='Specifies the Photon algorithm to use (default is PF)' )
    
    (options, args) = parser.parse_args(args=None)
    jobs = 10

    jetPrefix = 'PF2PAT'
    metPrefix = 'PFTypeI'

    lepPrefix = 'PF'
    doPFLeps  = 1;

    phtPrefix = ''
    doPFPhots = 0;

    jobName = ''
    isData = 0

    #cutFile        = '/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/cutFile_samp.txt'
    #triggerList    = '/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/triggerList.txt'
    #efficiencyList = '/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/sampleDef.txt'

    cutFile        = './cutFile.txt'
    triggerList    = './triggerList.txt'
    efficiencyList = './sampleDef.txt'

    if ( options.mode!='s' and options.mode!='t' and options.mode!=None ):
        print ("Incorrect submission mode specified "+options.mode+"\n")
        parser.print_help()
        sys.exit()
    if ( options.mode=='s' and options.inputFile==None ):
        print ("Single file mode requires an input file\n")
        parser.print_help()
        sys.exit()
    if ( options.mode=='t' and options.inputText==None ):
        print ("List mode requires a list file\n")
        parser.print_help()
        sys.exit()
    if ( options.mode==None and options.inputText==None ):
        print ("List mode requires a list file\n")
        parser.print_help()
        sys.exit()

    ### Done with all sanity checks

    if ( options.mode=='s'):
            print options.inputfile.split('/')
            jobName = options.inputfile.split('/')[-1].strip('.root')
    else:
        print options.inputText.split('/')
        #jobName = options.inputText.split('/')[-1].strip('.tx')
        jobName = options.inputText.split('/')[-1]
        jobName = jobName[0:-4]

    print jobName
    if (jobName.find('Run2010')>=0 or jobName.find('Run2011')>=0 or jobName.find('Prompt')>=0):
        print("Job is Data")
        isData = 1
    else:
        print("Job is MC ")
        isData = 0

    if ( options.numJobs!=None ):
        jobs = int(options.numJobs)
    if ( options.jetAlg!=None ):
        jetPrefix = options.jetAlg
    if ( options.metAlg!=None ):
        metPrefix = options.metAlg
    if ( options.lepAlg!=None ):
        lepPrefix = options.lepAlg
    if ( options.phtAlg!=None ):
        phtPrefix = options.phtAlg

    if (lepPrefix == "PF") :
        doPFLeps  = 1
    else:
        doPFLeps = 0
    if (phtPrefix == "PF"):
        doPFPhots = 1
    else:
        doPFPhots = 0
    
    extraDir = ""
    if (jetPrefix=="Calo"):
        extraDir = "calo/"
    elif (jetPrefix=="PF2PAT"):
        extraDir = "pf2pat/"
    elif (jetPrefix=="PF"):
        extraDir = "pf/"

    if ( options.outputDir==None ):
        print ("No output directory specified, using JobName and current working directory")
        pwd = os.getcwd()
        outputmain = '/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw413/newDiJetResults/'+extraDir+jobName
        print ("output directory is %s")%(outputmain)

    os.system("mkdir -p "+outputmain+"/input/")
    os.system("mkdir -p "+outputmain+"/log/")
    os.system("mkdir -p "+outputmain+"/src/")
    os.system("mkdir -p "+outputmain+"/root/")

    # output prefix
    outputPrefix = string.split(outputmain,"/")[-1]
#################################################
    numfiles = len(file(options.inputText).readlines())
    
    if jobs > numfiles:
        jobs=numfiles
    filesperjob = int(numfiles/jobs)
    if numfiles%jobs!=0:
        filesperjob = filesperjob+1
        jobs = int(numfiles/filesperjob)+1

#################################################
    input = open(options.inputText)
#################################################
    debug = False
    for ijob in range(jobs):
        # prepare the list file
        inputfilename = "%s/input/inputlist_%02d.txt"%(outputmain,ijob)
        inputfile = open(inputfilename,"w")
        for i in range(filesperjob):
            line = input.readline()
            if line != "":
                inputfile.write(line)
            continue
        inputfile.close()
        #for cut in range(2):
        ###Condor steps
        outputname = "%s/src/submit_%02d.sub"%(outputmain,ijob)
        FILE = open(outputname,"w")
        FILE.write("universe = vanilla\n")
        FILE.write("Executable = /uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/condorDiJets.csh\n")
        FILE.write("Should_Transfer_Files = YES\n")
        FILE.write("WhenToTransferOutput = ON_EXIT\n")
        tmpcutFile        = "/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/cutFile.txt"
        tmptriggerList    = "/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/triggerList.txt"
        tmpefficiencyList = "/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/common/config/sampleDef.txt"
        tmppragmaLib      = "/uscms_data/d2/sturdy07/SUSY/CMSSW_4_1_3_patch2/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/ntuplePragmas.so"
        FILE.write("Transfer_Input_Files = %s,%s,%s,%s\n"%(tmpcutFile,tmptriggerList,tmpefficiencyList,tmppragmaLib))
        FILE.write("Output = ../log/job_%02d.stdout\n"%(ijob))
        FILE.write("Error = ../log/job_%02d.stderr\n"%(ijob))
        FILE.write("Log = ../log/job_%02d.log\n"%(ijob))
        FILE.write("notification = never \n")
        #FILE.write("notification = error \n")
        #FILE.write("notify_user = $(logname)@fnal.gov \n")
        #FILE.write("Arguments = $(PROCESS) %s  %s  %s  %s  %d  %s  %s  %d  %d  %s/root/  %d  %d\n"%(inputfilename,efficiencyList,triggerListFile,int(isData),jetPrefix,metPrefix,doPFLeps,doPFPhots,outputmain,debug))
        FILE.write("Requirements = (Memory >= 599 && OpSys == \"LINUX\" && (Arch == \"INTEL\" || Arch ==\"x86_64\"))\n")
        FILE.write("Arguments = $(PROCESS) %s  %s  %s  %s  %d  %s  %s  %d  %d  $_CONDOR_SCRATCH_DIR  %d\n"%(inputfilename,efficiencyList,triggerList,cutFile,int(isData),jetPrefix,metPrefix,doPFLeps,doPFPhots,debug))
        FILE.write("Queue 1\n")
        
        FILE.close()
        os.chdir(outputmain+"/root/")
        print (os.getcwd())
        cmd = "condor_submit "+outputname
        print (cmd)
        os.system(cmd)
        

if __name__ == '__main__':
    main()

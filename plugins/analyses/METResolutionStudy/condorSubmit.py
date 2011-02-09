#/usr/bin/python

import sys,os
import string
import re
import optparse

def main():
    parser = optparse.OptionParser(
        usage='Usage: %prog [-m MODE] [-i INPUTTEXT] [-f INPUTFILE] -o OUTPUTDIR -n NUMJOBS -j JETALGO -s SCALETYPE -t STRICTTRIGGER -p STRICTPV ',
        description='Example: condorSubmit.py -i  -o rootfiles/ -j 20')
    parser.add_option( '-m', '--mode',      metavar='MODE',      action='store', help='Single file (s) or textfile (t) with list of files (default)' )
    parser.add_option( '-i', '--inputText', metavar='INPUTTEXT', action='store', help='Specifies the input text file listing the .root files. Please use the full path.  Not required for single file mode' )
    parser.add_option( '-f', '--inputFile', metavar='INPUTFILE', action='store', help='Specifies the input root file. Please use the full path.  Required for single file mode' )
    parser.add_option( '-o', '--outputDir', metavar='OUTPUTDIR', action='store', help='Specifies the output directory where the results will be stored. Please use the full path' )
    parser.add_option( '-n', '--numJobs',   metavar='NUMJOBS',   action='store', help='Specifies the number of jobs to break the submission into for list mode (default is 10)' )
    parser.add_option( '-j', '--jetAlg',    metavar='JETALGO',   action='store', help='Specifies the Jet algorithm to use (default is PF)' )
    parser.add_option( '-s', '--scaleType', metavar='SCALETYPE', action='store', help='Specifies the MC version to which the SumET will be scaled (default is Fall10 Pythia8 from TH2F (value 11), other values are 12,21,22' )
    #parser.add_option( '-t', '--hltNames',  metavar='HLTNAMES',  action='store', help='Specifies which HLT jet trigger to use (default is all)' )
    parser.add_option( '-t', '--strictTrigger',  metavar='STRICTTRIGGER',  action='store', help='Specifies whether to use smart triggering on jets (default is false)' )
    parser.add_option( '-p', '--strictPV',  metavar='STRICTPV',  action='store', help='Specifies whether to use strict PV checking (default is false)' )
    
    (options, args) = parser.parse_args(args=None)
    jobs = 10
    jetPrefix = 'PF'
    jobName = ''
    isData = 0
    scale = 1
    #hltJetNames = 'all'
    strictTriggerCheck = 0
    strictPVCheck      = 0
    
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
        jobName = options.inputfile.split('/')[-1].strip('.root')
    else:
        jobName = options.inputText.split('/')[-1].strip('.txt')

    print("JobName is "+jobName)
    if (jobName.find('PATtuple_V9_DATA')>=0):
        print("Job is Data")
        isData = 1
    elif (jobName.find('PATtuple_V9_MC')>=0):
        print("Job is MC ")
        isData = 0

    #if ( options.hltNames!=None ):
    #    hltJetNames = options.hltNames
    if ( options.strictTrigger==None ):
        print ("no trigger checking specified")
    if ( options.strictTrigger!=None ):
        strictTriggerCheck = options.strictTrigger

    jobDir = ""
    if (int(strictTriggerCheck)==0) :
        jobDir = "all/"
    elif (int(strictTriggerCheck)==1) :
        jobDir = "jet15u/"
    elif (int(strictTriggerCheck)==2) :
        jobDir = "jet30u/"
    elif (int(strictTriggerCheck)==3) :
        jobDir = "jet50u/"
    elif (int(strictTriggerCheck)==4) :
        jobDir = "jet70u/"
    elif (int(strictTriggerCheck)==5) :
        jobDir = "jet100u/"
    elif (int(strictTriggerCheck)==6) :
        jobDir = "jet140u/"
    elif (int(strictTriggerCheck)==7) :
        jobDir = "loose1TRG/"
    elif (int(strictTriggerCheck)==8) :
        jobDir = "loose2TRG/"
    elif (int(strictTriggerCheck)==9) :
        jobDir = "loose3TRG/"

    ###PV check 
    if ( options.strictPV==None ):
        print ("no pv checking specified")
    if ( options.strictPV!=None ):
        strictPVCheck = options.strictPV

    print "strict Trigger check = "+str(strictTriggerCheck)
    print "strict PV check = "     +str(strictPVCheck)
    
    if (int(strictPVCheck)==0) :
        jobDir = jobDir+"strict1PV"
        
    elif (int(strictPVCheck)==1) :
        jobDir = jobDir+"loose1PV"
        
    elif (int(strictPVCheck)==2) :
        jobDir = jobDir+"loose2PV"
        
    elif (int(strictPVCheck)==3) :
        jobDir = jobDir+"loose3PV"
        
    elif (int(strictPVCheck)==4) :
        jobDir = jobDir+"loose4PV"
        
    else :
        jobDir = jobDir+"loosePV"

    if ( options.outputDir==None ):
        print ("No output directory specified, using JobName and 3DayLifetime")
        pwd = os.getcwd()
        #outputmain = pwd+'/'+jobName
        #outputmain = '/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/'+jobDir+'/'+jobName
        outputmain = jobDir+'/'+jobName

    joboutdir = '/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/metResStudy/feb4th/'

    if ( options.numJobs!=None ):
        jobs = int(options.numJobs)
    if ( options.jetAlg!=None ):
        jetPrefix = options.jetAlg
    if ( options.scaleType!=None ):
        scale = options.scaleType

    os.system("mkdir -p "+joboutdir+outputmain+"/input/")
    os.system("mkdir -p "+joboutdir+outputmain+"/log/")
    os.system("mkdir -p "+joboutdir+outputmain+"/src/")
    os.system("mkdir -p "+joboutdir+outputmain+"/root/")

    # output prefix
    outputPrefix = string.split(outputmain,"/")[-1]
#################################################
    numfiles = len(file(options.inputText).readlines())
    
    print ("before anything "+str(jobs)+" jobs to create on "+str(numfiles)+" files")
    if jobs > numfiles:
        print (str(jobs)+" > "+str(numfiles)+": "+str(jobs)+" jobs to create on "+str(numfiles)+" files")
        jobs=numfiles
    filesperjob = int(numfiles/jobs)
    print (str(filesperjob)+" files per job")
    print (str(numfiles)+"%"+str(jobs)+": "+str(numfiles%jobs)+"")
    if numfiles%jobs!=0:
        filesperjob = filesperjob+1
        print ("numfiles%jobs!=0 "+str(filesperjob)+" files per job")
        jobs = int(numfiles/filesperjob)+1

    print ("all said and done "+str(jobs)+" jobs to create")

#################################################
    input = open(options.inputText)
#################################################
    for ijob in range(jobs):
        # prepare the list file
        inputfilename = "%s%s/input/inputlist_%02d.txt"%(joboutdir,outputmain,ijob)
        inputfile = open(inputfilename,"w")
        for i in range(filesperjob):
            line = input.readline()
            if line != "" and line != '/n':
                inputfile.write(line)
            continue
        inputfile.close()
    
        ###Condor steps
        outputname = "%s%s/src/submit_%02d.sub"%(joboutdir,outputmain,ijob)
        FILE = open(outputname,"w")
        FILE.write("universe = vanilla\n")
        #FILE.write("Executable = condorMETResolution.csh\n")
        FILE.write("Executable = /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/condorMETResolution.csh\n")
        FILE.write("Should_Transfer_Files = YES\n")
        FILE.write("WhenToTransferOutput = ON_EXIT\n")
        tmppragmaLib       = "/uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/ntuplePragmas.so"
        FILE.write("Transfer_Input_Files = %s\n"%(tmppragmaLib))
        #FILE.write("Output = %s/log/job_%02d.stdout\n"%(outputmain,ijob))
        #FILE.write("Error  = %s/log/job_%02d.stderr\n"%(outputmain,ijob))
        #FILE.write("Log    = %s/log/job_%02d.log\n"%(outputmain,ijob))
        FILE.write("Output = job_%02d.stdout\n"%(ijob))
        FILE.write("Error  = job_%02d.stderr\n"%(ijob))
        FILE.write("Log    = job_%02d.log\n"   %(ijob))
        ###FILE.write("notify_user = jared.todd.sturdy@cern.ch\n")
        FILE.write("notification = never\n")
        #FILE.write("Arguments = $(PROCESS) %s  %d  %d  %s  %s  %d  %s\n"%(inputfilename,int(isData),int(scale),jetPrefix,hltJetNames,0,outputmain+"/root"))
        #FILE.write("Arguments = $(PROCESS) %s  %d  %d  %s  %d  %d  %d  %s/root\n"%(inputfilename,int(isData),int(scale),jetPrefix,int(strictTriggerCheck),int(strictPVCheck),0,outputmain))
        FILE.write("Requirements = (Memory >= 599 && OpSys == \"LINUX\" && (Arch == \"INTEL\" || Arch ==\"x86_64\"))\n")
        #FILE.write("Arguments = $(PROCESS) %s  %d  %d  %s  %d  %d  %d  %s/root\n"%(inputfilename,int(isData),int(scale),jetPrefix,int(strictTriggerCheck),int(strictPVCheck),0,joboutdir+outputmain))
        #FILE.write("Arguments = $(PROCESS) %s  %d  %d  %s  %d  %d  %d  %s  %s\n"%(inputfilename,int(isData),int(scale),jetPrefix,int(strictTriggerCheck),int(strictPVCheck),0,jobName,joboutdir+outputmain))
        FILE.write("Arguments = $(PROCESS) %s  %d  %d  %s  %d  %d  %d  $_CONDOR_SCRATCH_DIR\n"%(inputfilename,int(isData),int(scale),jetPrefix,int(strictTriggerCheck),int(strictPVCheck),0))
        FILE.write("Queue 1\n")
        
        FILE.close()
        os.chdir(joboutdir+outputmain+"/root/")
        print (os.getcwd())
        cmd = "condor_submit "+outputname
        print (cmd)
        os.system(cmd)
        

if __name__ == '__main__':
    main()

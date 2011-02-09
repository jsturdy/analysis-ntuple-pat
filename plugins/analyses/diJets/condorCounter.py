#/usr/bin/python

import sys,os
import string
import re
import optparse

def main():
    parser = optparse.OptionParser(
        usage='Usage: %prog [-m MODE] [-i INPUTTEXT] [-f INPUTFILE] -o OUTPUTDIR -n NUMJOBS',
        description='Example: condorSubmit.py -i  -o rootfiles/ -j 20')
    parser.add_option( '-m', '--mode',      metavar='MODE',      action='store', help='Single file (s) or textfile (t) with list of files (default)' )
    parser.add_option( '-i', '--inputText', metavar='INPUTTEXT', action='store', help='Specifies the input text file listing the .root files. Please use the full path.  Not required for single file mode' )
    parser.add_option( '-f', '--inputFile', metavar='INPUTFILE', action='store', help='Specifies the input root file. Please use the full path.  Required for single file mode' )
    parser.add_option( '-o', '--outputDir', metavar='OUTPUTDIR', action='store', help='Specifies the output directory where the results will be stored. Please use the full path' )
    parser.add_option( '-n', '--numJobs',   metavar='NUMJOBS',   action='store', help='Specifies the number of jobs to break the submission into for list mode (default is 10)' )
    
    (options, args) = parser.parse_args(args=None)
    jobs = 10

    jobName = ''

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

    if ( options.outputDir==None ):
        print ("No output directory specified, using JobName and current working directory")
        pwd = os.getcwd()
        outputmain = '/uscmst1b_scratch/lpc1/3DayLifetime/sturdy07/tmp/cmssw387/mccounter/'+jobName
        
    if ( options.numJobs!=None ):
        jobs = int(options.numJobs)
    
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
        ###Condor steps
        outputname = "%s/src/submit_%02d.sub"%(outputmain,ijob)
        FILE = open(outputname,"w")
        FILE.write("universe = vanilla\n")
        FILE.write("Executable = condorMCCounter.csh\n")
        FILE.write("Should_Transfer_Files = YES\n")
        FILE.write("WhenToTransferOutput = ON_EXIT\n")
        tmppragmaLib  = "/uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/ntuplePragmas.so"
        FILE.write("Transfer_Input_Files = %s\n"%(tmppragmaLib))
        FILE.write("Output = count_%02d.stdout\n"%(ijob))
        FILE.write("Error  = count_%02d.stderr\n"%(ijob))
        FILE.write("Log    = count_%02d.log\n"%(ijob))
        FILE.write("\n")
        FILE.write("Arguments = $(PROCESS) %s\n"%(inputfilename))
        FILE.write("Queue 1\n")
        
        FILE.close()
        cmd = "condor_submit "+outputname
        print (cmd)
        os.system(cmd)
        
        
if __name__ == '__main__':
    main()

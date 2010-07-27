#!/bin/tcsh 
unsetenv CMS_PATH
#if (!(${?CMS_PATH})) then 
#endif
#here $2 = $1 in Arguments = \$(Process) ${1} ${2} ${3}
set Process = ${1}
set file    = ${2}
echo $1
echo $2 

cd /uscms_data/d2/sturdy07/SUSY/CMSSW_3_7_0_patch4/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/
source /uscmst1/prod/sw/cms/cshrc uaf
cmsenv

#cd $_CONDOR_SCRATCH_DIR
#/uscmst1/prod/sw/cms/slc5_ia32_gcc434/lcg/root/5.22.00d-cms16/bin/root -b -x -q ${2}
root -b -x -q ${2}
#python runBisectorStudyCalo_data.py

#!/bin/tcsh 
unsetenv CMS_PATH

set Process   = ${1}
set filelist  = ${2}
set isdata    = ${3}
set scale     = ${4}
set jets      = ${5}
set techTrigs = ${6}
set debug     = ${7}
set output    = ${8}
echo $1
echo $2 
echo $3 
echo $4 
echo $5 
echo $6 
echo $7 
echo $8

cd /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_5/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/
source /uscmst1/prod/sw/cms/cshrc uaf
cmsenv

./METResolution.exe ${2} ${3} ${4} ${5} ${6} ${7} ${8}

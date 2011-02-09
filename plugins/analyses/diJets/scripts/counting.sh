#!/bin/bash

python condorCounter.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_WJets-madgraph.txt -n 25
python condorCounter.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt500to1000-madgraph.txt -n 25

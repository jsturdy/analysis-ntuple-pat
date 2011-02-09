#!/bin/bash

#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_EG_Run2010A-Nov4thReReco.txt        -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Electron_Run2010B-Nov4thReReco.txt  -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_JetMETTau_Run2010A-Nov4thReReco.txt -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_JetMET_Run2010A-Nov4thReReco.txt    -n 203 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Jet_Run2010B-Nov4thReReco.txt       -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_METFwd_Run2010B-Nov4thReReco.txt    -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_MultiJet_Run2010B-Nov4thReReco.txt  -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Mu_Run2010A-Nov4thReReco.txt        -n 103 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Mu_Run2010B-Nov4thReReco.txt        -n 103 -j PF2PAT -e PFTypeI -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt50to100-madgraph.txt       -n 6 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt100to250-madgraph.txt      -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt250to500-madgraph.txt      -n 73 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt500to1000-madgraph.txt     -n 73 -j PF2PAT -e PFTypeI -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM0.txt                       -n 17 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM13.txt                      -n 17 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM1.txt                       -n 17 -j PF2PAT -e PFTypeI -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_TTbarJets-madgraph.txt        -n 37 -j PF2PAT -e PFTypeI -l PF -p PF

#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Wenu.txt                      -n  -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_WJets-madgraph.txt            -n 73 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Wmunu.txt                     -n  -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_ZInvisibleJets-madgraph.txt   -n 27 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_ZJets-madgraph.txt            -n 27 -j PF2PAT -e PFTypeI -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Zmumu.txt                     -n  -j PF2PAT -e PFTypeI -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt0to15.txt       -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt15to20.txt      -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt20to30.txt      -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt30to50.txt      -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt50to80.txt      -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt80to120.txt     -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt120to170.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt170to230.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt230to300.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt300to380.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt380to470.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt470to600.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt600to800.txt    -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt800to1000.txt   -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1000to1400.txt  -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1400to1800.txt  -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200.txt  -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt2200to2600.txt  -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt2600to3000.txt  -n 37 -j PF2PAT -e PFTypeI -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt3000to3500.txt  -n 1 -j PF2PAT -e PFTypeI -l PF -p PF


#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_EG_Run2010A-Nov4thReReco.txt        -n 103 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Electron_Run2010B-Nov4thReReco.txt  -n 103 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_JetMETTau_Run2010A-Nov4thReReco.txt -n 103 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_JetMET_Run2010A-Nov4thReReco.txt    -n 203 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Jet_Run2010B-Nov4thReReco.txt       -n 103 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_METFwd_Run2010B-Nov4thReReco.txt    -n 103 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_MultiJet_Run2010B-Nov4thReReco.txt  -n 103 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Mu_Run2010A-Nov4thReReco.txt        -n 103 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_DATA_387_Mu_Run2010B-Nov4thReReco.txt        -n 103 -j PF2PAT -e PF -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt50to100-madgraph.txt       -n 6 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt100to250-madgraph.txt      -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt250to500-madgraph.txt      -n 73 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_QCD_pt500to1000-madgraph.txt     -n 73 -j PF2PAT -e PF -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM0.txt                       -n 17 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM13.txt                      -n 17 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_SUSY_LM1.txt                       -n 17 -j PF2PAT -e PF -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_TTbarJets-madgraph.txt        -n 37 -j PF2PAT -e PF -l PF -p PF

#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Wenu.txt                      -n  -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_WJets-madgraph.txt            -n 73 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Wmunu.txt                     -n  -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_ZInvisibleJets-madgraph.txt   -n 27 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_ZJets-madgraph.txt            -n 27 -j PF2PAT -e PF -l PF -p PF
#python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_387_Zmumu.txt                     -n  -j PF2PAT -e PF -l PF -p PF

python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt0to15.txt       -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt15to20.txt      -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt20to30.txt      -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt30to50.txt      -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt50to80.txt      -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt80to120.txt     -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt120to170.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt170to230.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt230to300.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt300to380.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt380to470.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt470to600.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt600to800.txt    -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt800to1000.txt   -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1000to1400.txt  -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1400to1800.txt  -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt1800to2200.txt  -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt2200to2600.txt  -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt2600to3000.txt  -n 37 -j PF2PAT -e PF -l PF -p PF
python condorSubmit.py -i /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/config/PATtuple_V9_MC_QCD_DiJets_Pt3000to3500.txt  -n 1 -j PF2PAT -e PF -l PF -p PF

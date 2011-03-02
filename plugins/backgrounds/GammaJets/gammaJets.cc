#include "photonJets.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <stdlib.h>
#include <iomanip>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include "/uscms_data/d2/sturdy07/SUSY/new387/CMSSW_4_1_1/src/JSturdy/AnalysisNtuplePAT/plugins/common/ntuplePragmas.h"
//#include "myDict.h"

using namespace std;
using namespace ROOT;

int main(int argc, char* argv[])
{
  bool debug = true;
  const int Nparam1=12;   // NUMBER OF PARAMETERS
  for (int thearg = 0; thearg < argc; ++thearg) 
    cout<<"arg["<<thearg<<"]" << "  -  "  << argv[thearg]<<endl;
  cout<<endl;
  if(argc!=Nparam1+1)
    {
      cout << "gammaJets() : argc = " << argc << " is different from " << Nparam1+1<<". Exiting." <<endl;
      cout << "Usage  : ./gammaJets inputFileList(or input file name) efficiencyFile triggerList  cutFile  isData  jetPrefix  metPrefix  lepPrefix  photPrefix relaxedCuts strictDiJets debug" << endl;
      cout << "Example: ./gammaJets ntuples.txt  efficiencyList.txt  triggerList.txt  cutFile.txt 1 Calo   CaloTypeI  0  0  1  1  1" << endl;
      cout << "Example: ./gammaJets ntuple.root  efficiencyList.txt  triggerList.txt  cutFile.txt 0 PF2PAT PF         1  1  0  0  0" << endl;
      exit (1);
    };
  //Should clean up the arguments
  //1. Make them switch based, rather than order specific
  //2. Also helps with making default values

  std::string inputfiles = argv[1];
  std::string* efficiencyList = new string(argv[2]);
  std::string* triggerList    = new string(argv[3]);
  std::string* cutFile        = new string(argv[4]);

  std::stringstream ss1 ( argv[5] );
  bool isData = 0;
  ss1 >> isData;

  std::string jets   = argv[6];
  std::string mets   = argv[7];

  std::string leps   = "";
  std::stringstream ss2 ( argv[8] );
  bool doPFLeps;
  ss2 >> doPFLeps;
  if (doPFLeps)
    leps = "PF";

  std::string phots  = "";
  std::stringstream ss3 ( argv[9] );
  bool doPFPhots;
  ss3 >> doPFPhots;
  if (doPFPhots)
    phots = "PF";

  std::stringstream ss4 ( argv[10] );
  bool relaxed;
  ss4 >> relaxed;
  
  std::stringstream ss5 ( argv[11] );
  bool doStrictDiJets;
  ss5 >> doStrictDiJets;

  std::stringstream ss6 ( argv[12] );
  ss6 >> debug;

  std::cout<<"inputfiles = "    <<inputfiles<<std::endl;
  std::cout<<"efficiencyList = "<<efficiencyList<<std::endl;
  std::cout<<"triggerList = "   <<triggerList<<std::endl;
  std::cout<<"cutFile = "       <<cutFile<<std::endl;
  std::cout<<"isData = "        <<isData<<std::endl;
  std::cout<<"jets = "          <<jets<<std::endl;
  std::cout<<"mets = "          <<mets<<std::endl;
  std::cout<<"leps = "          <<leps<<std::endl;
  std::cout<<"phots = "         <<phots<<std::endl;
  std::cout<<"relaxed = "       <<relaxed<<std::endl;
  std::cout<<"strictDiJets = "  <<doStrictDiJets<<std::endl;
  std::cout<<"debug = "         <<debug<<std::endl;

  //
  std::string outputfile;
  std::string tmpKey = "test";

  TChain *chainA = new TChain("analysisNtuplePAT/AllData");
  if (debug) std::cout<<"checking to see if we were passed a list "<<std::endl;
  if (inputfiles.rfind(".txt")!=string::npos) {
    if (debug) std::cout<<"opening inputfiles list "<<inputfiles<<std::endl;
    ifstream is(inputfiles.c_str());
    if (is.good()) {
      //loop over all files in the list and add them to the chain
      char pName[500];
      if (debug) std::cout<<"reading inputfiles list "<<inputfiles<<std::endl;
      while( is.getline(pName, 500, '\n') )
        {
          if (pName[0] == '#') continue;
	  //if (pName[0] == ' ') continue; // do we want to skip lines that start with a space?
	  if (pName[0] == '\n') continue;// simple protection against blank lines
	  //if (debug) std::cout<<"Adding file: " << pName<<std::endl;
          chainA->Add(pName);
        }
      //output root files
      outputfile = inputfiles.erase(inputfiles.rfind('.'));
      
      //Getting the sample name for the output file
      size_t firstPAT   = string::npos;
      size_t firstInput = string::npos;
      firstPAT   = outputfile.find("PAT");
      firstInput = outputfile.find("input");
      if (debug) std::cout<<"at step 1 "<<outputfile<<std::endl;
      //size_t position = outputfile.rfind("/input/inputlist");
      //outputfile.erase(position,16);
      if (debug) std::cout<<"at step 2 "<<outputfile<<std::endl;
	
      int bb = 0;
      while (outputfile.find('/')!=string::npos)
	{
	  ++bb;
	  outputfile.erase(0,outputfile.find('/')+12);
	  if (debug) std::cout<<"at step 3."<<bb<<" "<<outputfile<<std::endl;
	}
      if (debug) std::cout<<"at step 4 "<<outputfile<<std::endl;
      if (outputfile.find("PATtuple_V9_")!=string::npos)
	outputfile.erase(0,outputfile.find("PATtuple_V9_")+12);
      if (debug) std::cout<<"at step 5 "<<outputfile<<std::endl;
      if (outputfile.find("DATA_")!=string::npos)
	outputfile.erase(0,outputfile.find("DATA_")+5);
      if (debug) std::cout<<"at step 6 "<<outputfile<<std::endl;
      if (outputfile.find("MC_")!=string::npos)
	outputfile.erase(0,outputfile.find("MC_")+3);
      if (debug) std::cout<<"at step 7 "<<outputfile<<std::endl;
      if (outputfile.find("387_")!=string::npos)
	outputfile.erase(0,outputfile.find("387_")+4);
       if (debug) std::cout<<"at step 8 "<<outputfile<<std::endl;
     tmpKey = outputfile;
    }
    else {
      std::cout << "ERROR opening inputfiles list:" << inputfiles << std::endl;
      exit (1);
    }
  }
  else {
    chainA->Add(inputfiles.c_str());
    outputfile = inputfiles.erase(inputfiles.rfind('.'));
    tmpKey = outputfile;
  }

  if (debug) std::cout<<"finished "<<outputfile<<std::endl;
  std::cout<<"Input file is: "     <<inputfiles<<std::endl;
  TTree *treeA = chainA;
    
  float cutJet1 = 150;
  float cutJet2 = 150;
  float cutMET  = 250;
  char tmpoutputfile[128];

  if (relaxed) {
    std::cout<<"Using relaxed cuts"<<std::endl;
    cutJet1 = 100;
    cutJet2 = 100;
    cutMET  = 200;
  }
  
  sampleInfo sampVals;
  std::string sampleKey;
  sampleKey = tmpKey.erase(tmpKey.rfind("_"),string::npos);
  std::cout<<"sampleKey = "<<sampleKey<<std::endl;
  if (debug) std::cout<<"key for efficiencies "<<sampleKey<<std::endl;

  photonJets* analysis = new photonJets(treeA, 
					efficiencyList, 
					triggerList, 
					cutFile, 
					isData, 
					jets, 
					mets, 
					leps, 
					phots, 
					sampleKey);

  
  /*
  sampVals = analysis->ReadInEfficiencies(efficiencyList,sampleKey);
  if (isData) {
    sampVals.xs      = 1.;
    sampVals.eff     = 1.;
    sampVals.numGen  = 1.;
  }

  sampVals.lumi = 35.;
  sampVals.scale = 1.;

  if (!isData)
    sampVals.scale = sampVals.lumi * sampVals.xs * sampVals.eff / sampVals.numGen;
  
  std::cout<<"parameters passed to the event loop:"<<std::endl;
  std::cout<<"\tlumi = "  <<sampVals.lumi;
  std::cout<<"\tscale = " <<sampVals.scale;
  std::cout<<"\txs = "    <<sampVals.xs;
  std::cout<<"\teff = "   <<sampVals.eff;
  std::cout<<"\tnumGen = "<<sampVals.numGen;
  std::cout<<std::endl;
  */

  sprintf(tmpoutputfile,"%s_j1-%d_j2-%d_m-%d_out",outputfile.c_str(),int(cutJet1),int(cutJet2),int(cutMET));
  std::cout<<"Output file is: "<<string(tmpoutputfile)<<std::endl;
  /*
  float lumi   = sampVals.lumi;
  float eff    = sampVals.eff;
  float xs     = sampVals.xs;
  float numGen = sampVals.numGen;
  float scale  = sampVals.scale;

  std::cout<<"\tscale = "     <<scale;
  std::cout<<"\tluminosity = "<<lumi;
  std::cout<<"\txs = "        <<xs;
  std::cout<<"\teff = "       <<eff;
  std::cout<<"\tnumGen = "    <<numGen;
  std::cout<<std::endl;
  */
  int triggerPaths = 2;
  //analysis->Loop(string(tmpoutputfile), float(lumi), float(xs), float(eff), float(numGen), float(cutJet1), float(cutJet2), float(cutMET));
  analysis->Loop(string(tmpoutputfile), float(cutJet1), float(cutJet2), float(cutMET),doStrictDiJets,triggerPaths);
  //analysis->Loop(string(tmpoutputfile), lumi, scale, cutJet1, cutJet2, cutMET);

  std::cout<<"Done with gammaJets.exe"<<std::endl;

  delete chainA;
  delete analysis;
}


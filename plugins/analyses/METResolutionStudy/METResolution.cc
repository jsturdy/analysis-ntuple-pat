#include "METResolutionStudy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <iomanip>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
//#include "ntuplePragmas.h"
//#include "myDict.h"

using namespace std;
using namespace ROOT;


int main(int argc, char* argv[])
{
  const int Nparam1=7;   // NUMBER OF PARAMETERS
  for (int thearg = 0; thearg < argc; ++thearg) 
    cout << "  -  "  << argv[thearg];
  cout<<endl;
  if(argc!=Nparam1+1)
    {
      cout << "METResolution() : argc = " << argc << " is different from " << Nparam1+1<<". Exiting." <<endl;
      cout << "Usage  : ./METResolution inputFileList(or input file name) isData scaleType jetPrefix doTechTrigs debug outDir" << endl;
      cout << "Example: ./METResolution ntuples.txt 0 1 Calo 0 0 outputdirectory" << endl;
      cout << "Example: ./METResolution ntuple.root 0 1 PF 1 0 outputdir" << endl;
      exit (1);
    };

  std::string inputfiles = argv[1];

  std::stringstream ss1 ( argv[2] );
  bool isData = 0;
  ss1 >> isData;

  std::stringstream ss2 ( argv[3] );
  int scale_type = -1;
  ss2 >> scale_type;

  std::string jets  = argv[4];

  std::stringstream ss3 ( argv[5] );
  bool doTechTrigs = 0;
  ss3 >> doTechTrigs;

  std::stringstream ss4 ( argv[6] );
  bool debug = 0;
  ss4 >> debug;

  std::string phots = "";
  std::string outDir = argv[7];
  
  //scaling recoSumEt to MC using 
  //1 - FullSim Pythia8
  //2 - FullSim Pythia8 Summer10

  /**************

    3 - #/MinBias_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    4 - #/MinBias_TuneProQ20_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    5 - #/MinBias_TuneProPT0_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    6 - #/MinBias_TuneP0_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    7 - #/MinBias_TuneDW_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    8 - #/MinBias_TuneD6T_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    9 - #/MinBias_TuneCW_7TeV-pythia6/Fall10-START38_V12-v2/GEN-SIM-RECO

  ***************/
  //int scale_type = 1;

  std::string outputfile;
  TChain *chainA = new TChain("analysisNtuplePAT/AllData");
  if (inputfiles.rfind(".txt")!=string::npos) {
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
	  if (debug) std::cout<<"Adding file: " << pName<<std::endl;
          chainA->Add(pName);
        }
      //output root files
      outputfile = inputfiles.erase(inputfiles.rfind('.'));
      
      size_t firstPAT = string::npos;
      size_t firstInput = string::npos;
      firstPAT   = outputfile.find("PAT");
      firstInput = outputfile.find("input");
      size_t position = outputfile.rfind("/input/inputlist");
      outputfile.erase(position,16);
	
      while (outputfile.find('/')!=string::npos)
	{
	  outputfile.erase(0,outputfile.find('/')+1);
	}
      if (outputfile.find("PATtuple_V9_")!=string::npos)
	outputfile.erase(0,outputfile.find("PATtuple_V9_")+12);
      if (outputfile.find("DATA_")!=string::npos)
	outputfile.erase(0,outputfile.find("DATA_")+5);
      if (outputfile.find("MC_")!=string::npos)
	outputfile.erase(0,outputfile.find("MC_")+3);
      outputfile = outDir + "/" + outputfile+"_out";
    }
    else {
      std::cout << "ERROR opening inputfiles list:" << inputfiles << std::endl;
      exit (1);
    }
  }
  else {
    chainA->Add(inputfiles.c_str());
    outputfile = inputfiles.erase(inputfiles.rfind('.'))+"_out";
  }
  TTree *treeA = chainA;

  std::cout<<"outputfile:"<<outputfile<<
    "  -  isData: "       <<isData<<
    "  -  scale_type: "   <<scale_type<<
    "  -  jets: "         <<jets<<
    "  -  phots: "        <<phots<<
    "  -  doTechTrigs: "  <<doTechTrigs<<
    "  -  debug: "        <<debug<<
    "  -  outDir: "       <<outDir<<std::endl;
    
  METResolutionStudy* analysis = new METResolutionStudy(treeA, isData, jets, phots, doTechTrigs, debug);
  analysis->Loop(outputfile, scale_type);
  std::cout<<"Done with METResolution.exe"<<std::endl;
  //delete treeA;
  delete chainA;
  delete analysis;
}

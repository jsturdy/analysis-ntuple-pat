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
  const int Nparam1=6;   // NUMBER OF PARAMETERS
  for (int thearg = 0; thearg < argc; ++thearg) 
    cout << "  -  "  << argv[thearg];
  cout<<endl;
  if(argc!=Nparam1+1)
    {
      cout << "METResolution() : argc = " << argc << " is different from " << Nparam1+1<<". Exiting." <<endl;
      cout << "Usage  : ./METResolution inputFileList(or input file name) isData scaleType jetPrefix debug outDir" << endl;
      cout << "Example: ./METResolution ntuples.txt 0 1 Calo 0 outputdirectory" << endl;
      cout << "Example: ./METResolution ntuple.root 0 1 PF 0 outputdir" << endl;
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
  bool debug = 0;
  ss3 >> debug;

  std::string phots = "";
  std::string outDir = argv[6];
  
  //scaling recoMET to MC using 
  //0 - FastSim TuneX1
  //1 - FullSim Pythia8
  //2 - FullSim TuneD6T
  //3 - FullSim TuneP0

  /**************

    #/MinBias_TuneZ2_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneProQ20_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneProPT0_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneP0_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneDW_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneD6T_7TeV-pythia6/Fall10-START38_V12-v1/GEN-SIM-RECO
    #/MinBias_TuneCW_7TeV-pythia6/Fall10-START38_V12-v2/GEN-SIM-RECO
    #/MinBias_7TeV-pythia8/Fall10-START38_V12-v1/GEN-SIM-RECO

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
      //if (firstPAT < firstInput)
      //outputfile.erase(outputfile.rfind("/input/inputlist_"));
      //else
      //#outputfile.erase(0,outputfile.find("/input/inputlist_"));
	
      if (debug) std::cout<<"outputfile is: "<<outputfile<<std::endl;
      while (outputfile.find('/')!=string::npos)
	{
	  outputfile.erase(0,outputfile.find('/')+1);
	  if (debug) std::cout<<"outputfile is: "<<outputfile<<std::endl;
	}
      if (debug) std::cout<<"done looping through to find '/', outputfile is: "<<outputfile<<std::endl;
      
      if (outputfile.find("PATtuple_V9_")!=string::npos)
	outputfile.erase(0,outputfile.find("PATtuple_V9_")+12);
      if (debug) std::cout<<"done searching for 'PATtuple_V9_', outputfile is: "<<outputfile<<std::endl;
      if (outputfile.find("DATA_")!=string::npos)
	outputfile.erase(0,outputfile.find("DATA_")+5);
      if (debug) std::cout<<"done searching for 'DATA_', outputfile is: "<<outputfile<<std::endl;
      if (outputfile.find("MC_")!=string::npos)
	outputfile.erase(0,outputfile.find("MC_")+3);
      if (debug) std::cout<<"done searching for 'MC_', outputfile is: "<<outputfile<<std::endl;
      outputfile = outDir + "/" + outputfile+"_out";
      if (debug) std::cout<<"results will be written to "<<outputfile<<std::endl;
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
  
  METResolutionStudy* analysis = new METResolutionStudy(treeA, isData, jets, phots, debug);
  analysis->Loop(outputfile, scale_type);
  std::cout<<"Done with METResolution.exe"<<std::endl;
  //delete treeA;
  delete chainA;
  delete analysis;
}

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include "TFile.h"
#include "TROOT.h" 
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TTree.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TImage.h"
#include "TRandom.h"
#include "TGaxis.h"
#include "TAxis.h"
#include "TCut.h"
#include "TPostScript.h"
#include "TF1.h"
#include "TLeaf.h"
#include <TLegend.h>
#include <TKey.h>

using namespace std;

void makeCutFlow(std::string mettype="CaloMET", std::string jettype="CaloJets", std::string energy="7TeV")
{
  static const int NUMVARS   = 4;
  static const int NUMFILES  = 12;

  //gROOT->SetStyle("Plain");

  TFile* file[NUMFILES];
  TString filenames[NUMFILES];
  
  //TString suffix_ = "_met_jCalomCaloTypeIl";
  TString suffix_ = "_mht_jCalomCaloTypeIl";
  //TString suffix_ = "_full_jCalomCaloTypeIl";
  filenames[0]  = "LM0";
  filenames[1]  = "LM1";
  filenames[2]  = "LM5";
  filenames[3]  = "LM6";
  filenames[4]  = "LM12";
  filenames[5]  = "LM13";
  filenames[6]  = "ZJets-madgraph";
  filenames[7]  = "TTbarJets-madgraph";  
  filenames[8]  = "ZInvisibleJets";
  filenames[9]  = "WJets-madgraph";
  filenames[10] = "QCD_MadGraph_Pt50toInf";
  filenames[11] = "7TeV_Data";
  //filenames2[5]  = "VectorBosons";
  //filenames2[6]  = "SM_Background";


  //filenames[1]  = "Zmumu";
  //filenames[1]  = "Wmunu";
  TString histnames[NUMVARS];
  TString totalevents;
  TH1D*   hist[NUMFILES][NUMVARS];

  histnames[0]  = "h_pre_cuts_events";
  histnames[1]  = "h_individual_cuts_events";
  histnames[2]  = "h_N1_cuts_events";
  histnames[3]  = "h_post_cuts_events";

  TString metTag    = mettype;
  TString jetTag    = jettype;
  TString energyTag = energy;
  
  printf("Cut Series: -  Nevents - preselection - triggers - finaljet - leptonveto - metselection - dphiselection - htselection - mhtselection - dphistarselection\n");
  for (int j = 0; j < NUMFILES; j++) {
    TString filepath = "./MHT_Analysis/"+filenames[j]+suffix_+".root";
    file[j] = new TFile(filepath);
    std::cout<<filenames[j]<<std::endl;
    for (int tt = 0; tt < NUMVARS; tt++) {
      hist[j][tt] = (TH1D*)gDirectory->Get(histnames[tt]);
      double eventvals[9];
      printf("%s  ",std::string(histnames[tt]).c_str());
      printf("-  %2.4f  ",hist[j][tt]->GetBinContent(11));
      for (int bin = 1; bin < 10; ++bin) {
	eventvals[bin-1] = hist[j][tt]->GetBinContent(bin);
	printf("-  %2.4f  ",eventvals[bin-1]);
      }
      printf("\n");
    }
  }
}

#define   METResolutionStudy_cxx
#include "/uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/METResolutionStudy.h"
#include <TMath.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TH2F.h>
#include <TProfile.h>
#include <fstream>
#include <algorithm>
#include <iostream>
//#include <boost/algorithm/string.hpp>
//#include "boost/algorithm/string.hpp"

#include <map>
#include <vector>
#include <string>

using namespace std;

void METResolutionStudy::Loop(const TString& output_filename,
			      const int& scale_type,
			      const std::string& jetTrigger,
			      const int& strictTriggerCheck,
			      const int& strictPVCheck) 
{
  //----------------------------------------------------------
  //Define output file
  //----------------------------------------------------------
  std::cout<<"arguments"<<std::endl;
  std::cout<<"scale_type: "<<scale_type<<std::endl;
  std::cout<<"jetTrigger: "<<jetTrigger<<std::endl;
  std::cout<<"strictTriggerCheck:"<<strictTriggerCheck<<std::endl;
  std::cout<<"strictPVCheck: "<<strictPVCheck<<std::endl;
  

  TString root_name = output_filename+".root";
  TString text_name = output_filename+".txt";
  TFile *outfile = new TFile(root_name.Data(),"RECREATE");
  outfile->cd();
  
  gROOT->ProcessLine(".L /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/ntuplePragmas.so");
  //gROOT->ProcessLine(".L ./ntuplePragmas.so");
  ofstream out;
  
  out.open(text_name.Data(), ios::out | ios::app);
  
  //----------------------------------------------------------
  //Histogram Declarations
  //----------------------------------------------------------
  
  TH1F *h_tcmet_x_v[125];
  TH1F *h_pfmet_x_v[125];
  TH1F *h_type1pfmet_x_v[125];
  TH1F *h_type1calomet_x_v[125];
  TH1F *h_type2calomet_x_v[125];
  
  TH1F *h_tcmet_x_v_reco[125];
  TH1F *h_pfmet_x_v_reco[125];
  TH1F *h_type1pfmet_x_v_reco[125];
  TH1F *h_type1calomet_x_v_reco[125];
  TH1F *h_type2calomet_x_v_reco[125];

  TH1F *h_tcmet_x_v_reco_pf[125];
  TH1F *h_type1calomet_x_v_reco_pf[125];
  TH1F *h_type2calomet_x_v_reco_pf[125];

  TH1F *h_tcmet_x_v_reco_type1pf[125];
  TH1F *h_type1calomet_x_v_reco_type1pf[125];
  TH1F *h_type2calomet_x_v_reco_type1pf[125];

  TH1F *h_tcmet_x_v_reco_type1[125];
  TH1F *h_tcmet_x_v_reco_type2[125];
  TH1F *h_type1calomet_x_v_reco_tc[125];
  TH1F *h_type2calomet_x_v_reco_tc[125];

  TH1F *h_pfmet_x_v_reco_type1[125];
  TH1F *h_pfmet_x_v_reco_type2[125];
  TH1F *h_pfmet_x_v_reco_tc[125];

  TH1F *h_type1pfmet_x_v_reco_type1[125];
  TH1F *h_type1pfmet_x_v_reco_type2[125];
  TH1F *h_type1pfmet_x_v_reco_tc[125];

  TH1F *h_tcmet_x_v_Rescaling[125];
  TH1F *h_pfmet_x_v_Rescaling[125];
  TH1F *h_type1pfmet_x_v_Rescaling[125];
  TH1F *h_type1calomet_x_v_Rescaling[125];
  TH1F *h_type2calomet_x_v_Rescaling[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO[125];
  TH1F *h_type1pfmet_x_v_RescalingMETALSO[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_pf[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type2[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_type2[125];
  TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_type2[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_type2[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type1pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
  TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
  TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];

  TH2F *h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];
  TProfile *hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];
  TH2F *h_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];
  TProfile *hprof_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];

  TH2F *h_type2sumet_vs_type2met_bins_of_pfsumEt[125];
  TProfile *hprof_type2sumet_vs_type2met_bins_of_pfsumEt[125];
  TH2F *h_type2sumet_vs_type2met_bins_of_type1pfsumEt[125];
  TProfile *hprof_type2sumet_vs_type2met_bins_of_type1pfsumEt[125];

  if (debug_) out<<"I get here, beginning of defining array histos "<<endl;

  for(int aii=0;aii<125;++aii) {
    if (debug_) out<<"I get here, beginning of array loop "<<endl;
    h_tcmet_x_v[aii] = new TH1F(Form("h_tcmet_x_%i",aii),"",              500,-250,250);
    h_pfmet_x_v[aii] = new TH1F(Form("h_pfmet_x_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v[aii] = new TH1F(Form("h_type1pfmet_x_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v[aii] = new TH1F(Form("h_type1calomet_x_%i",aii),"",500,-250,250);
    h_type2calomet_x_v[aii] = new TH1F(Form("h_type2calomet_x_%i",aii),"",500,-250,250);

    h_tcmet_x_v_reco[aii] = new TH1F(Form("h_tcmet_x_reco_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_reco[aii] = new TH1F(Form("h_pfmet_x_reco_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_reco[aii] = new TH1F(Form("h_type1pfmet_x_reco_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_reco[aii] = new TH1F(Form("h_type1calomet_x_reco_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_reco[aii] = new TH1F(Form("h_type2calomet_x_reco_%i",aii),"",500,-250,250);

    h_tcmet_x_v_reco_pf[aii] = new TH1F(Form("h_tcmet_x_reco_pf_%i",aii),"",              500,-250,250);
    h_type1calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type1calomet_x_reco_pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type2calomet_x_reco_pf_%i",aii),"",500,-250,250);
    h_type1calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type1calomet_x_reco_tc_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type2calomet_x_reco_tc_%i",aii),"",500,-250,250);

    h_tcmet_x_v_reco_type1pf[aii] = new TH1F(Form("h_tcmet_x_reco_type1pf_%i",aii),"",              500,-250,250);
    h_type1calomet_x_v_reco_type1pf[aii] = new TH1F(Form("h_type1calomet_x_reco_type1pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_reco_type1pf[aii] = new TH1F(Form("h_type2calomet_x_reco_type1pf_%i",aii),"",500,-250,250);

    h_tcmet_x_v_reco_type1[aii] = new TH1F(Form("h_tcmet_x_reco_type1_%i",aii),"",          500,-250,250);
    h_tcmet_x_v_reco_type2[aii] = new TH1F(Form("h_tcmet_x_reco_type2_%i",aii),"",          500,-250,250);
    h_pfmet_x_v_reco_type1[aii] = new TH1F(Form("h_pfmet_x_reco_type1_%i",aii),"",          500,-250,250);
    h_pfmet_x_v_reco_type2[aii] = new TH1F(Form("h_pfmet_x_reco_type2_%i",aii),"",          500,-250,250);
    h_type1pfmet_x_v_reco_type1[aii] = new TH1F(Form("h_type1pfmet_x_reco_type1_%i",aii),"",500,-250,250);
    h_type1pfmet_x_v_reco_type2[aii] = new TH1F(Form("h_type1pfmet_x_reco_type2_%i",aii),"",500,-250,250);

    h_pfmet_x_v_reco_tc[aii] = new TH1F(Form("h_pfmet_x_reco_tc_%i",aii),"",          500,-250,250);
    h_type1pfmet_x_v_reco_tc[aii] = new TH1F(Form("h_type1pfmet_x_reco_tc_%i",aii),"",500,-250,250);

    h_tcmet_x_v_Rescaling[aii] = new TH1F(Form("h_tcmet_x_Rescaling_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_Rescaling[aii] = new TH1F(Form("h_pfmet_x_Rescaling_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_Rescaling[aii] = new TH1F(Form("h_type1pfmet_x_Rescaling_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type1calomet_x_Rescaling_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type2calomet_x_Rescaling_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type1pfmet_x_RescalingMETALSO_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii),"",              500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_type2[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_type2_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_RescalingMETALSO_vs_type2[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_type2_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii] = new TH1F(Form("h_type1pfmet_x_RescalingMETALSO_vs_type2_%i",aii),"",500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_type2[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_type2_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_type1pf_%i",aii),"",              500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_type1pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_type1pf_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = new TH1F(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii),"",500,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii),"",              500,-250,250);
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii),"",              500,-250,250);
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = new TH1F(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii),"",    500,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii),"",500,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii),"",500,-250,250);

    if (debug_) out<<"I get here, near end of single array loop "<<endl;

    h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TH2F(Form("h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",                      100,0,500,100,0,500);
    hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TProfile(Form("hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",          50,0,250,0,500);
    h_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TH2F(Form("h_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",            100,0,500,100,0,500);
    hprof_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TProfile(Form("hprof_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",50,0,250,0,500);

    h_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TH2F(Form("h_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",                      100,0,500,100,0,500);
    hprof_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TProfile(Form("hprof_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",          50,0,250,0,500);
    h_type2sumet_vs_type2met_bins_of_type1pfsumEt[aii] = new TH2F(Form("h_type2sumet_vs_type2met_bins_of_type1pfsumEt_%i",aii),"",            100,0,500,100,0,500);
    hprof_type2sumet_vs_type2met_bins_of_type1pfsumEt[aii] = new TProfile(Form("hprof_type2sumet_vs_type2met_bins_of_type1pfsumEt_%i",aii),"",50,0,250,0,500);

    if (debug_) out<<"I get here, end of single array loop "<<endl;
  }

  ///
  for(int aii=0;aii<125;++aii) {
    h_tcmet_x_v[aii]->Sumw2();
    h_pfmet_x_v[aii]->Sumw2();
    h_type1pfmet_x_v[aii]->Sumw2();
    h_type1calomet_x_v[aii]->Sumw2();
    h_type2calomet_x_v[aii]->Sumw2();

    h_tcmet_x_v_reco[aii]->Sumw2();
    h_pfmet_x_v_reco[aii]->Sumw2();
    h_type1pfmet_x_v_reco[aii]->Sumw2();
    h_type1calomet_x_v_reco[aii]->Sumw2();
    h_type2calomet_x_v_reco[aii]->Sumw2();

    h_tcmet_x_v_reco_pf[aii]->Sumw2();
    h_type1calomet_x_v_reco_pf[aii]->Sumw2();
    h_type2calomet_x_v_reco_pf[aii]->Sumw2();
    h_type1calomet_x_v_reco_tc[aii]->Sumw2();
    h_type2calomet_x_v_reco_tc[aii]->Sumw2();

    h_tcmet_x_v_reco_type1pf[aii]->Sumw2();
    h_type1calomet_x_v_reco_type1pf[aii]->Sumw2();
    h_type2calomet_x_v_reco_type1pf[aii]->Sumw2();

    h_tcmet_x_v_reco_type1[aii]->Sumw2();
    h_tcmet_x_v_reco_type2[aii]->Sumw2();
    h_pfmet_x_v_reco_type1[aii]->Sumw2();
    h_pfmet_x_v_reco_type2[aii]->Sumw2();
    h_type1pfmet_x_v_reco_type1[aii]->Sumw2();
    h_type1pfmet_x_v_reco_type2[aii]->Sumw2();

    h_pfmet_x_v_reco_tc[aii]->Sumw2();
    h_type1pfmet_x_v_reco_tc[aii]->Sumw2();

    h_tcmet_x_v_Rescaling[aii]->Sumw2();
    h_pfmet_x_v_Rescaling[aii]->Sumw2();
    h_type1pfmet_x_v_Rescaling[aii]->Sumw2();
    h_type1calomet_x_v_Rescaling[aii]->Sumw2();
    h_type2calomet_x_v_Rescaling[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO[aii]->Sumw2();
    h_pfmet_x_v_RescalingMETALSO[aii]->Sumw2();
    h_type1pfmet_x_v_RescalingMETALSO[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Sumw2();
    h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Sumw2();
    h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_type2[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Sumw2();
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Sumw2();
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Sumw2();
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Sumw2();
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Sumw2();

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Sumw2();
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Sumw2();
    h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Sumw2();
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Sumw2();
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Sumw2();

    h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii]->Sumw2();
    h_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii]->Sumw2();

    h_type2sumet_vs_type2met_bins_of_pfsumEt[aii]->Sumw2();
    h_type2sumet_vs_type2met_bins_of_type1pfsumEt[aii]->Sumw2();

  }
  ///
  if (debug_) out<<"I get here, end of defining array histos "<<endl;

  TH1F *h_tcMET        = new TH1F("h_tcMET","",       500,0,500);
  TH1F *h_pfMET        = new TH1F("h_pfMET","",       500,0,500);
  TH1F *h_type1pfMET   = new TH1F("h_type1pfMET","",  500,0,500);
  TH1F *h_type1caloMET = new TH1F("h_type1caloMET","",500,0,500);
  TH1F *h_type2caloMET = new TH1F("h_type2caloMET","",500,0,500);

  TH2F *h_tcMET_vs_pfMET             = new TH2F("h_tcMET_vs_pfMET","",            500,0,500,500,0,500);
  TH2F *h_tcMET_vs_type1pfMET        = new TH2F("h_tcMET_vs_type1pfMET","",       500,0,500,500,0,500);
  TH2F *h_tcMET_vs_type1caloMET      = new TH2F("h_tcMET_vs_type1caloMET","",     500,0,500,500,0,500);
  TH2F *h_pfMET_vs_type1caloMET      = new TH2F("h_pfMET_vs_type1caloMET","",     500,0,500,500,0,500);
  TH2F *h_type1pfMET_vs_type1caloMET = new TH2F("h_type1pfMET_vs_type1caloMET","",500,0,500,500,0,500);
  TH2F *h_tcMET_vs_type2caloMET      = new TH2F("h_tcMET_vs_type2caloMET","",     500,0,500,500,0,500);
  TH2F *h_pfMET_vs_type2caloMET      = new TH2F("h_pfMET_vs_type2caloMET","",     500,0,500,500,0,500);
  TH2F *h_type1pfMET_vs_type2caloMET = new TH2F("h_type1pfMET_vs_type2caloMET","",500,0,500,500,0,500);

  TH1F *h_tcSUMET        = new TH1F("h_tcSUMET","",       1000,0,2500);
  TH1F *h_pfSUMET        = new TH1F("h_pfSUMET","",       1000,0,2500);
  TH1F *h_type1pfSUMET   = new TH1F("h_type1pfSUMET","",  1000,0,2500);
  TH1F *h_type1caloSUMET = new TH1F("h_type1caloSUMET","",1000,0,2500);
  TH1F *h_type2caloSUMET = new TH1F("h_type2caloSUMET","",1000,0,2500);

  TH2F *h_tcSUMET_vs_pfSUMET             = new TH2F("h_tcSUMET_vs_pfSUMET","",            1000,0,2500,1000,0,2500);
  TH2F *h_tcSUMET_vs_type1pfSUMET        = new TH2F("h_tcSUMET_vs_type1pfSUMET","",       1000,0,2500,1000,0,2500);
  TH2F *h_tcSUMET_vs_type1caloSUMET      = new TH2F("h_tcSUMET_vs_type1caloSUMET","",     1000,0,2500,1000,0,2500);
  TH2F *h_pfSUMET_vs_type1caloSUMET      = new TH2F("h_pfSUMET_vs_type1caloSUMET","",     1000,0,2500,1000,0,2500);
  TH2F *h_type1pfSUMET_vs_type1caloSUMET = new TH2F("h_type1pfSUMET_vs_type1caloSUMET","",1000,0,2500,1000,0,2500);
  TH2F *h_tcSUMET_vs_type2caloSUMET      = new TH2F("h_tcSUMET_vs_type2caloSUMET","",     1000,0,2500,1000,0,2500);
  TH2F *h_pfSUMET_vs_type2caloSUMET      = new TH2F("h_pfSUMET_vs_type2caloSUMET","",     1000,0,2500,1000,0,2500);
  TH2F *h_type1pfSUMET_vs_type2caloSUMET = new TH2F("h_type1pfSUMET_vs_type2caloSUMET","",1000,0,2500,1000,0,2500);
   
  TH2F *h_tcMET_vs_RescaledSUMET      = new TH2F("h_tcMET_vs_RescaledSUMET","",     1000,0,2500,500,0,500);
  TH2F *h_tcMET_vs_RescaledType1SUMET = new TH2F("h_tcMET_vs_RescaledType1SUMET","",1000,0,2500,500,0,500);
  TH2F *h_tcMET_vs_genCaloSUMET       = new TH2F("h_tcMET_vs_genCaloSUMET" ,"",     1000,0,2500,500,0,500);

  TH2F *h_pfMET_vs_RescaledSUMET      = new TH2F("h_pfMET_vs_RescaledSUMET","",     1000,0,2500,500,0,500);
  TH2F *h_pfMET_vs_RescaledType1SUMET = new TH2F("h_pfMET_vs_RescaledType1SUMET","",1000,0,2500,500,0,500);
  TH2F *h_pfMET_vs_genCaloSUMET       = new TH2F("h_pfMET_vs_genCaloSUMET" ,"",     1000,0,2500,500,0,500);

  TH2F *h_type1pfMET_vs_RescaledSUMET      = new TH2F("h_type1pfMET_vs_RescaledSUMET","",     1000,0,2500,500,0,500);
  TH2F *h_type1pfMET_vs_RescaledType1SUMET = new TH2F("h_type1pfMET_vs_RescaledType1SUMET","",1000,0,2500,500,0,500);
  TH2F *h_type1pfMET_vs_genCaloSUMET       = new TH2F("h_type1pfMET_vs_genCaloSUMET" ,"",     1000,0,2500,500,0,500);

  TH2F *h_type1MET_vs_RescaledSUMET      = new TH2F("h_type1MET_vs_RescaledSUMET","",     1000,0,2500,500,0,500);
  TH2F *h_type1MET_vs_RescaledType1SUMET = new TH2F("h_type1MET_vs_RescaledType1SUMET","",1000,0,2500,500,0,500);
  TH2F *h_type1MET_vs_genCaloSUMET       = new TH2F("h_type1MET_vs_genCaloSUMET" ,"",     1000,0,2500,500,0,500);

  TH2F *h_type2MET_vs_RescaledSUMET      = new TH2F("h_type2MET_vs_RescaledSUMET","",     1000,0,2500,500,0,500);
  TH2F *h_type2MET_vs_RescaledType1SUMET = new TH2F("h_type2MET_vs_RescaledType1SUMET","",1000,0,2500,500,0,500);
  TH2F *h_type2MET_vs_genCaloSUMET       = new TH2F("h_type2MET_vs_genCaloSUMET" ,"",     1000,0,2500,500,0,500);

  ////scaling properly
  h_tcMET->Sumw2();
  h_pfMET->Sumw2();
  h_type1pfMET->Sumw2();
  h_type1caloMET->Sumw2();
  h_type2caloMET->Sumw2();

  h_tcMET_vs_pfMET->Sumw2();
  h_tcMET_vs_type1pfMET->Sumw2();
  h_tcMET_vs_type1caloMET      ->Sumw2();
  h_pfMET_vs_type1caloMET      ->Sumw2();
  h_type1pfMET_vs_type1caloMET ->Sumw2();
  h_tcMET_vs_type2caloMET      ->Sumw2();
  h_pfMET_vs_type2caloMET      ->Sumw2();
  h_type1pfMET_vs_type2caloMET ->Sumw2();

  h_tcSUMET        ->Sumw2();
  h_pfSUMET        ->Sumw2();
  h_type1pfSUMET   ->Sumw2();
  h_type1caloSUMET ->Sumw2();
  h_type2caloSUMET ->Sumw2();

  h_tcSUMET_vs_pfSUMET             ->Sumw2();
  h_tcSUMET_vs_type1pfSUMET        ->Sumw2();
  h_tcSUMET_vs_type1caloSUMET      ->Sumw2();
  h_pfSUMET_vs_type1caloSUMET      ->Sumw2();
  h_type1pfSUMET_vs_type1caloSUMET ->Sumw2();
  h_tcSUMET_vs_type2caloSUMET      ->Sumw2();
  h_pfSUMET_vs_type2caloSUMET      ->Sumw2();
  h_type1pfSUMET_vs_type2caloSUMET ->Sumw2();
  
  h_tcMET_vs_RescaledSUMET      ->Sumw2();
  h_tcMET_vs_RescaledType1SUMET ->Sumw2();
  h_tcMET_vs_genCaloSUMET       ->Sumw2();

  h_pfMET_vs_RescaledSUMET      ->Sumw2();
  h_pfMET_vs_RescaledType1SUMET ->Sumw2();
  h_pfMET_vs_genCaloSUMET       ->Sumw2();

  h_type1pfMET_vs_RescaledSUMET      ->Sumw2();
  h_type1pfMET_vs_RescaledType1SUMET ->Sumw2();
  h_type1pfMET_vs_genCaloSUMET       ->Sumw2();

  h_type1MET_vs_RescaledSUMET      ->Sumw2();
  h_type1MET_vs_RescaledType1SUMET ->Sumw2();
  h_type1MET_vs_genCaloSUMET       ->Sumw2();

  h_type2MET_vs_RescaledSUMET      ->Sumw2();
  h_type2MET_vs_RescaledType1SUMET ->Sumw2();
  h_type2MET_vs_genCaloSUMET       ->Sumw2();
  //////////////////////////Histograms for running on MC////////////////////////
   
  TH1F *h_genMETCalo   = NULL;
  TH1F *h_genSUMETCalo = NULL;
  //TH1F *h_genMETTrue   = NULL;
  //TH1F *h_genSUMETTrue = NULL;

  TH2F *h_genMETCalo_vs_pfMET        = NULL;
  TH2F *h_genMETCalo_vs_type1pfMET   = NULL;
  TH2F *h_genMETCalo_vs_tcMET        = NULL;
  TH2F *h_genMETCalo_vs_type1caloMET = NULL;
  TH2F *h_genMETCalo_vs_type2caloMET = NULL;
   
  TH2F *h_pfSUMET_vs_genSUMETCalo        = NULL;
  TH2F *h_type1pfSUMET_vs_genSUMETCalo   = NULL;
  TH2F *h_tcSUMET_vs_genSUMETCalo        = NULL;
  TH2F *h_type1caloSUMET_vs_genSUMETCalo = NULL;
  TH2F *h_type2caloSUMET_vs_genSUMETCalo = NULL;

  TProfile *hprof_tcsumet_vs_calogensumet      = NULL;
  TProfile *hprof_pfsumet_vs_calogensumet      = NULL;
  TProfile *hprof_type1pfsumet_vs_calogensumet = NULL;
  TProfile *hprof_type1sumet_vs_calogensumet   = NULL;
  TProfile *hprof_type2sumet_vs_calogensumet   = NULL;
   
  //if (!isData_) {
  h_genMETCalo = new TH1F("h_genMETCalo","",    100,0,500);
  h_genSUMETCalo = new TH1F("h_genSUMETCalo","",500,0,2500);
  
  h_genMETCalo_vs_pfMET = new TH2F("h_genMETCalo_vs_pfMET","",              100,0,500,100,0,500);
  h_genMETCalo_vs_type1pfMET = new TH2F("h_genMETCalo_vs_type1pfMET","",    100,0,500,100,0,500);
  h_genMETCalo_vs_tcMET = new TH2F("h_genMETCalo_vs_tcMET","",              100,0,500,100,0,500);
  h_genMETCalo_vs_type1caloMET = new TH2F("h_genMETCalo_vs_type1caloMET","",100,0,500,100,0,500);
  h_genMETCalo_vs_type2caloMET = new TH2F("h_genMETCalo_vs_type2caloMET","",100,0,500,100,0,500);
  
  h_pfSUMET_vs_genSUMETCalo = new TH2F("h_pfSUMET_vs_genSUMETCalo","",              500,0,2500,500,0,2500);
  h_type1pfSUMET_vs_genSUMETCalo = new TH2F("h_type1pfSUMET_vs_genSUMETCalo","",    500,0,2500,500,0,2500);
  h_tcSUMET_vs_genSUMETCalo = new TH2F("h_tcSUMET_vs_genSUMETCalo","",              500,0,2500,500,0,2500);
  h_type1caloSUMET_vs_genSUMETCalo = new TH2F("h_type1caloSUMET_vs_genSUMETCalo","",500,0,2500,500,0,2500);
  h_type2caloSUMET_vs_genSUMETCalo = new TH2F("h_type2caloSUMET_vs_genSUMETCalo","",500,0,2500,500,0,2500);
  
  hprof_tcsumet_vs_calogensumet  = new TProfile("hprof_tcsumet_vs_calogensumet","Profile of tcsumet vs. calogensumet",               125,0,2500,0,2500);
  hprof_pfsumet_vs_calogensumet  = new TProfile("hprof_pfsumet_vs_calogensumet","Profile of pfsumet vs. calogensumet",               125,0,2500,0,2500);
  hprof_type1pfsumet_vs_calogensumet  = new TProfile("hprof_type1pfsumet_vs_calogensumet","Profile of type1pfsumet vs. calogensumet",125,0,2500,0,2500);
  hprof_type1sumet_vs_calogensumet  = new TProfile("hprof_type1sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet", 125,0,2500,0,2500);
  hprof_type2sumet_vs_calogensumet  = new TProfile("hprof_type2sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet", 125,0,2500,0,2500);
  
  /////scaling
  h_genMETCalo->Sumw2();
  h_genSUMETCalo->Sumw2();
  
  h_genMETCalo_vs_pfMET ->Sumw2();
  h_genMETCalo_vs_type1pfMET ->Sumw2();
  h_genMETCalo_vs_tcMET ->Sumw2();
  h_genMETCalo_vs_type1caloMET ->Sumw2();
  h_genMETCalo_vs_type2caloMET ->Sumw2();
  
  h_pfSUMET_vs_genSUMETCalo ->Sumw2();
  h_type1pfSUMET_vs_genSUMETCalo ->Sumw2();
  h_tcSUMET_vs_genSUMETCalo ->Sumw2();
  h_type1caloSUMET_vs_genSUMETCalo ->Sumw2();
  h_type2caloSUMET_vs_genSUMETCalo ->Sumw2();
  
  //}
  
  TH2F *h_pfsumet_vs_dijetavg = new TH2F("h_pfsumet_vs_dijetavg","",          100,0,500,100,0,5);
  TH2F *h_type1pfsumet_vs_dijetavg = new TH2F("h_type1pfsumet_vs_dijetavg","",100,0,500,100,0,5);
  TH2F *h_tcsumet_vs_dijetavg = new TH2F("h_tcsumet_vs_dijetavg","",          100,0,500,100,0,5);
  TH2F *h_type1sumet_vs_dijetavg = new TH2F("h_type1sumet_vs_dijetavg","",    100,0,500,100,0,5);
  TH2F *h_type2sumet_vs_dijetavg = new TH2F("h_type2sumet_vs_dijetavg","",    100,0,500,100,0,5);

  TProfile *hprof_tcsumet_vs_dijetavg      = new TProfile("hprof_tcsumet_vs_dijetavg","Profile of tcsumet vs. dijetavg",           50,0,250,0,10);
  TProfile *hprof_pfsumet_vs_dijetavg      = new TProfile("hprof_pfsumet_vs_dijetavg","Profile of pfsumet vs. dijetavg",           50,0,250,0,10);
  TProfile *hprof_type1pfsumet_vs_dijetavg = new TProfile("hprof_type1pfsumet_vs_dijetavg","Profile of type1pfsumet vs. dijetavg", 50,0,250,0,10);
  TProfile *hprof_type1sumet_vs_dijetavg   = new TProfile("hprof_type1sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",50,0,250,0,10);
  TProfile *hprof_type2sumet_vs_dijetavg   = new TProfile("hprof_type2sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",50,0,250,0,10);

  TH2F *h_pfmet_vs_dijetavg      = new TH2F("h_pfmet_vs_dijetavg","",     100,0,500,100,0,5);
  TH2F *h_type1pfmet_vs_dijetavg = new TH2F("h_type1pfmet_vs_dijetavg","",100,0,500,100,0,5);
  TH2F *h_tcmet_vs_dijetavg      = new TH2F("h_tcmet_vs_dijetavg","",     100,0,500,100,0,5);
  TH2F *h_type1met_vs_dijetavg   = new TH2F("h_type1met_vs_dijetavg","",  100,0,500,100,0,5);
  TH2F *h_type2met_vs_dijetavg   = new TH2F("h_type2met_vs_dijetavg","",  100,0,500,100,0,5);

  TProfile *hprof_tcmet_vs_dijetavg      = new TProfile("hprof_tcmet_vs_dijetavg","Profile of tcmet vs. dijetavg",           50,0,250,0,10);
  TProfile *hprof_pfmet_vs_dijetavg      = new TProfile("hprof_pfmet_vs_dijetavg","Profile of pfmet vs. dijetavg",           50,0,250,0,10);
  TProfile *hprof_type1pfmet_vs_dijetavg = new TProfile("hprof_type1pfmet_vs_dijetavg","Profile of type1pfmet vs. dijetavg", 50,0,250,0,10);
  TProfile *hprof_type1met_vs_dijetavg   = new TProfile("hprof_type1met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",50,0,250,0,10);
  TProfile *hprof_type2met_vs_dijetavg   = new TProfile("hprof_type2met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",50,0,250,0,10);

  ////scaled

  h_pfsumet_vs_dijetavg ->Sumw2();
  h_type1pfsumet_vs_dijetavg->Sumw2();
  h_tcsumet_vs_dijetavg->Sumw2();
  h_type1sumet_vs_dijetavg ->Sumw2();
  h_type2sumet_vs_dijetavg ->Sumw2();

  h_pfmet_vs_dijetavg      ->Sumw2();
  h_type1pfmet_vs_dijetavg ->Sumw2();
  h_tcmet_vs_dijetavg      ->Sumw2();
  h_type1met_vs_dijetavg   ->Sumw2();
  h_type2met_vs_dijetavg   ->Sumw2();

  ///

  //----------------------------------------------------------
  //Initializing variables to count events passing certain requirements
  //----------------------------------------------------------
  //double bins[51] = {
  double bins[126] = {
    0,20,40,60,80,
    100,120,140,160,180,
    200,220,240,260,280,
    300,320,340,360,380,
    400,420,440,460,480,
    500,520,540,560,580,
    600,620,640,660,680,
    700,720,740,760,780,
    800,820,840,860,880,
    900,920,940,960,980,
    //1000,
    1000,1020,1040,1060,1080,
    1100,1120,1140,1160,1180,
    1200,1220,1240,1260,1280,
    1300,1320,1340,1360,1380,
    1400,1420,1440,1460,1480,
    1500,1520,1540,1560,1580,
    1600,1620,1640,1660,1680,
    1700,1720,1740,1760,1780,
    1800,1820,1840,1860,1880,
    1900,1920,1940,1960,1980,

    2000,2020,2040,2060,2080,
    2100,2120,2140,2160,2180,
    2200,2220,2240,2260,2280,
    2300,2320,2340,2360,2380,
    2400,2420,2440,2460,2480,
    //2500
    10000
  };
  
  
  //----------------------------------------------------------     
  //Number of events to loop over
  //----------------------------------------------------------
  if (debug_) cout<<"Getting the entries from the tree"<<endl;
  Int_t nentries = (Int_t)fChain->GetEntries();
  //Long64_t nentries = fChain->GetEntriesFast();
  out<<"The number of entries is: "<<nentries<<endl;
  if (debug_) cout<<"The number of entries is: "<<nentries<<endl;
   
  //----------------------------------------------------------
  //Main Event loop
  //----------------------------------------------------------
  int counting_number_events_passing_cuts = 0;
  int count_number_events_processed = 0;
  int count_number_jettrigger = 0;
  int count_number_dijet = 0;
  int count_number_pv = 0;
  //int count_number_trigger = 0;
  //int tmpRun = -9999;
  for(int ia = 0; ia<nentries;++ia) {
    //for(int ia = 0; ia<200000;++ia) {
    //for(int ia = 0; ia<500;++ia) {
    
    if (debug_) cout<<"trying to get entry "<<ia<<"... ";
    
    if (fChain->GetEntry(ia)) {
      if (debug_) cout<<"success!"<<endl;

      ////if (Run != tmpRun ) {
      //std::cout<<"Run #"<<Run<<std::endl;

      ++count_number_events_processed;

      bool techBeamHalo = false;
      bool jetTrigs     = false;
      bool jet15uTrigs  = false;
      bool jet30uTrigs  = false;
      bool jet50uTrigs  = false;
      bool jet70uTrigs  = false;
      bool jet100uTrigs = false;
      bool jet140uTrigs = false;
    
      
      //Trigger selection                                                                                                                                      
      std::string singlejetTriggerPath;

      std::map<int,std::string>::iterator key = singlejetTriggers.begin();
      while (key != singlejetTriggers.end() ) {
	if (Run < key->first) {
	  singlejetTriggerPath = key->second;
	  if (debug_) std::cout<<"Run::"<<Run<<" using HLT path::"<<singlejetTriggerPath<<std::endl;
	  break;
	}
	++key;
      }


      stringtobool::iterator jetBits;
      stringtoint::iterator  jetPres;

      if (debug_) std::cout<<"HLTTriggered::"<<HLTTriggered<<std::endl;
      if (debug_) std::cout<<"HLTPrescaled::"<<HLTPrescaled<<std::endl;

      //Jet15U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet15u")) {
      if (jetTrigger=="all" || jetTrigger=="jet15u" || jetTrigger=="All" || jetTrigger=="Jet15U" ) {
	jetBits = HLTTriggered->find("HLT_Jet15U");
	jetPres = HLTPrescaled->find("HLT_Jet15U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet15U";
	  if (jetBits->second)
	    jet15uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet15U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet15U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet15U_v1";
	  if (jetBits->second)
	    jet15uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet15U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet15U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet15U_v2";
	  if (jetBits->second)
	    jet15uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet15U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet15U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet15U_v3";
	  if (jetBits->second)
	    jet15uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      //Jet30U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet30u")) {
      if (jetTrigger=="all" || jetTrigger=="jet30u" || jetTrigger=="All" || jetTrigger=="Jet30U" ) {
	jetBits = HLTTriggered->find("HLT_Jet30U");
	jetPres = HLTPrescaled->find("HLT_Jet30U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet30U";
	  if (jetBits->second)
	    jet30uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet30U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet30U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet30U_v1";
	  if (jetBits->second)
	    jet30uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet30U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet30U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet30U_v2";
	  if (jetBits->second)
	    jet30uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet30U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet30U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet30U_v3";
	  if (jetBits->second)
	    jet30uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      //Jet50U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet50u")) {
      if (jetTrigger=="all" || jetTrigger=="jet50u" || jetTrigger=="All" || jetTrigger=="Jet50U" ) {
	jetBits = HLTTriggered->find("HLT_Jet50U");
	jetPres = HLTPrescaled->find("HLT_Jet50U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet50U";
	  if (jetBits->second)
	    jet50uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet50U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet50U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet50U_v1";
	  if (jetBits->second)
	    jet50uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet50U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet50U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet50U_v2";
	  if (jetBits->second)
	    jet50uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet50U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet50U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet50U_v3";
	  if (jetBits->second)
	    jet50uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      //Jet70U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet70u")) {
      if (jetTrigger=="all" || jetTrigger=="jet70u" || jetTrigger=="All" || jetTrigger=="Jet70U" ) {
	jetBits = HLTTriggered->find("HLT_Jet70U");
	jetPres = HLTPrescaled->find("HLT_Jet70U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet70U";
	  if (jetBits->second)
	    jet70uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet70U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet70U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet70U_v1";
	  if (jetBits->second)
	    jet70uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet70U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet70U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet70U_v2";
	  if (jetBits->second)
	    jet70uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet70U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet70U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet70U_v3";
	  if (jetBits->second)
	    jet70uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      //Jet100U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet100u")) {
      if (jetTrigger=="all" || jetTrigger=="jet100u" || jetTrigger=="All" || jetTrigger=="Jet100U" ) {
	jetBits = HLTTriggered->find("HLT_Jet100U");
	jetPres = HLTPrescaled->find("HLT_Jet100U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet100U";
	  if (jetBits->second)
	    jet100uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet100U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet100U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet100U_v1";
	  if (jetBits->second)
	    jet100uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet100U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet100U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet100U_v2";
	  if (jetBits->second)
	    jet100uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet100U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet100U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet100U_v3";
	  if (jetBits->second)
	    jet100uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      //Jet140U Triggers
      //if (boost::algorithms::iequals(jetTrigger,"all") || boost::algorithms::iequals(jetTrigger,"jet140u")) {
      if (jetTrigger=="all" || jetTrigger=="jet140u" || jetTrigger=="All" || jetTrigger=="Jet140U" ) {
	jetBits = HLTTriggered->find("HLT_Jet140U");
	jetPres = HLTPrescaled->find("HLT_Jet140U");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet140U";
	  if (jetBits->second)
	    jet140uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet140U_v1");
	jetPres = HLTPrescaled->find("HLT_Jet140U_v1");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet140U_v1";
	  if (jetBits->second)
	    jet140uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet140U_v2");
	jetPres = HLTPrescaled->find("HLT_Jet140U_v2");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet140U_v2";
	  if (jetBits->second)
	    jet140uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
	jetBits = HLTTriggered->find("HLT_Jet140U_v3");
	jetPres = HLTPrescaled->find("HLT_Jet140U_v3");
	if (jetBits!=HLTTriggered->end()) {
	  if (debug_) std::cout<<"Found HLT_Jet140U_v3";
	  if (jetBits->second)
	    jet140uTrigs = true;
	  if (debug_) std::cout<<" with result: "<<jetBits->second<<" and prescale "<<jetPres->second<<std::endl;
	}
      }

      bool expType=true;
      if(expType) {
      
	int numPVs = 0;
	if (debug_) std::cout<<"looping over vertex collection"<<std::endl;
	for (int vtx = 0; vtx < nVtx; ++vtx) {
	  if (debug_) std::cout<<"vertex number "<<vtx;
	  if (Vertexd0->at(vtx) <= 2.)
	    if (VertexNdof->at(vtx) >=4)
	      if (fabs(VertexZ->at(vtx)) <= 24.){
		if (debug_) std::cout<<" is PV";
		++numPVs;
	      }
	  if (debug_) std::cout<<std::endl;
	}
      
	if (debug_) std::cout<<"vertex, nVtx = "<<nVtx<<"  numPVs = "<<numPVs<<std::endl;
	//++count_number_trigger;
       
	int count_number_jets = 0;
	double first_highest_jet_pt  = -999;
	int first_highest_location   = -999;
	double second_highest_jet_pt = -999;

	if (debug_) cout<<"Run: "<<Run<<", looping over the "<<NJets<<" jets to find the highest pt jet"<<endl;
      
	for(int aia = 0;aia<NJets;++aia) {
	  //if (debug_) cout<<"jet "<<aia;
	  //do JetID here?
	  //if(!JetIDLoose->at(aia))
	  if(fabs(JetP4->at(aia).Eta())<3)
	    if (JetP4->at(aia).Pt()>25) {
	      if (debug_) cout<<", passed minimal eta/pt cuts ";
	      if (debug_) printf(": pt: %2.2f  eta: %2.2f\n",JetP4->at(aia).Pt(), JetP4->at(aia).Eta());
	      if(!JetIDLoose->at(aia))
		if (debug_) cout<<"There is a problem with jet Id"<<endl;
	    
	      if (JetIDLoose->at(aia)) {
		if (debug_) cout<<"jet "<<aia<<" passed all requirements, now ordering first"<<std::endl;
		++count_number_jets;     
		if(JetP4->at(aia).Pt()>first_highest_jet_pt) {
		  if (debug_) cout<<", is highest pt jet encountered ";
		  first_highest_jet_pt=JetP4->at(aia).Pt();
		  first_highest_location=aia;
		  if (debug_) cout<<endl;
		}//end of looking for highest pt jet
	      }//end loose jetID requirement
	    }//if requirement for pt and eta
	}//end of for loop over jets
      
	//if (debug_) cout<<"looping over the jets to find the 2nd highest pt jet"<<endl;
	for(int aia = 0;aia<NJets;++aia) {
	  if (debug_)
	    std::cout<<"looping for the second time over the jets"<<std::endl;
	  //if (debug_) cout<<"jet "<<aia<<endl;
	  if(fabs(JetP4->at(aia).Eta())<3&&JetP4->at(aia).Pt()>25) {
	    if (debug_) printf(": pt: %2.2f  eta: %2.2f\n",JetP4->at(aia).Pt(), JetP4->at(aia).Eta());
	    if(!JetIDLoose->at(aia))
	      if (debug_) cout<<"There is a problem with jet Id"<<endl;
	    if (JetIDLoose->at(aia)) {
	      if (debug_) cout<<"jet "<<aia<<" passed all requirements, now ordering second"<<std::endl;
	      if(aia!=first_highest_location&&JetP4->at(aia).Pt()>second_highest_jet_pt) {
		second_highest_jet_pt=JetP4->at(aia).Pt();
	      }//end of looking for highest pt jet
	    }//end loose jetID requirement
	  }//if requirement for pt and eta
	}//end of for loop over jets
      
	if (count_number_jets>1) {
	  if (debug_) {
	    std::cout<<"first_highest_jet_pt: "<<first_highest_jet_pt<<std::endl;
	    std::cout<<"second_highest_jet_pt: "<<second_highest_jet_pt<<std::endl;
	  }
	}
	double dijet_avg = (first_highest_jet_pt+second_highest_jet_pt)/2;

	// set up the SumET so it can be used for trigger selection
	double tcmet   = 0; 
	double tcsumet = 0;
	double tcmet_x = 0;
	double tcmet_y = 0;
	double tcphi   = -999;
	
	double pfmet   = 0; 
	double pfsumet = 0; 
	double pfmet_x = 0; 
	double pfmet_y = 0; 
	double pfphi   = -999;
	
	double type1pfmet   = 0; 
	double type1pfsumet = 0; 
	double type1pfmet_x = 0; 
	double type1pfmet_y = 0; 
	double type1pfphi   = -999;
	
	double type1calomet   = 0; 
	double type1calosumet = 0; 
	double type1calomet_x = 0; 
	double type1calomet_y = 0; 
	double type1calophi   = -999;
	
	double type2calomet   = 0; 
	double type2calosumet = 0; 
	double type2calomet_x = 0; 
	double type2calomet_y = 0; 
	double type2calophi   = -999;
	
	double calogenmet   = -999; 
	double calogenmetet = -999; 
	
	tcphi   = TCMETP4->Phi();
	tcmet   = TCMETP4->Pt();
	tcsumet = TCMETsumEt;
	tcmet_x = TCMETP4->Px();
	tcmet_y = TCMETP4->Py();
	
	pfphi   = PFMETP4->Phi();
	pfmet   = PFMETP4->Pt();
	pfsumet = PFMETsumEt;
	pfmet_x = PFMETP4->Px();
	pfmet_y = PFMETP4->Py();
	
	if (PFTypeIMETP4) {
	  type1pfphi   = PFTypeIMETP4->Phi();
	  type1pfmet   = PFTypeIMETP4->Pt();
	  type1pfsumet = PFTypeIMETsumEt;
	  type1pfmet_x = PFTypeIMETP4->Px();
	  type1pfmet_y = PFTypeIMETP4->Py();
	}
	
	type1calophi   = CaloTypeIMETP4->Phi();
	type1calomet   = CaloTypeIMETP4->Pt();
	type1calosumet = CaloTypeIMETsumEt;
	type1calomet_x = CaloTypeIMETP4->Px();
	type1calomet_y = CaloTypeIMETP4->Py();
	
	type2calophi   = CaloTypeIIMETP4->Phi();
	type2calomet   = CaloTypeIIMETP4->Pt();
	type2calosumet = CaloTypeIIMETsumEt;
	type2calomet_x = CaloTypeIIMETP4->Px();
	type2calomet_y = CaloTypeIIMETP4->Py();
	
	if (!isData_) {
	  calogenmet   = GenCaloMETP4->Pt();
	  calogenmetet = GenCaloSumEt;
	}
	if (sumEtTriggers) {
	  if (pfsumet < 650)
	    jet140uTrigs = false;
	  if (pfsumet < 550)
	    jet100uTrigs = false;
	  if (pfsumet < 400)
	    jet70uTrigs = false;
	  if (pfsumet < 300)
	    jet50uTrigs = false;
	  if (pfsumet < 150)
	    jet30uTrigs = false;
	}
	  //

	if (strictTriggerCheck==0) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==0, trigger OR"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet15uTrigs || jet30uTrigs || jet50uTrigs || jet70uTrigs || jet100uTrigs || jet140uTrigs;
	}
	else if (strictTriggerCheck==1) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==1, jet15u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet15uTrigs;
	}

	else if (strictTriggerCheck==2) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==2, jet30u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet30uTrigs;
	}

	else if (strictTriggerCheck==3) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==3, jet50u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet50uTrigs;
	}

	else if (strictTriggerCheck==4) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==4, jet70u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet70uTrigs;
	}

	else if (strictTriggerCheck==5) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==5, jet100u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet100uTrigs;
	}

	else if (strictTriggerCheck==6) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==6, jet140u"<<std::endl;
	  //pass any jet trigger
	  jetTrigs = jet140uTrigs;
	}

	//highest pt jet must pass compatible trigger
	else if (strictTriggerCheck==7) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==7, based on leading jet pT"<<std::endl;
	  if (first_highest_jet_pt > 150)
	    jetTrigs = jetTrigs || jet140uTrigs;
	  else if (first_highest_jet_pt > 145)
	    jetTrigs = jetTrigs || jet100uTrigs || jet140uTrigs;
	  else if (first_highest_jet_pt > 110)
	    jetTrigs = jetTrigs || jet100uTrigs;
	  else if (first_highest_jet_pt > 105)
	    jetTrigs = jetTrigs || jet70uTrigs || jet100uTrigs;
	  else if (first_highest_jet_pt > 80)
	    jetTrigs = jetTrigs || jet70uTrigs;
	  else if (first_highest_jet_pt > 75)
	    jetTrigs = jetTrigs || jet50uTrigs || jet70uTrigs;
	  else if (first_highest_jet_pt > 60)
	    jetTrigs = jetTrigs || jet50uTrigs;
	  else if (first_highest_jet_pt > 55)
	    jetTrigs = jetTrigs || jet30uTrigs || jet50uTrigs;
	  else if (first_highest_jet_pt > 45)
	    jetTrigs = jetTrigs || jet30uTrigs;
	  else if (first_highest_jet_pt > 40)
	    jetTrigs = jetTrigs || jet15uTrigs || jet30uTrigs;
	  else if (first_highest_jet_pt > 0)
	    jetTrigs = jetTrigs || jet15uTrigs;
	}
	
	else if (strictTriggerCheck==8) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==8, intelligent OR"<<std::endl;
	  if (first_highest_jet_pt > 145)
	    jetTrigs = jetTrigs || jet140uTrigs || jet100uTrigs || jet70uTrigs || jet50uTrigs || jet30uTrigs || jet15uTrigs;
	  
	  else if (first_highest_jet_pt > 105)
	    jetTrigs = jetTrigs || jet100uTrigs || jet70uTrigs || jet50uTrigs || jet30uTrigs || jet15uTrigs;
	  
	  else if (first_highest_jet_pt > 75)
	    jetTrigs = jetTrigs || jet70uTrigs || jet50uTrigs || jet30uTrigs || jet15uTrigs;
	  
	  else if (first_highest_jet_pt > 55)
	    jetTrigs = jetTrigs || jet50uTrigs || jet30uTrigs || jet15uTrigs;
	  
	  else if (first_highest_jet_pt > 40)
	    jetTrigs = jetTrigs || jet30uTrigs || jet15uTrigs;
	  
	  else if (first_highest_jet_pt > 0)
	    jetTrigs = jetTrigs || jet15uTrigs;
	}
	
	
	else if (strictTriggerCheck==9) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==9, selective OR"<<std::endl;
	  if (first_highest_jet_pt > 0)
	    jetTrigs = jetTrigs || jet15uTrigs;
	  if (first_highest_jet_pt > 40)
	    jetTrigs = jetTrigs || jet15uTrigs || jet30uTrigs;
	  if (first_highest_jet_pt > 45)
	    jetTrigs = jetTrigs || jet30uTrigs;
	  if (first_highest_jet_pt > 55)
	    jetTrigs = jetTrigs || jet30uTrigs || jet50uTrigs;
	  if (first_highest_jet_pt > 60)
	    jetTrigs = jetTrigs || jet50uTrigs;
	  if (first_highest_jet_pt > 75)
	    jetTrigs = jetTrigs || jet50uTrigs || jet70uTrigs;
	  if (first_highest_jet_pt > 80)
	    jetTrigs = jetTrigs || jet70uTrigs;
	  if (first_highest_jet_pt > 105)
	    jetTrigs = jetTrigs || jet70uTrigs || jet100uTrigs;
	  if (first_highest_jet_pt > 110)
	    jetTrigs = jetTrigs || jet100uTrigs;
	  if (first_highest_jet_pt > 145)
	    jetTrigs = jetTrigs || jet100uTrigs || jet140uTrigs;
	  if (first_highest_jet_pt > 150)
	    jetTrigs = jetTrigs || jet140uTrigs;
	}
	
	else if (strictTriggerCheck==10) {
	  if (debug_) std::cout<<"Using strictTriggerCheck==10, lowest unprescaled: "<<singlejetTriggerPath<<std::endl;
	  jetBits = HLTTriggered->find(singlejetTriggerPath);
	  if (jetBits!=HLTTriggered->end())
	    jetTrigs = jetBits->second;
	}	

	if (debug_) {
	  if (dijet_avg > -1) {
	    std::cout<<"  ::  dijet_avg "<<dijet_avg;
	    std::cout<<"  ::  15u "<<jet15uTrigs;
	    std::cout<<"  ::  30u "<<jet30uTrigs;
	    std::cout<<"  ::  50u "<<jet50uTrigs;
	    std::cout<<"  ::  70u "<<jet70uTrigs;
	    std::cout<<"  ::  100u "<<jet100uTrigs;
	    std::cout<<"  ::  140u "<<jet140uTrigs;
	    std::cout<<"  ::  jetTrigs "<<jetTrigs;
	    std::cout<<std::endl;
	  }
	}
	if (debug_) cout<<"done looping over the jets"<<endl;

	bool dijets = false;
	if(strictDiJets)
	  if(count_number_jets==2)
	    dijets=true;
	else
	  if(count_number_jets>1)
	    dijets=true;

	if(dijets) {
	  if (debug_) cout<<"I get past the jet cuts"<<endl;
	  ++count_number_dijet;
	  bool passpvsel = false;

	  if (debug_) std::cout<<nVtx<<" number of vertices"<<std::endl;
	  if (nVtx > 0)
	    if (strictPVCheck==0) {
	      if (debug_) std::cout<<"using strict PV ==1 checking"<<std::endl;
	      //strict numPVs == 1 check
	      if (numPVs == 1) {
		passpvsel = true;}}
	    else if (strictPVCheck==1) {
	      if (debug_) std::cout<<"using loose PV >=1 checking"<<std::endl;
	      //loose numPVs >= 1 check
	      if (numPVs >= 1) {
		passpvsel = true;}}
	    else if (strictPVCheck==2) {
	      if (debug_) std::cout<<"using loose PV >=2 checking"<<std::endl;
	      //loose numPVs >= 2 check
	      if (numPVs >= 2) {
		passpvsel = true;}}
	    else if (strictPVCheck==3) {
	      if (debug_) std::cout<<"using loose PV >=3 checking"<<std::endl;
	      //loose numPVs >= 3 check
	      if (numPVs >= 3) {
		passpvsel = true;}}
	    else if (strictPVCheck==4) {
	      if (debug_) std::cout<<"using loose PV >=4 checking"<<std::endl;
	      //loose numPVs >= 4 check
	      if (numPVs >= 4) {
		passpvsel = true;}}
	  if (debug_) std::cout<<"PV cut = "<<passpvsel<<std::endl;
	
	  if (!jetTrigs) {
	    if (debug_) cout<<"passed dijets, but failed the jet triggers"<<endl;
	  }
	  else {
	    if (debug_) cout<<"passed the jet triggers"<<endl;
	    ++count_number_jettrigger;
	    if (passpvsel) {
	      ++count_number_pv;
	      if (debug_) cout<<"I get past the PV cut"<<endl;
	      //passed all cuts
	      ++counting_number_events_passing_cuts;
	      
	
	      h_genMETCalo->Fill(calogenmet);
	      h_genSUMETCalo->Fill(calogenmetet);

	      for(int itb=0;itb<125;++itb) {
		if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]) {
		  h_tcmet_x_v_reco[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco[itb]->Fill(tcmet_y);
		}

		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  h_pfmet_x_v_reco[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco[itb]->Fill(pfmet_y);
		}

		if(type1pfsumet>=bins[itb]&&type1pfsumet<bins[itb+1]) {
		  h_type1pfmet_x_v_reco[itb]->Fill(type1pfmet_x);
		  h_type1pfmet_x_v_reco[itb]->Fill(type1pfmet_y);
		}

		if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_reco[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco[itb]->Fill(type1calomet_y);
		}

		if(type2calosumet>=bins[itb]&&type2calosumet<bins[itb+1]) {
		  h_type2calomet_x_v_reco[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_reco[itb]->Fill(type2calomet_y);
		}

		// filling distributions vs pfsumet
		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  //type1 calo
		  h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_y);
		  
		  //type2 calo
		  h_type2calomet_x_v_reco_pf[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_reco_pf[itb]->Fill(type2calomet_y);
		  
		  //tcmet
		  h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_y);
		  
		  //profiles
		  h_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet);
		  hprof_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet,1);
		}

		if(type1pfsumet>=bins[itb]&&type1pfsumet<bins[itb+1]) {
		  //type1 calo
		  h_type1calomet_x_v_reco_type1pf[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco_type1pf[itb]->Fill(type1calomet_y);
		  
		  //type2 calo
		  h_type2calomet_x_v_reco_type1pf[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_reco_type1pf[itb]->Fill(type2calomet_y);
		  
		  //tcmet
		  h_tcmet_x_v_reco_type1pf[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco_type1pf[itb]->Fill(tcmet_y);
		  
		  //profiles
		  h_type2sumet_vs_type2met_bins_of_type1pfsumEt[itb]->Fill(type2calomet,type2calosumet);
		  hprof_type2sumet_vs_type2met_bins_of_type1pfsumEt[itb]->Fill(type2calomet,type2calosumet,1);
		}

		//filling distributions vs type1 sumet
		if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]) {
		  //tcmet
		  h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_y);

		  //pf met
		  h_pfmet_x_v_reco_type1[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco_type1[itb]->Fill(pfmet_y);

		  //type1pf met
		  h_type1pfmet_x_v_reco_type1[itb]->Fill(type1pfmet_x);
		  h_type1pfmet_x_v_reco_type1[itb]->Fill(type1pfmet_y);
		}
		
		//filling distributions vs tcsumet
		if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]) {
		  //type1 calo met
		  h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_y);

		  //type2 calo met
		  h_type2calomet_x_v_reco_tc[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_reco_tc[itb]->Fill(type2calomet_y);

		  //pfmet
		  h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_y);
		  
		  //type1pf met
		  h_type1pfmet_x_v_reco_tc[itb]->Fill(type1pfmet_x);
		  h_type1pfmet_x_v_reco_tc[itb]->Fill(type1pfmet_y);
		}
	      }

	      ////////////////////////////////////////////////////////////////////////////
	      //This section does the rescaling of the reco sumet to be like the gen sumet
	      //Rescaling of reco sumet for FullSim CMSSW_3_5_7
	      ////////////////////////////////////////////////////////////////////////////

	      double rescaledtcsumet = 0;
	      double rescaledpfsumet = 0;
	      double rescaledtype1pfsumet   = 0;
	      double rescaledtype1calosumet = 0;
	      double rescaledtype2calosumet = 0;

	      //For FastSim TuneX1
	      if(scale_type==0) {
		rescaledtype1calosumet = type1calosumet*2.6056 - 33.300;
		rescaledtype2calosumet = type2calosumet*1.217  - 29.699;
		rescaledpfsumet        = pfsumet       *1.417  - 6.176;
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
		rescaledtcsumet        = tcsumet       *1.666  - 1.284;
	      }

	      //For FullSimPythia8 Fall10
	      if(scale_type==11) {
		//From fitting a line to the TH2F
		rescaledtype1calosumet = type1calosumet*1.7406 - 28.4748;
		rescaledtype2calosumet = type2calosumet*1.0822 - 26.8355;
		rescaledtcsumet        = tcsumet       *1.3397 - 7.4847;
		rescaledpfsumet        = pfsumet       *1.1748 - 12.9957;
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
	      }
	      if(scale_type==12) {
		/////loose PV checking
		rescaledtype1calosumet = type1calosumet*1.8434 - 46.1097;
		rescaledtype2calosumet = type2calosumet*1.0703 - 26.0395;
		rescaledtcsumet        = tcsumet       *1.3669 - 11.0822;
		rescaledpfsumet        = pfsumet       *1.1830 - 13.8059;
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
	      }
	      if(scale_type==13) {
		////tight PV checking
		rescaledtype1calosumet = type1calosumet*1.8440 - 46.1746;
		rescaledtype2calosumet = type2calosumet*1.0705 - 26.0522;
		rescaledtcsumet        = tcsumet       *1.3672 - 11.1158;
		rescaledpfsumet        = pfsumet       *1.1832 - 13.8306;	
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
	
	      }

	      //For FullSimPythia8 Summer10
	      if(scale_type==21) {
		//From fitting a line to the TH2F
		rescaledtype1calosumet = type1calosumet*1.8933 - 29.0647;
		rescaledtype2calosumet = type2calosumet*1.1199 - 16.2920;
		rescaledtcsumet        = tcsumet       *1.4158 - 1.7334;
		rescaledpfsumet        = pfsumet       *1.2351 - 6.7233;
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
	      }
	      if(scale_type==22) {
		//From fitting a line to the TProfile
		rescaledtype1calosumet = type1calosumet*1.5088 - 1.7760;
		rescaledtype2calosumet = type2calosumet*1.0576 - 22.1946;
		rescaledtcsumet        = tcsumet       *1.3632 - 9.7624;
		rescaledpfsumet        = pfsumet       *1.1822 - 13.5598;
		rescaledtype1pfsumet   = type1pfsumet  *1      - 0;
	      }

	      //For FullSimPythia8 Summer10 Finn
	      if(scale_type==3) {
		//These are for FullSim correction
		rescaledtype1calosumet = type1calosumet*2.112 - 55.396;
		rescaledtype2calosumet = type2calosumet*1.170 - 25.287;
		rescaledtcsumet        = tcsumet       *1.581 - 10.737;
		//below is for FastSim correction	      - 
		rescaledpfsumet        = pfsumet       *1.400 - 16.57;
		rescaledtype1pfsumet   = type1pfsumet  *1     - 0;
	      }

	      //For Summer10 QCD DiJets
	      if(scale_type==4) {
		rescaledtype1calosumet = type1calosumet*1.08157 + 57.42729;
		rescaledtype2calosumet = type2calosumet*0.99153 + 0.43781;
		rescaledtcsumet        = tcsumet       *1.09536 + 43.17073;
		rescaledpfsumet        = pfsumet       *1.08441 + 19.39854;
		rescaledtype1pfsumet   = type1pfsumet  *1.0083  + 15.9682;
	      }

	      ////////////////////////////////////////////////////////////////////////////
	      //This section does the scaling of the reco met where the scaling factor
	      //is taken from Jordan's photon plus MET studies
	      ////////////////////////////////////////////////////////////////////////////

	      double rescaledtype1met   = -999;
	      double rescaledtype2met   = -999;
	      double rescaledtcmet      = -999;
	      double rescaledpfmet      = -999;
	      double rescaledtype1pfmet = -999;

	      double rescaledtype1met_x   = -999;
	      double rescaledtype2met_x   = -999;
	      double rescaledtcmet_x      = -999;
	      double rescaledpfmet_x      = -999;
	      double rescaledtype1pfmet_x = -999;

	      double rescaledtype1met_y   = -999;
	      double rescaledtype2met_y   = -999;
	      double rescaledtcmet_y      = -999;
	      double rescaledpfmet_y      = -999;
	      double rescaledtype1pfmet_y = -999;

	      double pt_photon_bins[16] = {
		0,
		19.994,
		24.2614,
		29.4396,
		35.723,
		43.3474,
		52.5992,
		63.8256,
		77.448,
		93.978,
		114.036,
		138.375,
		167.909,
		203.746,
		247.232,
		//1000.0
		2500.0
	      };

	      //double pt_photon_bins[15] = {
	      //	0,
	      //	22.1277,
	      //	26.8505,
	      //	32.5813,
	      //	39.5352,
	      //	47.9733,
	      //	58.2124,
	      //	85.713,
	      //	104.007,
	      //	126.205,
	      //	153.142,
	      //	185.827,
	      //	225.489,
	      //	273.616,
	      //	1000
	      //};
	      
	      double pt_rescale_tc[15] = {
		0.798048,
		0.798048,
		0.80663,
		0.821587,
		0.828747,
		0.845635,
		0.866897,
		0.879801,
		0.889473,
		0.908083,
		0.91239,
		0.943248,
		0.928311,
		0.961492,
		0.940583
	      };
	      double pt_rescale_pf[15] = {
		0.884981,
		0.884981,
		0.88838,
		0.897928,
		0.903705,
		0.913987,
		0.926193,
		0.927874,
		0.933238,
		0.934715,
		0.934175,
		0.945302,
		0.924562,
		0.941707,
		0.930475
	      };
	      double pt_rescale_type1pf[15] = {
		0.884981,
		0.884981,
		0.88838,
		0.897928,
		0.903705,
		0.913987,
		0.926193,
		0.927874,
		0.933238,
		0.934715,
		0.934175,
		0.945302,
		0.924562,
		0.941707,
		0.930475
	      };
	      double pt_rescale_type1[15] = {
		0.731329,
		0.731329,
		0.779014,
		0.83713,
		0.865974,
		0.897195,
		0.928577,
		0.944169,
		0.945976,
		0.969765,
		0.980242,
		0.993283,
		0.971475,
		0.981181,
		0.962692		
	      };
		 
	      double pt_rescale_type2[15] = {
		1.04701,
		1.04701,
		1.04096,
		1.03785,
		1.01449,
		1.02264,
		1.02432,
		1.02064,
		1.01483,
		1.02098,
		1.02475,
		1.03016,
		1.00755,
		1.00258,
		0.98724
	      };

	      //double pt_photon_bins[17] = {0,19.9475,24.3339,29.6389,36.0547,43.8141,53.1982,64.5475,78.2732,94.8732,114.949,139.229,168.593,204.107,247.056,299.9999,1000};
	      //
	      //double pt_rescale_tc[16] = {0.788873,0.786946,0.791559,0.808645,0.822854,0.841836,0.854884,0.864537,0.882782,0.892939,0.920738,0.924707,0.939333,0.939326,0.971899,0.929645};
	      //double pt_rescale_pf[16] = {0.906095,0.904362,0.907742,0.920871,0.925145,0.935496,0.939409,0.936432,0.937474,0.939678,0.948415,0.934699,0.944803,0.934277,0.932801,0.880993};
	      //double pt_rescale_type1[16] = {0.744853,0.777192,0.831074,0.8946,0.929688,0.966164,0.981742,0.989977,0.999186,1.00557,1.01076,0.99985,0.991945,1.0028,0.995419,0.928936};
	      //double pt_rescale_type2[16] = {1.03931,1.04369,1.03908,1.0499,1.04997,1.06003,1.05406,1.05361,1.04718,1.05128,1.04572,1.04194,1.01565,1.02073,1.02455,0.965356};

	      for(int aig = 0;aig<15;++aig) {
		//for(int aig = 0;aig<16;++aig) {
		if(type1calomet<pt_photon_bins[aig+1]&&type1calomet>pt_photon_bins[aig]) {
		  rescaledtype1met=type1calomet/pt_rescale_type1[aig];}

		if(pfmet<pt_photon_bins[aig+1]&&pfmet>pt_photon_bins[aig]) {
		  rescaledpfmet=pfmet/pt_rescale_pf[aig];}

		if(type1pfmet<pt_photon_bins[aig+1]&&type1pfmet>pt_photon_bins[aig]) {
		  rescaledtype1pfmet=type1pfmet/pt_rescale_type1pf[aig];}

		if(tcmet<pt_photon_bins[aig+1]&&tcmet>pt_photon_bins[aig]) {
		  rescaledtcmet=tcmet/pt_rescale_tc[aig];}

		if(type2calomet<pt_photon_bins[aig+1]&&type2calomet>pt_photon_bins[aig]) {
		  rescaledtype2met=type2calomet/pt_rescale_type2[aig];}
	      }
	      
	      rescaledtcmet_x=rescaledtcmet*TMath::Cos(tcphi);
	      rescaledtcmet_y=rescaledtcmet*TMath::Sin(tcphi);
	      
	      rescaledpfmet_x=rescaledpfmet*TMath::Cos(pfphi);
	      rescaledpfmet_y=rescaledpfmet*TMath::Sin(pfphi);

	      rescaledtype1pfmet_x=rescaledtype1pfmet*TMath::Cos(type1pfphi);
	      rescaledtype1pfmet_y=rescaledtype1pfmet*TMath::Sin(type1pfphi);

	      rescaledtype1met_x=rescaledtype1met*TMath::Cos(type1calophi);
	      rescaledtype1met_y=rescaledtype1met*TMath::Sin(type1calophi);

	      rescaledtype2met_x=rescaledtype2met*TMath::Cos(type2calophi);
	      rescaledtype2met_y=rescaledtype2met*TMath::Sin(type2calophi);

	      //Plotting rescaled met vs. gen sumEt for each algorithm

	      if (!isData_) {
		for(int itb=0;itb<125;++itb) {
		  // using GenMETCalo
		  if(calogenmetet>=bins[itb]&&calogenmetet<bins[itb+1]) {
		    h_tcmet_x_v[itb]->Fill(rescaledtcmet_x);
		    h_tcmet_x_v[itb]->Fill(rescaledtcmet_y);
	       
		    h_pfmet_x_v[itb]->Fill(rescaledpfmet_x);
		    h_pfmet_x_v[itb]->Fill(rescaledpfmet_y);
	       
		    h_type1pfmet_x_v[itb]->Fill(rescaledtype1pfmet_x);
		    h_type1pfmet_x_v[itb]->Fill(rescaledtype1pfmet_y);
	       
		    h_type1calomet_x_v[itb]->Fill(rescaledtype1met_x);
		    h_type1calomet_x_v[itb]->Fill(rescaledtype1met_y);
	       
		    h_type2calomet_x_v[itb]->Fill(rescaledtype2met_x);
		    h_type2calomet_x_v[itb]->Fill(rescaledtype2met_y);
		  }	 
		}
	      } 

	      ////////////////////////////////////////////////////////////////////////////////////////////
	      //Plotting rescaled MET in bins of rescaled sumET (will do fit after running over all events
	      ////////////////////////////////////////////////////////////////////////////////////////////
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype2calosumet>=bins[itb]&&rescaledtype2calosumet<bins[itb+1]) {
		  h_type2calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype2met_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtcmet_y);
		  
		  h_pfmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledpfmet_x);
		  h_pfmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledpfmet_y);
		  
		  h_type1pfmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtype1pfmet_x);
		  h_type1pfmet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtype1pfmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_type2[itb]->Fill(rescaledtype1met_y);

		  h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet);
		  hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet,1);
		  h_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,type1pfsumet);
		  hprof_type1pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,type1pfsumet,1);
		}
		if(type2calosumet>=bins[itb]&&type2calosumet<bins[itb+1]) {
		  h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledpfmet_x);
		  h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledpfmet_y);
		  
		  h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype1pfmet_x);
		  h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype1pfmet_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtcmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype1met_y);
		  
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[itb]->Fill(rescaledtype2met_y);
		}
		

	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtcsumet>=bins[itb]&&rescaledtcsumet<bins[itb+1]) {
		  h_tcmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtcmet_y);
		}
	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledpfsumet>=bins[itb]&&rescaledpfsumet<bins[itb+1]) {
		  h_pfmet_x_v_RescalingMETALSO[itb]->Fill(rescaledpfmet_x);
		  h_pfmet_x_v_RescalingMETALSO[itb]->Fill(rescaledpfmet_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtcmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtype1met_y);
		  
		  h_type2calomet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO_vs_pf[itb]->Fill(rescaledtype2met_y);
		}
		
		if(rescaledtype1pfsumet>=bins[itb]&&rescaledtype1pfsumet<bins[itb+1]) {
		  h_type1pfmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1pfmet_x);
		  h_type1pfmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1pfmet_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtcmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtype1met_y);
		  
		  h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[itb]->Fill(rescaledtype2met_y);
		}
		
		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledpfmet_x);
		  h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledpfmet_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtcmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtype1met_y);
		  
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[itb]->Fill(rescaledtype2met_y);
		}
		
		if(type1pfsumet>=bins[itb]&&type1pfsumet<bins[itb+1]) {
		  h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype1pfmet_x);
		  h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype1pfmet_y);
		  
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtcmet_x);
		  h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtcmet_y);
		  
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype1met_y);
		  
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype2met_x);
		  h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[itb]->Fill(rescaledtype2met_y);
		}
	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_y);
		}
	      }
	      
	      //MET vs. rescaled SumET
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtcsumet>=bins[itb]&&rescaledtcsumet<bins[itb+1]) {
		  h_tcmet_x_v_Rescaling[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_Rescaling[itb]->Fill(tcmet_y);
		}
	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledpfsumet>=bins[itb]&&rescaledpfsumet<bins[itb+1]) {
		  h_pfmet_x_v_Rescaling[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_Rescaling[itb]->Fill(pfmet_y);
		}
		
		if(rescaledtype1pfsumet>=bins[itb]&&rescaledtype1pfsumet<bins[itb+1]) {
		  h_type1pfmet_x_v_Rescaling[itb]->Fill(type1pfmet_x);
		  h_type1pfmet_x_v_Rescaling[itb]->Fill(type1pfmet_y);
		}
	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_Rescaling[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_Rescaling[itb]->Fill(type1calomet_y);
		}
	      }
	      
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype2calosumet>=bins[itb]&&rescaledtype2calosumet<bins[itb+1]) {
		  h_type2calomet_x_v_Rescaling[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_Rescaling[itb]->Fill(type2calomet_y);
		}
	      }
	      
	      ////////////////////////////////////////////////////////////////////////////////////////////
	      //Plotting some basic distributions
	      ////////////////////////////////////////////////////////////////////////////////////////////
	      
	      
	      h_tcMET->Fill(tcmet);
	      h_pfMET->Fill(pfmet);
	      h_type1pfMET->Fill(type1pfmet);
	      h_type1caloMET->Fill(type1calomet);
	      h_type2caloMET->Fill(type2calomet);
		 
	      h_tcMET_vs_pfMET->Fill(pfmet,tcmet);
	      h_tcMET_vs_type1pfMET->Fill(type1pfmet,tcmet);
	      h_tcMET_vs_type1caloMET->Fill(type1calomet,tcmet);
	      h_pfMET_vs_type1caloMET->Fill(type1calomet,pfmet);
	      h_type1pfMET_vs_type1caloMET->Fill(type1calomet,type1pfmet);
	      h_tcMET_vs_type2caloMET->Fill(type2calomet,tcmet);
	      h_pfMET_vs_type2caloMET->Fill(type2calomet,pfmet);
	      h_type1pfMET_vs_type2caloMET->Fill(type2calomet,type1pfmet);
		 
	      h_tcSUMET->Fill(tcsumet);
	      h_pfSUMET->Fill(pfsumet);
	      h_type1pfSUMET->Fill(type1pfsumet);
	      h_type1caloSUMET->Fill(type1calosumet);
	      h_type2caloSUMET->Fill(type2calosumet);
	      h_tcSUMET_vs_pfSUMET->Fill(pfsumet,tcsumet);
	      h_tcSUMET_vs_type1pfSUMET->Fill(type1pfsumet,tcsumet);
	      h_tcSUMET_vs_type1caloSUMET->Fill(type1calosumet,tcsumet);
	      h_pfSUMET_vs_type1caloSUMET->Fill(type1calosumet,pfsumet);
	      h_type1pfSUMET_vs_type1caloSUMET->Fill(type1calosumet,type1pfsumet);
	      h_tcSUMET_vs_type2caloSUMET->Fill(type2calosumet,tcsumet);
	      h_pfSUMET_vs_type2caloSUMET->Fill(type2calosumet,pfsumet);
	      h_type1pfSUMET_vs_type2caloSUMET->Fill(type2calosumet,type1pfsumet);
		 
	      h_genMETCalo_vs_pfMET->Fill(pfsumet,calogenmetet);
	      h_genMETCalo_vs_pfMET->Fill(pfsumet,calogenmetet);
	      h_genMETCalo_vs_type1pfMET->Fill(type1pfsumet,calogenmetet);
	      h_genMETCalo_vs_tcMET->Fill(tcsumet,calogenmetet);
	      h_genMETCalo_vs_type1caloMET->Fill(type1calosumet,calogenmetet);
	      h_genMETCalo_vs_type2caloMET->Fill(type2calosumet,calogenmetet);
	
	      h_pfSUMET_vs_genSUMETCalo->Fill(calogenmetet,pfsumet);
	      h_type1pfSUMET_vs_genSUMETCalo->Fill(calogenmetet,type1pfsumet);
	      h_tcSUMET_vs_genSUMETCalo->Fill(calogenmetet,tcsumet);
	      h_type1caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type1calosumet);
	      h_type2caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type2calosumet);
	
	      hprof_tcsumet_vs_calogensumet->Fill(calogenmetet,tcsumet,1);
	      hprof_pfsumet_vs_calogensumet->Fill(calogenmetet,pfsumet,1);
	      hprof_type1pfsumet_vs_calogensumet->Fill(calogenmetet,type1pfsumet,1);
	      hprof_type1sumet_vs_calogensumet->Fill(calogenmetet,type1calosumet,1);
	      hprof_type2sumet_vs_calogensumet->Fill(calogenmetet,type2calosumet,1);
	
	      h_tcsumet_vs_dijetavg->Fill(dijet_avg,rescaledtcsumet/tcsumet);
	      h_pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledpfsumet/pfsumet);
	      h_type1pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1pfsumet/type1pfsumet);
	      h_type1sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1calosumet/type1calosumet);
	      h_type2sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype2calosumet/type2calosumet);
	
	      hprof_tcsumet_vs_dijetavg->Fill(dijet_avg,rescaledtcsumet/tcsumet,1);
	      hprof_pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledpfsumet/pfsumet,1);
	      hprof_type1pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1pfsumet/type1pfsumet,1);
	      hprof_type1sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1calosumet/type1calosumet,1);
	      hprof_type2sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype2calosumet/type2calosumet,1);
	
	      h_tcmet_vs_dijetavg->Fill(dijet_avg,rescaledtcmet/tcmet);
	      h_pfmet_vs_dijetavg->Fill(dijet_avg,rescaledpfmet/pfmet);
	      h_type1pfmet_vs_dijetavg->Fill(dijet_avg,rescaledtype1pfmet/type1pfmet);
	      h_type1met_vs_dijetavg->Fill(dijet_avg,rescaledtype1met/type1calomet);
	      h_type2met_vs_dijetavg->Fill(dijet_avg,rescaledtype2met/type2calomet);

	      hprof_tcmet_vs_dijetavg->Fill(dijet_avg,rescaledtcmet/tcmet,1);
	      hprof_pfmet_vs_dijetavg->Fill(dijet_avg,rescaledpfmet/pfmet,1);
	      hprof_type1pfmet_vs_dijetavg->Fill(dijet_avg,rescaledtype1pfmet/type1pfmet,1);
	      hprof_type1met_vs_dijetavg->Fill(dijet_avg,rescaledtype1met/type1calomet,1);
	      hprof_type2met_vs_dijetavg->Fill(dijet_avg,rescaledtype2met/type2calomet,1);

	      h_tcMET_vs_RescaledSUMET    ->Fill(rescaledpfsumet,tcmet       );
	      h_pfMET_vs_RescaledSUMET    ->Fill(rescaledpfsumet,pfmet       );
	      h_type1MET_vs_RescaledSUMET ->Fill(rescaledpfsumet,type1calomet);
	      h_type2MET_vs_RescaledSUMET ->Fill(rescaledpfsumet,type2calomet);
	      
	      h_tcMET_vs_RescaledType1SUMET     ->Fill(rescaledtype1pfsumet,tcmet       );
	      h_type1pfMET_vs_RescaledType1SUMET->Fill(rescaledtype1pfsumet,type1pfmet  );
	      h_type1MET_vs_RescaledType1SUMET  ->Fill(rescaledtype1pfsumet,type1calomet);
	      h_type2MET_vs_RescaledType1SUMET  ->Fill(rescaledtype1pfsumet,type2calomet);
	      
	      h_tcMET_vs_genCaloSUMET     ->Fill(calogenmetet,tcmet       );
	      h_pfMET_vs_genCaloSUMET     ->Fill(calogenmetet,pfmet       );
	      h_type1pfMET_vs_genCaloSUMET->Fill(calogenmetet,type1pfmet  );
	      h_type1MET_vs_genCaloSUMET  ->Fill(calogenmetet,type1calomet);
	      h_type2MET_vs_genCaloSUMET  ->Fill(calogenmetet,type2calomet);

	    }//end jet trigger check
	  }//end check on single pv
	}//end of loop for requiring two jets
      }
    }//end check on get entry
  }//end over loop over all the events
  
  out<<"The number of events passing all the cuts: "              <<counting_number_events_passing_cuts<<endl;
  out<<"The number of events processed is: "                      <<count_number_events_processed<<endl;
  out<<"count the number of events passing the dijet cuts "       <<count_number_dijet<<endl;
  out<<"count the number of events passing the jet trigger cuts " <<count_number_jettrigger<<endl;
  out<<"count the number of events passing the pv cuts "          <<count_number_pv<<endl;
  
  if (debug_) cout<<"The number of events passing all the cuts is: "           <<counting_number_events_passing_cuts<<endl;
  if (debug_) cout<<"The number of events processed is: "                      <<count_number_events_processed<<endl;
  if (debug_) cout<<"count the number of events passing the dijet cuts "       <<count_number_dijet<<endl;
  if (debug_) cout<<"count the number of events passing the jet trigger cuts " <<count_number_jettrigger<<endl;
  if (debug_) cout<<"count the number of events passing the pv cuts "          <<count_number_pv<<endl;

  //----------------------------------------------------------     
  //Write out histogram file
  //----------------------------------------------------------      
  outfile->cd();
  outfile->Write();
  
}



#define   METResolutionStudy_cxx
#include "METResolutionStudy.h"
#include <TMath.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TH2F.h>
#include <TProfile.h>
#include <fstream>

#include <map>
#include <vector>
#include <string>

using namespace std;

void METResolutionStudy::Loop(TString output_filename,int scale_type) 
{
  //----------------------------------------------------------
  //Define output file
  //----------------------------------------------------------
  TString root_name = output_filename+".root";
  TString text_name = output_filename+".txt";
  TFile *outfile = new TFile(root_name.Data(),"RECREATE");
  outfile->cd();
  
  gROOT->ProcessLine(".L ntuplePragmas.so");
  ofstream out;
  
  out.open(text_name.Data(), ios::out | ios::app);
  
  //----------------------------------------------------------
  //Histogram Declarations
  //----------------------------------------------------------
  
  TH1F *h_tcmet_x_v[125];
  TH1F *h_pfmet_x_v[125];
  TH1F *h_type1calomet_x_v[125];
  TH1F *h_type2calomet_x_v[125];
  
  TH1F *h_tcmet_x_v_reco[125];
  TH1F *h_pfmet_x_v_reco[125];
  TH1F *h_type1calomet_x_v_reco[125];
  TH1F *h_type2calomet_x_v_reco[125];

  TH1F *h_tcmet_x_v_reco_pf[125];
  TH1F *h_type1calomet_x_v_reco_pf[125];
  TH1F *h_type2calomet_x_v_reco_pf[125];

  TH1F *h_tcmet_x_v_reco_type1[125];
  TH1F *h_tcmet_x_v_reco_type2[125];
  TH1F *h_type1calomet_x_v_reco_tc[125];
  TH1F *h_type2calomet_x_v_reco_tc[125];

  TH1F *h_pfmet_x_v_reco_type1[125];
  TH1F *h_pfmet_x_v_reco_type2[125];
  TH1F *h_pfmet_x_v_reco_tc[125];

  TH1F *h_tcmet_x_v_Rescaling[125];
  TH1F *h_pfmet_x_v_Rescaling[125];
  TH1F *h_type1calomet_x_v_Rescaling[125];
  TH1F *h_type2calomet_x_v_Rescaling[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_pf[125];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];

  TH2F *h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];
  TProfile *hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[125];

  TH2F *h_type2sumet_vs_type2met_bins_of_pfsumEt[125];
  TProfile *hprof_type2sumet_vs_type2met_bins_of_pfsumEt[125];

  if (debug_) out<<"I get here, beginning of defining array histos "<<endl;

  for(int aii=0;aii<50;++aii) {
    if (debug_) out<<"I get here, beginning of array loop "<<endl;
    h_tcmet_x_v[aii] = new TH1F(Form("h_tcmet_x_%i",aii),"",25000,-250,250);
    h_pfmet_x_v[aii] = new TH1F(Form("h_pfmet_x_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v[aii] = new TH1F(Form("h_type1calomet_x_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v[aii] = new TH1F(Form("h_type2calomet_x_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_reco[aii] = new TH1F(Form("h_tcmet_x_reco_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_reco[aii] = new TH1F(Form("h_pfmet_x_reco_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_reco[aii] = new TH1F(Form("h_type1calomet_x_reco_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_reco[aii] = new TH1F(Form("h_type2calomet_x_reco_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_reco_pf[aii] = new TH1F(Form("h_tcmet_x_reco_pf_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type1calomet_x_reco_pf_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type2calomet_x_reco_pf_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type1calomet_x_reco_tc_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type2calomet_x_reco_tc_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_reco_type1[aii] = new TH1F(Form("h_tcmet_x_reco_type1_%i",aii),"",25000,-250,250);
    h_tcmet_x_v_reco_type2[aii] = new TH1F(Form("h_tcmet_x_reco_type2_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_reco_type1[aii] = new TH1F(Form("h_pfmet_x_reco_type1_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_reco_type2[aii] = new TH1F(Form("h_pfmet_x_reco_type2_%i",aii),"",25000,-250,250);

    h_pfmet_x_v_reco_tc[aii] = new TH1F(Form("h_pfmet_x_reco_tc_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_Rescaling[aii] = new TH1F(Form("h_tcmet_x_Rescaling_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_Rescaling[aii] = new TH1F(Form("h_pfmet_x_Rescaling_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type1calomet_x_Rescaling_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type2calomet_x_Rescaling_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",25000,-250,250);

    h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",25000,-250,250);
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",25000,-250,250);
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",25000,-250,250);
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",25000,-250,250);

    if (debug_) out<<"I get here, near end of single array loop "<<endl;

    h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TH2F(Form("h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",500,0,500,500,0,500);
    hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TProfile(Form("hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",50,0,250,0,500);

    h_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TH2F(Form("h_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",500,0,500,500,0,500);
    hprof_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TProfile(Form("hprof_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",50,0,250,0,500);

    if (debug_) out<<"I get here, end of single array loop "<<endl;
  }

  if (debug_) out<<"I get here, end of defining array histos "<<endl;

  TH1F *h_tcMET = new TH1F("h_tcMET","",500,0,500);
  TH1F *h_pfMET = new TH1F("h_pfMET","",500,0,500);
  TH1F *h_type1caloMET = new TH1F("h_type1caloMET","",500,0,500);
  TH1F *h_type2caloMET = new TH1F("h_type2caloMET","",500,0,500);

  TH2F *h_tcMET_vs_pfMET = new TH2F("h_tcMET_vs_pfMET","",500,0,500,500,0,500);
  TH2F *h_tcMET_vs_type1caloMET = new TH2F("h_tcMET_vs_type1caloMET","",500,0,500,500,0,500);
  TH2F *h_pfMET_vs_type1caloMET = new TH2F("h_pfMET_vs_type1caloMET","",500,0,500,500,0,500);
  TH2F *h_tcMET_vs_type2caloMET = new TH2F("h_tcMET_vs_type2caloMET","",500,0,500,500,0,500);
  TH2F *h_pfMET_vs_type2caloMET = new TH2F("h_pfMET_vs_type2caloMET","",500,0,500,500,0,500);

  TH1F *h_tcSUMET = new TH1F("h_tcSUMET","",2500,0,2500);
  TH1F *h_pfSUMET = new TH1F("h_pfSUMET","",2500,0,2500);
  TH1F *h_type1caloSUMET = new TH1F("h_type1caloSUMET","",2500,0,2500);
  TH1F *h_type2caloSUMET = new TH1F("h_type2caloSUMET","",2500,0,2500);

  TH2F *h_tcSUMET_vs_pfSUMET = new TH2F("h_tcSUMET_vs_pfSUMET","",2500,0,2500,2500,0,2500);
  TH2F *h_tcSUMET_vs_type1caloSUMET = new TH2F("h_tcSUMET_vs_type1caloSUMET","",2500,0,2500,2500,0,2500);
  TH2F *h_pfSUMET_vs_type1caloSUMET = new TH2F("h_pfSUMET_vs_type1caloSUMET","",2500,0,2500,2500,0,2500);
  TH2F *h_tcSUMET_vs_type2caloSUMET = new TH2F("h_tcSUMET_vs_type2caloSUMET","",2500,0,2500,2500,0,2500);
  TH2F *h_pfSUMET_vs_type2caloSUMET = new TH2F("h_pfSUMET_vs_type2caloSUMET","",2500,0,2500,2500,0,2500);
   
  //////////////////////////Histograms for running on MC////////////////////////
   
  TH1F *h_genMETCalo = NULL;
  TH1F *h_genMETTrue = NULL;
  TH1F *h_genSUMETCalo = NULL;
  TH1F *h_genSUMETTrue = NULL;

  TH2F *h_genMETCalo_vs_pfMET = NULL;
  TH2F *h_genMETCalo_vs_tcMET = NULL;
  TH2F *h_genMETCalo_vs_type1caloMET = NULL;
  TH2F *h_genMETCalo_vs_type2caloMET = NULL;
   
  TH2F *h_genMETTrue_vs_pfMET = NULL;
  TH2F *h_genMETTrue_vs_tcMET = NULL;
  TH2F *h_genMETTrue_vs_type1caloMET = NULL;
  TH2F *h_genMETTrue_vs_type2caloMET = NULL;
   
  TH2F *h_pfSUMET_vs_genSUMETTrue = NULL;
  TH2F *h_tcSUMET_vs_genSUMETTrue = NULL;
  TH2F *h_type1caloSUMET_vs_genSUMETTrue = NULL;
  TH2F *h_type2caloSUMET_vs_genSUMETTrue = NULL;
   
  TH2F *h_pfSUMET_vs_genSUMETCalo = NULL;
  TH2F *h_tcSUMET_vs_genSUMETCalo = NULL;
  TH2F *h_type1caloSUMET_vs_genSUMETCalo = NULL;
  TH2F *h_type2caloSUMET_vs_genSUMETCalo = NULL;
   
  TProfile *hprof_tcsumet_vs_truegensumet = NULL;
  TProfile *hprof_pfsumet_vs_truegensumet = NULL;
  TProfile *hprof_type1sumet_vs_truegensumet = NULL;
  TProfile *hprof_type2sumet_vs_truegensumet = NULL;
   
  TProfile *hprof_tcsumet_vs_calogensumet = NULL;
  TProfile *hprof_pfsumet_vs_calogensumet = NULL;
  TProfile *hprof_type1sumet_vs_calogensumet = NULL;
  TProfile *hprof_type2sumet_vs_calogensumet = NULL;
   
  //if (!isData_) {
  h_genMETCalo = new TH1F("h_genMETCalo","",500,0,500);
  h_genMETTrue = new TH1F("h_genMETTrue","",500,0,500);
  h_genSUMETCalo = new TH1F("h_genSUMETCalo","",2500,0,2500);
  h_genSUMETTrue = new TH1F("h_genSUMETTrue","",2500,0,2500);
  
  h_genMETCalo_vs_pfMET = new TH2F("h_genMETCalo_vs_pfMET","",500,0,500,500,0,500);
  h_genMETCalo_vs_tcMET = new TH2F("h_genMETCalo_vs_tcMET","",500,0,500,500,0,500);
  h_genMETCalo_vs_type1caloMET = new TH2F("h_genMETCalo_vs_type1caloMET","",500,0,500,500,0,500);
  h_genMETCalo_vs_type2caloMET = new TH2F("h_genMETCalo_vs_type2caloMET","",500,0,500,500,0,500);
  
  h_genMETTrue_vs_pfMET = new TH2F("h_genMETTrue_vs_pfMET","",500,0,500,500,0,500);
  h_genMETTrue_vs_tcMET = new TH2F("h_genMETTrue_vs_tcMET","",500,0,500,500,0,500);
  h_genMETTrue_vs_type1caloMET = new TH2F("h_genMETTrue_vs_type1caloMET","",500,0,500,500,0,500);
  h_genMETTrue_vs_type2caloMET = new TH2F("h_genMETTrue_vs_type2caloMET","",500,0,500,500,0,500);
  
  h_pfSUMET_vs_genSUMETTrue = new TH2F("h_pfSUMET_vs_genSUMETTrue","",2500,0,2500,2500,0,2500);
  h_tcSUMET_vs_genSUMETTrue = new TH2F("h_tcSUMET_vs_genSUMETTrue","",2500,0,2500,2500,0,2500);
  h_type1caloSUMET_vs_genSUMETTrue = new TH2F("h_type1caloSUMET_vs_genSUMETTrue","",2500,0,2500,2500,0,2500);
  h_type2caloSUMET_vs_genSUMETTrue = new TH2F("h_type2caloSUMET_vs_genSUMETTrue","",2500,0,2500,2500,0,2500);
  
  h_pfSUMET_vs_genSUMETCalo = new TH2F("h_pfSUMET_vs_genSUMETCalo","",2500,0,2500,2500,0,2500);
  h_tcSUMET_vs_genSUMETCalo = new TH2F("h_tcSUMET_vs_genSUMETCalo","",2500,0,2500,2500,0,2500);
  h_type1caloSUMET_vs_genSUMETCalo = new TH2F("h_type1caloSUMET_vs_genSUMETCalo","",2500,0,2500,2500,0,2500);
  h_type2caloSUMET_vs_genSUMETCalo = new TH2F("h_type2caloSUMET_vs_genSUMETCalo","",2500,0,2500,2500,0,2500);
  
  hprof_tcsumet_vs_truegensumet  = new TProfile("hprof_tcsumet_vs_truegensumet","Profile of tcsumet vs. truegensumet",125,0,2500,0,2500);
  hprof_pfsumet_vs_truegensumet  = new TProfile("hprof_pfsumet_vs_truegensumet","Profile of pfsumet vs. truegensumet",125,0,2500,0,2500);
  hprof_type1sumet_vs_truegensumet  = new TProfile("hprof_type1sumet_vs_truegensumet","Profile of type1 calosumet vs. truegensumet",125,0,2500,0,2500);
  hprof_type2sumet_vs_truegensumet  = new TProfile("hprof_type2sumet_vs_truegensumet","Profile of type1 calosumet vs. truegensumet",125,0,2500,0,2500);
  
  hprof_tcsumet_vs_calogensumet  = new TProfile("hprof_tcsumet_vs_calogensumet","Profile of tcsumet vs. calogensumet",125,0,2500,0,2500);
  hprof_pfsumet_vs_calogensumet  = new TProfile("hprof_pfsumet_vs_calogensumet","Profile of pfsumet vs. calogensumet",125,0,2500,0,2500);
  hprof_type1sumet_vs_calogensumet  = new TProfile("hprof_type1sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet",125,0,2500,0,2500);
  hprof_type2sumet_vs_calogensumet  = new TProfile("hprof_type2sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet",125,0,2500,0,2500);
  //}
  
  TH2F *h_pfsumet_vs_dijetavg = new TH2F("h_pfsumet_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_tcsumet_vs_dijetavg = new TH2F("h_tcsumet_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_type1sumet_vs_dijetavg = new TH2F("h_type1sumet_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_type2sumet_vs_dijetavg = new TH2F("h_type2sumet_vs_dijetavg","",500,0,500,200,0,5);

  TProfile *hprof_tcsumet_vs_dijetavg     = new TProfile("hprof_tcsumet_vs_dijetavg","Profile of tcsumet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_pfsumet_vs_dijetavg     = new TProfile("hprof_pfsumet_vs_dijetavg","Profile of pfsumet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_type1sumet_vs_dijetavg  = new TProfile("hprof_type1sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_type2sumet_vs_dijetavg  = new TProfile("hprof_type2sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",50,0,500,0,10);

  TH2F *h_pfmet_vs_dijetavg    = new TH2F("h_pfmet_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_tcmet_vs_dijetavg    = new TH2F("h_tcmet_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_type1met_vs_dijetavg = new TH2F("h_type1met_vs_dijetavg","",500,0,500,200,0,5);
  TH2F *h_type2met_vs_dijetavg = new TH2F("h_type2met_vs_dijetavg","",500,0,500,200,0,5);

  TProfile *hprof_tcmet_vs_dijetavg     = new TProfile("hprof_tcmet_vs_dijetavg","Profile of tcmet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_pfmet_vs_dijetavg     = new TProfile("hprof_pfmet_vs_dijetavg","Profile of pfmet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_type1met_vs_dijetavg  = new TProfile("hprof_type1met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",50,0,500,0,10);
  TProfile *hprof_type2met_vs_dijetavg  = new TProfile("hprof_type2met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",50,0,500,0,10);

  if (debug_) cout<<"I get here, end of defining histos "<<endl;

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
    2500
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
  int count_number_techtrigger = 0;
  int count_number_jettrigger = 0;
  int count_number_dijet = 0;
  int count_number_pv = 0;
  //int count_number_trigger = 0;
  //int tmpRun = -9999;
  for(int ia = 0; ia<nentries;++ia) {
    //for(int ia = 0; ia<1;++ia) {
    
    if (debug_) cout<<"trying to get entry "<<ia<<"... ";
    fChain->GetEntry(ia);
    if (debug_) cout<<"success!"<<endl;

    ////if (Run != tmpRun ) {
    //std::cout<<"Run #"<<Run<<std::endl;

    ++count_number_events_processed;

    bool techTrigs    = false;
    bool techBeamHalo = false;
    bool jetTrigs     = false;
    

    //stringtobool::const_iterator hlts   = HLTTriggered->begin();
    //stringtobool::const_iterator l1bits = L1Triggered->begin();
    //stringtoint::const_iterator hltsp   = HLTPrescaled->begin();
    //stringtoint::const_iterator l1pbits = L1Prescaled->begin();
    //
    //out<<"HLTTriggered->size() = "<<HLTTriggered->size()<<std::endl;
    //out<<"HLTPrescaled->size() = "<<HLTPrescaled->size()<<std::endl;
    //out<<"L1Triggered->size() = "<<L1Triggered->size()<<std::endl;
    //out<<"L1Prescaled->size() = "<<L1Prescaled->size()<<std::endl;
    //
    //for (; hlts!=HLTTriggered->end(); ++hlts) {
    //  if (debug_) out<<hlts->first<<" had result "<<hlts->second;
    //  std::string hltname = hlts->first;
    //  stringtoint::iterator hlt;
    //  hlt = HLTPrescaled->find(hltname);
    //  if (hlt!=HLTPrescaled->end())
    //	if (debug_) out<<" and prescale "<<hlt->second<<endl;
    //}
    //
    //for (; l1bits!=L1Triggered->end(); ++l1bits) {
    //  if (debug_) out<<l1bits->first<<" had result "<<l1bits->second;
    //  std::string l1name = l1bits->first;
    //  stringtoint::iterator l1;
    //  l1 = L1Prescaled->find(l1name);
    //  if (l1!=L1Prescaled->end())
    //	if (debug_) out<<" and prescale "<<l1->second<<endl;
    //}
    
    stringtobool::iterator jetBits;
    jetBits = HLTTriggered->find("HLT_Jet15U");
    if (jetBits!=HLTTriggered->end()) {
      if (debug_) std::cout<<"Found HLT_Jet15U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet30U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet30U";
      if (jetBits->second)
	jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet50U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet50U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet70U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet70U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet100U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet100U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet100U_v1");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet100U_v1";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet100U_v2");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet100U_v2";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet100U_v3");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet100U_v3";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet140U_v1");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet140U_v1";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet140U_v2");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet140U_v2";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_Jet140U_v3");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_Jet140U_v3";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_L1Jet6U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_L1Jet6U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }
    jetBits = HLTTriggered->find("HLT_L1Jet10U");
    if (jetBits!=HLTTriggered->end())  {
      if (debug_) std::cout<<"Found HLT_L1Jet10U";
      if (jetBits->second)
	//jetTrigs = true;
      if (debug_) std::cout<<" with result: "<<jetBits->second<<std::endl;
    }

    //Technical trigger bits to filter out beam halo
    stringtobool::iterator techBits;
    techBits =L1Triggered->find("L1Tech_BSC_halo_beam2_inner.v0");
    if (techBits!=L1Triggered->end()) {
      if (debug_) std::cout<<"Found L1Tech_BSC_halo_beam2_inner.v0";
      if (techBits->second)
	techBeamHalo = true;
      if (debug_) std::cout<<" with result: "<<techBits->second<<std::endl;      
    }
    techBits =L1Triggered->find("L1Tech_BSC_halo_beam2_outer.v0");
    if (techBits!=L1Triggered->end())  {
      if (debug_) std::cout<<"Found L1Tech_BSC_halo_beam2_outer.v0";
      if (techBits->second)
	techBeamHalo = true;
      if (debug_) std::cout<<" with result: "<<techBits->second<<std::endl;      
    }
    techBits =L1Triggered->find("L1Tech_BSC_halo_beam1_inner.v0");
    if (techBits!=L1Triggered->end())  {
      if (debug_) std::cout<<"Found L1Tech_BSC_halo_beam1_inner.v0";
      if (techBits->second)
	techBeamHalo = true;
      if (debug_) std::cout<<" with result: "<<techBits->second<<std::endl;      
    }
    techBits =L1Triggered->find("L1Tech_BSC_halo_beam1_outer.v0");
    if (techBits!=L1Triggered->end())  {
      if (debug_) std::cout<<"Found L1Tech_BSC_halo_beam1_outer.v0";
      if (techBits->second)
	techBeamHalo = true;
      if (debug_) std::cout<<" with result: "<<techBits->second<<std::endl;      
    }
    
    techBits =L1Triggered->find("L1Tech_BPTX_plus_AND_minus.v0");
    if (techBits!=L1Triggered->end())  {
      if (debug_) std::cout<<"Found L1Tech_BPTX_plus_AND_minus.v0";
      if (techBits->second)
	techTrigs = true;
      if (debug_) std::cout<<" with result: "<<techBits->second<<std::endl;      
    }

    //only use L1 tech bit0 on data, if not data, techTrigs is true
    techTrigs = techTrigs || !isData_;

    techTrigs = techTrigs && !techBeamHalo;
    // if we don't want to check tech trigs, set bit true
    techTrigs = techTrigs || !doTechTrigs_;
    
    //don't worry about tech trigs at the moment
    techTrigs = true;

    bool expType=true;
    if(expType) {
       
      //++count_number_trigger;
       
      int count_number_jets = 0;
      double first_highest_jet_pt  = -999;
      int first_highest_location   = -999;
      double second_highest_jet_pt = -999;

      if (debug_) cout<<"looping over the "<<NJets<<" jets to find the highest pt jet"<<endl;
      
      for(int aia = 0;aia<NJets;++aia) {
	if (debug_) cout<<"jet "<<aia;
	//do JetID here?
	//if(!JetIDLoose->at(aia))
	if (debug_) printf(": pt: %2.2f  eta: %2.2f\n",JetP4->at(aia).Pt(), JetP4->at(aia).Eta());
	if(fabs(JetP4->at(aia).Eta())<3)
	  if (JetP4->at(aia).Pt()>25) {
	    if (debug_) cout<<", passed minimal eta/pt cuts ";
	    if(!JetIDLoose->at(aia))
	      if (debug_) cout<<"There is a problem with jet Id"<<endl;
	    
	    if (JetIDLoose->at(aia)) {
	      ++count_number_jets;     
	      if(JetP4->at(aia).Pt()>first_highest_jet_pt) {
		if (debug_) cout<<", is highest pt jet encountered ";
		first_highest_jet_pt=JetP4->at(aia).Pt();
		first_highest_location=aia;
	      }//end of looking for highest pt jet
	    }//end loose jetID requirement
	  }//if requirement for pt and eta
	if (debug_) cout<<endl;
      }//end of for loop over jets
       
      if (debug_) cout<<"looping over the jets to find the 2nd highest pt jet"<<endl;
      for(int aia = 0;aia<NJets;++aia) {
	if (debug_) cout<<"jet "<<aia<<endl;
	if(fabs(JetP4->at(aia).Eta())<3&&JetP4->at(aia).Pt()>25) {
	  if(!JetIDLoose->at(aia))
	    if (debug_) cout<<"There is a problem with jet Id"<<endl;
	  if (JetIDLoose->at(aia)) {
	    if(aia!=first_highest_location&&JetP4->at(aia).Pt()>second_highest_jet_pt) {
	      second_highest_jet_pt=JetP4->at(aia).Pt();
	    }//end of looking for highest pt jet
	  }//end loose jetID requirement
	}//if requirement for pt and eta
      }//end of for loop over jets
       
      double dijet_avg = (first_highest_jet_pt+second_highest_jet_pt)/2;
      
      if (debug_) cout<<"done looping over the jets"<<endl;

      bool dijets = false;
      if(count_number_jets>1)
	dijets=true;

      if(dijets) {
	if (debug_) cout<<"I get past the jet cuts"<<endl;
	++count_number_dijet;
	bool singlepv = false;
	//std::cout<<nVtx<<" number of vertices"<<std::endl;
	if (nVtx > 0)
	  singlepv = true;

	if (!jetTrigs)
	  out<<"passed dijets, but failed the jet triggers"<<endl;
	else {
	  ++count_number_jettrigger;
	  if (techTrigs) {
	    ++count_number_techtrigger;
	    if (singlepv) {
	      ++count_number_pv;
	      if (debug_) cout<<"I get past the PF cut"<<endl;
	      //passed all cuts
	      ++counting_number_events_passing_cuts;
	 
	      double tcmet = 0; 
	      double tcsumet = 0;
	      double tcmet_x = 0;
	      double tcmet_y = 0;
	      double tcphi = -999;

	      double pfmet = 0; 
	      double pfsumet = 0; 
	      double pfmet_x = 0; 
	      double pfmet_y = 0; 
	      double pfphi = -999;

	      double type1calomet = 0; 
	      double type1calosumet = 0; 
	      double type1calomet_x = 0; 
	      double type1calomet_y = 0; 
	      double type1calophi = -999;
	     
	      double type2calomet = 0; 
	      double type2calosumet = 0; 
	      double type2calomet_x = 0; 
	      double type2calomet_y = 0; 
	      double type2calophi = -999;
	     
	      double truegenmet   = -999; 
	      double truegenmetet = -999; 

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
		truegenmet   = GenTrueMETP4->Pt();
		truegenmetet = GenTrueSumEt;
	    
		calogenmet   = GenCaloMETP4->Pt();
		calogenmetet = GenCaloSumEt;
	      }
	
	      h_genMETTrue->Fill(truegenmet);
	      h_genSUMETTrue->Fill(truegenmetet);
	
	      h_genMETCalo->Fill(calogenmet);
	      h_genSUMETCalo->Fill(calogenmetet);

	      for(int itb=0;itb<125;++itb) {
		if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]) {
		  h_tcmet_x_v_reco[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco[itb]->Fill(tcmet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  h_pfmet_x_v_reco[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco[itb]->Fill(pfmet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_reco[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco[itb]->Fill(type1calomet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(type2calosumet>=bins[itb]&&type2calosumet<bins[itb+1]) {
		  h_type2calomet_x_v_reco[itb]->Fill(type2calomet_x);
		  h_type2calomet_x_v_reco[itb]->Fill(type2calomet_y);
		}
	      }

	      for(int itb=0;itb<125;++itb) {
		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]) {
		  h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_y);
		  h_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet);
		  hprof_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet,1);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]) {
		  h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_x);
		  h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]) {
		  h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_y);
		}
	      }
	     
	      for(int itb=0;itb<125;++itb) {
		if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]) {
		  h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_y);
		}
	      }
		 
	      for(int itb=0;itb<125;++itb) {
		if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]) {
		  h_pfmet_x_v_reco_type1[itb]->Fill(pfmet_x);
		  h_pfmet_x_v_reco_type1[itb]->Fill(pfmet_y);
		}
	      }

	      ////////////////////////////////////////////////////////////////////////////
	      //This section does the rescaling of the reco sumet to be like the gen sumet
	      //Rescaling of reco sumet for FullSim CMSSW_3_5_7
	      ////////////////////////////////////////////////////////////////////////////
	      /*
		double rescaledtcsumet = tcsumet*1.567+6.74;
		double rescaledpfsumet = pfsumet*1.248+2.2;
		double rescaledtype1calosumet = type1calosumet*2.33-17.69;
	      */
	      //double rescaledtype1calosumet = type1calosumet*2.43-25.15;

	      double rescaledtcsumet = 0;
	      double rescaledpfsumet = 0;
	      double rescaledtype1calosumet = 0;
	      double rescaledtype2calosumet = 0;

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

	      //For FastSim TuneX1
	      if(scale_type==0) {
		rescaledtype1calosumet = type1calosumet*2.6056-33.300;
		rescaledtype2calosumet = type2calosumet*1.217-29.699;
		rescaledpfsumet        = pfsumet*1.417-6.176;
		rescaledtcsumet        = tcsumet*1.666-1.284;
	      }

	      //For FullSimPythia8 Fall10
	      if(scale_type==11) {
		//From fitting a line to the TH2F
		rescaledtype1calosumet = type1calosumet*1.7406-28.4748;
		rescaledtype2calosumet = type2calosumet*1.0822-26.8355;
		rescaledtcsumet        = tcsumet*1.3397-7.4847;
		rescaledpfsumet        = pfsumet*1.1748-12.9957;
	      }
	      if(scale_type==12) {
		//From fitting a line to the TProfile
		rescaledtype1calosumet = type1calosumet*1.8807-44.5614;
		rescaledtype2calosumet = type2calosumet*1.0957-28.8939;
		rescaledtcsumet        = tcsumet*1.3925-13.6462;
		rescaledpfsumet        = pfsumet*1.1946-15.5569;
	      }

	      //For FullSimPythia8 Summer10
	      if(scale_type==21) {
		//From fitting a line to the TH2F
		rescaledtype1calosumet = type1calosumet*1.8933-29.0647;
		rescaledtype2calosumet = type2calosumet*1.1199-16.2920;
		rescaledtcsumet        = tcsumet*1.4158-1.7334;
		rescaledpfsumet        = pfsumet*1.2351-6.7233;
	      }
	      if(scale_type==22) {
		//From fitting a line to the TProfile
		rescaledtype1calosumet = type1calosumet*1.5088-1.7760;
		rescaledtype2calosumet = type2calosumet*1.0576-22.1946;
		rescaledtcsumet        = tcsumet*1.3632-9.7624;
		rescaledpfsumet        = pfsumet*1.1822-13.5598;
	      }

	      //For FullSimPythia8 Summer10 Finn
	      if(scale_type==3) {
		/*
		  rescaledtcsumet = tcsumet*1.607-6.559;
		  rescaledpfsumet = pfsumet*1.275-5.487;
		  rescaledtype1calosumet = type1calosumet*2.279-52.496;
		  rescaledtype2calosumet = type2calosumet*1.163-20.08;
		*/
		//These are for FullSim correction
		rescaledtype1calosumet = type1calosumet*2.112-55.396;
		rescaledtype2calosumet = type2calosumet*1.170-25.287;
		rescaledtcsumet        = tcsumet*1.581-10.737;
		//rescaledpfsumet        = pfsumet*1.254-7.4567;
		//below is for FastSim correction
		rescaledpfsumet        = pfsumet*1.400-16.57;
	      }

	      //For FullSimTuneD6T
	      if(scale_type==4) {
		/*
		  rescaledtcsumet = tcsumet*1.55+2.54;
		  rescaledpfsumet = pfsumet*1.242-0.322;
		  rescaledtype1calosumet = type1calosumet*2.22-50.13;
		  rescaledtype2calosumet = type2calosumet*1.067-11.019;
		*/
		rescaledtype1calosumet = type1calosumet*2.037-49.470;
		rescaledtype2calosumet = type2calosumet*1.064-12.339;
		rescaledtcsumet = tcsumet*1.526-0.5104;
		rescaledpfsumet = pfsumet*1.231-1.735;
	      }

	      //For FullSimTuneP0
	      if(scale_type==5) {
		/*
		  rescaledtcsumet = tcsumet*1.578-7.353;
		  rescaledpfsumet = pfsumet*1.264-6.133;
		  rescaledtype1calosumet = type1calosumet*2.225-54.584;
		  rescaledtype2calosumet = type2calosumet*1.174-24.92;
		*/
		rescaledtype1calosumet = type1calosumet*2.037-56.133;
		rescaledtype2calosumet = type2calosumet*1.160-27.630;
		rescaledtcsumet = tcsumet*1.524-7.830;
		rescaledpfsumet = pfsumet*1.243-6.970;
	      }

	      ////////////////////////////////////////////////////////////////////////////
	      //This section does the scaling of the reco met where the scaling factor
	      //is taken from Jordan's photon plus MET studies
	      ////////////////////////////////////////////////////////////////////////////

	      double rescaledtype1met = -999;
	      double rescaledtype2met = -999;
	      double rescaledtcmet = -999;
	      double rescaledpfmet = -999;

	      double rescaledtype1met_x = -999;
	      double rescaledtype2met_x = -999;
	      double rescaledtcmet_x = -999;
	      double rescaledpfmet_x = -999;

	      double rescaledtype1met_y = -999;
	      double rescaledtype2met_y = -999;
	      double rescaledtcmet_y = -999;
	      double rescaledpfmet_y = -999;

	      double pt_photon_bins[15] = {
		0,
		22.1277,
		26.8505,
		32.5813,
		39.5352,
		47.9733,
		58.2124,
		85.713,
		104.007,
		126.205,
		153.142,
		185.827,
		225.489,
		273.616,
		1000
	      };

	      double pt_rescale_tc[14] = {
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
	      double pt_rescale_pf[14] = {
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
	      double pt_rescale_type1[14] = {
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
		 
	      double pt_rescale_type2[14] = {
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

	      for(int aig = 0;aig<14;++aig) {
		//for(int aig = 0;aig<16;++aig) {
		if(type1calomet<pt_photon_bins[aig+1]&&type1calomet>pt_photon_bins[aig]) {
		  rescaledtype1met=type1calomet/pt_rescale_type1[aig];}

		if(pfmet<pt_photon_bins[aig+1]&&pfmet>pt_photon_bins[aig]) {
		  rescaledpfmet=pfmet/pt_rescale_pf[aig];}

		if(tcmet<pt_photon_bins[aig+1]&&tcmet>pt_photon_bins[aig]) {
		  rescaledtcmet=tcmet/pt_rescale_tc[aig];}

		if(type2calomet<pt_photon_bins[aig+1]&&type2calomet>pt_photon_bins[aig]) {
		  rescaledtype2met=type2calomet/pt_rescale_type2[aig];}
	      }
		 
	      rescaledtcmet_x=rescaledtcmet*TMath::Cos(tcphi);
	      rescaledtcmet_y=rescaledtcmet*TMath::Sin(tcphi);

	      rescaledpfmet_x=rescaledpfmet*TMath::Cos(pfphi);
	      rescaledpfmet_y=rescaledpfmet*TMath::Sin(pfphi);

	      rescaledtype1met_x=rescaledtype1met*TMath::Cos(type1calophi);
	      rescaledtype1met_y=rescaledtype1met*TMath::Sin(type1calophi);

	      rescaledtype2met_x=rescaledtype2met*TMath::Cos(type2calophi);
	      rescaledtype2met_y=rescaledtype2met*TMath::Sin(type2calophi);

	      //Plotting rescaled met vs. gen sumEt for each algorithm

	      if (!isData_) {
		for(int itb=0;itb<125;++itb) {
		  //// using GenMETTrue
		  //if(truegenmetet>=bins[itb]&&truegenmetet<bins[itb+1]) {
		  //  h_tcmet_x_v[itb]->Fill(rescaledtcmet_x);
		  //  h_tcmet_x_v[itb]->Fill(rescaledtcmet_y);
		  //   
		  //  h_pfmet_x_v[itb]->Fill(rescaledpfmet_x);
		  //  h_pfmet_x_v[itb]->Fill(rescaledpfmet_y);
		  //   
		  //  h_type1calomet_x_v[itb]->Fill(rescaledtype1met_x);
		  //  h_type1calomet_x_v[itb]->Fill(rescaledtype1met_y);
		  //   
		  //  h_type2calomet_x_v[itb]->Fill(rescaledtype2met_x);
		  //  h_type2calomet_x_v[itb]->Fill(rescaledtype2met_y);
		  //   
		  //}	 
		  // using GenMETCalo
		  if(calogenmetet>=bins[itb]&&calogenmetet<bins[itb+1]) {
		    h_tcmet_x_v[itb]->Fill(rescaledtcmet_x);
		    h_tcmet_x_v[itb]->Fill(rescaledtcmet_y);
	       
		    h_pfmet_x_v[itb]->Fill(rescaledpfmet_x);
		    h_pfmet_x_v[itb]->Fill(rescaledpfmet_y);
	       
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
		     
		  h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet);
		  hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet,1);
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
	      }
		 
	      for(int itb=0;itb<125;++itb) {
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
	      }
		 
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_x);
		  h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_y);
		}
	      }

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
	      }
		 
	      for(int itb=0;itb<125;++itb) {
		if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]) {
		  h_type1calomet_x_v_Rescaling[itb]->Fill(type1calomet_x);
		  h_type1calomet_x_v_Rescaling[itb]->Fill(type1calomet_y);
		}
	      }

	      ////////////////////////////////////////////////////////////////////////////////////////////
	      //Plotting some basic distributions
	      ////////////////////////////////////////////////////////////////////////////////////////////
	 
		 
	      h_tcMET->Fill(tcmet);
	      h_pfMET->Fill(pfmet);
	      h_type1caloMET->Fill(type1calomet);
	      h_type2caloMET->Fill(type2calomet);
		 
	      h_tcMET_vs_pfMET->Fill(pfmet,tcmet);
	      h_tcMET_vs_type1caloMET->Fill(type1calomet,tcmet);
	      h_pfMET_vs_type1caloMET->Fill(type1calomet,pfmet);
	      h_tcMET_vs_type2caloMET->Fill(type2calomet,tcmet);
	      h_pfMET_vs_type2caloMET->Fill(type2calomet,pfmet);
		 
	      h_tcSUMET->Fill(tcsumet);
	      h_pfSUMET->Fill(pfsumet);
	      h_type1caloSUMET->Fill(type1calosumet);
	      h_type2caloSUMET->Fill(type2calosumet);
	      h_tcSUMET_vs_pfSUMET->Fill(pfsumet,tcsumet);
	      h_tcSUMET_vs_type1caloSUMET->Fill(type1calosumet,tcsumet);
	      h_pfSUMET_vs_type1caloSUMET->Fill(type1calosumet,pfsumet);
	      h_tcSUMET_vs_type2caloSUMET->Fill(type2calosumet,tcsumet);
	      h_pfSUMET_vs_type2caloSUMET->Fill(type2calosumet,pfsumet);
		 
	      h_genMETTrue_vs_pfMET->Fill(pfsumet,truegenmetet);
	      h_genMETTrue_vs_tcMET->Fill(tcsumet,truegenmetet);
	      h_genMETTrue_vs_type1caloMET->Fill(type1calosumet,truegenmetet);
	      h_genMETTrue_vs_type2caloMET->Fill(type2calosumet,truegenmetet);
	
	      h_pfSUMET_vs_genSUMETTrue->Fill(truegenmetet,pfsumet);
	      h_tcSUMET_vs_genSUMETTrue->Fill(truegenmetet,tcsumet);
	      h_type1caloSUMET_vs_genSUMETTrue->Fill(truegenmetet,type1calosumet);
	      h_type2caloSUMET_vs_genSUMETTrue->Fill(truegenmetet,type2calosumet);
	
	      hprof_tcsumet_vs_truegensumet->Fill(truegenmetet,tcsumet,1);
	      hprof_pfsumet_vs_truegensumet->Fill(truegenmetet,pfsumet,1);
	      hprof_type1sumet_vs_truegensumet->Fill(truegenmetet,type1calosumet,1);
	      hprof_type2sumet_vs_truegensumet->Fill(truegenmetet,type2calosumet,1);
	
	      h_genMETCalo_vs_pfMET->Fill(pfsumet,calogenmetet);
	      h_genMETCalo_vs_tcMET->Fill(tcsumet,calogenmetet);
	      h_genMETCalo_vs_type1caloMET->Fill(type1calosumet,calogenmetet);
	      h_genMETCalo_vs_type2caloMET->Fill(type2calosumet,calogenmetet);
	
	      h_pfSUMET_vs_genSUMETCalo->Fill(calogenmetet,pfsumet);
	      h_tcSUMET_vs_genSUMETCalo->Fill(calogenmetet,tcsumet);
	      h_type1caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type1calosumet);
	      h_type2caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type2calosumet);
	
	      hprof_tcsumet_vs_calogensumet->Fill(calogenmetet,tcsumet,1);
	      hprof_pfsumet_vs_calogensumet->Fill(calogenmetet,pfsumet,1);
	      hprof_type1sumet_vs_calogensumet->Fill(calogenmetet,type1calosumet,1);
	      hprof_type2sumet_vs_calogensumet->Fill(calogenmetet,type2calosumet,1);
	
	      h_tcsumet_vs_dijetavg->Fill(dijet_avg,rescaledtcsumet/tcsumet);
	      h_pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledpfsumet/pfsumet);
	      h_type1sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1calosumet/type1calosumet);
	      h_type2sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype2calosumet/type2calosumet);
	
	      hprof_tcsumet_vs_dijetavg->Fill(dijet_avg,rescaledtcsumet/tcsumet,1);
	      hprof_pfsumet_vs_dijetavg->Fill(dijet_avg,rescaledpfsumet/pfsumet,1);
	      hprof_type1sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype1calosumet/type1calosumet,1);
	      hprof_type2sumet_vs_dijetavg->Fill(dijet_avg,rescaledtype2calosumet/type2calosumet,1);
	
	      h_tcmet_vs_dijetavg->Fill(dijet_avg,rescaledtcmet/tcmet);
	      h_pfmet_vs_dijetavg->Fill(dijet_avg,rescaledpfmet/pfmet);
	      h_type1met_vs_dijetavg->Fill(dijet_avg,rescaledtype1met/type1calomet);
	      h_type2met_vs_dijetavg->Fill(dijet_avg,rescaledtype2met/type2calomet);

	      hprof_tcmet_vs_dijetavg->Fill(dijet_avg,rescaledtcmet/tcmet,1);
	      hprof_pfmet_vs_dijetavg->Fill(dijet_avg,rescaledpfmet/pfmet,1);
	      hprof_type1met_vs_dijetavg->Fill(dijet_avg,rescaledtype1met/type1calomet,1);
	      hprof_type2met_vs_dijetavg->Fill(dijet_avg,rescaledtype2met/type2calomet,1);
	    }// end of tech trigger requirements
	  }//end jet trigger check
	}//end check on single pv
      }//end of loop for requiring two jets
    }//
    //}  
    //tmpRun = Run;
  }//end over loop over all the events
  
  out<<"The number of events passing all the cuts: "              <<counting_number_events_passing_cuts<<endl;
  out<<"The number of events processed is: "                      <<count_number_events_processed<<endl;
  out<<"count the number of events passing the tech trigger cuts "<<count_number_techtrigger<<endl;
  out<<"count the number of events passing the dijet cuts "       <<count_number_dijet<<endl;
  out<<"count the number of events passing the jet trigger cuts " <<count_number_jettrigger<<endl;
  out<<"count the number of events passing the pv cuts "          <<count_number_pv<<endl;
  
  if (debug_) cout<<"The number of events passing all the cuts is: "           <<counting_number_events_passing_cuts<<endl;
  if (debug_) cout<<"The number of events processed is: "                      <<count_number_events_processed<<endl;
  if (debug_) cout<<"count the number of events passing the tech trigger cuts "<<count_number_techtrigger<<endl;
  if (debug_) cout<<"count the number of events passing the dijet cuts "       <<count_number_dijet<<endl;
  if (debug_) cout<<"count the number of events passing the jet trigger cuts " <<count_number_jettrigger<<endl;
  if (debug_) cout<<"count the number of events passing the pv cuts "          <<count_number_pv<<endl;

  //----------------------------------------------------------     
  //Write out histogram file
  //----------------------------------------------------------      
  outfile->cd();
  outfile->Write();
  
}



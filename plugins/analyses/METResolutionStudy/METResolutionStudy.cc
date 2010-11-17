#define   METResolutionStudy_cxx
#include "METResolutionStudy.h"
#include <TMath.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TF1.h>
#include <TH2F.h>
#include <TProfile.h>
#include <fstream>

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
  
  
  ofstream out;
  
  //  ofstream out2;
  // in.open("cross.out");
  out.open(text_name.Data(), ios::out | ios::app);
  //  out2.open("GeneratingParticles.txt",ios::out | ios::app)
  
  
  //----------------------------------------------------------
  //Histogram Declarations
  //----------------------------------------------------------
  
  TH1F *h_tcmet_x_v[20];
  TH1F *h_pfmet_x_v[20];
  TH1F *h_type1calomet_x_v[20];
  TH1F *h_type2calomet_x_v[20];
  
  
  TH1F *h_tcmet_x_v_reco[20];
  TH1F *h_pfmet_x_v_reco[20];
  TH1F *h_type1calomet_x_v_reco[20];
  TH1F *h_type2calomet_x_v_reco[20];

  TH1F *h_tcmet_x_v_reco_pf[20];
  TH1F *h_type1calomet_x_v_reco_pf[20];
  TH1F *h_type2calomet_x_v_reco_pf[20];


  TH1F *h_tcmet_x_v_reco_type1[20];
  TH1F *h_tcmet_x_v_reco_type2[20];
  TH1F *h_type1calomet_x_v_reco_tc[20];
  TH1F *h_type2calomet_x_v_reco_tc[20];

  TH1F *h_pfmet_x_v_reco_type1[20];
  TH1F *h_pfmet_x_v_reco_type2[20];
  TH1F *h_pfmet_x_v_reco_tc[20];


  TH1F *h_tcmet_x_v_Rescaling[20];
  TH1F *h_pfmet_x_v_Rescaling[20];
  TH1F *h_type1calomet_x_v_Rescaling[20];
  TH1F *h_type2calomet_x_v_Rescaling[20];


  TH1F *h_tcmet_x_v_RescalingMETALSO[20];
  TH1F *h_pfmet_x_v_RescalingMETALSO[20];
  TH1F *h_type1calomet_x_v_RescalingMETALSO[20];
  TH1F *h_type2calomet_x_v_RescalingMETALSO[20];


  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_pf[20];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_pf[20];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_pf[20];

  TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[20];
  TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[20];
  TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[20];
  TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[20];

  TH2F *h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[20];
  TProfile *hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[20];

  TH2F *h_type2sumet_vs_type2met_bins_of_pfsumEt[20];
  TProfile *hprof_type2sumet_vs_type2met_bins_of_pfsumEt[20];

  if (debug_) cout<<"I get here, beginning of defining array histos "<<endl;

  for(int aii=0;aii<20;++aii){
    if (debug_) cout<<"I get here, beginning of array loop "<<endl;
    h_tcmet_x_v[aii] = new TH1F(Form("h_tcmet_x_%i",aii),"",10000,-100,100);
    h_pfmet_x_v[aii] = new TH1F(Form("h_pfmet_x_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v[aii] = new TH1F(Form("h_type1calomet_x_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v[aii] = new TH1F(Form("h_type2calomet_x_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_reco[aii] = new TH1F(Form("h_tcmet_x_reco_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_reco[aii] = new TH1F(Form("h_pfmet_x_reco_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_reco[aii] = new TH1F(Form("h_type1calomet_x_reco_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_reco[aii] = new TH1F(Form("h_type2calomet_x_reco_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_reco_pf[aii] = new TH1F(Form("h_tcmet_x_reco_pf_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type1calomet_x_reco_pf_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_reco_pf[aii] = new TH1F(Form("h_type2calomet_x_reco_pf_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type1calomet_x_reco_tc_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_reco_tc[aii] = new TH1F(Form("h_type2calomet_x_reco_tc_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_reco_type1[aii] = new TH1F(Form("h_tcmet_x_reco_type1_%i",aii),"",10000,-100,100);
    h_tcmet_x_v_reco_type2[aii] = new TH1F(Form("h_tcmet_x_reco_type2_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_reco_type1[aii] = new TH1F(Form("h_pfmet_x_reco_type1_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_reco_type2[aii] = new TH1F(Form("h_pfmet_x_reco_type2_%i",aii),"",10000,-100,100);

    h_pfmet_x_v_reco_tc[aii] = new TH1F(Form("h_pfmet_x_reco_tc_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_Rescaling[aii] = new TH1F(Form("h_tcmet_x_Rescaling_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_Rescaling[aii] = new TH1F(Form("h_pfmet_x_Rescaling_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type1calomet_x_Rescaling_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_Rescaling[aii] = new TH1F(Form("h_type2calomet_x_Rescaling_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_RescalingMETALSO[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_%i",aii),"",10000,-100,100);

    h_tcmet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii),"",10000,-100,100);


    h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",10000,-100,100);
    h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",10000,-100,100);
    h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",10000,-100,100);
    h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = new TH1F(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii),"",10000,-100,100);

    if (debug_) cout<<"I get here, near end of single array loop "<<endl;

    h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TH2F(Form("h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",200,0,200,200,0,200);
    hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[aii] = new TProfile(Form("hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt_%i",aii),"",20,0,100,0,200);

    h_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TH2F(Form("h_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",200,0,200,200,0,200);
    hprof_type2sumet_vs_type2met_bins_of_pfsumEt[aii] = new TProfile(Form("hprof_type2sumet_vs_type2met_bins_of_pfsumEt_%i",aii),"",20,0,100,0,200);


    if (debug_) cout<<"I get here, end of single array loop "<<endl;

  }

  if (debug_) cout<<"I get here, end of defining array histos "<<endl;


  TH1F *h_tcMET = new TH1F("h_tcMET","",200,0,200);
  TH1F *h_pfMET = new TH1F("h_pfMET","",200,0,200);
  TH1F *h_type1caloMET = new TH1F("h_type1caloMET","",200,0,200);
  TH1F *h_type2caloMET = new TH1F("h_type2caloMET","",200,0,200);

  TH2F *h_tcMET_vs_pfMET = new TH2F("h_tcMET_vs_pfMET","",200,0,200,200,0,200);
  TH2F *h_tcMET_vs_type1caloMET = new TH2F("h_tcMET_vs_type1caloMET","",200,0,200,200,0,200);
  TH2F *h_pfMET_vs_type1caloMET = new TH2F("h_pfMET_vs_type1caloMET","",200,0,200,200,0,200);
  TH2F *h_tcMET_vs_type2caloMET = new TH2F("h_tcMET_vs_type2caloMET","",200,0,200,200,0,200);
  TH2F *h_pfMET_vs_type2caloMET = new TH2F("h_pfMET_vs_type2caloMET","",200,0,200,200,0,200);

  TH1F *h_tcSUMET = new TH1F("h_tcSUMET","",400,0,400);
  TH1F *h_pfSUMET = new TH1F("h_pfSUMET","",400,0,400);
  TH1F *h_type1caloSUMET = new TH1F("h_type1caloSUMET","",400,0,400);
  TH1F *h_type2caloSUMET = new TH1F("h_type2caloSUMET","",400,0,400);

  TH2F *h_tcSUMET_vs_pfSUMET = new TH2F("h_tcSUMET_vs_pfSUMET","",400,0,400,400,0,400);
  TH2F *h_tcSUMET_vs_type1caloSUMET = new TH2F("h_tcSUMET_vs_type1caloSUMET","",400,0,400,400,0,400);
  TH2F *h_pfSUMET_vs_type1caloSUMET = new TH2F("h_pfSUMET_vs_type1caloSUMET","",400,0,400,400,0,400);
  TH2F *h_tcSUMET_vs_type2caloSUMET = new TH2F("h_tcSUMET_vs_type2caloSUMET","",400,0,400,400,0,400);
  TH2F *h_pfSUMET_vs_type2caloSUMET = new TH2F("h_pfSUMET_vs_type2caloSUMET","",400,0,400,400,0,400);
   

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
  h_genMETCalo = new TH1F("h_genMETCalo","",200,0,200);
  h_genMETTrue = new TH1F("h_genMETTrue","",200,0,200);
  h_genSUMETCalo = new TH1F("h_genSUMETCalo","",400,0,400);
  h_genSUMETTrue = new TH1F("h_genSUMETTrue","",400,0,400);
  
  h_genMETCalo_vs_pfMET = new TH2F("h_genMETCalo_vs_pfMET","",200,0,200,200,0,200);
  h_genMETCalo_vs_tcMET = new TH2F("h_genMETCalo_vs_tcMET","",200,0,200,200,0,200);
  h_genMETCalo_vs_type1caloMET = new TH2F("h_genMETCalo_vs_type1caloMET","",200,0,200,200,0,200);
  h_genMETCalo_vs_type2caloMET = new TH2F("h_genMETCalo_vs_type2caloMET","",200,0,200,200,0,200);
  
  h_genMETTrue_vs_pfMET = new TH2F("h_genMETTrue_vs_pfMET","",200,0,200,200,0,200);
  h_genMETTrue_vs_tcMET = new TH2F("h_genMETTrue_vs_tcMET","",200,0,200,200,0,200);
  h_genMETTrue_vs_type1caloMET = new TH2F("h_genMETTrue_vs_type1caloMET","",200,0,200,200,0,200);
  h_genMETTrue_vs_type2caloMET = new TH2F("h_genMETTrue_vs_type2caloMET","",200,0,200,200,0,200);
  
  h_pfSUMET_vs_genSUMETTrue = new TH2F("h_pfSUMET_vs_genSUMETTrue","",400,0,400,400,0,400);
  h_tcSUMET_vs_genSUMETTrue = new TH2F("h_tcSUMET_vs_genSUMETTrue","",400,0,400,400,0,400);
  h_type1caloSUMET_vs_genSUMETTrue = new TH2F("h_type1caloSUMET_vs_genSUMETTrue","",400,0,400,400,0,400);
  h_type2caloSUMET_vs_genSUMETTrue = new TH2F("h_type2caloSUMET_vs_genSUMETTrue","",400,0,400,400,0,400);
  
  h_pfSUMET_vs_genSUMETCalo = new TH2F("h_pfSUMET_vs_genSUMETCalo","",400,0,400,400,0,400);
  h_tcSUMET_vs_genSUMETCalo = new TH2F("h_tcSUMET_vs_genSUMETCalo","",400,0,400,400,0,400);
  h_type1caloSUMET_vs_genSUMETCalo = new TH2F("h_type1caloSUMET_vs_genSUMETCalo","",400,0,400,400,0,400);
  h_type2caloSUMET_vs_genSUMETCalo = new TH2F("h_type2caloSUMET_vs_genSUMETCalo","",400,0,400,400,0,400);
  
  hprof_tcsumet_vs_truegensumet  = new TProfile("hprof_tcsumet_vs_truegensumet","Profile of tcsumet vs. truegensumet",20,0,400,0,400);
  hprof_pfsumet_vs_truegensumet  = new TProfile("hprof_pfsumet_vs_truegensumet","Profile of pfsumet vs. truegensumet",20,0,400,0,400);
  hprof_type1sumet_vs_truegensumet  = new TProfile("hprof_type1sumet_vs_truegensumet","Profile of type1 calosumet vs. truegensumet",20,0,400,0,400);
  hprof_type2sumet_vs_truegensumet  = new TProfile("hprof_type2sumet_vs_truegensumet","Profile of type1 calosumet vs. truegensumet",20,0,400,0,400);
  
  hprof_tcsumet_vs_calogensumet  = new TProfile("hprof_tcsumet_vs_calogensumet","Profile of tcsumet vs. calogensumet",20,0,400,0,400);
  hprof_pfsumet_vs_calogensumet  = new TProfile("hprof_pfsumet_vs_calogensumet","Profile of pfsumet vs. calogensumet",20,0,400,0,400);
  hprof_type1sumet_vs_calogensumet  = new TProfile("hprof_type1sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet",20,0,400,0,400);
  hprof_type2sumet_vs_calogensumet  = new TProfile("hprof_type2sumet_vs_calogensumet","Profile of type1 calosumet vs. calogensumet",20,0,400,0,400);
  //}
  
  TH2F *h_pfsumet_vs_dijetavg = new TH2F("h_pfsumet_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_tcsumet_vs_dijetavg = new TH2F("h_tcsumet_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_type1sumet_vs_dijetavg = new TH2F("h_type1sumet_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_type2sumet_vs_dijetavg = new TH2F("h_type2sumet_vs_dijetavg","",200,0,200,500,0,5);



  TProfile *hprof_tcsumet_vs_dijetavg  = new TProfile("hprof_tcsumet_vs_dijetavg","Profile of tcsumet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_pfsumet_vs_dijetavg  = new TProfile("hprof_pfsumet_vs_dijetavg","Profile of pfsumet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_type1sumet_vs_dijetavg  = new TProfile("hprof_type1sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_type2sumet_vs_dijetavg  = new TProfile("hprof_type2sumet_vs_dijetavg","Profile of type1 calosumet vs. dijetavg",20,0,200,0,10);



  TH2F *h_pfmet_vs_dijetavg = new TH2F("h_pfmet_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_tcmet_vs_dijetavg = new TH2F("h_tcmet_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_type1met_vs_dijetavg = new TH2F("h_type1met_vs_dijetavg","",200,0,200,500,0,5);
  TH2F *h_type2met_vs_dijetavg = new TH2F("h_type2met_vs_dijetavg","",200,0,200,500,0,5);



  TProfile *hprof_tcmet_vs_dijetavg  = new TProfile("hprof_tcmet_vs_dijetavg","Profile of tcmet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_pfmet_vs_dijetavg  = new TProfile("hprof_pfmet_vs_dijetavg","Profile of pfmet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_type1met_vs_dijetavg  = new TProfile("hprof_type1met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",20,0,200,0,10);
  TProfile *hprof_type2met_vs_dijetavg  = new TProfile("hprof_type2met_vs_dijetavg","Profile of type1 calomet vs. dijetavg",20,0,200,0,10);

  if (debug_) cout<<"I get here, end of defining histos "<<endl;

  //----------------------------------------------------------
  //Initializing variables to count events passing certain requirements
  //----------------------------------------------------------
  double bins[21] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};


  //----------------------------------------------------------     
  //Number of events to loop over
  //----------------------------------------------------------
  Int_t nentries = (Int_t)fChain->GetEntries();
  //Long64_t nentries = fChain->GetEntriesFast();
  out<<"The number of entries is: "<<nentries<<endl;
  if (debug_) cout<<"The number of entries is: "<<nentries<<endl;
   
  //----------------------------------------------------------
  //Main Event loop
  //----------------------------------------------------------
  int counting_number_events_passing_cuts = 0;
  int count_number_trigger = 0;

  for(int ia = 0; ia<nentries;++ia){

    if (debug_) cout<<"trying to get entry "<<ia<<"... ";
    fChain->GetEntry(ia);
    if (debug_) cout<<"success!"<<endl;
     
    bool expType=true;
    if(expType){
       
      ++count_number_trigger;
       
      //bool isJet = false;
       
      int count_number_jets = 0;
      double first_highest_jet_pt  = -999;
      int first_highest_location   = -999;
      double second_highest_jet_pt = -999;

      if (debug_) cout<<"looping over the "<<NJets<<" jets to find the highest pt jet"<<endl;
      
      for(int aia = 0;aia<NJets;++aia){
	if (debug_) cout<<"jet "<<aia;
	//do JetID here?
	//if(!JetIDLoose->at(aia))
	if (debug_) printf(": pt: %2.2f  eta: %2.2f\n",JetP4->at(aia).Pt(), JetP4->at(aia).Eta());
	if(fabs(JetP4->at(aia).Eta())<3)
	  if (JetP4->at(aia).Pt()>25){
	  if (debug_) cout<<", passed minimal eta/pt cuts ";
	
	  ++count_number_jets;     
	   
	  if(JetP4->at(aia).Pt()>first_highest_jet_pt){
	    if (debug_) cout<<", is highest pt jet encountered ";
	    first_highest_jet_pt=JetP4->at(aia).Pt();
	    first_highest_location=aia;
	  }//end of looking for highest pt jet
	}//if requirement for pt and eta
	if (debug_) cout<<endl;
      }//end of for loop over jets
       
      if (debug_) cout<<"looping over the jets to find the 2nd highest pt jet"<<endl;
      for(int aia = 0;aia<NJets;++aia){
	if (debug_) cout<<"jet "<<aia<<endl;
	if(!JetIDLoose->at(aia))
	  {if (debug_) cout<<"There is a problem with jet Id"<<endl;}
	if(fabs(JetP4->at(aia).Eta())<3&&JetP4->at(aia).Pt()>25){
	   
	  if(aia!=first_highest_location&&JetP4->at(aia).Pt()>second_highest_jet_pt){
	    second_highest_jet_pt=JetP4->at(aia).Pt();
	  }//end of looking for highest pt jet
	}//if requirement for pt and eta
      }//end of for loop over jets
       
      double dijet_avg = (first_highest_jet_pt+second_highest_jet_pt)/2;
      
      if (debug_) cout<<"done looping over the jets"<<endl;

      bool dijets = false;
      if(count_number_jets>1)
	dijets=true;
      //	       dijets = true;
      if(dijets){
	if (debug_) cout<<"I get past the jet cuts"<<endl;
	//passed all cuts
	++counting_number_events_passing_cuts;
	 
	double tcmet = 0; 
	double tcsumet = 0;
	double tcmet_x = 0;
	double tcmet_y = 0;
	double pfmet = 0; 
	double pfsumet = 0; 
	double pfmet_x = 0; 
	double pfmet_y = 0; 
	double type1calomet = 0; 
	double type2calomet = 0; 
	double tcphi = -999;
	double pfphi = -999;
	double type1calophi = -999;
	     
	double type1calomet_x = 0; 
	double type1calomet_y = 0; 
	double type1calosumet = 0; 
	     
	double type2calophi = -999;
	     
	double type2calomet_x = 0; 
	double type2calomet_y = 0; 
	double type2calosumet = 0; 
	     
	double truegenmet   = -999; 
	double truegenmetet = -999; 

	double calogenmet   = -999; 
	double calogenmetet = -999; 
	     
	//if (debug_) cout<<"The tcmets_et size is: "<<tcmets_et->size()<<endl;
	tcphi = TCMETP4->Phi();
	tcmet = TCMETP4->Pt();
	tcsumet = TCMETsumEt;
	tcmet_x = TCMETP4->Px();
	tcmet_y = TCMETP4->Py();
	   
	//if (debug_) cout<<"The pfmets_et size is: "<<pfmets_et->size()<<endl;
	pfphi = PFMETP4->Phi();
	pfmet = PFMETP4->Pt();
	pfsumet = PFMETsumEt;
	pfmet_x = PFMETP4->Px();
	pfmet_y = PFMETP4->Py();
	     
	//if (debug_) cout<<"The type1mets_et size is: "<<type1calomets_et->size()<<endl;
	type1calophi = CaloTypeIMETP4->Phi();
	type1calomet = CaloTypeIMETP4->Pt();
	type1calosumet = CaloTypeIMETsumEt;
	type1calomet_x = CaloTypeIMETP4->Px();
	type1calomet_y = CaloTypeIMETP4->Py();
	     
	type2calophi = CaloTypeIIMETP4->Phi();
	type2calomet = CaloTypeIIMETP4->Pt();
	type2calosumet = CaloTypeIIMETsumEt;
	type2calomet_x = CaloTypeIIMETP4->Px();
	type2calomet_y = CaloTypeIIMETP4->Py();
	     
	//		 if (debug_) cout<<"The genCalomets_et size is: "<<genCalomets_et->size()<<endl;
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

	for(int itb=0;itb<20;++itb){
	  if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]){
	    h_tcmet_x_v_reco[itb]->Fill(tcmet_x);
	    h_tcmet_x_v_reco[itb]->Fill(tcmet_y);
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]){
	    h_pfmet_x_v_reco[itb]->Fill(pfmet_x);
	    h_pfmet_x_v_reco[itb]->Fill(pfmet_y);
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]){
	    h_type1calomet_x_v_reco[itb]->Fill(type1calomet_x);
	    h_type1calomet_x_v_reco[itb]->Fill(type1calomet_y);
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(type2calosumet>=bins[itb]&&type2calosumet<bins[itb+1]){
	    h_type2calomet_x_v_reco[itb]->Fill(type2calomet_x);
	    h_type2calomet_x_v_reco[itb]->Fill(type2calomet_y);
	  }
	}
	     
	     
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]){
	    h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_x);
	    h_type1calomet_x_v_reco_pf[itb]->Fill(type1calomet_y);
	  }
	}
	     
	for(int itb=0;itb<20;++itb){
	  if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]){
	    h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_x);
	    h_tcmet_x_v_reco_pf[itb]->Fill(tcmet_y);
	    h_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet);
	    hprof_type2sumet_vs_type2met_bins_of_pfsumEt[itb]->Fill(type2calomet,type2calosumet,1);
		 
		 
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]){
	    h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_x);
	    h_tcmet_x_v_reco_type1[itb]->Fill(tcmet_y);
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]){
	    h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_x);
	    h_type1calomet_x_v_reco_tc[itb]->Fill(type1calomet_y);
	  }
	}
	     
	     
	for(int itb=0;itb<20;++itb){
	  if(tcsumet>=bins[itb]&&tcsumet<bins[itb+1]){
	    h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_x);
	    h_pfmet_x_v_reco_tc[itb]->Fill(pfmet_y);
	  }
	}
		 
		 
	for(int itb=0;itb<20;++itb){
	  if(type1calosumet>=bins[itb]&&type1calosumet<bins[itb+1]){
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
	if(scale_type==0){
	  rescaledtype1calosumet = type1calosumet*2.6056-33.300;
	  rescaledtype2calosumet = type2calosumet*1.217-29.699;
	  rescaledpfsumet = pfsumet*1.417-6.176;
	  rescaledtcsumet = tcsumet*1.666-1.284;
	}


	//For FullSimPythia8
	if(scale_type==1){
	  /*
	    rescaledtcsumet = tcsumet*1.607-6.559;
	    rescaledpfsumet = pfsumet*1.275-5.487;
	    rescaledtype1calosumet = type1calosumet*2.279-52.496;
	    rescaledtype2calosumet = type2calosumet*1.163-20.08;
	  */
	  //These are for FullSim correction
	  rescaledtype1calosumet = type1calosumet*2.112-55.396;
	  rescaledtype2calosumet = type2calosumet*1.170-25.287;
	  rescaledtcsumet = tcsumet*1.581-10.737;
	  //		   rescaledpfsumet = pfsumet*1.254-7.4567;
	  //below is for FastSim correction
	  rescaledpfsumet = pfsumet*1.400-16.57;

	}

	//For FullSimTuneD6T
	if(scale_type==2){
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
	if(scale_type==3){
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

	double pt_photon_bins[17] = {0,19.9475,24.3339,29.6389,36.0547,43.8141,53.1982,64.5475,78.2732,94.8732,114.949,139.229,168.593,204.107,247.056,299.9999,1000};

	double pt_rescale_tc[16] = {0.788873,0.786946,0.791559,0.808645,0.822854,0.841836,0.854884,0.864537,0.882782,0.892939,0.920738,0.924707,0.939333,0.939326,0.971899,0.929645};
	double pt_rescale_pf[16] = {0.906095,0.904362,0.907742,0.920871,0.925145,0.935496,0.939409,0.936432,0.937474,0.939678,0.948415,0.934699,0.944803,0.934277,0.932801,0.880993};
	double pt_rescale_type1[16] = {0.744853,0.777192,0.831074,0.8946,0.929688,0.966164,0.981742,0.989977,0.999186,1.00557,1.01076,0.99985,0.991945,1.0028,0.995419,0.928936};
		 
	double pt_rescale_type2[16] = {1.03931,1.04369,1.03908,1.0499,1.04997,1.06003,1.05406,1.05361,1.04718,1.05128,1.04572,1.04194,1.01565,1.02073,1.02455,0.965356};

	for(int aig = 0;aig<16;++aig){
	  if(type1calomet<pt_photon_bins[aig+1]&&type1calomet>pt_photon_bins[aig]){
	    rescaledtype1met=type1calomet/pt_rescale_type1[aig];}

	  if(pfmet<pt_photon_bins[aig+1]&&pfmet>pt_photon_bins[aig]){
	    rescaledpfmet=pfmet/pt_rescale_pf[aig];}

	  if(tcmet<pt_photon_bins[aig+1]&&tcmet>pt_photon_bins[aig]){
	    rescaledtcmet=tcmet/pt_rescale_tc[aig];}

	  if(type2calomet<pt_photon_bins[aig+1]&&type2calomet>pt_photon_bins[aig]){
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


	//		 if (debug_) cout<<"The met x from ntuple is: "<<pfmet_x<<endl;
	// if (debug_) cout<<"The met x from MET is: "<<pfmet*TMath::Cos(pfphi)<<endl;



	//Plotting rescaled met vs. gen sumEt for each algorithm

	if (!isData_) {
	  for(int itb=0;itb<20;++itb){
	    //// using GenMETTrue
	    //if(truegenmetet>=bins[itb]&&truegenmetet<bins[itb+1]){
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
	    if(calogenmetet>=bins[itb]&&calogenmetet<bins[itb+1]){
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

		 
	for(int itb=0;itb<20;++itb){
	  if(rescaledtype2calosumet>=bins[itb]&&rescaledtype2calosumet<bins[itb+1]){
	    h_type2calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype2met_x);
	    h_type2calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype2met_y);
		     
	    h_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet);
	    hprof_pfsumet_vs_type2_met_bins_of_type2correctedsumEt[itb]->Fill(type2calomet,pfsumet,1);

	  }
	}


	for(int itb=0;itb<20;++itb){
	  if(rescaledtcsumet>=bins[itb]&&rescaledtcsumet<bins[itb+1]){
	    h_tcmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtcmet_x);
	    h_tcmet_x_v_RescalingMETALSO[itb]->Fill(rescaledtcmet_y);
	  }
	}
		 

	for(int itb=0;itb<20;++itb){
	  if(rescaledpfsumet>=bins[itb]&&rescaledpfsumet<bins[itb+1]){
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
		 
		 

	for(int itb=0;itb<20;++itb){
	  if(pfsumet>=bins[itb]&&pfsumet<bins[itb+1]){
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
		 




	for(int itb=0;itb<20;++itb){
	  if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]){
	    h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_x);
	    h_type1calomet_x_v_RescalingMETALSO[itb]->Fill(rescaledtype1met_y);
	  }
	}

		 

	for(int itb=0;itb<20;++itb){
	  if(rescaledtcsumet>=bins[itb]&&rescaledtcsumet<bins[itb+1]){
	    h_tcmet_x_v_Rescaling[itb]->Fill(tcmet_x);
	    h_tcmet_x_v_Rescaling[itb]->Fill(tcmet_y);
	  }
	}
		 

	for(int itb=0;itb<20;++itb){
	  if(rescaledpfsumet>=bins[itb]&&rescaledpfsumet<bins[itb+1]){
	    h_pfmet_x_v_Rescaling[itb]->Fill(pfmet_x);
	    h_pfmet_x_v_Rescaling[itb]->Fill(pfmet_y);
	  }
	}
		 
		 
	for(int itb=0;itb<20;++itb){
	  if(rescaledtype1calosumet>=bins[itb]&&rescaledtype1calosumet<bins[itb+1]){
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
		 
	//if (!isData_) {
	h_genMETTrue_vs_pfMET->Fill(pfsumet,truegenmetet);
	h_genMETTrue_vs_tcMET->Fill(tcsumet,truegenmetet);
	h_genMETTrue_vs_type1caloMET->Fill(type1calosumet,truegenmetet);
	
	
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
	
	
	h_pfSUMET_vs_genSUMETCalo->Fill(calogenmetet,pfsumet);
	h_tcSUMET_vs_genSUMETCalo->Fill(calogenmetet,tcsumet);
	h_type1caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type1calosumet);
	h_type2caloSUMET_vs_genSUMETCalo->Fill(calogenmetet,type2calosumet);
	
	hprof_tcsumet_vs_calogensumet->Fill(calogenmetet,tcsumet,1);
	hprof_pfsumet_vs_calogensumet->Fill(calogenmetet,pfsumet,1);
	hprof_type1sumet_vs_calogensumet->Fill(calogenmetet,type1calosumet,1);
	hprof_type2sumet_vs_calogensumet->Fill(calogenmetet,type2calosumet,1);
	//}
	
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

      }//end of loop for requiring two jets
    }//
  }//end over loop over all the events
  
  
  if (debug_) cout<<"count the number of events passing the trigger cuts"<<count_number_trigger<<endl;
  if (debug_) cout<<"The number of events passing all the cuts are: "<<counting_number_events_passing_cuts<<endl;
  
  //----------------------------------------------------------     
  //Write out histogram file
  //----------------------------------------------------------      
  outfile->cd();
  outfile->Write();
   
}



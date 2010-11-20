#include "TMath.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include <iostream>
#include <fstream>
#include "TString.h"
#include "TVector3.h"
#include "TGraphAsymmErrors.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TProfile.h"
using namespace std;

//void METResolutionCalculation(TString input_filename, TString output_filename, double cross_section_pb, int scale_type)
void METResolutionCalculation(TString input_filename)
{   
  
  //----------------------------------------------------------
  //Define output file
  //----------------------------------------------------------
  TString output_filename = input_filename+"_out";
  TString file_name = input_filename+".root";

  TString root_name = output_filename+".root";
  TString text_name = output_filename+".txt";
  TFile *infile = new TFile(file_name.Data(),"OPEN");
  TFile *outfile = new TFile(root_name.Data(),"RECREATE");
  std::cout<<"input file: "<<file_name<<" "<<infile<<std::endl;
  std::cout<<"output file: "<<root_name<<" "<<outfile<<std::endl;
  infile->cd();
  
  
  ofstream out;
  
  out.open(text_name.Data(), ios::out | ios::app);
  

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

   cout<<"I get here, beginning of defining array histos "<<endl;

   for(int aii=0;aii<20;aii++){
     cout<<"I get here, beginning of array loop "<<endl;
     h_tcmet_x_v[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_%i",aii));
     std::cout<<"h_tcmet_x_v["<<aii<<"] = "<<h_tcmet_x_v[aii]<<std::endl;
     h_pfmet_x_v[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_%i",aii));
     std::cout<<"h_pfmet_x_v["<<aii<<"] = "<<h_pfmet_x_v[aii]<<std::endl;
     h_type1calomet_x_v[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_%i",aii));
     std::cout<<"h_type1calomet_x_v["<<aii<<"] = "<<h_type1calomet_x_v[aii]<<std::endl;
     h_type2calomet_x_v[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_%i",aii));
     std::cout<<"h_type2calomet_x_v["<<aii<<"] = "<<h_type2calomet_x_v[aii]<<std::endl;

     h_tcmet_x_v_reco[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_%i",aii));
     std::cout<<"h_tcmet_x_v_reco["<<aii<<"] = "<<h_tcmet_x_v_reco[aii]<<std::endl;
     h_pfmet_x_v_reco[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_reco_%i",aii));
     std::cout<<"h_pfmet_x_v_reco["<<aii<<"] = "<<h_pfmet_x_v_reco[aii]<<std::endl;
     h_type1calomet_x_v_reco[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_%i",aii));
     std::cout<<"h_type1calomet_x_v_reco["<<aii<<"] = "<<h_type1calomet_x_v_reco[aii]<<std::endl;
     h_type2calomet_x_v_reco[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_%i",aii));
     std::cout<<"h_type2calomet_x_v_reco["<<aii<<"] = "<<h_type2calomet_x_v_reco[aii]<<std::endl;

     h_tcmet_x_v_reco_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_pf_%i",aii));
     std::cout<<"h_tcmet_x_v_reco_pf["<<aii<<"] = "<<h_tcmet_x_v_reco_pf[aii]<<std::endl;
     h_type1calomet_x_v_reco_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_pf_%i",aii));
     std::cout<<"h_type1calomet_x_v_reco_pf["<<aii<<"] = "<<h_type1calomet_x_v_reco_pf[aii]<<std::endl;
     h_type2calomet_x_v_reco_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_pf_%i",aii));
     std::cout<<"h_type2calomet_x_v_reco_pf["<<aii<<"] = "<<h_type2calomet_x_v_reco_pf[aii]<<std::endl;
     h_type1calomet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_tc_%i",aii));
     std::cout<<"h_type1calomet_x_v_reco_tc["<<aii<<"] = "<<h_type1calomet_x_v_reco_tc[aii]<<std::endl;
     h_type2calomet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_tc_%i",aii));
     std::cout<<"h_type2calomet_x_v_reco_tc["<<aii<<"] = "<<h_type2calomet_x_v_reco_tc[aii]<<std::endl;

     h_tcmet_x_v_reco_type1[aii] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type1_%i",aii));
     std::cout<<"h_tcmet_x_v_reco_type1["<<aii<<"] = "<<h_tcmet_x_v_reco_type1[aii]<<std::endl;
     h_tcmet_x_v_reco_type2[aii] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type2_%i",aii));
     std::cout<<"h_tcmet_x_v_reco_type2["<<aii<<"] = "<<h_tcmet_x_v_reco_type2[aii]<<std::endl;
     h_pfmet_x_v_reco_type1[aii] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type1_%i",aii));
     std::cout<<"h_pfmet_x_v_reco_type1["<<aii<<"] = "<<h_pfmet_x_v_reco_type1[aii]<<std::endl;
     h_pfmet_x_v_reco_type2[aii] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type2_%i",aii));
     std::cout<<"h_pfmet_x_v_reco_type2["<<aii<<"] = "<<h_pfmet_x_v_reco_type2[aii]<<std::endl;

     h_pfmet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_tc_%i",aii));
     std::cout<<"h_pfmet_x_v_reco_tc["<<aii<<"] = "<<h_pfmet_x_v_reco_tc[aii]<<std::endl;

     h_tcmet_x_v_Rescaling[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_Rescaling_%i",aii));
     std::cout<<"h_tcmet_x_v_Rescaling["<<aii<<"] = "<<h_tcmet_x_v_Rescaling[aii]<<std::endl;
     h_pfmet_x_v_Rescaling[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_Rescaling_%i",aii));
     std::cout<<"h_pfmet_x_v_Rescaling["<<aii<<"] = "<<h_pfmet_x_v_Rescaling[aii]<<std::endl;
     h_type1calomet_x_v_Rescaling[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_Rescaling_%i",aii));
     std::cout<<"h_type1calomet_x_v_Rescaling["<<aii<<"] = "<<h_type1calomet_x_v_Rescaling[aii]<<std::endl;
     h_type2calomet_x_v_Rescaling[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_Rescaling_%i",aii));
     std::cout<<"h_type2calomet_x_v_Rescaling["<<aii<<"] = "<<h_type2calomet_x_v_Rescaling[aii]<<std::endl;

     h_tcmet_x_v_RescalingMETALSO[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_%i",aii));
     std::cout<<"h_tcmet_x_v_RescalingMETALSO["<<aii<<"] = "<<h_tcmet_x_v_RescalingMETALSO[aii]<<std::endl;
     h_pfmet_x_v_RescalingMETALSO[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_%i",aii));
     std::cout<<"h_pfmet_x_v_RescalingMETALSO["<<aii<<"] = "<<h_pfmet_x_v_RescalingMETALSO[aii]<<std::endl;
     h_type1calomet_x_v_RescalingMETALSO[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_%i",aii));
     std::cout<<"h_type1calomet_x_v_RescalingMETALSO["<<aii<<"] = "<<h_type1calomet_x_v_RescalingMETALSO[aii]<<std::endl;
     h_type2calomet_x_v_RescalingMETALSO[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_%i",aii));
     std::cout<<"h_type2calomet_x_v_RescalingMETALSO["<<aii<<"] = "<<h_type2calomet_x_v_RescalingMETALSO[aii]<<std::endl;

     h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii));
     std::cout<<"h_tcmet_x_v_RescalingMETALSO_vs_pf["<<aii<<"] = "<<h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]<<std::endl;
     h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_pf_%i",aii));
     std::cout<<"h_type1calomet_x_v_RescalingMETALSO_vs_pf["<<aii<<"] = "<<h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]<<std::endl;
     h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii));
     std::cout<<"h_type2calomet_x_v_RescalingMETALSO_vs_pf["<<aii<<"] = "<<h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]<<std::endl;


     h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     std::cout<<"h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf["<<aii<<"] = "<<h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]<<std::endl;
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     std::cout<<"h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf["<<aii<<"] = "<<h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]<<std::endl;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     std::cout<<"h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf["<<aii<<"] = "<<h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]<<std::endl;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     std::cout<<"h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf["<<aii<<"] = "<<h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]<<std::endl;

     cout<<"I get here, near end of single array loop "<<endl;


     cout<<"I get here, end of single array loop "<<endl;

   }

   cout<<"I get here, end of defining array histos "<<endl;


   //TH1F *h_tcMET        = (TH1F*)infile->Get("h_tcMET");
   //TH1F *h_pfMET        = (TH1F*)infile->Get("h_pfMET");
   //TH1F *h_type1caloMET = (TH1F*)infile->Get("h_type1caloMET");
   //TH1F *h_type2caloMET = (TH1F*)infile->Get("h_type2caloMET");
   //
   //TH1F *h_METCalogen = (TH1F*)infile->Get("h_METCalogen");
   //TH1F *h_METTruegen = (TH1F*)infile->Get("h_METTruegen");
   //
   //TH2F *h_tcMET_vs_pfMET        = (TH2F*)infile->Get("h_tcMET_vs_pfMET");
   //TH2F *h_tcMET_vs_type1caloMET = (TH2F*)infile->Get("h_tcMET_vs_type1caloMET");
   //TH2F *h_pfMET_vs_type1caloMET = (TH2F*)infile->Get("h_pfMET_vs_type1caloMET");
   //TH2F *h_tcMET_vs_type2caloMET = (TH2F*)infile->Get("h_tcMET_vs_type2caloMET");
   //TH2F *h_pfMET_vs_type2caloMET = (TH2F*)infile->Get("h_pfMET_vs_type2caloMET");
   //
   //TH1F *h_tcSUMET        = (TH1F*)infile->Get("h_tcSUMET");
   //TH1F *h_pfSUMET        = (TH1F*)infile->Get("h_pfSUMET");
   //TH1F *h_type1caloSUMET = (TH1F*)infile->Get("h_type1caloSUMET");
   //TH1F *h_type2caloSUMET = (TH1F*)infile->Get("h_type2caloSUMET");
   //
   //TH1F *h_SUMETCalogen = (TH1F*)infile->Get("h_SUMETCalogen");
   //TH1F *h_SUMETTruegen = (TH1F*)infile->Get("h_SUMETTruegen");
   //
   //TH2F *h_tcSUMET_vs_pfSUMET        = (TH2F*)infile->Get("h_tcSUMET_vs_pfSUMET");
   //TH2F *h_tcSUMET_vs_type1caloSUMET = (TH2F*)infile->Get("h_tcSUMET_vs_type1caloSUMET");
   //TH2F *h_pfSUMET_vs_type1caloSUMET = (TH2F*)infile->Get("h_pfSUMET_vs_type1caloSUMET");
   //TH2F *h_tcSUMET_vs_type2caloSUMET = (TH2F*)infile->Get("h_tcSUMET_vs_type2caloSUMET");
   //TH2F *h_pfSUMET_vs_type2caloSUMET = (TH2F*)infile->Get("h_pfSUMET_vs_type2caloSUMET");
   //
   //TH2F *h_CalogenMET_vs_pfMET        = (TH2F*)infile->Get("h_CalogenMET_vs_pfMET");
   //TH2F *h_CalogenMET_vs_tcMET        = (TH2F*)infile->Get("h_CalogenMET_vs_tcMET");
   //TH2F *h_CalogenMET_vs_type1caloMET = (TH2F*)infile->Get("h_CalogenMET_vs_type1caloMET");
   //TH2F *h_CalogenMET_vs_type2caloMET = (TH2F*)infile->Get("h_CalogenMET_vs_type2caloMET");
   //
   //TH2F *h_TruegenMET_vs_pfMET        = (TH2F*)infile->Get("h_TruegenMET_vs_pfMET");
   //TH2F *h_TruegenMET_vs_tcMET        = (TH2F*)infile->Get("h_TruegenMET_vs_tcMET");
   //TH2F *h_TruegenMET_vs_type1caloMET = (TH2F*)infile->Get("h_TruegenMET_vs_type1caloMET");
   //TH2F *h_TruegenMET_vs_type2caloMET = (TH2F*)infile->Get("h_TruegenMET_vs_type2caloMET");
   //
   //TH2F *h_pfSUMET_vs_TruegenSUMET        = (TH2F*)infile->Get("h_pfSUMET_vs_TruegenSUMET");
   //TH2F *h_tcSUMET_vs_TruegenSUMET        = (TH2F*)infile->Get("h_tcSUMET_vs_TruegenSUMET");
   //TH2F *h_type1caloSUMET_vs_TruegenSUMET = (TH2F*)infile->Get("h_type1caloSUMET_vs_TruegenSUMET");
   //TH2F *h_type2caloSUMET_vs_TruegenSUMET = (TH2F*)infile->Get("h_type2caloSUMET_vs_TruegenSUMET");
   //
   //TH2F *h_pfSUMET_vs_CalogenSUMET        = (TH2F*)infile->Get("h_pfSUMET_vs_CalogenSUMET");
   //TH2F *h_tcSUMET_vs_CalogenSUMET        = (TH2F*)infile->Get("h_tcSUMET_vs_CalogenSUMET");
   //TH2F *h_type1caloSUMET_vs_CalogenSUMET = (TH2F*)infile->Get("h_type1caloSUMET_vs_CalogenSUMET");
   //TH2F *h_type2caloSUMET_vs_CalogenSUMET = (TH2F*)infile->Get("h_type2caloSUMET_vs_CalogenSUMET");
   //
   //TH2F *h_tcmet_x_vs_truegenmetet = (TH2F*)infile->Get("h_tcmet_x_vs_truegenmetet");
   //TH2F *h_tcmet_x_vs_calogenmetet = (TH2F*)infile->Get("h_tcmet_x_vs_calogenmetet");
   //
   //TProfile *hprof_tcsumet_vs_truegensumet     = (TProfile*)infile->Get("hprof_tcsumet_vs_truegensumet");
   //TProfile *hprof_pfsumet_vs_truegensumet     = (TProfile*)infile->Get("hprof_pfsumet_vs_truegensumet");
   //TProfile *hprof_type1sumet_vs_truegensumet  = (TProfile*)infile->Get("hprof_type1sumet_vs_truegensumet");
   //TProfile *hprof_type2sumet_vs_truegensumet  = (TProfile*)infile->Get("hprof_type2sumet_vs_truegensumet");
   //
   //TProfile *hprof_tcsumet_vs_calogensumet     = (TProfile*)infile->Get("hprof_tcsumet_vs_calogensumet");
   //TProfile *hprof_pfsumet_vs_calogensumet     = (TProfile*)infile->Get("hprof_pfsumet_vs_calogensumet");
   //TProfile *hprof_type1sumet_vs_calogensumet  = (TProfile*)infile->Get("hprof_type1sumet_vs_calogensumet");
   //TProfile *hprof_type2sumet_vs_calogensumet  = (TProfile*)infile->Get("hprof_type2sumet_vs_calogensumet");
   //
   //
   //
   //TH2F *h_pfsumet_vs_dijetavg    = (TH2F*)infile->Get("h_pfsumet_vs_dijetavg");
   //TH2F *h_tcsumet_vs_dijetavg    = (TH2F*)infile->Get("h_tcsumet_vs_dijetavg");
   //TH2F *h_type1sumet_vs_dijetavg = (TH2F*)infile->Get("h_type1sumet_vs_dijetavg");
   //TH2F *h_type2sumet_vs_dijetavg = (TH2F*)infile->Get("h_type2sumet_vs_dijetavg");
   //
   //
   //
   //TProfile *hprof_tcsumet_vs_dijetavg     = (TProfile*)infile->Get("hprof_tcsumet_vs_dijetavg");
   //TProfile *hprof_pfsumet_vs_dijetavg     = (TProfile*)infile->Get("hprof_pfsumet_vs_dijetavg");
   //TProfile *hprof_type1sumet_vs_dijetavg  = (TProfile*)infile->Get("hprof_type1sumet_vs_dijetavg");
   //TProfile *hprof_type2sumet_vs_dijetavg  = (TProfile*)infile->Get("hprof_type2sumet_vs_dijetavg");
   //
   //
   //
   //TH2F *h_pfmet_vs_dijetavg    = (TH2F*)infile->Get("h_pfmet_vs_dijetavg");
   //TH2F *h_tcmet_vs_dijetavg    = (TH2F*)infile->Get("h_tcmet_vs_dijetavg");
   //TH2F *h_type1met_vs_dijetavg = (TH2F*)infile->Get("h_type1met_vs_dijetavg");
   //TH2F *h_type2met_vs_dijetavg = (TH2F*)infile->Get("h_type2met_vs_dijetavg");
   //
   //
   //
   //TProfile *hprof_tcmet_vs_dijetavg     = (TProfile*)infile->Get("hprof_tcmet_vs_dijetavg");
   //TProfile *hprof_pfmet_vs_dijetavg     = (TProfile*)infile->Get("hprof_pfmet_vs_dijetavg");
   //TProfile *hprof_type1met_vs_dijetavg  = (TProfile*)infile->Get("hprof_type1met_vs_dijetavg");
   //TProfile *hprof_type2met_vs_dijetavg  = (TProfile*)infile->Get("hprof_type2met_vs_dijetavg");

   outfile->cd();

   cout<<"I get here, starting to define the new histograms"<<endl;


   TH1F *h_tcmet_RMS_vs_truegensumet        = new TH1F("h_tcmet_RMS_vs_truegensumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_truegensumet        = new TH1F("h_pfmet_RMS_vs_truegensumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_truegensumet = new TH1F("h_type1calomet_RMS_vs_truegensumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_truegensumet = new TH1F("h_type2calomet_RMS_vs_truegensumet","",20,0,400);

   TH1F *h_tcmet_RMS_vs_calogensumet        = new TH1F("h_tcmet_RMS_vs_calogensumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_calogensumet        = new TH1F("h_pfmet_RMS_vs_calogensumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_calogensumet = new TH1F("h_type1calomet_RMS_vs_calogensumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_calogensumet = new TH1F("h_type2calomet_RMS_vs_calogensumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_recosumet        = new TH1F("h_tcmet_RMS_vs_recosumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_recosumet        = new TH1F("h_pfmet_RMS_vs_recosumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_recosumet = new TH1F("h_type1calomet_RMS_vs_recosumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_recosumet = new TH1F("h_type2calomet_RMS_vs_recosumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_pfrecosumet        = new TH1F("h_tcmet_RMS_vs_pfrecosumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_pfrecosumet = new TH1F("h_type1calomet_RMS_vs_pfrecosumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_pfrecosumet = new TH1F("h_type2calomet_RMS_vs_pfrecosumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_type1recosumet     = new TH1F("h_tcmet_RMS_vs_type1recosumet","",20,0,400);
   TH1F *h_tcmet_RMS_vs_type2recosumet     = new TH1F("h_tcmet_RMS_vs_type2recosumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_tcrecosumet = new TH1F("h_type1calomet_RMS_vs_tcrecosumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_tcrecosumet = new TH1F("h_type2calomet_RMS_vs_tcrecosumet","",20,0,400);


   TH1F *h_pfmet_RMS_vs_type1recosumet = new TH1F("h_pfmet_RMS_vs_type1recosumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_type2recosumet = new TH1F("h_pfmet_RMS_vs_type2recosumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_tcrecosumet    = new TH1F("h_pfmet_RMS_vs_tcrecosumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_Rescalingsumet        = new TH1F("h_tcmet_RMS_vs_Rescalingsumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_Rescalingsumet        = new TH1F("h_pfmet_RMS_vs_Rescalingsumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_Rescalingsumet = new TH1F("h_type1calomet_RMS_vs_Rescalingsumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_Rescalingsumet = new TH1F("h_type2calomet_RMS_vs_Rescalingsumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet","",20,0,400);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet        = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_RescalingMETALSOsumet = new TH1F("h_type1calomet_RMS_vs_RescalingMETALSOsumet","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet","",20,0,400);


   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_pf = new TH1F("h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_pf","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf","",20,0,400);



   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",20,0,400);
   TH1F *h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf = new TH1F("h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",20,0,400);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",20,0,400);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf        = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",20,0,400);


   cout<<"I get here, end of defining histos "<<endl;

   //----------------------------------------------------------
   //Initializing variables to count events passing certain requirements
   //----------------------------------------------------------
   //double count = 0;
   //double bins[21] = {0,20,40,60,80,100,120,140,160,180,200,220,240,260,280,300,320,340,360,380,400};
   



   //----------------------------------------------------------     
   //Number of events to loop over
   //----------------------------------------------------------
   //Int_t nentries = (Int_t)fChain->GetEntries();
   ////  Int_t nentries = (Int_t)t1->GetEntries();
   //out<<"The number of entries is: "<<nentries<<endl;
   //cout<<"The number of entries is: "<<nentries<<endl;
   //double Nentries = fChain->GetEntries();
   //double weight_1fb=Nentries/(cross_section_pb*1000.);

   for(int aii=0;aii<20;aii++){    
     cout<<"I get here, looping over binned histos "<<endl;
     
     ////vs true gen met
     //if(aii>1&&aii<18){
     //  //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
     //  //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
     //  cout<<"I get here,  rebinning type1 "<<endl;
     //  h_type1calomet_x_v[aii]->Rebin(80);
     //  TF1 *myfit04 = new TF1("myfit04","gaus",-40,40);
     //  h_type1calomet_x_v[aii]->Fit("myfit04","L","",-40,40);     
     //  double RMS_type1 = myfit04->GetParameter(2);
     //  double RMSerror_type1 = myfit04->GetParError(2);
     //  
     //  h_type1calomet_RMS_vs_truegensumet->SetBinContent(aii+1,RMS_type1);
     //  h_type1calomet_RMS_vs_truegensumet->SetBinError(aii+1,RMSerror_type1);
     //}
     //
     //
     //if(aii>1&&aii<18){
     //  //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
     //  //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
     //  cout<<"I get here,  rebinning type2 "<<endl;
     //  h_type2calomet_x_v[aii]->Rebin(80);
     //  TF1 *myfit05 = new TF1("myfit05","gaus",-40,40);
     //  h_type2calomet_x_v[aii]->Fit("myfit05","L","",-40,40);     
     //  double RMS_type2 = myfit05->GetParameter(2);
     //  double RMSerror_type2 = myfit05->GetParError(2);
     //  
     //  h_type2calomet_RMS_vs_truegensumet->SetBinContent(aii+1,RMS_type2);
     //  h_type2calomet_RMS_vs_truegensumet->SetBinError(aii+1,RMSerror_type2);
     //}
     //
     //
     //
     //if(aii>1&&aii<18){
     //  //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
     //  //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
     //  cout<<"I get here,  rebinning type1 "<<endl;
     //  h_pfmet_x_v[aii]->Rebin(80);
     //  TF1 *myfit06 = new TF1("myfit06","gaus",-40,40);
     //  h_pfmet_x_v[aii]->Fit("myfit06","L","",-40,40);     
     //  double RMS_pf = myfit06->GetParameter(2);
     //  double RMSerror_pf = myfit06->GetParError(2);
     //  
     //  h_pfmet_RMS_vs_truegensumet->SetBinContent(aii+1,RMS_pf);
     //  h_pfmet_RMS_vs_truegensumet->SetBinError(aii+1,RMSerror_pf);
     //}
     //
     //
     //if(aii>1&&aii<18){
     //  //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
     //  //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
     //  h_tcmet_x_v[aii]->Rebin(80);
     //  cout<<"I get here,  rebinning type1 "<<endl;
     //  TF1 *myfit07 = new TF1("myfit07","gaus",-40,40);
     //  h_tcmet_x_v[aii]->Fit("myfit07","L","",-40,40);     
     //  double RMS_tc = myfit07->GetParameter(2);
     //  double RMSerror_tc = myfit07->GetParError(2);
     //  
     //  h_tcmet_RMS_vs_truegensumet->SetBinContent(aii+1,RMS_tc);
     //  h_tcmet_RMS_vs_truegensumet->SetBinError(aii+1,RMSerror_tc);
     //}

     //vs calo gen met
     if(aii>1&&aii<18){
       //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
       //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
       cout<<"I get here,  rebinning type1 "<<endl;
       h_type1calomet_x_v[aii]->Rebin(80);
       TF1 *myfit004 = new TF1("myfit004","gaus",-40,40);
       h_type1calomet_x_v[aii]->Fit("myfit004","L","",-40,40);     
       double RMS_type1 = myfit004->GetParameter(2);
       double RMSerror_type1 = myfit004->GetParError(2);
       
       h_type1calomet_RMS_vs_calogensumet->SetBinContent(aii+1,RMS_type1);
       h_type1calomet_RMS_vs_calogensumet->SetBinError(aii+1,RMSerror_type1);
     }
     
     
     if(aii>1&&aii<18){
       //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
       //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
       cout<<"I get here,  rebinning type2 "<<endl;
       h_type2calomet_x_v[aii]->Rebin(80);
       TF1 *myfit005 = new TF1("myfit005","gaus",-40,40);
       h_type2calomet_x_v[aii]->Fit("myfit005","L","",-40,40);     
       double RMS_type2 = myfit005->GetParameter(2);
       double RMSerror_type2 = myfit005->GetParError(2);
       
       h_type2calomet_RMS_vs_calogensumet->SetBinContent(aii+1,RMS_type2);
       h_type2calomet_RMS_vs_calogensumet->SetBinError(aii+1,RMSerror_type2);
     }
     
     
     
     if(aii>1&&aii<18){
       //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
       //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
       cout<<"I get here,  rebinning pf "<<endl;
       h_pfmet_x_v[aii]->Rebin(80);
       TF1 *myfit006 = new TF1("myfit006","gaus",-40,40);
       h_pfmet_x_v[aii]->Fit("myfit006","L","",-40,40);     
       double RMS_pf = myfit006->GetParameter(2);
       double RMSerror_pf = myfit006->GetParError(2);
       
       h_pfmet_RMS_vs_calogensumet->SetBinContent(aii+1,RMS_pf);
       h_pfmet_RMS_vs_calogensumet->SetBinError(aii+1,RMSerror_pf);
     }


     if(aii>1&&aii<18){
       //     double RMS_type1 = h_type1calomet_x_v[aii]->GetRMS();
       //     double RMSerror_type1 = h_type1calomet_x_v[aii]->GetRMSError();
       cout<<"I get here,  rebinning tc "<<endl;
       h_tcmet_x_v[aii]->Rebin(80);
       TF1 *myfit007 = new TF1("myfit007","gaus",-40,40);
       h_tcmet_x_v[aii]->Fit("myfit007","L","",-40,40);     
       double RMS_tc = myfit007->GetParameter(2);
       double RMSerror_tc = myfit007->GetParError(2);
       
       h_tcmet_RMS_vs_calogensumet->SetBinContent(aii+1,RMS_tc);
       h_tcmet_RMS_vs_calogensumet->SetBinError(aii+1,RMSerror_tc);
     }

     //vs. reco sumet
     if(aii>1&&aii<14){
       cout<<"I get here,  rebinning tc vs reco "<<endl;
       h_tcmet_x_v_reco[aii]->Rebin(80);     
       TF1 *myfit1 = new TF1("myfit1","gaus",-25,25);
       h_tcmet_x_v_reco[aii]->Fit("myfit1","L","",-25,25);     
       double recoRMS_tc =      myfit1->GetParameter(2);
       double recoRMSerror_tc =      myfit1->GetParError(2);
       h_tcmet_RMS_vs_recosumet->SetBinContent(aii+1,recoRMS_tc);
       h_tcmet_RMS_vs_recosumet->SetBinError(aii+1,recoRMSerror_tc);
     }

     if(aii>1&&aii<17){
       cout<<"I get here,  rebinning pf vs reco "<<endl;
       h_pfmet_x_v_reco[aii]->Rebin(80);     
       TF1 *myfit2 = new TF1("myfit2","gaus",-25,25);
       h_pfmet_x_v_reco[aii]->Fit("myfit2","L","",-25,25);     
       double recoRMS_pf =      myfit2->GetParameter(2);
       double recoRMSerror_pf =      myfit2->GetParError(2);
       h_pfmet_RMS_vs_recosumet->SetBinContent(aii+1,recoRMS_pf);
       h_pfmet_RMS_vs_recosumet->SetBinError(aii+1,recoRMSerror_pf);
     }
    
     if(aii>1&&aii<12){
       cout<<"I get here,  rebinning type1 vs reco "<<endl;
       h_type1calomet_x_v_reco[aii]->Rebin(80);     
       TF1 *myfit3 = new TF1("myfit3","gaus",-40,40);
       h_type1calomet_x_v_reco[aii]->Fit("myfit3","L","",-40,40);     
       double recoRMS_type1calo =      myfit3->GetParameter(2);
       double recoRMSerror_type1calo =      myfit3->GetParError(2);
       h_type1calomet_RMS_vs_recosumet->SetBinContent(aii+1,recoRMS_type1calo);
       h_type1calomet_RMS_vs_recosumet->SetBinError(aii+1,recoRMSerror_type1calo);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here,  rebinning type2 vs reco "<<endl;
       h_type2calomet_x_v_reco[aii]->Rebin(80);     
       TF1 *myfit4 = new TF1("myfit4","gaus",-40,40);
       h_type2calomet_x_v_reco[aii]->Fit("myfit4","L","",-40,40);     
       double recoRMS_type2calo =      myfit4->GetParameter(2);
       double recoRMSerror_type2calo =      myfit4->GetParError(2);
       h_type2calomet_RMS_vs_recosumet->SetBinContent(aii+1,recoRMS_type2calo);
       h_type2calomet_RMS_vs_recosumet->SetBinError(aii+1,recoRMSerror_type2calo);
     }
     //

     cout<<"I get here,  done rebinning histos "<<endl;
     double tcrecoRMS_pf = h_tcmet_x_v_reco_pf[aii]->GetRMS();
     double tcrecoRMSerror_pf = h_tcmet_x_v_reco_pf[aii]->GetRMSError();
     h_tcmet_RMS_vs_pfrecosumet->SetBinContent(aii+1,tcrecoRMS_pf);
     h_tcmet_RMS_vs_pfrecosumet->SetBinError(aii+1,tcrecoRMSerror_pf);


     double type1recoRMS_pf = h_type1calomet_x_v_reco_pf[aii]->GetRMS();
     double type1recoRMSerror_pf = h_type1calomet_x_v_reco_pf[aii]->GetRMSError();
     h_type1calomet_RMS_vs_pfrecosumet->SetBinContent(aii+1,type1recoRMS_pf);
     h_type1calomet_RMS_vs_pfrecosumet->SetBinError(aii+1,type1recoRMSerror_pf);

     double type2recoRMS_pf = h_type2calomet_x_v_reco_pf[aii]->GetRMS();
     double type2recoRMSerror_pf = h_type2calomet_x_v_reco_pf[aii]->GetRMSError();
     h_type2calomet_RMS_vs_pfrecosumet->SetBinContent(aii+1,type2recoRMS_pf);
     h_type2calomet_RMS_vs_pfrecosumet->SetBinError(aii+1,type2recoRMSerror_pf);

     double tcrecoRMS_type1 = h_tcmet_x_v_reco_type1[aii]->GetRMS();
     double tcrecoRMSerror_type1 = h_tcmet_x_v_reco_type1[aii]->GetRMSError();
     h_tcmet_RMS_vs_type1recosumet->SetBinContent(aii+1,tcrecoRMS_type1);
     h_tcmet_RMS_vs_type1recosumet->SetBinError(aii+1,tcrecoRMSerror_type1);

     double tcrecoRMS_type2 = h_tcmet_x_v_reco_type2[aii]->GetRMS();
     double tcrecoRMSerror_type2 = h_tcmet_x_v_reco_type2[aii]->GetRMSError();
     h_tcmet_RMS_vs_type2recosumet->SetBinContent(aii+1,tcrecoRMS_type2);
     h_tcmet_RMS_vs_type2recosumet->SetBinError(aii+1,tcrecoRMSerror_type2);


     double type1recoRMS_tc = h_type1calomet_x_v_reco_tc[aii]->GetRMS();
     double type1recoRMSerror_tc = h_type1calomet_x_v_reco_tc[aii]->GetRMSError();
     h_type1calomet_RMS_vs_tcrecosumet->SetBinContent(aii+1,type1recoRMS_tc);
     h_type1calomet_RMS_vs_tcrecosumet->SetBinError(aii+1,type1recoRMSerror_tc);

     double type2recoRMS_tc = h_type2calomet_x_v_reco_tc[aii]->GetRMS();
     double type2recoRMSerror_tc = h_type2calomet_x_v_reco_tc[aii]->GetRMSError();
     h_type2calomet_RMS_vs_tcrecosumet->SetBinContent(aii+1,type2recoRMS_tc);
     h_type2calomet_RMS_vs_tcrecosumet->SetBinError(aii+1,type2recoRMSerror_tc);


     double pfrecoRMS_tc = h_pfmet_x_v_reco_tc[aii]->GetRMS();
     double pfrecoRMSerror_tc = h_pfmet_x_v_reco_tc[aii]->GetRMSError();
     h_pfmet_RMS_vs_tcrecosumet->SetBinContent(aii+1,pfrecoRMS_tc);
     h_pfmet_RMS_vs_tcrecosumet->SetBinError(aii+1,pfrecoRMSerror_tc);


     double pfrecoRMS_type1 = h_pfmet_x_v_reco_type1[aii]->GetRMS();
     double pfrecoRMSerror_type1 = h_pfmet_x_v_reco_type1[aii]->GetRMSError();
     h_pfmet_RMS_vs_type1recosumet->SetBinContent(aii+1,pfrecoRMS_type1);
     h_pfmet_RMS_vs_type1recosumet->SetBinError(aii+1,pfrecoRMSerror_type1);

     double pfrecoRMS_type2 = h_pfmet_x_v_reco_type2[aii]->GetRMS();
     double pfrecoRMSerror_type2 = h_pfmet_x_v_reco_type2[aii]->GetRMSError();
     h_pfmet_RMS_vs_type2recosumet->SetBinContent(aii+1,pfrecoRMS_type2);
     h_pfmet_RMS_vs_type2recosumet->SetBinError(aii+1,pfrecoRMSerror_type2);




     double RescalingRMS_tc = h_tcmet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_tc = h_tcmet_x_v_Rescaling[aii]->GetRMSError();
     h_tcmet_RMS_vs_Rescalingsumet->SetBinContent(aii+1,RescalingRMS_tc);
     h_tcmet_RMS_vs_Rescalingsumet->SetBinError(aii+1,RescalingRMSerror_tc);

     double RescalingRMS_pf = h_pfmet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_pf = h_pfmet_x_v_Rescaling[aii]->GetRMSError();
     h_pfmet_RMS_vs_Rescalingsumet->SetBinContent(aii+1,RescalingRMS_pf);
     h_pfmet_RMS_vs_Rescalingsumet->SetBinError(aii+1,RescalingRMSerror_pf);

     double RescalingRMS_type1 = h_type1calomet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_type1 = h_type1calomet_x_v_Rescaling[aii]->GetRMSError();
     h_type1calomet_RMS_vs_Rescalingsumet->SetBinContent(aii+1,RescalingRMS_type1);
     h_type1calomet_RMS_vs_Rescalingsumet->SetBinError(aii+1,RescalingRMSerror_type1);

     double RescalingRMS_type2 = h_type2calomet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_type2 = h_type2calomet_x_v_Rescaling[aii]->GetRMSError();
     h_type2calomet_RMS_vs_Rescalingsumet->SetBinContent(aii+1,RescalingRMS_type2);
     h_type2calomet_RMS_vs_Rescalingsumet->SetBinError(aii+1,RescalingRMSerror_type2);





     //vs. reco sumet ALL rescaled
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning tc vs rescaled "<<endl;
       h_tcmet_x_v_RescalingMETALSO[aii]->Rebin(80);     
       TF1 *myfit5 = new TF1("myfit5","gaus",-25,25);
       h_tcmet_x_v_RescalingMETALSO[aii]->Fit("myfit5","L","",-25,25);     
       double RescalingMETALSORMS_tc =      myfit5->GetParameter(2);
       double RescalingMETALSORMSerror_tc =      myfit5->GetParError(2);
       h_tcmet_RMS_vs_RescalingMETALSOsumet->SetBinContent(aii+1,RescalingMETALSORMS_tc);
       h_tcmet_RMS_vs_RescalingMETALSOsumet->SetBinError(aii+1,RescalingMETALSORMSerror_tc);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning pf vs rescaled "<<endl;
       h_pfmet_x_v_RescalingMETALSO[aii]->Rebin(80);     
       TF1 *myfit6 = new TF1("myfit6","gaus",-25,25);
       h_pfmet_x_v_RescalingMETALSO[aii]->Fit("myfit6","L","",-25,25);     
       double RescalingMETALSORMS_pf =      myfit6->GetParameter(2);
       double RescalingMETALSORMSerror_pf =      myfit6->GetParError(2);
       h_pfmet_RMS_vs_RescalingMETALSOsumet->SetBinContent(aii+1,RescalingMETALSORMS_pf);
       h_pfmet_RMS_vs_RescalingMETALSOsumet->SetBinError(aii+1,RescalingMETALSORMSerror_pf);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type1 vs rescaled "<<endl;
       h_type1calomet_x_v_RescalingMETALSO[aii]->Rebin(80);     
       TF1 *myfit7 = new TF1("myfit7","gaus",-40,40);
       h_type1calomet_x_v_RescalingMETALSO[aii]->Fit("myfit7","L","",-40,40);     
       double RescalingMETALSORMS_type1calo =      myfit7->GetParameter(2);
       double RescalingMETALSORMSerror_type1calo =      myfit7->GetParError(2);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet->SetBinContent(aii+1,RescalingMETALSORMS_type1calo);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet->SetBinError(aii+1,RescalingMETALSORMSerror_type1calo);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type2 vs rescaled "<<endl;
       h_type2calomet_x_v_RescalingMETALSO[aii]->Rebin(80);     
       TF1 *myfit8 = new TF1("myfit8","gaus",-40,40);
       h_type2calomet_x_v_RescalingMETALSO[aii]->Fit("myfit8","L","",-40,40);     
       double RescalingMETALSORMS_type2calo =      myfit8->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo =      myfit8->GetParError(2);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet->SetBinContent(aii+1,RescalingMETALSORMS_type2calo);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet->SetBinError(aii+1,RescalingMETALSORMSerror_type2calo);
     }
     
     
     //vs. reco sumet ALL rescaled
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning tc vs rescaled pfsumet "<<endl;
       h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Rebin(80);     
       TF1 *myfit51 = new TF1("myfit51","gaus",-25,25);
       h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit51","L","",-25,25);     
       double RescalingMETALSORMS_tc_vs_pf =      myfit51->GetParameter(2);
       double RescalingMETALSORMSerror_tc_vs_pf =      myfit51->GetParError(2);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(aii+1,RescalingMETALSORMS_tc_vs_pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(aii+1,RescalingMETALSORMSerror_tc_vs_pf);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type1 vs rescaled pfsumet "<<endl;
       h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]->Rebin(80);     
       TF1 *myfit71 = new TF1("myfit71","gaus",-40,40);
       h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit71","L","",-40,40);     
       double RescalingMETALSORMS_type1calo_vs_pf =      myfit71->GetParameter(2);
       double RescalingMETALSORMSerror_type1calo_vs_pf =      myfit71->GetParError(2);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(aii+1,RescalingMETALSORMS_type1calo_vs_pf);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(aii+1,RescalingMETALSORMSerror_type1calo_vs_pf);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type2 vs rescaled pfsumet "<<endl;
       h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Rebin(80);     
       TF1 *myfit81 = new TF1("myfit81","gaus",-40,40);
       h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit81","L","",-40,40);     
       double RescalingMETALSORMS_type2calo_vs_pf =      myfit81->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo_vs_pf =      myfit81->GetParError(2);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(aii+1,RescalingMETALSORMS_type2calo_vs_pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(aii+1,RescalingMETALSORMSerror_type2calo_vs_pf);
     }
     
     
     
     
     //vs. reco pfsumet not rescaled
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning tc vs unrescaled pfsumet "<<endl;
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(80);     
       TF1 *myfit511 = new TF1("myfit511","gaus",-25,25);
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit511","L","",-25,25);     
       double RescalingMETALSORMS_tc_vs_uncal_pf =      myfit511->GetParameter(2);
       double RescalingMETALSORMSerror_tc_vs_uncal_pf =      myfit511->GetParError(2);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(aii+1,RescalingMETALSORMS_tc_vs_uncal_pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(aii+1,RescalingMETALSORMSerror_tc_vs_uncal_pf);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type1 vs unrescaled pfsumet "<<endl;
       h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(80);     
       TF1 *myfit711 = new TF1("myfit711","gaus",-40,40);
       h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit711","L","",-40,40);     
       double RescalingMETALSORMS_type1calo_vs_uncal_pf =      myfit711->GetParameter(2);
       double RescalingMETALSORMSerror_type1calo_vs_uncal_pf =      myfit711->GetParError(2);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(aii+1,RescalingMETALSORMS_type1calo_vs_uncal_pf);
       h_type1calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(aii+1,RescalingMETALSORMSerror_type1calo_vs_uncal_pf);
     }
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning type2 vs unrescaled pfsumet "<<endl;
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(80);     
       TF1 *myfit811 = new TF1("myfit811","gaus",-40,40);
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit811","L","",-40,40);     
       double RescalingMETALSORMS_type2calo_vs_uncal_pf =      myfit811->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo_vs_uncal_pf =      myfit811->GetParError(2);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(aii+1,RescalingMETALSORMS_type2calo_vs_uncal_pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(aii+1,RescalingMETALSORMSerror_type2calo_vs_uncal_pf);
     }
     
     
     if(aii>1&&aii<18){
       cout<<"I get here, rebinning pf vs unrescaled pfsumet "<<endl;
       h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(80);     
       TF1 *myfit911 = new TF1("myfit911","gaus",-40,40);
       h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit911","L","",-40,40);     
       double RescalingMETALSORMS_pf_vs_uncal_pf =      myfit911->GetParameter(2);
       double RescalingMETALSORMSerror_pf_vs_uncal_pf =      myfit911->GetParError(2);
       h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(aii+1,RescalingMETALSORMS_pf_vs_uncal_pf);
       h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(aii+1,RescalingMETALSORMSerror_pf_vs_uncal_pf);
     }
     cout<<"I get here, done rebinning vs unrescaled pfsumet "<<endl;
     
   }
   
   //----------------------------------------------------------     
   //Write out histogram file
   //----------------------------------------------------------      
   outfile->cd();
   outfile->Write();
}

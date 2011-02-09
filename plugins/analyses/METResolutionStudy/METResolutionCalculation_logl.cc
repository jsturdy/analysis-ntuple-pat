#include "TMath.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2F.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "TString.h"
#include "TVector3.h"
#include "TGraphAsymmErrors.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TProfile.h"
using namespace std;

//void METResolutionCalculation(TString input_filename, TString output_filename, double cross_section_pb, int scale_type)
void METResolutionCalculation(const TString& input_filename, const bool& doExtra)
{   
  
  bool debug_ = false;
  //----------------------------------------------------------
  //Define output file
  //----------------------------------------------------------
  TString output_filename = "";
  output_filename = input_filename+"_logl_optimized";
  
  TString file_name = input_filename+".root";
  
  TString root_name = output_filename+".root";
  TString text_name = output_filename+".txt";
  TFile *infile = new TFile(file_name.Data(),"OPEN");
  TFile *outfile = new TFile(root_name.Data(),"RECREATE");
  if(debug_)cout<<"input file: "<<file_name<<" "<<infile<<std::endl;
  if(debug_)cout<<"output file: "<<root_name<<" "<<outfile<<std::endl;
  infile->cd();
  
  
  ofstream out;
  
  out.open(text_name.Data(), ios::out | ios::app);
  

  //----------------------------------------------------------
  //Histogram Declarations
  //----------------------------------------------------------
  ///125-67-58
   TH1F *h_tcmet_x_v[59];
   TH1F *h_pfmet_x_v[59];
   TH1F *h_type1pfmet_x_v[59];
   TH1F *h_type2calomet_x_v[59];


   TH1F *h_tcmet_x_v_reco[59];
   TH1F *h_pfmet_x_v_reco[59];
   TH1F *h_type1pfmet_x_v_reco[59];
   TH1F *h_type2calomet_x_v_reco[59];

   TH1F *h_tcmet_x_v_reco_pf[59];
   TH1F *h_type2calomet_x_v_reco_pf[59];

   TH1F *h_tcmet_x_v_reco_type1pf[59];
   TH1F *h_type2calomet_x_v_reco_type1pf[59];


   TH1F *h_tcmet_x_v_reco_type1[59];
   TH1F *h_tcmet_x_v_reco_type2[59];
   TH1F *h_type2calomet_x_v_reco_tc[59];

   TH1F *h_pfmet_x_v_reco_type1[59];
   TH1F *h_pfmet_x_v_reco_type2[59];
   TH1F *h_pfmet_x_v_reco_tc[59];

   TH1F *h_type1pfmet_x_v_reco_type1[59];
   TH1F *h_type1pfmet_x_v_reco_type2[59];
   TH1F *h_type1pfmet_x_v_reco_tc[59];


   TH1F *h_tcmet_x_v_Rescaling[59];
   TH1F *h_pfmet_x_v_Rescaling[59];
   TH1F *h_type1pfmet_x_v_Rescaling[59];
   TH1F *h_type2calomet_x_v_Rescaling[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO[59];
   TH1F *h_pfmet_x_v_RescalingMETALSO[59];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_pf[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_pf[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type2[59];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_type2[59];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_type2[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type1pf[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[59];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[59];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[59];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[59];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[59];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[59];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[59];

   if(debug_)cout<<"I get here, beginning of defining array histos "<<endl;

   int hist[125] = {
     0,1,2,3,4,5,6,7,8,9,                             //0,1,2,3,4,5,6,7,8,9,
     10,11,12,13,14,15,16,17,18,19,                   //10,11,12,13,14,15,16,17,18,19,
     20,21,22,23,24,25,26,27,28,29,                   //20,21,22,23,24,25,26,27,28,29,
     30,31,32,33,34,35,36,37,38,39,                   //30,31,32,33,34,35,36,37,38,39,
     40,41,42,43,44,45,46,47,48,49,                   //40,41,42,43,44,45,46,47,48,49,
     50,50,51,51,52,                                  //50,51,52,53,54,55,56,57,58,59,
     52,52,53,53,53,
     54,54,54,54,54,                                  //60,60,60,60,60,
     55,55,55,55,55,                                  //61,61,61,61,61,
     56,56,56,56,56,56,56,56,56,56,                   //62,62,62,62,62,62,62,62,62,62,
     57,57,57,57,57,57,57,57,57,57,                   //63,63,63,63,63,63,63,63,63,63,
     57,57,57,57,57,57,57,57,57,57,                   //64,64,64,64,64,64,64,64,64,64,
     58,58,58,58,58,58,58,58,58,58,                   //65,65,65,65,65,65,65,65,65,65,
     58,58,58,58,58,58,58,58,58,58,58,58,58,58,58     //66,66,66,66,66,66,66,66,66,66,66,66,66,66,66
   };
   
   for(int aii=0;aii<125;aii++){

     if(debug_)cout<<"I get here, beginning of array loop "<<endl;
     if(debug_)cout<<"hist["<<aii<<" = "<<hist[aii]<<endl;
     //if ( aii < 60 || (aii==60  || aii==65  || aii==70  || aii==80  || aii==90  || aii==100 || aii==110 || aii==124) ) 
     if ( aii < 50 || (aii==50  || aii==52  || aii==54  || aii==57  || aii==60  || aii==65  || aii==70  || aii==80  || aii==100 || aii==124) ) 

         //if aii>50 && aii<52 h[50]->Add(h[50],h[aii])     bin midpoint = 1020	 //if aii>60 && aii<65 h[60]->Add(h[60],h[aii])     bin midpoint = 1250
         //if aii>52 && aii<54 h[52]->Add(h[52],h[aii])     bin midpoint = 1060	 //if aii>65 && aii<70 h[65]->Add(h[65],h[aii])     bin midpoint = 1350
         //if aii>54 && aii<57 h[54]->Add(h[54],h[aii])     bin midpoint = 1110	 //if aii>70 && aii<80 h[70]->Add(h[70],h[aii])     bin midpoint = 1500
         //if aii>57 && aii<60 h[57]->Add(h[57],h[aii])     bin midpoint = 1170	 //if aii>80 && aii<90 h[80]->Add(h[80],h[aii])     bin midpoint = 1700
         //if aii>60 && aii<65 h[60]->Add(h[60],h[aii])     bin midpoint = 1250	 //if aii>90 && aii<100 h[90]->Add(h[90],h[aii])    bin midpoint = 1900
         //if aii>65 && aii<70 h[65]->Add(h[65],h[aii])     bin midpoint = 1350	 //if aii>100 && aii<110 h[100]->Add(h[100],h[aii]) bin midpoint = 2100
         //if aii>70 && aii<80 h[70]->Add(h[70],h[aii])     bin midpoint = 1500	 //if aii>110 && aii<125 h[110]->Add(h[110],h[aii]) bin midpoint = 2350
         //if aii>80 && aii<100 h[80]->Add(h[80],h[aii])    bin midpoint = 1800
         //if aii>100 && aii<125 h[100]->Add(h[100],h[aii]) bin midpoint = 2250
       {

	 h_tcmet_x_v[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_%i",aii));
	 if(debug_)cout<<"h_tcmet_x_v["<<hist[aii]<<"] = "<<h_tcmet_x_v[hist[aii]]<<std::endl;
	 h_pfmet_x_v[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_%i",aii));
	 if(debug_)cout<<"h_pfmet_x_v["<<hist[aii]<<"] = "<<h_pfmet_x_v[hist[aii]]<<std::endl;
	 h_type1pfmet_x_v[hist[aii]]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_%i",aii));
	 if(debug_)cout<<"h_type1pfmet_x_v["<<hist[aii]<<"] = "<<h_type1pfmet_x_v[hist[aii]]<<std::endl;
	 h_type2calomet_x_v[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_%i",aii));
	 if(debug_)cout<<"h_type2calomet_x_v["<<hist[aii]<<"] = "<<h_type2calomet_x_v[hist[aii]]<<std::endl;

	 h_tcmet_x_v_reco[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_%i",aii));
	 h_pfmet_x_v_reco[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_reco_%i",aii));
	 h_type1pfmet_x_v_reco[hist[aii]]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_%i",aii));
	 h_type2calomet_x_v_reco[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_%i",aii));
	 
	 h_tcmet_x_v_reco_pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_pf_%i",aii));
	 h_type2calomet_x_v_reco_pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_pf_%i",aii));
	 
	 h_tcmet_x_v_reco_type1pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type1pf_%i",aii));
	 h_type2calomet_x_v_reco_type1pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_type1pf_%i",aii));
	 
	 h_type2calomet_x_v_reco_tc[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_tc_%i",aii));
	 
	 h_tcmet_x_v_reco_type1[hist[aii]] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type1_%i",aii));
	 h_tcmet_x_v_reco_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type2_%i",aii));
	 h_pfmet_x_v_reco_type1[hist[aii]] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type1_%i",aii));
	 h_pfmet_x_v_reco_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type2_%i",aii));
	 
	 h_type1pfmet_x_v_reco_type1[hist[aii]] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type1_%i",aii));
	 h_type1pfmet_x_v_reco_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type2_%i",aii));
	 
	 h_pfmet_x_v_reco_tc[hist[aii]]      = (TH1F*)infile->Get(Form("h_pfmet_x_reco_tc_%i",aii));
	 h_type1pfmet_x_v_reco_tc[hist[aii]] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_tc_%i",aii));
	 
	 h_tcmet_x_v_Rescaling[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_Rescaling_%i",aii));
	 h_pfmet_x_v_Rescaling[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_Rescaling_%i",aii));
	 h_type1pfmet_x_v_Rescaling[hist[aii]]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_Rescaling_%i",aii));
	 h_type2calomet_x_v_Rescaling[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_Rescaling_%i",aii));
	 
	 h_tcmet_x_v_RescalingMETALSO[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_%i",aii));
	 h_pfmet_x_v_RescalingMETALSO[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_%i",aii));
	 h_type1pfmet_x_v_RescalingMETALSO[hist[aii]]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_%i",aii));
	 h_type2calomet_x_v_RescalingMETALSO[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_%i",aii));

	 if (doExtra) {
	   h_tcmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type2_%i",aii));
	   h_pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_type2_%i",aii));
	   h_type1pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_type2_%i",aii));
	   
	   h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
	   h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
	   h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]        = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
	   h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
	 }
	 h_tcmet_x_v_RescalingMETALSO_vs_pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii));
	 h_type2calomet_x_v_RescalingMETALSO_vs_pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii));
	 
	 h_tcmet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type1pf_%i",aii));
	 h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_type1pf_%i",aii));
	 
	 
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
	 h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
	 
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));
	 h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));

       }

     else 
       {
         //if aii>50 && aii<52 h[50]->Add(h[50],h[aii])     bin midpoint = 1020	 //if aii>60 && aii<65 h[60]->Add(h[60],h[aii])     bin midpoint = 1250
         //if aii>52 && aii<54 h[52]->Add(h[52],h[aii])     bin midpoint = 1060	 //if aii>65 && aii<70 h[65]->Add(h[65],h[aii])     bin midpoint = 1350
         //if aii>54 && aii<57 h[54]->Add(h[54],h[aii])     bin midpoint = 1110	 //if aii>70 && aii<80 h[70]->Add(h[70],h[aii])     bin midpoint = 1500
         //if aii>57 && aii<60 h[57]->Add(h[57],h[aii])     bin midpoint = 1170	 //if aii>80 && aii<90 h[80]->Add(h[80],h[aii])     bin midpoint = 1700
         //if aii>60 && aii<65 h[60]->Add(h[60],h[aii])     bin midpoint = 1250	 //if aii>90 && aii<100 h[90]->Add(h[90],h[aii])    bin midpoint = 1900
         //if aii>65 && aii<70 h[65]->Add(h[65],h[aii])     bin midpoint = 1350	 //if aii>100 && aii<110 h[100]->Add(h[100],h[aii]) bin midpoint = 2100
         //if aii>70 && aii<80 h[70]->Add(h[70],h[aii])     bin midpoint = 1500	 //if aii>110 && aii<125 h[110]->Add(h[110],h[aii]) bin midpoint = 2350
         //if aii>80 && aii<100 h[80]->Add(h[80],h[aii])    bin midpoint = 1800
         //if aii>100 && aii<125 h[100]->Add(h[100],h[aii]) bin midpoint = 2250
	 
	 if(debug_)cout<<"Adding histograms together: hist["<<aii<<"] = "<<hist[aii]<<std::endl;
	 h_tcmet_x_v[hist[aii]]                    ->Add(h_tcmet_x_v[hist[aii]]                    ,(TH1F*)infile->Get(Form("h_tcmet_x_%i",aii)));
	 if(debug_)cout<<"h_tcmet_x_v["<<hist[aii]<<"] = "<<h_tcmet_x_v[hist[aii]]<<std::endl;
	 h_pfmet_x_v[hist[aii]]                    ->Add(h_pfmet_x_v[hist[aii]]                    ,(TH1F*)infile->Get(Form("h_pfmet_x_%i",aii)));
	 if(debug_)cout<<"h_pfmet_x_v["<<hist[aii]<<"] = "<<h_pfmet_x_v[hist[aii]]<<std::endl;
	 h_type1pfmet_x_v[hist[aii]]               ->Add(h_type1pfmet_x_v[hist[aii]]               ,(TH1F*)infile->Get(Form("h_type1pfmet_x_%i",aii)));
	 if(debug_)cout<<"h_type1pfmet_x_v["<<hist[aii]<<"] = "<<h_type1pfmet_x_v[hist[aii]]<<std::endl;
	 h_type2calomet_x_v[hist[aii]]             ->Add(h_type2calomet_x_v[hist[aii]]             ,(TH1F*)infile->Get(Form("h_type2calomet_x_%i",aii)));
	 if(debug_)cout<<"h_type2calomet_x_v["<<hist[aii]<<"] = "<<h_type2calomet_x_v[hist[aii]]<<std::endl;
	 
	 h_tcmet_x_v_reco[hist[aii]]               ->Add(h_tcmet_x_v_reco[hist[aii]]               ,(TH1F*)infile->Get(Form("h_tcmet_x_reco_%i",aii)));
	 h_pfmet_x_v_reco[hist[aii]]               ->Add(h_pfmet_x_v_reco[hist[aii]]               ,(TH1F*)infile->Get(Form("h_pfmet_x_reco_%i",aii)));
	 h_type1pfmet_x_v_reco[hist[aii]]          ->Add(h_type1pfmet_x_v_reco[hist[aii]]          ,(TH1F*)infile->Get(Form("h_type1pfmet_x_reco_%i",aii)));
	 h_type2calomet_x_v_reco[hist[aii]]        ->Add(h_type2calomet_x_v_reco[hist[aii]]        ,(TH1F*)infile->Get(Form("h_type2calomet_x_reco_%i",aii)));
	 
	 h_tcmet_x_v_reco_pf[hist[aii]]            ->Add(h_tcmet_x_v_reco_pf[hist[aii]]            ,(TH1F*)infile->Get(Form("h_tcmet_x_reco_pf_%i",aii)));
	 h_type2calomet_x_v_reco_pf[hist[aii]]     ->Add(h_type2calomet_x_v_reco_pf[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type2calomet_x_reco_pf_%i",aii)));
	 
	 h_tcmet_x_v_reco_type1pf[hist[aii]]       ->Add(h_tcmet_x_v_reco_type1pf[hist[aii]]       ,(TH1F*)infile->Get(Form("h_tcmet_x_reco_type1pf_%i",aii)));
	 h_type2calomet_x_v_reco_type1pf[hist[aii]]->Add(h_type2calomet_x_v_reco_type1pf[hist[aii]],(TH1F*)infile->Get(Form("h_type2calomet_x_reco_type1pf_%i",aii)));
	 
	 h_type2calomet_x_v_reco_tc[hist[aii]]     ->Add(h_type2calomet_x_v_reco_tc[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type2calomet_x_reco_tc_%i",aii)));
	 
	 h_tcmet_x_v_reco_type1[hist[aii]]         ->Add(h_tcmet_x_v_reco_type1[hist[aii]]         ,(TH1F*)infile->Get(Form("h_tcmet_x_reco_type1_%i",aii)));
	 h_tcmet_x_v_reco_type2[hist[aii]]         ->Add(h_tcmet_x_v_reco_type2[hist[aii]]         ,(TH1F*)infile->Get(Form("h_tcmet_x_reco_type2_%i",aii)));
	 h_pfmet_x_v_reco_type1[hist[aii]]         ->Add(h_pfmet_x_v_reco_type1[hist[aii]]         ,(TH1F*)infile->Get(Form("h_pfmet_x_reco_type1_%i",aii)));
	 h_pfmet_x_v_reco_type2[hist[aii]]         ->Add(h_pfmet_x_v_reco_type2[hist[aii]]         ,(TH1F*)infile->Get(Form("h_pfmet_x_reco_type2_%i",aii)));
	 
	 h_type1pfmet_x_v_reco_type1[hist[aii]]    ->Add(h_type1pfmet_x_v_reco_type1[hist[aii]]    ,(TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type1_%i",aii)));
	 h_type1pfmet_x_v_reco_type2[hist[aii]]    ->Add(h_type1pfmet_x_v_reco_type2[hist[aii]]    ,(TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type2_%i",aii)));
	 
	 h_pfmet_x_v_reco_tc[hist[aii]]            ->Add(h_pfmet_x_v_reco_tc[hist[aii]]            ,(TH1F*)infile->Get(Form("h_pfmet_x_reco_tc_%i",aii)));
	 h_type1pfmet_x_v_reco_tc[hist[aii]]       ->Add(h_type1pfmet_x_v_reco_tc[hist[aii]]       ,(TH1F*)infile->Get(Form("h_type1pfmet_x_reco_tc_%i",aii)));
	 
	 h_tcmet_x_v_Rescaling[hist[aii]]          ->Add(h_tcmet_x_v_Rescaling[hist[aii]]          ,(TH1F*)infile->Get(Form("h_tcmet_x_Rescaling_%i",aii)));
	 h_pfmet_x_v_Rescaling[hist[aii]]          ->Add(h_pfmet_x_v_Rescaling[hist[aii]]          ,(TH1F*)infile->Get(Form("h_pfmet_x_Rescaling_%i",aii)));
	 h_type1pfmet_x_v_Rescaling[hist[aii]]     ->Add(h_type1pfmet_x_v_Rescaling[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type1pfmet_x_Rescaling_%i",aii)));
	 h_type2calomet_x_v_Rescaling[hist[aii]]   ->Add(h_type2calomet_x_v_Rescaling[hist[aii]]   ,(TH1F*)infile->Get(Form("h_type2calomet_x_Rescaling_%i",aii)));
	 
	 h_tcmet_x_v_RescalingMETALSO[hist[aii]]                        ->Add(h_tcmet_x_v_RescalingMETALSO[hist[aii]]                        ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_%i",aii)));
	 h_pfmet_x_v_RescalingMETALSO[hist[aii]]                        ->Add(h_pfmet_x_v_RescalingMETALSO[hist[aii]]                        ,(TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_%i",aii)));
	 h_type1pfmet_x_v_RescalingMETALSO[hist[aii]]                   ->Add(h_type1pfmet_x_v_RescalingMETALSO[hist[aii]]                   ,(TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_%i",aii)));
	 h_type2calomet_x_v_RescalingMETALSO[hist[aii]]                 ->Add(h_type2calomet_x_v_RescalingMETALSO[hist[aii]]                 ,(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_%i",aii)));

	 if (doExtra) {
	   h_tcmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]                  ->Add(h_tcmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]                  ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type2_%i",aii)));
	   h_pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]                  ->Add(h_pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]                  ,(TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_type2_%i",aii)));
	   h_type1pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]           ->Add(h_type1pfmet_x_v_RescalingMETALSO_vs_type2[hist[aii]]           ,(TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_type2_%i",aii)));
	 
	   h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]            ->Add(h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]            ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii)));
	   h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]            ->Add(h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]            ,(TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii)));
	   h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]     ->Add(h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii)));
	   h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]     ->Add(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii)));
	 }	 							                                                                             
	 h_tcmet_x_v_RescalingMETALSO_vs_pf[hist[aii]]                  ->Add(h_tcmet_x_v_RescalingMETALSO_vs_pf[hist[aii]]                  ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii)));
	 h_type2calomet_x_v_RescalingMETALSO_vs_pf[hist[aii]]           ->Add(h_type2calomet_x_v_RescalingMETALSO_vs_pf[hist[aii]]           ,(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii)));
	 
	 h_tcmet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]]             ->Add(h_tcmet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]]             ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type1pf_%i",aii)));
	 h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]]      ->Add(h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[hist[aii]]      ,(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_type1pf_%i",aii)));
	 							                                                                             
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]            ->Add(h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]            ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii)));
	 h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]            ->Add(h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]            ,(TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii)));
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]     ->Add(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[hist[aii]]     ,(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii)));
	 								                                                                     
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]       ->Add(h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]       ,(TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii)));
	 h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]  ->Add(h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]  ,(TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii)));
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]]->Add(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[hist[aii]],(TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii)));
     }
   }

   outfile->cd();

   TH1F *h_tcmet_RMS_vs_calogensumet        = new TH1F("h_tcmet_RMS_vs_calogensumet","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_calogensumet        = new TH1F("h_pfmet_RMS_vs_calogensumet","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_calogensumet   = new TH1F("h_type1pfmet_RMS_vs_calogensumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_calogensumet = new TH1F("h_type2calomet_RMS_vs_calogensumet","",250,0,2500);


   TH1F *h_tcmet_RMS_vs_recosumet        = new TH1F("h_tcmet_RMS_vs_recosumet","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_recosumet        = new TH1F("h_pfmet_RMS_vs_recosumet","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_recosumet   = new TH1F("h_type1pfmet_RMS_vs_recosumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_recosumet = new TH1F("h_type2calomet_RMS_vs_recosumet","",250,0,2500);


   TH1F *h_tcmet_RMS_vs_pfrecosumet        = new TH1F("h_tcmet_RMS_vs_pfrecosumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_pfrecosumet = new TH1F("h_type2calomet_RMS_vs_pfrecosumet","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_type1pfrecosumet        = new TH1F("h_tcmet_RMS_vs_type1pfrecosumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_type1pfrecosumet = new TH1F("h_type2calomet_RMS_vs_type1pfrecosumet","",250,0,2500);


   TH1F *h_tcmet_RMS_vs_type2recosumet     = new TH1F("h_tcmet_RMS_vs_type2recosumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_tcrecosumet = new TH1F("h_type2calomet_RMS_vs_tcrecosumet","",250,0,2500);


   TH1F *h_pfmet_RMS_vs_type2recosumet = new TH1F("h_pfmet_RMS_vs_type2recosumet","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_tcrecosumet    = new TH1F("h_pfmet_RMS_vs_tcrecosumet","",250,0,2500);

   TH1F *h_type1pfmet_RMS_vs_type2recosumet = new TH1F("h_type1pfmet_RMS_vs_type2recosumet","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_tcrecosumet    = new TH1F("h_type1pfmet_RMS_vs_tcrecosumet","",250,0,2500);


   TH1F *h_tcmet_RMS_vs_Rescalingsumet        = new TH1F("h_tcmet_RMS_vs_Rescalingsumet","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_Rescalingsumet        = new TH1F("h_pfmet_RMS_vs_Rescalingsumet","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_Rescalingsumet   = new TH1F("h_type1pfmet_RMS_vs_Rescalingsumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_Rescalingsumet = new TH1F("h_type2calomet_RMS_vs_Rescalingsumet","",250,0,2500);


   TH1F *h_tcmet_gRMS_vs_RescalingMETALSOsumet        = new TH1F("h_tcmet_gRMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_pfmet_gRMS_vs_RescalingMETALSOsumet        = new TH1F("h_pfmet_gRMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_type1pfmet_gRMS_vs_RescalingMETALSOsumet   = new TH1F("h_type1pfmet_gRMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_type2calomet_gRMS_vs_RescalingMETALSOsumet = new TH1F("h_type2calomet_gRMS_vs_RescalingMETALSOsumet","",250,0,2500);


   TH1F *h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_type2       = new TH1F("h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);
   TH1F *h_pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2       = new TH1F("h_pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);
   TH1F *h_type1pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2  = new TH1F("h_type1pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);

   TH1F *h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_pf        = new TH1F("h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_pf","",250,0,2500);
   TH1F *h_type2calomet_gRMS_vs_RescalingMETALSOsumet_vs_pf = new TH1F("h_type2calomet_gRMS_vs_RescalingMETALSOsumet_vs_pf","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet        = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_RescalingMETALSOsumet   = new TH1F("h_type1pfmet_RMS_vs_RescalingMETALSOsumet","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet","",250,0,2500);


   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type2       = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2       = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2  = new TH1F("h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type1pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type1pf","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_type1pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_type1pf","",250,0,2500);



   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2 = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2        = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2   = new TH1F("h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",250,0,2500);
   TH1F *h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf        = new TH1F("h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf","",250,0,2500);

   TH1F *h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf        = new TH1F("h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf","",250,0,2500);
   TH1F *h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf = new TH1F("h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf","",250,0,2500);
   TH1F *h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf    = new TH1F("h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf","",250,0,2500);


   if(debug_)cout<<"I get here, end of defining histos "<<endl;

   int binValue[59] = {
     1,3,5,7,9,      //5       //1,3,5,7,9,      //5       //10,30,50,70,90,      //5
     11,13,15,17,19,//10       //11,13,15,17,19,//10       //110,130,150,170,190,//10
     21,23,25,27,29,//15       //21,23,25,27,29,//15       //210,230,250,270,290,//15
     31,33,35,37,39,//20       //31,33,35,37,39,//20       //310,330,350,370,390,//20
     41,43,45,47,49,//25       //41,43,45,47,49,//25       //410,430,450,470,490,//25
     51,53,55,57,59,//30       //51,53,55,57,59,//30       //510,530,550,570,590,//30
     61,63,65,67,69,//35       //61,63,65,67,69,//35       //610,630,650,670,690,//35
     71,73,75,77,79,//40       //71,73,75,77,79,//40       //710,730,750,770,790,//40
     81,83,85,87,89,//45       //81,83,85,87,89,//45       //810,830,850,870,890,//45
     91,93,95,97,99,//50       //91,93,95,97,99,//50       //910,930,950,970,990,//50
     102,106     ,  //52       //101,103,105,107,109,  //55//1010,1030,1050,1070,1090,  //55
     111,117,       //54       //111,113,115,117,119,  //60//1110,1130,1150,1170,1190,  //60
     125,           //55       //125,                      //61//1250,                      //61
     135,           //56       //135,                      //62//1350,                      //62
     //150,                    //150,                      //63//1500,                      //63
     180,           //57       //170,                      //64//1700,                      //64
     //190,                    //190,                      //65//1900,                      //65
     //210,                    //210,                      //66//2100,                      //66
     225,           //58       //235                       //67 //2350                      //67
     250            //59         //250                       //68//2500                       //68
   };
   
   for(int aii=0;aii<59;aii++){    
     if(debug_)cout<<"I get here, looping over binned histos "<<endl;

     //vs calo gen met

     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning type2 "<<endl;
       //h_type2calomet_x_v[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v[aii]->Fit("myfit0","LLEMIRq","",-width,width);
       
       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RMS_type2 =      myfit1->GetParameter(2);
       double RMSerror_type2 = myfit1->GetParError(2);
       
       h_type2calomet_RMS_vs_calogensumet->SetBinContent(binValue[aii],RMS_type2);
       h_type2calomet_RMS_vs_calogensumet->SetBinError(binValue[aii],RMSerror_type2);
     }
     
     
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning pf "<<endl;
       //h_pfmet_x_v[aii]->Rebin(50);

       double width = 2*(h_pfmet_x_v[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_pfmet_x_v[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_pfmet_x_v[aii]->Fit("myfit1","LLEMIRq","",-width,width);
       
       double RMS_pf =      myfit1->GetParameter(2);
       double RMSerror_pf = myfit1->GetParError(2);
       
       h_pfmet_RMS_vs_calogensumet->SetBinContent(binValue[aii],RMS_pf);
       h_pfmet_RMS_vs_calogensumet->SetBinError(binValue[aii],RMSerror_pf);
     }

     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning tc "<<endl;
       //h_tcmet_x_v[aii]->Rebin(50);
       
       double width = 2*(h_tcmet_x_v[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RMS_tc =      myfit1->GetParameter(2);
       double RMSerror_tc = myfit1->GetParError(2);
       
       h_tcmet_RMS_vs_calogensumet->SetBinContent(binValue[aii],RMS_tc);
       h_tcmet_RMS_vs_calogensumet->SetBinError(binValue[aii],RMSerror_tc);
     }

     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning type1pf "<<endl;
       //h_type1pfmet_x_v[aii]->Rebin(50);

       double width = 2*(h_type1pfmet_x_v[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type1pfmet_x_v[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type1pfmet_x_v[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RMS_type1pf =      myfit1->GetParameter(2);
       double RMSerror_type1pf = myfit1->GetParError(2);
       
       h_type1pfmet_RMS_vs_calogensumet->SetBinContent(binValue[aii],RMS_type1pf);
       h_type1pfmet_RMS_vs_calogensumet->SetBinError(binValue[aii],RMSerror_type1pf);
     }


     //vs. reco sumet
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning tc vs reco "<<endl;
       //h_tcmet_x_v_reco[aii]->Rebin(50);

       double width = 2*(h_tcmet_x_v_reco[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_reco[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_reco[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double recoRMS_tc =      myfit1->GetParameter(2);
       double recoRMSerror_tc = myfit1->GetParError(2);

       h_tcmet_RMS_vs_recosumet->SetBinContent(binValue[aii],recoRMS_tc);
       h_tcmet_RMS_vs_recosumet->SetBinError(binValue[aii],recoRMSerror_tc);
     }

     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning pf vs reco "<<endl;
       //h_pfmet_x_v_reco[aii]->Rebin(50);

       double width = 2*(h_pfmet_x_v_reco[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_pfmet_x_v_reco[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_pfmet_x_v_reco[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double recoRMS_pf =      myfit1->GetParameter(2);
       double recoRMSerror_pf = myfit1->GetParError(2);

       h_pfmet_RMS_vs_recosumet->SetBinContent(binValue[aii],recoRMS_pf);
       h_pfmet_RMS_vs_recosumet->SetBinError(binValue[aii],recoRMSerror_pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning type2 vs reco "<<endl;
       //h_type2calomet_x_v_reco[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_reco[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_reco[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_reco[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double recoRMS_type2calo =      myfit1->GetParameter(2);
       double recoRMSerror_type2calo = myfit1->GetParError(2);

       h_type2calomet_RMS_vs_recosumet->SetBinContent(binValue[aii],recoRMS_type2calo);
       h_type2calomet_RMS_vs_recosumet->SetBinError(binValue[aii],recoRMSerror_type2calo);
     }

     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here aii="<<aii<<" ,  rebinning type1pf vs reco "<<endl;
       //h_type1pfmet_x_v_reco[aii]->Rebin(50);

       double width = 2*(h_type1pfmet_x_v_reco[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type1pfmet_x_v_reco[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type1pfmet_x_v_reco[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double recoRMS_type1pf =      myfit1->GetParameter(2);
       double recoRMSerror_type1pf = myfit1->GetParError(2);

       h_type1pfmet_RMS_vs_recosumet->SetBinContent(binValue[aii],recoRMS_type1pf);
       h_type1pfmet_RMS_vs_recosumet->SetBinError(binValue[aii],recoRMSerror_type1pf);
     }
     
     //
     
     if(debug_)cout<<"I get here,  done rebinning histos "<<endl;
     if(debug_)cout<<"h_tcmet_x_v_reco_pf["<<aii<<"] = "<<h_tcmet_x_v_reco_pf[aii]<<endl;
     double tcrecoRMS_pf =      h_tcmet_x_v_reco_pf[aii]->GetRMS();
     double tcrecoRMSerror_pf = h_tcmet_x_v_reco_pf[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  tcmet_rms_vs_pfrecosumet "<<endl;
     h_tcmet_RMS_vs_pfrecosumet->SetBinContent(binValue[aii],tcrecoRMS_pf);
     h_tcmet_RMS_vs_pfrecosumet->SetBinError(binValue[aii],tcrecoRMSerror_pf);


     double type2recoRMS_pf =      h_type2calomet_x_v_reco_pf[aii]->GetRMS();
     double type2recoRMSerror_pf = h_type2calomet_x_v_reco_pf[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type2calomet_rms_vs_pfrecosumet "<<endl;
     h_type2calomet_RMS_vs_pfrecosumet->SetBinContent(binValue[aii],type2recoRMS_pf);
     h_type2calomet_RMS_vs_pfrecosumet->SetBinError(binValue[aii],type2recoRMSerror_pf);

     if(debug_)cout<<"h_tcmet_x_v_reco_type1pf["<<aii<<"] = "<<h_tcmet_x_v_reco_type1pf[aii]<<endl;
     double tcrecoRMS_type1pf =      h_tcmet_x_v_reco_type1pf[aii]->GetRMS();
     double tcrecoRMSerror_type1pf = h_tcmet_x_v_reco_type1pf[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  tcmet_rms_vs_type1pfrecosumet "<<endl;
     h_tcmet_RMS_vs_type1pfrecosumet->SetBinContent(binValue[aii],tcrecoRMS_type1pf);
     h_tcmet_RMS_vs_type1pfrecosumet->SetBinError(binValue[aii],tcrecoRMSerror_type1pf);


     double type2recoRMS_type1pf =      h_type2calomet_x_v_reco_type1pf[aii]->GetRMS();
     double type2recoRMSerror_type1pf = h_type2calomet_x_v_reco_type1pf[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type2calomet_rms_vs_type1pfrecosumet "<<endl;
     h_type2calomet_RMS_vs_type1pfrecosumet->SetBinContent(binValue[aii],type2recoRMS_type1pf);
     h_type2calomet_RMS_vs_type1pfrecosumet->SetBinError(binValue[aii],type2recoRMSerror_type1pf);

     double tcrecoRMS_type2 =      h_tcmet_x_v_reco_type2[aii]->GetRMS();
     double tcrecoRMSerror_type2 = h_tcmet_x_v_reco_type2[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  tcmet_rms_vs_type2recosumet "<<endl;
     h_tcmet_RMS_vs_type2recosumet->SetBinContent(binValue[aii],tcrecoRMS_type2);
     h_tcmet_RMS_vs_type2recosumet->SetBinError(binValue[aii],tcrecoRMSerror_type2);


     double type2recoRMS_tc =      h_type2calomet_x_v_reco_tc[aii]->GetRMS();
     double type2recoRMSerror_tc = h_type2calomet_x_v_reco_tc[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type2calomet_rms_vs_tcrecosumet "<<endl;
     h_type2calomet_RMS_vs_tcrecosumet->SetBinContent(binValue[aii],type2recoRMS_tc);
     h_type2calomet_RMS_vs_tcrecosumet->SetBinError(binValue[aii],type2recoRMSerror_tc);


     double pfrecoRMS_tc =      h_pfmet_x_v_reco_tc[aii]->GetRMS();
     double pfrecoRMSerror_tc = h_pfmet_x_v_reco_tc[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  pfmet_rms_vs_tcrecosumet "<<endl;
     h_pfmet_RMS_vs_tcrecosumet->SetBinContent(binValue[aii],pfrecoRMS_tc);
     h_pfmet_RMS_vs_tcrecosumet->SetBinError(binValue[aii],pfrecoRMSerror_tc);


     double pfrecoRMS_type2 =      h_pfmet_x_v_reco_type2[aii]->GetRMS();
     double pfrecoRMSerror_type2 = h_pfmet_x_v_reco_type2[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  pfmet_rms_vs_type2recosumet "<<endl;
     h_pfmet_RMS_vs_type2recosumet->SetBinContent(binValue[aii],pfrecoRMS_type2);
     h_pfmet_RMS_vs_type2recosumet->SetBinError(binValue[aii],pfrecoRMSerror_type2);

     double type1pfrecoRMS_tc =      h_type1pfmet_x_v_reco_tc[aii]->GetRMS();
     double type1pfrecoRMSerror_tc = h_type1pfmet_x_v_reco_tc[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type1pfmet_rms_vs_tcrecosumet "<<endl;
     h_type1pfmet_RMS_vs_tcrecosumet->SetBinContent(binValue[aii],type1pfrecoRMS_tc);
     h_type1pfmet_RMS_vs_tcrecosumet->SetBinError(binValue[aii],type1pfrecoRMSerror_tc);


     double type1pfrecoRMS_type2 =      h_type1pfmet_x_v_reco_type2[aii]->GetRMS();
     double type1pfrecoRMSerror_type2 = h_type1pfmet_x_v_reco_type2[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type1pfmet_rms_vs_type2recosumet "<<endl;
     h_type1pfmet_RMS_vs_type2recosumet->SetBinContent(binValue[aii],type1pfrecoRMS_type2);
     h_type1pfmet_RMS_vs_type2recosumet->SetBinError(binValue[aii],type1pfrecoRMSerror_type2);




     double RescalingRMS_tc =      h_tcmet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_tc = h_tcmet_x_v_Rescaling[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  tcmet_rms_vs_rescalingsumet "<<endl;
     h_tcmet_RMS_vs_Rescalingsumet->SetBinContent(binValue[aii],RescalingRMS_tc);
     h_tcmet_RMS_vs_Rescalingsumet->SetBinError(binValue[aii],RescalingRMSerror_tc);

     double RescalingRMS_pf =      h_pfmet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_pf = h_pfmet_x_v_Rescaling[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  pfmet_rms_vs_rescalingsumet "<<endl;
     h_pfmet_RMS_vs_Rescalingsumet->SetBinContent(binValue[aii],RescalingRMS_pf);
     h_pfmet_RMS_vs_Rescalingsumet->SetBinError(binValue[aii],RescalingRMSerror_pf);

     double RescalingRMS_type1pf =      h_type1pfmet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_type1pf = h_type1pfmet_x_v_Rescaling[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type1pfmet_rms_vs_rescalingsumet "<<endl;
     h_type1pfmet_RMS_vs_Rescalingsumet->SetBinContent(binValue[aii],RescalingRMS_type1pf);
     h_type1pfmet_RMS_vs_Rescalingsumet->SetBinError(binValue[aii],RescalingRMSerror_type1pf);

     double RescalingRMS_type2 =      h_type2calomet_x_v_Rescaling[aii]->GetRMS();
     double RescalingRMSerror_type2 = h_type2calomet_x_v_Rescaling[aii]->GetRMSError();
     if(debug_)cout<<"I get here,  type2calomet_rms_vs_rescalingsumet "<<endl;
     h_type2calomet_RMS_vs_Rescalingsumet->SetBinContent(binValue[aii],RescalingRMS_type2);
     h_type2calomet_RMS_vs_Rescalingsumet->SetBinError(binValue[aii],RescalingRMSerror_type2);





     //vs. reco sumet ALL rescaled
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning tc vs rescaled "<<endl;
       //h_tcmet_x_v_RescalingMETALSO[aii]->Rebin(50);

       double width = 2*(h_tcmet_x_v_RescalingMETALSO[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_tc =      h_tcmet_x_v_RescalingMETALSO[aii]->GetRMS();
       double RescalingMETALSORMSerror_tc = h_tcmet_x_v_RescalingMETALSO[aii]->GetRMSError();

       h_tcmet_RMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSORMS_tc);
       h_tcmet_RMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_tc =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_tc = myfit1->GetParError(2);

       h_tcmet_gRMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSOgRMS_tc);
       h_tcmet_gRMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_tc);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning pf vs rescaled "<<endl;
       //h_pfmet_x_v_RescalingMETALSO[aii]->Rebin(50);

       double width = 2*(h_pfmet_x_v_RescalingMETALSO[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_pfmet_x_v_RescalingMETALSO[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_pf =      h_pfmet_x_v_RescalingMETALSO[aii]->GetRMS();
       double RescalingMETALSORMSerror_pf = h_pfmet_x_v_RescalingMETALSO[aii]->GetRMSError();

       h_pfmet_RMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSORMS_pf);
       h_pfmet_RMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSORMSerror_pf);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_pfmet_x_v_RescalingMETALSO[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_pf =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_pf = myfit1->GetParError(2);

       h_pfmet_gRMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSOgRMS_pf);
       h_pfmet_gRMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type2 vs rescaled "<<endl;
       //h_type2calomet_x_v_RescalingMETALSO[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_RescalingMETALSO[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type2calo =      h_type2calomet_x_v_RescalingMETALSO[aii]->GetRMS();
       double RescalingMETALSORMSerror_type2calo = h_type2calomet_x_v_RescalingMETALSO[aii]->GetRMSError();

       h_type2calomet_RMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_type2calo =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_type2calo = myfit1->GetParError(2);

       h_type2calomet_gRMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSOgRMS_type2calo);
       h_type2calomet_gRMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_type2calo);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type1pf vs rescaled "<<endl;
       //h_type1pfmet_x_v_RescalingMETALSO[aii]->Rebin(50);

       double width = 2*(h_type1pfmet_x_v_RescalingMETALSO[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type1pfmet_x_v_RescalingMETALSO[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type1pf =      h_type1pfmet_x_v_RescalingMETALSO[aii]->GetRMS();
       double RescalingMETALSORMSerror_type1pf = h_type1pfmet_x_v_RescalingMETALSO[aii]->GetRMSError();

       h_type1pfmet_RMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSORMS_type1pf);
       h_type1pfmet_RMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSORMSerror_type1pf);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type1pfmet_x_v_RescalingMETALSO[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_type1pf = myfit1->GetParError(2);

       h_type1pfmet_gRMS_vs_RescalingMETALSOsumet->SetBinContent(binValue[aii],RescalingMETALSOgRMS_type1pf);
       h_type1pfmet_gRMS_vs_RescalingMETALSOsumet->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_type1pf);
     }
     
     
     //vs. reco sumet ALL rescaled
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning tc vs rescaled pfsumet "<<endl;
       //h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Rebin(50);

       double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_tc_vs_pf =      h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMS();
       double RescalingMETALSORMSerror_tc_vs_pf = h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMSError();

       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_pf);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_tc_vs_pf =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_tc_vs_pf = myfit1->GetParError(2);

       h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(binValue[aii],RescalingMETALSOgRMS_tc_vs_pf);
       h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_tc_vs_pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type2 vs rescaled type2 calo sumet "<<endl;
       //h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type2calo_vs_pf =      h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMS();
       double RescalingMETALSORMSerror_type2calo_vs_pf = h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->GetRMSError();

       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo_vs_pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo_vs_pf);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSOgRMS_type2calo_vs_pf =      myfit1->GetParameter(2);
       double RescalingMETALSOgRMSerror_type2calo_vs_pf = myfit1->GetParError(2);

       h_type2calomet_gRMS_vs_RescalingMETALSOsumet_vs_pf->SetBinContent(binValue[aii],RescalingMETALSOgRMS_type2calo_vs_pf);
       h_type2calomet_gRMS_vs_RescalingMETALSOsumet_vs_pf->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_type2calo_vs_pf);
     }
     
     //vs. reco sumet ALL type2 rescaled
     if (doExtra) {
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning tc vs rescaled type2 calo sumet "<<endl;
	 //h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSORMS_tc_vs_type2 =      h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS();
	 double RescalingMETALSORMSerror_tc_vs_type2 = h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMSError();
	 
	 h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_type2);
	 h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_type2);

	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSOgRMS_tc_vs_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSOgRMSerror_tc_vs_type2 = myfit1->GetParError(2);
	 
	 h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSOgRMS_tc_vs_type2);
	 h_tcmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_tc_vs_type2);
       }
       
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning  vs rescaled type2 calo sumet "<<endl;
	 //h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);

	 double RescalingMETALSORMS_pf_vs_type2 =      h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS();
	 double RescalingMETALSORMSerror_pf_vs_type2 = h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMSError();
	 
	 h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_pf_vs_type2);
	 h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_pf_vs_type2);

	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSOgRMS_pf_vs_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSOgRMSerror_pf_vs_type2 = myfit1->GetParError(2);
	 
	 h_pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSOgRMS_pf_vs_type2);
	 h_pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_pf_vs_type2);
       }
       
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning type1 vs rescaled type2 calo sumet "<<endl;
	 //h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);

	 double RescalingMETALSORMS_type1pf_vs_type2 =      h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMS();
	 double RescalingMETALSORMSerror_type1pf_vs_type2 = h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->GetRMSError();
	 
	 h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_type1pf_vs_type2);
	 h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_type1pf_vs_type2);
	 
	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSOgRMS_type1pf_vs_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSOgRMSerror_type1pf_vs_type2 = myfit1->GetParError(2);
	 
	 h_type1pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinContent(binValue[aii],RescalingMETALSOgRMS_type1pf_vs_type2);
	 h_type1pfmet_gRMS_vs_RescalingMETALSOsumet_vs_type2->SetBinError(binValue[aii],RescalingMETALSOgRMSerror_type1pf_vs_type2);
       }
     }
     
     //vs. reco sumet ALL type1 rescaled
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning tc vs rescaled type1pfsumet "<<endl;
       //h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Rebin(50);
       
       double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_tc_vs_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_tc_vs_type1pf = myfit1->GetParError(2);

       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type1pf->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_type1pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_type1pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_type1pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type2 vs rescaled type1pfsumet "<<endl;
       //h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type2calo_vs_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo_vs_type1pf = myfit1->GetParError(2);

       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_type1pf->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo_vs_type1pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_type1pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo_vs_type1pf);
     }
     
     //vs. reco type2sumet not rescaled
     if (doExtra) {
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning tc vs unrescaled type2sumet "<<endl;
	 //h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);
	 
	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);

	 double RescalingMETALSORMS_tc_vs_uncal_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSORMSerror_tc_vs_uncal_type2 = myfit1->GetParError(2);
	 
	 h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_uncal_type2);
	 h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_uncal_type2);
       }
       
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning type2 vs unrescaled type2sumet "<<endl;
	 //h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);
	 
	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSORMS_type2calo_vs_uncal_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSORMSerror_type2calo_vs_uncal_type2 = myfit1->GetParError(2);
	 
	 h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo_vs_uncal_type2);
	 h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo_vs_uncal_type2);
       }
       
       
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning pf vs unrescaled type2sumet "<<endl;
	 //h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Rebin(50);

	 double width = 2*(h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);
	 
	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSORMS_pf_vs_uncal_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSORMSerror_pf_vs_uncal_type2 = myfit1->GetParError(2);

	 h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_pf_vs_uncal_type2);
	 h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_pf_vs_uncal_type2);
       }
       
       if(aii>1&&aii<58){
	 if(debug_)cout<<"I get here, rebinning type1pf vs unrescaled type2sumet "<<endl;
	 //h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Rebin(50);
	 
	 double width = 2*(h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->GetRMS());
	 TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
	 h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit0","LLEMIRq","",-width,width);
	 
	 width = 2*(myfit0->GetParameter(2));
	 TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
	 h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Fit("myfit1","LLEMIRq","",-width,width);
	 
	 double RescalingMETALSORMS_type1pf_vs_uncal_type2 =      myfit1->GetParameter(2);
	 double RescalingMETALSORMSerror_type1pf_vs_uncal_type2 = myfit1->GetParError(2);
	 
	 h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinContent(binValue[aii],RescalingMETALSORMS_type1pf_vs_uncal_type2);
	 h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type2->SetBinError(binValue[aii],RescalingMETALSORMSerror_type1pf_vs_uncal_type2);
       }
     }
     
     //vs. reco pfsumet not rescaled
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning tc vs unrescaled pfsumet "<<endl;
       //h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(50);

       double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_tc_vs_uncal_pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_tc_vs_uncal_pf = myfit1->GetParError(2);

       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_uncal_pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_uncal_pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type2 vs unrescaled pfsumet "<<endl;
       //h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type2calo_vs_uncal_pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo_vs_uncal_pf = myfit1->GetParError(2);

       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo_vs_uncal_pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo_vs_uncal_pf);
     }
     
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning pf vs unrescaled pfsumet "<<endl;
       //h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Rebin(50);

       double width = 2*(h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_pf_vs_uncal_pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_pf_vs_uncal_pf = myfit1->GetParError(2);

       h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinContent(binValue[aii],RescalingMETALSORMS_pf_vs_uncal_pf);
       h_pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_pf_vs_uncal_pf);
     }
     if(debug_)cout<<"I get here, done rebinning vs unrescaled pfsumet "<<endl;
     
     //vs. reco type1pfsumet not rescaled
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning tc vs unrescaled type1pfsumet "<<endl;
       //h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Rebin(50);

       double width = 2*(h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_tc_vs_uncal_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_tc_vs_uncal_type1pf = myfit1->GetParError(2);

       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinContent(binValue[aii],RescalingMETALSORMS_tc_vs_uncal_type1pf);
       h_tcmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_tc_vs_uncal_type1pf);
     }
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type2 vs unrescaled type1pfsumet "<<endl;
       //h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Rebin(50);

       double width = 2*(h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type2calo_vs_uncal_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_type2calo_vs_uncal_type1pf = myfit1->GetParError(2);

       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinContent(binValue[aii],RescalingMETALSORMS_type2calo_vs_uncal_type1pf);
       h_type2calomet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_type2calo_vs_uncal_type1pf);
     }
     
     
     if(aii>1&&aii<58){
       if(debug_)cout<<"I get here, rebinning type1pf vs unrescaled type1pfsumet "<<endl;
       //h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Rebin(50);

       double width = 2*(h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->GetRMS());
       TF1 *myfit0 = new TF1("myfit0","gaus",-width,width);
       h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit0","LLEMIRq","",-width,width);

       width = 2*(myfit0->GetParameter(2));
       TF1 *myfit1 = new TF1("myfit1","gaus",-width,width);
       h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Fit("myfit1","LLEMIRq","",-width,width);

       double RescalingMETALSORMS_type1pf_vs_uncal_type1pf =      myfit1->GetParameter(2);
       double RescalingMETALSORMSerror_type1pf_vs_uncal_type1pf = myfit1->GetParError(2);

       h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinContent(binValue[aii],RescalingMETALSORMS_type1pf_vs_uncal_type1pf);
       h_type1pfmet_RMS_vs_RescalingMETALSOsumet_vs_uncal_type1pf->SetBinError(binValue[aii],RescalingMETALSORMSerror_type1pf_vs_uncal_type1pf);
     }
     if(debug_)cout<<"I get here, done rebinning vs unrescaled type1pfsumet "<<endl;
     
   }
   
   //----------------------------------------------------------     
   //Write out histogram file
   //----------------------------------------------------------      
   if(debug_)cout<<"changing to output file"<<endl;
   outfile->cd();
   if(debug_)cout<<"writing out the results"<<endl;
   outfile->Write();
   if(debug_)cout<<"no more steps"<<endl;

   //delete [] infile;
   //delete [] outfile;

}

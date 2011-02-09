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



typedef struct {
  float lumi  ;
  float xs    ;
  float eff   ;
  float numGen;
  float scale ;
}sampleInfo;


sampleInfo ReadInEfficiencies(std::string* efficiencyFile_,std::string sampleKey)
{
  sampleInfo returnVal;
  std::string s;
  bool debug = true;
  if (!efficiencyFile_) {
    std::cout<<"ERROR no efficiency file specified, exiting"<<std::endl;
    exit(1);
  }
  bool matched = false;
  if (debug) std::cout<<"Reading in efficiency file"<<std::endl;
  ifstream is(efficiencyFile_->c_str());
  if(is.good()) {
    while( getline(is,s) )
      {
        if (debug) std::cout<<"read line: " << s<<std::endl;
        if (s[0] == '#' || s.empty()) continue;
  
        if (s.find(sampleKey)!=std::string::npos) {
          matched = true;
          //Line format is sample name - gen events - cross section - efficiency   - note                                                                                                                                                                              
          //                           - int/long   - double/float  - double/float - note                                                                                                                                                                              
	  std::vector<std::string> line;
	  std::string::size_type i =0;
          while (i != s.size()){
            while (i != s.size() && isspace(s[i]))
              ++i;
	    std::string::size_type j = i;
            while (j != s.size() && !isspace(s[j]) && &(s[j])!="-")
              ++j;
            if (i != j){
	      std::cout<<"pushing back "<<s.substr(i, j -i)<<std::endl;
              line.push_back(s.substr(i, j -i));
              i = j;
            }
          }
          returnVal.numGen  = atof(line[2].c_str());
          returnVal.xs      = atof(line[4].c_str());
          returnVal.eff     = atof(line[6].c_str());
          return returnVal;
        }
      }
  }
  else {
    std::cout<<"ERROR opening "<<efficiencyFile_->c_str()<<" exiting!"<<std::endl;
    exit(1);
  }

  std::cout<<"Unable to find sample "<<sampleKey<<" in "<<efficiencyFile_->c_str()<<" exiting!"<<std::endl;
  exit(1);
  //return returnVal;                                                                                                                                                                                                                                                  
}

//void scaleQCD(TString input_filename, TString output_filename, double cross_section_pb, int scale_type)
void scaleQCD(const TString& input_filename)
{   
  
  bool debug_ = false;
  //----------------------------------------------------------
  //Define output file
  //----------------------------------------------------------
  TString output_filename = input_filename+"_scaled";
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
  std::string* sampleList_ = new std::string("/uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/METResolutionStudy/config/sampleDef.txt");
  std::string sampleKey;
  sampleKey = input_filename;
  sampleKey = sampleKey.erase(0,sampleKey.rfind("/QCD"));
  sampleKey = sampleKey.erase(0,1);
  std::cout<<"sampleKey = "<<sampleKey<<std::endl;
  std::cout<<"sampleList_ = "<<sampleList_<<std::endl;
  
  sampleInfo sampVals = ReadInEfficiencies(sampleList_,sampleKey);
  
  sampVals.xs      = 1.;
  sampVals.eff     = 1.;
  sampVals.numGen  = 1.;

  sampVals.lumi = 35.;
  
  sampVals.scale = sampVals.lumi * sampVals.xs * sampVals.eff / sampVals.numGen;
  
  float scale_            = sampVals.scale;
  float luminosity_       = sampVals.lumi;
  float cross_section_    = sampVals.xs;
  float efficiency_       = sampVals.eff;
  float generated_events_ = sampVals.numGen;

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


   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type2[125];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_type2[125];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_type2[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_type2[125];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_pf[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_pf[125];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_pf[125];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_type1pf[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[125];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[125];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[125];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[125];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
   TH1F *h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[125];

   TH1F *h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
   TH1F *h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
   TH1F *h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];
   TH1F *h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[125];

   if(debug_)cout<<"I get here, beginning of defining array histos "<<endl;
   
   for(int aii=0;aii<125;aii++){

     h_tcmet_x_v[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_%i",aii));
     h_pfmet_x_v[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_%i",aii));
     h_type1pfmet_x_v[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_%i",aii));
     h_type1calomet_x_v[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_%i",aii));
     h_type2calomet_x_v[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_%i",aii));
     
     h_tcmet_x_v_reco[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_%i",aii));
     h_pfmet_x_v_reco[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_reco_%i",aii));
     h_type1pfmet_x_v_reco[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_%i",aii));
     h_type1calomet_x_v_reco[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_%i",aii));
     h_type2calomet_x_v_reco[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_%i",aii));
     
     h_tcmet_x_v_reco_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_pf_%i",aii));
     h_type1calomet_x_v_reco_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_pf_%i",aii));
     h_type2calomet_x_v_reco_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_pf_%i",aii));
     
     h_tcmet_x_v_reco_type1pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type1pf_%i",aii));
     h_type1calomet_x_v_reco_type1pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_type1pf_%i",aii));
     h_type2calomet_x_v_reco_type1pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_type1pf_%i",aii));
     
     h_type1calomet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_reco_tc_%i",aii));
     h_type2calomet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_reco_tc_%i",aii));
     
     h_tcmet_x_v_reco_type1[aii] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type1_%i",aii));
     h_tcmet_x_v_reco_type2[aii] = (TH1F*)infile->Get(Form("h_tcmet_x_reco_type2_%i",aii));
     h_pfmet_x_v_reco_type1[aii] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type1_%i",aii));
     h_pfmet_x_v_reco_type2[aii] = (TH1F*)infile->Get(Form("h_pfmet_x_reco_type2_%i",aii));
     
     h_type1pfmet_x_v_reco_type1[aii] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type1_%i",aii));
     h_type1pfmet_x_v_reco_type2[aii] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_type2_%i",aii));
     
     h_pfmet_x_v_reco_tc[aii]      = (TH1F*)infile->Get(Form("h_pfmet_x_reco_tc_%i",aii));
     h_type1pfmet_x_v_reco_tc[aii] = (TH1F*)infile->Get(Form("h_type1pfmet_x_reco_tc_%i",aii));
     
     h_tcmet_x_v_Rescaling[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_Rescaling_%i",aii));
     h_pfmet_x_v_Rescaling[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_Rescaling_%i",aii));
     h_type1pfmet_x_v_Rescaling[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_Rescaling_%i",aii));
     h_type1calomet_x_v_Rescaling[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_Rescaling_%i",aii));
     h_type2calomet_x_v_Rescaling[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_Rescaling_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_%i",aii));
     h_pfmet_x_v_RescalingMETALSO[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_%i",aii));
     h_type1pfmet_x_v_RescalingMETALSO[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type2_%i",aii));
     h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_type2_%i",aii));
     h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_type2_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_type2[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_type2_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_pf_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_pf_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_pf_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_type1pf_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_type1pf_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_type1pf_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type2_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]        = (TH1F*)infile->Get(Form("h_pfmet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_pf_%i",aii));
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]        = (TH1F*)infile->Get(Form("h_tcmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]   = (TH1F*)infile->Get(Form("h_type1pfmet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = (TH1F*)infile->Get(Form("h_type1calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii] = (TH1F*)infile->Get(Form("h_type2calomet_x_RescalingMETALSO_vs_uncal_type1pf_%i",aii));

     ///////////////////////////////////////
     outfile->cd();
     h_tcmet_x_v[aii]->Scale(scale_)        ;
     h_pfmet_x_v[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v[aii]->Scale(scale_)   ;
     h_type1calomet_x_v[aii]->Scale(scale_) ;
     h_type2calomet_x_v[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_reco[aii]->Scale(scale_)        ;
     h_pfmet_x_v_reco[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_reco[aii]->Scale(scale_)   ;
     h_type1calomet_x_v_reco[aii]->Scale(scale_) ;
     h_type2calomet_x_v_reco[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_reco_pf[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_reco_pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_reco_pf[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_reco_type1pf[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_reco_type1pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_reco_type1pf[aii]->Scale(scale_) ;
     
     h_type1calomet_x_v_reco_tc[aii]->Scale(scale_) ;
     h_type2calomet_x_v_reco_tc[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_reco_type1[aii]->Scale(scale_) ;
     h_tcmet_x_v_reco_type2[aii]->Scale(scale_) ;
     h_pfmet_x_v_reco_type1[aii]->Scale(scale_) ;
     h_pfmet_x_v_reco_type2[aii]->Scale(scale_) ;
     
     h_type1pfmet_x_v_reco_type1[aii]->Scale(scale_) ;
     h_type1pfmet_x_v_reco_type2[aii]->Scale(scale_) ;
     
     h_pfmet_x_v_reco_tc[aii]->Scale(scale_)      ;
     h_type1pfmet_x_v_reco_tc[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_Rescaling[aii]->Scale(scale_)        ;
     h_pfmet_x_v_Rescaling[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_Rescaling[aii]->Scale(scale_)   ;
     h_type1calomet_x_v_Rescaling[aii]->Scale(scale_) ;
     h_type2calomet_x_v_Rescaling[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO[aii]->Scale(scale_)        ;
     h_pfmet_x_v_RescalingMETALSO[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_RescalingMETALSO[aii]->Scale(scale_)   ;
     h_type1calomet_x_v_RescalingMETALSO[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Scale(scale_)        ;
     h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Scale(scale_) ;
     h_type1calomet_x_v_RescalingMETALSO_vs_type2[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Scale(scale_)        ;
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Scale(scale_) ;
          
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Scale(scale_)        ;
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Scale(scale_)        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Scale(scale_) ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Scale(scale_)        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Scale(scale_)   ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Scale(scale_) ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Scale(scale_) ;

     if(debug_)cout<<"I get here, near end of single array loop "<<endl;
     
     outfile->cd();
     h_tcmet_x_v[aii]->Write()        ;
     h_pfmet_x_v[aii]->Write()        ;
     h_type1pfmet_x_v[aii]->Write()   ;
     h_type1calomet_x_v[aii]->Write() ;
     h_type2calomet_x_v[aii]->Write() ;
     
     h_tcmet_x_v_reco[aii]->Write()        ;
     h_pfmet_x_v_reco[aii]->Write()        ;
     h_type1pfmet_x_v_reco[aii]->Write()   ;
     h_type1calomet_x_v_reco[aii]->Write() ;
     h_type2calomet_x_v_reco[aii]->Write() ;
     
     h_tcmet_x_v_reco_pf[aii]->Write()        ;
     h_type1calomet_x_v_reco_pf[aii]->Write() ;
     h_type2calomet_x_v_reco_pf[aii]->Write() ;
     
     h_tcmet_x_v_reco_type1pf[aii]->Write()        ;
     h_type1calomet_x_v_reco_type1pf[aii]->Write() ;
     h_type2calomet_x_v_reco_type1pf[aii]->Write() ;
     
     h_type1calomet_x_v_reco_tc[aii]->Write() ;
     h_type2calomet_x_v_reco_tc[aii]->Write() ;
     
     h_tcmet_x_v_reco_type1[aii]->Write() ;
     h_tcmet_x_v_reco_type2[aii]->Write() ;
     h_pfmet_x_v_reco_type1[aii]->Write() ;
     h_pfmet_x_v_reco_type2[aii]->Write() ;
     
     h_type1pfmet_x_v_reco_type1[aii]->Write() ;
     h_type1pfmet_x_v_reco_type2[aii]->Write() ;
     
     h_pfmet_x_v_reco_tc[aii]->Write()      ;
     h_type1pfmet_x_v_reco_tc[aii]->Write() ;
     
     h_tcmet_x_v_Rescaling[aii]->Write()        ;
     h_pfmet_x_v_Rescaling[aii]->Write()        ;
     h_type1pfmet_x_v_Rescaling[aii]->Write()   ;
     h_type1calomet_x_v_Rescaling[aii]->Write() ;
     h_type2calomet_x_v_Rescaling[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO[aii]->Write()        ;
     h_pfmet_x_v_RescalingMETALSO[aii]->Write()        ;
     h_type1pfmet_x_v_RescalingMETALSO[aii]->Write()   ;
     h_type1calomet_x_v_RescalingMETALSO[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_type2[aii]->Write()        ;
     h_pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Write()        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_type2[aii]->Write() ;
     h_type1calomet_x_v_RescalingMETALSO_vs_type2[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_pf[aii]->Write()        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_pf[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO_vs_pf[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_type1pf[aii]->Write()        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO_vs_type1pf[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Write()        ;
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Write()        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Write()        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type2[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Write()        ;
     h_pfmet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Write()        ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_pf[aii]->Write() ;
     
     h_tcmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Write()        ;
     h_type1pfmet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Write()   ;
     h_type1calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Write() ;
     h_type2calomet_x_v_RescalingMETALSO_vs_uncal_type1pf[aii]->Write() ;

     
     if(debug_)cout<<"I get here, end of single array loop "<<endl;
     
   }
   
   outfile->cd();
   
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

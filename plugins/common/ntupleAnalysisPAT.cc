#define ntupleAnalysisPAT_cxx
#include "ntupleAnalysisPAT.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


//void ntupleAnalysisPAT::Loop(const std::string& outputfile, const double& lum, const double& xs, const double& eff, const double& numGen)
//{
//  outfilename_ = outputfile;
//  
//  luminosity_       = lum;
//  cross_section_    = xs;
//  efficiency_       = eff;
//  generated_events_ = numGen;
//
//  if (fChain == 0) return;
//
//  char tmpfile[128];
//  sprintf(tmpfile,"%s",outfilename_.c_str());
//  TFile *file = new TFile(tmpfile,"RECREATE");
//  file->cd();
//   
//  Long64_t nentries = fChain->GetEntriesFast();
//   
//  Long64_t nbytes = 0, nb = 0;
//  for (Long64_t jentry=0; jentry<nentries;jentry++) {
//    Long64_t ientry = LoadTree(jentry);
//    if (ientry < 0) break;
//    nb = fChain->GetEntry(jentry); nbytes += nb;
//  }
//
//  file->cd();
//  file->Write();
//}


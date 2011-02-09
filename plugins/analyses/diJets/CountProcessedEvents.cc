#define CountProcessedEvents_cxx
#include "CountProcessedEvents.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

CountProcessedEvents::CountProcessedEvents(TTree *tree)
  :ntupleAnalysisPAT(tree)
  //  :ntupleAnalysisPAT(tree, "", "", false, "PF", "PF", "PF", "PF")
{
  
}
CountProcessedEvents::~CountProcessedEvents()
{
}

void CountProcessedEvents::Loop()
{

  gROOT->ProcessLine(".L ntuplePragmas.so");
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
   

  Long64_t nbytes = 0, nb = 0;
  unsigned int totalcounter = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry); nbytes += nb;
    ++totalcounter;
    //if (jentry%5000==0||jentry%5000==1)
    //  std::cout<<"done with entry "<<jentry<<std::endl;
  }

  
  int Nevents = totalcounter;
  //int Nevents = nentries;
  std::cout<<"Nevents = "<<Nevents<<std::endl;
}


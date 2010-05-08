//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Oct 20 22:33:25 2009 by ROOT version 5.24/00
// from TTree myvariables/Higgs Analysis Variables
// found on file: C:/root/macros/higgs_debug.root
//////////////////////////////////////////////////////////

#ifndef compareDataMC_h
#define compareDataMC_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <stdlib.h>
#include "TString.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <TLegend.h>
#include <TLatex.h>
#include <THStack.h>
#include "TStopwatch.h"
#include "TLorentzVector.h"
#include <TMath.h>

class compareDataMC {
public :
  
    compareDataMC();
    ~compareDataMC();
   
   virtual void plot(TString hist, TString name, TString title, int alg, bool logscale);
   
};

#endif

#ifdef compareDataMC_cxx
compareDataMC::compareDataMC()
{

}
 

compareDataMC::~compareDataMC()
{
  
}





//________________________________________________________________________________________



#endif 

#ifndef HTMHTANALYZERPAT
#define HTMHTANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
//#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// SUSY include files
//#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"

#include "DataFormats/PatCandidates/interface/Jet.h"

//#include "PhysicsTools/Utilities/interface/deltaPhi.h"
//#include "PhysicsTools/Utilities/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Hemisphere.h"


//
// Class declaration
//

class HTMHTAnalyzerPAT {
 public:
  HTMHTAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~HTMHTAnalyzerPAT();
  
  bool filter(const edm::Event&, const edm::EventSetup&);
  
  //*** Plotting
  /// Define all plots
  void bookTTree();

 private:

  // Configuration parameters
  edm::ParameterSet htmhtParams;
  TString prefix_;

  double jetMaxEta_;  /// for preselection cuts on jets and to calculate HT and MHT
  double jetMinPt_;   /// for preselection cuts on jets and to calculate HT and MHT

  int  debug_;
  bool doMCData_;

  // Data tags
  edm::InputTag jetTag_;
  edm::InputTag genJetTag_;
    
  char logmessage[128];

  // Plots
  TTree * mHTMHTData;      /// Will contain the data passing the jet selection

  bool   m_HTMHTPreselection;

  int    m_NJets;
  double m_Ht;
  double m_MHx;
  double m_MHy;
  double m_MHt;
  double m_MHtphi;
  //double m_MHtsig;

  //Generator level information
  double m_GenHt;
  double m_GenMHx;
  double m_GenMHy;
  double m_GenMHt;
  double m_GenMHtphi;
  //double m_GenMHtsig;

  std::string outputFileName_;

  double localPi;

};
#endif

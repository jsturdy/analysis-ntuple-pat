#ifndef PHOTONANALYZERPAT
#define PHOTONANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// SUSY include files
//#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"

#include "DataFormats/PatCandidates/interface/Photon.h"

//#include "DataFormats/L1Trigger/interface/L1ParticleMap.h"

//#include "UserCode/AnalysisTools/test/ALPGENParticleId.cc"


//
// Class declaration
//
class PhotonAnalyzerPAT {
 public:
  PhotonAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~PhotonAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );
  
  //*** Plotting
  /// Define all plots
  void bookTTree();
  

private:
  
  //configuration parameters
  edm::InputTag photTag_;
  edm::InputTag genTag_;


  double photMaxEta_, photMaxEt_, photMinEt_, photRelIso_;  /// for prelection cuts on photons
  bool   doMCData_;                 /// switch to turn off generator level information
  int    debug_;
  TString prefix_;

  char logmessage[128];

  // Plots
  TTree * mPhotonData;      /// Will contain the additional di-jet specific data

  // Variables
  int    m_PhotN;
  double m_PhotE[50];
  double m_PhotEt[50];
  double m_PhotPt[50];
  double m_PhotPx[50];
  double m_PhotPy[50];
  double m_PhotPz[50];
  double m_PhotEta[50];
  double m_PhotPhi[50];

  double m_PhotTrkIso[50];
  double m_PhotECalIso[50];
  double m_PhotHCalIso[50];
  double m_PhotAllIso[50];

  //bool m_ccPhotAssoc[50];
  bool m_PhotLooseEM[50];
  bool m_PhotLoosePhoton[50];
  bool m_PhotTightPhoton[50];

  double m_PhotGenPdgId[50];
  double m_PhotGenMother[50];
  double m_PhotGenPx[50];
  double m_PhotGenPy[50];
  double m_PhotGenPz[50];
  double m_PhotGenPt[50];
  double m_PhotGenEt[50];
  double m_PhotGenE[50];
  //

  int   genPhotLength;
  int   genPhotIds[500];
  int   genPhotRefs[500];
  int   genPhotStatus[500];
  float genPhotE[500];
  float genPhotPx[500];
  float genPhotPy[500];
  float genPhotPz[500];


  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

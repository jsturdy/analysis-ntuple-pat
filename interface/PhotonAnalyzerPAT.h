#ifndef PHOTONANALYZERPAT
#define PHOTONANALYZERPAT

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
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
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
  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_photP4 (new std::vector<reco::Candidate::LorentzVector>() );
  std::vector<reco::Candidate::LorentzVector> v_photP4;
  int    i_PhotN;
  double mat_d_PhotE[50];
  double mat_d_PhotEt[50];
  double mat_d_PhotPt[50];
  double mat_d_PhotPx[50];
  double mat_d_PhotPy[50];
  double mat_d_PhotPz[50];
  double mat_d_PhotEta[50];
  double mat_d_PhotPhi[50];

  double mat_d_PhotTrkIso[50];
  double mat_d_PhotECalIso[50];
  double mat_d_PhotHCalIso[50];
  double mat_d_PhotAllIso[50];

  //bool m_ccPhotAssoc[50];
  bool mat_b_PhotLooseEM[50];
  bool mat_b_PhotLoosePhoton[50];
  bool mat_b_PhotTightPhoton[50];

  double mat_d_PhotGenPdgId[50];
  double mat_d_PhotGenMother[50];
  double mat_d_PhotGenPx[50];
  double mat_d_PhotGenPy[50];
  double mat_d_PhotGenPz[50];
  double mat_d_PhotGenPt[50];
  double mat_d_PhotGenEt[50];
  double mat_d_PhotGenE[50];
  //

  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_genPhotP4 (new std::vector<reco::Candidate::LorentzVector>() );
  std::vector<reco::Candidate::LorentzVector> v_genPhotP4;
  int   i_genPhotLength;
  int   mat_i_genPhotIds[500];
  int   mat_i_genPhotRefs[500];
  int   mat_i_genPhotStatus[500];
  float mat_f_genPhotE[500];
  float mat_f_genPhotPx[500];
  float mat_f_genPhotPy[500];
  float mat_f_genPhotPz[500];


  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

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
  std::vector<reco::Candidate::LorentzVector> v_photP4;
  int    i_PhotN;

  std::vector<double>  vd_PhotTrkIso;
  std::vector<double>  vd_PhotECalIso;
  std::vector<double>  vd_PhotHCalIso;
  std::vector<double>  vd_PhotAllIso;

  //bool m_ccPhotAssoc[50];
  std::vector<bool>  vb_PhotLooseEM;
  std::vector<bool>  vb_PhotLoosePhoton;
  std::vector<bool>  vb_PhotTightPhoton;

  std::vector<reco::Candidate::LorentzVector> v_genphotP4;
  std::vector<double> vd_PhotGenPdgId;
  std::vector<double> vd_PhotGenMother;
  //

  std::vector<reco::Candidate::LorentzVector> v_genPhotP4;
  int   i_genPhotLength;
  std::vector<int>   vi_genPhotIds;
  std::vector<int>   vi_genPhotRefs;
  std::vector<int>   vi_genPhotStatus;


  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

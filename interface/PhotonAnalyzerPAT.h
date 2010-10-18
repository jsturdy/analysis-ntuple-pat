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

  std::vector<double>  vd_PhotPx;
  std::vector<double>  vd_PhotPy;
  std::vector<double>  vd_PhotPz;
  std::vector<double>  vd_PhotE;

  std::vector<double>  vd_PhotTrkIso;
  std::vector<double>  vd_PhotECalIso;
  std::vector<double>  vd_PhotHCalIso;
  std::vector<double>  vd_PhotAllIso;

  //bool m_ccPhotAssoc[50];
  std::vector<bool>  vb_PhotLooseEM;
  std::vector<bool>  vb_PhotLoosePhoton;
  std::vector<bool>  vb_PhotTightPhoton;

  std::vector<reco::Candidate::LorentzVector> v_genphotP4;
  std::vector<double>  vd_PhotGenPx;
  std::vector<double>  vd_PhotGenPy;
  std::vector<double>  vd_PhotGenPz;
  std::vector<double>  vd_PhotGenE;

  std::vector<double> vd_PhotGenPdgId;
  std::vector<double> vd_PhotGenMother;
  //

  std::vector<reco::Candidate::LorentzVector> v_genPhotP4;
  int   i_genPhotLength;
  std::vector<double>  vd_genPhotPx;
  std::vector<double>  vd_genPhotPy;
  std::vector<double>  vd_genPhotPz;
  std::vector<double>  vd_genPhotE;
  std::vector<int>   vi_genPhotIds;
  std::vector<int>   vi_genPhotRefs;
  std::vector<int>   vi_genPhotStatus;


  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

  void maintenancePhots(const int& nPhots) {
    v_photP4.clear();
    vd_PhotPx.clear();
    vd_PhotPy.clear();
    vd_PhotPz.clear();
    vd_PhotE.clear();
    vd_PhotTrkIso.clear();
    vd_PhotECalIso.clear();
    vd_PhotHCalIso.clear();
    vd_PhotAllIso.clear();
    vb_PhotLooseEM.clear();
    vb_PhotLoosePhoton.clear();
    vb_PhotTightPhoton.clear();
    v_genphotP4.clear();
    vd_PhotGenPx.clear();
    vd_PhotGenPy.clear();
    vd_PhotGenPz.clear();
    vd_PhotGenE.clear();
    vd_PhotGenPdgId.clear();
    vd_PhotGenMother.clear();

    //v_photP4.reserve(nPhots);
    //vd_PhotPx.reserve(nPhots);
    //vd_PhotPy.reserve(nPhots);
    //vd_PhotPz.reserve(nPhots);
    //vd_PhotE.reserve(nPhots);
    //vd_PhotTrkIso.reserve(nPhots);
    //vd_PhotECalIso.reserve(nPhots);
    //vd_PhotHCalIso.reserve(nPhots);
    //vd_PhotAllIso.reserve(nPhots);
    //vb_PhotLooseEM.reserve(nPhots);
    //vb_PhotLoosePhoton.reserve(nPhots);
    //vb_PhotTightPhoton.reserve(nPhots);
    //v_genphotP4.reserve(nPhots);
    //vd_PhotGenPx.reserve(nPhots);
    //vd_PhotGenPy.reserve(nPhots);
    //vd_PhotGenPz.reserve(nPhots);
    //vd_PhotGenE.reserve(nPhots);
    //vd_PhotGenPdgId.reserve(nPhots);
    //vd_PhotGenMother.reserve(nPhots);
  //
  }
  void maintenanceGen(const int& nPhots) {
    v_genPhotP4.clear();
    vd_genPhotPx.clear();
    vd_genPhotPy.clear();
    vd_genPhotPz.clear();
    vd_genPhotE.clear();
    vi_genPhotIds.clear();
    vi_genPhotRefs.clear();
    vi_genPhotStatus.clear();

    //v_genPhotP4.reserve(nPhots);
    //vd_genPhotPx.reserve(nPhots);
    //vd_genPhotPy.reserve(nPhots);
    //vd_genPhotPz.reserve(nPhots);
    //vd_genPhotE.reserve(nPhots);
    //vi_genPhotIds.reserve(nPhots);
    //vi_genPhotRefs.reserve(nPhots);
    //vi_genPhotStatus.reserve(nPhots);
  }
};

#endif

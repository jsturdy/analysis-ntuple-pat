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

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"

#include "DataFormats/PatCandidates/interface/Photon.h"


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
  bool   bool_PhotVeto;

  std::vector<double>  vd_PhotTrkIso;
  std::vector<double>  vd_PhotECalIso;
  std::vector<double>  vd_PhotHCalIso;
  std::vector<double>  vd_PhotAllIso;

  std::vector<double>  vd_PhotTrkIsoDeposit;
  std::vector<double>  vd_PhotECalIsoDeposit;
  std::vector<double>  vd_PhotHCalIsoDeposit;

  //bool m_ccPhotAssoc[50];
  std::vector<bool>  vb_PhotIsEB;
  std::vector<bool>  vb_PhotIsEE;
  //std::vector<bool>  vb_PhotLooseEM;
  std::vector<bool>  vb_PhotLoosePhoton;
  std::vector<bool>  vb_PhotTightPhoton;

  std::vector<double>  vd_PhotHadOverEM;
  std::vector<double>  vd_PhotE2OverE9;
  std::vector<double>  vd_PhotSwissCross;
  //std::vector<double>  vd_PhotTSeed;
  std::vector<double>  vd_PhotSigmaIetaIeta;
  std::vector<bool>    vb_PhotHasPixelSeed;
  std::vector<bool>    vb_PhotHasConversionTracks;

  std::vector<reco::Candidate::LorentzVector> v_genphotP4;

  std::vector<double> vd_PhotGenPdgId;
  std::vector<double> vd_PhotGenMother;
  //

  std::vector<reco::Candidate::LorentzVector> v_genPhotP4;
  int   i_genPhotLength;
  std::vector<int>   vi_genPhotIds;
  std::vector<int>   vi_genPhotRefs;
  std::vector<int>   vi_genPhotStatus;
  std::vector<int>   vi_genPhotDaughters;


  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

  void maintenancePhots(const int& nPhots) {
    v_photP4.clear();

    vd_PhotTrkIso.clear();
    vd_PhotECalIso.clear();
    vd_PhotHCalIso.clear();
    vd_PhotAllIso.clear();

    vd_PhotTrkIsoDeposit.clear();
    vd_PhotECalIsoDeposit.clear();
    vd_PhotHCalIsoDeposit.clear();

    vb_PhotIsEB.clear();
    vb_PhotIsEE.clear();
    //vb_PhotLooseEM.clear();
    vb_PhotLoosePhoton.clear();
    vb_PhotTightPhoton.clear();

    vd_PhotE2OverE9.clear();
    vd_PhotSwissCross.clear();
    //vd_PhotTSeed.clear();
    vd_PhotSigmaIetaIeta.clear();
    vb_PhotHasPixelSeed.clear();
    vb_PhotHasConversionTracks.clear();
    vd_PhotHadOverEM.clear();

    v_genphotP4.clear();
    vd_PhotGenPdgId.clear();
    vd_PhotGenMother.clear();
  }
  void maintenanceGen(const int& nPhots) {
    v_genPhotP4.clear();
    vi_genPhotIds.clear();
    vi_genPhotRefs.clear();
    vi_genPhotStatus.clear();
    vi_genPhotDaughters.clear();
  }
};

#endif

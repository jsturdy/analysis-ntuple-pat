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
  
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  /// Define all plots
  void bookTTree();
  

private:
  
  //configuration parameters
  edm::InputTag photTag_;

  double photMaxEta_, photMaxEt_, photMinEt_, photRelIso_;  /// for prelection cuts on photons
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

  std::vector<double>  vd_PhotPFAllParticleIso;
  std::vector<double>  vd_PhotPFChargedHadronIso;
  std::vector<double>  vd_PhotPFNeutralHadronIso;
  std::vector<double>  vd_PhotPFGammaIso;
 
  //std::vector<double>  vd_PhotTrkIsoDeposit;
  //std::vector<double>  vd_PhotECalIsoDeposit;
  //std::vector<double>  vd_PhotHCalIsoDeposit;
  //
  //std::vector<double>  vd_PhotPFAllParticleIsoDeposit;
  //std::vector<double>  vd_PhotPFChargedHadronIsoDeposit;
  //std::vector<double>  vd_PhotPFNeutralHadronIsoDeposit;
  //std::vector<double>  vd_PhotPFGammaIsoDeposit;

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

  std::vector<int> vi_PhotGenPdgId;
  std::vector<int> vi_PhotGenStatus;
  std::vector<int> vi_PhotGenMother;
  std::vector<int> vi_PhotGenMotherStatus;
  //

  void maintenancePhots(const int& nPhots) {
    v_photP4.clear();

    vd_PhotTrkIso.clear();
    vd_PhotECalIso.clear();
    vd_PhotHCalIso.clear();
    vd_PhotAllIso.clear();

    vd_PhotPFAllParticleIso.clear();
    vd_PhotPFChargedHadronIso.clear();
    vd_PhotPFNeutralHadronIso.clear();
    vd_PhotPFGammaIso.clear();

    //vd_PhotTrkIsoDeposit.clear();
    //vd_PhotECalIsoDeposit.clear();
    //vd_PhotHCalIsoDeposit.clear();
    //
    //vd_PhotPFAllParticleIsoDeposit.clear();
    //vd_PhotPFChargedHadronIsoDeposit.clear();
    //vd_PhotPFNeutralHadronIsoDeposit.clear();
    //vd_PhotPFGammaIsoDeposit.clear();

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
    vi_PhotGenPdgId.clear();
    vi_PhotGenStatus.clear();
    vi_PhotGenMother.clear();
    vi_PhotGenMotherStatus.clear();
  }
};

#endif

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
  void bookTTree(TTree* mPhotonData);
  

private:
  
  //configuration parameters
  edm::InputTag photTag_;

  double photMaxEta_, photMaxEt_, photMinEt_, photRelIso_;  /// for prelection cuts on photons
  int    debug_;
  TString prefix_;

  // Plots
  //TTree * mPhotonData;      /// Will contain the additional di-jet specific data

  // Variables
  int    i_PhotN;
  bool   bool_PhotVeto;
  
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> >  v_photP4;

  std::auto_ptr<std::vector<double> >  vd_PhotTrkIso;
  std::auto_ptr<std::vector<double> >  vd_PhotECalIso;
  std::auto_ptr<std::vector<double> >  vd_PhotHCalIso;
  std::auto_ptr<std::vector<double> >  vd_PhotAllIso;

  std::auto_ptr<std::vector<double> >  vd_PhotPFAllParticleIso;
  std::auto_ptr<std::vector<double> >  vd_PhotPFChargedHadronIso;
  std::auto_ptr<std::vector<double> >  vd_PhotPFNeutralHadronIso;
  std::auto_ptr<std::vector<double> >  vd_PhotPFGammaIso;
 
  std::auto_ptr<std::vector<double> >  vd_PhotTrkIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_PhotECalIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_PhotHCalIsoDeposit;
  
  std::auto_ptr<std::vector<double> >  vd_PhotPFAllParticleIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_PhotPFChargedHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_PhotPFNeutralHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_PhotPFGammaIsoDeposit;

  std::auto_ptr<std::vector<double> >  vd_PhotSCEta ;
  std::auto_ptr<std::vector<double> >  vd_PhotSCPhi ;
  std::auto_ptr<std::vector<double> >  vd_PhotSCEn  ;
  std::auto_ptr<std::vector<double> >  vd_PhotSCPt  ;
  std::auto_ptr<std::vector<double> >  vd_PhotSCRawE;

  std::auto_ptr<std::vector<int> >  vb_PhotIsEB;
  std::auto_ptr<std::vector<int> >  vb_PhotIsEE;
  std::auto_ptr<std::vector<int> >  vb_PhotIsEBGap;
  std::auto_ptr<std::vector<int> >  vb_PhotIsEEGap;
  std::auto_ptr<std::vector<int> >  vb_PhotIsEBEEGap;

  std::auto_ptr<std::vector<int> >  vb_PhotLoosePhoton;
  std::auto_ptr<std::vector<int> >  vb_PhotTightPhoton;

  std::auto_ptr<std::vector<double> >  vd_PhotHadOverEM;
  std::auto_ptr<std::vector<double> >  vd_PhotE2OverE9;
  std::auto_ptr<std::vector<double> >  vd_PhotSwissCross;
  std::auto_ptr<std::vector<double> >  vd_PhotTSeed;
  std::auto_ptr<std::vector<double> >  vd_PhotESeed;
  std::auto_ptr<std::vector<double> >  vd_PhotSigmaIetaIeta;
  std::auto_ptr<std::vector<int> >  vb_PhotHasPixelSeed;
  std::auto_ptr<std::vector<int> >  vb_PhotHasConversionTracks;

  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> >  v_genphotP4;

  std::auto_ptr<std::vector<int> >  vi_PhotGenPdgId;
  std::auto_ptr<std::vector<int> >  vi_PhotGenStatus;
  std::auto_ptr<std::vector<int> >  vi_PhotGenMother;
  std::auto_ptr<std::vector<int> >  vi_PhotGenMotherStatus;
  //

  void maintenancePhots() {
    v_photP4->clear();

    vd_PhotTrkIso->clear();
    vd_PhotECalIso->clear();
    vd_PhotHCalIso->clear();
    vd_PhotAllIso->clear();

    vd_PhotPFAllParticleIso->clear();
    vd_PhotPFChargedHadronIso->clear();
    vd_PhotPFNeutralHadronIso->clear();
    vd_PhotPFGammaIso->clear();

    vd_PhotTrkIsoDeposit->clear();
    vd_PhotECalIsoDeposit->clear();
    vd_PhotHCalIsoDeposit->clear();
    
    vd_PhotPFAllParticleIsoDeposit->clear();
    vd_PhotPFChargedHadronIsoDeposit->clear();
    vd_PhotPFNeutralHadronIsoDeposit->clear();
    vd_PhotPFGammaIsoDeposit->clear();

    vd_PhotSCEta ->clear();
    vd_PhotSCPhi ->clear();
    vd_PhotSCEn  ->clear();
    vd_PhotSCPt  ->clear();
    vd_PhotSCRawE->clear();

    vb_PhotIsEB->clear();
    vb_PhotIsEE->clear();
    vb_PhotIsEBGap->clear();
    vb_PhotIsEEGap->clear();
    vb_PhotIsEBEEGap->clear();

    vb_PhotLoosePhoton->clear();
    vb_PhotTightPhoton->clear();

    vd_PhotHadOverEM->clear();
    vd_PhotE2OverE9->clear();
    vd_PhotSwissCross->clear();
    vd_PhotTSeed->clear();
    vd_PhotESeed->clear();
    vd_PhotSigmaIetaIeta->clear();
    vb_PhotHasPixelSeed->clear();
    vb_PhotHasConversionTracks->clear();

    v_genphotP4->clear();

    vi_PhotGenPdgId->clear();
    vi_PhotGenStatus->clear();
    vi_PhotGenMother->clear();
    vi_PhotGenMotherStatus->clear();

  }
};

#endif

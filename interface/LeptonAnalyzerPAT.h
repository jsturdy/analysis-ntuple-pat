#ifndef LEPTONANALYZERPAT
#define LEPTONANALYZERPAT

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

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h" 

#include "DataFormats/TauReco/interface/PFTau.h"
#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"

#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"

//#include "DataFormats/L1Trigger/interface/L1ParticleMap.h"

//#include "UserCode/AnalysisTools/test/ALPGENParticleId.cc"


//
// Class declaration
//
class LeptonAnalyzerPAT {
 public:
  LeptonAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~LeptonAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );
  
  //*** Plotting
  /// Define all plots
  void bookTTree();
  

private:
  
  //configuration parameters
  edm::ParameterSet leptonParams;
  edm::InputTag elecTag_;
  edm::InputTag muonTag_;
  edm::InputTag tauTag_;

  double elecMaxEta_, elecMaxEt_, elecMinEt_, elecRelIso_;  /// for preselection cuts on electrons
  double muonMaxEta_, muonMaxEt_, muonMinEt_, muonRelIso_;  /// for preselection cuts on muons
  double tauMaxEta_, tauMaxEt_, tauMinEt_, tauRelIso_;      /// for preselection cuts on taus

  int    debug_;
  TString prefix_;

  char logmessage[128];
    
  // Plots
  TTree * mLeptonData;   /// Will contain the lepton data after cuts

  // Variables
  std::vector<reco::Candidate::LorentzVector> v_elecP4;
  std::vector<reco::Candidate::LorentzVector> v_genelecP4;
  int    i_ElecN;
  int    i_ElecNIso;
  bool   bool_ElecVeto;
  bool   bool_spike;
  
  std::vector<double> vd_ElecTrkIso;
  std::vector<double> vd_ElecECalIso;
  std::vector<double> vd_ElecHCalIso;
  std::vector<double> vd_ElecAllIso;

  std::vector<double> vd_ElecPFAllParticleIso;
  std::vector<double> vd_ElecPFChargedHadronIso;
  std::vector<double> vd_ElecPFNeutralHadronIso;
  std::vector<double> vd_ElecPFGammaIso;

  std::vector<double> vd_ElecTrkChiNorm;
  std::vector<double> vd_ElecCharge;

  std::vector<float>  vf_ElecIdLoose;
  std::vector<float>  vf_ElecIdTight;
  std::vector<float>  vf_ElecIdRobLoose;
  std::vector<float>  vf_ElecIdRobTight;
  std::vector<float>  vf_ElecIdRobHighE;

  std::vector<double>  vd_ElecHadOverEM;
  std::vector<double>  vd_ElecE2OverE9;
  std::vector<double>  vd_ElecSwissCross;
  //std::vector<double>  vd_ElecTSeed;
  std::vector<double>  vd_ElecSigmaIetaIeta;

  std::vector<double> vd_ElecChargeMode;
  std::vector<double> vd_ElecPtTrkMode;
  std::vector<double> vd_ElecQOverPErrTrkMode;

  std::vector<int>    vi_ElecGenPdgId;
  std::vector<int>    vi_ElecGenStatus;
  std::vector<int>    vi_ElecGenMother;
  std::vector<int>    vi_ElecGenMotherStatus;

  std::vector<double> vd_ElecCaloEnergy;
  std::vector<double> vd_ElecHOverE;
  std::vector<double> vd_ElecVx;
  std::vector<double> vd_ElecVy;
  std::vector<double> vd_ElecVz;
  std::vector<double> vd_ElecD0;
  std::vector<double> vd_ElecD0Err;
  std::vector<double> vd_ElecDz;
  std::vector<double> vd_ElecPtTrk;
  std::vector<double> vd_ElecQOverPErrTrk;
  std::vector<double> vd_ElecLostHits;
  std::vector<double> vd_ElecValidHits;
  //std::vector<double> vd_ElecNCluster;
  std::vector<double> vd_ElecEtaTrk;
  std::vector<double> vd_ElecPhiTrk;
  std::vector<double> vd_ElecWidthClusterEta;
  std::vector<double> vd_ElecWidthClusterPhi;
  std::vector<double> vd_ElecPinTrk;
  std::vector<double> vd_ElecPoutTrk;
  std::vector<double> vd_ElecNormChi2;
  //std::vector<bool> vb_ccElecAssoc;

  std::vector<double> vd_ElecECalIsoDeposit;
  std::vector<double> vd_ElecHCalIsoDeposit;

  std::vector<reco::Candidate::LorentzVector> v_muonP4;
  std::vector<reco::Candidate::LorentzVector> v_genmuonP4;
  int    i_MuonN;
  bool   bool_MuonVeto;

  std::vector<double> vd_MuonTrkIso;
  std::vector<double> vd_MuonECalIso;
  std::vector<double> vd_MuonHCalIso;
  std::vector<double> vd_MuonAllIso;

  std::vector<double> vd_MuonPFAllParticleIso;
  std::vector<double> vd_MuonPFChargedHadronIso;
  std::vector<double> vd_MuonPFNeutralHadronIso;
  std::vector<double> vd_MuonPFGammaIso;

  std::vector<double> vd_MuonTrkChiNorm;
  std::vector<double> vd_MuonCharge;

  std::vector<bool> vb_MuonIsGlobal;
  std::vector<bool> vb_MuonIsStandAlone;
  std::vector<bool> vb_MuonIsTracker;

  std::vector<bool> vb_MuonGlobalMuonPromptTight;

  std::vector<bool> vb_MuonAllArbitrated;
  std::vector<bool> vb_MuonTrackerMuonArbitrated;
  std::vector<bool> vb_MuonGMTkKinkTight;
  std::vector<bool> vb_MuonGMTkChiCompatibility;
  std::vector<bool> vb_MuonGMStaChiCompatibility;
  std::vector<bool> vb_MuonTM2DCompatibilityLoose;
  std::vector<bool> vb_MuonTM2DCompatibilityTight;
  std::vector<bool> vb_MuonTMOneStationLoose;
  std::vector<bool> vb_MuonTMOneStationTight;
  std::vector<bool> vb_MuonTMLastStationLoose;
  std::vector<bool> vb_MuonTMLastStationTight;
  std::vector<bool> vb_MuonTMLastStationAngLoose;
  std::vector<bool> vb_MuonTMLastStationAngTight;
  std::vector<bool> vb_MuonTMLastStationOptimizedLowPtLoose;
  std::vector<bool> vb_MuonTMLastStationOptimizedLowPtTight;
  std::vector<bool> vb_MuonTMLastStationOptimizedBarrelLowPtLoose;
  std::vector<bool> vb_MuonTMLastStationOptimizedBarrelLowPtTight;

  std::vector<double> vd_MuonECalIsoDeposit;
  std::vector<double> vd_MuonHCalIsoDeposit;
  
  std::vector<double> vd_MuonCombChi2;
  std::vector<double> vd_MuonCombNdof;
  std::vector<double> vd_MuonTrkD0;
  std::vector<double> vd_MuonTrkD0Err;
  
  std::vector<double> vd_MuonId;
  std::vector<double> vd_MuonCombVx;
  std::vector<double> vd_MuonCombVy;
  std::vector<double> vd_MuonCombVz;
  std::vector<double> vd_MuonCombD0;
  std::vector<double> vd_MuonCombD0Err;
  std::vector<double> vd_MuonCombDz;

  std::vector<double> vd_MuonStandValidHits;
  std::vector<double> vd_MuonStandLostHits;
  std::vector<double> vd_MuonStandPt;
  std::vector<double> vd_MuonStandPz;
  std::vector<double> vd_MuonStandP;
  std::vector<double> vd_MuonStandEta;
  std::vector<double> vd_MuonStandPhi;
  std::vector<double> vd_MuonStandChi;
  std::vector<double> vd_MuonStandCharge;
  std::vector<double> vd_MuonStandQOverPErr;

  std::vector<double> vd_MuonTrkValidHits;
  std::vector<double> vd_MuonTrkLostHits;
  std::vector<double> vd_MuonTrkPt;
  std::vector<double> vd_MuonTrkPz;
  std::vector<double> vd_MuonTrkP;
  std::vector<double> vd_MuonTrkEta;
  std::vector<double> vd_MuonTrkPhi;
  std::vector<double> vd_MuonTrkChi;
  std::vector<double> vd_MuonTrkCharge;
  std::vector<double> vd_MuonTrkQOverPErr;
  std::vector<double> vd_MuonTrkOuterZ;
  std::vector<double> vd_MuonTrkOuterR;

  std::vector<int>    vi_MuonGenPdgId;
  std::vector<int>    vi_MuonGenStatus;
  std::vector<int>    vi_MuonGenMother;
  std::vector<int>    vi_MuonGenMotherStatus;


  // Variables
  enum TauIDType {
    Electron,
    Muon,
    OneProng0Pi0,
    OneProng1Pi0,
    OneProng2Pi0,
    OneProngOther,
    ThreeProng0Pi0,
    ThreeProng1Pi0,
    ThreeProng2Pi0,
    ThreeProngOther,
    Rare              
  };

  std::map<std::string,TauIDType> tauidMap;

  std::vector<reco::Candidate::LorentzVector> v_tauP4;
  std::vector<reco::Candidate::LorentzVector> v_gentauP4;
  std::vector<reco::Candidate::LorentzVector> v_gentaujetP4;
  int    i_TauN;
  int    i_TauNIso;
  bool   bool_TauVeto;
  std::vector<double> vd_TauCharge;

  std::vector<int> vi_TauGenPdgId;
  std::vector<int> vi_TauGenStatus;
  std::vector<int> vi_TauGenMother;
  std::vector<int> vi_TauGenMotherStatus;
  std::vector<int> vi_TauGen;

  std::vector<int>    vi_TauSigTrk;
  std::vector<double> vd_TauTrkIso;
  std::vector<double> vd_TauECalIso;
  std::vector<double> vd_TauHCalIso;
  std::vector<double> vd_TauAllIso;

  std::vector<double> vd_TauPFAllParticleIso;
  std::vector<double> vd_TauPFChargedHadronIso;
  std::vector<double> vd_TauPFNeutralHadronIso;
  std::vector<double> vd_TauPFGammaIso;

  std::vector<double> vd_TauVx;
  std::vector<double> vd_TauVy;
  std::vector<double> vd_TauVz;
  std::vector<double> vd_TauD0;
  std::vector<double> vd_TauD0Err;
  std::vector<double> vd_TauDz;

  std::vector<float> vf_TauIdElec;
  std::vector<float> vf_TauIdMuon;
  std::vector<float> vf_TauIdIso;
  std::vector<float> vf_TauIdNCfrHalf;
  std::vector<float> vf_TauIdNCfrQuarter;
  std::vector<float> vf_TauIdNCfrTenth;
  std::vector<float> vf_TauIdNCfrFull;


  void maintenanceElecs(const int& nElecs) {
    v_elecP4.clear();
    v_genelecP4.clear();
    
    vd_ElecTrkIso.clear();
    vd_ElecECalIso.clear();
    vd_ElecHCalIso.clear();
    vd_ElecAllIso.clear();

    vd_ElecPFAllParticleIso.clear();
    vd_ElecPFChargedHadronIso.clear();
    vd_ElecPFNeutralHadronIso.clear();
    vd_ElecPFGammaIso.clear();

    vd_ElecTrkChiNorm.clear();
    vd_ElecCharge.clear();
    
    vf_ElecIdLoose.clear();
    vf_ElecIdTight.clear();
    vf_ElecIdRobLoose.clear();
    vf_ElecIdRobTight.clear();
    vf_ElecIdRobHighE.clear();
    vd_ElecChargeMode.clear();
    vd_ElecPtTrkMode.clear();
    vd_ElecQOverPErrTrkMode.clear();
    
    vd_ElecE2OverE9.clear();
    vd_ElecSwissCross.clear();
    //vd_ElecTSeed.clear();
    vd_ElecSigmaIetaIeta.clear();
    vd_ElecHadOverEM.clear();

    vi_ElecGenPdgId.clear();
    vi_ElecGenStatus.clear();
    vi_ElecGenMother.clear();
    vi_ElecGenMotherStatus.clear();
    
    vd_ElecCaloEnergy.clear();
    vd_ElecHOverE.clear();
    vd_ElecVx.clear();
    vd_ElecVy.clear();
    vd_ElecVz.clear();
    vd_ElecD0.clear();
    vd_ElecD0Err.clear();
    vd_ElecDz.clear();
    vd_ElecPtTrk.clear();
    vd_ElecQOverPErrTrk.clear();
    vd_ElecLostHits.clear();
    vd_ElecValidHits.clear();
    //vd_ElecNCluster.clear();
    vd_ElecEtaTrk.clear();
    vd_ElecPhiTrk.clear();
    vd_ElecWidthClusterEta.clear();
    vd_ElecWidthClusterPhi.clear();
    vd_ElecPinTrk.clear();
    vd_ElecPoutTrk.clear();
    vd_ElecNormChi2.clear();
    //vb_ccElecAssoc.clear();
    
    vd_ElecECalIsoDeposit.clear();
    vd_ElecHCalIsoDeposit.clear();
  }

  void maintenanceMuons(const int& nMuons) {
    v_muonP4.clear();
    v_genmuonP4.clear();

    vd_MuonTrkIso.clear();
    vd_MuonECalIso.clear();
    vd_MuonHCalIso.clear();
    vd_MuonAllIso.clear();

    vd_MuonPFAllParticleIso.clear();
    vd_MuonPFChargedHadronIso.clear();
    vd_MuonPFNeutralHadronIso.clear();
    vd_MuonPFGammaIso.clear();

    vd_MuonTrkChiNorm.clear();
    vd_MuonCharge.clear();

    vb_MuonIsGlobal.clear();
    vb_MuonIsStandAlone.clear();
    vb_MuonIsTracker.clear();

    vb_MuonGlobalMuonPromptTight.clear();

    vb_MuonAllArbitrated.clear();
    vb_MuonTrackerMuonArbitrated.clear();
    vb_MuonGMTkKinkTight.clear();
    vb_MuonGMTkChiCompatibility.clear();
    vb_MuonGMStaChiCompatibility.clear();
    vb_MuonTM2DCompatibilityLoose.clear();
    vb_MuonTM2DCompatibilityTight.clear();
    vb_MuonTMOneStationLoose.clear();
    vb_MuonTMOneStationTight.clear();
    vb_MuonTMLastStationLoose.clear();
    vb_MuonTMLastStationTight.clear();
    vb_MuonTMLastStationAngLoose.clear();
    vb_MuonTMLastStationAngTight.clear();
    vb_MuonTMLastStationOptimizedLowPtLoose.clear();
    vb_MuonTMLastStationOptimizedLowPtTight.clear();
    vb_MuonTMLastStationOptimizedBarrelLowPtLoose.clear();
    vb_MuonTMLastStationOptimizedBarrelLowPtTight.clear();

    vd_MuonECalIsoDeposit.clear();
    vd_MuonHCalIsoDeposit.clear();
  
    vd_MuonCombChi2.clear();
    vd_MuonCombNdof.clear();
    vd_MuonTrkD0.clear();
    vd_MuonTrkD0Err.clear();
  
    vd_MuonId.clear();
    vd_MuonCombVx.clear();
    vd_MuonCombVy.clear();
    vd_MuonCombVz.clear();
    vd_MuonCombD0.clear();
    vd_MuonCombD0Err.clear();
    vd_MuonCombDz.clear();

    vd_MuonStandValidHits.clear();
    vd_MuonStandLostHits.clear();
    vd_MuonStandPt.clear();
    vd_MuonStandPz.clear();
    vd_MuonStandP.clear();
    vd_MuonStandEta.clear();
    vd_MuonStandPhi.clear();
    vd_MuonStandChi.clear();
    vd_MuonStandCharge.clear();
    vd_MuonStandQOverPErr.clear();

    vd_MuonTrkValidHits.clear();
    vd_MuonTrkLostHits.clear();
    vd_MuonTrkPt.clear();
    vd_MuonTrkPz.clear();
    vd_MuonTrkP.clear();
    vd_MuonTrkEta.clear();
    vd_MuonTrkPhi.clear();
    vd_MuonTrkChi.clear();
    vd_MuonTrkCharge.clear();
    vd_MuonTrkQOverPErr.clear();
    vd_MuonTrkOuterZ.clear();
    vd_MuonTrkOuterR.clear();

    vi_MuonGenPdgId.clear();
    vi_MuonGenStatus.clear();
    vi_MuonGenMother.clear();
    vi_MuonGenMotherStatus.clear();
  }

  void maintenanceTaus(const int& nTaus) {
    tauidMap.clear();
  
    v_tauP4.clear();
    v_gentauP4.clear();
    v_gentaujetP4.clear();
    vd_TauCharge.clear();

    vi_TauGenPdgId.clear();
    vi_TauGenStatus.clear();
    vi_TauGenMother.clear();
    vi_TauGenMotherStatus.clear();
    vi_TauGen.clear();
    
    vd_TauTrkIso.clear();
    vd_TauECalIso.clear();
    vd_TauHCalIso.clear();
    vd_TauAllIso.clear();

    vd_TauPFAllParticleIso.clear();
    vd_TauPFChargedHadronIso.clear();
    vd_TauPFNeutralHadronIso.clear();
    vd_TauPFGammaIso.clear();

    vd_TauVx.clear();
    vd_TauVy.clear();
    vd_TauVz.clear();
    vd_TauD0.clear();
    vd_TauD0Err.clear();
    vd_TauDz.clear();


    vf_TauIdElec.clear();
    vf_TauIdMuon.clear();
    vf_TauIdIso.clear();
    vf_TauIdNCfrHalf.clear();
    vf_TauIdNCfrQuarter.clear();
    vf_TauIdNCfrTenth.clear();
    vf_TauIdNCfrFull.clear();
  }  
};

#endif

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

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

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
  
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  /// Define all plots
  void bookTTree();
  

private:
  
  //configuration parameters
  edm::ParameterSet leptonParams;
  edm::InputTag elecTag_;
  edm::InputTag muonTag_;
  edm::InputTag tauTag_;
  edm::InputTag _vtxTag;
  edm::InputTag _beamspotTag;

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
  
  std::vector<double> vd_ElecdB;
  std::vector<double> vd_ElecdBerr;

  std::vector<double> vd_ElecTrkIso;
  std::vector<double> vd_ElecECalIso;
  std::vector<double> vd_ElecHCalIso;
  std::vector<double> vd_ElecAllIso;

  std::vector<double> vd_ElecPFAllParticleIso;
  std::vector<double> vd_ElecPFChargedHadronIso;
  std::vector<double> vd_ElecPFNeutralHadronIso;
  std::vector<double> vd_ElecPFGammaIso;

  std::vector<double> vd_ElecTrkIsoDeposit;
  std::vector<double> vd_ElecECalIsoDeposit;
  std::vector<double> vd_ElecHCalIsoDeposit;

  std::vector<double> vd_ElecPFAllParticleIsoDeposit;
  std::vector<double> vd_ElecPFChargedHadronIsoDeposit;
  std::vector<double> vd_ElecPFNeutralHadronIsoDeposit;
  std::vector<double> vd_ElecPFGammaIsoDeposit;

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
  std::vector<double> vd_ElecPVDxy;
  std::vector<double> vd_ElecBSDxy;
  std::vector<double> vd_ElecDxy;
  std::vector<double> vd_ElecDxyErr;
  std::vector<double> vd_ElecD0;
  std::vector<double> vd_ElecD0Err;
  std::vector<double> vd_ElecDz;
  std::vector<double> vd_ElecDzErr;
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
  //std::vector<int> vb_ccElecAssoc;

  std::vector<reco::Candidate::LorentzVector> v_muonP4;
  std::vector<reco::Candidate::LorentzVector> v_genmuonP4;
  int    i_MuonN;
  bool   bool_MuonVeto;

  std::vector<double> vd_MuondB;
  std::vector<double> vd_MuondBerr;

  std::vector<double> vd_MuonTrkIso;
  std::vector<double> vd_MuonECalIso;
  std::vector<double> vd_MuonHCalIso;
  std::vector<double> vd_MuonAllIso;

  std::vector<double> vd_MuonPFAllParticleIso;
  std::vector<double> vd_MuonPFChargedHadronIso;
  std::vector<double> vd_MuonPFNeutralHadronIso;
  std::vector<double> vd_MuonPFGammaIso;

  std::vector<double> vd_MuonTrkIsoDeposit;
  std::vector<double> vd_MuonECalIsoDeposit;
  std::vector<double> vd_MuonHCalIsoDeposit;
  std::vector<double> vd_MuonECalIsoDepositR03;
  std::vector<double> vd_MuonHCalIsoDepositR03;

  std::vector<double> vd_MuonPFAllParticleIsoDeposit;
  std::vector<double> vd_MuonPFChargedHadronIsoDeposit;
  std::vector<double> vd_MuonPFNeutralHadronIsoDeposit;
  std::vector<double> vd_MuonPFGammaIsoDeposit;

  //Muon ID results
  std::vector<int> vb_MuonIsGlobal;
  std::vector<int> vb_MuonIsStandAlone;
  std::vector<int> vb_MuonIsTracker;

  std::vector<int> vb_MuonGlobalMuonPromptTight;

  std::vector<int> vb_MuonAllArbitrated;
  std::vector<int> vb_MuonTrackerMuonArbitrated;
  std::vector<int> vb_MuonGMTkKinkTight;
  std::vector<int> vb_MuonGMTkChiCompatibility;
  std::vector<int> vb_MuonGMStaChiCompatibility;
  std::vector<int> vb_MuonTM2DCompatibilityLoose;
  std::vector<int> vb_MuonTM2DCompatibilityTight;
  std::vector<int> vb_MuonTMOneStationLoose;
  std::vector<int> vb_MuonTMOneStationTight;
  std::vector<int> vb_MuonTMLastStationLoose;
  std::vector<int> vb_MuonTMLastStationTight;
  std::vector<int> vb_MuonTMLastStationAngLoose;
  std::vector<int> vb_MuonTMLastStationAngTight;
  std::vector<int> vb_MuonTMLastStationOptimizedLowPtLoose;
  std::vector<int> vb_MuonTMLastStationOptimizedLowPtTight;
  std::vector<int> vb_MuonTMLastStationOptimizedBarrelLowPtLoose;
  std::vector<int> vb_MuonTMLastStationOptimizedBarrelLowPtTight;

  std::vector<double> vd_MuonId;

  //Variables for combined muons
  std::vector<double> vd_MuonCombVx;
  std::vector<double> vd_MuonCombVy;
  std::vector<double> vd_MuonCombVz;
  std::vector<double> vd_MuonCombPVDxy;
  std::vector<double> vd_MuonCombBSDxy;
  std::vector<double> vd_MuonCombDxy;
  std::vector<double> vd_MuonCombDxyErr;
  std::vector<double> vd_MuonCombD0;
  std::vector<double> vd_MuonCombD0Err;
  std::vector<double> vd_MuonCombDz;
  std::vector<double> vd_MuonCombDzErr;
  std::vector<double> vd_MuonCombChi2;
  std::vector<double> vd_MuonCombNdof;
  std::vector<double> vd_MuonCombPt;
  std::vector<double> vd_MuonCombPz;
  std::vector<double> vd_MuonCombP;
  std::vector<double> vd_MuonCombEta;
  std::vector<double> vd_MuonCombPhi;
  std::vector<double> vd_MuonCombChi;
  std::vector<double> vd_MuonCombCharge;
  std::vector<double> vd_MuonCombQOverPErr;

  //Variables for Stand alone muons
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

  std::vector<double> vd_MuonTrkChiNorm;
  std::vector<double> vd_MuonCharge;
  std::vector<double> vd_MuonTrkValidHits;
  std::vector<double> vd_MuonTrkLostHits;
  std::vector<double> vd_MuonTrkPVDxy;
  std::vector<double> vd_MuonTrkBSDxy;
  std::vector<double> vd_MuonTrkDxy;
  std::vector<double> vd_MuonTrkDxyErr;
  std::vector<double> vd_MuonTrkD0;
  std::vector<double> vd_MuonTrkD0Err;
  std::vector<double> vd_MuonTrkDz;
  std::vector<double> vd_MuonTrkDzErr;
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

  std::vector<double> vd_MuonPickyTrkChiNorm;
  std::vector<double> vd_MuonPickyCharge;
  std::vector<double> vd_MuonPickyTrkValidHits;
  std::vector<double> vd_MuonPickyTrkLostHits;
  std::vector<double> vd_MuonPickyTrkPVDxy;
  std::vector<double> vd_MuonPickyTrkBSDxy;
  std::vector<double> vd_MuonPickyTrkDxy;
  std::vector<double> vd_MuonPickyTrkDxyErr;
  std::vector<double> vd_MuonPickyTrkD0;
  std::vector<double> vd_MuonPickyTrkD0Err;
  std::vector<double> vd_MuonPickyTrkDz;
  std::vector<double> vd_MuonPickyTrkDzErr;
  std::vector<double> vd_MuonPickyTrkPt;
  std::vector<double> vd_MuonPickyTrkPz;
  std::vector<double> vd_MuonPickyTrkP;
  std::vector<double> vd_MuonPickyTrkEta;
  std::vector<double> vd_MuonPickyTrkPhi;
  std::vector<double> vd_MuonPickyTrkChi;
  std::vector<double> vd_MuonPickyTrkCharge;
  std::vector<double> vd_MuonPickyTrkQOverPErr;
  std::vector<double> vd_MuonPickyTrkOuterZ;
  std::vector<double> vd_MuonPickyTrkOuterR;

  std::vector<double> vd_MuonTPFMSTrkChiNorm;
  std::vector<double> vd_MuonTPFMSCharge;
  std::vector<double> vd_MuonTPFMSTrkValidHits;
  std::vector<double> vd_MuonTPFMSTrkLostHits;
  std::vector<double> vd_MuonTPFMSTrkPVDxy;
  std::vector<double> vd_MuonTPFMSTrkBSDxy;
  std::vector<double> vd_MuonTPFMSTrkDxy;
  std::vector<double> vd_MuonTPFMSTrkDxyErr;
  std::vector<double> vd_MuonTPFMSTrkD0;
  std::vector<double> vd_MuonTPFMSTrkD0Err;
  std::vector<double> vd_MuonTPFMSTrkDz;
  std::vector<double> vd_MuonTPFMSTrkDzErr;
  std::vector<double> vd_MuonTPFMSTrkPt;
  std::vector<double> vd_MuonTPFMSTrkPz;
  std::vector<double> vd_MuonTPFMSTrkP;
  std::vector<double> vd_MuonTPFMSTrkEta;
  std::vector<double> vd_MuonTPFMSTrkPhi;
  std::vector<double> vd_MuonTPFMSTrkChi;
  std::vector<double> vd_MuonTPFMSTrkCharge;
  std::vector<double> vd_MuonTPFMSTrkQOverPErr;
  std::vector<double> vd_MuonTPFMSTrkOuterZ;
  std::vector<double> vd_MuonTPFMSTrkOuterR;

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

  std::vector<double> vd_TauTrkIsoDeposit;
  std::vector<double> vd_TauECalIsoDeposit;
  std::vector<double> vd_TauHCalIsoDeposit;

  std::vector<double> vd_TauPFAllParticleIsoDeposit;
  std::vector<double> vd_TauPFChargedHadronIsoDeposit;
  std::vector<double> vd_TauPFNeutralHadronIsoDeposit;
  std::vector<double> vd_TauPFGammaIsoDeposit;


  std::vector<double> vd_TauVx;
  std::vector<double> vd_TauVy;
  std::vector<double> vd_TauVz;
  std::vector<double> vd_TauPVDxy;
  std::vector<double> vd_TauBSDxy;
  std::vector<double> vd_TauDxy;
  std::vector<double> vd_TauDxyErr;
  std::vector<double> vd_TauD0;
  std::vector<double> vd_TauD0Err;
  std::vector<double> vd_TauDz;
  std::vector<double> vd_TauDzErr;

  std::vector<float> vf_TauIdElec;
  std::vector<float> vf_TauIdMuon;
  std::vector<float> vf_TauIdIso;
  std::vector<float> vf_TauIdNCfrHalf;
  std::vector<float> vf_TauIdNCfrQuarter;
  std::vector<float> vf_TauIdNCfrTenth;
  std::vector<float> vf_TauIdNCfrFull;

  std::vector<float> vf_TauCaloLeadTrkSignedIP      ;
  std::vector<float> vf_TauCaloLeadTrkHcal3x3EtSum  ;
  std::vector<float> vf_TauCaloLeadTrkHcal3x3HotDEta;
  std::vector<float> vf_TauCaloSignalTrkMInv        ;
  std::vector<float> vf_TauCaloTrkMInv              ;
  std::vector<float> vf_TauCaloIsoTrkPtSum          ;
  std::vector<float> vf_TauCaloIsoEcalEtSum         ;
  std::vector<float> vf_TauCaloMaxEtHCAL            ;
  
  std::vector<float> vf_TrkPFIsoChargedHadPtSum;
  std::vector<float> vf_TrkPFIsoGammaEtSum     ;
  std::vector<float> vf_TrkPFHcalClusterMaxEt  ;
  std::vector<float> vf_TrkPFEFrac_em          ;
  std::vector<float> vf_TrkPFHcalTotalOverPLead;
  std::vector<float> vf_TrkPFHcalMaxOverPLead  ;
  std::vector<float> vf_TrkPFHcal3x3OverPLead  ;
  std::vector<float> vf_TrkPFEcalStripOverPLead;
  std::vector<float> vf_TrkPFBremRecOverPLead  ;
  std::vector<float> vf_TrkPFElePreIDOut       ;
  std::vector<float> vf_TrkPFMuonCaloComp      ;
  std::vector<float> vf_TrkPFMuonSegComp       ;
  
  std::vector<float> vf_TauEtaEtaMom;
  std::vector<float> vf_TauPhiPhiMom;
  std::vector<float> vf_TauEtaPhiMom;


 public:
  void maintenanceElecs() {
    v_elecP4.clear();
    v_genelecP4.clear();
    
    vd_ElecdB.clear();
    vd_ElecdBerr.clear();

    vd_ElecTrkIso.clear();
    vd_ElecECalIso.clear();
    vd_ElecHCalIso.clear();
    vd_ElecAllIso.clear();

    vd_ElecPFAllParticleIso.clear();
    vd_ElecPFChargedHadronIso.clear();
    vd_ElecPFNeutralHadronIso.clear();
    vd_ElecPFGammaIso.clear();

    vd_ElecTrkIsoDeposit.clear();
    vd_ElecECalIsoDeposit.clear();
    vd_ElecHCalIsoDeposit.clear();

    vd_ElecPFAllParticleIsoDeposit.clear();
    vd_ElecPFChargedHadronIsoDeposit.clear();
    vd_ElecPFNeutralHadronIsoDeposit.clear();
    vd_ElecPFGammaIsoDeposit.clear();

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
    vd_ElecPVDxy.clear();
    vd_ElecBSDxy.clear();
    vd_ElecDxy.clear();
    vd_ElecDxyErr.clear();
    vd_ElecD0.clear();
    vd_ElecD0Err.clear();
    vd_ElecDz.clear();
    vd_ElecDzErr.clear();
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
  }

  void maintenanceMuons() {
    v_muonP4.clear();
    v_genmuonP4.clear();

    vd_MuondB.clear();
    vd_MuondBerr.clear();

    vd_MuonTrkIso.clear();
    vd_MuonECalIso.clear();
    vd_MuonHCalIso.clear();
    vd_MuonAllIso.clear();

    vd_MuonPFAllParticleIso.clear();
    vd_MuonPFChargedHadronIso.clear();
    vd_MuonPFNeutralHadronIso.clear();
    vd_MuonPFGammaIso.clear();

    vd_MuonTrkIsoDeposit.clear();
    vd_MuonECalIsoDeposit.clear();
    vd_MuonHCalIsoDeposit.clear();
    vd_MuonECalIsoDepositR03.clear();
    vd_MuonHCalIsoDepositR03.clear();

    vd_MuonPFAllParticleIsoDeposit.clear();
    vd_MuonPFChargedHadronIsoDeposit.clear();
    vd_MuonPFNeutralHadronIsoDeposit.clear();
    vd_MuonPFGammaIsoDeposit.clear();

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

    vd_MuonCombChi2.clear();
    vd_MuonCombNdof.clear();
  
    vd_MuonId.clear();
    vd_MuonCombVx.clear();
    vd_MuonCombVy.clear();
    vd_MuonCombVz.clear();
    vd_MuonCombPVDxy.clear();
    vd_MuonCombBSDxy.clear();
    vd_MuonCombDxy.clear();
    vd_MuonCombDxyErr.clear();
    vd_MuonCombD0.clear();
    vd_MuonCombD0Err.clear();
    vd_MuonCombDz.clear();
    vd_MuonCombDzErr.clear();
    vd_MuonCombPt.clear();
    vd_MuonCombPz.clear();
    vd_MuonCombP.clear();
    vd_MuonCombEta.clear();
    vd_MuonCombPhi.clear();
    vd_MuonCombChi.clear();
    vd_MuonCombCharge.clear();
    vd_MuonCombQOverPErr.clear();

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
    vd_MuonTrkPVDxy.clear();
    vd_MuonTrkBSDxy.clear();
    vd_MuonTrkDxy.clear();
    vd_MuonTrkDxyErr.clear();
    vd_MuonTrkD0.clear();
    vd_MuonTrkD0Err.clear();
    vd_MuonTrkDz.clear();
    vd_MuonTrkDzErr.clear();
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

    vd_MuonPickyTrkValidHits.clear();
    vd_MuonPickyTrkLostHits.clear();
    vd_MuonPickyTrkPVDxy.clear();
    vd_MuonPickyTrkBSDxy.clear();
    vd_MuonPickyTrkDxy.clear();
    vd_MuonPickyTrkDxyErr.clear();
    vd_MuonPickyTrkD0.clear();
    vd_MuonPickyTrkD0Err.clear();
    vd_MuonPickyTrkDz.clear();
    vd_MuonPickyTrkDzErr.clear();
    vd_MuonPickyTrkPt.clear();
    vd_MuonPickyTrkPz.clear();
    vd_MuonPickyTrkP.clear();
    vd_MuonPickyTrkEta.clear();
    vd_MuonPickyTrkPhi.clear();
    vd_MuonPickyTrkChi.clear();
    vd_MuonPickyTrkCharge.clear();
    vd_MuonPickyTrkQOverPErr.clear();
    vd_MuonPickyTrkOuterZ.clear();
    vd_MuonPickyTrkOuterR.clear();

    vd_MuonTPFMSTrkValidHits.clear();
    vd_MuonTPFMSTrkLostHits.clear();
    vd_MuonTPFMSTrkPVDxy.clear();
    vd_MuonTPFMSTrkBSDxy.clear();
    vd_MuonTPFMSTrkDxy.clear();
    vd_MuonTPFMSTrkDxyErr.clear();
    vd_MuonTPFMSTrkD0.clear();
    vd_MuonTPFMSTrkD0Err.clear();
    vd_MuonTPFMSTrkDz.clear();
    vd_MuonTPFMSTrkDzErr.clear();
    vd_MuonTPFMSTrkPt.clear();
    vd_MuonTPFMSTrkPz.clear();
    vd_MuonTPFMSTrkP.clear();
    vd_MuonTPFMSTrkEta.clear();
    vd_MuonTPFMSTrkPhi.clear();
    vd_MuonTPFMSTrkChi.clear();
    vd_MuonTPFMSTrkCharge.clear();
    vd_MuonTPFMSTrkQOverPErr.clear();
    vd_MuonTPFMSTrkOuterZ.clear();
    vd_MuonTPFMSTrkOuterR.clear();

    vi_MuonGenPdgId.clear();
    vi_MuonGenStatus.clear();
    vi_MuonGenMother.clear();
    vi_MuonGenMotherStatus.clear();
  }

  void maintenanceTaus() {
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

    vd_TauTrkIsoDeposit.clear();
    vd_TauECalIsoDeposit.clear();
    vd_TauHCalIsoDeposit.clear();

    vd_TauPFAllParticleIsoDeposit.clear();
    vd_TauPFChargedHadronIsoDeposit.clear();
    vd_TauPFNeutralHadronIsoDeposit.clear();
    vd_TauPFGammaIsoDeposit.clear();

    vd_TauVx.clear();
    vd_TauVy.clear();
    vd_TauVz.clear();
    vd_TauPVDxy.clear();
    vd_TauBSDxy.clear();
    vd_TauDxy.clear();
    vd_TauDxyErr.clear();
    vd_TauD0.clear();
    vd_TauD0Err.clear();
    vd_TauDz.clear();
    vd_TauDzErr.clear();


    vf_TauIdElec.clear();
    vf_TauIdMuon.clear();
    vf_TauIdIso.clear();
    vf_TauIdNCfrHalf.clear();
    vf_TauIdNCfrQuarter.clear();
    vf_TauIdNCfrTenth.clear();
    vf_TauIdNCfrFull.clear();


    vf_TauCaloLeadTrkSignedIP      .clear();
    vf_TauCaloLeadTrkHcal3x3EtSum  .clear();
    vf_TauCaloLeadTrkHcal3x3HotDEta.clear();
    vf_TauCaloSignalTrkMInv        .clear();
    vf_TauCaloTrkMInv              .clear();
    vf_TauCaloIsoTrkPtSum          .clear();
    vf_TauCaloIsoEcalEtSum         .clear();
    vf_TauCaloMaxEtHCAL            .clear();
    
    vf_TrkPFIsoChargedHadPtSum.clear();
    vf_TrkPFIsoGammaEtSum     .clear();
    vf_TrkPFHcalClusterMaxEt  .clear();
    vf_TrkPFEFrac_em          .clear();
    vf_TrkPFHcalTotalOverPLead.clear();
    vf_TrkPFHcalMaxOverPLead  .clear();
    vf_TrkPFHcal3x3OverPLead  .clear();
    vf_TrkPFEcalStripOverPLead.clear();
    vf_TrkPFBremRecOverPLead  .clear();
    vf_TrkPFElePreIDOut       .clear();
    vf_TrkPFMuonCaloComp      .clear();
    vf_TrkPFMuonSegComp       .clear();
    
    vf_TauEtaEtaMom.clear();
    vf_TauPhiPhiMom.clear();
    vf_TauEtaPhiMom.clear();
  }
};

#endif

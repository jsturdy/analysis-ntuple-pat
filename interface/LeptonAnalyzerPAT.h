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
  void bookTTree(TTree*);
  

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

  // Plots
  //TTree * mLeptonData;   /// Will contain the lepton data after cuts

  // Variables
  int    i_ElecN;
  int    i_ElecNIso;
  bool   bool_ElecVeto;
  bool   bool_spike;

  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_elecP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_genelecP4;
  
  std::auto_ptr<std::vector<double> >  vd_ElecdB;
  std::auto_ptr<std::vector<double> >  vd_ElecdBerr;

  std::auto_ptr<std::vector<double> >  vd_ElecTrkIso;
  std::auto_ptr<std::vector<double> >  vd_ElecECalIso;
  std::auto_ptr<std::vector<double> >  vd_ElecHCalIso;
  std::auto_ptr<std::vector<double> >  vd_ElecAllIso;

  std::auto_ptr<std::vector<double> >  vd_ElecPFAllParticleIso;
  std::auto_ptr<std::vector<double> >  vd_ElecPFChargedHadronIso;
  std::auto_ptr<std::vector<double> >  vd_ElecPFNeutralHadronIso;
  std::auto_ptr<std::vector<double> >  vd_ElecPFGammaIso;

  std::auto_ptr<std::vector<double> >  vd_ElecTrkIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_ElecECalIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_ElecHCalIsoDeposit;

  std::auto_ptr<std::vector<double> >  vd_ElecPFAllParticleIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_ElecPFChargedHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_ElecPFNeutralHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_ElecPFGammaIsoDeposit;

  std::auto_ptr<std::vector<double> >  vd_ElecTrkChiNorm;
  std::auto_ptr<std::vector<double> >  vd_ElecCharge;

  std::auto_ptr<std::vector<double> >  vd_ElecIdLoose;
  std::auto_ptr<std::vector<double> >  vd_ElecIdTight;
  std::auto_ptr<std::vector<double> >  vd_ElecIdRobLoose;
  std::auto_ptr<std::vector<double> >  vd_ElecIdRobTight;
  std::auto_ptr<std::vector<double> >  vd_ElecIdRobHighE;

  std::auto_ptr<std::vector<double> >  vd_ElecChargeMode;
  std::auto_ptr<std::vector<double> >  vd_ElecPtTrkMode;
  std::auto_ptr<std::vector<double> >  vd_ElecQOverPErrTrkMode;

  std::auto_ptr<std::vector<double> >  vd_ElecE2OverE9;
  std::auto_ptr<std::vector<double> >  vd_ElecSwissCross;
  std::auto_ptr<std::vector<double> >  vd_ElecE1x5;
  std::auto_ptr<std::vector<double> >  vd_ElecE5x5;
  std::auto_ptr<std::vector<double> >  vd_ElecE2x5Max;
  std::auto_ptr<std::vector<double> >  vd_ElecFbrem;
  std::auto_ptr<std::vector<double> >  vd_ElecSigmaEtaEta;
  std::auto_ptr<std::vector<double> >  vd_ElecSigmaIetaIeta;
  std::auto_ptr<std::vector<double> >  vd_ElecHadOverEM;
  std::auto_ptr<std::vector<double> >  vd_ElecTSeed;
  std::auto_ptr<std::vector<double> >  vd_ElecESeed;

  std::auto_ptr<std::vector<int> >     vi_ElecGenPdgId;
  std::auto_ptr<std::vector<int> >     vi_ElecGenStatus;
  std::auto_ptr<std::vector<int> >     vi_ElecGenMother;
  std::auto_ptr<std::vector<int> >     vi_ElecGenMotherStatus;

  std::auto_ptr<std::vector<double> >  vd_ElecCaloEnergy;
  std::auto_ptr<std::vector<double> >  vd_ElecVx;
  std::auto_ptr<std::vector<double> >  vd_ElecVy;
  std::auto_ptr<std::vector<double> >  vd_ElecVz;
  std::auto_ptr<std::vector<double> >  vd_ElecPVDxy;
  std::auto_ptr<std::vector<double> >  vd_ElecBSDxy;
  std::auto_ptr<std::vector<double> >  vd_ElecDxy;
  std::auto_ptr<std::vector<double> >  vd_ElecDxyErr;
  std::auto_ptr<std::vector<double> >  vd_ElecD0;
  std::auto_ptr<std::vector<double> >  vd_ElecD0Err;
  std::auto_ptr<std::vector<double> >  vd_ElecDz;
  std::auto_ptr<std::vector<double> >  vd_ElecDzErr;
  std::auto_ptr<std::vector<double> >  vd_ElecPtTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecQOverPErrTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecLostHits;
  std::auto_ptr<std::vector<double> >  vd_ElecValidHits;
  //std::auto_ptr<std::vector<double> >  vd_ElecNCluster;
  std::auto_ptr<std::vector<double> >  vd_ElecEtaTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecPhiTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecWidthClusterEta;
  std::auto_ptr<std::vector<double> >  vd_ElecWidthClusterPhi;
  std::auto_ptr<std::vector<double> >  vd_ElecSCEta ;
  std::auto_ptr<std::vector<double> >  vd_ElecSCPhi ;
  std::auto_ptr<std::vector<double> >  vd_ElecSCEn  ;
  std::auto_ptr<std::vector<double> >  vd_ElecSCPt  ;
  std::auto_ptr<std::vector<double> >  vd_ElecSCRawE;

  std::auto_ptr<std::vector<double> >  vd_ElecPinTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecPoutTrk;
  std::auto_ptr<std::vector<double> >  vd_ElecNormChi2;

  int    i_MuonN;
  bool   bool_MuonVeto;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_muonP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_genmuonP4;

  std::auto_ptr<std::vector<double> >  vd_MuondB;
  std::auto_ptr<std::vector<double> >  vd_MuondBerr;

  std::auto_ptr<std::vector<double> >  vd_MuonCharge;

  std::auto_ptr<std::vector<double> >  vd_MuonTrkIso;
  std::auto_ptr<std::vector<double> >  vd_MuonECalIso;
  std::auto_ptr<std::vector<double> >  vd_MuonHCalIso;
  std::auto_ptr<std::vector<double> >  vd_MuonAllIso;

  std::auto_ptr<std::vector<double> >  vd_MuonPFAllParticleIso;
  std::auto_ptr<std::vector<double> >  vd_MuonPFChargedHadronIso;
  std::auto_ptr<std::vector<double> >  vd_MuonPFNeutralHadronIso;
  std::auto_ptr<std::vector<double> >  vd_MuonPFGammaIso;

  std::auto_ptr<std::vector<double> >  vd_MuonTrkIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonECalIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonHCalIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonECalIsoDepositR03;
  std::auto_ptr<std::vector<double> >  vd_MuonHCalIsoDepositR03;

  std::auto_ptr<std::vector<double> >  vd_MuonPFAllParticleIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonPFChargedHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonPFNeutralHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_MuonPFGammaIsoDeposit;

  //Muon ID results
  std::auto_ptr<std::vector<int> >  vb_MuonIsGlobal;
  std::auto_ptr<std::vector<int> >  vb_MuonIsStandAlone;
  std::auto_ptr<std::vector<int> >  vb_MuonIsTracker;

  std::auto_ptr<std::vector<int> >  vb_MuonGlobalMuonPromptTight;

  std::auto_ptr<std::vector<int> >  vb_MuonAllArbitrated;
  std::auto_ptr<std::vector<int> >  vb_MuonTrackerMuonArbitrated;
  std::auto_ptr<std::vector<int> >  vb_MuonGMTkKinkTight;
  std::auto_ptr<std::vector<int> >  vb_MuonGMTkChiCompatibility;
  std::auto_ptr<std::vector<int> >  vb_MuonGMStaChiCompatibility;
  std::auto_ptr<std::vector<int> >  vb_MuonTM2DCompatibilityLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTM2DCompatibilityTight;
  std::auto_ptr<std::vector<int> >  vb_MuonTMOneStationLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTMOneStationTight;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationTight;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationAngLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationAngTight;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationOptimizedLowPtLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationOptimizedLowPtTight;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationOptimizedBarrelLowPtLoose;
  std::auto_ptr<std::vector<int> >  vb_MuonTMLastStationOptimizedBarrelLowPtTight;

  //Variables for combined muons
  std::auto_ptr<std::vector<double> >  vd_MuonCombVx;
  std::auto_ptr<std::vector<double> >  vd_MuonCombVy;
  std::auto_ptr<std::vector<double> >  vd_MuonCombVz;
  std::auto_ptr<std::vector<double> >  vd_MuonCombPVDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonCombBSDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonCombDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonCombDxyErr;
  std::auto_ptr<std::vector<double> >  vd_MuonCombD0;
  std::auto_ptr<std::vector<double> >  vd_MuonCombD0Err;
  std::auto_ptr<std::vector<double> >  vd_MuonCombDz;
  std::auto_ptr<std::vector<double> >  vd_MuonCombDzErr;
  std::auto_ptr<std::vector<double> >  vd_MuonCombChi2;
  std::auto_ptr<std::vector<double> >  vd_MuonCombNdof;
  std::auto_ptr<std::vector<double> >  vd_MuonCombPt;
  std::auto_ptr<std::vector<double> >  vd_MuonCombPz;
  std::auto_ptr<std::vector<double> >  vd_MuonCombP;
  std::auto_ptr<std::vector<double> >  vd_MuonCombEta;
  std::auto_ptr<std::vector<double> >  vd_MuonCombPhi;
  std::auto_ptr<std::vector<double> >  vd_MuonCombChi;
  std::auto_ptr<std::vector<double> >  vd_MuonCombCharge;
  std::auto_ptr<std::vector<double> >  vd_MuonCombQOverPErr;
  std::auto_ptr<std::vector<double> >  vd_MuonCombValidHits;

  //Variables for Stand alone muons
  std::auto_ptr<std::vector<double> >  vd_MuonStandValidHits;
  std::auto_ptr<std::vector<double> >  vd_MuonStandLostHits;
  std::auto_ptr<std::vector<double> >  vd_MuonStandPt;
  std::auto_ptr<std::vector<double> >  vd_MuonStandPz;
  std::auto_ptr<std::vector<double> >  vd_MuonStandP;
  std::auto_ptr<std::vector<double> >  vd_MuonStandEta;
  std::auto_ptr<std::vector<double> >  vd_MuonStandPhi;
  std::auto_ptr<std::vector<double> >  vd_MuonStandChi;
  std::auto_ptr<std::vector<double> >  vd_MuonStandCharge;
  std::auto_ptr<std::vector<double> >  vd_MuonStandQOverPErr;
  /*
  std::auto_ptr<std::vector<double> >  vd_MuonTrkChiNorm;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkValidHits;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkLostHits;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkPVDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkBSDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkDxyErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkD0;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkD0Err;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkDz;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkDzErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkPt;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkPz;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkP;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkEta;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkPhi;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkChi;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkCharge;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkQOverPErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkOuterZ;
  std::auto_ptr<std::vector<double> >  vd_MuonTrkOuterR;
  */
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkChiNorm;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkValidHits;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkLostHits;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkPVDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkBSDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkDxyErr;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkD0;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkD0Err;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkDz;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkDzErr;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkPt;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkPz;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkP;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkEta;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkPhi;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkChi;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkCharge;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkQOverPErr;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkOuterZ;
  std::auto_ptr<std::vector<double> >  vd_MuonPickyTrkOuterR;

  /*
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkChiNorm;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkValidHits;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkLostHits;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkPVDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkBSDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkDxy;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkDxyErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkD0;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkD0Err;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkDz;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkDzErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkPt;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkPz;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkP;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkEta;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkPhi;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkChi;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkCharge;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkQOverPErr;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkOuterZ;
  std::auto_ptr<std::vector<double> >  vd_MuonTPFMSTrkOuterR;
  */

  std::auto_ptr<std::vector<int> >     vi_MuonGenPdgId;
  std::auto_ptr<std::vector<int> >     vi_MuonGenStatus;
  std::auto_ptr<std::vector<int> >     vi_MuonGenMother;
  std::auto_ptr<std::vector<int> >     vi_MuonGenMotherStatus;


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

  std::auto_ptr<std::map<std::string,TauIDType> >  tauidMap;

  int    i_TauN;
  int    i_TauNIso;
  bool   bool_TauVeto;

  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_tauP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_gentauP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> > v_gentaujetP4;
  std::auto_ptr<std::vector<double> >  vd_TauCharge;

  std::auto_ptr<std::vector<int> >  vi_TauGenPdgId;
  std::auto_ptr<std::vector<int> >  vi_TauGenStatus;
  std::auto_ptr<std::vector<int> >  vi_TauGenMother;
  std::auto_ptr<std::vector<int> >  vi_TauGenMotherStatus;
  std::auto_ptr<std::vector<int> >  vi_TauGen;

  std::auto_ptr<std::vector<int> >     vi_TauSigTrk;
  std::auto_ptr<std::vector<double> >  vd_TauTrkIso;
  std::auto_ptr<std::vector<double> >  vd_TauECalIso;
  std::auto_ptr<std::vector<double> >  vd_TauHCalIso;
  std::auto_ptr<std::vector<double> >  vd_TauAllIso;

  std::auto_ptr<std::vector<double> >  vd_TauPFAllParticleIso;
  std::auto_ptr<std::vector<double> >  vd_TauPFChargedHadronIso;
  std::auto_ptr<std::vector<double> >  vd_TauPFNeutralHadronIso;
  std::auto_ptr<std::vector<double> >  vd_TauPFGammaIso;

  std::auto_ptr<std::vector<double> >  vd_TauTrkIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_TauECalIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_TauHCalIsoDeposit;

  std::auto_ptr<std::vector<double> >  vd_TauPFAllParticleIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_TauPFChargedHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_TauPFNeutralHadronIsoDeposit;
  std::auto_ptr<std::vector<double> >  vd_TauPFGammaIsoDeposit;

  std::auto_ptr<std::vector<double> >  vd_TauVx;
  std::auto_ptr<std::vector<double> >  vd_TauVy;
  std::auto_ptr<std::vector<double> >  vd_TauVz;
  std::auto_ptr<std::vector<double> >  vd_TauPVDxy;
  std::auto_ptr<std::vector<double> >  vd_TauBSDxy;
  std::auto_ptr<std::vector<double> >  vd_TauDxy;
  std::auto_ptr<std::vector<double> >  vd_TauDxyErr;
  std::auto_ptr<std::vector<double> >  vd_TauD0;
  std::auto_ptr<std::vector<double> >  vd_TauD0Err;
  std::auto_ptr<std::vector<double> >  vd_TauDz;
  std::auto_ptr<std::vector<double> >  vd_TauDzErr;

  std::auto_ptr<std::vector<double> >  vd_TauIdElec;
  std::auto_ptr<std::vector<double> >  vd_TauIdMuon;
  std::auto_ptr<std::vector<double> >  vd_TauIdIso          ;
  std::auto_ptr<std::vector<double> >  vd_TauIdIsoLeadPi    ;
  std::auto_ptr<std::vector<double> >  vd_TauIdEcalIso      ;
  std::auto_ptr<std::vector<double> >  vd_TauIdEcalIsoLeadPi;
  std::auto_ptr<std::vector<double> >  vd_TauIdLeadPiPt     ;
  std::auto_ptr<std::vector<double> >  vd_TauIdLeadTrk      ;
  std::auto_ptr<std::vector<double> >  vd_TauIdLeadTrkPt    ;
  std::auto_ptr<std::vector<double> >  vd_TauIdTrkIso       ;
  std::auto_ptr<std::vector<double> >  vd_TauIdTrkIsoLeadPi ;
  std::auto_ptr<std::vector<double> >  vd_TauIdNCfrHalf;
  std::auto_ptr<std::vector<double> >  vd_TauIdNCfrQuarter;
  std::auto_ptr<std::vector<double> >  vd_TauIdNCfrTenth;
  std::auto_ptr<std::vector<double> >  vd_TauIdNCfrFull;

  std::auto_ptr<std::vector<double> >  vd_TauCaloLeadTrkSignedIP      ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloLeadTrkHcal3x3EtSum  ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloLeadTrkHcal3x3HotDEta;
  std::auto_ptr<std::vector<double> >  vd_TauCaloSignalTrkMInv        ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloTrkMInv              ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloIsoTrkPtSum          ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloIsoEcalEtSum         ;
  std::auto_ptr<std::vector<double> >  vd_TauCaloMaxEtHCAL            ;
  
  std::auto_ptr<std::vector<double> >  vd_TrkPFIsoChargedHadPtSum;
  std::auto_ptr<std::vector<double> >  vd_TrkPFIsoGammaEtSum     ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFHcalClusterMaxEt  ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFEFrac_em          ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFHcalTotalOverPLead;
  std::auto_ptr<std::vector<double> >  vd_TrkPFHcalMaxOverPLead  ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFHcal3x3OverPLead  ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFEcalStripOverPLead;
  std::auto_ptr<std::vector<double> >  vd_TrkPFBremRecOverPLead  ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFElePreIDOut       ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFMuonCaloComp      ;
  std::auto_ptr<std::vector<double> >  vd_TrkPFMuonSegComp       ;
  
  std::auto_ptr<std::vector<double> >  vd_TauEtaEtaMom;
  std::auto_ptr<std::vector<double> >  vd_TauPhiPhiMom;
  std::auto_ptr<std::vector<double> >  vd_TauEtaPhiMom;


 public:
  void maintenanceElecs() {
    v_elecP4->clear();
    v_genelecP4->clear();
    
    vd_ElecdB->clear();
    vd_ElecdBerr->clear();

    vd_ElecTrkIso->clear();
    vd_ElecECalIso->clear();
    vd_ElecHCalIso->clear();
    vd_ElecAllIso->clear();

    vd_ElecPFAllParticleIso->clear();
    vd_ElecPFChargedHadronIso->clear();
    vd_ElecPFNeutralHadronIso->clear();
    vd_ElecPFGammaIso->clear();

    vd_ElecTrkIsoDeposit->clear();
    vd_ElecECalIsoDeposit->clear();
    vd_ElecHCalIsoDeposit->clear();

    vd_ElecPFAllParticleIsoDeposit->clear();
    vd_ElecPFChargedHadronIsoDeposit->clear();
    vd_ElecPFNeutralHadronIsoDeposit->clear();
    vd_ElecPFGammaIsoDeposit->clear();

    vd_ElecTrkChiNorm->clear();
    vd_ElecCharge->clear();
    
    vd_ElecIdLoose->clear();
    vd_ElecIdTight->clear();
    vd_ElecIdRobLoose->clear();
    vd_ElecIdRobTight->clear();
    vd_ElecIdRobHighE->clear();

    vd_ElecChargeMode->clear();
    vd_ElecPtTrkMode->clear();
    vd_ElecQOverPErrTrkMode->clear();
    
    vd_ElecE2OverE9->clear();
    vd_ElecSwissCross->clear();
    vd_ElecE1x5->clear();
    vd_ElecE5x5->clear();
    vd_ElecE2x5Max->clear();
    vd_ElecFbrem->clear();
    vd_ElecSigmaEtaEta->clear();
    vd_ElecSigmaIetaIeta->clear();
    vd_ElecHadOverEM->clear();
    vd_ElecTSeed->clear();
    vd_ElecESeed->clear();

    vi_ElecGenPdgId->clear();
    vi_ElecGenStatus->clear();
    vi_ElecGenMother->clear();
    vi_ElecGenMotherStatus->clear();
    
    vd_ElecCaloEnergy->clear();
    vd_ElecVx->clear();
    vd_ElecVy->clear();
    vd_ElecVz->clear();
    vd_ElecPVDxy->clear();
    vd_ElecBSDxy->clear();
    vd_ElecDxy->clear();
    vd_ElecDxyErr->clear();
    vd_ElecD0->clear();
    vd_ElecD0Err->clear();
    vd_ElecDz->clear();
    vd_ElecDzErr->clear();
    vd_ElecPtTrk->clear();
    vd_ElecQOverPErrTrk->clear();
    vd_ElecLostHits->clear();
    vd_ElecValidHits->clear();
    //vd_ElecNCluster->clear();
    vd_ElecEtaTrk->clear();
    vd_ElecPhiTrk->clear();
    vd_ElecWidthClusterEta->clear();
    vd_ElecWidthClusterPhi->clear();
    vd_ElecSCEta ->clear();
    vd_ElecSCPhi ->clear();
    vd_ElecSCEn  ->clear();
    vd_ElecSCPt  ->clear();
    vd_ElecSCRawE->clear();

    vd_ElecPinTrk->clear();
    vd_ElecPoutTrk->clear();
    vd_ElecNormChi2->clear();
  }

  void maintenanceMuons() {
    v_muonP4->clear();
    v_genmuonP4->clear();

    vd_MuondB->clear();
    vd_MuondBerr->clear();

    vd_MuonCharge->clear();

    vd_MuonTrkIso->clear();
    vd_MuonECalIso->clear();
    vd_MuonHCalIso->clear();
    vd_MuonAllIso->clear();

    vd_MuonPFAllParticleIso->clear();
    vd_MuonPFChargedHadronIso->clear();
    vd_MuonPFNeutralHadronIso->clear();
    vd_MuonPFGammaIso->clear();

    vd_MuonTrkIsoDeposit->clear();
    vd_MuonECalIsoDeposit->clear();
    vd_MuonHCalIsoDeposit->clear();
    vd_MuonECalIsoDepositR03->clear();
    vd_MuonHCalIsoDepositR03->clear();

    vd_MuonPFAllParticleIsoDeposit->clear();
    vd_MuonPFChargedHadronIsoDeposit->clear();
    vd_MuonPFNeutralHadronIsoDeposit->clear();
    vd_MuonPFGammaIsoDeposit->clear();


    vb_MuonIsGlobal->clear();
    vb_MuonIsStandAlone->clear();
    vb_MuonIsTracker->clear();

    vb_MuonGlobalMuonPromptTight->clear();

    vb_MuonAllArbitrated->clear();
    vb_MuonTrackerMuonArbitrated->clear();
    vb_MuonGMTkKinkTight->clear();
    vb_MuonGMTkChiCompatibility->clear();
    vb_MuonGMStaChiCompatibility->clear();
    vb_MuonTM2DCompatibilityLoose->clear();
    vb_MuonTM2DCompatibilityTight->clear();
    vb_MuonTMOneStationLoose->clear();
    vb_MuonTMOneStationTight->clear();
    vb_MuonTMLastStationLoose->clear();
    vb_MuonTMLastStationTight->clear();
    vb_MuonTMLastStationAngLoose->clear();
    vb_MuonTMLastStationAngTight->clear();
    vb_MuonTMLastStationOptimizedLowPtLoose->clear();
    vb_MuonTMLastStationOptimizedLowPtTight->clear();
    vb_MuonTMLastStationOptimizedBarrelLowPtLoose->clear();
    vb_MuonTMLastStationOptimizedBarrelLowPtTight->clear();


    vd_MuonCombVx->clear();
    vd_MuonCombVy->clear();
    vd_MuonCombVz->clear();
    vd_MuonCombPVDxy->clear();
    vd_MuonCombBSDxy->clear();
    vd_MuonCombDxy->clear();
    vd_MuonCombDxyErr->clear();
    vd_MuonCombD0->clear();
    vd_MuonCombD0Err->clear();
    vd_MuonCombDz->clear();
    vd_MuonCombDzErr->clear();
    vd_MuonCombChi2->clear();
    vd_MuonCombNdof->clear();
    vd_MuonCombPt->clear();
    vd_MuonCombPz->clear();
    vd_MuonCombP->clear();
    vd_MuonCombEta->clear();
    vd_MuonCombPhi->clear();
    vd_MuonCombChi->clear();
    vd_MuonCombCharge->clear();
    vd_MuonCombQOverPErr->clear();
    vd_MuonCombValidHits->clear();


    vd_MuonStandValidHits->clear();
    vd_MuonStandLostHits->clear();
    vd_MuonStandPt->clear();
    vd_MuonStandPz->clear();
    vd_MuonStandP->clear();
    vd_MuonStandEta->clear();
    vd_MuonStandPhi->clear();
    vd_MuonStandChi->clear();
    vd_MuonStandCharge->clear();
    vd_MuonStandQOverPErr->clear();
    /*
    vd_MuonTrkChiNorm->clear();
    vd_MuonTrkValidHits->clear();
    vd_MuonTrkLostHits->clear();
    vd_MuonTrkPVDxy->clear();
    vd_MuonTrkBSDxy->clear();
    vd_MuonTrkDxy->clear();
    vd_MuonTrkDxyErr->clear();
    vd_MuonTrkD0->clear();
    vd_MuonTrkD0Err->clear();
    vd_MuonTrkDz->clear();
    vd_MuonTrkDzErr->clear();
    vd_MuonTrkPt->clear();
    vd_MuonTrkPz->clear();
    vd_MuonTrkP->clear();
    vd_MuonTrkEta->clear();
    vd_MuonTrkPhi->clear();
    vd_MuonTrkChi->clear();
    vd_MuonTrkCharge->clear();
    vd_MuonTrkQOverPErr->clear();
    vd_MuonTrkOuterZ->clear();
    vd_MuonTrkOuterR->clear();
    */
    vd_MuonPickyTrkChiNorm->clear();
    vd_MuonPickyTrkValidHits->clear();
    vd_MuonPickyTrkLostHits->clear();
    vd_MuonPickyTrkPVDxy->clear();
    vd_MuonPickyTrkBSDxy->clear();
    vd_MuonPickyTrkDxy->clear();
    vd_MuonPickyTrkDxyErr->clear();
    vd_MuonPickyTrkD0->clear();
    vd_MuonPickyTrkD0Err->clear();
    vd_MuonPickyTrkDz->clear();
    vd_MuonPickyTrkDzErr->clear();
    vd_MuonPickyTrkPt->clear();
    vd_MuonPickyTrkPz->clear();
    vd_MuonPickyTrkP->clear();
    vd_MuonPickyTrkEta->clear();
    vd_MuonPickyTrkPhi->clear();
    vd_MuonPickyTrkChi->clear();
    vd_MuonPickyTrkCharge->clear();
    vd_MuonPickyTrkQOverPErr->clear();
    vd_MuonPickyTrkOuterZ->clear();
    vd_MuonPickyTrkOuterR->clear();

    /*
    vd_MuonTPFMSTrkChiNorm->clear();
    vd_MuonTPFMSTrkValidHits->clear();
    vd_MuonTPFMSTrkLostHits->clear();
    vd_MuonTPFMSTrkPVDxy->clear();
    vd_MuonTPFMSTrkBSDxy->clear();
    vd_MuonTPFMSTrkDxy->clear();
    vd_MuonTPFMSTrkDxyErr->clear();
    vd_MuonTPFMSTrkD0->clear();
    vd_MuonTPFMSTrkD0Err->clear();
    vd_MuonTPFMSTrkDz->clear();
    vd_MuonTPFMSTrkDzErr->clear();
    vd_MuonTPFMSTrkPt->clear();
    vd_MuonTPFMSTrkPz->clear();
    vd_MuonTPFMSTrkP->clear();
    vd_MuonTPFMSTrkEta->clear();
    vd_MuonTPFMSTrkPhi->clear();
    vd_MuonTPFMSTrkChi->clear();
    vd_MuonTPFMSTrkCharge->clear();
    vd_MuonTPFMSTrkQOverPErr->clear();
    vd_MuonTPFMSTrkOuterZ->clear();
    vd_MuonTPFMSTrkOuterR->clear();
    */

    vi_MuonGenPdgId->clear();
    vi_MuonGenStatus->clear();
    vi_MuonGenMother->clear();
    vi_MuonGenMotherStatus->clear();
  }

  void maintenanceTaus() {
    tauidMap->clear();
  
    v_tauP4->clear();
    v_gentauP4->clear();
    v_gentaujetP4->clear();
    vd_TauCharge->clear();

    vi_TauGenPdgId->clear();
    vi_TauGenStatus->clear();
    vi_TauGenMother->clear();
    vi_TauGenMotherStatus->clear();
    vi_TauGen->clear();
    
    vi_TauSigTrk->clear();
    vd_TauTrkIso->clear();
    vd_TauECalIso->clear();
    vd_TauHCalIso->clear();
    vd_TauAllIso->clear();

    vd_TauPFAllParticleIso->clear();
    vd_TauPFChargedHadronIso->clear();
    vd_TauPFNeutralHadronIso->clear();
    vd_TauPFGammaIso->clear();

    vd_TauTrkIsoDeposit->clear();
    vd_TauECalIsoDeposit->clear();
    vd_TauHCalIsoDeposit->clear();

    vd_TauPFAllParticleIsoDeposit->clear();
    vd_TauPFChargedHadronIsoDeposit->clear();
    vd_TauPFNeutralHadronIsoDeposit->clear();
    vd_TauPFGammaIsoDeposit->clear();

    vd_TauVx->clear();
    vd_TauVy->clear();
    vd_TauVz->clear();
    vd_TauPVDxy->clear();
    vd_TauBSDxy->clear();
    vd_TauDxy->clear();
    vd_TauDxyErr->clear();
    vd_TauD0->clear();
    vd_TauD0Err->clear();
    vd_TauDz->clear();
    vd_TauDzErr->clear();

    vd_TauIdElec->clear();
    vd_TauIdMuon->clear();
    vd_TauIdIso->clear();
    vd_TauIdIsoLeadPi    ->clear();
    vd_TauIdEcalIso      ->clear();
    vd_TauIdEcalIsoLeadPi->clear();
    vd_TauIdLeadPiPt     ->clear();
    vd_TauIdLeadTrk      ->clear();
    vd_TauIdLeadTrkPt    ->clear();
    vd_TauIdTrkIso       ->clear();
    vd_TauIdTrkIsoLeadPi ->clear();
    vd_TauIdNCfrHalf->clear();
    vd_TauIdNCfrQuarter->clear();
    vd_TauIdNCfrTenth->clear();
    vd_TauIdNCfrFull->clear();

    vd_TauCaloLeadTrkSignedIP      ->clear();
    vd_TauCaloLeadTrkHcal3x3EtSum  ->clear();
    vd_TauCaloLeadTrkHcal3x3HotDEta->clear();
    vd_TauCaloSignalTrkMInv        ->clear();
    vd_TauCaloTrkMInv              ->clear();
    vd_TauCaloIsoTrkPtSum          ->clear();
    vd_TauCaloIsoEcalEtSum         ->clear();
    vd_TauCaloMaxEtHCAL            ->clear();
    
    vd_TrkPFIsoChargedHadPtSum->clear();
    vd_TrkPFIsoGammaEtSum     ->clear();
    vd_TrkPFHcalClusterMaxEt  ->clear();
    vd_TrkPFEFrac_em          ->clear();
    vd_TrkPFHcalTotalOverPLead->clear();
    vd_TrkPFHcalMaxOverPLead  ->clear();
    vd_TrkPFHcal3x3OverPLead  ->clear();
    vd_TrkPFEcalStripOverPLead->clear();
    vd_TrkPFBremRecOverPLead  ->clear();
    vd_TrkPFElePreIDOut       ->clear();
    vd_TrkPFMuonCaloComp      ->clear();
    vd_TrkPFMuonSegComp       ->clear();
    
    vd_TauEtaEtaMom->clear();
    vd_TauPhiPhiMom->clear();
    vd_TauEtaPhiMom->clear();
  }
};

#endif

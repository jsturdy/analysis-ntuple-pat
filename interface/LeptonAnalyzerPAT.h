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
  //edm::InputTag tauTag_;
  edm::InputTag genTag_;

  double elecMaxEta_, elecMaxEt_, elecMinEt_, elecRelIso_;  /// for preselection cuts on electrons
  double muonMaxEta_, muonMaxEt_, muonMinEt_, muonRelIso_;  /// for preselection cuts on muons
  //double tauMaxEta_, tauMaxEt_, tauMinEt_, tauRelIso_;      /// for preselection cuts on taus

  bool   doMCData_;                 /// switch to turn off generator level information
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
  std::vector<double> vd_ElecTrkIso;
  std::vector<double> vd_ElecECalIso;
  std::vector<double> vd_ElecHCalIso;
  std::vector<double> vd_ElecAllIso;
  std::vector<double> vd_ElecTrkChiNorm;
  std::vector<double> vd_ElecCharge;

  std::vector<double> vd_ElecIdLoose;
  std::vector<double> vd_ElecIdTight;
  std::vector<double> vd_ElecIdRobLoose;
  std::vector<double> vd_ElecIdRobTight;
  std::vector<double> vd_ElecIdRobHighE;
  std::vector<double> vd_ElecChargeMode;
  std::vector<double> vd_ElecPtTrkMode;
  std::vector<double> vd_ElecQOverPErrTrkMode;

  std::vector<double> vd_ElecGenPdgId;
  std::vector<double> vd_ElecGenMother;

  std::vector<double> vd_ElecCaloEnergy;
  std::vector<double> vd_ElecHOverE;
  std::vector<double> vd_ElecVx;
  std::vector<double> vd_ElecVy;
  std::vector<double> vd_ElecVz;
  std::vector<double> vd_ElecD0;
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
  std::vector<double> vd_MuonTrkChiNorm;
  std::vector<double> vd_MuonCharge;

  std::vector<double> vd_MuonIsGlobal;
  std::vector<double> vd_MuonIsStandAlone;
  std::vector<double> vd_MuonIsTracker;

  std::vector<double> vd_MuonGlobalMuonPromptTight;

  std::vector<double> vd_MuonAllArbitrated;
  std::vector<double> vd_MuonTrackerMuonArbitrated;
  std::vector<double> vd_MuonGMTkKinkTight;
  std::vector<double> vd_MuonGMTkChiCompatibility;
  std::vector<double> vd_MuonGMStaChiCompatibility;
  std::vector<double> vd_MuonTM2DCompatibilityLoose;
  std::vector<double> vd_MuonTM2DCompatibilityTight;
  std::vector<double> vd_MuonTMOneStationLoose;
  std::vector<double> vd_MuonTMOneStationTight;
  std::vector<double> vd_MuonTMLastStationLoose;
  std::vector<double> vd_MuonTMLastStationTight;
  std::vector<double> vd_MuonTMLastStationAngLoose;
  std::vector<double> vd_MuonTMLastStationAngTight;
  std::vector<double> vd_MuonTMLastStationOptimizedLowPtLoose;
  std::vector<double> vd_MuonTMLastStationOptimizedLowPtTight;
  std::vector<double> vd_MuonTMLastStationOptimizedBarrelLowPtLoose;
  std::vector<double> vd_MuonTMLastStationOptimizedBarrelLowPtTight;

  std::vector<double> vd_MuonECalIsoDeposit;
  std::vector<double> vd_MuonHCalIsoDeposit;
  
  std::vector<double> vd_MuonCombChi2;
  std::vector<double> vd_MuonCombNdof;
  std::vector<double> vd_MuonTrkD0;
  
  std::vector<double> vd_MuonId;
  std::vector<double> vd_MuonCombVx;
  std::vector<double> vd_MuonCombVy;
  std::vector<double> vd_MuonCombVz;
  std::vector<double> vd_MuonCombD0;
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
  std::vector<double> vd_MuonStandQOverPError;

  std::vector<double> vd_MuonTrkValidHits;
  std::vector<double> vd_MuonTrkLostHits;
  std::vector<double> vd_MuonTrkPt;
  std::vector<double> vd_MuonTrkPz;
  std::vector<double> vd_MuonTrkP;
  std::vector<double> vd_MuonTrkEta;
  std::vector<double> vd_MuonTrkPhi;
  std::vector<double> vd_MuonTrkChi;
  std::vector<double> vd_MuonTrkCharge;
  std::vector<double> vd_MuonTrkQOverPError;
  std::vector<double> vd_MuonTrkOuterZ;
  std::vector<double> vd_MuonTrkOuterR;

  std::vector<double> vd_MuonGenPdgId;
  std::vector<double> vd_MuonGenMother;

  //int    m_AlpIdTest;
  //std::vector<double> vd_AlpPtScale;
  double d_Pthat;

  //std::vector<double> vd_MuonPairMass;
  //int    m_MuonPairIndex[2];

  std::vector<reco::Candidate::LorentzVector> v_genP4;
  std::vector<reco::Candidate::LorentzVector> v_genLepP4;
  int               i_length;
  std::vector<int>  vi_genIds;
  std::vector<int>  vi_genRefs;
  std::vector<int>  vi_genStatus;

  int               i_genLepLength;
  std::vector<int>  vi_genLepIds;
  std::vector<int>  vi_genLepRefs;
  std::vector<int>  vi_genLepStatus;

  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

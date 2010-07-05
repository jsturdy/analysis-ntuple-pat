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
  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_elecP4 ( new std::vector<reco::Candidate::LorentzVector>() );
  std::vector<reco::Candidate::LorentzVector> v_elecP4;
  int    i_ElecN;
  int    i_ElecNIso;
  bool   bool_ElecVeto;
  double mat_d_ElecEt[50];
  double mat_d_ElecPt[50];
  double mat_d_ElecPx[50];
  double mat_d_ElecPy[50];
  double mat_d_ElecPz[50];
  double mat_d_ElecE[50];
  double mat_d_ElecEta[50];
  double mat_d_ElecPhi[50];
  double mat_d_ElecTrkIso[50];
  double mat_d_ElecECalIso[50];
  double mat_d_ElecHCalIso[50];
  double mat_d_ElecAllIso[50];
  double mat_d_ElecTrkChiNorm[50];
  double mat_d_ElecCharge[50];

  double mat_d_ElecIdLoose[50];
  double mat_d_ElecIdTight[50];
  double mat_d_ElecIdRobLoose[50];
  double mat_d_ElecIdRobTight[50];
  double mat_d_ElecIdRobHighE[50];
  double mat_d_ElecChargeMode[50];
  double mat_d_ElecPtTrkMode[50];
  double mat_d_ElecQOverPErrTrkMode[50];

  double mat_d_ElecGenPdgId[50];
  double mat_d_ElecGenMother[50];
  double mat_d_ElecGenPx[50];
  double mat_d_ElecGenPy[50];
  double mat_d_ElecGenPz[50];
  double mat_d_ElecGenPt[50];
  double mat_d_ElecGenEt[50];
  double mat_d_ElecGenE[50];

  double mat_d_ElecCaloEnergy[50];
  double mat_d_ElecHOverE[50];
  double mat_d_ElecVx[50];
  double mat_d_ElecVy[50];
  double mat_d_ElecVz[50];
  double mat_d_ElecD0[50];
  double mat_d_ElecDz[50];
  double mat_d_ElecPtTrk[50];
  double mat_d_ElecQOverPErrTrk[50];
  double mat_d_ElecLostHits[50];
  double mat_d_ElecValidHits[50];
  //double mat_d_ElecNCluster[50];
  double mat_d_ElecEtaTrk[50];
  double mat_d_ElecPhiTrk[50];
  double mat_d_ElecWidthClusterEta[50];
  double mat_d_ElecWidthClusterPhi[50];
  double mat_d_ElecPinTrk[50];
  double mat_d_ElecPoutTrk[50];
  double mat_d_ElecNormChi2[50];
  //bool mat_b_ccElecAssoc[50];

  double mat_d_ElecECalIsoDeposit[50];
  double mat_d_ElecHCalIsoDeposit[50];

  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_muonP4 ( new std::vector<reco::Candidate::LorentzVector>() );
  std::vector<reco::Candidate::LorentzVector> v_muonP4;
  int    i_MuonN;
  bool   bool_MuonVeto;
  double mat_d_MuonEt[50];
  double mat_d_MuonPt[50];
  double mat_d_MuonPx[50];
  double mat_d_MuonPy[50];
  double mat_d_MuonPz[50];
  double mat_d_MuonE[50];
  double mat_d_MuonEta[50];
  double mat_d_MuonPhi[50];
  double mat_d_MuonTrkIso[50];
  double mat_d_MuonECalIso[50];
  double mat_d_MuonHCalIso[50];
  double mat_d_MuonAllIso[50];
  double mat_d_MuonTrkChiNorm[50];
  double mat_d_MuonCharge[50];

  double mat_d_MuonIsGlobal[50];
  double mat_d_MuonIsStandAlone[50];
  double mat_d_MuonIsTracker[50];

  double mat_d_MuonGlobalMuonPromptTight[50];

  double mat_d_MuonAllArbitrated[50];
  double mat_d_MuonTrackerMuonArbitrated[50];
  double mat_d_MuonGMTkKinkTight[50];
  double mat_d_MuonGMTkChiCompatibility[50];
  double mat_d_MuonGMStaChiCompatibility[50];
  double mat_d_MuonTM2DCompatibilityLoose[50];
  double mat_d_MuonTM2DCompatibilityTight[50];
  double mat_d_MuonTMOneStationLoose[50];
  double mat_d_MuonTMOneStationTight[50];
  double mat_d_MuonTMLastStationLoose[50];
  double mat_d_MuonTMLastStationTight[50];
  double mat_d_MuonTMLastStationAngLoose[50];
  double mat_d_MuonTMLastStationAngTight[50];
  double mat_d_MuonTMLastStationOptimizedLowPtLoose[50];
  double mat_d_MuonTMLastStationOptimizedLowPtTight[50];
  double mat_d_MuonTMLastStationOptimizedBarrelLowPtLoose[50];
  double mat_d_MuonTMLastStationOptimizedBarrelLowPtTight[50];

  double mat_d_MuonECalIsoDeposit[50];
  double mat_d_MuonHCalIsoDeposit[50];
  
  double mat_d_MuonCombChi2[50];
  double mat_d_MuonCombNdof[50];
  double mat_d_MuonTrkD0[50];
  
  double mat_d_MuonId[50];
  double mat_d_MuonCombVx[50];
  double mat_d_MuonCombVy[50];
  double mat_d_MuonCombVz[50];
  double mat_d_MuonCombD0[50];
  double mat_d_MuonCombDz[50];

  double mat_d_MuonStandValidHits[50];
  double mat_d_MuonStandLostHits[50];
  double mat_d_MuonStandPt[50];
  double mat_d_MuonStandPz[50];
  double mat_d_MuonStandP[50];
  double mat_d_MuonStandEta[50];
  double mat_d_MuonStandPhi[50];
  double mat_d_MuonStandChi[50];
  double mat_d_MuonStandCharge[50];
  double mat_d_MuonStandQOverPError[50];

  double mat_d_MuonTrkValidHits[50];
  double mat_d_MuonTrkLostHits[50];
  double mat_d_MuonTrkPt[50];
  double mat_d_MuonTrkPz[50];
  double mat_d_MuonTrkP[50];
  double mat_d_MuonTrkEta[50];
  double mat_d_MuonTrkPhi[50];
  double mat_d_MuonTrkChi[50];
  double mat_d_MuonTrkCharge[50];
  double mat_d_MuonTrkQOverPError[50];
  double mat_d_MuonTrkOuterZ[50];
  double mat_d_MuonTrkOuterR[50];

  double mat_d_MuonGenPdgId[50];
  double mat_d_MuonGenMother[50];
  double mat_d_MuonGenPx[50];
  double mat_d_MuonGenPy[50];
  double mat_d_MuonGenPz[50];
  double mat_d_MuonGenPt[50];
  double mat_d_MuonGenEt[50];
  double mat_d_MuonGenE[50];

  //int    m_AlpIdTest;
  //double mat_d_AlpPtScale;
  double d_Pthat;

  //double mat_d_MuonPairMass;
  //int    m_MuonPairIndex[2];

  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_genP4    ( new std::vector<reco::Candidate::LorentzVector>() );
  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector> > v_genLepP4 ( new std::vector<reco::Candidate::LorentzVector>() );
  std::vector<reco::Candidate::LorentzVector> v_genP4;
  std::vector<reco::Candidate::LorentzVector> v_genLepP4;
  int   i_length;
  int   mat_i_genIds[500];
  int   mat_i_genRefs[500];
  int   mat_i_genStatus[500];
  float mat_f_genE[500];
  float mat_f_genPx[500];
  float mat_f_genPy[500];
  float mat_f_genPz[500];

  int   mat_i_genLepLength;
  int   mat_i_genLepIds[500];
  int   mat_i_genLepRefs[500];
  int   mat_i_genLepStatus[500];
  float mat_f_genLepE[500];
  float mat_f_genLepPx[500];
  float mat_f_genLepPy[500];
  float mat_f_genLepPz[500];

  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

#ifndef LEPTONANALYZERPAT
#define LEPTONANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
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
  int    m_ElecN;
  int    m_ElecNIso;
  bool   m_ElecVeto;
  double m_ElecEt[50];
  double m_ElecPt[50];
  double m_ElecPx[50];
  double m_ElecPy[50];
  double m_ElecPz[50];
  double m_ElecE[50];
  double m_ElecEta[50];
  double m_ElecPhi[50];
  double m_ElecTrkIso[50];
  double m_ElecECalIso[50];
  double m_ElecHCalIso[50];
  double m_ElecAllIso[50];
  double m_ElecTrkChiNorm[50];
  double m_ElecCharge[50];

  double m_ElecIdLoose[50];
  double m_ElecIdTight[50];
  double m_ElecIdRobLoose[50];
  double m_ElecIdRobTight[50];
  double m_ElecChargeMode[50];
  double m_ElecPtTrkMode[50];
  double m_ElecQOverPErrTrkMode[50];

  double m_ElecGenPdgId[50];
  double m_ElecGenMother[50];
  double m_ElecGenPx[50];
  double m_ElecGenPy[50];
  double m_ElecGenPz[50];
  double m_ElecGenPt[50];
  double m_ElecGenEt[50];
  double m_ElecGenE[50];

  double m_ElecCaloEnergy[50];
  double m_ElecHOverE[50];
  double m_ElecVx[50];
  double m_ElecVy[50];
  double m_ElecVz[50];
  double m_ElecD0[50];
  double m_ElecDz[50];
  double m_ElecPtTrk[50];
  double m_ElecQOverPErrTrk[50];
  double m_ElecLostHits[50];
  double m_ElecValidHits[50];
  double m_ElecNCluster[50];
  double m_ElecEtaTrk[50];
  double m_ElecPhiTrk[50];
  double m_ElecWidthClusterEta[50];
  double m_ElecWidthClusterPhi[50];
  double m_ElecPinTrk[50];
  double m_ElecPoutTrk[50];
  double m_ElecNormChi2[50];
  bool m_ccElecAssoc[50];

  double m_ElecECalIsoDeposit[50];
  double m_ElecHCalIsoDeposit[50];

  int    m_MuonN;
  bool   m_MuonVeto;
  double m_MuonEt[50];
  double m_MuonPt[50];
  double m_MuonPx[50];
  double m_MuonPy[50];
  double m_MuonPz[50];
  double m_MuonE[50];
  double m_MuonEta[50];
  double m_MuonPhi[50];
  double m_MuonTrkIso[50];
  double m_MuonECalIso[50];
  double m_MuonHCalIso[50];
  double m_MuonAllIso[50];
  double m_MuonTrkChiNorm[50];
  double m_MuonCharge[50];

  double m_MuonIsGlobal[50];
  double m_MuonIsStandAlone[50];
  double m_MuonIsTracker[50];

  double m_MuonGlobalMuonPromptTight[50];

  double m_MuonAllArbitrated[50];
  double m_MuonTrackerMuonArbitrated[50];
  double m_MuonGMTkKinkTight[50];
  double m_MuonGMTkChiCompatibility[50];
  double m_MuonGMStaChiCompatibility[50];
  double m_MuonTM2DCompatibilityLoose[50];
  double m_MuonTM2DCompatibilityTight[50];
  double m_MuonTMOneStationLoose[50];
  double m_MuonTMOneStationTight[50];
  double m_MuonTMLastStationLoose[50];
  double m_MuonTMLastStationTight[50];
  double m_MuonTMLastStationAngLoose[50];
  double m_MuonTMLastStationAngTight[50];
  double m_MuonTMLastStationOptimizedLowPtLoose[50];
  double m_MuonTMLastStationOptimizedLowPtTight[50];
  double m_MuonTMLastStationOptimizedBarrelLowPtLoose[50];
  double m_MuonTMLastStationOptimizedBarrelLowPtTight[50];

  double m_MuonECalIsoDeposit[50];
  double m_MuonHCalIsoDeposit[50];
  
  double m_MuonCombChi2[50];
  double m_MuonCombNdof[50];
  double m_MuonTrkD0[50];
  
  double m_MuonId[50];
  double m_MuonCombVx[50];
  double m_MuonCombVy[50];
  double m_MuonCombVz[50];
  double m_MuonCombD0[50];
  double m_MuonCombDz[50];

  double m_MuonStandValidHits[50];
  double m_MuonStandLostHits[50];
  double m_MuonStandPt[50];
  double m_MuonStandPz[50];
  double m_MuonStandP[50];
  double m_MuonStandEta[50];
  double m_MuonStandPhi[50];
  double m_MuonStandChi[50];
  double m_MuonStandCharge[50];
  double m_MuonStandQOverPError[50];

  double m_MuonTrkValidHits[50];
  double m_MuonTrkLostHits[50];
  double m_MuonTrkPt[50];
  double m_MuonTrkPz[50];
  double m_MuonTrkP[50];
  double m_MuonTrkEta[50];
  double m_MuonTrkPhi[50];
  double m_MuonTrkChi[50];
  double m_MuonTrkCharge[50];
  double m_MuonTrkQOverPError[50];
  double m_MuonTrkOuterZ[50];
  double m_MuonTrkOuterR[50];

  double m_MuonGenPdgId[50];
  double m_MuonGenMother[50];
  double m_MuonGenPx[50];
  double m_MuonGenPy[50];
  double m_MuonGenPz[50];
  double m_MuonGenPt[50];
  double m_MuonGenEt[50];
  double m_MuonGenE[50];

  int    m_AlpIdTest;
  double m_AlpPtScale;
  double m_Pthat;

  double m_MuonPairMass;
  int    m_MuonPairIndex[2];

  int   length;
  int   genIds[500];
  int   genRefs[500];
  int   genStatus[500];
  float genE[500];
  float genPx[500];
  float genPy[500];
  float genPz[500];

  int   genLepLength;
  int   genLepIds[500];
  int   genLepRefs[500];
  int   genLepStatus[500];
  float genLepE[500];
  float genLepPx[500];
  float genLepPy[500];
  float genLepPz[500];

  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

};

#endif

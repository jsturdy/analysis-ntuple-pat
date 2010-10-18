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
  std::vector<double> vd_ElecGenPx;
  std::vector<double> vd_ElecGenPy;
  std::vector<double> vd_ElecGenPz;
  std::vector<double> vd_ElecGenE;
  
  std::vector<double> vd_ElecPx;
  std::vector<double> vd_ElecPy;
  std::vector<double> vd_ElecPz;
  std::vector<double> vd_ElecE;
  
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
  std::vector<double> vd_MuonGenPx;
  std::vector<double> vd_MuonGenPy;
  std::vector<double> vd_MuonGenPz;
  std::vector<double> vd_MuonGenE;
  
  std::vector<double> vd_MuonPx;
  std::vector<double> vd_MuonPy;
  std::vector<double> vd_MuonPz;
  std::vector<double> vd_MuonE;

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
  std::vector<double> vd_genPx;
  std::vector<double> vd_genPy;
  std::vector<double> vd_genPz;
  std::vector<double> vd_genE;

  int               i_genLepLength;
  std::vector<int>  vi_genLepIds;
  std::vector<int>  vi_genLepRefs;
  std::vector<int>  vi_genLepStatus;
  std::vector<double> vd_genLepPx;
  std::vector<double> vd_genLepPy;
  std::vector<double> vd_genLepPz;
  std::vector<double> vd_genLepE;

  bool init_;                          // vectors initialised or not


  std::string outputFileName_;

  //input from .cfg

  double localPi;

  void maintenanceGen(const int& nParts) {
    v_genP4.clear();
    v_genLepP4.clear();
    vi_genIds.clear();
    vi_genRefs.clear();
    vi_genStatus.clear();
    vd_genPx.clear();
    vd_genPy.clear();
    vd_genPz.clear();
    vd_genE.clear();
    
    vi_genLepIds.clear();
    vi_genLepRefs.clear();
    vi_genLepStatus.clear();
    vd_genLepPx.clear();
    vd_genLepPy.clear();
    vd_genLepPz.clear();
    vd_genLepE.clear();

    //v_genP4.reserve(nParts);
    //v_genLepP4.reserve(nParts);
    //vi_genIds.reserve(nParts);
    //vi_genRefs.reserve(nParts);
    //vi_genStatus.reserve(nParts);
    //vd_genPx.reserve(nParts);
    //vd_genPy.reserve(nParts);
    //vd_genPz.reserve(nParts);
    //vd_genE.reserve(nParts);
    //
    //vi_genLepIds.reserve(nParts);
    //vi_genLepRefs.reserve(nParts);
    //vi_genLepStatus.reserve(nParts);
    //vd_genLepPx.reserve(nParts);
    //vd_genLepPy.reserve(nParts);
    //vd_genLepPz.reserve(nParts);
    //vd_genLepE.reserve(nParts);
    
  }

  void maintenanceElecs(const int& nElecs) {
    v_elecP4.clear();
    v_genelecP4.clear();
    vd_ElecGenPx.clear();
    vd_ElecGenPy.clear();
    vd_ElecGenPz.clear();
    vd_ElecGenE.clear();
    
    vd_ElecPx.clear();
    vd_ElecPy.clear();
    vd_ElecPz.clear();
    vd_ElecE.clear();
    
    vd_ElecTrkIso.clear();
    vd_ElecECalIso.clear();
    vd_ElecHCalIso.clear();
    vd_ElecAllIso.clear();
    vd_ElecTrkChiNorm.clear();
    vd_ElecCharge.clear();
    
    vd_ElecIdLoose.clear();
    vd_ElecIdTight.clear();
    vd_ElecIdRobLoose.clear();
    vd_ElecIdRobTight.clear();
    vd_ElecIdRobHighE.clear();
    vd_ElecChargeMode.clear();
    vd_ElecPtTrkMode.clear();
    vd_ElecQOverPErrTrkMode.clear();
    
    vd_ElecGenPdgId.clear();
    vd_ElecGenMother.clear();
    
    vd_ElecCaloEnergy.clear();
    vd_ElecHOverE.clear();
    vd_ElecVx.clear();
    vd_ElecVy.clear();
    vd_ElecVz.clear();
    vd_ElecD0.clear();
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

    //v_elecP4.reserve(nElecs);
    //v_genelecP4.reserve(nElecs);
    //vd_ElecGenPx.reserve(nElecs);
    //vd_ElecGenPy.reserve(nElecs);
    //vd_ElecGenPz.reserve(nElecs);
    //vd_ElecGenE.reserve(nElecs);
    //
    //vd_ElecPx.reserve(nElecs);
    //vd_ElecPy.reserve(nElecs);
    //vd_ElecPz.reserve(nElecs);
    //vd_ElecE.reserve(nElecs);
    //
    //vd_ElecTrkIso.reserve(nElecs);
    //vd_ElecECalIso.reserve(nElecs);
    //vd_ElecHCalIso.reserve(nElecs);
    //vd_ElecAllIso.reserve(nElecs);
    //vd_ElecTrkChiNorm.reserve(nElecs);
    //vd_ElecCharge.reserve(nElecs);
    //
    //vd_ElecIdLoose.reserve(nElecs);
    //vd_ElecIdTight.reserve(nElecs);
    //vd_ElecIdRobLoose.reserve(nElecs);
    //vd_ElecIdRobTight.reserve(nElecs);
    //vd_ElecIdRobHighE.reserve(nElecs);
    //vd_ElecChargeMode.reserve(nElecs);
    //vd_ElecPtTrkMode.reserve(nElecs);
    //vd_ElecQOverPErrTrkMode.reserve(nElecs);
    //
    //vd_ElecGenPdgId.reserve(nElecs);
    //vd_ElecGenMother.reserve(nElecs);
    //
    //vd_ElecCaloEnergy.reserve(nElecs);
    //vd_ElecHOverE.reserve(nElecs);
    //vd_ElecVx.reserve(nElecs);
    //vd_ElecVy.reserve(nElecs);
    //vd_ElecVz.reserve(nElecs);
    //vd_ElecD0.reserve(nElecs);
    //vd_ElecDz.reserve(nElecs);
    //vd_ElecPtTrk.reserve(nElecs);
    //vd_ElecQOverPErrTrk.reserve(nElecs);
    //vd_ElecLostHits.reserve(nElecs);
    //vd_ElecValidHits.reserve(nElecs);
    ////vd_ElecNCluster.reserve(nElecs);
    //vd_ElecEtaTrk.reserve(nElecs);
    //vd_ElecPhiTrk.reserve(nElecs);
    //vd_ElecWidthClusterEta.reserve(nElecs);
    //vd_ElecWidthClusterPhi.reserve(nElecs);
    //vd_ElecPinTrk.reserve(nElecs);
    //vd_ElecPoutTrk.reserve(nElecs);
    //vd_ElecNormChi2.reserve(nElecs);
    ////vb_ccElecAssoc.reserve(nElecs);
    //
    //vd_ElecECalIsoDeposit.reserve(nElecs);
    //vd_ElecHCalIsoDeposit.reserve(nElecs);
  }

  void maintenanceMuons(const int& nMuons) {
    v_muonP4.clear();
    v_genmuonP4.clear();
    vd_MuonGenPx.clear();
    vd_MuonGenPy.clear();
    vd_MuonGenPz.clear();
    vd_MuonGenE.clear();
  
    vd_MuonPx.clear();
    vd_MuonPy.clear();
    vd_MuonPz.clear();
    vd_MuonE.clear();

    vd_MuonTrkIso.clear();
    vd_MuonECalIso.clear();
    vd_MuonHCalIso.clear();
    vd_MuonAllIso.clear();
    vd_MuonTrkChiNorm.clear();
    vd_MuonCharge.clear();

    vd_MuonIsGlobal.clear();
    vd_MuonIsStandAlone.clear();
    vd_MuonIsTracker.clear();

    vd_MuonGlobalMuonPromptTight.clear();

    vd_MuonAllArbitrated.clear();
    vd_MuonTrackerMuonArbitrated.clear();
    vd_MuonGMTkKinkTight.clear();
    vd_MuonGMTkChiCompatibility.clear();
    vd_MuonGMStaChiCompatibility.clear();
    vd_MuonTM2DCompatibilityLoose.clear();
    vd_MuonTM2DCompatibilityTight.clear();
    vd_MuonTMOneStationLoose.clear();
    vd_MuonTMOneStationTight.clear();
    vd_MuonTMLastStationLoose.clear();
    vd_MuonTMLastStationTight.clear();
    vd_MuonTMLastStationAngLoose.clear();
    vd_MuonTMLastStationAngTight.clear();
    vd_MuonTMLastStationOptimizedLowPtLoose.clear();
    vd_MuonTMLastStationOptimizedLowPtTight.clear();
    vd_MuonTMLastStationOptimizedBarrelLowPtLoose.clear();
    vd_MuonTMLastStationOptimizedBarrelLowPtTight.clear();

    vd_MuonECalIsoDeposit.clear();
    vd_MuonHCalIsoDeposit.clear();
  
    vd_MuonCombChi2.clear();
    vd_MuonCombNdof.clear();
    vd_MuonTrkD0.clear();
  
    vd_MuonId.clear();
    vd_MuonCombVx.clear();
    vd_MuonCombVy.clear();
    vd_MuonCombVz.clear();
    vd_MuonCombD0.clear();
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
    vd_MuonStandQOverPError.clear();

    vd_MuonTrkValidHits.clear();
    vd_MuonTrkLostHits.clear();
    vd_MuonTrkPt.clear();
    vd_MuonTrkPz.clear();
    vd_MuonTrkP.clear();
    vd_MuonTrkEta.clear();
    vd_MuonTrkPhi.clear();
    vd_MuonTrkChi.clear();
    vd_MuonTrkCharge.clear();
    vd_MuonTrkQOverPError.clear();
    vd_MuonTrkOuterZ.clear();
    vd_MuonTrkOuterR.clear();

    vd_MuonGenPdgId.clear();
    vd_MuonGenMother.clear();

    //v_muonP4.reserve(nMuons);
    //v_genmuonP4.reserve(nMuons);
    //vd_MuonGenPx.reserve(nMuons);
    //vd_MuonGenPy.reserve(nMuons);
    //vd_MuonGenPz.reserve(nMuons);
    //vd_MuonGenE.reserve(nMuons);
    //
    //vd_MuonPx.reserve(nMuons);
    //vd_MuonPy.reserve(nMuons);
    //vd_MuonPz.reserve(nMuons);
    //vd_MuonE.reserve(nMuons);
    //
    //vd_MuonTrkIso.reserve(nMuons);
    //vd_MuonECalIso.reserve(nMuons);
    //vd_MuonHCalIso.reserve(nMuons);
    //vd_MuonAllIso.reserve(nMuons);
    //vd_MuonTrkChiNorm.reserve(nMuons);
    //vd_MuonCharge.reserve(nMuons);
    //
    //vd_MuonIsGlobal.reserve(nMuons);
    //vd_MuonIsStandAlone.reserve(nMuons);
    //vd_MuonIsTracker.reserve(nMuons);
    //
    //vd_MuonGlobalMuonPromptTight.reserve(nMuons);
    //
    //vd_MuonAllArbitrated.reserve(nMuons);
    //vd_MuonTrackerMuonArbitrated.reserve(nMuons);
    //vd_MuonGMTkKinkTight.reserve(nMuons);
    //vd_MuonGMTkChiCompatibility.reserve(nMuons);
    //vd_MuonGMStaChiCompatibility.reserve(nMuons);
    //vd_MuonTM2DCompatibilityLoose.reserve(nMuons);
    //vd_MuonTM2DCompatibilityTight.reserve(nMuons);
    //vd_MuonTMOneStationLoose.reserve(nMuons);
    //vd_MuonTMOneStationTight.reserve(nMuons);
    //vd_MuonTMLastStationLoose.reserve(nMuons);
    //vd_MuonTMLastStationTight.reserve(nMuons);
    //vd_MuonTMLastStationAngLoose.reserve(nMuons);
    //vd_MuonTMLastStationAngTight.reserve(nMuons);
    //vd_MuonTMLastStationOptimizedLowPtLoose.reserve(nMuons);
    //vd_MuonTMLastStationOptimizedLowPtTight.reserve(nMuons);
    //vd_MuonTMLastStationOptimizedBarrelLowPtLoose.reserve(nMuons);
    //vd_MuonTMLastStationOptimizedBarrelLowPtTight.reserve(nMuons);
    //
    //vd_MuonECalIsoDeposit.reserve(nMuons);
    //vd_MuonHCalIsoDeposit.reserve(nMuons);
    //
    //vd_MuonCombChi2.reserve(nMuons);
    //vd_MuonCombNdof.reserve(nMuons);
    //vd_MuonTrkD0.reserve(nMuons);
    //
    //vd_MuonId.reserve(nMuons);
    //vd_MuonCombVx.reserve(nMuons);
    //vd_MuonCombVy.reserve(nMuons);
    //vd_MuonCombVz.reserve(nMuons);
    //vd_MuonCombD0.reserve(nMuons);
    //vd_MuonCombDz.reserve(nMuons);
    //
    //vd_MuonStandValidHits.reserve(nMuons);
    //vd_MuonStandLostHits.reserve(nMuons);
    //vd_MuonStandPt.reserve(nMuons);
    //vd_MuonStandPz.reserve(nMuons);
    //vd_MuonStandP.reserve(nMuons);
    //vd_MuonStandEta.reserve(nMuons);
    //vd_MuonStandPhi.reserve(nMuons);
    //vd_MuonStandChi.reserve(nMuons);
    //vd_MuonStandCharge.reserve(nMuons);
    //vd_MuonStandQOverPError.reserve(nMuons);
    //
    //vd_MuonTrkValidHits.reserve(nMuons);
    //vd_MuonTrkLostHits.reserve(nMuons);
    //vd_MuonTrkPt.reserve(nMuons);
    //vd_MuonTrkPz.reserve(nMuons);
    //vd_MuonTrkP.reserve(nMuons);
    //vd_MuonTrkEta.reserve(nMuons);
    //vd_MuonTrkPhi.reserve(nMuons);
    //vd_MuonTrkChi.reserve(nMuons);
    //vd_MuonTrkCharge.reserve(nMuons);
    //vd_MuonTrkQOverPError.reserve(nMuons);
    //vd_MuonTrkOuterZ.reserve(nMuons);
    //vd_MuonTrkOuterR.reserve(nMuons);
    //
    //vd_MuonGenPdgId.reserve(nMuons);
    //vd_MuonGenMother.reserve(nMuons);

  }
};

#endif

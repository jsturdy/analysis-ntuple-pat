//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef ntupleAnalysisPAT_h
#define ntupleAnalysisPAT_h

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <map>
#include <set>
#include <utility>
#include "ntuplePragmas.h"

#include <unistd.h> // getcwd() definition
#include <sys/param.h> // MAXPATHLEN definitio

typedef struct {
  double lumi  ;
  double xs    ;
  double eff   ;
  double numGen;
  double scale ;
} sampleInfo;

class ntupleAnalysisPAT {
 public :
  TTree *allChain;    //!pointer to the analyzed TTree or TChain
  //TTree *eventChain;  //!pointer to the analyzed TTree or TChain
  TTree *jetChain;    //!pointer to the analyzed TTree or TChain
  TTree *metChain;    //!pointer to the analyzed TTree or TChain
  TTree *leptonChain; //!pointer to the analyzed TTree or TChain
  TTree *photonChain; //!pointer to the analyzed TTree or TChain
  TTree *triggerChain;//!pointer to the analyzed TTree or TChain
  TTree *vertexChain; //!pointer to the analyzed TTree or TChain
  TTree *genChain;    //!pointer to the analyzed TTree or TChain
  Int_t  fCurrent;//!current Tree number in a TChain
    
  // Declaration of leaf types
  //Standard event information
  Bool_t  isData;
  Int_t  totalEvents;

  Int_t  Run;
  Int_t  Event;
  Int_t  OrbitN;
  Int_t  StoreN;
  Int_t  LumiSection;
  Int_t  BunchCrossing;
  
  Double_t susyScanA0;
  Double_t susyScanM0;
  Double_t susyScanM12;
  Double_t susyScanMu;
  Double_t susyScanRun;
  Double_t susyScantanbeta;
  Double_t susyScanCrossSection;
    
  //Jets
  Int_t  NJets;
  Bool_t JetPreselection;
    
  Double_t    Ht;
  LorentzP4V *MHtP4;
    
  //std::vector<TLorentzVector>
  LorentzP4Vs *JetP4;
  LorentzP4Vs *RawJetP4;

  std::vector<double>  *JetEtaEtaMoment;
  std::vector<double>  *JetEtaPhiMoment;
  std::vector<double>  *JetPhiPhiMoment;

  //JES and Jet correction related variables
  std::map<std::string, std::vector<double> > *JetCorrectionFactor;
  std::vector<double> *JetCorrectionFactorUnc;
  std::vector<double> *JetCorrectionFactorL1;
  std::vector<double> *JetCorrectionFactorL2;
  std::vector<double> *JetCorrectionFactorL3;
  std::vector<double> *JetCorrectionFactorL2L3;
  std::vector<double> *JetCorrectionFactorL5uds;
  std::vector<double> *JetCorrectionFactorL5c;
  std::vector<double> *JetCorrectionFactorL5b;
  std::vector<double> *JetCorrectionFactorL5glu;
  std::vector<double> *JetCorrectionFactorL7uds;
  std::vector<double> *JetCorrectionFactorL7c;
  std::vector<double> *JetCorrectionFactorL7b;
  std::vector<double> *JetCorrectionFactorL7glu;

  std::vector<double>  *JECUncPlus;
  std::vector<double>  *JECUncMinus;
  ///////////////////////////

  ///Jet cross cleaning variables
  //std::map<std::string, std::vector<int> >  *JetOverlaps;
  //std::map<std::string, std::vector<int> >  *JetNOverlaps;

  std::vector<int>  *JetElectronOverlaps;
  std::vector<int>  *JetElectronNOverlaps;
  std::vector<int>  *JetMuonOverlaps;
  std::vector<int>  *JetMuonNOverlaps;
  std::vector<int>  *JetTauOverlaps;
  std::vector<int>  *JetTauNOverlaps;
  std::vector<int>  *JetPhotonOverlaps;
  std::vector<int>  *JetPhotonNOverlaps;
  ///////////////////

  //JetID info
  std::vector<int>    *JetIDMinimal;
  std::vector<int>    *JetIDLoose;
  std::vector<int>    *JetIDTight;
    
  std::vector<double>  *JetCharge;
  std::vector<int>  *JetNConst;
    
  std::vector<double>  *JetfHPD;
  std::vector<double>  *JetfRBX;
  std::vector<double>  *Jetn90;

  std::vector<double>  *JetTrackPt;
  std::vector<double>  *JetTrackPhi;
  std::vector<double>  *JetTrackPhiWeighted;
  std::vector<int>     *JetTrackNo;
    
  //Energy fractions
  std::vector<double>  *JetEFrac_em;
  std::vector<double>  *JetEFrac_had;
  std::vector<double>  *JetEFrac_muon;
  std::vector<double>  *JetEFrac_photon;
  std::vector<double>  *JetEFrac_electron;

  std::vector<double>  *JetChargedFrac_em;
  std::vector<double>  *JetChargedFrac_had;
  std::vector<double>  *JetChargedFrac_muon;
  std::vector<double>  *JetNeutralFrac_em;
  std::vector<double>  *JetNeutralFrac_had;

  std::vector<double>  *JetHFFrac_em;
  std::vector<double>  *JetHFFrac_had;

  //Energy
  std::vector<double>  *JetEn_em;
  std::vector<double>  *JetEn_had;
  std::vector<double>  *JetEn_muon;
  std::vector<double>  *JetEn_photon;
  std::vector<double>  *JetEn_electron;

  std::vector<double>  *JetChargedEn_em;
  std::vector<double>  *JetChargedEn_had;
  std::vector<double>  *JetChargedEn_muon;
  std::vector<double>  *JetNeutralEn_em;
  std::vector<double>  *JetNeutralEn_had;

  std::vector<double>  *JetHFEn_em;
  std::vector<double>  *JetHFEn_had;

  //Multiplicities
  std::vector<double>  *JetMuonMulti;
  std::vector<double>  *JetPhotonMult;
  std::vector<double>  *JetElectronMulti;
  std::vector<double>  *JetChargedMult;
  std::vector<double>  *JetNeutralMult;

  std::vector<double>  *JetHFMult_had;
  std::vector<double>  *JetHFMult_em;
  std::vector<double>  *JetNeutralMult_had;
  std::vector<double>  *JetChargedMult_had;
  //////////////////////////////////
    
  //B-Tag info
  std::vector<double>  *JetBTag_TCHE;
  std::vector<double>  *JetBTag_TCHP;
  std::vector<double>  *JetBTag_jetProb;
  std::vector<double>  *JetBTag_jetBProb;
  std::vector<double>  *JetBTag_SSVHE;
  std::vector<double>  *JetBTag_SSVHP;
  std::vector<double>  *JetBTag_CSV;
  std::vector<double>  *JetBTag_CSVMVA;
  std::vector<double>  *JetBTag_SoftLepton;
  std::vector<double>  *JetBTag_SoftLeptonByIP;
  std::vector<double>  *JetBTag_SoftLeptonByPt;
    
  LorentzP4Vs *GenJetP4;
  LorentzP4Vs *JetPartonP4;

  Double_t    GenHt;
  LorentzP4V *GenMHtP4;
    
  std::vector<int>  *JetPartonId;
  std::vector<int>  *JetPartonStatus;
  std::vector<int>  *JetPartonMother;
  std::vector<int>  *JetPartonMotherStatus;
  std::vector<int>  *JetPartonFlavour;
  /*************End of Jet Variables***************/



  /************MET Variables**************/
  //MET Information
  LorentzP4V     *METP4;

  Int_t           nFullMET;
  Int_t           nUncorrMET;

  Double_t        MET_Fullcorr[3];
  Double_t        METpt_Fullcorr;
  Double_t        METphi_Fullcorr;
  Double_t        METsumEt_Fullcorr;
  Double_t        METsignificance;
  //Remove all corrections
  Double_t        MET_Nocorr[2];
  Double_t        METpt_Nocorr;
  Double_t        METphi_Nocorr;
  Double_t        METsumEt_Nocorr;
  //remove JES corrections
  Double_t        MET_Muoncorr[2];
  Double_t        METpt_Muoncorr;
  Double_t        METphi_Muoncorr;
  Double_t        METsumEt_Muoncorr;
  //Remove Muon corrections
  Double_t        MET_JEScorr[2];
  Double_t        METpt_JEScorr;
  Double_t        METphi_JEScorr;
  Double_t        METsumEt_JEScorr;

  //specific to calo met
  Double_t METmaxEt_em;
  Double_t METmaxEt_had;
  Double_t METetFrac_had;
  Double_t METetFrac_em;
  Double_t METmetSig;

  //specific to PF met
  Double_t METFrac_neutralEM;
  Double_t METFrac_neutralHad;
  Double_t METFrac_chargedEM;
  Double_t METFrac_chargedHad;
  Double_t METFrac_muon;
  Double_t METFrac_type6;
  Double_t METFrac_type7;

  LorentzP4V     *GenMETP4;
  LorentzP4V     *GenMETTrueP4;
  LorentzP4V     *GenMETCaloP4;
  Double_t        GenSumEt;
  Double_t        GenTrueSumEt;
  Double_t        GenCaloSumEt;
  Double_t        GenMETSig;
  Double_t        GenTrueMETSig;
  Double_t        GenCaloMETSig;
  Double_t        GenSignificance;
  Double_t        GenTrueSignificance;
  Double_t        GenCaloSignificance;
  /*****************End of MET Variables**************************/

  /*****************Photon Variables**************************/
  //Photons
  Bool_t          PhotVeto;
  Int_t           PhotN;
  LorentzP4Vs    *PhotonP4;
  LorentzP4Vs    *PhotGenP4;

  std::vector<int> *PhotGenPdgId;
  std::vector<int> *PhotGenStatus;
  std::vector<int> *PhotGenMother;
  std::vector<int> *PhotGenMotherStatus;

  std::vector<double> *PhotTrkIso;
  std::vector<double> *PhotECalIso;
  std::vector<double> *PhotHCalIso;
  std::vector<double> *PhotAllIso;
  std::vector<double> *PhotPFAllParticleIso;
  std::vector<double> *PhotPFChargedHadronIso;
  std::vector<double> *PhotPFNeutralHadronIso;
  std::vector<double> *PhotPFGammaIso;

  //std::vector<double> *PhotTrkIsoDeposit;
  //std::vector<double> *PhotECalIsoDeposit;
  //std::vector<double> *PhotHCalIsoDeposit;
  //std::vector<double> *PhotPFAllParticleIsoDeposit;
  //std::vector<double> *PhotPFChargedHadronIsoDeposit;
  //std::vector<double> *PhotPFNeutralHadronIsoDeposit;
  //std::vector<double> *PhotPFGammaIsoDeposit;

  std::vector<double> *PhotSCEta;
  std::vector<double> *PhotSCPhi;
  std::vector<double> *PhotSCEn;
  std::vector<double> *PhotSCPt;
  std::vector<double> *PhotSCRawE;

  std::vector<int>   *PhotLoosePhoton;
  std::vector<int>   *PhotTightPhoton;
    
  std::vector<int>   *PhotIsEB;
  std::vector<int>   *PhotIsEE;
  std::vector<int>   *PhotIsEBGap;
  std::vector<int>   *PhotIsEEGap;
  std::vector<int>   *PhotIsEBEEGap;
  std::vector<int>   *PhotHasPixelSeed;
  std::vector<int>   *PhotHasConversionTracks;

  std::vector<double> *PhotTSeed;
  std::vector<double> *PhotESeed;
  std::vector<double> *PhotE2OverE9;
  std::vector<double> *PhotSwissCross;
  std::vector<double> *PhotHadOverEM;
  std::vector<double> *PhotSigmaIetaIeta;
  /*****************End of Photon Variables**************************/



  /*****************Electron Variables**************************/
  //Electrons
  Bool_t          ElecVeto;
  Int_t           ElecN;
  LorentzP4Vs    *ElectronP4;
  LorentzP4Vs    *ElecGenP4;

  std::vector<int> *ElecGenPdgId;
  std::vector<int> *ElecGenStatus;
  std::vector<int> *ElecGenMother;
  std::vector<int> *ElecGenMotherStatus;

  std::vector<double> *ElecdB;
  std::vector<double> *ElecdBerr;

  std::vector<double> *ElecCharge;
  std::vector<double> *ElecHadOverEM;
  std::vector<double> *ElecTrkChiNorm;

  std::vector<double> *ElecTrkIso;
  std::vector<double> *ElecECalIso;
  std::vector<double> *ElecHCalIso;
  std::vector<double> *ElecAllIso;
  std::vector<double> *ElecPFAllParticleIso;
  std::vector<double> *ElecPFChargedHadronIso;
  std::vector<double> *ElecPFNeutralHadronIso;
  std::vector<double> *ElecPFGammaIso;

  //std::vector<double> *ElecTrkIsoDeposit;
  //std::vector<double> *ElecECalIsoDeposit;
  //std::vector<double> *ElecHCalIsoDeposit;
  //std::vector<double> *ElecPFAllParticleIsoDeposit;
  //std::vector<double> *ElecPFChargedHadronIsoDeposit;
  //std::vector<double> *ElecPFNeutralHadronIsoDeposit;
  //std::vector<double> *ElecPFGammaIsoDeposit;

  std::vector<double>  *ElecIdLoose;
  std::vector<double>  *ElecIdTight;
  std::vector<double>  *ElecIdRobLoose;
  std::vector<double>  *ElecIdRobTight;
  std::vector<double>  *ElecIdRobHighE;
  
  std::vector<double> *ElecE2OverE9;
  std::vector<double> *ElecSwissCross;

  std::vector<double> *ElecE1x5;
  std::vector<double> *ElecE5x5;
  std::vector<double> *ElecE2x5Max;
  std::vector<double> *ElecFbrem;

  std::vector<double> *ElecTSeed;
  std::vector<double> *ElecESeed;
  std::vector<double> *ElecSigmaEtaEta;
  std::vector<double> *ElecSigmaIetaIeta;

  std::vector<double> *ElecVx;
  std::vector<double> *ElecVy;
  std::vector<double> *ElecVz;
  std::vector<double> *ElecPVDxy;
  std::vector<double> *ElecBSDxy;
  std::vector<double> *ElecDxy;
  std::vector<double> *ElecDxyErr;
  std::vector<double> *ElecD0;
  std::vector<double> *ElecD0Err;
  std::vector<double> *ElecDz;
  std::vector<double> *ElecDzErr;

  std::vector<double> *ElecPtTrk;
  std::vector<double> *ElecPtMode;
  std::vector<double> *ElecChargeMode;
  std::vector<double> *ElecQOverPErrTrkMode;
  std::vector<double> *ElecCaloEnergy;
  std::vector<double> *ElecQOverPErrTrk;
  std::vector<double> *ElecPinTrk;
  std::vector<double> *ElecPoutTrk;
  std::vector<double> *ElecLostHits;
  std::vector<double> *ElecValidHits;
  std::vector<double> *ElecEtaTrk;
  std::vector<double> *ElecPhiTrk;

  std::vector<double> *ElecSCEta;
  std::vector<double> *ElecSCPhi;
  std::vector<double> *ElecSCEn;
  std::vector<double> *ElecSCPt;
  std::vector<double> *ElecSCRawE;
  std::vector<double> *ElecWidthClusterEta;
  std::vector<double> *ElecWidthClusterPhi;
  /*****************End of Electron Variables**************************/



  /*****************Muon Variables**************************/
  //Muons
  Bool_t          MuonVeto;
  Int_t           MuonN;
  LorentzP4Vs    *MuonP4;
  LorentzP4Vs    *MuonGenP4;

  std::vector<double> *MuonCharge;

  std::vector<int> *MuonGenPdgId;
  std::vector<int> *MuonGenStatus;
  std::vector<int> *MuonGenMother;
  std::vector<int> *MuonGenMotherStatus;

  std::vector<double> *MuonTrkIso;
  std::vector<double> *MuonECalIso;
  std::vector<double> *MuonHCalIso;
  std::vector<double> *MuonAllIso;
  std::vector<double> *MuonPFAllParticleIso;
  std::vector<double> *MuonPFChargedHadronIso;
  std::vector<double> *MuonPFNeutralHadronIso;
  std::vector<double> *MuonPFGammaIso;

  //std::vector<double> *MuonTrkIsoDeposit;
  //std::vector<double> *MuonECalIsoDeposit;
  //std::vector<double> *MuonHCalIsoDeposit;
  //std::vector<double> *MuonECalIsoDepositR03;
  //std::vector<double> *MuonHCalIsoDepositR03;
  //std::vector<double> *MuonPFAllParticleIsoDeposit;
  //std::vector<double> *MuonPFChargedHadronIsoDeposit;
  //std::vector<double> *MuonPFNeutralHadronIsoDeposit;
  //std::vector<double> *MuonPFGammaIsoDeposit;

  std::vector<int> *MuonIsGlobal;
  std::vector<int> *MuonIsStandAlone;
  std::vector<int> *MuonIsTracker;
  std::vector<int> *MuonGlobalMuonPromptTight;

  std::vector<int> *MuonAllArbitrated;
  std::vector<int> *MuonTrackerMuonArbitrated;
  std::vector<int> *MuonTMLastStationLoose;
  std::vector<int> *MuonTMLastStationTight;
  std::vector<int> *MuonTM2DCompatibilityLoose;
  std::vector<int> *MuonTM2DCompatibilityTight;
  std::vector<int> *MuonTMOneStationLoose;
  std::vector<int> *MuonTMOneStationTight;
  std::vector<int> *MuonTMLastStationOptimizedLowPtLoose;
  std::vector<int> *MuonTMLastStationOptimizedLowPtTight;
  std::vector<int> *MuonGMTkChiCompatibility;
  std::vector<int> *MuonGMStaChiCompatibility;
  std::vector<int> *MuonGMTkKinkTight;
  std::vector<int> *MuonTMLastStationAngLoose;
  std::vector<int> *MuonTMLastStationAngTight;
  std::vector<int> *MuonTMLastStationOptimizedBarrelLowPtLoose;
  std::vector<int> *MuonTMLastStationOptimizedBarrelLowPtTight;

  //std::vector<int> *MuonId;

  std::vector<double> *MuonCombVx;
  std::vector<double> *MuonCombVy;
  std::vector<double> *MuonCombVz;
  std::vector<double> *MuonCombPVDxy;
  std::vector<double> *MuonCombBSDxy;
  std::vector<double> *MuonCombDxy;
  std::vector<double> *MuonCombDxyErr;
  std::vector<double> *MuonCombD0;
  std::vector<double> *MuonCombD0Err;
  std::vector<double> *MuonCombDz;
  std::vector<double> *MuonCombDzErr;
  std::vector<double> *MuonCombChi2;
  std::vector<double> *MuonCombNdof;
  std::vector<double> *MuonCombPt;
  std::vector<double> *MuonCombPz;
  std::vector<double> *MuonCombP;
  std::vector<double> *MuonCombEta;
  std::vector<double> *MuonCombPhi;
  std::vector<double> *MuonCombChi;
  std::vector<double> *MuonCombCharge;
  std::vector<double> *MuonCombQOverPErr;
  std::vector<double> *MuonCombValidHits;


  std::vector<double> *MuonStandValidHits;
  std::vector<double> *MuonStandLostHits;
  std::vector<double> *MuonStandPt;
  std::vector<double> *MuonStandPz;
  std::vector<double> *MuonStandP;
  std::vector<double> *MuonStandEta;
  std::vector<double> *MuonStandPhi;
  std::vector<double> *MuonStandCharge;
  std::vector<double> *MuonStandChi;
  std::vector<double> *MuonStandQOverPErr;
    
  std::vector<double> *MuonTrkChiNorm;
  std::vector<double> *MuonTrkValidHits;
  std::vector<double> *MuonTrkLostHits;
  std::vector<double> *MuonTrkPVDxy;
  std::vector<double> *MuonTrkBSDxy;
  std::vector<double> *MuonTrkDxy;
  std::vector<double> *MuonTrkDxyErr;
  std::vector<double> *MuonTrkD0;
  std::vector<double> *MuonTrkD0Err;
  std::vector<double> *MuonTrkDz;
  std::vector<double> *MuonTrkDzErr;
  std::vector<double> *MuonTrkPt;
  std::vector<double> *MuonTrkPz;
  std::vector<double> *MuonTrkP;
  std::vector<double> *MuonTrkEta;
  std::vector<double> *MuonTrkPhi;
  std::vector<double> *MuonTrkChi;
  std::vector<double> *MuonTrkCharge;
  std::vector<double> *MuonTrkQOverPErr;
  std::vector<double> *MuonTrkOuterZ;
  std::vector<double> *MuonTrkOuterR;

//  std::vector<double> *MuonPickyCharge;
//  std::vector<double> *MuonPickyTrkChiNorm;
//  std::vector<double> *MuonPickyTrkValidHits;
//  std::vector<double> *MuonPickyTrkLostHits;
//  std::vector<double> *MuonPickyTrkPVDxy;
//  std::vector<double> *MuonPickyTrkBSDxy;
//  std::vector<double> *MuonPickyTrkDxy;
//  std::vector<double> *MuonPickyTrkDxyErr;
//  std::vector<double> *MuonPickyTrkD0;
//  std::vector<double> *MuonPickyTrkD0Err;
//  std::vector<double> *MuonPickyTrkDz;
//  std::vector<double> *MuonPickyTrkDzErr;
//  std::vector<double> *MuonPickyTrkPt;
//  std::vector<double> *MuonPickyTrkPz;
//  std::vector<double> *MuonPickyTrkP;
//  std::vector<double> *MuonPickyTrkEta;
//  std::vector<double> *MuonPickyTrkPhi;
//  std::vector<double> *MuonPickyTrkChi;
//  std::vector<double> *MuonPickyTrkCharge;
//  std::vector<double> *MuonPickyTrkQOverPErr;
//  std::vector<double> *MuonPickyTrkOuterZ;
//  std::vector<double> *MuonPickyTrkOuterR;
//
//  std::vector<double> *MuonTPFMSTrkChiNorm;
//  std::vector<double> *MuonTPFMSCharge;
//  std::vector<double> *MuonTPFMSTrkValidHits;
//  std::vector<double> *MuonTPFMSTrkLostHits;
//  std::vector<double> *MuonTPFMSTrkPVDxy;
//  std::vector<double> *MuonTPFMSTrkBSDxy;
//  std::vector<double> *MuonTPFMSTrkDxy;
//  std::vector<double> *MuonTPFMSTrkDxyErr;
//  std::vector<double> *MuonTPFMSTrkD0;
//  std::vector<double> *MuonTPFMSTrkD0Err;
//  std::vector<double> *MuonTPFMSTrkDz;
//  std::vector<double> *MuonTPFMSTrkDzErr;
//  std::vector<double> *MuonTPFMSTrkPt;
//  std::vector<double> *MuonTPFMSTrkPz;
//  std::vector<double> *MuonTPFMSTrkP;
//  std::vector<double> *MuonTPFMSTrkEta;
//  std::vector<double> *MuonTPFMSTrkPhi;
//  std::vector<double> *MuonTPFMSTrkChi;
//  std::vector<double> *MuonTPFMSTrkCharge;
//  std::vector<double> *MuonTPFMSTrkQOverPErr;
//  std::vector<double> *MuonTPFMSTrkOuterZ;
//  std::vector<double> *MuonTPFMSTrkOuterR;
  /*****************End of Muon Variables**************************/



  /*****************Tau Variables**************************/
  //Taus
  Bool_t          TauVeto;
  Int_t           TauN;
  LorentzP4Vs    *TauP4;

  LorentzP4Vs    *TauGenP4;
  LorentzP4Vs    *TauGenJetP4;

  std::vector<int> *TauGen;
  std::vector<int> *TauGenPdgId;
  std::vector<int> *TauGenStatus;
  std::vector<int> *TauGenMother;
  std::vector<int> *TauGenMotherStatus;

  std::vector<double> *TauCharge;

  std::vector<double> *TauTrkIso;
  std::vector<double> *TauECalIso;
  std::vector<double> *TauHCalIso;
  std::vector<double> *TauAllIso;
  std::vector<double> *TauPFAllParticleIso;
  std::vector<double> *TauPFChargedHadronIso;
  std::vector<double> *TauPFNeutralHadronIso;
  std::vector<double> *TauPFGammaIso;

  //std::vector<double> *TauTrkIsoDeposit;
  //std::vector<double> *TauECalIsoDeposit;
  //std::vector<double> *TauHCalIsoDeposit;
  //std::vector<double> *TauPFAllParticleIsoDeposit;
  //std::vector<double> *TauPFChargedHadronIsoDeposit;
  //std::vector<double> *TauPFNeutralHadronIsoDeposit;
  //std::vector<double> *TauPFGammaIsoDeposit;

  std::vector<double> *TauVx;
  std::vector<double> *TauVy;
  std::vector<double> *TauVz;
  std::vector<double> *TauPVDxy;
  std::vector<double> *TauBSDxy;
  std::vector<double> *TauDxy;
  std::vector<double> *TauDxyErr;
  std::vector<double> *TauD0;
  std::vector<double> *TauD0Err;
  std::vector<double> *TauDz;
  std::vector<double> *TauDzErr;

  std::vector<double>  *TauIdElec;
  std::vector<double>  *TauIdMuon;

  std::vector<double>  *TauIdIso;
  std::vector<double>  *TauIdIsoLeadPi;

  std::vector<double>  *TauIdEcalIso;
  std::vector<double>  *TauIdEcalIsoLeadPi;

  std::vector<double>  *TauIdLeadPiPt;
  std::vector<double>  *TauIdLeadTrk;
  std::vector<double>  *TauIdLeadTrkPt;

  std::vector<double>  *TauIdTrkIso;
  std::vector<double>  *TauIdTrkIsoLeadPi;

  std::vector<double>  *TauIdNCfrFull;
  std::vector<double>  *TauIdNCfrHalf;
  std::vector<double>  *TauIdNCfrTenth;
  std::vector<double>  *TauIdNCfrQuarter;
  
  std::vector<double>  *TauCaloLeadTrkSignedIP      ;
  std::vector<double>  *TauCaloLeadTrkHcal3x3EtSum  ;
  std::vector<double>  *TauCaloLeadTrkHcal3x3HotDEta;
  std::vector<double>  *TauCaloSignalTrkMInv        ;
  std::vector<double>  *TauCaloTrkMInv              ;
  std::vector<double>  *TauCaloIsoTrkPtSum          ;
  std::vector<double>  *TauCaloIsoEcalEtSum         ;
  std::vector<double>  *TauCaloMaxEtHCAL            ;

  std::vector<double>  *TauPFIsoChargedHadPtSum;
  std::vector<double>  *TauPFIsoGammaEtSum     ;
  std::vector<double>  *TauPFHcalClusterMaxEt  ;
  std::vector<double>  *TauPFEFrac_em          ;
  std::vector<double>  *TauPFHcalTotalOverPLead;
  std::vector<double>  *TauPFHcalMaxOverPLead  ;
  std::vector<double>  *TauPFHcal3x3OverPLead  ;
  std::vector<double>  *TauPFEcalStripOverPLead;
  std::vector<double>  *TauPFBremRecOverPLead  ;
  std::vector<double>  *TauPFElePreIDOut       ;
  std::vector<double>  *TauPFMuonCaloComp      ;
  std::vector<double>  *TauPFMuonSegComp       ;

  std::vector<double>  *TauEtaEtaMom;
  std::vector<double>  *TauPhiPhiMom;
  std::vector<double>  *TauEtaPhiMom;

  /*****************End of Tau Variables**************************/



  /*****************Beamspot Variables**************************/
  //Beamspot 
  Double_t        beamspotX0;
  Double_t        beamspotY0;
  Double_t        beamspotZ0;
  Double_t        beamspotX0Err;
  Double_t        beamspotY0Err;
  Double_t        beamspotZ0Err;
  Double_t        beamspotWidthX;
  Double_t        beamspotWidthY;
  Double_t        beamspotWidthXErr;
  Double_t        beamspotWidthYErr;
  Double_t        beamspotdxdz;
  Double_t        beamspotdydz;
  Double_t        beamspotdxdzErr;
  Double_t        beamspotdydzErr;
  Double_t        beamspotSigmaZ0;
  Double_t        beamspotSigmaZ0Err;
  Double_t        beamspotEmittanceX;
  Double_t        beamspotEmittanceY;
  Double_t        beamspotBetaStar;
  /*****************End of Beamspot Variables**************************/



  /*****************Vertex Variables**************************/
  //Vertex information
  Int_t           nVtx;
  std::vector<double> *VertexIsValid;
  std::vector<double> *VertexChi2;
  std::vector<double> *VertexNdof;
  std::vector<double> *VertexNTrks;
  std::vector<double> *VertexNRawTrks;
  std::vector<double> *VertexSumTrkPt;
  std::vector<double> *VertexSumTrkPt2;
  std::vector<double> *VertexNormalizedChi2;
  std::vector<double> *VertexX;
  std::vector<double> *VertexY;
  std::vector<double> *VertexZ;
  std::vector<double> *Vertexd0;
  std::vector<double> *VertexdX;
  std::vector<double> *VertexdY;
  std::vector<double> *VertexdZ;
  /*****************End of Vertex Variables**************************/



  /*****************Beamspot Variables**************************/
  /*
  //MPT information
  Double_t        MPTPhi;
  Double_t        MPTPx;
  Double_t        MPTPy;
  Double_t        MPTPz;
  */
  /*****************End of Beamspot Variables**************************/
  


  /*****************Trigger Variables**************************/
  //Trigger information
  stringtobool *HLTTriggered;
  stringtoint  *HLTPrescaled;
  /*****************End of Trigger Variables**************************/



  /*****************Gen Particle Variables**************************/
  //Generator information
  Int_t             genN;
  LorentzP4Vs      *genP4;
  std::vector<int> *genId;
  std::vector<int> *genStatus;
  std::vector<int> *genMother;
  std::vector<int> *genDaughters;

  Int_t             genParticleN;
  LorentzP4Vs      *genParticleP4;
  std::vector<int> *genParticleId;
  std::vector<int> *genParticleStatus;
  std::vector<int> *genParticleMother;
  std::vector<int> *genParticleDaughters;

  Double_t pthat;
  bool doSusyScan;

  // List of branches
  TBranch  *b_isData;
  TBranch  *b_totalEvents;

  TBranch  *b_Run;
  TBranch  *b_Event;
  TBranch  *b_OrbitN;
  TBranch  *b_StoreN;
  TBranch  *b_LumiSection;
  TBranch  *b_BunchCrossing;
    
  TBranch  *b_susyScanA0;
  TBranch  *b_susyScanM0;
  TBranch  *b_susyScanM12;
  TBranch  *b_susyScanMu;
  TBranch  *b_susyScanRun;
  TBranch  *b_susyScantanbeta;
  TBranch  *b_susyScanCrossSection;
  //************************************Jet Branches************************************
  TBranch  *b_NJets;
  TBranch  *b_Ht;
  TBranch  *b_MHtP4;

  TBranch  *b_JetP4;
  TBranch  *b_RawJetP4;

  TBranch  *b_GenHt;
  TBranch  *b_GenMHtP4;

  TBranch  *b_GenJetP4;

  TBranch  *b_JetPartonP4;
  TBranch  *b_JetPartonId;
  TBranch  *b_JetPartonStatus;
  TBranch  *b_JetPartonMother;
  TBranch  *b_JetPartonMotherStatus;
  TBranch  *b_JetPartonFlavour;
    	     
  TBranch  *b_JetEtaEtaMoment;
  TBranch  *b_JetEtaPhiMoment;
  TBranch  *b_JetPhiPhiMoment;

  TBranch  *b_JetCorrectionFactor;
  TBranch  *b_JetCorrectionFactorUnc;
  TBranch  *b_JetCorrectionFactorL1;
  TBranch  *b_JetCorrectionFactorL2;
  TBranch  *b_JetCorrectionFactorL3;
  TBranch  *b_JetCorrectionFactorL2L3;
  TBranch  *b_JetCorrectionFactorL5uds;
  TBranch  *b_JetCorrectionFactorL5c;
  TBranch  *b_JetCorrectionFactorL5b;
  TBranch  *b_JetCorrectionFactorL5glu;
  TBranch  *b_JetCorrectionFactorL7uds;
  TBranch  *b_JetCorrectionFactorL7c;
  TBranch  *b_JetCorrectionFactorL7b;
  TBranch  *b_JetCorrectionFactorL7glu;

  TBranch  *b_JECUncPlus;
  TBranch  *b_JECUncMinus;

  TBranch  *b_JetElectronOverlaps;
  TBranch  *b_JetElectronNOverlaps;
  TBranch  *b_JetMuonOverlaps;
  TBranch  *b_JetMuonNOverlaps;
  TBranch  *b_JetTauOverlaps;
  TBranch  *b_JetTauNOverlaps;
  TBranch  *b_JetPhotonOverlaps;
  TBranch  *b_JetPhotonNOverlaps;

  TBranch  *b_JetPreselection;

  TBranch  *b_JetIDMinimal;
  TBranch  *b_JetIDLoose;
  TBranch  *b_JetIDTight;

  TBranch  *b_JetCharge;
  TBranch  *b_JetNConst;

  TBranch  *b_JetfHPD;
  TBranch  *b_JetfRBX;
  TBranch  *b_Jetn90;

  TBranch  *b_JetTrackPt;
  TBranch  *b_JetTrackPhi;
  TBranch  *b_JetTrackPhiWeighted;
  TBranch  *b_JetTrackNo;
    	     
  //Energy fractions
  TBranch  *b_JetEFrac_em;
  TBranch  *b_JetEFrac_had;
  TBranch  *b_JetEFrac_muon;
  TBranch  *b_JetEFrac_photon;
  TBranch  *b_JetEFrac_electron;

  TBranch  *b_JetChargedFrac_em;
  TBranch  *b_JetChargedFrac_had;
  TBranch  *b_JetChargedFrac_muon;
  TBranch  *b_JetNeutralFrac_em;
  TBranch  *b_JetNeutralFrac_had;

  TBranch  *b_JetHFFrac_em;
  TBranch  *b_JetHFFrac_had;

  //Energy
  TBranch  *b_JetEn_em;
  TBranch  *b_JetEn_had;
  TBranch  *b_JetEn_muon;
  TBranch  *b_JetEn_photon;
  TBranch  *b_JetEn_electron;

  TBranch  *b_JetChargedEn_em;
  TBranch  *b_JetChargedEn_had;
  TBranch  *b_JetChargedEn_muon;
  TBranch  *b_JetNeutralEn_em;
  TBranch  *b_JetNeutralEn_had;

  TBranch  *b_JetHFEn_em;
  TBranch  *b_JetHFEn_had;

  //Multiplicities
  TBranch  *b_JetMuonMulti;
  TBranch  *b_JetPhotonMult;
  TBranch  *b_JetElectronMulti;
  TBranch  *b_JetChargedMult;
  TBranch  *b_JetNeutralMult;

  TBranch  *b_JetHFMult_had;
  TBranch  *b_JetHFMult_em;
  TBranch  *b_JetNeutralMult_had;
  TBranch  *b_JetChargedMult_had;

  ///btagging
  TBranch  *b_JetBTag_TCHE;
  TBranch  *b_JetBTag_TCHP;
  TBranch  *b_JetBTag_jetProb;
  TBranch  *b_JetBTag_jetBProb;
  TBranch  *b_JetBTag_SSVHE;
  TBranch  *b_JetBTag_SSVHP;
  TBranch  *b_JetBTag_CSV;
  TBranch  *b_JetBTag_CSVMVA;
  TBranch  *b_JetBTag_SoftLepton;
  TBranch  *b_JetBTag_SoftLeptonByIP;
  TBranch  *b_JetBTag_SoftLeptonByPt;
    	     
  //************************************MET Branches************************************
  TBranch  *b_METP4;
  TBranch  *b_nFullMET;
  TBranch  *b_nUncorrMET;

  TBranch  *b_MET_Fullcorr;
  TBranch  *b_METpt_Fullcorr;
  TBranch  *b_METphi_Fullcorr;
  TBranch  *b_METsumEt_Fullcorr;
  TBranch  *b_METsignificance;

  TBranch  *b_MET_Nocorr;
  TBranch  *b_METpt_Nocorr;
  TBranch  *b_METphi_Nocorr;
  TBranch  *b_METsumEt_Nocorr;

  TBranch  *b_MET_Muoncorr;
  TBranch  *b_METpt_Muoncorr;
  TBranch  *b_METphi_Muoncorr;
  TBranch  *b_METsumEt_Muoncorr;

  TBranch  *b_MET_JEScorr;
  TBranch  *b_METpt_JEScorr;
  TBranch  *b_METphi_JEScorr;
  TBranch  *b_METsumEt_JEScorr;

  //specific to calo met
  TBranch *b_METmaxEt_em;
  TBranch *b_METmaxEt_had;
  TBranch *b_METetFrac_had;
  TBranch *b_METetFrac_em;
  TBranch *b_METmetSig;

  //specific to PF met
  TBranch *b_METFrac_neutralEM;
  TBranch *b_METFrac_neutralHad;
  TBranch *b_METFrac_chargedEM;
  TBranch *b_METFrac_chargedHad;
  TBranch *b_METFrac_muon;
  TBranch *b_METFrac_type6;
  TBranch *b_METFrac_type7;

  TBranch  *b_GenMETP4;
  TBranch  *b_GenMETTrueP4;
  TBranch  *b_GenMETCaloP4;
  TBranch  *b_GenSumEt;
  TBranch  *b_GenTrueSumEt;
  TBranch  *b_GenCaloSumEt;
  TBranch  *b_GenMETSig;
  TBranch  *b_GenTrueMETSig;
  TBranch  *b_GenCaloMETSig;
  TBranch  *b_GenSignificance;
  TBranch  *b_GenTrueSignificance;
  TBranch  *b_GenCaloSignificance;
    
  //************************************Photon Branches************************************
  TBranch  *b_PhotGenP4;
  TBranch  *b_PhotGenPdgId;
  TBranch  *b_PhotGenStatus;
  TBranch  *b_PhotGenMother;
  TBranch  *b_PhotGenMotherStatus;

  TBranch  *b_PhotonP4;
  TBranch  *b_PhotN;
  TBranch  *b_PhotVeto;

  TBranch  *b_PhotTrkIso;
  TBranch  *b_PhotECalIso;
  TBranch  *b_PhotHCalIso;
  TBranch  *b_PhotAllIso;
  TBranch  *b_PhotPFAllParticleIso;
  TBranch  *b_PhotPFChargedHadronIso;
  TBranch  *b_PhotPFNeutralHadronIso;
  TBranch  *b_PhotPFGammaIso;

  //TBranch  *b_PhotTrkIsoDeposit;
  //TBranch  *b_PhotECalIsoDeposit;
  //TBranch  *b_PhotHCalIsoDeposit;
  //TBranch  *b_PhotPFAllParticleIsoDeposit;
  //TBranch  *b_PhotPFChargedHadronIsoDeposit;
  //TBranch  *b_PhotPFNeutralHadronIsoDeposit;
  //TBranch  *b_PhotPFGammaIsoDeposit;

  TBranch  *b_PhotLoosePhoton;
  TBranch  *b_PhotTightPhoton;

  TBranch  *b_PhotSCEta;
  TBranch  *b_PhotSCPhi;
  TBranch  *b_PhotSCEn;
  TBranch  *b_PhotSCPt;
  TBranch  *b_PhotSCRawE;

  TBranch  *b_PhotTSeed;
  TBranch  *b_PhotESeed;
  TBranch  *b_PhotE2OverE9;
  TBranch  *b_PhotSwissCross;
  TBranch  *b_PhotHadOverEM;
  TBranch  *b_PhotSigmaIetaIeta;

  TBranch  *b_PhotIsEB;
  TBranch  *b_PhotIsEE;
  TBranch  *b_PhotIsEBGap;
  TBranch  *b_PhotIsEEGap;
  TBranch  *b_PhotIsEBEEGap;
  TBranch  *b_PhotHasPixelSeed;
  TBranch  *b_PhotHasConversionTracks;

  //************************************Electron Branches************************************
  TBranch  *b_ElecGenP4;
  TBranch  *b_ElecGenPdgId;
  TBranch  *b_ElecGenStatus;
  TBranch  *b_ElecGenMother;
  TBranch  *b_ElecGenMotherStatus;
    	     
  TBranch  *b_ElecVeto;
  TBranch  *b_ElectronP4;
  TBranch  *b_ElecN;

  TBranch  *b_ElecTrkIso;
  TBranch  *b_ElecECalIso;
  TBranch  *b_ElecHCalIso;
  TBranch  *b_ElecAllIso;
  TBranch  *b_ElecPFAllParticleIso;
  TBranch  *b_ElecPFChargedHadronIso;
  TBranch  *b_ElecPFNeutralHadronIso;
  TBranch  *b_ElecPFGammaIso;

  //TBranch  *b_ElecTrkIsoDeposit;
  //TBranch  *b_ElecECalIsoDeposit;
  //TBranch  *b_ElecHCalIsoDeposit;
  //TBranch  *b_ElecPFAllParticleIsoDeposit;
  //TBranch  *b_ElecPFChargedHadronIsoDeposit;
  //TBranch  *b_ElecPFNeutralHadronIsoDeposit;
  //TBranch  *b_ElecPFGammaIsoDeposit;

  TBranch  *b_ElecdB;
  TBranch  *b_ElecdBerr;
  TBranch  *b_ElecCharge;
  TBranch  *b_ElecHadOverEM;
  TBranch  *b_ElecTrkChiNorm;

  TBranch  *b_ElecIdLoose;
  TBranch  *b_ElecIdTight;
  TBranch  *b_ElecIdRobLoose;
  TBranch  *b_ElecIdRobTight;
  TBranch  *b_ElecIdRobHighE;

  TBranch  *b_ElecE2OverE9;
  TBranch  *b_ElecSwissCross;

  TBranch  *b_ElecE1x5;
  TBranch  *b_ElecE5x5;
  TBranch  *b_ElecE2x5Max;
  TBranch  *b_ElecFbrem;

  TBranch  *b_ElecTSeed;
  TBranch  *b_ElecESeed;
  TBranch  *b_ElecSigmaIetaIeta;

  TBranch  *b_ElecVx;
  TBranch  *b_ElecVy;
  TBranch  *b_ElecVz;
  TBranch  *b_ElecPVDxy;
  TBranch  *b_ElecBSDxy;
  TBranch  *b_ElecDxy;
  TBranch  *b_ElecDxyErr;
  TBranch  *b_ElecD0;
  TBranch  *b_ElecD0Err;
  TBranch  *b_ElecDz;
  TBranch  *b_ElecDzErr;

  TBranch  *b_ElecPtTrk;
  TBranch  *b_ElecPtMode;
  TBranch  *b_ElecChargeMode;
  TBranch  *b_ElecQOverPErrTrkMode;
  TBranch  *b_ElecCaloEnergy;
  TBranch  *b_ElecQOverPErrTrk;
  TBranch  *b_ElecPinTrk;
  TBranch  *b_ElecPoutTrk;
  TBranch  *b_ElecLostHits;
  TBranch  *b_ElecValidHits;
  TBranch  *b_ElecEtaTrk;
  TBranch  *b_ElecPhiTrk;

  TBranch  *b_ElecSCEta;
  TBranch  *b_ElecSCPhi;
  TBranch  *b_ElecSCEn;
  TBranch  *b_ElecSCPt;
  TBranch  *b_ElecSCRawE;
  TBranch  *b_ElecWidthClusterEta;
  TBranch  *b_ElecWidthClusterPhi;
    	     
  //************************************Muon Branches************************************
  TBranch  *b_MuonGenP4;
  TBranch  *b_MuonGenPdgId;
  TBranch  *b_MuonGenStatus;
  TBranch  *b_MuonGenMother;
  TBranch  *b_MuonGenMotherStatus;

  TBranch  *b_MuonVeto;
  TBranch  *b_MuonP4;
  TBranch  *b_MuonN;

  TBranch  *b_MuonCharge;

  TBranch  *b_MuonTrkIso;
  TBranch  *b_MuonECalIso;
  TBranch  *b_MuonHCalIso;
  TBranch  *b_MuonAllIso;
  TBranch  *b_MuonPFAllParticleIso;
  TBranch  *b_MuonPFChargedHadronIso;
  TBranch  *b_MuonPFNeutralHadronIso;
  TBranch  *b_MuonPFGammaIso;

  //TBranch  *b_MuonTrkIsoDeposit;
  //TBranch  *b_MuonECalIsoDeposit;
  //TBranch  *b_MuonHCalIsoDeposit;
  //TBranch  *b_MuonECalIsoDepositR03;
  //TBranch  *b_MuonHCalIsoDepositR03;
  //TBranch  *b_MuonPFAllParticleIsoDeposit;
  //TBranch  *b_MuonPFChargedHadronIsoDeposit;
  //TBranch  *b_MuonPFNeutralHadronIsoDeposit;
  //TBranch  *b_MuonPFGammaIsoDeposit;

  TBranch  *b_MuonIsGlobal;
  TBranch  *b_MuonIsStandAlone;
  TBranch  *b_MuonIsTracker;
  TBranch  *b_MuonGlobalMuonPromptTight;

  TBranch  *b_MuonAllArbitrated;
  TBranch  *b_MuonTrackerMuonArbitrated;
  TBranch  *b_MuonTMLastStationLoose;
  TBranch  *b_MuonTMLastStationTight;
  TBranch  *b_MuonTM2DCompatibilityLoose;
  TBranch  *b_MuonTM2DCompatibilityTight;
  TBranch  *b_MuonTMOneStationLoose;
  TBranch  *b_MuonTMOneStationTight;
  TBranch  *b_MuonTMLastStationOptimizedLowPtLoose;
  TBranch  *b_MuonTMLastStationOptimizedLowPtTight;
  TBranch  *b_MuonGMTkChiCompatibility;
  TBranch  *b_MuonGMStaChiCompatibility;
  TBranch  *b_MuonGMTkKinkTight;
  TBranch  *b_MuonTMLastStationAngLoose;
  TBranch  *b_MuonTMLastStationAngTight;
  TBranch  *b_MuonTMLastStationOptimizedBarrelLowPtLoose;
  TBranch  *b_MuonTMLastStationOptimizedBarrelLowPtTight;
    
  //TBranch  *b_MuonId;

  TBranch  *b_MuonCombVx;
  TBranch  *b_MuonCombVy;
  TBranch  *b_MuonCombVz;
  TBranch  *b_MuonCombPVDxy;
  TBranch  *b_MuonCombBSDxy;
  TBranch  *b_MuonCombDxy;
  TBranch  *b_MuonCombDxyErr;
  TBranch  *b_MuonCombD0;
  TBranch  *b_MuonCombD0Err;
  TBranch  *b_MuonCombDz;
  TBranch  *b_MuonCombDzErr;
  TBranch  *b_MuonCombChi2;
  TBranch  *b_MuonCombNdof;
  TBranch  *b_MuonCombPt;
  TBranch  *b_MuonCombPz;
  TBranch  *b_MuonCombP;
  TBranch  *b_MuonCombEta;
  TBranch  *b_MuonCombPhi;
  TBranch  *b_MuonCombChi;
  TBranch  *b_MuonCombCharge;
  TBranch  *b_MuonCombQOverPErr;
  TBranch  *b_MuonCombValidHits;


  TBranch  *b_MuonStandValidHits;
  TBranch  *b_MuonStandLostHits;
  TBranch  *b_MuonStandPt;
  TBranch  *b_MuonStandPz;
  TBranch  *b_MuonStandP;
  TBranch  *b_MuonStandEta;
  TBranch  *b_MuonStandPhi;
  TBranch  *b_MuonStandCharge;
  TBranch  *b_MuonStandChi;
  TBranch  *b_MuonStandQOverPErr;
    
  TBranch  *b_MuonTrkChiNorm;
  TBranch  *b_MuonTrkValidHits;
  TBranch  *b_MuonTrkLostHits;
  TBranch  *b_MuonTrkPVDxy;
  TBranch  *b_MuonTrkBSDxy;
  TBranch  *b_MuonTrkDxy;
  TBranch  *b_MuonTrkDxyErr;
  TBranch  *b_MuonTrkD0;
  TBranch  *b_MuonTrkD0Err;
  TBranch  *b_MuonTrkDz;
  TBranch  *b_MuonTrkDzErr;
  TBranch  *b_MuonTrkPt;
  TBranch  *b_MuonTrkPz;
  TBranch  *b_MuonTrkP;
  TBranch  *b_MuonTrkEta;
  TBranch  *b_MuonTrkPhi;
  TBranch  *b_MuonTrkChi;
  TBranch  *b_MuonTrkCharge;
  TBranch  *b_MuonTrkQOverPErr;
  TBranch  *b_MuonTrkOuterZ;
  TBranch  *b_MuonTrkOuterR;

//  TBranch  *b_MuonPickyTrkChiNorm;
//  TBranch  *b_MuonPickyCharge;
//  TBranch  *b_MuonPickyTrkValidHits;
//  TBranch  *b_MuonPickyTrkLostHits;
//  TBranch  *b_MuonPickyTrkPVDxy;
//  TBranch  *b_MuonPickyTrkBSDxy;
//  TBranch  *b_MuonPickyTrkDxy;
//  TBranch  *b_MuonPickyTrkDxyErr;
//  TBranch  *b_MuonPickyTrkD0;
//  TBranch  *b_MuonPickyTrkD0Err;
//  TBranch  *b_MuonPickyTrkDz;
//  TBranch  *b_MuonPickyTrkDzErr;
//  TBranch  *b_MuonPickyTrkPt;
//  TBranch  *b_MuonPickyTrkPz;
//  TBranch  *b_MuonPickyTrkP;
//  TBranch  *b_MuonPickyTrkEta;
//  TBranch  *b_MuonPickyTrkPhi;
//  TBranch  *b_MuonPickyTrkChi;
//  TBranch  *b_MuonPickyTrkCharge;
//  TBranch  *b_MuonPickyTrkQOverPErr;
//  TBranch  *b_MuonPickyTrkOuterZ;
//  TBranch  *b_MuonPickyTrkOuterR;
//
//  TBranch  *b_MuonTPFMSTrkChiNorm;
//  TBranch  *b_MuonTPFMSCharge;
//  TBranch  *b_MuonTPFMSTrkValidHits;
//  TBranch  *b_MuonTPFMSTrkLostHits;
//  TBranch  *b_MuonTPFMSTrkPVDxy;
//  TBranch  *b_MuonTPFMSTrkBSDxy;
//  TBranch  *b_MuonTPFMSTrkDxy;
//  TBranch  *b_MuonTPFMSTrkDxyErr;
//  TBranch  *b_MuonTPFMSTrkD0;
//  TBranch  *b_MuonTPFMSTrkD0Err;
//  TBranch  *b_MuonTPFMSTrkDz;
//  TBranch  *b_MuonTPFMSTrkDzErr;
//  TBranch  *b_MuonTPFMSTrkPt;
//  TBranch  *b_MuonTPFMSTrkPz;
//  TBranch  *b_MuonTPFMSTrkP;
//  TBranch  *b_MuonTPFMSTrkEta;
//  TBranch  *b_MuonTPFMSTrkPhi;
//  TBranch  *b_MuonTPFMSTrkChi;
//  TBranch  *b_MuonTPFMSTrkCharge;
//  TBranch  *b_MuonTPFMSTrkQOverPErr;
//  TBranch  *b_MuonTPFMSTrkOuterZ;
//  TBranch  *b_MuonTPFMSTrkOuterR;
 
  //************************************Tau Branches************************************
  TBranch  *b_TauGenP4;
  TBranch  *b_TauGenJetP4;
  TBranch  *b_TauGen;
  TBranch  *b_TauGenPdgId;
  TBranch  *b_TauGenStatus;
  TBranch  *b_TauGenMother;
  TBranch  *b_TauGenMotherStatus;

  TBranch  *b_TauVeto;
  TBranch  *b_TauP4;
  TBranch  *b_TauN;
  TBranch  *b_TauCharge;

  TBranch  *b_TauTrkIso;
  TBranch  *b_TauECalIso;
  TBranch  *b_TauHCalIso;
  TBranch  *b_TauAllIso;
  TBranch  *b_TauPFAllParticleIso;
  TBranch  *b_TauPFChargedHadronIso;
  TBranch  *b_TauPFNeutralHadronIso;
  TBranch  *b_TauPFGammaIso;

  //TBranch  *b_TauTrkIsoDeposit;
  //TBranch  *b_TauECalIsoDeposit;
  //TBranch  *b_TauHCalIsoDeposit;
  //TBranch  *b_TauPFAllParticleIsoDeposit;
  //TBranch  *b_TauPFChargedHadronIsoDeposit;
  //TBranch  *b_TauPFNeutralHadronIsoDeposit;
  //TBranch  *b_TauPFGammaIsoDeposit;

  TBranch  *b_TauVx;
  TBranch  *b_TauVy;
  TBranch  *b_TauVz;
  TBranch  *b_TauPVDxy;
  TBranch  *b_TauBSDxy;
  TBranch  *b_TauDxy;
  TBranch  *b_TauDxyErr;
  TBranch  *b_TauD0;
  TBranch  *b_TauD0Err;
  TBranch  *b_TauDz;
  TBranch  *b_TauDzErr;

  TBranch  *b_TauIdElec;
  TBranch  *b_TauIdMuon;

  TBranch  *b_TauIdIso;
  TBranch  *b_TauIdIsoLeadPi;

  TBranch  *b_TauIdEcalIso;
  TBranch  *b_TauIdEcalIsoLeadPi;

  TBranch  *b_TauIdLeadPiPt;
  TBranch  *b_TauIdLeadTrk;
  TBranch  *b_TauIdLeadTrkPt;

  TBranch  *b_TauIdTrkIso;
  TBranch  *b_TauIdTrkIsoLeadPi;

  TBranch  *b_TauIdNCfrFull;
  TBranch  *b_TauIdNCfrHalf;
  TBranch  *b_TauIdNCfrTenth;
  TBranch  *b_TauIdNCfrQuarter;

  TBranch  *b_TauCaloLeadTrkSignedIP      ;
  TBranch  *b_TauCaloLeadTrkHcal3x3EtSum  ;
  TBranch  *b_TauCaloLeadTrkHcal3x3HotDEta;
  TBranch  *b_TauCaloSignalTrkMInv        ;
  TBranch  *b_TauCaloTrkMInv              ;
  TBranch  *b_TauCaloIsoTrkPtSum          ;
  TBranch  *b_TauCaloIsoEcalEtSum         ;
  TBranch  *b_TauCaloMaxEtHCAL            ;

  TBranch  *b_TauPFIsoChargedHadPtSum;
  TBranch  *b_TauPFIsoGammaEtSum     ;
  TBranch  *b_TauPFHcalClusterMaxEt  ;
  TBranch  *b_TauPFEFrac_em          ;
  TBranch  *b_TauPFHcalTotalOverPLead;
  TBranch  *b_TauPFHcalMaxOverPLead  ;
  TBranch  *b_TauPFHcal3x3OverPLead  ;
  TBranch  *b_TauPFEcalStripOverPLead;
  TBranch  *b_TauPFBremRecOverPLead  ;
  TBranch  *b_TauPFElePreIDOut       ;
  TBranch  *b_TauPFMuonCaloComp      ;
  TBranch  *b_TauPFMuonSegComp       ;

  TBranch  *b_TauEtaEtaMom;
  TBranch  *b_TauPhiPhiMom;
  TBranch  *b_TauEtaPhiMom;
  //************************************Beamspot Branches************************************
  TBranch  *b_beamspotX0;
  TBranch  *b_beamspotY0;
  TBranch  *b_beamspotZ0;
  TBranch  *b_beamspotX0Err;
  TBranch  *b_beamspotY0Err;
  TBranch  *b_beamspotZ0Err;
  TBranch  *b_beamspotWidthX;
  TBranch  *b_beamspotWidthY;
  TBranch  *b_beamspotWidthXErr;
  TBranch  *b_beamspotWidthYErr;
  TBranch  *b_beamspotdxdz;
  TBranch  *b_beamspotdydz;
  TBranch  *b_beamspotdxdzErr;
  TBranch  *b_beamspotdydzErr;
  TBranch  *b_beamspotSigmaZ0;
  TBranch  *b_beamspotSigmaZ0Err;
  TBranch  *b_beamspotEmittanceX;
  TBranch  *b_beamspotEmittanceY;
  TBranch  *b_beamspotBetaStar;
    	     
  //************************************Vertex Branches************************************
  TBranch  *b_nVtx;
  TBranch  *b_VertexIsValid;
  TBranch  *b_VertexChi2;
  TBranch  *b_VertexNdof;
  TBranch  *b_VertexNTrks;
  TBranch  *b_VertexNRawTrks;
  TBranch  *b_VertexSumTrkPt;
  TBranch  *b_VertexSumTrkPt2;
  TBranch  *b_VertexNormalizedChi2;
  TBranch  *b_VertexX;
  TBranch  *b_VertexY;
  TBranch  *b_VertexZ;
  TBranch  *b_Vertexd0;
  TBranch  *b_VertexdX;
  TBranch  *b_VertexdY;
  TBranch  *b_VertexdZ;
    	     
  /************************************Jet Branches************************************/
  /*
    TBranch  *b_MPTPhi;
    TBranch  *b_MPTPx;
    TBranch  *b_MPTPy;
    TBranch  *b_MPTPz;
  */
  //************************************Trigger Branches************************************
  TBranch  *b_HLTTriggered;
  TBranch  *b_HLTPrescaled;
    
  //************************************Gen Particle Branches************************************
  TBranch  *b_genParticleN;
  TBranch  *b_genParticleP4;
  TBranch  *b_genParticleId;
  TBranch  *b_genParticleStatus;
  TBranch  *b_genParticleMother;
  TBranch  *b_genParticleDaughters;

  TBranch  *b_genN;
  TBranch  *b_genP4;
  TBranch  *b_genId;
  TBranch  *b_genStatus;
  TBranch  *b_genMother;
  TBranch  *b_genDaughters;

  TBranch  *b_pthat;
  //////////****************************End of branch pointers ****************************

  ///
  ntupleAnalysisPAT(TTree *allTree,
		    //TTree *eventTree,
		    TTree *jetTree,
		    TTree *metTree, 
		    TTree *leptonTree,
		    TTree *photonTree, 
		    TTree *triggerTree,
		    TTree *vertexTree, 
		    //TTree *trackTree,
		    TTree *genTree, 
		    std::string* sampleList=0,
		    std::string* triggerList=0,
		    std::string* cutFile=0,
		    const bool &fromData=false,
		    const std::string &jetPrefix="PF2PAT",
		    const std::string &metPrefix="PFTypeI",
		    const std::string &lepPrefix="PF",
		    const std::string &phtPrefix="",
		    const std::string &sampleKey="");

  virtual ~ntupleAnalysisPAT();
    
  virtual Int_t    Cut(Long64_t entry);
    
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *allTree,
			//TTree *eventTree,
			TTree *jetTree,
			TTree *metTree, 
			TTree *leptonTree,
			TTree *photonTree, 
			TTree *triggerTree,
			TTree *vertexTree,
			//TTree *trackTree,
			TTree *genTree
			);
  virtual Bool_t   Notify();
    
  virtual sampleInfo ReadInCrossSections(std::string* efficiencyFile_, std::string sampleKey_);
  virtual void       ReadInTriggers();
  virtual void       ReadInCuts();
  std::pair<int, std::string> split(const std::string& s);

  virtual void     Show(Long64_t entry = -1);
  
  //Special functions
  //Bool_t   goodMuonTag(  const int& index, const int& mode=1);
  //Bool_t   goodMuonProbe(const int& index, const int& mode=1, const int& charge=1);
  //  
  //Bool_t   goodElectronTag(const int& index, const int& mode=1);
  //Bool_t   goodElectronProbe(const int& index, const int& mode=1, const int& charge=1);
  //
  //Bool_t   goodPhotonTag(const int& index, const int& mode=1);
  //Bool_t   goodPhotonProbe(const int& index, const int& mode=1, const int& charge=1);
  //
  //Object identification
  Bool_t   vertexIsPrimary( const int& index);
  Bool_t   jetID(     const int& index, const bool& tight=false);
  Bool_t   muonID(    const int& index);
  //Bool_t   tauID(    const int& index);
  Bool_t   electronID(const int& index, const bool& tight=false);
  Bool_t   photonID(  const int& index, const bool& tight=false);
  

  //Object Definitions
  Double_t       computeHT(const double& minpt, const double& maxeta,
			   const LorentzP4Vs& theJets,
			   const bool& useJetID);
  TLorentzVector computeMHT(const double& minpt, const double& maxeta,
			    const LorentzP4Vs& theJets,
			    const bool& useJetID);
  Double_t       computeDPhiStar(const TLorentzVector& mht,
				 const double& minpt, const double& maxeta,
				 const LorentzP4Vs& theJets,
				 const bool& useJetID);

  Double_t       computeMinDPhi(const double& minpt,
				const LorentzP4Vs& theJets,
				const LorentzP4V& theMET);
  Double_t       computeMinDPhi(const double& minpt,
				const LorentzP4Vs& theJets,
				const double& metphi);

  //Commonly useful functions
  Double_t       computeDPhi(const double& phiObj1, const double& phiObj2);
  Double_t       computeDPhi(const LorentzP4V& obj1,
			     const LorentzP4V& obj2);

  Double_t       computeDR(const double& phiObj1, const double& etaObj1,
			   const double& phiObj2, const double& etaObj2);
  Double_t       computeDR(const LorentzP4V& obj1,
			   const LorentzP4V& obj2);
  
    

  //friend class commonFunctions;

  Double_t luminosity_, scale_, cross_section_, efficiency_, generated_events_;
  std::string outfilename_;
  std::string infilename_;
  std::string jetPrefix_;
  std::string metPrefix_;
  std::string lepPrefix_;
  std::string phtPrefix_;
  std::string analysisVer_;
  
  std::string* cutFile_;
  std::string* triggerList_;
  std::string* sampleList_;

  std::map<unsigned int,std::string> dijetTriggers;
  std::map<unsigned int,std::string> singlejetTriggers;
  std::map<unsigned int,std::string> metTriggers;
  std::map<unsigned int,std::string> muonTriggers;
  std::map<unsigned int,std::string> electronTriggers;
  std::map<unsigned int,std::string> photonTriggers;

  bool isData_;

    
  //private :
  virtual void setIsolationParameters();

 public:
  int electron_minhits;
  double electron_minpt;
  double electron_maxpt;
  double electron_noniso;
  double electron_maxeta;
  double electron_maxreliso;
  double electron_maxd0;
  double electron_maxchi2;
    
  int muon_minhits;
  double muon_minpt;
  double muon_maxpt;
  double muon_noniso;
  double muon_maxeta;
  double muon_maxreliso;
  double muon_maxd0;
  double muon_maxchi2;
    
  double photon_minpt     ;
  double photon_maxpt     ;
  double photon_maxeta    ;
  double photon_maxreliso ;
  double photon_maxhoverem   ;
  double photon_maxe2overe9  ;
  double photon_sigieiereqEB ;
  double photon_sigieiereqEE ;


};

#endif

#ifdef ntupleAnalysisPAT_cxx

ntupleAnalysisPAT::ntupleAnalysisPAT(TTree *allTree,
				     //TTree *eventTree,
				     TTree *jetTree,
				     TTree *metTree, 
				     TTree *leptonTree,
				     TTree *photonTree, 
				     TTree *triggerTree,
				     TTree *vertexTree, 
				     //TTree *trackTree,
				     TTree *genTree, 
				     std::string * sampleList,
				     std::string * triggerList,
				     std::string * cutFile,
				     const bool &fromData, //can get from data ntuple?
				     const std::string &jetPrefix, 
				     const std::string &metPrefix, 
				     const std::string &lepPrefix, 
				     const std::string &phtPrefix,
				     const std::string &sampleKey ) {
  
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  bool debug = false;
  if (debug) std::cout<<"Executing ntupleAnalysisPAT::ntupleAnalysisPAT()"<<std::endl;
  if (allTree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    if (!f) {
      f = new TFile("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    }
    allTree     = (TTree*)gDirectory->Get("analysisNtuplePAT/AllData");
    //if (gDirectory->Get("analysisNtuplePAT/EventData"))
    //  eventTree   = (TTree*)gDirectory->Get("analysisNtuplePAT/EventData");
    jetTree     = (TTree*)gDirectory->Get("analysisNtuplePAT/JetData");
    metTree     = (TTree*)gDirectory->Get("analysisNtuplePAT/METData");
    leptonTree  = (TTree*)gDirectory->Get("analysisNtuplePAT/LeptonData");
    photonTree  = (TTree*)gDirectory->Get("analysisNtuplePAT/PhotonData");
    triggerTree = (TTree*)gDirectory->Get("analysisNtuplePAT/TriggerData");
    vertexTree  = (TTree*)gDirectory->Get("analysisNtuplePAT/VertexData");
    //trackTree   = (TTree*)gDirectory->Get("analysisNtuplePAT/TrackData");
    //be careful, this tree doesn't necessarily exist
    //if (gDirectory->Get("analysisNtuplePAT/GenParticleData"))
    if (!isData_)
      genTree     = (TTree*)gDirectory->Get("analysisNtuplePAT/GenParticleData");
  }
  if (debug)std::cout<<"allTree::"    <<allTree    <<std::endl;
  if (debug)std::cout<<"jetTree::"    <<jetTree    <<std::endl;
  if (debug)std::cout<<"metTree::"    <<metTree    <<std::endl;
  if (debug)std::cout<<"leptonTree::" <<leptonTree <<std::endl;
  if (debug)std::cout<<"photonTree::" <<photonTree <<std::endl;
  if (debug)std::cout<<"triggerTree::"<<triggerTree<<std::endl;
  if (debug)std::cout<<"vertexTree::" <<vertexTree <<std::endl;
  if (debug)std::cout<<"genTree::"    <<genTree<<std::endl;
  //if (debug)std::cout<<"eventTree::"  <<eventTree<<std:endl;
  /*
////Read in the cross-section/efficiency information
sampleList_ = sampleList;
sampleInfo sampVals = ReadInCrossSections(sampleList_,sampleKey);

if (isData) {
sampVals.xs      = 1.;
sampVals.eff     = 1.;
sampVals.numGen  = 1.;
}

sampVals.lumi = 35.;
sampVals.scale = 1.;

if (!isData)
sampVals.scale = sampVals.lumi * sampVals.xs * sampVals.eff / sampVals.numGen;

scale_            = sampVals.scale;
luminosity_       = sampVals.lumi;
cross_section_    = sampVals.xs;
efficiency_       = sampVals.eff;
generated_events_ = sampVals.numGen;
  

//Read in the trigger information
triggerList_ = triggerList;
ReadInTriggers();
//read in the cuts
cutFile_     = cutFile;
ReadInCuts();
setCuts();
  */
  setIsolationParameters();
  //running on data/mc
  isData_      = fromData;
  //set the data labels
  jetPrefix_ = jetPrefix;
  metPrefix_ = metPrefix;
  lepPrefix_ = lepPrefix;
  phtPrefix_ = phtPrefix;

  if (debug) std::cout<<"jetPrefix = "<<jetPrefix<<" or jetPrefix_ = "<<jetPrefix_<<std::endl;
  if (debug) std::cout<<"metPrefix = "<<metPrefix<<" or metPrefix_ = "<<metPrefix_<<std::endl;
  if (debug) std::cout<<"lepPrefix = "<<lepPrefix<<" or lepPrefix_ = "<<lepPrefix_<<std::endl;
  if (debug) std::cout<<"phtPrefix = "<<phtPrefix<<" or phtPrefix_ = "<<phtPrefix_<<std::endl;

  //Initialize the tree
  Init(allTree,
       //eventTree,
       jetTree,
       metTree,
       leptonTree,
       photonTree,
       triggerTree,
       vertexTree,
       //trackTree,
       genTree);
}

ntupleAnalysisPAT::~ntupleAnalysisPAT() {
  if (!allChain) return;
  delete allChain    ->GetCurrentFile();
  //if (eventChain)
  //  delete eventChain->GetCurrentFile();
  delete jetChain    ->GetCurrentFile();
  delete metChain    ->GetCurrentFile();
  delete leptonChain ->GetCurrentFile();
  delete photonChain ->GetCurrentFile();
  delete triggerChain->GetCurrentFile();
  delete vertexChain ->GetCurrentFile();
  //delete trackChain  ->GetCurrentFile();
  if (!isData_)
    delete genChain  ->GetCurrentFile();

  //delete allChain    ;
  ////if (eventChain)
  ////  delete eventChain;
  //delete jetChain    ;
  //delete metChain    ;
  //delete leptonChain ;
  //delete photonChain ;
  //delete triggerChain;
  //delete vertexChain ;
  ////delete trackChain  ;
  ////if (genChain)
  ////  delete genChain  ;
}

void ntupleAnalysisPAT::setIsolationParameters() {

  electron_minpt     = 8.0;
  electron_maxpt     = 10.0;
  electron_noniso    = 0.5;
  electron_maxeta    = 2.4;
  electron_minhits   = 10;
  electron_maxreliso = 0.5;
  electron_maxd0     = 0.2;
  electron_maxchi2   = 10.0;
  //eidLoose;

  muon_minpt     = 8.0;
  muon_maxpt     = 10.0;
  muon_noniso    = 0.5;
  muon_maxeta    = 2.4;
  muon_minhits   = 10;
  muon_maxreliso = 0.1;
  muon_maxd0     = 0.2;
  muon_maxchi2   = 10.0;
  //GlobalMuonPromptTight
  //GlobalMuon
  //                            //loose       tight       QCD       EXO/SUS       HIG->yy
  photon_minpt          = 10.0; //
  photon_maxpt          = 10.0; //
  photon_maxeta         = 2.5;  //
  photon_maxreliso      = 0.1;  //
  photon_maxhoverem     = 0.05; //0.05        0.03        0.05       0.05          0.02
  photon_maxe2overe9    = 0.95; //0.95        0.95        0.95       0.95          0.95
  photon_sigieiereqEB   = 0.013;//0.01        0.01        0.01       0.013         0.01
  photon_sigieiereqEE   = 0.03; //0.03        0.028       0.03       0.03          0.028

  return;
}

void ntupleAnalysisPAT::ReadInTriggers() {
  bool debug = false;
  std::string s;
  if (!triggerList_) {
    if (debug) std::cout<<" no trigger list specified"<<std::endl;
    return;
  }

  if (debug) std::cout<<"Reading in trigger list"<<std::endl;

  char path1[MAXPATHLEN]; // This is a buffer for the text
  getcwd(path1, MAXPATHLEN);
  std::string cwd(path1);
  std::cout<<"pwd = "<<cwd<<std::endl;
  
  ifstream is(triggerList_->c_str());
  std::map<unsigned int,std::string> theTriggers;
  if(is.good()) {
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;
	if (s[0] == '!') {
	  //read in the rest of the line to figure out which trigger is next
	  if (s.find("dijet")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      dijetTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("singlejet")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      singlejetTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("met")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      metTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("muon")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      muonTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("electron")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      electronTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("photon")!=std::string::npos) {
	    std::map<unsigned int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      photonTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  theTriggers.clear();
	  
	}
	else {
	  std::pair<int, std::string> trigs = split(s);
	  theTriggers[trigs.first] = trigs.second;
	}
      }
  }
  
  std::map<unsigned int,std::string>::iterator key = dijetTriggers.begin();
  while (key!= dijetTriggers.end()) {
    std::cout<<"dijetTriggers["<<key->first<<"] = "<<key->second<<std::endl;
    ++key;
  }
  key = singlejetTriggers.begin();
  while (key!= singlejetTriggers.end()) {
    std::cout<<"singlejetTriggers["<<key->first<<"] = "<<key->second<<std::endl;
    ++key;
  }
  key = metTriggers.begin();
  while (key!= metTriggers.end()) {
    std::cout<<"metTriggers["<<key->first<<"] = "<<key->second<<std::endl;
    ++key;
  }
  //key = muonTriggers.begin();
  //while (key!= muonTriggers.end()) {
  //  std::cout<<"muonTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
  //key = electronTriggers.begin();
  //while (key!= electronTriggers.end()) {
  //  std::cout<<"electronTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
	
  return;
}

void ntupleAnalysisPAT::ReadInCuts() {
  std::string s;
  bool debug = false;
  if (!cutFile_) {
    std::cout<<" no cut file specified"<<std::endl;
    return;
  }

  if (debug) std::cout<<"Reading in cut file"<<std::endl;
  char path1[MAXPATHLEN]; // This is a buffer for the text
  getcwd(path1, MAXPATHLEN);
  std::string cwd(path1);
  std::cout<<"pwd = "<<cwd<<std::endl;
  
  ifstream is(cutFile_->c_str());
  if(is.good()) {
    std::cout<<"opened "<<cutFile_->c_str()<<std::endl;
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;
	
      }
  }
  return;
}

sampleInfo ntupleAnalysisPAT::ReadInCrossSections(std::string* efficiencyFile_,std::string sampleKey)
{
  sampleInfo returnVal;
  std::string s;
  bool debug = false;
  if (!efficiencyFile_) {
    std::cout<<"ERROR no efficiency file specified, exiting"<<std::endl;
    exit(1);
  }
  bool matched = false;
  if (debug) std::cout<<"Reading in efficiency file "<<efficiencyFile_->c_str()<<std::endl;
  char path1[MAXPATHLEN]; // This is a buffer for the text
  getcwd(path1, MAXPATHLEN);
  std::string cwd(path1);
  std::cout<<"pwd = "<<cwd<<std::endl;
  
  ifstream is(efficiencyFile_->c_str());
  if(is.good()) {
    std::cout<<"opened "<<efficiencyFile_->c_str()<<std::endl;
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;

	if (s.find(sampleKey)!=std::string::npos) {
	  matched = true;
	  //Line format is sample name - gen events - cross section - efficiency   - note
	  //                           - int/long   - double/double  - double/double - note
	  std::vector<std::string> line;
	  std::string::size_type i =0;
	  while (i != s.size()){
	    while (i != s.size() && isspace(s[i]))
	      ++i;
	    std::string::size_type j = i;
	    while (j != s.size() && !isspace(s[j]) && &(s[j])!="-")
	      ++j;
	    if (i != j){
	      if (debug) std::cout<<"pushing back "<<s.substr(i, j -i)<<std::endl;
	      line.push_back(s.substr(i, j -i));
	      i = j;
	    }
	  }
	  returnVal.numGen  = atof(line[2].c_str());
	  returnVal.xs      = atof(line[4].c_str());
	  returnVal.eff     = atof(line[6].c_str());
	  return returnVal;
	}
      }
  }
  else {
    std::cout<<"ERROR opening "<<efficiencyFile_->c_str()<<" exiting!"<<std::endl;
    exit(1);
  }
  
  std::cout<<"Unable to find sample "<<sampleKey<<" in "<<efficiencyFile_->c_str()<<" exiting!"<<std::endl;
  exit(1);
  //return returnVal;
}


std::pair<int, std::string> ntupleAnalysisPAT::split(const std::string& s) {
  std::pair<int,std::string> value;
  std::vector<std::string> ret;
  std::string::size_type i =0;
  while (i != s.size()){
    while (i != s.size() && isspace(s[i]))
      ++i;
    std::string::size_type j = i;
    while (j != s.size() && !isspace(s[j]))
      ++j;
    if (i != j){
      ret.push_back(s.substr(i, j -i));
      i = j;
    }
  }
  int runNum;
  std::stringstream ss (ret.at(0));
  ss>>runNum;
  value.first  = runNum;
  value.second = ret.at(1);
  
  return value;
}

Int_t ntupleAnalysisPAT::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!allChain) return 0;
  Int_t   entryGotten = -1;
  entryGotten = allChain    ->GetEntry(entry);
  //if (eventChain)
  //  entryGotten += eventChain  ->GetEntry(entry);
  entryGotten += jetChain    ->GetEntry(entry);
  entryGotten += metChain    ->GetEntry(entry);
  entryGotten += leptonChain ->GetEntry(entry);
  entryGotten += photonChain ->GetEntry(entry);
  entryGotten += triggerChain->GetEntry(entry);
  entryGotten += vertexChain ->GetEntry(entry);
  //entryGotten += trackChain  ->GetEntry(entry);
  if (!isData_)
    entryGotten += genChain    ->GetEntry(entry);

  return entryGotten;
}

Long64_t ntupleAnalysisPAT::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!allChain) return -5;
  Long64_t centry = 0;
  centry += allChain->LoadTree(entry);
  //allChain    ->LoadTree(entry);
  //if (eventChain)
  //centry += eventChain  ->LoadTree(entry);
  centry += jetChain    ->LoadTree(entry);
  centry += metChain    ->LoadTree(entry);
  centry += leptonChain ->LoadTree(entry);
  centry += photonChain ->LoadTree(entry);
  centry += triggerChain->LoadTree(entry);
  centry += vertexChain ->LoadTree(entry);
  //centry += trackChain  ->LoadTree(entry);
  if (!isData_)
    centry += genChain    ->LoadTree(entry);

  if (centry < 0) return centry;
  if (!allChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)allChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ntupleAnalysisPAT::Init(TTree *allTree,
			     //TTree *eventTree,
			     TTree *jetTree,
			     TTree *metTree, 
			     TTree *leptonTree,
			     TTree *photonTree, 
			     TTree *triggerTree,
			     TTree *vertexTree,
			     //TTree *trackTree,
			     TTree *genTree
			     ) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  doSusyScan = false;

  //Set pointers
  MHtP4    = 0;
  JetP4    = 0;
  RawJetP4 = 0;

  JetIDMinimal  = 0;
  JetIDLoose    = 0;
  JetIDTight    = 0;
    
  JetEtaEtaMoment = 0;
  JetEtaPhiMoment = 0;
  JetPhiPhiMoment = 0;
  
  JetCorrectionFactor      = 0;
  JetCorrectionFactorUnc   = 0;
  JetCorrectionFactorL1    = 0;
  JetCorrectionFactorL2    = 0;
  JetCorrectionFactorL3    = 0;
  JetCorrectionFactorL2L3  = 0;
  JetCorrectionFactorL5uds = 0;
  JetCorrectionFactorL5c   = 0;
  JetCorrectionFactorL5b   = 0;
  JetCorrectionFactorL5glu = 0;
  JetCorrectionFactorL7uds = 0;
  JetCorrectionFactorL7c   = 0;
  JetCorrectionFactorL7b   = 0;
  JetCorrectionFactorL7glu = 0;
  
  JECUncPlus  = 0;
  JECUncMinus = 0;
  
  JetElectronOverlaps  = 0;
  JetElectronNOverlaps = 0;
  JetMuonOverlaps      = 0;
  JetMuonNOverlaps     = 0;
  JetTauOverlaps       = 0;
  JetTauNOverlaps      = 0;
  JetPhotonOverlaps    = 0;
  JetPhotonNOverlaps   = 0;
  
  JetCharge     = 0;
  JetNConst     = 0;

  JetfHPD             = 0;
  JetfRBX             = 0;
  Jetn90              = 0;

  JetTrackPt          = 0;
  JetTrackPhi         = 0;
  JetTrackPhiWeighted = 0;
  JetTrackNo          = 0;
    
  //Energy fractions
  JetEFrac_em       = 0;
  JetEFrac_had      = 0;
  JetEFrac_muon     = 0;
  JetEFrac_photon   = 0;
  JetEFrac_electron = 0;

  JetChargedFrac_em   = 0;
  JetChargedFrac_had  = 0;
  JetChargedFrac_muon = 0;
  JetNeutralFrac_em   = 0;
  JetNeutralFrac_had  = 0;

  JetHFFrac_em      = 0;
  JetHFFrac_had     = 0;

  //Energy
  JetEn_em       = 0;
  JetEn_had      = 0;
  JetEn_muon     = 0;
  JetEn_photon   = 0;
  JetEn_electron = 0;

  JetChargedEn_em   = 0;
  JetChargedEn_had  = 0;
  JetChargedEn_muon = 0;
  JetNeutralEn_em   = 0;
  JetNeutralEn_had  = 0;

  JetHFEn_em        = 0;
  JetHFEn_had       = 0;

  //Multiplicities
  JetMuonMulti     = 0;
  JetPhotonMult    = 0;
  JetElectronMulti = 0;
  JetChargedMult   = 0;
  JetNeutralMult   = 0;

  JetHFMult_had      = 0;
  JetHFMult_em       = 0;
  JetNeutralMult_had = 0;
  JetChargedMult_had = 0;

  JetBTag_TCHE           = 0;
  JetBTag_TCHP           = 0;
  JetBTag_jetProb        = 0;
  JetBTag_jetBProb       = 0;
  JetBTag_SSVHE          = 0;
  JetBTag_SSVHP          = 0;
  JetBTag_CSV            = 0;
  JetBTag_CSVMVA         = 0;
  JetBTag_SoftLepton     = 0;
  JetBTag_SoftLeptonByIP = 0;
  JetBTag_SoftLeptonByPt = 0;
    
  GenJetP4    = 0;
  JetPartonP4 = 0;

  GenMHtP4 = 0;
    
  JetPartonId      = 0;
  JetPartonStatus  = 0;
  JetPartonMother  = 0;
  JetPartonMotherStatus  = 0;
  JetPartonFlavour = 0;

  //MET
  METP4        = 0;

  GenMETP4     = 0;
  GenMETTrueP4 = 0;
  GenMETCaloP4 = 0;

  //Photons
  PhotonP4  = 0;
  PhotGenP4 = 0;

  PhotGenPdgId        = 0;
  PhotGenStatus       = 0;
  PhotGenMother       = 0;
  PhotGenMotherStatus = 0;

  PhotTrkIso             = 0;
  PhotECalIso            = 0;
  PhotHCalIso            = 0;
  PhotAllIso             = 0;
  PhotPFAllParticleIso   = 0;
  PhotPFChargedHadronIso = 0;
  PhotPFNeutralHadronIso = 0;
  PhotPFGammaIso         = 0;

  //PhotTrkIsoDeposit             = 0;
  //PhotECalIsoDeposit            = 0;
  //PhotHCalIsoDeposit            = 0;
  //PhotPFAllParticleIsoDeposit   = 0;
  //PhotPFChargedHadronIsoDeposit = 0;
  //PhotPFNeutralHadronIsoDeposit = 0;
  //PhotPFGammaIsoDeposit         = 0;

  PhotLoosePhoton = 0;
  PhotTightPhoton = 0;

  PhotSCEta  = 0;
  PhotSCPhi  = 0;
  PhotSCEn   = 0;
  PhotSCPt   = 0;
  PhotSCRawE = 0;

  PhotTSeed     = 0;
  PhotESeed     = 0;
  PhotE2OverE9            = 0;
  PhotSwissCross          = 0;
  PhotHadOverEM           = 0;
  PhotSigmaIetaIeta       = 0;

  PhotIsEB                = 0;
  PhotIsEE                = 0;
  PhotIsEBGap             = 0;
  PhotIsEEGap             = 0;
  PhotIsEBEEGap           = 0;
  PhotHasPixelSeed        = 0;
  PhotHasConversionTracks = 0;

  //Electrons
  ElectronP4 = 0;
  ElecGenP4  = 0;

  ElecGenPdgId        = 0;
  ElecGenStatus       = 0;
  ElecGenMother       = 0;
  ElecGenMotherStatus = 0;

  ElecCharge     = 0;
  ElecHadOverEM  = 0;
  ElecTrkIso     = 0;
  ElecECalIso    = 0;
  ElecHCalIso    = 0;
  ElecAllIso     = 0;
  ElecPFAllParticleIso   = 0;
  ElecPFChargedHadronIso = 0;
  ElecPFNeutralHadronIso = 0;
  ElecPFGammaIso         = 0;

  //ElecTrkIsoDeposit             = 0;
  //ElecECalIsoDeposit            = 0;
  //ElecHCalIsoDeposit            = 0;
  //ElecPFAllParticleIsoDeposit   = 0;
  //ElecPFChargedHadronIsoDeposit = 0;
  //ElecPFNeutralHadronIsoDeposit = 0;
  //ElecPFGammaIsoDeposit         = 0;

  ElecdB         = 0;
  ElecdBerr      = 0;
  ElecCharge     = 0;
  ElecTrkChiNorm = 0;

  ElecIdLoose    = 0;
  ElecIdTight    = 0;
  ElecIdRobLoose = 0;
  ElecIdRobTight = 0;
  ElecIdRobHighE = 0;

  ElecE2OverE9      = 0;
  ElecSwissCross    = 0;

  ElecE1x5    = 0;
  ElecE5x5    = 0;
  ElecE2x5Max = 0;
  ElecFbrem   = 0;
  ElecTSeed   = 0;
  ElecESeed   = 0;
  ElecSigmaIetaIeta = 0;

  ElecVx     = 0;
  ElecVy     = 0;
  ElecVz     = 0;
  ElecPVDxy  = 0;
  ElecBSDxy  = 0;
  ElecDxy    = 0;
  ElecDxyErr = 0;
  ElecD0     = 0;
  ElecD0Err  = 0;
  ElecDz     = 0;
  ElecDzErr  = 0;

  ElecPtTrk           = 0;
  ElecPtMode           = 0;
  ElecChargeMode       = 0;
  ElecQOverPErrTrkMode = 0;
  ElecCaloEnergy    = 0;
  ElecQOverPErrTrk  = 0;
  ElecPinTrk    = 0;
  ElecPoutTrk   = 0;
  ElecLostHits  = 0;
  ElecValidHits = 0;
  ElecEtaTrk    = 0;
  ElecPhiTrk    = 0;

  ElecSCEta           = 0;
  ElecSCPhi           = 0;
  ElecSCEn            = 0;
  ElecSCPt            = 0;
  ElecSCRawE          = 0;
  ElecWidthClusterEta = 0;
  ElecWidthClusterPhi = 0;


  //Muons
  MuonP4        = 0;
  MuonGenP4     = 0;

  MuonGenPdgId        = 0;
  MuonGenStatus       = 0;
  MuonGenMother       = 0;
  MuonGenMotherStatus = 0;

  MuonCharge       = 0;
 
  MuonTrkIso         = 0;
  MuonECalIso        = 0;
  MuonHCalIso        = 0;
  MuonAllIso         = 0;
  MuonPFAllParticleIso   = 0;
  MuonPFChargedHadronIso = 0;
  MuonPFNeutralHadronIso = 0;
  MuonPFGammaIso         = 0;

  //MuonTrkIsoDeposit         = 0;
  //MuonECalIsoDeposit        = 0;
  //MuonHCalIsoDeposit        = 0;
  //MuonPFAllParticleIsoDeposit   = 0;
  //MuonPFChargedHadronIsoDeposit = 0;
  //MuonPFNeutralHadronIsoDeposit = 0;
  //MuonPFGammaIsoDeposit         = 0;
  //MuonECalIsoDepositR03 = 0;
  //MuonHCalIsoDepositR03 = 0;
    
  MuonIsGlobal                               = 0;
  MuonIsStandAlone                           = 0;
  MuonIsTracker                              = 0;
  MuonGlobalMuonPromptTight                  = 0;
  MuonAllArbitrated                          = 0;
  MuonTrackerMuonArbitrated                  = 0;
  MuonTMLastStationLoose                     = 0;
  MuonTMLastStationTight                     = 0;
  MuonTM2DCompatibilityLoose                 = 0;
  MuonTM2DCompatibilityTight                 = 0;
  MuonTMOneStationLoose                      = 0;
  MuonTMOneStationTight                      = 0;
  MuonTMLastStationOptimizedLowPtLoose       = 0;
  MuonTMLastStationOptimizedLowPtTight       = 0;
  MuonGMTkChiCompatibility                   = 0;
  MuonGMStaChiCompatibility                  = 0;
  MuonGMTkKinkTight                          = 0;
  MuonTMLastStationAngLoose                  = 0;
  MuonTMLastStationAngTight                  = 0;
  MuonTMLastStationOptimizedBarrelLowPtLoose = 0;
  MuonTMLastStationOptimizedBarrelLowPtTight = 0;
    
  MuonCombVx        = 0;
  MuonCombVy        = 0;
  MuonCombVz        = 0;
  MuonCombPVDxy     = 0;
  MuonCombBSDxy     = 0;
  MuonCombDxy       = 0;
  MuonCombDxyErr    = 0;
  MuonCombD0        = 0;
  MuonCombD0Err     = 0;
  MuonCombDz        = 0;
  MuonCombDzErr     = 0;
  MuonCombChi2      = 0;
  MuonCombNdof      = 0;
  MuonCombPt        = 0;
  MuonCombPz        = 0;
  MuonCombP         = 0;
  MuonCombEta       = 0;
  MuonCombPhi       = 0;
  MuonCombChi       = 0;
  MuonCombCharge    = 0;
  MuonCombQOverPErr = 0;
  MuonCombValidHits = 0;

  MuonStandValidHits = 0;
  MuonStandLostHits  = 0;
  MuonStandPt        = 0;
  MuonStandPz        = 0;
  MuonStandP         = 0;
  MuonStandEta       = 0;
  MuonStandPhi       = 0;
  MuonStandCharge    = 0;
  MuonStandChi       = 0;
  MuonStandQOverPErr = 0;
    
  MuonTrkChiNorm   = 0;
  MuonTrkValidHits = 0;
  MuonTrkLostHits  = 0;
  MuonTrkPVDxy     = 0;
  MuonTrkBSDxy     = 0;
  MuonTrkDxy       = 0;
  MuonTrkDxyErr    = 0;
  MuonTrkD0        = 0;
  MuonTrkD0Err     = 0;
  MuonTrkDz        = 0;
  MuonTrkDzErr     = 0;
  MuonTrkPt        = 0;
  MuonTrkPz        = 0;
  MuonTrkP         = 0;
  MuonTrkEta       = 0;
  MuonTrkPhi       = 0;
  MuonTrkChi       = 0;
  MuonTrkCharge    = 0;
  MuonTrkQOverPErr = 0;
  MuonTrkOuterZ    = 0;
  MuonTrkOuterR    = 0;

//  MuonPickyTrkChiNorm   = 0;
//  MuonPickyCharge       = 0;
//  MuonPickyTrkValidHits = 0;
//  MuonPickyTrkLostHits  = 0;
//  MuonPickyTrkPVDxy     = 0;
//  MuonPickyTrkBSDxy     = 0;
//  MuonPickyTrkDxy       = 0;
//  MuonPickyTrkDxyErr    = 0;
//  MuonPickyTrkD0        = 0;
//  MuonPickyTrkD0Err     = 0;
//  MuonPickyTrkDz        = 0;
//  MuonPickyTrkDzErr     = 0;
//  MuonPickyTrkPt        = 0;
//  MuonPickyTrkPz        = 0;
//  MuonPickyTrkP         = 0;
//  MuonPickyTrkEta       = 0;
//  MuonPickyTrkPhi       = 0;
//  MuonPickyTrkChi       = 0;
//  MuonPickyTrkCharge    = 0;
//  MuonPickyTrkQOverPErr = 0;
//  MuonPickyTrkOuterZ    = 0;
//  MuonPickyTrkOuterR    = 0;
//
//  MuonTPFMSTrkChiNorm   = 0;
//  MuonTPFMSCharge       = 0;
//  MuonTPFMSTrkValidHits = 0;
//  MuonTPFMSTrkLostHits  = 0;
//  MuonTPFMSTrkPVDxy     = 0;
//  MuonTPFMSTrkBSDxy     = 0;
//  MuonTPFMSTrkDxy       = 0;
//  MuonTPFMSTrkDxyErr    = 0;
//  MuonTPFMSTrkD0        = 0;
//  MuonTPFMSTrkD0Err     = 0;
//  MuonTPFMSTrkDz        = 0;
//  MuonTPFMSTrkDzErr     = 0;
//  MuonTPFMSTrkPt        = 0;
//  MuonTPFMSTrkPz        = 0;
//  MuonTPFMSTrkP         = 0;
//  MuonTPFMSTrkEta       = 0;
//  MuonTPFMSTrkPhi       = 0;
//  MuonTPFMSTrkChi       = 0;
//  MuonTPFMSTrkCharge    = 0;
//  MuonTPFMSTrkQOverPErr = 0;
//  MuonTPFMSTrkOuterZ    = 0;
//  MuonTPFMSTrkOuterR    = 0;

  //// Taus
  TauP4        = 0;

  TauGenP4     = 0;
  TauGenJetP4  = 0;

  TauGen       = 0;
  TauGenPdgId        = 0;
  TauGenStatus       = 0;
  TauGenMother       = 0;
  TauGenMotherStatus = 0;

  TauCharge  = 0;

  TauTrkIso  = 0;
  TauECalIso = 0;
  TauHCalIso = 0;
  TauAllIso  = 0;
  TauPFAllParticleIso   = 0;
  TauPFChargedHadronIso = 0;
  TauPFNeutralHadronIso = 0;
  TauPFGammaIso         = 0;
    
  //TauTrkIsoDeposit  = 0;
  //TauECalIsoDeposit = 0;
  //TauHCalIsoDeposit = 0;
  //TauPFAllParticleIsoDeposit   = 0;
  //TauPFChargedHadronIsoDeposit = 0;
  //TauPFNeutralHadronIsoDeposit = 0;
  //TauPFGammaIsoDeposit         = 0;
  
  TauVx     = 0;
  TauVy     = 0;
  TauVz     = 0;
  TauPVDxy  = 0;
  TauBSDxy  = 0;
  TauDxy    = 0;
  TauDxyErr = 0;
  TauD0     = 0;
  TauD0Err  = 0;
  TauDz     = 0;
  TauDzErr  = 0;
  
  
  TauIdElec         = 0;
  TauIdMuon         = 0;
  TauIdIso          = 0;
  TauIdIsoLeadPi    = 0;
  TauIdEcalIso      = 0;
  TauIdEcalIsoLeadPi = 0;
  TauIdLeadPiPt      = 0;
  TauIdLeadTrk       = 0;
  TauIdLeadTrkPt     = 0;
  TauIdTrkIso        = 0;
  TauIdTrkIsoLeadPi  = 0;
  TauIdNCfrFull      = 0;
  TauIdNCfrHalf      = 0;
  TauIdNCfrTenth     = 0;
  TauIdNCfrQuarter   = 0;

  TauCaloLeadTrkSignedIP       = 0;
  TauCaloLeadTrkHcal3x3EtSum   = 0;
  TauCaloLeadTrkHcal3x3HotDEta = 0;
  TauCaloSignalTrkMInv         = 0;
  TauCaloTrkMInv               = 0;
  TauCaloIsoTrkPtSum           = 0;
  TauCaloIsoEcalEtSum          = 0;
  TauCaloMaxEtHCAL             = 0;

  TauPFIsoChargedHadPtSum = 0;
  TauPFIsoGammaEtSum      = 0;
  TauPFHcalClusterMaxEt   = 0;
  TauPFEFrac_em           = 0;
  TauPFHcalTotalOverPLead = 0;
  TauPFHcalMaxOverPLead   = 0;
  TauPFHcal3x3OverPLead   = 0;
  TauPFEcalStripOverPLead = 0;
  TauPFBremRecOverPLead   = 0;
  TauPFElePreIDOut        = 0;
  TauPFMuonCaloComp       = 0;
  TauPFMuonSegComp        = 0;

  TauEtaEtaMom = 0;
  TauPhiPhiMom = 0;
  TauEtaPhiMom = 0;
    
  VertexChi2      = 0;
  VertexNdof      = 0;
  VertexNTrks     = 0;
  VertexSumTrkPt  = 0;
  VertexSumTrkPt2 = 0;
  VertexNRawTrks  = 0;
  VertexIsValid   = 0;
  VertexNormalizedChi2 = 0;

  VertexX  = 0;
  VertexY  = 0;
  VertexZ  = 0;
  Vertexd0 = 0;
  VertexdX = 0;
  VertexdY = 0;
  VertexdZ = 0;
    
  HLTTriggered = 0;
  HLTPrescaled = 0;

  genP4        = 0;
  genId        = 0;
  genStatus    = 0;
  genMother    = 0;
  genDaughters = 0;

  genParticleP4        = 0;
  genParticleId        = 0;
  genParticleStatus    = 0;
  genParticleMother    = 0;
  genParticleDaughters = 0;

  pthat            = 0;

  // Set branch addresses and branch pointers
  if (!allTree || !jetTree 
      || !metTree || !leptonTree || !photonTree 
      || !triggerTree || !vertexTree)
    return;
  allChain     = allTree;
  //if (eventTree)
  //  eventChain   = eventTree;
  jetChain     = jetTree;
  metChain     = metTree;
  leptonChain  = leptonTree;
  photonChain  = photonTree;
  triggerChain = triggerTree;
  vertexChain  = vertexTree;
  //trackChain = trackTree;
  if (!isData_) {
    if (!genTree)
      return;
    genChain     = genTree;
  }

  fCurrent = -1;
  //fChain->SetMakeClass(1);
  
  bool debug = false;

  TString jets  = jetPrefix_;
  TString met   = metPrefix_;
  TString leps  = lepPrefix_;
  TString phots = phtPrefix_;
  if (debug) std::cout<<"Jets = " <<jets <<" or jetPrefix_ = "<<jetPrefix_<<std::endl;
  if (debug) std::cout<<"Met = "  <<met  <<" or metPrefix_ = "<<metPrefix_<<std::endl;
  if (debug) std::cout<<"Leps = " <<leps <<" or lepPrefix_ = "<<lepPrefix_<<std::endl;
  if (debug) std::cout<<"Phots = "<<phots<<" or phtPrefix_ = "<<phtPrefix_<<std::endl;

  /*  
  allChain->SetBranchStatus("*",0);
  //eventChain->SetBranchStatus("*",0);
  jetChain->SetBranchStatus("*",0);
  metChain->SetBranchStatus("*",0);
  photonChain->SetBranchStatus("*",0);
  leptonChain->SetBranchStatus("*",0);
  //triggerChain->SetBranchStatus("*",0);
  vertexChain->SetBranchStatus("*",0);
  //if (!isData_)
    //genChain->SetBranchStatus("*",0);
  
  //if (eventChain) {
  //  eventChain->SetBranchStatus("isData",1);
  //  eventChain->SetBranchStatus("totalEvents",1);
  //}

  allChain->SetBranchStatus("Run",1);//           &Run,          &b_Run);
  allChain->SetBranchStatus("Event",1);//         &Event,        &b_Event);
  //allChain->SetBranchStatus("OrbitN",1);//        &OrbitN,       &b_OrbitN);
  //allChain->SetBranchStatus("StoreN",1);//        &StoreN,       &b_StoreN);
  allChain->SetBranchStatus("LumiSection",1);//   &LumiSection,  &b_LumiSection);
  //allChain->SetBranchStatus("BunchCrossing",1);// &BunchCrossing,&b_BunchCrossing);

  if (allChain->GetBranch("susyScanA0")) {
    allChain->SetBranchStatus("susyScanA0",1);
    allChain->SetBranchStatus("susyScanCrossSection",1);
    allChain->SetBranchStatus("susyScanM0",1);
    allChain->SetBranchStatus("susyScanM12",1);
    allChain->SetBranchStatus("susyScanMu",1);
    allChain->SetBranchStatus("susyScanRun",1);
    allChain->SetBranchStatus("susyScantanbeta",1);
  }

  ///////
  //jetChain->SetBranchStatus(jets+"Ht",    1);
  //jetChain->SetBranchStatus(jets+"MHtP4", 1);

  jetChain->SetBranchStatus(jets+"NJets",   1);
  jetChain->SetBranchStatus(jets+"JetP4",   1);
  //jetChain->SetBranchStatus(jets+"RawJetP4",1);

  jetChain->SetBranchStatus(jets+"JetEtaEtaMoment", 1);
  jetChain->SetBranchStatus(jets+"JetEtaPhiMoment", 1);
  jetChain->SetBranchStatus(jets+"JetPhiPhiMoment", 1);

  //if (jetChain->GetBranch(jets+"JetCorrFactor") )
  //  jetChain->SetBranchStatus(jets+"JetCorrFactor", 1);

  if (jetChain->GetBranch(jets+"JetCorrFactorUnc") ) {
    jetChain->SetBranchStatus(jets+"JetCorrFactorUnc",   1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL1",    1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL2",    1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL3",    1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL2L3",  1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL5uds", 1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL5c",   1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL5b",   1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL5glu", 1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL7uds", 1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL7c",   1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL7b",   1);
    jetChain->SetBranchStatus(jets+"JetCorrFactorL7glu", 1);
  }

  //jetChain->SetBranchStatus(jets+"JetOverlaps",       1);
  //jetChain->SetBranchStatus(jets+"JetNOverlaps",      1);
  jetChain->SetBranchStatus(jets+"ElectronOverlaps",  1);
  jetChain->SetBranchStatus(jets+"ElectronNOverlaps", 1);
  jetChain->SetBranchStatus(jets+"MuonOverlaps",      1);
  jetChain->SetBranchStatus(jets+"MuonNOverlaps",     1);
  jetChain->SetBranchStatus(jets+"TauOverlaps",       1);
  jetChain->SetBranchStatus(jets+"TauNOverlaps",      1);
  jetChain->SetBranchStatus(jets+"PhotonOverlaps",    1);
  jetChain->SetBranchStatus(jets+"PhotonNOverlaps",   1);

  jetChain->SetBranchStatus(jets+"JECUncPlus",  1);
  jetChain->SetBranchStatus(jets+"JECUncMinus", 1);

  //jetChain->SetBranchStatus(jets+"JetPreselection", 1);

  //Jet ID (implemented only for Calo/JPT (all three) and PF jets (loose/tight)
  //jetChain->SetBranchStatus(jets+"JetIDMinimal", 1);
  jetChain->SetBranchStatus(jets+"JetIDLoose",   1);
  jetChain->SetBranchStatus(jets+"JetIDTight",   1);

  jetChain->SetBranchStatus(jets+"JetEFrac_em",  1);
  jetChain->SetBranchStatus(jets+"JetEFrac_had", 1);
  jetChain->SetBranchStatus(jets+"JetCharge",    1);
  jetChain->SetBranchStatus(jets+"JetNConst",    1);
  
  //b-Tagging information
  jetChain->SetBranchStatus(jets+"JetBTag_TCHE",           1);
  jetChain->SetBranchStatus(jets+"JetBTag_TCHP",           1);
  jetChain->SetBranchStatus(jets+"JetBTag_jetProb",        1);
  jetChain->SetBranchStatus(jets+"JetBTag_jetBProb",       1);
  jetChain->SetBranchStatus(jets+"JetBTag_SSVHE",          1);
  jetChain->SetBranchStatus(jets+"JetBTag_SSVHP",          1);
  jetChain->SetBranchStatus(jets+"JetBTag_CSV",            1);
  jetChain->SetBranchStatus(jets+"JetBTag_CSVMVA",         1);
  jetChain->SetBranchStatus(jets+"JetBTag_SoftLepton",     1);
  jetChain->SetBranchStatus(jets+"JetBTag_SoftLeptonByIP", 1);
  jetChain->SetBranchStatus(jets+"JetBTag_SoftLeptonByPt", 1);

  //Calo/JPT Jet specific variables
  if (jetChain->GetBranch(jets+"JetfHPD") ) {
    jetChain->SetBranchStatus(jets+"JetfHPD",       1);
    jetChain->SetBranchStatus(jets+"JetfRBX",       1);
    jetChain->SetBranchStatus(jets+"Jetn90",        1);
  }
  
  if (jetChain->GetBranch(jets+"JetTrackPt") ) {
    jetChain->SetBranchStatus(jets+"JetTrackPt",          1);
    jetChain->SetBranchStatus(jets+"JetTrackPhi",         1);
    jetChain->SetBranchStatus(jets+"JetTrackPhiWeighted", 1);
    jetChain->SetBranchStatus(jets+"JetTrackNo",          1);
  }
  
  //JPT/PF Jet specific variables
  if (jetChain->GetBranch(jets+"JetChargedFrac_em") ) {
    jetChain->SetBranchStatus(jets+"JetChargedFrac_em",  1);
    jetChain->SetBranchStatus(jets+"JetNeutralFrac_em",  1);
    jetChain->SetBranchStatus(jets+"JetChargedFrac_had", 1);
    jetChain->SetBranchStatus(jets+"JetNeutralFrac_had", 1);
    jetChain->SetBranchStatus(jets+"JetChargedMult",     1);
    jetChain->SetBranchStatus(jets+"JetElectronMulti",   1);
    jetChain->SetBranchStatus(jets+"JetMuonMulti",       1);
  }
  
  //PF Jet specific variables
  if (jetChain->GetBranch(jets+"JetHFFrac_em") ) {
    jetChain->SetBranchStatus(jets+"JetHFFrac_em",        1);
    jetChain->SetBranchStatus(jets+"JetHFFrac_had",       1);
    jetChain->SetBranchStatus(jets+"JetEFrac_muon",       1);
    jetChain->SetBranchStatus(jets+"JetChargedFrac_muon", 1);
    jetChain->SetBranchStatus(jets+"JetEFrac_photon",     1);
    jetChain->SetBranchStatus(jets+"JetEFrac_electron",   1);
  
    jetChain->SetBranchStatus(jets+"JetHFEn_em",        1);
    jetChain->SetBranchStatus(jets+"JetHFEn_had",       1);
    if (jetChain->GetBranch(jets+"JetEEn_muon"))
      jetChain->SetBranchStatus(jets+"JetEEn_muon",      1);
    else 
      jetChain->SetBranchStatus(jets+"JetEn_muon",      1);
    jetChain->SetBranchStatus(jets+"JetChargedEn_muon", 1);
    jetChain->SetBranchStatus(jets+"JetEn_photon",      1);
    jetChain->SetBranchStatus(jets+"JetEn_electron",    1);
  
    jetChain->SetBranchStatus(jets+"JetHFMult_em",       1);
    jetChain->SetBranchStatus(jets+"JetHFMult_had",      1);;
    jetChain->SetBranchStatus(jets+"JetChargedMult_had", 1);
    jetChain->SetBranchStatus(jets+"JetNeutralMult_had", 1);
    jetChain->SetBranchStatus(jets+"JetPhotonMult",      1);
    jetChain->SetBranchStatus(jets+"JetNeutralMult",     1);
  }
  
  //jetChain->SetBranchStatus(jets+"GenHt",    1);
  //jetChain->SetBranchStatus(jets+"GenMHtP4", 1);

  jetChain->SetBranchStatus(jets+"GenJetP4",              1);
  jetChain->SetBranchStatus(jets+"JetPartonP4",           1);
  jetChain->SetBranchStatus(jets+"JetPartonId",           1);
  jetChain->SetBranchStatus(jets+"JetPartonStatus",       1);
  jetChain->SetBranchStatus(jets+"JetPartonMother",       1);
  jetChain->SetBranchStatus(jets+"JetPartonMotherStatus", 1);
  jetChain->SetBranchStatus(jets+"JetPartonFlavour",      1);

  //MET
  //metChain->SetBranchStatus("nFull"+met+"MET",   &nFullMET,  &b_nFullMET);
  //metChain->SetBranchStatus("nUncorr"+met+"MET", &nUncorrMET,&b_nUncorrMET);

  metChain->SetBranchStatus(met+"METP4",   1);

  //metChain->SetBranchStatus(met+"MET_Fullcorr",            1);
  //metChain->SetBranchStatus(met+"METpt_Fullcorr",          1);
  //metChain->SetBranchStatus(met+"METphi_Fullcorr",         1);
  metChain->SetBranchStatus(met+"METsumEt_Fullcorr",       1);
  metChain->SetBranchStatus(met+"METsignificance_Fullcorr",1);

  metChain->SetBranchStatus(met+"MET_Nocorr",     1);
  metChain->SetBranchStatus(met+"METpt_Nocorr",   1);
  metChain->SetBranchStatus(met+"METphi_Nocorr",  1);
  metChain->SetBranchStatus(met+"METsumEt_Nocorr",1);

  metChain->SetBranchStatus(met+"MET_Muoncorr",     1);
  metChain->SetBranchStatus(met+"METpt_Muoncorr",   1);
  metChain->SetBranchStatus(met+"METphi_Muoncorr",  1);
  metChain->SetBranchStatus(met+"METsumEt_Muoncorr",1);

  metChain->SetBranchStatus(met+"MET_JEScorr",     1);
  metChain->SetBranchStatus(met+"METpt_JEScorr",   1);
  metChain->SetBranchStatus(met+"METphi_JEScorr",  1);
  metChain->SetBranchStatus(met+"METsumEt_JEScorr",1);

  //Calo met specific
  if (metChain->GetBranch(met+"METmaxEt_em") ) {
    metChain->SetBranchStatus(met+"METmaxEt_em",   1);
    metChain->SetBranchStatus(met+"METmaxEt_had",  1);
    metChain->SetBranchStatus(met+"METetFrac_em",  1);
    metChain->SetBranchStatus(met+"METetFrac_had", 1);
    metChain->SetBranchStatus(met+"METmetSig",     1);
  }
  //PF met specific
  if (    metChain->GetBranch(met+"METFrac_neutralEM") ) {
    metChain->SetBranchStatus(met+"METFrac_neutralEM",  1);
    metChain->SetBranchStatus(met+"METFrac_neutralHad", 1);
    metChain->SetBranchStatus(met+"METFrac_chargedEM",  1);
    metChain->SetBranchStatus(met+"METFrac_chargedHad", 1);
    metChain->SetBranchStatus(met+"METFrac_muon",       1);
    metChain->SetBranchStatus(met+"METFrac_type6",      1);
    metChain->SetBranchStatus(met+"METFrac_type7",      1);
  }

  //if (metChain->GetBranch(met+"GenMETP4") ) {
  //  metChain->SetBranchStatus(met+"GenMETP4",       1);
  //  metChain->SetBranchStatus(met+"GenSumEt",       1);
  //  metChain->SetBranchStatus(met+"GenMETSig",      1);
  //  metChain->SetBranchStatus(met+"GenSignificance",1);
  //}
  if (metChain->GetBranch("GenTrueMETP4") ) {
    metChain->SetBranchStatus("GenTrueMETP4",       1);
    metChain->SetBranchStatus("GenCaloMETP4",       1);
    metChain->SetBranchStatus("GenTrueSumEt",       1);
    metChain->SetBranchStatus("GenCaloSumEt",       1);
    metChain->SetBranchStatus("GenTrueMetSig",      1);
    metChain->SetBranchStatus("GenCaloMetSig",      1);
    metChain->SetBranchStatus("GenTrueSignificance",1);
    metChain->SetBranchStatus("GenCaloSignificance",1);
  }

  //Photons
  photonChain->SetBranchStatus(phots+"PhotN",          1);
  //photonChain->SetBranchStatus(phots+"PhotVeto",       1);
  photonChain->SetBranchStatus(phots+"PhotonP4",       1);

  photonChain->SetBranchStatus(phots+"PhotTrkIso",             1);
  photonChain->SetBranchStatus(phots+"PhotECalIso",            1);
  photonChain->SetBranchStatus(phots+"PhotHCalIso",            1);
  photonChain->SetBranchStatus(phots+"PhotAllIso",             1);
  photonChain->SetBranchStatus(phots+"PhotPFAllParticleIso",   1);
  photonChain->SetBranchStatus(phots+"PhotPFChargedHadronIso", 1);
  photonChain->SetBranchStatus(phots+"PhotPFNeutralHadronIso", 1);
  photonChain->SetBranchStatus(phots+"PhotPFGammaIso",         1);

  //photonChain->SetBranchStatus(phots+"PhotTrkIsoDeposit",     1);
  //photonChain->SetBranchStatus(phots+"PhotECalIsoDeposit",    1);
  //photonChain->SetBranchStatus(phots+"PhotHCalIsoDeposit",    1);
  //photonChain->SetBranchStatus(phots+"PhotPFAllParticleIsoDeposit",   1);
  //photonChain->SetBranchStatus(phots+"PhotPFChargedHadronIsoDeposit", 1);
  //photonChain->SetBranchStatus(phots+"PhotPFNeutralHadronIsoDeposit", 1);
  //photonChain->SetBranchStatus(phots+"PhotPFGammaIsoDeposit",         1);

  photonChain->SetBranchStatus(phots+"PhotLoosePhoton",1);
  photonChain->SetBranchStatus(phots+"PhotTightPhoton",1);
  
  photonChain->SetBranchStatus(phots+"PhotSCEta", 1);
  photonChain->SetBranchStatus(phots+"PhotSCPhi", 1);
  photonChain->SetBranchStatus(phots+"PhotSCEn",  1);
  photonChain->SetBranchStatus(phots+"PhotSCPt",  1);
  photonChain->SetBranchStatus(phots+"PhotSCRawE",1);

  photonChain->SetBranchStatus(phots+"PhotTSeed",        1);
  photonChain->SetBranchStatus(phots+"PhotESeed",        1);
  photonChain->SetBranchStatus(phots+"PhotE2OverE9",     1);
  photonChain->SetBranchStatus(phots+"PhotSwissCross",   1);
  photonChain->SetBranchStatus(phots+"PhotHadOverEM",    1);
  photonChain->SetBranchStatus(phots+"PhotSigmaIetaIeta",1);

  photonChain->SetBranchStatus(phots+"PhotIsEB",               1);
  photonChain->SetBranchStatus(phots+"PhotIsEE",               1);
  photonChain->SetBranchStatus(phots+"PhotIsEBGap",            1);
  photonChain->SetBranchStatus(phots+"PhotIsEEGap",            1);
  photonChain->SetBranchStatus(phots+"PhotIsEBEEGap",          1);
  photonChain->SetBranchStatus(phots+"PhotHasPixelSeed",       1);
  photonChain->SetBranchStatus(phots+"PhotHasConversionTracks",1);

  //Electrons
  leptonChain->SetBranchStatus(leps+"ElecVeto",  1);
  leptonChain->SetBranchStatus(leps+"ElectronP4",1);
  leptonChain->SetBranchStatus(leps+"ElecN",     1);

  leptonChain->SetBranchStatus(leps+"ElecdB",     1);
  leptonChain->SetBranchStatus(leps+"ElecdBerr",  1);
  leptonChain->SetBranchStatus(leps+"ElecCharge", 1);

  leptonChain->SetBranchStatus(leps+"ElecTrkIso",    1);
  leptonChain->SetBranchStatus(leps+"ElecECalIso",   1);
  leptonChain->SetBranchStatus(leps+"ElecHCalIso",   1);
  leptonChain->SetBranchStatus(leps+"ElecAllIso",    1);

  leptonChain->SetBranchStatus(leps+"ElecPFAllParticleIso",   1);
  leptonChain->SetBranchStatus(leps+"ElecPFChargedHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"ElecPFNeutralHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"ElecPFGammaIso",         1);

  //leptonChain->SetBranchStatus(leps+"ElecTrkIsoDeposit",    1);
  //leptonChain->SetBranchStatus(leps+"ElecECalIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"ElecHCalIsoDeposit",   1);
  //
  //leptonChain->SetBranchStatus(leps+"ElecPFAllParticleIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"ElecPFChargedHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"ElecPFNeutralHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"ElecPFGammaIsoDeposit",         1);

  leptonChain->SetBranchStatus(leps+"ElecIdLoose",   1);
  leptonChain->SetBranchStatus(leps+"ElecIdTight",   1);
  leptonChain->SetBranchStatus(leps+"ElecIdRobLoose",1);
  leptonChain->SetBranchStatus(leps+"ElecIdRobTight",1);
  leptonChain->SetBranchStatus(leps+"ElecIdRobHighE",1);

  //leptonChain->SetBranchStatus(leps+"ElecPtMode",          1);
  //leptonChain->SetBranchStatus(leps+"ElecChargeMode",      1);
  //leptonChain->SetBranchStatus(leps+"ElecQOverPErrTrkMode",1);

  //leptonChain->SetBranchStatus(leps+"ElecVx",     1);
  //leptonChain->SetBranchStatus(leps+"ElecVy",     1);
  //leptonChain->SetBranchStatus(leps+"ElecVz",     1);
  //leptonChain->SetBranchStatus(leps+"ElecPVDxy",  1);
  leptonChain->SetBranchStatus(leps+"ElecBSDxy",  1);
  leptonChain->SetBranchStatus(leps+"ElecDxy",    1);
  leptonChain->SetBranchStatus(leps+"ElecDxyErr", 1);
  leptonChain->SetBranchStatus(leps+"ElecD0",     1);
  leptonChain->SetBranchStatus(leps+"ElecD0Err",  1);
  leptonChain->SetBranchStatus(leps+"ElecDz",     1);
  leptonChain->SetBranchStatus(leps+"ElecDzErr",  1);
  leptonChain->SetBranchStatus(leps+"ElecPtTrk",  1);

  leptonChain->SetBranchStatus(leps+"ElecHadOverEM",     1);
  leptonChain->SetBranchStatus(leps+"ElecTrkChiNorm",    1);
  leptonChain->SetBranchStatus(leps+"ElecCaloEnergy",    1);
  leptonChain->SetBranchStatus(leps+"ElecE2OverE9",      1);

  //leptonChain->SetBranchStatus(leps+"ElecE1x5",      1);
  //leptonChain->SetBranchStatus(leps+"ElecE5x5",      1);
  //leptonChain->SetBranchStatus(leps+"ElecE2x5Max",   1);
  //leptonChain->SetBranchStatus(leps+"ElecFbrem",     1);
  leptonChain->SetBranchStatus(leps+"ElecSwissCross",    1);
  leptonChain->SetBranchStatus(leps+"ElecSigmaIetaIeta", 1);

  //leptonChain->SetBranchStatus(leps+"ElecQOverPErrTrk",  1);
  //leptonChain->SetBranchStatus(leps+"ElecPinTrk",        1);
  //leptonChain->SetBranchStatus(leps+"ElecPoutTrk",       1);
  //leptonChain->SetBranchStatus(leps+"ElecLostHits",      1);
  leptonChain->SetBranchStatus(leps+"ElecValidHits",       1);
  //leptonChain->SetBranchStatus(leps+"ElecEtaTrk",        1);
  //leptonChain->SetBranchStatus(leps+"ElecPhiTrk",        1);

  leptonChain->SetBranchStatus(leps+"ElecSCEta",           1);
  leptonChain->SetBranchStatus(leps+"ElecSCPhi",           1);
  leptonChain->SetBranchStatus(leps+"ElecSCEn",            1);
  leptonChain->SetBranchStatus(leps+"ElecSCPt",            1);
  leptonChain->SetBranchStatus(leps+"ElecSCRawE",          1);
  leptonChain->SetBranchStatus(leps+"ElecWidthClusterEta", 1);
  leptonChain->SetBranchStatus(leps+"ElecWidthClusterPhi", 1);

  //Muon
  leptonChain->SetBranchStatus(leps+"MuonVeto",1);
  leptonChain->SetBranchStatus(leps+"MuonP4",  1);
  leptonChain->SetBranchStatus(leps+"MuonN",   1);

  leptonChain->SetBranchStatus(leps+"MuonCharge",  1);

  leptonChain->SetBranchStatus(leps+"MuonTrkIso",  1);
  leptonChain->SetBranchStatus(leps+"MuonECalIso", 1);
  leptonChain->SetBranchStatus(leps+"MuonHCalIso", 1);
  leptonChain->SetBranchStatus(leps+"MuonAllIso",  1);

  leptonChain->SetBranchStatus(leps+"MuonPFAllParticleIso",   1);
  leptonChain->SetBranchStatus(leps+"MuonPFChargedHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"MuonPFNeutralHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"MuonPFGammaIso",         1);

  //leptonChain->SetBranchStatus(leps+"MuonTrkIsoDeposit",    1);
  //leptonChain->SetBranchStatus(leps+"MuonECalIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"MuonHCalIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"MuonECalIsoDepositR03",1);
  //leptonChain->SetBranchStatus(leps+"MuonHCalIsoDepositR03",1);

  //leptonChain->SetBranchStatus(leps+"MuonPFAllParticleIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"MuonPFChargedHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"MuonPFNeutralHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"MuonPFGammaIsoDeposit",         1);


  leptonChain->SetBranchStatus(leps+"MuonIsGlobal",               1);
  leptonChain->SetBranchStatus(leps+"MuonIsStandAlone",           1);
  leptonChain->SetBranchStatus(leps+"MuonIsTracker",              1);
  leptonChain->SetBranchStatus(leps+"MuonGlobalMuonPromptTight",  1);
  //leptonChain->SetBranchStatus(leps+"MuonAllArbitrated",          1);
  //leptonChain->SetBranchStatus(leps+"MuonTrackerMuonArbitrated",  1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationLoose",     1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationTight",     1);
  //leptonChain->SetBranchStatus(leps+"MuonTM2DCompatibilityLoose", 1);
  //leptonChain->SetBranchStatus(leps+"MuonTM2DCompatibilityTight", 1);
  //leptonChain->SetBranchStatus(leps+"MuonTMOneStationLoose",      1);
  //leptonChain->SetBranchStatus(leps+"MuonTMOneStationTight",      1);
  //
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationOptimizedLowPtLoose",      1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationOptimizedLowPtTight",      1);
  //leptonChain->SetBranchStatus(leps+"MuonGMTkChiCompatibility",                  1);
  //leptonChain->SetBranchStatus(leps+"MuonGMStaChiCompatibility",                 1);
  //leptonChain->SetBranchStatus(leps+"MuonGMTkKinkTight",                         1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationAngLoose",                 1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationAngTight",                 1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationOptimizedBarrelLowPtLoose",1);
  //leptonChain->SetBranchStatus(leps+"MuonTMLastStationOptimizedBarrelLowPtTight",1);

  leptonChain->SetBranchStatus(leps+"MuonCombChi2",     1);
  leptonChain->SetBranchStatus(leps+"MuonCombNdof",     1);
  //leptonChain->SetBranchStatus(leps+"MuonCombVx",       1);
  //leptonChain->SetBranchStatus(leps+"MuonCombVy",       1);
  //leptonChain->SetBranchStatus(leps+"MuonCombVz",       1);
  leptonChain->SetBranchStatus(leps+"MuonCombPVDxy",    1);
  leptonChain->SetBranchStatus(leps+"MuonCombBSDxy",    1);
  leptonChain->SetBranchStatus(leps+"MuonCombDxy",      1);
  leptonChain->SetBranchStatus(leps+"MuonCombDxyErr",   1);
  leptonChain->SetBranchStatus(leps+"MuonCombD0",       1);
  leptonChain->SetBranchStatus(leps+"MuonCombD0Err",    1);
  leptonChain->SetBranchStatus(leps+"MuonCombDz",       1);
  leptonChain->SetBranchStatus(leps+"MuonCombDzErr",    1);
  leptonChain->SetBranchStatus(leps+"MuonCombPt",       1);
  leptonChain->SetBranchStatus(leps+"MuonCombPz",       1);
  leptonChain->SetBranchStatus(leps+"MuonCombP",        1);
  leptonChain->SetBranchStatus(leps+"MuonCombEta",      1);
  leptonChain->SetBranchStatus(leps+"MuonCombPhi",      1);
  leptonChain->SetBranchStatus(leps+"MuonCombCharge",   1);
  leptonChain->SetBranchStatus(leps+"MuonCombChi",      1);
  leptonChain->SetBranchStatus(leps+"MuonCombQOverPErr",1);
  leptonChain->SetBranchStatus(leps+"MuonCombValidHits",1);

  leptonChain->SetBranchStatus(leps+"MuonStandValidHits",1);
  leptonChain->SetBranchStatus(leps+"MuonStandLostHits", 1);
  leptonChain->SetBranchStatus(leps+"MuonStandPt",       1);
  leptonChain->SetBranchStatus(leps+"MuonStandPz",       1);
  leptonChain->SetBranchStatus(leps+"MuonStandP",        1);
  leptonChain->SetBranchStatus(leps+"MuonStandEta",      1);
  leptonChain->SetBranchStatus(leps+"MuonStandPhi",      1);
  leptonChain->SetBranchStatus(leps+"MuonStandCharge",   1);
  leptonChain->SetBranchStatus(leps+"MuonStandChi",      1);
  leptonChain->SetBranchStatus(leps+"MuonStandQOverPErr",1);

  leptonChain->SetBranchStatus(leps+"MuonTrkChiNorm",   1);
  leptonChain->SetBranchStatus(leps+"MuonTrkValidHits", 1);
  leptonChain->SetBranchStatus(leps+"MuonTrkLostHits",  1);
  leptonChain->SetBranchStatus(leps+"MuonTrkPVDxy",     1);
  leptonChain->SetBranchStatus(leps+"MuonTrkBSDxy",     1);
  leptonChain->SetBranchStatus(leps+"MuonTrkDxy",       1);
  leptonChain->SetBranchStatus(leps+"MuonTrkDxyErr",    1);
  leptonChain->SetBranchStatus(leps+"MuonTrkD0",        1);
  leptonChain->SetBranchStatus(leps+"MuonTrkD0Err",     1);
  leptonChain->SetBranchStatus(leps+"MuonTrkPt",        1);
  leptonChain->SetBranchStatus(leps+"MuonTrkPz",        1);
  leptonChain->SetBranchStatus(leps+"MuonTrkP",         1);
  leptonChain->SetBranchStatus(leps+"MuonTrkEta",       1);
  leptonChain->SetBranchStatus(leps+"MuonTrkPhi",       1);
  leptonChain->SetBranchStatus(leps+"MuonTrkCharge",    1);
  leptonChain->SetBranchStatus(leps+"MuonTrkChi",       1);
  leptonChain->SetBranchStatus(leps+"MuonTrkQOverPErr", 1);
  leptonChain->SetBranchStatus(leps+"MuonTrkOuterZ",    1);
  leptonChain->SetBranchStatus(leps+"MuonTrkOuterR",    1);

//  leptonChain->SetBranchStatus(leps+"MuonPickyCharge",       1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkChiNorm",   1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkValidHits", 1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkLostHits",  1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkPVDxy",     1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkBSDxy",     1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkDxy",       1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkDxyErr",    1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkD0",        1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkD0Err",     1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkPt",        1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkPz",        1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkP",         1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkEta",       1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkPhi",       1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkCharge",    1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkChi",       1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkQOverPErr", 1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkOuterZ",    1);
//  leptonChain->SetBranchStatus(leps+"MuonPickyTrkOuterR",    1);
//
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSCharge",       1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkChiNorm",   1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkValidHits", 1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkLostHits",  1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkPVDxy",     1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkBSDxy",     1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkDxy",       1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkDxyErr",    1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkD0",        1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkD0Err",     1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkPt",        1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkPz",        1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkP",         1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkEta",       1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkPhi",       1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkCharge",    1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkChi",       1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkQOverPErr", 1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkOuterZ",    1);
//  leptonChain->SetBranchStatus(leps+"MuonTPFMSTrkOuterR",    1);

  //Taus
  leptonChain->SetBranchStatus(leps+"TauVeto",  1);
  leptonChain->SetBranchStatus(leps+"TauP4",    1);
  leptonChain->SetBranchStatus(leps+"TauN",     1);

  leptonChain->SetBranchStatus(leps+"TauCharge",    1);

  leptonChain->SetBranchStatus(leps+"TauTrkIso",    1);
  leptonChain->SetBranchStatus(leps+"TauECalIso",   1);
  leptonChain->SetBranchStatus(leps+"TauHCalIso",   1);
  leptonChain->SetBranchStatus(leps+"TauAllIso",    1);

  leptonChain->SetBranchStatus(leps+"TauPFAllParticleIso",   1);
  leptonChain->SetBranchStatus(leps+"TauPFChargedHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"TauPFNeutralHadronIso", 1);
  leptonChain->SetBranchStatus(leps+"TauPFGammaIso",         1);

  //leptonChain->SetBranchStatus(leps+"TauTrkIsoDeposit",    1);
  //leptonChain->SetBranchStatus(leps+"TauECalIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"TauHCalIsoDeposit",   1);
  //
  //leptonChain->SetBranchStatus(leps+"TauPFAllParticleIsoDeposit",   1);
  //leptonChain->SetBranchStatus(leps+"TauPFChargedHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"TauPFNeutralHadronIsoDeposit", 1);
  //leptonChain->SetBranchStatus(leps+"TauPFGammaIsoDeposit",         1);

  leptonChain->SetBranchStatus(leps+"TauIdElec",       1);
  leptonChain->SetBranchStatus(leps+"TauIdMuon",       1);

  leptonChain->SetBranchStatus(leps+"TauIdIso",        1);
  leptonChain->SetBranchStatus(leps+"TauIdIsoLeadPi",  1);

  leptonChain->SetBranchStatus(leps+"TauIdEcalIso",       1);
  leptonChain->SetBranchStatus(leps+"TauIdEcalIsoLeadPi", 1);

  leptonChain->SetBranchStatus(leps+"TauIdLeadPiPt",    1);
  leptonChain->SetBranchStatus(leps+"TauIdLeadTrk",     1);
  leptonChain->SetBranchStatus(leps+"TauIdLeadTrkPt",   1);

  leptonChain->SetBranchStatus(leps+"TauIdTrkIso",        1);
  leptonChain->SetBranchStatus(leps+"TauIdTrkIsoLeadPi",  1);

  leptonChain->SetBranchStatus(leps+"TauIdNCfrFull",   1);
  leptonChain->SetBranchStatus(leps+"TauIdNCfrHalf",   1);
  leptonChain->SetBranchStatus(leps+"TauIdNCfrTenth",  1);
  leptonChain->SetBranchStatus(leps+"TauIdNCfrQuarter",1);

  leptonChain->SetBranchStatus(leps+"TauVx",     1);
  leptonChain->SetBranchStatus(leps+"TauVy",     1);
  leptonChain->SetBranchStatus(leps+"TauVz",     1);
  leptonChain->SetBranchStatus(leps+"TauPVDxy",  1);
  leptonChain->SetBranchStatus(leps+"TauBSDxy",  1);
  leptonChain->SetBranchStatus(leps+"TauDxy",    1);
  leptonChain->SetBranchStatus(leps+"TauDxyErr", 1);
  leptonChain->SetBranchStatus(leps+"TauD0",     1);
  leptonChain->SetBranchStatus(leps+"TauD0Err",  1);
  leptonChain->SetBranchStatus(leps+"TauDz",     1);
  leptonChain->SetBranchStatus(leps+"TauDzErr",  1);


  if (leptonChain->GetBranch(leps+"TauCaloLeadTrkSignedIP") ) {
    leptonChain->SetBranchStatus(leps+"TauCaloLeadTrkSignedIP",           1);
    leptonChain->SetBranchStatus(leps+"TauCaloLeadTrkHcal3x3EtSum",       1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloLeadTrkHcal3x3HotDEta", 1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloSignalTrkMInv"        , 1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloTrkMInv"              , 1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloIsoTrkPtSum"          , 1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloIsoEcalEtSum"         , 1);
    leptonChain->SetBranchStatus(leps+"TauCaloCaloMaxEtHCAL"            , 1);
  }
  
  if (leptonChain->GetBranch(leps+"TauPFPFIsoChargedHadPtSum") ) {
    leptonChain->SetBranchStatus(leps+"TauPFPFIsoChargedHadPtSum",   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFIsoGammaEtSum"     ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFHcalClusterMaxEt"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFEFrac_em"          ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFHcalTotalOverPLead",   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFHcalMaxOverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFHcal3x3OverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFEcalStripOverPLead",   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFBremRecOverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFElePreIDOut"       ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFMuonCaloComp"      ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFPFMuonSegComp"       ,   1);
  }
  else if (leptonChain->GetBranch(leps+"TauPFIsoChargedHadPtSum") ) {
    leptonChain->SetBranchStatus(leps+"TauPFIsoChargedHadPtSum",   1);
    leptonChain->SetBranchStatus(leps+"TauPFIsoGammaEtSum"     ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFHcalClusterMaxEt"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFEFrac_em"          ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFHcalTotalOverPLead",   1);
    leptonChain->SetBranchStatus(leps+"TauPFHcalMaxOverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFHcal3x3OverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFEcalStripOverPLead",   1);
    leptonChain->SetBranchStatus(leps+"TauPFBremRecOverPLead"  ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFElePreIDOut"       ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFMuonCaloComp"      ,   1);
    leptonChain->SetBranchStatus(leps+"TauPFMuonSegComp"       ,   1);
  }

  leptonChain->SetBranchStatus(leps+"TauEtaEtaMoment",1);
  leptonChain->SetBranchStatus(leps+"TauPhiPhiMoment",1);
  leptonChain->SetBranchStatus(leps+"TauEtaPhiMoment",1);


  //Beamspot variables
  //vertexChain->SetBranchStatus("beamspotX0",        1);
  //vertexChain->SetBranchStatus("beamspotY0",        1);
  //vertexChain->SetBranchStatus("beamspotZ0",        1);
  //vertexChain->SetBranchStatus("beamspotX0Err",     1);
  //vertexChain->SetBranchStatus("beamspotY0Err",     1);
  //vertexChain->SetBranchStatus("beamspotZ0Err",     1);
  //vertexChain->SetBranchStatus("beamspotWidthX",    1);
  //vertexChain->SetBranchStatus("beamspotWidthY",    1);
  //vertexChain->SetBranchStatus("beamspotWidthXErr", 1);
  //vertexChain->SetBranchStatus("beamspotWidthYErr", 1);
  //vertexChain->SetBranchStatus("beamspotdxdz",      1);
  //vertexChain->SetBranchStatus("beamspotdydz",      1);
  //vertexChain->SetBranchStatus("beamspotdxdzErr",   1);
  //vertexChain->SetBranchStatus("beamspotdydzErr",   1);
  //vertexChain->SetBranchStatus("beamspotSigmaZ0",   1);
  //vertexChain->SetBranchStatus("beamspotSigmaZ0Err",1);
  //vertexChain->SetBranchStatus("beamspotEmittanceX",1);
  //vertexChain->SetBranchStatus("beamspotEmittanceY",1);
  //vertexChain->SetBranchStatus("beamspotBetaStar",  1);

  vertexChain->SetBranchStatus("nVtx",                1);
  vertexChain->SetBranchStatus("VertexChi2",          1);
  vertexChain->SetBranchStatus("VertexNdof",          1);
  vertexChain->SetBranchStatus("VertexNTrks",         1);
  vertexChain->SetBranchStatus("VertexSumTrkPt",      1);
  vertexChain->SetBranchStatus("VertexSumTrkPt2",     1);
  vertexChain->SetBranchStatus("VertexNRawTrks",      1);
  vertexChain->SetBranchStatus("VertexIsValid",       1);
  vertexChain->SetBranchStatus("VertexNormalizedChi2",1);
  vertexChain->SetBranchStatus("VertexX",             1);
  vertexChain->SetBranchStatus("VertexY",             1);
  vertexChain->SetBranchStatus("VertexZ",             1);
  vertexChain->SetBranchStatus("Vertexd0",            1);
  vertexChain->SetBranchStatus("VertexdX",            1);
  vertexChain->SetBranchStatus("VertexdY",            1);
  vertexChain->SetBranchStatus("VertexdZ",            1);

  //if (trackChain->GetBranch("MPTPhi") ) {
  //  trackChain->SetBranchStatus("MPTPhi",1);
  //  trackChain->SetBranchStatus("MPTPx", 1);
  //  trackChain->SetBranchStatus("MPTPy", 1);
  //  trackChain->SetBranchStatus("MPTPz", 1);
  //}
  
  triggerChain->SetBranchStatus("HLTTriggered",1);
  triggerChain->SetBranchStatus("HLTPrescaled",1);

  
  leptonChain->SetBranchStatus(leps+"ElecGenP4",          1);
  leptonChain->SetBranchStatus(leps+"ElecGenPdgId",       1);
  leptonChain->SetBranchStatus(leps+"ElecGenStatus",      1);
  leptonChain->SetBranchStatus(leps+"ElecGenMother",      1);
  leptonChain->SetBranchStatus(leps+"ElecGenMotherStatus",1);
  
  leptonChain->SetBranchStatus(leps+"MuonGenP4",          1);
  leptonChain->SetBranchStatus(leps+"MuonGenPdgId",       1);
  leptonChain->SetBranchStatus(leps+"MuonGenStatus",      1);
  leptonChain->SetBranchStatus(leps+"MuonGenMother",      1);
  leptonChain->SetBranchStatus(leps+"MuonGenMotherStatus",1);
  
  leptonChain->SetBranchStatus(leps+"TauGen",            1);
  leptonChain->SetBranchStatus(leps+"TauGenP4",          1);
  leptonChain->SetBranchStatus(leps+"TauGenPdgId",       1);
  leptonChain->SetBranchStatus(leps+"TauGenStatus",      1);
  leptonChain->SetBranchStatus(leps+"TauGenMother",      1);
  leptonChain->SetBranchStatus(leps+"TauGenMotherStatus",1);
  leptonChain->SetBranchStatus(leps+"TauGenJetP4",       1);
  
  photonChain->SetBranchStatus(phots+"PhotGenP4",          1);
  photonChain->SetBranchStatus(phots+"PhotGenPdgId",       1);
  photonChain->SetBranchStatus(phots+"PhotGenStatus",      1);
  photonChain->SetBranchStatus(phots+"PhotGenMother",      1);
  photonChain->SetBranchStatus(phots+"PhotGenMotherStatus",1);
  
  ///////


  jetChain->SetBranchStatus(jets+"*",1);


  //MET
  //metChain->SetBranchStatus("nFull"+met+"MET",1);
  //metChain->SetBranchStatus("nUncorr"+met+"MET",1);

  metChain->SetBranchStatus(met+"*",1);

  if (metChain->GetBranch("GenTrueMETP4") ) {
    metChain->SetBranchStatus("GenTrueMETP4",1);
    metChain->SetBranchStatus("GenCaloMETP4",1);
    metChain->SetBranchStatus("GenTrueSumEt",1);
    metChain->SetBranchStatus("GenCaloSumEt",1);
    metChain->SetBranchStatus("GenTrueMetSig",1);
    metChain->SetBranchStatus("GenCaloMetSig",1);
    metChain->SetBranchStatus("GenTrueSignificance",1);
    metChain->SetBranchStatus("GenCaloSignificance",1);
  }

  //Photons
  photonChain->SetBranchStatus(phots+"*",1);

  //Electrons
  leptonChain->SetBranchStatus(leps+"*",1);

  //Beamspot variables
  //vertexChain->SetBranchStatus("beams*",1);

  vertexChain->SetBranchStatus("nVtx",1);
  vertexChain->SetBranchStatus("Vertex*",1);

  //if (trackChain->GetBranch("MPTPhi") )
  //  trackChain->SetBranchStatus("MPT*",1);
  
  //triggerChain->SetBranchStatus("HLTTriggered",1);
  //triggerChain->SetBranchStatus("HLTPrescaled",1);

  
  //if (!isData_) {
  //  genChain->SetBranchStatus("gen*",1);
  //  genChain->SetBranchStatus("pthat",1);
  //}
  */

  //Set branch addresses  
  //if (eventChain) {
  //  eventChain->SetBranchAddress("isData",        &isData,      &b_isData);
  //  eventChain->SetBranchAddress("totalEvents",   &totalEvents, &b_totalEvents);
  //}

  allChain->SetBranchAddress("Run",           &Run,          &b_Run);
  allChain->SetBranchAddress("Event",         &Event,        &b_Event);
  //allChain->SetBranchAddress("OrbitN",        &OrbitN,       &b_OrbitN);
  //allChain->SetBranchAddress("StoreN",        &StoreN,       &b_StoreN);
  allChain->SetBranchAddress("LumiSection",   &LumiSection,  &b_LumiSection);
  //allChain->SetBranchAddress("BunchCrossing", &BunchCrossing,&b_BunchCrossing);

  if (allChain->GetBranch("susyScanA0")) {
    doSusyScan = true;
    allChain->SetBranchAddress("susyScanA0",              &susyScanA0           ,        &b_susyScanA0          );
    allChain->SetBranchAddress("susyScanCrossSection",    &susyScanCrossSection ,        &b_susyScanCrossSection);
    allChain->SetBranchAddress("susyScanM0",              &susyScanM0           ,        &b_susyScanM0          );
    allChain->SetBranchAddress("susyScanM12",             &susyScanM12          ,        &b_susyScanM12         );
    allChain->SetBranchAddress("susyScanMu",              &susyScanMu           ,        &b_susyScanMu          );
    allChain->SetBranchAddress("susyScanRun",             &susyScanRun          ,        &b_susyScanRun         );
    allChain->SetBranchAddress("susyScantanbeta",         &susyScantanbeta      ,        &b_susyScantanbeta     );
  }

  //jetChain->SetBranchAddress(jets+"Ht",    &Ht,    &b_Ht);
  //jetChain->SetBranchAddress(jets+"MHtP4", &MHtP4, &b_MHtP4);

  jetChain->SetBranchAddress(jets+"NJets",   &NJets,   &b_NJets);
  jetChain->SetBranchAddress(jets+"JetP4",   &JetP4,   &b_JetP4);
  //jetChain->SetBranchAddress(jets+"RawJetP4",&RawJetP4,&b_RawJetP4);

  jetChain->SetBranchAddress(jets+"JetEtaEtaMoment", &JetEtaEtaMoment, &b_JetEtaEtaMoment);
  jetChain->SetBranchAddress(jets+"JetEtaPhiMoment", &JetEtaPhiMoment, &b_JetEtaPhiMoment);
  jetChain->SetBranchAddress(jets+"JetPhiPhiMoment", &JetPhiPhiMoment, &b_JetPhiPhiMoment);

  //if (jetChain->GetBranch(jets+"JetCorrFactor") )
  //  jetChain->SetBranchAddress(jets+"JetCorrFactor", &JetCorrectionFactor, &b_JetCorrectionFactor);

  if (jetChain->GetBranch(jets+"JetCorrFactorUnc") ) {
    jetChain->SetBranchAddress(jets+"JetCorrFactorUnc",   &JetCorrectionFactorUnc  , &b_JetCorrectionFactorUnc  );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL1",    &JetCorrectionFactorL1   , &b_JetCorrectionFactorL1   );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL2",    &JetCorrectionFactorL2   , &b_JetCorrectionFactorL2   );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL3",    &JetCorrectionFactorL3   , &b_JetCorrectionFactorL3   );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL2L3",  &JetCorrectionFactorL2L3 , &b_JetCorrectionFactorL2L3 );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL5uds", &JetCorrectionFactorL5uds, &b_JetCorrectionFactorL5uds);
    jetChain->SetBranchAddress(jets+"JetCorrFactorL5c",   &JetCorrectionFactorL5c  , &b_JetCorrectionFactorL5c  );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL5b",   &JetCorrectionFactorL5b  , &b_JetCorrectionFactorL5b  );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL5glu", &JetCorrectionFactorL5glu, &b_JetCorrectionFactorL5glu);
    jetChain->SetBranchAddress(jets+"JetCorrFactorL7uds", &JetCorrectionFactorL7uds, &b_JetCorrectionFactorL7uds);
    jetChain->SetBranchAddress(jets+"JetCorrFactorL7c",   &JetCorrectionFactorL7c  , &b_JetCorrectionFactorL7c  );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL7b",   &JetCorrectionFactorL7b  , &b_JetCorrectionFactorL7b  );
    jetChain->SetBranchAddress(jets+"JetCorrFactorL7glu", &JetCorrectionFactorL7glu, &b_JetCorrectionFactorL7glu);
  }

  //jetChain->SetBranchAddress(jets+"JetOverlaps",     &JetOverlaps           , &b_JetOverlaps         );
  //jetChain->SetBranchAddress(jets+"JetNOverlaps",    &JetNOverlaps          , &b_JetNOverlaps        );
  jetChain->SetBranchAddress(jets+"ElectronOverlaps",  &JetElectronOverlaps , &b_JetElectronOverlaps );
  jetChain->SetBranchAddress(jets+"ElectronNOverlaps", &JetElectronNOverlaps, &b_JetElectronNOverlaps);
  jetChain->SetBranchAddress(jets+"MuonOverlaps",      &JetMuonOverlaps     , &b_JetMuonOverlaps     );
  jetChain->SetBranchAddress(jets+"MuonNOverlaps",     &JetMuonNOverlaps    , &b_JetMuonNOverlaps    );
  jetChain->SetBranchAddress(jets+"TauOverlaps",       &JetTauOverlaps      , &b_JetTauOverlaps      );
  jetChain->SetBranchAddress(jets+"TauNOverlaps",      &JetTauNOverlaps     , &b_JetTauNOverlaps     );
  jetChain->SetBranchAddress(jets+"PhotonOverlaps",    &JetPhotonOverlaps   , &b_JetPhotonOverlaps   );
  jetChain->SetBranchAddress(jets+"PhotonNOverlaps",   &JetPhotonNOverlaps  , &b_JetPhotonNOverlaps  );

  jetChain->SetBranchAddress(jets+"JECUncPlus",   &JECUncPlus  , &b_JECUncPlus );
  jetChain->SetBranchAddress(jets+"JECUncMinus",  &JECUncMinus , &b_JECUncMinus);

  //jetChain->SetBranchAddress(jets+"JetPreselection", &JetPreselection, &b_JetPreselection);

  //Jet ID (implemented only for Calo/JPT (all three) and PF jets (loose/tight)
  //jetChain->SetBranchAddress(jets+"JetIDMinimal", &JetIDMinimal,&b_JetIDMinimal);
  jetChain->SetBranchAddress(jets+"JetIDLoose",   &JetIDLoose,  &b_JetIDLoose);
  jetChain->SetBranchAddress(jets+"JetIDTight",   &JetIDTight,  &b_JetIDTight);

  jetChain->SetBranchAddress(jets+"JetEFrac_em",  &JetEFrac_em,  &b_JetEFrac_em);
  jetChain->SetBranchAddress(jets+"JetEFrac_had", &JetEFrac_had, &b_JetEFrac_had);
  jetChain->SetBranchAddress(jets+"JetCharge",    &JetCharge,    &b_JetCharge);
  jetChain->SetBranchAddress(jets+"JetNConst",    &JetNConst,    &b_JetNConst);
  
  //b-Tagging information
  jetChain->SetBranchAddress(jets+"JetBTag_TCHE",           &JetBTag_TCHE,          &b_JetBTag_TCHE);
  jetChain->SetBranchAddress(jets+"JetBTag_TCHP",           &JetBTag_TCHP,          &b_JetBTag_TCHP);
  jetChain->SetBranchAddress(jets+"JetBTag_jetProb",        &JetBTag_jetProb,       &b_JetBTag_jetProb);
  jetChain->SetBranchAddress(jets+"JetBTag_jetBProb",       &JetBTag_jetBProb,      &b_JetBTag_jetBProb);
  jetChain->SetBranchAddress(jets+"JetBTag_SSVHE",          &JetBTag_SSVHE,         &b_JetBTag_SSVHE);
  jetChain->SetBranchAddress(jets+"JetBTag_SSVHP",          &JetBTag_SSVHP,         &b_JetBTag_SSVHP);
  jetChain->SetBranchAddress(jets+"JetBTag_CSV",            &JetBTag_CSV,           &b_JetBTag_CSV);
  jetChain->SetBranchAddress(jets+"JetBTag_CSVMVA",         &JetBTag_CSVMVA,        &b_JetBTag_CSVMVA);
  jetChain->SetBranchAddress(jets+"JetBTag_SoftLepton",     &JetBTag_SoftLepton,    &b_JetBTag_SoftLepton);
  jetChain->SetBranchAddress(jets+"JetBTag_SoftLeptonByIP", &JetBTag_SoftLeptonByIP,&b_JetBTag_SoftLeptonByIP);
  jetChain->SetBranchAddress(jets+"JetBTag_SoftLeptonByPt", &JetBTag_SoftLeptonByPt,&b_JetBTag_SoftLeptonByPt);

  //Calo/JPT Jet specific variables
  if (jetChain->GetBranch(jets+"JetfHPD") ) {
    jetChain->SetBranchAddress(jets+"JetfHPD",             &JetfHPD,            &b_JetfHPD);
    jetChain->SetBranchAddress(jets+"JetfRBX",             &JetfRBX,            &b_JetfRBX);
    jetChain->SetBranchAddress(jets+"Jetn90",              &Jetn90,             &b_Jetn90);
  }
  
  if (jetChain->GetBranch(jets+"JetTrackPt") ) {
    jetChain->SetBranchAddress(jets+"JetTrackPt",          &JetTrackPt,         &b_JetTrackPt);
    jetChain->SetBranchAddress(jets+"JetTrackPhi",         &JetTrackPhi,        &b_JetTrackPhi);
    jetChain->SetBranchAddress(jets+"JetTrackPhiWeighted", &JetTrackPhiWeighted,&b_JetTrackPhiWeighted);
    jetChain->SetBranchAddress(jets+"JetTrackNo",          &JetTrackNo,         &b_JetTrackNo);
  }
  
  //JPT/PF Jet specific variables
  if (jetChain->GetBranch(jets+"JetChargedFrac_em") ) {
    jetChain->SetBranchAddress(jets+"JetChargedFrac_em",  &JetChargedFrac_em, &b_JetChargedFrac_em);
    jetChain->SetBranchAddress(jets+"JetNeutralFrac_em",  &JetNeutralFrac_em, &b_JetNeutralFrac_em);
    jetChain->SetBranchAddress(jets+"JetChargedFrac_had", &JetChargedFrac_had,&b_JetChargedFrac_had);
    jetChain->SetBranchAddress(jets+"JetNeutralFrac_had", &JetNeutralFrac_had,&b_JetNeutralFrac_had);
    jetChain->SetBranchAddress(jets+"JetChargedMult",     &JetChargedMult,    &b_JetChargedMult);
    jetChain->SetBranchAddress(jets+"JetElectronMulti",   &JetElectronMulti,  &b_JetElectronMulti);
    jetChain->SetBranchAddress(jets+"JetMuonMulti",       &JetMuonMulti,      &b_JetMuonMulti);
  }
  
  //PF Jet specific variables
  if (jetChain->GetBranch(jets+"JetHFFrac_em") ) {
    jetChain->SetBranchAddress(jets+"JetHFFrac_em",        &JetHFFrac_em,        &b_JetHFFrac_em);
    jetChain->SetBranchAddress(jets+"JetHFFrac_had",       &JetHFFrac_had,       &b_JetHFFrac_had);
    jetChain->SetBranchAddress(jets+"JetEFrac_muon",       &JetEFrac_muon,       &b_JetEFrac_muon);
    jetChain->SetBranchAddress(jets+"JetChargedFrac_muon", &JetChargedFrac_muon, &b_JetChargedFrac_muon);
    jetChain->SetBranchAddress(jets+"JetEFrac_photon",     &JetEFrac_photon,     &b_JetEFrac_photon);
    jetChain->SetBranchAddress(jets+"JetEFrac_electron",   &JetEFrac_electron,   &b_JetEFrac_electron);
  
    jetChain->SetBranchAddress(jets+"JetHFEn_em",        &JetHFEn_em,        &b_JetHFEn_em);
    jetChain->SetBranchAddress(jets+"JetHFEn_had",       &JetHFEn_had,       &b_JetHFEn_had);
    if (jetChain->GetBranch(jets+"JetEEn_muon"))
      jetChain->SetBranchAddress(jets+"JetEEn_muon",        &JetEn_muon,        &b_JetEn_muon);
    else 
      jetChain->SetBranchAddress(jets+"JetEn_muon",        &JetEn_muon,        &b_JetEn_muon);
    jetChain->SetBranchAddress(jets+"JetChargedEn_muon", &JetChargedEn_muon, &b_JetChargedEn_muon);
    jetChain->SetBranchAddress(jets+"JetEn_photon",      &JetEn_photon,      &b_JetEn_photon);
    jetChain->SetBranchAddress(jets+"JetEn_electron",    &JetEn_electron,    &b_JetEn_electron);
  
    jetChain->SetBranchAddress(jets+"JetHFMult_em",       &JetHFMult_em,      &b_JetHFMult_em);
    jetChain->SetBranchAddress(jets+"JetHFMult_had",      &JetHFMult_had,     &b_JetHFMult_had);
    jetChain->SetBranchAddress(jets+"JetChargedMult_had", &JetChargedMult_had,&b_JetChargedMult_had);
    jetChain->SetBranchAddress(jets+"JetNeutralMult_had", &JetNeutralMult_had,&b_JetNeutralMult_had);
    jetChain->SetBranchAddress(jets+"JetPhotonMult",      &JetPhotonMult,     &b_JetPhotonMult);
    jetChain->SetBranchAddress(jets+"JetNeutralMult",     &JetNeutralMult,    &b_JetNeutralMult);
  }
  
  //jetChain->SetBranchAddress(jets+"GenHt",    &GenHt,    &b_GenHt);
  //jetChain->SetBranchAddress(jets+"GenMHtP4", &GenMHtP4, &b_GenMHtP4);

  jetChain->SetBranchAddress(jets+"GenJetP4",              &GenJetP4,        &b_GenJetP4);
  jetChain->SetBranchAddress(jets+"JetPartonP4",           &JetPartonP4,     &b_JetPartonP4);
  jetChain->SetBranchAddress(jets+"JetPartonId",           &JetPartonId,     &b_JetPartonId);
  jetChain->SetBranchAddress(jets+"JetPartonStatus",       &JetPartonStatus, &b_JetPartonStatus);
  jetChain->SetBranchAddress(jets+"JetPartonMother",       &JetPartonMother, &b_JetPartonMother);
  jetChain->SetBranchAddress(jets+"JetPartonMotherStatus", &JetPartonMotherStatus, &b_JetPartonMotherStatus);
  jetChain->SetBranchAddress(jets+"JetPartonFlavour",      &JetPartonFlavour,&b_JetPartonFlavour);

  //MET
  //metChain->SetBranchAddress("nFull"+met+"MET",   &nFullMET,  &b_nFullMET);
  //metChain->SetBranchAddress("nUncorr"+met+"MET", &nUncorrMET,&b_nUncorrMET);

  metChain->SetBranchAddress(met+"METP4",   &METP4,   &b_METP4);

  //metChain->SetBranchAddress(met+"MET_Fullcorr",             MET_Fullcorr,      &b_MET_Fullcorr);
  //metChain->SetBranchAddress(met+"METpt_Fullcorr",          &METpt_Fullcorr,    &b_METpt_Fullcorr);
  //metChain->SetBranchAddress(met+"METphi_Fullcorr",         &METphi_Fullcorr,   &b_METphi_Fullcorr);
  metChain->SetBranchAddress(met+"METsumEt_Fullcorr",       &METsumEt_Fullcorr, &b_METsumEt_Fullcorr);
  metChain->SetBranchAddress(met+"METsignificance_Fullcorr",&METsignificance,   &b_METsignificance);

  metChain->SetBranchAddress(met+"MET_Nocorr",      MET_Nocorr,     &b_MET_Nocorr);
  metChain->SetBranchAddress(met+"METpt_Nocorr",   &METpt_Nocorr,   &b_METpt_Nocorr);
  metChain->SetBranchAddress(met+"METphi_Nocorr",  &METphi_Nocorr,  &b_METphi_Nocorr);
  metChain->SetBranchAddress(met+"METsumEt_Nocorr",&METsumEt_Nocorr,&b_METsumEt_Nocorr);

  metChain->SetBranchAddress(met+"MET_Muoncorr",      MET_Muoncorr,     &b_MET_Muoncorr);
  metChain->SetBranchAddress(met+"METpt_Muoncorr",   &METpt_Muoncorr,   &b_METpt_Muoncorr);
  metChain->SetBranchAddress(met+"METphi_Muoncorr",  &METphi_Muoncorr,  &b_METphi_Muoncorr);
  metChain->SetBranchAddress(met+"METsumEt_Muoncorr",&METsumEt_Muoncorr,&b_METsumEt_Muoncorr);

  metChain->SetBranchAddress(met+"MET_JEScorr",      MET_JEScorr,     &b_MET_JEScorr);
  metChain->SetBranchAddress(met+"METpt_JEScorr",   &METpt_JEScorr,   &b_METpt_JEScorr);
  metChain->SetBranchAddress(met+"METphi_JEScorr",  &METphi_JEScorr,  &b_METphi_JEScorr);
  metChain->SetBranchAddress(met+"METsumEt_JEScorr",&METsumEt_JEScorr,&b_METsumEt_JEScorr);

  //Calo met specific
  if (metChain->GetBranch(met+"METmaxEt_em") ) {
    metChain->SetBranchAddress(met+"METmaxEt_em",   &METmaxEt_em,   &b_METmaxEt_em  );
    metChain->SetBranchAddress(met+"METmaxEt_had",  &METmaxEt_had,  &b_METmaxEt_had );
    metChain->SetBranchAddress(met+"METetFrac_em",  &METetFrac_em,  &b_METetFrac_em );
    metChain->SetBranchAddress(met+"METetFrac_had", &METetFrac_had, &b_METetFrac_had);
    metChain->SetBranchAddress(met+"METmetSig",     &METmetSig,     &b_METmetSig    );
  }
  //PF met specific
  if (    metChain->GetBranch(met+"METFrac_neutralEM") ) {
    metChain->SetBranchAddress(met+"METFrac_neutralEM",  &METFrac_neutralEM,  &b_METFrac_neutralEM  );
    metChain->SetBranchAddress(met+"METFrac_neutralHad", &METFrac_neutralHad, &b_METFrac_neutralHad );
    metChain->SetBranchAddress(met+"METFrac_chargedEM",  &METFrac_chargedEM,  &b_METFrac_chargedEM  );
    metChain->SetBranchAddress(met+"METFrac_chargedHad", &METFrac_chargedHad, &b_METFrac_chargedHad );
    metChain->SetBranchAddress(met+"METFrac_muon",       &METFrac_muon,       &b_METFrac_muon       );
    metChain->SetBranchAddress(met+"METFrac_type6",      &METFrac_type6,      &b_METFrac_type6      );
    metChain->SetBranchAddress(met+"METFrac_type7",      &METFrac_type7,      &b_METFrac_type7      );
  }

  //if (metChain->GetBranch(met+"GenMETP4") ) {
  //  metChain->SetBranchAddress(met+"GenMETP4",       &GenMETP4,       &b_GenMETP4);
  //  metChain->SetBranchAddress(met+"GenSumEt",       &GenSumEt,       &b_GenSumEt);
  //  metChain->SetBranchAddress(met+"GenMETSig",      &GenMETSig,      &b_GenMETSig);
  //  metChain->SetBranchAddress(met+"GenSignificance",&GenSignificance,&b_GenSignificance);
  //}
  if (metChain->GetBranch("GenTrueMETP4") ) {
    metChain->SetBranchAddress("GenTrueMETP4",       &GenMETTrueP4,       &b_GenMETTrueP4);
    metChain->SetBranchAddress("GenCaloMETP4",       &GenMETCaloP4,       &b_GenMETCaloP4);
    metChain->SetBranchAddress("GenTrueSumEt",       &GenTrueSumEt,       &b_GenTrueSumEt);
    metChain->SetBranchAddress("GenCaloSumEt",       &GenCaloSumEt,       &b_GenCaloSumEt);
    metChain->SetBranchAddress("GenTrueMetSig",      &GenTrueMETSig,      &b_GenTrueMETSig);
    metChain->SetBranchAddress("GenCaloMetSig",      &GenCaloMETSig,      &b_GenCaloMETSig);
    metChain->SetBranchAddress("GenTrueSignificance",&GenTrueSignificance,&b_GenTrueSignificance);
    metChain->SetBranchAddress("GenCaloSignificance",&GenCaloSignificance,&b_GenCaloSignificance);
  }

  //Photons
  photonChain->SetBranchAddress(phots+"PhotN",          &PhotN,          &b_PhotN);
  //photonChain->SetBranchAddress(phots+"PhotVeto",       &PhotVeto,       &b_PhotVeto);
  photonChain->SetBranchAddress(phots+"PhotonP4",       &PhotonP4,       &b_PhotonP4);

  photonChain->SetBranchAddress(phots+"PhotTrkIso",             &PhotTrkIso,             &b_PhotTrkIso);
  photonChain->SetBranchAddress(phots+"PhotECalIso",            &PhotECalIso,            &b_PhotECalIso);
  photonChain->SetBranchAddress(phots+"PhotHCalIso",            &PhotHCalIso,            &b_PhotHCalIso);
  photonChain->SetBranchAddress(phots+"PhotAllIso",             &PhotAllIso,             &b_PhotAllIso);
  photonChain->SetBranchAddress(phots+"PhotPFAllParticleIso",   &PhotPFAllParticleIso,   &b_PhotPFAllParticleIso);
  photonChain->SetBranchAddress(phots+"PhotPFChargedHadronIso", &PhotPFChargedHadronIso, &b_PhotPFChargedHadronIso);
  photonChain->SetBranchAddress(phots+"PhotPFNeutralHadronIso", &PhotPFNeutralHadronIso, &b_PhotPFNeutralHadronIso);
  photonChain->SetBranchAddress(phots+"PhotPFGammaIso",         &PhotPFGammaIso,         &b_PhotPFGammaIso);

  //photonChain->SetBranchAddress(phots+"PhotTrkIsoDeposit",     &PhotTrkIsoDeposit,     &b_PhotTrkIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotECalIsoDeposit",    &PhotECalIsoDeposit,    &b_PhotECalIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotHCalIsoDeposit",    &PhotHCalIsoDeposit,    &b_PhotHCalIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotPFAllParticleIsoDeposit",   &PhotPFAllParticleIsoDeposit,     &b_PhotPFAllParticleIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotPFChargedHadronIsoDeposit", &PhotPFChargedHadronIsoDeposit,   &b_PhotPFChargedHadronIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotPFNeutralHadronIsoDeposit", &PhotPFNeutralHadronIsoDeposit,   &b_PhotPFNeutralHadronIsoDeposit);
  //photonChain->SetBranchAddress(phots+"PhotPFGammaIsoDeposit",         &PhotPFGammaIsoDeposit, &b_PhotPFGammaIsoDeposit);

  photonChain->SetBranchAddress(phots+"PhotLoosePhoton",&PhotLoosePhoton,&b_PhotLoosePhoton);
  photonChain->SetBranchAddress(phots+"PhotTightPhoton",&PhotTightPhoton,&b_PhotTightPhoton);
  
  photonChain->SetBranchAddress(phots+"PhotSCEta", &PhotSCEta, &b_PhotSCEta);
  photonChain->SetBranchAddress(phots+"PhotSCPhi", &PhotSCPhi, &b_PhotSCPhi);
  photonChain->SetBranchAddress(phots+"PhotSCEn",  &PhotSCEn,  &b_PhotSCEn);
  photonChain->SetBranchAddress(phots+"PhotSCPt",  &PhotSCPt,  &b_PhotSCPt);
  photonChain->SetBranchAddress(phots+"PhotSCRawE",&PhotSCRawE,&b_PhotSCRawE);

  photonChain->SetBranchAddress(phots+"PhotTSeed",        &PhotTSeed,        &b_PhotTSeed);
  photonChain->SetBranchAddress(phots+"PhotESeed",        &PhotESeed,        &b_PhotESeed);
  photonChain->SetBranchAddress(phots+"PhotE2OverE9",     &PhotE2OverE9,     &b_PhotE2OverE9);
  photonChain->SetBranchAddress(phots+"PhotSwissCross",   &PhotSwissCross,   &b_PhotSwissCross);
  photonChain->SetBranchAddress(phots+"PhotHadOverEM",    &PhotHadOverEM,    &b_PhotHadOverEM);
  photonChain->SetBranchAddress(phots+"PhotSigmaIetaIeta",&PhotSigmaIetaIeta,&b_PhotSigmaIetaIeta);

  photonChain->SetBranchAddress(phots+"PhotIsEB",               &PhotIsEB,               &b_PhotIsEB);
  photonChain->SetBranchAddress(phots+"PhotIsEE",               &PhotIsEE,               &b_PhotIsEE);
  photonChain->SetBranchAddress(phots+"PhotIsEBGap",            &PhotIsEBGap,            &b_PhotIsEBGap);
  photonChain->SetBranchAddress(phots+"PhotIsEEGap",            &PhotIsEEGap,            &b_PhotIsEEGap);
  photonChain->SetBranchAddress(phots+"PhotIsEBEEGap",          &PhotIsEBEEGap,          &b_PhotIsEBEEGap);
  photonChain->SetBranchAddress(phots+"PhotHasPixelSeed",       &PhotHasPixelSeed,       &b_PhotHasPixelSeed);
  photonChain->SetBranchAddress(phots+"PhotHasConversionTracks",&PhotHasConversionTracks,&b_PhotHasConversionTracks);

  //Electrons
  leptonChain->SetBranchAddress(leps+"ElecVeto",  &ElecVeto,  &b_ElecVeto);
  leptonChain->SetBranchAddress(leps+"ElectronP4",&ElectronP4,&b_ElectronP4);
  leptonChain->SetBranchAddress(leps+"ElecN",     &ElecN,     &b_ElecN);

  leptonChain->SetBranchAddress(leps+"ElecdB",     &ElecdB,     &b_ElecdB);
  leptonChain->SetBranchAddress(leps+"ElecdBerr",  &ElecdBerr,  &b_ElecdBerr);
  leptonChain->SetBranchAddress(leps+"ElecCharge", &ElecCharge, &b_ElecCharge);

  leptonChain->SetBranchAddress(leps+"ElecTrkIso",    &ElecTrkIso,    &b_ElecTrkIso);
  leptonChain->SetBranchAddress(leps+"ElecECalIso",   &ElecECalIso,   &b_ElecECalIso);
  leptonChain->SetBranchAddress(leps+"ElecHCalIso",   &ElecHCalIso,   &b_ElecHCalIso);
  leptonChain->SetBranchAddress(leps+"ElecAllIso",    &ElecAllIso,    &b_ElecAllIso);

  leptonChain->SetBranchAddress(leps+"ElecPFAllParticleIso",   &ElecPFAllParticleIso,   &b_ElecPFAllParticleIso);
  leptonChain->SetBranchAddress(leps+"ElecPFChargedHadronIso", &ElecPFChargedHadronIso, &b_ElecPFChargedHadronIso);
  leptonChain->SetBranchAddress(leps+"ElecPFNeutralHadronIso", &ElecPFNeutralHadronIso, &b_ElecPFNeutralHadronIso);
  leptonChain->SetBranchAddress(leps+"ElecPFGammaIso",         &ElecPFGammaIso,         &b_ElecPFGammaIso);

  //leptonChain->SetBranchAddress(leps+"ElecTrkIsoDeposit",    &ElecTrkIsoDeposit,    &b_ElecTrkIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"ElecECalIsoDeposit",   &ElecECalIsoDeposit,   &b_ElecECalIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"ElecHCalIsoDeposit",   &ElecHCalIsoDeposit,   &b_ElecHCalIsoDeposit);
  //
  //leptonChain->SetBranchAddress(leps+"ElecPFAllParticleIsoDeposit",   &ElecPFAllParticleIsoDeposit,   &b_ElecPFAllParticleIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"ElecPFChargedHadronIsoDeposit", &ElecPFChargedHadronIsoDeposit, &b_ElecPFChargedHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"ElecPFNeutralHadronIsoDeposit", &ElecPFNeutralHadronIsoDeposit, &b_ElecPFNeutralHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"ElecPFGammaIsoDeposit",         &ElecPFGammaIsoDeposit,         &b_ElecPFGammaIsoDeposit);

  leptonChain->SetBranchAddress(leps+"ElecIdLoose",   &ElecIdLoose,   &b_ElecIdLoose);
  leptonChain->SetBranchAddress(leps+"ElecIdTight",   &ElecIdTight,   &b_ElecIdTight);
  leptonChain->SetBranchAddress(leps+"ElecIdRobLoose",&ElecIdRobLoose,&b_ElecIdRobLoose);
  leptonChain->SetBranchAddress(leps+"ElecIdRobTight",&ElecIdRobTight,&b_ElecIdRobTight);
  leptonChain->SetBranchAddress(leps+"ElecIdRobHighE",&ElecIdRobHighE,&b_ElecIdRobHighE);

  //leptonChain->SetBranchAddress(leps+"ElecPtMode",          &ElecPtMode,          &b_ElecPtMode);
  //leptonChain->SetBranchAddress(leps+"ElecChargeMode",      &ElecChargeMode,      &b_ElecChargeMode);
  //leptonChain->SetBranchAddress(leps+"ElecQOverPErrTrkMode",&ElecQOverPErrTrkMode,&b_ElecQOverPErrTrkMode);

  //leptonChain->SetBranchAddress(leps+"ElecVx",     &ElecVx,     &b_ElecVx);
  //leptonChain->SetBranchAddress(leps+"ElecVy",     &ElecVy,     &b_ElecVy);
  //leptonChain->SetBranchAddress(leps+"ElecVz",     &ElecVz,     &b_ElecVz);
  //leptonChain->SetBranchAddress(leps+"ElecPVDxy",  &ElecPVDxy,  &b_ElecPVDxy);
  leptonChain->SetBranchAddress(leps+"ElecBSDxy",  &ElecBSDxy,  &b_ElecBSDxy);
  leptonChain->SetBranchAddress(leps+"ElecDxy",    &ElecDxy,    &b_ElecDxy);
  leptonChain->SetBranchAddress(leps+"ElecDxyErr", &ElecDxyErr, &b_ElecDxyErr);
  leptonChain->SetBranchAddress(leps+"ElecD0",     &ElecD0,     &b_ElecD0);
  leptonChain->SetBranchAddress(leps+"ElecD0Err",  &ElecD0Err,  &b_ElecD0Err);
  leptonChain->SetBranchAddress(leps+"ElecDz",     &ElecDz,     &b_ElecDz);
  leptonChain->SetBranchAddress(leps+"ElecDzErr",  &ElecDzErr,  &b_ElecDzErr);
  leptonChain->SetBranchAddress(leps+"ElecPtTrk",  &ElecPtTrk,  &b_ElecPtTrk);

  leptonChain->SetBranchAddress(leps+"ElecHadOverEM",     &ElecHadOverEM,     &b_ElecHadOverEM);
  leptonChain->SetBranchAddress(leps+"ElecTrkChiNorm",    &ElecTrkChiNorm,    &b_ElecTrkChiNorm);
  leptonChain->SetBranchAddress(leps+"ElecCaloEnergy",    &ElecCaloEnergy,    &b_ElecCaloEnergy);
  leptonChain->SetBranchAddress(leps+"ElecE2OverE9",      &ElecE2OverE9,      &b_ElecE2OverE9);

  //leptonChain->SetBranchAddress(leps+"ElecE1x5",      &ElecE1x5,      &b_ElecE1x5);
  //leptonChain->SetBranchAddress(leps+"ElecE5x5",      &ElecE5x5,      &b_ElecE5x5);
  //leptonChain->SetBranchAddress(leps+"ElecE2x5Max",   &ElecE2x5Max,   &b_ElecE2x5Max);
  //leptonChain->SetBranchAddress(leps+"ElecFbrem",     &ElecFbrem,     &b_ElecFbrem);
  leptonChain->SetBranchAddress(leps+"ElecSwissCross",    &ElecSwissCross,    &b_ElecSwissCross);
  leptonChain->SetBranchAddress(leps+"ElecSigmaIetaIeta", &ElecSigmaIetaIeta, &b_ElecSigmaIetaIeta);

  //leptonChain->SetBranchAddress(leps+"ElecQOverPErrTrk",    &ElecQOverPErrTrk,    &b_ElecQOverPErrTrk);
  //leptonChain->SetBranchAddress(leps+"ElecPinTrk",          &ElecPinTrk,          &b_ElecPinTrk);
  //leptonChain->SetBranchAddress(leps+"ElecPoutTrk",         &ElecPoutTrk,         &b_ElecPoutTrk);
  //leptonChain->SetBranchAddress(leps+"ElecLostHits",        &ElecLostHits,        &b_ElecLostHits);
  leptonChain->SetBranchAddress(leps+"ElecValidHits",       &ElecValidHits,       &b_ElecValidHits);
  //leptonChain->SetBranchAddress(leps+"ElecEtaTrk",          &ElecEtaTrk,          &b_ElecEtaTrk);
  //leptonChain->SetBranchAddress(leps+"ElecPhiTrk",          &ElecPhiTrk,          &b_ElecPhiTrk);

  leptonChain->SetBranchAddress(leps+"ElecSCEta",           &ElecSCEta,           &b_ElecSCEta);
  leptonChain->SetBranchAddress(leps+"ElecSCPhi",           &ElecSCPhi,           &b_ElecSCPhi);
  leptonChain->SetBranchAddress(leps+"ElecSCEn",            &ElecSCEn,            &b_ElecSCEn);
  leptonChain->SetBranchAddress(leps+"ElecSCPt",            &ElecSCPt,            &b_ElecSCPt);
  leptonChain->SetBranchAddress(leps+"ElecSCRawE",          &ElecSCRawE,          &b_ElecSCRawE);
  leptonChain->SetBranchAddress(leps+"ElecWidthClusterEta", &ElecWidthClusterEta, &b_ElecWidthClusterEta);
  leptonChain->SetBranchAddress(leps+"ElecWidthClusterPhi", &ElecWidthClusterPhi, &b_ElecWidthClusterPhi);

  //Muon
  leptonChain->SetBranchAddress(leps+"MuonVeto",&MuonVeto,&b_MuonVeto);
  leptonChain->SetBranchAddress(leps+"MuonP4",  &MuonP4,  &b_MuonP4);
  leptonChain->SetBranchAddress(leps+"MuonN",   &MuonN,   &b_MuonN);

  leptonChain->SetBranchAddress(leps+"MuonCharge",       &MuonCharge,       &b_MuonCharge);

  leptonChain->SetBranchAddress(leps+"MuonTrkIso",  &MuonTrkIso, &b_MuonTrkIso);
  leptonChain->SetBranchAddress(leps+"MuonECalIso", &MuonECalIso,&b_MuonECalIso);
  leptonChain->SetBranchAddress(leps+"MuonHCalIso", &MuonHCalIso,&b_MuonHCalIso);
  leptonChain->SetBranchAddress(leps+"MuonAllIso",  &MuonAllIso, &b_MuonAllIso);

  leptonChain->SetBranchAddress(leps+"MuonPFAllParticleIso",   &MuonPFAllParticleIso,   &b_MuonPFAllParticleIso);
  leptonChain->SetBranchAddress(leps+"MuonPFChargedHadronIso", &MuonPFChargedHadronIso, &b_MuonPFChargedHadronIso);
  leptonChain->SetBranchAddress(leps+"MuonPFNeutralHadronIso", &MuonPFNeutralHadronIso, &b_MuonPFNeutralHadronIso);
  leptonChain->SetBranchAddress(leps+"MuonPFGammaIso",         &MuonPFGammaIso,         &b_MuonPFGammaIso);

  //leptonChain->SetBranchAddress(leps+"MuonTrkIsoDeposit",    &MuonTrkIsoDeposit,    &b_MuonTrkIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonECalIsoDeposit",   &MuonECalIsoDeposit,   &b_MuonECalIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonHCalIsoDeposit",   &MuonHCalIsoDeposit,   &b_MuonHCalIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonECalIsoDepositR03",&MuonECalIsoDepositR03,&b_MuonECalIsoDepositR03);
  //leptonChain->SetBranchAddress(leps+"MuonHCalIsoDepositR03",&MuonHCalIsoDepositR03,&b_MuonHCalIsoDepositR03);

  //leptonChain->SetBranchAddress(leps+"MuonPFAllParticleIsoDeposit",   &MuonPFAllParticleIsoDeposit,   &b_MuonPFAllParticleIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonPFChargedHadronIsoDeposit", &MuonPFChargedHadronIsoDeposit, &b_MuonPFChargedHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonPFNeutralHadronIsoDeposit", &MuonPFNeutralHadronIsoDeposit, &b_MuonPFNeutralHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"MuonPFGammaIsoDeposit",         &MuonPFGammaIsoDeposit,         &b_MuonPFGammaIsoDeposit);


  leptonChain->SetBranchAddress(leps+"MuonIsGlobal",               &MuonIsGlobal,              &b_MuonIsGlobal);
  leptonChain->SetBranchAddress(leps+"MuonIsStandAlone",           &MuonIsStandAlone,          &b_MuonIsStandAlone);
  leptonChain->SetBranchAddress(leps+"MuonIsTracker",              &MuonIsTracker,             &b_MuonIsTracker);
  leptonChain->SetBranchAddress(leps+"MuonGlobalMuonPromptTight",  &MuonGlobalMuonPromptTight, &b_MuonGlobalMuonPromptTight);
  //leptonChain->SetBranchAddress(leps+"MuonAllArbitrated",          &MuonAllArbitrated,         &b_MuonAllArbitrated);
  //leptonChain->SetBranchAddress(leps+"MuonTrackerMuonArbitrated",  &MuonTrackerMuonArbitrated, &b_MuonTrackerMuonArbitrated);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationLoose",     &MuonTMLastStationLoose,    &b_MuonTMLastStationLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationTight",     &MuonTMLastStationTight,    &b_MuonTMLastStationTight);
  //leptonChain->SetBranchAddress(leps+"MuonTM2DCompatibilityLoose", &MuonTM2DCompatibilityLoose,&b_MuonTM2DCompatibilityLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTM2DCompatibilityTight", &MuonTM2DCompatibilityTight,&b_MuonTM2DCompatibilityTight);
  //leptonChain->SetBranchAddress(leps+"MuonTMOneStationLoose",      &MuonTMOneStationLoose,     &b_MuonTMOneStationLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTMOneStationTight",      &MuonTMOneStationTight,     &b_MuonTMOneStationTight);
  //
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedLowPtLoose",      &MuonTMLastStationOptimizedLowPtLoose,      &b_MuonTMLastStationOptimizedLowPtLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedLowPtTight",      &MuonTMLastStationOptimizedLowPtTight,      &b_MuonTMLastStationOptimizedLowPtTight);
  //leptonChain->SetBranchAddress(leps+"MuonGMTkChiCompatibility",                  &MuonGMTkChiCompatibility,                  &b_MuonGMTkChiCompatibility);
  //leptonChain->SetBranchAddress(leps+"MuonGMStaChiCompatibility",                 &MuonGMStaChiCompatibility,                 &b_MuonGMStaChiCompatibility);
  //leptonChain->SetBranchAddress(leps+"MuonGMTkKinkTight",                         &MuonGMTkKinkTight,                         &b_MuonGMTkKinkTight);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationAngLoose",                 &MuonTMLastStationAngLoose,                 &b_MuonTMLastStationAngLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationAngTight",                 &MuonTMLastStationAngTight,                 &b_MuonTMLastStationAngTight);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedBarrelLowPtLoose",&MuonTMLastStationOptimizedBarrelLowPtLoose,&b_MuonTMLastStationOptimizedBarrelLowPtLoose);
  //leptonChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedBarrelLowPtTight",&MuonTMLastStationOptimizedBarrelLowPtTight,&b_MuonTMLastStationOptimizedBarrelLowPtTight);

  leptonChain->SetBranchAddress(leps+"MuonCombChi2",     &MuonCombChi2,     &b_MuonCombChi2);
  leptonChain->SetBranchAddress(leps+"MuonCombNdof",     &MuonCombNdof,     &b_MuonCombNdof);
  //leptonChain->SetBranchAddress(leps+"MuonCombVx",       &MuonCombVx,       &b_MuonCombVx);
  //leptonChain->SetBranchAddress(leps+"MuonCombVy",       &MuonCombVy,       &b_MuonCombVy);
  //leptonChain->SetBranchAddress(leps+"MuonCombVz",       &MuonCombVz,       &b_MuonCombVz);
  leptonChain->SetBranchAddress(leps+"MuonCombPVDxy",    &MuonCombPVDxy,    &b_MuonCombPVDxy);
  leptonChain->SetBranchAddress(leps+"MuonCombBSDxy",    &MuonCombBSDxy,    &b_MuonCombBSDxy);
  leptonChain->SetBranchAddress(leps+"MuonCombDxy",      &MuonCombDxy,      &b_MuonCombDxy);
  leptonChain->SetBranchAddress(leps+"MuonCombDxyErr",   &MuonCombDxyErr,   &b_MuonCombDxyErr);
  leptonChain->SetBranchAddress(leps+"MuonCombD0",       &MuonCombD0,       &b_MuonCombD0);
  leptonChain->SetBranchAddress(leps+"MuonCombD0Err",    &MuonCombD0Err,    &b_MuonCombD0Err);
  leptonChain->SetBranchAddress(leps+"MuonCombDz",       &MuonCombDz,       &b_MuonCombDz);
  leptonChain->SetBranchAddress(leps+"MuonCombDzErr",    &MuonCombDzErr,    &b_MuonCombDzErr);
  leptonChain->SetBranchAddress(leps+"MuonCombPt",       &MuonCombPt,       &b_MuonCombPt);
  leptonChain->SetBranchAddress(leps+"MuonCombPz",       &MuonCombPz,       &b_MuonCombPz);
  leptonChain->SetBranchAddress(leps+"MuonCombP",        &MuonCombP,        &b_MuonCombP);
  leptonChain->SetBranchAddress(leps+"MuonCombEta",      &MuonCombEta,      &b_MuonCombEta);
  leptonChain->SetBranchAddress(leps+"MuonCombPhi",      &MuonCombPhi,      &b_MuonCombPhi);
  leptonChain->SetBranchAddress(leps+"MuonCombCharge",   &MuonCombCharge,   &b_MuonCombCharge);
  leptonChain->SetBranchAddress(leps+"MuonCombChi",      &MuonCombChi,      &b_MuonCombChi);
  leptonChain->SetBranchAddress(leps+"MuonCombQOverPErr",&MuonCombQOverPErr,&b_MuonCombQOverPErr);
  leptonChain->SetBranchAddress(leps+"MuonCombValidHits",&MuonCombValidHits,&b_MuonCombValidHits);

  leptonChain->SetBranchAddress(leps+"MuonStandValidHits",&MuonStandValidHits,&b_MuonStandValidHits);
  leptonChain->SetBranchAddress(leps+"MuonStandLostHits", &MuonStandLostHits, &b_MuonStandLostHits);
  leptonChain->SetBranchAddress(leps+"MuonStandPt",       &MuonStandPt,       &b_MuonStandPt);
  leptonChain->SetBranchAddress(leps+"MuonStandPz",       &MuonStandPz,       &b_MuonStandPz);
  leptonChain->SetBranchAddress(leps+"MuonStandP",        &MuonStandP,        &b_MuonStandP);
  leptonChain->SetBranchAddress(leps+"MuonStandEta",      &MuonStandEta,      &b_MuonStandEta);
  leptonChain->SetBranchAddress(leps+"MuonStandPhi",      &MuonStandPhi,      &b_MuonStandPhi);
  leptonChain->SetBranchAddress(leps+"MuonStandCharge",   &MuonStandCharge,   &b_MuonStandCharge);
  leptonChain->SetBranchAddress(leps+"MuonStandChi",      &MuonStandChi,      &b_MuonStandChi);
  leptonChain->SetBranchAddress(leps+"MuonStandQOverPErr",&MuonStandQOverPErr,&b_MuonStandQOverPErr);

  leptonChain->SetBranchAddress(leps+"MuonTrkChiNorm",   &MuonTrkChiNorm,   &b_MuonTrkChiNorm);
  leptonChain->SetBranchAddress(leps+"MuonTrkValidHits", &MuonTrkValidHits, &b_MuonTrkValidHits);
  leptonChain->SetBranchAddress(leps+"MuonTrkLostHits",  &MuonTrkLostHits,  &b_MuonTrkLostHits);
  leptonChain->SetBranchAddress(leps+"MuonTrkPVDxy",     &MuonTrkPVDxy,     &b_MuonTrkPVDxy);
  leptonChain->SetBranchAddress(leps+"MuonTrkBSDxy",     &MuonTrkBSDxy,     &b_MuonTrkBSDxy);
  leptonChain->SetBranchAddress(leps+"MuonTrkDxy",       &MuonTrkDxy,       &b_MuonTrkDxy);
  leptonChain->SetBranchAddress(leps+"MuonTrkDxyErr",    &MuonTrkDxyErr,    &b_MuonTrkDxyErr);
  leptonChain->SetBranchAddress(leps+"MuonTrkD0",        &MuonTrkD0,        &b_MuonTrkD0);
  leptonChain->SetBranchAddress(leps+"MuonTrkD0Err",     &MuonTrkD0Err,     &b_MuonTrkD0Err);
  leptonChain->SetBranchAddress(leps+"MuonTrkPt",        &MuonTrkPt,        &b_MuonTrkPt);
  leptonChain->SetBranchAddress(leps+"MuonTrkPz",        &MuonTrkPz,        &b_MuonTrkPz);
  leptonChain->SetBranchAddress(leps+"MuonTrkP",         &MuonTrkP,         &b_MuonTrkP);
  leptonChain->SetBranchAddress(leps+"MuonTrkEta",       &MuonTrkEta,       &b_MuonTrkEta);
  leptonChain->SetBranchAddress(leps+"MuonTrkPhi",       &MuonTrkPhi,       &b_MuonTrkPhi);
  leptonChain->SetBranchAddress(leps+"MuonTrkCharge",    &MuonTrkCharge,    &b_MuonTrkCharge);
  leptonChain->SetBranchAddress(leps+"MuonTrkChi",       &MuonTrkChi,       &b_MuonTrkChi);
  leptonChain->SetBranchAddress(leps+"MuonTrkQOverPErr", &MuonTrkQOverPErr, &b_MuonTrkQOverPErr);
  leptonChain->SetBranchAddress(leps+"MuonTrkOuterZ",    &MuonTrkOuterZ,    &b_MuonTrkOuterZ);
  leptonChain->SetBranchAddress(leps+"MuonTrkOuterR",    &MuonTrkOuterR,    &b_MuonTrkOuterR);

//  leptonChain->SetBranchAddress(leps+"MuonPickyCharge",       &MuonPickyCharge,       &b_MuonPickyCharge);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkChiNorm",   &MuonPickyTrkChiNorm,   &b_MuonPickyTrkChiNorm);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkValidHits", &MuonPickyTrkValidHits, &b_MuonPickyTrkValidHits);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkLostHits",  &MuonPickyTrkLostHits,  &b_MuonPickyTrkLostHits);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkPVDxy",     &MuonPickyTrkPVDxy,     &b_MuonPickyTrkPVDxy);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkBSDxy",     &MuonPickyTrkBSDxy,     &b_MuonPickyTrkBSDxy);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkDxy",       &MuonPickyTrkDxy,       &b_MuonPickyTrkDxy);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkDxyErr",    &MuonPickyTrkDxyErr,    &b_MuonPickyTrkDxyErr);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkD0",        &MuonPickyTrkD0,        &b_MuonPickyTrkD0);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkD0Err",     &MuonPickyTrkD0Err,     &b_MuonPickyTrkD0Err);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkPt",        &MuonPickyTrkPt,        &b_MuonPickyTrkPt);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkPz",        &MuonPickyTrkPz,        &b_MuonPickyTrkPz);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkP",         &MuonPickyTrkP,         &b_MuonPickyTrkP);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkEta",       &MuonPickyTrkEta,       &b_MuonPickyTrkEta);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkPhi",       &MuonPickyTrkPhi,       &b_MuonPickyTrkPhi);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkCharge",    &MuonPickyTrkCharge,    &b_MuonPickyTrkCharge);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkChi",       &MuonPickyTrkChi,       &b_MuonPickyTrkChi);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkQOverPErr", &MuonPickyTrkQOverPErr, &b_MuonPickyTrkQOverPErr);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkOuterZ",    &MuonPickyTrkOuterZ,    &b_MuonPickyTrkOuterZ);
//  leptonChain->SetBranchAddress(leps+"MuonPickyTrkOuterR",    &MuonPickyTrkOuterR,    &b_MuonPickyTrkOuterR);
//
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSCharge",       &MuonTPFMSCharge,       &b_MuonTPFMSCharge);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkChiNorm",   &MuonTPFMSTrkChiNorm,   &b_MuonTPFMSTrkChiNorm);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkValidHits", &MuonTPFMSTrkValidHits, &b_MuonTPFMSTrkValidHits);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkLostHits",  &MuonTPFMSTrkLostHits,  &b_MuonTPFMSTrkLostHits);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkPVDxy",     &MuonTPFMSTrkPVDxy,     &b_MuonTPFMSTrkPVDxy);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkBSDxy",     &MuonTPFMSTrkBSDxy,     &b_MuonTPFMSTrkBSDxy);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkDxy",       &MuonTPFMSTrkDxy,       &b_MuonTPFMSTrkDxy);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkDxyErr",    &MuonTPFMSTrkDxyErr,    &b_MuonTPFMSTrkDxyErr);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkD0",        &MuonTPFMSTrkD0,        &b_MuonTPFMSTrkD0);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkD0Err",     &MuonTPFMSTrkD0Err,     &b_MuonTPFMSTrkD0Err);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkPt",        &MuonTPFMSTrkPt,        &b_MuonTPFMSTrkPt);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkPz",        &MuonTPFMSTrkPz,        &b_MuonTPFMSTrkPz);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkP",         &MuonTPFMSTrkP,         &b_MuonTPFMSTrkP);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkEta",       &MuonTPFMSTrkEta,       &b_MuonTPFMSTrkEta);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkPhi",       &MuonTPFMSTrkPhi,       &b_MuonTPFMSTrkPhi);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkCharge",    &MuonTPFMSTrkCharge,    &b_MuonTPFMSTrkCharge);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkChi",       &MuonTPFMSTrkChi,       &b_MuonTPFMSTrkChi);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkQOverPErr", &MuonTPFMSTrkQOverPErr, &b_MuonTPFMSTrkQOverPErr);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkOuterZ",    &MuonTPFMSTrkOuterZ,    &b_MuonTPFMSTrkOuterZ);
//  leptonChain->SetBranchAddress(leps+"MuonTPFMSTrkOuterR",    &MuonTPFMSTrkOuterR,    &b_MuonTPFMSTrkOuterR);

  //Taus
  leptonChain->SetBranchAddress(leps+"TauVeto",  &TauVeto,  &b_TauVeto);
  leptonChain->SetBranchAddress(leps+"TauP4",    &TauP4,    &b_TauP4);
  leptonChain->SetBranchAddress(leps+"TauN",     &TauN,     &b_TauN);

  leptonChain->SetBranchAddress(leps+"TauCharge",    &TauCharge,    &b_TauCharge);

  leptonChain->SetBranchAddress(leps+"TauTrkIso",    &TauTrkIso,    &b_TauTrkIso);
  leptonChain->SetBranchAddress(leps+"TauECalIso",   &TauECalIso,   &b_TauECalIso);
  leptonChain->SetBranchAddress(leps+"TauHCalIso",   &TauHCalIso,   &b_TauHCalIso);
  leptonChain->SetBranchAddress(leps+"TauAllIso",    &TauAllIso,    &b_TauAllIso);

  leptonChain->SetBranchAddress(leps+"TauPFAllParticleIso",   &TauPFAllParticleIso,   &b_TauPFAllParticleIso);
  leptonChain->SetBranchAddress(leps+"TauPFChargedHadronIso", &TauPFChargedHadronIso, &b_TauPFChargedHadronIso);
  leptonChain->SetBranchAddress(leps+"TauPFNeutralHadronIso", &TauPFNeutralHadronIso, &b_TauPFNeutralHadronIso);
  leptonChain->SetBranchAddress(leps+"TauPFGammaIso",         &TauPFGammaIso,         &b_TauPFGammaIso);

  //leptonChain->SetBranchAddress(leps+"TauTrkIsoDeposit",    &TauTrkIsoDeposit,    &b_TauTrkIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"TauECalIsoDeposit",   &TauECalIsoDeposit,   &b_TauECalIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"TauHCalIsoDeposit",   &TauHCalIsoDeposit,   &b_TauHCalIsoDeposit);
  //
  //leptonChain->SetBranchAddress(leps+"TauPFAllParticleIsoDeposit",   &TauPFAllParticleIsoDeposit,   &b_TauPFAllParticleIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"TauPFChargedHadronIsoDeposit", &TauPFChargedHadronIsoDeposit, &b_TauPFChargedHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"TauPFNeutralHadronIsoDeposit", &TauPFNeutralHadronIsoDeposit, &b_TauPFNeutralHadronIsoDeposit);
  //leptonChain->SetBranchAddress(leps+"TauPFGammaIsoDeposit",         &TauPFGammaIsoDeposit,         &b_TauPFGammaIsoDeposit);

  leptonChain->SetBranchAddress(leps+"TauIdElec",       &TauIdElec,       &b_TauIdElec);
  leptonChain->SetBranchAddress(leps+"TauIdMuon",       &TauIdMuon,       &b_TauIdMuon);

  leptonChain->SetBranchAddress(leps+"TauIdIso",        &TauIdIso,        &b_TauIdIso);
  leptonChain->SetBranchAddress(leps+"TauIdIsoLeadPi",  &TauIdIsoLeadPi,  &b_TauIdIsoLeadPi);

  leptonChain->SetBranchAddress(leps+"TauIdEcalIso",        &TauIdEcalIso,        &b_TauIdEcalIso);
  leptonChain->SetBranchAddress(leps+"TauIdEcalIsoLeadPi",  &TauIdEcalIsoLeadPi,  &b_TauIdEcalIsoLeadPi);

  leptonChain->SetBranchAddress(leps+"TauIdLeadPiPt",    &TauIdLeadPiPt,    &b_TauIdLeadPiPt);
  leptonChain->SetBranchAddress(leps+"TauIdLeadTrk",     &TauIdLeadTrk,     &b_TauIdLeadTrk);
  leptonChain->SetBranchAddress(leps+"TauIdLeadTrkPt",   &TauIdLeadTrkPt,   &b_TauIdLeadTrkPt);

  leptonChain->SetBranchAddress(leps+"TauIdTrkIso",        &TauIdTrkIso,        &b_TauIdTrkIso);
  leptonChain->SetBranchAddress(leps+"TauIdTrkIsoLeadPi",  &TauIdTrkIsoLeadPi,  &b_TauIdTrkIsoLeadPi);

  leptonChain->SetBranchAddress(leps+"TauIdNCfrFull",   &TauIdNCfrFull,   &b_TauIdNCfrFull);
  leptonChain->SetBranchAddress(leps+"TauIdNCfrHalf",   &TauIdNCfrHalf,   &b_TauIdNCfrHalf);
  leptonChain->SetBranchAddress(leps+"TauIdNCfrTenth",  &TauIdNCfrTenth,  &b_TauIdNCfrTenth);
  leptonChain->SetBranchAddress(leps+"TauIdNCfrQuarter",&TauIdNCfrQuarter,&b_TauIdNCfrQuarter);

  leptonChain->SetBranchAddress(leps+"TauVx",     &TauVx,     &b_TauVx);
  leptonChain->SetBranchAddress(leps+"TauVy",     &TauVy,     &b_TauVy);
  leptonChain->SetBranchAddress(leps+"TauVz",     &TauVz,     &b_TauVz);
  leptonChain->SetBranchAddress(leps+"TauPVDxy",  &TauPVDxy,  &b_TauPVDxy);
  leptonChain->SetBranchAddress(leps+"TauBSDxy",  &TauBSDxy,  &b_TauBSDxy);
  leptonChain->SetBranchAddress(leps+"TauDxy",    &TauDxy,    &b_TauDxy);
  leptonChain->SetBranchAddress(leps+"TauDxyErr", &TauDxyErr, &b_TauDxyErr);
  leptonChain->SetBranchAddress(leps+"TauD0",     &TauD0,     &b_TauD0);
  leptonChain->SetBranchAddress(leps+"TauD0Err",  &TauD0Err,  &b_TauD0Err);
  leptonChain->SetBranchAddress(leps+"TauDz",     &TauDz,     &b_TauDz);
  leptonChain->SetBranchAddress(leps+"TauDzErr",  &TauDzErr,  &b_TauDzErr);


  if (leptonChain->GetBranch(leps+"TauCaloLeadTrkSignedIP") ) {
    leptonChain->SetBranchAddress(leps+"TauCaloLeadTrkSignedIP",           &TauCaloLeadTrkSignedIP,       &b_TauCaloLeadTrkSignedIP);
    leptonChain->SetBranchAddress(leps+"TauCaloLeadTrkHcal3x3EtSum",       &TauCaloLeadTrkHcal3x3EtSum,   &b_TauCaloLeadTrkHcal3x3EtSum);
    leptonChain->SetBranchAddress(leps+"TauCaloCaloLeadTrkHcal3x3HotDEta", &TauCaloLeadTrkHcal3x3HotDEta, &b_TauCaloLeadTrkHcal3x3HotDEta);
    leptonChain->SetBranchAddress(leps+"TauCaloCaloSignalTrkMInv"        , &TauCaloSignalTrkMInv        , &b_TauCaloSignalTrkMInv        );
    leptonChain->SetBranchAddress(leps+"TauCaloCaloTrkMInv"              , &TauCaloTrkMInv              , &b_TauCaloTrkMInv              );
    leptonChain->SetBranchAddress(leps+"TauCaloCaloIsoTrkPtSum"          , &TauCaloIsoTrkPtSum          , &b_TauCaloIsoTrkPtSum          );
    leptonChain->SetBranchAddress(leps+"TauCaloCaloIsoEcalEtSum"         , &TauCaloIsoEcalEtSum         , &b_TauCaloIsoEcalEtSum         );
    leptonChain->SetBranchAddress(leps+"TauCaloCaloMaxEtHCAL"            , &TauCaloMaxEtHCAL            , &b_TauCaloMaxEtHCAL            );
  }
  
  if (leptonChain->GetBranch(leps+"TauPFPFIsoChargedHadPtSum") ) {
    leptonChain->SetBranchAddress(leps+"TauPFPFIsoChargedHadPtSum",   &TauPFIsoChargedHadPtSum,   &b_TauPFIsoChargedHadPtSum);
    leptonChain->SetBranchAddress(leps+"TauPFPFIsoGammaEtSum"     ,   &TauPFIsoGammaEtSum     ,   &b_TauPFIsoGammaEtSum     );
    leptonChain->SetBranchAddress(leps+"TauPFPFHcalClusterMaxEt"  ,   &TauPFHcalClusterMaxEt  ,   &b_TauPFHcalClusterMaxEt  );
    leptonChain->SetBranchAddress(leps+"TauPFPFEFrac_em"          ,   &TauPFEFrac_em          ,   &b_TauPFEFrac_em          );
    leptonChain->SetBranchAddress(leps+"TauPFPFHcalTotalOverPLead",   &TauPFHcalTotalOverPLead,   &b_TauPFHcalTotalOverPLead);
    leptonChain->SetBranchAddress(leps+"TauPFPFHcalMaxOverPLead"  ,   &TauPFHcalMaxOverPLead  ,   &b_TauPFHcalMaxOverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFPFHcal3x3OverPLead"  ,   &TauPFHcal3x3OverPLead  ,   &b_TauPFHcal3x3OverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFPFEcalStripOverPLead",   &TauPFEcalStripOverPLead,   &b_TauPFEcalStripOverPLead);
    leptonChain->SetBranchAddress(leps+"TauPFPFBremRecOverPLead"  ,   &TauPFBremRecOverPLead  ,   &b_TauPFBremRecOverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFPFElePreIDOut"       ,   &TauPFElePreIDOut       ,   &b_TauPFElePreIDOut       );
    leptonChain->SetBranchAddress(leps+"TauPFPFMuonCaloComp"      ,   &TauPFMuonCaloComp      ,   &b_TauPFMuonCaloComp      );
    leptonChain->SetBranchAddress(leps+"TauPFPFMuonSegComp"       ,   &TauPFMuonSegComp       ,   &b_TauPFMuonSegComp       );
  }
  else if (leptonChain->GetBranch(leps+"TauPFIsoChargedHadPtSum") ) {
    leptonChain->SetBranchAddress(leps+"TauPFIsoChargedHadPtSum",   &TauPFIsoChargedHadPtSum,   &b_TauPFIsoChargedHadPtSum);
    leptonChain->SetBranchAddress(leps+"TauPFIsoGammaEtSum"     ,   &TauPFIsoGammaEtSum     ,   &b_TauPFIsoGammaEtSum     );
    leptonChain->SetBranchAddress(leps+"TauPFHcalClusterMaxEt"  ,   &TauPFHcalClusterMaxEt  ,   &b_TauPFHcalClusterMaxEt  );
    leptonChain->SetBranchAddress(leps+"TauPFEFrac_em"          ,   &TauPFEFrac_em          ,   &b_TauPFEFrac_em          );
    leptonChain->SetBranchAddress(leps+"TauPFHcalTotalOverPLead",   &TauPFHcalTotalOverPLead,   &b_TauPFHcalTotalOverPLead);
    leptonChain->SetBranchAddress(leps+"TauPFHcalMaxOverPLead"  ,   &TauPFHcalMaxOverPLead  ,   &b_TauPFHcalMaxOverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFHcal3x3OverPLead"  ,   &TauPFHcal3x3OverPLead  ,   &b_TauPFHcal3x3OverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFEcalStripOverPLead",   &TauPFEcalStripOverPLead,   &b_TauPFEcalStripOverPLead);
    leptonChain->SetBranchAddress(leps+"TauPFBremRecOverPLead"  ,   &TauPFBremRecOverPLead  ,   &b_TauPFBremRecOverPLead  );
    leptonChain->SetBranchAddress(leps+"TauPFElePreIDOut"       ,   &TauPFElePreIDOut       ,   &b_TauPFElePreIDOut       );
    leptonChain->SetBranchAddress(leps+"TauPFMuonCaloComp"      ,   &TauPFMuonCaloComp      ,   &b_TauPFMuonCaloComp      );
    leptonChain->SetBranchAddress(leps+"TauPFMuonSegComp"       ,   &TauPFMuonSegComp       ,   &b_TauPFMuonSegComp       );
  }

  leptonChain->SetBranchAddress(leps+"TauEtaEtaMoment",   &TauEtaEtaMom,   &b_TauEtaEtaMom);
  leptonChain->SetBranchAddress(leps+"TauPhiPhiMoment",   &TauPhiPhiMom,   &b_TauPhiPhiMom);
  leptonChain->SetBranchAddress(leps+"TauEtaPhiMoment",   &TauEtaPhiMom,   &b_TauEtaPhiMom);


  //Beamspot variables
  //vertexChain->SetBranchAddress("beamspotX0",        &beamspotX0,        &b_beamspotX0);
  //vertexChain->SetBranchAddress("beamspotY0",        &beamspotY0,        &b_beamspotY0);
  //vertexChain->SetBranchAddress("beamspotZ0",        &beamspotZ0,        &b_beamspotZ0);
  //vertexChain->SetBranchAddress("beamspotX0Err",     &beamspotX0Err,     &b_beamspotX0Err);
  //vertexChain->SetBranchAddress("beamspotY0Err",     &beamspotY0Err,     &b_beamspotY0Err);
  //vertexChain->SetBranchAddress("beamspotZ0Err",     &beamspotZ0Err,     &b_beamspotZ0Err);
  //vertexChain->SetBranchAddress("beamspotWidthX",    &beamspotWidthX,    &b_beamspotWidthX);
  //vertexChain->SetBranchAddress("beamspotWidthY",    &beamspotWidthY,    &b_beamspotWidthY);
  //vertexChain->SetBranchAddress("beamspotWidthXErr", &beamspotWidthXErr, &b_beamspotWidthXErr);
  //vertexChain->SetBranchAddress("beamspotWidthYErr", &beamspotWidthYErr, &b_beamspotWidthYErr);
  //vertexChain->SetBranchAddress("beamspotdxdz",      &beamspotdxdz,      &b_beamspotdxdz);
  //vertexChain->SetBranchAddress("beamspotdydz",      &beamspotdydz,      &b_beamspotdydz);
  //vertexChain->SetBranchAddress("beamspotdxdzErr",   &beamspotdxdzErr,   &b_beamspotdxdzErr);
  //vertexChain->SetBranchAddress("beamspotdydzErr",   &beamspotdydzErr,   &b_beamspotdydzErr);
  //vertexChain->SetBranchAddress("beamspotSigmaZ0",   &beamspotSigmaZ0,   &b_beamspotSigmaZ0);
  //vertexChain->SetBranchAddress("beamspotSigmaZ0Err",&beamspotSigmaZ0Err,&b_beamspotSigmaZ0Err);
  //vertexChain->SetBranchAddress("beamspotEmittanceX",&beamspotEmittanceX,&b_beamspotEmittanceX);
  //vertexChain->SetBranchAddress("beamspotEmittanceY",&beamspotEmittanceY,&b_beamspotEmittanceY);
  //vertexChain->SetBranchAddress("beamspotBetaStar",  &beamspotBetaStar,  &b_beamspotBetaStar);

  vertexChain->SetBranchAddress("nVtx",                &nVtx,                 &b_nVtx);
  vertexChain->SetBranchAddress("VertexChi2",          &VertexChi2,           &b_VertexChi2);
  vertexChain->SetBranchAddress("VertexNdof",          &VertexNdof,           &b_VertexNdof);
  vertexChain->SetBranchAddress("VertexNTrks",         &VertexNTrks,          &b_VertexNTrks);
  vertexChain->SetBranchAddress("VertexSumTrkPt",      &VertexSumTrkPt,       &b_VertexSumTrkPt);
  vertexChain->SetBranchAddress("VertexSumTrkPt2",     &VertexSumTrkPt2,      &b_VertexSumTrkPt2);
  vertexChain->SetBranchAddress("VertexNRawTrks",      &VertexNRawTrks,       &b_VertexNRawTrks);
  vertexChain->SetBranchAddress("VertexIsValid",       &VertexIsValid,        &b_VertexIsValid);
  vertexChain->SetBranchAddress("VertexNormalizedChi2",&VertexNormalizedChi2, &b_VertexNormalizedChi2);
  vertexChain->SetBranchAddress("VertexX",             &VertexX,              &b_VertexX);
  vertexChain->SetBranchAddress("VertexY",             &VertexY,              &b_VertexY);
  vertexChain->SetBranchAddress("VertexZ",             &VertexZ,              &b_VertexZ);
  vertexChain->SetBranchAddress("Vertexd0",            &Vertexd0,             &b_Vertexd0);
  vertexChain->SetBranchAddress("VertexdX",            &VertexdX,             &b_VertexdX);
  vertexChain->SetBranchAddress("VertexdY",            &VertexdY,             &b_VertexdY);
  vertexChain->SetBranchAddress("VertexdZ",            &VertexdZ,             &b_VertexdZ);

  //if (trackChain->GetBranch("MPTPhi") ) {
  //  trackChain->SetBranchAddress("MPTPhi",&MPTPhi,&b_MPTPhi);
  //  trackChain->SetBranchAddress("MPTPx", &MPTPx, &b_MPTPx);
  //  trackChain->SetBranchAddress("MPTPy", &MPTPy, &b_MPTPy);
  //  trackChain->SetBranchAddress("MPTPz", &MPTPz, &b_MPTPz);
  //}
  
  triggerChain->SetBranchAddress("HLTTriggered",&HLTTriggered,&b_HLTTriggered);
  triggerChain->SetBranchAddress("HLTPrescaled",&HLTPrescaled,&b_HLTPrescaled);

  
  leptonChain->SetBranchAddress(leps+"ElecGenP4",          &ElecGenP4,          &b_ElecGenP4);
  leptonChain->SetBranchAddress(leps+"ElecGenPdgId",       &ElecGenPdgId,       &b_ElecGenPdgId);
  leptonChain->SetBranchAddress(leps+"ElecGenStatus",      &ElecGenStatus,      &b_ElecGenStatus);
  leptonChain->SetBranchAddress(leps+"ElecGenMother",      &ElecGenMother,      &b_ElecGenMother);
  leptonChain->SetBranchAddress(leps+"ElecGenMotherStatus",&ElecGenMotherStatus,&b_ElecGenMotherStatus);
  
  leptonChain->SetBranchAddress(leps+"MuonGenP4",          &MuonGenP4,          &b_MuonGenP4);
  leptonChain->SetBranchAddress(leps+"MuonGenPdgId",       &MuonGenPdgId,       &b_MuonGenPdgId);
  leptonChain->SetBranchAddress(leps+"MuonGenStatus",      &MuonGenStatus,      &b_MuonGenStatus);
  leptonChain->SetBranchAddress(leps+"MuonGenMother",      &MuonGenMother,      &b_MuonGenMother);
  leptonChain->SetBranchAddress(leps+"MuonGenMotherStatus",&MuonGenMotherStatus,&b_MuonGenMotherStatus);
  
  leptonChain->SetBranchAddress(leps+"TauGen",            &TauGen,            &b_TauGen);
  leptonChain->SetBranchAddress(leps+"TauGenP4",          &TauGenP4,          &b_TauGenP4);
  leptonChain->SetBranchAddress(leps+"TauGenPdgId",       &TauGenPdgId,       &b_TauGenPdgId);
  leptonChain->SetBranchAddress(leps+"TauGenStatus",      &TauGenStatus,      &b_TauGenStatus);
  leptonChain->SetBranchAddress(leps+"TauGenMother",      &TauGenMother,      &b_TauGenMother);
  leptonChain->SetBranchAddress(leps+"TauGenMotherStatus",&TauGenMotherStatus,&b_TauGenMotherStatus);
  leptonChain->SetBranchAddress(leps+"TauGenJetP4",       &TauGenJetP4,       &b_TauGenJetP4);
  
  photonChain->SetBranchAddress(phots+"PhotGenP4",          &PhotGenP4,          &b_PhotGenP4);
  photonChain->SetBranchAddress(phots+"PhotGenPdgId",       &PhotGenPdgId,       &b_PhotGenPdgId);
  photonChain->SetBranchAddress(phots+"PhotGenStatus",      &PhotGenStatus,      &b_PhotGenStatus);
  photonChain->SetBranchAddress(phots+"PhotGenMother",      &PhotGenMother,      &b_PhotGenMother);
  photonChain->SetBranchAddress(phots+"PhotGenMotherStatus",&PhotGenMotherStatus,&b_PhotGenMotherStatus);
  
  if (!isData_) {
    std::cout<<"setting up branches for gen particles"<<std::endl;
    genChain->SetBranchAddress("genN",         &genN,        &b_genN);
    genChain->SetBranchAddress("genP4",        &genP4,       &b_genP4 );
    genChain->SetBranchAddress("genId",        &genId,       &b_genId);
    genChain->SetBranchAddress("genStatus",    &genStatus,   &b_genStatus);
    genChain->SetBranchAddress("genMother",    &genMother,   &b_genMother);
    genChain->SetBranchAddress("genDaughters", &genDaughters,&b_genDaughters);
    
    genChain->SetBranchAddress("genParticleN",        &genParticleN,        &b_genParticleN);
    genChain->SetBranchAddress("genParticleP4",       &genParticleP4,       &b_genParticleP4);
    genChain->SetBranchAddress("genParticleId",       &genParticleId,       &b_genParticleId);
    genChain->SetBranchAddress("genParticleStatus",   &genParticleStatus,   &b_genParticleStatus);
    genChain->SetBranchAddress("genParticleMother",   &genParticleMother,   &b_genParticleMother);
    genChain->SetBranchAddress("genParticleDaughters",&genParticleDaughters,&b_genParticleDaughters);
    
    genChain->SetBranchAddress("pthat",        &pthat, &b_pthat);
  }

  Notify();
}

Bool_t ntupleAnalysisPAT::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ntupleAnalysisPAT::Show(Long64_t entry) {

  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!allChain) return;
  allChain->Show(entry);
  //eventChain->Show(entry);
  jetChain->Show(entry);
  metChain->Show(entry);
  leptonChain->Show(entry);
  photonChain->Show(entry);
  triggerChain->Show(entry);
  vertexChain->Show(entry);
  //genChain->Show(entry);
}

Int_t ntupleAnalysisPAT::Cut(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}


Bool_t ntupleAnalysisPAT::vertexIsPrimary(const int& index) {
  bool isPrimary = false;
  if (VertexIsValid->at(index))
    //if (VertexNTrks->at(index)>=_minVtxTrks)
    //if (VertexSumTrkPt->at(index)>=_minVtxSumTrkPt)
    if (VertexNdof->at(index) >= 4)
      if (VertexZ->at(index) <= 24)
	if (Vertexd0->at(index) <= 2)
	  isPrimary = true;
  
  return isPrimary;
}

Bool_t ntupleAnalysisPAT::jetID(const int& index, const bool& tight) {
  //Requirements for jetID
  bool jetID = false;
  bool jetRequirement;
  bool looseJet = true;
  if (tight)
    jetRequirement = JetIDTight->at(index);
  else
    jetRequirement = JetIDLoose->at(index);

  if (jetPrefix_=="PF" || jetPrefix_=="PF2PAT" || jetPrefix_=="JPT" || jetPrefix_=="Calo")
    looseJet &= JetIDLoose->at(index);

  //track
  else {
    looseJet &= JetP4->at(index).Pt()         > 20.;
    looseJet &= fabs(JetP4->at(index).Eta()) < 2.4;
  }

  //if (jetRequirement)
  if (looseJet)
    jetID = true;
  
  return jetID;
}

Bool_t ntupleAnalysisPAT::muonID(const int& index) {
  //Requirements for muonID
  double relIso = (MuonTrkIso->at(index)+MuonECalIso->at(index)+MuonHCalIso->at(index))/MuonP4->at(index).Pt();
  //possible difference for PF muons?
  //relIso = (MuonPFChargedHadronIso->at(index)+MuonPFGammaIso->at(index)+MuonPFNeutralHadronIso->at(index)) / MuonP4->at(index).Pt();

  bool muonID = false;
  double muonChi2Ndof = MuonCombChi2->at(index)/MuonCombNdof->at(index);
  if (MuonGlobalMuonPromptTight->at(index))
    if (MuonP4->at(index).Pt() >= muon_minpt)
      if (fabs(MuonP4->at(index).Eta()) <= muon_maxeta)
	if (muonChi2Ndof < muon_maxchi2)
	  if (MuonCombValidHits->at(index) >= muon_minhits)
	    if (relIso < muon_maxreliso)
	      if (fabs(MuonCombBSDxy->at(index))< muon_maxd0)
		//if (fabs(MuonCombPVDxy->at(index))< muon_maxd0)
		//if (fabs(MuonCombD0->at(index))< muon_maxd0)
		muonID = true;

  return muonID;
}

Bool_t ntupleAnalysisPAT::electronID(const int& index, const bool& tight ) {
  //Requirements for electronID
  double relIso = 0;
  // for normal electrons
  relIso = (ElecTrkIso->at(index)+ElecECalIso->at(index)+ElecHCalIso->at(index))/ElectronP4->at(index).Pt();
  //for PF electrons
  //relIso = (ElecPFChargedHadronIso->at(index)+ElecPFGammaIso->at(index)+ElecPFNeutralHadronIso->at(index)) / ElectronP4->at(index).Pt();

  //Possibly check whethere the electron is a gap electron?
  //isEBGap, isEEGap, isEBEEGap

  bool electronID = false;
  bool electronRequirement;
  if (tight)
    electronRequirement = ElecIdTight->at(index);
  else
    electronRequirement = ElecIdLoose->at(index);
  
  if (electronRequirement)
    if (ElectronP4->at(index).Pt() >= electron_minpt)
      if (fabs(ElectronP4->at(index).Eta()) <= electron_maxeta)
	if (relIso < electron_maxreliso)
	  if (fabs(ElecBSDxy->at(index))< electron_maxd0)
	    //if (ElecPVDxy->at(index)< electron_maxd0)
	    //if (ElecD0->at(index)< electron_maxd0)
	    ///Maybe don't worry about this? is the electron in the gap?
	    //if (ElectronP4->at(index).Eta() < 1.4442 || ElectronP4->at(index).Eta() > 1.566
	    if (ElecSCEta->at(index) < 1.4442 || ElecSCEta->at(index) > 1.566)
	      electronID = true;
  
  return electronID;
}

//Simple identification criteria for photons
Bool_t ntupleAnalysisPAT::photonID(const int& index, const bool& tight) {
  //return value
  bool photonID = false;
  
  //Requirements for photonID
  double relIso = (PhotTrkIso->at(index)+PhotECalIso->at(index)+PhotHCalIso->at(index))/PhotonP4->at(index).Pt();
 
 bool photonRequirement;
  if (tight)
    photonRequirement = PhotTightPhoton->at(index);
  else
    photonRequirement = PhotLoosePhoton->at(index);

  double photon_ieiereq = 0;
  if (PhotIsEB->at(index))
    photon_ieiereq = photon_sigieiereqEB;
  else if (PhotIsEB->at(index))
    photon_ieiereq = photon_sigieiereqEE;
	       
  double trkIsoReq  = 2.0 + 0.0010*PhotonP4->at(index).Pt();//2.0   0.9    2.0 + 0.001*pT     2.0 + 0.0010*pT     1.5 + 0.0010*pT
  double ecalIsoReq = 4.2 + 0.0060*PhotonP4->at(index).Pt();//4.2   2.4    4.2 + 0.003*pT     4.2 + 0.0060*pT     2.0 + 0.0060*pT
  double hcalIsoReq = 2.2 + 0.0025*PhotonP4->at(index).Pt();//2.2   1.0    2.2 + 0.001*pT     2.2 + 0.0025*pT     2.0 + 0.0025*pT

  //if (photonRequirement)
  if (PhotonP4->at(index).Pt() >= photon_minpt)
    if (fabs(PhotonP4->at(index).Eta()) <= photon_maxeta)
      if (!PhotHasPixelSeed->at(index))
	if (PhotTrkIso->at(index) < trkIsoReq)
	  if (PhotECalIso->at(index) < ecalIsoReq)
	    if (PhotHCalIso->at(index) < hcalIsoReq)
	      //if (relIso < photon_maxreliso)
	      if (PhotHadOverEM->at(index) < photon_maxhoverem)
		//if (PhotE2OverE9->at(index) < photon_maxe2overe9)
		if (PhotSigmaIetaIeta->at(index) < photon_ieiereq)
		  /*
		 ///Maybe don't worry about this?
		 if (!PhotIsEBGap->at(index))
		 if (!PhotIsEEGap->at(index))
		 if (!PhotIsEBEEGap->at(index))
		 if (PhotonP4->at(index).Pt() < 130) {
		 if (PhotTSeed->at(index))
		 photonID = true;
		 }
		 else if (PhotTSeed->at(index) > 0)
		  */
		  photonID = true;
  
  return photonID;
}

//Compute HT from the Jet Collection
//If possible, use the stored P4
Double_t ntupleAnalysisPAT::computeHT(const double& minpt, const double& maxeta,
				      const LorentzP4Vs& theJets,
				      const bool& useJetID) {
  
  Double_t theHT    = 0.;
  
  LorentzP4Vs::const_iterator jet = theJets.begin();
  int jin = 0;
  while (jet != theJets.end()) {
    if (jet->Pt() > minpt)
      if (fabs(jet->Eta()) < maxeta)
	if (useJetID) {
	  if (jetID(jin)) 
	    theHT += jet->Pt();}
	else 
	  theHT += jet->Pt();
    ++jet;
    ++jin;
  }
  return theHT;
}

TLorentzVector ntupleAnalysisPAT::computeMHT(const double& minpt, const double& maxeta,
					     const LorentzP4Vs& theJets,
					     const bool& useJetID) {
  
  TLorentzVector theMHT;
  theMHT.SetPxPyPzE(0,0,0,0);
  
  TLorentzVector theJet;
  LorentzP4Vs::const_iterator jet = theJets.begin();
  int jin = 0;
  while (jet != theJets.end()) {
    if (jet->Pt() > minpt) 
      if (fabs(jet->Eta()) < maxeta) {
	theJet.SetPxPyPzE(jet->Px(),jet->Py(),jet->Pz(),jet->E());
	if (useJetID) {
	  if (jetID(jin)) 
	    theMHT -= theJet;}
	else 
	  theMHT -= theJet;
      }
    ++jet;
    ++jin;
  }
  return theMHT;
}

Double_t ntupleAnalysisPAT::computeDPhiStar(const TLorentzVector& mht,
					    const double& minpt, const double& maxeta, 
					    const LorentzP4Vs& theJets,
					    const bool& useJetID) {

  double    dphistar = 10.;

  TLorentzVector theMHT = mht;
  TLorentzVector theJet;

  LorentzP4Vs::const_iterator jet = theJets.begin();
  int jin = 0;
  while (jet != theJets.end()) {
    if (jet->Pt() > minpt)
      if (fabs(jet->Eta()) < maxeta) {
	theJet.SetPxPyPzE(jet->Px(),jet->Py(),jet->Pz(),jet->E());
	if (useJetID) {
	  if (jetID(jin)) 
	    theMHT += theJet;}
	else 
	  theMHT += theJet;
	double tmpdphi = computeDPhi(theJet.Phi(),theMHT.Phi());
	
	dphistar = (fabs(dphistar) < fabs(tmpdphi)) ? dphistar : tmpdphi;
      }
    ++jet;
    ++jin;
  }
  return dphistar;
}


Double_t ntupleAnalysisPAT::computeMinDPhi(const double& minPt,
					   const LorentzP4Vs& theJets,
					   const double& metPhi) {

  double    mindphi = 10.;

  LorentzP4Vs::const_iterator jet = theJets.begin();
  while (jet != theJets.end()) {
    if (jet->Pt() > minPt) {
      double tmpdphi = computeDPhi(jet->Phi(),metPhi);
      mindphi = (fabs(mindphi) < fabs(tmpdphi)) ? mindphi : tmpdphi;
    }
    ++jet;
  }
  return mindphi;
}

Double_t ntupleAnalysisPAT::computeMinDPhi(const double& minPt,
					   const LorentzP4Vs& theJets,
					   const LorentzP4V& theMET) {

  double    mindphi = 10.;

  LorentzP4Vs::const_iterator jet = theJets.begin();
  while (jet != theJets.end()) {
    if (jet->Pt() > minPt) {
      double tmpdphi = computeDPhi(jet->Phi(),theMET.Phi());
      mindphi = (fabs(mindphi) < fabs(tmpdphi)) ? mindphi : tmpdphi;
    }
    ++jet;
  }
  return mindphi;
}


Double_t ntupleAnalysisPAT::computeDPhi(const double& phiObj1, const double& phiObj2) {

  double tmpdphi = phiObj1 - phiObj2;
  tmpdphi = (tmpdphi < 0)    ? -tmpdphi         : tmpdphi;
  tmpdphi = (tmpdphi > M_PI) ? 2*M_PI - tmpdphi : tmpdphi;

  return tmpdphi;
}

Double_t ntupleAnalysisPAT::computeDPhi(const LorentzP4V& obj1, const LorentzP4V& obj2) {
  TLorentzVector tObj1;
  TLorentzVector tObj2;
  tObj1.SetPxPyPzE(obj1.px(),obj1.py(),obj1.pz(),obj1.e());
  tObj2.SetPxPyPzE(obj2.px(),obj2.py(),obj2.pz(),obj2.e());
  
  return tObj1.DeltaPhi(tObj2);
}


Double_t ntupleAnalysisPAT::computeDR(const double& phiObj1, const double& etaObj1,
				      const double& phiObj2, const double& etaObj2) {

  double dphi = computeDPhi(phiObj1,phiObj2);
  double deta = fabs(etaObj1 - etaObj2);
  
  return sqrt((dphi*dphi) + (deta*deta));
}

Double_t ntupleAnalysisPAT::computeDR(const LorentzP4V& obj1, const LorentzP4V& obj2) {
  //std::cout<<"computing DR from two lorentz vectors"<<std::endl;
  TLorentzVector tObj1;
  TLorentzVector tObj2;
  tObj1.SetPxPyPzE(obj1.px(),obj1.py(),obj1.pz(),obj1.e());
  tObj2.SetPxPyPzE(obj2.px(),obj2.py(),obj2.pz(),obj2.e());

  return tObj1.DeltaR(tObj2);
}


#endif // #ifdef ntupleAnalysisPAT_cxx

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef DiJetStudy_h
#define DiJetStudy_h

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>
#include "ntuplePragmas.h"

class DiJetStudy {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  //Standard event information
  UInt_t          Run;
  UInt_t          Event;
  UInt_t          OrbitN;
  UInt_t          StoreN;
  UInt_t          LumiSection;
  UInt_t          BunchCrossing;

  //Jets and the like
  Int_t           NJets;
  Double_t        Ht;
  Double_t        MHx;
  Double_t        MHy;
  Double_t        MHt;
  //std::vector<TLorentzVector>
  LorentzVs       JetP4;
  LorentzVs       JetRawP4;
  //std::map<std::string, std::vector<float> >
  jetcorrs        JetCorrFactor;
   
  Double_t        JetE[50];   //[NJets]
  Double_t        JetEt[50];   //[NJets]
  Double_t        JetPt[50];   //[NJets]
  Double_t        JetPx[50];   //[NJets]
  Double_t        JetPy[50];   //[NJets]
  Double_t        JetPz[50];   //[NJets]
  Double_t        JetRawE[50];   //[NJets]
  Double_t        JetRawEt[50];   //[NJets]
  Double_t        JetRawPt[50];   //[NJets]
  Double_t        JetRawPx[50];   //[NJets]
  Double_t        JetRawPy[50];   //[NJets]
  Double_t        JetRawPz[50];   //[NJets]
  Double_t        JetEta[50];   //[NJets]
  Double_t        JetPhi[50];   //[NJets]
  Double_t        JetFem[50];   //[NJets]
  Double_t        JetFhad[50];   //[NJets]
  Double_t        JetCharge[50];   //[NJets]
  Double_t        JetNConst[50];   //[NJets]
  Bool_t          JetPreselection;
  Bool_t          JetIDMinimal[50];   //[NJets]
  Bool_t          JetIDLoose[50];   //[NJets]
  Bool_t          JetIDTight[50];   //[NJets]
  Double_t        JetBTag_TCHE[50];   //[NJets]
  Double_t        JetBTag_TCHP[50];   //[NJets]
  Double_t        JetBTag_jetProb[50];   //[NJets]
  Double_t        JetBTag_jetBProb[50];   //[NJets]
  Double_t        JetBTag_SSVHE[50];   //[NJets]
  Double_t        JetBTag_SSVHP[50];   //[NJets]
  Double_t        JetBTag_CSV[50];   //[NJets]
  Double_t        JetBTag_CSVMVA[50];   //[NJets]
  Double_t        JetBTag_SoftLepton[50];   //[NJets]
  Double_t        JetBTag_SoftLeptonByIP[50];   //[NJets]
  Double_t        JetBTag_SoftLeptonByPt[50];   //[NJets]
  Double_t        GenHt;
  Double_t        GenMHt;
  Double_t        JetGenE[50];   //[NJets]
  Double_t        JetGenEt[50];   //[NJets]
  Double_t        JetGenPt[50];   //[NJets]
  Double_t        JetGenPx[50];   //[NJets]
  Double_t        JetGenPy[50];   //[NJets]
  Double_t        JetGenPz[50];   //[NJets]
  Double_t        JetGenEta[50];   //[NJets]
  Double_t        JetGenPhi[50];   //[NJets]
  Int_t           JetPartonId[50];   //[NJets]
  Int_t           JetPartonMother[50];   //[NJets]
  Double_t        JetPartonPx[50];   //[NJets]
  Double_t        JetPartonPy[50];   //[NJets]
  Double_t        JetPartonPz[50];   //[NJets]
  Double_t        JetPartonEt[50];   //[NJets]
  Double_t        JetPartonE[50];   //[NJets]
  Double_t        JetPartonPhi[50];   //[NJets]
  Double_t        JetPartonEta[50];   //[NJets]
  Int_t           JetPartonFlavour[50];   //[NJets]
  Double_t        JetfHPD[50];   //[NJets]
  Double_t        JetfRBX[50];   //[NJets]
  Double_t        Jetn90[50];   //[NJets]
  Double_t        JetTrackPt[50];   //[NJets]
  Double_t        JetTrackPhi[50];   //[NJets]
  Double_t        JetTrackPhiWeighted[50];   //[NJets]
  Int_t           JetTrackNo[50];   //[NJets]

  Double_t        JetChargedFem[50];   //[NJets]
  Double_t        JetNeutralFem[50];   //[NJets]
  Double_t        JetChargedFhad[50];   //[NJets]
  Double_t        JetNeutralFhad[50];   //[NJets]
  Int_t           JetChargedMult[50];   //[NJets]
  Int_t           JetElecMulti[50];   //[NJets]
  Int_t           JetMuonMulti[50];   //[NJets]

  Double_t        JetChargedFmu[50];   //[NJets]
  Double_t        JetChargedFele[50];   //[NJets]
  Double_t        JetChargedFpho[50];   //[NJets]
  Double_t        JetHFFem[50];   //[NJets]
  Double_t        JetHFFhad[50];   //[NJets]
  Int_t           JetChargedHadMult[50];   //[NJets]
  Int_t           JetNeutralHadMult[50];   //[NJets]
  Int_t           JetPhotonMult[50];   //[NJets]
  Int_t           JetNeutralMult[50];   //[NJets]

  Int_t           nFullMET;
  Int_t           nUncorrMET;
  TLorentzVector  METP4;
  //LorentzV        METP4;
  Double_t        MET_Fullcorr_nocc[3];
  Double_t        METpt_Fullcorr_nocc;
  Double_t        METphi_Fullcorr_nocc;
  Double_t        METsumEt_Fullcorr_nocc;
  Double_t        METsignificance_Fullcorr_nocc;
  Double_t        MET_Nocorr_nocc[2];   //[nUncorrMET]
  Double_t        METpt_Nocorr_nocc;
  Double_t        METphi_Nocorr_nocc;
  Double_t        METsumEt_Nocorr_nocc;
  Double_t        MET_Muoncorr_nocc[2];   //[nUncorrMET]
  Double_t        METpt_Muoncorr_nocc;
  Double_t        METphi_Muoncorr_nocc;
  Double_t        METsumEt_Muoncorr_nocc;
  Double_t        MET_JEScorr_nocc[2];   //[nUncorrMET]
  Double_t        METpt_JEScorr_nocc;
  Double_t        METphi_JEScorr_nocc;
  Double_t        METsumEt_JEScorr_nocc;
  Double_t        GenMET[3];

  LorentzVs       PhotonP4;
  Int_t           PhotN;
  Double_t        PhotE[50];   //[PhotN]
  Double_t        PhotEt[50];   //[PhotN]
  Double_t        PhotPt[50];   //[PhotN]
  Double_t        PhotPx[50];   //[PhotN]
  Double_t        PhotPy[50];   //[PhotN]
  Double_t        PhotPz[50];   //[PhotN]
  Double_t        PhotEta[50];   //[PhotN]
  Double_t        PhotPhi[50];   //[PhotN]
  Double_t        PhotTrkIso[50];   //[PhotN]
  Double_t        PhotECalIso[50];   //[PhotN]
  Double_t        PhotHCalIso[50];   //[PhotN]
  Double_t        PhotAllIso[50];   //[PhotN]
  Bool_t          PhotLoosePhoton[50];   //[PhotN]
  Bool_t          PhotTightPhoton[50];   //[PhotN]

  Bool_t          ElecVeto;
  LorentzVs       ElectronP4;
  Int_t           ElecN;
  Double_t        ElecE[50];   //[ElecN]
  Double_t        ElecEt[50];   //[ElecN]
  Double_t        ElecPt[50];   //[ElecN]
  Double_t        ElecPx[50];   //[ElecN]
  Double_t        ElecPy[50];   //[ElecN]
  Double_t        ElecPz[50];   //[ElecN]
  Double_t        ElecEta[50];   //[ElecN]
  Double_t        ElecPhi[50];   //[ElecN]
  Double_t        ElecCharge[50];   //[ElecN]
  Double_t        ElecHOverE[50];   //[ElecN]
  Double_t        ElecTrkIso[50];   //[ElecN]
  Double_t        ElecECalIso[50];   //[ElecN]
  Double_t        ElecHCalIso[50];   //[ElecN]
  Double_t        ElecAllIso[50];   //[ElecN]
  Double_t        ElecTrkChiNorm[50];   //[ElecN]
  Double_t        ElecIdLoose[50];   //[ElecN]
  Double_t        ElecIdTight[50];   //[ElecN]
  Double_t        ElecIdRobLoose[50];   //[ElecN]
  Double_t        ElecIdRobTight[50];   //[ElecN]
  Double_t        ElecIdRobHighE[50];   //[ElecN]
  Double_t        ElecChargeMode[50];   //[ElecN]
  Double_t        ElecPtMode[50];   //[ElecN]
  Double_t        ElecVx[50];   //[ElecN]
  Double_t        ElecVy[50];   //[ElecN]
  Double_t        ElecVz[50];   //[ElecN]
  Double_t        ElecD0[50];   //[ElecN]
  Double_t        ElecDz[50];   //[ElecN]
  Double_t        ElecPtTrk[50];   //[ElecN]
  Double_t        ElecQOverPErrTrkMode[50];   //[ElecN]
  Double_t        ElecCaloEnergy[50];   //[ElecN]
  Double_t        ElecQOverPErrTrk[50];   //[ElecN]
  Double_t        ElecPinTrk[50];   //[ElecN]
  Double_t        ElecPoutTrk[50];   //[ElecN]
  Double_t        ElecLostHits[50];   //[ElecN]
  Double_t        ElecValidHits[50];   //[ElecN]
  Double_t        ElecEtaTrk[50];   //[ElecN]
  Double_t        ElecPhiTrk[50];   //[ElecN]
  Double_t        ElecWidthClusterEta[50];   //[ElecN]
  Double_t        ElecWidthClusterPhi[50];   //[ElecN]

  Bool_t          MuonVeto;
  LorentzVs       MuonP4;
  Int_t           MuonN;
  Double_t        MuonE[50];   //[MuonN]
  Double_t        MuonEt[50];   //[MuonN]
  Double_t        MuonPt[50];   //[MuonN]
  Double_t        MuonPx[50];   //[MuonN]
  Double_t        MuonPy[50];   //[MuonN]
  Double_t        MuonPz[50];   //[MuonN]
  Double_t        MuonEta[50];   //[MuonN]
  Double_t        MuonPhi[50];   //[MuonN]
  Double_t        MuonCharge[50];   //[MuonN]
  Double_t        MuonTrkIso[50];   //[MuonN]
  Double_t        MuonECalIso[50];   //[MuonN]
  Double_t        MuonHCalIso[50];   //[MuonN]
  Double_t        MuonAllIso[50];   //[MuonN]
  Double_t        MuonTrkChiNorm[50];   //[MuonN]
  Double_t        MuonECalIsoDeposit[50];   //[MuonN]
  Double_t        MuonHCalIsoDeposit[50];   //[MuonN]
  Double_t        MuonIsGlobal[50];   //[MuonN]
  Double_t        MuonIsStandAlone[50];   //[MuonN]
  Double_t        MuonIsTracker[50];   //[MuonN]
  Double_t        MuonGlobalMuonPromptTight[50];   //[MuonN]
  Double_t        MuonAllArbitrated[50];   //[MuonN]
  Double_t        MuonTrackerMuonArbitrated[50];   //[MuonN]
  Double_t        MuonTMLastStationLoose[50];   //[MuonN]
  Double_t        MuonTMLastStationTight[50];   //[MuonN]
  Double_t        MuonTM2DCompatibilityLoose[50];   //[MuonN]
  Double_t        MuonTM2DCompatibilityTight[50];   //[MuonN]
  Double_t        MuonTMOneStationLoose[50];   //[MuonN]
  Double_t        MuonTMOneStationTight[50];   //[MuonN]
  Double_t        MuonTMLastStationOptimizedLowPtLoose[50];   //[MuonN]
  Double_t        MuonTMLastStationOptimizedLowPtTight[50];   //[MuonN]
  Double_t        MuonGMTkChiCompatibility[50];   //[MuonN]
  Double_t        MuonGMStaChiCompatibility[50];   //[MuonN]
  Double_t        MuonGMTkKinkTight[50];   //[MuonN]
  Double_t        MuonTMLastStationAngLoose[50];   //[MuonN]
  Double_t        MuonTMLastStationAngTight[50];   //[MuonN]
  Double_t        MuonTMLastStationOptimizedBarrelLowPtLoose[50];   //[MuonN]
  Double_t        MuonTMLastStationOptimizedBarrelLowPtTight[50];   //[MuonN]
  Double_t        MuonCombChi2[50];   //[MuonN]
  Double_t        MuonCombNdof[50];   //[MuonN]
  Double_t        MuonCombVx[50];   //[MuonN]
  Double_t        MuonCombVy[50];   //[MuonN]
  Double_t        MuonCombVz[50];   //[MuonN]
  Double_t        MuonCombD0[50];   //[MuonN]
  Double_t        MuonCombDz[50];   //[MuonN]
  Double_t        MuonStandValidHits[50];   //[MuonN]
  Double_t        MuonStandLostHits[50];   //[MuonN]
  Double_t        MuonStandPt[50];   //[MuonN]
  Double_t        MuonStandPz[50];   //[MuonN]
  Double_t        MuonStandP[50];   //[MuonN]
  Double_t        MuonStandEta[50];   //[MuonN]
  Double_t        MuonStandPhi[50];   //[MuonN]
  Double_t        MuonStandCharge[50];   //[MuonN]
  Double_t        MuonStandChi[50];   //[MuonN]
  Double_t        MuonStandQOverPError[50];   //[MuonN]
  Double_t        MuonTrkValidHits[50];   //[MuonN]
  Double_t        MuonTrkLostHits[50];   //[MuonN]
  Double_t        MuonTrkD0[50];   //[MuonN]
  Double_t        MuonTrkPt[50];   //[MuonN]
  Double_t        MuonTrkPz[50];   //[MuonN]
  Double_t        MuonTrkP[50];   //[MuonN]
  Double_t        MuonTrkEta[50];   //[MuonN]
  Double_t        MuonTrkPhi[50];   //[MuonN]
  Double_t        MuonTrkCharge[50];   //[MuonN]
  Double_t        MuonTrkChi[50];   //[MuonN]
  Double_t        MuonTrkQOverPError[50];   //[MuonN]
  Double_t        MuonTrkOuterZ[50];   //[MuonN]
  Double_t        MuonTrkOuterR[50];   //[MuonN]

  Double_t        beamspotX0;
  Double_t        beamspotY0;
  Double_t        beamspotZ0;
  Double_t        beamspotWidthX;
  Double_t        beamspotWidthY;
  Double_t        beamspotX0Error;
  Double_t        beamspotY0Error;
  Double_t        beamspotZ0Error;
  Double_t        beamspotWidthXError;
  Double_t        beamspotWidthYError;
  Double_t        beamspotSigmaZ0;
  Double_t        beamspotSigmaZ0Error;
  Double_t        beamspotdxdz;
  Double_t        beamspotdxdzError;
  Double_t        beamspotdydz;
  Double_t        beamspotdydzError;
  Double_t        beamspotEmittanceX;
  Double_t        beamspotEmittanceY;
  Double_t        beamspotBetaStar;

  Int_t           nVtx;
  Double_t        VertexChi2[10];   //[nVtx]
  Double_t        VertexNdof[10];   //[nVtx]
  Double_t        VertexNTrks[10];   //[nVtx]
  Double_t        VertexNRawTrks[10];   //[nVtx]
  Double_t        VertexIsValid[10];   //[nVtx]
  Double_t        VertexNormalizedChi2[10];   //[nVtx]
  Double_t        VertexX[10];   //[nVtx]
  Double_t        VertexY[10];   //[nVtx]
  Double_t        VertexZ[10];   //[nVtx]
  Double_t        Vertexd0[10];   //[nVtx]
  Double_t        VertexdX[10];   //[nVtx]
  Double_t        VertexdY[10];   //[nVtx]
  Double_t        VertexdZ[10];   //[nVtx]

  Double_t        MPTPhi;
  Double_t        MPTPx;
  Double_t        MPTPy;
  Double_t        MPTPz;

  Int_t           nHLT;
  Int_t           HLTArray[137];   //[nHLT]
  std::string     HLTNames[137];   //[nHLT]
  Bool_t          HLT1JET;
  Bool_t          HLT2JET;
  Bool_t          HLT1MET;
  Bool_t          HLT11HT;
  Bool_t          HLT1HT1MHT;
  Bool_t          HLT1MUON;
  Bool_t          HLTMINBIAS;

  Int_t           nL1Technical;
  Int_t           L1TechnicalArray[64];   //[nL1Technical]
  std::string     L1TechnicalNames[64];   //[nL1Technical]
  Int_t           nL1Physics;
  Int_t           L1PhysicsArray[128];   //[nL1Physics]
  std::string     L1PhysicsNames[128];   //[nL1Physics]
  trigger_b       L1Triggered;
  trigger_i       L1Prescaled;
  Bool_t          L1MUON1;
  Bool_t          L1MUON2;
  Bool_t          L1MUON3;
  Bool_t          L1MUON4;

  // List of branches
  TBranch        *b_Run;
  TBranch        *b_Event;
  TBranch        *b_OrbitN;
  TBranch        *b_StoreN;
  TBranch        *b_LumiSection;
  TBranch        *b_BunchCrossing;

  TBranch        *b_NJets;
  TBranch        *b_Ht;
  TBranch        *b_MHx;
  TBranch        *b_MHy;
  TBranch        *b_MHt;
  TBranch        *b_JetP4;
  TBranch        *b_JetRawP4;
  TBranch        *b_JetE;
  TBranch        *b_JetEt;
  TBranch        *b_JetPt;
  TBranch        *b_JetPx;
  TBranch        *b_JetPy;
  TBranch        *b_JetPz;
  TBranch        *b_JetRawE;
  TBranch        *b_JetRawEt;
  TBranch        *b_JetRawPt;
  TBranch        *b_JetRawPx;
  TBranch        *b_JetRawPy;
  TBranch        *b_JetRawPz;
  TBranch        *b_JetEta;
  TBranch        *b_JetPhi;
  TBranch        *b_JetFem;
  TBranch        *b_JetFhad;
  TBranch        *b_JetCharge;
  TBranch        *b_JetNConst;
  TBranch        *b_JetCorrFactor;
  TBranch        *b_JetPreselection;
  TBranch        *b_JetIDMinimal;
  TBranch        *b_JetIDLoose;
  TBranch        *b_JetIDTight;
  TBranch        *b_JetBTag_TCHE;
  TBranch        *b_JetBTag_TCHP;
  TBranch        *b_JetBTag_jetProb;
  TBranch        *b_JetBTag_jetBProb;
  TBranch        *b_JetBTag_SSVHE;
  TBranch        *b_JetBTag_SSVHP;
  TBranch        *b_JetBTag_CSV;
  TBranch        *b_JetBTag_CSVMVA;
  TBranch        *b_JetBTag_SoftLepton;
  TBranch        *b_JetBTag_SoftLeptonByIP;
  TBranch        *b_JetBTag_SoftLeptonByPt;
  TBranch        *b_GenHt;
  TBranch        *b_GenMHt;
  TBranch        *b_JetGenE;
  TBranch        *b_JetGenEt;
  TBranch        *b_JetGenPt;
  TBranch        *b_JetGenPx;
  TBranch        *b_JetGenPy;
  TBranch        *b_JetGenPz;
  TBranch        *b_JetGenEta;
  TBranch        *b_JetGenPhi;
  TBranch        *b_JetPartonId;
  TBranch        *b_JetPartonMother;
  TBranch        *b_JetPartonPx;
  TBranch        *b_JetPartonPy;
  TBranch        *b_JetPartonPz;
  TBranch        *b_JetPartonEt;
  TBranch        *b_JetPartonE;
  TBranch        *b_JetPartonPhi;
  TBranch        *b_JetPartonEta;
  TBranch        *b_JetPartonFlavour;
  TBranch        *b_JetfHPD;
  TBranch        *b_JetfRBX;
  TBranch        *b_Jetn90;
  TBranch        *b_JetTrackPt;
  TBranch        *b_JetTrackPhi;
  TBranch        *b_JetTrackPhiWeighted;
  TBranch        *b_JetTrackNo;

  TBranch        *b_JetChargedFem;
  TBranch        *b_JetNeutralFem;
  TBranch        *b_JetChargedFhad;
  TBranch        *b_JetNeutralFhad;
  TBranch        *b_JetChargedMult;
  TBranch        *b_JetElecMulti;
  TBranch        *b_JetMuonMulti;

  TBranch        *b_JetChargedFmu;
  TBranch        *b_JetChargedFele;
  TBranch        *b_JetChargedFpho;
  TBranch        *b_JetHFFem;
  TBranch        *b_JetHFFhad;
  TBranch        *b_JetChargedHadMult;
  TBranch        *b_JetNeutralHadMult;
  TBranch        *b_JetPhotonMult;
  TBranch        *b_JetNeutralMult;

  TBranch        *b_nFullMET;
  TBranch        *b_nUncorrMET;
  TBranch        *b_METP4;
  TBranch        *b_MET_Fullcorr_nocc;
  TBranch        *b_METpt_Fullcorr_nocc;
  TBranch        *b_METphi_Fullcorr_nocc;
  TBranch        *b_METsumEt_Fullcorr_nocc;
  TBranch        *b_METsignificance_Fullcorr_nocc;
  TBranch        *b_MET_Nocorr_nocc;
  TBranch        *b_METpt_Nocorr_nocc;
  TBranch        *b_METphi_Nocorr_nocc;
  TBranch        *b_METsumEt_Nocorr_nocc;
  TBranch        *b_MET_Muoncorr_nocc;
  TBranch        *b_METpt_Muoncorr_nocc;
  TBranch        *b_METphi_Muoncorr_nocc;
  TBranch        *b_METsumEt_Muoncorr_nocc;
  TBranch        *b_MET_JEScorr_nocc;
  TBranch        *b_METpt_JEScorr_nocc;
  TBranch        *b_METphi_JEScorr_nocc;
  TBranch        *b_METsumEt_JEScorr_nocc;
  TBranch        *b_GenMET;

  TBranch        *b_PhotonP4;
  TBranch        *b_PhotN;
  TBranch        *b_PhotE;
  TBranch        *b_PhotEt;
  TBranch        *b_PhotPt;
  TBranch        *b_PhotPx;
  TBranch        *b_PhotPy;
  TBranch        *b_PhotPz;
  TBranch        *b_PhotEta;
  TBranch        *b_PhotPhi;
  TBranch        *b_PhotTrkIso;
  TBranch        *b_PhotECalIso;
  TBranch        *b_PhotHCalIso;
  TBranch        *b_PhotAllIso;
  TBranch        *b_PhotLoosePhoton;
  TBranch        *b_PhotTightPhoton;

  TBranch        *b_ElecVeto;
  TBranch        *b_ElectronP4;
  TBranch        *b_ElecN;
  TBranch        *b_ElecE;
  TBranch        *b_ElecEt;
  TBranch        *b_ElecPt;
  TBranch        *b_ElecPx;
  TBranch        *b_ElecPy;
  TBranch        *b_ElecPz;
  TBranch        *b_ElecEta;
  TBranch        *b_ElecPhi;
  TBranch        *b_ElecCharge;
  TBranch        *b_ElecHOverE;
  TBranch        *b_ElecTrkIso;
  TBranch        *b_ElecECalIso;
  TBranch        *b_ElecHCalIso;
  TBranch        *b_ElecAllIso;
  TBranch        *b_ElecTrkChiNorm;
  TBranch        *b_ElecIdLoose;
  TBranch        *b_ElecIdTight;
  TBranch        *b_ElecIdRobLoose;
  TBranch        *b_ElecIdRobTight;
  TBranch        *b_ElecIdRobHighE;
  TBranch        *b_ElecChargeMode;
  TBranch        *b_ElecPtMode;
  TBranch        *b_ElecVx;
  TBranch        *b_ElecVy;
  TBranch        *b_ElecVz;
  TBranch        *b_ElecD0;
  TBranch        *b_ElecDz;
  TBranch        *b_ElecPtTrk;
  TBranch        *b_ElecQOverPErrTrkMode;
  TBranch        *b_ElecCaloEnergy;
  TBranch        *b_ElecQOverPErrTrk;
  TBranch        *b_ElecPinTrk;
  TBranch        *b_ElecPoutTrk;
  TBranch        *b_ElecLostHits;
  TBranch        *b_ElecValidHits;
  TBranch        *b_ElecEtaTrk;
  TBranch        *b_ElecPhiTrk;
  TBranch        *b_ElecWidthClusterEta;
  TBranch        *b_ElecWidthClusterPhi;

  TBranch        *b_MuonVeto;
  TBranch        *b_MuonP4;
  TBranch        *b_MuonN;
  TBranch        *b_MuonE;
  TBranch        *b_MuonEt;
  TBranch        *b_MuonPt;
  TBranch        *b_MuonPx;
  TBranch        *b_MuonPy;
  TBranch        *b_MuonPz;
  TBranch        *b_MuonEta;
  TBranch        *b_MuonPhi;
  TBranch        *b_MuonCharge;
  TBranch        *b_MuonTrkIso;
  TBranch        *b_MuonECalIso;
  TBranch        *b_MuonHCalIso;
  TBranch        *b_MuonAllIso;
  TBranch        *b_MuonTrkChiNorm;
  TBranch        *b_MuonECalIsoDeposit;
  TBranch        *b_MuonHCalIsoDeposit;
  TBranch        *b_MuonIsGlobal;
  TBranch        *b_MuonIsStandAlone;
  TBranch        *b_MuonIsTracker;
  TBranch        *b_MuonGlobalMuonPromptTight;
  TBranch        *b_MuonAllArbitrated;
  TBranch        *b_MuonTrackerMuonArbitrated;
  TBranch        *b_MuonTMLastStationLoose;
  TBranch        *b_MuonTMLastStationTight;
  TBranch        *b_MuonTM2DCompatibilityLoose;
  TBranch        *b_MuonTM2DCompatibilityTight;
  TBranch        *b_MuonTMOneStationLoose;
  TBranch        *b_MuonTMOneStationTight;
  TBranch        *b_MuonTMLastStationOptimizedLowPtLoose;
  TBranch        *b_MuonTMLastStationOptimizedLowPtTight;
  TBranch        *b_MuonGMTkChiCompatibility;
  TBranch        *b_MuonGMStaChiCompatibility;
  TBranch        *b_MuonGMTkKinkTight;
  TBranch        *b_MuonTMLastStationAngLoose;
  TBranch        *b_MuonTMLastStationAngTight;
  TBranch        *b_MuonTMLastStationOptimizedBarrelLowPtLoose;
  TBranch        *b_MuonTMLastStationOptimizedBarrelLowPtTight;
  TBranch        *b_MuonCombChi2;
  TBranch        *b_MuonCombNdof;
  TBranch        *b_MuonCombVx;
  TBranch        *b_MuonCombVy;
  TBranch        *b_MuonCombVz;
  TBranch        *b_MuonCombD0;
  TBranch        *b_MuonCombDz;
  TBranch        *b_MuonStandValidHits;
  TBranch        *b_MuonStandLostHits;
  TBranch        *b_MuonStandPt;
  TBranch        *b_MuonStandPz;
  TBranch        *b_MuonStandP;
  TBranch        *b_MuonStandEta;
  TBranch        *b_MuonStandPhi;
  TBranch        *b_MuonStandCharge;
  TBranch        *b_MuonStandChi;
  TBranch        *b_MuonStandQOverPError;
  TBranch        *b_MuonTrkValidHits;
  TBranch        *b_MuonTrkLostHits;
  TBranch        *b_MuonTrkD0;
  TBranch        *b_MuonTrkPt;
  TBranch        *b_MuonTrkPz;
  TBranch        *b_MuonTrkP;
  TBranch        *b_MuonTrkEta;
  TBranch        *b_MuonTrkPhi;
  TBranch        *b_MuonTrkCharge;
  TBranch        *b_MuonTrkChi;
  TBranch        *b_MuonTrkQOverPError;
  TBranch        *b_MuonTrkOuterZ;
  TBranch        *b_MuonTrkOuterR;

  TBranch        *b_beamspotX0;
  TBranch        *b_beamspotY0;
  TBranch        *b_beamspotZ0;
  TBranch        *b_beamspotWidthX;
  TBranch        *b_beamspotWidthY;
  TBranch        *b_beamspotX0Error;
  TBranch        *b_beamspotY0Error;
  TBranch        *b_beamspotZ0Error;
  TBranch        *b_beamspotWidthXError;
  TBranch        *b_beamspotWidthYError;
  TBranch        *b_beamspotSigmaZ0;
  TBranch        *b_beamspotSigmaZ0Error;
  TBranch        *b_beamspotdxdz;
  TBranch        *b_beamspotdxdzError;
  TBranch        *b_beamspotdydz;
  TBranch        *b_beamspotdydzError;
  TBranch        *b_beamspotEmittanceX;
  TBranch        *b_beamspotEmittanceY;
  TBranch        *b_beamspotBetaStar;

  TBranch        *b_nVtx;
  TBranch        *b_VertexChi2;
  TBranch        *b_VertexNdof;
  TBranch        *b_VertexNTrks;
  TBranch        *b_VertexNRawTrks;
  TBranch        *b_VertexIsValid;
  TBranch        *b_VertexNormalizedChi2;
  TBranch        *b_VertexX;
  TBranch        *b_VertexY;
  TBranch        *b_VertexZ;
  TBranch        *b_Vertexd0;
  TBranch        *b_VertexdX;
  TBranch        *b_VertexdY;
  TBranch        *b_VertexdZ;

  TBranch        *b_MPTPhi;
  TBranch        *b_MPTPx;
  TBranch        *b_MPTPy;
  TBranch        *b_MPTPz;

  TBranch        *b_nHLT;
  TBranch        *b_HLTArray;
  TBranch        *b_HLTNames;
  TBranch        *b_HLT1JET;
  TBranch        *b_HLT2JET;
  TBranch        *b_HLT1MET;
  TBranch        *b_HLT1HT;
  TBranch        *b_HLT1HT1MHT;
  TBranch        *b_HLT1MUON;
  TBranch        *b_HLTMINBIAS;

  TBranch        *b_nL1Technical;
  TBranch        *b_L1TechnicalArray;
  TBranch        *b_L1TechnicalNames;
  TBranch        *b_nL1Physics;
  TBranch        *b_L1PhysicsArray;
  TBranch        *b_L1PhysicsNames;
  TBranch        *b_L1Triggered;
  TBranch        *b_L1Prescaled;
  TBranch        *b_L1MUON1;
  TBranch        *b_L1MUON2;
  TBranch        *b_L1MUON3;
  TBranch        *b_L1MUON4;

  DiJetStudy(TTree *tree=0, bool isData=false, std::string jetPrefix="Calo", std::string metPrefix="CaloTypeI", std::string lepPrefix="", std::string phtPrefix="");
  virtual ~DiJetStudy();

  virtual Int_t    Preselection(Long64_t entry);
  virtual Int_t    TriggerSelection(Long64_t entry);
  virtual Int_t    JetSelection(Long64_t entry);
  virtual Int_t    DiJetSelection(Long64_t entry);
  virtual Int_t    LeptonVeto(Long64_t entry);
  virtual Int_t    METSelection(Long64_t entry);
  virtual Int_t    HTSelection(Long64_t entry);
  virtual Int_t    MHTSelection(Long64_t entry);
  virtual Int_t    Cut(Long64_t entry);

  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree, TString jetPrefix, TString metPrefix, TString lepPrefix, TString phtPrefix);
  virtual void     Loop(std::string outfilename="outfile.root", std::string analysisVer="met", double lum=1., double xs=1., double eff=1., double numGen=1.);
  virtual Bool_t   Notify();

  Bool_t   goodMuonTag(int index, int mode=1);
  Bool_t   goodMuonProbe(int index, int mode=1, int charge=1);
  
  //Bool_t   goodElectronTag(int index, int mode=1);
  //Bool_t   goodElectronProbe(int index, int mode=1, int charge=1);
  //
  //Bool_t   goodPhotonTag(int index, int mode=1);
  //Bool_t   goodPhotonProbe(int index, int mode=1, int charge=1);
  //
  Bool_t   jetID(int index, bool tight=false);
  Bool_t   muonID(int index, int mode);
  Bool_t   electronID(int index, bool tight=false);
  Bool_t   photonID(int index, bool tight=false);

  Double_t computeHT(double& minpt, double& maxeta, bool fromRAW);
  TLorentzVector computeMHT(double& minpt, double& maxeta, bool fromRAW);
  Double_t computeDPhiStar(TLorentzVector mht, double& minpt, double& maxeta, bool fromRAW);

  virtual void     Show(Long64_t entry = -1);

  Double_t luminosity_, cross_section_, efficiency_, generated_events_;
  std::string outfilename_;
  std::string infilename_;
  std::string jetPrefix_;
  std::string metPrefix_;
  std::string lepPrefix_;
  std::string phtPrefix_;
  std::string analysisVer_;

  bool isData_;

  double jet1_minpt;
  double jet1_maxeta;
  double jet2_minpt;
  double jet2_maxeta;
  double jetall_minpt;
  double jetall_maxpt;
  double jetall_maxeta;
  double jet_maxreliso;
  double jet_maxd0;
  double jet_maxchi2;

  double ht_jet_minpt;
  double ht_jet_maxeta;
  double mht_jet_minpt;
  double mht_jet_maxeta;

  int cut_njet;
  double cut_met;
  double cut_ht;
  double cut_mht;
  double cut_meff;

  double cut_jet12dphi;
  double cut_jet1metdphi;
  double cut_jet2metdphi;
  double cut_jetallmetdphi;
  double cut_dphistar;

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

  int photon_minhits;
  double photon_minpt;
  double photon_maxpt;
  double photon_noniso;
  double photon_maxeta;
  double photon_maxreliso;
  double photon_maxd0;
  double photon_maxchi2;
  
  double maxzbox;

};

#endif

#ifdef DiJetStudy_cxx

DiJetStudy::DiJetStudy(TTree *tree, 
	   bool isData, 
	   std::string jetPrefix, 
	   std::string metPrefix, 
	   std::string lepPrefix, 
	   std::string phtPrefix ) {
  
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  isData_      = isData;

  jetPrefix_ = jetPrefix;
  metPrefix_ = metPrefix;
  lepPrefix_ = lepPrefix;
  phtPrefix_ = phtPrefix;

  //Would like to pass these in via a cut file or similar
  jet1_minpt    = 100.;
  jet1_maxeta   = 2.5;

  jet2_minpt    = 100.;
  jet2_maxeta   = 3.0;

  jetall_minpt  = 50.;
  jetall_maxeta = 3.0;
  jetall_maxpt  = 50.;

  ht_jet_minpt  = 50;
  ht_jet_maxeta = 3.0;

  mht_jet_minpt  = 30;
  mht_jet_maxeta = 5.0;

  cut_njet = 2;
  cut_met  = 250.;
  cut_ht   = 0.;
  cut_mht  = 250.;
  cut_meff = 0.;
  //To be fixed
  cut_jet12dphi     = -1.;
  cut_jet1metdphi   = 0.5;
  cut_jet2metdphi   = 0.5;
  cut_jetallmetdphi = -1.;
  cut_dphistar      = 0.25;

  electron_minpt     = 10.0;
  electron_maxpt     = 10.0;
  electron_noniso    = 0.5;
  electron_maxeta    = 2.4;
  electron_minhits   = 10;
  electron_maxreliso = 0.5;
  electron_maxd0     = 0.2;
  electron_maxchi2   = 10.0;
  //eidLoose;

  muon_minpt     = 10.0;
  muon_maxpt     = 10.0;
  muon_noniso    = 0.5;
  muon_maxeta    = 2.4;
  muon_minhits   = 10;
  muon_maxreliso = 0.1;
  muon_maxd0     = 0.2;
  muon_maxchi2   = 10.0;
  //GlobalMuonPromptTight
  //GlobalMuon

  photon_minpt     = 15.0;
  photon_maxpt     = 15.0;
  photon_noniso    = 0.5;
  photon_maxeta    = 2.5;
  photon_minhits   = 10;
  photon_maxreliso = 0.1;
  photon_maxd0     = 0.2;
  photon_maxchi2   = 10.0;

  maxzbox   = 30.0;

  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    if (!f) {
      f = new TFile("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    }
    tree = (TTree*)gDirectory->Get("analysisNtuplePAT/AllData");
    
  }
  Init(tree,jetPrefix_,metPrefix_,lepPrefix_,phtPrefix);
}

DiJetStudy::~DiJetStudy() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t DiJetStudy::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t DiJetStudy::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void DiJetStudy::Init(TTree *tree, TString jetPrefix, TString metPrefix, TString lepPrefix, TString phtPrefix) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Run", &Run, &b_Run);
  fChain->SetBranchAddress("Event", &Event, &b_Event);
  fChain->SetBranchAddress("OrbitN", &OrbitN, &b_OrbitN);
  fChain->SetBranchAddress("StoreN", &StoreN, &b_StoreN);
  fChain->SetBranchAddress("LumiSection", &LumiSection, &b_LumiSection);
  fChain->SetBranchAddress("BunchCrossing", &BunchCrossing, &b_BunchCrossing);

  fChain->SetBranchAddress(jetPrefix+"Ht", &Ht, &b_Ht);
  fChain->SetBranchAddress(jetPrefix+"MHx", &MHx, &b_MHx);
  fChain->SetBranchAddress(jetPrefix+"MHy", &MHy, &b_MHy);
  fChain->SetBranchAddress(jetPrefix+"MHt", &MHt, &b_MHt);

  fChain->SetBranchAddress(jetPrefix+"NJets", &NJets, &b_NJets);
  //fChain->SetBranchAddress(jetPrefix+"JetP4", JetP4, &b_JetP4);
  fChain->SetBranchAddress(jetPrefix+"JetE", JetE, &b_JetE);
  fChain->SetBranchAddress(jetPrefix+"JetEt", JetEt, &b_JetEt);
  fChain->SetBranchAddress(jetPrefix+"JetPt", JetPt, &b_JetPt);
  fChain->SetBranchAddress(jetPrefix+"JetPx", JetPx, &b_JetPx);
  fChain->SetBranchAddress(jetPrefix+"JetPy", JetPy, &b_JetPy);
  fChain->SetBranchAddress(jetPrefix+"JetPz", JetPz, &b_JetPz);
  fChain->SetBranchAddress(jetPrefix+"JetEta", JetEta, &b_JetEta);
  fChain->SetBranchAddress(jetPrefix+"JetPhi", JetPhi, &b_JetPhi);
  fChain->SetBranchAddress(jetPrefix+"JetFem", JetFem, &b_JetFem);
  fChain->SetBranchAddress(jetPrefix+"JetFhad", JetFhad, &b_JetFhad);
  fChain->SetBranchAddress(jetPrefix+"JetCharge", JetCharge, &b_JetCharge);
  fChain->SetBranchAddress(jetPrefix+"JetNConst", JetNConst, &b_JetNConst);

  //fChain->SetBranchAddress(jetPrefix+"JetRawP4", JetRawP4, &b_JetRawP4);
  fChain->SetBranchAddress(jetPrefix+"JetRawE", JetRawE, &b_JetRawE);
  fChain->SetBranchAddress(jetPrefix+"JetRawEt", JetRawEt, &b_JetRawEt);
  fChain->SetBranchAddress(jetPrefix+"JetRawPt", JetRawPt, &b_JetRawPt);
  fChain->SetBranchAddress(jetPrefix+"JetRawPx", JetRawPx, &b_JetRawPx);
  fChain->SetBranchAddress(jetPrefix+"JetRawPy", JetRawPy, &b_JetRawPy);
  fChain->SetBranchAddress(jetPrefix+"JetRawPz", JetRawPz, &b_JetRawPz);

  fChain->SetBranchAddress(jetPrefix+"JetCorrFactor", &JetCorrFactor, &b_JetCorrFactor);
  fChain->SetBranchAddress(jetPrefix+"JetPreselection", &JetPreselection, &b_JetPreselection);

  //Jet ID (implemented only for Calo (all three) and PF jets (loose/tight)
  fChain->SetBranchAddress(jetPrefix+"JetIDMinimal", JetIDMinimal, &b_JetIDMinimal);
  fChain->SetBranchAddress(jetPrefix+"JetIDLoose", JetIDLoose, &b_JetIDLoose);
  fChain->SetBranchAddress(jetPrefix+"JetIDTight", JetIDTight, &b_JetIDTight);

  //b-Tagging information
  fChain->SetBranchAddress(jetPrefix+"JetBTag_TCHE", JetBTag_TCHE, &b_JetBTag_TCHE);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_TCHP", JetBTag_TCHP, &b_JetBTag_TCHP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_jetProb", JetBTag_jetProb, &b_JetBTag_jetProb);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_jetBProb", JetBTag_jetBProb, &b_JetBTag_jetBProb);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SSVHE", JetBTag_SSVHE, &b_JetBTag_SSVHE);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SSVHP", JetBTag_SSVHP, &b_JetBTag_SSVHP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_CSV", JetBTag_CSV, &b_JetBTag_CSV);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_CSVMVA", JetBTag_CSVMVA, &b_JetBTag_CSVMVA);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLepton", JetBTag_SoftLepton, &b_JetBTag_SoftLepton);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLeptonByIP", JetBTag_SoftLeptonByIP, &b_JetBTag_SoftLeptonByIP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLeptonByPt", JetBTag_SoftLeptonByPt, &b_JetBTag_SoftLeptonByPt);

  //Calo/JPT Jet specific variables
  if (jetPrefix=="Calo"||jetPrefix=="JPT") {
    fChain->SetBranchAddress(jetPrefix+"JetfHPD", JetfHPD, &b_JetfHPD);
    fChain->SetBranchAddress(jetPrefix+"JetfRBX", JetfRBX, &b_JetfRBX);
    fChain->SetBranchAddress(jetPrefix+"Jetn90", Jetn90, &b_Jetn90);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPt", JetTrackPt, &b_JetTrackPt);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPhi", JetTrackPhi, &b_JetTrackPhi);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPhiWeighted", JetTrackPhiWeighted, &b_JetTrackPhiWeighted);
    fChain->SetBranchAddress(jetPrefix+"JetTrackNo", JetTrackNo, &b_JetTrackNo);
  }

  //JPT/PF Jet specific variables
  if (jetPrefix=="JPT"||jetPrefix=="PF") {
    fChain->SetBranchAddress(jetPrefix+"JetChargedFem", JetChargedFem, &b_JetChargedFem);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralFem", JetNeutralFem, &b_JetNeutralFem);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFhad", JetChargedFhad, &b_JetChargedFhad);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralFhad", JetNeutralFhad, &b_JetNeutralFhad);
    fChain->SetBranchAddress(jetPrefix+"JetChargedMult", JetChargedMult, &b_JetChargedMult);
    fChain->SetBranchAddress(jetPrefix+"JetElecMulti", JetElecMulti, &b_JetElecMulti);
    fChain->SetBranchAddress(jetPrefix+"JetMuonMulti", JetMuonMulti, &b_JetMuonMulti);
  }

  //PF Jet specific variables
  if (jetPrefix=="PF") {
    fChain->SetBranchAddress(jetPrefix+"JetChargedFmu", JetChargedFmu, &b_JetChargedFmu);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFele", JetChargedFele, &b_JetChargedFele);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFpho", JetChargedFpho, &b_JetChargedFpho);
    fChain->SetBranchAddress(jetPrefix+"JetHFFem", JetHFFem, &b_JetHFFem);
    fChain->SetBranchAddress(jetPrefix+"JetHFFhad", JetHFFhad, &b_JetHFFhad);
    fChain->SetBranchAddress(jetPrefix+"JetChargedHadMult", JetChargedHadMult, &b_JetChargedHadMult);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralHadMult", JetNeutralHadMult, &b_JetNeutralHadMult);
    fChain->SetBranchAddress(jetPrefix+"JetPhotonMult", JetPhotonMult, &b_JetPhotonMult);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralMult", JetNeutralMult, &b_JetNeutralMult);
  }

  fChain->SetBranchAddress(jetPrefix+"GenHt", &GenHt, &b_GenHt);
  fChain->SetBranchAddress(jetPrefix+"GenMHt", &GenMHt, &b_GenMHt);
  fChain->SetBranchAddress(jetPrefix+"JetGenE", JetGenE, &b_JetGenE);
  fChain->SetBranchAddress(jetPrefix+"JetGenEt", JetGenEt, &b_JetGenEt);
  fChain->SetBranchAddress(jetPrefix+"JetGenPt", JetGenPt, &b_JetGenPt);
  fChain->SetBranchAddress(jetPrefix+"JetGenPx", JetGenPx, &b_JetGenPx);
  fChain->SetBranchAddress(jetPrefix+"JetGenPy", JetGenPy, &b_JetGenPy);
  fChain->SetBranchAddress(jetPrefix+"JetGenPz", JetGenPz, &b_JetGenPz);
  fChain->SetBranchAddress(jetPrefix+"JetGenEta", JetGenEta, &b_JetGenEta);
  fChain->SetBranchAddress(jetPrefix+"JetGenPhi", JetGenPhi, &b_JetGenPhi);
  fChain->SetBranchAddress(jetPrefix+"JetPartonId", JetPartonId, &b_JetPartonId);
  fChain->SetBranchAddress(jetPrefix+"JetPartonMother", JetPartonMother, &b_JetPartonMother);
  fChain->SetBranchAddress(jetPrefix+"JetPartonPx", JetPartonPx, &b_JetPartonPx);
  fChain->SetBranchAddress(jetPrefix+"JetPartonPy", JetPartonPy, &b_JetPartonPy);
  fChain->SetBranchAddress(jetPrefix+"JetPartonPz", JetPartonPz, &b_JetPartonPz);
  fChain->SetBranchAddress(jetPrefix+"JetPartonEt", JetPartonEt, &b_JetPartonEt);
  fChain->SetBranchAddress(jetPrefix+"JetPartonE", JetPartonE, &b_JetPartonE);
  fChain->SetBranchAddress(jetPrefix+"JetPartonPhi", JetPartonPhi, &b_JetPartonPhi);
  fChain->SetBranchAddress(jetPrefix+"JetPartonEta", JetPartonEta, &b_JetPartonEta);
  fChain->SetBranchAddress(jetPrefix+"JetPartonFlavour", JetPartonFlavour, &b_JetPartonFlavour);

  //MET
  fChain->SetBranchAddress("nFull"+metPrefix+"MET", &nFullMET, &b_nFullMET);
  fChain->SetBranchAddress("nUncorr"+metPrefix+"MET", &nUncorrMET, &b_nUncorrMET);
  //fChain->SetBranchAddress(metPrefix+"METP4", &METP4, &b_METP4);
  fChain->SetBranchAddress(metPrefix+"MET_Fullcorr_nocc", MET_Fullcorr_nocc, &b_MET_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Fullcorr_nocc", &METpt_Fullcorr_nocc, &b_METpt_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Fullcorr_nocc", &METphi_Fullcorr_nocc, &b_METphi_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Fullcorr_nocc", &METsumEt_Fullcorr_nocc, &b_METsumEt_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsignificance_Fullcorr_nocc", &METsignificance_Fullcorr_nocc, &b_METsignificance_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"MET_Nocorr_nocc", MET_Nocorr_nocc, &b_MET_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Nocorr_nocc", &METpt_Nocorr_nocc, &b_METpt_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Nocorr_nocc", &METphi_Nocorr_nocc, &b_METphi_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Nocorr_nocc", &METsumEt_Nocorr_nocc, &b_METsumEt_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"MET_Muoncorr_nocc", MET_Muoncorr_nocc, &b_MET_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Muoncorr_nocc", &METpt_Muoncorr_nocc, &b_METpt_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Muoncorr_nocc", &METphi_Muoncorr_nocc, &b_METphi_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Muoncorr_nocc", &METsumEt_Muoncorr_nocc, &b_METsumEt_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"MET_JEScorr_nocc", MET_JEScorr_nocc, &b_MET_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_JEScorr_nocc", &METpt_JEScorr_nocc, &b_METpt_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_JEScorr_nocc", &METphi_JEScorr_nocc, &b_METphi_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_JEScorr_nocc", &METsumEt_JEScorr_nocc, &b_METsumEt_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"GenMET", GenMET, &b_GenMET);

  //fChain->SetBranchAddress(phtPrefix+"PhotonP4", PhotonP4, &b_PhotonP4);
  fChain->SetBranchAddress(phtPrefix+"PhotN", &PhotN, &b_PhotN);
  fChain->SetBranchAddress(phtPrefix+"PhotE", PhotE, &b_PhotE);
  fChain->SetBranchAddress(phtPrefix+"PhotEt", PhotEt, &b_PhotEt);
  fChain->SetBranchAddress(phtPrefix+"PhotPt", PhotPt, &b_PhotPt);
  fChain->SetBranchAddress(phtPrefix+"PhotPx", PhotPx, &b_PhotPx);
  fChain->SetBranchAddress(phtPrefix+"PhotPy", PhotPy, &b_PhotPy);
  fChain->SetBranchAddress(phtPrefix+"PhotPz", PhotPz, &b_PhotPz);
  fChain->SetBranchAddress(phtPrefix+"PhotEta", PhotEta, &b_PhotEta);
  fChain->SetBranchAddress(phtPrefix+"PhotPhi", PhotPhi, &b_PhotPhi);
  fChain->SetBranchAddress(phtPrefix+"PhotTrkIso", PhotTrkIso, &b_PhotTrkIso);
  fChain->SetBranchAddress(phtPrefix+"PhotECalIso", PhotECalIso, &b_PhotECalIso);
  fChain->SetBranchAddress(phtPrefix+"PhotHCalIso", PhotHCalIso, &b_PhotHCalIso);
  fChain->SetBranchAddress(phtPrefix+"PhotAllIso", PhotAllIso, &b_PhotAllIso);
  fChain->SetBranchAddress(phtPrefix+"PhotLoosePhoton", PhotLoosePhoton, &b_PhotLoosePhoton);
  fChain->SetBranchAddress(phtPrefix+"PhotTightPhoton", PhotTightPhoton, &b_PhotTightPhoton);

  fChain->SetBranchAddress(lepPrefix+"ElecVeto", &ElecVeto, &b_ElecVeto);
  //fChain->SetBranchAddress(lepPrefix+"ElectronP4", ElectronP4, &b_ElectronP4);
  fChain->SetBranchAddress(lepPrefix+"ElecN", &ElecN, &b_ElecN);
  fChain->SetBranchAddress(lepPrefix+"ElecE", ElecE, &b_ElecE);
  fChain->SetBranchAddress(lepPrefix+"ElecEt", ElecEt, &b_ElecEt);
  fChain->SetBranchAddress(lepPrefix+"ElecPt", ElecPt, &b_ElecPt);
  fChain->SetBranchAddress(lepPrefix+"ElecPx", ElecPx, &b_ElecPx);
  fChain->SetBranchAddress(lepPrefix+"ElecPy", ElecPy, &b_ElecPy);
  fChain->SetBranchAddress(lepPrefix+"ElecPz", ElecPz, &b_ElecPz);
  fChain->SetBranchAddress(lepPrefix+"ElecEta", ElecEta, &b_ElecEta);
  fChain->SetBranchAddress(lepPrefix+"ElecPhi", ElecPhi, &b_ElecPhi);
  fChain->SetBranchAddress(lepPrefix+"ElecCharge", ElecCharge, &b_ElecCharge);
  fChain->SetBranchAddress(lepPrefix+"ElecHOverE", ElecHOverE, &b_ElecHOverE);
  fChain->SetBranchAddress(lepPrefix+"ElecTrkIso", ElecTrkIso, &b_ElecTrkIso);
  fChain->SetBranchAddress(lepPrefix+"ElecECalIso", ElecECalIso, &b_ElecECalIso);
  fChain->SetBranchAddress(lepPrefix+"ElecHCalIso", ElecHCalIso, &b_ElecHCalIso);
  fChain->SetBranchAddress(lepPrefix+"ElecAllIso", ElecAllIso, &b_ElecAllIso);
  fChain->SetBranchAddress(lepPrefix+"ElecTrkChiNorm", ElecTrkChiNorm, &b_ElecTrkChiNorm);
  fChain->SetBranchAddress(lepPrefix+"ElecIdLoose", ElecIdLoose, &b_ElecIdLoose);
  fChain->SetBranchAddress(lepPrefix+"ElecIdTight", ElecIdTight, &b_ElecIdTight);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobLoose", ElecIdRobLoose, &b_ElecIdRobLoose);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobTight", ElecIdRobTight, &b_ElecIdRobTight);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobHighE", ElecIdRobHighE, &b_ElecIdRobHighE);
  fChain->SetBranchAddress(lepPrefix+"ElecChargeMode", ElecChargeMode, &b_ElecChargeMode);
  fChain->SetBranchAddress(lepPrefix+"ElecPtMode", ElecPtMode, &b_ElecPtMode);
  fChain->SetBranchAddress(lepPrefix+"ElecVx", ElecVx, &b_ElecVx);
  fChain->SetBranchAddress(lepPrefix+"ElecVy", ElecVy, &b_ElecVy);
  fChain->SetBranchAddress(lepPrefix+"ElecVz", ElecVz, &b_ElecVz);
  fChain->SetBranchAddress(lepPrefix+"ElecD0", ElecD0, &b_ElecD0);
  fChain->SetBranchAddress(lepPrefix+"ElecDz", ElecDz, &b_ElecDz);
  fChain->SetBranchAddress(lepPrefix+"ElecPtTrk", ElecPtTrk, &b_ElecPtTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecQOverPErrTrkMode", ElecQOverPErrTrkMode, &b_ElecQOverPErrTrkMode);
  fChain->SetBranchAddress(lepPrefix+"ElecCaloEnergy", ElecCaloEnergy, &b_ElecCaloEnergy);
  fChain->SetBranchAddress(lepPrefix+"ElecQOverPErrTrk", ElecQOverPErrTrk, &b_ElecQOverPErrTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPinTrk", ElecPinTrk, &b_ElecPinTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPoutTrk", ElecPoutTrk, &b_ElecPoutTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecLostHits", ElecLostHits, &b_ElecLostHits);
  fChain->SetBranchAddress(lepPrefix+"ElecValidHits", ElecValidHits, &b_ElecValidHits);
  fChain->SetBranchAddress(lepPrefix+"ElecEtaTrk", ElecEtaTrk, &b_ElecEtaTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPhiTrk", ElecPhiTrk, &b_ElecPhiTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecWidthClusterEta", ElecWidthClusterEta, &b_ElecWidthClusterEta);
  fChain->SetBranchAddress(lepPrefix+"ElecWidthClusterPhi", ElecWidthClusterPhi, &b_ElecWidthClusterPhi);

  fChain->SetBranchAddress(lepPrefix+"MuonVeto", &MuonVeto, &b_MuonVeto);
  //fChain->SetBranchAddress(lepPrefix+"MuonP4", MuonP4, &b_MuonP4);
  fChain->SetBranchAddress(lepPrefix+"MuonN", &MuonN, &b_MuonN);
  fChain->SetBranchAddress(lepPrefix+"MuonE", MuonE, &b_MuonE);
  fChain->SetBranchAddress(lepPrefix+"MuonEt", MuonEt, &b_MuonEt);
  fChain->SetBranchAddress(lepPrefix+"MuonPt", MuonPt, &b_MuonPt);
  fChain->SetBranchAddress(lepPrefix+"MuonPx", MuonPx, &b_MuonPx);
  fChain->SetBranchAddress(lepPrefix+"MuonPy", MuonPy, &b_MuonPy);
  fChain->SetBranchAddress(lepPrefix+"MuonPz", MuonPz, &b_MuonPz);
  fChain->SetBranchAddress(lepPrefix+"MuonEta", MuonEta, &b_MuonEta);
  fChain->SetBranchAddress(lepPrefix+"MuonPhi", MuonPhi, &b_MuonPhi);
  fChain->SetBranchAddress(lepPrefix+"MuonCharge", MuonCharge, &b_MuonCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkIso", MuonTrkIso, &b_MuonTrkIso);
  fChain->SetBranchAddress(lepPrefix+"MuonECalIso", MuonECalIso, &b_MuonECalIso);
  fChain->SetBranchAddress(lepPrefix+"MuonHCalIso", MuonHCalIso, &b_MuonHCalIso);
  fChain->SetBranchAddress(lepPrefix+"MuonAllIso", MuonAllIso, &b_MuonAllIso);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkChiNorm", MuonTrkChiNorm, &b_MuonTrkChiNorm);
  fChain->SetBranchAddress(lepPrefix+"MuonECalIsoDeposit", MuonECalIsoDeposit, &b_MuonECalIsoDeposit);
  fChain->SetBranchAddress(lepPrefix+"MuonHCalIsoDeposit", MuonHCalIsoDeposit, &b_MuonHCalIsoDeposit);
  fChain->SetBranchAddress(lepPrefix+"MuonIsGlobal", MuonIsGlobal, &b_MuonIsGlobal);
  fChain->SetBranchAddress(lepPrefix+"MuonIsStandAlone", MuonIsStandAlone, &b_MuonIsStandAlone);
  fChain->SetBranchAddress(lepPrefix+"MuonIsTracker", MuonIsTracker, &b_MuonIsTracker);
  fChain->SetBranchAddress(lepPrefix+"MuonGlobalMuonPromptTight", MuonGlobalMuonPromptTight, &b_MuonGlobalMuonPromptTight);
  fChain->SetBranchAddress(lepPrefix+"MuonAllArbitrated", MuonAllArbitrated, &b_MuonAllArbitrated);
  fChain->SetBranchAddress(lepPrefix+"MuonTrackerMuonArbitrated", MuonTrackerMuonArbitrated, &b_MuonTrackerMuonArbitrated);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationLoose", MuonTMLastStationLoose, &b_MuonTMLastStationLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationTight", MuonTMLastStationTight, &b_MuonTMLastStationTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTM2DCompatibilityLoose", MuonTM2DCompatibilityLoose, &b_MuonTM2DCompatibilityLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTM2DCompatibilityTight", MuonTM2DCompatibilityTight, &b_MuonTM2DCompatibilityTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMOneStationLoose", MuonTMOneStationLoose, &b_MuonTMOneStationLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMOneStationTight", MuonTMOneStationTight, &b_MuonTMOneStationTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedLowPtLoose", MuonTMLastStationOptimizedLowPtLoose, &b_MuonTMLastStationOptimizedLowPtLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedLowPtTight", MuonTMLastStationOptimizedLowPtTight, &b_MuonTMLastStationOptimizedLowPtTight);
  fChain->SetBranchAddress(lepPrefix+"MuonGMTkChiCompatibility", MuonGMTkChiCompatibility, &b_MuonGMTkChiCompatibility);
  fChain->SetBranchAddress(lepPrefix+"MuonGMStaChiCompatibility", MuonGMStaChiCompatibility, &b_MuonGMStaChiCompatibility);
  fChain->SetBranchAddress(lepPrefix+"MuonGMTkKinkTight", MuonGMTkKinkTight, &b_MuonGMTkKinkTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationAngLoose", MuonTMLastStationAngLoose, &b_MuonTMLastStationAngLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationAngTight", MuonTMLastStationAngTight, &b_MuonTMLastStationAngTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedBarrelLowPtLoose", MuonTMLastStationOptimizedBarrelLowPtLoose, &b_MuonTMLastStationOptimizedBarrelLowPtLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedBarrelLowPtTight", MuonTMLastStationOptimizedBarrelLowPtTight, &b_MuonTMLastStationOptimizedBarrelLowPtTight);
  fChain->SetBranchAddress(lepPrefix+"MuonCombChi2", MuonCombChi2, &b_MuonCombChi2);
  fChain->SetBranchAddress(lepPrefix+"MuonCombNdof", MuonCombNdof, &b_MuonCombNdof);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVx", MuonCombVx, &b_MuonCombVx);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVy", MuonCombVy, &b_MuonCombVy);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVz", MuonCombVz, &b_MuonCombVz);
  fChain->SetBranchAddress(lepPrefix+"MuonCombD0", MuonCombD0, &b_MuonCombD0);
  fChain->SetBranchAddress(lepPrefix+"MuonCombDz", MuonCombDz, &b_MuonCombDz);
  fChain->SetBranchAddress(lepPrefix+"MuonStandValidHits", MuonStandValidHits, &b_MuonStandValidHits);
  fChain->SetBranchAddress(lepPrefix+"MuonStandLostHits", MuonStandLostHits, &b_MuonStandLostHits);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPt", MuonStandPt, &b_MuonStandPt);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPz", MuonStandPz, &b_MuonStandPz);
  fChain->SetBranchAddress(lepPrefix+"MuonStandP", MuonStandP, &b_MuonStandP);
  fChain->SetBranchAddress(lepPrefix+"MuonStandEta", MuonStandEta, &b_MuonStandEta);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPhi", MuonStandPhi, &b_MuonStandPhi);
  fChain->SetBranchAddress(lepPrefix+"MuonStandCharge", MuonStandCharge, &b_MuonStandCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonStandChi", MuonStandChi, &b_MuonStandChi);
  fChain->SetBranchAddress(lepPrefix+"MuonStandQOverPError", MuonStandQOverPError, &b_MuonStandQOverPError);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkValidHits", MuonTrkValidHits, &b_MuonTrkValidHits);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkLostHits", MuonTrkLostHits, &b_MuonTrkLostHits);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkD0", MuonTrkD0, &b_MuonTrkD0);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPt", MuonTrkPt, &b_MuonTrkPt);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPz", MuonTrkPz, &b_MuonTrkPz);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkP", MuonTrkP, &b_MuonTrkP);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkEta", MuonTrkEta, &b_MuonTrkEta);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPhi", MuonTrkPhi, &b_MuonTrkPhi);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkCharge", MuonTrkCharge, &b_MuonTrkCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkChi", MuonTrkChi, &b_MuonTrkChi);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkQOverPError", MuonTrkQOverPError, &b_MuonTrkQOverPError);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkOuterZ", MuonTrkOuterZ, &b_MuonTrkOuterZ);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkOuterR", MuonTrkOuterR, &b_MuonTrkOuterR);

  fChain->SetBranchAddress("beamspotX0", &beamspotX0, &b_beamspotX0);
  fChain->SetBranchAddress("beamspotY0", &beamspotY0, &b_beamspotY0);
  fChain->SetBranchAddress("beamspotZ0", &beamspotZ0, &b_beamspotZ0);
  fChain->SetBranchAddress("beamspotWidthX", &beamspotWidthX, &b_beamspotWidthX);
  fChain->SetBranchAddress("beamspotWidthY", &beamspotWidthY, &b_beamspotWidthY);
  fChain->SetBranchAddress("beamspotX0Error", &beamspotX0Error, &b_beamspotX0Error);
  fChain->SetBranchAddress("beamspotY0Error", &beamspotY0Error, &b_beamspotY0Error);
  fChain->SetBranchAddress("beamspotZ0Error", &beamspotZ0Error, &b_beamspotZ0Error);
  fChain->SetBranchAddress("beamspotWidthXError", &beamspotWidthXError, &b_beamspotWidthXError);
  fChain->SetBranchAddress("beamspotWidthYError", &beamspotWidthYError, &b_beamspotWidthYError);
  fChain->SetBranchAddress("beamspotSigmaZ0", &beamspotSigmaZ0, &b_beamspotSigmaZ0);
  fChain->SetBranchAddress("beamspotSigmaZ0Error", &beamspotSigmaZ0Error, &b_beamspotSigmaZ0Error);
  fChain->SetBranchAddress("beamspotdxdz", &beamspotdxdz, &b_beamspotdxdz);
  fChain->SetBranchAddress("beamspotdxdzError", &beamspotdxdzError, &b_beamspotdxdzError);
  fChain->SetBranchAddress("beamspotdydz", &beamspotdydz, &b_beamspotdydz);
  fChain->SetBranchAddress("beamspotdydzError", &beamspotdydzError, &b_beamspotdydzError);
  fChain->SetBranchAddress("beamspotEmittanceX", &beamspotEmittanceX, &b_beamspotEmittanceX);
  fChain->SetBranchAddress("beamspotEmittanceY", &beamspotEmittanceY, &b_beamspotEmittanceY);
  fChain->SetBranchAddress("beamspotBetaStar", &beamspotBetaStar, &b_beamspotBetaStar);

  fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
  fChain->SetBranchAddress("VertexChi2", VertexChi2, &b_VertexChi2);
  fChain->SetBranchAddress("VertexNdof", VertexNdof, &b_VertexNdof);
  fChain->SetBranchAddress("VertexNTrks", VertexNTrks, &b_VertexNTrks);
  fChain->SetBranchAddress("VertexNRawTrks", VertexNRawTrks, &b_VertexNRawTrks);
  fChain->SetBranchAddress("VertexIsValid", VertexIsValid, &b_VertexIsValid);
  fChain->SetBranchAddress("VertexNormalizedChi2", VertexNormalizedChi2, &b_VertexNormalizedChi2);
  fChain->SetBranchAddress("VertexX", VertexX, &b_VertexX);
  fChain->SetBranchAddress("VertexY", VertexY, &b_VertexY);
  fChain->SetBranchAddress("VertexZ", VertexZ, &b_VertexZ);
  fChain->SetBranchAddress("Vertexd0", Vertexd0, &b_Vertexd0);
  fChain->SetBranchAddress("VertexdX", VertexdX, &b_VertexdX);
  fChain->SetBranchAddress("VertexdY", VertexdY, &b_VertexdY);
  fChain->SetBranchAddress("VertexdZ", VertexdZ, &b_VertexdZ);

  fChain->SetBranchAddress("MPTPhi", &MPTPhi, &b_MPTPhi);
  fChain->SetBranchAddress("MPTPx", &MPTPx, &b_MPTPx);
  fChain->SetBranchAddress("MPTPy", &MPTPy, &b_MPTPy);
  fChain->SetBranchAddress("MPTPz", &MPTPz, &b_MPTPz);

  fChain->SetBranchAddress("nHLT", &nHLT, &b_nHLT);
  fChain->SetBranchAddress("HLTArray", HLTArray, &b_HLTArray);
  fChain->SetBranchAddress("HLTNames", HLTNames, &b_HLTNames);
  fChain->SetBranchAddress("HLT1JET", &HLT1JET, &b_HLT1JET);
  fChain->SetBranchAddress("HLT2JET", &HLT2JET, &b_HLT2JET);
  fChain->SetBranchAddress("HLT1MET", &HLT1MET, &b_HLT1MET);
  fChain->SetBranchAddress("HLT11HT", &HLT11HT, &b_HLT1HT);
  fChain->SetBranchAddress("HLT1HT1MHT", &HLT1HT1MHT, &b_HLT1HT1MHT);
  fChain->SetBranchAddress("HLT1MUON", &HLT1MUON, &b_HLT1MUON);
  fChain->SetBranchAddress("HLTMINBIAS", &HLTMINBIAS, &b_HLTMINBIAS);

  fChain->SetBranchAddress("nL1Technical", &nL1Technical, &b_nL1Technical);
  fChain->SetBranchAddress("L1TechnicalArray", L1TechnicalArray, &b_L1TechnicalArray);
  fChain->SetBranchAddress("L1TechnicalNames", L1TechnicalNames, &b_L1TechnicalNames);
  fChain->SetBranchAddress("nL1Physics", &nL1Physics, &b_nL1Physics);
  fChain->SetBranchAddress("L1PhysicsArray", L1PhysicsArray, &b_L1PhysicsArray);
  fChain->SetBranchAddress("L1PhysicsNames", L1PhysicsNames, &b_L1PhysicsNames);
  //fChain->SetBranchAddress("L1Triggered", &L1Triggered, &b_L1Triggered);
  //fChain->SetBranchAddress("L1Prescaled", &L1Prescaled, &b_L1Prescaled);
  fChain->SetBranchAddress("L1MUON1", &L1MUON1, &b_L1MUON1);
  fChain->SetBranchAddress("L1MUON2", &L1MUON2, &b_L1MUON2);
  fChain->SetBranchAddress("L1MUON3", &L1MUON3, &b_L1MUON3);
  fChain->SetBranchAddress("L1MUON4", &L1MUON4, &b_L1MUON4);
  Notify();
}

Bool_t DiJetStudy::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

Bool_t DiJetStudy::jetID(int index, bool tight) {
  //Requirements for jetID
  bool jetID = false;
  bool jetRequirement;
  bool looseJet = true;
  if (tight)
    jetRequirement = JetIDTight[index];
  else
    jetRequirement = JetIDLoose[index];

  ////calo/jpt
  //if (jetPrefix_=="Calo"||jetPrefix_=="JPT") {
  //  looseJet &= JetPt[index]         > 20.;
  //  looseJet &= fabs(JetEta[index])  < 5.0;
  //  looseJet &= JetfHPD[index]       < 0.98;
  //  looseJet &= Jetn90[index]        > 1;
  //  looseJet &= (fabs(JetEta[index]) > 2.6 || JetFem[index] > 0.01);
  //}
  if (jetPrefix_=="JPT") {
    looseJet &= JetPt[index]         > 20.;
    looseJet &= fabs(JetEta[index])  < 5.0;
    looseJet &= JetfHPD[index]       < 0.98;
    looseJet &= Jetn90[index]        > 1;
  }
  //pf
  //else if (jetPrefix_=="PF") {
  //  looseJet &= JetPt[index]          > 20.;
  //  looseJet &= fabs(JetEta[index])   < 5.0;
  //  looseJet &= JetNeutralFhad[index] < 1.0;
  //  looseJet &= JetNeutralFem[index]  < 1.0;
  //  looseJet &= JetChargedFem[index]  < 1.0;
  //  looseJet &= (fabs(JetEta[index])  > 2.4 || (JetChargedFhad[index] > 0.0 && JetChargedMult[index] > 0.0) );
  //}
  else if (jetPrefix_=="PF" || jetPrefix_=="Calo")
    looseJet &= JetIDLoose[index];
  //track
  else {
    looseJet &= JetPt[index]        > 20.;
    looseJet &= fabs(JetEta[index]) < 2.4;
  }

  //if (jetRequirement)
  if (looseJet)
    jetID = true;
  
  return jetID;
}

Bool_t DiJetStudy::muonID(int index, int mode) {
  //Requirements for muonID
  double relIso = (MuonTrkIso[index]+MuonECalIso[index]+MuonHCalIso[index])/MuonPt[index];
  bool muonID = false;
  if (MuonGlobalMuonPromptTight[index])
    //if (MuonIsGlobal[index])
    //if (< muon_maxchi2)
    //if (>= muon_minhits)
    if (MuonPt[index] >= muon_minpt)
      if (fabs(MuonEta[index]) <= muon_maxeta)
	if (relIso < muon_maxreliso)
	  if (MuonTrkD0[index]< muon_maxd0)
	    //if (MuonCompD0[index]< muon_maxd0)
	    muonID = true;
  
  return muonID;
}

Bool_t DiJetStudy::electronID(int index, bool tight ) {
  //Requirements for electronID
  double relIso = (ElecTrkIso[index]+ElecECalIso[index]+ElecHCalIso[index])/ElecPt[index];
  bool electronID = false;
  bool electronRequirement;
  if (tight)
    electronRequirement = ElecIdTight[index];
  else
    electronRequirement = ElecIdLoose[index];

  if (electronRequirement)
    if (ElecPt[index] >= electron_minpt)
      //if (fabs(ElecEta[index]) <= electron_maxeta)
      if (relIso < electron_maxreliso)
	if (ElecD0[index]< electron_maxd0)
	  //if (ElecCompD0[index]< electron_maxd0)
	  electronID = true;
  
  return electronID;
}

//Simple identification criteria for photons
Bool_t DiJetStudy::photonID(int index, bool tight) {

  //Requirements for photonID
  double relIso = (PhotTrkIso[index]+PhotECalIso[index]+PhotHCalIso[index])/PhotPt[index];
  bool photonID = false;
  bool photonRequirement;
  if (tight)
    photonRequirement = PhotTightPhoton[index];
  else
    photonRequirement = PhotLoosePhoton[index];

  if (photonRequirement)
    if (PhotPt[index] >= photon_minpt)
      if (fabs(PhotEta[index]) <= photon_maxeta)
	if (relIso < photon_maxreliso)
	  //if (PhotTrkD0[index]< photon_maxd0)
	  //if (PhotCompD0[index]< photon_maxd0)
	  photonID = true;
  
  return photonID;
}

//Compute HT from the Jet Collection
//If possible, use the stored P4
Double_t DiJetStudy::computeHT(double& minpt, double& maxeta, bool fromRAW) {
  
  LorentzVs theJets;
  Double_t theHT    = 0.;
  
  LorentzV theJet;
  for (int jet = 0; jet < NJets; ++jet) {
    if (fromRAW) 
      theJet.SetPxPyPzE(JetRawPx[jet],JetRawPy[jet],JetRawPz[jet],JetRawE[jet]);
    else
      theJet.SetPxPyPzE(JetPx[jet],JetPy[jet],JetPz[jet],JetE[jet]);
    if (theJet.Pt() > minpt)
      if (fabs(theJet.Eta()) < maxeta)
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theHT += theJet.Pt();
  }

  //if (fromRAW) 
  //  theJets = JetRawP4;
  //else 
  //  theJets = JetP4;
  //
  //for (unsigned int jet = 0; jet < theJets.size(); ++jet) {
  //  LorentzV myJet = theJets.at(jet);
  //  if (myJet.Pt() > minpt)
  //    if (fabs(myJet.Eta()) < maxeta)
  //	//if (jetID(jet,false)
  //	//Do we want some jetID requirement?
  //	theHT += myJet.Pt();
  //}
  return theHT;
}

TLorentzVector DiJetStudy::computeMHT(double& minpt, double& maxeta, bool fromRAW) {

  LorentzVs theJets;
  TLorentzVector theMHT;
  theMHT.SetPxPyPzE(0,0,0,0);

  TLorentzVector theJet;
  for (int jet = 0; jet < NJets; ++jet) {
    if (fromRAW) 
      theJet.SetPxPyPzE(JetRawPx[jet],JetRawPy[jet],JetRawPz[jet],JetRawE[jet]);
    else
      theJet.SetPxPyPzE(JetPx[jet],JetPy[jet],JetPz[jet],JetE[jet]);
    if (theJet.Pt() > minpt)
      if (fabs(theJet.Eta()) < maxeta) {
	
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theMHT -= theJet;
      }
  }

  //if (fromRAW) 
  //  theJets = JetRawP4;  
  //else 
  //  theJets = JetP4;
  //
  //for (unsigned int jet = 0; jet < theJets.size(); ++jet) {
  //  TLorentzVector myJet = theJets.at(jet);
  //  if (myJet.Pt() > minpt)
  //    if (fabs(myJet.Eta()) < maxeta)
  //	//if (jetID(jet,false)
  //	//Do we want some jetID requirement?
  //	theMHT -= myJet;
  //}
  return theMHT;
}

Double_t DiJetStudy::computeDPhiStar(TLorentzVector mht, double& minpt, double& maxeta, bool fromRAW) {

  LorentzVs theJets;
  double dphistar = 10.;

  TLorentzVector theJet;
  for (int jet = 0; jet < NJets; ++jet) {

    if (fromRAW) 
      theJet.SetPxPyPzE(JetRawPx[jet],JetRawPy[jet],JetRawPz[jet],JetRawE[jet]);
    else 
      theJet.SetPxPyPzE(JetPx[jet],JetPy[jet],JetPz[jet],JetE[jet]);
    if (theJet.Pt() > minpt)
      if (fabs(theJet.Eta()) < maxeta) {
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	mht += theJet;
	double tmpdphi = theJet.DeltaPhi(mht);
	dphistar = (dphistar < 0)    ? -dphistar         : dphistar;
	dphistar = (dphistar > M_PI) ? 2*M_PI - dphistar : dphistar;
	dphistar = (fabs(dphistar) < fabs(tmpdphi)) ? dphistar : tmpdphi;
      }
  }

  //if (fromRAW) 
  //  theJets = JetRawP4;  
  //else 
  //  theJets = JetP4;
  //
  //for (unsigned int jet = 0; jet < theJets.size(); ++jet) {
  //  TLorentzVector myJet = theJets.at(jet);
  //if (myJet.Pt() > minpt)
  //  if (fabs(myJet.Eta()) < maxeta) {
  //	//if (jetID(jet,false)
  //	//Do we want some jetID requirement?
  //	mht += myJet;
  //	double tmpdphi = mht.DeltaPhi(myJet);
  //	dphistar = (fabs(dphistar) < fabs(tmpdphi)) ? dphistar : tmpdphi;
  //	
  //  }
  return dphistar;
}

void DiJetStudy::Show(Long64_t entry) {

  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t DiJetStudy::Preselection(Long64_t entry) {
  int preselection = -1;
  // This function may be called from Loop.
  if (JetPt[1] > 30)
    preselection = 1;
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return preselection;
}

Int_t DiJetStudy::TriggerSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::JetSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::DiJetSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::LeptonVeto(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::METSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::HTSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::MHTSelection(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

Int_t DiJetStudy::Cut(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

//Probe muon has tighter criteria
Bool_t DiJetStudy::goodMuonProbe(int index, int mode, int probeCharge) {
  if (probeCharge==MuonCharge[index])
    return false;
  bool result = false;
  bool muonType;
  double relIso = 0;

  switch (mode) {
  case 1:
    muonType = MuonIsGlobal[index];
    break;
  case 2:
    muonType = MuonIsTracker[index];
    break;
  case 3:
    muonType = MuonIsStandAlone[index];
    break;
  default:
    muonType = MuonIsTracker[index];
    break;
  }

  relIso = (MuonTrkIso[index]+MuonECalIso[index]+MuonHCalIso[index])/MuonPt[index];
  
  if (muonType && MuonIsTracker[index]) {
    if (MuonPt[index] > muon_minpt)
      if (fabs(MuonEta[index]) < muon_maxeta)
	if (MuonTrkValidHits[index] > muon_minhits)
	  if (relIso < muon_maxreliso)
	    //if (MuonCombD0[index] < muon_maxd0)
	    if (MuonTrkD0[index] < muon_maxd0)
	      if (MuonCombChi2[index] < muon_maxchi2)
		result = true;
	  }
  return result;
}

//Tag muon criteria

Bool_t DiJetStudy::goodMuonTag(int index, int mode) {
  bool result = false;
  bool muonType;
  double relIso = 0;

  switch (mode) {
  case 1:
    muonType = MuonIsGlobal[index];
    break;
  case 2:
    muonType = MuonIsTracker[index];
    break;
  case 3:
    muonType = MuonIsStandAlone[index];
    break;
  default:
    muonType = MuonIsTracker[index];
    break;
  }

  relIso = (MuonTrkIso[index]+MuonECalIso[index]+MuonHCalIso[index])/MuonPt[index];

  if (muonType) {
    if (MuonPt[index] > muon_minpt)
      if (fabs(MuonEta[index]) < muon_maxeta)
	if (MuonTrkValidHits[index] > muon_minhits)
	  if (relIso < muon_maxreliso)
	    //if (MuonCombD0[index] < muon_maxd0)
	    //if (MuonTrkD0[index] < muon_maxd0)
	    //if (MuonCombChi2[index] < muon_maxchi2)
	    result = true;
	  }
  return result;
}


#endif // #ifdef DiJetStudy_cxx

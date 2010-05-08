#ifndef firstData_h
#define firstData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "TLorentzVector.h"

//#define M_PI = 3.1415926535897932348626

class firstData {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  bool doGenInfo_;
  
  // Declaration of leaf types
  UInt_t          Run;
  UInt_t          Event;

  Int_t           nHLT;
  Int_t           HLTArray[200];
  Int_t           HLTNames[200];
  UChar_t         HLT1JET;
  UChar_t         HLT2JET;
  UChar_t         HLT1MET;
  UChar_t         HLT1HT;
  UChar_t         HLT1HT1MHT;
  UChar_t         HLT1MUON;

  //gen particles
  UInt_t      genN;
  UInt_t      genid[500];
  UInt_t      genMother[500];
  Double_t    genE[500];
  Double_t    genPx[500];
  Double_t    genPy[500];
  Double_t    genPz[500];
  Double_t    genStatus[500];

  Double_t    genLepN;
  Double_t    genLepId[500];
  Double_t    genLepMother[500];
  Double_t    genLepE[500];
  Double_t    genLepPx[500];
  Double_t    genLepPy[500];
  Double_t    genLepPz[500];
  Double_t    genLepStatus[500];
  
  Double_t    genPhotN;
  Double_t    genPhotId[500];
  Double_t    genPhotMother[500];
  Double_t    genPhotE[500];
  Double_t    genPhotPx[500];
  Double_t    genPhotPy[500];
  Double_t    genPhotPz[500];
  Double_t    genPhotStatus[500];
  


  //Vertex variables
  UInt_t          nVtx;
  Double_t        VtxChi2[5];
  Double_t        VtxNdof[5];
  Bool_t          VtxIsValid[5];
  Double_t        VtxNormalizedChi2[5];
  Double_t        VtxX[5];
  Double_t        VtxY[5];
  Double_t        VtxZ[5];
  Double_t        VtxdX[5]; 
  Double_t        VtxdY[5]; 
  Double_t        VtxdZ[5];

  //MET variables
  UInt_t          nFullMET;
  UInt_t          nUncorrMET;

  //PF MET
  Double_t        pfMET_Fullcorr_nocc[3];
  Double_t        pfMETphi_Fullcorr_nocc;
  Double_t        pfMETsumEt_Fullcorr_nocc;
  Double_t        pfMETsignificance_Fullcorr_nocc;

  Double_t        pfMET_Nocorr_nocc[2];
  Double_t        pfMETpt_Nocorr_nocc;
  Double_t        pfMETphi_Nocorr_nocc;
  Double_t        pfMETsumEt_Nocorr_nocc;

  Double_t        pfMET_JECcorr_nocc[2];
  Double_t        pfMETpt_JECcorr_nocc;
  Double_t        pfMETphi_JECcorr_nocc;
  Double_t        pfMETsumEt_JECcorr_nocc;

  Double_t        pfMET_Muoncorr_nocc[2];
  Double_t        pfMETpt_Muoncorr_nocc;
  Double_t        pfMETphi_Muoncorr_nocc;
  Double_t        pfMETsumEt_Muoncorr_nocc;

  Double_t        pfMET_Gen[3];

  //TC MET
  Double_t        tcMET_Fullcorr_nocc[3];
  Double_t        tcMETphi_Fullcorr_nocc;
  Double_t        tcMETsumEt_Fullcorr_nocc;
  Double_t        tcMETsignificance_Fullcorr_nocc;

  Double_t        tcMET_Nocorr_nocc[2];
  Double_t        tcMETpt_Nocorr_nocc;
  Double_t        tcMETphi_Nocorr_nocc;
  Double_t        tcMETsumEt_Nocorr_nocc;

  Double_t        tcMET_JECcorr_nocc[2];
  Double_t        tcMETpt_JECcorr_nocc;
  Double_t        tcMETphi_JECcorr_nocc;
  Double_t        tcMETsumEt_JECcorr_nocc;

  Double_t        tcMET_Muoncorr_nocc[2];
  Double_t        tcMETpt_Muoncorr_nocc;
  Double_t        tcMETphi_Muoncorr_nocc;
  Double_t        tcMETsumEt_Muoncorr_nocc;

  Double_t        tcMET_Gen[3];

  //Calo MET
  Double_t        caloMET_Fullcorr_nocc[3];
  Double_t        caloMETphi_Fullcorr_nocc;
  Double_t        caloMETsumEt_Fullcorr_nocc;
  Double_t        caloMETsignificance_Fullcorr_nocc;

  Double_t        caloMET_Nocorr_nocc[2];
  Double_t        caloMETpt_Nocorr_nocc;
  Double_t        caloMETphi_Nocorr_nocc;
  Double_t        caloMETsumEt_Nocorr_nocc;

  Double_t        caloMET_JECcorr_nocc[2];
  Double_t        caloMETpt_JECcorr_nocc;
  Double_t        caloMETphi_JECcorr_nocc;
  Double_t        caloMETsumEt_JECcorr_nocc;

  Double_t        caloMET_Muoncorr_nocc[2];
  Double_t        caloMETpt_Muoncorr_nocc;
  Double_t        caloMETphi_Muoncorr_nocc;
  Double_t        caloMETsumEt_Muoncorr_nocc;

  Double_t        caloMET_Gen[3];

  //Jet variables
  UInt_t          CaloNJets;
  Double_t        CaloHt;
  Double_t        CaloMHt;
  Double_t        CaloMHx;
  Double_t        CaloMHy;
  Double_t        CaloJetE[50];
  Double_t        CaloJetEt[50];
  Double_t        CaloJetPt[50];
  Double_t        CaloJetPx[50];
  Double_t        CaloJetPy[50];
  Double_t        CaloJetPz[50];
  Double_t        CaloJetEta[50];
  Double_t        CaloJetPhi[50];
  Double_t        CaloJetFem[50];
  Double_t        CaloJetfHPD[50];
  Double_t        CaloJetfRBX[50];
  Double_t        CaloJetn90[50];
  Double_t        CaloJet_JPTcorrFactor[50];
  Double_t        CaloJetPartonFlavour[50];
  Double_t        CaloJetPreselection[50];

  Float_t         JetsBTag_TkCountHighEff[50];
  Float_t         JetsBTag_SimpleSecVtx[50];
  Float_t         JetsBTag_CombSecVtx[50];

  Double_t        CaloJetTrackPt[50];
  Double_t        CaloJetTrackPhi[50];
  Double_t        CaloJetTrackPhiWeighted[50];
  UInt_t          CaloJetTrackNo[50];

  //JPT Jet variables
  UInt_t          JPTNJets;
  Double_t        JPTHt;
  Double_t        JPTMHt;
  Double_t        JPTMHx;
  Double_t        JPTMHy;
  Double_t        JPTJetE[50];
  Double_t        JPTJetEt[50];
  Double_t        JPTJetPt[50];
  Double_t        JPTJetPx[50];
  Double_t        JPTJetPy[50];
  Double_t        JPTJetPz[50];
  Double_t        JPTJetEta[50];
  Double_t        JPTJetPhi[50];
  Double_t        JPTJetFem[50];
  Double_t        JPTJetfHPD[50];
  Double_t        JPTJetfRBX[50];
  Double_t        JPTJetn90[50];
  Double_t        JPTJetPartonFlavour[50];
  Double_t        JPTJetPreselection[50];

  Double_t        JPTJetTrackPt[50];
  Double_t        JPTJetTrackPhi[50];
  Double_t        JPTJetTrackPhiWeighted[50];
  UInt_t          JPTJetTrackNo[50];

  //Track Jet variables
  UInt_t          TrackNJets;
  Double_t        TrackHt;
  Double_t        TrackMHt;
  Double_t        TrackMHx;
  Double_t        TrackMHy;
  Double_t        TrackJetE[50];
  Double_t        TrackJetEt[50];
  Double_t        TrackJetPt[50];
  Double_t        TrackJetPx[50];
  Double_t        TrackJetPy[50];
  Double_t        TrackJetPz[50];
  Double_t        TrackJetEta[50];
  Double_t        TrackJetPhi[50];
  Double_t        TrackJetFem[50];
  Double_t        TrackJetCharge[50];
  Double_t        TrackJetPartonFlavour[50];
  Double_t        TrackJetPreselection[50];

  //PF jet variables
  UInt_t          PFNJets;
  Double_t        PFHt;
  Double_t        PFMHt;
  Double_t        PFMHx;
  Double_t        PFMHy;
  Double_t        PFJetE[50];
  Double_t        PFJetEt[50];
  Double_t        PFJetPt[50];
  Double_t        PFJetPx[50];
  Double_t        PFJetPy[50];
  Double_t        PFJetPz[50];
  Double_t        PFJetEta[50];
  Double_t        PFJetPhi[50];
  Double_t        PFJetFem[50];
  Double_t        PFJetCharge[50];
  Double_t        PFJetPartonFlavour[50];
  Double_t        PFJetPreselection[50];

  UInt_t          JetPartonId[50];
  UInt_t          JetPartonMother[50];
  Double_t        JetPartonPx[50];
  Double_t        JetPartonPy[50];
  Double_t        JetPartonPz[50];
  Double_t        JetPartonEt[50];
  Double_t        JetPartonE[50];
  Double_t        JetPartonPhi[50];
  Double_t        JetPartonEta[50];
  UInt_t          JetPartonFlavour[50];

  Double_t        GenHt;
  Double_t        GenMHt;
  Double_t        GenMHx;
  Double_t        GenMHy;
  Double_t        GenJetE[50];
  Double_t        GenJetEt[50];
  Double_t        GenJetPt[50];
  Double_t        GenJetPx[50];
  Double_t        GenJetPy[50];
  Double_t        GenJetPz[50];
  Double_t        GenJetEta[50];
  Double_t        GenJetPhi[50];
	          
  //Electron variables
  Bool_t          ElecVeto;
  UInt_t          ElecN;
  Double_t        ElecEt[50];
  Double_t        ElecPt[50];
  Double_t        ElecPx[50];
  Double_t        ElecPy[50];
  Double_t        ElecPz[50];
  Double_t        ElecE[50];
  Double_t        ElecEta[50];
  Double_t        ElecPhi[50];
  Double_t        ElecTrkIso[50];
  Double_t        ElecECalIso[50];
  Double_t        ElecHCalIso[50];
  Double_t        ElecAllIso[50];
  Double_t        ElecTrkChiNorm[50];
  Double_t        ElecCharge[50];
  Double_t        ElecIdLoose[50];
  Double_t        ElecIdTight[50];
  Double_t        ElecIdRobLoose[50];
  Double_t        ElecIdRobTight[50];
  Double_t        ElecChargeMode[50];
  Double_t        ElecPtTrkMode[50];
  Double_t        ElecQOverPErrTrkMode[50];

  Double_t        ElecCaloEnergy[50];
  Double_t        ElecHOverE[50];
  Double_t        ElecVx[50];
  Double_t        ElecVy[50];
  Double_t        ElecVz[50];
  Double_t        ElecD0[50];
  Double_t        ElecDz[50];
  Double_t        ElecPtTrk[50];
  Double_t        ElecQOverPErrTrk[50];
  Double_t        ElecLostHits[50];
  Double_t        ElecValidHits[50];
  Double_t        ElecNCluster[50];
  Double_t        ElecEtaTrk[50];
  Double_t        ElecPhiTrk[50];
  Double_t        ElecWidthClusterEta[50];
  Double_t        ElecWidthClusterPhi[50];
  Double_t        ElecPinTrk[50];
  Double_t        ElecPoutTrk[50];
  Double_t        ElecNormChi2[50];
  
  Double_t        ElecECalIsoDeposit[50];
  Double_t        ElecHCalIsoDeposit[50];
  
  UInt_t       ElecGenPdgId[50];
  UInt_t       ElecGenMother[50];
  Double_t     ElecGenPx[50];
  Double_t     ElecGenPy[50];
  Double_t     ElecGenPz[50];
  Double_t     ElecGenPt[50];
  Double_t     ElecGenEt[50];
  Double_t     ElecGenE[50];
  
  //Muon variables
  Bool_t          MuonVeto;
  UInt_t          MuonN;
  Double_t        MuonEt[50];
  Double_t        MuonPt[50];
  Double_t        MuonPx[50];
  Double_t        MuonPy[50];
  Double_t        MuonPz[50];
  Double_t        MuonE[50];
  Double_t        MuonEta[50];
  Double_t        MuonPhi[50];
  Double_t        MuonTrkIso[50];
  Double_t        MuonECalIso[50];
  Double_t        MuonHCalIso[50];
  Double_t        MuonAllIso[50];
  Double_t        MuonTrkChiNorm[50];
  Double_t        MuonCharge[50];
  Bool_t          MuonIsGlobal[50];
  Bool_t          MuonIsStandAlone[50];
  Bool_t          MuonIsTracker[50]; 
  Bool_t          MuonIsGlobalTight[50];
  Bool_t          MuonIsTMLastStationLoose[50];
  Bool_t          MuonTMLastStationTight[50];
  Bool_t          MuonTM2DCompatibilityLoose[50];
  Bool_t          MuonTM2DCompatibilityTight[50];
  	          
  Double_t        MuonCombChi2[50];
  Double_t        MuonCombNdof[50];
  Double_t        MuonTrkD0[50];
  	          
  Double_t        MuonId[50];
  Double_t        MuonCombVx[50];
  Double_t        MuonCombVy[50];
  Double_t        MuonCombVz[50];
  Double_t        MuonCombD0[50];
  Double_t        MuonCombDz[50];
	          
  Double_t        MuonStandValidHits[50];
  Double_t        MuonStandLostHits[50];
  Double_t        MuonStandPt[50];
  Double_t        MuonStandPz[50];
  Double_t        MuonStandP[50];
  Double_t        MuonStandEta[50];
  Double_t        MuonStandPhi[50];
  Double_t        MuonStandChi[50];
  Double_t        MuonStandCharge[50];
  Double_t        MuonStandQOverPError[50];
	          
  Double_t        MuonTrkValidHits[50];
  Double_t        MuonTrkLostHits[50];
  Double_t        MuonTrkPt[50];
  Double_t        MuonTrkPz[50];
  Double_t        MuonTrkP[50];
  Double_t        MuonTrkEta[50];
  Double_t        MuonTrkPhi[50];
  Double_t        MuonTrkChi[50];
  Double_t        MuonTrkCharge[50];
  Double_t        MuonTrkQOverPError[50];
  Double_t        MuonTrkOuterZ[50];
  Double_t        MuonTrkOuterR[50];

  UInt_t       MuonGenPdgId[50];
  UInt_t       MuonGenMother[50];
  Double_t     MuonGenPx[50];
  Double_t     MuonGenPy[50];
  Double_t     MuonGenPz[50];
  Double_t     MuonGenPt[50];
  Double_t     MuonGenEt[50];
  Double_t     MuonGenE[50];  

  //Photon variables
  UInt_t       PhotN;
  Double_t     PhotE[50];
  Double_t     PhotEt[50];
  Double_t     PhotPt[50];
  Double_t     PhotPx[50];
  Double_t     PhotPy[50];
  Double_t     PhotPz[50];
  Double_t     PhotEta[50];
  Double_t     PhotPhi[50];
  
  Double_t     PhotTrkIso[50];
  Double_t     PhotECalIso[50];
  Double_t     PhotHCalIso[50];
  Double_t     PhotAllIso[50];
  
  Bool_t       PhotLoosePhoton[50];
  Bool_t       PhotTightPhoton[50];

  UInt_t       PhotGenPdgId[50];
  UInt_t       PhotGenMother[50];
  Double_t     PhotGenPx[50];
  Double_t     PhotGenPy[50];
  Double_t     PhotGenPz[50];
  Double_t     PhotGenPt[50];
  Double_t     PhotGenEt[50];
  Double_t     PhotGenE[50];
  
  //MPT variables
  Double_t        MPTPhi;
  Double_t        MPTPx;
  Double_t        MPTPy;
  Double_t        MPTPz;

  // List of branches
  TBranch        *b_Run;
  TBranch        *b_Event;
  //hlt paths
  TBranch        *b_nHLT;
  TBranch        *b_HLTArray;
  TBranch        *b_HLTNames;
  TBranch        *b_HLT1JET;
  TBranch        *b_HLT2JET;
  TBranch        *b_HLT1MET;
  TBranch        *b_HLT1HT;
  TBranch        *b_HLT1HT1MHT;
  TBranch        *b_HLT1MUON;
  //gen particles
  TBranch        *b_genN;
  TBranch        *b_genid;
  TBranch        *b_genMother;
  TBranch        *b_genE;
  TBranch        *b_genPx;
  TBranch        *b_genPy;
  TBranch        *b_genPz;
  TBranch        *b_genStatus;
  //gen leptons
  TBranch        *b_genLepN;
  TBranch        *b_genLepId;
  TBranch        *b_genLepMother;
  TBranch        *b_genLepE;
  TBranch        *b_genLepPx;
  TBranch        *b_genLepPy;
  TBranch        *b_genLepPz;
  TBranch        *b_genLepStatus;
  //gen photons
  TBranch        *b_genPhotN;
  TBranch        *b_genPhotId;
  TBranch        *b_genPhotMother;
  TBranch        *b_genPhotE;
  TBranch        *b_genPhotPx;
  TBranch        *b_genPhotPy;
  TBranch        *b_genPhotPz;
  TBranch        *b_genPhotStatus;

  //MET
  TBranch        *b_nFullMET;
  TBranch        *b_nUncorrMET;
  //PF MET
  TBranch        *b_pfMET_Fullcorr_nocc;
  TBranch        *b_pfMETphi_Fullcorr_nocc;
  TBranch        *b_pfMETsumEt_Fullcorr_nocc;
  TBranch        *b_pfMETsignificance_Fullcorr_nocc;
  TBranch        *b_pfMET_Nocorr_nocc;
  TBranch        *b_pfMETpt_Nocorr_nocc;
  TBranch        *b_pfMETphi_Nocorr_nocc;
  TBranch        *b_pfMETsumEt_Nocorr_nocc;
  TBranch        *b_pfMET_JECcorr_nocc;
  TBranch        *b_pfMETpt_JECcorr_nocc;
  TBranch        *b_pfMETphi_JECcorr_nocc;
  TBranch        *b_pfMETsumEt_JECcorr_nocc;
  TBranch        *b_pfMET_Muoncorr_nocc;
  TBranch        *b_pfMETpt_Muoncorr_nocc;
  TBranch        *b_pfMETphi_Muoncorr_nocc;
  TBranch        *b_pfMETsumEt_Muoncorr_nocc;
  TBranch        *b_pfMET_Gen;
  //TC MET
  TBranch        *b_tcMET_Fullcorr_nocc;
  TBranch        *b_tcMETphi_Fullcorr_nocc;
  TBranch        *b_tcMETsumEt_Fullcorr_nocc;
  TBranch        *b_tcMETsignificance_Fullcorr_nocc;
  TBranch        *b_tcMET_Nocorr_nocc;
  TBranch        *b_tcMETpt_Nocorr_nocc;
  TBranch        *b_tcMETphi_Nocorr_nocc;
  TBranch        *b_tcMETsumEt_Nocorr_nocc;
  TBranch        *b_tcMET_JECcorr_nocc;
  TBranch        *b_tcMETpt_JECcorr_nocc;
  TBranch        *b_tcMETphi_JECcorr_nocc;
  TBranch        *b_tcMETsumEt_JECcorr_nocc;
  TBranch        *b_tcMET_Muoncorr_nocc;
  TBranch        *b_tcMETpt_Muoncorr_nocc;
  TBranch        *b_tcMETphi_Muoncorr_nocc;
  TBranch        *b_tcMETsumEt_Muoncorr_nocc;
  TBranch        *b_tcMET_Gen;
  //Calo MET
  TBranch        *b_caloMET_Fullcorr_nocc;
  TBranch        *b_caloMETphi_Fullcorr_nocc;
  TBranch        *b_caloMETsumEt_Fullcorr_nocc;
  TBranch        *b_caloMETsignificance_Fullcorr_nocc;
  TBranch        *b_caloMET_Nocorr_nocc;
  TBranch        *b_caloMETpt_Nocorr_nocc;
  TBranch        *b_caloMETphi_Nocorr_nocc;
  TBranch        *b_caloMETsumEt_Nocorr_nocc;
  TBranch        *b_caloMET_JECcorr_nocc;
  TBranch        *b_caloMETpt_JECcorr_nocc;
  TBranch        *b_caloMETphi_JECcorr_nocc;
  TBranch        *b_caloMETsumEt_JECcorr_nocc;
  TBranch        *b_caloMET_Muoncorr_nocc;
  TBranch        *b_caloMETpt_Muoncorr_nocc;
  TBranch        *b_caloMETphi_Muoncorr_nocc;
  TBranch        *b_caloMETsumEt_Muoncorr_nocc;
  TBranch        *b_caloMET_Gen;


  TBranch        *b_nVtx;
  TBranch        *b_VertexChi2;
  TBranch        *b_VertexNdof;
  TBranch        *b_VertexIsValid;
  TBranch        *b_VertexNormalizedChi2;
  TBranch        *b_VertexX;
  TBranch        *b_VertexY;
  TBranch        *b_VertexZ;
  TBranch        *b_VertexdX;
  TBranch        *b_VertexdY;
  TBranch        *b_VertexdZ;
  //Calo Jets
  TBranch        *b_CaloNJets;
  TBranch        *b_CaloHt;
  TBranch        *b_CaloMHt;
  TBranch        *b_CaloMHx;
  TBranch        *b_CaloMHy;
  TBranch        *b_CaloJetE;
  TBranch        *b_CaloJetEt;
  TBranch        *b_CaloJetPt;
  TBranch        *b_CaloJetPx;
  TBranch        *b_CaloJetPy;
  TBranch        *b_CaloJetPz;
  TBranch        *b_CaloJetEta;
  TBranch        *b_CaloJetPhi;
  TBranch        *b_CaloJetFem;
  TBranch        *b_CaloJetfHPD;
  TBranch        *b_CaloJetfRBX;
  TBranch        *b_CaloJetn90;
  TBranch        *b_CaloJet_JPTcorrFactor;
  TBranch        *b_CaloJetPartonFlavour;
  TBranch        *b_CaloJetPreselection;
  TBranch        *b_CaloJetTrackPt;
  TBranch        *b_CaloJetTrackPhi;
  TBranch        *b_CaloJetTrackPhiWeighted;
  TBranch        *b_CaloJetTrackNo;
  //JPT Jets
  TBranch        *b_JPTNJets;
  TBranch        *b_JPTHt;
  TBranch        *b_JPTMHt;
  TBranch        *b_JPTMHx;
  TBranch        *b_JPTMHy;
  TBranch        *b_JPTJetE;
  TBranch        *b_JPTJetEt;
  TBranch        *b_JPTJetPt;
  TBranch        *b_JPTJetPx;
  TBranch        *b_JPTJetPy;
  TBranch        *b_JPTJetPz;
  TBranch        *b_JPTJetEta;
  TBranch        *b_JPTJetPhi;
  TBranch        *b_JPTJetFem;
  TBranch        *b_JPTJetfHPD;
  TBranch        *b_JPTJetfRBX;
  TBranch        *b_JPTJetn90;
  TBranch        *b_JPTJetPartonFlavour;
  TBranch        *b_JPTJetPreselection;
  TBranch        *b_JPTJetTrackPt;
  TBranch        *b_JPTJetTrackPhi;
  TBranch        *b_JPTJetTrackPhiWeighted;
  TBranch        *b_JPTJetTrackNo;
 

  TBranch        *b_JetPartonId;
  TBranch        *b_JetPartonMother;
  TBranch        *b_JetPartonPx;
  TBranch        *b_JetPartonPy;
  TBranch        *b_JetPartonPz;
  TBranch        *b_JetPartonEt;
  TBranch        *b_JetPartonE;
  TBranch        *b_JetPartonPhi;
  TBranch        *b_JetPartonEta;

  //Gen jets (from Calo Jets)
  TBranch        *b_GenHt;
  TBranch        *b_GenMHt;
  TBranch        *b_GenMHx;
  TBranch        *b_GenMHy;
  TBranch        *b_GenJetE;
  TBranch        *b_GenJetEt;
  TBranch        *b_GenJetPt;
  TBranch        *b_GenJetPx;
  TBranch        *b_GenJetPy;
  TBranch        *b_GenJetPz;
  TBranch        *b_GenJetEta;
  TBranch        *b_GenJetPhi;
  //PF jets
  TBranch        *b_PFNJets;
  TBranch        *b_PFHt;
  TBranch        *b_PFMHt;
  TBranch        *b_PFMHx;
  TBranch        *b_PFMHy;
  TBranch        *b_PFJetE;
  TBranch        *b_PFJetEt;
  TBranch        *b_PFJetPt;
  TBranch        *b_PFJetPx;
  TBranch        *b_PFJetPy;
  TBranch        *b_PFJetPz;
  TBranch        *b_PFJetEta;
  TBranch        *b_PFJetPhi;
  TBranch        *b_PFJetFem;
  TBranch        *b_PFJetCharge;
  TBranch        *b_PFJetPartonFlavour;
  TBranch        *b_PFJetPreselection;
  //Track jets
  TBranch        *b_TrackNJets;
  TBranch        *b_TrackHt;
  TBranch        *b_TrackMHt;
  TBranch        *b_TrackMHx;
  TBranch        *b_TrackMHy;
  TBranch        *b_TrackJetE;
  TBranch        *b_TrackJetEt;
  TBranch        *b_TrackJetPt;
  TBranch        *b_TrackJetPx;
  TBranch        *b_TrackJetPy;
  TBranch        *b_TrackJetPz;
  TBranch        *b_TrackJetEta;
  TBranch        *b_TrackJetPhi;
  TBranch        *b_TrackJetFem;
  TBranch        *b_TrackJetCharge;
  TBranch        *b_TrackJetPartonFlavour;
  TBranch        *b_TrackJetPreselection;

  //add electrons
  TBranch        *b_ElecVeto;
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
  TBranch        *b_ElecTrkIso;
  TBranch        *b_ElecECalIso;
  TBranch        *b_ElecHCalIso;
  TBranch        *b_ElecAllIso;
  TBranch        *b_ElecTrkChiNorm;
  TBranch        *b_ElecECalIsoDeposit;
  TBranch        *b_ElecHCalIsoDeposit;
  TBranch        *b_ElecIdLoose;
  TBranch        *b_ElecIdTight;
  TBranch        *b_ElecIdRobLoose;
  TBranch        *b_ElecIdRobTight;
  TBranch        *b_ElecChargeMode;
  TBranch        *b_ElecPtMode;
  TBranch        *b_ElecQOverPErrTrkMode;
  TBranch        *b_ElecCaloEnergy;
  TBranch        *b_ElecHOverE;
  TBranch        *b_ElecVx;
  TBranch        *b_ElecVy;
  TBranch        *b_ElecVz;
  TBranch        *b_ElecD0;
  TBranch        *b_ElecDz;
  TBranch        *b_ElecPtTrk;
  TBranch        *b_ElecQOverPErrTrk;
  TBranch        *b_ElecPinTrk;
  TBranch        *b_ElecPoutTrk;
  TBranch        *b_ElecLostHits;
  TBranch        *b_ElecValidHits;
  TBranch        *b_ElecNCluster;
  TBranch        *b_ElecEtaTrk;
  TBranch        *b_ElecPhiTrk;
  TBranch        *b_ElecWidthClusterEta;
  TBranch        *b_ElecWidthClusterPhi;

  TBranch        *b_ElecGenPdgId;
  TBranch        *b_ElecGenMother;
  TBranch        *b_ElecGenPx;
  TBranch        *b_ElecGenPy;
  TBranch        *b_ElecGenPz;
  TBranch        *b_ElecGenPt;
  TBranch        *b_ElecGenEt;
  TBranch        *b_ElecGenE;

  //add muons
  TBranch        *b_MuonVeto;
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
  TBranch        *b_MuonIsGlobal;
  TBranch        *b_MuonIsStandAlone;
  TBranch        *b_MuonIsGlobalTight;
  TBranch        *b_MuonIsTMLastStationLoose;
  TBranch        *b_MuonIsTracker;
  TBranch        *b_MuonIsTMLastStationTight;
  TBranch        *b_MuonIsTM2DCompatibilityLoose;
  TBranch        *b_MuonIsTM2DCompatibilityTight;
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

  TBranch        *b_MuonGenPdgId;
  TBranch        *b_MuonGenMother;
  TBranch        *b_MuonGenPx;
  TBranch        *b_MuonGenPy;
  TBranch        *b_MuonGenPz;
  TBranch        *b_MuonGenPt;
  TBranch        *b_MuonGenEt;
  TBranch        *b_MuonGenE;

  //add photons
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

  TBranch        *b_PhotGenPdgId;
  TBranch        *b_PhotGenMother;
  TBranch        *b_PhotGenPx;
  TBranch        *b_PhotGenPy;
  TBranch        *b_PhotGenPz;
  TBranch        *b_PhotGenPt;
  TBranch        *b_PhotGenEt;
  TBranch        *b_PhotGenE;

  //add tracks
  TBranch        *b_MPTPhi;
  TBranch        *b_MPTPx;
  TBranch        *b_MPTPy;
  TBranch        *b_MPTPz;

  firstData(TTree *tree=0, std::string outfilename="outfile.root", bool=false);
  virtual ~firstData();

  std::pair<double, double> relpt_mindr(const std::vector<TLorentzVector>& vJetCollection, const TLorentzVector& vLepton);

  bool isPrompt(long pdgid);

  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

  Double_t luminosity_, cross_section_, efficiency_;
  std::string outfilename_;
  std::string infilename_;

  Double_t cut_jet12dphi, cut_alljetet, cut_alljeteta, cut_njet, minjetet, cut_jet12dR;
  Double_t cut_jet1et, cut_jet2et, cut_jet1eta, cut_jet2eta, cut_third_jetet;
  Double_t cut_jetemfrac[2], cut_jethpdfrac[2], cut_jetrbxfrac[2], cut_jetn90[2];
  Double_t cut_elecpt, cut_muonpt,cut_eleceta, cut_muoneta, cut_eleciso, cut_muoniso;
  //Double_t cut_nelec, cut_nmuon;


  inline double deltaPhi(double phi1, double phi2) {
    double dPhi = phi1 - phi2;
    //std::cout<<"M_PI is: "<<M_PI<<" dPhi is: "<<dPhi<<std::endl;
    while (dPhi > M_PI)  dPhi -= 2*M_PI;
    while (dPhi <= -M_PI) dPhi += 2*M_PI;
    //std::cout<<"Returning value: "<<dPhi<<" for deltaPhi"<<std::endl;
    return dPhi;
  }
  
  inline double deltaR2(double eta1, double phi1, double eta2, double phi2) {
    double dEta = eta1 - eta2;
    double dPhi = deltaPhi(phi1, phi2);
    return dEta*dEta + dPhi*dPhi;
  }
  
  inline double deltaR(double eta1, double phi1, double eta2, double phi2) { 
    return deltaR2(eta1, phi1, eta2, phi2);
  }
  
  inline double deltaR(double deltar2) {
    return sqrt(deltar2);
  }
  
  inline double calcMomentum(double px, double py, double pz) {
    return sqrt(px*px + py*py* + pz*pz);
  }

  inline double calcEta(double px, double py, double pz) {
    return 0.5*log( (calcMomentum(px,py,pz) + pz)/(calcMomentum(px,py,pz) - pz) );
  }

  inline double correctHt(double Ht, double jetpt) {
    return Ht - jetpt;
  }
 
  inline double correctMHx(double MHx, double jetpx) {
    return MHx + jetpx;
  }
 
  inline double correctMHy(double MHy, double jetpy) {
    return MHy + jetpy;
  }
 
  inline double correctMHt(double MHx, double MHy, double jetpx, double jetpy) {
    MHx += jetpx;
    MHy += jetpy;
    return sqrt(MHx*MHx + MHy*MHy);
  }
 
};

#endif

#ifdef firstData_cxx
firstData::firstData(TTree *tree, std::string outfilename, bool doGenInfo)
{
  outfilename_   = outfilename;
  doGenInfo_     = doGenInfo;
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("SUSY_LM0_PATtified.root");
    if (!f) {
      f = new TFile("SUSY_LM0_PATtified.root");
      if (f) std::cout << "file "<<"SUSY_LM0_PATtified.root"<<" opened\n";
    }
    tree = (TTree*)gDirectory->Get("dijet/allData;");
    if (tree) std::cout << "tree opened\n";

  }
  Init(tree);
}

firstData::~firstData()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t firstData::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t firstData::LoadTree(Long64_t entry)
{
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

void firstData::Init(TTree *tree)
{
  // Set branch addresses and branch pointers
  if (!tree) {std::cout << "tree pointer null\n"; return; }
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Run",   &Run,   &b_Run);
  fChain->SetBranchAddress("Event", &Event, &b_Event);

  fChain->SetBranchAddress("nHLT",       &nHLT,        &b_nHLT);
  fChain->SetBranchAddress("HLTArray",    HLTArray,    &b_HLTArray);
  fChain->SetBranchAddress("HLTNames",    HLTNames,    &b_HLTNames);
  fChain->SetBranchAddress("HLT1JET",    &HLT1JET,     &b_HLT1JET);
  fChain->SetBranchAddress("HLT2JET",    &HLT2JET,     &b_HLT2JET);
  fChain->SetBranchAddress("HLT1MET",    &HLT1MET,     &b_HLT1MET);
  //fChain->SetBranchAddress("HLT1HT",     &HLT1HT,      &b_HLT1HT);
  fChain->SetBranchAddress("HLT11HT",     &HLT1HT,      &b_HLT1HT);
  fChain->SetBranchAddress("HLT1HT1MHT", &HLT1HT1MHT,  &b_HLT1HT1MHT);
  fChain->SetBranchAddress("HLT1MUON",   &HLT1MUON,    &b_HLT1MUON);

  fChain->SetBranchAddress("genN",      &genN,      &b_genN);
  fChain->SetBranchAddress("genid",      genid,     &b_genid);
  fChain->SetBranchAddress("genMother",  genMother, &b_genMother);
  //fChain->SetBranchAddress("genStatus",  genStatus, &b_genStatus);
  fChain->SetBranchAddress("genE",       genE,      &b_genE);
  fChain->SetBranchAddress("genPx",      genPx,     &b_genPx);
  fChain->SetBranchAddress("genPy",      genPy,     &b_genPy);
  fChain->SetBranchAddress("genPz",      genPz,     &b_genPz);

  fChain->SetBranchAddress("genLepN",     &genLepN,      &b_genLepN);
  fChain->SetBranchAddress("genLepId",     genLepId,     &b_genLepId);
  fChain->SetBranchAddress("genLepMother", genLepMother, &b_genLepMother);
  fChain->SetBranchAddress("genLepStatus", genLepStatus, &b_genLepStatus);
  fChain->SetBranchAddress("genLepE",      genLepE,      &b_genLepE);
  fChain->SetBranchAddress("genLepPx",     genLepPx,     &b_genLepPx);
  fChain->SetBranchAddress("genLepPy",     genLepPy,     &b_genLepPy);
  fChain->SetBranchAddress("genLepPz",     genLepPz,     &b_genLepPz);
  
  fChain->SetBranchAddress("genPhotN",     &genPhotN,      &b_genPhotN);
  fChain->SetBranchAddress("genPhotId",     genPhotId,     &b_genPhotId);
  fChain->SetBranchAddress("genPhotMother", genPhotMother, &b_genPhotMother);
  fChain->SetBranchAddress("genPhotStatus", genPhotStatus, &b_genPhotStatus);
  fChain->SetBranchAddress("genPhotE",      genPhotE,      &b_genPhotE);
  fChain->SetBranchAddress("genPhotPx",     genPhotPx,     &b_genPhotPx);
  fChain->SetBranchAddress("genPhotPy",     genPhotPy,     &b_genPhotPy);
  fChain->SetBranchAddress("genPhotPz",     genPhotPz,     &b_genPhotPz);
  
  //vertex information
  fChain->SetBranchAddress("nVtx",                &nVtx,              &b_nVtx);
  fChain->SetBranchAddress("VertexChi2",           VtxChi2,           &b_VertexChi2);
  fChain->SetBranchAddress("VertexNdof",           VtxNdof,           &b_VertexNdof);
  fChain->SetBranchAddress("VertexIsValid",        VtxIsValid,        &b_VertexIsValid);
  fChain->SetBranchAddress("VertexNormalizedChi2", VtxNormalizedChi2, &b_VertexNormalizedChi2);
  fChain->SetBranchAddress("VertexX",              VtxX,              &b_VertexX);
  fChain->SetBranchAddress("VertexY",              VtxY,              &b_VertexY);
  fChain->SetBranchAddress("VertexZ",              VtxZ,              &b_VertexZ);
  fChain->SetBranchAddress("VertexdX",             VtxdX,             &b_VertexdX);
  fChain->SetBranchAddress("VertexdY",             VtxdY,             &b_VertexdY);
  fChain->SetBranchAddress("VertexdZ",             VtxdZ,             &b_VertexdZ);


  //MET information
  fChain->SetBranchAddress("nFullMET",             &nFullMET,             &b_nFullMET);
  fChain->SetBranchAddress("nUncorrMET",           &nUncorrMET,           &b_nUncorrMET);

  //pf MET
  fChain->SetBranchAddress("pfMET_Fullcorr_nocc",              pfMET_Fullcorr_nocc,             &b_pfMET_Fullcorr_nocc);
  fChain->SetBranchAddress("pfMETphi_Fullcorr_nocc",          &pfMETphi_Fullcorr_nocc,          &b_pfMETphi_Fullcorr_nocc);
  fChain->SetBranchAddress("pfMETsumEt_Fullcorr_nocc",        &pfMETsumEt_Fullcorr_nocc,        &b_pfMET_Fullcorr_nocc);
  fChain->SetBranchAddress("pfMETsignificance_Fullcorr_nocc", &pfMETsignificance_Fullcorr_nocc, &b_pfMET_Fullcorr_nocc);
  fChain->SetBranchAddress("pfMET_Nocorr_nocc",                pfMET_Nocorr_nocc,               &b_pfMET_Nocorr_nocc);
  fChain->SetBranchAddress("pfMETpt_Nocorr_nocc",             &pfMETpt_Nocorr_nocc,             &b_pfMETpt_Nocorr_nocc);
  fChain->SetBranchAddress("pfMETphi_Nocorr_nocc",            &pfMETphi_Nocorr_nocc,            &b_pfMETphi_Nocorr_nocc);
  fChain->SetBranchAddress("pfMETsumEt_Nocorr_nocc",          &pfMETsumEt_Nocorr_nocc,          &b_pfMET_Nocorr_nocc);
  fChain->SetBranchAddress("pfMET_JECcorr_nocc",               pfMET_JECcorr_nocc,              &b_pfMET_JECcorr_nocc);
  fChain->SetBranchAddress("pfMETpt_JECcorr_nocc",            &pfMETpt_JECcorr_nocc,            &b_pfMETpt_JECcorr_nocc);
  fChain->SetBranchAddress("pfMETphi_JECcorr_nocc",           &pfMETphi_JECcorr_nocc,           &b_pfMETphi_JECcorr_nocc);
  fChain->SetBranchAddress("pfMETsumEt_JECcorr_nocc",         &pfMETsumEt_JECcorr_nocc,         &b_pfMET_JECcorr_nocc);
  fChain->SetBranchAddress("pfMET_Muoncorr_nocc",              pfMET_Muoncorr_nocc,             &b_pfMET_Muoncorr_nocc);
  fChain->SetBranchAddress("pfMETpt_Muoncorr_nocc",           &pfMETpt_Muoncorr_nocc,           &b_pfMETpt_Muoncorr_nocc);
  fChain->SetBranchAddress("pfMETphi_Muoncorr_nocc",          &pfMETphi_Muoncorr_nocc,          &b_pfMETphi_Muoncorr_nocc);
  fChain->SetBranchAddress("pfMETsumEt_Muoncorr_nocc",        &pfMETsumEt_Muoncorr_nocc,        &b_pfMET_Muoncorr_nocc);
  fChain->SetBranchAddress("pfMET_Gen",                        pfMET_Gen,                       &b_pfMET_Gen);

  //tc MET
  fChain->SetBranchAddress("tcMET_Fullcorr_nocc",              tcMET_Fullcorr_nocc,             &b_tcMET_Fullcorr_nocc);
  fChain->SetBranchAddress("tcMETphi_Fullcorr_nocc",          &tcMETphi_Fullcorr_nocc,          &b_tcMETphi_Fullcorr_nocc);
  fChain->SetBranchAddress("tcMETsumEt_Fullcorr_nocc",        &tcMETsumEt_Fullcorr_nocc,        &b_tcMET_Fullcorr_nocc);
  fChain->SetBranchAddress("tcMETsignificance_Fullcorr_nocc", &tcMETsignificance_Fullcorr_nocc, &b_tcMET_Fullcorr_nocc);
  fChain->SetBranchAddress("tcMET_Nocorr_nocc",                tcMET_Nocorr_nocc,               &b_tcMET_Nocorr_nocc);
  fChain->SetBranchAddress("tcMETpt_Nocorr_nocc",             &tcMETpt_Nocorr_nocc,             &b_tcMETpt_Nocorr_nocc);
  fChain->SetBranchAddress("tcMETphi_Nocorr_nocc",            &tcMETphi_Nocorr_nocc,            &b_tcMETphi_Nocorr_nocc);
  fChain->SetBranchAddress("tcMETsumEt_Nocorr_nocc",          &tcMETsumEt_Nocorr_nocc,          &b_tcMET_Nocorr_nocc);
  fChain->SetBranchAddress("tcMET_JECcorr_nocc",               tcMET_JECcorr_nocc,              &b_tcMET_JECcorr_nocc);
  fChain->SetBranchAddress("tcMETpt_JECcorr_nocc",            &tcMETpt_JECcorr_nocc,            &b_tcMETpt_JECcorr_nocc);
  fChain->SetBranchAddress("tcMETphi_JECcorr_nocc",           &tcMETphi_JECcorr_nocc,           &b_tcMETphi_JECcorr_nocc);
  fChain->SetBranchAddress("tcMETsumEt_JECcorr_nocc",         &tcMETsumEt_JECcorr_nocc,         &b_tcMET_JECcorr_nocc);
  fChain->SetBranchAddress("tcMET_Muoncorr_nocc",              tcMET_Muoncorr_nocc,             &b_tcMET_Muoncorr_nocc);
  fChain->SetBranchAddress("tcMETpt_Muoncorr_nocc",           &tcMETpt_Muoncorr_nocc,           &b_tcMETpt_Muoncorr_nocc);
  fChain->SetBranchAddress("tcMETphi_Muoncorr_nocc",          &tcMETphi_Muoncorr_nocc,          &b_tcMETphi_Muoncorr_nocc);
  fChain->SetBranchAddress("tcMETsumEt_Muoncorr_nocc",        &tcMETsumEt_Muoncorr_nocc,        &b_tcMET_Muoncorr_nocc);
  fChain->SetBranchAddress("tcMET_Gen",                        tcMET_Gen,                       &b_tcMET_Gen);

  //calo MET
  fChain->SetBranchAddress("caloMET_Fullcorr_nocc",              caloMET_Fullcorr_nocc,             &b_caloMET_Fullcorr_nocc);
  fChain->SetBranchAddress("caloMETphi_Fullcorr_nocc",          &caloMETphi_Fullcorr_nocc,          &b_caloMETphi_Fullcorr_nocc);
  fChain->SetBranchAddress("caloMETsumEt_Fullcorr_nocc",        &caloMETsumEt_Fullcorr_nocc,        &b_caloMET_Fullcorr_nocc);
  fChain->SetBranchAddress("caloMETsignificance_Fullcorr_nocc", &caloMETsignificance_Fullcorr_nocc, &b_caloMET_Fullcorr_nocc);
  fChain->SetBranchAddress("caloMET_Nocorr_nocc",                caloMET_Nocorr_nocc,               &b_caloMET_Nocorr_nocc);
  fChain->SetBranchAddress("caloMETpt_Nocorr_nocc",             &caloMETpt_Nocorr_nocc,             &b_caloMETpt_Nocorr_nocc);
  fChain->SetBranchAddress("caloMETphi_Nocorr_nocc",            &caloMETphi_Nocorr_nocc,            &b_caloMETphi_Nocorr_nocc);
  fChain->SetBranchAddress("caloMETsumEt_Nocorr_nocc",          &caloMETsumEt_Nocorr_nocc,          &b_caloMET_Nocorr_nocc);
  fChain->SetBranchAddress("caloMET_JECcorr_nocc",               caloMET_JECcorr_nocc,              &b_caloMET_JECcorr_nocc);
  fChain->SetBranchAddress("caloMETpt_JECcorr_nocc",            &caloMETpt_JECcorr_nocc,            &b_caloMETpt_JECcorr_nocc);
  fChain->SetBranchAddress("caloMETphi_JECcorr_nocc",           &caloMETphi_JECcorr_nocc,           &b_caloMETphi_JECcorr_nocc);
  fChain->SetBranchAddress("caloMETsumEt_JECcorr_nocc",         &caloMETsumEt_JECcorr_nocc,         &b_caloMET_JECcorr_nocc);
  fChain->SetBranchAddress("caloMET_Muoncorr_nocc",              caloMET_Muoncorr_nocc,             &b_caloMET_Muoncorr_nocc);
  fChain->SetBranchAddress("caloMETpt_Muoncorr_nocc",           &caloMETpt_Muoncorr_nocc,           &b_caloMETpt_Muoncorr_nocc);
  fChain->SetBranchAddress("caloMETphi_Muoncorr_nocc",          &caloMETphi_Muoncorr_nocc,          &b_caloMETphi_Muoncorr_nocc);
  fChain->SetBranchAddress("caloMETsumEt_Muoncorr_nocc",        &caloMETsumEt_Muoncorr_nocc,        &b_caloMET_Muoncorr_nocc);
  fChain->SetBranchAddress("caloMET_Gen",                        caloMET_Gen,                       &b_caloMET_Gen);

  //Jets
  //PF Jets
  fChain->SetBranchAddress("PFNJets",    &PFNJets,     &b_PFNJets);
  fChain->SetBranchAddress("PFHt",       &PFHt,        &b_PFHt);
  fChain->SetBranchAddress("PFMHx",      &PFMHx,       &b_PFMHx);
  fChain->SetBranchAddress("PFMHy",      &PFMHy,       &b_PFMHy);
  fChain->SetBranchAddress("PFMHt",      &PFMHt,       &b_PFMHt);
  fChain->SetBranchAddress("PFJetE",      PFJetE,      &b_PFJetE);
  fChain->SetBranchAddress("PFJetEt",     PFJetEt,     &b_PFJetEt);
  fChain->SetBranchAddress("PFJetPt",     PFJetPt,     &b_PFJetPt);
  fChain->SetBranchAddress("PFJetPx",     PFJetPx,     &b_PFJetPx);
  fChain->SetBranchAddress("PFJetPy",     PFJetPy,     &b_PFJetPy);
  fChain->SetBranchAddress("PFJetPz",     PFJetPz,     &b_PFJetPz);
  fChain->SetBranchAddress("PFJetEta",    PFJetEta,    &b_PFJetEta);
  fChain->SetBranchAddress("PFJetPhi",    PFJetPhi,    &b_PFJetPhi);
  fChain->SetBranchAddress("PFJetFem",    PFJetFem,    &b_PFJetFem);
  fChain->SetBranchAddress("PFJetCharge", PFJetCharge, &b_PFJetCharge);
  fChain->SetBranchAddress("PFJetPreselection",  &PFJetPreselection,  &b_PFJetPreselection);
  fChain->SetBranchAddress("PFJetPartonFlavour", &PFJetPartonFlavour, &b_PFJetPartonFlavour);

  //Track Jets
  fChain->SetBranchAddress("TrackNJets",    &TrackNJets,     &b_TrackNJets);
  fChain->SetBranchAddress("TrackHt",       &TrackHt,        &b_TrackHt);
  fChain->SetBranchAddress("TrackMHx",      &TrackMHx,       &b_TrackMHx);
  fChain->SetBranchAddress("TrackMHy",      &TrackMHy,       &b_TrackMHy);
  fChain->SetBranchAddress("TrackMHt",      &TrackMHt,       &b_TrackMHt);
  fChain->SetBranchAddress("TrackJetE",      TrackJetE,      &b_TrackJetE);
  fChain->SetBranchAddress("TrackJetEt",     TrackJetEt,     &b_TrackJetEt);
  fChain->SetBranchAddress("TrackJetPt",     TrackJetPt,     &b_TrackJetPt);
  fChain->SetBranchAddress("TrackJetPx",     TrackJetPx,     &b_TrackJetPx);
  fChain->SetBranchAddress("TrackJetPy",     TrackJetPy,     &b_TrackJetPy);
  fChain->SetBranchAddress("TrackJetPz",     TrackJetPz,     &b_TrackJetPz);
  fChain->SetBranchAddress("TrackJetEta",    TrackJetEta,    &b_TrackJetEta);
  fChain->SetBranchAddress("TrackJetPhi",    TrackJetPhi,    &b_TrackJetPhi);
  fChain->SetBranchAddress("TrackJetFem",    TrackJetFem,    &b_TrackJetFem);
  fChain->SetBranchAddress("TrackJetCharge", TrackJetCharge, &b_TrackJetCharge);
  fChain->SetBranchAddress("TrackJetPreselection",  &TrackJetPreselection,  &b_TrackJetPreselection);
  fChain->SetBranchAddress("TrackJetPartonFlavour", &TrackJetPartonFlavour, &b_TrackJetPartonFlavour);

  //Calo Jets
  fChain->SetBranchAddress("CaloNJets",  &CaloNJets,   &b_CaloNJets);
  fChain->SetBranchAddress("CaloHt",     &CaloHt,      &b_CaloHt);
  fChain->SetBranchAddress("CaloMHx",    &CaloMHx,     &b_CaloMHx);
  fChain->SetBranchAddress("CaloMHy",    &CaloMHy,     &b_CaloMHy);
  fChain->SetBranchAddress("CaloMHt",    &CaloMHt,     &b_CaloMHt);
  fChain->SetBranchAddress("CaloJetE",    CaloJetE,    &b_CaloJetE);
  fChain->SetBranchAddress("CaloJetEt",   CaloJetEt,   &b_CaloJetEt);
  fChain->SetBranchAddress("CaloJetPt",   CaloJetPt,   &b_CaloJetPt);
  fChain->SetBranchAddress("CaloJetPx",   CaloJetPx,   &b_CaloJetPx);
  fChain->SetBranchAddress("CaloJetPy",   CaloJetPy,   &b_CaloJetPy);
  fChain->SetBranchAddress("CaloJetPz",   CaloJetPz,   &b_CaloJetPz);
  fChain->SetBranchAddress("CaloJetEta",  CaloJetEta,  &b_CaloJetEta);
  fChain->SetBranchAddress("CaloJetPhi",  CaloJetPhi,  &b_CaloJetPhi);
  fChain->SetBranchAddress("CaloJetFem",  CaloJetFem,  &b_CaloJetFem);
  fChain->SetBranchAddress("CaloJetfHPD", CaloJetfHPD, &b_CaloJetfHPD);
  fChain->SetBranchAddress("CaloJetfRBX", CaloJetfRBX, &b_CaloJetfRBX);
  fChain->SetBranchAddress("CaloJetn90",  CaloJetn90,  &b_CaloJetn90);

  fChain->SetBranchAddress("CaloJetPreselection",    &CaloJetPreselection,     &b_CaloJetPreselection);
  fChain->SetBranchAddress("CaloJet_JPTcorrFactor",   CaloJet_JPTcorrFactor,   &b_CaloJet_JPTcorrFactor);
  fChain->SetBranchAddress("CaloJetPartonFlavour",    CaloJetPartonFlavour,    &b_CaloJetPartonFlavour);
  fChain->SetBranchAddress("CaloJetTrackPt",          CaloJetTrackPt,          &b_CaloJetTrackPt);
  fChain->SetBranchAddress("CaloJetTrackPhi",         CaloJetTrackPhi,         &b_CaloJetTrackPhi);
  fChain->SetBranchAddress("CaloJetTrackPhiWeighted", CaloJetTrackPhiWeighted, &b_CaloJetTrackPhiWeighted);
  fChain->SetBranchAddress("CaloJetTrackNo",          CaloJetTrackNo,          &b_CaloJetTrackNo);

  //JPT corrected calo Jets
  fChain->SetBranchAddress("JPTNJets",  &JPTNJets,   &b_JPTNJets);
  fChain->SetBranchAddress("JPTHt",     &JPTHt,      &b_JPTHt);
  fChain->SetBranchAddress("JPTMHx",    &JPTMHx,     &b_JPTMHx);
  fChain->SetBranchAddress("JPTMHy",    &JPTMHy,     &b_JPTMHy);
  fChain->SetBranchAddress("JPTMHt",    &JPTMHt,     &b_JPTMHt);
  fChain->SetBranchAddress("JPTJetE",    JPTJetE,    &b_JPTJetE);
  fChain->SetBranchAddress("JPTJetEt",   JPTJetEt,   &b_JPTJetEt);
  fChain->SetBranchAddress("JPTJetPt",   JPTJetPt,   &b_JPTJetPt);
  fChain->SetBranchAddress("JPTJetPx",   JPTJetPx,   &b_JPTJetPx);
  fChain->SetBranchAddress("JPTJetPy",   JPTJetPy,   &b_JPTJetPy);
  fChain->SetBranchAddress("JPTJetPz",   JPTJetPz,   &b_JPTJetPz);
  fChain->SetBranchAddress("JPTJetEta",  JPTJetEta,  &b_JPTJetEta);
  fChain->SetBranchAddress("JPTJetPhi",  JPTJetPhi,  &b_JPTJetPhi);
  fChain->SetBranchAddress("JPTJetFem",  JPTJetFem,  &b_JPTJetFem);
  fChain->SetBranchAddress("JPTJetfHPD", JPTJetfHPD, &b_JPTJetfHPD);
  fChain->SetBranchAddress("JPTJetfRBX", JPTJetfRBX, &b_JPTJetfRBX);
  fChain->SetBranchAddress("JPTJetn90",  JPTJetn90,  &b_JPTJetn90);

  fChain->SetBranchAddress("JPTJetPreselection",    &JPTJetPreselection,    &b_JPTJetPreselection);
  fChain->SetBranchAddress("JPTJetPartonFlavour",    JPTJetPartonFlavour,    &b_JPTJetPartonFlavour);
  fChain->SetBranchAddress("JPTJetTrackPt",          JPTJetTrackPt,          &b_JPTJetTrackPt);
  fChain->SetBranchAddress("JPTJetTrackPhi",         JPTJetTrackPhi,         &b_JPTJetTrackPhi);
  fChain->SetBranchAddress("JPTJetTrackPhiWeighted", JPTJetTrackPhiWeighted, &b_JPTJetTrackPhiWeighted);
  fChain->SetBranchAddress("JPTJetTrackNo",          JPTJetTrackNo,          &b_JPTJetTrackNo);

  //Gen level jets
  fChain->SetBranchAddress("GenHt",    &GenHt,     &b_GenHt);
  fChain->SetBranchAddress("GenMHt",   &GenMHt,    &b_GenMHt);
  fChain->SetBranchAddress("GenMHx",   &GenMHx,    &b_GenMHx);
  fChain->SetBranchAddress("GenMHy",   &GenMHy,    &b_GenMHy);
  fChain->SetBranchAddress("GenJetE",   GenJetE,   &b_GenJetE);
  fChain->SetBranchAddress("GenJetEt",  GenJetEt,  &b_GenJetEt);
  fChain->SetBranchAddress("GenJetPt",  GenJetPt,  &b_GenJetPt);
  fChain->SetBranchAddress("GenJetPx",  GenJetPx,  &b_GenJetPx);
  fChain->SetBranchAddress("GenJetPy",  GenJetPy,  &b_GenJetPy);
  fChain->SetBranchAddress("GenJetPz",  GenJetPz,  &b_GenJetPz);
  fChain->SetBranchAddress("GenJetEta", GenJetEta, &b_GenJetEta);
  fChain->SetBranchAddress("GenJetPhi", GenJetPhi, &b_GenJetPhi);

  fChain->SetBranchAddress("JetPartonId",         JetPartonId,         &b_JetPartonId);
  fChain->SetBranchAddress("JetPartonMother",     JetPartonMother,     &b_JetPartonMother);
  fChain->SetBranchAddress("JetPartonPx",         JetPartonPx,         &b_JetPartonPx);
  fChain->SetBranchAddress("JetPartonPy",         JetPartonPy,         &b_JetPartonPy);
  fChain->SetBranchAddress("JetPartonPz",         JetPartonPz,         &b_JetPartonPz);
  fChain->SetBranchAddress("JetPartonEt",         JetPartonEt,         &b_JetPartonEt);
  fChain->SetBranchAddress("JetPartonE",          JetPartonE,          &b_JetPartonE);
  fChain->SetBranchAddress("JetPartonPhi",        JetPartonPhi,        &b_JetPartonPhi);
  fChain->SetBranchAddress("JetPartonEta",        JetPartonEta,        &b_JetPartonEta);

  //Photons
  fChain->SetBranchAddress("PhotN",      &PhotN,       &b_PhotN);
  fChain->SetBranchAddress("PhotE",       PhotE,       &b_PhotE);
  fChain->SetBranchAddress("PhotEt",      PhotEt,      &b_PhotEt);
  fChain->SetBranchAddress("PhotPt",      PhotPt,      &b_PhotPt);
  fChain->SetBranchAddress("PhotPx",      PhotPx,      &b_PhotPx);
  fChain->SetBranchAddress("PhotPy",      PhotPy,      &b_PhotPy);
  fChain->SetBranchAddress("PhotPz",      PhotPz,      &b_PhotPz);
  fChain->SetBranchAddress("PhotEta",     PhotEta,     &b_PhotEta);
  fChain->SetBranchAddress("PhotPhi",     PhotPhi,     &b_PhotPhi);
  fChain->SetBranchAddress("PhotTrkIso",  PhotTrkIso,  &b_PhotTrkIso);
  fChain->SetBranchAddress("PhotECalIso", PhotECalIso, &b_PhotECalIso);
  fChain->SetBranchAddress("PhotHCalIso", PhotHCalIso, &b_PhotHCalIso);
  fChain->SetBranchAddress("PhotAllIso",  PhotAllIso,  &b_PhotAllIso);

  fChain->SetBranchAddress("PhotLoosePhoton",   PhotLoosePhoton,       &b_PhotLoosePhoton);
  fChain->SetBranchAddress("PhotTightPhoton",   PhotTightPhoton,       &b_PhotTightPhoton);

  fChain->SetBranchAddress("PhotGenPdgId",  PhotGenPdgId,  &b_PhotGenPdgId);
  fChain->SetBranchAddress("PhotGenMother", PhotGenMother, &b_PhotGenMother);
  fChain->SetBranchAddress("PhotGenPx",     PhotGenPx,     &b_PhotGenPx);
  fChain->SetBranchAddress("PhotGenPy",     PhotGenPy,     &b_PhotGenPy);
  fChain->SetBranchAddress("PhotGenPz",     PhotGenPz,     &b_PhotGenPz);
  fChain->SetBranchAddress("PhotGenPt",     PhotGenPt,     &b_PhotGenPt);
  fChain->SetBranchAddress("PhotGenEt",     PhotGenEt,     &b_PhotGenEt);
  fChain->SetBranchAddress("PhotGenE",      PhotGenE,      &b_PhotGenE);
 
  //add electrons
  fChain->SetBranchAddress("ElecN",  &ElecN,   &b_ElecN);
  fChain->SetBranchAddress("ElecE",   ElecE,   &b_ElecE);
  fChain->SetBranchAddress("ElecEt",  ElecEt,  &b_ElecEt);
  fChain->SetBranchAddress("ElecPt",  ElecPt,  &b_ElecPt);
  fChain->SetBranchAddress("ElecPx",  ElecPx,  &b_ElecPx);
  fChain->SetBranchAddress("ElecPy",  ElecPy,  &b_ElecPy);
  fChain->SetBranchAddress("ElecPz",  ElecPz,  &b_ElecPz);
  fChain->SetBranchAddress("ElecEta", ElecEta, &b_ElecEta);
  fChain->SetBranchAddress("ElecPhi", ElecPhi, &b_ElecPhi);

  fChain->SetBranchAddress("ElecCharge",    ElecCharge,   &b_ElecCharge);
  fChain->SetBranchAddress("ElecHOverE",    ElecHOverE,   &b_ElecHOverE);
  fChain->SetBranchAddress("ElecTrkIso",    ElecTrkIso,   &b_ElecTrkIso);
  fChain->SetBranchAddress("ElecECalIso",   ElecECalIso,  &b_ElecECalIso);
  fChain->SetBranchAddress("ElecHCalIso",   ElecHCalIso,  &b_ElecHCalIso);
  fChain->SetBranchAddress("ElecAllIso",    ElecAllIso,   &b_ElecAllIso);
  fChain->SetBranchAddress("ElecTrkChiNorm",ElecNormChi2 ,&b_ElecTrkChiNorm);

  fChain->SetBranchAddress("ElecECalIsoDeposit", ElecECalIsoDeposit,&b_ElecECalIsoDeposit);
  fChain->SetBranchAddress("ElecHCalIsoDeposit", ElecHCalIsoDeposit,&b_ElecHCalIsoDeposit);

  fChain->SetBranchAddress("ElecIdLoose",   ElecIdLoose,   &b_ElecIdLoose );
  fChain->SetBranchAddress("ElecIdTight",   ElecIdTight,   &b_ElecIdTight );
  fChain->SetBranchAddress("ElecIdRobLoose",ElecIdRobLoose,&b_ElecIdRobLoose );
  fChain->SetBranchAddress("ElecIdRobTight",ElecIdRobTight,&b_ElecIdRobTight );
  fChain->SetBranchAddress("ElecChargeMode",ElecChargeMode,&b_ElecChargeMode );
  fChain->SetBranchAddress("ElecPtMode",    ElecPtTrkMode, &b_ElecPtMode );

  fChain->SetBranchAddress("ElecVx",    ElecVx,    &b_ElecVx);
  fChain->SetBranchAddress("ElecVy",    ElecVy,    &b_ElecVy);
  fChain->SetBranchAddress("ElecVz",    ElecVz,    &b_ElecVz);
  fChain->SetBranchAddress("ElecD0",    ElecD0,    &b_ElecD0);
  fChain->SetBranchAddress("ElecDz",    ElecDz,    &b_ElecDz);
  fChain->SetBranchAddress("ElecPtTrk", ElecPtTrk, &b_ElecPtTrk);

  fChain->SetBranchAddress("ElecQOverPErrTrkMode",ElecQOverPErrTrkMode,&b_ElecQOverPErrTrkMode );
  fChain->SetBranchAddress("ElecCaloEnergy",      ElecCaloEnergy,      &b_ElecCaloEnergy);

  fChain->SetBranchAddress("ElecQOverPErrTrk", ElecQOverPErrTrk,&b_ElecQOverPErrTrk);
  fChain->SetBranchAddress("ElecPinTrk",       ElecPinTrk,      &b_ElecPinTrk);
  fChain->SetBranchAddress("ElecPoutTrk",      ElecPoutTrk,     &b_ElecPoutTrk); 
  fChain->SetBranchAddress("ElecLostHits",     ElecLostHits,    &b_ElecLostHits); 
  fChain->SetBranchAddress("ElecValidHits",    ElecValidHits,   &b_ElecValidHits); 
  fChain->SetBranchAddress("ElecNCluster",     ElecNCluster,    &b_ElecNCluster); 
  fChain->SetBranchAddress("ElecEtaTrk",       ElecEtaTrk,      &b_ElecEtaTrk); 
  fChain->SetBranchAddress("ElecPhiTrk",       ElecPhiTrk,      &b_ElecPhiTrk); 

  fChain->SetBranchAddress("ElecWidthClusterEta",ElecWidthClusterEta,&b_ElecWidthClusterEta); 
  fChain->SetBranchAddress("ElecWidthClusterPhi",ElecWidthClusterPhi,&b_ElecWidthClusterPhi); 

  fChain->SetBranchAddress("ElecGenPdgId",  ElecGenPdgId,  &b_ElecGenPdgId);
  fChain->SetBranchAddress("ElecGenMother", ElecGenMother, &b_ElecGenMother);
  fChain->SetBranchAddress("ElecGenPx",     ElecGenPx,     &b_ElecGenPx);
  fChain->SetBranchAddress("ElecGenPy",     ElecGenPy,     &b_ElecGenPy);
  fChain->SetBranchAddress("ElecGenPz",     ElecGenPz,     &b_ElecGenPz);
  fChain->SetBranchAddress("ElecGenPt",     ElecGenPt,     &b_ElecGenPt);
  fChain->SetBranchAddress("ElecGenEt",     ElecGenEt,     &b_ElecGenEt);
  fChain->SetBranchAddress("ElecGenE",      ElecGenE,      &b_ElecGenE);
  fChain->SetBranchAddress("ElecVeto",     &ElecVeto,      &b_ElecVeto);
  
  //add muons
  fChain->SetBranchAddress("MuonN",         &MuonN,          &b_MuonN);  
  fChain->SetBranchAddress("MuonE",          MuonE,          &b_MuonE);
  fChain->SetBranchAddress("MuonEt",         MuonEt,         &b_MuonEt);
  fChain->SetBranchAddress("MuonPt",         MuonPt,         &b_MuonPt);
  fChain->SetBranchAddress("MuonPx",         MuonPx,         &b_MuonPx);
  fChain->SetBranchAddress("MuonPy",         MuonPy,         &b_MuonPy);
  fChain->SetBranchAddress("MuonPz",         MuonPz,         &b_MuonPz);
  fChain->SetBranchAddress("MuonEta",        MuonEta,        &b_MuonEta);
  fChain->SetBranchAddress("MuonPhi",        MuonPhi,        &b_MuonPhi);
  fChain->SetBranchAddress("MuonCharge",     MuonCharge,     &b_MuonCharge);
  fChain->SetBranchAddress("MuonTrkIso",     MuonTrkIso,     &b_MuonTrkIso);
  fChain->SetBranchAddress("MuonECalIso",    MuonECalIso,    &b_MuonECalIso);
  fChain->SetBranchAddress("MuonHCalIso",    MuonHCalIso,    &b_MuonHCalIso);
  fChain->SetBranchAddress("MuonAllIso",     MuonAllIso,     &b_MuonAllIso);
  fChain->SetBranchAddress("MuonTrkChiNorm", MuonTrkChiNorm, &b_MuonTrkChiNorm);

  //fChain->SetBranchAddress("MuonECalIsoDeposit", MuonECalIsoDeposit,&b_MuonECalIsoDeposit);
  //fChain->SetBranchAddress("MuonHCalIsoDeposit", MuonHCalIsoDeposit,&b_MuonHCalIsoDeposit);

  fChain->SetBranchAddress("MuonIsGlobal",                MuonIsGlobal,              &b_MuonIsGlobal);
  fChain->SetBranchAddress("MuonIsStandAlone",            MuonIsStandAlone,          &b_MuonIsStandAlone);
  fChain->SetBranchAddress("MuonIsGlobalTight",           MuonIsGlobalTight,         &b_MuonIsGlobalTight);
  fChain->SetBranchAddress("MuonIsTMLastStationLoose",    MuonIsTMLastStationLoose,  &b_MuonIsTMLastStationLoose);
  fChain->SetBranchAddress("MuonIsTracker",               MuonIsTracker,             &b_MuonIsTracker);
  fChain->SetBranchAddress("MuonIsTMLastStationTight",    MuonTMLastStationTight,    &b_MuonIsTMLastStationTight);
  fChain->SetBranchAddress("MuonIsTM2DCompatibilityLoose",MuonTM2DCompatibilityLoose,&b_MuonIsTM2DCompatibilityLoose);
  fChain->SetBranchAddress("MuonIsTM2DCompatibilityTight",MuonTM2DCompatibilityTight,&b_MuonIsTM2DCompatibilityTight);

  fChain->SetBranchAddress("MuonCombChi2",MuonCombChi2,&b_MuonCombChi2);
  fChain->SetBranchAddress("MuonCombNdof",MuonCombNdof,&b_MuonCombNdof);
  fChain->SetBranchAddress("MuonCombVx",  MuonCombVx,  &b_MuonCombVx);
  fChain->SetBranchAddress("MuonCombVy",  MuonCombVy,  &b_MuonCombVy);
  fChain->SetBranchAddress("MuonCombVz",  MuonCombVz,  &b_MuonCombVz);
  fChain->SetBranchAddress("MuonCombD0",  MuonCombD0,  &b_MuonCombD0);
  fChain->SetBranchAddress("MuonCombDz",  MuonCombDz,  &b_MuonCombDz);

  fChain->SetBranchAddress("MuonStandValidHits",  MuonStandValidHits,  &b_MuonStandValidHits);
  fChain->SetBranchAddress("MuonStandLostHits",   MuonStandLostHits,   &b_MuonStandLostHits);
  fChain->SetBranchAddress("MuonStandPt",         MuonStandPt,         &b_MuonStandPt);
  fChain->SetBranchAddress("MuonStandPz",         MuonStandPz,         &b_MuonStandPz);
  fChain->SetBranchAddress("MuonStandP",          MuonStandP,          &b_MuonStandP);
  fChain->SetBranchAddress("MuonStandEta",        MuonStandEta,        &b_MuonStandEta);
  fChain->SetBranchAddress("MuonStandPhi",        MuonStandPhi,        &b_MuonStandPhi);
  fChain->SetBranchAddress("MuonStandCharge",     MuonStandCharge,     &b_MuonStandCharge);
  fChain->SetBranchAddress("MuonStandChi",        MuonStandChi,        &b_MuonStandChi);
  fChain->SetBranchAddress("MuonStandQOverPError",MuonStandQOverPError,&b_MuonStandQOverPError);

  fChain->SetBranchAddress("MuonTrkValidHits",  MuonTrkValidHits,  &b_MuonTrkValidHits);
  fChain->SetBranchAddress("MuonTrkLostHits",   MuonTrkLostHits,   &b_MuonTrkLostHits);
  fChain->SetBranchAddress("MuonTrkD0",         MuonTrkD0,         &b_MuonTrkD0);
  fChain->SetBranchAddress("MuonTrkPt",         MuonTrkPt,         &b_MuonTrkPt);
  fChain->SetBranchAddress("MuonTrkPz",         MuonTrkPz,         &b_MuonTrkPz);
  fChain->SetBranchAddress("MuonTrkP",          MuonTrkP,          &b_MuonTrkP);
  fChain->SetBranchAddress("MuonTrkEta",        MuonTrkEta,        &b_MuonTrkEta);
  fChain->SetBranchAddress("MuonTrkPhi",        MuonTrkPhi,        &b_MuonTrkPhi);
  fChain->SetBranchAddress("MuonTrkCharge",     MuonTrkCharge,     &b_MuonTrkCharge);
  fChain->SetBranchAddress("MuonTrkChi",        MuonTrkChi,        &b_MuonTrkChi);
  fChain->SetBranchAddress("MuonTrkQOverPError",MuonTrkQOverPError,&b_MuonTrkQOverPError); 
  fChain->SetBranchAddress("MuonTrkOuterZ",     MuonTrkOuterZ,     &b_MuonTrkOuterZ);
  fChain->SetBranchAddress("MuonTrkOuterR",     MuonTrkOuterR,     &b_MuonTrkOuterR);

  fChain->SetBranchAddress("MuonGenPdgId",  MuonGenPdgId,  &b_MuonGenPdgId);
  fChain->SetBranchAddress("MuonGenMother", MuonGenMother, &b_MuonGenMother);
  fChain->SetBranchAddress("MuonGenPx",     MuonGenPx,     &b_MuonGenPx);
  fChain->SetBranchAddress("MuonGenPy",     MuonGenPy,     &b_MuonGenPy);
  fChain->SetBranchAddress("MuonGenPz",     MuonGenPz,     &b_MuonGenPz);
  fChain->SetBranchAddress("MuonGenPt",     MuonGenPt,     &b_MuonGenPt);
  fChain->SetBranchAddress("MuonGenEt",     MuonGenEt,     &b_MuonGenEt);
  fChain->SetBranchAddress("MuonGenE",      MuonGenE,      &b_MuonGenE);
  fChain->SetBranchAddress("MuonVeto",     &MuonVeto,      &b_MuonVeto);

  //fChain->SetBranchAddress("AlpPtScale", &AlpPtScale, &b_AlpPtScale);
  //fChain->SetBranchAddress("AlpIdTest",  &AlpIdTest,  &b_AlpIdTest);

  fChain->SetBranchAddress("MPTPhi", &MPTPhi, &b_MPTPhi);
  fChain->SetBranchAddress("MPTPx",  &MPTPx,  &b_MPTPx);
  fChain->SetBranchAddress("MPTPy",  &MPTPy,  &b_MPTPy);
  fChain->SetBranchAddress("MPTPz",  &MPTPz,  &b_MPTPz);
  Notify();
}

Bool_t firstData::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void firstData::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

std::pair<double, double> firstData::relpt_mindr(const std::vector<TLorentzVector>& vJetCollection,
						 const TLorentzVector& vLepton) {
  double relpt = 0.;
  double mindr = 99.;

  for (unsigned int ijet = 0; ijet < vJetCollection.size(); ++ijet) {
    if ( vJetCollection[ijet].DeltaR(vLepton) < mindr ) {
      if (vLepton.P() > 0.01 && vJetCollection[ijet].P() > 0.01) 
	relpt = ( (vLepton - vJetCollection[ijet]*vJetCollection[ijet].Dot(vLepton)) * (1./(vLepton.P()*vJetCollection[ijet].P())) ).P();
      mindr = vJetCollection[ijet].DeltaR(vLepton);
    }
  } // jets
 
  std::pair<double,double> thepair(relpt, mindr);
  return thepair;
}

bool firstData::isPrompt(long pdgid) {
  pdgid++;
  //  return indexToPromptBool[ abs(pdgToIndex[pdgid]) ];
  return true;  
}

#endif // #ifdef firstData_cxx


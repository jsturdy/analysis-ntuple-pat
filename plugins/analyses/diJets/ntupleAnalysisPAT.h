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
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>
#include "ntuplePragmas.h"

class ntupleAnalysisPAT {
  public :
    TTree *fChain;//!pointer to the analyzed TTree or TChain
    Int_t  fCurrent;//!current Tree number in a TChain
    
    // Declaration of leaf types
    //Standard event information
    UInt_t  Run;
    UInt_t  Event;
    UInt_t  OrbitN;
    UInt_t  StoreN;
    UInt_t  LumiSection;
    UInt_t  BunchCrossing;
    
    //Jets
    Int_t  NJets;
    Bool_t JetPreselection;
    
    Double_t   Ht;
    LorentzP4V MHtP4;
    
    //std::vector<TLorentzVector>
    LorentzP4Vs *JetP4;
    LorentzP4Vs *JetRawP4;

    std::vector<double>  *JetCharge;
    
    //std::map<std::string, std::vector<float> >
    stringtovfloat *JetCorrFactor;
    
    //JetID info
    std::vector<bool>    *JetIDMinimal;
    std::vector<bool>    *JetIDLoose;
    std::vector<bool>    *JetIDTight;
    
    std::vector<double>  *JetEtaEtaMoment;
    std::vector<double>  *JetEtaPhiMoment;
    std::vector<double>  *JetPhiPhiMoment;

    std::vector<double>  *JetNConst;
    
    std::vector<double>  *JetfHPD;
    std::vector<double>  *JetfRBX;
    std::vector<double>  *Jetn90;
    std::vector<double>  *JetTrackPt;
    std::vector<double>  *JetTrackPhi;
    std::vector<double>  *JetTrackPhiWeighted;
    std::vector<int>     *JetTrackNo;
    
    std::vector<double>  *JetFem;
    std::vector<double>  *JetFhad;
    std::vector<double>  *JetChargedFem;
    std::vector<double>  *JetNeutralFem;
    std::vector<double>  *JetChargedFhad;
    std::vector<double>  *JetNeutralFhad;
    std::vector<double>  *JetChargedFmu;
    std::vector<double>  *JetChargedFele;
    std::vector<double>  *JetChargedFpho;
    std::vector<double>  *JetHFFem;
    std::vector<double>  *JetHFFhad;

    std::vector<int>     *JetChargedMult;
    std::vector<int>     *JetElecMulti;
    std::vector<int>     *JetMuonMulti;
    std::vector<int>     *JetChargedHadMult;
    std::vector<int>     *JetNeutralHadMult;
    std::vector<int>     *JetPhotonMult;
    std::vector<int>     *JetNeutralMult;
    
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
    
    LorentzP4Vs *JetGenP4;
    LorentzP4Vs *JetPartonP4;

    Double_t    GenHt;
    LorentzP4V *GenMHtP4;
    
    std::vector<int>  *JetPartonId;
    std::vector<int>  *JetPartonMother;
    std::vector<int>  *JetPartonFlavour;
    
    //MET Information
    Int_t           nFullMET;
    Int_t           nUncorrMET;
    LorentzP4V      METP4;
    LorentzP4V      GenMETP4;
    Double_t        MET_Fullcorr_nocc[3];
    Double_t        METpt_Fullcorr_nocc;
    Double_t        METphi_Fullcorr_nocc;
    Double_t        METsumEt_Fullcorr_nocc;
    Double_t        METsignificance_Fullcorr_nocc;
    Double_t        MET_Nocorr_nocc[2];//[nUncorrMET]
    Double_t        METpt_Nocorr_nocc;
    Double_t        METphi_Nocorr_nocc;
    Double_t        METsumEt_Nocorr_nocc;
    Double_t        MET_Muoncorr_nocc[2];//[nUncorrMET]
    Double_t        METpt_Muoncorr_nocc;
    Double_t        METphi_Muoncorr_nocc;
    Double_t        METsumEt_Muoncorr_nocc;
    Double_t        MET_JEScorr_nocc[2];//[nUncorrMET]
    Double_t        METpt_JEScorr_nocc;
    Double_t        METphi_JEScorr_nocc;
    Double_t        METsumEt_JEScorr_nocc;
    Double_t        GenMET[3];
    
    //Photons
    Bool_t          PhotVeto;
    Int_t           PhotN;
    LorentzP4Vs    *PhotonP4;
    LorentzP4Vs    *PhotGenP4;

    std::vector<int> *PhotGenPdgId;
    std::vector<int> *PhotGenMother;

    std::vector<double> *PhotTrkIso;
    std::vector<double> *PhotECalIso;
    std::vector<double> *PhotHCalIso;
    std::vector<double> *PhotAllIso;
    std::vector<bool>   *PhotLoosePhoton;
    std::vector<bool>   *PhotTightPhoton;
    
    //Electrons
    Bool_t          ElecVeto;
    Int_t           ElecN;
    LorentzP4Vs    *ElectronP4;
    LorentzP4Vs    *ElecGenP4;

    std::vector<int> *ElecGenPdgId;
    std::vector<int> *ElecGenMother;

    std::vector<double> *ElecCharge;
    std::vector<double> *ElecHOverE;
    std::vector<double> *ElecTrkIso;
    std::vector<double> *ElecECalIso;
    std::vector<double> *ElecHCalIso;
    std::vector<double> *ElecAllIso;
    std::vector<double> *ElecTrkChiNorm;
    
    std::vector<float>  *ElecIdLoose;
    std::vector<float>  *ElecIdTight;
    std::vector<float>  *ElecIdRobLoose;
    std::vector<float>  *ElecIdRobTight;
    std::vector<float>  *ElecIdRobHighE;
  
    std::vector<double> *ElecChargeMode;
    std::vector<double> *ElecPtMode;
    std::vector<double> *ElecVx;
    std::vector<double> *ElecVy;
    std::vector<double> *ElecVz;
    std::vector<double> *ElecD0;
    std::vector<double> *ElecD0Err;
    std::vector<double> *ElecDz;
    std::vector<double> *ElecPtTrk;
    std::vector<double> *ElecQOverPErrTrkMode;
    std::vector<double> *ElecCaloEnergy;
    std::vector<double> *ElecQOverPErrTrk;
    std::vector<double> *ElecPinTrk;
    std::vector<double> *ElecPoutTrk;
    std::vector<double> *ElecLostHits;
    std::vector<double> *ElecValidHits;
    std::vector<double> *ElecEtaTrk;
    std::vector<double> *ElecPhiTrk;
    std::vector<double> *ElecWidthClusterEta;
    std::vector<double> *ElecWidthClusterPhi;
    
    //Muons
    Bool_t          MuonVeto;
    Int_t           MuonN;
    LorentzP4Vs    *MuonP4;
    LorentzP4Vs    *MuonGenP4;
    std::vector<int> *MuonGenPdgId;
    std::vector<int> *MuonGenMother;

    std::vector<double> *MuonCharge;
    std::vector<double> *MuonTrkIso;
    std::vector<double> *MuonECalIso;
    std::vector<double> *MuonHCalIso;
    std::vector<double> *MuonAllIso;
    std::vector<double> *MuonTrkChiNorm;
    std::vector<double> *MuonECalIsoDeposit;
    std::vector<double> *MuonHCalIsoDeposit;
    
    std::vector<bool> *MuonIsGlobal;
    std::vector<bool> *MuonIsStandAlone;
    std::vector<bool> *MuonIsTracker;
    std::vector<bool> *MuonGlobalMuonPromptTight;
    std::vector<bool> *MuonAllArbitrated;
    std::vector<bool> *MuonTrackerMuonArbitrated;
    std::vector<bool> *MuonTMLastStationLoose;
    std::vector<bool> *MuonTMLastStationTight;
    std::vector<bool> *MuonTM2DCompatibilityLoose;
    std::vector<bool> *MuonTM2DCompatibilityTight;
    std::vector<bool> *MuonTMOneStationLoose;
    std::vector<bool> *MuonTMOneStationTight;
    std::vector<bool> *MuonTMLastStationOptimizedLowPtLoose;
    std::vector<bool> *MuonTMLastStationOptimizedLowPtTight;
    std::vector<bool> *MuonGMTkChiCompatibility;
    std::vector<bool> *MuonGMStaChiCompatibility;
    std::vector<bool> *MuonGMTkKinkTight;
    std::vector<bool> *MuonTMLastStationAngLoose;
    std::vector<bool> *MuonTMLastStationAngTight;
    std::vector<bool> *MuonTMLastStationOptimizedBarrelLowPtLoose;
    std::vector<bool> *MuonTMLastStationOptimizedBarrelLowPtTight;
    
    std::vector<double> *MuonCombChi2;
    std::vector<double> *MuonCombNdof;
    std::vector<double> *MuonCombVx;
    std::vector<double> *MuonCombVy;
    std::vector<double> *MuonCombVz;
    std::vector<double> *MuonCombD0;
    std::vector<double> *MuonCombD0Err;
    std::vector<double> *MuonCombDz;

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
    
    std::vector<double> *MuonTrkValidHits;
    std::vector<double> *MuonTrkLostHits;
    std::vector<double> *MuonTrkD0;
    std::vector<double> *MuonTrkD0Err;
    std::vector<double> *MuonTrkD0z;
    std::vector<double> *MuonTrkPt;
    std::vector<double> *MuonTrkPz;
    std::vector<double> *MuonTrkP;
    std::vector<double> *MuonTrkEta;
    std::vector<double> *MuonTrkPhi;
    std::vector<double> *MuonTrkCharge;
    std::vector<double> *MuonTrkChi;
    std::vector<double> *MuonTrkQOverPErr;
    std::vector<double> *MuonTrkOuterZ;
    std::vector<double> *MuonTrkOuterR;
    
    //Taus
    Bool_t          TauVeto;
    Int_t           TauN;
    LorentzP4Vs    *TauP4;

    LorentzP4Vs    *TauGenP4;
    LorentzP4Vs    *TauGenJetP4;
    std::vector<int> *TauGenPdgId;
    std::vector<int> *TauGenMother;
    std::vector<int> *TauGen;

    std::vector<double> *TauCharge;
    std::vector<double> *TauTrkIso;
    std::vector<double> *TauECalIso;
    std::vector<double> *TauHCalIso;
    std::vector<double> *TauAllIso;
    
    std::vector<float>  *TauIdElec;
    std::vector<float>  *TauIdMuon;
    std::vector<float>  *TauIdIso;
    std::vector<float>  *TauIdNCfrFull;
    std::vector<float>  *TauIdNCfrHalf;
    std::vector<float>  *TauIdNCfrQuarter;
  
    std::vector<double> *TauVx;
    std::vector<double> *TauVy;
    std::vector<double> *TauVz;
    std::vector<double> *TauD0;
    std::vector<double> *TauD0Err;
    std::vector<double> *TauDz;
    
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
    
    //Vertex information
    Int_t           nVtx;
    std::vector<double> *VertexChi2;
    std::vector<double> *VertexNdof;
    std::vector<double> *VertexNTrks;
    std::vector<double> *VertexNRawTrks;
    std::vector<double> *VertexIsValid;
    std::vector<double> *VertexNormalizedChi2;
    std::vector<double> *VertexX;
    std::vector<double> *VertexY;
    std::vector<double> *VertexZ;
    std::vector<double> *Vertexd0;
    std::vector<double> *VertexdX;
    std::vector<double> *VertexdY;
    std::vector<double> *VertexdZ;
    
    //MPT information
    Double_t        MPTPhi;
    Double_t        MPTPx;
    Double_t        MPTPy;
    Double_t        MPTPz;
    
    //Trigger information
    Int_t           nHLT;
    Bool_t          HLT1JET;
    Bool_t          HLT2JET;
    Bool_t          HLT1MET;
    Bool_t          HLT11HT;
    Bool_t          HLT1HT1MHT;
    Bool_t          HLT1MUON;
    Bool_t          HLTMINBIAS;
    
    stringtobool *L1Triggered;
    stringtoint  *L1Prescaled;
    stringtobool *HLTTriggered;
    stringtoint  *HLTPrescaled;

    //Generator information
    Uint_t            genN;
    LorentzP4Vs      *genP4;
    std::vector<int> *genId;
    std::vector<int> *genStatus;
    std::vector<int> *genMother;
    std::vector<int> *genDaughters;

    Uint_t            genLepN;
    LorentzP4Vs      *genLepP4;
    std::vector<int> *genLepId;
    std::vector<int> *genLepStatus;
    std::vector<int> *genLepMother;
    std::vector<int> *genLepDaughters;

    Uint_t            genPhotN;
    LorentzP4Vs      *genPhotP4;
    std::vector<int> *genPhotId;
    std::vector<int> *genPhotStatus;
    std::vector<int> *genPhotMother;
    std::vector<int> *genPhotDaughters;

    Double_t pthat;

    // List of branches
    TBranch  *b_Run;
    TBranch  *b_Event;
    TBranch  *b_OrbitN;
    TBranch  *b_StoreN;
    TBranch  *b_LumiSection;
    TBranch  *b_BunchCrossing;
    	     
    TBranch  *b_NJets;
    TBranch  *b_Ht;
    TBranch  *b_MHtP4;
    TBranch  *b_JetP4;
    TBranch  *b_JetRawP4;
    TBranch  *b_JetGenP4;
    TBranch  *b_JetPartonP4;

    TBranch  *b_JetEtaEtaMoment;
    TBranch  *b_JetEtaPhiMoment;
    TBranch  *b_JetPhiPhiMoment;

    TBranch  *b_JetCorrFactor;
	     
    TBranch  *b_JetFem;
    TBranch  *b_JetFhad;
    TBranch  *b_JetCharge;
    TBranch  *b_JetNConst;
    TBranch  *b_JetPreselection;
    TBranch  *b_JetIDMinimal;
    TBranch  *b_JetIDLoose;
    TBranch  *b_JetIDTight;
    TBranch  *b_JetfHPD;
    TBranch  *b_JetfRBX;
    TBranch  *b_Jetn90;
    TBranch  *b_JetChargedFem;
    TBranch  *b_JetNeutralFem;
    TBranch  *b_JetChargedFhad;
    TBranch  *b_JetNeutralFhad;
    TBranch  *b_JetChargedMult;
    TBranch  *b_JetElecMulti;
    TBranch  *b_JetMuonMulti;
	     
    TBranch  *b_JetChargedFmu;
    TBranch  *b_JetChargedFele;
    TBranch  *b_JetChargedFpho;
    TBranch  *b_JetHFFem;
    TBranch  *b_JetHFFhad;
    TBranch  *b_JetChargedHadMult;
    TBranch  *b_JetNeutralHadMult;
    TBranch  *b_JetPhotonMult;
    TBranch  *b_JetNeutralMult;
    	     
    TBranch  *b_JetTrackPt;
    TBranch  *b_JetTrackPhi;
    TBranch  *b_JetTrackPhiWeighted;
    TBranch  *b_JetTrackNo;
    	     
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
    	     
    TBranch  *b_GenHt;
    TBranch  *b_GenMHtP4;
    TBranch  *b_JetPartonId;
    TBranch  *b_JetPartonMother;
    TBranch  *b_JetPartonFlavour;
    	     
    TBranch  *b_nFullMET;
    TBranch  *b_nUncorrMET;
    TBranch  *b_METP4;
    TBranch  *b_GenMETP4;
    TBranch  *b_MET_Fullcorr_nocc;
    TBranch  *b_METpt_Fullcorr_nocc;
    TBranch  *b_METphi_Fullcorr_nocc;
    TBranch  *b_METsumEt_Fullcorr_nocc;
    TBranch  *b_METsignificance_Fullcorr_nocc;
    TBranch  *b_MET_Nocorr_nocc;
    TBranch  *b_METpt_Nocorr_nocc;
    TBranch  *b_METphi_Nocorr_nocc;
    TBranch  *b_METsumEt_Nocorr_nocc;
    TBranch  *b_MET_Muoncorr_nocc;
    TBranch  *b_METpt_Muoncorr_nocc;
    TBranch  *b_METphi_Muoncorr_nocc;
    TBranch  *b_METsumEt_Muoncorr_nocc;
    TBranch  *b_MET_JEScorr_nocc;
    TBranch  *b_METpt_JEScorr_nocc;
    TBranch  *b_METphi_JEScorr_nocc;
    TBranch  *b_METsumEt_JEScorr_nocc;
    TBranch  *b_GenMET;
    	     
    TBranch  *b_PhotonP4;
    TBranch  *b_PhotN;
    TBranch  *b_PhotVeto;
    TBranch  *b_PhotTrkIso;
    TBranch  *b_PhotECalIso;
    TBranch  *b_PhotHCalIso;
    TBranch  *b_PhotAllIso;
    TBranch  *b_PhotLoosePhoton;
    TBranch  *b_PhotTightPhoton;
    	     
    TBranch  *b_ElecVeto;
    TBranch  *b_ElectronP4;
    TBranch  *b_ElecN;
    TBranch  *b_ElecCharge;
    TBranch  *b_ElecHOverE;
    TBranch  *b_ElecTrkIso;
    TBranch  *b_ElecECalIso;
    TBranch  *b_ElecHCalIso;
    TBranch  *b_ElecAllIso;
    TBranch  *b_ElecTrkChiNorm;
    TBranch  *b_ElecIdLoose;
    TBranch  *b_ElecIdTight;
    TBranch  *b_ElecIdRobLoose;
    TBranch  *b_ElecIdRobTight;
    TBranch  *b_ElecIdRobHighE;
    TBranch  *b_ElecChargeMode;
    TBranch  *b_ElecPtMode;
    TBranch  *b_ElecVx;
    TBranch  *b_ElecVy;
    TBranch  *b_ElecVz;
    TBranch  *b_ElecD0;
    TBranch  *b_ElecD0Err;
    TBranch  *b_ElecDz;
    TBranch  *b_ElecPtTrk;
    TBranch  *b_ElecQOverPErrTrkMode;
    TBranch  *b_ElecCaloEnergy;
    TBranch  *b_ElecQOverPErrTrk;
    TBranch  *b_ElecPinTrk;
    TBranch  *b_ElecPoutTrk;
    TBranch  *b_ElecLostHits;
    TBranch  *b_ElecValidHits;
    TBranch  *b_ElecEtaTrk;
    TBranch  *b_ElecPhiTrk;
    TBranch  *b_ElecWidthClusterEta;
    TBranch  *b_ElecWidthClusterPhi;
    	     
    TBranch  *b_MuonVeto;
    TBranch  *b_MuonP4;
    TBranch  *b_MuonN;
    TBranch  *b_MuonCharge;
    TBranch  *b_MuonTrkIso;
    TBranch  *b_MuonECalIso;
    TBranch  *b_MuonHCalIso;
    TBranch  *b_MuonAllIso;
    TBranch  *b_MuonTrkChiNorm;
    TBranch  *b_MuonECalIsoDeposit;
    TBranch  *b_MuonHCalIsoDeposit;
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
    TBranch  *b_MuonCombChi2;
    TBranch  *b_MuonCombNdof;
    TBranch  *b_MuonCombVx;
    TBranch  *b_MuonCombVy;
    TBranch  *b_MuonCombVz;
    TBranch  *b_MuonCombD0;
    TBranch  *b_MuonCombD0Err;
    TBranch  *b_MuonCombDz;
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
    TBranch  *b_MuonTrkValidHits;
    TBranch  *b_MuonTrkLostHits;
    TBranch  *b_MuonTrkD0;
    TBranch  *b_MuonTrkD0Err;
    TBranch  *b_MuonTrkDz;
    TBranch  *b_MuonTrkPt;
    TBranch  *b_MuonTrkPz;
    TBranch  *b_MuonTrkP;
    TBranch  *b_MuonTrkEta;
    TBranch  *b_MuonTrkPhi;
    TBranch  *b_MuonTrkCharge;
    TBranch  *b_MuonTrkChi;
    TBranch  *b_MuonTrkQOverPErr;
    TBranch  *b_MuonTrkOuterZ;
    TBranch  *b_MuonTrkOuterR;
    	     
    TBranch  *b_TauVeto;
    TBranch  *b_TauP4;
    TBranch  *b_TauN;
    TBranch  *b_TauCharge;
    TBranch  *b_TauTrkIso;
    TBranch  *b_TauECalIso;
    TBranch  *b_TauHCalIso;
    TBranch  *b_TauAllIso;
    TBranch  *b_TauIdElec;
    TBranch  *b_TauIdMuon;
    TBranch  *b_TauIdIso;
    TBranch  *b_TauIdNCfrFull;
    TBranch  *b_TauIdNCfrHalf;
    TBranch  *b_TauIdNCfrQuarter;

    TBranch  *b_TauVx;
    TBranch  *b_TauVy;
    TBranch  *b_TauVz;
    TBranch  *b_TauD0;
    TBranch  *b_TauD0Err;
    TBranch  *b_TauDz;

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
    	     
    TBranch  *b_nVtx;
    TBranch  *b_VertexChi2;
    TBranch  *b_VertexNdof;
    TBranch  *b_VertexNTrks;
    TBranch  *b_VertexNRawTrks;
    TBranch  *b_VertexIsValid;
    TBranch  *b_VertexNormalizedChi2;
    TBranch  *b_VertexX;
    TBranch  *b_VertexY;
    TBranch  *b_VertexZ;
    TBranch  *b_Vertexd0;
    TBranch  *b_VertexdX;
    TBranch  *b_VertexdY;
    TBranch  *b_VertexdZ;
    	     
    TBranch  *b_MPTPhi;
    TBranch  *b_MPTPx;
    TBranch  *b_MPTPy;
    TBranch  *b_MPTPz;
    	     
    TBranch  *b_HLT1JET;
    TBranch  *b_HLT2JET;
    TBranch  *b_HLT1MET;
    TBranch  *b_HLT1HT;
    TBranch  *b_HLT1HT1MHT;
    TBranch  *b_HLT1MUON;
    TBranch  *b_HLTMINBIAS;
    	     
    TBranch  *b_L1Triggered;
    TBranch  *b_L1Prescaled;
    TBranch  *b_HLTTriggered;
    TBranch  *b_HLTPrescaled;
    
    TBranch  *b_genPhotN;
    TBranch  *b_genPhotP4;
    TBranch  *b_genPhotId;
    TBranch  *b_genPhotStatus;
    TBranch  *b_genPhotMother;
    TBranch  *b_genPhotDaughters;
    TBranch  *b_genN;
    TBranch  *b_genP4;
    TBranch  *b_genId;
    TBranch  *b_genStatus;
    TBranch  *b_genMother;
    TBranch  *b_genDaughters;
    TBranch  *b_genLepN;
    TBranch  *b_genLepP4;
    TBranch  *b_genLepId;
    TBranch  *b_genLepStatus;
    TBranch  *b_genLepMother;
    TBranch  *b_genLepDaughters;
    TBranch  *pthat;

    ntupleAnalysisPAT(TTree *tree=0, bool isData=false, std::string jetPrefix="Calo", std::string metPrefix="CaloTypeI", std::string lepPrefix="", std::string phtPrefix="");
    virtual ~ntupleAnalysisPAT();
    
    virtual Int_t    Cut(Long64_t entry);
    
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree, TString jetPrefix, TString metPrefix, TString lepPrefix, TString phtPrefix);
    virtual void     Loop(std::string outfilename="outfile.root", double lum=1., double xs=1., double eff=1., double numGen=1.);
    virtual Bool_t   Notify();
    
    virtual void     Show(Long64_t entry = -1);
    //Special functions
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
    
    Double_t       computeHT(double& minpt, double& maxeta, bool fromRAW);
    TLorentzVector computeMHT(double& minpt, double& maxeta, bool fromRAW);
    Double_t       computeDPhiStar(TLorentzVector mht, double& minpt, double& maxeta, bool fromRAW);
    

    //friend class commonFunctions;

    Double_t luminosity_, cross_section_, efficiency_, generated_events_;
    std::string outfilename_;
    std::string infilename_;
    std::string jetPrefix_;
    std::string metPrefix_;
    std::string lepPrefix_;
    std::string phtPrefix_;
    std::string analysisVer_;
    
    bool isData_;
};

#endif

#ifdef ntupleAnalysisPAT_cxx

ntupleAnalysisPAT::ntupleAnalysisPAT(TTree *tree, 
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

  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    if (!f) {
      f = new TFile("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    }
    tree = (TTree*)gDirectory->Get("analysisNtuplePAT/AllData");
    
  }
  Init(tree,jetPrefix_,metPrefix_,lepPrefix_,phtPrefix);
}

ntupleAnalysisPAT::~ntupleAnalysisPAT() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ntupleAnalysisPAT::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t ntupleAnalysisPAT::LoadTree(Long64_t entry) {
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

void ntupleAnalysisPAT::Init(TTree *tree, TString jetPrefix, TString metPrefix, TString lepPrefix, TString phtPrefix) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  //Set pointers
  JetP4    = 0;
  JetRawP4 = 0;

  JetCharge     = 0;
  JetNConst      = 0;
  JetCorrFactor = 0;
  JetIDMinimal  = 0;
  JetIDLoose    = 0;
  JetIDTight    = 0;
    
  JetEtaEtaMoment = 0;
  JetEtaPhiMoment = 0;
  JetPhiPhiMoment = 0;

  JetfHPD             = 0;
  JetfRBX             = 0;
  Jetn90              = 0;
  JetTrackPt          = 0;
  JetTrackPhi         = 0;
  JetTrackPhiWeighted = 0;
  JetTrackNo          = 0;
    
  JetFem         = 0;
  JetFhad        = 0;
  JetChargedFem  = 0;
  JetNeutralFem  = 0;
  JetChargedFhad = 0;
  JetNeutralFhad = 0;
  JetChargedFmu  = 0;
  JetChargedFele = 0;
  JetChargedFpho = 0;
  JetHFFem       = 0;
  JetHFFhad      = 0;

  JetChargedMult    = 0;
  JetElecMulti      = 0;
  JetMuonMulti      = 0;
  JetChargedHadMult = 0;
  JetNeutralHadMult = 0;
  JetPhotonMult     = 0;
  JetNeutralMult    = 0;
    
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
    
  JetGenP4    = 0;
  JetPartonP4 = 0;

  GenMHtP4 = 0;
    
  JetPartonId      = 0;
  JetPartonMother  = 0;
  JetPartonFlavour = 0;
    
  PhotonP4  = 0;
  PhotGenP4 = 0;

  PhotGenPdgId  = 0;
  PhotGenMother = 0;

  PhotTrkIso      = 0;
  PhotECalIso     = 0;
  PhotHCalIso     = 0;
  PhotAllIso      = 0;
  PhotLoosePhoton = 0;
  PhotTightPhoton = 0;
    
  ElectronP4 = 0;
  ElecGenP4  = 0;

  ElecGenPdgId  = 0;
  ElecGenMother = 0;

  ElecCharge     = 0;
  ElecHOverE     = 0;
  ElecTrkIso     = 0;
  ElecECalIso    = 0;
  ElecHCalIso    = 0;
  ElecAllIso     = 0;
  ElecTrkChiNorm = 0;
    
  ElecIdLoose    = 0;
  ElecIdTight    = 0;
  ElecIdRobLoose = 0;
  ElecIdRobTight = 0;
  ElecIdRobHighE = 0;
  
  ElecChargeMode       = 0;
  ElecPtMode           = 0;
  ElecVx               = 0;
  ElecVy               = 0;
  ElecVz               = 0;
  ElecD0               = 0;
  ElecD0Err            = 0;
  ElecDz               = 0;
  ElecPtTrk            = 0;
  ElecQOverPErrTrkMode = 0;
  ElecCaloEnergy       = 0;
  ElecQOverPErrTrk     = 0;
  ElecPinTrk           = 0;
  ElecPoutTrk          = 0;
  ElecLostHits         = 0;
  ElecValidHits        = 0;
  ElecEtaTrk           = 0;
  ElecPhiTrk           = 0;
  ElecWidthClusterEta  = 0;
  ElecWidthClusterPhi  = 0;
    
  MuonP4        = 0;
  MuonGenP4     = 0;
  MuonGenPdgId  = 0;
  MuonGenMother = 0;

  MuonCharge         = 0;
  MuonTrkIso         = 0;
  MuonECalIso        = 0;
  MuonHCalIso        = 0;
  MuonAllIso         = 0;
  MuonTrkChiNorm     = 0;
  MuonECalIsoDeposit = 0;
  MuonHCalIsoDeposit = 0;
    
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
    
  MuonCombChi2  = 0;
  MuonCombNdof  = 0;
  MuonCombVx    = 0;
  MuonCombVy    = 0;
  MuonCombVz    = 0;
  MuonCombD0    = 0;
  MuonCombD0Err = 0;
  MuonCombDz    = 0;

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
    
  MuonTrkValidHits = 0;
  MuonTrkLostHits  = 0;
  MuonTrkD0        = 0;
  MuonTrkD0Err     = 0;
  MuonTrkD0z       = 0;
  MuonTrkPt        = 0;
  MuonTrkPz        = 0;
  MuonTrkP         = 0;
  MuonTrkEta       = 0;
  MuonTrkPhi       = 0;
  MuonTrkCharge    = 0;
  MuonTrkChi       = 0;
  MuonTrkQOverPErr = 0;
  MuonTrkOuterZ    = 0;
  MuonTrkOuterR    = 0;
    
  TauP4        = 0;
  TauGen       = 0;
  TauGenP4     = 0;
  TauGenJetP4  = 0;
  TauGenPdgId  = 0;
  TauGenMother = 0;

  TauCharge  = 0;
  TauTrkIso  = 0;
  TauECalIso = 0;
  TauHCalIso = 0;
  TauAllIso  = 0;
    
  TauIdElec        = 0;
  TauIdMuon        = 0;
  TauIdIso         = 0;
  TauIdNCfrFull    = 0;
  TauIdNCfrHalf    = 0;
  TauIdNCfrQuarter = 0;
  
  TauVx    = 0;
  TauVy    = 0;
  TauVz    = 0;
  TauD0    = 0;
  TauD0Err = 0;
  TauDz    = 0;
    
  VertexChi2     = 0;
  VertexNdof     = 0;
  VertexNTrks    = 0;
  VertexNRawTrks = 0;
  VertexIsValid  = 0;
  VertexNormalizedChi2 = 0;

  VertexX  = 0;
  VertexY  = 0;
  VertexZ  = 0;
  Vertexd0 = 0;
  VertexdX = 0;
  VertexdY = 0;
  VertexdZ = 0;
    
  L1Triggered  = 0;
  L1Prescaled  = 0;
  HLTTriggered = 0;
  HLTPrescaled = 0;

  genP4        = 0;
  genId        = 0;
  genStatus    = 0;
  genMother    = 0;
  genDaughters = 0;

  genLepP4        = 0;
  genLepId        = 0;
  genLepStatus    = 0;
  genLepMother    = 0;
  genLepDaughters = 0;

  genPhotP4        = 0;
  genPhotId        = 0;
  genPhotStatus    = 0;
  genPhotMother    = 0;
  genPhotDaughters = 0;

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Run",           &Run,          &b_Run);
  fChain->SetBranchAddress("Event",         &Event,        &b_Event);
  fChain->SetBranchAddress("OrbitN",        &OrbitN,       &b_OrbitN);
  fChain->SetBranchAddress("StoreN",        &StoreN,       &b_StoreN);
  fChain->SetBranchAddress("LumiSection",   &LumiSection,  &b_LumiSection);
  fChain->SetBranchAddress("BunchCrossing", &BunchCrossing,&b_BunchCrossing);

  fChain->SetBranchAddress(jetPrefix+"Ht",    &Ht,    &b_Ht);
  fChain->SetBranchAddress(jetPrefix+"MHtP4", &MHtP4, &b_MHtP4);

  fChain->SetBranchAddress(jetPrefix+"NJets",   &NJets,   &b_NJets);
  fChain->SetBranchAddress(jetPrefix+"JetP4",   &JetP4,   &b_JetP4);
  fChain->SetBranchAddress(jetPrefix+"JetRawP4",&JetRawP4,&b_JetRawP4);

  fChain->SetBranchAddress(jetPrefix+"JetEtaEtaMoment", &JetEtaEtaMoment, &b_JetEtaEtaMoment);
  fChain->SetBranchAddress(jetPrefix+"JetEtaPhiMoment", &JetEtaPhiMoment, &b_JetEtaPhiMoment);
  fChain->SetBranchAddress(jetPrefix+"JetPhiPhiMoment", &JetPhiPhiMoment, &b_JetPhiPhiMoment);

  fChain->SetBranchAddress(jetPrefix+"JetCorrFactor",   &JetCorrFactor, &b_JetCorrFactor);
  fChain->SetBranchAddress(jetPrefix+"JetPreselection", &JetPreselection, &b_JetPreselection);

  //Jet ID (implemented only for Calo/JPT (all three) and PF jets (loose/tight)
  fChain->SetBranchAddress(jetPrefix+"JetIDMinimal", &JetIDMinimal,&b_JetIDMinimal);
  fChain->SetBranchAddress(jetPrefix+"JetIDLoose",   &JetIDLoose,  &b_JetIDLoose);
  fChain->SetBranchAddress(jetPrefix+"JetIDTight",   &JetIDTight,  &b_JetIDTight);

  fChain->SetBranchAddress(jetPrefix+"JetFem",    &JetFem,    &b_JetFem);
  fChain->SetBranchAddress(jetPrefix+"JetFhad",   &JetFhad,   &b_JetFhad);
  fChain->SetBranchAddress(jetPrefix+"JetCharge", &JetCharge, &b_JetCharge);
  fChain->SetBranchAddress(jetPrefix+"JetNConst", &JetNConst, &b_JetNConst);

  //b-Tagging information
  fChain->SetBranchAddress(jetPrefix+"JetBTag_TCHE",           &JetBTag_TCHE,          &b_JetBTag_TCHE);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_TCHP",           &JetBTag_TCHP,          &b_JetBTag_TCHP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_jetProb",        &JetBTag_jetProb,       &b_JetBTag_jetProb);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_jetBProb",       &JetBTag_jetBProb,      &b_JetBTag_jetBProb);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SSVHE",          &JetBTag_SSVHE,         &b_JetBTag_SSVHE);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SSVHP",          &JetBTag_SSVHP,         &b_JetBTag_SSVHP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_CSV",            &JetBTag_CSV,           &b_JetBTag_CSV);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_CSVMVA",         &JetBTag_CSVMVA,        &b_JetBTag_CSVMVA);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLepton",     &JetBTag_SoftLepton,    &b_JetBTag_SoftLepton);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLeptonByIP", &JetBTag_SoftLeptonByIP,&b_JetBTag_SoftLeptonByIP);
  fChain->SetBranchAddress(jetPrefix+"JetBTag_SoftLeptonByPt", &JetBTag_SoftLeptonByPt,&b_JetBTag_SoftLeptonByPt);

  //Calo/JPT Jet specific variables
  if (jetPrefix=="Calo"||jetPrefix=="JPT") {
    fChain->SetBranchAddress(jetPrefix+"JetfHPD",             &JetfHPD,            &b_JetfHPD);
    fChain->SetBranchAddress(jetPrefix+"JetfRBX",             &JetfRBX,            &b_JetfRBX);
    fChain->SetBranchAddress(jetPrefix+"Jetn90",              &Jetn90,             &b_Jetn90);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPt",          &JetTrackPt,         &b_JetTrackPt);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPhi",         &JetTrackPhi,        &b_JetTrackPhi);
    fChain->SetBranchAddress(jetPrefix+"JetTrackPhiWeighted", &JetTrackPhiWeighted,&b_JetTrackPhiWeighted);
    fChain->SetBranchAddress(jetPrefix+"JetTrackNo",          &JetTrackNo,         &b_JetTrackNo);
  }

  //JPT/PF Jet specific variables
  if (jetPrefix=="JPT"||jetPrefix=="PF") {
    fChain->SetBranchAddress(jetPrefix+"JetChargedFem",  &JetChargedFem, &b_JetChargedFem);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralFem",  &JetNeutralFem, &b_JetNeutralFem);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFhad", &JetChargedFhad,&b_JetChargedFhad);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralFhad", &JetNeutralFhad,&b_JetNeutralFhad);
    fChain->SetBranchAddress(jetPrefix+"JetChargedMult", &JetChargedMult,&b_JetChargedMult);
    fChain->SetBranchAddress(jetPrefix+"JetElecMulti",   &JetElecMulti,  &b_JetElecMulti);
    fChain->SetBranchAddress(jetPrefix+"JetMuonMulti",   &JetMuonMulti,  &b_JetMuonMulti);
  }

  //PF Jet specific variables
  if (jetPrefix=="PF") {
    fChain->SetBranchAddress(jetPrefix+"JetChargedFmu",     &JetChargedFmu,    &b_JetChargedFmu);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFele",    &JetChargedFele,   &b_JetChargedFele);
    fChain->SetBranchAddress(jetPrefix+"JetChargedFpho",    &JetChargedFpho,   &b_JetChargedFpho);
    fChain->SetBranchAddress(jetPrefix+"JetHFFem",          &JetHFFem,         &b_JetHFFem);
    fChain->SetBranchAddress(jetPrefix+"JetHFFhad",         &JetHFFhad,        &b_JetHFFhad);
    fChain->SetBranchAddress(jetPrefix+"JetChargedHadMult", &JetChargedHadMult,&b_JetChargedHadMult);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralHadMult", &JetNeutralHadMult,&b_JetNeutralHadMult);
    fChain->SetBranchAddress(jetPrefix+"JetPhotonMult",     &JetPhotonMult,    &b_JetPhotonMult);
    fChain->SetBranchAddress(jetPrefix+"JetNeutralMult",    &JetNeutralMult,   &b_JetNeutralMult);
  }

  fChain->SetBranchAddress(jetPrefix+"GenHt",    &GenHt,    &b_GenHt);
  fChain->SetBranchAddress(jetPrefix+"GenMHtP4", &GenMHtP4, &b_GenMHtP4);

  fChain->SetBranchAddress(jetPrefix+"JetGenP4",        &JetGenP4,        &b_JetGenP4);
  fChain->SetBranchAddress(jetPrefix+"JetPartonP4",     &JetPartonP4,     &b_JetPartonP4);
  fChain->SetBranchAddress(jetPrefix+"JetPartonId",     &JetPartonId,     &b_JetPartonId);
  fChain->SetBranchAddress(jetPrefix+"JetPartonMother", &JetPartonMother, &b_JetPartonMother);
  fChain->SetBranchAddress(jetPrefix+"JetPartonFlavour",&JetPartonFlavour,&b_JetPartonFlavour);

  //MET
  fChain->SetBranchAddress("nFull"+metPrefix+"MET",   &nFullMET,  &b_nFullMET);
  fChain->SetBranchAddress("nUncorr"+metPrefix+"MET", &nUncorrMET,&b_nUncorrMET);

  fChain->SetBranchAddress(metPrefix+"METP4",   &METP4,   &b_METP4);
  fChain->SetBranchAddress(metPrefix+"GenMETP4",&GenMETP4,&b_METP4);
  fChain->SetBranchAddress(metPrefix+"GenMET",   GenMET,  &b_GenMET);

  fChain->SetBranchAddress(metPrefix+"MET_Fullcorr_nocc",             MET_Fullcorr_nocc,            &b_MET_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Fullcorr_nocc",          &METpt_Fullcorr_nocc,          &b_METpt_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Fullcorr_nocc",         &METphi_Fullcorr_nocc,         &b_METphi_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Fullcorr_nocc",       &METsumEt_Fullcorr_nocc,       &b_METsumEt_Fullcorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsignificance_Fullcorr_nocc",&METsignificance_Fullcorr_nocc,&b_METsignificance_Fullcorr_nocc);

  fChain->SetBranchAddress(metPrefix+"MET_Nocorr_nocc",      MET_Nocorr_nocc,     &b_MET_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Nocorr_nocc",   &METpt_Nocorr_nocc,   &b_METpt_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Nocorr_nocc",  &METphi_Nocorr_nocc,  &b_METphi_Nocorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Nocorr_nocc",&METsumEt_Nocorr_nocc,&b_METsumEt_Nocorr_nocc);

  fChain->SetBranchAddress(metPrefix+"MET_Muoncorr_nocc",      MET_Muoncorr_nocc,     &b_MET_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_Muoncorr_nocc",   &METpt_Muoncorr_nocc,   &b_METpt_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_Muoncorr_nocc",  &METphi_Muoncorr_nocc,  &b_METphi_Muoncorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_Muoncorr_nocc",&METsumEt_Muoncorr_nocc,&b_METsumEt_Muoncorr_nocc);

  fChain->SetBranchAddress(metPrefix+"MET_JEScorr_nocc",      MET_JEScorr_nocc,     &b_MET_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METpt_JEScorr_nocc",   &METpt_JEScorr_nocc,   &b_METpt_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METphi_JEScorr_nocc",  &METphi_JEScorr_nocc,  &b_METphi_JEScorr_nocc);
  fChain->SetBranchAddress(metPrefix+"METsumEt_JEScorr_nocc",&METsumEt_JEScorr_nocc,&b_METsumEt_JEScorr_nocc);

  fChain->SetBranchAddress(phtPrefix+"PhotN",          &PhotN,          &b_PhotN);
  fChain->SetBranchAddress(phtPrefix+"PhotVeto",       &PhotVeto,       &b_PhotVeto);
  fChain->SetBranchAddress(phtPrefix+"PhotonP4",       &PhotP4,         &b_PhotP4);
  fChain->SetBranchAddress(phtPrefix+"PhotTrkIso",     &PhotTrkIso,     &b_PhotTrkIso);
  fChain->SetBranchAddress(phtPrefix+"PhotECalIso",    &PhotECalIso,    &b_PhotECalIso);
  fChain->SetBranchAddress(phtPrefix+"PhotHCalIso",    &PhotHCalIso,    &b_PhotHCalIso);
  fChain->SetBranchAddress(phtPrefix+"PhotAllIso",     &PhotAllIso,     &b_PhotAllIso);
  fChain->SetBranchAddress(phtPrefix+"PhotLoosePhoton",&PhotLoosePhoton,&b_PhotLoosePhoton);
  fChain->SetBranchAddress(phtPrefix+"PhotTightPhoton",&PhotTightPhoton,&b_PhotTightPhoton);

  fChain->SetBranchAddress(lepPrefix+"ElecVeto",  &ElecVeto,  &b_ElecVeto);
  fChain->SetBranchAddress(lepPrefix+"ElectronP4",&ElectronP4,&b_ElectronP4);
  fChain->SetBranchAddress(lepPrefix+"ElecN",     &ElecN,     &b_ElecN);

  fChain->SetBranchAddress(lepPrefix+"ElecCharge",    &ElecCharge,    &b_ElecCharge);
  fChain->SetBranchAddress(lepPrefix+"ElecHOverE",    &ElecHOverE,    &b_ElecHOverE);
  fChain->SetBranchAddress(lepPrefix+"ElecTrkIso",    &ElecTrkIso,    &b_ElecTrkIso);
  fChain->SetBranchAddress(lepPrefix+"ElecECalIso",   &ElecECalIso,   &b_ElecECalIso);
  fChain->SetBranchAddress(lepPrefix+"ElecHCalIso",   &ElecHCalIso,   &b_ElecHCalIso);
  fChain->SetBranchAddress(lepPrefix+"ElecAllIso",    &ElecAllIso,    &b_ElecAllIso);
  fChain->SetBranchAddress(lepPrefix+"ElecTrkChiNorm",&ElecTrkChiNorm,&b_ElecTrkChiNorm);

  fChain->SetBranchAddress(lepPrefix+"ElecIdLoose",   &ElecIdLoose,   &b_ElecIdLoose);
  fChain->SetBranchAddress(lepPrefix+"ElecIdTight",   &ElecIdTight,   &b_ElecIdTight);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobLoose",&ElecIdRobLoose,&b_ElecIdRobLoose);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobTight",&ElecIdRobTight,&b_ElecIdRobTight);
  fChain->SetBranchAddress(lepPrefix+"ElecIdRobHighE",&ElecIdRobHighE,&b_ElecIdRobHighE);

  fChain->SetBranchAddress(lepPrefix+"ElecChargeMode",&ElecChargeMode,&b_ElecChargeMode);
  fChain->SetBranchAddress(lepPrefix+"ElecPtMode",    &ElecPtMode,    &b_ElecPtMode);

  fChain->SetBranchAddress(lepPrefix+"ElecVx",   &ElecVx,   &b_ElecVx);
  fChain->SetBranchAddress(lepPrefix+"ElecVy",   &ElecVy,   &b_ElecVy);
  fChain->SetBranchAddress(lepPrefix+"ElecVz",   &ElecVz,   &b_ElecVz);
  fChain->SetBranchAddress(lepPrefix+"ElecD0",   &ElecD0,   &b_ElecD0);
  fChain->SetBranchAddress(lepPrefix+"ElecD0Err",&ElecD0Err,&b_ElecD0Err);
  fChain->SetBranchAddress(lepPrefix+"ElecDz",   &ElecDz,   &b_ElecDz);
  fChain->SetBranchAddress(lepPrefix+"ElecPtTrk",&ElecPtTrk,&b_ElecPtTrk);

  fChain->SetBranchAddress(lepPrefix+"ElecQOverPErrTrkMode",&ElecQOverPErrTrkMode,&b_ElecQOverPErrTrkMode);
  fChain->SetBranchAddress(lepPrefix+"ElecCaloEnergy",      &ElecCaloEnergy,      &b_ElecCaloEnergy);
  fChain->SetBranchAddress(lepPrefix+"ElecQOverPErrTrk",    &ElecQOverPErrTrk,    &b_ElecQOverPErrTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPinTrk",          &ElecPinTrk,          &b_ElecPinTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPoutTrk",         &ElecPoutTrk,         &b_ElecPoutTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecLostHits",        &ElecLostHits,        &b_ElecLostHits);
  fChain->SetBranchAddress(lepPrefix+"ElecValidHits",       &ElecValidHits,       &b_ElecValidHits);
  fChain->SetBranchAddress(lepPrefix+"ElecEtaTrk",          &ElecEtaTrk,          &b_ElecEtaTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecPhiTrk",          &ElecPhiTrk,          &b_ElecPhiTrk);
  fChain->SetBranchAddress(lepPrefix+"ElecWidthClusterEta", &ElecWidthClusterEta, &b_ElecWidthClusterEta);
  fChain->SetBranchAddress(lepPrefix+"ElecWidthClusterPhi", &ElecWidthClusterPhi, &b_ElecWidthClusterPhi);

  fChain->SetBranchAddress(lepPrefix+"MuonVeto",&MuonVeto,&b_MuonVeto);
  fChain->SetBranchAddress(lepPrefix+"MuonP4",  &MuonP4,  &b_MuonP4);
  fChain->SetBranchAddress(lepPrefix+"MuonN",   &MuonN,   &b_MuonN);

  fChain->SetBranchAddress(lepPrefix+"MuonCharge",  &MuonCharge, &b_MuonCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkIso",  &MuonTrkIso, &b_MuonTrkIso);
  fChain->SetBranchAddress(lepPrefix+"MuonECalIso", &MuonECalIso,&b_MuonECalIso);
  fChain->SetBranchAddress(lepPrefix+"MuonHCalIso", &MuonHCalIso,&b_MuonHCalIso);
  fChain->SetBranchAddress(lepPrefix+"MuonAllIso",  &MuonAllIso, &b_MuonAllIso);

  fChain->SetBranchAddress(lepPrefix+"MuonTrkChiNorm",    &MuonTrkChiNorm,    &b_MuonTrkChiNorm);
  fChain->SetBranchAddress(lepPrefix+"MuonECalIsoDeposit",&MuonECalIsoDeposit,&b_MuonECalIsoDeposit);
  fChain->SetBranchAddress(lepPrefix+"MuonHCalIsoDeposit",&MuonHCalIsoDeposit,&b_MuonHCalIsoDeposit);

  fChain->SetBranchAddress(lepPrefix+"MuonIsGlobal",               &MuonIsGlobal,              &b_MuonIsGlobal);
  fChain->SetBranchAddress(lepPrefix+"MuonIsStandAlone",           &MuonIsStandAlone,          &b_MuonIsStandAlone);
  fChain->SetBranchAddress(lepPrefix+"MuonIsTracker",              &MuonIsTracker,             &b_MuonIsTracker);
  fChain->SetBranchAddress(lepPrefix+"MuonGlobalMuonPromptTight",  &MuonGlobalMuonPromptTight, &b_MuonGlobalMuonPromptTight);
  fChain->SetBranchAddress(lepPrefix+"MuonAllArbitrated",          &MuonAllArbitrated,         &b_MuonAllArbitrated);
  fChain->SetBranchAddress(lepPrefix+"MuonTrackerMuonArbitrated",  &MuonTrackerMuonArbitrated, &b_MuonTrackerMuonArbitrated);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationLoose",     &MuonTMLastStationLoose,    &b_MuonTMLastStationLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationTight",     &MuonTMLastStationTight,    &b_MuonTMLastStationTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTM2DCompatibilityLoose", &MuonTM2DCompatibilityLoose,&b_MuonTM2DCompatibilityLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTM2DCompatibilityTight", &MuonTM2DCompatibilityTight,&b_MuonTM2DCompatibilityTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMOneStationLoose",      &MuonTMOneStationLoose,     &b_MuonTMOneStationLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMOneStationTight",      &MuonTMOneStationTight,     &b_MuonTMOneStationTight);

  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedLowPtLoose",      &MuonTMLastStationOptimizedLowPtLoose,      &b_MuonTMLastStationOptimizedLowPtLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedLowPtTight",      &MuonTMLastStationOptimizedLowPtTight,      &b_MuonTMLastStationOptimizedLowPtTight);
  fChain->SetBranchAddress(lepPrefix+"MuonGMTkChiCompatibility",                  &MuonGMTkChiCompatibility,                  &b_MuonGMTkChiCompatibility);
  fChain->SetBranchAddress(lepPrefix+"MuonGMStaChiCompatibility",                 &MuonGMStaChiCompatibility,                 &b_MuonGMStaChiCompatibility);
  fChain->SetBranchAddress(lepPrefix+"MuonGMTkKinkTight",                         &MuonGMTkKinkTight,                         &b_MuonGMTkKinkTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationAngLoose",                 &MuonTMLastStationAngLoose,                 &b_MuonTMLastStationAngLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationAngTight",                 &MuonTMLastStationAngTight,                 &b_MuonTMLastStationAngTight);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedBarrelLowPtLoose",&MuonTMLastStationOptimizedBarrelLowPtLoose,&b_MuonTMLastStationOptimizedBarrelLowPtLoose);
  fChain->SetBranchAddress(lepPrefix+"MuonTMLastStationOptimizedBarrelLowPtTight",&MuonTMLastStationOptimizedBarrelLowPtTight,&b_MuonTMLastStationOptimizedBarrelLowPtTight);

  fChain->SetBranchAddress(lepPrefix+"MuonCombChi2", &MuonCombChi2, &b_MuonCombChi2);
  fChain->SetBranchAddress(lepPrefix+"MuonCombNdof", &MuonCombNdof, &b_MuonCombNdof);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVx",   &MuonCombVx,   &b_MuonCombVx);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVy",   &MuonCombVy,   &b_MuonCombVy);
  fChain->SetBranchAddress(lepPrefix+"MuonCombVz",   &MuonCombVz,   &b_MuonCombVz);
  fChain->SetBranchAddress(lepPrefix+"MuonCombD0",   &MuonCombD0,   &b_MuonCombD0);
  fChain->SetBranchAddress(lepPrefix+"MuonCombD0Err",&MuonCombD0Err,&b_MuonCombD0Err);
  fChain->SetBranchAddress(lepPrefix+"MuonCombDz",   &MuonCombDz,   &b_MuonCombDz);

  fChain->SetBranchAddress(lepPrefix+"MuonStandValidHits",&MuonStandValidHits,&b_MuonStandValidHits);
  fChain->SetBranchAddress(lepPrefix+"MuonStandLostHits", &MuonStandLostHits, &b_MuonStandLostHits);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPt",       &MuonStandPt,       &b_MuonStandPt);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPz",       &MuonStandPz,       &b_MuonStandPz);
  fChain->SetBranchAddress(lepPrefix+"MuonStandP",        &MuonStandP,        &b_MuonStandP);
  fChain->SetBranchAddress(lepPrefix+"MuonStandEta",      &MuonStandEta,      &b_MuonStandEta);
  fChain->SetBranchAddress(lepPrefix+"MuonStandPhi",      &MuonStandPhi,      &b_MuonStandPhi);
  fChain->SetBranchAddress(lepPrefix+"MuonStandCharge",   &MuonStandCharge,   &b_MuonStandCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonStandChi",      &MuonStandChi,      &b_MuonStandChi);
  fChain->SetBranchAddress(lepPrefix+"MuonStandQOverPErr",&MuonStandQOverPErr,&b_MuonStandQOverPErr);

  fChain->SetBranchAddress(lepPrefix+"MuonTrkValidHits",&MuonTrkValidHits,&b_MuonTrkValidHits);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkLostHits", &MuonTrkLostHits, &b_MuonTrkLostHits);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkD0",       &MuonTrkD0,       &b_MuonTrkD0);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkD0Err",    &MuonTrkD0Err,    &b_MuonTrkD0Err);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkD0z",      &MuonTrkD0z,      &b_MuonTrkD0z);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPt",       &MuonTrkPt,       &b_MuonTrkPt);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPz",       &MuonTrkPz,       &b_MuonTrkPz);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkP",        &MuonTrkP,        &b_MuonTrkP);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkEta",      &MuonTrkEta,      &b_MuonTrkEta);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkPhi",      &MuonTrkPhi,      &b_MuonTrkPhi);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkCharge",   &MuonTrkCharge,   &b_MuonTrkCharge);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkChi",      &MuonTrkChi,      &b_MuonTrkChi);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkQOverPErr",&MuonTrkQOverPErr,&b_MuonTrkQOverPErr);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkOuterZ",   &MuonTrkOuterZ,   &b_MuonTrkOuterZ);
  fChain->SetBranchAddress(lepPrefix+"MuonTrkOuterR",   &MuonTrkOuterR,   &b_MuonTrkOuterR);

  fChain->SetBranchAddress(lepPrefix+"TauVeto",  &TauVeto,  &b_TauVeto);
  fChain->SetBranchAddress(lepPrefix+"TauP4",    &TauP4,    &b_TauP4);
  fChain->SetBranchAddress(lepPrefix+"TauN",     &TauN,     &b_TauN);

  fChain->SetBranchAddress(lepPrefix+"TauCharge",    &TauCharge,    &b_TauCharge);
  fChain->SetBranchAddress(lepPrefix+"TauTrkIso",    &TauTrkIso,    &b_TauTrkIso);
  fChain->SetBranchAddress(lepPrefix+"TauECalIso",   &TauECalIso,   &b_TauECalIso);
  fChain->SetBranchAddress(lepPrefix+"TauHCalIso",   &TauHCalIso,   &b_TauHCalIso);
  fChain->SetBranchAddress(lepPrefix+"TauAllIso",    &TauAllIso,    &b_TauAllIso);

  fChain->SetBranchAddress(lepPrefix+"TauIdElec",       &TauIdElec,       &b_TauIdElec);
  fChain->SetBranchAddress(lepPrefix+"TauIdMuon",       &TauIdMuon,       &b_TauIdMuon);
  fChain->SetBranchAddress(lepPrefix+"TauIdIso",        &TauIdIso,        &b_TauIdIso);
  fChain->SetBranchAddress(lepPrefix+"TauIdNCfrFull",   &TauIdNCfrFull,   &b_TauIdNCfrFull);
  fChain->SetBranchAddress(lepPrefix+"TauIdNCfrHalf",   &TauIdNCfrHalf,   &b_TauIdNCfrHalf);
  fChain->SetBranchAddress(lepPrefix+"TauIdNCfrQuarter",&TauIdNCfrQuarter,&b_TauIdNCfrQuarter);

  fChain->SetBranchAddress(lepPrefix+"TauVx",   &TauVx,   &b_TauVx);
  fChain->SetBranchAddress(lepPrefix+"TauVy",   &TauVy,   &b_TauVy);
  fChain->SetBranchAddress(lepPrefix+"TauVz",   &TauVz,   &b_TauVz);
  fChain->SetBranchAddress(lepPrefix+"TauD0",   &TauD0,   &b_TauD0);
  fChain->SetBranchAddress(lepPrefix+"TauD0Err",&TauD0Err,&b_TauD0Err);
  fChain->SetBranchAddress(lepPrefix+"TauDz",   &TauDz,   &b_TauDz);

  fChain->SetBranchAddress("beamspotX0",        &beamspotX0,        &b_beamspotX0);
  fChain->SetBranchAddress("beamspotY0",        &beamspotY0,        &b_beamspotY0);
  fChain->SetBranchAddress("beamspotZ0",        &beamspotZ0,        &b_beamspotZ0);
  fChain->SetBranchAddress("beamspotX0Err",     &beamspotX0Err,     &b_beamspotX0Err);
  fChain->SetBranchAddress("beamspotY0Err",     &beamspotY0Err,     &b_beamspotY0Err);
  fChain->SetBranchAddress("beamspotZ0Err",     &beamspotZ0Err,     &b_beamspotZ0Err);
  fChain->SetBranchAddress("beamspotWidthX",    &beamspotWidthX,    &b_beamspotWidthX);
  fChain->SetBranchAddress("beamspotWidthY",    &beamspotWidthY,    &b_beamspotWidthY);
  fChain->SetBranchAddress("beamspotWidthXErr", &beamspotWidthXErr, &b_beamspotWidthXErr);
  fChain->SetBranchAddress("beamspotWidthYErr", &beamspotWidthYErr, &b_beamspotWidthYErr);
  fChain->SetBranchAddress("beamspotdxdz",      &beamspotdxdz,      &b_beamspotdxdz);
  fChain->SetBranchAddress("beamspotdydz",      &beamspotdydz,      &b_beamspotdydz);
  fChain->SetBranchAddress("beamspotdxdzErr",   &beamspotdxdzErr,   &b_beamspotdxdzErr);
  fChain->SetBranchAddress("beamspotdydzErr",   &beamspotdydzErr,   &b_beamspotdydzErr);
  fChain->SetBranchAddress("beamspotSigmaZ0",   &beamspotSigmaZ0,   &b_beamspotSigmaZ0);
  fChain->SetBranchAddress("beamspotSigmaZ0Err",&beamspotSigmaZ0Err,&b_beamspotSigmaZ0Err);
  fChain->SetBranchAddress("beamspotEmittanceX",&beamspotEmittanceX,&b_beamspotEmittanceX);
  fChain->SetBranchAddress("beamspotEmittanceY",&beamspotEmittanceY,&b_beamspotEmittanceY);
  fChain->SetBranchAddress("beamspotBetaStar",  &beamspotBetaStar,  &b_beamspotBetaStar);

  fChain->SetBranchAddress("nVtx",                &nVtx,                 &b_nVtx);
  fChain->SetBranchAddress("VertexChi2",          &VertexChi2,           &b_VertexChi2);
  fChain->SetBranchAddress("VertexNdof",          &VertexNdof,           &b_VertexNdof);
  fChain->SetBranchAddress("VertexNTrks",         &VertexNTrks,          &b_VertexNTrks);
  fChain->SetBranchAddress("VertexNRawTrks",      &VertexNRawTrks,       &b_VertexNRawTrks);
  fChain->SetBranchAddress("VertexIsValid",       &VertexIsValid,        &b_VertexIsValid);
  fChain->SetBranchAddress("VertexNormalizedChi2",&VertexNormalizedChi2, &b_VertexNormalizedChi2);
  fChain->SetBranchAddress("VertexX",             &VertexX,              &b_VertexX);
  fChain->SetBranchAddress("VertexY",             &VertexY,              &b_VertexY);
  fChain->SetBranchAddress("VertexZ",             &VertexZ,              &b_VertexZ);
  fChain->SetBranchAddress("Vertexd0",            &Vertexd0,             &b_Vertexd0);
  fChain->SetBranchAddress("VertexdX",            &VertexdX,             &b_VertexdX);
  fChain->SetBranchAddress("VertexdY",            &VertexdY,             &b_VertexdY);
  fChain->SetBranchAddress("VertexdZ",            &VertexdZ,             &b_VertexdZ);

  fChain->SetBranchAddress("MPTPhi",&MPTPhi,&b_MPTPhi);
  fChain->SetBranchAddress("MPTPx", &MPTPx, &b_MPTPx);
  fChain->SetBranchAddress("MPTPy", &MPTPy, &b_MPTPy);
  fChain->SetBranchAddress("MPTPz", &MPTPz, &b_MPTPz);

  fChain->SetBranchAddress("HLT1JET",   &HLT1JET,   &b_HLT1JET);
  fChain->SetBranchAddress("HLT2JET",   &HLT2JET,   &b_HLT2JET);
  fChain->SetBranchAddress("HLT1MET",   &HLT1MET,   &b_HLT1MET);
  fChain->SetBranchAddress("HLT11HT",   &HLT11HT,   &b_HLT1HT);
  fChain->SetBranchAddress("HLT1HT1MHT",&HLT1HT1MHT,&b_HLT1HT1MHT);
  fChain->SetBranchAddress("HLT1MUON",  &HLT1MUON,  &b_HLT1MUON);
  fChain->SetBranchAddress("HLTMINBIAS",&HLTMINBIAS,&b_HLTMINBIAS);

  fChain->SetBranchAddress("L1Triggered", &L1Triggered, &b_L1Triggered);
  fChain->SetBranchAddress("L1Prescaled", &L1Prescaled, &b_L1Prescaled);
  fChain->SetBranchAddress("HLTTriggered",&HLTTriggered,&b_HLTTriggered);
  fChain->SetBranchAddress("HLTPrescaled",&HLTPrescaled,&b_HLTPrescaled);

  fChain->SetBranchAddress(lepPrefix+"ElecGenP4",    &ElecGenP4,    &b_ElecGenP4);
  fChain->SetBranchAddress(lepPrefix+"ElecGenPdgId", &ElecGenPdgId, &b_ElecGenPdgId);
  fChain->SetBranchAddress(lepPrefix+"ElecGenMother",&ElecGenMother,&b_ElecGenMother);
  
  fChain->SetBranchAddress(lepPrefix+"MuonGenP4",    &MuonGenP4,    &b_MuonGenP4);
  fChain->SetBranchAddress(lepPrefix+"MuonGenPdgId", &MuonGenPdgId, &b_MuonGenPdgId);
  fChain->SetBranchAddress(lepPrefix+"MuonGenMother",&MuonGenMother,&b_MuonGenMother);
  
  fChain->SetBranchAddress(lepPrefix+"TauGen",      &TauGen,      &b_TauGen);
  fChain->SetBranchAddress(lepPrefix+"TauGenP4",    &TauGenP4,    &b_TauGenP4);
  fChain->SetBranchAddress(lepPrefix+"TauGenPdgId", &TauGenPdgId, &b_TauGenPdgId);
  fChain->SetBranchAddress(lepPrefix+"TauGenMother",&TauGenMother,&b_TauGenMother);
  fChain->SetBranchAddress(lepPrefix+"TauGenJetP4", &TauGenJetP4, &b_TauGenJetP4);
  
  fChain->SetBranchAddress(photPrefix+"PhotGenP4",    &PhotGenP4,    &b_PhotGenP4);
  fChain->SetBranchAddress(photPrefix+"PhotGenPdgId", &PhotGenPdgId, &b_PhotGenPdgId);
  fChain->SetBranchAddress(photPrefix+"PhotGenMother",&PhotGenMother,&b_PhotGenMother);

  if (doMC) {
    fChain->SetBranchAddress(lepPrefix+"genN",         &genN,        &b_genN);
    fChain->SetBranchAddress(lepPrefix+"genP4",        &genP4,       &b_genP4 );
    fChain->SetBranchAddress(lepPrefix+"genId",        &genId,       &b_genId);
    fChain->SetBranchAddress(lepPrefix+"genStatus",    &genStatus,   &b_genStatus);
    fChain->SetBranchAddress(lepPrefix+"genMother",    &genMother,   &b_genMother);
    fChain->SetBranchAddress(lepPrefix+"genDaughters", &genDaughters,&b_genDaughters);
    
    fChain->SetBranchAddress(lepPrefix+"genPhotN",        &PhotN,        &b_PhotN);
    fChain->SetBranchAddress(lepPrefix+"genPhotP4",       &PhotP4,       &b_PhotP4);
    fChain->SetBranchAddress(lepPrefix+"genPhotId",       &PhotId,       &b_PhotId);
    fChain->SetBranchAddress(lepPrefix+"genPhotStatus",   &PhotStatus,   &b_PhotStatus);
    fChain->SetBranchAddress(lepPrefix+"genPhotMother",   &PhotMother,   &b_PhotMother);
    fChain->SetBranchAddress(lepPrefix+"genPhotDaughters",&PhotDaughters,&b_PhotDaughters);
    
    fChain->SetBranchAddress(lepPrefix+"genLepN",        &genLepN,        &b_genLepN);
    fChain->SetBranchAddress(lepPrefix+"genLepP4",       &genLepP4,       &b_genLepP4);
    fChain->SetBranchAddress(lepPrefix+"genLepId",       &genLepId,       &b_genLepId);
    fChain->SetBranchAddress(lepPrefix+"genLepStatus",   &genLepStatus,   &b_genLepStatus);
    fChain->SetBranchAddress(lepPrefix+"genLepMother",   &genLepMother,   &b_genLepMother);
    fChain->SetBranchAddress(lepPrefix+"genLepDaughters",&genLepDaughters,&b_genLepDaughters);
    
    fChain->SetBranchAddress(lepPrefix+"pthat",        &pthat, &b_pthat);

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
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t ntupleAnalysisPAT::Cut(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}


Bool_t ntupleAnalysisPAT::jetID(int index, bool tight) {
  //Requirements for jetID
  bool jetID = false;
  bool jetRequirement;
  bool looseJet = true;
  if (tight)
    jetRequirement = JetIDTight.at(index);
  else
    jetRequirement = JetIDLoose.at(index);

  if (jetPrefix_=="PF" || jetPrefix_=="JPT" || jetPrefix_=="Calo")
    looseJet &= JetIDLoose.at(index);

  //track
  else {
    looseJet &= JetP4.at(index).pt()         > 20.;
    looseJet &= fabs(JetP4.at(index).eta().eta()) < 2.4;
  }

  //if (jetRequirement)
  if (looseJet)
    jetID = true;
  
  return jetID;
}

Bool_t ntupleAnalysisPAT::muonID(int index, int mode) {
  //Requirements for muonID
  double relIso = (MuonTrkIso.at(index)+MuonECalIso.at(index)+MuonHCalIso.at(index))/MuonP4.at(index).pt();
  bool muonID = false;
  if (MuonGlobalMuonPromptTight.at(index))
    //if (MuonIsGlobal.at(index))
    //if (< muon_maxchi2)
    //if (>= muon_minhits)
    if (MuonP4.at(index).pt() >= muon_minpt)
      if (fabs(MuonP4.at(index).eta()) <= muon_maxeta)
	if (relIso < muon_maxreliso)
	  if (MuonTrkD0.at(index)< muon_maxd0)
	    //if (MuonCompD0.at(index)< muon_maxd0)
	    muonID = true;
  
  return muonID;
}

Bool_t ntupleAnalysisPAT::electronID(int index, bool tight ) {
  //Requirements for electronID
  double relIso = (ElecTrkIso.at(index)+ElecECalIso.at(index)+ElecHCalIso.at(index))/ElecP4.at(index).pt();
  bool electronID = false;
  bool electronRequirement;
  if (tight)
    electronRequirement = ElecIdTight.at(index);
  else
    electronRequirement = ElecIdLoose.at(index);

  if (electronRequirement)
    if (ElecP4.at(index).pt() >= electron_minpt)
      //if (fabs(ElecP4.at(index).eta()) <= electron_maxeta)
      if (relIso < electron_maxreliso)
	if (ElecD0.at(index)< electron_maxd0)
	  //if (ElecCompD0.at(index)< electron_maxd0)
	  electronID = true;
  
  return electronID;
}

//Simple identification criteria for photons
Bool_t ntupleAnalysisPAT::photonID(int index, bool tight) {

  //Requirements for photonID
  double relIso = (PhotTrkIso.at(index)+PhotECalIso.at(index)+PhotHCalIso.at(index))/PhotP4.at(index).pt();
  bool photonID = false;
  bool photonRequirement;
  if (tight)
    photonRequirement = PhotTightPhoton.at(index);
  else
    photonRequirement = PhotLoosePhoton.at(index);

  if (photonRequirement)
    if (PhotP4.at(index).pt() >= photon_minpt)
      if (fabs(PhotP4.at(index).eta()) <= photon_maxeta)
	if (relIso < photon_maxreliso)
	  //if (PhotTrkD0.at(index)< photon_maxd0)
	  //if (PhotCompD0.at(index)< photon_maxd0)
	  photonID = true;
  
  return photonID;
}

//Compute HT from the Jet Collection
//If possible, use the stored P4
Double_t ntupleAnalysisPAT::computeHT(double& minpt, double& maxeta, bool fromRAW) {
  
  LorentzP4 theJets;
  if (fromRAW) 
    theJets = JetRawP4;
  else
    theJets = JetP4;
  Double_t theHT    = 0.;
  
  LorentzP4theJet;
  LorentzP4Vs::iterator jet = theJets.begin();
  while (jet != theJets.end()) {
    if (jet.pt() > minpt)
      if (fabs(jet.eta()) < maxeta)
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theHT += theJet.Pt();
    ++jet;
  }
  return theHT;
}

TLorentzVector ntupleAnalysisPAT::computeMHT(double& minpt, double& maxeta, bool fromRAW) {

  LorentzVs theJets;
  if (fromRAW) 
    theJets = JetRawP4;
  else
    theJets = JetP4;
  TLorentzVector theMHT;
  theMHT.SetPxPyPzE(0,0,0,0);

  LorentzP4Vs::iterator jet = theJets.begin();
  while (jet != theJets.end()) {
    if (jet.pt() > minpt)
      if (fabs(jet.eta()) < maxeta) {
	
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theMHT -= theJet;
      }
  }
  return theMHT;
}

Double_t ntupleAnalysisPAT::computeDPhiStar(TLorentzVector mht, double& minpt, double& maxeta, bool fromRAW) {

  LorentzP4Vs theJets;
  if (fromRAW) 
    theJets = JetRawP4;
  else
    theJets = JetP4;

  double    dphistar = 10.;

  LorentzP4Vs::iterator jet = theJets.begin();
  while (jet != theJets.end()) {
    if (jet.pt() > minpt)
      if (fabs(jet.eta()) < maxeta) {
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	mht += jet;
	double tmpdphi = jet.DeltaPhi(mht);
	tmpdphi = (tmpdphi < 0)    ? -tmpdphi         : tmpdphi;
	tmpdphi = (tmpdphi > M_PI) ? 2*M_PI - tmpdphi : tmpdphi;
	dphistar = (fabs(dphistar) < fabs(tmpdphi)) ? dphistar : tmpdphi;
      }
  }
  return dphistar;
}


#endif // #ifdef ntupleAnalysisPAT_cxx

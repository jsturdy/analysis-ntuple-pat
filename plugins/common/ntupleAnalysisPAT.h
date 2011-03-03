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

typedef struct {
  float lumi  ;
  float xs    ;
  float eff   ;
  float numGen;
  float scale ;
}sampleInfo;

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
    
    Double_t    Ht;
    LorentzP4V *MHtP4;
    
    //std::vector<TLorentzVector>
    LorentzP4Vs *JetP4;
    LorentzP4Vs *RawJetP4;

    //JetID info
    std::vector<bool>    *JetIDMinimal;
    std::vector<bool>    *JetIDLoose;
    std::vector<bool>    *JetIDTight;
    
    std::vector<double>  *JetEtaEtaMoment;
    std::vector<double>  *JetEtaPhiMoment;
    std::vector<double>  *JetPhiPhiMoment;

    std::vector<double>  *JetCharge;
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
    
    LorentzP4Vs *GenJetP4;
    LorentzP4Vs *JetPartonP4;

    Double_t    GenHt;
    LorentzP4V *GenMHtP4;
    
    std::vector<int>  *JetPartonId;
    std::vector<int>  *JetPartonMother;
    std::vector<int>  *JetPartonFlavour;
    
    //MET Information
    LorentzP4V     *METP4;

    Int_t           nFullMET;
    Int_t           nUncorrMET;
    Double_t        MET_Fullcorr[3];
    Double_t        METpt_Fullcorr;
    Double_t        METphi_Fullcorr;
    Double_t        METsumEt_Fullcorr;
    Double_t        METsignificance_Fullcorr;
    Double_t        MET_Nocorr[2];//[nUncorrMET]
    Double_t        METpt_Nocorr;
    Double_t        METphi_Nocorr;
    Double_t        METsumEt_Nocorr;
    Double_t        MET_Muoncorr[2];//[nUncorrMET]
    Double_t        METpt_Muoncorr;
    Double_t        METphi_Muoncorr;
    Double_t        METsumEt_Muoncorr;
    Double_t        MET_JEScorr[2];//[nUncorrMET]
    Double_t        METpt_JEScorr;
    Double_t        METphi_JEScorr;
    Double_t        METsumEt_JEScorr;

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

    std::vector<int> *TauGen;
    std::vector<int> *TauGenPdgId;
    std::vector<int> *TauGenMother;

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
    stringtobool *HLTTriggered;
    stringtoint  *HLTPrescaled;

    //Generator information
    Int_t             genN;
    LorentzP4Vs      *genP4;
    std::vector<int> *genId;
    std::vector<int> *genStatus;
    std::vector<int> *genMother;
    std::vector<int> *genDaughters;

    Int_t             genLepN;
    LorentzP4Vs      *genLepP4;
    std::vector<int> *genLepId;
    std::vector<int> *genLepStatus;
    std::vector<int> *genLepMother;
    std::vector<int> *genLepDaughters;

    Int_t             genPhotN;
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
    TBranch  *b_RawJetP4;
    TBranch  *b_GenJetP4;
    TBranch  *b_JetPartonP4;

    TBranch  *b_JetEtaEtaMoment;
    TBranch  *b_JetEtaPhiMoment;
    TBranch  *b_JetPhiPhiMoment;

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
    	     
    TBranch  *b_METP4;
    TBranch  *b_nFullMET;
    TBranch  *b_nUncorrMET;
    TBranch  *b_MET_Fullcorr;
    TBranch  *b_METpt_Fullcorr;
    TBranch  *b_METphi_Fullcorr;
    TBranch  *b_METsumEt_Fullcorr;
    TBranch  *b_METsignificance_Fullcorr;
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
    	     
    TBranch  *b_PhotGenP4;
    TBranch  *b_PhotGenPdgId;
    TBranch  *b_PhotGenMother;

    TBranch  *b_PhotonP4;
    TBranch  *b_PhotN;
    TBranch  *b_PhotVeto;
    TBranch  *b_PhotTrkIso;
    TBranch  *b_PhotECalIso;
    TBranch  *b_PhotHCalIso;
    TBranch  *b_PhotAllIso;
    TBranch  *b_PhotLoosePhoton;
    TBranch  *b_PhotTightPhoton;

    TBranch  *b_ElecGenP4;
    TBranch  *b_ElecGenPdgId;
    TBranch  *b_ElecGenMother;
    	     
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
    	     
    TBranch  *b_MuonGenP4;
    TBranch  *b_MuonGenPdgId;
    TBranch  *b_MuonGenMother;

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
    	     
    TBranch  *b_TauGenP4;
    TBranch  *b_TauGenJetP4;
    TBranch  *b_TauGen;
    TBranch  *b_TauGenPdgId;
    TBranch  *b_TauGenMother;

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

    TBranch  *b_pthat;

    ntupleAnalysisPAT(TTree *tree=0, std::string* sampleList=0, std::string* triggerList=0, std::string* cutFile=0, const bool &isData=false, const std::string &jetPrefix="Calo", const std::string &metPrefix="CaloTypeI", const std::string &lepPrefix="", const std::string &phtPrefix="", const std::string &sampleKey="");
    virtual ~ntupleAnalysisPAT();
    
    virtual Int_t    Cut(Long64_t entry);
    
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    //virtual void     Loop(const std::string& outfilename="outfile.root", const double& lum=1., const double& scale=1., const double &cutJet1=100., const double &cutJet2=100., const double &cutMET=200.);
    virtual Bool_t   Notify();
    
    virtual sampleInfo ReadInEfficiencies(std::string* efficiencyFile_, std::string sampleKey_);
    virtual void       ReadInTriggers();
    virtual void       ReadInCuts();
    std::pair<int, std::string> split(const std::string& s);

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

    std::map<int,std::string> dijetTriggers;
    std::map<int,std::string> singlejetTriggers;
    std::map<int,std::string> metTriggers;
    std::map<int,std::string> muonTriggers;
    std::map<int,std::string> electronTriggers;
    std::map<int,std::string> photonTriggers;

    bool isData_;

    //DiJet specific variables
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
    
    //private :
    virtual void setCuts();
};

#endif

#ifdef ntupleAnalysisPAT_cxx

ntupleAnalysisPAT::ntupleAnalysisPAT(TTree *tree, 
				     std::string * sampleList,
				     std::string * triggerList,
				     std::string * cutFile,
				     const bool &isData, 
				     const std::string &jetPrefix, 
				     const std::string &metPrefix, 
				     const std::string &lepPrefix, 
				     const std::string &phtPrefix,
				     const std::string &sampleKey ) {
  
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  std::cout<<"Executing ntupleAnalysisPAT::ntupleAnalysisPAT()"<<std::endl;
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    if (!f) {
      f = new TFile("/tmp/sturdy/PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root");
    }
    tree = (TTree*)gDirectory->Get("analysisNtuplePAT/AllData");
    
  }
  /*
  ////Read in the cross-section/efficiency information
  sampleList_ = sampleList;
  sampleInfo sampVals = ReadInEfficiencies(sampleList_,sampleKey);

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
  //running on data/mc
  isData_      = isData;
  //set the data labels
  jetPrefix_ = jetPrefix;
  metPrefix_ = metPrefix;
  lepPrefix_ = lepPrefix;
  phtPrefix_ = phtPrefix;
  bool debug = false;
  if (debug) std::cout<<"jetPrefix = "<<jetPrefix<<" or jetPrefix_ = "<<jetPrefix_<<std::endl;
  if (debug) std::cout<<"metPrefix = "<<metPrefix<<" or metPrefix_ = "<<metPrefix_<<std::endl;
  if (debug) std::cout<<"lepPrefix = "<<lepPrefix<<" or lepPrefix_ = "<<lepPrefix_<<std::endl;
  if (debug) std::cout<<"phtPrefix = "<<phtPrefix<<" or phtPrefix_ = "<<phtPrefix_<<std::endl;

  //Initialize the tree
  Init(tree);
}

ntupleAnalysisPAT::~ntupleAnalysisPAT() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

void ntupleAnalysisPAT::setCuts() {
  //Would like to pass these in via a cut file or similar
  jet1_minpt    = 120.;//100
  jet1_maxeta   = 2.5;

  jet2_minpt    = 100.;//100
  jet2_maxeta   = 3.0;

  jetall_minpt  = 30.;
  jetall_maxeta = 5.0;
  jetall_maxpt  = 50.;

  ht_jet_minpt  = 50;
  ht_jet_maxeta = 3.0;

  mht_jet_minpt  = 30;
  mht_jet_maxeta = 5.0;

  cut_njet = 2;
  cut_met  = 250.;//325
  cut_ht   = 0.;
  cut_mht  = 250.;
  cut_meff = 0.;

  //To be fixed
  cut_jet12dphi     = -1.;
  cut_jet1metdphi   = 1.0;
  cut_jet2metdphi   = 1.0;
  cut_jetallmetdphi = 0.3;
  cut_dphistar      = -1;

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

  photon_minpt     = 15.0;
  photon_maxpt     = 15.0;
  photon_noniso    = 0.5;
  photon_maxeta    = 2.5;
  photon_minhits   = 10;
  photon_maxreliso = 0.1;
  photon_maxd0     = 0.2;
  photon_maxchi2   = 10.0;

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
  ifstream is(triggerList_->c_str());
  std::map<int,std::string> theTriggers;
  if(is.good()) {
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;
	if (s[0] == '!') {
	  //read in the rest of the line to figure out which trigger is next
	  if (s.find("dijet")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      dijetTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("singlejet")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      singlejetTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("met")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      metTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("muon")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      muonTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("electron")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
	    while (key!= theTriggers.end()) {
	      electronTriggers[key->first] = key->second;
	      ++key;
	    }
	  }
	  else if (s.find("photon")!=std::string::npos) {
	    std::map<int,std::string>::iterator key = theTriggers.begin();
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
  
  //std::map<int,std::string>::iterator key = dijetTriggers.begin();
  //while (key!= dijetTriggers.end()) {
  //  //std::cout<<"dijetTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
  //key = singlejetTriggers.begin();
  //while (key!= singlejetTriggers.end()) {
  //  //std::cout<<"singlejetTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
  //key = metTriggers.begin();
  //while (key!= metTriggers.end()) {
  //  //std::cout<<"metTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
  //key = muonTriggers.begin();
  //while (key!= muonTriggers.end()) {
  //  //std::cout<<"muonTriggers["<<key->first<<"] = "<<key->second<<std::endl;
  //  ++key;
  //}
  //key = electronTriggers.begin();
  //while (key!= electronTriggers.end()) {
  //  //std::cout<<"electronTriggers["<<key->first<<"] = "<<key->second<<std::endl;
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
  ifstream is(cutFile_->c_str());
  if(is.good()) {
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;
	
      }
  }
  return;
}

sampleInfo ntupleAnalysisPAT::ReadInEfficiencies(std::string* efficiencyFile_,std::string sampleKey)
{
  sampleInfo returnVal;
  std::string s;
  bool debug = false;
  if (!efficiencyFile_) {
    std::cout<<"ERROR no efficiency file specified, exiting"<<std::endl;
    exit(1);
  }
  bool matched = false;
  if (debug) std::cout<<"Reading in efficiency file"<<std::endl;
  ifstream is(efficiencyFile_->c_str());
  if(is.good()) {
    while( getline(is,s) )
      {
	if (debug) std::cout<<"read line: " << s<<std::endl;
	if (s[0] == '#' || s.empty()) continue;

	if (s.find(sampleKey)!=std::string::npos) {
	  matched = true;
	  //Line format is sample name - gen events - cross section - efficiency   - note
	  //                           - int/long   - double/float  - double/float - note
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

void ntupleAnalysisPAT::Init(TTree *tree) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

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

  JetCharge     = 0;
  JetNConst     = 0;

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
    
  GenJetP4    = 0;
  JetPartonP4 = 0;

  GenMHtP4 = 0;
    
  JetPartonId      = 0;
  JetPartonMother  = 0;
  JetPartonFlavour = 0;

  METP4        = 0;

  GenMETP4     = 0;
  GenMETTrueP4 = 0;
  GenMETCaloP4 = 0;
    
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

  TauGenP4     = 0;
  TauGenJetP4  = 0;

  TauGen       = 0;
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
  pthat            = 0;

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  //fChain->SetMakeClass(1);
  
  bool debug = false;

  TString jets  = jetPrefix_;
  TString met   = metPrefix_;
  TString leps  = lepPrefix_;
  TString phots = phtPrefix_;
  if (debug) std::cout<<"Jets = "<<jets<<" or jetPrefix_ = "<<jetPrefix_<<std::endl;
  if (debug) std::cout<<"Met = "<<met<<" or metPrefix_ = "<<metPrefix_<<std::endl;
  if (debug) std::cout<<"Leps = "<<leps<<" or lepPrefix_ = "<<lepPrefix_<<std::endl;
  if (debug) std::cout<<"Phots = "<<phots<<" or phtPrefix_ = "<<phtPrefix_<<std::endl;
  
  fChain->SetBranchAddress("Run",           &Run,          &b_Run);
  fChain->SetBranchAddress("Event",         &Event,        &b_Event);
  fChain->SetBranchAddress("OrbitN",        &OrbitN,       &b_OrbitN);
  fChain->SetBranchAddress("StoreN",        &StoreN,       &b_StoreN);
  fChain->SetBranchAddress("LumiSection",   &LumiSection,  &b_LumiSection);
  fChain->SetBranchAddress("BunchCrossing", &BunchCrossing,&b_BunchCrossing);

  fChain->SetBranchAddress(jets+"Ht",    &Ht,    &b_Ht);
  fChain->SetBranchAddress(jets+"MHtP4", &MHtP4, &b_MHtP4);

  fChain->SetBranchAddress(jets+"NJets",   &NJets,   &b_NJets);
  fChain->SetBranchAddress(jets+"JetP4",   &JetP4,   &b_JetP4);
  fChain->SetBranchAddress(jets+"RawJetP4",&RawJetP4,&b_RawJetP4);

  fChain->SetBranchAddress(jets+"JetEtaEtaMoment", &JetEtaEtaMoment, &b_JetEtaEtaMoment);
  fChain->SetBranchAddress(jets+"JetEtaPhiMoment", &JetEtaPhiMoment, &b_JetEtaPhiMoment);
  fChain->SetBranchAddress(jets+"JetPhiPhiMoment", &JetPhiPhiMoment, &b_JetPhiPhiMoment);

  fChain->SetBranchAddress(jets+"JetPreselection", &JetPreselection, &b_JetPreselection);

  //Jet ID (implemented only for Calo/JPT (all three) and PF jets (loose/tight)
  fChain->SetBranchAddress(jets+"JetIDMinimal", &JetIDMinimal,&b_JetIDMinimal);
  fChain->SetBranchAddress(jets+"JetIDLoose",   &JetIDLoose,  &b_JetIDLoose);
  fChain->SetBranchAddress(jets+"JetIDTight",   &JetIDTight,  &b_JetIDTight);

  fChain->SetBranchAddress(jets+"JetFem",    &JetFem,    &b_JetFem);
  fChain->SetBranchAddress(jets+"JetFhad",   &JetFhad,   &b_JetFhad);
  fChain->SetBranchAddress(jets+"JetCharge", &JetCharge, &b_JetCharge);
  fChain->SetBranchAddress(jets+"JetNConst", &JetNConst, &b_JetNConst);

  //b-Tagging information
  fChain->SetBranchAddress(jets+"JetBTag_TCHE",           &JetBTag_TCHE,          &b_JetBTag_TCHE);
  fChain->SetBranchAddress(jets+"JetBTag_TCHP",           &JetBTag_TCHP,          &b_JetBTag_TCHP);
  fChain->SetBranchAddress(jets+"JetBTag_jetProb",        &JetBTag_jetProb,       &b_JetBTag_jetProb);
  fChain->SetBranchAddress(jets+"JetBTag_jetBProb",       &JetBTag_jetBProb,      &b_JetBTag_jetBProb);
  fChain->SetBranchAddress(jets+"JetBTag_SSVHE",          &JetBTag_SSVHE,         &b_JetBTag_SSVHE);
  fChain->SetBranchAddress(jets+"JetBTag_SSVHP",          &JetBTag_SSVHP,         &b_JetBTag_SSVHP);
  fChain->SetBranchAddress(jets+"JetBTag_CSV",            &JetBTag_CSV,           &b_JetBTag_CSV);
  fChain->SetBranchAddress(jets+"JetBTag_CSVMVA",         &JetBTag_CSVMVA,        &b_JetBTag_CSVMVA);
  fChain->SetBranchAddress(jets+"JetBTag_SoftLepton",     &JetBTag_SoftLepton,    &b_JetBTag_SoftLepton);
  fChain->SetBranchAddress(jets+"JetBTag_SoftLeptonByIP", &JetBTag_SoftLeptonByIP,&b_JetBTag_SoftLeptonByIP);
  fChain->SetBranchAddress(jets+"JetBTag_SoftLeptonByPt", &JetBTag_SoftLeptonByPt,&b_JetBTag_SoftLeptonByPt);

  //Calo/JPT Jet specific variables
  if (jets=="Calo"||jets=="JPT") {
    fChain->SetBranchAddress(jets+"JetfHPD",             &JetfHPD,            &b_JetfHPD);
    fChain->SetBranchAddress(jets+"JetfRBX",             &JetfRBX,            &b_JetfRBX);
    fChain->SetBranchAddress(jets+"Jetn90",              &Jetn90,             &b_Jetn90);
    fChain->SetBranchAddress(jets+"JetTrackPt",          &JetTrackPt,         &b_JetTrackPt);
    fChain->SetBranchAddress(jets+"JetTrackPhi",         &JetTrackPhi,        &b_JetTrackPhi);
    fChain->SetBranchAddress(jets+"JetTrackPhiWeighted", &JetTrackPhiWeighted,&b_JetTrackPhiWeighted);
    fChain->SetBranchAddress(jets+"JetTrackNo",          &JetTrackNo,         &b_JetTrackNo);
  }

  //JPT/PF Jet specific variables
  if (jets=="JPT"||jets=="PF") {
    fChain->SetBranchAddress(jets+"JetChargedFem",  &JetChargedFem, &b_JetChargedFem);
    fChain->SetBranchAddress(jets+"JetNeutralFem",  &JetNeutralFem, &b_JetNeutralFem);
    fChain->SetBranchAddress(jets+"JetChargedFhad", &JetChargedFhad,&b_JetChargedFhad);
    fChain->SetBranchAddress(jets+"JetNeutralFhad", &JetNeutralFhad,&b_JetNeutralFhad);
    fChain->SetBranchAddress(jets+"JetChargedMult", &JetChargedMult,&b_JetChargedMult);
    fChain->SetBranchAddress(jets+"JetElecMulti",   &JetElecMulti,  &b_JetElecMulti);
    fChain->SetBranchAddress(jets+"JetMuonMulti",   &JetMuonMulti,  &b_JetMuonMulti);
  }

  //PF Jet specific variables
  if (jets=="PF") {
    fChain->SetBranchAddress(jets+"JetChargedFmu",     &JetChargedFmu,    &b_JetChargedFmu);
    fChain->SetBranchAddress(jets+"JetChargedFele",    &JetChargedFele,   &b_JetChargedFele);
    fChain->SetBranchAddress(jets+"JetChargedFpho",    &JetChargedFpho,   &b_JetChargedFpho);
    fChain->SetBranchAddress(jets+"JetHFFem",          &JetHFFem,         &b_JetHFFem);
    fChain->SetBranchAddress(jets+"JetHFFhad",         &JetHFFhad,        &b_JetHFFhad);
    fChain->SetBranchAddress(jets+"JetChargedHadMult", &JetChargedHadMult,&b_JetChargedHadMult);
    fChain->SetBranchAddress(jets+"JetNeutralHadMult", &JetNeutralHadMult,&b_JetNeutralHadMult);
    fChain->SetBranchAddress(jets+"JetPhotonMult",     &JetPhotonMult,    &b_JetPhotonMult);
    fChain->SetBranchAddress(jets+"JetNeutralMult",    &JetNeutralMult,   &b_JetNeutralMult);
  }

  fChain->SetBranchAddress(jets+"GenHt",    &GenHt,    &b_GenHt);
  fChain->SetBranchAddress(jets+"GenMHtP4", &GenMHtP4, &b_GenMHtP4);

  fChain->SetBranchAddress(jets+"GenJetP4",        &GenJetP4,        &b_GenJetP4);
  fChain->SetBranchAddress(jets+"JetPartonP4",     &JetPartonP4,     &b_JetPartonP4);
  fChain->SetBranchAddress(jets+"JetPartonId",     &JetPartonId,     &b_JetPartonId);
  fChain->SetBranchAddress(jets+"JetPartonMother", &JetPartonMother, &b_JetPartonMother);
  fChain->SetBranchAddress(jets+"JetPartonFlavour",&JetPartonFlavour,&b_JetPartonFlavour);

  //MET
  fChain->SetBranchAddress("nFull"+met+"MET",   &nFullMET,  &b_nFullMET);
  fChain->SetBranchAddress("nUncorr"+met+"MET", &nUncorrMET,&b_nUncorrMET);

  fChain->SetBranchAddress(met+"METP4",   &METP4,   &b_METP4);

  //fChain->SetBranchAddress(met+"MET_Fullcorr_nocc",             MET_Fullcorr,            &b_MET_Fullcorr);
  //fChain->SetBranchAddress(met+"METpt_Fullcorr_nocc",          &METpt_Fullcorr,          &b_METpt_Fullcorr);
  //fChain->SetBranchAddress(met+"METphi_Fullcorr_nocc",         &METphi_Fullcorr,         &b_METphi_Fullcorr);
  fChain->SetBranchAddress(met+"METsumEt_Fullcorr_nocc",       &METsumEt_Fullcorr,       &b_METsumEt_Fullcorr);
  fChain->SetBranchAddress(met+"METsignificance_Fullcorr_nocc",&METsignificance_Fullcorr,&b_METsignificance_Fullcorr);

  fChain->SetBranchAddress(met+"MET_Nocorr_nocc",      MET_Nocorr,     &b_MET_Nocorr);
  fChain->SetBranchAddress(met+"METpt_Nocorr_nocc",   &METpt_Nocorr,   &b_METpt_Nocorr);
  fChain->SetBranchAddress(met+"METphi_Nocorr_nocc",  &METphi_Nocorr,  &b_METphi_Nocorr);
  fChain->SetBranchAddress(met+"METsumEt_Nocorr_nocc",&METsumEt_Nocorr,&b_METsumEt_Nocorr);

  fChain->SetBranchAddress(met+"MET_Muoncorr_nocc",      MET_Muoncorr,     &b_MET_Muoncorr);
  fChain->SetBranchAddress(met+"METpt_Muoncorr_nocc",   &METpt_Muoncorr,   &b_METpt_Muoncorr);
  fChain->SetBranchAddress(met+"METphi_Muoncorr_nocc",  &METphi_Muoncorr,  &b_METphi_Muoncorr);
  fChain->SetBranchAddress(met+"METsumEt_Muoncorr_nocc",&METsumEt_Muoncorr,&b_METsumEt_Muoncorr);

  fChain->SetBranchAddress(met+"MET_JEScorr_nocc",      MET_JEScorr,     &b_MET_JEScorr);
  fChain->SetBranchAddress(met+"METpt_JEScorr_nocc",   &METpt_JEScorr,   &b_METpt_JEScorr);
  fChain->SetBranchAddress(met+"METphi_JEScorr_nocc",  &METphi_JEScorr,  &b_METphi_JEScorr);
  fChain->SetBranchAddress(met+"METsumEt_JEScorr_nocc",&METsumEt_JEScorr,&b_METsumEt_JEScorr);

  if (!isData_){
    //fChain->SetBranchAddress(met+"GenMETP4",    &GenMETP4,    &b_GenMETP4);
    fChain->SetBranchAddress("GenTrueMETP4",&GenMETTrueP4,&b_GenMETTrueP4);
    fChain->SetBranchAddress("GenCaloMETP4",&GenMETCaloP4,&b_GenMETCaloP4);
    //fChain->SetBranchAddress(met+"GenSumEt",    &GenSumEt,    &b_GenSumEt);
    fChain->SetBranchAddress("GenTrueSumEt",&GenTrueSumEt,&b_GenTrueSumEt);
    fChain->SetBranchAddress("GenCaloSumEt",&GenCaloSumEt,&b_GenCaloSumEt);
    //fChain->SetBranchAddress(met+"GenMETSig",    &GenMETSig,    &b_GenMETSig);
    fChain->SetBranchAddress("GenTrueMetSig",&GenTrueMETSig,&b_GenTrueMETSig);
    fChain->SetBranchAddress("GenCaloMetSig",&GenCaloMETSig,&b_GenCaloMETSig);
    //fChain->SetBranchAddress(met+"GenSignificance",    &GenSignificance,    &b_GenSignificance);
    fChain->SetBranchAddress("GenTrueSignificance",&GenTrueSignificance,&b_GenTrueSignificance);
    fChain->SetBranchAddress("GenCaloSignificance",&GenCaloSignificance,&b_GenCaloSignificance);
  }

  fChain->SetBranchAddress(phots+"PhotN",          &PhotN,          &b_PhotN);
  fChain->SetBranchAddress(phots+"PhotVeto",       &PhotVeto,       &b_PhotVeto);
  fChain->SetBranchAddress(phots+"PhotonP4",       &PhotonP4,       &b_PhotonP4);
  fChain->SetBranchAddress(phots+"PhotTrkIso",     &PhotTrkIso,     &b_PhotTrkIso);
  fChain->SetBranchAddress(phots+"PhotECalIso",    &PhotECalIso,    &b_PhotECalIso);
  fChain->SetBranchAddress(phots+"PhotHCalIso",    &PhotHCalIso,    &b_PhotHCalIso);
  fChain->SetBranchAddress(phots+"PhotAllIso",     &PhotAllIso,     &b_PhotAllIso);
  fChain->SetBranchAddress(phots+"PhotLoosePhoton",&PhotLoosePhoton,&b_PhotLoosePhoton);
  fChain->SetBranchAddress(phots+"PhotTightPhoton",&PhotTightPhoton,&b_PhotTightPhoton);

  fChain->SetBranchAddress(leps+"ElecVeto",  &ElecVeto,  &b_ElecVeto);
  fChain->SetBranchAddress(leps+"ElectronP4",&ElectronP4,&b_ElectronP4);
  fChain->SetBranchAddress(leps+"ElecN",     &ElecN,     &b_ElecN);

  fChain->SetBranchAddress(leps+"ElecCharge",    &ElecCharge,    &b_ElecCharge);
  fChain->SetBranchAddress(leps+"ElecHOverE",    &ElecHOverE,    &b_ElecHOverE);
  fChain->SetBranchAddress(leps+"ElecTrkIso",    &ElecTrkIso,    &b_ElecTrkIso);
  fChain->SetBranchAddress(leps+"ElecECalIso",   &ElecECalIso,   &b_ElecECalIso);
  fChain->SetBranchAddress(leps+"ElecHCalIso",   &ElecHCalIso,   &b_ElecHCalIso);
  fChain->SetBranchAddress(leps+"ElecAllIso",    &ElecAllIso,    &b_ElecAllIso);
  fChain->SetBranchAddress(leps+"ElecTrkChiNorm",&ElecTrkChiNorm,&b_ElecTrkChiNorm);

  fChain->SetBranchAddress(leps+"ElecIdLoose",   &ElecIdLoose,   &b_ElecIdLoose);
  fChain->SetBranchAddress(leps+"ElecIdTight",   &ElecIdTight,   &b_ElecIdTight);
  fChain->SetBranchAddress(leps+"ElecIdRobLoose",&ElecIdRobLoose,&b_ElecIdRobLoose);
  fChain->SetBranchAddress(leps+"ElecIdRobTight",&ElecIdRobTight,&b_ElecIdRobTight);
  fChain->SetBranchAddress(leps+"ElecIdRobHighE",&ElecIdRobHighE,&b_ElecIdRobHighE);

  fChain->SetBranchAddress(leps+"ElecChargeMode",&ElecChargeMode,&b_ElecChargeMode);
  fChain->SetBranchAddress(leps+"ElecPtMode",    &ElecPtMode,    &b_ElecPtMode);

  fChain->SetBranchAddress(leps+"ElecVx",   &ElecVx,   &b_ElecVx);
  fChain->SetBranchAddress(leps+"ElecVy",   &ElecVy,   &b_ElecVy);
  fChain->SetBranchAddress(leps+"ElecVz",   &ElecVz,   &b_ElecVz);
  fChain->SetBranchAddress(leps+"ElecD0",   &ElecD0,   &b_ElecD0);
  fChain->SetBranchAddress(leps+"ElecD0Err",&ElecD0Err,&b_ElecD0Err);
  fChain->SetBranchAddress(leps+"ElecDz",   &ElecDz,   &b_ElecDz);
  fChain->SetBranchAddress(leps+"ElecPtTrk",&ElecPtTrk,&b_ElecPtTrk);

  fChain->SetBranchAddress(leps+"ElecQOverPErrTrkMode",&ElecQOverPErrTrkMode,&b_ElecQOverPErrTrkMode);
  fChain->SetBranchAddress(leps+"ElecCaloEnergy",      &ElecCaloEnergy,      &b_ElecCaloEnergy);
  fChain->SetBranchAddress(leps+"ElecQOverPErrTrk",    &ElecQOverPErrTrk,    &b_ElecQOverPErrTrk);
  fChain->SetBranchAddress(leps+"ElecPinTrk",          &ElecPinTrk,          &b_ElecPinTrk);
  fChain->SetBranchAddress(leps+"ElecPoutTrk",         &ElecPoutTrk,         &b_ElecPoutTrk);
  fChain->SetBranchAddress(leps+"ElecLostHits",        &ElecLostHits,        &b_ElecLostHits);
  fChain->SetBranchAddress(leps+"ElecValidHits",       &ElecValidHits,       &b_ElecValidHits);
  fChain->SetBranchAddress(leps+"ElecEtaTrk",          &ElecEtaTrk,          &b_ElecEtaTrk);
  fChain->SetBranchAddress(leps+"ElecPhiTrk",          &ElecPhiTrk,          &b_ElecPhiTrk);
  fChain->SetBranchAddress(leps+"ElecWidthClusterEta", &ElecWidthClusterEta, &b_ElecWidthClusterEta);
  fChain->SetBranchAddress(leps+"ElecWidthClusterPhi", &ElecWidthClusterPhi, &b_ElecWidthClusterPhi);

  fChain->SetBranchAddress(leps+"MuonVeto",&MuonVeto,&b_MuonVeto);
  fChain->SetBranchAddress(leps+"MuonP4",  &MuonP4,  &b_MuonP4);
  fChain->SetBranchAddress(leps+"MuonN",   &MuonN,   &b_MuonN);

  fChain->SetBranchAddress(leps+"MuonCharge",  &MuonCharge, &b_MuonCharge);
  fChain->SetBranchAddress(leps+"MuonTrkIso",  &MuonTrkIso, &b_MuonTrkIso);
  fChain->SetBranchAddress(leps+"MuonECalIso", &MuonECalIso,&b_MuonECalIso);
  fChain->SetBranchAddress(leps+"MuonHCalIso", &MuonHCalIso,&b_MuonHCalIso);
  fChain->SetBranchAddress(leps+"MuonAllIso",  &MuonAllIso, &b_MuonAllIso);

  fChain->SetBranchAddress(leps+"MuonTrkChiNorm",    &MuonTrkChiNorm,    &b_MuonTrkChiNorm);
  fChain->SetBranchAddress(leps+"MuonECalIsoDeposit",&MuonECalIsoDeposit,&b_MuonECalIsoDeposit);
  fChain->SetBranchAddress(leps+"MuonHCalIsoDeposit",&MuonHCalIsoDeposit,&b_MuonHCalIsoDeposit);

  fChain->SetBranchAddress(leps+"MuonIsGlobal",               &MuonIsGlobal,              &b_MuonIsGlobal);
  fChain->SetBranchAddress(leps+"MuonIsStandAlone",           &MuonIsStandAlone,          &b_MuonIsStandAlone);
  fChain->SetBranchAddress(leps+"MuonIsTracker",              &MuonIsTracker,             &b_MuonIsTracker);
  fChain->SetBranchAddress(leps+"MuonGlobalMuonPromptTight",  &MuonGlobalMuonPromptTight, &b_MuonGlobalMuonPromptTight);
  fChain->SetBranchAddress(leps+"MuonAllArbitrated",          &MuonAllArbitrated,         &b_MuonAllArbitrated);
  fChain->SetBranchAddress(leps+"MuonTrackerMuonArbitrated",  &MuonTrackerMuonArbitrated, &b_MuonTrackerMuonArbitrated);
  fChain->SetBranchAddress(leps+"MuonTMLastStationLoose",     &MuonTMLastStationLoose,    &b_MuonTMLastStationLoose);
  fChain->SetBranchAddress(leps+"MuonTMLastStationTight",     &MuonTMLastStationTight,    &b_MuonTMLastStationTight);
  fChain->SetBranchAddress(leps+"MuonTM2DCompatibilityLoose", &MuonTM2DCompatibilityLoose,&b_MuonTM2DCompatibilityLoose);
  fChain->SetBranchAddress(leps+"MuonTM2DCompatibilityTight", &MuonTM2DCompatibilityTight,&b_MuonTM2DCompatibilityTight);
  fChain->SetBranchAddress(leps+"MuonTMOneStationLoose",      &MuonTMOneStationLoose,     &b_MuonTMOneStationLoose);
  fChain->SetBranchAddress(leps+"MuonTMOneStationTight",      &MuonTMOneStationTight,     &b_MuonTMOneStationTight);

  fChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedLowPtLoose",      &MuonTMLastStationOptimizedLowPtLoose,      &b_MuonTMLastStationOptimizedLowPtLoose);
  fChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedLowPtTight",      &MuonTMLastStationOptimizedLowPtTight,      &b_MuonTMLastStationOptimizedLowPtTight);
  fChain->SetBranchAddress(leps+"MuonGMTkChiCompatibility",                  &MuonGMTkChiCompatibility,                  &b_MuonGMTkChiCompatibility);
  fChain->SetBranchAddress(leps+"MuonGMStaChiCompatibility",                 &MuonGMStaChiCompatibility,                 &b_MuonGMStaChiCompatibility);
  fChain->SetBranchAddress(leps+"MuonGMTkKinkTight",                         &MuonGMTkKinkTight,                         &b_MuonGMTkKinkTight);
  fChain->SetBranchAddress(leps+"MuonTMLastStationAngLoose",                 &MuonTMLastStationAngLoose,                 &b_MuonTMLastStationAngLoose);
  fChain->SetBranchAddress(leps+"MuonTMLastStationAngTight",                 &MuonTMLastStationAngTight,                 &b_MuonTMLastStationAngTight);
  fChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedBarrelLowPtLoose",&MuonTMLastStationOptimizedBarrelLowPtLoose,&b_MuonTMLastStationOptimizedBarrelLowPtLoose);
  fChain->SetBranchAddress(leps+"MuonTMLastStationOptimizedBarrelLowPtTight",&MuonTMLastStationOptimizedBarrelLowPtTight,&b_MuonTMLastStationOptimizedBarrelLowPtTight);

  fChain->SetBranchAddress(leps+"MuonCombChi2", &MuonCombChi2, &b_MuonCombChi2);
  fChain->SetBranchAddress(leps+"MuonCombNdof", &MuonCombNdof, &b_MuonCombNdof);
  fChain->SetBranchAddress(leps+"MuonCombVx",   &MuonCombVx,   &b_MuonCombVx);
  fChain->SetBranchAddress(leps+"MuonCombVy",   &MuonCombVy,   &b_MuonCombVy);
  fChain->SetBranchAddress(leps+"MuonCombVz",   &MuonCombVz,   &b_MuonCombVz);
  fChain->SetBranchAddress(leps+"MuonCombD0",   &MuonCombD0,   &b_MuonCombD0);
  fChain->SetBranchAddress(leps+"MuonCombD0Err",&MuonCombD0Err,&b_MuonCombD0Err);
  fChain->SetBranchAddress(leps+"MuonCombDz",   &MuonCombDz,   &b_MuonCombDz);

  fChain->SetBranchAddress(leps+"MuonStandValidHits",&MuonStandValidHits,&b_MuonStandValidHits);
  fChain->SetBranchAddress(leps+"MuonStandLostHits", &MuonStandLostHits, &b_MuonStandLostHits);
  fChain->SetBranchAddress(leps+"MuonStandPt",       &MuonStandPt,       &b_MuonStandPt);
  fChain->SetBranchAddress(leps+"MuonStandPz",       &MuonStandPz,       &b_MuonStandPz);
  fChain->SetBranchAddress(leps+"MuonStandP",        &MuonStandP,        &b_MuonStandP);
  fChain->SetBranchAddress(leps+"MuonStandEta",      &MuonStandEta,      &b_MuonStandEta);
  fChain->SetBranchAddress(leps+"MuonStandPhi",      &MuonStandPhi,      &b_MuonStandPhi);
  fChain->SetBranchAddress(leps+"MuonStandCharge",   &MuonStandCharge,   &b_MuonStandCharge);
  fChain->SetBranchAddress(leps+"MuonStandChi",      &MuonStandChi,      &b_MuonStandChi);
  fChain->SetBranchAddress(leps+"MuonStandQOverPErr",&MuonStandQOverPErr,&b_MuonStandQOverPErr);

  fChain->SetBranchAddress(leps+"MuonTrkValidHits",&MuonTrkValidHits,&b_MuonTrkValidHits);
  fChain->SetBranchAddress(leps+"MuonTrkLostHits", &MuonTrkLostHits, &b_MuonTrkLostHits);
  fChain->SetBranchAddress(leps+"MuonTrkD0",       &MuonTrkD0,       &b_MuonTrkD0);
  fChain->SetBranchAddress(leps+"MuonTrkD0Err",    &MuonTrkD0Err,    &b_MuonTrkD0Err);
  fChain->SetBranchAddress(leps+"MuonTrkPt",       &MuonTrkPt,       &b_MuonTrkPt);
  fChain->SetBranchAddress(leps+"MuonTrkPz",       &MuonTrkPz,       &b_MuonTrkPz);
  fChain->SetBranchAddress(leps+"MuonTrkP",        &MuonTrkP,        &b_MuonTrkP);
  fChain->SetBranchAddress(leps+"MuonTrkEta",      &MuonTrkEta,      &b_MuonTrkEta);
  fChain->SetBranchAddress(leps+"MuonTrkPhi",      &MuonTrkPhi,      &b_MuonTrkPhi);
  fChain->SetBranchAddress(leps+"MuonTrkCharge",   &MuonTrkCharge,   &b_MuonTrkCharge);
  fChain->SetBranchAddress(leps+"MuonTrkChi",      &MuonTrkChi,      &b_MuonTrkChi);
  fChain->SetBranchAddress(leps+"MuonTrkQOverPErr",&MuonTrkQOverPErr,&b_MuonTrkQOverPErr);
  fChain->SetBranchAddress(leps+"MuonTrkOuterZ",   &MuonTrkOuterZ,   &b_MuonTrkOuterZ);
  fChain->SetBranchAddress(leps+"MuonTrkOuterR",   &MuonTrkOuterR,   &b_MuonTrkOuterR);

  fChain->SetBranchAddress(leps+"TauVeto",  &TauVeto,  &b_TauVeto);
  fChain->SetBranchAddress(leps+"TauP4",    &TauP4,    &b_TauP4);
  fChain->SetBranchAddress(leps+"TauN",     &TauN,     &b_TauN);

  fChain->SetBranchAddress(leps+"TauCharge",    &TauCharge,    &b_TauCharge);
  fChain->SetBranchAddress(leps+"TauTrkIso",    &TauTrkIso,    &b_TauTrkIso);
  fChain->SetBranchAddress(leps+"TauECalIso",   &TauECalIso,   &b_TauECalIso);
  fChain->SetBranchAddress(leps+"TauHCalIso",   &TauHCalIso,   &b_TauHCalIso);
  fChain->SetBranchAddress(leps+"TauAllIso",    &TauAllIso,    &b_TauAllIso);

  fChain->SetBranchAddress(leps+"TauIdElec",       &TauIdElec,       &b_TauIdElec);
  fChain->SetBranchAddress(leps+"TauIdMuon",       &TauIdMuon,       &b_TauIdMuon);
  fChain->SetBranchAddress(leps+"TauIdIso",        &TauIdIso,        &b_TauIdIso);
  fChain->SetBranchAddress(leps+"TauIdNCfrFull",   &TauIdNCfrFull,   &b_TauIdNCfrFull);
  fChain->SetBranchAddress(leps+"TauIdNCfrHalf",   &TauIdNCfrHalf,   &b_TauIdNCfrHalf);
  fChain->SetBranchAddress(leps+"TauIdNCfrQuarter",&TauIdNCfrQuarter,&b_TauIdNCfrQuarter);

  fChain->SetBranchAddress(leps+"TauVx",   &TauVx,   &b_TauVx);
  fChain->SetBranchAddress(leps+"TauVy",   &TauVy,   &b_TauVy);
  fChain->SetBranchAddress(leps+"TauVz",   &TauVz,   &b_TauVz);
  fChain->SetBranchAddress(leps+"TauD0",   &TauD0,   &b_TauD0);
  fChain->SetBranchAddress(leps+"TauD0Err",&TauD0Err,&b_TauD0Err);
  fChain->SetBranchAddress(leps+"TauDz",   &TauDz,   &b_TauDz);

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

  fChain->SetBranchAddress("HLTTriggered",&HLTTriggered,&b_HLTTriggered);
  fChain->SetBranchAddress("HLTPrescaled",&HLTPrescaled,&b_HLTPrescaled);

  fChain->SetBranchAddress(leps+"ElecGenP4",    &ElecGenP4,    &b_ElecGenP4);
  fChain->SetBranchAddress(leps+"ElecGenPdgId", &ElecGenPdgId, &b_ElecGenPdgId);
  fChain->SetBranchAddress(leps+"ElecGenMother",&ElecGenMother,&b_ElecGenMother);
  
  fChain->SetBranchAddress(leps+"MuonGenP4",    &MuonGenP4,    &b_MuonGenP4);
  fChain->SetBranchAddress(leps+"MuonGenPdgId", &MuonGenPdgId, &b_MuonGenPdgId);
  fChain->SetBranchAddress(leps+"MuonGenMother",&MuonGenMother,&b_MuonGenMother);
  
  fChain->SetBranchAddress(leps+"TauGen",      &TauGen,      &b_TauGen);
  fChain->SetBranchAddress(leps+"TauGenP4",    &TauGenP4,    &b_TauGenP4);
  fChain->SetBranchAddress(leps+"TauGenPdgId", &TauGenPdgId, &b_TauGenPdgId);
  fChain->SetBranchAddress(leps+"TauGenMother",&TauGenMother,&b_TauGenMother);
  fChain->SetBranchAddress(leps+"TauGenJetP4", &TauGenJetP4, &b_TauGenJetP4);
  
  fChain->SetBranchAddress(phots+"PhotGenP4",    &PhotGenP4,    &b_PhotGenP4);
  fChain->SetBranchAddress(phots+"PhotGenPdgId", &PhotGenPdgId, &b_PhotGenPdgId);
  fChain->SetBranchAddress(phots+"PhotGenMother",&PhotGenMother,&b_PhotGenMother);

  if (!isData_) {
    //if ( fChain->GetBranch(leps+"genN") ) {
      fChain->SetBranchAddress(leps+"genN",         &genN,        &b_genN);
      fChain->SetBranchAddress(leps+"genP4",        &genP4,       &b_genP4 );
      fChain->SetBranchAddress(leps+"genId",        &genId,       &b_genId);
      fChain->SetBranchAddress(leps+"genStatus",    &genStatus,   &b_genStatus);
      fChain->SetBranchAddress(leps+"genMother",    &genMother,   &b_genMother);
      fChain->SetBranchAddress(leps+"genDaughters", &genDaughters,&b_genDaughters);
      //}
      //if ( fChain->GetBranch(leps+"genPhotN") ) {
      fChain->SetBranchAddress(leps+"genPhotN",        &genPhotN,        &b_genPhotN);
      fChain->SetBranchAddress(leps+"genPhotP4",       &genPhotP4,       &b_genPhotP4);
      fChain->SetBranchAddress(leps+"genPhotId",       &genPhotId,       &b_genPhotId);
      fChain->SetBranchAddress(leps+"genPhotStatus",   &genPhotStatus,   &b_genPhotStatus);
      fChain->SetBranchAddress(leps+"genPhotMother",   &genPhotMother,   &b_genPhotMother);
      fChain->SetBranchAddress(leps+"genPhotDaughters",&genPhotDaughters,&b_genPhotDaughters);
      //}
      //if ( fChain->GetBranch(leps+"genLepN") ) {
      fChain->SetBranchAddress(leps+"genLepN",        &genLepN,        &b_genLepN);
      fChain->SetBranchAddress(leps+"genLepP4",       &genLepP4,       &b_genLepP4);
      fChain->SetBranchAddress(leps+"genLepId",       &genLepId,       &b_genLepId);
      fChain->SetBranchAddress(leps+"genLepStatus",   &genLepStatus,   &b_genLepStatus);
      fChain->SetBranchAddress(leps+"genLepMother",   &genLepMother,   &b_genLepMother);
      fChain->SetBranchAddress(leps+"genLepDaughters",&genLepDaughters,&b_genLepDaughters);
      //}    
    fChain->SetBranchAddress(leps+"pthat",        &pthat, &b_pthat);

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

Bool_t ntupleAnalysisPAT::muonID(int index, int mode) {
  //Requirements for muonID
  double relIso = (MuonTrkIso->at(index)+MuonECalIso->at(index)+MuonHCalIso->at(index))/MuonP4->at(index).Pt();
  bool muonID = false;
  if (MuonGlobalMuonPromptTight->at(index))
    //if (MuonIsGlobal->at(index))
    //if (< muon_maxchi2)
    //if (>= muon_minhits)
    if (MuonP4->at(index).Pt() >= muon_minpt)
      if (fabs(MuonP4->at(index).Eta()) <= muon_maxeta)
	if (relIso < muon_maxreliso)
	  if (MuonTrkD0->at(index)< muon_maxd0)
	    //if (MuonCompD0->at(index)< muon_maxd0)
	    muonID = true;
  
  return muonID;
}

Bool_t ntupleAnalysisPAT::electronID(int index, bool tight ) {
  //Requirements for electronID
  double relIso = (ElecTrkIso->at(index)+ElecECalIso->at(index)+ElecHCalIso->at(index))/ElectronP4->at(index).Pt();
  bool electronID = false;
  bool electronRequirement;
  if (tight)
    electronRequirement = ElecIdTight->at(index);
  else
    electronRequirement = ElecIdLoose->at(index);

  if (electronRequirement)
    if (ElectronP4->at(index).Pt() >= electron_minpt)
      //if (fabs(ElectronP4->at(index).Eta()) <= electron_maxeta)
      if (relIso < electron_maxreliso)
	if (ElecD0->at(index)< electron_maxd0)
	  //if (ElecCompD0->at(index)< electron_maxd0)
	  electronID = true;
  
  return electronID;
}

//Simple identification criteria for photons
Bool_t ntupleAnalysisPAT::photonID(int index, bool tight) {

  //Requirements for photonID
  double relIso = (PhotTrkIso->at(index)+PhotECalIso->at(index)+PhotHCalIso->at(index))/PhotonP4->at(index).Pt();
  bool photonID = false;
  bool photonRequirement;
  if (tight)
    photonRequirement = PhotTightPhoton->at(index);
  else
    photonRequirement = PhotLoosePhoton->at(index);

  if (photonRequirement)
    if (PhotonP4->at(index).Pt() >= photon_minpt)
      if (fabs(PhotonP4->at(index).Eta()) <= photon_maxeta)
	if (relIso < photon_maxreliso)
	  //if (PhotTrkD0->at(index)< photon_maxd0)
	  //if (PhotCompD0->at(index)< photon_maxd0)
	  photonID = true;
  
  return photonID;
}

//Compute HT from the Jet Collection
//If possible, use the stored P4
Double_t ntupleAnalysisPAT::computeHT(double& minpt, double& maxeta, bool fromRAW) {
  
  LorentzP4Vs *theJets;
  if (fromRAW) 
    theJets = RawJetP4;
  else
    theJets = JetP4;
  Double_t theHT    = 0.;
  
  LorentzP4V theJet;
  LorentzP4Vs::iterator jet = theJets->begin();
  while (jet != theJets->end()) {
    theJet = *jet ;
    if (theJet.Pt() > minpt)
      if (fabs(theJet.Eta()) < maxeta)
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theHT += theJet.Pt();
    ++jet;
  }
  return theHT;
}

TLorentzVector ntupleAnalysisPAT::computeMHT(double& minpt, double& maxeta, bool fromRAW) {

  LorentzP4Vs *theJets;
  if (fromRAW) 
    theJets = RawJetP4;
  else
    theJets = JetP4;
  TLorentzVector theMHT;
  theMHT.SetPxPyPzE(0,0,0,0);

  TLorentzVector theJet;
  LorentzP4Vs::iterator jet = theJets->begin();
  while (jet != theJets->end()) {
    if (jet->Pt() > minpt) 
      if (fabs(jet->Eta()) < maxeta) {
	
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theJet.SetPxPyPzE(jet->Px(),jet->Py(),jet->Pz(),jet->E());
	theMHT -= theJet;
      }
    ++jet;
  }
  return theMHT;
}

Double_t ntupleAnalysisPAT::computeDPhiStar(TLorentzVector mht, double& minpt, double& maxeta, bool fromRAW) {

  LorentzP4Vs *theJets;
  if (fromRAW) 
    theJets = RawJetP4;
  else
    theJets = JetP4;

  double    dphistar = 10.;

  TLorentzVector theJet;
  LorentzP4Vs::iterator jet = theJets->begin();
  while (jet != theJets->end()) {
    if (jet->Pt() > minpt)
      if (fabs(jet->Eta()) < maxeta) {
	//if (jetID(jet,false)
	//Do we want some jetID requirement?
	theJet.SetPxPyPzE(jet->Px(),jet->Py(),jet->Pz(),jet->E());
	mht += theJet;
	double tmpdphi = theJet.DeltaPhi(mht);
	tmpdphi = (tmpdphi < 0)    ? -tmpdphi         : tmpdphi;
	tmpdphi = (tmpdphi > M_PI) ? 2*M_PI - tmpdphi : tmpdphi;
	dphistar = (fabs(dphistar) < fabs(tmpdphi)) ? dphistar : tmpdphi;
      }
    ++jet;
  }
  return dphistar;
}


#endif // #ifdef ntupleAnalysisPAT_cxx

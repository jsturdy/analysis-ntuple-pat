#ifndef METResolutionStudy_h
#define METResolutionStudy_h

#include <TROOT.h>
#include <TLorentzVector.h>
#include <TChain.h>
#include <TTree.h>
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

#include "../ntuplePragmas.h"
//#include "../myDict.h"

//typedef std::map<std::string, bool>                               stringtobool;
//typedef std::map<std::string, int>                                stringtoint;
//typedef std::map<std::string, std::vector<float> >                stringtovfloat;

class METResolutionStudy  {
 public :
  
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  UInt_t  Run;
  UInt_t  Event;
  UInt_t  OrbitN;
  UInt_t  StoreN;
  UInt_t  LumiSection;
  UInt_t  BunchCrossing;
    
  //Jets
  Int_t  NJets;
    
  //std::vector<TLorentzVector>
  LorentzP4Vs *JetP4;
  LorentzP4Vs *RawJetP4;

  //JetID info
  std::vector<bool>    *JetIDMinimal;
  std::vector<bool>    *JetIDLoose;
  std::vector<bool>    *JetIDTight;
    
  LorentzP4V     *CaloTypeIMETP4;
  LorentzP4V     *CaloTypeIIMETP4;
  LorentzP4V     *PFMETP4;
  LorentzP4V     *TCMETP4;

  //ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> >     *METP4;
  Double_t        CaloTypeIMETsumEt;
  Double_t        CaloTypeIMETsignificance;

  Double_t        CaloTypeIIMETsumEt;
  Double_t        CaloTypeIIMETsignificance;

  Double_t        PFMETsumEt;
  Double_t        PFMETsignificance;

  Double_t        TCMETsumEt;
  Double_t        TCMETsignificance;

  LorentzP4V     *GenTrueMETP4;
  LorentzP4V     *GenCaloMETP4;

  Double_t        GenTrueSumEt;
  Double_t        GenCaloSumEt;

  Double_t        GenTrueMETSig;
  Double_t        GenCaloMETSig;

  Double_t        GenTrueSignificance;
  Double_t        GenCaloSignificance;

  //Photons
  Int_t           PhotN;
  LorentzP4Vs    *PhotonP4;

  std::vector<double> *PhotTrkIso;
  std::vector<double> *PhotECalIso;
  std::vector<double> *PhotHCalIso;
  std::vector<double> *PhotAllIso;
  std::vector<bool>   *PhotLoosePhoton;
  std::vector<bool>   *PhotTightPhoton;
    
    
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
    
  //Trigger information
  stringtobool *L1Triggered;
  stringtoint  *L1Prescaled;
  stringtobool *HLTTriggered;
  stringtoint  *HLTPrescaled;

  // List of branches
  TBranch  *b_Run;
  TBranch  *b_Event;
  TBranch  *b_OrbitN;
  TBranch  *b_StoreN;
  TBranch  *b_LumiSection;
  TBranch  *b_BunchCrossing;
    	     
  TBranch  *b_NJets;
  TBranch  *b_JetP4;
  TBranch  *b_RawJetP4;

  TBranch  *b_JetIDMinimal;
  TBranch  *b_JetIDLoose;
  TBranch  *b_JetIDTight;
	     

  TBranch  *b_CaloTypeIMETP4;
  TBranch  *b_CaloTypeIMETsumEt;
  TBranch  *b_CaloTypeIMETsignificance;

  TBranch  *b_CaloTypeIIMETP4;
  TBranch  *b_CaloTypeIIMETsumEt;
  TBranch  *b_CaloTypeIIMETsignificance;

  TBranch  *b_PFMETP4;
  TBranch  *b_PFMETsumEt;
  TBranch  *b_PFMETsignificance;

  TBranch  *b_TCMETP4;
  TBranch  *b_TCMETsumEt;
  TBranch  *b_TCMETsignificance;

  TBranch  *b_GenTrueMETP4;
  TBranch  *b_GenCaloMETP4;

  TBranch  *b_GenTrueSumEt;
  TBranch  *b_GenCaloSumEt;

  TBranch  *b_GenTrueMETSig;
  TBranch  *b_GenCaloMETSig;

  TBranch  *b_GenTrueSignificance;
  TBranch  *b_GenCaloSignificance;    	     
    	     
  TBranch  *b_PhotonP4;
  TBranch  *b_PhotN;
  TBranch  *b_PhotTrkIso;
  TBranch  *b_PhotECalIso;
  TBranch  *b_PhotHCalIso;
  TBranch  *b_PhotAllIso;
  TBranch  *b_PhotLoosePhoton;
  TBranch  *b_PhotTightPhoton;
    	     
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
    	     
  TBranch  *b_L1Triggered;
  TBranch  *b_L1Prescaled;
  TBranch  *b_HLTTriggered;
  TBranch  *b_HLTPrescaled;


  METResolutionStudy(TTree *tree=0, bool isData=false, std::string jetPrefix="PF", std::string phtPrefix="", bool debug=false);
  ~METResolutionStudy();

  Int_t    Cut(Long64_t entry);

  Int_t    GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void     Init(TTree *tree);
  Bool_t   Notify();
  void     Show(Long64_t entry = -1);
  void     Loop(TString outfile,int scale_type);

  //friend class commonFunctions;

  Double_t luminosity_, cross_section_, efficiency_, generated_events_;
  std::string outfilename_;
  std::string infilename_;
  std::string jetPrefix_;
  std::string phtPrefix_;
    
  bool isData_;
  bool debug_;
};

#endif

#ifdef METResolutionStudy_cxx

METResolutionStudy::METResolutionStudy(TTree *tree, 
				       bool isData, 
				       std::string jetPrefix, 
				       std::string phtPrefix,
				       bool debug ) {
  
  std::cout<<"METResolutionStudy::Constructor"<<std::endl;
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  isData_    = isData;
  debug_     = debug;
  jetPrefix_ = jetPrefix;
  phtPrefix_ = phtPrefix;
  
  
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/tmp/sturdy/PATtuple_V9_MC_TTBar.root");
    if (!f) {
      f = new TFile("/tmp/sturdy/PATtuple_V9_MC_TTBar.root");
    }
    tree = (TTree*)gDirectory->Get("analysisNtuplePAT/AllData");
    
  }
  Init(tree);
}

METResolutionStudy::~METResolutionStudy() 
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t METResolutionStudy::GetEntry(Long64_t entry) {
  std::cout<<"trying to get the entry of the tree"<<std::endl;
  // Read contents of entry.
  if (!fChain) return 0;
  std::cout<<"tree valid, getting the entry"<<std::endl;
  return fChain->GetEntry(entry);
}

Long64_t METResolutionStudy::LoadTree(Long64_t entry) {
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

void METResolutionStudy::Init(TTree *tree) {
  std::cout<<"METResolutionStudy::Init"<<std::endl;
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  //Set pointers
  JetP4    = 0;
  RawJetP4 = 0;

  JetIDMinimal  = 0;
  JetIDLoose    = 0;
  JetIDTight    = 0;
    
  CaloTypeIMETP4        = 0;
  CaloTypeIIMETP4        = 0;
  PFMETP4        = 0;
  TCMETP4        = 0;

  GenTrueMETP4 = 0;
  GenCaloMETP4 = 0;
    
  PhotonP4  = 0;

  PhotTrkIso      = 0;
  PhotECalIso     = 0;
  PhotHCalIso     = 0;
  PhotAllIso      = 0;
  PhotLoosePhoton = 0;
  PhotTightPhoton = 0;

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

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  //fChain->SetMakeClass(1);

  fChain->SetBranchAddress("Run",           &Run,          &b_Run);
  fChain->SetBranchAddress("Event",         &Event,        &b_Event);
  fChain->SetBranchAddress("OrbitN",        &OrbitN,       &b_OrbitN);
  fChain->SetBranchAddress("StoreN",        &StoreN,       &b_StoreN);
  fChain->SetBranchAddress("LumiSection",   &LumiSection,  &b_LumiSection);
  fChain->SetBranchAddress("BunchCrossing", &BunchCrossing,&b_BunchCrossing);

  fChain->SetBranchAddress(TString(jetPrefix_)+"NJets",   &NJets,   &b_NJets);

  fChain->SetBranchAddress(TString(jetPrefix_)+"JetP4",    &JetP4,    &b_JetP4);
  fChain->SetBranchAddress(TString(jetPrefix_)+"RawJetP4", &RawJetP4, &b_RawJetP4);

  //Jet ID (implemented only for Calo/JPT (all three) and PF jets (loose/tight)
  fChain->SetBranchAddress(TString(jetPrefix_)+"JetIDMinimal", &JetIDMinimal,&b_JetIDMinimal);
  fChain->SetBranchAddress(TString(jetPrefix_)+"JetIDLoose",   &JetIDLoose,  &b_JetIDLoose);
  fChain->SetBranchAddress(TString(jetPrefix_)+"JetIDTight",   &JetIDTight,  &b_JetIDTight);

  fChain->SetBranchAddress("CaloTypeIMETP4",  &CaloTypeIMETP4,  &b_CaloTypeIMETP4);
  fChain->SetBranchAddress("CaloTypeIIMETP4", &CaloTypeIIMETP4, &b_CaloTypeIIMETP4);
  fChain->SetBranchAddress("PFMETP4",         &PFMETP4,         &b_PFMETP4);
  fChain->SetBranchAddress("TCMETP4",         &TCMETP4,         &b_TCMETP4);

  fChain->SetBranchAddress("CaloTypeIMETsumEt_Fullcorr_nocc",        &CaloTypeIMETsumEt,        &b_CaloTypeIMETsumEt);
  fChain->SetBranchAddress("CaloTypeIMETsignificance_Fullcorr_nocc", &CaloTypeIMETsignificance, &b_CaloTypeIMETsignificance);

  fChain->SetBranchAddress("CaloTypeIIMETsumEt_Fullcorr_nocc",        &CaloTypeIIMETsumEt,        &b_CaloTypeIIMETsumEt);
  fChain->SetBranchAddress("CaloTypeIIMETsignificance_Fullcorr_nocc", &CaloTypeIIMETsignificance, &b_CaloTypeIIMETsignificance);

  fChain->SetBranchAddress("PFMETsumEt_Fullcorr_nocc",        &PFMETsumEt,        &b_PFMETsumEt);
  fChain->SetBranchAddress("PFMETsignificance_Fullcorr_nocc", &PFMETsignificance, &b_PFMETsignificance);

  fChain->SetBranchAddress("TCMETsumEt_Fullcorr_nocc",        &TCMETsumEt,        &b_TCMETsumEt);
  fChain->SetBranchAddress("TCMETsignificance_Fullcorr_nocc", &TCMETsignificance, &b_TCMETsignificance);

  if (!isData_) {
    fChain->SetBranchAddress("GenMetTrueMETP4", &GenTrueMETP4, &b_GenTrueMETP4);
    fChain->SetBranchAddress("GenMetCaloMETP4", &GenCaloMETP4, &b_GenCaloMETP4);
    
    fChain->SetBranchAddress("GenMetTrueSumEt", &GenTrueSumEt, &b_GenTrueSumEt);
    fChain->SetBranchAddress("GenMetCaloSumEt", &GenCaloSumEt, &b_GenCaloSumEt);
    
    fChain->SetBranchAddress("GenMetTrueMetSig", &GenTrueMETSig, &b_GenTrueMETSig);
    fChain->SetBranchAddress("GenMetCaloMetSig", &GenCaloMETSig, &b_GenCaloMETSig);
    
    fChain->SetBranchAddress("GenMetTrueSignificance", &GenTrueSignificance, &b_GenTrueSignificance);
    fChain->SetBranchAddress("GenMetCaloSignificance", &GenCaloSignificance, &b_GenCaloSignificance);
  }

  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotN",          &PhotN,          &b_PhotN);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotonP4",       &PhotonP4,       &b_PhotonP4);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotTrkIso",     &PhotTrkIso,     &b_PhotTrkIso);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotECalIso",    &PhotECalIso,    &b_PhotECalIso);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotHCalIso",    &PhotHCalIso,    &b_PhotHCalIso);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotAllIso",     &PhotAllIso,     &b_PhotAllIso);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotLoosePhoton",&PhotLoosePhoton,&b_PhotLoosePhoton);
  fChain->SetBranchAddress(TString(phtPrefix_)+"PhotTightPhoton",&PhotTightPhoton,&b_PhotTightPhoton);
  
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

  fChain->SetBranchAddress("L1Triggered", &L1Triggered, &b_L1Triggered);
  fChain->SetBranchAddress("L1Prescaled", &L1Prescaled, &b_L1Prescaled);
  fChain->SetBranchAddress("HLTTriggered",&HLTTriggered,&b_HLTTriggered);
  fChain->SetBranchAddress("HLTPrescaled",&HLTPrescaled,&b_HLTPrescaled);

  Notify();
}

Bool_t METResolutionStudy::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void METResolutionStudy::Show(Long64_t entry) {

  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t METResolutionStudy::Cut(Long64_t entry) {

  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

#endif // #ifdef METResolutionStudy_cxx

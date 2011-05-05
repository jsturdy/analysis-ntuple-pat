//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef DiJetStudy_h
#define DiJetStudy_h

#include "../../common/ntupleAnalysisPAT.h"

class DiJetStudy : public ntupleAnalysisPAT {
 public :
  
  DiJetStudy(TTree *allTree=0,
	     //TTree *eventTree=0,
	     TTree *jetTree=0,
	     TTree *metTree=0, 
	     TTree *leptonTree=0,
	     TTree *photonTree=0, 
	     TTree *triggerTree=0,
	     TTree *vertexTree=0, 
	     TTree *genTree=0,
	     std::string* sampleList=0,
	     std::string* triggerList=0,
	     std::string* cutFile=0,
	     const bool &isData=false,
	     const std::string &jetPrefix="PF2PAT",
	     const std::string &metPrefix="PFTypeI",
	     const std::string &lepPrefix="PF",
	     const std::string &phtPrefix="",
	     const std::string &sampleKey="");
  
  virtual ~DiJetStudy();
  
  virtual void     Loop(const std::string &outfilename="outfile.root",
			const double &cutJet1=100.,
			const double &cutJet2=100.,
			const double &cutMET=200.,
			const bool   &debug=false);

  /*
    virtual void     Loop(std::string outfilename="outfile.root",
    double lum=35.,
    double xs=1.,
    double eff=1.,
    double numGen=1.,
    double cutJet1=100.,
    double cutJet2=100.,
    double cutMET=200.);
    virtual void     Loop(const std::string &outfilename="outfile.root",
    const double lum=35.,
    const double scale=1.,
    const double &cutJet1=100.,
    const double &cutJet2=100.,
    const double &cutMET=200.);
  */

  void setCuts();
  void initializeTree();

  //methods for the analysis loop:
  void getTriggerInfo();
  void getJetInfo(const int& nJets);
  void getMETInfo();
  void getLeptonInfo(const int& nElecs, const int& nMuons, const int& nTaus );
  void getPhotonInfo(const int& nPhots);
  void getHTMHTInfo();
  void getVertexInfo(const int& nVtxs);
  void getSelectionInfo(const int& nJets);

  //print out the event information for events that pass our cuts
  //if the event is real data, print out extra information
  void printOutEventInfo();

  //DiJet specific variables
  double jet1_minpt;
  double jet1_maxeta;
  double jet2_minpt;
  double jet2_maxeta;

  double jetall_minpt;
  double jetall_maxpt;
  double jetall_maxeta;
    
  double ht_jet_minpt;
  double ht_jet_maxeta;
  double mht_jet_minpt;
  double mht_jet_maxeta;
    
  int cut_njet;
  double cut_met;
  
  double cut_jet12dphi;
  double cut_jet1metdphi;
  double cut_jet2metdphi;
  double cut_minjetmetdphi;
  
  TTree* dijetVariables;

  //Variables to be stored in mini ntuple
  //Event Information
  int mRun, mLS, mEvent;
  double mScaleFactor;

  double mSusyScanA0, mSusyScanM0, mSusyScanM12, 
    mSusyScanMu, mSusyScanRun,
    mSusyScantanbeta, mSusyScanCrossSection;
  
  //General Vars
  double mHT, mMHT, mMHTphi, mMeff, mDPhiStar,
    mIDHT, mIDMHT, mIDMHTphi, mIDMeff, mIDDPhiStar,

    mMET, mMETphi, mMETx, mMETy,
    mRawMET, //mRawMETx, mRawMETy,
    mSumEt, mRawSumEt,
    mSigMET,

    mMinvJet1Jet2,  mMinvJet1Jet3,  mMinvJet2Jet3,  mMinvJet1Jet2Jet3,
    mMTJet1Jet2,    mMTJet1Jet3,    mMTJet2Jet3,    mMTJet1Jet2Jet3,
    mMTJet1Jet2MET, mMTJet1Jet3MET, mMTJet2Jet3MET, mMTJet1Jet2Jet3MET;

  //Jet Vars
  int mNJets,     mNJets10,     mNJets30,     mNJets50;
  int mNGoodJets, mNGoodJets10, mNGoodJets30, mNGoodJets50;
  int mNBadJets,  mNBadJets10,  mNBadJets30,  mNBadJets50;
  
  double mJet1METDphi, mJet2METDphi, mMinJetMETDphi,
    mJet1Jet2Dphi, mJet1Jet3Dphi, mJet2Jet3Dphi;
  double mR1, mR2;
  double mJet1Jet2DR, mJet1Jet3DR, mJet2Jet3DR;
  double mJet1Jet2DpT, mJet1Jet3DpT, mJet2Jet3DpT;
  
  double mJet1pT, mJet1en, mJet1eta, mJet1phi, mJet1ssvhe, mJet1ssvhp;
  double mJet2pT, mJet2en, mJet2eta, mJet2phi, mJet2ssvhe, mJet2ssvhp;
  double mJet3pT, mJet3en, mJet3eta, mJet3phi, mJet3ssvhe, mJet3ssvhp;
  double mJet4pT, mJet4en, mJet4eta, mJet4phi, mJet4ssvhe, mJet4ssvhp;
  
  bool mJet1ID, mJet2ID, mJet3ID, mJet4ID;

  int mNbJets;
  double mbJet1pT, mbJet1en, mbJet1eta, mbJet1phi, mbJet1ssvhe, mbJet1ssvhp;
  double mbJet2pT, mbJet2en, mbJet2eta, mbJet2phi, mbJet2ssvhe, mbJet2ssvhp;
  double mbJet3pT, mbJet3en, mbJet3eta, mbJet3phi, mbJet3ssvhe, mbJet3ssvhp;
  bool mbJet1ID, mbJet2ID, mbJet3ID;

  //Lepton Vars
  int mNElec,     mNPhot,     mNMuon,     mNTau;
  int mNGoodElec, mNGoodPhot, mNGoodMuon;

  int mNElec10, mNPhot10, mNMuon10, mNTau10;
  int mNElec15, mNPhot15, mNMuon15, mNTau15;
  int mNElec25, mNPhot25, mNMuon25, mNTau25;

  //Vertex information
  int mNPV, mPVNTrks;
  double mPVSumTrkPt;

  //event counters
  int mTotalEvents;//, mPSEvents, mTriggerEvents, mPVEvents, 
  //mDiJetEvents, mLeptonEvents, mDPhiEvents, mMETEvents;

  //trigger results
  
  int Prescale_CentralJet80_MET65;
  int Prescale_CentralJet80_MET80;
  int Prescale_CentralJet80_MET100;
  int Prescale_CentralJet80_MET160;
  int PrescaleMC_MET65_CenJet50U;
  int PrescaleMC_MET80_CenJet50U;

  int Prescale_DiJet60_MET45;
  int Prescale_DiJetAve100U;
  int Prescale_DiJetAve140U;
  int Prescale_DiJetAve180U;
  int Prescale_DiJetAve300U;

  int Prescale_HT250_MHT60;
  int Prescale_HT300_MHT75;

  int Prescale_HT300;
  int Prescale_HT350;
  int Prescale_HT360;
  int Prescale_HT400;
  int Prescale_HT440;
  int Prescale_HT450;
  int Prescale_HT500;
  int Prescale_HT520;
  int Prescale_HT550;

  int Prescale_Jet110;
  int Prescale_Jet150;
  int Prescale_Jet190;
  int Prescale_Jet240;
  int Prescale_Jet370;

  int Prescale_MET100;
  int Prescale_MET120;
  int Prescale_MET200;
  int Prescale_PFMHT150;

  int Prescale_IsoMu12;
  int Prescale_Mu15;
  int Prescale_Mu20;

  int Prescale_Ele27;
  int Prescale_Ele32;
  int Prescale_Ele45;

  int Prescale_PhotonIso50;
  int Prescale_PhotonIso75;
  int Prescale_Photon75;
  int PrescaleMC_Photon70;

  int Prescale_Photon60HT200;
  int Prescale_Photon70HT200;
  int Prescale_Photon70HT300;
  int Prescale_Photon70MHT30;
  int Prescale_Photon70MHT50;

  
  bool HLT_CentralJet80_MET65;
  bool HLT_CentralJet80_MET80;
  bool HLT_CentralJet80_MET100;
  bool HLT_CentralJet80_MET160;
  bool HLTMC_MET65_CenJet50U;
  bool HLTMC_MET80_CenJet50U;

  bool HLT_DiJet60_MET45;
  bool HLT_DiJetAve100U;
  bool HLT_DiJetAve140U;
  bool HLT_DiJetAve180U;
  bool HLT_DiJetAve300U;

  bool HLT_HT250_MHT60;
  bool HLT_HT300_MHT75;

  bool HLT_HT300;
  bool HLT_HT350;
  bool HLT_HT360;
  bool HLT_HT400;
  bool HLT_HT440;
  bool HLT_HT450;
  bool HLT_HT500;
  bool HLT_HT520;
  bool HLT_HT550;

  bool HLT_Jet110;
  bool HLT_Jet150;
  bool HLT_Jet190;
  bool HLT_Jet240;
  bool HLT_Jet370;

  bool HLT_MET100;
  bool HLT_MET120;
  bool HLT_MET200;
  bool HLT_PFMHT150;


  bool HLT_IsoMu12;
  bool HLT_Mu15;
  bool HLT_Mu20;

  bool HLT_Ele27;
  bool HLT_Ele32;
  bool HLT_Ele45;

  bool HLT_PhotonIso50;
  bool HLT_PhotonIso75;
  bool HLT_Photon75;
  bool HLTMC_Photon70;

  bool HLT_Photon60HT200;
  bool HLT_Photon70HT200;
  bool HLT_Photon70HT300;
  bool HLT_Photon70MHT30;
  bool HLT_Photon70MHT50;


  
  //cuts
  bool passPS, passTriggers, passDiJetTrigger,
    passJetTrigger, passMETTrigger, passPV,
    passElectronVeto, passMuonVeto, passDLV, 
    passJet1DPhi, passJet2DPhi, passJet1Jet2DPhi,
    passMinJetDPhi, passDPhi, passMET, 
    passExclusiveAllButDLVDPhiMET, passExclusiveAllButDPhiMET, passExclusiveAllButMET, 
    passInclusiveAllButDLVDPhiMET, passInclusiveAllButDPhiMET, passInclusiveAllButMET, 
    passNJets, passExclusiveDiJets, passInclusiveDiJets, 
    passThirdJetVeto, passJetIDRejection,
    passJet1Pt, passJet1Eta, passJet1ID,
    passJet2Pt, passJet2Eta, passJet2ID;
  ;
};

#endif

#ifdef DiJetStudy_cxx

void DiJetStudy::setCuts() {
  //Would like to pass these in via a cut file or similar
  jet1_minpt    = 150.;//100
  jet1_maxeta   = 2.5;

  jet2_minpt    = 150.;//100
  jet2_maxeta   = 2.5;

  jetall_minpt  = 30.;
  jetall_maxeta = 5.0;
  jetall_maxpt  = 50.;

  ht_jet_minpt  = 50;
  ht_jet_maxeta = 3.0;

  mht_jet_minpt  = 30;
  mht_jet_maxeta = 5.0;

  cut_njet = 2;
  cut_met  = 250.;//325

  //To be fixed
  cut_jet12dphi     = -1.;
  cut_jet1metdphi   = 1.0;
  cut_jet2metdphi   = 1.0;
  cut_minjetmetdphi = 0.3;
  
}

void DiJetStudy::initializeTree() {
  dijetVariables = new TTree("dijetVariables", "secondary ntuple with dijet variables");

  dijetVariables->Branch("Run",         &mRun,        "mRun/I");
  dijetVariables->Branch("LS",          &mLS,         "mLS/I");
  dijetVariables->Branch("Event",       &mEvent,      "mEvent/I");
  dijetVariables->Branch("ScaleFactor", &mScaleFactor,"mScaleFactor/D");

  dijetVariables->Branch("SusyScanA0",           &mSusyScanA0          ,"mSusyScanA0/D");
  dijetVariables->Branch("SusyScanM0",           &mSusyScanM0          ,"mSusyScanM0/D");
  dijetVariables->Branch("SusyScanM12",          &mSusyScanM12         ,"mSusyScanM12/D");
  dijetVariables->Branch("SusyScanMu",           &mSusyScanMu          ,"mSusyScanMu/D");
  dijetVariables->Branch("SusyScanRun",          &mSusyScanRun         ,"mSusyScanRun/D");
  dijetVariables->Branch("SusyScantanbeta",      &mSusyScantanbeta     ,"mSusyScantanbeta/D");
  dijetVariables->Branch("SusyScanCrossSection", &mSusyScanCrossSection,"mSusyScanCrossSection/D");
  
  dijetVariables->Branch("HT",       &mHT,       "mHT/D");
  dijetVariables->Branch("MHT",      &mMHT,      "mMHT/D");
  dijetVariables->Branch("MHTphi",   &mMHTphi,   "mMHTphi/D");
  dijetVariables->Branch("Meff",     &mMeff,     "mMeff/D");
  dijetVariables->Branch("dPhiStar", &mDPhiStar, "mDPhiStar/D");

  dijetVariables->Branch("HT_JetID",       &mIDHT,       "mIDHT/D");
  dijetVariables->Branch("MHT_JetID",      &mIDMHT,      "mIDMHT/D");
  dijetVariables->Branch("MHTphi_JetID",   &mIDMHTphi,   "mIDMHTphi/D");
  dijetVariables->Branch("Meff_JetID",     &mIDMeff,     "mIDMeff/D");
  dijetVariables->Branch("dPhiStar_JetID", &mIDDPhiStar, "mIDDPhiStar/D");

  dijetVariables->Branch("MET",      &mMET,      "mMET/D");
  dijetVariables->Branch("METphi",   &mMETphi,   "mMETphi/D");
  dijetVariables->Branch("METx",     &mMETx,     "mMETx/D");
  dijetVariables->Branch("METy",     &mMETy,     "mMETy/D");
  dijetVariables->Branch("RawMET",   &mRawMET,   "mRawMET/D");
  dijetVariables->Branch("SumEt",    &mSumEt,    "mSumEt/D");
  dijetVariables->Branch("RawSumEt", &mRawSumEt, "mRawSumEt/D");
  dijetVariables->Branch("SigMET",    &mSigMET,    "mSigMET/D");

  dijetVariables->Branch("MinvJet1Jet2",     &mMinvJet1Jet2,     "mMinvJet1Jet2/D");
  dijetVariables->Branch("MinvJet1Jet3",     &mMinvJet1Jet3,     "mMinvJet1Jet3/D");
  dijetVariables->Branch("MinvJet2Jet3",     &mMinvJet2Jet3,     "mMinvJet2Jet3/D");
  dijetVariables->Branch("MinvJet1Jet2Jet3", &mMinvJet1Jet2Jet3, "mMinvJet1Jet2Jet3/D");

  dijetVariables->Branch("MTJet1Jet2",     &mMTJet1Jet2,     "mMTJet1Jet2/D");
  dijetVariables->Branch("MTJet1Jet3",     &mMTJet1Jet3,     "mMTJet1Jet3/D");
  dijetVariables->Branch("MTJet2Jet3",     &mMTJet2Jet3,     "mMTJet2Jet3/D");
  dijetVariables->Branch("MTJet1Jet2Jet3", &mMTJet1Jet2Jet3, "mMTJet1Jet2Jet3/D");

  dijetVariables->Branch("MTJet1Jet2MET",     &mMTJet1Jet2MET,     "mMTJet1Jet2MET/D");
  dijetVariables->Branch("MTJet1Jet3MET",     &mMTJet1Jet3MET,     "mMTJet1Jet3MET/D");
  dijetVariables->Branch("MTJet2Jet3MET",     &mMTJet2Jet3MET,     "mMTJet2Jet3MET/D");
  dijetVariables->Branch("MTJet1Jet2Jet3MET", &mMTJet1Jet2Jet3MET, "mMTJet1Jet2Jet3MET/D");

  dijetVariables->Branch("NJets",   &mNJets,   "mNJets/I");
  dijetVariables->Branch("NJets10", &mNJets10, "mNJets10/I");
  dijetVariables->Branch("NJets30", &mNJets30, "mNJets30/I");
  dijetVariables->Branch("NJets50", &mNJets50, "mNJets50/I");

  dijetVariables->Branch("NGoodJets",   &mNGoodJets,   "mNGoodJets/I");
  dijetVariables->Branch("NGoodJets10", &mNGoodJets10, "mNGoodJets10/I");
  dijetVariables->Branch("NGoodJets30", &mNGoodJets30, "mNGoodJets30/I");
  dijetVariables->Branch("NGoodJets50", &mNGoodJets50, "mNGoodJets50/I");

  dijetVariables->Branch("NBadJets",   &mNBadJets,   "mNBadJets/I");
  dijetVariables->Branch("NBadJets10", &mNBadJets10, "mNBadJets10/I");
  dijetVariables->Branch("NBadJets30", &mNBadJets30, "mNBadJets30/I");
  dijetVariables->Branch("NBadJets50", &mNBadJets50, "mNBadJets50/I");

  dijetVariables->Branch("Jet1METDphi",   &mJet1METDphi,   "mJet1METDphi/D");
  dijetVariables->Branch("Jet2METDphi",   &mJet2METDphi,   "mJet2METDphi/D");
  dijetVariables->Branch("MinJetMETDphi", &mMinJetMETDphi, "mMinJetMETDphi/D");

  dijetVariables->Branch("Jet1Jet2Dphi",   &mJet1Jet2Dphi,   "mJet1Jet2Dphi/D");
  dijetVariables->Branch("Jet1Jet3Dphi",   &mJet1Jet3Dphi,   "mJet1Jet3Dphi/D");
  dijetVariables->Branch("Jet2Jet3Dphi",   &mJet2Jet3Dphi,   "mJet2Jet3Dphi/D");

  dijetVariables->Branch("R1",   &mR1,   "mR1/D");
  dijetVariables->Branch("R2",   &mR2,   "mR2/D");

  dijetVariables->Branch("Jet1Jet2DR",   &mJet1Jet2DR,   "mJet1Jet2DR/D");
  dijetVariables->Branch("Jet1Jet3DR",   &mJet1Jet3DR,   "mJet1Jet3DR/D");
  dijetVariables->Branch("Jet2Jet3DR",   &mJet2Jet3DR,   "mJet2Jet3DR/D");

  dijetVariables->Branch("Jet1Jet2DpT",   &mJet1Jet2DpT,   "mJet1Jet2DpT/D");
  dijetVariables->Branch("Jet1Jet3DpT",   &mJet1Jet3DpT,   "mJet1Jet3DpT/D");
  dijetVariables->Branch("Jet2Jet3DpT",   &mJet2Jet3DpT,   "mJet2Jet3DpT/D");

  ///Jet variables for leading 4 jets
  dijetVariables->Branch("Jet1pT",    &mJet1pT,    "mJet1pT/D");
  dijetVariables->Branch("Jet1en",    &mJet1en,    "mJet1en/D");
  dijetVariables->Branch("Jet1eta",   &mJet1eta,   "mJet1eta/D");
  dijetVariables->Branch("Jet1phi",   &mJet1phi,   "mJet1phi/D");
  dijetVariables->Branch("Jet1ssvhe", &mJet1ssvhe, "mJet1ssvhe/D");
  dijetVariables->Branch("Jet1ssvhp", &mJet1ssvhp, "mJet1ssvhp/D");
  dijetVariables->Branch("Jet1ID",    &mJet1ID,    "mJet1ID/B");

  dijetVariables->Branch("Jet2pT",    &mJet2pT,    "mJet2pT/D");
  dijetVariables->Branch("Jet2en",    &mJet2en,    "mJet2en/D");
  dijetVariables->Branch("Jet2eta",   &mJet2eta,   "mJet2eta/D");
  dijetVariables->Branch("Jet2phi",   &mJet2phi,   "mJet2phi/D");
  dijetVariables->Branch("Jet2ssvhe", &mJet2ssvhe, "mJet2ssvhe/D");
  dijetVariables->Branch("Jet2ssvhp", &mJet2ssvhp, "mJet2ssvhp/D");
  dijetVariables->Branch("Jet2ID",    &mJet2ID,    "mJet2ID/B");

  dijetVariables->Branch("Jet3pT",    &mJet3pT,    "mJet3pT/D");
  dijetVariables->Branch("Jet3en",    &mJet3en,    "mJet3en/D");
  dijetVariables->Branch("Jet3eta",   &mJet3eta,   "mJet3eta/D");
  dijetVariables->Branch("Jet3phi",   &mJet3phi,   "mJet3phi/D");
  dijetVariables->Branch("Jet3ssvhe", &mJet3ssvhe, "mJet3ssvhe/D");
  dijetVariables->Branch("Jet3ssvhp", &mJet3ssvhp, "mJet3ssvhp/D");
  dijetVariables->Branch("Jet3ID",    &mJet3ID,    "mJet3ID/B");

  dijetVariables->Branch("Jet4pT",    &mJet4pT,    "mJet4pT/D");
  dijetVariables->Branch("Jet4en",    &mJet4en,    "mJet4en/D");
  dijetVariables->Branch("Jet4eta",   &mJet4eta,   "mJet4eta/D");
  dijetVariables->Branch("Jet4phi",   &mJet4phi,   "mJet4phi/D");
  dijetVariables->Branch("Jet4ssvhe", &mJet4ssvhe, "mJet4ssvhe/D");
  dijetVariables->Branch("Jet4ssvhp", &mJet4ssvhp, "mJet4ssvhp/D");
  dijetVariables->Branch("Jet4ID",    &mJet4ID,    "mJet4ID/B");

  //bjets
  dijetVariables->Branch("NbJets",     &mNbJets,     "mNbJets/I");
  dijetVariables->Branch("bJet1pT",    &mbJet1pT,    "mbJet1pT/D");
  dijetVariables->Branch("bJet1en",    &mbJet1en,    "mbJet1en/D");
  dijetVariables->Branch("bJet1eta",   &mbJet1eta,   "mbJet1eta/D");
  dijetVariables->Branch("bJet1phi",   &mbJet1phi,   "mbJet1phi/D");
  dijetVariables->Branch("bJet1ssvhe", &mbJet1ssvhe, "mbJet1ssvhe/D");
  dijetVariables->Branch("bJet1ssvhp", &mbJet1ssvhp, "mbJet1ssvhp/D");
  dijetVariables->Branch("bJet1ID",    &mbJet1ID,    "mbJet1ID/B");

  dijetVariables->Branch("bJet2pT",    &mbJet2pT,    "mbJet2pT/D");
  dijetVariables->Branch("bJet2en",    &mbJet2en,    "mbJet2en/D");
  dijetVariables->Branch("bJet2eta",   &mbJet2eta,   "mbJet2eta/D");
  dijetVariables->Branch("bJet2phi",   &mbJet2phi,   "mbJet2phi/D");
  dijetVariables->Branch("bJet2ssvhe", &mbJet2ssvhe, "mbJet2ssvhe/D");
  dijetVariables->Branch("bJet2ssvhp", &mbJet2ssvhp, "mbJet2ssvhp/D");
  dijetVariables->Branch("bJet2ID",    &mbJet2ID,    "mbJet2ID/B");

  dijetVariables->Branch("bJet3pT",    &mbJet3pT,    "mbJet3pT/D");
  dijetVariables->Branch("bJet3en",    &mbJet3en,    "mbJet3en/D");
  dijetVariables->Branch("bJet3eta",   &mbJet3eta,   "mbJet3eta/D");
  dijetVariables->Branch("bJet3phi",   &mbJet3phi,   "mbJet3phi/D");
  dijetVariables->Branch("bJet3ssvhe", &mbJet3ssvhe, "mbJet3ssvhe/D");
  dijetVariables->Branch("bJet3ssvhp", &mbJet3ssvhp, "mbJet3ssvhp/D");
  dijetVariables->Branch("bJet3ID",    &mbJet3ID,    "mbJet3ID/B");


  ///lepton and photon counters
  dijetVariables->Branch("NElec",     &mNElec,     "mNElec/I");
  dijetVariables->Branch("NGoodElec", &mNGoodElec, "mNGoodElec/I");
  dijetVariables->Branch("NElec10",   &mNElec10,   "mNElec10/I");
  dijetVariables->Branch("NElec15",   &mNElec15,   "mNElec15/I");
  dijetVariables->Branch("NElec25",   &mNElec25,   "mNElec25/I");

  dijetVariables->Branch("NMuon",     &mNMuon,     "mNMuon/I");
  dijetVariables->Branch("NGoodMuon", &mNGoodMuon, "mNGoodMuon/I");
  dijetVariables->Branch("NMuon10",   &mNMuon10,   "mNMuon10/I");
  dijetVariables->Branch("NMuon15",   &mNMuon15,   "mNMuon15/I");
  dijetVariables->Branch("NMuon25",   &mNMuon25,   "mNMuon25/I");

  dijetVariables->Branch("NTau",     &mNTau,     "mNTau/I");
  dijetVariables->Branch("NTau10",   &mNTau10,   "mNTau10/I");
  dijetVariables->Branch("NTau15",   &mNTau15,   "mNTau15/I");
  dijetVariables->Branch("NTau25",   &mNTau25,   "mNTau25/I");

  dijetVariables->Branch("NPhot",     &mNPhot,     "mNPhot/I");
  dijetVariables->Branch("NGoodPhot", &mNGoodPhot, "mNGoodPhot/I");
  dijetVariables->Branch("NPhot10",   &mNPhot10,   "mNPhot10/I");
  dijetVariables->Branch("NPhot15",   &mNPhot15,   "mNPhot15/I");
  dijetVariables->Branch("NPhot25",   &mNPhot25,   "mNPhot25/I");

  ///vertex information
  dijetVariables->Branch("NPV",        &mNPV,        "mNPV/I");
  dijetVariables->Branch("PVNTrks",    &mPVNTrks,    "mPVNTrks/I");
  dijetVariables->Branch("PVSumTrkPt", &mPVSumTrkPt, "mPVSumTrkPt/D");

  //Trigger bits
  dijetVariables->Branch("prescale_CentralJet80_MET65",  &Prescale_CentralJet80_MET65,  "prescale_CentralJet80_MET65/I");
  dijetVariables->Branch("prescale_CentralJet80_MET80",  &Prescale_CentralJet80_MET80,  "prescale_CentralJet80_MET80/I");
  dijetVariables->Branch("prescale_CentralJet80_MET100", &Prescale_CentralJet80_MET100, "prescale_CentralJet80_MET100/I");
  dijetVariables->Branch("prescale_CentralJet80_MET160", &Prescale_CentralJet80_MET160, "prescale_CentralJet80_MET160/I");

  dijetVariables->Branch("prescaleMC_MET65_CenJet50U", &PrescaleMC_MET65_CenJet50U, "prescaleMC_MET65_CenJet50U/I");
  dijetVariables->Branch("prescaleMC_MET80_CenJet50U", &PrescaleMC_MET80_CenJet50U, "prescaleMC_MET80_CenJet50U/I");

  dijetVariables->Branch("prescale_DiJet60_MET45", &Prescale_DiJet60_MET45, "prescale_DiJet60_MET45/I");
  dijetVariables->Branch("prescale_DiJetAve100U",  &Prescale_DiJetAve100U,  "prescale_DiJetAve100U/I"); 
  dijetVariables->Branch("prescale_DiJetAve140U",  &Prescale_DiJetAve140U,  "prescale_DiJetAve140U/I"); 
  dijetVariables->Branch("prescale_DiJetAve180U",  &Prescale_DiJetAve180U,  "prescale_DiJetAve180U/I"); 
  dijetVariables->Branch("prescale_DiJetAve300U",  &Prescale_DiJetAve300U,  "prescale_DiJetAve300U/I"); 

  dijetVariables->Branch("prescale_HT250_MHT60",	  &Prescale_HT250_MHT60,   "prescale_HT250_MHT60/I");  
  dijetVariables->Branch("prescale_HT300_MHT75",	  &Prescale_HT300_MHT75,   "prescale_HT300_MHT75/I");  

  dijetVariables->Branch("prescale_HT300",	  &Prescale_HT300,         "prescale_HT300/I");        
  dijetVariables->Branch("prescale_HT350",	  &Prescale_HT350,         "prescale_HT350/I");        
  dijetVariables->Branch("prescale_HT360",	  &Prescale_HT360,         "prescale_HT360/I");        
  dijetVariables->Branch("prescale_HT400",	  &Prescale_HT400,         "prescale_HT400/I");        
  dijetVariables->Branch("prescale_HT440",	  &Prescale_HT440,         "prescale_HT440/I");        
  dijetVariables->Branch("prescale_HT450",	  &Prescale_HT450,         "prescale_HT450/I");        
  dijetVariables->Branch("prescale_HT500",	  &Prescale_HT500,         "prescale_HT500/I");        
  dijetVariables->Branch("prescale_HT520",	  &Prescale_HT520,         "prescale_HT520/I");        
  dijetVariables->Branch("prescale_HT550",	  &Prescale_HT550,         "prescale_HT550/I");        

  dijetVariables->Branch("prescale_Jet110",	  &Prescale_Jet110,        "prescale_Jet110/I");       
  dijetVariables->Branch("prescale_Jet150",	  &Prescale_Jet150,        "prescale_Jet150/I");       
  dijetVariables->Branch("prescale_Jet190",	  &Prescale_Jet190,        "prescale_Jet190/I");       
  dijetVariables->Branch("prescale_Jet240",	  &Prescale_Jet240,        "prescale_Jet240/I");       
  dijetVariables->Branch("prescale_Jet370",	  &Prescale_Jet370,        "prescale_Jet370/I");       

  dijetVariables->Branch("prescale_MET100",	  &Prescale_MET100,        "prescale_MET100/I");       
  dijetVariables->Branch("prescale_MET120",	  &Prescale_MET120,        "prescale_MET120/I");       
  dijetVariables->Branch("prescale_MET200",	  &Prescale_MET200,        "prescale_MET200/I");       
  dijetVariables->Branch("prescale_PFMHT150",     &Prescale_PFMHT150,      "prescale_PFMHT150/I");     
 
  dijetVariables->Branch("prescale_IsoMu12" , &Prescale_IsoMu12 , "prescale_IsoMu12/I" );
  dijetVariables->Branch("prescale_Mu15"    , &Prescale_Mu15    , "prescale_Mu15/I"    );
  dijetVariables->Branch("prescale_Mu20"    , &Prescale_Mu20    , "prescale_Mu20/I"    );

  dijetVariables->Branch("prescale_Ele27"   , &Prescale_Ele27   , "prescale_Ele27/I"   );
  dijetVariables->Branch("prescale_Ele32"   , &Prescale_Ele32   , "prescale_Ele32/I"   );
  dijetVariables->Branch("prescale_Ele45"   , &Prescale_Ele45   , "prescale_Ele45/I"   );

  dijetVariables->Branch("prescale_PhotonIso50", &Prescale_PhotonIso50,  "prescale_PhotonIso50/I");
  dijetVariables->Branch("prescale_PhotonIso75", &Prescale_PhotonIso75,  "prescale_PhotonIso75/I");
  dijetVariables->Branch("prescale_Photon75",    &Prescale_Photon75,     "prescale_Photon75/I");
  dijetVariables->Branch("prescaleMC_Photon70",    &PrescaleMC_Photon70,     "prescaleMC_Photon70/I");

  dijetVariables->Branch("prescale_Photon60HT200", &Prescale_Photon60HT200,  "prescale_Photon60HT200/I");
  dijetVariables->Branch("prescale_Photon70HT200", &Prescale_Photon70HT200,  "prescale_Photon70HT200/I");
  dijetVariables->Branch("prescale_Photon70HT300", &Prescale_Photon70HT300,  "prescale_Photon70HT300/I");
  dijetVariables->Branch("prescale_Photon70MHT30", &Prescale_Photon70MHT30,  "prescale_Photon70MHT30/I");
  dijetVariables->Branch("prescale_Photon70MHT50", &Prescale_Photon70MHT50,  "prescale_Photon70MHT50/I");

  //Trigger bits
  dijetVariables->Branch("passHLT_CentralJet80_MET65",  &HLT_CentralJet80_MET65,  "passHLT_CentralJet80_MET65/B");
  dijetVariables->Branch("passHLT_CentralJet80_MET80",  &HLT_CentralJet80_MET80,  "passHLT_CentralJet80_MET80/B");
  dijetVariables->Branch("passHLT_CentralJet80_MET100", &HLT_CentralJet80_MET100, "passHLT_CentralJet80_MET100/B");
  dijetVariables->Branch("passHLT_CentralJet80_MET160", &HLT_CentralJet80_MET160, "passHLT_CentralJet80_MET160/B");

  dijetVariables->Branch("passHLTMC_MET65_CenJet50U", &HLTMC_MET65_CenJet50U, "passHLTMC_MET65_CenJet50U/B");
  dijetVariables->Branch("passHLTMC_MET80_CenJet50U", &HLTMC_MET80_CenJet50U, "passHLTMC_MET80_CenJet50U/B");

  dijetVariables->Branch("passHLT_DiJet60_MET45", &HLT_DiJet60_MET45, "passHLT_DiJet60_MET45/B");
  dijetVariables->Branch("passHLT_DiJetAve100U",  &HLT_DiJetAve100U,  "passHLT_DiJetAve100U/B"); 
  dijetVariables->Branch("passHLT_DiJetAve140U",  &HLT_DiJetAve140U,  "passHLT_DiJetAve140U/B"); 
  dijetVariables->Branch("passHLT_DiJetAve180U",  &HLT_DiJetAve180U,  "passHLT_DiJetAve180U/B"); 
  dijetVariables->Branch("passHLT_DiJetAve300U",  &HLT_DiJetAve300U,  "passHLT_DiJetAve300U/B"); 

  dijetVariables->Branch("passHLT_HT250_MHT60",	  &HLT_HT250_MHT60,   "passHLT_HT250_MHT60/B");  
  dijetVariables->Branch("passHLT_HT300_MHT75",	  &HLT_HT300_MHT75,   "passHLT_HT300_MHT75/B");  

  dijetVariables->Branch("passHLT_HT300",	  &HLT_HT300,         "passHLT_HT300/B");        
  dijetVariables->Branch("passHLT_HT350",	  &HLT_HT350,         "passHLT_HT350/B");        
  dijetVariables->Branch("passHLT_HT360",	  &HLT_HT360,         "passHLT_HT360/B");        
  dijetVariables->Branch("passHLT_HT400",	  &HLT_HT400,         "passHLT_HT400/B");        
  dijetVariables->Branch("passHLT_HT440",	  &HLT_HT440,         "passHLT_HT440/B");        
  dijetVariables->Branch("passHLT_HT450",	  &HLT_HT450,         "passHLT_HT450/B");        
  dijetVariables->Branch("passHLT_HT500",	  &HLT_HT500,         "passHLT_HT500/B");        
  dijetVariables->Branch("passHLT_HT520",	  &HLT_HT520,         "passHLT_HT520/B");        
  dijetVariables->Branch("passHLT_HT550",	  &HLT_HT550,         "passHLT_HT550/B");        

  dijetVariables->Branch("passHLT_Jet110",	  &HLT_Jet110,        "passHLT_Jet110/B");       
  dijetVariables->Branch("passHLT_Jet150",	  &HLT_Jet150,        "passHLT_Jet150/B");       
  dijetVariables->Branch("passHLT_Jet190",	  &HLT_Jet190,        "passHLT_Jet190/B");       
  dijetVariables->Branch("passHLT_Jet240",	  &HLT_Jet240,        "passHLT_Jet240/B");       
  dijetVariables->Branch("passHLT_Jet370",	  &HLT_Jet370,        "passHLT_Jet370/B");       

  dijetVariables->Branch("passHLT_MET100",	  &HLT_MET100,        "passHLT_MET100/B");       
  dijetVariables->Branch("passHLT_MET120",	  &HLT_MET120,        "passHLT_MET120/B");       
  dijetVariables->Branch("passHLT_MET200",	  &HLT_MET200,        "passHLT_MET200/B");       
  dijetVariables->Branch("passHLT_PFMHT150",	  &HLT_PFMHT150,      "passHLT_PFMHT150/B");     
  
  dijetVariables->Branch("passHLT_IsoMu12" , &HLT_IsoMu12 , "passHLT_IsoMu12/B" );
  dijetVariables->Branch("passHLT_Mu15"    , &HLT_Mu15    , "passHLT_Mu15/B"    );
  dijetVariables->Branch("passHLT_Mu20"    , &HLT_Mu20    , "passHLT_Mu20/B"    );

  dijetVariables->Branch("passHLT_Ele27"   , &HLT_Ele27   , "passHLT_Ele27/B"   );
  dijetVariables->Branch("passHLT_Ele32"   , &HLT_Ele32   , "passHLT_Ele32/B"   );
  dijetVariables->Branch("passHLT_Ele45"   , &HLT_Ele45   , "passHLT_Ele45/B"   );

  dijetVariables->Branch("passHLT_PhotonIso50", &HLT_PhotonIso50,  "passHLT_PhotonIso50/B");
  dijetVariables->Branch("passHLT_PhotonIso75", &HLT_PhotonIso75,  "passHLT_PhotonIso75/B");
  dijetVariables->Branch("passHLT_Photon75",    &HLT_Photon75,     "passHLT_Photon75/B");
  dijetVariables->Branch("passHLTMC_Photon70",    &HLTMC_Photon70,     "passHLTMC_Photon70/B");

  dijetVariables->Branch("passHLT_Photon60HT200", &HLT_Photon60HT200,  "passHLT_Photon60HT200/B");
  dijetVariables->Branch("passHLT_Photon70HT200", &HLT_Photon70HT200,  "passHLT_Photon70HT200/B");
  dijetVariables->Branch("passHLT_Photon70HT300", &HLT_Photon70HT300,  "passHLT_Photon70HT300/B");
  dijetVariables->Branch("passHLT_Photon70MHT30", &HLT_Photon70MHT30,  "passHLT_Photon70MHT30/B");
  dijetVariables->Branch("passHLT_Photon70MHT50", &HLT_Photon70MHT50,  "passHLT_Photon70MHT50/B");


 
  ////Boolean values
  dijetVariables->Branch("passPS", &passPS, "passPS/B");
  dijetVariables->Branch("passPV", &passPV, "passPV/B");

  dijetVariables->Branch("passTriggers",     &passTriggers,     "passTriggers/B");
  dijetVariables->Branch("passJetTrigger",   &passJetTrigger,   "passJetTrigger/B");
  dijetVariables->Branch("passMETTrigger",   &passMETTrigger,   "passMETTrigger/B");
  dijetVariables->Branch("passDiJetTrigger", &passDiJetTrigger, "passDiJetTrigger/B");

  dijetVariables->Branch("passJet1Pt",  &passJet1Pt,  "passJet1Pt/B");
  dijetVariables->Branch("passJet1Eta", &passJet1Eta, "passJet1Eta/B");
  dijetVariables->Branch("passJet1ID",  &passJet1ID,  "passJet1ID/B");

  dijetVariables->Branch("passJet2Pt",  &passJet2Pt,  "passJet2Pt/B");
  dijetVariables->Branch("passJet2Eta", &passJet2Eta, "passJet2Eta/B");
  dijetVariables->Branch("passJet2ID",  &passJet2ID,  "passJet2ID/B");

  dijetVariables->Branch("passNJets",           &passNJets,           "passNJets/B");
  dijetVariables->Branch("passThirdJetVeto",    &passThirdJetVeto,    "passJetVeto/B");
  dijetVariables->Branch("passExclusiveDiJets", &passExclusiveDiJets, "passExclusiveDiJets/B");
  dijetVariables->Branch("passInclusiveDiJets", &passInclusiveDiJets, "passInclusiveDiJets/B");
  dijetVariables->Branch("passJetIDRejection",  &passJetIDRejection,  "passJetIDRejection/B");

  dijetVariables->Branch("passElectronVeto", &passElectronVeto, "passElectronVeto/B");
  dijetVariables->Branch("passMuonVeto",     &passMuonVeto,     "passMuonVeto/B");
  dijetVariables->Branch("passDLV",          &passDLV,          "passDLV/B");

  dijetVariables->Branch("passJet1DPhi",     &passJet1DPhi,     "passJet1DPhi/B");
  dijetVariables->Branch("passJet2DPhi",     &passJet2DPhi,     "passJet2DPhi/B");
  dijetVariables->Branch("passJet1Jet2DPhi", &passJet1Jet2DPhi, "passJet1Jet2DPhi/B");
  dijetVariables->Branch("passMinJetDPhi",   &passMinJetDPhi,   "passMinJetDPhi/B");
  dijetVariables->Branch("passDPhi",         &passDPhi,         "passDPhi/B");

  dijetVariables->Branch("passMET", &passMET, "passMET/B");

  dijetVariables->Branch("passExclusiveAllButDLVDPhiMET", &passExclusiveAllButDLVDPhiMET, "passExclusiveAllButDLVDPhiMET/B");
  dijetVariables->Branch("passExclusiveAllButDPhiMET",    &passExclusiveAllButDPhiMET,    "passExclusiveAllButDPhiMET/B");
  dijetVariables->Branch("passExclusiveAllButMET",        &passExclusiveAllButMET,        "passExclusiveAllButMET/B");

  dijetVariables->Branch("passInclusiveAllButDLVDPhiMET", &passInclusiveAllButDLVDPhiMET, "passInclusiveAllButDLVDPhiMET/B");
  dijetVariables->Branch("passInclusiveAllButDPhiMET",    &passInclusiveAllButDPhiMET,    "passInclusiveAllButDPhiMET/B");
  dijetVariables->Branch("passInclusiveAllButMET",        &passInclusiveAllButMET,        "passInclusiveAllButMET/B");

}

//methods for the analysis loop:
/***************Triggers****************/
void DiJetStudy::getTriggerInfo() {
  using namespace std;
  //Trigger selection
  string dijetTriggerPath;
  string singlejetTriggerPath;
  string metTriggerPath;
    
  map<unsigned int, string>::iterator key = dijetTriggers.begin();
  //if (debug_)
  //  std::cout<<"Run: "<<mRun<<" searching for dijet trigger...";
  while (key != dijetTriggers.end() ) {
    // (debug_)
    //std::cout<<".";
    if (mRun < key->first) {
      dijetTriggerPath = key->second;
      //if (debug_)
      //  std::cout<<" found dijet trigger "<<dijetTriggerPath;
      break;
    }
    ++key;
  }
  //if (debug_)
  //  std::cout<<std::endl;

  key = singlejetTriggers.begin();
  while (key != singlejetTriggers.end() ) {
    if (mRun < key->first) {
      singlejetTriggerPath = key->second;
      break;
    }
    ++key;
  }
    
  key = metTriggers.begin();
  while (key != metTriggers.end() ) {
    if (mRun < key->first) {
      metTriggerPath = key->second;
      break;
    }
    ++key;
  }
    
  //if (debug_) cout<<"Using "<<dijetTriggerPath    <<" as the dijet trigger"    <<endl;
  //if (debug_) cout<<"Using "<<singlejetTriggerPath<<" as the singlejet trigger"<<endl;
  //if (debug_) cout<<"Using "<<metTriggerPath      <<" as the met trigger"      <<endl;

  passTriggers     = false;
  passDiJetTrigger = false;
  passJetTrigger   = false;
  passMETTrigger   = false;

  stringtobool::iterator trigbit = HLTTriggered->find(dijetTriggerPath);
    
  if (trigbit!=HLTTriggered->end()) {
    if (trigbit->second)
      passDiJetTrigger = true;
  }
  else
    std::cout<<"unable to find "<<dijetTriggerPath<<" in list of triggers"<<std::endl;
    
  trigbit = HLTTriggered->find(singlejetTriggerPath);
  if (trigbit!=HLTTriggered->end()) {
    if (trigbit->second)
      passJetTrigger = true;
  }
  else
    std::cout<<"unable to find "<<singlejetTriggerPath<<" in list of triggers"<<std::endl;
    
  trigbit = HLTTriggered->find(metTriggerPath);
  if (trigbit!=HLTTriggered->end()) {
    if (trigbit->second)
      passMETTrigger = true;
  }
  else
    std::cout<<"unable to find "<<metTriggerPath<<" in list of triggers"<<std::endl;
    
  passTriggers = passMETTrigger;


  //storing trigger results
  Prescale_CentralJet80_MET65  = -1;
  Prescale_CentralJet80_MET80  = -1;
  Prescale_CentralJet80_MET100 = -1;
  Prescale_CentralJet80_MET160 = -1;
    
  PrescaleMC_MET65_CenJet50U = -1;
  PrescaleMC_MET80_CenJet50U = -1;

  Prescale_DiJet60_MET45 = -1;
  Prescale_DiJetAve100U = -1;
  Prescale_DiJetAve140U = -1;
  Prescale_DiJetAve180U = -1;
  Prescale_DiJetAve300U = -1;

  Prescale_HT250_MHT60 = -1;
  Prescale_HT300_MHT75 = -1;

  Prescale_HT300 = -1;
  Prescale_HT350 = -1;
  Prescale_HT360 = -1;
  Prescale_HT400 = -1;
  Prescale_HT440 = -1;
  Prescale_HT450 = -1;
  Prescale_HT500 = -1;
  Prescale_HT520 = -1;
  Prescale_HT550 = -1;

  Prescale_Jet110 = -1;
  Prescale_Jet150 = -1;
  Prescale_Jet190 = -1;
  Prescale_Jet240 = -1;
  Prescale_Jet370 = -1;

  Prescale_MET100 = -1;
  Prescale_MET120 = -1;
  Prescale_MET200 = -1;
  Prescale_PFMHT150 = -1;

  Prescale_IsoMu12  = -1;
  Prescale_Mu15     = -1;
  Prescale_Mu20     = -1;

  Prescale_Ele27    = -1;
  Prescale_Ele32    = -1;
  Prescale_Ele45    = -1;

  Prescale_PhotonIso50 = -1;
  Prescale_PhotonIso75 = -1;
  Prescale_Photon75    = -1;
  PrescaleMC_Photon70  = -1;

  ////trigger results
  HLT_CentralJet80_MET65  = false;
  HLT_CentralJet80_MET80  = false;
  HLT_CentralJet80_MET100 = false;
  HLT_CentralJet80_MET160 = false;

  HLTMC_MET65_CenJet50U = false;
  HLTMC_MET80_CenJet50U = false;

  HLT_DiJet60_MET45 = false;
  HLT_DiJetAve100U = false;
  HLT_DiJetAve140U = false;
  HLT_DiJetAve180U = false;
  HLT_DiJetAve300U = false;

  HLT_HT250_MHT60 = false;
  HLT_HT300_MHT75 = false;

  HLT_HT300 = false;
  HLT_HT350 = false;
  HLT_HT360 = false;
  HLT_HT400 = false;
  HLT_HT440 = false;
  HLT_HT450 = false;
  HLT_HT500 = false;
  HLT_HT520 = false;
  HLT_HT550 = false;

  HLT_Jet110 = false;
  HLT_Jet150 = false;
  HLT_Jet190 = false;
  HLT_Jet240 = false;
  HLT_Jet370 = false;

  HLT_MET100 = false;
  HLT_MET120 = false;
  HLT_MET200 = false;
  HLT_PFMHT150 = false;

  HLT_IsoMu12  = false;
  HLT_Mu15     = false;
  HLT_Mu20     = false;

  HLT_Ele27    = false;
  HLT_Ele32    = false;
  HLT_Ele45    = false;

  HLT_PhotonIso50 = false;
  HLT_PhotonIso75 = false;
  HLT_Photon75    = false;
  HLTMC_Photon70  = false;

  trigbit = HLTTriggered->begin();
  stringtoint::iterator  trigpre = HLTPrescaled->begin();

  while (trigbit!=HLTTriggered->end()) {
      
    if ((trigbit->first).find("HLT_MET65_CenJet50U_v")!=string::npos) {
      HLTMC_MET65_CenJet50U = trigbit->second;
      PrescaleMC_MET65_CenJet50U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_MET80_CenJet50U_v")!=string::npos) {
      HLTMC_MET80_CenJet50U = trigbit->second;
      PrescaleMC_MET80_CenJet50U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_CentralJet80_MET65_v")!=string::npos) {
      HLT_CentralJet80_MET65 = trigbit->second;
      Prescale_CentralJet80_MET65 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_CentralJet80_MET80_v")!=string::npos) {
      HLT_CentralJet80_MET80 = trigbit->second;
      Prescale_CentralJet80_MET80 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_CentralJet80_MET100_v")!=string::npos) {
      HLT_CentralJet80_MET100 = trigbit->second;
      Prescale_CentralJet80_MET100 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_CentralJet80_MET160_v")!=string::npos) {
      HLT_CentralJet80_MET160 = trigbit->second;
      Prescale_CentralJet80_MET160 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_DiJet60_MET45")!=string::npos) {
      HLT_DiJet60_MET45 = trigbit->second;
      Prescale_DiJet60_MET45 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_DiJetAve100U")!=string::npos) {
      HLT_DiJetAve100U = trigbit->second;
      Prescale_DiJetAve100U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_DiJetAve140U")!=string::npos) {
      HLT_DiJetAve140U = trigbit->second;
      Prescale_DiJetAve140U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_DiJetAve180U")!=string::npos) {
      HLT_DiJetAve180U = trigbit->second;
      Prescale_DiJetAve180U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_DiJetAve300U")!=string::npos) {
      HLT_DiJetAve300U = trigbit->second;
      Prescale_DiJetAve300U = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT300_v")!=string::npos) {
      HLT_HT300 = trigbit->second;
      Prescale_HT300 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT350_v")!=string::npos) {
      HLT_HT350 = trigbit->second;
      Prescale_HT350 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT360_v")!=string::npos) {
      HLT_HT360 = trigbit->second;
      Prescale_HT360 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT400_v")!=string::npos) {
      HLT_HT400 = trigbit->second;
      Prescale_HT400 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT440_v")!=string::npos) {
      HLT_HT440 = trigbit->second;
      Prescale_HT440 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT450_v")!=string::npos) {
      HLT_HT450 = trigbit->second;
      Prescale_HT450 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT500_v")!=string::npos) {
      HLT_HT500 = trigbit->second;
      Prescale_HT500 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT520_v")!=string::npos) {
      HLT_HT520 = trigbit->second;
      Prescale_HT520 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT550_v")!=string::npos) {
      HLT_HT550 = trigbit->second;
      Prescale_HT550 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT250_MHT60")!=string::npos) {
      HLT_HT250_MHT60 = trigbit->second;
      Prescale_HT250_MHT60 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_HT300_MHT75")!=string::npos) {
      HLT_HT300_MHT75 = trigbit->second;
      Prescale_HT300_MHT75 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Jet110_v")!=string::npos) {
      HLT_Jet110 = trigbit->second;
      Prescale_Jet110 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Jet150_v")!=string::npos) {
      HLT_Jet150 = trigbit->second;
      Prescale_Jet150 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Jet190_v")!=string::npos) {
      HLT_Jet190 = trigbit->second;
      Prescale_Jet190 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Jet240_v")!=string::npos) {
      HLT_Jet240 = trigbit->second;
      Prescale_Jet240 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Jet370_v")!=string::npos) {
      HLT_Jet370 = trigbit->second;
      Prescale_Jet370 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_MET100")!=string::npos) {
      HLT_MET100 = trigbit->second;
      Prescale_MET100 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_MET120")!=string::npos) {
      HLT_MET120 = trigbit->second;
      Prescale_MET120 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_MET200")!=string::npos) {
      HLT_MET200 = trigbit->second;
      Prescale_MET200 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_PFMHT150")!=string::npos) {
      HLT_PFMHT150 = trigbit->second;
      Prescale_PFMHT150 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_IsoMu12_v")!=string::npos) {
      HLT_IsoMu12  = trigbit->second;
      Prescale_IsoMu12  = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Mu15_v")!=string::npos) {
      HLT_Mu15     = trigbit->second;
      Prescale_Mu15     = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Mu20_v")!=string::npos) {
      HLT_Mu20     = trigbit->second;
      Prescale_Mu20     = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v")!=string::npos) {
      HLT_Ele27    = trigbit->second;
      Prescale_Ele27    = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v")!=string::npos) {
      HLT_Ele32    = trigbit->second;
      Prescale_Ele32    = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Ele45_CaloIdVT_TrkIdT_v")!=string::npos) {
      HLT_Ele45    = trigbit->second;
      Prescale_Ele45    = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Photon50_CaloIdVL_IsoL_v")!=string::npos) {
      HLT_PhotonIso50 = trigbit->second;
      Prescale_PhotonIso50 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Photon75_CaloIdVL_IsoL_v")!=string::npos) {
      HLT_PhotonIso75 = trigbit->second;
      Prescale_PhotonIso75 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Photon75_CaloIdVL_v")!=string::npos) {
      HLT_Photon75 = trigbit->second;
      Prescale_Photon75 = trigpre->second;
    }

    if ((trigbit->first).find("HLT_Photon70_Cleaned_L1R_v")!=string::npos) {
      HLTMC_Photon70 = trigbit->second;
      PrescaleMC_Photon70 = trigpre->second;
    }

    ++trigbit;
    ++trigpre;
  }


}

/***************Jets****************/
void DiJetStudy::getJetInfo(const int& nJets) {
  using namespace std;
  mJet1pT  = -9;    mJet2pT  = -9;    mJet3pT  = -9;    mJet4pT  = -9;
  mJet1en  = -9;    mJet2en  = -9;    mJet3en  = -9;    mJet4en  = -9;
  mJet1eta = -9;    mJet2eta = -9;    mJet3eta = -9;    mJet4eta = -9;
  mJet1phi = -9;    mJet2phi = -9;    mJet3phi = -9;    mJet4phi = -9;
  mJet1ssvhe = -9;  mJet2ssvhe = -9;  mJet3ssvhe = -9;  mJet4ssvhe = -9;
  mJet1ssvhp = -9;  mJet2ssvhp = -9;  mJet3ssvhp = -9;  mJet4ssvhp = -9;
  mJet1ID  = false; mJet2ID  = false; mJet3ID  = false; mJet4ID  = false;
    
  //Jet variables
  if (nJets > 0) {
    mJet1pT    = JetP4->at(0).Pt();
    mJet1en    = JetP4->at(0).E();
    mJet1eta   = JetP4->at(0).Eta();
    mJet1phi   = JetP4->at(0).Phi();
    mJet1ssvhe = JetBTag_SSVHE->at(0);
    mJet1ssvhp = JetBTag_SSVHP->at(0);
    mJet1ID    = jetID(0);
      
    if (nJets > 1) {
      mJet2pT  = JetP4->at(1).Pt();
      mJet2en  = JetP4->at(1).E();
      mJet2eta = JetP4->at(1).Eta();
      mJet2phi = JetP4->at(1).Phi();
      mJet2ssvhe = JetBTag_SSVHE->at(1);
      mJet2ssvhp = JetBTag_SSVHP->at(1);
      mJet2ID  = jetID(1);
	
      if (nJets > 2) {
	mJet3pT  = JetP4->at(2).Pt();
	mJet3en  = JetP4->at(2).E();
	mJet3eta = JetP4->at(2).Eta();
	mJet3phi = JetP4->at(2).Phi();
	mJet3ssvhe = JetBTag_SSVHE->at(2);
	mJet3ssvhp = JetBTag_SSVHP->at(2);
	mJet3ID  = jetID(2);
	  
	if (nJets > 3) {
	  mJet4pT  = JetP4->at(3).Pt();
	  mJet4en  = JetP4->at(3).E();
	  mJet4eta = JetP4->at(3).Eta();
	  mJet4phi = JetP4->at(3).Phi();
	  mJet4ssvhe = JetBTag_SSVHE->at(3);
	  mJet4ssvhp = JetBTag_SSVHP->at(3);
	  mJet4ID  = jetID(3);
	    
	}
      }
    }
  }
  //Loop over all jets
  mNJets   = 0, mNGoodJets   = 0, mNBadJets   = 0;
  mNJets10 = 0, mNGoodJets10 = 0, mNBadJets10 = 0;
  mNJets30 = 0, mNGoodJets30 = 0, mNBadJets30 = 0;
  mNJets50 = 0, mNGoodJets50 = 0, mNBadJets50 = 0;
    
  mbJet1pT  = -9;    mbJet2pT  = -9;    mbJet3pT  = -9;   
  mbJet1en  = -9;    mbJet2en  = -9;    mbJet3en  = -9;   
  mbJet1eta = -9;    mbJet2eta = -9;    mbJet3eta = -9;   
  mbJet1phi = -9;    mbJet2phi = -9;    mbJet3phi = -9;   
  mbJet1ssvhe = -9;  mbJet2ssvhe = -9;  mbJet3ssvhe = -9; 
  mbJet1ssvhp = -9;  mbJet2ssvhp = -9;  mbJet3ssvhp = -9; 
  mbJet1ID  = false; mbJet2ID  = false; mbJet3ID  = false;
    
  //LorentzP4Vs goodJetsP4;
  //LorentzP4Vs badJetsP4;
  mNbJets = 0;
  for ( int jjj = 0; jjj < nJets; ++jjj) {
    //find the b-jets
    if (JetP4->at(jjj).Pt() > 30. && JetBTag_SSVHE->at(jjj) > 1.74 ) {
      ++mNbJets;
      if (mNbJets == 1) {
	mbJet1pT    = JetP4->at(jjj).Pt();
	mbJet1en    = JetP4->at(jjj).E();
	mbJet1eta   = JetP4->at(jjj).Eta();
	mbJet1phi   = JetP4->at(jjj).Phi();
	mbJet1ssvhe = JetBTag_SSVHE->at(jjj);
	mbJet1ssvhp = JetBTag_SSVHP->at(jjj);
	mbJet1ID    = jetID(jjj);
      }

      else if (mNbJets == 2) {
	mbJet2pT    = JetP4->at(jjj).Pt();
	mbJet2en    = JetP4->at(jjj).E();
	mbJet2eta   = JetP4->at(jjj).Eta();
	mbJet2phi   = JetP4->at(jjj).Phi();
	mbJet2ssvhe = JetBTag_SSVHE->at(jjj);
	mbJet2ssvhp = JetBTag_SSVHP->at(jjj);
	mbJet2ID    = jetID(jjj);
      }

      else if (mNbJets == 3) {
	mbJet3pT    = JetP4->at(jjj).Pt();
	mbJet3en    = JetP4->at(jjj).E();
	mbJet3eta   = JetP4->at(jjj).Eta();
	mbJet3phi   = JetP4->at(jjj).Phi();
	mbJet3ssvhe = JetBTag_SSVHE->at(jjj);
	mbJet3ssvhp = JetBTag_SSVHP->at(jjj);
	mbJet3ID    = jetID(jjj);
      }
    }//end b-jet info

    //Count the jets
    ++mNJets;
    if (JetIDLoose->at(jjj) ) {
      ++mNGoodJets;
      //goodJetsP4.push_back(JetP4->at(jjj));
    }
    else {
      ++mNBadJets;
      //badJetsP4.push_back(JetP4->at(jjj));
    }
      
    if (JetP4->at(jjj).Pt() > 10) {
      ++mNJets10;
      if (JetIDLoose->at(jjj) )
	++mNGoodJets10;
      else
	++mNBadJets10;
    }
    if (JetP4->at(jjj).Pt() > 30) {
      ++mNJets30;
      if (JetIDLoose->at(jjj) )
	++mNGoodJets30;
      else
	++mNBadJets30;
    }
    if (JetP4->at(jjj).Pt() > 50) {
      ++mNJets50;
      if (JetIDLoose->at(jjj) )
	++mNGoodJets50;
      else
	++mNBadJets50;
    }
  }

  //Calculate various dphi values
  mJet1METDphi   = -9.;
  mJet2METDphi   = -9.;
  mMinJetMETDphi = -9.;

  mJet1Jet2Dphi  = -9.;
  mJet1Jet3Dphi  = -9.;
  mJet2Jet3Dphi  = -9.;

  mR1  = -9.;
  mR2  = -9.;

  mJet1Jet2DR = -9.;
  mJet1Jet3DR = -9.;
  mJet2Jet3DR = -9.;

  mJet1Jet2DpT = -9.;
  mJet1Jet3DpT = -9.;
  mJet2Jet3DpT = -9.;

  if (nJets > 1){
    mJet1METDphi   = computeDPhi(JetP4->at(0).Phi(), mMETphi);
    mJet1Jet2Dphi  = computeDPhi(JetP4->at(0).Phi(), JetP4->at(1).Phi());
    mJet2METDphi   = computeDPhi(JetP4->at(1).Phi(), mMETphi);
    mMinJetMETDphi = computeMinDPhi(50., *JetP4, mMETphi);
      
    mJet1Jet2DR  = computeDR(JetP4->at(0), JetP4->at(1));
    mJet1Jet2DpT = JetP4->at(0).Pt() - JetP4->at(1).Pt();
      
    mR1 = sqrt(mJet1METDphi*mJet1METDphi + (M_PI-mJet2METDphi)*(M_PI-mJet2METDphi));
    mR2 = sqrt(mJet2METDphi*mJet2METDphi + (M_PI-mJet1METDphi)*(M_PI-mJet1METDphi));

    if (nJets > 2) {
      mJet1Jet3Dphi  = computeDPhi(JetP4->at(0).Phi(), JetP4->at(2).Phi());
      mJet2Jet3Dphi  = computeDPhi(JetP4->at(1).Phi(), JetP4->at(2).Phi());

      mJet1Jet3DR = computeDR(JetP4->at(0), JetP4->at(2));
      mJet2Jet3DR = computeDR(JetP4->at(1), JetP4->at(2));
	
      mJet1Jet3DpT = JetP4->at(0).Pt() - JetP4->at(2).Pt();
      mJet2Jet3DpT = JetP4->at(1).Pt() - JetP4->at(2).Pt();
    }
  }

  mMinvJet1Jet2        = -9.,
    mMinvJet1Jet3      = -9.,
    mMinvJet2Jet3      = -9.,
    mMinvJet1Jet2Jet3  = -9.;

  mMTJet1Jet2        = -9.,
    mMTJet1Jet3      = -9.,
    mMTJet2Jet3      = -9.,
    mMTJet1Jet2Jet3  = -9.;
    
  mMTJet1Jet2MET        = -9.,
    mMTJet1Jet3MET      = -9.,
    mMTJet2Jet3MET      = -9.,
    mMTJet1Jet2Jet3MET  = -9.;

  if (nJets > 1) {
    TLorentzVector jet1, jet2, themet;
    TLorentzVector dijet;
    jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
    jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
    themet.SetPxPyPzE(METP4->Px(),METP4->Py(),METP4->Pz(),METP4->E());

    dijet = jet1 + jet2;
    mMTJet1Jet2   = dijet.Mt();
    mMinvJet1Jet2 = dijet.M();
      
    //dijets + met transverse mass
    dijet = jet1 + jet2 + themet;
    mMTJet1Jet2MET   = dijet.Mt();
      
    if (nJets > 2) {
      TLorentzVector jet3;
      jet3.SetPxPyPzE(JetP4->at(2).Px(),JetP4->at(2).Py(),JetP4->at(2).Pz(),JetP4->at(2).E());
	
      dijet = jet1 + jet3;
      mMTJet1Jet3   = dijet.Mt();
      mMinvJet1Jet3 = dijet.M();
	
      dijet = jet2 + jet3;
      mMTJet2Jet3   = dijet.Mt();
      mMinvJet2Jet3 = dijet.M();
	
      //trijet transverse/invariant mass
      dijet = jet1 + jet2 + jet3;
      mMTJet1Jet2Jet3   = dijet.Mt();
      mMinvJet1Jet2Jet3 = dijet.M();
	
      //dijets + met transverse mass
      dijet = jet1 + jet3 + themet;
      mMTJet1Jet3MET   = dijet.Mt();
	
      dijet = jet2 + jet3 + themet;
      mMTJet2Jet3MET   = dijet.Mt();
	
      //trijet + met transverse mass
      dijet = jet1 + jet2 + jet3 + themet;
      mMTJet1Jet2Jet3MET   = dijet.Mt();
	
    }
  }

}

/***************MET****************/
void DiJetStudy::getMETInfo() { 
  using namespace std;
  mMET      = METP4->Pt();
  mRawMET   = METpt_Nocorr;

  mMETphi   = METP4->Phi();
  mMETx     = METP4->Px();
  mMETy     = METP4->Py();

  mSigMET    = METsignificance;

  mSumEt    = METsumEt_Fullcorr;
  mRawSumEt = METsumEt_Nocorr;
}

/***************Leptons****************/
void DiJetStudy::getLeptonInfo(const int& nElecs, const int& nMuons, const int& nTaus ) {
  using namespace std;
  //electrons
  mNElec   = 0, mNGoodElec   = 0, mNElec10 = 0, mNElec15 = 0,  mNElec25 = 0;
  for ( int eee = 0; eee < nElecs; ++eee) {
    ++mNElec;
    if (electronID(eee,false) ) {
      ++mNGoodElec;
      if (ElectronP4->at(eee).Pt() > 10) 
	++mNElec10;
      if (ElectronP4->at(eee).Pt() > 15) 
	++mNElec15;
      if (ElectronP4->at(eee).Pt() > 25) 
	++mNElec25;
    }
  }

  //muons
  mNMuon   = 0, mNGoodMuon   = 0, mNMuon10 = 0, mNMuon15 = 0,  mNMuon25 = 0;
  for ( int mmm = 0; mmm < nMuons; ++mmm) {
    ++mNMuon;
    if (muonID(mmm) ) {
      ++mNGoodMuon;
      if (MuonP4->at(mmm).Pt() > 10) 
	++mNMuon10;
      if (MuonP4->at(mmm).Pt() > 15) 
	++mNMuon15;
      if (MuonP4->at(mmm).Pt() > 25) 
	++mNMuon25;
    }
  }

  //taus
  mNTau   = 0, mNTau10 = 0, mNTau15 = 0,  mNTau25 = 0;
  for ( int ttt = 0; ttt < nTaus; ++ttt) {
    ++mNTau;
    if (TauP4->at(ttt).Pt() > 10) 
      ++mNTau10;
    if (TauP4->at(ttt).Pt() > 15) 
      ++mNTau15;
    if (TauP4->at(ttt).Pt() > 25) 
      ++mNTau25;
  }
}

/***************Photons****************/
void DiJetStudy::getPhotonInfo(const int& nPhots) {
  using namespace std;
  mNPhot   = 0, mNGoodPhot   = 0, mNPhot10 = 0, mNPhot15 = 0,  mNPhot25 = 0;
  for ( int ppp = 0; ppp < nPhots; ++ppp) {
    ++mNPhot;
    if (photonID(ppp,false) ) {
      ++mNGoodPhot;
      if (PhotonP4->at(ppp).Pt() > 10) 
	++mNPhot10;
      if (PhotonP4->at(ppp).Pt() > 15) 
	++mNPhot15;
      if (PhotonP4->at(ppp).Pt() > 25) 
	++mNPhot25;
    }
  }
}

/***************HT/MHT****************/
void DiJetStudy::getHTMHTInfo() {
  using namespace std;
  double ht  = computeHT(ht_jet_minpt, ht_jet_maxeta, *JetP4, false);
  mHT = ht;

  TLorentzVector mht = computeMHT(mht_jet_minpt, mht_jet_maxeta, *JetP4, false);
  mMHT = mht.Pt();
  mMHTphi = mht.Phi();
  //calculate dphistar
  mDPhiStar = 0.;
  mDPhiStar = computeDPhiStar(mht,mht_jet_minpt,mht_jet_maxeta,*JetP4,false);
  mMeff = ht + mht.Pt();


  //Same HT/MHT quantities calculated with a JetID requirement
  ht  = computeHT(ht_jet_minpt, ht_jet_maxeta, *JetP4, true);
  mIDHT = ht;
  mht = computeMHT(mht_jet_minpt, mht_jet_maxeta, *JetP4, true);
  mIDMHT = mht.Pt();
  mIDMHTphi = mht.Phi();
  //calculate dphistar
  mIDDPhiStar = 0.;
  mIDDPhiStar = computeDPhiStar(mht,mht_jet_minpt,mht_jet_maxeta,*JetP4,true);
  mIDMeff = ht + mht.Pt();

}


/***************Vertex info****************/
void DiJetStudy::getVertexInfo(const int& nVtxs) {
  using namespace std;
  mNPV = 0;
  passPV = false;
  if (nVtxs > 0)
    if (vertexIsPrimary(0)) {
      mNPV = 1;
      mPVNTrks = VertexNTrks->at(0);
      mPVSumTrkPt = VertexSumTrkPt->at(0);
      passPV = true;
    }
  if (nVtxs > 1)
    for (int vvv = 1; vvv < nVtxs; ++vvv) {
      if (vertexIsPrimary(vvv))
	++mNPV;
    }
}


/***************Event selection****************/
void DiJetStudy::getSelectionInfo(const int& nJets) {
  using namespace std;
  /////Lepton veto values
  passElectronVeto = true;
  if (mNElec10 > 0)
    passElectronVeto = false;
    
  passMuonVeto = true;
  if (mNMuon10 > 0)
    passMuonVeto = false;
    
  passDLV   = true;
  passDLV  &= passElectronVeto;
  passDLV  &= passMuonVeto;


  //Preselection 2 good jets, with Et > 50GeV
  passPS = true;
  if (nJets < 2) 
    passPS = false;
  else {
    if (JetP4->at(1).Pt() < 50.)
      passPS = false;
    else if ( !(jetID(0,false) && jetID(1,false) ) )
      passPS = false;
    else
      passPS = true;
  }

  /*****************
   *Here is where the analysis cuts are defined
   *
   *
   *****************/
  ///Set up the jet cuts
  //Jets
  if (nJets>0) {
    passJet1Pt   = (JetP4->at(0).Pt()        >= jet1_minpt)  ? true : false;
    passJet1Eta  = (fabs(JetP4->at(0).Eta()) <= jet1_maxeta) ? true : false;
    passJet1ID   = jetID(0,false);
    passJet1DPhi = (mJet1METDphi >= cut_jet1metdphi)         ? true : false;
  }
  if (nJets>1) {
    passJet2Pt     = (JetP4->at(1).Pt() >= jet2_minpt)             ? true : false;
    passJet2Eta    = (fabs(JetP4->at(1).Eta()) <= jet2_maxeta)     ? true : false;
    passJet2ID     = jetID(1,false);
    passJet2DPhi   = (mJet2METDphi             >= cut_jet2metdphi) ? true : false;

    passJet1Jet2DPhi = (mJet1Jet2Dphi  >= cut_jet12dphi)     ? true : false;
    passMinJetDPhi   = (mMinJetMETDphi >= cut_minjetmetdphi) ? true : false;
  }
    
  //switch for looking at exclusive vs inclusive dijet events
  passThirdJetVeto = true;
  for (int ijet = 2; ijet < nJets; ++ijet) 
    if (jetID(ijet,false)) 
      if (JetP4->at(ijet).Pt() > jetall_maxpt)
	passThirdJetVeto = false;
    
  //look at events with certain jets failing jetID
  passJetIDRejection = true;
  for (int ijet = 0; ijet < nJets; ++ijet) 
    if (JetP4->at(ijet).Pt() > jetall_minpt)
      if (fabs(JetP4->at(ijet).Eta()) < jetall_maxeta)
	if (!jetID(ijet,false)) 
	  passJetIDRejection = false;
    
    
  //Final selections
  passExclusiveDiJets = passJet1Pt && passJet1Eta && passJet1ID &&
    passJet2Pt && passJet2Eta && passJet2ID &&
    passThirdJetVeto;
    
  passInclusiveDiJets = passJet1Pt && passJet1Eta && passJet1ID &&
    passJet2Pt && passJet2Eta && passJet2ID;
    
  passDPhi  = passJet1DPhi &&
    passJet2DPhi;
      
  passMET  = (mMET >= cut_met)  ? true : false;

  //passExclusiveAllButDLVDPhiMET = passPS && passPV && passTriggers && passExclusiveDiJets;
  passExclusiveAllButDLVDPhiMET = passPS && passPV && passExclusiveDiJets;
  passExclusiveAllButDPhiMET    = passExclusiveAllButDLVDPhiMET && passDLV;
  passExclusiveAllButMET        = passExclusiveAllButDPhiMET && passDPhi;

  //passInclusiveAllButDLVDPhiMET = passPS && passPV && passTriggers && passInclusiveDiJets;
  passInclusiveAllButDLVDPhiMET = passPS && passPV && passInclusiveDiJets;
  passInclusiveAllButDPhiMET    = passInclusiveAllButDLVDPhiMET && passDLV;
  passInclusiveAllButMET        = passInclusiveAllButDPhiMET && passDPhi;


}


#endif // #ifdef DiJetStudy_cxx

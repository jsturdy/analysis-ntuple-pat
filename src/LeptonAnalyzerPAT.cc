// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      LeptonAnalyzerPAT
// 
/**\class LeptonAnalyzerPAT LeptonAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/LeptonAnalyzerPAT.cc

Description: Variable collector/ntupler for SUSY search with Jets + MET

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: LeptonAnalyzerPAT.cc,v 1.18 2011/03/18 10:58:50 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/LeptonAnalyzerPAT.h"
//#include "DataFormats/MuonReco/interface/MuonSelectors.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 

#pragma link C++ class std::vector< < reco::Candidate::LorentzVector> >+; 
#pragma link C++ class std::map< std::string, TauIDType >+; 

#endif
//________________________________________________________________________________________
LeptonAnalyzerPAT::LeptonAnalyzerPAT(const edm::ParameterSet& leptonParams, TTree* mLeptonData)
  :
  v_elecP4   (new std::vector<reco::Candidate::LorentzVector> ),
  v_genelecP4(new std::vector<reco::Candidate::LorentzVector> ),
  
  vd_ElecdB(new std::vector<double> ),
  vd_ElecdBerr(new std::vector<double> ),
  
  vd_ElecTrkIso(new std::vector<double> ),
  vd_ElecECalIso(new std::vector<double> ),
  vd_ElecHCalIso(new std::vector<double> ),
  vd_ElecAllIso(new std::vector<double> ),
  
  vd_ElecPFAllParticleIso(new std::vector<double> ),
  vd_ElecPFChargedHadronIso(new std::vector<double> ),
  vd_ElecPFNeutralHadronIso(new std::vector<double> ),
  vd_ElecPFGammaIso(new std::vector<double> ),
  
  vd_ElecTrkIsoDeposit(new std::vector<double> ),
  vd_ElecECalIsoDeposit(new std::vector<double> ),
  vd_ElecHCalIsoDeposit(new std::vector<double> ),
  
  vd_ElecPFAllParticleIsoDeposit(new std::vector<double> ),
  vd_ElecPFChargedHadronIsoDeposit(new std::vector<double> ),
  vd_ElecPFNeutralHadronIsoDeposit(new std::vector<double> ),
  vd_ElecPFGammaIsoDeposit(new std::vector<double> ),
  
  vd_ElecTrkChiNorm(new std::vector<double> ),
  vd_ElecCharge(new std::vector<double> ),
  
  vd_ElecIdLoose(new std::vector<double> ),
  vd_ElecIdTight(new std::vector<double> ),
  vd_ElecIdRobLoose(new std::vector<double> ),
  vd_ElecIdRobTight(new std::vector<double> ),
  vd_ElecIdRobHighE(new std::vector<double> ),

  vd_ElecChargeMode(new std::vector<double> ),
  vd_ElecPtTrkMode(new std::vector<double> ),
  vd_ElecQOverPErrTrkMode(new std::vector<double> ),

  vd_ElecE2OverE9(new std::vector<double> ),
  vd_ElecSwissCross(new std::vector<double> ),
  vd_ElecE1x5(new std::vector<double> ),
  vd_ElecE5x5(new std::vector<double> ),
  vd_ElecE2x5Max(new std::vector<double> ),
  vd_ElecFbrem(new std::vector<double> ),
  vd_ElecSigmaEtaEta(new std::vector<double> ),
  vd_ElecSigmaIetaIeta(new std::vector<double> ),
  vd_ElecHadOverEM(new std::vector<double> ),
  vd_ElecTSeed(new std::vector<double> ),
  vd_ElecESeed(new std::vector<double> ),

  vi_ElecGenPdgId (new std::vector<int> ),
  vi_ElecGenStatus(new std::vector<int> ),
  vi_ElecGenMother(new std::vector<int> ),
  vi_ElecGenMotherStatus(new std::vector<int> ),

  vd_ElecCaloEnergy(new std::vector<double> ),
  vd_ElecVx(new std::vector<double> ),
  vd_ElecVy(new std::vector<double> ),
  vd_ElecVz(new std::vector<double> ),
  vd_ElecPVDxy(new std::vector<double> ),
  vd_ElecBSDxy(new std::vector<double> ),
  vd_ElecDxy(new std::vector<double> ),
  vd_ElecDxyErr(new std::vector<double> ),
  vd_ElecD0(new std::vector<double> ),
  vd_ElecD0Err(new std::vector<double> ),
  vd_ElecDz(new std::vector<double> ),
  vd_ElecDzErr(new std::vector<double> ),
  vd_ElecPtTrk(new std::vector<double> ),
  vd_ElecQOverPErrTrk(new std::vector<double> ),
  vd_ElecLostHits(new std::vector<double> ),
  vd_ElecValidHits(new std::vector<double> ),
  //vd_ElecNCluster(new std::vector<double> ),
  vd_ElecEtaTrk(new std::vector<double> ),
  vd_ElecPhiTrk(new std::vector<double> ),
  vd_ElecWidthClusterEta(new std::vector<double> ),
  vd_ElecWidthClusterPhi(new std::vector<double> ),
  vd_ElecSCEta (new std::vector<double> ),
  vd_ElecSCPhi (new std::vector<double> ),
  vd_ElecSCEn  (new std::vector<double> ),
  vd_ElecSCPt  (new std::vector<double> ),
  vd_ElecSCRawE(new std::vector<double> ),

  vd_ElecPinTrk(new std::vector<double> ),
  vd_ElecPoutTrk(new std::vector<double> ),
  vd_ElecNormChi2(new std::vector<double> ),
  
  
  //Muons
  v_muonP4   (new std::vector<reco::Candidate::LorentzVector> ),
  v_genmuonP4(new std::vector<reco::Candidate::LorentzVector> ),
  
  vd_MuondB(new std::vector<double> ),
  vd_MuondBerr(new std::vector<double> ),

  vd_MuonCharge(new std::vector<double> ),

  vd_MuonTrkIso(new std::vector<double> ),
  vd_MuonECalIso(new std::vector<double> ),
  vd_MuonHCalIso(new std::vector<double> ),
  vd_MuonAllIso(new std::vector<double> ),

  vd_MuonPFAllParticleIso(new std::vector<double> ),
  vd_MuonPFChargedHadronIso(new std::vector<double> ),
  vd_MuonPFNeutralHadronIso(new std::vector<double> ),
  vd_MuonPFGammaIso(new std::vector<double> ),

  vd_MuonTrkIsoDeposit(new std::vector<double> ),
  vd_MuonECalIsoDeposit(new std::vector<double> ),
  vd_MuonHCalIsoDeposit(new std::vector<double> ),
  vd_MuonECalIsoDepositR03(new std::vector<double> ),
  vd_MuonHCalIsoDepositR03(new std::vector<double> ),

  vd_MuonPFAllParticleIsoDeposit(new std::vector<double> ),
  vd_MuonPFChargedHadronIsoDeposit(new std::vector<double> ),
  vd_MuonPFNeutralHadronIsoDeposit(new std::vector<double> ),
  vd_MuonPFGammaIsoDeposit(new std::vector<double> ),

  //Muon ID results
  vb_MuonIsGlobal(new std::vector<int> ),
  vb_MuonIsStandAlone(new std::vector<int> ),
  vb_MuonIsTracker(new std::vector<int> ),

  vb_MuonGlobalMuonPromptTight(new std::vector<int> ),

  vb_MuonAllArbitrated(new std::vector<int> ),
  vb_MuonTrackerMuonArbitrated(new std::vector<int> ),
  vb_MuonGMTkKinkTight(new std::vector<int> ),
  vb_MuonGMTkChiCompatibility(new std::vector<int> ),
  vb_MuonGMStaChiCompatibility(new std::vector<int> ),
  vb_MuonTM2DCompatibilityLoose(new std::vector<int> ),
  vb_MuonTM2DCompatibilityTight(new std::vector<int> ),
  vb_MuonTMOneStationLoose(new std::vector<int> ),
  vb_MuonTMOneStationTight(new std::vector<int> ),
  vb_MuonTMLastStationLoose(new std::vector<int> ),
  vb_MuonTMLastStationTight(new std::vector<int> ),
  vb_MuonTMLastStationAngLoose(new std::vector<int> ),
  vb_MuonTMLastStationAngTight(new std::vector<int> ),
  vb_MuonTMLastStationOptimizedLowPtLoose(new std::vector<int> ),
  vb_MuonTMLastStationOptimizedLowPtTight(new std::vector<int> ),
  vb_MuonTMLastStationOptimizedBarrelLowPtLoose(new std::vector<int> ),
  vb_MuonTMLastStationOptimizedBarrelLowPtTight(new std::vector<int> ),

  //Variables for combined muons
  vd_MuonCombVx(new std::vector<double> ),
  vd_MuonCombVy(new std::vector<double> ),
  vd_MuonCombVz(new std::vector<double> ),
  vd_MuonCombPVDxy(new std::vector<double> ),
  vd_MuonCombBSDxy(new std::vector<double> ),
  vd_MuonCombDxy(new std::vector<double> ),
  vd_MuonCombDxyErr(new std::vector<double> ),
  vd_MuonCombD0(new std::vector<double> ),
  vd_MuonCombD0Err(new std::vector<double> ),
  vd_MuonCombDz(new std::vector<double> ),
  vd_MuonCombDzErr(new std::vector<double> ),
  vd_MuonCombChi2(new std::vector<double> ),
  vd_MuonCombNdof(new std::vector<double> ),
  vd_MuonCombPt(new std::vector<double> ),
  vd_MuonCombPz(new std::vector<double> ),
  vd_MuonCombP(new std::vector<double> ),
  vd_MuonCombEta(new std::vector<double> ),
  vd_MuonCombPhi(new std::vector<double> ),
  vd_MuonCombChi(new std::vector<double> ),
  vd_MuonCombCharge(new std::vector<double> ),
  vd_MuonCombQOverPErr(new std::vector<double> ),
  vd_MuonCombValidHits(new std::vector<double> ),
  
  //Variables for Stand alone muons
  vd_MuonStandValidHits(new std::vector<double> ),
  vd_MuonStandLostHits(new std::vector<double> ),
  vd_MuonStandPt(new std::vector<double> ),
  vd_MuonStandPz(new std::vector<double> ),
  vd_MuonStandP(new std::vector<double> ),
  vd_MuonStandEta(new std::vector<double> ),
  vd_MuonStandPhi(new std::vector<double> ),
  vd_MuonStandChi(new std::vector<double> ),
  vd_MuonStandCharge(new std::vector<double> ),
  vd_MuonStandQOverPErr(new std::vector<double> ),
  /*
  vd_MuonTrkChiNorm(new std::vector<double> ),
  vd_MuonTrkValidHits(new std::vector<double> ),
  vd_MuonTrkLostHits(new std::vector<double> ),
  vd_MuonTrkPVDxy(new std::vector<double> ),
  vd_MuonTrkBSDxy(new std::vector<double> ),
  vd_MuonTrkDxy(new std::vector<double> ),
  vd_MuonTrkDxyErr(new std::vector<double> ),
  vd_MuonTrkD0(new std::vector<double> ),
  vd_MuonTrkD0Err(new std::vector<double> ),
  vd_MuonTrkDz(new std::vector<double> ),
  vd_MuonTrkDzErr(new std::vector<double> ),
  vd_MuonTrkPt(new std::vector<double> ),
  vd_MuonTrkPz(new std::vector<double> ),
  vd_MuonTrkP(new std::vector<double> ),
  vd_MuonTrkEta(new std::vector<double> ),
  vd_MuonTrkPhi(new std::vector<double> ),
  vd_MuonTrkChi(new std::vector<double> ),
  vd_MuonTrkCharge(new std::vector<double> ),
  vd_MuonTrkQOverPErr(new std::vector<double> ),
  vd_MuonTrkOuterZ(new std::vector<double> ),
  vd_MuonTrkOuterR(new std::vector<double> ),
  */
  vd_MuonPickyTrkChiNorm(new std::vector<double> ),
  vd_MuonPickyTrkValidHits(new std::vector<double> ),
  vd_MuonPickyTrkLostHits(new std::vector<double> ),
  vd_MuonPickyTrkPVDxy(new std::vector<double> ),
  vd_MuonPickyTrkBSDxy(new std::vector<double> ),
  vd_MuonPickyTrkDxy(new std::vector<double> ),
  vd_MuonPickyTrkDxyErr(new std::vector<double> ),
  vd_MuonPickyTrkD0(new std::vector<double> ),
  vd_MuonPickyTrkD0Err(new std::vector<double> ),
  vd_MuonPickyTrkDz(new std::vector<double> ),
  vd_MuonPickyTrkDzErr(new std::vector<double> ),
  vd_MuonPickyTrkPt(new std::vector<double> ),
  vd_MuonPickyTrkPz(new std::vector<double> ),
  vd_MuonPickyTrkP(new std::vector<double> ),
  vd_MuonPickyTrkEta(new std::vector<double> ),
  vd_MuonPickyTrkPhi(new std::vector<double> ),
  vd_MuonPickyTrkChi(new std::vector<double> ),
  vd_MuonPickyTrkCharge(new std::vector<double> ),
  vd_MuonPickyTrkQOverPErr(new std::vector<double> ),
  vd_MuonPickyTrkOuterZ(new std::vector<double> ),
  vd_MuonPickyTrkOuterR(new std::vector<double> ),

  /*
  vd_MuonTPFMSTrkChiNorm(new std::vector<double> ),
  vd_MuonTPFMSTrkValidHits(new std::vector<double> ),
  vd_MuonTPFMSTrkLostHits(new std::vector<double> ),
  vd_MuonTPFMSTrkPVDxy(new std::vector<double> ),
  vd_MuonTPFMSTrkBSDxy(new std::vector<double> ),
  vd_MuonTPFMSTrkDxy(new std::vector<double> ),
  vd_MuonTPFMSTrkDxyErr(new std::vector<double> ),
  vd_MuonTPFMSTrkD0(new std::vector<double> ),
  vd_MuonTPFMSTrkD0Err(new std::vector<double> ),
  vd_MuonTPFMSTrkDz(new std::vector<double> ),
  vd_MuonTPFMSTrkDzErr(new std::vector<double> ),
  vd_MuonTPFMSTrkPt(new std::vector<double> ),
  vd_MuonTPFMSTrkPz(new std::vector<double> ),
  vd_MuonTPFMSTrkP(new std::vector<double> ),
  vd_MuonTPFMSTrkEta(new std::vector<double> ),
  vd_MuonTPFMSTrkPhi(new std::vector<double> ),
  vd_MuonTPFMSTrkChi(new std::vector<double> ),
  vd_MuonTPFMSTrkCharge(new std::vector<double> ),
  vd_MuonTPFMSTrkQOverPErr(new std::vector<double> ),
  vd_MuonTPFMSTrkOuterZ(new std::vector<double> ),
  vd_MuonTPFMSTrkOuterR(new std::vector<double> ),
  */
  vi_MuonGenPdgId       (new std::vector<int> ),
  vi_MuonGenStatus      (new std::vector<int> ),
  vi_MuonGenMother      (new std::vector<int> ),
  vi_MuonGenMotherStatus(new std::vector<int> ),
  
  //Taus
  tauidMap(new std::map<std::string,TauIDType> ),
  
  v_tauP4      (new std::vector<reco::Candidate::LorentzVector>),
  v_gentauP4   (new std::vector<reco::Candidate::LorentzVector>),
  v_gentaujetP4(new std::vector<reco::Candidate::LorentzVector>),
  vd_TauCharge(new std::vector<double>  ),
  
  vi_TauGenPdgId       (new std::vector<int>),
  vi_TauGenStatus      (new std::vector<int>),
  vi_TauGenMother      (new std::vector<int>),
  vi_TauGenMotherStatus(new std::vector<int>),
  vi_TauGen            (new std::vector<int>),

  vi_TauSigTrk (new std::vector<int>),
  vd_TauTrkIso (new std::vector<double>),
  vd_TauECalIso(new std::vector<double>),
  vd_TauHCalIso(new std::vector<double>),
  vd_TauAllIso (new std::vector<double>),

  vd_TauPFAllParticleIso  (new std::vector<double>),
  vd_TauPFChargedHadronIso(new std::vector<double>),
  vd_TauPFNeutralHadronIso(new std::vector<double>),
  vd_TauPFGammaIso        (new std::vector<double>),

  vd_TauTrkIsoDeposit (new std::vector<double>),
  vd_TauECalIsoDeposit(new std::vector<double>),
  vd_TauHCalIsoDeposit(new std::vector<double>),

  vd_TauPFAllParticleIsoDeposit  (new std::vector<double>),
  vd_TauPFChargedHadronIsoDeposit(new std::vector<double>),
  vd_TauPFNeutralHadronIsoDeposit(new std::vector<double>),
  vd_TauPFGammaIsoDeposit        (new std::vector<double>),

  vd_TauVx    (new std::vector<double>),
  vd_TauVy    (new std::vector<double>),
  vd_TauVz    (new std::vector<double>),
  vd_TauPVDxy (new std::vector<double>),
  vd_TauBSDxy (new std::vector<double>),
  vd_TauDxy   (new std::vector<double>),
  vd_TauDxyErr(new std::vector<double>),
  vd_TauD0    (new std::vector<double>),
  vd_TauD0Err (new std::vector<double>),
  vd_TauDz    (new std::vector<double>),
  vd_TauDzErr (new std::vector<double>),

  vd_TauIdElec         (new std::vector<double>),
  vd_TauIdMuon         (new std::vector<double>),
  vd_TauIdIso          (new std::vector<double>),
  vd_TauIdIsoLeadPi    (new std::vector<double>),
  vd_TauIdEcalIso      (new std::vector<double>),
  vd_TauIdEcalIsoLeadPi(new std::vector<double>),
  vd_TauIdLeadPiPt     (new std::vector<double>),
  vd_TauIdLeadTrk      (new std::vector<double>),
  vd_TauIdLeadTrkPt    (new std::vector<double>),
  vd_TauIdTrkIso       (new std::vector<double>),
  vd_TauIdTrkIsoLeadPi (new std::vector<double>),

  vd_TauIdNCfrHalf   (new std::vector<double>),
  vd_TauIdNCfrQuarter(new std::vector<double>),
  vd_TauIdNCfrTenth  (new std::vector<double>),
  vd_TauIdNCfrFull   (new std::vector<double>),
  
  vd_TauCaloLeadTrkSignedIP      (new std::vector<double>),
  vd_TauCaloLeadTrkHcal3x3EtSum  (new std::vector<double>),
  vd_TauCaloLeadTrkHcal3x3HotDEta(new std::vector<double>),
  vd_TauCaloSignalTrkMInv        (new std::vector<double>),
  vd_TauCaloTrkMInv              (new std::vector<double>),
  vd_TauCaloIsoTrkPtSum          (new std::vector<double>),
  vd_TauCaloIsoEcalEtSum         (new std::vector<double>),
  vd_TauCaloMaxEtHCAL            (new std::vector<double>),
  
  vd_TrkPFIsoChargedHadPtSum(new std::vector<double>),
  vd_TrkPFIsoGammaEtSum     (new std::vector<double>),
  vd_TrkPFHcalClusterMaxEt  (new std::vector<double>),
  vd_TrkPFEFrac_em          (new std::vector<double>),
  vd_TrkPFHcalTotalOverPLead(new std::vector<double>),
  vd_TrkPFHcalMaxOverPLead  (new std::vector<double>),
  vd_TrkPFHcal3x3OverPLead  (new std::vector<double>),
  vd_TrkPFEcalStripOverPLead(new std::vector<double>),
  vd_TrkPFBremRecOverPLead  (new std::vector<double>),
  vd_TrkPFElePreIDOut       (new std::vector<double>),
  vd_TrkPFMuonCaloComp      (new std::vector<double>),
  vd_TrkPFMuonSegComp       (new std::vector<double>),
  
  vd_TauEtaEtaMom(new std::vector<double>),
  vd_TauPhiPhiMom(new std::vector<double>),
  vd_TauEtaPhiMom(new std::vector<double>)


{ 

  // Read in parameters from the config file
  elecMaxEta_ = leptonParams.getUntrackedParameter<double>("elecMaxEta",3.0);
  elecMaxEt_  = leptonParams.getUntrackedParameter<double>("elecMaxEt",9999.);
  elecMinEt_  = leptonParams.getUntrackedParameter<double>("elecMinEt",5.);
  elecRelIso_ = leptonParams.getUntrackedParameter<double>("elecRelIso",0.5);

  muonMaxEta_ = leptonParams.getUntrackedParameter<double>("muonMaxEta",3.0);
  muonMaxEt_  = leptonParams.getUntrackedParameter<double>("muonMaxEt",9999.);
  muonMinEt_  = leptonParams.getUntrackedParameter<double>("muonMinEt",5.);
  muonRelIso_ = leptonParams.getUntrackedParameter<double>("muonRelIso",0.1);

  tauMaxEta_ = leptonParams.getUntrackedParameter<double>("tauMaxEta",12.0);
  tauMaxEt_  = leptonParams.getUntrackedParameter<double>("tauMaxEt",9999.);
  tauMinEt_  = leptonParams.getUntrackedParameter<double>("tauMinEt",5.);
  tauRelIso_ = leptonParams.getUntrackedParameter<double>("tauRelIso",0.5);

  debug_   = leptonParams.getUntrackedParameter<int>("debugLeps",0);
  prefix_  = leptonParams.getUntrackedParameter<std::string>("prefixLeps","");
 
  // get the data tags
  elecTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("elecTag");
  muonTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("muonTag");
  tauTag_    = leptonParams.getUntrackedParameter<edm::InputTag>("tauTag");
  _vtxTag      = leptonParams.getUntrackedParameter<edm::InputTag>("vtxTag"); 
  _beamspotTag = leptonParams.getUntrackedParameter<edm::InputTag>("beamspotTag"); 

  // Initialise ntuple branches
  bookTTree(mLeptonData);

}


//________________________________________________________________________________________
LeptonAnalyzerPAT::~LeptonAnalyzerPAT() {
  
}

//
//________________________________________________________________________________________
void LeptonAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{

}

//________________________________________________________________________________________
bool LeptonAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  bool_ElecVeto      = false;
  bool_MuonVeto      = false;
  bool_TauVeto       = false;
  bool lepton_result = true;

  edm::LogVerbatim("LeptonEvent") << " Start  " << std::endl;
  std::ostringstream dbg;

  edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
  ev.getByLabel(_beamspotTag,recoBeamSpotHandle);
  reco::BeamSpot bs = *recoBeamSpotHandle;   
  double bsx0 =0., bsy0 = 0., bsz0 = 0.;
  math::XYZPoint bsPoint(bsx0,bsy0,bsz0);

  edm::LogVerbatim("VertexAnalyzerPAT") << "Vertex results for InputTag" << _vtxTag;
  Handle<VertexCollection> vertices;
  ev.getByLabel(_vtxTag, vertices);

  double pvx0 = 0., pvy0 = 0., pvz0 = 0.;
  if (vertices->size() > 0) {
    const reco::Vertex& pVertex = (*vertices)[0];
    if(pVertex.isValid()) {
      pvx0 = pVertex.x();
      pvy0 = pVertex.y();
      pvz0 = pVertex.z();
    }
  }
  math::XYZPoint pvPoint(pvx0,pvy0,pvz0);
  /*
   *Get the information on all the electrons
   *
   */

  // get the electrons
  edm::Handle< std::vector<pat::Electron> > elecHandle;
  ev.getByLabel(elecTag_, elecHandle);
  if ( !elecHandle.isValid() ) {
    edm::LogWarning("LeptonEvent") << "No Electron results for InputTag " << elecTag_;
    if (debug_) std::cout<<" Electron results for InputTag " << elecTag_<<std::endl;
    return false;
  }

  edm::Handle<EcalRecHitCollection> recHitsEB;
  //ev.getByLabel( "ecalRecHit","reducedEcalRecHitsEB", recHitsEB);
  ev.getByLabel("reducedEcalRecHitsEB", recHitsEB);

  edm::Handle<EcalRecHitCollection> recHitsEE;
  //ev.getByLabel( "ecalRecHit","reducedEcalRecHitsEE", recHitsEE);
  ev.getByLabel("reducedEcalRecHitsEE", recHitsEE);
  
  const EcalRecHitCollection *myEBRecHits = recHitsEB.product();
  const EcalRecHitCollection *myEERecHits = recHitsEE.product();
  
  edm::LogVerbatim("LeptonEvent") << " start reading in electrons " << std::endl;
  // Add the electrons
  i_ElecN = elecHandle->size();
  if (debug_) std::cout<<i_ElecN<<" Electron results for InputTag " << elecTag_<<std::endl;
  
  if ( i_ElecN > 50 ) i_ElecN = 50;
  maintenanceElecs();

  bool_spike = false;
    
  int el = 0;
  for (int i=0;i<i_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() > elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;

      // ECAL spike cleaning
      // Cut only on EB, ecal-seeded electrons
      double mySwissCross = -999;
      double myE2OverE9   = -999;

      vd_ElecdB    ->push_back(theElectron.dB());
      vd_ElecdBerr ->push_back(theElectron.edB());

      v_elecP4->push_back(theElectron.p4());
      vd_ElecCharge->push_back(theElectron.charge());

      vd_ElecTrkIso ->push_back(theElectron.trackIso());
      vd_ElecECalIso->push_back(theElectron.ecalIso());
      vd_ElecHCalIso->push_back(theElectron.hcalIso());
      vd_ElecAllIso ->push_back(theElectron.caloIso());

      //Special PF based isolation variables
      vd_ElecPFAllParticleIso  ->push_back(theElectron.particleIso());
      vd_ElecPFChargedHadronIso->push_back(theElectron.chargedHadronIso());
      vd_ElecPFNeutralHadronIso->push_back(theElectron.neutralHadronIso());
      vd_ElecPFGammaIso        ->push_back(theElectron.photonIso());
      
      if (theElectron.trackIsoDeposit())
	vd_ElecTrkIsoDeposit ->push_back(theElectron.trackIsoDeposit()->candEnergy());
      else
	vd_ElecTrkIsoDeposit ->push_back(-999.);

      if (theElectron.ecalIsoDeposit())
	vd_ElecECalIsoDeposit ->push_back(theElectron.ecalIsoDeposit()->candEnergy());
      else
	vd_ElecECalIsoDeposit ->push_back(-999.);

      if (theElectron.hcalIsoDeposit())
	vd_ElecHCalIsoDeposit ->push_back(theElectron.hcalIsoDeposit()->candEnergy());
      else
	vd_ElecHCalIsoDeposit ->push_back(-999.);

      if (theElectron.userIsoDeposit(pat::PfAllParticleIso))
	vd_ElecPFAllParticleIsoDeposit ->push_back(theElectron.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_ElecPFAllParticleIsoDeposit ->push_back(-999.);

      if (theElectron.userIsoDeposit(pat::PfChargedHadronIso))
	vd_ElecPFChargedHadronIsoDeposit ->push_back(theElectron.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_ElecPFChargedHadronIsoDeposit ->push_back(-999.);

      if (theElectron.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_ElecPFNeutralHadronIsoDeposit ->push_back(theElectron.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_ElecPFNeutralHadronIsoDeposit ->push_back(-999.);

      if (theElectron.userIsoDeposit(pat::PfGammaIso))
	vd_ElecPFGammaIsoDeposit ->push_back(theElectron.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_ElecPFGammaIsoDeposit ->push_back(-999.);

      
      vd_ElecIdLoose   ->push_back(theElectron.electronID("eidLoose"));
      vd_ElecIdTight   ->push_back(theElectron.electronID("eidTight"));
      vd_ElecIdRobLoose->push_back(theElectron.electronID("eidRobustLoose"));
      vd_ElecIdRobTight->push_back(theElectron.electronID("eidRobustTight")); 
      vd_ElecIdRobHighE->push_back(theElectron.electronID("eidRobustHighEnergy")); 
      
      vd_ElecCaloEnergy->push_back(theElectron.caloEnergy());

      vd_ElecVx   ->push_back(theElectron.vx());
      vd_ElecVy   ->push_back(theElectron.vy());
      vd_ElecVz   ->push_back(theElectron.vz());

      if (theElectron.gsfTrack().isNonnull()) {
	vd_ElecPVDxy ->push_back(theElectron.gsfTrack()->dxy(pvPoint));
	vd_ElecBSDxy ->push_back(theElectron.gsfTrack()->dxy(bsPoint));
	vd_ElecDxy   ->push_back(theElectron.gsfTrack()->dxy());
	vd_ElecDxyErr->push_back(theElectron.gsfTrack()->dxyError());
	vd_ElecD0    ->push_back(theElectron.gsfTrack()->d0());
	vd_ElecD0Err ->push_back(theElectron.gsfTrack()->d0Error());
	vd_ElecDz    ->push_back(theElectron.gsfTrack()->dz());
	vd_ElecDzErr ->push_back(theElectron.gsfTrack()->dzError());
	
	vd_ElecChargeMode      ->push_back(theElectron.gsfTrack()->chargeMode());	
	vd_ElecPtTrkMode       ->push_back(theElectron.gsfTrack()->ptMode());
	vd_ElecQOverPErrTrkMode->push_back(theElectron.gsfTrack()->qoverpModeError());
	vd_ElecCharge          ->push_back(theElectron.gsfTrack()->charge());
	vd_ElecPtTrk           ->push_back(theElectron.gsfTrack()->pt());
	vd_ElecQOverPErrTrk    ->push_back(theElectron.gsfTrack()->qoverpError());
	vd_ElecNormChi2        ->push_back(theElectron.gsfTrack()->normalizedChi2());
	vd_ElecLostHits        ->push_back(theElectron.gsfTrack()->lost());
	vd_ElecValidHits       ->push_back(theElectron.gsfTrack()->found());

	vd_ElecEtaTrk->push_back(theElectron.trackMomentumAtVtx().Eta());
	vd_ElecPhiTrk->push_back(theElectron.trackMomentumAtVtx().Phi());
	vd_ElecPinTrk->push_back(sqrt(theElectron.trackMomentumAtVtx().Mag2()));
	vd_ElecPoutTrk->push_back(sqrt(theElectron.trackMomentumOut().Mag2()));
      }

      else {
	vd_ElecPVDxy ->push_back(-999.);
	vd_ElecBSDxy ->push_back(-999.);
	vd_ElecDxy   ->push_back(-999.);
	vd_ElecDxyErr->push_back(-999.);
	vd_ElecD0    ->push_back(-999.);
	vd_ElecD0Err ->push_back(-999.);
	vd_ElecDz    ->push_back(-999.);
	vd_ElecDzErr ->push_back(-999.);
	
	vd_ElecChargeMode      ->push_back(-999.);
	vd_ElecPtTrkMode       ->push_back(-999.);
	vd_ElecQOverPErrTrkMode->push_back(-999.);
	vd_ElecCharge          ->push_back(-999.);
	vd_ElecPtTrk           ->push_back(-999.);
	vd_ElecQOverPErrTrk    ->push_back(-999.);
	vd_ElecNormChi2        ->push_back(-999.);
	vd_ElecLostHits        ->push_back(-999.);
	vd_ElecValidHits       ->push_back(-999.);

	vd_ElecEtaTrk ->push_back(-999.);
	vd_ElecPhiTrk ->push_back(-999.);
	vd_ElecPinTrk ->push_back(-999.);
	vd_ElecPoutTrk->push_back(-999.);
      }
      
      
      double mySCEta      = -999;
      double mySCPhi      = -999;
      double mySCEn       = -999;
      double mySCPt       = -999;
      double mySCRawE     = -999;

      if (theElectron.superCluster().isNonnull()) {
	
	
	const reco::CaloClusterPtr    seed =    theElectron.superCluster()->seed(); // seed cluster
	int subdet = seed->hitsAndFractions()[0].first.subdetId();

	const EcalRecHitCollection* ecalRecHits = 0;
	//if (subdet == EcalBarrel) ecalRecHits = recHitsEB.product();
	//if (subdet == EcalEndcap) ecalRecHits = recHitsEE.product();
	if (subdet == EcalBarrel) ecalRecHits = myEBRecHits;
	if (subdet == EcalEndcap) ecalRecHits = myEERecHits;
	
	
	const   DetId seedId = seed->seed();
	
	//if(theElectron.ecalDrivenSeed()>0 && fabs(theElectron.superCluster()->eta())<1.4442) {
	EcalSeverityLevelAlgo severity;
	//mySwissCross =  severity.swissCross(seedId, *myEBRecHits) ;
	//myE2OverE9   =  severity.swissCross(seedId, *myEBRecHits) ;
	mySwissCross =  severity.swissCross(seedId, *ecalRecHits) ;
	myE2OverE9   =  severity.swissCross(seedId, *ecalRecHits) ;
	if (mySwissCross > 0.95) { 
	  //continue; //ingnore this electron if it has swiss cross > 0.95
	    bool_spike = true;
	}
	//}
	vd_ElecE2OverE9->push_back(myE2OverE9);
	vd_ElecSwissCross->push_back(mySwissCross);
	
	vd_ElecE1x5->push_back(theElectron.e1x5());
	vd_ElecE5x5->push_back(theElectron.e5x5());
	vd_ElecE2x5Max->push_back(theElectron.e2x5Max());
	vd_ElecFbrem->push_back(theElectron.fbrem());
	vd_ElecSigmaEtaEta->push_back(theElectron.sigmaEtaEta());
	vd_ElecSigmaIetaIeta->push_back(theElectron.sigmaIetaIeta());
	vd_ElecHadOverEM->push_back(theElectron.hadronicOverEm());
	///
	vd_ElecTSeed->push_back(ecalRecHits->find(seedId)->time());
	vd_ElecESeed->push_back(ecalRecHits->find(seedId)->energy());
	/////
	
	mySCEta      = theElectron.superCluster()->eta();
	mySCPhi      = theElectron.superCluster()->phi();
	mySCEn       = theElectron.superCluster()->energy();
	mySCPt       = mySCEn/cosh(theElectron.superCluster()->eta());
	mySCRawE     = theElectron.superCluster()->rawEnergy();

	vd_ElecWidthClusterEta->push_back(theElectron.superCluster()->etaWidth());
	vd_ElecWidthClusterPhi->push_back(theElectron.superCluster()->phiWidth());
      }
      
      else {
	vd_ElecE2OverE9->push_back(-999.);
	vd_ElecSwissCross->push_back(-999.);
	vd_ElecE1x5->push_back(-999.);
	vd_ElecE5x5->push_back(-999.);
	vd_ElecE2x5Max->push_back(-999.);
	vd_ElecFbrem->push_back(-999.);
	vd_ElecSigmaEtaEta->push_back(-999.);
	vd_ElecSigmaIetaIeta->push_back(-999.);
	vd_ElecHadOverEM->push_back(-999.);
	vd_ElecTSeed->push_back(-999.);
	vd_ElecESeed->push_back(-999.);
	vd_ElecWidthClusterEta->push_back(-999.);
	vd_ElecWidthClusterPhi->push_back(-999.);
      }
      vd_ElecSCEta ->push_back(mySCEta );
      vd_ElecSCPhi ->push_back(mySCPhi );
      vd_ElecSCEn  ->push_back(mySCEn  );
      vd_ElecSCPt  ->push_back(mySCPt  );
      vd_ElecSCRawE->push_back(mySCRawE);
      
      //get associated gen particle information
      const reco::Candidate* candElec = theElectron.genLepton();
      if ( candElec ) {
	vi_ElecGenPdgId->push_back(candElec->pdgId());
	vi_ElecGenStatus->push_back(candElec->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candElec->px(),candElec->py(),candElec->pz(),candElec->energy());
	v_genelecP4->push_back(genp4);
      	
	const reco::Candidate* elecMother = candElec->mother();
	if( elecMother ) {
	  //is this necessary
	  //while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
	  //if ( elecMother ) {
	  vi_ElecGenMother->push_back(theElectron.genLepton()->mother()->pdgId());
	  vi_ElecGenMotherStatus->push_back(theElectron.genLepton()->mother()->status());
	  //}
	}
      }
      else {
	vi_ElecGenPdgId       ->push_back(-999);
	vi_ElecGenStatus      ->push_back(-999);
	vi_ElecGenMother      ->push_back(-999);
	vi_ElecGenMotherStatus->push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_genelecP4->push_back(genp4);
      }
      double elecIsoReq = (vd_ElecTrkIso->at(el)+vd_ElecECalIso->at(el)+vd_ElecHCalIso->at(el))/theElectron.pt();
      if ( elecIsoReq  > elecRelIso_) bool_ElecVeto = bool_ElecVeto || true;
      if ( theElectron.pt() > elecMaxEt_ ) bool_ElecVeto = bool_ElecVeto || true;
      ++el;
    }
  }//end loop over Electrons
  i_ElecN = el;

  /*
   * get the muons
   *
   */
  edm::Handle< std::vector<pat::Muon> > muonHandle;
  ev.getByLabel(muonTag_, muonHandle);
  if ( !muonHandle.isValid() ) {
    edm::LogWarning("LeptonEvent") << "No Muon results for InputTag " << muonTag_;
    if (debug_) std::cout<<" Muon results for InputTag " << muonTag_<<std::endl;
    return false;
  }
  
  edm::LogVerbatim("LeptonEvent") << " start reading in muons " << std::endl;

  // Add the muons
  i_MuonN= muonHandle->size();
  if (debug_) std::cout<<i_MuonN<<" Muon results for InputTag " << muonTag_<<std::endl;

  if ( i_MuonN > 50 ) i_MuonN = 50;
  maintenanceMuons();
  int mu = 0;

  for (int i=0;i<i_MuonN;i++){
    const pat::Muon& theMuon = (*muonHandle)[i];
    if ( (theMuon.pt() > muonMinEt_) && !(theMuon.eta() > muonMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good muons " << std::endl;      
      v_muonP4->push_back(theMuon.p4());

      vd_MuondB    ->push_back(theMuon.dB());
      vd_MuondBerr ->push_back(theMuon.edB());

      vd_MuonCharge->push_back(theMuon.charge());

      //Muon isolation variables
      vd_MuonTrkIso->push_back(theMuon.trackIso());
      vd_MuonECalIso->push_back(theMuon.ecalIso());
      vd_MuonHCalIso->push_back(theMuon.hcalIso());
      vd_MuonAllIso->push_back(theMuon.caloIso());

      //Special PF based isolation variables
      vd_MuonPFAllParticleIso  ->push_back(theMuon.particleIso());
      vd_MuonPFChargedHadronIso->push_back(theMuon.chargedHadronIso());
      vd_MuonPFNeutralHadronIso->push_back(theMuon.neutralHadronIso());
      vd_MuonPFGammaIso        ->push_back(theMuon.photonIso());
      
      if (theMuon.trackIsoDeposit())
	vd_MuonTrkIsoDeposit ->push_back(theMuon.trackIsoDeposit()->candEnergy());
      else
	vd_MuonTrkIsoDeposit ->push_back(-999.);

      if (theMuon.ecalIsoDeposit())
	vd_MuonECalIsoDeposit ->push_back(theMuon.ecalIsoDeposit()->candEnergy());
      else
	vd_MuonECalIsoDeposit ->push_back(-999.);

      if (theMuon.hcalIsoDeposit())
	vd_MuonHCalIsoDeposit ->push_back(theMuon.hcalIsoDeposit()->candEnergy());
      else
	vd_MuonHCalIsoDeposit ->push_back(-999.);

      if (theMuon.userIsoDeposit(pat::PfAllParticleIso))
	vd_MuonPFAllParticleIsoDeposit ->push_back(theMuon.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_MuonPFAllParticleIsoDeposit ->push_back(-999.);

      if (theMuon.userIsoDeposit(pat::PfChargedHadronIso))
	vd_MuonPFChargedHadronIsoDeposit ->push_back(theMuon.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_MuonPFChargedHadronIsoDeposit ->push_back(-999.);

      if (theMuon.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_MuonPFNeutralHadronIsoDeposit ->push_back(theMuon.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_MuonPFNeutralHadronIsoDeposit ->push_back(-999.);

      if (theMuon.userIsoDeposit(pat::PfGammaIso))
	vd_MuonPFGammaIsoDeposit ->push_back(theMuon.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_MuonPFGammaIsoDeposit ->push_back(-999.);

      vd_MuonECalIsoDepositR03->push_back(theMuon.isolationR03().emVetoEt);
      vd_MuonHCalIsoDepositR03->push_back(theMuon.isolationR03().hadVetoEt);

      //Muon classification variables
      int muonIDisGlobal  = theMuon.isGlobalMuon() ? 1 : 0;
      int muonIDisSA      = theMuon.isStandAloneMuon() ? 1 : 0;
      int muonIDisTrk     = theMuon.isTrackerMuon() ? 1 : 0;
      int muonIDGMPT      = theMuon.muonID("GlobalMuonPromptTight") ? 1 : 0;
      int muonIDAA        = theMuon.muonID("AllArbitrated") ? 1 : 0;
      int muonIDTMA       = theMuon.muonID("TrackerMuonArbitrated") ? 1 : 0;
      int muonIDTMSL      = theMuon.muonID("TMLastStationLoose") ? 1 : 0;
      int muonIDTMST      = theMuon.muonID("TMLastStationTight") ? 1 : 0;
      int muonIDTM2CL     = theMuon.muonID("TM2DCompatibilityLoose") ? 1 : 0;
      int muonIDTM2CT     = theMuon.muonID("TM2DCompatibilityTight") ? 1 : 0;
      int muonIDTMOSL     = theMuon.muonID("TMOneStationLoose") ? 1 : 0;
      int muonIDTMOST     = theMuon.muonID("TMOneStationTight") ? 1 : 0;
      int muonIDTMLSOL    = theMuon.muonID("TMLastStationOptimizedLowPtLoose") ? 1 : 0;
      int muonIDTMLSOT    = theMuon.muonID("TMLastStationOptimizedLowPtTight") ? 1 : 0;
      int muonIDGMTrkChiC = theMuon.muonID("GMTkChiCompatibility") ? 1 : 0;
      int muonIDGMStaChiC = theMuon.muonID("GMStaChiCompatibility") ? 1 : 0;
      int muonIDGMTkKT    = theMuon.muonID("GMTkKinkTight") ? 1 : 0;
      int muonIDTMLSAngL  = theMuon.muonID("TMLastStationAngLoose") ? 1 : 0;
      int muonIDTMLSAngT  = theMuon.muonID("TMLastStationAngTight") ? 1 : 0;
      int muonIDTMLSLSOBL = theMuon.muonID("TMLastStationOptimizedBarrelLowPtLoose") ? 1 : 0;
      int muonIDTMLSLSOBT = theMuon.muonID("TMLastStationOptimizedBarrelLowPtTight") ? 1 : 0;


      vb_MuonIsGlobal                              ->push_back(muonIDisGlobal  );
      vb_MuonIsStandAlone                          ->push_back(muonIDisSA      );
      vb_MuonIsTracker                             ->push_back(muonIDisTrk     );
      vb_MuonGlobalMuonPromptTight                 ->push_back(muonIDGMPT      );
      vb_MuonAllArbitrated                         ->push_back(muonIDAA        );
      vb_MuonTrackerMuonArbitrated                 ->push_back(muonIDTMA       );
      vb_MuonTMLastStationLoose                    ->push_back(muonIDTMSL      );
      vb_MuonTMLastStationTight                    ->push_back(muonIDTMST      );
      vb_MuonTM2DCompatibilityLoose                ->push_back(muonIDTM2CL     );
      vb_MuonTM2DCompatibilityTight                ->push_back(muonIDTM2CT     );
      vb_MuonTMOneStationLoose                     ->push_back(muonIDTMOSL     );
      vb_MuonTMOneStationTight                     ->push_back(muonIDTMOST     );
      vb_MuonTMLastStationOptimizedLowPtLoose      ->push_back(muonIDTMLSOL    );
      vb_MuonTMLastStationOptimizedLowPtTight      ->push_back(muonIDTMLSOT    );
      vb_MuonGMTkChiCompatibility                  ->push_back(muonIDGMTrkChiC );
      vb_MuonGMStaChiCompatibility                 ->push_back(muonIDGMStaChiC );
      vb_MuonGMTkKinkTight                         ->push_back(muonIDGMTkKT    );
      vb_MuonTMLastStationAngLoose                 ->push_back(muonIDTMLSAngL  );
      vb_MuonTMLastStationAngTight                 ->push_back(muonIDTMLSAngT  );
      vb_MuonTMLastStationOptimizedBarrelLowPtLoose->push_back(muonIDTMLSLSOBL );
      vb_MuonTMLastStationOptimizedBarrelLowPtTight->push_back(muonIDTMLSLSOBT );
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	vd_MuonCombChi2->push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombNdof->push_back(theMuon.combinedMuon()->ndof());

	vd_MuonCombVx    ->push_back(theMuon.combinedMuon()->vx());
	vd_MuonCombVy    ->push_back(theMuon.combinedMuon()->vy());
	vd_MuonCombVz    ->push_back(theMuon.combinedMuon()->vz());
	vd_MuonCombPVDxy ->push_back(theMuon.combinedMuon()->dxy(pvPoint));
	vd_MuonCombBSDxy ->push_back(theMuon.combinedMuon()->dxy(bsPoint));
      	vd_MuonCombDxy   ->push_back(theMuon.combinedMuon()->dxy());
      	vd_MuonCombDxyErr->push_back(theMuon.combinedMuon()->dxyError());
	vd_MuonCombD0    ->push_back(theMuon.combinedMuon()->d0());
	vd_MuonCombD0Err ->push_back(theMuon.combinedMuon()->d0Error());
	vd_MuonCombDz    ->push_back(theMuon.combinedMuon()->dz());
	vd_MuonCombDzErr ->push_back(theMuon.combinedMuon()->dzError());

	vd_MuonCombPt->push_back(theMuon.combinedMuon()->pt());
	vd_MuonCombPz->push_back(theMuon.combinedMuon()->pz());
	vd_MuonCombP->push_back(theMuon .combinedMuon()->p());
	vd_MuonCombEta->push_back(theMuon.combinedMuon()->eta());
	vd_MuonCombPhi->push_back(theMuon.combinedMuon()->phi());
	vd_MuonCombChi->push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombCharge->push_back(theMuon   .combinedMuon()->charge());
	vd_MuonCombQOverPErr->push_back(theMuon.combinedMuon()->qoverpError());
	vd_MuonCombValidHits->push_back(theMuon.combinedMuon()->numberOfValidHits());
      }
      else {
	vd_MuonCombChi2  ->push_back(-999.);
	vd_MuonCombNdof  ->push_back(-999.);
	vd_MuonCombVx    ->push_back(-999.);
	vd_MuonCombVy    ->push_back(-999.);
	vd_MuonCombVz    ->push_back(-999.);
	vd_MuonCombPVDxy ->push_back(-999.);
	vd_MuonCombBSDxy ->push_back(-999.);
      	vd_MuonCombDxy   ->push_back(-999.);
      	vd_MuonCombDxyErr->push_back(-999.);
	vd_MuonCombD0    ->push_back(-999.);
	vd_MuonCombD0Err ->push_back(-999.);
	vd_MuonCombDz    ->push_back(-999.);
	vd_MuonCombDzErr ->push_back(-999.);
	vd_MuonCombPt->push_back(-999.);
	vd_MuonCombPz->push_back(-999.);
	vd_MuonCombP->push_back(-999.);
	vd_MuonCombEta->push_back(-999.);
	vd_MuonCombPhi->push_back(-999.);
	vd_MuonCombChi->push_back(-999.);
	vd_MuonCombCharge->push_back(-999.);
	vd_MuonCombQOverPErr->push_back(-999.);
	vd_MuonCombValidHits->push_back(-999.);
      }

      //Standalone muon information
      if(theMuon.isStandAloneMuon() && theMuon.standAloneMuon().isNonnull()){
	vd_MuonStandValidHits->push_back(theMuon.standAloneMuon()->found());
	vd_MuonStandLostHits->push_back(theMuon .standAloneMuon()->lost());
	vd_MuonStandPt->push_back(theMuon.standAloneMuon()->pt());
	vd_MuonStandPz->push_back(theMuon.standAloneMuon()->pz());
	vd_MuonStandP->push_back(theMuon .standAloneMuon()->p());
	vd_MuonStandEta->push_back(theMuon.standAloneMuon()->eta());
	vd_MuonStandPhi->push_back(theMuon.standAloneMuon()->phi());
	vd_MuonStandChi->push_back(theMuon.standAloneMuon()->chi2());
	vd_MuonStandCharge->push_back(theMuon   .standAloneMuon()->charge());
	vd_MuonStandQOverPErr->push_back(theMuon.standAloneMuon()->qoverpError());
      } 
      else{
	vd_MuonStandValidHits->push_back(-999.);
	vd_MuonStandLostHits->push_back(-999.);
	vd_MuonStandPt->push_back(-999.);
	vd_MuonStandPz->push_back(-999.);
	vd_MuonStandP->push_back(-999.);
	vd_MuonStandEta->push_back(-999.);
	vd_MuonStandPhi->push_back(-999.);
	vd_MuonStandChi->push_back(-999.);
	vd_MuonStandCharge->push_back(-999.);
	vd_MuonStandQOverPErr->push_back(-999.);
      }

      /*
      //Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.track().isNonnull()){
	vd_MuonTrkChiNorm  ->push_back(theMuon.track()->normalizedChi2());
	vd_MuonTrkValidHits->push_back(theMuon.track()->found());
	vd_MuonTrkLostHits ->push_back(theMuon.track()->lost());
	vd_MuonTrkPVDxy    ->push_back(theMuon.track()->dxy(pvPoint));
	vd_MuonTrkBSDxy    ->push_back(theMuon.track()->dxy(bsPoint));
      	vd_MuonTrkDxy      ->push_back(theMuon.track()->dxy());
      	vd_MuonTrkDxyErr   ->push_back(theMuon.track()->dxyError());
	vd_MuonTrkD0       ->push_back(theMuon.track()->d0());
	vd_MuonTrkD0Err    ->push_back(theMuon.track()->d0Error());
	vd_MuonTrkDz       ->push_back(theMuon.track()->dz());
	vd_MuonTrkDzErr    ->push_back(theMuon.track()->dzError());
	vd_MuonTrkPt       ->push_back(theMuon.track()->pt());
	vd_MuonTrkPz       ->push_back(theMuon.track()->pz());
	vd_MuonTrkP        ->push_back(theMuon.track()->p());
	vd_MuonTrkEta      ->push_back(theMuon.track()->eta());
	vd_MuonTrkPhi      ->push_back(theMuon.track()->phi());
	vd_MuonTrkChi      ->push_back(theMuon.track()->chi2());
	vd_MuonTrkCharge   ->push_back(theMuon.track()->charge());
	vd_MuonTrkQOverPErr->push_back(theMuon.track()->qoverpError());
	vd_MuonTrkOuterZ   ->push_back(theMuon.track()->outerZ());
	vd_MuonTrkOuterR   ->push_back(theMuon.track()->outerRadius());
      }
      else{
	vd_MuonTrkChiNorm->push_back(-999.);
	vd_MuonTrkValidHits->push_back(-999.);
	vd_MuonTrkLostHits->push_back(-999.);
	vd_MuonTrkPVDxy  ->push_back(-999.);
	vd_MuonTrkBSDxy  ->push_back(-999.);
      	vd_MuonTrkDxy    ->push_back(-999.);
      	vd_MuonTrkDxyErr ->push_back(-999.);
	vd_MuonTrkD0    ->push_back(-999.);
	vd_MuonTrkD0Err ->push_back(-999.);
	vd_MuonTrkDz    ->push_back(-999.);
	vd_MuonTrkDzErr ->push_back(-999.);
	vd_MuonTrkPt    ->push_back(-999.);
	vd_MuonTrkPz    ->push_back(-999.);
	vd_MuonTrkP     ->push_back(-999.);
	vd_MuonTrkEta   ->push_back(-999.);
	vd_MuonTrkPhi   ->push_back(-999.);
	vd_MuonTrkChi   ->push_back(-999.);
	vd_MuonTrkCharge->push_back(-999.);
	vd_MuonTrkQOverPErr->push_back(-999.);
	vd_MuonTrkOuterZ->push_back(-999.);
	vd_MuonTrkOuterR->push_back(-999.);
      }
      */

      //Picky Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.pickyMuon().isNonnull()){
	vd_MuonPickyTrkChiNorm  ->push_back(theMuon.pickyMuon()->normalizedChi2());
	vd_MuonPickyTrkValidHits->push_back(theMuon.pickyMuon()->found());
	vd_MuonPickyTrkLostHits ->push_back(theMuon.pickyMuon()->lost());
	vd_MuonPickyTrkPVDxy    ->push_back(theMuon.pickyMuon()->dxy(pvPoint));
	vd_MuonPickyTrkBSDxy    ->push_back(theMuon.pickyMuon()->dxy(bsPoint));
      	vd_MuonPickyTrkDxy      ->push_back(theMuon.pickyMuon()->dxy());
      	vd_MuonPickyTrkDxyErr   ->push_back(theMuon.pickyMuon()->dxyError());
	vd_MuonPickyTrkD0       ->push_back(theMuon.pickyMuon()->d0());
	vd_MuonPickyTrkD0Err    ->push_back(theMuon.pickyMuon()->d0Error());
	vd_MuonPickyTrkDz       ->push_back(theMuon.pickyMuon()->dz());
	vd_MuonPickyTrkDzErr    ->push_back(theMuon.pickyMuon()->dzError());
	vd_MuonPickyTrkPt       ->push_back(theMuon.pickyMuon()->pt());
	vd_MuonPickyTrkPz       ->push_back(theMuon.pickyMuon()->pz());
	vd_MuonPickyTrkP        ->push_back(theMuon.pickyMuon()->p());
	vd_MuonPickyTrkEta      ->push_back(theMuon.pickyMuon()->eta());
	vd_MuonPickyTrkPhi      ->push_back(theMuon.pickyMuon()->phi());
	vd_MuonPickyTrkChi      ->push_back(theMuon.pickyMuon()->chi2());
	vd_MuonPickyTrkCharge   ->push_back(theMuon.pickyMuon()->charge());
	vd_MuonPickyTrkQOverPErr->push_back(theMuon.pickyMuon()->qoverpError());
	vd_MuonPickyTrkOuterZ   ->push_back(theMuon.pickyMuon()->outerZ());
	vd_MuonPickyTrkOuterR   ->push_back(theMuon.pickyMuon()->outerRadius());
      }
      else{
 	vd_MuonPickyTrkChiNorm->push_back(-999.);
	vd_MuonPickyTrkValidHits->push_back(-999.);
	vd_MuonPickyTrkLostHits->push_back(-999.);
	vd_MuonPickyTrkPVDxy  ->push_back(-999.);
	vd_MuonPickyTrkBSDxy  ->push_back(-999.);
      	vd_MuonPickyTrkDxy    ->push_back(-999.);
      	vd_MuonPickyTrkDxyErr ->push_back(-999.);
	vd_MuonPickyTrkD0    ->push_back(-999.);
	vd_MuonPickyTrkD0Err ->push_back(-999.);
	vd_MuonPickyTrkDz    ->push_back(-999.);
	vd_MuonPickyTrkDzErr ->push_back(-999.);
	vd_MuonPickyTrkPt    ->push_back(-999.);
	vd_MuonPickyTrkPz    ->push_back(-999.);
	vd_MuonPickyTrkP     ->push_back(-999.);
	vd_MuonPickyTrkEta   ->push_back(-999.);
	vd_MuonPickyTrkPhi   ->push_back(-999.);
	vd_MuonPickyTrkChi   ->push_back(-999.);
	vd_MuonPickyTrkCharge->push_back(-999.);
	vd_MuonPickyTrkQOverPErr->push_back(-999.);
	vd_MuonPickyTrkOuterZ->push_back(-999.);
	vd_MuonPickyTrkOuterR->push_back(-999.);
      }

      /*
      //TPFMS Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.tpfmsMuon().isNonnull()){
	vd_MuonTPFMSTrkChiNorm  ->push_back(theMuon.tpfmsMuon()->normalizedChi2());
	vd_MuonTPFMSTrkValidHits->push_back(theMuon.tpfmsMuon()->found());
	vd_MuonTPFMSTrkLostHits ->push_back(theMuon.tpfmsMuon()->lost());
	vd_MuonTPFMSTrkPVDxy    ->push_back(theMuon.tpfmsMuon()->dxy(pvPoint));
	vd_MuonTPFMSTrkBSDxy    ->push_back(theMuon.tpfmsMuon()->dxy(bsPoint));
      	vd_MuonTPFMSTrkDxy      ->push_back(theMuon.tpfmsMuon()->dxy());
      	vd_MuonTPFMSTrkDxyErr   ->push_back(theMuon.tpfmsMuon()->dxyError());
	vd_MuonTPFMSTrkD0       ->push_back(theMuon.tpfmsMuon()->d0());
	vd_MuonTPFMSTrkD0Err    ->push_back(theMuon.tpfmsMuon()->d0Error());
	vd_MuonTPFMSTrkDz       ->push_back(theMuon.tpfmsMuon()->dz());
	vd_MuonTPFMSTrkDzErr    ->push_back(theMuon.tpfmsMuon()->dzError());
	vd_MuonTPFMSTrkPt       ->push_back(theMuon.tpfmsMuon()->pt());
	vd_MuonTPFMSTrkPz       ->push_back(theMuon.tpfmsMuon()->pz());
	vd_MuonTPFMSTrkP        ->push_back(theMuon.tpfmsMuon()->p());
	vd_MuonTPFMSTrkEta      ->push_back(theMuon.tpfmsMuon()->eta());
	vd_MuonTPFMSTrkPhi      ->push_back(theMuon.tpfmsMuon()->phi());
	vd_MuonTPFMSTrkChi      ->push_back(theMuon.tpfmsMuon()->chi2());
	vd_MuonTPFMSTrkCharge   ->push_back(theMuon.tpfmsMuon()->charge());
	vd_MuonTPFMSTrkQOverPErr->push_back(theMuon.tpfmsMuon()->qoverpError());
	vd_MuonTPFMSTrkOuterZ   ->push_back(theMuon.tpfmsMuon()->outerZ());
	vd_MuonTPFMSTrkOuterR   ->push_back(theMuon.tpfmsMuon()->outerRadius());
      }
      else{
	vd_MuonTPFMSTrkChiNorm->push_back(-999.);
	vd_MuonTPFMSTrkValidHits->push_back(-999.);
	vd_MuonTPFMSTrkLostHits->push_back(-999.);
	vd_MuonTPFMSTrkPVDxy  ->push_back(-999.);
	vd_MuonTPFMSTrkBSDxy  ->push_back(-999.);
      	vd_MuonTPFMSTrkDxy    ->push_back(-999.);
      	vd_MuonTPFMSTrkDxyErr ->push_back(-999.);
	vd_MuonTPFMSTrkD0    ->push_back(-999.);
	vd_MuonTPFMSTrkD0Err ->push_back(-999.);
	vd_MuonTPFMSTrkDz    ->push_back(-999.);
	vd_MuonTPFMSTrkDzErr ->push_back(-999.);
	vd_MuonTPFMSTrkPt    ->push_back(-999.);
	vd_MuonTPFMSTrkPz    ->push_back(-999.);
	vd_MuonTPFMSTrkP     ->push_back(-999.);
	vd_MuonTPFMSTrkEta   ->push_back(-999.);
	vd_MuonTPFMSTrkPhi   ->push_back(-999.);
	vd_MuonTPFMSTrkChi   ->push_back(-999.);
	vd_MuonTPFMSTrkCharge->push_back(-999.);
	vd_MuonTPFMSTrkQOverPErr->push_back(-999.);
	vd_MuonTPFMSTrkOuterZ->push_back(-999.);
	vd_MuonTPFMSTrkOuterR->push_back(-999.);
      }
      */
  
      //Muon gen particle association variables
      const reco::Candidate* candMuon = theMuon.genLepton();
      if ( candMuon ) {
	vi_MuonGenPdgId->push_back(candMuon->pdgId());
	vi_MuonGenStatus->push_back(candMuon->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candMuon->px(),candMuon->py(),candMuon->pz(),candMuon->energy());
	v_genmuonP4->push_back(genp4);
	
	const reco::Candidate* muonMother = candMuon->mother();
	if( muonMother ) {
	  //is this necessary
	  //while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
	  //if ( muonMother ) {
	  vi_MuonGenMother->push_back(theMuon.genLepton()->mother()->pdgId());
	  vi_MuonGenMotherStatus->push_back(theMuon.genLepton()->mother()->status());
	  //}
	}
      }
      
      else{
	vi_MuonGenPdgId       ->push_back(-999);
	vi_MuonGenStatus      ->push_back(-999);
	vi_MuonGenMother      ->push_back(-999);
	vi_MuonGenMotherStatus->push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	v_genmuonP4->push_back(genp4);
      }
      double muonIsoReq = (vd_MuonTrkIso->at(mu)+vd_MuonECalIso->at(mu)+vd_MuonHCalIso->at(mu))/theMuon.pt();
      if ( muonIsoReq  > muonRelIso_) bool_MuonVeto = bool_MuonVeto || true;
      if ( theMuon.pt() > muonMaxEt_)  bool_MuonVeto = bool_MuonVeto || true;
      ++mu;
    }
  }// end loop over muons
  i_MuonN = mu;

  // get the taus
  edm::Handle< std::vector<pat::Tau> > tauHandle;
  ev.getByLabel(tauTag_, tauHandle);
  if ( !tauHandle.isValid() ) {
    edm::LogWarning("LeptonEvent") << "No Tau results for InputTag " << tauTag_;
    if (debug_) std::cout<<" Tau results for InputTag " << tauTag_<<std::endl;
    return false;
  }

  edm::LogVerbatim("LeptonEvent") << " start reading in taus " << std::endl;
  // Add the taus
  i_TauN = tauHandle->size();
  if (debug_) std::cout<<i_TauN<<" Tau results for InputTag " << tauTag_<<std::endl;
  
  if ( i_TauN > 50 ) i_TauN = 50;
  maintenanceTaus();
  
  (*tauidMap)["electron"       ] = Electron;
  (*tauidMap)["muon"           ] = Muon;
  (*tauidMap)["oneProng0Pi0"   ] = OneProng0Pi0;
  (*tauidMap)["oneProng1Pi0"   ] = OneProng1Pi0;
  (*tauidMap)["oneProng2Pi0"   ] = OneProng2Pi0;
  (*tauidMap)["oneProngOther"  ] = OneProngOther;
  (*tauidMap)["threeProng0Pi0" ] = ThreeProng0Pi0;
  (*tauidMap)["threeProng1Pi0" ] = ThreeProng1Pi0;
  (*tauidMap)["threeProng2Pi0" ] = ThreeProng2Pi0;
  (*tauidMap)["threeProngOther"] = ThreeProngOther;
  (*tauidMap)["rare"           ] = Rare;

  int tau = 0;
  for (int i=0;i<i_TauN;i++){
    const::pat::Tau& theTau = (*tauHandle)[i];
    if ( (theTau.pt() > tauMinEt_) && !(theTau.eta() > tauMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good taus " << std::endl;
      v_tauP4->push_back(theTau.p4());
      vd_TauCharge->push_back(theTau.charge());
      
      vd_TauTrkIso ->push_back(theTau.trackIso());
      vd_TauECalIso->push_back(theTau.ecalIso());
      vd_TauHCalIso->push_back(theTau.hcalIso());
      vd_TauAllIso ->push_back(theTau.caloIso());
      
      //Special PF based isolation variables
      vd_TauPFAllParticleIso  ->push_back(theTau.particleIso());
      vd_TauPFChargedHadronIso->push_back(theTau.chargedHadronIso());
      vd_TauPFNeutralHadronIso->push_back(theTau.neutralHadronIso());
      vd_TauPFGammaIso        ->push_back(theTau.photonIso());

      if (theTau.trackIsoDeposit())
	vd_TauTrkIsoDeposit ->push_back(theTau.trackIsoDeposit()->candEnergy());
      else
	vd_TauTrkIsoDeposit ->push_back(-999.);

      if (theTau.ecalIsoDeposit())
	vd_TauECalIsoDeposit ->push_back(theTau.ecalIsoDeposit()->candEnergy());
      else
	vd_TauECalIsoDeposit ->push_back(-999.);

      if (theTau.hcalIsoDeposit())
	vd_TauHCalIsoDeposit ->push_back(theTau.hcalIsoDeposit()->candEnergy());
      else
	vd_TauHCalIsoDeposit ->push_back(-999.);

      if (theTau.userIsoDeposit(pat::PfAllParticleIso))
	vd_TauPFAllParticleIsoDeposit ->push_back(theTau.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_TauPFAllParticleIsoDeposit ->push_back(-999.);

      if (theTau.userIsoDeposit(pat::PfChargedHadronIso))
	vd_TauPFChargedHadronIsoDeposit ->push_back(theTau.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_TauPFChargedHadronIsoDeposit ->push_back(-999.);

      if (theTau.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_TauPFNeutralHadronIsoDeposit ->push_back(theTau.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_TauPFNeutralHadronIsoDeposit ->push_back(-999.);

      if (theTau.userIsoDeposit(pat::PfGammaIso))
	vd_TauPFGammaIsoDeposit ->push_back(theTau.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_TauPFGammaIsoDeposit ->push_back(-999.);
      
      vi_TauSigTrk ->push_back(theTau.signalTracks().size());  
      vd_TauVx     ->push_back(theTau.vx());
      vd_TauVy     ->push_back(theTau.vy());
      vd_TauVz     ->push_back(theTau.vz());

      if (theTau.leadTrack().isNonnull()) {
      	vd_TauPVDxy  ->push_back(theTau.leadTrack()->dxy(pvPoint));
      	vd_TauBSDxy  ->push_back(theTau.leadTrack()->dxy(bsPoint));
      	vd_TauDxy    ->push_back(theTau.leadTrack()->dxy());
      	vd_TauDxyErr ->push_back(theTau.leadTrack()->dxyError());
      	vd_TauD0     ->push_back(theTau.leadTrack()->d0());
      	vd_TauD0Err  ->push_back(theTau.leadTrack()->d0Error());
      	vd_TauDz     ->push_back(theTau.leadTrack()->dz());
      	vd_TauDzErr  ->push_back(theTau.leadTrack()->dzError());
      }
      else {
	//edm::LogWarning("LeptonEvent") << "Tau leadTrack is Null";
      	vd_TauPVDxy ->push_back(-999.);
      	vd_TauBSDxy ->push_back(-999.);
      	vd_TauDxy   ->push_back(-999.);
      	vd_TauDxyErr->push_back(-999.);
      	vd_TauD0    ->push_back(-999.);
      	vd_TauD0Err ->push_back(-999.);
      	vd_TauDz    ->push_back(-999.);
      	vd_TauDzErr ->push_back(-999.);
      }
      vd_TauIdElec         ->push_back(theTau.tauID("againstElectron"));
      vd_TauIdMuon         ->push_back(theTau.tauID("againstMuon"));

      vd_TauIdIso          ->push_back(theTau.tauID("byIsolation"));
      vd_TauIdIsoLeadPi    ->push_back(theTau.tauID("byIsolationUsingLeadingPion"));

      vd_TauIdEcalIso      ->push_back(theTau.tauID("ecalIsolation"));
      vd_TauIdEcalIsoLeadPi->push_back(theTau.tauID("ecalIsolationUsingLeadingPion"));

      vd_TauIdLeadPiPt     ->push_back(theTau.tauID("leadingPionPtCut"));
      vd_TauIdLeadTrk      ->push_back(theTau.tauID("leadingTrackFinding"));
      vd_TauIdLeadTrkPt    ->push_back(theTau.tauID("leadingTrackPtCut"));

      vd_TauIdTrkIso       ->push_back(theTau.tauID("trackIsolation"));
      vd_TauIdTrkIsoLeadPi ->push_back(theTau.tauID("trackIsolationUsingLeadingPion"));

      //
      vd_TauIdNCfrHalf   ->push_back(theTau.tauID("byTaNCfrHalfPercent"));
      vd_TauIdNCfrQuarter->push_back(theTau.tauID("byTaNCfrQuarterPercent"));
      vd_TauIdNCfrTenth  ->push_back(theTau.tauID("byTaNCfrTenthPercent"));
      vd_TauIdNCfrFull   ->push_back(theTau.tauID("byTaNCfrOnePercent"));

      //Calo specific information
      if (theTau.isCaloTau()) {
	vd_TauCaloLeadTrkSignedIP      ->push_back(theTau.leadTracksignedSipt());
	vd_TauCaloLeadTrkHcal3x3EtSum  ->push_back(theTau.leadTrackHCAL3x3hitsEtSum());
	vd_TauCaloLeadTrkHcal3x3HotDEta->push_back(theTau.leadTrackHCAL3x3hottesthitDEta());
	vd_TauCaloSignalTrkMInv        ->push_back(theTau.signalTracksInvariantMass());
	vd_TauCaloTrkMInv              ->push_back(theTau.TracksInvariantMass());
	vd_TauCaloIsoTrkPtSum          ->push_back(theTau.isolationTracksPtSum());
	vd_TauCaloIsoEcalEtSum         ->push_back(theTau.isolationECALhitsEtSum());
	vd_TauCaloMaxEtHCAL            ->push_back(theTau.maximumHCALhitEt());
      }

      if (theTau.isPFTau()) {
	vd_TrkPFIsoChargedHadPtSum->push_back(theTau.isolationPFChargedHadrCandsPtSum());
	vd_TrkPFIsoGammaEtSum     ->push_back(theTau.isolationPFGammaCandsEtSum());
	vd_TrkPFHcalClusterMaxEt  ->push_back(theTau.maximumHCALPFClusterEt());
	vd_TrkPFEFrac_em          ->push_back(theTau.emFraction());
	vd_TrkPFHcalTotalOverPLead->push_back(theTau.hcalTotOverPLead());
	vd_TrkPFHcalMaxOverPLead  ->push_back(theTau.hcalMaxOverPLead());
	vd_TrkPFHcal3x3OverPLead  ->push_back(theTau.hcal3x3OverPLead());
	vd_TrkPFEcalStripOverPLead->push_back(theTau.ecalStripSumEOverPLead());
	vd_TrkPFBremRecOverPLead  ->push_back(theTau.bremsRecoveryEOverPLead());
	vd_TrkPFElePreIDOut       ->push_back(theTau.electronPreIDOutput());
	vd_TrkPFMuonCaloComp      ->push_back(theTau.caloComp());
	vd_TrkPFMuonSegComp       ->push_back(theTau.segComp());
      }

      vd_TauEtaEtaMom->push_back(theTau.etaetaMoment());
      vd_TauPhiPhiMom->push_back(theTau.phiphiMoment());
      vd_TauEtaPhiMom->push_back(theTau.etaphiMoment());

      //get associated gen particle information
      const reco::Candidate* candTau    = theTau.genLepton();
      if ( candTau ) {
	vi_TauGenPdgId ->push_back(candTau->pdgId());
	vi_TauGenStatus->push_back(candTau->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candTau->px(),candTau->py(),candTau->pz(),candTau->energy());
	v_gentauP4->push_back(genp4);
	const reco::Candidate* tauMother = candTau->mother();
	if( tauMother ) {
	  //is this necessary
	  //while (tauMother->pdgId() == candTau->pdgId()) tauMother = tauMother->mother();
	  //if ( tauMother ) {
	  vi_TauGenMother->push_back(theTau.genLepton()->mother()->pdgId());
	  vi_TauGenMotherStatus->push_back(theTau.genLepton()->mother()->status());
	  //}
	}
      }
      else {
	vi_TauGenPdgId->push_back(-999);
	vi_TauGenMother->push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_gentauP4->push_back(genp4);
      }

      const reco::Candidate* candTauJet = theTau.genJet();
      if (candTauJet) {
	reco::Candidate::LorentzVector genjetp4;
	genjetp4.SetPxPyPzE(candTauJet->px(),candTauJet->py(),candTauJet->pz(),candTauJet->energy());
	v_gentaujetP4->push_back(genjetp4);
	
	const reco::CompositePtrCandidate *TauGenID = theTau.genJet();
	std::string genTauDecayMode = JetMCTagUtils::genTauDecayMode(*TauGenID);
	
	switch((*tauidMap)[genTauDecayMode]) {
	case Electron:
	  vi_TauGen->push_back(1);
	  break;
	case Muon:
	  vi_TauGen->push_back(2);
	  break;
	case OneProng0Pi0:
	  vi_TauGen->push_back(3);
	  break;
	case OneProng1Pi0:
	  vi_TauGen->push_back(4);
	  break;
	case OneProng2Pi0:
	  vi_TauGen->push_back(5);
	  break;
	case OneProngOther:
	  vi_TauGen->push_back(6);
	  break;
	case ThreeProng0Pi0:
	  vi_TauGen->push_back(7);
	  break;
	case ThreeProng1Pi0:
	  vi_TauGen->push_back(8);
	  break;
	case ThreeProng2Pi0:
	  vi_TauGen->push_back(9);
	  break;
	case ThreeProngOther:
	  vi_TauGen->push_back(10);
	  break;
	case Rare:
	  vi_TauGen->push_back(11);
	  break;
	default:
	  vi_TauGen->push_back(12);
	}
      }
      else {
	reco::Candidate::LorentzVector genjetp4;
	genjetp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_gentaujetP4->push_back(genjetp4);
	vi_TauGen->push_back(-999);
      }

      double tauIsoReq = (vd_TauTrkIso->at(tau)+vd_TauECalIso->at(tau)+vd_TauHCalIso->at(tau))/theTau.pt();
      if ( tauIsoReq  > tauRelIso_) bool_TauVeto = bool_TauVeto || true;
      if ( theTau.pt() > tauMaxEt_ ) bool_TauVeto = bool_TauVeto || true;
      ++tau;
    }
  }

  // return true when none of the events have leptons above threshold
  lepton_result = !(bool_ElecVeto || bool_MuonVeto || bool_TauVeto);
  //mLeptonData->Fill();
  if (debug_)
    std::cout<<"Done analyzing leptons"<<std::endl;
  return lepton_result;
  }

//________________________________________________________________________________________
void LeptonAnalyzerPAT::bookTTree(TTree* mLeptonData) {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Add the branches
  //add electrons
  mLeptonData->Branch(prefix_+"ElecVeto", &bool_ElecVeto, prefix_+"ElecVeto/O");
  //General electron information
  mLeptonData->Branch(prefix_+"ElectronP4", &(*v_elecP4.get() ) );
  mLeptonData->Branch(prefix_+"ElecN",      &i_ElecN, prefix_+"ElecN/I");  
  
  mLeptonData->Branch(prefix_+"ElecdB",    &(*vd_ElecdB.get() ) );
  mLeptonData->Branch(prefix_+"ElecdBerr", &(*vd_ElecdBerr.get() ) );

  mLeptonData->Branch(prefix_+"ElecCharge", &(*vd_ElecCharge.get() ) );
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"ElecTrkIso",     &(*vd_ElecTrkIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecECalIso",    &(*vd_ElecECalIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecHCalIso",    &(*vd_ElecHCalIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecAllIso",     &(*vd_ElecAllIso.get() ) );

  mLeptonData->Branch(prefix_+"ElecPFAllParticleIso",   &(*vd_ElecPFAllParticleIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFChargedHadronIso", &(*vd_ElecPFChargedHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFNeutralHadronIso", &(*vd_ElecPFNeutralHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFGammaIso",         &(*vd_ElecPFGammaIso.get() ) );

  mLeptonData->Branch(prefix_+"ElecTrkIsoDeposit",     &(*vd_ElecTrkIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"ElecECalIsoDeposit",    &(*vd_ElecECalIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"ElecHCalIsoDeposit",    &(*vd_ElecHCalIsoDeposit.get() ) );

  mLeptonData->Branch(prefix_+"ElecPFAllParticleIsoDeposit",   &(*vd_ElecPFAllParticleIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFChargedHadronIsoDeposit", &(*vd_ElecPFChargedHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFNeutralHadronIsoDeposit", &(*vd_ElecPFNeutralHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"ElecPFGammaIsoDeposit",         &(*vd_ElecPFGammaIsoDeposit.get() ) );

  mLeptonData->Branch(prefix_+"ElecTrkChiNorm", &(*vd_ElecNormChi2.get() ) );
  
  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    &(*vd_ElecIdLoose.get() ) );
  mLeptonData->Branch(prefix_+"ElecIdTight",    &(*vd_ElecIdTight.get() ) );
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", &(*vd_ElecIdRobLoose.get() ) );
  mLeptonData->Branch(prefix_+"ElecIdRobTight", &(*vd_ElecIdRobTight.get() ) );
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", &(*vd_ElecIdRobHighE.get() ) );
  mLeptonData->Branch(prefix_+"ElecChargeMode", &(*vd_ElecChargeMode.get() ) );
  mLeptonData->Branch(prefix_+"ElecPtMode",     &(*vd_ElecPtTrkMode.get() ) );
  
  mLeptonData->Branch(prefix_+"ElecE2OverE9",      &(*vd_ElecE2OverE9.get() ) );
  mLeptonData->Branch(prefix_+"ElecSwissCross",    &(*vd_ElecSwissCross.get() ) );

  mLeptonData->Branch(prefix_+"ElecE1x5",    &(*vd_ElecE1x5.get() ) );
  mLeptonData->Branch(prefix_+"ElecE5x5",    &(*vd_ElecE5x5.get() ) );
  mLeptonData->Branch(prefix_+"ElecE2x5Max",    &(*vd_ElecE2x5Max.get() ) );
  mLeptonData->Branch(prefix_+"ElecFbrem",    &(*vd_ElecFbrem.get() ) );

  mLeptonData->Branch(prefix_+"ElecSigmaEtaEta",    &(*vd_ElecSigmaEtaEta.get() ) );
  mLeptonData->Branch(prefix_+"ElecSigmaIetaIeta",    &(*vd_ElecSigmaIetaIeta.get() ) );
  mLeptonData->Branch(prefix_+"ElecHadOverEM",    &(*vd_ElecHadOverEM.get() ) );

  mLeptonData->Branch(prefix_+"ElecTSeed",    &(*vd_ElecTSeed.get() ) );
  mLeptonData->Branch(prefix_+"ElecESeed",    &(*vd_ElecESeed.get() ) );

  
  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     &(*vd_ElecVx.get() ) );
  mLeptonData->Branch(prefix_+"ElecVy",     &(*vd_ElecVy.get() ) );
  mLeptonData->Branch(prefix_+"ElecVz",     &(*vd_ElecVz.get() ) );
  mLeptonData->Branch(prefix_+"ElecPVDxy",  &(*vd_ElecPVDxy.get() ) );
  mLeptonData->Branch(prefix_+"ElecBSDxy",  &(*vd_ElecBSDxy.get() ) );
  mLeptonData->Branch(prefix_+"ElecDxy",    &(*vd_ElecDxy.get() ) );
  mLeptonData->Branch(prefix_+"ElecDxyErr", &(*vd_ElecDxyErr.get() ) );
  mLeptonData->Branch(prefix_+"ElecD0",     &(*vd_ElecD0.get() ) );
  mLeptonData->Branch(prefix_+"ElecD0Err",  &(*vd_ElecD0Err.get() ) );
  mLeptonData->Branch(prefix_+"ElecDz",     &(*vd_ElecDz.get() ) );
  mLeptonData->Branch(prefix_+"ElecDzErr",  &(*vd_ElecDzErr.get() ) );
  mLeptonData->Branch(prefix_+"ElecPtTrk",  &(*vd_ElecPtTrk.get() ) );
  
  //Additonal electron detector information
  //Electron tracking information
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrkMode", &(*vd_ElecQOverPErrTrkMode.get() ) );
  mLeptonData->Branch(prefix_+"ElecCaloEnergy",       &(*vd_ElecCaloEnergy.get() ) );
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrk",     &(*vd_ElecQOverPErrTrk.get() ) );
  mLeptonData->Branch(prefix_+"ElecPinTrk",           &(*vd_ElecPinTrk.get() ) );
  mLeptonData->Branch(prefix_+"ElecPoutTrk",          &(*vd_ElecPoutTrk.get() ) );
  mLeptonData->Branch(prefix_+"ElecLostHits",         &(*vd_ElecLostHits.get() ) );
  mLeptonData->Branch(prefix_+"ElecValidHits",        &(*vd_ElecValidHits.get() ) );
  //mLeptonData->Branch(prefix_+"ElecNCluster",         &(*vd_ElecNCluster.get() ) );
  mLeptonData->Branch(prefix_+"ElecEtaTrk",           &(*vd_ElecEtaTrk.get() ) );
  mLeptonData->Branch(prefix_+"ElecPhiTrk",           &(*vd_ElecPhiTrk.get() ) );
  mLeptonData->Branch(prefix_+"ElecWidthClusterEta",  &(*vd_ElecWidthClusterEta.get() ) );
  mLeptonData->Branch(prefix_+"ElecWidthClusterPhi",  &(*vd_ElecWidthClusterPhi.get() ) );
  mLeptonData->Branch(prefix_+"ElecSCEta",  &(*vd_ElecSCEta .get() ) );
  mLeptonData->Branch(prefix_+"ElecSCPhi",  &(*vd_ElecSCPhi .get() ) );
  mLeptonData->Branch(prefix_+"ElecSCEn",   &(*vd_ElecSCEn  .get() ) );
  mLeptonData->Branch(prefix_+"ElecSCPt",   &(*vd_ElecSCPt  .get() ) );
  mLeptonData->Branch(prefix_+"ElecSCRawE", &(*vd_ElecSCRawE.get() ) );
  
  //Generator level information stored in the electron object
  mLeptonData->Branch(prefix_+"ElecGenP4",           &(*v_genelecP4.get() ) );
  mLeptonData->Branch(prefix_+"ElecGenPdgId",        &(*vi_ElecGenPdgId.get() ) );
  mLeptonData->Branch(prefix_+"ElecGenStatus",       &(*vi_ElecGenStatus.get() ) );
  mLeptonData->Branch(prefix_+"ElecGenMother",       &(*vi_ElecGenMother.get() ) );
  mLeptonData->Branch(prefix_+"ElecGenMotherStatus", &(*vi_ElecGenMotherStatus.get() ) );

  //add muons
  mLeptonData->Branch(prefix_+"MuonVeto", &bool_MuonVeto, prefix_+"MuonVeto/O");
  //General kinematic variables related to muons
  mLeptonData->Branch(prefix_+"MuonP4",        &(*v_muonP4.get() ) );
  mLeptonData->Branch(prefix_+"MuonN",         &i_MuonN,  prefix_+"MuonN/I");  
  
  mLeptonData->Branch(prefix_+"MuondB",    &(*vd_MuondB.get() ) );
  mLeptonData->Branch(prefix_+"MuondBerr", &(*vd_MuondBerr.get() ) );

  mLeptonData->Branch(prefix_+"MuonCharge",    &(*vd_MuonCharge.get() ) );
  
  //Muon isolation variables
  //mLeptonData->Branch("NIsomuon",      &m_NIsomuon,       "NIsomuon/I");  
  mLeptonData->Branch(prefix_+"MuonTrkIso",     &(*vd_MuonTrkIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonECalIso",    &(*vd_MuonECalIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonHCalIso",    &(*vd_MuonHCalIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonAllIso",     &(*vd_MuonAllIso.get() ) );

  mLeptonData->Branch(prefix_+"MuonPFAllParticleIso",   &(*vd_MuonPFAllParticleIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFChargedHadronIso", &(*vd_MuonPFChargedHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFNeutralHadronIso", &(*vd_MuonPFNeutralHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFGammaIso",         &(*vd_MuonPFGammaIso.get() ) );

  mLeptonData->Branch(prefix_+"MuonTrkIsoDeposit",     &(*vd_MuonTrkIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonECalIsoDeposit",    &(*vd_MuonECalIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonHCalIsoDeposit",    &(*vd_MuonHCalIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonECalIsoDeposit", &(*vd_MuonECalIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonHCalIsoDeposit", &(*vd_MuonHCalIsoDeposit.get() ) );

  mLeptonData->Branch(prefix_+"MuonPFAllParticleIsoDeposit",   &(*vd_MuonPFAllParticleIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFChargedHadronIsoDeposit", &(*vd_MuonPFChargedHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFNeutralHadronIsoDeposit", &(*vd_MuonPFNeutralHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"MuonPFGammaIsoDeposit",         &(*vd_MuonPFGammaIsoDeposit.get() ) );


  //Muon calorimeter type
  mLeptonData->Branch(prefix_+"MuonIsGlobal",                              &(*vb_MuonIsGlobal.get() ) );
  mLeptonData->Branch(prefix_+"MuonIsStandAlone",                          &(*vb_MuonIsStandAlone.get() ) );
  mLeptonData->Branch(prefix_+"MuonIsTracker",                             &(*vb_MuonIsTracker.get() ) );
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonGlobalMuonPromptTight",                 &(*vb_MuonGlobalMuonPromptTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonAllArbitrated",                         &(*vb_MuonAllArbitrated.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrackerMuonArbitrated",                 &(*vb_MuonTrackerMuonArbitrated.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationLoose",                    &(*vb_MuonTMLastStationLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationTight",                    &(*vb_MuonTMLastStationTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityLoose",                &(*vb_MuonTM2DCompatibilityLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityTight",                &(*vb_MuonTM2DCompatibilityTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     &(*vb_MuonTMOneStationLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     &(*vb_MuonTMOneStationTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtLoose",      &(*vb_MuonTMLastStationOptimizedLowPtLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtTight",      &(*vb_MuonTMLastStationOptimizedLowPtTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonGMTkChiCompatibility",                  &(*vb_MuonGMTkChiCompatibility.get() ) );
  mLeptonData->Branch(prefix_+"MuonGMStaChiCompatibility",                 &(*vb_MuonGMStaChiCompatibility.get() ) );
  mLeptonData->Branch(prefix_+"MuonGMTkKinkTight",                         &(*vb_MuonGMTkKinkTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngLoose",                 &(*vb_MuonTMLastStationAngLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngTight",                 &(*vb_MuonTMLastStationAngTight.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose",&(*vb_MuonTMLastStationOptimizedBarrelLowPtLoose.get() ) );
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight",&(*vb_MuonTMLastStationOptimizedBarrelLowPtTight.get() ) );
  
  mLeptonData->Branch(prefix_+"MuonCombChi2",  &(*vd_MuonCombChi2.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombNdof",  &(*vd_MuonCombNdof.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombVx",    &(*vd_MuonCombVx.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombVy",    &(*vd_MuonCombVy.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombVz",    &(*vd_MuonCombVz.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombPVDxy", &(*vd_MuonCombPVDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombBSDxy", &(*vd_MuonCombBSDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombDxy",   &(*vd_MuonCombDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombDxyErr",&(*vd_MuonCombDxyErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombD0",    &(*vd_MuonCombD0.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombD0Err", &(*vd_MuonCombD0Err.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombDz",    &(*vd_MuonCombDz.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombDzErr", &(*vd_MuonCombDzErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombPt",        &(*vd_MuonCombPt.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombPz",        &(*vd_MuonCombPz.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombP",         &(*vd_MuonCombP.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombEta",       &(*vd_MuonCombEta.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombPhi",       &(*vd_MuonCombPhi.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombCharge",    &(*vd_MuonCombCharge.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombChi",       &(*vd_MuonCombChi.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombQOverPErr", &(*vd_MuonCombQOverPErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonCombValidHits", &(*vd_MuonCombValidHits.get() ) );
  
  //Muon tracking information
  mLeptonData->Branch(prefix_+"MuonStandValidHits", &(*vd_MuonStandValidHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandLostHits",  &(*vd_MuonStandLostHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandPt",        &(*vd_MuonStandPt.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandPz",        &(*vd_MuonStandPz.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandP",         &(*vd_MuonStandP.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandEta",       &(*vd_MuonStandEta.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandPhi",       &(*vd_MuonStandPhi.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandCharge",    &(*vd_MuonStandCharge.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandChi",       &(*vd_MuonStandChi.get() ) );
  mLeptonData->Branch(prefix_+"MuonStandQOverPErr", &(*vd_MuonStandQOverPErr.get() ) );
  /*
  mLeptonData->Branch(prefix_+"MuonTrkChiNorm", &(*vd_MuonTrkChiNorm.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkValidHits", &(*vd_MuonTrkValidHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",  &(*vd_MuonTrkLostHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPVDxy",     &(*vd_MuonTrkPVDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkBSDxy",     &(*vd_MuonTrkBSDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDxy",       &(*vd_MuonTrkDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDxyErr",    &(*vd_MuonTrkDxyErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkD0",        &(*vd_MuonTrkD0.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkD0Err",     &(*vd_MuonTrkD0Err.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDz",        &(*vd_MuonTrkDz.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDzErr",     &(*vd_MuonTrkDzErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPt",        &(*vd_MuonTrkPt.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPz",        &(*vd_MuonTrkPz.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkP",         &(*vd_MuonTrkP.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkEta",       &(*vd_MuonTrkEta.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPhi",       &(*vd_MuonTrkPhi.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkCharge",    &(*vd_MuonTrkCharge.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkChi",       &(*vd_MuonTrkChi.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkQOverPErr", &(*vd_MuonTrkQOverPErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",    &(*vd_MuonTrkOuterZ.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",    &(*vd_MuonTrkOuterR.get() ) );
  */  
  mLeptonData->Branch(prefix_+"MuonTrkChiNorm",   &(*vd_MuonPickyTrkChiNorm.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkValidHits", &(*vd_MuonPickyTrkValidHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",  &(*vd_MuonPickyTrkLostHits.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPVDxy",     &(*vd_MuonPickyTrkPVDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkBSDxy",     &(*vd_MuonPickyTrkBSDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDxy",       &(*vd_MuonPickyTrkDxy.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDxyErr",    &(*vd_MuonPickyTrkDxyErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkD0",        &(*vd_MuonPickyTrkD0.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkD0Err",     &(*vd_MuonPickyTrkD0Err.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDz",        &(*vd_MuonPickyTrkDz.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkDzErr",     &(*vd_MuonPickyTrkDzErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPt",        &(*vd_MuonPickyTrkPt.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPz",        &(*vd_MuonPickyTrkPz.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkP",         &(*vd_MuonPickyTrkP.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkEta",       &(*vd_MuonPickyTrkEta.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkPhi",       &(*vd_MuonPickyTrkPhi.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkCharge",    &(*vd_MuonPickyTrkCharge.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkChi",       &(*vd_MuonPickyTrkChi.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkQOverPErr", &(*vd_MuonPickyTrkQOverPErr.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",    &(*vd_MuonPickyTrkOuterZ.get() ) );
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",    &(*vd_MuonPickyTrkOuterR.get() ) );
  
  //Generator level muon information
  mLeptonData->Branch(prefix_+"MuonGenP4",           &(*v_genmuonP4.get() ) );
  mLeptonData->Branch(prefix_+"MuonGenPdgId",        &(*vi_MuonGenPdgId.get() ) );
  mLeptonData->Branch(prefix_+"MuonGenStatus",       &(*vi_MuonGenStatus.get() ) );
  mLeptonData->Branch(prefix_+"MuonGenMother",       &(*vi_MuonGenMother.get() ) );
  mLeptonData->Branch(prefix_+"MuonGenMotherStatus", &(*vi_MuonGenMotherStatus.get() ) );
  
  //add taus
  mLeptonData->Branch(prefix_+"TauVeto", &bool_TauVeto, prefix_+"TauVeto/O");
  //General tau information
  mLeptonData->Branch(prefix_+"TauP4", &(*v_tauP4.get() ) );
  mLeptonData->Branch(prefix_+"TauN",  &i_TauN,  prefix_+"TauN/I");  
  
  mLeptonData->Branch(prefix_+"TauCharge", &(*vd_TauCharge.get() ) );
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"TauTrkIso",     &(*vd_TauTrkIso.get() ) );
  mLeptonData->Branch(prefix_+"TauECalIso",    &(*vd_TauECalIso.get() ) );
  mLeptonData->Branch(prefix_+"TauHCalIso",    &(*vd_TauHCalIso.get() ) );
  mLeptonData->Branch(prefix_+"TauAllIso",     &(*vd_TauAllIso.get() ) );

  mLeptonData->Branch(prefix_+"TauPFAllParticleIso",   &(*vd_TauPFAllParticleIso.get() ) );
  mLeptonData->Branch(prefix_+"TauPFChargedHadronIso", &(*vd_TauPFChargedHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"TauPFNeutralHadronIso", &(*vd_TauPFNeutralHadronIso.get() ) );
  mLeptonData->Branch(prefix_+"TauPFGammaIso",         &(*vd_TauPFGammaIso.get() ) );

  mLeptonData->Branch(prefix_+"TauTrkIsoDeposit",     &(*vd_TauTrkIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"TauECalIsoDeposit",    &(*vd_TauECalIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"TauHCalIsoDeposit",    &(*vd_TauHCalIsoDeposit.get() ) );

  mLeptonData->Branch(prefix_+"TauPFAllParticleIsoDeposit",   &(*vd_TauPFAllParticleIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"TauPFChargedHadronIsoDeposit", &(*vd_TauPFChargedHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"TauPFNeutralHadronIsoDeposit", &(*vd_TauPFNeutralHadronIsoDeposit.get() ) );
  mLeptonData->Branch(prefix_+"TauPFGammaIsoDeposit",         &(*vd_TauPFGammaIsoDeposit.get() ) );

  //Tau identification values
  mLeptonData->Branch(prefix_+"TauIdElec",       &(*vd_TauIdElec.get() ) );
  mLeptonData->Branch(prefix_+"TauIdMuon",       &(*vd_TauIdMuon.get() ) );

  mLeptonData->Branch(prefix_+"TauIdIso",       &(*vd_TauIdIso.get() ) );
  mLeptonData->Branch(prefix_+"TauIdIsoLeadPi",       &(*vd_TauIdIsoLeadPi.get() ) );

  mLeptonData->Branch(prefix_+"TauIdEcalIso",       &(*vd_TauIdEcalIso.get() ) );
  mLeptonData->Branch(prefix_+"TauIdEcalIsoLeadPi",       &(*vd_TauIdEcalIsoLeadPi.get() ) );

  mLeptonData->Branch(prefix_+"TauIdLeadPiPt",       &(*vd_TauIdLeadPiPt.get() ) );
  mLeptonData->Branch(prefix_+"TauIdLeadTrk",       &(*vd_TauIdLeadTrk.get() ) );
  mLeptonData->Branch(prefix_+"TauIdLeadTrkPt",       &(*vd_TauIdLeadTrkPt.get() ) );

  mLeptonData->Branch(prefix_+"TauIdTrkIso",       &(*vd_TauIdTrkIso.get() ) );
  mLeptonData->Branch(prefix_+"TauIdTrkIsoLeadPi",       &(*vd_TauIdTrkIsoLeadPi.get() ) );

  mLeptonData->Branch(prefix_+"TauIdNCfrFull",   &(*vd_TauIdNCfrFull.get() ) );
  mLeptonData->Branch(prefix_+"TauIdNCfrHalf",   &(*vd_TauIdNCfrHalf.get() ) );
  mLeptonData->Branch(prefix_+"TauIdNCfrQuarter",&(*vd_TauIdNCfrQuarter.get() ) );
  mLeptonData->Branch(prefix_+"TauIdNCfrTenth",  &(*vd_TauIdNCfrTenth.get() ) );

  //mLeptonData->Branch(prefix_+"TauIdMap",        &(*tauidMap.get() ) );

  mLeptonData->Branch(prefix_+"TauEtaEtaMoment", &(*vd_TauEtaEtaMom.get() ) );
  mLeptonData->Branch(prefix_+"TauPhiPhiMoment", &(*vd_TauPhiPhiMom.get() ) );
  mLeptonData->Branch(prefix_+"TauEtaPhiMoment", &(*vd_TauEtaPhiMom.get() ) );

  //Tau Calo info
  if (prefix_ == "") {
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkSignedIP"      , &(*vd_TauCaloLeadTrkSignedIP      .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkHcal3x3EtSum"  , &(*vd_TauCaloLeadTrkHcal3x3EtSum  .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkHcal3x3HotDEta", &(*vd_TauCaloLeadTrkHcal3x3HotDEta.get() ) );
    mLeptonData->Branch(prefix_+"TauCaloSignalTrkMInv"        , &(*vd_TauCaloSignalTrkMInv        .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloTrkMInv"              , &(*vd_TauCaloTrkMInv              .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloIsoTrkPtSum"          , &(*vd_TauCaloIsoTrkPtSum          .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloIsoEcalEtSum"         , &(*vd_TauCaloIsoEcalEtSum         .get() ) );
    mLeptonData->Branch(prefix_+"TauCaloMaxEtHCAL"            , &(*vd_TauCaloMaxEtHCAL            .get() ) );
  }

  //Tau PF info
  if (prefix_ == "PF" || prefix_ == "PF2PAT") {
    mLeptonData->Branch(prefix_+"TauPFPFIsoChargedHadPtSum", &(*vd_TrkPFIsoChargedHadPtSum.get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFIsoGammaEtSum"     , &(*vd_TrkPFIsoGammaEtSum     .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFHcalClusterMaxEt"  , &(*vd_TrkPFHcalClusterMaxEt  .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFEFrac_em"          , &(*vd_TrkPFEFrac_em          .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFHcalTotalOverPLead", &(*vd_TrkPFHcalTotalOverPLead.get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFHcalMaxOverPLead"  , &(*vd_TrkPFHcalMaxOverPLead  .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFHcal3x3OverPLead"  , &(*vd_TrkPFHcal3x3OverPLead  .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFEcalStripOverPLead", &(*vd_TrkPFEcalStripOverPLead.get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFBremRecOverPLead"  , &(*vd_TrkPFBremRecOverPLead  .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFElePreIDOut"       , &(*vd_TrkPFElePreIDOut       .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFMuonCaloComp"      , &(*vd_TrkPFMuonCaloComp      .get() ) );
    mLeptonData->Branch(prefix_+"TauPFPFMuonSegComp"       , &(*vd_TrkPFMuonSegComp       .get() ) );
  }
  //Tau vertex information
  mLeptonData->Branch(prefix_+"TauSigTrk", &(*vi_TauSigTrk.get() ) );
  mLeptonData->Branch(prefix_+"TauVx",     &(*vd_TauVx.get() ) );
  mLeptonData->Branch(prefix_+"TauVy",     &(*vd_TauVy.get() ) );
  mLeptonData->Branch(prefix_+"TauVz",     &(*vd_TauVz.get() ) );
  mLeptonData->Branch(prefix_+"TauPVDxy",  &(*vd_TauPVDxy.get() ) );
  mLeptonData->Branch(prefix_+"TauBSDxy",  &(*vd_TauBSDxy.get() ) );
  mLeptonData->Branch(prefix_+"TauDxy",    &(*vd_TauDxy.get() ) );
  mLeptonData->Branch(prefix_+"TauDxyErr", &(*vd_TauDxyErr.get() ) );
  mLeptonData->Branch(prefix_+"TauD0",     &(*vd_TauD0.get() ) );
  mLeptonData->Branch(prefix_+"TauD0Err",  &(*vd_TauD0Err.get() ) );
  mLeptonData->Branch(prefix_+"TauDz",     &(*vd_TauDz.get() ) );
  mLeptonData->Branch(prefix_+"TauDzErr",  &(*vd_TauDzErr.get() ) );
  
  //Generator level information stored in the tau object
  mLeptonData->Branch(prefix_+"TauGenP4",           &(*v_gentauP4.get() ) );
  mLeptonData->Branch(prefix_+"TauGenJetP4",        &(*v_gentaujetP4.get() ) );
  mLeptonData->Branch(prefix_+"TauGenPdgId",        &(*vi_TauGenPdgId.get() ) );
  mLeptonData->Branch(prefix_+"TauGenStatus",       &(*vi_TauGenStatus.get() ) );
  mLeptonData->Branch(prefix_+"TauGenMother",       &(*vi_TauGenMother.get() ) );
  mLeptonData->Branch(prefix_+"TauGenMotherStatus", &(*vi_TauGenMotherStatus.get() ) );
  mLeptonData->Branch(prefix_+"TauGen",             &(*vi_TauGen.get() ) );
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

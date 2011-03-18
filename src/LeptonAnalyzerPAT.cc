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
// $Id: LeptonAnalyzerPAT.cc,v 1.17 2011/03/15 14:55:52 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/LeptonAnalyzerPAT.h"
//#include "DataFormats/MuonReco/interface/MuonSelectors.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

//#ifdef __CINT__ 
//
//#pragma link C++ class std::vector<<reco::Candidate::LorentzVector> >+; 
//
//#endif
//________________________________________________________________________________________
LeptonAnalyzerPAT::LeptonAnalyzerPAT(const edm::ParameterSet& leptonParams, TTree* tmpAllData)
{ 

  mLeptonData = tmpAllData;

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
  bookTTree();

}


//________________________________________________________________________________________
LeptonAnalyzerPAT::~LeptonAnalyzerPAT() {}

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

  edm::Handle<EcalRecHitCollection> recHits;
  ev.getByLabel( "ecalRecHit","EcalRecHitsEB", recHits);

  const EcalRecHitCollection *myRecHits = recHits.product();
  
  edm::LogVerbatim("LeptonEvent") << " start reading in electrons " << std::endl;
  // Add the electrons
  i_ElecN = elecHandle->size();
  if (debug_) std::cout<<i_ElecN<<" Electron results for InputTag " << elecTag_<<std::endl;
  
  if ( i_ElecN > 50 ) i_ElecN = 50;
  maintenanceElecs();

  bool_spike = false;
    
  int el = 0;
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<i_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() > elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;

      // ECAL spike cleaning
      // Cut only on EB, ecal-seeded electrons
      double mySwissCross = -999;
      double myE2OverE9   = -999;

      vd_ElecdB    .push_back(theElectron.dB());
      vd_ElecdBerr .push_back(theElectron.edB());

      if(theElectron.ecalDrivenSeed()>0 && fabs(theElectron.superCluster()->eta())<1.4442) {
	
	const reco::CaloClusterPtr    seed =    theElectron.superCluster()->seed(); // seed cluster
	const   DetId seedId = seed->seed();
	EcalSeverityLevelAlgo severity;
	mySwissCross =  severity.swissCross(seedId, *myRecHits) ;
	myE2OverE9   =  severity.swissCross(seedId, *myRecHits) ;
	if (mySwissCross > 0.95) { 
	  continue; //ingnore this electron if it has swiss cross > 0.95
	  bool_spike = true;
	}
      }
      vd_ElecE2OverE9.push_back(myE2OverE9);
      vd_ElecSwissCross.push_back(mySwissCross);
      //vd_ElecTSeed.push_back(severity.swissCross(seedID, *recHits));
      vd_ElecSigmaIetaIeta.push_back(theElectron.sigmaIetaIeta());
      vd_ElecHadOverEM.push_back(theElectron.hadronicOverEm());

      v_elecP4.push_back(theElectron.p4());
      vd_ElecCharge.push_back(theElectron.charge());

      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
      
      vd_ElecTrkIso .push_back(theElectron.trackIso());
      vd_ElecECalIso.push_back(theElectron.ecalIso());
      vd_ElecHCalIso.push_back(theElectron.hcalIso());
      vd_ElecAllIso .push_back(theElectron.caloIso());

      //Special PF based isolation variables
      vd_ElecPFAllParticleIso  .push_back(theElectron.particleIso());
      vd_ElecPFChargedHadronIso.push_back(theElectron.chargedHadronIso());
      vd_ElecPFNeutralHadronIso.push_back(theElectron.neutralHadronIso());
      vd_ElecPFGammaIso        .push_back(theElectron.photonIso());
      
      if (theElectron.trackIsoDeposit())
	vd_ElecTrkIsoDeposit .push_back(theElectron.trackIsoDeposit()->candEnergy());
      else
	vd_ElecTrkIsoDeposit .push_back(-999);

      if (theElectron.ecalIsoDeposit())
	vd_ElecECalIsoDeposit .push_back(theElectron.ecalIsoDeposit()->candEnergy());
      else
	vd_ElecECalIsoDeposit .push_back(-999);

      if (theElectron.hcalIsoDeposit())
	vd_ElecHCalIsoDeposit .push_back(theElectron.hcalIsoDeposit()->candEnergy());
      else
	vd_ElecHCalIsoDeposit .push_back(-999);

      if (theElectron.userIsoDeposit(pat::PfAllParticleIso))
	vd_ElecPFAllParticleIsoDeposit .push_back(theElectron.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_ElecPFAllParticleIsoDeposit .push_back(-999);

      if (theElectron.userIsoDeposit(pat::PfChargedHadronIso))
	vd_ElecPFChargedHadronIsoDeposit .push_back(theElectron.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_ElecPFChargedHadronIsoDeposit .push_back(-999);

      if (theElectron.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_ElecPFNeutralHadronIsoDeposit .push_back(theElectron.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_ElecPFNeutralHadronIsoDeposit .push_back(-999);

      if (theElectron.userIsoDeposit(pat::PfGammaIso))
	vd_ElecPFGammaIsoDeposit .push_back(theElectron.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_ElecPFGammaIsoDeposit .push_back(-999);

      
      vf_ElecIdLoose   .push_back(theElectron.electronID("eidLoose"));
      vf_ElecIdTight   .push_back(theElectron.electronID("eidTight"));
      vf_ElecIdRobLoose.push_back(theElectron.electronID("eidRobustLoose"));
      vf_ElecIdRobTight.push_back(theElectron.electronID("eidRobustTight")); 
      vf_ElecIdRobHighE.push_back(theElectron.electronID("eidRobustHighEnergy")); 
      
      vd_ElecCaloEnergy.push_back(theElectron.caloEnergy());
      vd_ElecHOverE    .push_back(theElectron.hadronicOverEm());

      vd_ElecVx   .push_back(theElectron.vx());
      vd_ElecVy   .push_back(theElectron.vy());
      vd_ElecVz   .push_back(theElectron.vz());

      if (theElectron.gsfTrack().isNonnull()) {
	vd_ElecPVDxy .push_back(theElectron.gsfTrack()->dxy(pvPoint));
	vd_ElecBSDxy .push_back(theElectron.gsfTrack()->dxy(bsPoint));
	vd_ElecDxy   .push_back(theElectron.gsfTrack()->dxy());
	vd_ElecDxyErr.push_back(theElectron.gsfTrack()->dxyError());
	vd_ElecD0    .push_back(theElectron.gsfTrack()->d0());
	vd_ElecD0Err .push_back(theElectron.gsfTrack()->d0Error());
	vd_ElecDz    .push_back(theElectron.gsfTrack()->dz());
	vd_ElecDzErr .push_back(theElectron.gsfTrack()->dzError());
	
	vd_ElecChargeMode      .push_back(theElectron.gsfTrack()->chargeMode());	
	vd_ElecPtTrkMode       .push_back(theElectron.gsfTrack()->ptMode());
	vd_ElecQOverPErrTrkMode.push_back(theElectron.gsfTrack()->qoverpModeError());
	vd_ElecCharge          .push_back(theElectron.gsfTrack()->charge());
	vd_ElecPtTrk           .push_back(theElectron.gsfTrack()->pt());
	vd_ElecQOverPErrTrk    .push_back(theElectron.gsfTrack()->qoverpError());
	vd_ElecNormChi2        .push_back(theElectron.gsfTrack()->normalizedChi2());
	vd_ElecLostHits        .push_back(theElectron.gsfTrack()->lost());
	vd_ElecValidHits       .push_back(theElectron.gsfTrack()->found());

	vd_ElecEtaTrk.push_back(theElectron.trackMomentumAtVtx().Eta());
	vd_ElecPhiTrk.push_back(theElectron.trackMomentumAtVtx().Phi());
	vd_ElecPinTrk.push_back(sqrt(theElectron.trackMomentumAtVtx().Mag2()));
	vd_ElecPoutTrk.push_back(sqrt(theElectron.trackMomentumOut().Mag2()));
      }

      else {
	vd_ElecPVDxy .push_back(-9999);
	vd_ElecBSDxy .push_back(-9999);
	vd_ElecDxy   .push_back(-9999);
	vd_ElecDxyErr.push_back(-9999);
	vd_ElecD0    .push_back(-9999);
	vd_ElecD0Err .push_back(-9999);
	vd_ElecDz    .push_back(-9999);
	vd_ElecDzErr .push_back(-9999);
	
	vd_ElecChargeMode      .push_back(-9999);
	vd_ElecPtTrkMode       .push_back(-9999);
	vd_ElecQOverPErrTrkMode.push_back(-9999);
	vd_ElecCharge          .push_back(-9999);
	vd_ElecPtTrk           .push_back(-9999);
	vd_ElecQOverPErrTrk    .push_back(-9999);
	vd_ElecNormChi2        .push_back(-9999);
	vd_ElecLostHits        .push_back(-9999);
	vd_ElecValidHits       .push_back(-9999);

	vd_ElecEtaTrk .push_back(-9999);
	vd_ElecPhiTrk .push_back(-9999);
	vd_ElecPinTrk .push_back(-9999);
	vd_ElecPoutTrk.push_back(-9999);
      }
      
      
      if (theElectron.superCluster().isNonnull()) {
	vd_ElecWidthClusterEta.push_back(theElectron.superCluster()->etaWidth());
	vd_ElecWidthClusterPhi.push_back(theElectron.superCluster()->phiWidth());
      }
      
      else {
	vd_ElecWidthClusterEta.push_back(-9999);
	vd_ElecWidthClusterPhi.push_back(-9999);
      }

      //get associated gen particle information
      const reco::Candidate* candElec = theElectron.genLepton();
      if ( candElec ) {
	vi_ElecGenPdgId.push_back(candElec->pdgId());
	vi_ElecGenStatus.push_back(candElec->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candElec->px(),candElec->py(),candElec->pz(),candElec->energy());
	v_genelecP4.push_back(genp4);
      	
	const reco::Candidate* elecMother = candElec->mother();
	if( elecMother ) {
	  //is this necessary
	  while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
	  if ( elecMother ) {
	    vi_ElecGenMother.push_back(theElectron.genLepton()->mother()->pdgId());
	    vi_ElecGenMotherStatus.push_back(theElectron.genLepton()->mother()->status());
	  }
	}
      }
      else {
	vi_ElecGenPdgId       .push_back(-999);
	vi_ElecGenStatus      .push_back(-999);
	vi_ElecGenMother      .push_back(-999);
	vi_ElecGenMotherStatus.push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_genelecP4.push_back(genp4);
      }
      double elecIsoReq = (vd_ElecTrkIso.at(el)+vd_ElecECalIso.at(el)+vd_ElecHCalIso.at(el))/theElectron.pt();
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

  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

  for (int i=0;i<i_MuonN;i++){
    const pat::Muon& theMuon = (*muonHandle)[i];
    if ( (theMuon.pt() > muonMinEt_) && !(theMuon.eta() > muonMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good muons " << std::endl;      
      v_muonP4.push_back(theMuon.p4());

      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

      vd_MuondB    .push_back(theMuon.dB());
      vd_MuondBerr .push_back(theMuon.edB());

      vd_MuonCharge.push_back(theMuon.charge());

      //Muon isolation variables
      vd_MuonTrkIso.push_back(theMuon.trackIso());
      vd_MuonECalIso.push_back(theMuon.ecalIso());
      vd_MuonHCalIso.push_back(theMuon.hcalIso());
      vd_MuonAllIso.push_back(theMuon.caloIso());

      //Special PF based isolation variables
      vd_MuonPFAllParticleIso  .push_back(theMuon.particleIso());
      vd_MuonPFChargedHadronIso.push_back(theMuon.chargedHadronIso());
      vd_MuonPFNeutralHadronIso.push_back(theMuon.neutralHadronIso());
      vd_MuonPFGammaIso        .push_back(theMuon.photonIso());
      
      if (theMuon.trackIsoDeposit())
	vd_MuonTrkIsoDeposit .push_back(theMuon.trackIsoDeposit()->candEnergy());
      else
	vd_MuonTrkIsoDeposit .push_back(-999);

      if (theMuon.ecalIsoDeposit())
	vd_MuonECalIsoDeposit .push_back(theMuon.ecalIsoDeposit()->candEnergy());
      else
	vd_MuonECalIsoDeposit .push_back(-999);

      if (theMuon.hcalIsoDeposit())
	vd_MuonHCalIsoDeposit .push_back(theMuon.hcalIsoDeposit()->candEnergy());
      else
	vd_MuonHCalIsoDeposit .push_back(-999);

      if (theMuon.userIsoDeposit(pat::PfAllParticleIso))
	vd_MuonPFAllParticleIsoDeposit .push_back(theMuon.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_MuonPFAllParticleIsoDeposit .push_back(-999);

      if (theMuon.userIsoDeposit(pat::PfChargedHadronIso))
	vd_MuonPFChargedHadronIsoDeposit .push_back(theMuon.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_MuonPFChargedHadronIsoDeposit .push_back(-999);

      if (theMuon.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_MuonPFNeutralHadronIsoDeposit .push_back(theMuon.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_MuonPFNeutralHadronIsoDeposit .push_back(-999);

      if (theMuon.userIsoDeposit(pat::PfGammaIso))
	vd_MuonPFGammaIsoDeposit .push_back(theMuon.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_MuonPFGammaIsoDeposit .push_back(-999);

      vd_MuonECalIsoDepositR03.push_back(theMuon.isolationR03().emVetoEt);
      vd_MuonHCalIsoDepositR03.push_back(theMuon.isolationR03().hadVetoEt);

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


      vb_MuonIsGlobal                              .push_back(muonIDisGlobal  );
      vb_MuonIsStandAlone                          .push_back(muonIDisSA      );
      vb_MuonIsTracker                             .push_back(muonIDisTrk     );
      vb_MuonGlobalMuonPromptTight                 .push_back(muonIDGMPT      );
      vb_MuonAllArbitrated                         .push_back(muonIDAA        );
      vb_MuonTrackerMuonArbitrated                 .push_back(muonIDTMA       );
      vb_MuonTMLastStationLoose                    .push_back(muonIDTMSL      );
      vb_MuonTMLastStationTight                    .push_back(muonIDTMST      );
      vb_MuonTM2DCompatibilityLoose                .push_back(muonIDTM2CL     );
      vb_MuonTM2DCompatibilityTight                .push_back(muonIDTM2CT     );
      vb_MuonTMOneStationLoose                     .push_back(muonIDTMOSL     );
      vb_MuonTMOneStationTight                     .push_back(muonIDTMOST     );
      vb_MuonTMLastStationOptimizedLowPtLoose      .push_back(muonIDTMLSOL    );
      vb_MuonTMLastStationOptimizedLowPtTight      .push_back(muonIDTMLSOT    );
      vb_MuonGMTkChiCompatibility                  .push_back(muonIDGMTrkChiC );
      vb_MuonGMStaChiCompatibility                 .push_back(muonIDGMStaChiC );
      vb_MuonGMTkKinkTight                         .push_back(muonIDGMTkKT    );
      vb_MuonTMLastStationAngLoose                 .push_back(muonIDTMLSAngL  );
      vb_MuonTMLastStationAngTight                 .push_back(muonIDTMLSAngT  );
      vb_MuonTMLastStationOptimizedBarrelLowPtLoose.push_back(muonIDTMLSLSOBL );
      vb_MuonTMLastStationOptimizedBarrelLowPtTight.push_back(muonIDTMLSLSOBT );
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	vd_MuonCombChi2.push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombNdof.push_back(theMuon.combinedMuon()->ndof());

	vd_MuonCombVx    .push_back(theMuon.combinedMuon()->vx());
	vd_MuonCombVy    .push_back(theMuon.combinedMuon()->vy());
	vd_MuonCombVz    .push_back(theMuon.combinedMuon()->vz());
	vd_MuonCombPVDxy .push_back(theMuon.combinedMuon()->dxy(pvPoint));
	vd_MuonCombBSDxy .push_back(theMuon.combinedMuon()->dxy(bsPoint));
      	vd_MuonCombDxy   .push_back(theMuon.combinedMuon()->dxy());
      	vd_MuonCombDxyErr.push_back(theMuon.combinedMuon()->dxyError());
	vd_MuonCombD0    .push_back(theMuon.combinedMuon()->d0());
	vd_MuonCombD0Err .push_back(theMuon.combinedMuon()->d0Error());
	vd_MuonCombDz    .push_back(theMuon.combinedMuon()->dz());
	vd_MuonCombDzErr .push_back(theMuon.combinedMuon()->dzError());

	vd_MuonCombPt.push_back(theMuon.combinedMuon()->pt());
	vd_MuonCombPz.push_back(theMuon.combinedMuon()->pz());
	vd_MuonCombP.push_back(theMuon .combinedMuon()->p());
	vd_MuonCombEta.push_back(theMuon.combinedMuon()->eta());
	vd_MuonCombPhi.push_back(theMuon.combinedMuon()->phi());
	vd_MuonCombChi.push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombCharge.push_back(theMuon   .combinedMuon()->charge());
	vd_MuonCombQOverPErr.push_back(theMuon.combinedMuon()->qoverpError());
      }
      else {
	vd_MuonCombChi2  .push_back(-9999.);
	vd_MuonCombNdof  .push_back(-9999.);
	vd_MuonCombVx    .push_back(-9999.);
	vd_MuonCombVy    .push_back(-9999.);
	vd_MuonCombVz    .push_back(-9999.);
	vd_MuonCombPVDxy .push_back(-9999.);
	vd_MuonCombBSDxy .push_back(-9999.);
      	vd_MuonCombDxy   .push_back(-9999);
      	vd_MuonCombDxyErr.push_back(-9999);
	vd_MuonCombD0    .push_back(-9999.);
	vd_MuonCombD0Err .push_back(-9999.);
	vd_MuonCombDz    .push_back(-9999.);
	vd_MuonCombDzErr .push_back(-9999.);
	vd_MuonCombPt.push_back(-9999.);
	vd_MuonCombPz.push_back(-9999.);
	vd_MuonCombP.push_back(-9999.);
	vd_MuonCombEta.push_back(-9999.);
	vd_MuonCombPhi.push_back(-9999.);
	vd_MuonCombChi.push_back(-9999.);
	vd_MuonCombCharge.push_back(-9999.);
	vd_MuonCombQOverPErr.push_back(-9999.);
      }

      //Standalone muon information
      if(theMuon.isStandAloneMuon() && theMuon.standAloneMuon().isNonnull()){
	vd_MuonStandValidHits.push_back(theMuon.standAloneMuon()->found());
	vd_MuonStandLostHits.push_back(theMuon .standAloneMuon()->lost());
	vd_MuonStandPt.push_back(theMuon.standAloneMuon()->pt());
	vd_MuonStandPz.push_back(theMuon.standAloneMuon()->pz());
	vd_MuonStandP.push_back(theMuon .standAloneMuon()->p());
	vd_MuonStandEta.push_back(theMuon.standAloneMuon()->eta());
	vd_MuonStandPhi.push_back(theMuon.standAloneMuon()->phi());
	vd_MuonStandChi.push_back(theMuon.standAloneMuon()->chi2());
	vd_MuonStandCharge.push_back(theMuon   .standAloneMuon()->charge());
	vd_MuonStandQOverPErr.push_back(theMuon.standAloneMuon()->qoverpError());
      } 
      else{
	vd_MuonStandValidHits.push_back(-9999.);
	vd_MuonStandLostHits.push_back(-9999.);
	vd_MuonStandPt.push_back(-9999.);
	vd_MuonStandPz.push_back(-9999.);
	vd_MuonStandP.push_back(-9999.);
	vd_MuonStandEta.push_back(-9999.);
	vd_MuonStandPhi.push_back(-9999.);
	vd_MuonStandChi.push_back(-9999.);
	vd_MuonStandCharge.push_back(-9999.);
	vd_MuonStandQOverPErr.push_back(-9999.);
      }

      //Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.track().isNonnull()){
	vd_MuonTrkChiNorm  .push_back(theMuon.track()->normalizedChi2());
	vd_MuonTrkValidHits.push_back(theMuon.track()->found());
	vd_MuonTrkLostHits .push_back(theMuon.track()->lost());
	vd_MuonTrkPVDxy    .push_back(theMuon.track()->dxy(pvPoint));
	vd_MuonTrkBSDxy    .push_back(theMuon.track()->dxy(bsPoint));
      	vd_MuonTrkDxy      .push_back(theMuon.track()->dxy());
      	vd_MuonTrkDxyErr   .push_back(theMuon.track()->dxyError());
	vd_MuonTrkD0       .push_back(theMuon.track()->d0());
	vd_MuonTrkD0Err    .push_back(theMuon.track()->d0Error());
	vd_MuonTrkDz       .push_back(theMuon.track()->dz());
	vd_MuonTrkDzErr    .push_back(theMuon.track()->dzError());
	vd_MuonTrkPt       .push_back(theMuon.track()->pt());
	vd_MuonTrkPz       .push_back(theMuon.track()->pz());
	vd_MuonTrkP        .push_back(theMuon.track()->p());
	vd_MuonTrkEta      .push_back(theMuon.track()->eta());
	vd_MuonTrkPhi      .push_back(theMuon.track()->phi());
	vd_MuonTrkChi      .push_back(theMuon.track()->chi2());
	vd_MuonTrkCharge   .push_back(theMuon.track()->charge());
	vd_MuonTrkQOverPErr.push_back(theMuon.track()->qoverpError());
	vd_MuonTrkOuterZ   .push_back(theMuon.track()->outerZ());
	vd_MuonTrkOuterR   .push_back(theMuon.track()->outerRadius());
      }
      else{
	vd_MuonTrkChiNorm.push_back(-9999.);
	vd_MuonTrkValidHits.push_back(-9999);
	vd_MuonTrkLostHits.push_back(-9999);
	vd_MuonTrkPVDxy  .push_back(-9999);
	vd_MuonTrkBSDxy  .push_back(-9999);
      	vd_MuonTrkDxy    .push_back(-9999);
      	vd_MuonTrkDxyErr .push_back(-9999);
	vd_MuonTrkD0    .push_back(-9999);
	vd_MuonTrkD0Err .push_back(-9999);
	vd_MuonTrkDz    .push_back(-9999);
	vd_MuonTrkDzErr .push_back(-9999);
	vd_MuonTrkPt    .push_back(-9999);
	vd_MuonTrkPz    .push_back(-9999);
	vd_MuonTrkP     .push_back(-9999);
	vd_MuonTrkEta   .push_back(-9999);
	vd_MuonTrkPhi   .push_back(-9999);
	vd_MuonTrkChi   .push_back(-9999);
	vd_MuonTrkCharge.push_back(-9999);
	vd_MuonTrkQOverPErr.push_back(-9999);
	vd_MuonTrkOuterZ.push_back(-9999.);
	vd_MuonTrkOuterR.push_back(-9999.);
      }

      //Picky Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.pickyMuon().isNonnull()){
	vd_MuonPickyTrkChiNorm  .push_back(theMuon.pickyMuon()->normalizedChi2());
	vd_MuonPickyTrkValidHits.push_back(theMuon.pickyMuon()->found());
	vd_MuonPickyTrkLostHits .push_back(theMuon.pickyMuon()->lost());
	vd_MuonPickyTrkPVDxy    .push_back(theMuon.pickyMuon()->dxy(pvPoint));
	vd_MuonPickyTrkBSDxy    .push_back(theMuon.pickyMuon()->dxy(bsPoint));
      	vd_MuonPickyTrkDxy      .push_back(theMuon.pickyMuon()->dxy());
      	vd_MuonPickyTrkDxyErr   .push_back(theMuon.pickyMuon()->dxyError());
	vd_MuonPickyTrkD0       .push_back(theMuon.pickyMuon()->d0());
	vd_MuonPickyTrkD0Err    .push_back(theMuon.pickyMuon()->d0Error());
	vd_MuonPickyTrkDz       .push_back(theMuon.pickyMuon()->dz());
	vd_MuonPickyTrkDzErr    .push_back(theMuon.pickyMuon()->dzError());
	vd_MuonPickyTrkPt       .push_back(theMuon.pickyMuon()->pt());
	vd_MuonPickyTrkPz       .push_back(theMuon.pickyMuon()->pz());
	vd_MuonPickyTrkP        .push_back(theMuon.pickyMuon()->p());
	vd_MuonPickyTrkEta      .push_back(theMuon.pickyMuon()->eta());
	vd_MuonPickyTrkPhi      .push_back(theMuon.pickyMuon()->phi());
	vd_MuonPickyTrkChi      .push_back(theMuon.pickyMuon()->chi2());
	vd_MuonPickyTrkCharge   .push_back(theMuon.pickyMuon()->charge());
	vd_MuonPickyTrkQOverPErr.push_back(theMuon.pickyMuon()->qoverpError());
	vd_MuonPickyTrkOuterZ   .push_back(theMuon.pickyMuon()->outerZ());
	vd_MuonPickyTrkOuterR   .push_back(theMuon.pickyMuon()->outerRadius());
      }
      else{
 	vd_MuonPickyTrkChiNorm.push_back(-9999.);
	vd_MuonPickyTrkValidHits.push_back(-9999);
	vd_MuonPickyTrkLostHits.push_back(-9999);
	vd_MuonPickyTrkPVDxy  .push_back(-9999);
	vd_MuonPickyTrkBSDxy  .push_back(-9999);
      	vd_MuonPickyTrkDxy    .push_back(-9999);
      	vd_MuonPickyTrkDxyErr .push_back(-9999);
	vd_MuonPickyTrkD0    .push_back(-9999);
	vd_MuonPickyTrkD0Err .push_back(-9999);
	vd_MuonPickyTrkDz    .push_back(-9999);
	vd_MuonPickyTrkDzErr .push_back(-9999);
	vd_MuonPickyTrkPt    .push_back(-9999);
	vd_MuonPickyTrkPz    .push_back(-9999);
	vd_MuonPickyTrkP     .push_back(-9999);
	vd_MuonPickyTrkEta   .push_back(-9999);
	vd_MuonPickyTrkPhi   .push_back(-9999);
	vd_MuonPickyTrkChi   .push_back(-9999);
	vd_MuonPickyTrkCharge.push_back(-9999);
	vd_MuonPickyTrkQOverPErr.push_back(-9999);
	vd_MuonPickyTrkOuterZ.push_back(-9999.);
	vd_MuonPickyTrkOuterR.push_back(-9999.);
      }

      //TPFMS Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.tpfmsMuon().isNonnull()){
	vd_MuonTPFMSTrkChiNorm  .push_back(theMuon.tpfmsMuon()->normalizedChi2());
	vd_MuonTPFMSTrkValidHits.push_back(theMuon.tpfmsMuon()->found());
	vd_MuonTPFMSTrkLostHits .push_back(theMuon.tpfmsMuon()->lost());
	vd_MuonTPFMSTrkPVDxy    .push_back(theMuon.tpfmsMuon()->dxy(pvPoint));
	vd_MuonTPFMSTrkBSDxy    .push_back(theMuon.tpfmsMuon()->dxy(bsPoint));
      	vd_MuonTPFMSTrkDxy      .push_back(theMuon.tpfmsMuon()->dxy());
      	vd_MuonTPFMSTrkDxyErr   .push_back(theMuon.tpfmsMuon()->dxyError());
	vd_MuonTPFMSTrkD0       .push_back(theMuon.tpfmsMuon()->d0());
	vd_MuonTPFMSTrkD0Err    .push_back(theMuon.tpfmsMuon()->d0Error());
	vd_MuonTPFMSTrkDz       .push_back(theMuon.tpfmsMuon()->dz());
	vd_MuonTPFMSTrkDzErr    .push_back(theMuon.tpfmsMuon()->dzError());
	vd_MuonTPFMSTrkPt       .push_back(theMuon.tpfmsMuon()->pt());
	vd_MuonTPFMSTrkPz       .push_back(theMuon.tpfmsMuon()->pz());
	vd_MuonTPFMSTrkP        .push_back(theMuon.tpfmsMuon()->p());
	vd_MuonTPFMSTrkEta      .push_back(theMuon.tpfmsMuon()->eta());
	vd_MuonTPFMSTrkPhi      .push_back(theMuon.tpfmsMuon()->phi());
	vd_MuonTPFMSTrkChi      .push_back(theMuon.tpfmsMuon()->chi2());
	vd_MuonTPFMSTrkCharge   .push_back(theMuon.tpfmsMuon()->charge());
	vd_MuonTPFMSTrkQOverPErr.push_back(theMuon.tpfmsMuon()->qoverpError());
	vd_MuonTPFMSTrkOuterZ   .push_back(theMuon.tpfmsMuon()->outerZ());
	vd_MuonTPFMSTrkOuterR   .push_back(theMuon.tpfmsMuon()->outerRadius());
      }
      else{
	vd_MuonTPFMSTrkChiNorm.push_back(-9999.);
	vd_MuonTPFMSTrkValidHits.push_back(-9999);
	vd_MuonTPFMSTrkLostHits.push_back(-9999);
	vd_MuonTPFMSTrkPVDxy  .push_back(-9999);
	vd_MuonTPFMSTrkBSDxy  .push_back(-9999);
      	vd_MuonTPFMSTrkDxy    .push_back(-9999);
      	vd_MuonTPFMSTrkDxyErr .push_back(-9999);
	vd_MuonTPFMSTrkD0    .push_back(-9999);
	vd_MuonTPFMSTrkD0Err .push_back(-9999);
	vd_MuonTPFMSTrkDz    .push_back(-9999);
	vd_MuonTPFMSTrkDzErr .push_back(-9999);
	vd_MuonTPFMSTrkPt    .push_back(-9999);
	vd_MuonTPFMSTrkPz    .push_back(-9999);
	vd_MuonTPFMSTrkP     .push_back(-9999);
	vd_MuonTPFMSTrkEta   .push_back(-9999);
	vd_MuonTPFMSTrkPhi   .push_back(-9999);
	vd_MuonTPFMSTrkChi   .push_back(-9999);
	vd_MuonTPFMSTrkCharge.push_back(-9999);
	vd_MuonTPFMSTrkQOverPErr.push_back(-9999);
	vd_MuonTPFMSTrkOuterZ.push_back(-9999.);
	vd_MuonTPFMSTrkOuterR.push_back(-9999.);
      }

      //Muon gen particle association variables
      const reco::Candidate* candMuon = theMuon.genLepton();
      if ( candMuon ) {
	vi_MuonGenPdgId.push_back(candMuon->pdgId());
	vi_MuonGenStatus.push_back(candMuon->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candMuon->px(),candMuon->py(),candMuon->pz(),candMuon->energy());
	v_genmuonP4.push_back(genp4);
	
	const reco::Candidate* muonMother = candMuon->mother();
	if( muonMother ) {
	  //is this necessary
	  while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
	  if ( muonMother ) {
	    vi_MuonGenMother.push_back(theMuon.genLepton()->mother()->pdgId());
	    vi_MuonGenMotherStatus.push_back(theMuon.genLepton()->mother()->status());
	  }
	}
      }
      
      else{
	vi_MuonGenPdgId       .push_back(-999);
	vi_MuonGenStatus      .push_back(-999);
	vi_MuonGenMother      .push_back(-999);
	vi_MuonGenMotherStatus.push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	v_genmuonP4.push_back(genp4);
      }
      double muonIsoReq = (vd_MuonTrkIso.at(mu)+vd_MuonECalIso.at(mu)+vd_MuonHCalIso.at(mu))/theMuon.pt();
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
  
  tauidMap["electron"       ] = Electron;
  tauidMap["muon"           ] = Muon;
  tauidMap["oneProng0Pi0"   ] = OneProng0Pi0;
  tauidMap["oneProng1Pi0"   ] = OneProng1Pi0;
  tauidMap["oneProng2Pi0"   ] = OneProng2Pi0;
  tauidMap["oneProngOther"  ] = OneProngOther;
  tauidMap["threeProng0Pi0" ] = ThreeProng0Pi0;
  tauidMap["threeProng1Pi0" ] = ThreeProng1Pi0;
  tauidMap["threeProng2Pi0" ] = ThreeProng2Pi0;
  tauidMap["threeProngOther"] = ThreeProngOther;
  tauidMap["rare"           ] = Rare;

  int tau = 0;
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<i_TauN;i++){
    const::pat::Tau& theTau = (*tauHandle)[i];
    if ( (theTau.pt() > tauMinEt_) && !(theTau.eta() > tauMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good taus " << std::endl;
      v_tauP4.push_back(theTau.p4());
      vd_TauCharge.push_back(theTau.charge());
      
      vd_TauTrkIso .push_back(theTau.trackIso());
      vd_TauECalIso.push_back(theTau.ecalIso());
      vd_TauHCalIso.push_back(theTau.hcalIso());
      vd_TauAllIso .push_back(theTau.caloIso());
      
      //Special PF based isolation variables
      vd_TauPFAllParticleIso  .push_back(theTau.particleIso());
      vd_TauPFChargedHadronIso.push_back(theTau.chargedHadronIso());
      vd_TauPFNeutralHadronIso.push_back(theTau.neutralHadronIso());
      vd_TauPFGammaIso        .push_back(theTau.photonIso());

      if (theTau.trackIsoDeposit())
	vd_TauTrkIsoDeposit .push_back(theTau.trackIsoDeposit()->candEnergy());
      else
	vd_TauTrkIsoDeposit .push_back(-999);

      if (theTau.ecalIsoDeposit())
	vd_TauECalIsoDeposit .push_back(theTau.ecalIsoDeposit()->candEnergy());
      else
	vd_TauECalIsoDeposit .push_back(-999);

      if (theTau.hcalIsoDeposit())
	vd_TauHCalIsoDeposit .push_back(theTau.hcalIsoDeposit()->candEnergy());
      else
	vd_TauHCalIsoDeposit .push_back(-999);

      if (theTau.userIsoDeposit(pat::PfAllParticleIso))
	vd_TauPFAllParticleIsoDeposit .push_back(theTau.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_TauPFAllParticleIsoDeposit .push_back(-999);

      if (theTau.userIsoDeposit(pat::PfChargedHadronIso))
	vd_TauPFChargedHadronIsoDeposit .push_back(theTau.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_TauPFChargedHadronIsoDeposit .push_back(-999);

      if (theTau.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_TauPFNeutralHadronIsoDeposit .push_back(theTau.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_TauPFNeutralHadronIsoDeposit .push_back(-999);

      if (theTau.userIsoDeposit(pat::PfGammaIso))
	vd_TauPFGammaIsoDeposit .push_back(theTau.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_TauPFGammaIsoDeposit .push_back(-999);
      
      vi_TauSigTrk .push_back(theTau.signalTracks().size());  
      vd_TauVx     .push_back(theTau.vx());
      vd_TauVy     .push_back(theTau.vy());
      vd_TauVz     .push_back(theTau.vz());

      if (theTau.leadTrack().isNonnull()) {
      	vd_TauPVDxy  .push_back(theTau.leadTrack()->dxy(pvPoint));
      	vd_TauBSDxy  .push_back(theTau.leadTrack()->dxy(bsPoint));
      	vd_TauDxy    .push_back(theTau.leadTrack()->dxy());
      	vd_TauDxyErr .push_back(theTau.leadTrack()->dxyError());
      	vd_TauD0     .push_back(theTau.leadTrack()->d0());
      	vd_TauD0Err  .push_back(theTau.leadTrack()->d0Error());
      	vd_TauDz     .push_back(theTau.leadTrack()->dz());
      	vd_TauDzErr  .push_back(theTau.leadTrack()->dzError());
      }
      else {
	edm::LogWarning("LeptonEvent") << "Tau leadTrack is Null";
      	vd_TauPVDxy.push_back(-9999);
      	vd_TauBSDxy.push_back(-9999);
      	vd_TauDxy   .push_back(-9999);
      	vd_TauDxyErr.push_back(-9999);
      	vd_TauD0   .push_back(-9999);
      	vd_TauD0Err.push_back(-9999);
      	vd_TauDz   .push_back(-9999);
      	vd_TauDzErr.push_back(-9999);
      }
      vf_TauIdElec       .push_back(theTau.tauID("againstElectron"));
      vf_TauIdMuon       .push_back(theTau.tauID("againstMuon"));
      vf_TauIdIso        .push_back(theTau.tauID("byIsolation"));
      vf_TauIdNCfrHalf   .push_back(theTau.tauID("byTaNCfrHalfPercent"));
      vf_TauIdNCfrQuarter.push_back(theTau.tauID("byTaNCfrQuarterPercent"));
      vf_TauIdNCfrTenth  .push_back(theTau.tauID("byTaNCfrTenthPercent"));
      vf_TauIdNCfrFull   .push_back(theTau.tauID("byTaNCfrOnePercent"));

      //Calo specific information
      if (theTau.isCaloTau()) {
	vf_TauCaloLeadTrkSignedIP      .push_back(theTau.leadTracksignedSipt());
	vf_TauCaloLeadTrkHcal3x3EtSum  .push_back(theTau.leadTrackHCAL3x3hitsEtSum());
	vf_TauCaloLeadTrkHcal3x3HotDEta.push_back(theTau.leadTrackHCAL3x3hottesthitDEta());
	vf_TauCaloSignalTrkMInv        .push_back(theTau.signalTracksInvariantMass());
	vf_TauCaloTrkMInv              .push_back(theTau.TracksInvariantMass());
	vf_TauCaloIsoTrkPtSum          .push_back(theTau.isolationTracksPtSum());
	vf_TauCaloIsoEcalEtSum         .push_back(theTau.isolationECALhitsEtSum());
	vf_TauCaloMaxEtHCAL            .push_back(theTau.maximumHCALhitEt());
      }

      if (theTau.isPFTau()) {
	vf_TrkPFIsoChargedHadPtSum.push_back(theTau.isolationPFChargedHadrCandsPtSum());
	vf_TrkPFIsoGammaEtSum     .push_back(theTau.isolationPFGammaCandsEtSum());
	vf_TrkPFHcalClusterMaxEt  .push_back(theTau.maximumHCALPFClusterEt());
	vf_TrkPFEFrac_em          .push_back(theTau.emFraction());
	vf_TrkPFHcalTotalOverPLead.push_back(theTau.hcalTotOverPLead());
	vf_TrkPFHcalMaxOverPLead  .push_back(theTau.hcalMaxOverPLead());
	vf_TrkPFHcal3x3OverPLead  .push_back(theTau.hcal3x3OverPLead());
	vf_TrkPFEcalStripOverPLead.push_back(theTau.ecalStripSumEOverPLead());
	vf_TrkPFBremRecOverPLead  .push_back(theTau.bremsRecoveryEOverPLead());
	vf_TrkPFElePreIDOut       .push_back(theTau.electronPreIDOutput());
	vf_TrkPFMuonCaloComp      .push_back(theTau.caloComp());
	vf_TrkPFMuonSegComp       .push_back(theTau.segComp());
      }

      vf_TauEtaEtaMom.push_back(theTau.etaetaMoment());
      vf_TauPhiPhiMom.push_back(theTau.phiphiMoment());
      vf_TauEtaPhiMom.push_back(theTau.etaphiMoment());

      //get associated gen particle information
      const reco::Candidate* candTau    = theTau.genLepton();
      if ( candTau ) {
	vi_TauGenPdgId .push_back(candTau->pdgId());
	vi_TauGenStatus.push_back(candTau->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candTau->px(),candTau->py(),candTau->pz(),candTau->energy());
	v_gentauP4.push_back(genp4);
	const reco::Candidate* tauMother = candTau->mother();
	if( tauMother ) {
	  //is this necessary
	  while (tauMother->pdgId() == candTau->pdgId()) tauMother = tauMother->mother();
	  if ( tauMother ) {
	    vi_TauGenMother.push_back(theTau.genLepton()->mother()->pdgId());
	    vi_TauGenMotherStatus.push_back(theTau.genLepton()->mother()->status());
	  }
	}
      }
      else {
	vi_TauGenPdgId.push_back(-999.);
	vi_TauGenMother.push_back(-999.);
	vi_TauGen.push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_gentauP4.push_back(genp4);
      }

      const reco::Candidate* candTauJet = theTau.genJet();
      if (candTauJet) {
	reco::Candidate::LorentzVector genjetp4;
	genjetp4.SetPxPyPzE(candTauJet->px(),candTauJet->py(),candTauJet->pz(),candTauJet->energy());
	v_gentaujetP4.push_back(genjetp4);
	
	const reco::CompositePtrCandidate *TauGenID = theTau.genJet();
	std::string genTauDecayMode = JetMCTagUtils::genTauDecayMode(*TauGenID);
	
	switch(tauidMap[genTauDecayMode]) {
	case Electron:
	  vi_TauGen.push_back(1);
	  break;
	case Muon:
	  vi_TauGen.push_back(2);
	  break;
	case OneProng0Pi0:
	  vi_TauGen.push_back(3);
	  break;
	case OneProng1Pi0:
	  vi_TauGen.push_back(4);
	  break;
	case OneProng2Pi0:
	  vi_TauGen.push_back(5);
	  break;
	case OneProngOther:
	  vi_TauGen.push_back(6);
	  break;
	case ThreeProng0Pi0:
	  vi_TauGen.push_back(7);
	  break;
	case ThreeProng1Pi0:
	  vi_TauGen.push_back(8);
	  break;
	case ThreeProng2Pi0:
	  vi_TauGen.push_back(9);
	  break;
	case ThreeProngOther:
	  vi_TauGen.push_back(10);
	  break;
	case Rare:
	  vi_TauGen.push_back(11);
	  break;
	default:
	  vi_TauGen.push_back(12);
	}
      }
      else {
	reco::Candidate::LorentzVector genjetp4;
	genjetp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	v_gentaujetP4.push_back(genjetp4);
      }

      double tauIsoReq = (vd_TauTrkIso.at(tau)+vd_TauECalIso.at(tau)+vd_TauHCalIso.at(tau))/theTau.pt();
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
void LeptonAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Add the branches
  //add electrons
  mLeptonData->Branch(prefix_+"ElecVeto", &bool_ElecVeto, prefix_+"ElecVeto/O");
  //General electron information
  mLeptonData->Branch(prefix_+"ElectronP4", &v_elecP4);
  mLeptonData->Branch(prefix_+"ElecN",      &i_ElecN, prefix_+"ElecN/I");  
  
  mLeptonData->Branch(prefix_+"ElecdB",    &vd_ElecdB);
  mLeptonData->Branch(prefix_+"ElecdBerr", &vd_ElecdBerr);

  mLeptonData->Branch(prefix_+"ElecCharge", &vd_ElecCharge);
  mLeptonData->Branch(prefix_+"ElecHOverE", &vd_ElecHOverE);
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"ElecTrkIso",     &vd_ElecTrkIso);
  mLeptonData->Branch(prefix_+"ElecECalIso",    &vd_ElecECalIso);
  mLeptonData->Branch(prefix_+"ElecHCalIso",    &vd_ElecHCalIso);
  mLeptonData->Branch(prefix_+"ElecAllIso",     &vd_ElecAllIso);

  mLeptonData->Branch(prefix_+"ElecPFAllParticleIso",   &vd_ElecPFAllParticleIso);
  mLeptonData->Branch(prefix_+"ElecPFChargedHadronIso", &vd_ElecPFChargedHadronIso);
  mLeptonData->Branch(prefix_+"ElecPFNeutralHadronIso", &vd_ElecPFNeutralHadronIso);
  mLeptonData->Branch(prefix_+"ElecPFGammaIso",         &vd_ElecPFGammaIso);

  mLeptonData->Branch(prefix_+"ElecTrkChiNorm", &vd_ElecNormChi2);
  
  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    &vf_ElecIdLoose);
  mLeptonData->Branch(prefix_+"ElecIdTight",    &vf_ElecIdTight);
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", &vf_ElecIdRobLoose);
  mLeptonData->Branch(prefix_+"ElecIdRobTight", &vf_ElecIdRobTight);
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", &vf_ElecIdRobHighE);
  mLeptonData->Branch(prefix_+"ElecChargeMode", &vd_ElecChargeMode);
  mLeptonData->Branch(prefix_+"ElecPtMode",     &vd_ElecPtTrkMode);
  
  mLeptonData->Branch(prefix_+"ElecE2OverE9",      &vd_ElecE2OverE9);
  mLeptonData->Branch(prefix_+"ElecSwissCross",    &vd_ElecSwissCross);
  mLeptonData->Branch(prefix_+"ElecHadOverEM",     &vd_ElecHadOverEM);
  mLeptonData->Branch(prefix_+"ElecSigmaIetaIeta", &vd_ElecSigmaIetaIeta);

  
  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     &vd_ElecVx);
  mLeptonData->Branch(prefix_+"ElecVy",     &vd_ElecVy);
  mLeptonData->Branch(prefix_+"ElecVz",     &vd_ElecVz);
  mLeptonData->Branch(prefix_+"ElecPVDxy",  &vd_ElecPVDxy);
  mLeptonData->Branch(prefix_+"ElecBSDxy",  &vd_ElecBSDxy);
  mLeptonData->Branch(prefix_+"ElecDxy",    &vd_ElecDxy);
  mLeptonData->Branch(prefix_+"ElecDxyErr", &vd_ElecDxyErr);
  mLeptonData->Branch(prefix_+"ElecD0",     &vd_ElecD0);
  mLeptonData->Branch(prefix_+"ElecD0Err",  &vd_ElecD0Err);
  mLeptonData->Branch(prefix_+"ElecDz",     &vd_ElecDz);
  mLeptonData->Branch(prefix_+"ElecDzErr",  &vd_ElecDzErr);
  mLeptonData->Branch(prefix_+"ElecPtTrk",  &vd_ElecPtTrk);
  
  //Additonal electron detector information
  //Electron tracking information
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrkMode", &vd_ElecQOverPErrTrkMode);
  mLeptonData->Branch(prefix_+"ElecCaloEnergy",       &vd_ElecCaloEnergy);
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrk",     &vd_ElecQOverPErrTrk);
  mLeptonData->Branch(prefix_+"ElecPinTrk",           &vd_ElecPinTrk);
  mLeptonData->Branch(prefix_+"ElecPoutTrk",          &vd_ElecPoutTrk);
  mLeptonData->Branch(prefix_+"ElecLostHits",         &vd_ElecLostHits);
  mLeptonData->Branch(prefix_+"ElecValidHits",        &vd_ElecValidHits);
  //mLeptonData->Branch(prefix_+"ElecNCluster",         &vd_ElecNCluster);
  mLeptonData->Branch(prefix_+"ElecEtaTrk",           &vd_ElecEtaTrk);
  mLeptonData->Branch(prefix_+"ElecPhiTrk",           &vd_ElecPhiTrk);
  mLeptonData->Branch(prefix_+"ElecWidthClusterEta",  &vd_ElecWidthClusterEta);
  mLeptonData->Branch(prefix_+"ElecWidthClusterPhi",  &vd_ElecWidthClusterPhi);
  
  //Generator level information stored in the electron object
  mLeptonData->Branch(prefix_+"ElecGenP4",           &v_genelecP4);
  mLeptonData->Branch(prefix_+"ElecGenPdgId",        &vi_ElecGenPdgId);
  mLeptonData->Branch(prefix_+"ElecGenStatus",       &vi_ElecGenStatus);
  mLeptonData->Branch(prefix_+"ElecGenMother",       &vi_ElecGenMother);
  mLeptonData->Branch(prefix_+"ElecGenMotherStatus", &vi_ElecGenMotherStatus);

  //add muons
  mLeptonData->Branch(prefix_+"MuonVeto", &bool_MuonVeto, prefix_+"MuonVeto/O");
  //General kinematic variables related to muons
  mLeptonData->Branch(prefix_+"MuonP4",        &v_muonP4);
  mLeptonData->Branch(prefix_+"MuonN",         &i_MuonN,  prefix_+"MuonN/I");  
  
  mLeptonData->Branch(prefix_+"MuondB",    &vd_MuondB);
  mLeptonData->Branch(prefix_+"MuondBerr", &vd_MuondBerr);

  mLeptonData->Branch(prefix_+"MuonCharge",    &vd_MuonCharge);
  
  //Muon isolation variables
  //mLeptonData->Branch("NIsomuon",      &m_NIsomuon,       "NIsomuon/I");  
  mLeptonData->Branch(prefix_+"MuonTrkIso",     &vd_MuonTrkIso);
  mLeptonData->Branch(prefix_+"MuonECalIso",    &vd_MuonECalIso);
  mLeptonData->Branch(prefix_+"MuonHCalIso",    &vd_MuonHCalIso);
  mLeptonData->Branch(prefix_+"MuonAllIso",     &vd_MuonAllIso);

  mLeptonData->Branch(prefix_+"MuonPFAllParticleIso",   &vd_MuonPFAllParticleIso);
  mLeptonData->Branch(prefix_+"MuonPFChargedHadronIso", &vd_MuonPFChargedHadronIso);
  mLeptonData->Branch(prefix_+"MuonPFNeutralHadronIso", &vd_MuonPFNeutralHadronIso);
  mLeptonData->Branch(prefix_+"MuonPFGammaIso",         &vd_MuonPFGammaIso);

  mLeptonData->Branch(prefix_+"MuonTrkChiNorm", &vd_MuonTrkChiNorm);
  
  mLeptonData->Branch(prefix_+"MuonECalIsoDeposit", &vd_MuonECalIsoDeposit);
  mLeptonData->Branch(prefix_+"MuonHCalIsoDeposit", &vd_MuonHCalIsoDeposit);

  //Muon calorimeter type
  mLeptonData->Branch(prefix_+"MuonIsGlobal",                              &vb_MuonIsGlobal);
  mLeptonData->Branch(prefix_+"MuonIsStandAlone",                          &vb_MuonIsStandAlone);
  mLeptonData->Branch(prefix_+"MuonIsTracker",                             &vb_MuonIsTracker);
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonGlobalMuonPromptTight",                 &vb_MuonGlobalMuonPromptTight);
  mLeptonData->Branch(prefix_+"MuonAllArbitrated",                         &vb_MuonAllArbitrated);
  mLeptonData->Branch(prefix_+"MuonTrackerMuonArbitrated",                 &vb_MuonTrackerMuonArbitrated);
  mLeptonData->Branch(prefix_+"MuonTMLastStationLoose",                    &vb_MuonTMLastStationLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationTight",                    &vb_MuonTMLastStationTight);
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityLoose",                &vb_MuonTM2DCompatibilityLoose);
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityTight",                &vb_MuonTM2DCompatibilityTight);
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     &vb_MuonTMOneStationLoose);
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     &vb_MuonTMOneStationTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtLoose",      &vb_MuonTMLastStationOptimizedLowPtLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtTight",      &vb_MuonTMLastStationOptimizedLowPtTight);
  mLeptonData->Branch(prefix_+"MuonGMTkChiCompatibility",                  &vb_MuonGMTkChiCompatibility);
  mLeptonData->Branch(prefix_+"MuonGMStaChiCompatibility",                 &vb_MuonGMStaChiCompatibility);
  mLeptonData->Branch(prefix_+"MuonGMTkKinkTight",                         &vb_MuonGMTkKinkTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngLoose",                 &vb_MuonTMLastStationAngLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngTight",                 &vb_MuonTMLastStationAngTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose",&vb_MuonTMLastStationOptimizedBarrelLowPtLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight",&vb_MuonTMLastStationOptimizedBarrelLowPtTight);
  
  //  mLeptonData->Branch(prefix_+"MuonId", &vd_MuonId);
  mLeptonData->Branch(prefix_+"MuonCombChi2",  &vd_MuonCombChi2);
  mLeptonData->Branch(prefix_+"MuonCombNdof",  &vd_MuonCombNdof);
  mLeptonData->Branch(prefix_+"MuonCombVx",    &vd_MuonCombVx);
  mLeptonData->Branch(prefix_+"MuonCombVy",    &vd_MuonCombVy);
  mLeptonData->Branch(prefix_+"MuonCombVz",    &vd_MuonCombVz);
  mLeptonData->Branch(prefix_+"MuonCombPVDxy", &vd_MuonCombPVDxy);
  mLeptonData->Branch(prefix_+"MuonCombBSDxy", &vd_MuonCombBSDxy);
  mLeptonData->Branch(prefix_+"MuonCombDxy",   &vd_MuonCombDxy);
  mLeptonData->Branch(prefix_+"MuonCombDxyErr",&vd_MuonCombDxyErr);
  mLeptonData->Branch(prefix_+"MuonCombD0",    &vd_MuonCombD0);
  mLeptonData->Branch(prefix_+"MuonCombD0Err", &vd_MuonCombD0Err);
  mLeptonData->Branch(prefix_+"MuonCombDz",    &vd_MuonCombDz);
  mLeptonData->Branch(prefix_+"MuonCombDzErr", &vd_MuonCombDzErr);
  mLeptonData->Branch(prefix_+"MuonCombPt",        &vd_MuonCombPt);
  mLeptonData->Branch(prefix_+"MuonCombPz",        &vd_MuonCombPz);
  mLeptonData->Branch(prefix_+"MuonCombP",         &vd_MuonCombP);
  mLeptonData->Branch(prefix_+"MuonCombEta",       &vd_MuonCombEta);
  mLeptonData->Branch(prefix_+"MuonCombPhi",       &vd_MuonCombPhi);
  mLeptonData->Branch(prefix_+"MuonCombCharge",    &vd_MuonCombCharge);
  mLeptonData->Branch(prefix_+"MuonCombChi",       &vd_MuonCombChi);
  mLeptonData->Branch(prefix_+"MuonCombQOverPErr", &vd_MuonCombQOverPErr);
  
  //Muon tracking information
  mLeptonData->Branch(prefix_+"MuonStandValidHits", &vd_MuonStandValidHits);
  mLeptonData->Branch(prefix_+"MuonStandLostHits",  &vd_MuonStandLostHits);
  mLeptonData->Branch(prefix_+"MuonStandPt",        &vd_MuonStandPt);
  mLeptonData->Branch(prefix_+"MuonStandPz",        &vd_MuonStandPz);
  mLeptonData->Branch(prefix_+"MuonStandP",         &vd_MuonStandP);
  mLeptonData->Branch(prefix_+"MuonStandEta",       &vd_MuonStandEta);
  mLeptonData->Branch(prefix_+"MuonStandPhi",       &vd_MuonStandPhi);
  mLeptonData->Branch(prefix_+"MuonStandCharge",    &vd_MuonStandCharge);
  mLeptonData->Branch(prefix_+"MuonStandChi",       &vd_MuonStandChi);
  mLeptonData->Branch(prefix_+"MuonStandQOverPErr", &vd_MuonStandQOverPErr);
  
  mLeptonData->Branch(prefix_+"MuonTrkValidHits", &vd_MuonTrkValidHits);
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",  &vd_MuonTrkLostHits);
  mLeptonData->Branch(prefix_+"MuonTrkPVDxy",     &vd_MuonTrkPVDxy);
  mLeptonData->Branch(prefix_+"MuonTrkBSDxy",     &vd_MuonTrkBSDxy);
  mLeptonData->Branch(prefix_+"MuonTrkDxy",       &vd_MuonTrkDxy);
  mLeptonData->Branch(prefix_+"MuonTrkDxyErr",    &vd_MuonTrkDxyErr);
  mLeptonData->Branch(prefix_+"MuonTrkD0",        &vd_MuonTrkD0);
  mLeptonData->Branch(prefix_+"MuonTrkD0Err",     &vd_MuonTrkD0Err);
  mLeptonData->Branch(prefix_+"MuonTrkDz",        &vd_MuonTrkDz);
  mLeptonData->Branch(prefix_+"MuonTrkDzErr",     &vd_MuonTrkDzErr);
  mLeptonData->Branch(prefix_+"MuonTrkPt",        &vd_MuonTrkPt);
  mLeptonData->Branch(prefix_+"MuonTrkPz",        &vd_MuonTrkPz);
  mLeptonData->Branch(prefix_+"MuonTrkP",         &vd_MuonTrkP);
  mLeptonData->Branch(prefix_+"MuonTrkEta",       &vd_MuonTrkEta);
  mLeptonData->Branch(prefix_+"MuonTrkPhi",       &vd_MuonTrkPhi);
  mLeptonData->Branch(prefix_+"MuonTrkCharge",    &vd_MuonTrkCharge);
  mLeptonData->Branch(prefix_+"MuonTrkChi",       &vd_MuonTrkChi);
  mLeptonData->Branch(prefix_+"MuonTrkQOverPErr", &vd_MuonTrkQOverPErr);
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",    &vd_MuonTrkOuterZ);
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",    &vd_MuonTrkOuterR);
  
  //Generator level muon information
  mLeptonData->Branch(prefix_+"MuonGenP4",           &v_genmuonP4);
  mLeptonData->Branch(prefix_+"MuonGenPdgId",        &vi_MuonGenPdgId);
  mLeptonData->Branch(prefix_+"MuonGenStatus",       &vi_MuonGenStatus);
  mLeptonData->Branch(prefix_+"MuonGenMother",       &vi_MuonGenMother);
  mLeptonData->Branch(prefix_+"MuonGenMotherStatus", &vi_MuonGenMotherStatus);
  
  //add taus
  mLeptonData->Branch(prefix_+"TauVeto", &bool_TauVeto, prefix_+"TauVeto/O");
  //General tau information
  mLeptonData->Branch(prefix_+"TauP4", &v_tauP4);
  mLeptonData->Branch(prefix_+"TauN",  &i_TauN,  prefix_+"TauN/I");  
  
  mLeptonData->Branch(prefix_+"TauCharge", &vd_TauCharge);
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"TauTrkIso",     &vd_TauTrkIso);
  mLeptonData->Branch(prefix_+"TauECalIso",    &vd_TauECalIso);
  mLeptonData->Branch(prefix_+"TauHCalIso",    &vd_TauHCalIso);
  mLeptonData->Branch(prefix_+"TauAllIso",     &vd_TauAllIso);

  mLeptonData->Branch(prefix_+"TauPFAllParticleIso",   &vd_TauPFAllParticleIso);
  mLeptonData->Branch(prefix_+"TauPFChargedHadronIso", &vd_TauPFChargedHadronIso);
  mLeptonData->Branch(prefix_+"TauPFNeutralHadronIso", &vd_TauPFNeutralHadronIso);
  mLeptonData->Branch(prefix_+"TauPFGammaIso",         &vd_TauPFGammaIso);

  //Tau identification values
  mLeptonData->Branch(prefix_+"TauIdElec",       &vf_TauIdElec);
  mLeptonData->Branch(prefix_+"TauIdMuon",       &vf_TauIdMuon);
  mLeptonData->Branch(prefix_+"TauIdIso",        &vf_TauIdIso);
  mLeptonData->Branch(prefix_+"TauIdNCfrFull",   &vf_TauIdNCfrFull);
  mLeptonData->Branch(prefix_+"TauIdNCfrHalf",   &vf_TauIdNCfrHalf);
  mLeptonData->Branch(prefix_+"TauIdNCfrQuarter",&vf_TauIdNCfrQuarter);
  mLeptonData->Branch(prefix_+"TauIdNCfrTenth",  &vf_TauIdNCfrTenth);

  mLeptonData->Branch(prefix_+"TauEtaEtaMoment", &vf_TauEtaEtaMom);
  mLeptonData->Branch(prefix_+"TauPhiPhiMoment", &vf_TauPhiPhiMom);
  mLeptonData->Branch(prefix_+"TauEtaPhiMoment", &vf_TauEtaPhiMom);

  //Tau Calo info
  if (prefix_ == "") {
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkSignedIP"      , &vf_TauCaloLeadTrkSignedIP      );
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkHcal3x3EtSum"  , &vf_TauCaloLeadTrkHcal3x3EtSum  );
    mLeptonData->Branch(prefix_+"TauCaloLeadTrkHcal3x3HotDEta", &vf_TauCaloLeadTrkHcal3x3HotDEta);
    mLeptonData->Branch(prefix_+"TauCaloSignalTrkMInv"        , &vf_TauCaloSignalTrkMInv        );
    mLeptonData->Branch(prefix_+"TauCaloTrkMInv"              , &vf_TauCaloTrkMInv              );
    mLeptonData->Branch(prefix_+"TauCaloIsoTrkPtSum"          , &vf_TauCaloIsoTrkPtSum          );
    mLeptonData->Branch(prefix_+"TauCaloIsoEcalEtSum"         , &vf_TauCaloIsoEcalEtSum         );
    mLeptonData->Branch(prefix_+"TauCaloMaxEtHCAL"            , &vf_TauCaloMaxEtHCAL            );
  }

  //Tau PF info
  if (prefix_ == "PF" || prefix_ == "PF2PAT") {
    mLeptonData->Branch(prefix_+"TauPFPFIsoChargedHadPtSum", &vf_TrkPFIsoChargedHadPtSum);
    mLeptonData->Branch(prefix_+"TauPFPFIsoGammaEtSum"     , &vf_TrkPFIsoGammaEtSum     );
    mLeptonData->Branch(prefix_+"TauPFPFHcalClusterMaxEt"  , &vf_TrkPFHcalClusterMaxEt  );
    mLeptonData->Branch(prefix_+"TauPFPFEFrac_em"          , &vf_TrkPFEFrac_em          );
    mLeptonData->Branch(prefix_+"TauPFPFHcalTotalOverPLead", &vf_TrkPFHcalTotalOverPLead);
    mLeptonData->Branch(prefix_+"TauPFPFHcalMaxOverPLead"  , &vf_TrkPFHcalMaxOverPLead  );
    mLeptonData->Branch(prefix_+"TauPFPFHcal3x3OverPLead"  , &vf_TrkPFHcal3x3OverPLead  );
    mLeptonData->Branch(prefix_+"TauPFPFEcalStripOverPLead", &vf_TrkPFEcalStripOverPLead);
    mLeptonData->Branch(prefix_+"TauPFPFBremRecOverPLead"  , &vf_TrkPFBremRecOverPLead  );
    mLeptonData->Branch(prefix_+"TauPFPFElePreIDOut"       , &vf_TrkPFElePreIDOut       );
    mLeptonData->Branch(prefix_+"TauPFPFMuonCaloComp"      , &vf_TrkPFMuonCaloComp      );
    mLeptonData->Branch(prefix_+"TauPFPFMuonSegComp"       , &vf_TrkPFMuonSegComp       );
  }
  //Tau vertex information
  mLeptonData->Branch(prefix_+"TauSigTrk", &vi_TauSigTrk);
  mLeptonData->Branch(prefix_+"TauVx",     &vd_TauVx);
  mLeptonData->Branch(prefix_+"TauVy",     &vd_TauVy);
  mLeptonData->Branch(prefix_+"TauVz",     &vd_TauVz);
  mLeptonData->Branch(prefix_+"TauPVDxy",  &vd_TauPVDxy);
  mLeptonData->Branch(prefix_+"TauBSDxy",  &vd_TauBSDxy);
  mLeptonData->Branch(prefix_+"TauDxy",    &vd_TauDxy);
  mLeptonData->Branch(prefix_+"TauDxyErr", &vd_TauDxyErr);
  mLeptonData->Branch(prefix_+"TauD0",     &vd_TauD0);
  mLeptonData->Branch(prefix_+"TauD0Err",  &vd_TauD0Err);
  mLeptonData->Branch(prefix_+"TauDz",     &vd_TauDz);
  mLeptonData->Branch(prefix_+"TauDzErr",  &vd_TauDzErr);
  
  //Generator level information stored in the tau object
  mLeptonData->Branch(prefix_+"TauGenP4",           &v_gentauP4);
  mLeptonData->Branch(prefix_+"TauGenJetP4",        &v_gentaujetP4);
  mLeptonData->Branch(prefix_+"TauGenPdgId",        &vi_TauGenPdgId);
  mLeptonData->Branch(prefix_+"TauGenStatus",       &vi_TauGenStatus);
  mLeptonData->Branch(prefix_+"TauGenMother",       &vi_TauGenMother);
  mLeptonData->Branch(prefix_+"TauGenMotherStatus", &vi_TauGenMotherStatus);
  mLeptonData->Branch(prefix_+"TauGen",             &vi_TauGen);
  
  edm::LogInfo("LeptonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

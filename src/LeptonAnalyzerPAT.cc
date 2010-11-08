
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
// $Id: LeptonAnalyzerPAT.cc,v 1.11 2010/11/02 13:55:17 sturdy Exp $
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

  //doMCData_   = leptonParams.getUntrackedParameter<bool>("doMCLeps",false);
  //if (doMCData_) 
  genTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("genLepTag");
  debug_   = leptonParams.getUntrackedParameter<int>("debugLeps",0);
  prefix_  = leptonParams.getUntrackedParameter<std::string>("prefixLeps","");
 
  // get the data tags
  elecTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("elecTag");
  muonTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("muonTag");
  tauTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("tauTag");

  localPi = acos(-1.0);

  // Initialise ntuple branches
  bookTTree();

}


//________________________________________________________________________________________
LeptonAnalyzerPAT::~LeptonAnalyzerPAT() {}


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

  // GEN INFO do only if running on MC data
  doMCData_ = ev.isRealData();

  if(!doMCData_) {
    //get pthat of process
    d_Pthat = -999.;
    
    Handle<double> genEventScale;
    ev.getByLabel( "genEventScale", genEventScale );
    if ( genEventScale.isValid() ) d_Pthat = *genEventScale;
    
    Handle<reco::GenParticleCollection>  genParticles;
    ev.getByLabel(genTag_, genParticles);   
    
    int count=0;
    int lcount=0;
    //int tcount=0;
    if (debug_>1) edm::LogVerbatim("LeptonEvent") << logmessage<< std::endl;

    maintenanceGen(genParticles->size());

    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      //get status 3 particles
      if (st==3) {
	v_genP4.push_back(pCand.p4());
	vi_genIds.push_back(pCand.pdgId());
	vi_genStatus.push_back(pCand.status());
	vi_genDaughters.push_back(pCand.numberOfDaughters());
      
	if (pCand.numberOfMothers() > 0 ) { 
	  const reco::Candidate * mom = pCand.mother();
	  while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	  
	  for( size_t j = 0; j < i; ++ j ) {
	    const Candidate * ref = &((*genParticles)[j]);
	    //if (ref == mom) { vi_genRefs.push_back(ref->pdgId()); } //return mother's pdgId
	    if (ref == mom) { vi_genRefs.push_back(j); } //point to particle that is reference
	  }  
	} else { vi_genRefs.push_back(-999);}

	if (debug_>1)  edm::LogVerbatim("LeptonEvent") << logmessage<<std::endl;
	++count;
      }
      else { // store also electrons or muons or taus of status 1 
	if ( (abs(pCand.pdgId()) == 11) || (abs(pCand.pdgId()) == 13) || (abs(pCand.pdgId()) == 15) ) {
	  
	  v_genLepP4.push_back(pCand.p4());
	  vi_genLepIds   .push_back(pCand.pdgId());
	  vi_genLepStatus.push_back(pCand.status());
	  vi_genLepDaughters.push_back(pCand.numberOfDaughters());
	  
	  if (pCand.numberOfMothers() > 0 ) { 
	    const reco::Candidate * mom = pCand.mother();
	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
	    
	    for( size_t j = 0; j < i; ++ j ) {
	      const reco::Candidate * ref = &((*genParticles)[j]);
	      //if (ref == mom) { vi_genLepRefs.push_back(ref->pdgId()); }
	      if (ref == mom) { vi_genLepRefs.push_back(j); }
	    }  
	  } else { vi_genLepRefs.push_back(-999);}

	  if (debug_>1)  edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
	  ++lcount;
	}
      }
    }
    i_length = count;
    i_genLepLength = lcount;
  }
  
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
  maintenanceElecs(i_ElecN);

  bool_spike = false;
    
  int el = 0;
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<i_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() > elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;

      // ECAL spike cleaning
      // Cut only on EB, ecal-seeded electrons
      if(theElectron.ecalDrivenSeed()>0 && fabs(theElectron.superCluster()->eta())<1.4442) {
	
	const reco::CaloClusterPtr    seed =    theElectron.superCluster()->seed(); // seed cluster
	const   DetId seedId = seed->seed();
	EcalSeverityLevelAlgo severity;
	double myswissCross =  severity.swissCross(seedId, *myRecHits) ;
	if (myswissCross > 0.95) { 
	  continue; //ingnore this electron if it has swiss cross > 0.95
	  bool_spike = true;
	}
      }

      v_elecP4.push_back(theElectron.p4());
      vd_ElecCharge.push_back(theElectron.charge());

      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
      
      vd_ElecTrkIso .push_back(theElectron.trackIso());
      vd_ElecECalIso.push_back(theElectron.ecalIso());
      vd_ElecHCalIso.push_back(theElectron.hcalIso());
      vd_ElecAllIso .push_back(theElectron.caloIso());
      
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
	vd_ElecD0   .push_back(theElectron.gsfTrack()->d0());
	vd_ElecD0Err.push_back(theElectron.gsfTrack()->d0Error());
	vd_ElecDz   .push_back(theElectron.gsfTrack()->dz());
	
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
	vd_ElecD0   .push_back(-9999);
	vd_ElecD0Err.push_back(-9999);
	vd_ElecDz   .push_back(-9999);
	
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
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candElec->px(),candElec->py(),candElec->pz(),candElec->energy());
	v_genelecP4.push_back(genp4);
      	
	const reco::Candidate* elecMother = candElec->mother();
	if( elecMother ) {
	  while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
	  if ( elecMother ) {
	    vi_ElecGenMother.push_back(theElectron.genLepton()->mother()->pdgId());
	  }
	}
      }
      else {
	vi_ElecGenPdgId.push_back(-999);
	vi_ElecGenMother.push_back(-999);
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
  maintenanceMuons(i_MuonN);
  int mu = 0;

  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

  for (int i=0;i<i_MuonN;i++){
    const pat::Muon& theMuon = (*muonHandle)[i];
    if ( (theMuon.pt() > muonMinEt_) && !(theMuon.eta() > muonMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good muons " << std::endl;      
      v_muonP4.push_back(theMuon.p4());

      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

      //Muon isolation variables
      vd_MuonCharge.push_back(theMuon.charge());
      vd_MuonTrkIso.push_back(theMuon.trackIso());
      vd_MuonECalIso.push_back(theMuon.ecalIso());
      vd_MuonHCalIso.push_back(theMuon.hcalIso());
      vd_MuonAllIso.push_back(theMuon.caloIso());

      vd_MuonECalIsoDeposit.push_back(theMuon.isolationR03().emVetoEt);
      vd_MuonHCalIsoDeposit.push_back(theMuon.isolationR03().hadVetoEt);

      //Muon classification variables
      vb_MuonIsGlobal.push_back(theMuon.isGlobalMuon());
      vb_MuonIsStandAlone.push_back(theMuon.isStandAloneMuon());
      vb_MuonIsTracker.push_back(theMuon.isTrackerMuon());
      
      vb_MuonGlobalMuonPromptTight.push_back(theMuon.muonID("GlobalMuonPromptTight"));
      						     
      vb_MuonAllArbitrated.push_back(theMuon.muonID("AllArbitrated"));
      vb_MuonTrackerMuonArbitrated.push_back(theMuon.muonID("TrackerMuonArbitrated"));

      vb_MuonTMLastStationLoose.push_back(theMuon.muonID("TMLastStationLoose"));
      vb_MuonTMLastStationTight.push_back(theMuon.muonID("TMLastStationTight"));

      vb_MuonTM2DCompatibilityLoose.push_back(theMuon.muonID("TM2DCompatibilityLoose"));
      vb_MuonTM2DCompatibilityTight.push_back(theMuon.muonID("TM2DCompatibilityTight"));

      vb_MuonTMOneStationLoose.push_back(theMuon.muonID("TMOneStationLoose"));
      vb_MuonTMOneStationTight.push_back(theMuon.muonID("TMOneStationTight"));

      vb_MuonTMLastStationOptimizedLowPtLoose.push_back(theMuon.muonID("TMLastStationOptimizedLowPtLoose"));
      vb_MuonTMLastStationOptimizedLowPtTight.push_back(theMuon.muonID("TMLastStationOptimizedLowPtTight"));

      vb_MuonGMTkChiCompatibility.push_back(theMuon.muonID("GMTkChiCompatibility"));
      vb_MuonGMStaChiCompatibility.push_back(theMuon.muonID("GMStaChiCompatibility"));
      vb_MuonGMTkKinkTight.push_back(theMuon.muonID("GMTkKinkTight"));

      vb_MuonTMLastStationAngLoose.push_back(theMuon.muonID("TMLastStationAngLoose"));
      vb_MuonTMLastStationAngTight.push_back(theMuon.muonID("TMLastStationAngTight"));

      vb_MuonTMLastStationOptimizedBarrelLowPtLoose.push_back(theMuon.muonID("TMLastStationOptimizedBarrelLowPtLoose"));
      vb_MuonTMLastStationOptimizedBarrelLowPtTight.push_back(theMuon.muonID("TMLastStationOptimizedBarrelLowPtTight"));
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	vd_MuonCombChi2.push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombNdof.push_back(theMuon.combinedMuon()->ndof());

	vd_MuonCombVx   .push_back(theMuon.combinedMuon()->vx());
	vd_MuonCombVy   .push_back(theMuon.combinedMuon()->vy());
	vd_MuonCombVz   .push_back(theMuon.combinedMuon()->vz());
	vd_MuonCombD0   .push_back(theMuon.combinedMuon()->d0());
	vd_MuonCombD0Err.push_back(theMuon.combinedMuon()->d0Error());
	vd_MuonCombDz   .push_back(theMuon.combinedMuon()->dz());

      }
      else {
	vd_MuonCombChi2 .push_back(-9999.);
	vd_MuonCombNdof .push_back(-9999.);
	vd_MuonCombVx   .push_back(-9999.);
	vd_MuonCombVy   .push_back(-9999.);
	vd_MuonCombVz   .push_back(-9999.);
	vd_MuonCombD0   .push_back(-9999.);
	vd_MuonCombD0Err.push_back(-9999.);
	vd_MuonCombDz   .push_back(-9999.);
      }

      //Standalone muon information
      if(theMuon.isStandAloneMuon() && theMuon.standAloneMuon().isNonnull()){
	vd_MuonStandValidHits.push_back(theMuon.standAloneMuon()->found());
	vd_MuonStandLostHits.push_back(theMuon.standAloneMuon()->lost());
	vd_MuonStandPt.push_back(theMuon.standAloneMuon()->pt());
	vd_MuonStandPz.push_back(theMuon.standAloneMuon()->pz());
	vd_MuonStandP.push_back(theMuon.standAloneMuon()->p());
	vd_MuonStandEta.push_back(theMuon.standAloneMuon()->eta());
	vd_MuonStandPhi.push_back(theMuon.standAloneMuon()->phi());
	vd_MuonStandChi.push_back(theMuon.standAloneMuon()->chi2());
	vd_MuonStandCharge.push_back(theMuon.standAloneMuon()->charge());
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
	vd_MuonTrkChiNorm.push_back(theMuon.track()->normalizedChi2());
	vd_MuonTrkValidHits.push_back(theMuon.track()->found());
	vd_MuonTrkLostHits.push_back(theMuon.track()->lost());
	vd_MuonTrkD0   .push_back(theMuon.track()->d0());
	vd_MuonTrkD0Err.push_back(theMuon.track()->d0Error());
	vd_MuonTrkPt   .push_back(theMuon.track()->pt());
	vd_MuonTrkPz   .push_back(theMuon.track()->pz());
	vd_MuonTrkP    .push_back(theMuon.track()->p());
	vd_MuonTrkEta  .push_back(theMuon.track()->eta());
	vd_MuonTrkPhi  .push_back(theMuon.track()->phi());
	vd_MuonTrkChi  .push_back(theMuon.track()->chi2());
	vd_MuonTrkCharge.push_back(theMuon.track()->charge());
	vd_MuonTrkQOverPErr.push_back(theMuon.track()->qoverpError());
	//  vd_MuonTrkOuterZ.push_back(theMuon.track()->outerZ());
	//  vd_MuonTrkOuterR.push_back(theMuon.track()->outerRadius());

      }
      else{
	vd_MuonTrkChiNorm.push_back(-9999.);
	vd_MuonTrkValidHits.push_back(-9999);
	vd_MuonTrkLostHits.push_back(-9999);
	vd_MuonTrkD0   .push_back(-9999);
	vd_MuonTrkD0Err.push_back(-9999);
	vd_MuonTrkPt   .push_back(-9999);
	vd_MuonTrkPz   .push_back(-9999);
	vd_MuonTrkP    .push_back(-9999);
	vd_MuonTrkEta  .push_back(-9999);
	vd_MuonTrkPhi  .push_back(-9999);
	vd_MuonTrkChi  .push_back(-9999);
	vd_MuonTrkCharge.push_back(-9999);
	vd_MuonTrkQOverPErr.push_back(-9999);
	//  vd_MuonTrkOuterZ.push_back(-9999.);
	//  vd_MuonTrkOuterR.push_back(-9999.);
      }

      //Muon gen particle association variables
      const reco::Candidate* candMuon = theMuon.genLepton();
      if ( candMuon ) {
	vi_MuonGenPdgId.push_back(candMuon->pdgId());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candMuon->px(),candMuon->py(),candMuon->pz(),candMuon->energy());
	v_genmuonP4.push_back(genp4);
	
	const reco::Candidate* muonMother = candMuon->mother();
	if( muonMother ) {
	  while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
	  if ( muonMother ) {
	    vi_MuonGenMother.push_back(theMuon.genLepton()->mother()->pdgId());
	  }
	}
      }
      
      else{
	vi_MuonGenPdgId.push_back(-999);
	vi_MuonGenMother.push_back(-999);
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
  maintenanceTaus(i_TauN);
  
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

      vd_TauVx     .push_back(theTau.vx());
      vd_TauVy     .push_back(theTau.vy());
      vd_TauVz     .push_back(theTau.vz());

      if (theTau.leadTrack().isNonnull()) {
      	vd_TauD0     .push_back(theTau.leadTrack()->d0());
      	vd_TauD0Err  .push_back(theTau.leadTrack()->d0Error());
      	vd_TauDz     .push_back(theTau.leadTrack()->dz());
      }
      else {
	edm::LogWarning("LeptonEvent") << "Tau leadTrack is Null";
      	vd_TauD0     .push_back(-9999);
      	vd_TauD0Err  .push_back(-9999);
      	vd_TauDz     .push_back(-9999);
      }
      vf_TauIdElec       .push_back(theTau.tauID("againstElectron"));
      vf_TauIdMuon       .push_back(theTau.tauID("againstMuon"));
      vf_TauIdIso        .push_back(theTau.tauID("byIsolation"));
      vf_TauIdNCfrFull   .push_back(theTau.tauID("byTaNCfrOnePercent"));
      vf_TauIdNCfrHalf   .push_back(theTau.tauID("byTaNCfrHalfPercent"));
      vf_TauIdNCfrQuarter.push_back(theTau.tauID("byTaNCfrQuarterPercent"));

      //get associated gen particle information
      const reco::Candidate* candTau    = theTau.genLepton();
      if ( candTau ) {
	vi_TauGenPdgId.push_back(candTau->pdgId());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candTau->px(),candTau->py(),candTau->pz(),candTau->energy());
	v_gentauP4.push_back(genp4);
	const reco::Candidate* tauMother = candTau->mother();
	if( tauMother ) {
	  while (tauMother->pdgId() == candTau->pdgId()) tauMother = tauMother->mother();
	  if ( tauMother ) {
	    vi_TauGenMother.push_back(theTau.genLepton()->mother()->pdgId());
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
  mLeptonData->Branch(prefix_+"ElecN",      &i_ElecN,      prefix_+"ElecN/I");  
  
  mLeptonData->Branch(prefix_+"ElecCharge", &vd_ElecCharge);
  mLeptonData->Branch(prefix_+"ElecHOverE", &vd_ElecHOverE);
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"ElecTrkIso",     &vd_ElecTrkIso);
  mLeptonData->Branch(prefix_+"ElecECalIso",    &vd_ElecECalIso);
  mLeptonData->Branch(prefix_+"ElecHCalIso",    &vd_ElecHCalIso);
  mLeptonData->Branch(prefix_+"ElecAllIso",     &vd_ElecAllIso);
  mLeptonData->Branch(prefix_+"ElecTrkChiNorm", &vd_ElecNormChi2);
  
  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    &vf_ElecIdLoose);
  mLeptonData->Branch(prefix_+"ElecIdTight",    &vf_ElecIdTight);
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", &vf_ElecIdRobLoose);
  mLeptonData->Branch(prefix_+"ElecIdRobTight", &vf_ElecIdRobTight);
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", &vf_ElecIdRobHighE);
  mLeptonData->Branch(prefix_+"ElecChargeMode", &vd_ElecChargeMode);
  mLeptonData->Branch(prefix_+"ElecPtMode",     &vd_ElecPtTrkMode);
  
  
  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     &vd_ElecVx);
  mLeptonData->Branch(prefix_+"ElecVy",     &vd_ElecVy);
  mLeptonData->Branch(prefix_+"ElecVz",     &vd_ElecVz);
  mLeptonData->Branch(prefix_+"ElecD0",     &vd_ElecD0);
  mLeptonData->Branch(prefix_+"ElecD0Err",  &vd_ElecD0Err);
  mLeptonData->Branch(prefix_+"ElecDz",     &vd_ElecDz);
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
  mLeptonData->Branch(prefix_+"ElecGenP4",     &v_genelecP4);
  mLeptonData->Branch(prefix_+"ElecGenPdgId",  &vi_ElecGenPdgId);
  mLeptonData->Branch(prefix_+"ElecGenMother", &vi_ElecGenMother);
  
  //add muons
  mLeptonData->Branch(prefix_+"MuonVeto", &bool_MuonVeto, prefix_+"MuonVeto/O");
  //General kinematic variables related to muons
  mLeptonData->Branch(prefix_+"MuonP4",        &v_muonP4);
  mLeptonData->Branch(prefix_+"MuonN",         &i_MuonN,          prefix_+"MuonN/I");  
  
  mLeptonData->Branch(prefix_+"MuonCharge",    &vd_MuonCharge);
  
  //Muon isolation variables
  //mLeptonData->Branch("NIsomuon",      &m_NIsomuon,       "NIsomuon/I");  
  mLeptonData->Branch(prefix_+"MuonTrkIso",     &vd_MuonTrkIso);
  mLeptonData->Branch(prefix_+"MuonECalIso",    &vd_MuonECalIso);
  mLeptonData->Branch(prefix_+"MuonHCalIso",    &vd_MuonHCalIso);
  mLeptonData->Branch(prefix_+"MuonAllIso",     &vd_MuonAllIso);
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
  mLeptonData->Branch(prefix_+"MuonCombChi2", &vd_MuonCombChi2);
  mLeptonData->Branch(prefix_+"MuonCombNdof", &vd_MuonCombNdof);
  mLeptonData->Branch(prefix_+"MuonCombVx",   &vd_MuonCombVx);
  mLeptonData->Branch(prefix_+"MuonCombVy",   &vd_MuonCombVy);
  mLeptonData->Branch(prefix_+"MuonCombVz",   &vd_MuonCombVz);
  mLeptonData->Branch(prefix_+"MuonCombD0",   &vd_MuonCombD0);
  mLeptonData->Branch(prefix_+"MuonCombD0Err",&vd_MuonCombD0Err);
  mLeptonData->Branch(prefix_+"MuonCombDz",   &vd_MuonCombDz);
  
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
  mLeptonData->Branch(prefix_+"MuonTrkD0",        &vd_MuonTrkD0);
  mLeptonData->Branch(prefix_+"MuonTrkD0Err",     &vd_MuonTrkD0Err);
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
  mLeptonData->Branch(prefix_+"MuonGenP4",     &v_genmuonP4);
  mLeptonData->Branch(prefix_+"MuonGenPdgId",  &vi_MuonGenPdgId);
  mLeptonData->Branch(prefix_+"MuonGenMother", &vi_MuonGenMother);
  
  //add taus
  mLeptonData->Branch(prefix_+"TauVeto", &bool_TauVeto, prefix_+"TauVeto/O");
  //General tau information
  mLeptonData->Branch(prefix_+"TauP4", &v_tauP4);
  mLeptonData->Branch(prefix_+"TauN",      &i_TauN,      prefix_+"TauN/I");  
  
  mLeptonData->Branch(prefix_+"TauCharge", &vd_TauCharge);
  
  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"TauTrkIso",     &vd_TauTrkIso);
  mLeptonData->Branch(prefix_+"TauECalIso",    &vd_TauECalIso);
  mLeptonData->Branch(prefix_+"TauHCalIso",    &vd_TauHCalIso);
  mLeptonData->Branch(prefix_+"TauAllIso",     &vd_TauAllIso);
  
  //Tau identification values
  mLeptonData->Branch(prefix_+"TauIdElec",       &vf_TauIdElec);
  mLeptonData->Branch(prefix_+"TauIdMuon",       &vf_TauIdMuon);
  mLeptonData->Branch(prefix_+"TauIdIso",        &vf_TauIdIso);
  mLeptonData->Branch(prefix_+"TauIdNCfrFull",   &vf_TauIdNCfrFull);
  mLeptonData->Branch(prefix_+"TauIdNCfrHalf",   &vf_TauIdNCfrHalf);
  mLeptonData->Branch(prefix_+"TauIdNCfrQuarter",&vf_TauIdNCfrQuarter);

  
  //Tau vertex information
  mLeptonData->Branch(prefix_+"TauVx",     &vd_TauVx);
  mLeptonData->Branch(prefix_+"TauVy",     &vd_TauVy);
  mLeptonData->Branch(prefix_+"TauVz",     &vd_TauVz);
  mLeptonData->Branch(prefix_+"TauD0",     &vd_TauD0);
  mLeptonData->Branch(prefix_+"TauD0Err",  &vd_TauD0Err);
  mLeptonData->Branch(prefix_+"TauDz",     &vd_TauDz);
  
  //Generator level information stored in the tau object
  mLeptonData->Branch(prefix_+"TauGenP4",    &v_gentauP4);
  mLeptonData->Branch(prefix_+"TauGenJetP4", &v_gentaujetP4);
  mLeptonData->Branch(prefix_+"TauGenPdgId", &vi_TauGenPdgId);
  mLeptonData->Branch(prefix_+"TauGenMother",&vi_TauGenMother);
  mLeptonData->Branch(prefix_+"TauGen",      &vi_TauGen);
  
  
  
  //generator level information
  if (!doMCData_) {
    //generator leptons (electrons and muons and taus
    mLeptonData->Branch(prefix_+"genP4",       &v_genP4);
    mLeptonData->Branch(prefix_+"genN",        &i_length,        prefix_+"genN/I");
    mLeptonData->Branch(prefix_+"genId",       &vi_genIds);
    mLeptonData->Branch(prefix_+"genStatus",   &vi_genStatus);
    mLeptonData->Branch(prefix_+"genMother",   &vi_genRefs);
    mLeptonData->Branch(prefix_+"genDaughters",&vi_genDaughters);
    
    //generator leptons status (electrons and muons and taus
    mLeptonData->Branch(prefix_+"genLepP4",       &v_genLepP4);
    mLeptonData->Branch(prefix_+"genLepN",        &i_genLepLength, prefix_+"genLepN/I");
    mLeptonData->Branch(prefix_+"genLepId",       &vi_genLepIds);
    mLeptonData->Branch(prefix_+"genLepStatus",   &vi_genLepStatus);
    mLeptonData->Branch(prefix_+"genLepMother",   &vi_genLepRefs);
    mLeptonData->Branch(prefix_+"genLepDaughters",&vi_genLepDaughters);
    
    mLeptonData->Branch(prefix_+"pthat", &d_Pthat, prefix_+"pthat/D");
  }    
  
  edm::LogInfo("LeptonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

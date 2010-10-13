
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
// $Id: LeptonAnalyzerPAT.cc,v 1.8 2010/07/08 03:22:30 sturdy Exp $
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

#pragma link C++ class std::vector<<reco::Candidate::LorentzVector> >+; 

#endif
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

  //tauMaxEta_ = leptonParams.getUntrackedParameter<double>("tauMaxEta",12.0);
  //tauMaxEt_  = leptonParams.getUntrackedParameter<double>("tauMaxEt",9999.);
  //tauMinEt_  = leptonParams.getUntrackedParameter<double>("tauMinEt",5.);
  //tauRelIso_ = leptonParams.getUntrackedParameter<double>("tauRelIso",0.5);

  doMCData_   = leptonParams.getUntrackedParameter<bool>("doMCLeps",false);
  if (doMCData_) 
    genTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("genLepTag");
  debug_   = leptonParams.getUntrackedParameter<int>("debugLeps",0);
  prefix_  = leptonParams.getUntrackedParameter<std::string>("prefixLeps","");
 
  // get the data tags
  elecTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("elecTag");
  muonTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("muonTag");
  //tauTag_   = leptonParams.getUntrackedParameter<edm::InputTag>("tauTag");

  localPi = acos(-1.0);

  // Initialise ntuple branches
  bookTTree();
}


//________________________________________________________________________________________
LeptonAnalyzerPAT::~LeptonAnalyzerPAT() {}


//________________________________________________________________________________________
bool LeptonAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;

  bool_ElecVeto      = false;
  bool_MuonVeto      = false;
  bool lepton_result = true;

  edm::LogVerbatim("LeptonEvent") << " Start  " << std::endl;

  std::ostringstream dbg;

  // GEN INFO do only if running on MC data
  if(doMCData_) {
    //get pthat of process
    d_Pthat = -999.;
    
    Handle<double> genEventScale;
    iEvent.getByLabel( "genEventScale", genEventScale );
    if ( genEventScale.isValid() ) d_Pthat = *genEventScale;
    
    Handle<reco::GenParticleCollection>  genParticles;
    iEvent.getByLabel(genTag_, genParticles);   
    
    int count=0;
    int lcount=0;
    //int tcount=0;
    if (debug_>1) edm::LogVerbatim("LeptonEvent") << logmessage<< std::endl;

    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      //get status 3 particles
      if (st==3) {
	v_genP4.push_back(pCand.p4());
	vi_genIds.push_back(pCand.pdgId());
	vi_genStatus.push_back(pCand.status());
      
	if (pCand.numberOfMothers() > 0 ) { 
	  const reco::Candidate * mom = pCand.mother();
	  while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	  
	  for( size_t j = 0; j < i; ++ j ) {
	    const Candidate * ref = &((*genParticles)[j]);
	    if (ref == mom) { vi_genRefs.push_back(ref->pdgId()); } //return mother's pdgId
	    //if (ref == mom) { vi_genRefs.push_back(j); } //point to particle that is reference
	  }  
	} else { vi_genRefs.push_back(-999);}

	if (debug_>1)  edm::LogVerbatim("LeptonEvent") << logmessage<<std::endl;
	++count;
      }
      else { // store also electrons or muons of status 1 
	if ( (abs(pCand.pdgId()) == 11) || (abs(pCand.pdgId()) == 13) ) {
	  
	  v_genLepP4.push_back(pCand.p4());
	  vi_genLepIds   .push_back(pCand.pdgId());
	  vi_genLepStatus.push_back(pCand.status());
	  
	  if (pCand.numberOfMothers() > 0 ) { 
	    const reco::Candidate * mom = pCand.mother();
	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
	    
	    for( size_t j = 0; j < i; ++ j ) {
	      const reco::Candidate * ref = &((*genParticles)[j]);
	      if (ref == mom) { vi_genLepRefs.push_back(ref->pdgId()); }
	      //if (ref == mom) { vi_genLepRefs.push_back(j); }
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
  iEvent.getByLabel(elecTag_, elecHandle);
  if ( !elecHandle.isValid() ) {
    edm::LogWarning("LeptonEvent") << "No Electron results for InputTag " << elecTag_;
    if (debug_) std::cout<<" Electron results for InputTag " << elecTag_<<std::endl;
    return false;
  }

  
  edm::LogVerbatim("LeptonEvent") << " start reading in electrons " << std::endl;
  // Add the electrons
  i_ElecN = elecHandle->size();
  if (debug_) std::cout<<i_ElecN<<" Electron results for InputTag " << elecTag_<<std::endl;
  
  if ( i_ElecN > 50 ) i_ElecN = 50;
  v_elecP4.resize(i_ElecN);
  int el = 0;
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<i_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() > elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;
      v_elecP4.push_back(theElectron.p4());
      vd_ElecCharge.push_back(theElectron.charge());

      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
      
      vd_ElecTrkIso .push_back(theElectron.trackIso());
      vd_ElecECalIso.push_back(theElectron.ecalIso());
      vd_ElecHCalIso.push_back(theElectron.hcalIso());
      vd_ElecAllIso .push_back(theElectron.caloIso());
      
      //vd_ElecECalIsoDeposit .push_back(theElectron.ecalIsoDeposit()->candEnergy() ;
      //vd_ElecHCalIsoDeposit .push_back(theElectron.hcalIsoDeposit()->candEnergy() ;
      
      vd_ElecIdLoose   .push_back(theElectron.electronID("eidLoose"));
      vd_ElecIdTight   .push_back(theElectron.electronID("eidTight"));
      vd_ElecIdRobLoose.push_back(theElectron.electronID("eidRobustLoose"));
      vd_ElecIdRobTight.push_back(theElectron.electronID("eidRobustTight")); 
      vd_ElecIdRobHighE.push_back(theElectron.electronID("eidRobustHighEnergy")); 
      
      vd_ElecCaloEnergy.push_back(theElectron.caloEnergy());
      vd_ElecHOverE    .push_back(theElectron.hadronicOverEm());
      vd_ElecVx        .push_back(theElectron.vx());
      vd_ElecVy        .push_back(theElectron.vy());
      vd_ElecVz        .push_back(theElectron.vz());
      
      vd_ElecD0              .push_back(theElectron.gsfTrack()->d0());
      vd_ElecDz              .push_back(theElectron.gsfTrack()->dz());
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
      
      vd_ElecWidthClusterEta.push_back(theElectron.superCluster()->etaWidth());
      vd_ElecWidthClusterPhi.push_back(theElectron.superCluster()->phiWidth());
      
      vd_ElecPinTrk.push_back(sqrt(theElectron.trackMomentumAtVtx().Mag2()));
      vd_ElecPoutTrk.push_back(sqrt(theElectron.trackMomentumOut().Mag2()));
      
      //get associated gen particle information
      if (doMCData_) {
      	const reco::Candidate* candElec = theElectron.genLepton();
      	if ( candElec ) {
      	  vd_ElecGenPdgId.push_back(candElec->pdgId());
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(candElec->px(),candElec->py(),candElec->pz(),candElec->energy());
	  v_genelecP4.push_back(genp4);
      	
      	  const reco::Candidate* elecMother = candElec->mother();
      	  if( elecMother ) {
      	    while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
      	    if ( elecMother ) {
      	      vd_ElecGenMother.push_back(theElectron.genLepton()->mother()->pdgId());
      	      //if ( theElectron.genLepton()->mother()->pdgId() ==  theElectron.genLepton()->pdgId()) 
      	      //  {
      	      //	vd_ElecGenMother[el] = theElectron.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	else {
      	  vd_ElecGenPdgId.push_back(-999.);
      	  vd_ElecGenMother.push_back(-999.);
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999.);
	  v_genelecP4.push_back(genp4);
      	}
      }
      double elecIsoReq = (vd_ElecTrkIso.at(el)+vd_ElecECalIso.at(el)+vd_ElecHCalIso.at(el))/v_elecP4.at(el).pt();
      if ( elecIsoReq  > elecRelIso_) bool_ElecVeto = bool_ElecVeto || true;
      if ( v_elecP4.at(el).pt() > elecMaxEt_ ) bool_ElecVeto = bool_ElecVeto || true;
      ++el;
    }
  }//end loop over Electrons
  i_ElecN = el;

  /*
   * get the muons
   *
   */

  edm::Handle< std::vector<pat::Muon> > muonHandle;
  iEvent.getByLabel(muonTag_, muonHandle);
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
  v_muonP4.resize(i_MuonN);
  v_genmuonP4.resize(i_MuonN);
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

      //vd_MuonECalIsoDeposit.push_back(theMuon.ecalIsoDeposit()->candEnergy());
      //vd_MuonHCalIsoDeposit.push_back(theMuon.hcalIsoDeposit()->candEnergy());

      vd_MuonECalIsoDeposit.push_back(theMuon.isolationR03().emVetoEt);
      vd_MuonHCalIsoDeposit.push_back(theMuon.isolationR03().hadVetoEt);

      //Muon classification variables
      vd_MuonIsGlobal.push_back(theMuon.isGlobalMuon());
      vd_MuonIsStandAlone.push_back(theMuon.isStandAloneMuon());
      vd_MuonIsTracker.push_back(theMuon.isTrackerMuon());
      
      vd_MuonGlobalMuonPromptTight.push_back(theMuon.muonID("GlobalMuonPromptTight"));
      						     
      vd_MuonAllArbitrated.push_back(theMuon.muonID("AllArbitrated"));
      vd_MuonTrackerMuonArbitrated.push_back(theMuon.muonID("TrackerMuonArbitrated"));

      vd_MuonTMLastStationLoose.push_back(theMuon.muonID("TMLastStationLoose"));
      vd_MuonTMLastStationTight.push_back(theMuon.muonID("TMLastStationTight"));

      vd_MuonTM2DCompatibilityLoose.push_back(theMuon.muonID("TM2DCompatibilityLoose"));
      vd_MuonTM2DCompatibilityTight.push_back(theMuon.muonID("TM2DCompatibilityTight"));

      vd_MuonTMOneStationLoose.push_back(theMuon.muonID("TMOneStationLoose"));
      vd_MuonTMOneStationTight.push_back(theMuon.muonID("TMOneStationTight"));

      vd_MuonTMLastStationOptimizedLowPtLoose.push_back(theMuon.muonID("TMLastStationOptimizedLowPtLoose"));
      vd_MuonTMLastStationOptimizedLowPtTight.push_back(theMuon.muonID("TMLastStationOptimizedLowPtTight"));

      vd_MuonGMTkChiCompatibility.push_back(theMuon.muonID("GMTkChiCompatibility"));
      vd_MuonGMStaChiCompatibility.push_back(theMuon.muonID("GMStaChiCompatibility"));
      vd_MuonGMTkKinkTight.push_back(theMuon.muonID("GMTkKinkTight"));

      vd_MuonTMLastStationAngLoose.push_back(theMuon.muonID("TMLastStationAngLoose"));
      vd_MuonTMLastStationAngTight.push_back(theMuon.muonID("TMLastStationAngTight"));

      vd_MuonTMLastStationOptimizedBarrelLowPtLoose.push_back(theMuon.muonID("TMLastStationOptimizedBarrelLowPtLoose"));
      vd_MuonTMLastStationOptimizedBarrelLowPtTight.push_back(theMuon.muonID("TMLastStationOptimizedBarrelLowPtTight"));
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	vd_MuonCombChi2.push_back(theMuon.combinedMuon()->chi2());
	vd_MuonCombNdof.push_back(theMuon.combinedMuon()->ndof());

	vd_MuonCombVx.push_back(theMuon.combinedMuon()->vx());
	vd_MuonCombVy.push_back(theMuon.combinedMuon()->vy());
	vd_MuonCombVz.push_back(theMuon.combinedMuon()->vz());
	vd_MuonCombD0.push_back(theMuon.combinedMuon()->d0());
	vd_MuonCombDz.push_back(theMuon.combinedMuon()->dz());

      } else {
	vd_MuonCombVx.push_back(999.);
	vd_MuonCombVy.push_back(999.);
	vd_MuonCombVz.push_back(999.);
	vd_MuonCombD0.push_back(999.);
	vd_MuonCombDz.push_back(999.);
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
	vd_MuonStandQOverPError.push_back(theMuon.standAloneMuon()->qoverpError());
      } 
      else{
	vd_MuonStandValidHits.push_back(999.);
	vd_MuonStandLostHits.push_back(999.);
	vd_MuonStandPt.push_back(999.);
	vd_MuonStandPz.push_back(999.);
	vd_MuonStandP.push_back(999.);
	vd_MuonStandEta.push_back(999.);
	vd_MuonStandPhi.push_back(999.);
	vd_MuonStandChi.push_back(999.);
	vd_MuonStandCharge.push_back(999.);
	vd_MuonStandQOverPError.push_back(999.);
      }

      //Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.track().isNonnull()){
	vd_MuonTrkChiNorm.push_back(theMuon.track()->normalizedChi2());
	vd_MuonTrkValidHits.push_back(theMuon.track()->found());
	vd_MuonTrkLostHits.push_back(theMuon.track()->lost());
	vd_MuonTrkD0.push_back(theMuon.track()->d0());
	vd_MuonTrkPt.push_back(theMuon.track()->pt());
	vd_MuonTrkPz.push_back(theMuon.track()->pz());
	vd_MuonTrkP.push_back(theMuon.track()->p());
	vd_MuonTrkEta.push_back(theMuon.track()->eta());
	vd_MuonTrkPhi.push_back(theMuon.track()->phi());
	vd_MuonTrkChi.push_back(theMuon.track()->chi2());
	vd_MuonTrkCharge.push_back(theMuon.track()->charge());
	vd_MuonTrkQOverPError.push_back(theMuon.track()->qoverpError());
	//  vd_MuonTrkOuterZ.push_back(theMuon.track()->outerZ());
	//  vd_MuonTrkOuterR.push_back(theMuon.track()->outerRadius());

      }
      else{
	vd_MuonTrkChiNorm.push_back(999.);
	vd_MuonTrkValidHits.push_back(999);
	vd_MuonTrkLostHits.push_back(999);
	vd_MuonTrkD0.push_back(999);
	vd_MuonTrkPt.push_back(999);
	vd_MuonTrkPz.push_back(999);
	vd_MuonTrkP.push_back(999);
	vd_MuonTrkEta.push_back(999);
	vd_MuonTrkPhi.push_back(999);
	vd_MuonTrkChi.push_back(999);
	vd_MuonTrkCharge.push_back(999);
	vd_MuonTrkQOverPError.push_back(999);
	//  vd_MuonTrkOuterZ.push_back(999.);
	//  vd_MuonTrkOuterR.push_back(999.);
      }

      //Muon gen particle association variables
      if (doMCData_) {
      	const reco::Candidate* candMuon = theMuon.genLepton();
      	if ( candMuon ) {
      	  vd_MuonGenPdgId.push_back(candMuon->pdgId());
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(candMuon->px(),candMuon->py(),candMuon->pz(),candMuon->energy());
	  v_genmuonP4.push_back(genp4);

      	  const reco::Candidate* muonMother = candMuon->mother();
      	  if( muonMother ) {
      	    while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
      	    if ( muonMother ) {
      	      vd_MuonGenMother.push_back(theMuon.genLepton()->mother()->pdgId());
      	      //if ( theMuon.genLepton()->mother()->pdgId() ==  theMuon.genLepton()->pdgId()) 
      	      //  {
      	      //	vd_MuonGenMother[mu] = theMuon.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	
      	else{
      	  vd_MuonGenPdgId.push_back(-999.);
	  vd_MuonGenMother.push_back(-999.);
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	  v_genmuonP4.push_back(genp4);
      	}
      }
      double muonIsoReq = (vd_MuonTrkIso.at(mu)+vd_MuonECalIso.at(mu)+vd_MuonHCalIso.at(mu))/v_muonP4.at(mu).pt();
      if ( muonIsoReq  > muonRelIso_) bool_MuonVeto = bool_MuonVeto || true;
      if ( v_muonP4.at(mu).pt() > muonMaxEt_)  bool_MuonVeto = bool_MuonVeto || true;
      ++mu;
    }
  }// end loop over muons
  i_MuonN = mu;
  // return true when none of the events have leptons above threshold
  lepton_result = !(bool_ElecVeto || bool_MuonVeto);
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

  // Add the branches
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
  //mLeptonData->Branch("NIsoelec",      &m_NIsoelec,     "NIsoelec/I");  

  //mLeptonData->Branch(prefix_+"ElecECalIsoDeposit", &vd_ElecECalIsoDeposit);
  //mLeptonData->Branch(prefix_+"ElecHCalIsoDeposit", &vd_ElecHCalIsoDeposit);

  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    &vd_ElecIdLoose);
  mLeptonData->Branch(prefix_+"ElecIdTight",    &vd_ElecIdTight);
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", &vd_ElecIdRobLoose);
  mLeptonData->Branch(prefix_+"ElecIdRobTight", &vd_ElecIdRobTight);
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", &vd_ElecIdRobHighE);
  mLeptonData->Branch(prefix_+"ElecChargeMode", &vd_ElecChargeMode);
  mLeptonData->Branch(prefix_+"ElecPtMode",     &vd_ElecPtTrkMode);


  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     &vd_ElecVx);
  mLeptonData->Branch(prefix_+"ElecVy",     &vd_ElecVy);
  mLeptonData->Branch(prefix_+"ElecVz",     &vd_ElecVz);
  mLeptonData->Branch(prefix_+"ElecD0",     &vd_ElecD0);
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

  if (doMCData_) {
    //Generator level information stored in the electron object
    mLeptonData->Branch(prefix_+"ElecGenPdgId",  &vd_ElecGenPdgId);
    mLeptonData->Branch(prefix_+"ElecGenMother", &vd_ElecGenMother);
    mLeptonData->Branch(prefix_+"ElecGenP4",&v_genelecP4);
  }

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
  mLeptonData->Branch(prefix_+"MuonIsGlobal",                              &vd_MuonIsGlobal);
  mLeptonData->Branch(prefix_+"MuonIsStandAlone",                          &vd_MuonIsStandAlone);
  mLeptonData->Branch(prefix_+"MuonIsTracker",                             &vd_MuonIsTracker);
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonGlobalMuonPromptTight",                 &vd_MuonGlobalMuonPromptTight);
  mLeptonData->Branch(prefix_+"MuonAllArbitrated",                         &vd_MuonAllArbitrated);
  mLeptonData->Branch(prefix_+"MuonTrackerMuonArbitrated",                 &vd_MuonTrackerMuonArbitrated);
  mLeptonData->Branch(prefix_+"MuonTMLastStationLoose",                    &vd_MuonTMLastStationLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationTight",                    &vd_MuonTMLastStationTight);
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityLoose",                &vd_MuonTM2DCompatibilityLoose);
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityTight",                &vd_MuonTM2DCompatibilityTight);
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     &vd_MuonTMOneStationLoose);
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     &vd_MuonTMOneStationTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtLoose",      &vd_MuonTMLastStationOptimizedLowPtLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtTight",      &vd_MuonTMLastStationOptimizedLowPtTight);
  mLeptonData->Branch(prefix_+"MuonGMTkChiCompatibility",                  &vd_MuonGMTkChiCompatibility);
  mLeptonData->Branch(prefix_+"MuonGMStaChiCompatibility",                 &vd_MuonGMStaChiCompatibility);
  mLeptonData->Branch(prefix_+"MuonGMTkKinkTight",                         &vd_MuonGMTkKinkTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngLoose",                 &vd_MuonTMLastStationAngLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngTight",                 &vd_MuonTMLastStationAngTight);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose",&vd_MuonTMLastStationOptimizedBarrelLowPtLoose);
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight",&vd_MuonTMLastStationOptimizedBarrelLowPtTight);
  
  //  mLeptonData->Branch(prefix_+"MuonId", &vd_MuonId);
  mLeptonData->Branch(prefix_+"MuonCombChi2", &vd_MuonCombChi2);
  mLeptonData->Branch(prefix_+"MuonCombNdof", &vd_MuonCombNdof);
  mLeptonData->Branch(prefix_+"MuonCombVx",   &vd_MuonCombVx);
  mLeptonData->Branch(prefix_+"MuonCombVy",   &vd_MuonCombVy);
  mLeptonData->Branch(prefix_+"MuonCombVz",   &vd_MuonCombVz);
  mLeptonData->Branch(prefix_+"MuonCombD0",   &vd_MuonCombD0);
  mLeptonData->Branch(prefix_+"MuonCombDz",   &vd_MuonCombDz);

  //Muon tracking information
  mLeptonData->Branch(prefix_+"MuonStandValidHits",   &vd_MuonStandValidHits);
  mLeptonData->Branch(prefix_+"MuonStandLostHits",    &vd_MuonStandLostHits);
  mLeptonData->Branch(prefix_+"MuonStandPt",          &vd_MuonStandPt);
  mLeptonData->Branch(prefix_+"MuonStandPz",          &vd_MuonStandPz);
  mLeptonData->Branch(prefix_+"MuonStandP",           &vd_MuonStandP);
  mLeptonData->Branch(prefix_+"MuonStandEta",         &vd_MuonStandEta);
  mLeptonData->Branch(prefix_+"MuonStandPhi",         &vd_MuonStandPhi);
  mLeptonData->Branch(prefix_+"MuonStandCharge",      &vd_MuonStandCharge);
  mLeptonData->Branch(prefix_+"MuonStandChi",         &vd_MuonStandChi);
  mLeptonData->Branch(prefix_+"MuonStandQOverPError", &vd_MuonStandQOverPError);

  mLeptonData->Branch(prefix_+"MuonTrkValidHits",   &vd_MuonTrkValidHits);
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",    &vd_MuonTrkLostHits);
  mLeptonData->Branch(prefix_+"MuonTrkD0",          &vd_MuonTrkD0);
  mLeptonData->Branch(prefix_+"MuonTrkPt",          &vd_MuonTrkPt);
  mLeptonData->Branch(prefix_+"MuonTrkPz",          &vd_MuonTrkPz);
  mLeptonData->Branch(prefix_+"MuonTrkP",           &vd_MuonTrkP);
  mLeptonData->Branch(prefix_+"MuonTrkEta",         &vd_MuonTrkEta);
  mLeptonData->Branch(prefix_+"MuonTrkPhi",         &vd_MuonTrkPhi);
  mLeptonData->Branch(prefix_+"MuonTrkCharge",      &vd_MuonTrkCharge);
  mLeptonData->Branch(prefix_+"MuonTrkChi",         &vd_MuonTrkChi);
  mLeptonData->Branch(prefix_+"MuonTrkQOverPError", &vd_MuonTrkQOverPError);
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",      &vd_MuonTrkOuterZ);
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",      &vd_MuonTrkOuterR);

  //Generator level muon information
  if (doMCData_) {
    mLeptonData->Branch(prefix_+"MuonGenPdgId",  &vd_MuonGenPdgId);
    mLeptonData->Branch(prefix_+"MuonGenMother", &vd_MuonGenMother);
    mLeptonData->Branch(prefix_+"MuonGenP4",     &v_genmuonP4);
    
    //generator leptons (electrons and muons)
    mLeptonData->Branch(prefix_+"genP4",     &v_genP4);
    mLeptonData->Branch(prefix_+"genN",      &i_length,        prefix_+"genN/I");
    mLeptonData->Branch(prefix_+"genid",     &vi_genIds);
    mLeptonData->Branch(prefix_+"genMother", &vi_genRefs);
    
    //generator leptons status (electrons and muons)
    mLeptonData->Branch(prefix_+"genLepP4",     &v_genLepP4);
    mLeptonData->Branch(prefix_+"genLepN",      &i_genLepLength, prefix_+"genLepN/I");
    mLeptonData->Branch(prefix_+"genLepId",     &vi_genLepIds);
    mLeptonData->Branch(prefix_+"genLepMother", &vi_genLepRefs);
    mLeptonData->Branch(prefix_+"genLepStatus", &vi_genLepStatus);

    mLeptonData->Branch(prefix_+"pthat", &d_Pthat, prefix_+"pthat/D");
  }    

  edm::LogInfo("LeptonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

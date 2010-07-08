
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
// $Id: LeptonAnalyzerPAT.cc,v 1.7 2010/07/05 09:28:12 sturdy Exp $
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
    //v_genP4.resize(genParticles->size());
    //v_genLepP4.resize(genParticles->size());
    if (debug_) sprintf(logmessage,"Status   genpart/%d   PdgId   genE   genPx   genPy   genPz   genMother",genParticles->size());
    if (debug_>1) edm::LogVerbatim("LeptonEvent") << logmessage<< std::endl;

    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      //get status 3 particles
      if (st==3) {
	//v_genP4.at(count)  = pCand.p4();
	v_genP4.push_back(pCand.p4());
	mat_i_genIds[count]    = pCand.pdgId();
	mat_i_genStatus[count] = pCand.status();
	mat_f_genE[count]      = pCand.energy();
	mat_f_genPx[count]     = pCand.px();
	mat_f_genPy[count]     = pCand.py();
	mat_f_genPz[count]     = pCand.pz();
      
	if (pCand.numberOfMothers() > 0 ) { 
	  const reco::Candidate * mom = pCand.mother();
	  while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	  
	  for( size_t j = 0; j < i; ++ j ) {
	    const Candidate * ref = &((*genParticles)[j]);
	    if (ref == mom) { mat_i_genRefs[count] = ref->pdgId(); } //return mother's pdgId
	    //if (ref == mom) { mat_i_genRefs[count] = j; } //point to particle that is reference
	  }  
	} else { mat_i_genRefs[count]=-999;}

	if (debug_) sprintf(logmessage,"%2d       %4d       %4d       %4.2f     %4.2f    %4.2f    %4.2f     %4d", \
	       mat_i_genStatus[count],count,mat_i_genIds[count],mat_f_genE[count],mat_f_genPx[count],mat_f_genPy[count],mat_f_genPz[count],mat_i_genRefs[count]);
	if (debug_>1)  edm::LogVerbatim("LeptonEvent") << logmessage<<std::endl;
	++count;
      }
      else { // store also electrons or muons of status 1 
	if ( (abs(pCand.pdgId()) == 11) || (abs(pCand.pdgId()) == 13) ) {
	  
	  //v_genLepP4.at(lcount) = pCand.p4();
	  v_genLepP4.push_back(pCand.p4());
	  mat_i_genLepIds[lcount]    = pCand.pdgId();
	  mat_i_genLepStatus[lcount] = pCand.status();
	  mat_f_genLepE[lcount]      = pCand.energy();
	  mat_f_genLepPx[lcount]     = pCand.px();
	  mat_f_genLepPy[lcount]     = pCand.py();
	  mat_f_genLepPz[lcount]     = pCand.pz();
	  
	  if (pCand.numberOfMothers() > 0 ) { 
	    const reco::Candidate * mom = pCand.mother();
	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
	    
	    for( size_t j = 0; j < i; ++ j ) {
	      const reco::Candidate * ref = &((*genParticles)[j]);
	      if (ref == mom) { mat_i_genLepRefs[lcount] = ref->pdgId(); }
	      //if (ref == mom) { mat_i_genLepRefs[lcount] = j; }
	    }  
	  } else { mat_i_genLepRefs[lcount]=-999;}

	  if (debug_) sprintf(logmessage,"%2d         %4d         %4d         %4.2f       %4.2f    %4.2f    %4.2f     %4d", \
		 mat_i_genLepStatus[lcount],lcount,mat_i_genLepIds[lcount],mat_f_genLepE[lcount],mat_f_genLepPx[lcount],mat_f_genLepPy[lcount],mat_f_genLepPz[lcount],mat_i_genLepRefs[lcount]);
	  if (debug_>1)  edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
	  ++lcount;
	}
      }
    }
    i_length = count;
    mat_i_genLepLength = lcount;
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
  if (debug_) sprintf(logmessage,"Elec/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",i_ElecN);
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<i_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() > elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;
      //v_elecP4.at(el)    = theElectron.p4();
      v_elecP4.push_back(theElectron.p4());
      mat_d_ElecE[el]      = theElectron.energy();
      mat_d_ElecEt[el]     = theElectron.et();
      mat_d_ElecPt[el]     = theElectron.pt();
      mat_d_ElecPx[el]     = theElectron.momentum().X();
      mat_d_ElecPy[el]     = theElectron.momentum().Y();
      mat_d_ElecPz[el]     = theElectron.momentum().Z();
      mat_d_ElecEta[el]    = theElectron.eta();
      mat_d_ElecPhi[el]    = theElectron.phi();
      mat_d_ElecCharge[el] = theElectron.charge();

      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f", \
			  el,mat_d_ElecE[el],mat_d_ElecEt[el],mat_d_ElecPt[el],mat_d_ElecPx[el],mat_d_ElecPy[el],mat_d_ElecPz[el],mat_d_ElecEta[el],mat_d_ElecPhi[el]);
      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
      
      mat_d_ElecTrkIso[el]  = theElectron.trackIso();
      mat_d_ElecECalIso[el] = theElectron.ecalIso();
      mat_d_ElecHCalIso[el] = theElectron.hcalIso() ;
      mat_d_ElecAllIso[el]  = theElectron.caloIso() ;
      
      //mat_d_ElecECalIsoDeposit[el]  = theElectron.ecalIsoDeposit()->candEnergy() ;
      //mat_d_ElecHCalIsoDeposit[el]  = theElectron.hcalIsoDeposit()->candEnergy() ;
      
      mat_d_ElecIdLoose[el]    = theElectron.electronID("eidLoose");
      mat_d_ElecIdTight[el]    = theElectron.electronID("eidTight");
      mat_d_ElecIdRobLoose[el] = theElectron.electronID("eidRobustLoose");
      mat_d_ElecIdRobTight[el] = theElectron.electronID("eidRobustTight"); 
      mat_d_ElecIdRobHighE[el] = theElectron.electronID("eidRobustHighEnergy"); 
      
      mat_d_ElecCaloEnergy[el] = theElectron.caloEnergy();
      mat_d_ElecHOverE[el]     = theElectron.hadronicOverEm();
      mat_d_ElecVx[el]         = theElectron.vx();
      mat_d_ElecVy[el]         = theElectron.vy();
      mat_d_ElecVz[el]         = theElectron.vz();
      
      mat_d_ElecD0[el]               = theElectron.gsfTrack()->d0();
      mat_d_ElecDz[el]               = theElectron.gsfTrack()->dz();
      mat_d_ElecChargeMode[el]       = theElectron.gsfTrack()->chargeMode();	
      mat_d_ElecPtTrkMode[el]        = theElectron.gsfTrack()->ptMode();
      mat_d_ElecQOverPErrTrkMode[el] = theElectron.gsfTrack()->qoverpModeError();
      mat_d_ElecCharge[el]           = theElectron.gsfTrack()->charge();
      mat_d_ElecPtTrk[el]            = theElectron.gsfTrack()->pt();
      mat_d_ElecQOverPErrTrk[el]     = theElectron.gsfTrack()->qoverpError();
      mat_d_ElecNormChi2[el]         = theElectron.gsfTrack()->normalizedChi2();
      mat_d_ElecLostHits[el]         = theElectron.gsfTrack()->lost();
      mat_d_ElecValidHits[el]        = theElectron.gsfTrack()->found();
    
      mat_d_ElecEtaTrk[el] = theElectron.trackMomentumAtVtx().Eta();
      mat_d_ElecPhiTrk[el] = theElectron.trackMomentumAtVtx().Phi();
      
      //mat_d_ElecNCluster[i] = theElectron.numberOfClusters();
      //// Added protection statement, against missing SuperCluster collection in 2_1_X PatLayer1 samples
      //try { 
      mat_d_ElecWidthClusterEta[el] = theElectron.superCluster()->etaWidth();
      mat_d_ElecWidthClusterPhi[el] = theElectron.superCluster()->phiWidth();
      //} catch ( const cms::Exception& e ) {
      //	mat_d_ElecWidthClusterEta[i]=-999.;
      //	mat_d_ElecWidthClusterPhi[i]=-999.;
      //	std::stringstream ss;
      //	ss << " cms::Exception caught!"
      //	   << " Invalid edm::Ref<reco::SuperCluster> returned from pat::Electron!" 
      //	   << std::endl 
      //	   << " Setting ClusterEta and ClusterPhi to -999.!" 
      //	   << std::endl 
      //	   << " Output from cms::Exception::what():"
      //	   << std::endl 
      //	   << e.what();
      //	edm::LogWarning("LeptonEvent") << ss.str();
      //}
      
      mat_d_ElecPinTrk[el]  = sqrt(theElectron.trackMomentumAtVtx().Mag2());
      mat_d_ElecPoutTrk[el] = sqrt(theElectron.trackMomentumOut().Mag2());
      
      //get associated gen particle information
      if (doMCData_) {
      	const reco::Candidate* candElec = theElectron.genLepton();
      	if ( candElec ) {
      	  mat_d_ElecGenPdgId[el] = candElec->pdgId();
      	  mat_d_ElecGenPx[el]    = candElec->px();
      	  mat_d_ElecGenPy[el]    = candElec->py();
      	  mat_d_ElecGenPz[el]    = candElec->pz();
      	  mat_d_ElecGenPt[el]    = candElec->pt();
      	  mat_d_ElecGenEt[el]    = candElec->et();
      	  mat_d_ElecGenE[el]     = candElec->energy();
        
      	  const reco::Candidate* elecMother = candElec->mother();
      	  if( elecMother ) {
      	    while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
      	    if ( elecMother ) {
      	      mat_d_ElecGenMother[el] = theElectron.genLepton()->mother()->pdgId();
      	      //if ( theElectron.genLepton()->mother()->pdgId() ==  theElectron.genLepton()->pdgId()) 
      	      //  {
      	      //	mat_d_ElecGenMother[el] = theElectron.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	else {
      	  mat_d_ElecGenPdgId[el]  = -999.;
      	  mat_d_ElecGenMother[el] = -999.;
      	  mat_d_ElecGenPx[el]     = -999.;
      	  mat_d_ElecGenPy[el]     = -999.;
      	  mat_d_ElecGenPz[el]     = -999.;
      	  mat_d_ElecGenPt[el]     = -999.;
      	  mat_d_ElecGenEt[el]     = -999.;
      	  mat_d_ElecGenE[el]      = -999.;
      	}
      }
      double elecIsoReq = (mat_d_ElecTrkIso[el]+mat_d_ElecECalIso[el]+mat_d_ElecHCalIso[el])/mat_d_ElecPt[el];
      if ( elecIsoReq  > elecRelIso_) bool_ElecVeto = bool_ElecVeto || true;
      if ( mat_d_ElecPt[el] > elecMaxEt_ ) bool_ElecVeto = bool_ElecVeto || true;
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
  int mu = 0;

  if (debug_) sprintf(logmessage,"Muon/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",i_MuonN);
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

  for (int i=0;i<i_MuonN;i++){
    const pat::Muon& theMuon = (*muonHandle)[i];
    if ( (theMuon.pt() > muonMinEt_) && !(theMuon.eta() > muonMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good muons " << std::endl;      
      //v_muonP4.at(mu) = theMuon.p4();
      v_muonP4.push_back(theMuon.p4());
      mat_d_MuonE[mu]   = theMuon.energy();
      mat_d_MuonEt[mu]  = theMuon.et();
      mat_d_MuonPt[mu]  = theMuon.pt();
      mat_d_MuonPx[mu]  = theMuon.momentum().X();
      mat_d_MuonPy[mu]  = theMuon.momentum().Y();
      mat_d_MuonPz[mu]  = theMuon.momentum().Z();
      mat_d_MuonEta[mu] = theMuon.eta();
      mat_d_MuonPhi[mu] = theMuon.phi();
      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f\n", \
			  mu,mat_d_MuonE[mu],mat_d_MuonEt[mu],mat_d_MuonPt[mu],mat_d_MuonPx[mu],mat_d_MuonPy[mu],mat_d_MuonPz[mu],mat_d_MuonEta[mu],mat_d_MuonPhi[mu]);
      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

      //Muon isolation variables
      mat_d_MuonCharge[mu]   = theMuon.charge();
      mat_d_MuonTrkIso[mu]   = theMuon.trackIso();
      mat_d_MuonECalIso[mu]  = theMuon.ecalIso();
      mat_d_MuonHCalIso[mu]  = theMuon.hcalIso() ;
      mat_d_MuonAllIso[mu]   = theMuon.caloIso() ;

      //mat_d_MuonECalIsoDeposit[mu]  = theMuon.ecalIsoDeposit()->candEnergy() ;
      //mat_d_MuonHCalIsoDeposit[mu]  = theMuon.hcalIsoDeposit()->candEnergy() ;

      mat_d_MuonECalIsoDeposit[mu]  = theMuon.isolationR03().emVetoEt;
      mat_d_MuonHCalIsoDeposit[mu]  = theMuon.isolationR03().hadVetoEt;

      //Muon classification variables
      mat_d_MuonIsGlobal[mu]     = theMuon.isGlobalMuon();
      mat_d_MuonIsStandAlone[mu] = theMuon.isStandAloneMuon();
      mat_d_MuonIsTracker[mu]    = theMuon.isTrackerMuon();
      
      mat_d_MuonGlobalMuonPromptTight[mu]          = theMuon.muonID("GlobalMuonPromptTight");
      
      mat_d_MuonAllArbitrated[mu]                  = theMuon.muonID("AllArbitrated");
      mat_d_MuonTrackerMuonArbitrated[mu]          = theMuon.muonID("TrackerMuonArbitrated");
      mat_d_MuonTMLastStationLoose[mu]             = theMuon.muonID("TMLastStationLoose");
      mat_d_MuonTMLastStationTight[mu]             = theMuon.muonID("TMLastStationTight");
      mat_d_MuonTM2DCompatibilityLoose[mu]         = theMuon.muonID("TM2DCompatibilityLoose");
      mat_d_MuonTM2DCompatibilityTight[mu]         = theMuon.muonID("TM2DCompatibilityTight");
      mat_d_MuonTMOneStationLoose[mu]              = theMuon.muonID("TMOneStationLoose");
      mat_d_MuonTMOneStationTight[mu]              = theMuon.muonID("TMOneStationTight");
      mat_d_MuonTMLastStationOptimizedLowPtLoose[mu] = theMuon.muonID("TMLastStationOptimizedLowPtLoose");
      mat_d_MuonTMLastStationOptimizedLowPtTight[mu] = theMuon.muonID("TMLastStationOptimizedLowPtTight");
      mat_d_MuonGMTkChiCompatibility[mu]           = theMuon.muonID("GMTkChiCompatibility");
      mat_d_MuonGMStaChiCompatibility[mu]          = theMuon.muonID("GMStaChiCompatibility");
      mat_d_MuonGMTkKinkTight[mu]                  = theMuon.muonID("GMTkKinkTight");
      mat_d_MuonTMLastStationAngLoose[mu]          = theMuon.muonID("TMLastStationAngLoose");
      mat_d_MuonTMLastStationAngTight[mu]          = theMuon.muonID("TMLastStationAngTight");
      mat_d_MuonTMLastStationOptimizedBarrelLowPtLoose[mu] = theMuon.muonID("TMLastStationOptimizedBarrelLowPtLoose");
      mat_d_MuonTMLastStationOptimizedBarrelLowPtTight[mu] = theMuon.muonID("TMLastStationOptimizedBarrelLowPtTight");
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	mat_d_MuonCombChi2[mu] = theMuon.combinedMuon()->chi2();
	mat_d_MuonCombNdof[mu] = theMuon.combinedMuon()->ndof();

	mat_d_MuonCombVx[mu] = theMuon.combinedMuon()->vx();
	mat_d_MuonCombVy[mu] = theMuon.combinedMuon()->vy();
	mat_d_MuonCombVz[mu] = theMuon.combinedMuon()->vz();
	mat_d_MuonCombD0[mu] = theMuon.combinedMuon()->d0();
	mat_d_MuonCombDz[mu] = theMuon.combinedMuon()->dz();

      } else {
	mat_d_MuonCombVx[mu] = 999.;
	mat_d_MuonCombVy[mu] = 999.;
	mat_d_MuonCombVz[mu] = 999.;
	mat_d_MuonCombD0[mu] = 999.;
	mat_d_MuonCombDz[mu] = 999.;
      }

      //Standalone muon information
      if(theMuon.isStandAloneMuon() && theMuon.standAloneMuon().isNonnull()){
	mat_d_MuonStandValidHits[mu]   = theMuon.standAloneMuon()->found();
	mat_d_MuonStandLostHits[mu]    = theMuon.standAloneMuon()->lost();
	mat_d_MuonStandPt[mu]          = theMuon.standAloneMuon()->pt();
	mat_d_MuonStandPz[mu]          = theMuon.standAloneMuon()->pz();
	mat_d_MuonStandP[mu]           = theMuon.standAloneMuon()->p();
	mat_d_MuonStandEta[mu]         = theMuon.standAloneMuon()->eta();
	mat_d_MuonStandPhi[mu]         = theMuon.standAloneMuon()->phi();
	mat_d_MuonStandChi[mu]         = theMuon.standAloneMuon()->chi2();
	mat_d_MuonStandCharge[mu]      = theMuon.standAloneMuon()->charge();
	mat_d_MuonStandQOverPError[mu] = theMuon.standAloneMuon()->qoverpError();
      } 
      else{
	mat_d_MuonStandValidHits[mu]   = 999.;
	mat_d_MuonStandLostHits[mu]    = 999.;
	mat_d_MuonStandPt[mu]          = 999.;
	mat_d_MuonStandPz[mu]          = 999.;
	mat_d_MuonStandP[mu]           = 999.;
	mat_d_MuonStandEta[mu]         = 999.;
	mat_d_MuonStandPhi[mu]         = 999.;
	mat_d_MuonStandChi[mu]         = 999.;
	mat_d_MuonStandCharge[mu]      = 999.;
	mat_d_MuonStandQOverPError[mu] = 999.;
      }

      //Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.track().isNonnull()){
	mat_d_MuonTrkChiNorm[mu]     = theMuon.track()->normalizedChi2();
	mat_d_MuonTrkValidHits[mu]   = theMuon.track()->found();
	mat_d_MuonTrkLostHits[mu]    = theMuon.track()->lost();
	mat_d_MuonTrkD0[mu]          = theMuon.track()->d0();
	mat_d_MuonTrkPt[mu]          = theMuon.track()->pt();
	mat_d_MuonTrkPz[mu]          = theMuon.track()->pz();
	mat_d_MuonTrkP[mu]           = theMuon.track()->p();
	mat_d_MuonTrkEta[mu]         = theMuon.track()->eta();
	mat_d_MuonTrkPhi[mu]         = theMuon.track()->phi();
	mat_d_MuonTrkChi[mu]         = theMuon.track()->chi2();
	mat_d_MuonTrkCharge[mu]      = theMuon.track()->charge();
	mat_d_MuonTrkQOverPError[mu] = theMuon.track()->qoverpError();
	//  mat_d_MuonTrkOuterZ[mu]=theMuon.track()->outerZ();
	//  mat_d_MuonTrkOuterR[mu]=theMuon.track()->outerRadius();

      }
      else{
	mat_d_MuonTrkChiNorm[mu]    = 999.;
	mat_d_MuonTrkValidHits[mu]  = 999.;
	mat_d_MuonTrkLostHits[mu]   = 999.;
	mat_d_MuonTrkPt[mu]         = 999.;
	mat_d_MuonTrkPz[mu]         = 999.;
	mat_d_MuonTrkP[mu]          = 999.;
	mat_d_MuonTrkEta[mu]        = 999.;
	mat_d_MuonTrkPhi[mu]        = 999.;
	mat_d_MuonTrkChi[mu]        = 999.;
	mat_d_MuonTrkCharge[mu]     = 999.;
	mat_d_MuonTrkQOverPError[mu]= 999.;
	mat_d_MuonTrkOuterZ[mu]     = 999.;
	mat_d_MuonTrkOuterR[mu]     = 999.;
      }

      //Muon gen particle association variables
      if (doMCData_) {
      	const reco::Candidate* candMuon = theMuon.genLepton();
      	if ( candMuon ) {
      	  mat_d_MuonGenPdgId[mu] = candMuon->pdgId();
      	  mat_d_MuonGenPx[mu]    = candMuon->px();
      	  mat_d_MuonGenPy[mu]    = candMuon->py();
      	  mat_d_MuonGenPz[mu]    = candMuon->pz();
      	  mat_d_MuonGenPt[mu]    = candMuon->pt();
      	  mat_d_MuonGenEt[mu]    = candMuon->et();
      	  mat_d_MuonGenE[mu]     = candMuon->energy();
      	  
      	  const reco::Candidate* muonMother = candMuon->mother();
      	  if( muonMother ) {
      	    while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
      	    if ( muonMother ) {
      	      mat_d_MuonGenMother[mu] = theMuon.genLepton()->mother()->pdgId();
      	      //if ( theMuon.genLepton()->mother()->pdgId() ==  theMuon.genLepton()->pdgId()) 
      	      //  {
      	      //	mat_d_MuonGenMother[mu] = theMuon.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	
      	else{
      	  mat_d_MuonGenPdgId[mu]  = -999.;
      	  mat_d_MuonGenMother[mu] = -999.;
      	  mat_d_MuonGenPx[mu]     = -999.;
      	  mat_d_MuonGenPy[mu]     = -999.;
      	  mat_d_MuonGenPz[mu]     = -999.;
      	  mat_d_MuonGenPt[mu]     = -999.;
      	  mat_d_MuonGenEt[mu]     = -999.;
      	  mat_d_MuonGenE[mu]      = -999.;
      	}
      }
      double muonIsoReq = (mat_d_MuonTrkIso[mu]+mat_d_MuonECalIso[mu]+mat_d_MuonHCalIso[mu])/mat_d_MuonPt[mu];
      if ( muonIsoReq  > muonRelIso_) bool_MuonVeto = bool_MuonVeto || true;
      if ( mat_d_MuonPt[mu] > muonMaxEt_)  bool_MuonVeto = bool_MuonVeto || true;
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
  mLeptonData->Branch(prefix_+"ElectronP4",&v_elecP4,     prefix_+"ElectronP4");
  mLeptonData->Branch(prefix_+"ElecN",     &i_ElecN,      prefix_+"ElecN/I");  
  mLeptonData->Branch(prefix_+"ElecE",      mat_d_ElecE,      prefix_+"ElecE["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecEt",     mat_d_ElecEt,     prefix_+"ElecEt["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPt",     mat_d_ElecPt,     prefix_+"ElecPt["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPx",     mat_d_ElecPx,     prefix_+"ElecPx["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPy",     mat_d_ElecPy,     prefix_+"ElecPy["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPz",     mat_d_ElecPz,     prefix_+"ElecPz["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecEta",    mat_d_ElecEta,    prefix_+"ElecEta["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPhi",    mat_d_ElecPhi,    prefix_+"ElecPhi["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecCharge", mat_d_ElecCharge, prefix_+"ElecCharge["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecHOverE", mat_d_ElecHOverE, prefix_+"ElecHOverE["+prefix_+"ElecN]/D");

  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"ElecTrkIso",     mat_d_ElecTrkIso,   prefix_+"ElecTrkIso["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecECalIso",    mat_d_ElecECalIso,  prefix_+"ElecECalIso["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecHCalIso",    mat_d_ElecHCalIso,  prefix_+"ElecHCalIso["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecAllIso",     mat_d_ElecAllIso,   prefix_+"ElecAllIso["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecTrkChiNorm", mat_d_ElecNormChi2, prefix_+"ElecTrkChiNorm["+prefix_+"ElecN]/D");
  //mLeptonData->Branch("NIsoelec",      &m_NIsoelec,     "NIsoelec/I");  

  //mLeptonData->Branch(prefix_+"ElecECalIsoDeposit", mat_d_ElecECalIsoDeposit, prefix_+"ElecECalIsoDeposit["+prefix_+"ElecN]/D");
  //mLeptonData->Branch(prefix_+"ElecHCalIsoDeposit", mat_d_ElecHCalIsoDeposit, prefix_+"ElecHCalIsoDeposit["+prefix_+"ElecN]/D");

  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    mat_d_ElecIdLoose,    prefix_+"ElecIdLoose["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecIdTight",    mat_d_ElecIdTight,    prefix_+"ElecIdTight["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", mat_d_ElecIdRobLoose, prefix_+"ElecIdRobLoose["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecIdRobTight", mat_d_ElecIdRobTight, prefix_+"ElecIdRobTight["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", mat_d_ElecIdRobHighE, prefix_+"ElecIdRobHighE["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecChargeMode", mat_d_ElecChargeMode, prefix_+"ElecChargeMode["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPtMode",     mat_d_ElecPtTrkMode,  prefix_+"ElecPtMode["+prefix_+"ElecN]/D");


  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     mat_d_ElecVx,     prefix_+"ElecVx["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecVy",     mat_d_ElecVy,     prefix_+"ElecVy["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecVz",     mat_d_ElecVz,     prefix_+"ElecVz["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecD0",     mat_d_ElecD0,     prefix_+"ElecD0["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecDz",     mat_d_ElecDz,     prefix_+"ElecDz["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPtTrk",  mat_d_ElecPtTrk,  prefix_+"ElecPtTrk["+prefix_+"ElecN]/D");

  //Additonal electron detector information
  //Electron tracking information
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrkMode", mat_d_ElecQOverPErrTrkMode, prefix_+"ElecQOverPErrTrkMode["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecCaloEnergy",       mat_d_ElecCaloEnergy,       prefix_+"ElecCaloEnergy["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrk",     mat_d_ElecQOverPErrTrk,     prefix_+"ElecQOverPErrTrk["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPinTrk",           mat_d_ElecPinTrk,           prefix_+"ElecPinTrk["+prefix_+"ElecN]/D");
  mLeptonData->Branch(prefix_+"ElecPoutTrk",          mat_d_ElecPoutTrk,          prefix_+"ElecPoutTrk["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecLostHits",         mat_d_ElecLostHits,         prefix_+"ElecLostHits["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecValidHits",        mat_d_ElecValidHits,        prefix_+"ElecValidHits["+prefix_+"ElecN]/D"); 
  //mLeptonData->Branch(prefix_+"ElecNCluster",         mat_d_ElecNCluster,         prefix_+"ElecNCluster["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecEtaTrk",           mat_d_ElecEtaTrk,           prefix_+"ElecEtaTrk["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecPhiTrk",           mat_d_ElecPhiTrk,           prefix_+"ElecPhiTrk["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecWidthClusterEta",  mat_d_ElecWidthClusterEta,  prefix_+"ElecWidthClusterEta["+prefix_+"ElecN]/D"); 
  mLeptonData->Branch(prefix_+"ElecWidthClusterPhi",  mat_d_ElecWidthClusterPhi,  prefix_+"ElecWidthClusterPhi["+prefix_+"ElecN]/D"); 

  if (doMCData_) {
    //Generator level information stored in the electron object
    mLeptonData->Branch(prefix_+"ElecGenPdgId",  mat_d_ElecGenPdgId,  prefix_+"ElecGenPdgId["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenMother", mat_d_ElecGenMother, prefix_+"ElecGenMother["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenPx",     mat_d_ElecGenPx,     prefix_+"ElecGenPx["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenPy",     mat_d_ElecGenPy,     prefix_+"ElecGenPy["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenPz",     mat_d_ElecGenPz,     prefix_+"ElecGenPz["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenPt",     mat_d_ElecGenPt,     prefix_+"ElecGenPt["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenEt",     mat_d_ElecGenEt,     prefix_+"ElecGenEt["+prefix_+"ElecN]/D");
    mLeptonData->Branch(prefix_+"ElecGenE",      mat_d_ElecGenE,      prefix_+"ElecGenE["+prefix_+"ElecN]/D");
  }

  //add muons
  mLeptonData->Branch(prefix_+"MuonVeto", &bool_MuonVeto, prefix_+"MuonVeto/O");
  //General kinematic variables related to muons
  mLeptonData->Branch(prefix_+"MuonP4",        &v_muonP4,         prefix_+"MuonP4");
  mLeptonData->Branch(prefix_+"MuonN",         &i_MuonN,          prefix_+"MuonN/I");  
  mLeptonData->Branch(prefix_+"MuonE",          mat_d_MuonE,          prefix_+"MuonE["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonEt",         mat_d_MuonEt,         prefix_+"MuonEt["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonPt",         mat_d_MuonPt,         prefix_+"MuonPt["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonPx",         mat_d_MuonPx,         prefix_+"MuonPx["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonPy",         mat_d_MuonPy,         prefix_+"MuonPy["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonPz",         mat_d_MuonPz,         prefix_+"MuonPz["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonEta",        mat_d_MuonEta,        prefix_+"MuonEta["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonPhi",        mat_d_MuonPhi,        prefix_+"MuonPhi["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCharge",     mat_d_MuonCharge,     prefix_+"MuonCharge["+prefix_+"MuonN]/D");

  //Muon isolation variables
  //mLeptonData->Branch("NIsomuon",      &m_NIsomuon,       "NIsomuon/I");  
  mLeptonData->Branch(prefix_+"MuonTrkIso",     mat_d_MuonTrkIso,     prefix_+"MuonTrkIso["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonECalIso",    mat_d_MuonECalIso,    prefix_+"MuonECalIso["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonHCalIso",    mat_d_MuonHCalIso,    prefix_+"MuonHCalIso["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonAllIso",     mat_d_MuonAllIso,     prefix_+"MuonAllIso["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkChiNorm", mat_d_MuonTrkChiNorm, prefix_+"MuonTrkChiNorm["+prefix_+"MuonN]/D");

  mLeptonData->Branch(prefix_+"MuonECalIsoDeposit", mat_d_MuonECalIsoDeposit, prefix_+"MuonECalIsoDeposit["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonHCalIsoDeposit", mat_d_MuonHCalIsoDeposit, prefix_+"MuonHCalIsoDeposit["+prefix_+"MuonN]/D");

  //Muon calorimeter type
  mLeptonData->Branch(prefix_+"MuonIsGlobal",                              mat_d_MuonIsGlobal,                               prefix_+"MuonIsGlobal["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonIsStandAlone",                          mat_d_MuonIsStandAlone,                           prefix_+"MuonIsStandAlone["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonIsTracker",                             mat_d_MuonIsTracker,                              prefix_+"MuonIsTracker["+prefix_+"MuonN]/D");
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonGlobalMuonPromptTight",                 mat_d_MuonGlobalMuonPromptTight,                  prefix_+"MuonGlobalMuonPromptTight["+prefix_+"MuonN]/D");
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonAllArbitrated",                         mat_d_MuonAllArbitrated,                          prefix_+"MuonAllArbitrated["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrackerMuonArbitrated",                 mat_d_MuonTrackerMuonArbitrated,                  prefix_+"MuonTrackerMuonArbitrated["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationLoose",                    mat_d_MuonTMLastStationLoose,                     prefix_+"MuonTMLastStationLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationTight",                    mat_d_MuonTMLastStationTight,                     prefix_+"MuonTMLastStationTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityLoose",                mat_d_MuonTM2DCompatibilityLoose,                 prefix_+"MuonTM2DCompatibilityLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityTight",                mat_d_MuonTM2DCompatibilityTight,                 prefix_+"MuonTM2DCompatibilityTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     mat_d_MuonTMOneStationLoose,                      prefix_+"MuonTMOneStationLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     mat_d_MuonTMOneStationTight,                      prefix_+"MuonTMOneStationTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtLoose",      mat_d_MuonTMLastStationOptimizedLowPtLoose,       prefix_+"MuonTMLastStationOptimizedLowPtLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtTight",      mat_d_MuonTMLastStationOptimizedLowPtTight,       prefix_+"MuonTMLastStationOptimizedLowPtTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonGMTkChiCompatibility",                  mat_d_MuonGMTkChiCompatibility,                   prefix_+"MuonGMTkChiCompatibility["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonGMStaChiCompatibility",                 mat_d_MuonGMStaChiCompatibility,                  prefix_+"MuonGMStaChiCompatibility["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonGMTkKinkTight",                         mat_d_MuonGMTkKinkTight,                          prefix_+"MuonGMTkKinkTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngLoose",                 mat_d_MuonTMLastStationAngLoose,                  prefix_+"MuonTMLastStationAngLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngTight",                 mat_d_MuonTMLastStationAngTight,                  prefix_+"MuonTMLastStationAngTight["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose",mat_d_MuonTMLastStationOptimizedBarrelLowPtLoose, prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight",mat_d_MuonTMLastStationOptimizedBarrelLowPtTight, prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight["+prefix_+"MuonN]/D");
  
  //  mLeptonData->Branch(prefix_+"MuonId", mat_d_MuonId, prefix_+"MuonId["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombChi2", mat_d_MuonCombChi2, prefix_+"MuonCombChi2["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombNdof", mat_d_MuonCombNdof, prefix_+"MuonCombNdof["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombVx",   mat_d_MuonCombVx,   prefix_+"MuonCombVx["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombVy",   mat_d_MuonCombVy,   prefix_+"MuonCombVy["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombVz",   mat_d_MuonCombVz,   prefix_+"MuonCombVz["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombD0",   mat_d_MuonCombD0,   prefix_+"MuonCombD0["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonCombDz",   mat_d_MuonCombDz,   prefix_+"MuonCombDz["+prefix_+"MuonN]/D");

  //Muon tracking information
  mLeptonData->Branch(prefix_+"MuonStandValidHits",   mat_d_MuonStandValidHits,   prefix_+"MuonStandValidHits["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandLostHits",    mat_d_MuonStandLostHits,    prefix_+"MuonStandLostHits["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandPt",          mat_d_MuonStandPt,          prefix_+"MuonStandPt["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandPz",          mat_d_MuonStandPz,          prefix_+"MuonStandPz["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandP",           mat_d_MuonStandP,           prefix_+"MuonStandP["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandEta",         mat_d_MuonStandEta,         prefix_+"MuonStandEta["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandPhi",         mat_d_MuonStandPhi,         prefix_+"MuonStandPhi["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandCharge",      mat_d_MuonStandCharge,      prefix_+"MuonStandCharge["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandChi",         mat_d_MuonStandChi,         prefix_+"MuonStandChi["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonStandQOverPError", mat_d_MuonStandQOverPError, prefix_+"MuonStandQOverPError["+prefix_+"MuonN]/D");

  mLeptonData->Branch(prefix_+"MuonTrkValidHits",   mat_d_MuonTrkValidHits,   prefix_+"MuonTrkValidHits["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",    mat_d_MuonTrkLostHits,    prefix_+"MuonTrkLostHits["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkD0",          mat_d_MuonTrkD0,          prefix_+"MuonTrkD0["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkPt",          mat_d_MuonTrkPt,          prefix_+"MuonTrkPt["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkPz",          mat_d_MuonTrkPz,          prefix_+"MuonTrkPz["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkP",           mat_d_MuonTrkP,           prefix_+"MuonTrkP["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkEta",         mat_d_MuonTrkEta,         prefix_+"MuonTrkEta["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkPhi",         mat_d_MuonTrkPhi,         prefix_+"MuonTrkPhi["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkCharge",      mat_d_MuonTrkCharge,      prefix_+"MuonTrkCharge["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkChi",         mat_d_MuonTrkChi,         prefix_+"MuonTrkChi["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkQOverPError", mat_d_MuonTrkQOverPError, prefix_+"MuonTrkQOverPError["+prefix_+"MuonN]/D"); 
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",      mat_d_MuonTrkOuterZ,      prefix_+"MuonOuterZ["+prefix_+"MuonN]/D");
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",      mat_d_MuonTrkOuterR,      prefix_+"MuonOuterR["+prefix_+"MuonN]/D");

  //Generator level muon information
  if (doMCData_) {
    mLeptonData->Branch(prefix_+"MuonGenPdgId",  mat_d_MuonGenPdgId,  prefix_+"MuonGenPdgId["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenMother", mat_d_MuonGenMother, prefix_+"MuonGenMother["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenPx",     mat_d_MuonGenPx,     prefix_+"MuonGenPx["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenPy",     mat_d_MuonGenPy,     prefix_+"MuonGenPy["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenPz",     mat_d_MuonGenPz,     prefix_+"MuonGenPz["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenPt",     mat_d_MuonGenPt,     prefix_+"MuonGenPt["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenEt",     mat_d_MuonGenEt,     prefix_+"MuonGenEt["+prefix_+"MuonN]/D");
    mLeptonData->Branch(prefix_+"MuonGenE",      mat_d_MuonGenE,      prefix_+"MuonGenE["+prefix_+"MuonN]/D");
    
    //generator leptons (electrons and muons)
    mLeptonData->Branch(prefix_+"ParticleP4",&v_genP4,         prefix_+"genP4");
    mLeptonData->Branch(prefix_+"genN",      &i_length,        prefix_+"genN/I");
    mLeptonData->Branch(prefix_+"genid",      mat_i_genIds,    prefix_+"genIds["+prefix_+"genN]/I");
    mLeptonData->Branch(prefix_+"genMother",  mat_i_genRefs,   prefix_+"genRefs["+prefix_+"genN]/I"); 
    mLeptonData->Branch(prefix_+"genE",       mat_f_genE,      prefix_+"genE["+prefix_+"genN]/F");
    mLeptonData->Branch(prefix_+"genPx",      mat_f_genPx,     prefix_+"genPx["+prefix_+"genN]/F");
    mLeptonData->Branch(prefix_+"genPy",      mat_f_genPy,     prefix_+"genPy["+prefix_+"genN]/F");
    mLeptonData->Branch(prefix_+"genPz",      mat_f_genPz,     prefix_+"genPz["+prefix_+"genN]/F");
    
    //generator leptons status (electrons and muons)
    mLeptonData->Branch(prefix_+"LeptonP4",    &v_genLepP4,         prefix_+"genLepP4");
    mLeptonData->Branch(prefix_+"genLepN",     &mat_i_genLepLength, prefix_+"genLepN/I");
    mLeptonData->Branch(prefix_+"genLepId",     mat_i_genLepIds,    prefix_+"genLepIds["+prefix_+"genLepN]/I");
    mLeptonData->Branch(prefix_+"genLepMother", mat_i_genLepRefs,   prefix_+"genLepRefs["+prefix_+"genLepN]/I");
    mLeptonData->Branch(prefix_+"genLepStatus", mat_i_genLepStatus, prefix_+"genLepStatus["+prefix_+"genLepN]/I");
    mLeptonData->Branch(prefix_+"genLepE",      mat_f_genLepE,      prefix_+"genLepE["+prefix_+"genLepN]/F");
    mLeptonData->Branch(prefix_+"genLepPx",     mat_f_genLepPx,     prefix_+"genLepPx["+prefix_+"genLepN]/F");
    mLeptonData->Branch(prefix_+"genLepPy",     mat_f_genLepPy,     prefix_+"genLepPy["+prefix_+"genLepN]/F");
    mLeptonData->Branch(prefix_+"genLepPz",     mat_f_genLepPz,     prefix_+"genLepPz["+prefix_+"genLepN]/F");

    mLeptonData->Branch(prefix_+"pthat", &d_Pthat, prefix_+"pthat/D");
  }    

  edm::LogInfo("LeptonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

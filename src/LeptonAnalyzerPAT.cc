
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
// $Id: LeptonAnalyzerPAT.cc,v 1.5 2010/05/21 10:13:37 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/LeptonAnalyzerPAT.h"
//#include "DataFormats/MuonReco/interface/MuonSelectors.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

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

  m_ElecVeto      = false;
  m_MuonVeto      = false;
  bool lepton_result = true;

  edm::LogVerbatim("LeptonEvent") << " Start  " << std::endl;

  std::ostringstream dbg;

  // GEN INFO do only if running on MC data
  if(doMCData_) {
    //get pthat of process
    m_Pthat = -999.;
    
    Handle<double> genEventScale;
    iEvent.getByLabel( "genEventScale", genEventScale );
    if ( genEventScale.isValid() ) m_Pthat = *genEventScale;
    
    Handle<reco::GenParticleCollection>  genParticles;
    iEvent.getByLabel(genTag_, genParticles);   
    
    int count=0;
    int lcount=0;
    //int tcount=0;

    if (debug_) sprintf(logmessage,"Status   genpart/%d   PdgId   genE   genPx   genPy   genPz   genMother",genParticles->size());
    if (debug_>1) edm::LogVerbatim("LeptonEvent") << logmessage<< std::endl;

    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      //get status 3 particles
      if (st==3) {
	genIds[count]    = pCand.pdgId();
	genStatus[count] = pCand.status();
	genE[count]      = pCand.energy();
	genPx[count]     = pCand.px();
	genPy[count]     = pCand.py();
	genPz[count]     = pCand.pz();
      
	if (pCand.numberOfMothers() > 0 ) { 
	  const reco::Candidate * mom = pCand.mother();
	  while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	  
	  for( size_t j = 0; j < i; ++ j ) {
	    const Candidate * ref = &((*genParticles)[j]);
	    if (ref == mom) { genRefs[count] = ref->pdgId(); } //return mother's pdgId
	    //if (ref == mom) { genRefs[count] = j; } //point to particle that is reference
	  }  
	} else { genRefs[count]=-999;}

	if (debug_) sprintf(logmessage,"%2d       %4d       %4d       %4.2f     %4.2f    %4.2f    %4.2f     %4d", \
	       genStatus[count],count,genIds[count],genE[count],genPx[count],genPy[count],genPz[count],genRefs[count]);
	if (debug_>1)  edm::LogVerbatim("LeptonEvent") << logmessage<<std::endl;
	++count;
      }
      else { // store also electrons or muons of status 1 
	if ( (abs(pCand.pdgId()) == 11) || (abs(pCand.pdgId()) == 13) ) {
	  
	  genLepIds[lcount]    = pCand.pdgId();
	  genLepStatus[lcount] = pCand.status();
	  genLepE[lcount]      = pCand.energy();
	  genLepPx[lcount]     = pCand.px();
	  genLepPy[lcount]     = pCand.py();
	  genLepPz[lcount]     = pCand.pz();
	  
	  if (pCand.numberOfMothers() > 0 ) { 
	    const reco::Candidate * mom = pCand.mother();
	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
	    
	    for( size_t j = 0; j < i; ++ j ) {
	      const reco::Candidate * ref = &((*genParticles)[j]);
	      if (ref == mom) { genLepRefs[lcount] = ref->pdgId(); }
	      //if (ref == mom) { genLepRefs[lcount] = j; }
	    }  
	  } else { genLepRefs[lcount]=-999;}

	  if (debug_) sprintf(logmessage,"%2d         %4d         %4d         %4.2f       %4.2f    %4.2f    %4.2f     %4d", \
		 genLepStatus[lcount],lcount,genLepIds[lcount],genLepE[lcount],genLepPx[lcount],genLepPy[lcount],genLepPz[lcount],genLepRefs[lcount]);
	  if (debug_>1)  edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
	  ++lcount;
	}
      }
    }
    length = count;
    genLepLength = lcount;
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
  m_ElecN = elecHandle->size();
  if (debug_) std::cout<<m_ElecN<<" Electron results for InputTag " << elecTag_<<std::endl;
  
  if ( m_ElecN > 50 ) m_ElecN = 50;
  int el = 0;
  if (debug_) sprintf(logmessage,"Elec/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",m_ElecN);
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
  for (int i=0;i<m_ElecN;i++){
    const::pat::Electron& theElectron = (*elecHandle)[i];
    if ( (theElectron.pt() > elecMinEt_) && !(theElectron.eta() < elecMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good electrons " << std::endl;
      m_ElecE[el]      = theElectron.energy();
      m_ElecEt[el]     = theElectron.et();
      m_ElecPt[el]     = theElectron.pt();
      m_ElecPx[el]     = theElectron.momentum().X();
      m_ElecPy[el]     = theElectron.momentum().Y();
      m_ElecPz[el]     = theElectron.momentum().Z();
      m_ElecEta[el]    = theElectron.eta();
      m_ElecPhi[el]    = theElectron.phi();
      m_ElecCharge[el] = theElectron.charge();

      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f", \
			  el,m_ElecE[el],m_ElecEt[el],m_ElecPt[el],m_ElecPx[el],m_ElecPy[el],m_ElecPz[el],m_ElecEta[el],m_ElecPhi[el]);
      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;
      
      m_ElecTrkIso[el]  = theElectron.trackIso();
      m_ElecECalIso[el] = theElectron.ecalIso();
      m_ElecHCalIso[el] = theElectron.hcalIso() ;
      m_ElecAllIso[el]  = theElectron.caloIso() ;
      
      m_ElecECalIsoDeposit[el]  = theElectron.ecalIsoDeposit()->candEnergy() ;
      m_ElecHCalIsoDeposit[el]  = theElectron.hcalIsoDeposit()->candEnergy() ;
      
      m_ElecIdLoose[el]    = theElectron.electronID("eidLoose");
      m_ElecIdTight[el]    = theElectron.electronID("eidTight");
      m_ElecIdRobLoose[el] = theElectron.electronID("eidRobustLoose");
      m_ElecIdRobTight[el] = theElectron.electronID("eidRobustTight"); 
      m_ElecIdRobHighE[el] = theElectron.electronID("eidRobustHighEnergy"); 
      
      m_ElecCaloEnergy[el] = theElectron.caloEnergy();
      m_ElecHOverE[el]     = theElectron.hadronicOverEm();
      m_ElecVx[el]         = theElectron.vx();
      m_ElecVy[el]         = theElectron.vy();
      m_ElecVz[el]         = theElectron.vz();
      
      m_ElecD0[el]               = theElectron.gsfTrack()->d0();
      m_ElecDz[el]               = theElectron.gsfTrack()->dz();
      m_ElecChargeMode[el]       = theElectron.gsfTrack()->chargeMode();	
      m_ElecPtTrkMode[el]        = theElectron.gsfTrack()->ptMode();
      m_ElecQOverPErrTrkMode[el] = theElectron.gsfTrack()->qoverpModeError();
      m_ElecCharge[el]           = theElectron.gsfTrack()->charge();
      m_ElecPtTrk[el]            = theElectron.gsfTrack()->pt();
      m_ElecQOverPErrTrk[el]     = theElectron.gsfTrack()->qoverpError();
      m_ElecNormChi2[el]         = theElectron.gsfTrack()->normalizedChi2();
      m_ElecLostHits[el]         = theElectron.gsfTrack()->lost();
      m_ElecValidHits[el]        = theElectron.gsfTrack()->found();
    
      m_ElecEtaTrk[el] = theElectron.trackMomentumAtVtx().Eta();
      m_ElecPhiTrk[el] = theElectron.trackMomentumAtVtx().Phi();
      
      //// Added protection statement, against missing SuperCluster collection in 2_1_X PatLayer1 samples
      //try { 
	m_ElecWidthClusterEta[el] = theElectron.superCluster()->etaWidth();
	m_ElecWidthClusterPhi[el] = theElectron.superCluster()->phiWidth();
      //} catch ( const cms::Exception& e ) {
      //	m_ElecWidthClusterEta[i]=-999.;
      //	m_ElecWidthClusterPhi[i]=-999.;
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
      
      m_ElecPinTrk[el]  = sqrt(theElectron.trackMomentumAtVtx().Mag2());
      m_ElecPoutTrk[el] = sqrt(theElectron.trackMomentumOut().Mag2());
      
      //get associated gen particle information
      if (doMCData_) {
      	const reco::Candidate* candElec = theElectron.genLepton();
      	if ( candElec ) {
      	  m_ElecGenPdgId[el] = candElec->pdgId();
      	  m_ElecGenPx[el]    = candElec->px();
      	  m_ElecGenPy[el]    = candElec->py();
      	  m_ElecGenPz[el]    = candElec->pz();
      	  m_ElecGenPt[el]    = candElec->pt();
      	  m_ElecGenEt[el]    = candElec->et();
      	  m_ElecGenE[el]     = candElec->energy();
        
      	  const reco::Candidate* elecMother = candElec->mother();
      	  if( elecMother ) {
      	    while (elecMother->pdgId() == candElec->pdgId()) elecMother = elecMother->mother();
      	    if ( elecMother ) {
      	      m_ElecGenMother[el] = theElectron.genLepton()->mother()->pdgId();
      	      //if ( theElectron.genLepton()->mother()->pdgId() ==  theElectron.genLepton()->pdgId()) 
      	      //  {
      	      //	m_ElecGenMother[el] = theElectron.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	else {
      	  m_ElecGenPdgId[el]  = -999.;
      	  m_ElecGenMother[el] = -999.;
      	  m_ElecGenPx[el]     = -999.;
      	  m_ElecGenPy[el]     = -999.;
      	  m_ElecGenPz[el]     = -999.;
      	  m_ElecGenPt[el]     = -999.;
      	  m_ElecGenEt[el]     = -999.;
      	  m_ElecGenE[el]      = -999.;
      	}
      }
      double elecIsoReq = (m_ElecTrkIso[el]+m_ElecECalIso[el]+m_ElecHCalIso[el])/m_ElecPt[el];
      if ( elecIsoReq  > elecRelIso_) m_ElecVeto = m_ElecVeto || true;
      if ( m_ElecPt[el] > elecMaxEt_ ) m_ElecVeto = m_ElecVeto || true;
      ++el;
    }
  }//end loop over Electrons
  m_ElecN = el;

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
  m_MuonN= muonHandle->size();
  if (debug_) std::cout<<m_MuonN<<" Muon results for InputTag " << muonTag_<<std::endl;

  if ( m_MuonN > 50 ) m_MuonN = 50;
  int mu = 0;

  if (debug_) sprintf(logmessage,"Muon/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",m_MuonN);
  if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

  for (int i=0;i<m_MuonN;i++){
    const pat::Muon& theMuon = (*muonHandle)[i];
    if ( (theMuon.pt() > muonMinEt_) && !(theMuon.eta() < muonMaxEta_) ) {
      if (debug_) edm::LogVerbatim("LeptonEvent") << " looping over good muons " << std::endl;      
      m_MuonPt[mu]  = theMuon.pt();
      m_MuonE[mu]   = theMuon.energy();
      m_MuonEt[mu]  = theMuon.et();
      m_MuonPx[mu]  = theMuon.momentum().X();
      m_MuonPy[mu]  = theMuon.momentum().Y();
      m_MuonPz[mu]  = theMuon.momentum().Z();
      m_MuonEta[mu] = theMuon.eta();
      m_MuonPhi[mu] = theMuon.phi();
      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f\n", \
			  mu,m_MuonE[mu],m_MuonEt[mu],m_MuonPt[mu],m_MuonPx[mu],m_MuonPy[mu],m_MuonPz[mu],m_MuonEta[mu],m_MuonPhi[mu]);
      if (debug_) edm::LogVerbatim("LeptonEvent")<<logmessage<<std::endl;

      //Muon isolation variables
      m_MuonTrkIso[mu]   = theMuon.trackIso();
      m_MuonCharge[mu]   = theMuon.charge();
      m_MuonECalIso[mu]  = theMuon.ecalIso();
      m_MuonHCalIso[mu]  = theMuon.hcalIso() ;
      m_MuonAllIso[mu]   = theMuon.caloIso() ;

      //m_MuonECalIsoDeposit[mu]  = theMuon.ecalIsoDeposit()->candEnergy() ;
      //m_MuonHCalIsoDeposit[mu]  = theMuon.hcalIsoDeposit()->candEnergy() ;

      m_MuonECalIsoDeposit[mu]  = theMuon.isolationR03().emVetoEt ;
      m_MuonHCalIsoDeposit[mu]  = theMuon.isolationR03().hadVetoEt ;

      //Muon classification variables
      m_MuonIsGlobal[mu]     = theMuon.isGlobalMuon();
      m_MuonIsStandAlone[mu] = theMuon.isStandAloneMuon();
      m_MuonIsTracker[mu]    = theMuon.isTrackerMuon();
      
      m_MuonGlobalMuonPromptTight[mu]          = theMuon.muonID("GlobalMuonPromptTight");
      
      m_MuonAllArbitrated[mu]                  = theMuon.muonID("AllArbitrated");
      m_MuonTrackerMuonArbitrated[mu]          = theMuon.muonID("TrackerMuonArbitrated");
      m_MuonTMLastStationLoose[mu]             = theMuon.muonID("TMLastStationLoose");
      m_MuonTMLastStationTight[mu]             = theMuon.muonID("TMLastStationTight");
      m_MuonTM2DCompatibilityLoose[mu]         = theMuon.muonID("TM2DCompatibilityLoose");
      m_MuonTM2DCompatibilityTight[mu]         = theMuon.muonID("TM2DCompatibilityTight");
      m_MuonTMOneStationLoose[mu]              = theMuon.muonID("TMOneStationLoose");
      m_MuonTMOneStationTight[mu]              = theMuon.muonID("TMOneStationTight");
      m_MuonTMLastStationOptimizedLowPtLoose[mu] = theMuon.muonID("TMLastStationOptimizedLowPtLoose");
      m_MuonTMLastStationOptimizedLowPtTight[mu] = theMuon.muonID("TMLastStationOptimizedLowPtTight");
      m_MuonGMTkChiCompatibility[mu]           = theMuon.muonID("GMTkChiCompatibility");
      m_MuonGMStaChiCompatibility[mu]          = theMuon.muonID("GMStaChiCompatibility");
      m_MuonGMTkKinkTight[mu]                  = theMuon.muonID("GMTkKinkTight");
      m_MuonTMLastStationAngLoose[mu]          = theMuon.muonID("TMLastStationAngLoose");
      m_MuonTMLastStationAngTight[mu]          = theMuon.muonID("TMLastStationAngTight");
      m_MuonTMOneStationLoose[mu]              = theMuon.muonID("TMOneStationLoose");
      m_MuonTMOneStationTight[mu]              = theMuon.muonID("TMOneStationTight");
      m_MuonTMLastStationOptimizedBarrelLowPtLoose[mu] = theMuon.muonID("TMLastStationOptimizedBarrelLowPtLoose");
      m_MuonTMLastStationOptimizedBarrelLowPtTight[mu] = theMuon.muonID("TMLastStationOptimizedBarrelLowPtTight");
      
    
      //Muon Vertex information
      // Vertex info is stored only for GlobalMuons (combined muons)
      if(theMuon.isGlobalMuon() && theMuon.combinedMuon().isNonnull()){ 

	m_MuonCombChi2[mu] = theMuon.combinedMuon()->chi2();
	m_MuonCombNdof[mu] = theMuon.combinedMuon()->ndof();

	m_MuonCombVx[mu] = theMuon.combinedMuon()->vx();
	m_MuonCombVy[mu] = theMuon.combinedMuon()->vy();
	m_MuonCombVz[mu] = theMuon.combinedMuon()->vz();
	m_MuonCombD0[mu] = theMuon.combinedMuon()->d0();
	m_MuonCombDz[mu] = theMuon.combinedMuon()->dz();

      } else {
	m_MuonCombVx[mu] = 999.;
	m_MuonCombVy[mu] = 999.;
	m_MuonCombVz[mu] = 999.;
	m_MuonCombD0[mu] = 999.;
	m_MuonCombDz[mu] = 999.;
      }

      //Standalone muon information
      if(theMuon.isStandAloneMuon() && theMuon.standAloneMuon().isNonnull()){
	m_MuonStandValidHits[mu]   = theMuon.standAloneMuon()->found();
	m_MuonStandLostHits[mu]    = theMuon.standAloneMuon()->lost();
	m_MuonStandPt[mu]          = theMuon.standAloneMuon()->pt();
	m_MuonStandPz[mu]          = theMuon.standAloneMuon()->pz();
	m_MuonStandP[mu]           = theMuon.standAloneMuon()->p();
	m_MuonStandEta[mu]         = theMuon.standAloneMuon()->eta();
	m_MuonStandPhi[mu]         = theMuon.standAloneMuon()->phi();
	m_MuonStandChi[mu]         = theMuon.standAloneMuon()->chi2();
	m_MuonStandCharge[mu]      = theMuon.standAloneMuon()->charge();
	m_MuonStandQOverPError[mu] = theMuon.standAloneMuon()->qoverpError();
      } 
      else{
	m_MuonStandValidHits[mu]   = 999.;
	m_MuonStandLostHits[mu]    = 999.;
	m_MuonStandPt[mu]          = 999.;
	m_MuonStandPz[mu]          = 999.;
	m_MuonStandP[mu]           = 999.;
	m_MuonStandEta[mu]         = 999.;
	m_MuonStandPhi[mu]         = 999.;
	m_MuonStandChi[mu]         = 999.;
	m_MuonStandCharge[mu]      = 999.;
	m_MuonStandQOverPError[mu] = 999.;
      }

      //Muon tracking information
      if(theMuon.isTrackerMuon() && theMuon.track().isNonnull()){
	m_MuonTrkChiNorm[mu]     = theMuon.track()->normalizedChi2();
	m_MuonTrkValidHits[mu]   = theMuon.track()->found();
	m_MuonTrkLostHits[mu]    = theMuon.track()->lost();
	m_MuonTrkD0[mu]          = theMuon.track()->d0();
	m_MuonTrkPt[mu]          = theMuon.track()->pt();
	m_MuonTrkPz[mu]          = theMuon.track()->pz();
	m_MuonTrkP[mu]           = theMuon.track()->p();
	m_MuonTrkEta[mu]         = theMuon.track()->eta();
	m_MuonTrkPhi[mu]         = theMuon.track()->phi();
	m_MuonTrkChi[mu]         = theMuon.track()->chi2();
	m_MuonTrkCharge[mu]      = theMuon.track()->charge();
	m_MuonTrkQOverPError[mu] = theMuon.track()->qoverpError();
	//  m_MuonTrkOuterZ[mu]=theMuon.track()->outerZ();
	//  m_MuonTrkOuterR[mu]=theMuon.track()->outerRadius();

      }
      else{
	m_MuonTrkChiNorm[mu]    = 999.;
	m_MuonTrkValidHits[mu]  = 999.;
	m_MuonTrkLostHits[mu]   = 999.;
	m_MuonTrkPt[mu]         = 999.;
	m_MuonTrkPz[mu]         = 999.;
	m_MuonTrkP[mu]          = 999.;
	m_MuonTrkEta[mu]        = 999.;
	m_MuonTrkPhi[mu]        = 999.;
	m_MuonTrkChi[mu]        = 999.;
	m_MuonTrkCharge[mu]     = 999.;
	m_MuonTrkQOverPError[mu]= 999.;
	m_MuonTrkOuterZ[mu]     = 999.;
	m_MuonTrkOuterR[mu]     = 999.;
      }

      //Muon gen particle association variables
      if (doMCData_) {
      	const reco::Candidate* candMuon = theMuon.genLepton();
      	if ( candMuon ) {
      	  m_MuonGenPdgId[mu] = candMuon->pdgId();
      	  m_MuonGenPx[mu]    = candMuon->px();
      	  m_MuonGenPy[mu]    = candMuon->py();
      	  m_MuonGenPz[mu]    = candMuon->pz();
      	  m_MuonGenPt[mu]    = candMuon->pt();
      	  m_MuonGenEt[mu]    = candMuon->et();
      	  m_MuonGenE[mu]     = candMuon->energy();
      	  
      	  const reco::Candidate* muonMother = candMuon->mother();
      	  if( muonMother ) {
      	    while (muonMother->pdgId() == candMuon->pdgId()) muonMother = muonMother->mother();
      	    if ( muonMother ) {
      	      m_MuonGenMother[mu] = theMuon.genLepton()->mother()->pdgId();
      	      //if ( theMuon.genLepton()->mother()->pdgId() ==  theMuon.genLepton()->pdgId()) 
      	      //  {
      	      //	m_MuonGenMother[mu] = theMuon.genLepton()->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	
      	else{
      	  m_MuonGenPdgId[mu]  = -999.;
      	  m_MuonGenMother[mu] = -999.;
      	  m_MuonGenPx[mu]     = -999.;
      	  m_MuonGenPy[mu]     = -999.;
      	  m_MuonGenPz[mu]     = -999.;
      	  m_MuonGenPt[mu]     = -999.;
      	  m_MuonGenEt[mu]     = -999.;
      	  m_MuonGenE[mu]      = -999.;
      	}
      }
      double muonIsoReq = (m_MuonTrkIso[mu]+m_MuonECalIso[mu]+m_MuonHCalIso[mu])/m_MuonPt[mu];
      if ( muonIsoReq  > muonRelIso_) m_MuonVeto = m_MuonVeto || true;
      if ( m_MuonPt[mu] > muonMaxEt_)  m_MuonVeto = m_MuonVeto || true;
      ++mu;
    }
  }// end loop over muons
  m_MuonN = mu;
  // return true when none of the events have leptons above threshold
  lepton_result = !(m_ElecVeto || m_MuonVeto);
  //mLeptonData->Fill();
  return lepton_result;
}

//________________________________________________________________________________________
void LeptonAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  // Add the branches
  //add electrons
  mLeptonData->Branch(prefix_+"ElecVeto", &m_ElecVeto, prefix_+"ElecVeto/bool");
  //General electron information
  mLeptonData->Branch(prefix_+"ElecN",     &m_ElecN,      prefix_+"ElecN/int");  
  mLeptonData->Branch(prefix_+"ElecE",      m_ElecE,      prefix_+"ElecE["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecEt",     m_ElecEt,     prefix_+"ElecEt["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPt",     m_ElecPt,     prefix_+"ElecPt["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPx",     m_ElecPx,     prefix_+"ElecPx["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPy",     m_ElecPy,     prefix_+"ElecPy["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPz",     m_ElecPz,     prefix_+"ElecPz["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecEta",    m_ElecEta,    prefix_+"ElecEta["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPhi",    m_ElecPhi,    prefix_+"ElecPhi["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecCharge", m_ElecCharge, prefix_+"ElecCharge["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecHOverE", m_ElecHOverE, prefix_+"ElecHOverE["+prefix_+"ElecN]/double");

  //Isolation and tracking variables
  mLeptonData->Branch(prefix_+"ElecTrkIso",     m_ElecTrkIso,   prefix_+"ElecTrkIso["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecECalIso",    m_ElecECalIso,  prefix_+"ElecECalIso["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecHCalIso",    m_ElecHCalIso,  prefix_+"ElecHCalIso["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecAllIso",     m_ElecAllIso,   prefix_+"ElecAllIso["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecTrkChiNorm", m_ElecNormChi2, prefix_+"ElecTrkChiNorm["+prefix_+"ElecN]/double");
  //mLeptonData->Branch("NIsoelec",      &m_NIsoelec,     "NIsoelec/int");  

  mLeptonData->Branch(prefix_+"ElecECalIsoDeposit", m_ElecECalIsoDeposit, prefix_+"ElecECalIsoDeposit["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecHCalIsoDeposit", m_ElecHCalIsoDeposit, prefix_+"ElecHCalIsoDeposit["+prefix_+"ElecN]/double");

  //Electron identification values
  mLeptonData->Branch(prefix_+"ElecIdLoose",    m_ElecIdLoose,    prefix_+"ElecIdLoose["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecIdTight",    m_ElecIdTight,    prefix_+"ElecIdTight["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecIdRobLoose", m_ElecIdRobLoose, prefix_+"ElecIdRobLoose["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecIdRobTight", m_ElecIdRobTight, prefix_+"ElecIdRobTight["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecIdRobHighE", m_ElecIdRobHighE, prefix_+"ElecIdRobHighE["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecChargeMode", m_ElecChargeMode, prefix_+"ElecChargeMode["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPtMode",     m_ElecPtTrkMode,  prefix_+"ElecPtMode["+prefix_+"ElecN]/double");


  //Electron vertex information
  mLeptonData->Branch(prefix_+"ElecVx",     m_ElecVx,     prefix_+"ElecVx["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecVy",     m_ElecVy,     prefix_+"ElecVy["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecVz",     m_ElecVz,     prefix_+"ElecVz["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecD0",     m_ElecD0,     prefix_+"ElecD0["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecDz",     m_ElecDz,     prefix_+"ElecDz["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPtTrk",  m_ElecPtTrk,  prefix_+"ElecPtTrk["+prefix_+"ElecN]/double");

  //Additonal electron detector information
  //Electron tracking information
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrkMode", m_ElecQOverPErrTrkMode, prefix_+"ElecQOverPErrTrkMode["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecCaloEnergy",       m_ElecCaloEnergy,       prefix_+"ElecCaloEnergy["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecQOverPErrTrk",     m_ElecQOverPErrTrk,     prefix_+"ElecQOverPErrTrk["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPinTrk",           m_ElecPinTrk,           prefix_+"ElecPinTrk["+prefix_+"ElecN]/double");
  mLeptonData->Branch(prefix_+"ElecPoutTrk",          m_ElecPoutTrk,          prefix_+"ElecPoutTrk["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecLostHits",         m_ElecLostHits,         prefix_+"ElecLostHits["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecValidHits",        m_ElecValidHits,        prefix_+"ElecValidHits["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecNCluster",         m_ElecNCluster,         prefix_+"ElecNCluster["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecEtaTrk",           m_ElecEtaTrk,           prefix_+"ElecEtaTrk["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecPhiTrk",           m_ElecPhiTrk,           prefix_+"ElecPhiTrk["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecWidthClusterEta",  m_ElecWidthClusterEta,  prefix_+"ElecWidthClusterEta["+prefix_+"ElecN]/double"); 
  mLeptonData->Branch(prefix_+"ElecWidthClusterPhi",  m_ElecWidthClusterPhi,  prefix_+"ElecWidthClusterPhi["+prefix_+"ElecN]/double"); 

  if (doMCData_) {
    //Generator level information stored in the electron object
    mLeptonData->Branch(prefix_+"ElecGenPdgId",  m_ElecGenPdgId,  prefix_+"ElecGenPdgId["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenMother", m_ElecGenMother, prefix_+"ElecGenMother["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenPx",     m_ElecGenPx,     prefix_+"ElecGenPx["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenPy",     m_ElecGenPy,     prefix_+"ElecGenPy["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenPz",     m_ElecGenPz,     prefix_+"ElecGenPz["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenPt",     m_ElecGenPt,     prefix_+"ElecGenPt["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenEt",     m_ElecGenEt,     prefix_+"ElecGenEt["+prefix_+"ElecN]/double");
    mLeptonData->Branch(prefix_+"ElecGenE",      m_ElecGenE,      prefix_+"ElecGenE["+prefix_+"ElecN]/double");
  }

  //add muons
  mLeptonData->Branch(prefix_+"MuonVeto", &m_MuonVeto, prefix_+"MuonVeto/bool");
  //General kinematic variables related to muons
  mLeptonData->Branch(prefix_+"MuonN",         &m_MuonN,          prefix_+"MuonN/int");  
  mLeptonData->Branch(prefix_+"MuonE",          m_MuonE,          prefix_+"MuonE["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonEt",         m_MuonEt,         prefix_+"MuonEt["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonPt",         m_MuonPt,         prefix_+"MuonPt["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonPx",         m_MuonPx,         prefix_+"MuonPx["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonPy",         m_MuonPy,         prefix_+"MuonPy["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonPz",         m_MuonPz,         prefix_+"MuonPz["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonEta",        m_MuonEta,        prefix_+"MuonEta["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonPhi",        m_MuonPhi,        prefix_+"MuonPhi["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCharge",     m_MuonCharge,     prefix_+"MuonCharge["+prefix_+"MuonN]/double");

  //Muon isolation variables
  //mLeptonData->Branch("NIsomuon",      &m_NIsomuon,       "NIsomuon/int");  
  mLeptonData->Branch(prefix_+"MuonTrkIso",     m_MuonTrkIso,     prefix_+"MuonTrkIso["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonECalIso",    m_MuonECalIso,    prefix_+"MuonECalIso["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonHCalIso",    m_MuonHCalIso,    prefix_+"MuonHCalIso["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonAllIso",     m_MuonAllIso,     prefix_+"MuonAllIso["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkChiNorm", m_MuonTrkChiNorm, prefix_+"MuonTrkChiNorm["+prefix_+"MuonN]/double");

  mLeptonData->Branch(prefix_+"MuonECalIsoDeposit", m_MuonECalIsoDeposit, prefix_+"MuonECalIsoDeposit["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonHCalIsoDeposit", m_MuonHCalIsoDeposit, prefix_+"MuonHCalIsoDeposit["+prefix_+"MuonN]/double");

  //Muon calorimeter type
  mLeptonData->Branch(prefix_+"MuonIsGlobal",                              m_MuonIsGlobal,                               prefix_+"MuonIsGlobal["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonIsStandAlone",                          m_MuonIsStandAlone,                           prefix_+"MuonIsStandAlone["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonIsTracker",                             m_MuonIsTracker,                              prefix_+"MuonIsTracker["+prefix_+"MuonN]/double");
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonGlobalMuonPromptTight",                 m_MuonGlobalMuonPromptTight,                  prefix_+"MuonGlobalMuonPromptTight["+prefix_+"MuonN]/double");
  			                                                                                                  
  mLeptonData->Branch(prefix_+"MuonAllArbitrated",                         m_MuonAllArbitrated,                          prefix_+"MuonAllArbitrated["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrackerMuonArbitrated",                 m_MuonTrackerMuonArbitrated,                  prefix_+"MuonTrackerMuonArbitrated["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationLoose",                    m_MuonTMLastStationLoose,                     prefix_+"MuonTMLastStationLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationTight",                    m_MuonTMLastStationTight,                     prefix_+"MuonTMLastStationTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityLoose",                m_MuonTM2DCompatibilityLoose,                 prefix_+"MuonTM2DCompatibilityLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTM2DCompatibilityTight",                m_MuonTM2DCompatibilityTight,                 prefix_+"MuonTM2DCompatibilityTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     m_MuonTMOneStationLoose,                      prefix_+"MuonTMOneStationLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     m_MuonTMOneStationTight,                      prefix_+"MuonTMOneStationTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtLoose",      m_MuonTMLastStationOptimizedLowPtLoose,       prefix_+"MuonTMLastStationOptimizedLowPtLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedLowPtTight",      m_MuonTMLastStationOptimizedLowPtTight,       prefix_+"MuonTMLastStationOptimizedLowPtTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonGMTkChiCompatibility",                  m_MuonGMTkChiCompatibility,                   prefix_+"MuonGMTkChiCompatibility["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonGMStaChiCompatibility",                 m_MuonGMStaChiCompatibility,                  prefix_+"MuonGMStaChiCompatibility["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonGMTkKinkTight",                         m_MuonGMTkKinkTight,                          prefix_+"MuonGMTkKinkTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngLoose",                 m_MuonTMLastStationAngLoose,                  prefix_+"MuonTMLastStationAngLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationAngTight",                 m_MuonTMLastStationAngTight,                  prefix_+"MuonTMLastStationAngTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMOneStationLoose",                     m_MuonTMOneStationLoose,                      prefix_+"MuonTMOneStationLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMOneStationTight",                     m_MuonTMOneStationTight,                      prefix_+"MuonTMOneStationTight["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose",m_MuonTMLastStationOptimizedBarrelLowPtLoose, prefix_+"MuonTMLastStationOptimizedBarrelLowPtLoose["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight",m_MuonTMLastStationOptimizedBarrelLowPtTight, prefix_+"MuonTMLastStationOptimizedBarrelLowPtTight["+prefix_+"MuonN]/double");
  
  //  mLeptonData->Branch(prefix_+"MuonId", m_MuonId, prefix_+"MuonId["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombChi2", m_MuonCombChi2, prefix_+"MuonCombChi2["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombNdof", m_MuonCombNdof, prefix_+"MuonCombNdof["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombVx",   m_MuonCombVx,   prefix_+"MuonCombVx["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombVy",   m_MuonCombVy,   prefix_+"MuonCombVy["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombVz",   m_MuonCombVz,   prefix_+"MuonCombVz["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombD0",   m_MuonCombD0,   prefix_+"MuonCombD0["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonCombDz",   m_MuonCombDz,   prefix_+"MuonCombDz["+prefix_+"MuonN]/double");

  //Muon tracking information
  mLeptonData->Branch(prefix_+"MuonStandValidHits",   m_MuonStandValidHits,   prefix_+"MuonStandValidHits["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandLostHits",    m_MuonStandLostHits,    prefix_+"MuonStandLostHits["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandPt",          m_MuonStandPt,          prefix_+"MuonStandPt["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandPz",          m_MuonStandPz,          prefix_+"MuonStandPz["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandP",           m_MuonStandP,           prefix_+"MuonStandP["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandEta",         m_MuonStandEta,         prefix_+"MuonStandEta["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandPhi",         m_MuonStandPhi,         prefix_+"MuonStandPhi["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandCharge",      m_MuonStandCharge,      prefix_+"MuonStandCharge["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandChi",         m_MuonStandChi,         prefix_+"MuonStandChi["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonStandQOverPError", m_MuonStandQOverPError, prefix_+"MuonStandQOverPError["+prefix_+"MuonN]/double");

  mLeptonData->Branch(prefix_+"MuonTrkValidHits",   m_MuonTrkValidHits,   prefix_+"MuonTrkValidHits["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkLostHits",    m_MuonTrkLostHits,    prefix_+"MuonTrkLostHits["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkD0",          m_MuonTrkD0,          prefix_+"MuonTrkD0["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkPt",          m_MuonTrkPt,          prefix_+"MuonTrkPt["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkPz",          m_MuonTrkPz,          prefix_+"MuonTrkPz["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkP",           m_MuonTrkP,           prefix_+"MuonTrkP["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkEta",         m_MuonTrkEta,         prefix_+"MuonTrkEta["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkPhi",         m_MuonTrkPhi,         prefix_+"MuonTrkPhi["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkCharge",      m_MuonTrkCharge,      prefix_+"MuonTrkCharge["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkChi",         m_MuonTrkChi,         prefix_+"MuonTrkChi["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkQOverPError", m_MuonTrkQOverPError, prefix_+"MuonTrkQOverPError["+prefix_+"MuonN]/double"); 
  mLeptonData->Branch(prefix_+"MuonTrkOuterZ",      m_MuonTrkOuterZ,      prefix_+"MuonOuterZ["+prefix_+"MuonN]/double");
  mLeptonData->Branch(prefix_+"MuonTrkOuterR",      m_MuonTrkOuterR,      prefix_+"MuonOuterR["+prefix_+"MuonN]/double");

  //Generator level muon information
  if (doMCData_) {
    mLeptonData->Branch(prefix_+"MuonGenPdgId",  m_MuonGenPdgId,  prefix_+"MuonGenPdgId["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenMother", m_MuonGenMother, prefix_+"MuonGenMother["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenPx",     m_MuonGenPx,     prefix_+"MuonGenPx["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenPy",     m_MuonGenPy,     prefix_+"MuonGenPy["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenPz",     m_MuonGenPz,     prefix_+"MuonGenPz["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenPt",     m_MuonGenPt,     prefix_+"MuonGenPt["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenEt",     m_MuonGenEt,     prefix_+"MuonGenEt["+prefix_+"MuonN]/double");
    mLeptonData->Branch(prefix_+"MuonGenE",      m_MuonGenE,      prefix_+"MuonGenE["+prefix_+"MuonN]/double");
    
    //generator leptons (electrons and muons)
    mLeptonData->Branch(prefix_+"genN",     &length,    prefix_+"genN/int");
    mLeptonData->Branch(prefix_+"genid",     genIds,    prefix_+"genIds["+prefix_+"genN]/int");
    mLeptonData->Branch(prefix_+"genMother", genRefs,   prefix_+"genRefs["+prefix_+"genN]/int"); 
    mLeptonData->Branch(prefix_+"genE",      genE,      prefix_+"genE["+prefix_+"genN]/float");
    mLeptonData->Branch(prefix_+"genPx",     genPx,     prefix_+"genPx["+prefix_+"genN]/float");
    mLeptonData->Branch(prefix_+"genPy",     genPy,     prefix_+"genPy["+prefix_+"genN]/float");
    mLeptonData->Branch(prefix_+"genPz",     genPz,     prefix_+"genPz["+prefix_+"genN]/float");
    
    //generator leptons status (electrons and muons)
    mLeptonData->Branch(prefix_+"genLepN",     &genLepLength, prefix_+"genLepN/int");
    mLeptonData->Branch(prefix_+"genLepId",     genLepIds,    prefix_+"genLepIds["+prefix_+"genLepN]/int");
    mLeptonData->Branch(prefix_+"genLepMother", genLepRefs,   prefix_+"genLepRefs["+prefix_+"genLepN]/int");
    mLeptonData->Branch(prefix_+"genLepStatus", genLepStatus, prefix_+"genLepStatus["+prefix_+"genLepN]/int");
    mLeptonData->Branch(prefix_+"genLepE",      genLepE,      prefix_+"genLepE["+prefix_+"genLepN]/float");
    mLeptonData->Branch(prefix_+"genLepPx",     genLepPx,     prefix_+"genLepPx["+prefix_+"genLepN]/float");
    mLeptonData->Branch(prefix_+"genLepPy",     genLepPy,     prefix_+"genLepPy["+prefix_+"genLepN]/float");
    mLeptonData->Branch(prefix_+"genLepPz",     genLepPz,     prefix_+"genLepPz["+prefix_+"genLepN]/float");

    mLeptonData->Branch(prefix_+"pthat", &m_Pthat, prefix_+"pthat/double");
  }    

  edm::LogInfo("LeptonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(LeptonAnalyzerPAT);

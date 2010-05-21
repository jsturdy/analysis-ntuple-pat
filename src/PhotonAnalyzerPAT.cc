
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      PhotonAnalyzerPAT
// 
/**\class PhotonAnalyzerPAT PhotonAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/PhotonAnalyzerPAT.cc

Description: Variable collector/ntupler for SUSY search with Jets + MET

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: PhotonAnalyzerPAT.cc,v 1.3 2010/05/20 19:40:14 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/PhotonAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
PhotonAnalyzerPAT::PhotonAnalyzerPAT(const edm::ParameterSet& photonParams, TTree* tmpAllData)
{ 

  mPhotonData = tmpAllData;

  // Read in parameters from the config file
  photMaxEta_ = photonParams.getUntrackedParameter<double>("photMaxEta",3.);
  photMaxEt_  = photonParams.getUntrackedParameter<double>("photMaxEt",999);
  photMinEt_  = photonParams.getUntrackedParameter<double>("photMinEt",5);
  photRelIso_ = photonParams.getUntrackedParameter<double>("photRelIso",0.5);

  doMCData_   = photonParams.getUntrackedParameter<bool>("doMCPhots",false);
  if (doMCData_) 
    genTag_  = photonParams.getUntrackedParameter<edm::InputTag>("genPhotTag");
  debug_   = photonParams.getUntrackedParameter<int>("debugPhots",0);
  prefix_  = photonParams.getUntrackedParameter<std::string>("prefixPhots","");
 
  // get the data tags
  photTag_ = photonParams.getUntrackedParameter<edm::InputTag>("photTag");

  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree();
}


//________________________________________________________________________________________
PhotonAnalyzerPAT::~PhotonAnalyzerPAT() {
  delete mPhotonData;
}


//________________________________________________________________________________________
// Method called to for each event
bool PhotonAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  using namespace reco;
  using namespace edm;

  //bool preselection = false;
  bool photon_result = true;
  edm::LogVerbatim("PhotonEvent") << " Start  " << std::endl;

  std::ostringstream dbg;
  
  // GEN INFO do only if running on MC data
  if (doMCData_) {
    
    Handle<reco::GenParticleCollection>  genParticles;
    iEvent.getByLabel(genTag_, genParticles);   
    
    int pcount=0;
    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      if (st==3) {
  	int status = 3;
      } else { // store photons of status 1 
  	if ( (abs(pCand.pdgId()) == 22) ) {
  	  
  	  genPhotIds[pcount]    = pCand.pdgId();
  	  genPhotStatus[pcount] = pCand.status();
  	  genPhotE[pcount]      = pCand.energy();
  	  genPhotPx[pcount]     = pCand.px();
  	  genPhotPy[pcount]     = pCand.py();
  	  genPhotPz[pcount]     = pCand.pz();
  	  
  	  if (pCand.numberOfMothers() > 0 ) { 
  	    const reco::Candidate * mom = pCand.mother();
  	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
  	    
  	    for( size_t j = 0; j < i; ++ j ) {
  	      const Candidate * ref = &((*genParticles)[j]);
  	      if (ref == mom) { genPhotRefs[pcount] = ref->pdgId(); }
  	      //if (ref == mom) { genPhotRefs[pcount] = j; }
  	    }  
  	  } else { genPhotRefs[pcount]=-999;}
  	  pcount++;
  	}
      }
    }
    genPhotLength = pcount;
  }
  

  /*
   *Get the information on all the photons
   *
   */

  // get the photons
  edm::Handle< std::vector<pat::Photon> > photHandle;
  iEvent.getByLabel(photTag_, photHandle);
  if ( !photHandle.isValid() ) {
    edm::LogWarning("PhotonEvent") << "No Photon results for InputTag " << photTag_;
    return false;
  }

  
  edm::LogVerbatim("PhotonEvent") << " start reading in photons " << std::endl;
  // Add the photons
  m_PhotN = photHandle->size();
  int ph = 0;
  if ( m_PhotN > 50 ) {
    m_PhotN = 50;
    if (debug_) sprintf(logmessage,"Photon/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",m_PhotN);
    if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
  }
  for (int i=0;i<m_PhotN;i++) {
    if ( ((*photHandle)[i].pt() > photMinEt_) && !((*photHandle)[i].eta() > photMaxEta_) ) {
      if (debug_) edm::LogVerbatim("PhotonEvent") << " looping over good photons " << std::endl;      
      m_PhotE[ph]   = (*photHandle)[i].energy();
      m_PhotEt[ph]  = (*photHandle)[i].et();
      m_PhotPt[ph]  = (*photHandle)[i].pt();
      m_PhotPx[ph]  = (*photHandle)[i].momentum().X();
      m_PhotPy[ph]  = (*photHandle)[i].momentum().Y();
      m_PhotPz[ph]  = (*photHandle)[i].momentum().Z();
      m_PhotEta[ph] = (*photHandle)[i].eta();
      m_PhotPhi[ph] = (*photHandle)[i].phi();

      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f", \
			  ph,m_PhotE[ph],m_PhotEt[ph],m_PhotPt[ph],m_PhotPx[ph],m_PhotPy[ph],m_PhotPz[ph],m_PhotEta[ph],m_PhotPhi[ph]);
      if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
    
      m_PhotTrkIso[ph]  = (*photHandle)[i].trackIso();
      m_PhotECalIso[ph] = (*photHandle)[i].ecalIso();
      m_PhotHCalIso[ph] = (*photHandle)[i].hcalIso();
      m_PhotAllIso[ph]  = (*photHandle)[i].caloIso();

      //m_PhotLooseEM[ph] = (*photHandle)[i].photonID("PhotonCutBasedIDLooseEM");
      m_PhotLoosePhoton[ph] = (*photHandle)[i].photonID("PhotonCutBasedIDLoose");
      m_PhotTightPhoton[ph] = (*photHandle)[i].photonID("PhotonCutBasedIDTight");
      
      // PhotGenon info
      if (doMCData_) {
      	//reco::Particle* part = const_cast<reco::Particle*>( (*photHandle)[i].genPhoton() );
      	const reco::Candidate* candPhot = (*photHandle)[i].genPhoton();

      	if (debug_) sprintf(logmessage,"      PhotGenon      E     Et    Pt    Px    Py    Pz    PdgId    Mother\n");
	if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

      	if ( candPhot ) {
      	  m_PhotGenPdgId[ph] = candPhot->pdgId();
      	  m_PhotGenPx[ph]    = candPhot->px();
      	  m_PhotGenPy[ph]    = candPhot->py();
      	  m_PhotGenPz[ph]    = candPhot->pz();
      	  m_PhotGenPt[ph]    = candPhot->pt();
      	  m_PhotGenEt[ph]    = candPhot->et();
      	  m_PhotGenE[ph]     = candPhot->energy();
      	  const reco::Candidate* photMother = candPhot->mother();
      	  if ( photMother ) {
      	    while (photMother->pdgId() == candPhot->pdgId()) photMother = photMother->mother();
      	    if ( photMother ) {
      	      m_PhotGenMother[ph] = photMother->pdgId();
      	      //if ( cand->mother()->pdgId() ==  cand->pdgId()) 
      	      //  {
      	      //	m_PhotGenMother[ph] = cand->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	else {
      	  m_PhotGenPdgId[ph]  = -999;
      	  m_PhotGenMother[ph] = -999;
      	  m_PhotGenPx[ph]     = -999;
      	  m_PhotGenPy[ph]     = -999;
      	  m_PhotGenPz[ph]     = -999;
      	  m_PhotGenPt[ph]     = -999;
      	  m_PhotGenEt[ph]     = -999;
      	  m_PhotGenE[ph]      = -999;
      	}

      	if (debug_) sprintf(logmessage,"      %6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f\n", \
      	       ph,m_PhotGenE[ph],m_PhotGenEt[ph],m_PhotGenPt[ph],m_PhotGenPx[ph],m_PhotGenPy[ph],m_PhotGenPz[ph],m_PhotGenPdgId[ph],m_PhotGenMother[ph]);
	if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

      }
      ++ph;
    }
  } // loop over pat::Photons
  m_PhotN = ph;
  
  
  // Fill the tree only if all preselection conditions are met
  return photon_result;
}

//________________________________________________________________________________________
void PhotonAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";
  
  // Add the branches

  //add photons
  mPhotonData->Branch(prefix_+"PhotN",   &m_PhotN,   prefix_+"PhotN/int");  
  mPhotonData->Branch(prefix_+"PhotE",    m_PhotE,   prefix_+"PhotE["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotEt",   m_PhotEt,  prefix_+"PhotEt["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotPt",   m_PhotPt,  prefix_+"PhotPt["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotPx",   m_PhotPx,  prefix_+"PhotPx["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotPy",   m_PhotPy,  prefix_+"PhotPy["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotPz",   m_PhotPz,  prefix_+"PhotPz["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotEta",  m_PhotEta, prefix_+"PhotEta["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotPhi",  m_PhotPhi, prefix_+"PhotPhi["+prefix_+"PhotN]/double");

  mPhotonData->Branch(prefix_+"PhotTrkIso",  m_PhotTrkIso,  prefix_+"PhotTrkIso["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotECalIso", m_PhotECalIso, prefix_+"PhotECalIso["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotHCalIso", m_PhotHCalIso, prefix_+"PhotHCalIso["+prefix_+"PhotN]/double");
  mPhotonData->Branch(prefix_+"PhotAllIso",  m_PhotAllIso,  prefix_+"PhotAllIso["+prefix_+"PhotN]/double");

  //mPhotonData->Branch(prefix_+"Phot_isccPhotAssoc", m_ccPhotAssoc,     prefix_+"ccPhotAssoc["+prefix_+"PhotN]/bool");
  //mPhotonData->Branch(prefix_+"PhotLooseEM",        m_PhotLooseEM,     prefix_+"PhotLooseEM["+prefix_+"PhotN]/bool");
  mPhotonData->Branch(prefix_+"PhotLoosePhoton",    m_PhotLoosePhoton, prefix_+"PhotLoosePhoton["+prefix_+"PhotN]/bool");
  mPhotonData->Branch(prefix_+"PhotTightPhoton",    m_PhotTightPhoton, prefix_+"PhotTightPhoton["+prefix_+"PhotN]/bool");

  if (doMCData_) {
    //from reco::candidate
    mPhotonData->Branch(prefix_+"PhotGenPdgId",  m_PhotGenPdgId,  prefix_+"PhotGenPdgId["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenMother", m_PhotGenMother, prefix_+"PhotGenMother["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenPx",     m_PhotGenPx,     prefix_+"PhotGenPx["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenPy",     m_PhotGenPy,     prefix_+"PhotGenPy["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenPz",     m_PhotGenPz,     prefix_+"PhotGenPz["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenPt",     m_PhotGenPt,     prefix_+"PhotGenPt["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenEt",     m_PhotGenEt,     prefix_+"PhotGenEt["+prefix_+"PhotN]/double");
    mPhotonData->Branch(prefix_+"PhotGenE",      m_PhotGenE,      prefix_+"PhotGenE["+prefix_+"PhotN]/double");
    //from genParticles
    mPhotonData->Branch(prefix_+"genPhotN",     &genPhotLength, prefix_+"genPhotN/int");
    mPhotonData->Branch(prefix_+"genPhotId",     genPhotIds,    prefix_+"genPhotIds["+prefix_+"genPhotN]/int");
    mPhotonData->Branch(prefix_+"genPhotMother", genPhotRefs,   prefix_+"genPhotRefs["+prefix_+"genPhotN]/int");
    mPhotonData->Branch(prefix_+"genPhotStatus", genPhotStatus, prefix_+"genPhotStatus["+prefix_+"genPhotN]/int");
    mPhotonData->Branch(prefix_+"genPhotE",      genPhotE,      prefix_+"genPhotE["+prefix_+"genPhotN]/float");
    mPhotonData->Branch(prefix_+"genPhotPx",     genPhotPx,     prefix_+"genPhotPx["+prefix_+"genPhotN]/float");
    mPhotonData->Branch(prefix_+"genPhotPy",     genPhotPy,     prefix_+"genPhotPy["+prefix_+"genPhotN]/float");
    mPhotonData->Branch(prefix_+"genPhotPz",     genPhotPz,     prefix_+"genPhotPz["+prefix_+"genPhotN]/float");

  }

  edm::LogInfo("PhotonEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//#include "FWCore/PluginManager/interface/ModuleDef.h"
//#include "FWCore/Framework/interface/ModuleFactory.h"
//
//DEFINE_EDM_PLUGIN(PhotonAnalyzerPAT);

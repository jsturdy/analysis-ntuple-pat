
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
// $Id: PhotonAnalyzerPAT.cc,v 1.7 2010/10/13 16:46:09 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/PhotonAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

//#ifdef __CINT__ 
//
//typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> LorentzV;
//typedef std::vector<LorentzV>                                   LorentzVs;
//
//#pragma link C++ typedef LorentzV;
//#pragma link C++ typedef LorentzVs;
//
//#pragma link C++ class reco::Candidate::LorentzVector +; 
//#pragma link C++ class std::vector< <reco::Candidate::LorentzVector> >+; 
//#pragma link C++ class LorentzV+; 
//#pragma link C++ class LorentzVs+; 
//
//#endif

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
    maintenanceGen(genParticles->size());
    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      if (st==3) {
  	int status = 3;
      } else { // store photons of status 1 
  	if ( (abs(pCand.pdgId()) == 22) ) {
  	  
	  v_genPhotP4     .push_back(pCand.p4());
	  vd_genPhotPx     .push_back(pCand.px());
	  vd_genPhotPy     .push_back(pCand.py());
	  vd_genPhotPz     .push_back(pCand.pz());
	  vd_genPhotE      .push_back(pCand.energy());
  	  vi_genPhotIds   .push_back(pCand.pdgId());
  	  vi_genPhotStatus.push_back(pCand.status());
  	  
  	  if (pCand.numberOfMothers() > 0 ) { 
  	    const reco::Candidate * mom = pCand.mother();
  	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
  	    
  	    for( size_t j = 0; j < i; ++ j ) {
  	      const Candidate * ref = &((*genParticles)[j]);
  	      //if (ref == mom) { vi_genPhotRefs.push_back(ref->pdgId()); }
  	      if (ref == mom) { vi_genPhotRefs.push_back(j); }
  	    }  
  	  } else { vi_genPhotRefs[pcount]=-999;}
  	  pcount++;
  	}
      }
    }
    i_genPhotLength = pcount;
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
  i_PhotN = photHandle->size();
  int ph = 0;
  if ( i_PhotN > 50 )
    i_PhotN = 50;
  if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
  maintenancePhots(i_PhotN);

  for (int i=0;i<i_PhotN;i++) {
    const pat::Photon thePhoton = (*photHandle)[i];
    if ( (thePhoton.pt() > photMinEt_) && !(thePhoton.eta() > photMaxEta_) ) {
      if (debug_) edm::LogVerbatim("PhotonEvent") << " looping over good photons " << std::endl;      
      v_photP4.push_back(thePhoton.p4());
      vd_PhotPx.push_back(thePhoton.px());
      vd_PhotPy.push_back(thePhoton.py());
      vd_PhotPz.push_back(thePhoton.pz());
      vd_PhotE .push_back(thePhoton.energy());

      if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
    
      vd_PhotTrkIso .push_back(thePhoton.trackIso());
      vd_PhotECalIso.push_back(thePhoton.ecalIso());
      vd_PhotHCalIso.push_back(thePhoton.hcalIso());
      vd_PhotAllIso .push_back(thePhoton.caloIso());

      //vb_PhotLooseEM.push_back(thePhoton.photonID("PhotonCutBasedIDLooseEM"));
      vb_PhotLoosePhoton.push_back(thePhoton.photonID("PhotonCutBasedIDLoose"));
      vb_PhotTightPhoton.push_back(thePhoton.photonID("PhotonCutBasedIDTight"));
      
      // PhotGenon info
      if (doMCData_) {
      	//reco::Particle* part = const_cast<reco::Particle*>( thePhoton.genPhoton() );
      	const reco::Candidate* candPhot = thePhoton.genPhoton();

	if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

      	if ( candPhot ) {
      	  vd_PhotGenPdgId.push_back(candPhot->pdgId());
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(candPhot->px(),candPhot->py(),candPhot->pz(),candPhot->energy());
	  v_genphotP4.push_back(genp4);
	  vd_PhotGenPx.push_back(candPhot->px());
	  vd_PhotGenPy.push_back(candPhot->py());
	  vd_PhotGenPz.push_back(candPhot->pz());
	  vd_PhotGenE .push_back(candPhot->energy());
      	  const reco::Candidate* photMother = candPhot->mother();
      	  if ( photMother ) {
      	    while (photMother->pdgId() == candPhot->pdgId()) photMother = photMother->mother();
      	    if ( photMother ) {
      	      vd_PhotGenMother.push_back(photMother->pdgId());
      	    }
      	  }
      	}
      	else {
      	  vd_PhotGenPdgId .push_back(-999);
      	  vd_PhotGenMother.push_back(-999);
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	  v_genphotP4.push_back(genp4);
	  vd_PhotGenPx.push_back(-999.);
	  vd_PhotGenPy.push_back(-999.);
	  vd_PhotGenPz.push_back(-999.);
	  vd_PhotGenE .push_back(-999.);
      	}

	if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

      }
      ++ph;
    }
  } // loop over pat::Photons
  i_PhotN = ph;
  
  
  // Fill the tree only if all preselection conditions are met
  if (debug_)
    std::cout<<"Done analyzing photons"<<std::endl;
  return photon_result;
}

//________________________________________________________________________________________
void PhotonAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";
  
  // Add the branches

  //add photons
  mPhotonData->Branch(prefix_+"PhotonP4",&v_photP4);
  mPhotonData->Branch(prefix_+"PhotN",   &i_PhotN,   prefix_+"PhotN/I");  
  //mPhotonData->Branch(prefix_+"PhotPx",  &vd_PhotPx);
  //mPhotonData->Branch(prefix_+"PhotPy",  &vd_PhotPy);
  //mPhotonData->Branch(prefix_+"PhotPz",  &vd_PhotPz);
  //mPhotonData->Branch(prefix_+"PhotE",   &vd_PhotE);
  //
  mPhotonData->Branch(prefix_+"PhotTrkIso",  &vd_PhotTrkIso);
  mPhotonData->Branch(prefix_+"PhotECalIso", &vd_PhotECalIso);
  mPhotonData->Branch(prefix_+"PhotHCalIso", &vd_PhotHCalIso);
  mPhotonData->Branch(prefix_+"PhotAllIso",  &vd_PhotAllIso);
  
  //mPhotonData->Branch(prefix_+"Phot_isccPhotAssoc", m_ccPhotAssoc,     prefix_+"ccPhotAssoc["+prefix_+"PhotN]/O");
  //mPhotonData->Branch(prefix_+"PhotLooseEM",        &vb_PhotLooseEM);
  mPhotonData->Branch(prefix_+"PhotLoosePhoton",    &vb_PhotLoosePhoton);
  mPhotonData->Branch(prefix_+"PhotTightPhoton",    &vb_PhotTightPhoton);
  
  if (doMCData_) {
    //from reco::candidate
    mPhotonData->Branch(prefix_+"PhotGenPdgId",  &vd_PhotGenPdgId);
    mPhotonData->Branch(prefix_+"PhotGenMother", &vd_PhotGenMother);
    mPhotonData->Branch(prefix_+"PhotGenP4",     &v_genphotP4);
    //mPhotonData->Branch(prefix_+"PhotGenPx",  &vd_PhotGenPx);
    //mPhotonData->Branch(prefix_+"PhotGenPy",  &vd_PhotGenPy);
    //mPhotonData->Branch(prefix_+"PhotGenPz",  &vd_PhotGenPz);
    //mPhotonData->Branch(prefix_+"PhotGenE",   &vd_PhotGenE);
  
    //from genParticles
    mPhotonData->Branch(prefix_+"genPhotP4",     &v_genPhotP4);
    //mPhotonData->Branch(prefix_+"genPhotPx",     &vd_genPhotPx);
    //mPhotonData->Branch(prefix_+"genPhotPy",     &vd_genPhotPy);
    //mPhotonData->Branch(prefix_+"genPhotPz",     &vd_genPhotPz);
    //mPhotonData->Branch(prefix_+"genPhotE",      &vd_genPhotE);
    mPhotonData->Branch(prefix_+"genPhotN",      &i_genPhotLength, prefix_+"genPhotN/I");
    mPhotonData->Branch(prefix_+"genPhotId",     &vi_genPhotIds);
    mPhotonData->Branch(prefix_+"genPhotMother", &vi_genPhotRefs);
    mPhotonData->Branch(prefix_+"genPhotStatus", &vi_genPhotStatus);
  
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


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
// $Id: PhotonAnalyzerPAT.cc,v 1.5 2010/06/09 18:02:30 sturdy Exp $
//
//


//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/PhotonAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 
#pragma link C++ class std::vector<<reco::Candidate::LorentzVector> >+; 
#endif

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
    
    //v_genPhotP4.resize(genParticles->size());
    int pcount=0;
    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      if (st==3) {
  	int status = 3;
      } else { // store photons of status 1 
  	if ( (abs(pCand.pdgId()) == 22) ) {
  	  
	  //v_genPhotP4.at(pcount)  = pCand.p4();
	  v_genPhotP4.push_back(pCand.p4());
  	  mat_i_genPhotIds[pcount]    = pCand.pdgId();
  	  mat_i_genPhotStatus[pcount] = pCand.status();
  	  mat_f_genPhotE[pcount]      = pCand.energy();
  	  mat_f_genPhotPx[pcount]     = pCand.px();
  	  mat_f_genPhotPy[pcount]     = pCand.py();
  	  mat_f_genPhotPz[pcount]     = pCand.pz();
  	  
  	  if (pCand.numberOfMothers() > 0 ) { 
  	    const reco::Candidate * mom = pCand.mother();
  	    while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
  	    
  	    for( size_t j = 0; j < i; ++ j ) {
  	      const Candidate * ref = &((*genParticles)[j]);
  	      if (ref == mom) { mat_i_genPhotRefs[pcount] = ref->pdgId(); }
  	      //if (ref == mom) { genPhotRefs[pcount] = j; }
  	    }  
  	  } else { mat_i_genPhotRefs[pcount]=-999;}
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
  //v_photP4.resize(i_PhotN);
  if (debug_) sprintf(logmessage,"Photon/%d      E     Et    Pt    Px    Py    Pz    Eta    Phi",i_PhotN);
  if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

  for (int i=0;i<i_PhotN;i++) {
    const pat::Photon thePhoton = (*photHandle)[i];
    if ( (thePhoton.pt() > photMinEt_) && !(thePhoton.eta() > photMaxEta_) ) {
      if (debug_) edm::LogVerbatim("PhotonEvent") << " looping over good photons " << std::endl;      
      //v_photP4.at(ph) = thePhoton.p4();
      v_photP4.push_back(thePhoton.p4());
      mat_d_PhotE[ph]   = thePhoton.energy();
      mat_d_PhotEt[ph]  = thePhoton.et();
      mat_d_PhotPt[ph]  = thePhoton.pt();
      mat_d_PhotPx[ph]  = thePhoton.momentum().X();
      mat_d_PhotPy[ph]  = thePhoton.momentum().Y();
      mat_d_PhotPz[ph]  = thePhoton.momentum().Z();
      mat_d_PhotEta[ph] = thePhoton.eta();
      mat_d_PhotPhi[ph] = thePhoton.phi();

      if (debug_) sprintf(logmessage,"%6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f", \
			  ph,mat_d_PhotE[ph],mat_d_PhotEt[ph],mat_d_PhotPt[ph],mat_d_PhotPx[ph],mat_d_PhotPy[ph],mat_d_PhotPz[ph],mat_d_PhotEta[ph],mat_d_PhotPhi[ph]);
      if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
    
      mat_d_PhotTrkIso[ph]  = thePhoton.trackIso();
      mat_d_PhotECalIso[ph] = thePhoton.ecalIso();
      mat_d_PhotHCalIso[ph] = thePhoton.hcalIso();
      mat_d_PhotAllIso[ph]  = thePhoton.caloIso();

      //mat_b_PhotLooseEM[ph] = thePhoton.photonID("PhotonCutBasedIDLooseEM");
      mat_b_PhotLoosePhoton[ph] = thePhoton.photonID("PhotonCutBasedIDLoose");
      mat_b_PhotTightPhoton[ph] = thePhoton.photonID("PhotonCutBasedIDTight");
      
      // PhotGenon info
      if (doMCData_) {
      	//reco::Particle* part = const_cast<reco::Particle*>( thePhoton.genPhoton() );
      	const reco::Candidate* candPhot = thePhoton.genPhoton();

      	if (debug_) sprintf(logmessage,"      PhotGenon      E     Et    Pt    Px    Py    Pz    PdgId    Mother\n");
	if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;

      	if ( candPhot ) {
      	  mat_d_PhotGenPdgId[ph] = candPhot->pdgId();
      	  mat_d_PhotGenPx[ph]    = candPhot->px();
      	  mat_d_PhotGenPy[ph]    = candPhot->py();
      	  mat_d_PhotGenPz[ph]    = candPhot->pz();
      	  mat_d_PhotGenPt[ph]    = candPhot->pt();
      	  mat_d_PhotGenEt[ph]    = candPhot->et();
      	  mat_d_PhotGenE[ph]     = candPhot->energy();
      	  const reco::Candidate* photMother = candPhot->mother();
      	  if ( photMother ) {
      	    while (photMother->pdgId() == candPhot->pdgId()) photMother = photMother->mother();
      	    if ( photMother ) {
      	      mat_d_PhotGenMother[ph] = photMother->pdgId();
      	      //if ( cand->mother()->pdgId() ==  cand->pdgId()) 
      	      //  {
      	      //	mat_d_PhotGenMother[ph] = cand->mother()->mother()->pdgId();
      	      //  }
      	    }
      	  }
      	}
      	else {
      	  mat_d_PhotGenPdgId[ph]  = -999;
      	  mat_d_PhotGenMother[ph] = -999;
      	  mat_d_PhotGenPx[ph]     = -999;
      	  mat_d_PhotGenPy[ph]     = -999;
      	  mat_d_PhotGenPz[ph]     = -999;
      	  mat_d_PhotGenPt[ph]     = -999;
      	  mat_d_PhotGenEt[ph]     = -999;
      	  mat_d_PhotGenE[ph]      = -999;
      	}

      	if (debug_) sprintf(logmessage,"      %6d   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f   %2.2f\n", \
      	       ph,mat_d_PhotGenE[ph],mat_d_PhotGenEt[ph],mat_d_PhotGenPt[ph],mat_d_PhotGenPx[ph],mat_d_PhotGenPy[ph],mat_d_PhotGenPz[ph],mat_d_PhotGenPdgId[ph],mat_d_PhotGenMother[ph]);
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
  mPhotonData->Branch(prefix_+"PhotonP4",&v_photP4,  prefix_+"PhotonP4");
  mPhotonData->Branch(prefix_+"PhotN",   &i_PhotN,   prefix_+"PhotN/I");  
  mPhotonData->Branch(prefix_+"PhotE",    mat_d_PhotE,   prefix_+"PhotE["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotEt",   mat_d_PhotEt,  prefix_+"PhotEt["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotPt",   mat_d_PhotPt,  prefix_+"PhotPt["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotPx",   mat_d_PhotPx,  prefix_+"PhotPx["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotPy",   mat_d_PhotPy,  prefix_+"PhotPy["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotPz",   mat_d_PhotPz,  prefix_+"PhotPz["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotEta",  mat_d_PhotEta, prefix_+"PhotEta["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotPhi",  mat_d_PhotPhi, prefix_+"PhotPhi["+prefix_+"PhotN]/D");

  mPhotonData->Branch(prefix_+"PhotTrkIso",  mat_d_PhotTrkIso,  prefix_+"PhotTrkIso["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotECalIso", mat_d_PhotECalIso, prefix_+"PhotECalIso["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotHCalIso", mat_d_PhotHCalIso, prefix_+"PhotHCalIso["+prefix_+"PhotN]/D");
  mPhotonData->Branch(prefix_+"PhotAllIso",  mat_d_PhotAllIso,  prefix_+"PhotAllIso["+prefix_+"PhotN]/D");

  //mPhotonData->Branch(prefix_+"Phot_isccPhotAssoc", m_ccPhotAssoc,     prefix_+"ccPhotAssoc["+prefix_+"PhotN]/O");
  //mPhotonData->Branch(prefix_+"PhotLooseEM",        mat_b_PhotLooseEM,     prefix_+"PhotLooseEM["+prefix_+"PhotN]/O");
  mPhotonData->Branch(prefix_+"PhotLoosePhoton",    mat_b_PhotLoosePhoton, prefix_+"PhotLoosePhoton["+prefix_+"PhotN]/O");
  mPhotonData->Branch(prefix_+"PhotTightPhoton",    mat_b_PhotTightPhoton, prefix_+"PhotTightPhoton["+prefix_+"PhotN]/O");

  if (doMCData_) {
    //from reco::candidate
    mPhotonData->Branch(prefix_+"PhotGen",      &v_genPhotP4,         prefix_+"PhotGenP4");
    mPhotonData->Branch(prefix_+"PhotGenPdgId",  mat_d_PhotGenPdgId,  prefix_+"PhotGenPdgId["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenMother", mat_d_PhotGenMother, prefix_+"PhotGenMother["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenPx",     mat_d_PhotGenPx,     prefix_+"PhotGenPx["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenPy",     mat_d_PhotGenPy,     prefix_+"PhotGenPy["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenPz",     mat_d_PhotGenPz,     prefix_+"PhotGenPz["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenPt",     mat_d_PhotGenPt,     prefix_+"PhotGenPt["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenEt",     mat_d_PhotGenEt,     prefix_+"PhotGenEt["+prefix_+"PhotN]/D");
    mPhotonData->Branch(prefix_+"PhotGenE",      mat_d_PhotGenE,      prefix_+"PhotGenE["+prefix_+"PhotN]/D");
    //from genParticles
    mPhotonData->Branch(prefix_+"genPhotN",     &i_genPhotLength, prefix_+"genPhotN/I");
    mPhotonData->Branch(prefix_+"genPhotId",     mat_i_genPhotIds,    prefix_+"genPhotIds["+prefix_+"genPhotN]/I");
    mPhotonData->Branch(prefix_+"genPhotMother", mat_i_genPhotRefs,   prefix_+"genPhotRefs["+prefix_+"genPhotN]/I");
    mPhotonData->Branch(prefix_+"genPhotStatus", mat_i_genPhotStatus, prefix_+"genPhotStatus["+prefix_+"genPhotN]/I");
    mPhotonData->Branch(prefix_+"genPhotE",      mat_f_genPhotE,      prefix_+"genPhotE["+prefix_+"genPhotN]/F");
    mPhotonData->Branch(prefix_+"genPhotPx",     mat_f_genPhotPx,     prefix_+"genPhotPx["+prefix_+"genPhotN]/F");
    mPhotonData->Branch(prefix_+"genPhotPy",     mat_f_genPhotPy,     prefix_+"genPhotPy["+prefix_+"genPhotN]/F");
    mPhotonData->Branch(prefix_+"genPhotPz",     mat_f_genPhotPz,     prefix_+"genPhotPz["+prefix_+"genPhotN]/F");

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

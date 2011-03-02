
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
// $Id: PhotonAnalyzerPAT.cc,v 1.10 2010/11/08 15:30:00 sturdy Exp $
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
bool PhotonAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  
  using namespace reco;
  using namespace edm;

  doMCData_ = ev.isRealData();
  
  bool_PhotVeto      = false;
  bool photon_result = true;
  edm::LogVerbatim("PhotonEvent") << " Start  " << std::endl;

  std::ostringstream dbg;
  
  // GEN INFO do only if running on MC data
  if (!doMCData_) {
    
    Handle<reco::GenParticleCollection>  genParticles;
    ev.getByLabel(genTag_, genParticles);   
    
    int pcount=0;
    maintenanceGen(genParticles->size());
    for( size_t i = 0; i < genParticles->size(); ++ i ) {
      const reco::Candidate& pCand = (*genParticles)[ i ];
      
      int st = pCand.status();  
      
      if (st==3) {
  	int status = 3;
      } else { // store photons of status 1 
  	if ( (abs(pCand.pdgId()) == 22) ) {
  	  
	  v_genPhotP4        .push_back(pCand.p4());
  	  vi_genPhotIds      .push_back(pCand.pdgId());
  	  vi_genPhotStatus   .push_back(pCand.status());
  	  vi_genPhotDaughters.push_back(pCand.numberOfDaughters());
  	  
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
  ev.getByLabel(photTag_, photHandle);
  if ( !photHandle.isValid() ) {
    edm::LogWarning("PhotonEvent") << "No Photon results for InputTag " << photTag_;
    return false;
  }

  //Get the ECAL rechist for EB to help with E2/E9 and swissCross
  edm::Handle<EcalRecHitCollection> recHits;
  ev.getByLabel( "ecalRecHit","EcalRecHitsEB", recHits);
  
  const EcalRecHitCollection *myRecHits = recHits.product();
  

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

      if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
    
      vd_PhotTrkIso .push_back(thePhoton.trackIso());
      vd_PhotECalIso.push_back(thePhoton.ecalIso());
      vd_PhotHCalIso.push_back(thePhoton.hcalIso());
      vd_PhotAllIso .push_back(thePhoton.caloIso());
      
      //IsolationKeys
      //TrackIso=0, EcalIso=1, HcalIso=2,
      //PfAllParticleIso=3,PfChargedHadronIso=4, PfNeutralHadronIso=5, PfGammaIso=6

      vd_PhotTrkIsoDeposit .push_back(thePhoton.trackIsoDeposit()->candEnergy());
      vd_PhotECalIsoDeposit.push_back(thePhoton.ecalIsoDeposit()->candEnergy());
      vd_PhotHCalIsoDeposit.push_back(thePhoton.hcalIsoDeposit()->candEnergy());

      vb_PhotIsEB.push_back(thePhoton.isEB());
      vb_PhotIsEE.push_back(thePhoton.isEE());

      //vb_PhotLooseEM.push_back(thePhoton.photonID("PhotonCutBasedIDLooseEM"));
      vb_PhotLoosePhoton.push_back(thePhoton.photonID("PhotonCutBasedIDLoose"));
      vb_PhotTightPhoton.push_back(thePhoton.photonID("PhotonCutBasedIDTight"));

      double mySwissCross = -999;
      double myE2OverE9   = -999;
      //double tSeed = -999;

      //if (thePhoton.ecalDrivenSeed()>0 && fabs(thePhoton.superCluster()->eta())<1.4442) {
      if (true) {
	const reco::CaloClusterPtr    seed =    thePhoton.superCluster()->seed(); // seed cluster
	const           DetId seedId = seed->seed();
	EcalSeverityLevelAlgo severity;
	mySwissCross =  severity.swissCross(seedId, *myRecHits) ;
	myE2OverE9   =  severity.swissCross(seedId, *myRecHits) ;
      }
      
      vd_PhotE2OverE9.push_back(myE2OverE9);
      vd_PhotSwissCross.push_back(mySwissCross);
      //vd_PhotTSeed.push_back(severity.swissCross(seedID, *recHits));
      vd_PhotSigmaIetaIeta.push_back(thePhoton.sigmaIetaIeta());

      vb_PhotHasPixelSeed.push_back(thePhoton.hasPixelSeed());
      vb_PhotHasConversionTracks.push_back(thePhoton.hasConversionTracks());

      vd_PhotHadOverEM.push_back(thePhoton.hadronicOverEm());
      
      // PhotGenon info
      const reco::Candidate* candPhot = thePhoton.genPhoton();
      
      if (debug_) edm::LogVerbatim("PhotonEvent")<<logmessage<<std::endl;
      
      if ( candPhot ) {
	vd_PhotGenPdgId.push_back(candPhot->pdgId());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candPhot->px(),candPhot->py(),candPhot->pz(),candPhot->energy());
	v_genphotP4.push_back(genp4);
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
      }
      double photIsoReq = (vd_PhotTrkIso.at(ph)+vd_PhotECalIso.at(ph)+vd_PhotHCalIso.at(ph))/thePhoton.pt();
      if ( photIsoReq  > photRelIso_) bool_PhotVeto = bool_PhotVeto || true;
      if ( thePhoton.pt() > photMaxEt_ ) bool_PhotVeto = bool_PhotVeto || true;
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
  mPhotonData->Branch(prefix_+"PhotVeto",&bool_PhotVeto,   prefix_+"PhotVeto/O");  
  mPhotonData->Branch(prefix_+"PhotonP4",&v_photP4);
  mPhotonData->Branch(prefix_+"PhotN",   &i_PhotN,   prefix_+"PhotN/I");  
  //
  mPhotonData->Branch(prefix_+"PhotTrkIso",  &vd_PhotTrkIso);
  mPhotonData->Branch(prefix_+"PhotECalIso", &vd_PhotECalIso);
  mPhotonData->Branch(prefix_+"PhotHCalIso", &vd_PhotHCalIso);
  mPhotonData->Branch(prefix_+"PhotAllIso",  &vd_PhotAllIso);
  
  mPhotonData->Branch(prefix_+"PhotTrkIsoDeposit",  &vd_PhotTrkIsoDeposit);
  mPhotonData->Branch(prefix_+"PhotECalIsoDeposit", &vd_PhotECalIsoDeposit);
  mPhotonData->Branch(prefix_+"PhotHCalIsoDeposit", &vd_PhotHCalIsoDeposit);

  mPhotonData->Branch(prefix_+"PhotIsEB", &vb_PhotIsEB);
  mPhotonData->Branch(prefix_+"PhotIsEE", &vb_PhotIsEE);
  mPhotonData->Branch(prefix_+"PhotHasPixelSeed", &vb_PhotHasPixelSeed);
  mPhotonData->Branch(prefix_+"PhotHasConversionTracks", &vb_PhotHasConversionTracks);

  //mPhotonData->Branch(prefix_+"Phot_isccPhotAssoc", m_ccPhotAssoc,     prefix_+"ccPhotAssoc["+prefix_+"PhotN]/O");
  //mPhotonData->Branch(prefix_+"PhotLooseEM",        &vb_PhotLooseEM);
  mPhotonData->Branch(prefix_+"PhotLoosePhoton",    &vb_PhotLoosePhoton);
  mPhotonData->Branch(prefix_+"PhotTightPhoton",    &vb_PhotTightPhoton);

  mPhotonData->Branch(prefix_+"PhotE2OverE9",   &vd_PhotE2OverE9);
  mPhotonData->Branch(prefix_+"PhotSwissCross", &vd_PhotSwissCross);
  mPhotonData->Branch(prefix_+"PhotHadOverEM",  &vd_PhotHadOverEM);
  mPhotonData->Branch(prefix_+"PhotSigmaIetaIeta",  &vd_PhotSigmaIetaIeta);

  //from reco::candidate
  mPhotonData->Branch(prefix_+"PhotGenPdgId",  &vd_PhotGenPdgId);
  mPhotonData->Branch(prefix_+"PhotGenMother", &vd_PhotGenMother);
  mPhotonData->Branch(prefix_+"PhotGenP4",     &v_genphotP4);
  
  if (!doMCData_) {
  
    //from genParticles
    mPhotonData->Branch(prefix_+"genPhotP4",       &v_genPhotP4);
    mPhotonData->Branch(prefix_+"genPhotN",        &i_genPhotLength, prefix_+"genPhotN/I");
    mPhotonData->Branch(prefix_+"genPhotId",       &vi_genPhotIds);
    mPhotonData->Branch(prefix_+"genPhotMother",   &vi_genPhotRefs);
    mPhotonData->Branch(prefix_+"genPhotStatus",   &vi_genPhotStatus);
    mPhotonData->Branch(prefix_+"genPhotDaughters",&vi_genPhotDaughters);
  
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

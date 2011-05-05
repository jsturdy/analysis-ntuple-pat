
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
// $Id: PhotonAnalyzerPAT.cc,v 1.15 2011/03/18 10:58:50 sturdy Exp $
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
PhotonAnalyzerPAT::PhotonAnalyzerPAT(const edm::ParameterSet& photonParams, TTree* mPhotonData)
  :
  v_photP4(new std::vector<reco::Candidate::LorentzVector>),
  
  vd_PhotTrkIso(new std::vector<double>),
  vd_PhotECalIso(new std::vector<double>),
  vd_PhotHCalIso(new std::vector<double>),
  vd_PhotAllIso(new std::vector<double>),

  vd_PhotPFAllParticleIso(new std::vector<double>),
  vd_PhotPFChargedHadronIso(new std::vector<double>),
  vd_PhotPFNeutralHadronIso(new std::vector<double>),
  vd_PhotPFGammaIso(new std::vector<double>),
 
  vd_PhotTrkIsoDeposit(new std::vector<double>),
  vd_PhotECalIsoDeposit(new std::vector<double>),
  vd_PhotHCalIsoDeposit(new std::vector<double>),
  
  vd_PhotPFAllParticleIsoDeposit(new std::vector<double>),
  vd_PhotPFChargedHadronIsoDeposit(new std::vector<double>),
  vd_PhotPFNeutralHadronIsoDeposit(new std::vector<double>),
  vd_PhotPFGammaIsoDeposit(new std::vector<double>),

  vd_PhotSCEta (new std::vector<double>),
  vd_PhotSCPhi (new std::vector<double>),
  vd_PhotSCEn  (new std::vector<double>),
  vd_PhotSCPt  (new std::vector<double>),
  vd_PhotSCRawE(new std::vector<double>),

  vb_PhotIsEB(new std::vector<int>),
  vb_PhotIsEE(new std::vector<int>),
  vb_PhotIsEBGap(new std::vector<int>),
  vb_PhotIsEEGap(new std::vector<int>),
  vb_PhotIsEBEEGap(new std::vector<int>),

  vb_PhotLoosePhoton(new std::vector<int>),
  vb_PhotTightPhoton(new std::vector<int>),

  vd_PhotHadOverEM(new std::vector<double>),
  vd_PhotE2OverE9(new std::vector<double>),
  vd_PhotSwissCross(new std::vector<double>),
  vd_PhotTSeed(new std::vector<double>),
  vd_PhotESeed(new std::vector<double>),
  vd_PhotSigmaIetaIeta(new std::vector<double>),

  vb_PhotHasPixelSeed       (new std::vector<int>),
  vb_PhotHasConversionTracks(new std::vector<int>),
  
  v_genphotP4(new  std::vector<reco::Candidate::LorentzVector> ),

  vi_PhotGenPdgId       (new std::vector<int>),
  vi_PhotGenStatus      (new std::vector<int>),
  vi_PhotGenMother      (new std::vector<int>),
  vi_PhotGenMotherStatus(new std::vector<int>)

{ 

  // Read in parameters from the config file
  photMaxEta_ = photonParams.getUntrackedParameter<double>("photMaxEta",3.);
  photMaxEt_  = photonParams.getUntrackedParameter<double>("photMaxEt",999);
  photMinEt_  = photonParams.getUntrackedParameter<double>("photMinEt",5);
  photRelIso_ = photonParams.getUntrackedParameter<double>("photRelIso",0.5);

  debug_   = photonParams.getUntrackedParameter<int>("debugPhots",0);
  prefix_  = photonParams.getUntrackedParameter<std::string>("prefixPhots","");
 
  // get the data tags
  photTag_ = photonParams.getUntrackedParameter<edm::InputTag>("photTag");

  // Initialise plots [should improve in the future]
  bookTTree(mPhotonData);
}


//________________________________________________________________________________________
PhotonAnalyzerPAT::~PhotonAnalyzerPAT() {
  //delete mPhotonData;
}

//
//________________________________________________________________________________________
void PhotonAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
}

//________________________________________________________________________________________
// Method called to for each event
bool PhotonAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  
  using namespace reco;
  using namespace edm;

  bool_PhotVeto      = false;
  bool photon_result = true;
  edm::LogVerbatim("PhotonEvent") << " Start  " << std::endl;
  maintenancePhots();

  std::ostringstream dbg;
  
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

  //Get the ECAL rechits for EB to help with E2/E9 and swissCross
  edm::Handle<EcalRecHitCollection> recHitsEB;
  //ev.getByLabel( "ecalRecHit","reducedEcalRecHitsEB", recHitsEB);
  ev.getByLabel("reducedEcalRecHitsEB", recHitsEB);

  edm::Handle<EcalRecHitCollection> recHitsEE;
  //ev.getByLabel( "ecalRecHit","reducedEcalRecHitsEE", recHitsEE);
  ev.getByLabel("reducedEcalRecHitsEE", recHitsEE);
  
  const EcalRecHitCollection *myEBRecHits = recHitsEB.product();
  const EcalRecHitCollection *myEERecHits = recHitsEE.product();

  edm::LogVerbatim("PhotonEvent") << " start reading in photons " << std::endl;
  // Add the photons
  i_PhotN = photHandle->size();
  int ph = 0;
  if ( i_PhotN > 50 )
    i_PhotN = 50;

  for (int i=0;i<i_PhotN;i++) {
    const pat::Photon thePhoton = (*photHandle)[i];
    if ( (thePhoton.pt() > photMinEt_) && !(thePhoton.eta() > photMaxEta_) ) {
      if (debug_) edm::LogVerbatim("PhotonEvent") << " looping over good photons " << std::endl;      
      v_photP4->push_back(thePhoton.p4());

      vd_PhotTrkIso ->push_back(thePhoton.trackIso());
      vd_PhotECalIso->push_back(thePhoton.ecalIso());
      vd_PhotHCalIso->push_back(thePhoton.hcalIso());
      vd_PhotAllIso ->push_back(thePhoton.caloIso());

      //Special PF based isolation variables
      vd_PhotPFAllParticleIso  ->push_back(thePhoton.userIsolation(pat::PfAllParticleIso));
      vd_PhotPFChargedHadronIso->push_back(thePhoton.userIsolation(pat::PfChargedHadronIso));
      vd_PhotPFNeutralHadronIso->push_back(thePhoton.userIsolation(pat::PfNeutralHadronIso));
      vd_PhotPFGammaIso        ->push_back(thePhoton.userIsolation(pat::PfGammaIso));
      
      if (thePhoton.trackIsoDeposit())
	vd_PhotTrkIsoDeposit ->push_back(thePhoton.trackIsoDeposit()->candEnergy());
      else
	vd_PhotTrkIsoDeposit ->push_back(-999);

      if (thePhoton.ecalIsoDeposit())
	vd_PhotECalIsoDeposit ->push_back(thePhoton.ecalIsoDeposit()->candEnergy());
      else
	vd_PhotECalIsoDeposit ->push_back(-999);

      if (thePhoton.hcalIsoDeposit())
	vd_PhotHCalIsoDeposit ->push_back(thePhoton.hcalIsoDeposit()->candEnergy());
      else
	vd_PhotHCalIsoDeposit ->push_back(-999);

      if (thePhoton.userIsoDeposit(pat::PfAllParticleIso))
	vd_PhotPFAllParticleIsoDeposit ->push_back(thePhoton.userIsoDeposit(pat::PfAllParticleIso)->candEnergy());
      else
	vd_PhotPFAllParticleIsoDeposit ->push_back(-999);

      if (thePhoton.userIsoDeposit(pat::PfChargedHadronIso))
	vd_PhotPFChargedHadronIsoDeposit ->push_back(thePhoton.userIsoDeposit(pat::PfChargedHadronIso)->candEnergy());
      else
	vd_PhotPFChargedHadronIsoDeposit ->push_back(-999);

      if (thePhoton.userIsoDeposit(pat::PfNeutralHadronIso))
	vd_PhotPFNeutralHadronIsoDeposit ->push_back(thePhoton.userIsoDeposit(pat::PfNeutralHadronIso)->candEnergy());
      else
	vd_PhotPFNeutralHadronIsoDeposit ->push_back(-999);

      if (thePhoton.userIsoDeposit(pat::PfGammaIso))
	vd_PhotPFGammaIsoDeposit ->push_back(thePhoton.userIsoDeposit(pat::PfGammaIso)->candEnergy());
      else
	vd_PhotPFGammaIsoDeposit ->push_back(-999);
      
      int photIsEB = thePhoton.isEB() ? 1 : 0;
      int photIsEE = thePhoton.isEE() ? 1 : 0;
      int photIsEBGap = thePhoton.isEBGap() ? 1 : 0;
      int photIsEEGap = thePhoton.isEEGap() ? 1 : 0;
      int photIsEBEEGap = thePhoton.isEBEEGap() ? 1 : 0;

      vb_PhotIsEB->push_back(photIsEB);
      vb_PhotIsEE->push_back(photIsEE);
      vb_PhotIsEBGap->push_back(photIsEBGap);
      vb_PhotIsEEGap->push_back(photIsEEGap);
      vb_PhotIsEBEEGap->push_back(photIsEBEEGap);
      
      //int photIDLooseEM = thePhoton.photonID("PhotonCutBasedIDLooseEM") ? 1 : 0;
      int photIDLoose   = thePhoton.photonID("PhotonCutBasedIDLoose") ? 1 : 0;
      int photIDTight   = thePhoton.photonID("PhotonCutBasedIDTight") ? 1 : 0;

      //vb_PhotLooseEM    ->push_back(photIDLooseEM);
      vb_PhotLoosePhoton->push_back(photIDLoose);
      vb_PhotTightPhoton->push_back(photIDTight);
      
      double mySwissCross = -999.;
      double myE2OverE9   = -999.;

      double mySCEta      = -999.;
      double mySCPhi      = -999.;
      double mySCEn       = -999.;
      double mySCPt       = -999.;
      double mySCRawE     = -999.;
      double tSeed = -999.;
      double eSeed = -999.;
      
      if (thePhoton.superCluster().isNonnull()) {
	const reco::CaloClusterPtr    seed   = thePhoton.superCluster()->seed(); // seed cluster
	const       DetId             seedId = seed->seed();
	int subdet = seed->hitsAndFractions()[0].first.subdetId();
	
	const EcalRecHitCollection* ecalRecHits = 0;
	if (subdet == EcalBarrel) ecalRecHits = myEBRecHits;
	if (subdet == EcalEndcap) ecalRecHits = myEERecHits;
	tSeed = ecalRecHits->find(seedId)->time();
	eSeed = ecalRecHits->find(seedId)->energy();
	
	EcalSeverityLevelAlgo severity;
	mySwissCross =  severity.swissCross(seedId, *ecalRecHits) ;
	myE2OverE9   =  severity.swissCross(seedId, *ecalRecHits) ;
	
	mySCEta      = thePhoton.superCluster()->eta();
	mySCPhi      = thePhoton.superCluster()->phi();
	mySCEn       = thePhoton.superCluster()->energy();
	mySCPt       = mySCEn/cosh(thePhoton.superCluster()->eta());
	mySCRawE     = thePhoton.superCluster()->rawEnergy();
      }
      
      vd_PhotSCEta ->push_back(mySCEta );
      vd_PhotSCPhi ->push_back(mySCPhi );
      vd_PhotSCEn  ->push_back(mySCEn  );
      vd_PhotSCPt  ->push_back(mySCPt  );
      vd_PhotSCRawE->push_back(mySCRawE);
      
      //
      vd_PhotE2OverE9->push_back(myE2OverE9);
      vd_PhotSwissCross->push_back(mySwissCross);
      
      vd_PhotTSeed->push_back(tSeed);
      vd_PhotESeed->push_back(eSeed);

      vd_PhotSigmaIetaIeta->push_back(thePhoton.sigmaIetaIeta());

      int photHasSeed   = thePhoton.hasPixelSeed()        ? 1 : 0;
      int photHasTracks = thePhoton.hasConversionTracks() ? 1 : 0;
      vb_PhotHasPixelSeed->push_back(photHasSeed);
      vb_PhotHasConversionTracks->push_back(photHasTracks);

      vd_PhotHadOverEM->push_back(thePhoton.hadronicOverEm());
      
      // PhotGenon info
      const reco::Candidate* candPhot = thePhoton.genPhoton();
      
      if ( candPhot ) {
	vi_PhotGenPdgId->push_back(candPhot->pdgId());
	vi_PhotGenStatus->push_back(candPhot->status());
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(candPhot->px(),candPhot->py(),candPhot->pz(),candPhot->energy());
	v_genphotP4->push_back(genp4);
	const reco::Candidate* photMother = candPhot->mother();
	if ( photMother ) {
	  //is this necessary
	  //while (photMother->pdgId() == candPhot->pdgId()) photMother = photMother->mother();
	  //if ( photMother ) {
	  vi_PhotGenMother->push_back(photMother->pdgId());
	  vi_PhotGenMotherStatus->push_back(photMother->status());
	  //}
	}
      }
      else {
	vi_PhotGenPdgId       ->push_back(-999);
	vi_PhotGenStatus      ->push_back(-999);
	vi_PhotGenMother      ->push_back(-999);
	vi_PhotGenMotherStatus->push_back(-999);
	reco::Candidate::LorentzVector genp4;
	genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	v_genphotP4->push_back(genp4);
      }
      double photIsoReq = (vd_PhotTrkIso->at(ph)+vd_PhotECalIso->at(ph)+vd_PhotHCalIso->at(ph))/thePhoton.pt();
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
void PhotonAnalyzerPAT::bookTTree(TTree* mPhotonData) {
  
  // Add the branches

  //add photons
  mPhotonData->Branch(prefix_+"PhotVeto",&bool_PhotVeto,   prefix_+"PhotVeto/O");  
  mPhotonData->Branch(prefix_+"PhotN",   &i_PhotN,   prefix_+"PhotN/I");  
  //
  mPhotonData->Branch(prefix_+"PhotonP4",&(*v_photP4.get() ));
  //
  mPhotonData->Branch(prefix_+"PhotTrkIso",  &(*vd_PhotTrkIso.get() ));
  mPhotonData->Branch(prefix_+"PhotECalIso", &(*vd_PhotECalIso.get() ));
  mPhotonData->Branch(prefix_+"PhotHCalIso", &(*vd_PhotHCalIso.get() ));
  mPhotonData->Branch(prefix_+"PhotAllIso",  &(*vd_PhotAllIso.get() ));

  mPhotonData->Branch(prefix_+"PhotPFAllParticleIso",   &(*vd_PhotPFAllParticleIso.get() ));
  mPhotonData->Branch(prefix_+"PhotPFChargedHadronIso", &(*vd_PhotPFChargedHadronIso.get() ));
  mPhotonData->Branch(prefix_+"PhotPFNeutralHadronIso", &(*vd_PhotPFNeutralHadronIso.get() ));
  mPhotonData->Branch(prefix_+"PhotPFGammaIso",         &(*vd_PhotPFGammaIso.get() ));
  
  mPhotonData->Branch(prefix_+"PhotTrkIsoDeposit",  &(*vd_PhotTrkIsoDeposit.get() ));
  mPhotonData->Branch(prefix_+"PhotECalIsoDeposit", &(*vd_PhotECalIsoDeposit.get() ));
  mPhotonData->Branch(prefix_+"PhotHCalIsoDeposit", &(*vd_PhotHCalIsoDeposit.get() ));
  
  mPhotonData->Branch(prefix_+"PhotPFAllParticleIsoDeposit",   &(*vd_PhotPFAllParticleIsoDeposit.get() ));
  mPhotonData->Branch(prefix_+"PhotPFChargedHadronIsoDeposit", &(*vd_PhotPFChargedHadronIsoDeposit.get() ));
  mPhotonData->Branch(prefix_+"PhotPFNeutralHadronIsoDeposit", &(*vd_PhotPFNeutralHadronIsoDeposit.get() ));
  mPhotonData->Branch(prefix_+"PhotPFGammaIsoDeposit",         &(*vd_PhotPFGammaIsoDeposit.get() ));
  
  mPhotonData->Branch(prefix_+"PhotIsEB", &(*vb_PhotIsEB.get() ));
  mPhotonData->Branch(prefix_+"PhotIsEE", &(*vb_PhotIsEE.get() ));
  mPhotonData->Branch(prefix_+"PhotIsEBGap", &(*vb_PhotIsEBGap.get() ));
  mPhotonData->Branch(prefix_+"PhotIsEEGap", &(*vb_PhotIsEEGap.get() ));
  mPhotonData->Branch(prefix_+"PhotIsEBEEGap", &(*vb_PhotIsEBEEGap.get() ));
  mPhotonData->Branch(prefix_+"PhotHasPixelSeed", &(*vb_PhotHasPixelSeed.get() ));
  mPhotonData->Branch(prefix_+"PhotHasConversionTracks", &(*vb_PhotHasConversionTracks.get() ));

  mPhotonData->Branch(prefix_+"PhotLoosePhoton",    &(*vb_PhotLoosePhoton.get() ));
  mPhotonData->Branch(prefix_+"PhotTightPhoton",    &(*vb_PhotTightPhoton.get() ));

  mPhotonData->Branch(prefix_+"PhotSCEta",  &(*vd_PhotSCEta .get() ));
  mPhotonData->Branch(prefix_+"PhotSCPhi",  &(*vd_PhotSCPhi .get() ));
  mPhotonData->Branch(prefix_+"PhotSCEn",   &(*vd_PhotSCEn  .get() ));
  mPhotonData->Branch(prefix_+"PhotSCPt",   &(*vd_PhotSCPt  .get() ));
  mPhotonData->Branch(prefix_+"PhotSCRawE", &(*vd_PhotSCRawE.get() ));

  mPhotonData->Branch(prefix_+"PhotTSeed",      &(*vd_PhotTSeed.get() ));
  mPhotonData->Branch(prefix_+"PhotESeed",      &(*vd_PhotESeed.get() ));
  mPhotonData->Branch(prefix_+"PhotE2OverE9",      &(*vd_PhotE2OverE9.get() ));
  mPhotonData->Branch(prefix_+"PhotSwissCross",    &(*vd_PhotSwissCross.get() ));
  mPhotonData->Branch(prefix_+"PhotHadOverEM",     &(*vd_PhotHadOverEM.get() ));
  mPhotonData->Branch(prefix_+"PhotSigmaIetaIeta", &(*vd_PhotSigmaIetaIeta.get() ));

  //from reco::candidate
  mPhotonData->Branch(prefix_+"PhotGenPdgId",   &(*vi_PhotGenPdgId.get() ));
  mPhotonData->Branch(prefix_+"PhotGenStatus",  &(*vi_PhotGenStatus.get() ));
  mPhotonData->Branch(prefix_+"PhotGenMother",  &(*vi_PhotGenMother.get() ));
  mPhotonData->Branch(prefix_+"PhotGenMotherStatus", &(*vi_PhotGenMotherStatus.get() ));
  mPhotonData->Branch(prefix_+"PhotGenP4",     &(*v_genphotP4.get() ));
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//#include "FWCore/PluginManager/interface/ModuleDef.h"
//#include "FWCore/Framework/interface/ModuleFactory.h"
//
//DEFINE_EDM_PLUGIN(PhotonAnalyzerPAT);

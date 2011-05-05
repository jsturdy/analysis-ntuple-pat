
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      JetAnalyzerPAT
// 
/**\class JetAnalyzerPAT JetAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/JetAnalyzerPAT.cc

Description: Collects variables related to jets, performs dijet preselection
             Energy of jets = (50,50,30...), |eta|<2.5, 0.05<emfrac<0.95
             If successful, it stores the variables and returns the value of the check

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: JetAnalyzerPAT.cc,v 1.22 2011/03/18 10:58:50 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/JetAnalyzerPAT.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 

#pragma link C++ struct MYMHT;
#pragma link C++ struct MYJETID;
#pragma link C++ struct BTAGINFO;
#pragma link C++ class JetAnalyzerPAT+;
//#pragma link C++ class BTAGINFO+;
//#pragma link C++ class MYJETID+;
//#pragma link C++ class MYMHT+;

#endif
//________________________________________________________________________________________
JetAnalyzerPAT::JetAnalyzerPAT(const edm::ParameterSet& jetParams, TTree* mJetData)
  :
  //map_s_vd_correctionFactor(new std::map<std::string, std::vector<double> >),
  vd_correctionFactorUnc(new std::vector<double> ),
  vd_correctionFactorL1(new std::vector<double> ),
  vd_correctionFactorL2(new std::vector<double> ),
  vd_correctionFactorL3(new std::vector<double> ),
  vd_correctionFactorL2L3(new std::vector<double> ),
  vd_correctionFactorL5uds(new std::vector<double> ),
  vd_correctionFactorL5c(new std::vector<double> ),
  vd_correctionFactorL5b(new std::vector<double> ),
  vd_correctionFactorL5glu(new std::vector<double> ),
  vd_correctionFactorL7uds(new std::vector<double> ),
  vd_correctionFactorL7c(new std::vector<double> ),
  vd_correctionFactorL7b(new std::vector<double> ),
  vd_correctionFactorL7glu(new std::vector<double> ),
  
  //map_s_vi_JetOverlaps (new std::map<std::string, std::vector<int> >  ),
  //map_s_vi_JetNOverlaps(new std::map<std::string, std::vector<int> >  ),
  
  vi_JetElectronOverlaps(new std::vector<int> ),
  vi_JetElectronNOverlaps(new std::vector<int> ),
  vi_JetMuonOverlaps(new std::vector<int> ),
  vi_JetMuonNOverlaps(new std::vector<int> ),
  vi_JetTauOverlaps(new std::vector<int> ),
  vi_JetTauNOverlaps(new std::vector<int> ),
  vi_JetPhotonOverlaps(new std::vector<int> ),
  vi_JetPhotonNOverlaps(new std::vector<int> ),

  v_JetP4   (new std::vector<reco::Candidate::LorentzVector >  ),
  v_RawJetP4(new std::vector<reco::Candidate::LorentzVector >  ),
  v_GenJetP4(new std::vector<reco::Candidate::LorentzVector >  ),
  
  MHtP4   (new reco::Candidate::LorentzVector),
  GenMHtP4(new reco::Candidate::LorentzVector),

  vd_JECUncPlus(new std::vector<double> ),
  vd_JECUncMinus(new std::vector<double> ),

  vd_JetEtaEtaMoment(new std::vector<double> ),
  vd_JetEtaPhiMoment(new std::vector<double> ),
  vd_JetPhiPhiMoment(new std::vector<double> ),

  vb_JetIDMinimal(new std::vector<int> ),
  vb_JetIDLoose(new std::vector<int> ),
  vb_JetIDTight(new std::vector<int> ),
  
  vd_JetEFrac_em(new std::vector<double> ),
  vd_JetEFrac_had(new std::vector<double> ),
  vd_JetCharge(new std::vector<double> ),
  vi_JetHemi(new std::vector<int> ),
  vi_JetNConst(new std::vector<int> ),

  //calo/jpt jet specific
  vd_JetfHPD(new std::vector<double> ),
  vd_JetfRBX(new std::vector<double> ),
  vd_JetN90(new std::vector<double> ),
  
  //jpt/pf jet specific
  vd_JetChargedFrac_em(new std::vector<double> ),
  vd_JetNeutralFrac_em(new std::vector<double> ),
  vd_JetChargedFrac_had(new std::vector<double> ),
  vd_JetNeutralFrac_had(new std::vector<double> ),

  vd_JetChargedEn_em(new std::vector<double> ),
  vd_JetNeutralEn_em(new std::vector<double> ),
  vd_JetChargedEn_had(new std::vector<double> ),
  vd_JetNeutralEn_had(new std::vector<double> ),

  vd_JetChargedMult(new std::vector<double> ),
  vd_JetElectronMult(new std::vector<double> ),
  vd_JetMuonMult(new std::vector<double> ),
  
  //pf jet specific
  vd_JetHFMult_had(new std::vector<double> ),
  vd_JetHFMult_em(new std::vector<double> ),
  vd_JetNeutralMult_had(new std::vector<double> ),
  vd_JetChargedMult_had(new std::vector<double> ),
  vd_JetPhotonMult(new std::vector<double> ),
  vd_JetNeutralMult(new std::vector<double> ),

  vd_JetHFFrac_em(new std::vector<double> ),
  vd_JetHFFrac_had(new std::vector<double> ),
  vd_JetEFrac_muon(new std::vector<double> ),
  vd_JetChargedFrac_muon(new std::vector<double> ),
  vd_JetEFrac_electron(new std::vector<double> ),
  vd_JetEFrac_photon(new std::vector<double> ),

  vd_JetHFEn_em(new std::vector<double> ),
  vd_JetHFEn_had(new std::vector<double> ),
  vd_JetEn_muon(new std::vector<double> ),
  vd_JetChargedEn_muon(new std::vector<double> ),
  vd_JetEn_electron(new std::vector<double> ),
  vd_JetEn_photon(new std::vector<double> ),

  // track info:
  vi_JetTrackNo(new std::vector<int> ),
  vd_JetTrackPhi(new std::vector<double> ),
  vd_JetTrackPhiWeighted(new std::vector<double> ),
  vd_JetTrackPt(new std::vector<double> ),
  
  vd_JetBTag_TCHE(new std::vector<double> ),
  vd_JetBTag_TCHP(new std::vector<double> ),
  vd_JetBTag_jetProb(new std::vector<double> ),
  vd_JetBTag_jetBProb(new std::vector<double> ),
  vd_JetBTag_SSVHE(new std::vector<double> ),
  vd_JetBTag_SSVHP(new std::vector<double> ),
  vd_JetBTag_CSV(new std::vector<double> ),
  vd_JetBTag_CSVMVA(new std::vector<double> ),
  vd_JetBTag_SoftLepton(new std::vector<double> ),
  vd_JetBTag_SoftLeptonByIP(new std::vector<double> ),
  vd_JetBTag_SoftLeptonByPt(new std::vector<double> ),
  
  //Parton level id for gen jets?
  v_JetPartonP4(new std::vector<reco::Candidate::LorentzVector> ),
  vi_JetPartonId(new std::vector<int> ),
  vi_JetPartonStatus(new std::vector<int> ),
  vi_JetPartonMother(new std::vector<int> ),
  vi_JetPartonMotherStatus(new std::vector<int> ),
  vi_JetPartonFlavour(new std::vector<int> )
{ 
  minNJets_  = 1;

  debug_     = jetParams.getUntrackedParameter<int>("debugJets",0);
  prefix_    = jetParams.getUntrackedParameter<std::string>("prefixJets","Calo");
  jetMaxEta_ = jetParams.getUntrackedParameter<double >("jetMaxEta",5.);
  jetMinPt_  = jetParams.getUntrackedParameter<double >("jetMinPt", 10.);

  htMaxEta_ = jetParams.getUntrackedParameter<double >("htMaxEta",jetMaxEta_);
  htMinPt_  = jetParams.getUntrackedParameter<double >("htMinPt", jetMinPt_);

  // get the data tags
  usePFJets_    = jetParams.getUntrackedParameter<bool>("usePFJets",   false);
  useJPTJets_   = jetParams.getUntrackedParameter<bool>("useJPTJets",  false);
  useCaloJets_  = jetParams.getUntrackedParameter<bool>("useCaloJets", false);
  useTrackJets_ = jetParams.getUntrackedParameter<bool>("useTrackJets",false);

  jetTag_     = jetParams.getUntrackedParameter<edm::InputTag>("jetTag");
  //genJetTag_  = jetParams.getUntrackedParameter<edm::InputTag>("genJetTag");

  jetCorTag_  = jetParams.getUntrackedParameter<std::string>("jetCorTag");

  electronPt_   = jetParams.getUntrackedParameter<double>("electronPt",  false);
  electronIso_  = jetParams.getUntrackedParameter<double>("electronIso", false);
  tauPt_        = jetParams.getUntrackedParameter<double>("tauPt",  false);
  tauIso_       = jetParams.getUntrackedParameter<double>("tauIso", false);
  muonPt_       = jetParams.getUntrackedParameter<double>("muonPt",  false);
  muonIso_      = jetParams.getUntrackedParameter<double>("muonIso", false);
  photonPt_     = jetParams.getUntrackedParameter<double>("photonPt",  false);
  photonIso_    = jetParams.getUntrackedParameter<double>("photonIso", false);

  jecUnc = 0;
  // Initialise plots [should improve in the future]
  bookTTree(mJetData);
}


//________________________________________________________________________________________
JetAnalyzerPAT::~JetAnalyzerPAT() {
  delete jecUnc;
  //delete mJetData;  
}

//
//________________________________________________________________________________________
void JetAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
}

//________________________________________________________________________________________
// Method called to for each event
bool JetAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  doMCData_ = ev.isRealData();

  bool_JetPreselection = false;
  bool jet_result = true;
  edm::LogVerbatim("DiJetEvent::JetAnalyzerPAT") << " Start  " << std::endl;

  edm::Handle< std::vector<pat::Jet> > jetHandle;
  ev.getByLabel(jetTag_, jetHandle);
  if ( !jetHandle.isValid() ) {
    edm::LogWarning("DiJetEvent::JetAnalyzerPAT") << "No Jet results for InputTag " << jetTag_;
    return false;
  }

  //get number of jets
  i_NJets = jetHandle->size();
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Processing Jets for InputTag " << jetTag_;
  if (debug_>5) std::cout<< "Processing "<<jetHandle->size() <<" Jets for InputTag " << jetTag_<<std::endl;
  if (debug_>5) {
    if (i_NJets) {
      std::cout<< "isCalo " <<(*jetHandle)[0].isCaloJet()  <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isJPT "  <<(*jetHandle)[0].isJPTJet()   <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isPF "   <<(*jetHandle)[0].isPFJet()    <<" Jets for InputTag " << jetTag_<<std::endl;
      //std::cout<< "isTrack "<<(*jetHandle)[0].isTrackJet() <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isBasic "<<(*jetHandle)[0].isBasicJet() <<" Jets for InputTag " << jetTag_<<std::endl;
    }
  }

  // Add the jets
  int mjet = 0;
  double jetsumpx = 0;
  double jetsumpy = 0;
  double jetsumpz = 0;
  double jetsume  = 0;
  double jetsumpt = 0;

  double gensumpx = 0;
  double gensumpy = 0;
  double gensumpz = 0;
  double gensume  = 0;
  double gensumpt = 0;

  if ( i_NJets >50 ) i_NJets = 50;
  maintenance();
  /////////
  
  std::string corrLevel;
  if (doMCData_)
    corrLevel = "L2L3Residual";
  else
    corrLevel = "L3Absolute";
  
  edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
  es.get<JetCorrectionsRecord>().get(jetCorTag_,JetCorParColl);
  JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
  jecUnc = new JetCorrectionUncertainty(JetCorPar);
  
  for (int k=0;k<i_NJets;k++){

    //const pat::Jet& theJet    = (*jetHandle)[k];
    //pat::Jet const& theJet    = (*jetHandle)[k].correctedJet(corrLevel);
    pat::Jet const& theJet    = (*jetHandle)[k].correctedJet(corrLevel);
    //const pat::Jet& corrJet = theJet.correctedJet(corrLevel);
    
    //const pat::Jet& uncorrJet = (theJet.isCaloJet()) ? theJet.correctedJet("RAW"): theJet;
    pat::Jet const& uncorrJet = (*jetHandle)[k].correctedJet("Uncorrected");

    /******************Construct the HT/MHT from the jet collection***************************/
    if (theJet.pt() > htMinPt_) {
      if (fabs(theJet.eta()) < htMaxEta_) {
	
	//This will help compute a baseline HT and MHT which can later be corrected for jetID
	jetsumpt += theJet.pt();
	jetsume  += theJet.energy();
	jetsumpx += theJet.momentum().X();
	jetsumpy += theJet.momentum().Y();
	jetsumpz += theJet.momentum().Z();
	
	//if (doMCData_) {
	if(theJet.genJet()!= 0) {
	  gensumpt += theJet.genJet()->pt();
	  gensume  += theJet.genJet()->energy();
	  gensumpx += theJet.genJet()->momentum().X();
	  gensumpy += theJet.genJet()->momentum().Y();
	  gensumpz += theJet.genJet()->momentum().Z();
	//}
	}
      }
    }


    /******************Now collect all the Jet related variables***************************/
    if (theJet.pt() > jetMinPt_) {
      if (fabs(theJet.eta()) < jetMaxEta_) {

	//Get overlaps
	const reco::CandidatePtrVector & elecs = theJet.overlaps("electrons");
	const reco::CandidatePtrVector & taus  = theJet.overlaps("taus");
	const reco::CandidatePtrVector & muons = theJet.overlaps("muons");
	const reco::CandidatePtrVector & phots = theJet.overlaps("photons");

	int nElecOverlaps = 0;
	int nTauOverlaps  = 0;
	int nMuonOverlaps = 0;
	int nPhotOverlaps = 0;

	int elecOverlap = 0;
	int tauOverlap  = 0;
	int muonOverlap = 0;
	int photOverlap = 0;

	//electron overlaps
	for (size_t el = 0; el < elecs.size(); ++el) {
	  // try to cast into pat::Electron
	  const pat::Electron *electron = dynamic_cast<const pat::Electron *>(&*elecs[el]);
	  if (electron) {
	    ++nElecOverlaps;
	    double elecRelIso = (electron->trackIso()+electron->ecalIso()+electron->hcalIso())/electron->pt();
	    if (elecRelIso < electronIso_ && electron->pt() > electronPt_ ) {
	      if (electron->electronID("eidRobustLoose")>0.)
		elecOverlap = elecOverlap | 1<<0;
	      if (electron->electronID("eidRobustTight")>0.)
		elecOverlap = elecOverlap | 1<<1;
	      if (electron->electronID("eidLoose")>0.)
		elecOverlap = elecOverlap | 1<<2;
	      if (electron->electronID("eidTight")>0.)
		elecOverlap = elecOverlap | 1<<3;
	      if (electron->electronID("eidRobustHighEnergy")>0.)
		elecOverlap = elecOverlap | 1<<4;
	    }
	  }
	}
	
	//tau overlaps
	for (size_t ta = 0; ta < taus.size(); ++ta) {
	  // try to cast into pat::Tau
	  const pat::Tau *tau = dynamic_cast<const pat::Tau *>(&*taus[ta]);
	  if (tau) {
	    ++nTauOverlaps;
	    double tauRelIso = (tau->trackIso()+tau->ecalIso()+tau->hcalIso())/tau->pt();
	    if (tauRelIso < tauIso_ && tau->pt() > tauPt_ ) {
	      if (tau->tauID("againstElectron")>0.)
		tauOverlap = tauOverlap | 1<<0;
	      if (tau->tauID("againstMuon")>0.)
		tauOverlap = tauOverlap | 1<<1;
	      if (tau->tauID("byIsolation")>0.)
		tauOverlap = tauOverlap | 1<<2;
	      if (tau->tauID("byTaNCfrHalfPercent")>0.)
		tauOverlap = tauOverlap | 1<<3;
	      if (tau->tauID("byTaNCfrQuarterPercent")>0.)
		tauOverlap = tauOverlap | 1<<4;
	      if (tau->tauID("byTaNCfrTenthPercent")>0.)
		tauOverlap = tauOverlap | 1<<5;
	      if (tau->tauID("byTaNCfrOnePercent")>0.)
		tauOverlap = tauOverlap | 1<<6;
	    }
	  }
	}
	
	//muon overlaps
	for (size_t mu = 0; mu < muons.size(); ++mu) {
	  // try to cast into pat::Muon
	  const pat::Muon *muon = dynamic_cast<const pat::Muon *>(&*muons[mu]);
	  if (muon) {
	    ++nMuonOverlaps;
	    double muonRelIso = (muon->trackIso()+muon->ecalIso()+muon->hcalIso())/muon->pt();
	    if (muonRelIso < muonIso_ && muon->pt() > muonPt_ ) {
	      if (muon->muonID("GlobalMuonPromptTight") )
		  muonOverlap = muonOverlap | 1<<0;
	      if (muon->muonID("AllArbitrated"));
		  muonOverlap = muonOverlap | 1<<1;
	      if (muon->muonID("TrackerMuonArbitrated"));
		  muonOverlap = muonOverlap | 1<<2;
	      if (muon->muonID("TMLastStationLoose"));
		  muonOverlap = muonOverlap | 1<<3;
	      if (muon->muonID("TMLastStationTight"));
		  muonOverlap = muonOverlap | 1<<4;
	      if (muon->muonID("TM2DCompatibilityLoose"));
		  muonOverlap = muonOverlap | 1<<5;
	      if (muon->muonID("TM2DCompatibilityTight"));
		  muonOverlap = muonOverlap | 1<<6;
	      if (muon->muonID("TMOneStationLoose"));
		  muonOverlap = muonOverlap | 1<<7;
	      if (muon->muonID("TMOneStationTight"));
		  muonOverlap = muonOverlap | 1<<8;
	      if (muon->muonID("TMLastStationOptimizedLowPtLoose"));
		  muonOverlap = muonOverlap | 1<<9;
	      if (muon->muonID("TMLastStationOptimizedLowPtTight"));
		  muonOverlap = muonOverlap | 1<<10;
	      if (muon->muonID("GMTkChiCompatibility"));
		  muonOverlap = muonOverlap | 1<<11;
	      if (muon->muonID("GMStaChiCompatibility"));
		  muonOverlap = muonOverlap | 1<<12;
	      if (muon->muonID("GMTkKinkTight"));
		  muonOverlap = muonOverlap | 1<<13;
	      if (muon->muonID("TMLastStationAngLoose"));
		  muonOverlap = muonOverlap | 1<<14;
	      if (muon->muonID("TMLastStationAngTight"));
		  muonOverlap = muonOverlap | 1<<15;
	      if (muon->muonID("TMLastStationOptimizedBarrelLowPtLoose"));
		  muonOverlap = muonOverlap | 1<<16;
	      if (muon->muonID("TMLastStationOptimizedBarrelLowPtTight"));
		  muonOverlap = muonOverlap | 1<<17;
	    }
	  }
	}
	
	//photon overlaps
	for (size_t ph = 0; ph < phots.size(); ++ph) {
	  // try to cast into pat::Photon
	  const pat::Photon *photon = dynamic_cast<const pat::Photon *>(&*phots[ph]);
	  if (photon) {
	    ++nPhotOverlaps;
	    double photRelIso = (photon->trackIso()+photon->ecalIso()+photon->hcalIso())/photon->pt();
	    if (photRelIso < photonIso_ && photon->pt() > photonPt_ ) {
	      if (photon->photonID("PhotonCutBasedIDLoose")>0.)
		photOverlap = photOverlap | 1<<0;
	      if (photon->photonID("PhotonCutBasedIDTight")>0.)
		photOverlap = photOverlap | 1<<1;
	    }
	  }
	}
	
	//map_s_vi_JetNOverlaps["electrons"]->push_back(nElecOverlaps);
	//map_s_vi_JetOverlaps["electrons"] ->push_back(elecOverlap);
	//map_s_vi_JetNOverlaps["taus"]->push_back(nTauOverlaps);
	//map_s_vi_JetOverlaps["taus"] ->push_back(tauOverlap);
	//map_s_vi_JetNOverlaps["muons"]->push_back(nMuonOverlaps);
	//map_s_vi_JetOverlaps["muons"] ->push_back(muonOverlap);
	//map_s_vi_JetNOverlaps["photons"]->push_back(nPhotOverlaps);
	//map_s_vi_JetOverlaps["photons"] ->push_back(photOverlap);

	vi_JetElectronNOverlaps->push_back(nElecOverlaps);
	vi_JetElectronOverlaps ->push_back(elecOverlap);
	vi_JetMuonNOverlaps    ->push_back(nTauOverlaps);
	vi_JetMuonOverlaps     ->push_back(tauOverlap);
	vi_JetTauNOverlaps     ->push_back(nMuonOverlaps);
	vi_JetTauOverlaps      ->push_back(muonOverlap);
	vi_JetPhotonNOverlaps  ->push_back(nPhotOverlaps);
	vi_JetPhotonOverlaps   ->push_back(photOverlap);

	//JEC uncertainties  
	//      if (jet.isJet()) {
	jecUnc->setJetEta(theJet.eta());
	jecUnc->setJetPt(theJet.pt()); //corrected pT
        const float uncplus = jecUnc->getUncertainty(true);
        vd_JECUncPlus->push_back(uncplus);

        //due to weird behavior of this JetUncertainty class, need to reset the eta and pt
        jecUnc->setJetEta(theJet.eta());
        jecUnc->setJetPt(theJet.pt()); //corrected pT
        const float uncminus = jecUnc->getUncertainty(false);
	vd_JECUncMinus->push_back(uncminus);
	
	//if (uncorrJet.pt() > jetMinPt_) {
	//  if (fabs(uncorrJet.eta()) < jetMaxEta_) {

	if (debug_>5) std::cout<<"\n\nPassed minimum jet requirements\n\n"<<std::endl;
	

	if (theJet.isCaloJet()) {
	  
	  if (debug_>5) std::cout<<"\n\nGetting track information from jets\n\n"<<std::endl;
	  const reco::TrackRefVector & mrTracksInJet = theJet.associatedTracks();
	  
	  vd_JetTrackPt         ->push_back(0);
	  vd_JetTrackPhi        ->push_back(0);
	  vd_JetTrackPhiWeighted->push_back(0);
	  vi_JetTrackNo         ->push_back(0);
	  
	  float JetPhi = theJet.phi();
	  
	  for (reco::TrackRefVector::iterator aIter = mrTracksInJet.begin();aIter!= mrTracksInJet.end();aIter++)
	    {
	      vd_JetTrackPt->at(mjet) += (*aIter)->pt();
	      float myPhi = (*aIter)->phi();
	      if( JetPhi > 2. ) {
		if(myPhi<0) myPhi = myPhi + 2*TMath::Pi();
	      }
	      if( JetPhi < -2. ) {
		if(myPhi>0) myPhi = myPhi - 2*TMath::Pi();
	      }
	      vd_JetTrackPhiWeighted->at(mjet) += (*aIter)->pt()*myPhi;
	      vd_JetTrackPhi->at(mjet)         += myPhi;
	      vi_JetTrackNo->at(mjet)++;
	      
	    }
	  
	  vd_JetTrackPhiWeighted->at(mjet) = vd_JetTrackPhiWeighted->at(mjet)/vd_JetTrackPt->at(mjet);
	  vd_JetTrackPhi->at(mjet)         = vd_JetTrackPhi->at(mjet)/float(vi_JetTrackNo->at(mjet));
	}

	if (debug_>5) std::cout<<"\n\nGetting corrections for calo jets\n\n"<<std::endl;

	//if (useCaloJets_) {
	if (theJet.jecSetsAvailable()) {
	  vd_correctionFactorUnc->push_back(uncorrJet.jecFactor("Uncorrected"));
	  vd_correctionFactorL1 ->push_back(uncorrJet.jecFactor("L1Offset"))   ;
	  vd_correctionFactorL2 ->push_back(uncorrJet.jecFactor("L2Relative")) ;
	  vd_correctionFactorL3 ->push_back(uncorrJet.jecFactor("L3Absolute")) ;
	  if (corrLevel=="L2L3Residual")
	    vd_correctionFactorL2L3->push_back(uncorrJet.jecFactor("L2L3Residual"));
	  vd_correctionFactorL5uds->push_back(uncorrJet.jecFactor("L5Flavor", "gluon"));;
	  vd_correctionFactorL5c  ->push_back(uncorrJet.jecFactor("L5Flavor", "uds"));  ;
	  vd_correctionFactorL5b  ->push_back(uncorrJet.jecFactor("L5Flavor", "charm"));;
	  vd_correctionFactorL5glu->push_back(uncorrJet.jecFactor("L5Flavor", "bottom"));
	  vd_correctionFactorL7uds->push_back(uncorrJet.jecFactor("L7Parton", "gluon"));;
	  vd_correctionFactorL7c  ->push_back(uncorrJet.jecFactor("L7Parton", "uds"));  ;
	  vd_correctionFactorL7b  ->push_back(uncorrJet.jecFactor("L7Parton", "charm"));;
	  vd_correctionFactorL7glu->push_back(uncorrJet.jecFactor("L7Parton", "bottom"));

	  //map_s_vd_correctionFactor["raw"]->push_back(uncorrJet.jecFactor("Uncorrected"));
	  //map_s_vd_correctionFactor["off"]->push_back(uncorrJet.jecFactor("L1Offset"));
	  //map_s_vd_correctionFactor["rel"]->push_back(uncorrJet.jecFactor("L2Relative"));
	  //map_s_vd_correctionFactor["abs"]->push_back(uncorrJet.jecFactor("L3Absolute"));
	  //if (corrLevel=="L2L3Residual")
	  //  map_s_vd_correctionFactor["residual"]->push_back(uncorrJet.jecFactor("L2L3Residual"));
	  ////map_s_vd_correctionFactor["emf"]->push_back(uncorrJet.jecFactor("L4Emf"));
	  //map_s_vd_correctionFactor["had:glu"]->push_back(uncorrJet.jecFactor("L5Flavor", "gluon"));
	  //map_s_vd_correctionFactor["had:uds"]->push_back(uncorrJet.jecFactor("L5Flavor", "uds"));
	  //map_s_vd_correctionFactor["had:c"]  ->push_back(uncorrJet.jecFactor("L5Flavor", "charm"));
	  //map_s_vd_correctionFactor["had:b"]  ->push_back(uncorrJet.jecFactor("L5Flavor", "bottom"));
	  ////map_s_vd_correctionFactor["ue:glu"]->push_back(uncorrJet.jecFactor("L6UE", "gluon"));
	  ////map_s_vd_correctionFactor["ue:uds"]->push_back(uncorrJet.jecFactor("L6UE", "uds"));
	  ////map_s_vd_correctionFactor["ue:c"]->push_back(uncorrJet.jecFactor("L6UE", "c"));
	  ////map_s_vd_correctionFactor["ue:b"]->push_back(uncorrJet.jecFactor("L6UE", "b"));
	  //map_s_vd_correctionFactor["part:glu"]->push_back(uncorrJet.jecFactor("L7Parton", "gluon"));
	  //map_s_vd_correctionFactor["part:uds"]->push_back(uncorrJet.jecFactor("L7Parton", "uds"));
	  //map_s_vd_correctionFactor["part:c"]  ->push_back(uncorrJet.jecFactor("L7Parton", "charm"));
	  //map_s_vd_correctionFactor["part:b"]  ->push_back(uncorrJet.jecFactor("L7Parton", "bottom"));
	}

	else {
	  if (debug_>5) std::cout<<"\n\nGetting corrections for other jets\n\n"<<std::endl;
	  vd_correctionFactorUnc->push_back(1);
	  vd_correctionFactorL1 ->push_back(1);
	  vd_correctionFactorL2 ->push_back(1);
	  vd_correctionFactorL3 ->push_back(1);
	  if (corrLevel=="L2L3Residual")
	    vd_correctionFactorL2L3->push_back(1);
	  vd_correctionFactorL5uds->push_back(1);
	  vd_correctionFactorL5c  ->push_back(1);
	  vd_correctionFactorL5b  ->push_back(1);
	  vd_correctionFactorL5glu->push_back(1);

	  vd_correctionFactorL7uds->push_back(1);
	  vd_correctionFactorL7c  ->push_back(1);
	  vd_correctionFactorL7b  ->push_back(1);
	  vd_correctionFactorL7glu->push_back(1);

	  //map_s_vd_correctionFactor["raw"]->push_back(1);
	  //map_s_vd_correctionFactor["off"]->push_back(1);
	  //map_s_vd_correctionFactor["rel"]->push_back(1);
	  //map_s_vd_correctionFactor["abs"]->push_back(1);
	  //if (corrLevel=="L2L3Residual")
	  //  map_s_vd_correctionFactor["residual"]->push_back(1);
	  ////map_s_vd_correctionFactor["emf"]->push_back(1);
	  //map_s_vd_correctionFactor["had:glu"]->push_back(1);
	  //map_s_vd_correctionFactor["had:uds"]->push_back(1);
	  //map_s_vd_correctionFactor["had:c"]->push_back(1);
	  //map_s_vd_correctionFactor["had:b"]->push_back(1);
	  ////map_s_vd_correctionFactor["ue:glu"]->push_back(1);
	  ////map_s_vd_correctionFactor["ue:uds"]->push_back(1);
	  ////map_s_vd_correctionFactor["ue:c"]->push_back(1);
	  ////map_s_vd_correctionFactor["ue:b"]->push_back(1);
	  //map_s_vd_correctionFactor["part:glu"]->push_back(1);
	  //map_s_vd_correctionFactor["part:uds"]->push_back(1);
	  //map_s_vd_correctionFactor["part:c"]->push_back(1);
	  //map_s_vd_correctionFactor["part:b"]->push_back(1);
	}
	
	v_JetP4->push_back(theJet.p4());
	v_RawJetP4->push_back(uncorrJet.p4());

	//Jet eta/phi moments
	vd_JetEtaEtaMoment->push_back(theJet.etaetaMoment());
	vd_JetEtaPhiMoment->push_back(theJet.etaphiMoment());
	vd_JetPhiPhiMoment->push_back(theJet.phiphiMoment());

	//MYJETID thejetid;
	//
	//thejetid.JetCharge = theJet.jetCharge();
	//thejetid.JetNConst = theJet.nConstituents();
	vd_JetCharge->push_back(theJet.jetCharge());
	vi_JetNConst->push_back(theJet.nConstituents());

	//Calo jet type specific
	if (debug_>5) 
	  std::cout<<"\n\nSetting up jetid\n\n"<<std::endl;
	if (theJet.isCaloJet() || theJet.isJPTJet()) {
	  pat::strbitset retmin;
	  pat::strbitset retloo;
	  pat::strbitset rettig;

	  JetIDSelectionFunctor jetIDMinimal( JetIDSelectionFunctor::PURE09,
					      JetIDSelectionFunctor::MINIMAL );
	  
	  JetIDSelectionFunctor jetIDLoose( JetIDSelectionFunctor::PURE09,
	  				    JetIDSelectionFunctor::LOOSE );
	  
	  JetIDSelectionFunctor jetIDTight( JetIDSelectionFunctor::PURE09,
	  				    JetIDSelectionFunctor::TIGHT );
	  
	  retmin = jetIDMinimal.getBitTemplate();
	  retloo = jetIDLoose.getBitTemplate();
	  rettig = jetIDTight.getBitTemplate();
	  
	  //retmin.set(false);
	  //thejetid.JetIDMinimal = jetIDMinimal(theJet, retmin);
	  //retloo.set(false);
	  //thejetid.JetIDLoose = jetIDLoose(theJet, retloo);
	  //rettig.set(false);
	  //thejetid.JetIDTight = jetIDTight(theJet, rettig);
	  //
	  //thejetid.JetFem  = theJet.emEnergyFraction();
	  //thejetid.JetFhad = theJet.energyFractionHadronic();
	  //thejetid.JetN90  = theJet.jetID().n90Hits;
	  //thejetid.JetfHPD = theJet.jetID().fHPD;
	  //thejetid.JetfRBX = theJet.jetID().fRBX;
	  
	  retmin.set(false);
	  int jetIDMin = jetIDMinimal(theJet, retmin);
	  retloo.set(false);
	  int jetIDLoo = jetIDLoose(theJet, retloo);
	  rettig.set(false);
	  int jetIDTig = jetIDTight(theJet, rettig);

	  vb_JetIDMinimal->push_back(jetIDMin);
	  vb_JetIDLoose  ->push_back(jetIDLoo);
	  vb_JetIDTight  ->push_back(jetIDTig);
	  
	  vd_JetEFrac_em ->push_back(theJet.emEnergyFraction());
	  vd_JetEFrac_had->push_back(theJet.energyFractionHadronic());
	  
	  vd_JetN90 ->push_back(theJet.jetID().n90Hits);
	  vd_JetfHPD->push_back(theJet.jetID().fHPD);
	  vd_JetfRBX->push_back(theJet.jetID().fRBX);
	}

	if (theJet.isJPTJet() ) {
	  vd_JetElectronMult->push_back(theJet.elecMultiplicity());
	}
	if (theJet.isJPTJet() || theJet.isPFJet()) {
	  //thejetid.JetChargedFem  = theJet.chargedEmEnergyFraction();
	  //thejetid.JetNeutralFem  = theJet.neutralEmEnergyFraction();
	  //thejetid.JetChargedFhad = theJet.chargedHadronEnergyFraction();
	  //thejetid.JetNeutralFhad = theJet.neutralHadronEnergyFraction();
	  //thejetid.JetChargedMult = theJet.chargedMultiplicity();
	  //thejetid.JetMuonMult    = theJet.muonMultiplicity();
	  //thejetid.JetFem  = theJet.neutralEmEnergyFraction()+
	  //  theJet.chargedEmEnergyFraction();
	  //thejetid.JetFhad = theJet.neutralHadronEnergyFraction()+
	  //  theJet.chargedHadronEnergyFraction();
	  
	  vd_JetChargedMult->push_back(theJet.chargedMultiplicity());
	  vd_JetMuonMult   ->push_back(theJet.muonMultiplicity());
	  
	  vd_JetChargedFrac_em ->push_back(theJet.chargedEmEnergyFraction());
	  vd_JetNeutralFrac_em ->push_back(theJet.neutralEmEnergyFraction());
	  vd_JetChargedFrac_had->push_back(theJet.chargedHadronEnergyFraction());
	  vd_JetNeutralFrac_had->push_back(theJet.neutralHadronEnergyFraction());
	  
	  vd_JetEFrac_em ->push_back(theJet.neutralEmEnergyFraction()+
	  		       theJet.chargedEmEnergyFraction());
	  vd_JetEFrac_had->push_back(theJet.neutralHadronEnergyFraction()+
	  		       theJet.chargedHadronEnergyFraction());

	  vd_JetChargedEn_em ->push_back(theJet.chargedEmEnergy());
	  vd_JetNeutralEn_em ->push_back(theJet.neutralEmEnergy());
	  vd_JetChargedEn_had->push_back(theJet.chargedHadronEnergy());
	  vd_JetNeutralEn_had->push_back(theJet.neutralHadronEnergy());
	  
	}

	//PF jet type specific variables
	if (theJet.isPFJet()) {

	  pat::strbitset retloo;
	  pat::strbitset rettig;

	  PFJetIDSelectionFunctor jetIDLoose( PFJetIDSelectionFunctor::FIRSTDATA,
	  				      PFJetIDSelectionFunctor::LOOSE );
	  
	  PFJetIDSelectionFunctor jetIDTight( PFJetIDSelectionFunctor::FIRSTDATA,
	  				      PFJetIDSelectionFunctor::TIGHT );
	  
	  retloo = jetIDLoose.getBitTemplate();
	  rettig = jetIDTight.getBitTemplate();
	
	  retloo.set(false);
	  int jetIDLoo = jetIDLoose(theJet, retloo);
	  rettig.set(false);
	  int jetIDTig = jetIDTight(theJet, rettig);

	  vb_JetIDLoose  ->push_back(jetIDLoo);
	  vb_JetIDTight  ->push_back(jetIDTig);
	  

	  vd_JetHFMult_had     ->push_back(theJet.HFHadronMultiplicity());
	  vd_JetHFMult_em      ->push_back(theJet.HFEMMultiplicity());
	  vd_JetChargedMult_had->push_back(theJet.chargedHadronMultiplicity());
	  vd_JetNeutralMult_had->push_back(theJet.neutralHadronMultiplicity());
	  vd_JetPhotonMult     ->push_back(theJet.photonMultiplicity());
	  vd_JetElectronMult   ->push_back(theJet.electronMultiplicity());
	  vd_JetNeutralMult    ->push_back(theJet.neutralMultiplicity());
	  
	  vd_JetHFFrac_em       ->push_back(theJet.HFEMEnergyFraction());
	  vd_JetHFFrac_had      ->push_back(theJet.HFHadronEnergyFraction());
	  vd_JetEFrac_muon      ->push_back(theJet.muonEnergyFraction());
	  vd_JetChargedFrac_muon->push_back(theJet.chargedMuEnergyFraction());
	  vd_JetEFrac_electron  ->push_back(theJet.electronEnergy() / theJet.energy());
	  vd_JetEFrac_photon    ->push_back(theJet.photonEnergyFraction());

	  vd_JetHFEn_em       ->push_back(theJet.HFEMEnergy());
	  vd_JetHFEn_had      ->push_back(theJet.HFHadronEnergy());
	  vd_JetEn_muon       ->push_back(theJet.muonEnergy());
	  vd_JetChargedEn_muon->push_back(theJet.chargedMuEnergy());
	  vd_JetEn_electron   ->push_back(theJet.electronEnergy());
	  vd_JetEn_photon     ->push_back(theJet.photonEnergy());

 	}
	
	//vjid_JetID->push_back(thejetid);
	//get jet flavour information
	vi_JetPartonFlavour  ->push_back(theJet.partonFlavour());

	////get b-tagging information

	vd_JetBTag_TCHE          ->push_back(theJet.bDiscriminator("trackCountingHighEffBJetTags"));
	vd_JetBTag_TCHP          ->push_back(theJet.bDiscriminator("trackCountingHighPurBJetTags"));
	vd_JetBTag_jetProb       ->push_back(theJet.bDiscriminator("jetProbabilityBJetTags"));
	vd_JetBTag_jetBProb      ->push_back(theJet.bDiscriminator("jetBProbabilityBJetTags"));
	vd_JetBTag_SSVHE         ->push_back(theJet.bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
	vd_JetBTag_SSVHP         ->push_back(theJet.bDiscriminator("simpleSecondaryVertexHighPurBJetTags"));
	vd_JetBTag_CSV           ->push_back(theJet.bDiscriminator("combinedSecondaryVertexBJetTags"));
	vd_JetBTag_CSVMVA        ->push_back(theJet.bDiscriminator("combinedSecondaryVertexMVABJetTags"));
	vd_JetBTag_SoftLepton    ->push_back(theJet.bDiscriminator("softMuonBJetTags"));
	vd_JetBTag_SoftLeptonByIP->push_back(theJet.bDiscriminator("softMuonByIP3dBJetTags"));
	vd_JetBTag_SoftLeptonByPt->push_back(theJet.bDiscriminator("softMuonByPtBJetTags"));


	//Get gen information for jet	
	if(theJet.genJet()!= 0) {
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(theJet.genJet()->px(),theJet.genJet()->py(),theJet.genJet()->pz(),theJet.genJet()->energy());
	  v_GenJetP4->push_back(genp4);
	}
	else {
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	  v_GenJetP4->push_back(genp4);
	}

	if(theJet.genParton() != 0){
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(theJet.genParton()->px(),theJet.genParton()->py(),theJet.genParton()->pz(),theJet.genParton()->energy());
	  v_JetPartonP4->push_back(genp4);
	  vi_JetPartonId    ->push_back(theJet.genParton()->pdgId());
	  vi_JetPartonStatus->push_back(theJet.genParton()->status());
	  vi_JetPartonMother->push_back(theJet.genParton()->mother()->pdgId());
	  vi_JetPartonMotherStatus->push_back(theJet.genParton()->mother()->status());
	}
	else{
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	  v_JetPartonP4->push_back(genp4);
	  vi_JetPartonId    ->push_back(999.);
	  vi_JetPartonStatus->push_back(999.);
	  vi_JetPartonMother->push_back(999.);
	  vi_JetPartonMotherStatus->push_back(999.);
	}
	++mjet;
      }
    }
  }
  
  i_NJets  =  mjet;

  d_Ht     =  jetsumpt;
  MHtP4->SetPxPyPzE(-jetsumpx, -jetsumpy, -jetsumpz, -jetsume);
  
  d_GenHt  =  gensumpt;
  GenMHtP4->SetPxPyPzE(-gensumpx, -gensumpy, -gensumpz, -gensume);
  
  if (vb_JetIDLoose->size() > 1)
    if (vb_JetIDLoose->at(0) && vb_JetIDLoose->at(1))
      if (v_JetP4->at(1).pt()> 50)
	if (fabs(v_JetP4->at(0).eta()) < 3.0 && fabs(v_JetP4->at(1).eta()) < 3.0)
	  bool_JetPreselection = true;

  jet_result = bool_JetPreselection;
  if (debug_ > 5)
    std::cout<<"Done analyzing all the jets"<<std::endl;
  return jet_result;
}


//________________________________________________________________________________________
void JetAnalyzerPAT::bookTTree(TTree* mJetData) {

  std::ostringstream variables; // Container for all variables

  mJetData->Branch(prefix_+"NJets",   &i_NJets,   prefix_+"NJets/I");  
  //mJetData->Branch(prefix_+"JetMHt",  &JetMHt, "MHt/D");
  mJetData->Branch(prefix_+"Ht",    &d_Ht,      prefix_+"Ht/D");
  mJetData->Branch(prefix_+"MHtP4", &(*MHtP4.get() ));
  
  mJetData->Branch(prefix_+"JetP4",     &(*v_JetP4   .get() ) );
  mJetData->Branch(prefix_+"RawJetP4",  &(*v_RawJetP4.get() ) );
  
  mJetData->Branch(prefix_+"JetEtaEtaMoment",  &(*vd_JetEtaEtaMoment.get() ) );
  mJetData->Branch(prefix_+"JetEtaPhiMoment",  &(*vd_JetEtaPhiMoment.get() ) );
  mJetData->Branch(prefix_+"JetPhiPhiMoment",  &(*vd_JetPhiPhiMoment.get() ) );
  //mJetData->Branch(prefix_+"JetHemi", &(*vi_JetHemi.get() ) );
  //mJetData->Branch(prefix_+"JetCorrFactor",   &(*map_s_vd_correctionFactor.get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorUnc",   &(*vd_correctionFactorUnc  .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL1",    &(*vd_correctionFactorL1   .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL2",    &(*vd_correctionFactorL2   .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL3",    &(*vd_correctionFactorL3   .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL2L3",  &(*vd_correctionFactorL2L3 .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL5uds", &(*vd_correctionFactorL5uds.get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL5c",   &(*vd_correctionFactorL5c  .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL5b",   &(*vd_correctionFactorL5b  .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL5glu", &(*vd_correctionFactorL5glu.get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL7uds", &(*vd_correctionFactorL7uds.get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL7c",   &(*vd_correctionFactorL7c  .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL7b",   &(*vd_correctionFactorL7b  .get() ) );
  mJetData->Branch(prefix_+"JetCorrFactorL7glu", &(*vd_correctionFactorL7glu.get() ) );
  //mJetData->Branch(prefix_+"JetOverlaps",     &(*map_s_vi_JetOverlaps.get() ) );
  //mJetData->Branch(prefix_+"JetNOverlaps",    &(*map_s_vi_JetNOverlaps.get() ) );
  mJetData->Branch(prefix_+"ElectronOverlaps",  &(*vi_JetElectronOverlaps.get() ) );
  mJetData->Branch(prefix_+"ElectronNOverlaps", &(*vi_JetElectronNOverlaps.get() ) );
  mJetData->Branch(prefix_+"MuonOverlaps",      &(*vi_JetMuonOverlaps.get() ) );
  mJetData->Branch(prefix_+"MuonNOverlaps",     &(*vi_JetMuonNOverlaps.get() ) );
  mJetData->Branch(prefix_+"TauOverlaps",       &(*vi_JetTauOverlaps.get() ) );
  mJetData->Branch(prefix_+"TauNOverlaps",      &(*vi_JetTauNOverlaps.get() ) );
  mJetData->Branch(prefix_+"PhotonOverlaps",    &(*vi_JetPhotonOverlaps.get() ) );
  mJetData->Branch(prefix_+"PhotonNOverlaps",   &(*vi_JetPhotonNOverlaps.get() ) );

  mJetData->Branch(prefix_+"JetPreselection",         &bool_JetPreselection, prefix_+"JetPreselection/O");

  mJetData->Branch(prefix_+"JECUncPlus",  &(*vd_JECUncPlus.get() ) );
  mJetData->Branch(prefix_+"JECUncMinus", &(*vd_JECUncMinus.get() ) );

  
  //b-tagging information
  //mJetData->Branch(prefix_+"JetBTAGINFO",            &(*vbtag_JetBtag.get() ) );
  mJetData->Branch(prefix_+"JetBTag_TCHE",            &(*vd_JetBTag_TCHE.get() ) );
  mJetData->Branch(prefix_+"JetBTag_TCHP",            &(*vd_JetBTag_TCHP.get() ) );
  mJetData->Branch(prefix_+"JetBTag_jetProb",         &(*vd_JetBTag_jetProb.get() ) );
  mJetData->Branch(prefix_+"JetBTag_jetBProb",        &(*vd_JetBTag_jetBProb.get() ) );
  mJetData->Branch(prefix_+"JetBTag_SSVHE",           &(*vd_JetBTag_SSVHE.get() ) );
  mJetData->Branch(prefix_+"JetBTag_SSVHP",           &(*vd_JetBTag_SSVHP.get() ) );
  mJetData->Branch(prefix_+"JetBTag_CSV",             &(*vd_JetBTag_CSV.get() ) );
  mJetData->Branch(prefix_+"JetBTag_CSVMVA",          &(*vd_JetBTag_CSVMVA.get() ) );
  mJetData->Branch(prefix_+"JetBTag_SoftLepton",      &(*vd_JetBTag_SoftLepton.get() ) );
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByIP",  &(*vd_JetBTag_SoftLeptonByIP.get() ) );
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByPt",  &(*vd_JetBTag_SoftLeptonByPt.get() ) );
  

  //information about associated gen jets
  //mJetData->Branch(prefix_+"GenMHt",  &GenMHt);
  mJetData->Branch(prefix_+"GenHt",    &d_GenHt,     prefix_+"GenHt/D");
  mJetData->Branch(prefix_+"GenMHtP4", &(*GenMHtP4.get() ) );
  //  
  mJetData->Branch(prefix_+"GenJetP4", &(*v_GenJetP4.get() ) );
  //
  //information about associated partons
  mJetData->Branch(prefix_+"JetPartonP4",      &(*v_JetPartonP4.get() ) );
  mJetData->Branch(prefix_+"JetPartonId",      &(*vi_JetPartonId.get() ) );
  mJetData->Branch(prefix_+"JetPartonStatus",  &(*vi_JetPartonStatus.get() ) );
  mJetData->Branch(prefix_+"JetPartonMother",  &(*vi_JetPartonMother.get() ) );
  mJetData->Branch(prefix_+"JetPartonMotherStatus", &(*vi_JetPartonMotherStatus.get() ) );
  mJetData->Branch(prefix_+"JetPartonFlavour",      &(*vi_JetPartonFlavour.get() ) );
    
  
  //mJetData->Branch(prefix_+"JetIDInfo",    &(*vjid_JetID.get() ) );
  mJetData->Branch(prefix_+"JetEFrac_em",  &(*vd_JetEFrac_em.get() ) );
  mJetData->Branch(prefix_+"JetEFrac_had", &(*vd_JetEFrac_had.get() ) );
  mJetData->Branch(prefix_+"JetCharge",    &(*vd_JetCharge.get() ) );
  mJetData->Branch(prefix_+"JetNConst",    &(*vi_JetNConst.get() ) );
  mJetData->Branch(prefix_+"JetIDMinimal", &(*vb_JetIDMinimal.get() ) );
  mJetData->Branch(prefix_+"JetIDLoose",   &(*vb_JetIDLoose.get() ) );
  mJetData->Branch(prefix_+"JetIDTight",   &(*vb_JetIDTight.get() ) );
  
  if (useJPTJets_ ) {
    if (debug_ > 5) std::cout<<"Saving JPT specific information"<<std::endl;
  }
  
  if (useJPTJets_ || usePFJets_) {
    if (debug_ > 5) std::cout<<"Saving JPT/PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetChargedFrac_em",  &(*vd_JetChargedFrac_em.get() ) );
    mJetData->Branch(prefix_+"JetNeutralFrac_em",  &(*vd_JetNeutralFrac_em.get() ) );
    mJetData->Branch(prefix_+"JetChargedFrac_had", &(*vd_JetChargedFrac_had.get() ) );
    mJetData->Branch(prefix_+"JetNeutralFrac_had", &(*vd_JetNeutralFrac_had.get() ) );
    mJetData->Branch(prefix_+"JetChargedMult",     &(*vd_JetChargedMult.get() ) );
    mJetData->Branch(prefix_+"JetElectronMulti",   &(*vd_JetElectronMult.get() ) );
    mJetData->Branch(prefix_+"JetMuonMulti",       &(*vd_JetMuonMult.get() ) );
  }
  
  if (usePFJets_) {
    if (debug_ > 5) std::cout<<"Saving PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetHFFrac_em",        &(*vd_JetHFFrac_em.get() ) );
    mJetData->Branch(prefix_+"JetHFFrac_had",       &(*vd_JetHFFrac_had.get() ) );
    mJetData->Branch(prefix_+"JetEFrac_muon",       &(*vd_JetEFrac_muon.get() ) );
    mJetData->Branch(prefix_+"JetChargedFrac_muon", &(*vd_JetChargedFrac_muon.get() ) );
    mJetData->Branch(prefix_+"JetEFrac_electron",   &(*vd_JetEFrac_electron.get() ) );
    mJetData->Branch(prefix_+"JetEFrac_photon",     &(*vd_JetEFrac_photon.get() ) );
  
    mJetData->Branch(prefix_+"JetHFEn_em",        &(*vd_JetHFEn_em.get() ) );
    mJetData->Branch(prefix_+"JetHFEn_had",       &(*vd_JetHFEn_had.get() ) );
    mJetData->Branch(prefix_+"JetEn_muon",       &(*vd_JetEn_muon.get() ) );
    mJetData->Branch(prefix_+"JetChargedEn_muon", &(*vd_JetChargedEn_muon.get() ) );
    mJetData->Branch(prefix_+"JetEn_electron",    &(*vd_JetEn_electron.get() ) );
    mJetData->Branch(prefix_+"JetEn_photon",      &(*vd_JetEn_photon.get() ) );
  
    mJetData->Branch(prefix_+"JetHFMult_em",       &(*vd_JetHFMult_em.get() ) );
    mJetData->Branch(prefix_+"JetHFMult_had",      &(*vd_JetHFMult_had.get() ) );
    mJetData->Branch(prefix_+"JetChargedMult_had", &(*vd_JetChargedMult_had.get() ) );
    mJetData->Branch(prefix_+"JetNeutralMult_had", &(*vd_JetNeutralMult_had.get() ) );
    mJetData->Branch(prefix_+"JetPhotonMult",      &(*vd_JetPhotonMult.get() ) );
    mJetData->Branch(prefix_+"JetNeutralMult",     &(*vd_JetNeutralMult.get() ) );
  }
  
  if (useCaloJets_ || useJPTJets_) {
    //if (debug_ > 5) std::cout<<"Saving Calo/JPT specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetfHPD", &(*vd_JetfHPD.get() ) );
    mJetData->Branch(prefix_+"JetfRBX", &(*vd_JetfRBX.get() ) );
    mJetData->Branch(prefix_+"Jetn90",  &(*vd_JetN90.get() ) );
  
    //information about associated tracks
    mJetData->Branch(prefix_+"JetTrackPt",          &(*vd_JetTrackPt.get() ) );
    mJetData->Branch(prefix_+"JetTrackPhi",         &(*vd_JetTrackPhi.get() ) );
    mJetData->Branch(prefix_+"JetTrackPhiWeighted", &(*vd_JetTrackPhiWeighted.get() ) );
    mJetData->Branch(prefix_+"JetTrackNo",          &(*vi_JetTrackNo.get() ) );
  
  }
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_EDM_PLUGIN(JetAnalyzerPAT);

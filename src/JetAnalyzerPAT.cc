
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
// $Id: JetAnalyzerPAT.cc,v 1.9 2010/07/08 03:22:30 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/JetAnalyzerPAT.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> LorentzV;
typedef std::vector<LorentzV>                                   LorentzVs;

#pragma link C++ typedef LorentzV;
#pragma link C++ typedef LorentzVs;

#pragma link C++ class std::map <std::string, std::vector<float> >+; 
#pragma link C++ class std::pair<std::string, std::vector<float> >; 
#pragma link C++ class std::pair<const std::string, std::vector<float> >; 
#pragma link C++ class std::vector< <reco::Candidate::LorentzVector> >+; 

#pragma link C++ class LorentzV+; 
#pragma link C++ class LorentzVs+; 

#endif
//________________________________________________________________________________________
JetAnalyzerPAT::JetAnalyzerPAT(const edm::ParameterSet& jetParams, TTree* tmpAllData)
{ 
  mJetData = tmpAllData;

  minNJets_  = 1;

  debug_     = jetParams.getUntrackedParameter<int>("debugJets",0);
  prefix_    = jetParams.getUntrackedParameter<std::string>("prefixJets","Calo");
  jetMaxEta_ = jetParams.getUntrackedParameter<double >("jetMaxEta",5.);
  jetMinPt_  = jetParams.getUntrackedParameter<double >("jetMinPt", 30.);
  jetMaxEMF_ = jetParams.getUntrackedParameter<double >("jetMaxEMF",0.99);
  jetMinEMF_ = jetParams.getUntrackedParameter<double >("jetMinEMF",0.01);

  htMaxEta_ = jetParams.getUntrackedParameter<double >("htMaxEta",jetMaxEta_);
  htMinPt_  = jetParams.getUntrackedParameter<double >("htMinPt", jetMinPt_);

  //Individual jet requirements
  //selJetMaxEta_ = jetParams.getUntrackedParameter<std::vector<double > >("selJetMaxEta");
  //selJetMinPt_  = jetParams.getUntrackedParameter<std::vector<double > >("selJetMinPt");
  //selJetMaxEMF_ = jetParams.getUntrackedParameter<std::vector<double > >("selJetMaxEMF");
  //selJetMinEMF_ = jetParams.getUntrackedParameter<std::vector<double > >("selJetMinEMF");
  //
  //if (debug_) {
  //  std::cout<<"size of dijet vector "<<selJetMaxEta_.size()<<std::endl;
  //  for (int nj = 0; nj < int(selJetMaxEta_.size()); ++nj) {
  //    printf("jet %2d, eta max %2.2f, min pt %2.2f, max emf %2.2f, min emf %2.2f\n",nj,selJetMaxEta_.at(nj), selJetMinPt_.at(nj),selJetMaxEMF_.at(nj), selJetMinEMF_.at(nj));
  //  }
  //}
  
  doMCData_     = jetParams.getUntrackedParameter<bool>("doMCJets",false);
  if (doMCData_) 
    genJetTag_    = jetParams.getUntrackedParameter<edm::InputTag>("genJetTag");
 
  // get the data tags
  usePFJets_    = jetParams.getUntrackedParameter<bool>("usePFJets",   false);
  useJPTJets_   = jetParams.getUntrackedParameter<bool>("useJPTJets",  false);
  useCaloJets_  = jetParams.getUntrackedParameter<bool>("useCaloJets", false);
  useTrackJets_ = jetParams.getUntrackedParameter<bool>("useTrackJets",false);

  jetTag_     = jetParams.getUntrackedParameter<edm::InputTag>("jetTag");

  //calo jet id
  jetMaxHPD_ = jetParams.getUntrackedParameter<double>("jetMaxHPD",1.01);
  jetMinHPD_ = jetParams.getUntrackedParameter<double>("jetMinHPD",0.00);
  jetMaxRBX_ = jetParams.getUntrackedParameter<double>("jetMaxRBX",1.01);
  jetMinRBX_ = jetParams.getUntrackedParameter<double>("jetMinRBX",0.00);
  jetMaxN90_ = jetParams.getUntrackedParameter<double>("jetMaxN90",100.);
  jetMinN90_ = jetParams.getUntrackedParameter<double>("jetMinN90",1.);

  //PF jet id
  jetMaxCHF_ = jetParams.getUntrackedParameter<double>("jetMaxCHF",1.01);
  jetMinCHF_ = jetParams.getUntrackedParameter<double>("jetMinCHF",0.00);
  jetMaxNHF_ = jetParams.getUntrackedParameter<double>("jetMaxNHF",1.01);
  jetMinNHF_ = jetParams.getUntrackedParameter<double>("jetMinNHF",0.00);
  jetMaxCEF_ = jetParams.getUntrackedParameter<double>("jetMaxCEF",1.01);
  jetMinCEF_ = jetParams.getUntrackedParameter<double>("jetMinCEF",0.00);
  jetMaxNEF_ = jetParams.getUntrackedParameter<double>("jetMaxNEF",1.01);
  jetMinNEF_ = jetParams.getUntrackedParameter<double>("jetMinNEF",0.00);
  jetMaxCMF_ = jetParams.getUntrackedParameter<double>("jetMaxCMF",1.01);
  jetMinCMF_ = jetParams.getUntrackedParameter<double>("jetMinCMF",0.00);

  jetMaxCMult_  = jetParams.getUntrackedParameter<double>("jetMaxCMult",9999.);
  jetMinCMult_  = jetParams.getUntrackedParameter<double>("jetMinCMult",0.);
  jetMaxNMult_  = jetParams.getUntrackedParameter<double>("jetMaxNMult",9999.);
  jetMinNMult_  = jetParams.getUntrackedParameter<double>("jetMinNMult",0.);
  jetMaxMuMult_ = jetParams.getUntrackedParameter<double>("jetMaxMuMult",9999.);
  jetMinMuMult_ = jetParams.getUntrackedParameter<double>("jetMinMuMult",0.);


  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree();
}


//________________________________________________________________________________________
JetAnalyzerPAT::~JetAnalyzerPAT() {
  delete mJetData;  
}


//________________________________________________________________________________________
// Method called to for each event
bool JetAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;


  bool_JetPreselection = false;
  bool jet_result = true;
  edm::LogVerbatim("DiJetEvent::JetAnalyzerPAT") << " Start  " << std::endl;

  edm::Handle< std::vector<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetTag_, jetHandle);
  if ( !jetHandle.isValid() ) {
    edm::LogWarning("DiJetEvent::JetAnalyzerPAT") << "No Jet results for InputTag " << jetTag_;
    return false;
  }

  //get number of jets
  i_NJets = jetHandle->size();
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Processing Jets for InputTag " << jetTag_;
  if (debug_ > 5) std::cout<< "Processing "<<jetHandle->size() <<" Jets for InputTag " << jetTag_<<std::endl;
  if (debug_) {
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
  double jetsumpt = 0;

  double gensumpx = 0;
  double gensumpy = 0;
  double gensumpt = 0;

  if ( i_NJets >50 ) i_NJets = 50;

  for (int k=0;k<i_NJets;k++){
    const pat::Jet& theJet    = (*jetHandle)[k];
    const pat::Jet& uncorrJet = (theJet.isCaloJet()) ? theJet.correctedJet("RAW"): theJet;

    /******************Construct the HT/MHT from the jet collection***************************/
    if (theJet.pt() > htMinPt_) {
      if (fabs(theJet.eta()) < htMaxEta_) {
	
	//This will help compute a baseline HT and MHT which can later be corrected for jetID
	jetsumpt += theJet.pt();
	jetsumpx += theJet.momentum().X();
	jetsumpy += theJet.momentum().Y();
	
	//if (doMCData_) {
	if(theJet.genJet()!= 0) {
	  gensumpt += theJet.genJet()->pt();
	  gensumpx += theJet.genJet()->momentum().X();
	  gensumpy += theJet.genJet()->momentum().Y();
	//}
	}
      }
    }


    /******************Now collect all the Jet related variables***************************/
    if (theJet.pt() > jetMinPt_) {
      if (fabs(theJet.eta()) < jetMaxEta_) {

	if (debug_) std::cout<<"\n\nPassed minimum jet id requirements\n\n"<<std::endl;
	

	if (theJet.isCaloJet()) {
	  
	  if (debug_) std::cout<<"\n\nGetting track information from jets\n\n"<<std::endl;
	  const reco::TrackRefVector & mrTracksInJet = theJet.associatedTracks();
	  
	  vd_JetTrackPt         .push_back(0);
	  vd_JetTrackPhi        .push_back(0);
	  vd_JetTrackPhiWeighted.push_back(0);
	  vi_JetTrackNo         .push_back(0);
	  
	  float JetPhi = theJet.phi();
	  
	  for (reco::TrackRefVector::iterator aIter = mrTracksInJet.begin();aIter!= mrTracksInJet.end();aIter++)
	    {
	      vd_JetTrackPt.at(mjet) += (*aIter)->pt();
	      float myPhi = (*aIter)->phi();
	      if( JetPhi > 2. ) {
		if(myPhi<0) myPhi = myPhi + 2*TMath::Pi();
	      }
	      if( JetPhi < -2. ) {
		if(myPhi>0) myPhi = myPhi - 2*TMath::Pi();
	      }
	      vd_JetTrackPhiWeighted.at(mjet) += (*aIter)->pt()*myPhi;
	      vd_JetTrackPhi.at(mjet)         += myPhi;
	      vi_JetTrackNo.at(mjet)++;
	      
	    }
	  
	  vd_JetTrackPhiWeighted.at(mjet) = vd_JetTrackPhiWeighted.at(mjet)/vd_JetTrackPt.at(mjet);
	  vd_JetTrackPhi.at(mjet)         = vd_JetTrackPhi.at(mjet)/float(vi_JetTrackNo.at(mjet));
	}

	if (debug_) std::cout<<"\n\nGetting corrections for calo jets\n\n"<<std::endl;

	if (useCaloJets_) {
	  //JES corrections for the RAW uncorrected jet (RAW)
	  map_s_vd_correctionFactor["raw"].push_back(uncorrJet.corrFactor("RAW"));
	  //JES corrections for the Offset (L1Offset)
	  map_s_vd_correctionFactor["off"].push_back(uncorrJet.corrFactor("OFF"));
	  //JES corrections for the Relative vs eta (L2Relative)
	  map_s_vd_correctionFactor["rel"].push_back(uncorrJet.corrFactor("REL"));
	  //JES corrections for the Absolute vs pT (L3Absolute)
	  map_s_vd_correctionFactor["abs"].push_back(uncorrJet.corrFactor("ABS"));
	  //JES corrections for the EM fraction (L4Emf)
	  map_s_vd_correctionFactor["emf"].push_back(uncorrJet.corrFactor("EMF"));
	  //JES corrections for the Hadrons (L5Flavour)
	  map_s_vd_correctionFactor["had:glu"].push_back(uncorrJet.corrFactor("HAD", "GLU"));
	  map_s_vd_correctionFactor["had:uds"].push_back(uncorrJet.corrFactor("HAD", "UDS"));
	  map_s_vd_correctionFactor["had:c"].push_back(uncorrJet.corrFactor("HAD", "C"));
	  map_s_vd_correctionFactor["had:b"].push_back(uncorrJet.corrFactor("HAD", "B"));
	  //JES corrections for the Underlying Event (L6UE)
	  map_s_vd_correctionFactor["ue:glu"].push_back(uncorrJet.corrFactor("UE", "GLU"));
	  map_s_vd_correctionFactor["ue:uds"].push_back(uncorrJet.corrFactor("UE", "UDS"));
	  map_s_vd_correctionFactor["ue:c"].push_back(uncorrJet.corrFactor("UE", "C"));
	  map_s_vd_correctionFactor["ue:b"].push_back(uncorrJet.corrFactor("UE", "B"));
	  //JES corrections for the Partons (L7Parton)
	  map_s_vd_correctionFactor["part:glu"].push_back(uncorrJet.corrFactor("PART", "GLU"));
	  map_s_vd_correctionFactor["part:uds"].push_back(uncorrJet.corrFactor("PART", "UDS"));
	  map_s_vd_correctionFactor["part:c"].push_back(uncorrJet.corrFactor("PART", "C"));
	  map_s_vd_correctionFactor["part:b"].push_back(uncorrJet.corrFactor("PART", "B"));
	}

	else {
	  if (debug_) std::cout<<"\n\nGetting corrections for other jets\n\n"<<std::endl;

	  map_s_vd_correctionFactor["raw"].push_back(1);
	  map_s_vd_correctionFactor["off"].push_back(1);
	  map_s_vd_correctionFactor["rel"].push_back(1);
	  map_s_vd_correctionFactor["abs"].push_back(1);
	  map_s_vd_correctionFactor["emf"].push_back(1);
	  map_s_vd_correctionFactor["had:glu"].push_back(1);
	  map_s_vd_correctionFactor["had:uds"].push_back(1);
	  map_s_vd_correctionFactor["had:c"].push_back(1);
	  map_s_vd_correctionFactor["had:b"].push_back(1);
	  map_s_vd_correctionFactor["ue:glu"].push_back(1);
	  map_s_vd_correctionFactor["ue:uds"].push_back(1);
	  map_s_vd_correctionFactor["ue:c"].push_back(1);
	  map_s_vd_correctionFactor["ue:b"].push_back(1);
	  map_s_vd_correctionFactor["part:glu"].push_back(1);
	  map_s_vd_correctionFactor["part:uds"].push_back(1);
	  map_s_vd_correctionFactor["part:c"].push_back(1);
	  map_s_vd_correctionFactor["part:b"].push_back(1);
	}

	v_JetP4.push_back(theJet.p4());
	v_JetRawP4.push_back(uncorrJet.p4());
	vd_JetCharge.push_back(theJet.jetCharge());
	vi_JetNConst.push_back(theJet.nConstituents());

	//Jet eta/phi moments
	vd_JetEtaEtaMoment.push_back(theJet.etaetaMoment());
	vd_JetEtaPhiMoment.push_back(theJet.etaphiMoment());
	vd_JetPhiPhiMoment.push_back(theJet.phiphiMoment());

	//Calo jet type specific
	if (debug_) 
	  std::cout<<"\n\nSetting up jetid\n\n"<<std::endl;
	if (useCaloJets_ ) {
	  JetIDSelectionFunctor jetIDMinimal( JetIDSelectionFunctor::PURE09,
					      JetIDSelectionFunctor::MINIMAL );
	  
	  JetIDSelectionFunctor jetIDLoose( JetIDSelectionFunctor::PURE09,
					    JetIDSelectionFunctor::LOOSE );
	  
	  JetIDSelectionFunctor jetIDTight( JetIDSelectionFunctor::PURE09,
					    JetIDSelectionFunctor::TIGHT );
	  
	  pat::strbitset retmin = jetIDMinimal.getBitTemplate();
	  pat::strbitset retloo = jetIDLoose.getBitTemplate();
	  pat::strbitset rettig = jetIDTight.getBitTemplate();
	  
	  retmin.set(false);
	  vb_JetIDMinimal.push_back(jetIDMinimal(theJet, retmin));
	  retloo.set(false);
	  vb_JetIDLoose.push_back(jetIDLoose(theJet, retloo));
	  rettig.set(false);
	  vb_JetIDTight.push_back(jetIDTight(theJet, rettig));
	  
	  vd_JetFem.push_back(theJet.emEnergyFraction());
	  vd_JetFhad.push_back(theJet.energyFractionHadronic());
	}
	
	if (debug_ > 5) 
	  std::cout<<"\n\nDone with jetid for calo jets\n\n"<<std::endl;
	if (useCaloJets_ || useJPTJets_) {
	  if (debug_ > 5)
	    std::cout<<"\n\naccessing jetid information for fhpd, frbx, and n90hits\n\n"<<std::endl;
	  vd_JetN90 .push_back(theJet.jetID().n90Hits);
	  vd_JetfHPD.push_back(theJet.jetID().fHPD);
	  vd_JetfRBX.push_back(theJet.jetID().fRBX);
	}

	if (useJPTJets_) {
	  if (debug_ > 5) std::cout<<"electron multiplicity"<<std::endl;
	  vd_JetElecMult.push_back(theJet.elecMultiplicity());
	}

	if (useJPTJets_ || usePFJets_) {
	  if (debug_ > 5) std::cout<<"charged em fraction"<<std::endl;
	  vd_JetChargedFem .push_back(theJet.chargedEmEnergyFraction());
	  if (debug_ > 5) std::cout<<"neutral em fraction"<<std::endl;
	  vd_JetNeutralFem .push_back(theJet.neutralEmEnergyFraction());
	  if (debug_ > 5) std::cout<<"charged hadron fraction"<<std::endl;
	  vd_JetChargedFhad.push_back(theJet.chargedHadronEnergyFraction());
	  if (debug_ > 5) std::cout<<"neutral hadron fraction"<<std::endl;
	  vd_JetNeutralFhad.push_back(theJet.neutralHadronEnergyFraction());
	  
	  if (debug_ > 5) std::cout<<"chraged multiplicity"<<std::endl;
	  vd_JetChargedMult.push_back(theJet.chargedMultiplicity());
	  if (debug_ > 5) std::cout<<"muon multiplicity"<<std::endl;
	  vd_JetMuonMult   .push_back(theJet.muonMultiplicity());
	  
	  if (debug_ > 5) std::cout<<"em fraction"<<std::endl;
	  vd_JetFem .push_back(theJet.neutralEmEnergyFraction()+
			       theJet.chargedEmEnergyFraction());
	  if (debug_ > 5) std::cout<<"hadron fraction"<<std::endl;
	  vd_JetFhad.push_back(theJet.neutralHadronEnergyFraction()+
			       theJet.chargedHadronEnergyFraction());
	}

	//PF jet type specific variables
	if (usePFJets_) {
	  PFJetIDSelectionFunctor jetIDLoose( PFJetIDSelectionFunctor::FIRSTDATA,
					      PFJetIDSelectionFunctor::LOOSE );
	  
	  PFJetIDSelectionFunctor jetIDTight( PFJetIDSelectionFunctor::FIRSTDATA,
					      PFJetIDSelectionFunctor::TIGHT );
	  
	  pat::strbitset ret = jetIDLoose.getBitTemplate();
	
	  ret.set(false);
	  vb_JetIDLoose.push_back(jetIDLoose(theJet, ret));
	  ret.set(false);
	  vb_JetIDTight.push_back(jetIDTight(theJet, ret));

	  vd_JetChargedFmu .push_back(theJet.muonEnergyFraction());
	  vd_JetChargedFele.push_back(theJet.electronEnergy() / theJet.energy());
	  vd_JetChargedFpho.push_back(theJet.photonEnergyFraction());

	  vd_JetHFFem .push_back(theJet.HFEMEnergyFraction());
	  vd_JetHFFhad.push_back(theJet.HFHadronEnergyFraction());
	  
	  if (debug_ > 5) std::cout<<"neutral multiplicity"<<std::endl;
	  vd_JetNeutralMult.push_back(theJet.neutralMultiplicity());

	  vd_JetChargedHadMult.push_back(theJet.chargedHadronMultiplicity());
	  vd_JetNeutralHadMult.push_back(theJet.neutralHadronMultiplicity());
	  vd_JetPhotonMult    .push_back(theJet.photonMultiplicity());
	  vd_JetElecMult      .push_back(theJet.electronMultiplicity());
 	}
	
	//get jet flavour information
	vi_JetPartonFlavour  .push_back(theJet.partonFlavour());

	//get b-tagging information
	vd_JetBTag_TCHE          .push_back(theJet.bDiscriminator("trackCountingHighEffBJetTags"));
	vd_JetBTag_TCHP          .push_back(theJet.bDiscriminator("trackCountingHighPurBJetTags"));
	vd_JetBTag_jetProb       .push_back(theJet.bDiscriminator("jetProbabilityBJetTags"));
	vd_JetBTag_jetBProb      .push_back(theJet.bDiscriminator("jetBProbabilityBJetTags"));
	vd_JetBTag_SSVHE         .push_back(theJet.bDiscriminator("simpleSecondaryVertexHighEffBJetTags"));
	vd_JetBTag_SSVHP         .push_back(theJet.bDiscriminator("simpleSecondaryVertexHighPurBJetTags"));
	vd_JetBTag_CSV           .push_back(theJet.bDiscriminator("combinedSecondaryVertexBJetTags"));
	vd_JetBTag_CSVMVA        .push_back(theJet.bDiscriminator("combinedSecondaryVertexMVABJetTags"));
	vd_JetBTag_SoftLepton    .push_back(theJet.bDiscriminator("softMuonBJetTags"));
	vd_JetBTag_SoftLeptonByIP.push_back(theJet.bDiscriminator("softMuonByIP3dBJetTags"));
	vd_JetBTag_SoftLeptonByPt.push_back(theJet.bDiscriminator("softMuonByPtBJetTags"));


	//Get gen information for jet	
	if(theJet.genJet()!= 0) {
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(theJet.genJet()->px(),theJet.genJet()->py(),theJet.genJet()->pz(),theJet.genJet()->energy());
	  v_GenJetP4.push_back(genp4);
	}
	else {
	  reco::Candidate::LorentzVector genp4;
	  genp4.SetPxPyPzE(-999.,-999.,-999.,-999);
	  v_GenJetP4.push_back(genp4);
	}

	if(theJet.genParton() != 0){
	  vi_JetPartonId    .push_back(theJet.genParton()->pdgId());
	  vd_JetPartonPx    .push_back(theJet.genParton()->px());
	  vd_JetPartonPy    .push_back(theJet.genParton()->py());
	  vd_JetPartonPz    .push_back(theJet.genParton()->pz());
	  vd_JetPartonEt    .push_back(theJet.genParton()->et());
	  vd_JetPartonPhi   .push_back(theJet.genParton()->phi());
	  vd_JetPartonEta   .push_back(theJet.genParton()->eta());
	  vd_JetPartonEnergy.push_back(theJet.genParton()->energy());
	  vi_JetPartonMother.push_back(theJet.genParton()->mother()->pdgId());
	}
	else{
	  vi_JetPartonId    .push_back(999.);
	  vd_JetPartonPx    .push_back(999.);
	  vd_JetPartonPy    .push_back(999.);
	  vd_JetPartonPz    .push_back(999.);
	  vd_JetPartonEt    .push_back(999.);
	  vd_JetPartonPhi   .push_back(999.);
	  vd_JetPartonEta   .push_back(999.);
	  vd_JetPartonEnergy.push_back(999.);
	  vi_JetPartonMother.push_back(999.);
	}
	++mjet;
      }
    }
  }
  
  i_NJets  =  mjet;
  d_Ht     =  jetsumpt;
  d_MHx    = -jetsumpx;
  d_MHy    = -jetsumpy;
  d_MHt    = -sqrt(jetsumpx*jetsumpx+jetsumpy*jetsumpy);
  
  d_GenHt  =  gensumpt;
  d_GenMHx = -gensumpx;
  d_GenMHy = -gensumpy;
  d_GenMHt = -sqrt(gensumpx*gensumpx+gensumpy*gensumpy);
  
  jet_result = bool_JetPreselection;
  if (debug_ > 5)
    std::cout<<"Done analyzing all the jets"<<std::endl;
  return jet_result;
}


//________________________________________________________________________________________
void JetAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  

  mJetData->Branch(prefix_+"NJets",   &i_NJets,   prefix_+"NJets/I");  
  mJetData->Branch(prefix_+"Ht",      &d_Ht,      prefix_+"Ht/D");
  mJetData->Branch(prefix_+"MHx",     &d_MHx,     prefix_+"MHx/D");
  mJetData->Branch(prefix_+"MHy",     &d_MHy,     prefix_+"MHy/D");
  mJetData->Branch(prefix_+"MHt",     &d_MHt,     prefix_+"MHt/D");
  
  mJetData->Branch(prefix_+"JetP4",     &v_JetP4);
  mJetData->Branch(prefix_+"JetRawP4",  &v_JetRawP4);
  mJetData->Branch(prefix_+"JetEtaEtaMoment",  &vd_JetEtaEtaMoment);
  mJetData->Branch(prefix_+"JetEtaPhiMoment",  &vd_JetEtaPhiMoment);
  mJetData->Branch(prefix_+"JetPhiPhiMoment",  &vd_JetPhiPhiMoment);
  mJetData->Branch(prefix_+"JetFem",    &vd_JetFem);
  mJetData->Branch(prefix_+"JetFhad",   &vd_JetFhad);
  mJetData->Branch(prefix_+"JetCharge", &vd_JetCharge);
  mJetData->Branch(prefix_+"JetNConst", &vi_JetNConst);
  //mJetData->Branch(prefix_+"JetHemi", &vi_JetHemi, prefix_+"JetHemi["+prefix_+"NJets]/I");
  mJetData->Branch(prefix_+"JetCorrFactor",   &map_s_vd_correctionFactor);
  mJetData->Branch(prefix_+"JetPreselection", &bool_JetPreselection, prefix_+"JetPreselection/O");
  mJetData->Branch(prefix_+"JetIDMinimal", &vb_JetIDMinimal);
  mJetData->Branch(prefix_+"JetIDLoose",   &vb_JetIDLoose);
  mJetData->Branch(prefix_+"JetIDTight",   &vb_JetIDTight);
  
  //b-tagging information
  mJetData->Branch(prefix_+"JetBTag_TCHE",            &vd_JetBTag_TCHE);
  mJetData->Branch(prefix_+"JetBTag_TCHP",            &vd_JetBTag_TCHP);
  mJetData->Branch(prefix_+"JetBTag_jetProb",         &vd_JetBTag_jetProb);
  mJetData->Branch(prefix_+"JetBTag_jetBProb",        &vd_JetBTag_jetBProb);
  mJetData->Branch(prefix_+"JetBTag_SSVHE",           &vd_JetBTag_SSVHE);
  mJetData->Branch(prefix_+"JetBTag_SSVHP",           &vd_JetBTag_SSVHP);
  mJetData->Branch(prefix_+"JetBTag_CSV",             &vd_JetBTag_CSV);
  mJetData->Branch(prefix_+"JetBTag_CSVMVA",          &vd_JetBTag_CSVMVA);
  mJetData->Branch(prefix_+"JetBTag_SoftLepton",      &vd_JetBTag_SoftLepton);
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByIP",  &vd_JetBTag_SoftLeptonByIP);
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByPt",  &vd_JetBTag_SoftLeptonByPt);
  
  //information about associated gen jets
  mJetData->Branch(prefix_+"GenHt",    &d_GenHt,     prefix_+"GenHt/D");
  mJetData->Branch(prefix_+"GenMHt",   &d_GenMHt,    prefix_+"GenMHt/D");
    
  //information about associated partons
  mJetData->Branch(prefix_+"JetPartonId",         &vi_JetPartonId);
  mJetData->Branch(prefix_+"JetPartonMother",     &vi_JetPartonMother);
  mJetData->Branch(prefix_+"JetPartonPx",         &vd_JetPartonPx);
  mJetData->Branch(prefix_+"JetPartonPy",         &vd_JetPartonPy);
  mJetData->Branch(prefix_+"JetPartonPz",         &vd_JetPartonPz);
  mJetData->Branch(prefix_+"JetPartonEt",         &vd_JetPartonEt);
  mJetData->Branch(prefix_+"JetPartonE" ,         &vd_JetPartonEnergy);
  mJetData->Branch(prefix_+"JetPartonPhi",        &vd_JetPartonPhi);
  mJetData->Branch(prefix_+"JetPartonEta",        &vd_JetPartonEta);
  mJetData->Branch(prefix_+"JetPartonFlavour",    &vi_JetPartonFlavour);
    
  
  if (useJPTJets_ ) {
    if (debug_ > 5) std::cout<<"Saving JPT specific information"<<std::endl;
  }
  
  if (useJPTJets_ || usePFJets_) {
    if (debug_ > 5) std::cout<<"Saving JPT/PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetChargedFem",  &vd_JetChargedFem);
    mJetData->Branch(prefix_+"JetNeutralFem",  &vd_JetNeutralFem);
    mJetData->Branch(prefix_+"JetChargedFhad", &vd_JetChargedFhad);
    mJetData->Branch(prefix_+"JetNeutralFhad", &vd_JetNeutralFhad);
    mJetData->Branch(prefix_+"JetChargedMult", &vd_JetChargedMult);
    mJetData->Branch(prefix_+"JetElecMulti",   &vd_JetElecMult);
    mJetData->Branch(prefix_+"JetMuonMulti",   &vd_JetMuonMult);
  }
  
  if (usePFJets_) {
    if (debug_ > 5) std::cout<<"Saving PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetChargedFmu",  &vd_JetChargedFmu);
    mJetData->Branch(prefix_+"JetChargedFele", &vd_JetChargedFele);
    mJetData->Branch(prefix_+"JetChargedFpho", &vd_JetChargedFpho);
  
    mJetData->Branch(prefix_+"JetHFFem",  &vd_JetHFFem);
    mJetData->Branch(prefix_+"JetHFFhad", &vd_JetHFFhad);
  
    mJetData->Branch(prefix_+"JetChargedHadMult", &vd_JetChargedHadMult);
    mJetData->Branch(prefix_+"JetNeutralHadMult", &vd_JetNeutralHadMult);
    mJetData->Branch(prefix_+"JetPhotonMult",     &vd_JetPhotonMult);
    mJetData->Branch(prefix_+"JetNeutralMult",    &vd_JetNeutralMult);
  }
  
  if (useTrackJets_) {
    if (debug_ > 5) std::cout<<"Saving Track specific information"<<std::endl;
    //mJetData->Branch(prefix_+"JetCharge",  &vd_JetCharge);
  }
  
  if (useCaloJets_ || useJPTJets_) {
    if (debug_ > 5) std::cout<<"Saving Calo/JPT specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetfHPD", &vd_JetfHPD);
    mJetData->Branch(prefix_+"JetfRBX", &vd_JetfRBX);
    mJetData->Branch(prefix_+"Jetn90",  &vd_JetN90);
  
    //information about associated tracks
    mJetData->Branch(prefix_+"JetTrackPt",          &vd_JetTrackPt);
    mJetData->Branch(prefix_+"JetTrackPhi",         &vd_JetTrackPhi);
    mJetData->Branch(prefix_+"JetTrackPhiWeighted", &vd_JetTrackPhiWeighted);
    mJetData->Branch(prefix_+"JetTrackNo",          &vi_JetTrackNo);
  
  }
  
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_EDM_PLUGIN(JetAnalyzerPAT);

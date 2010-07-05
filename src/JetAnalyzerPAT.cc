
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
// $Id: JetAnalyzerPAT.cc,v 1.7 2010/06/17 17:52:46 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/JetAnalyzerPAT.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 
#pragma link C++ class std::map<std::string, std::vector<float> >+; 
#pragma link C++ class std::vector<<reco::Candidate::LorentzVector> >+; 
#endif
//________________________________________________________________________________________
JetAnalyzerPAT::JetAnalyzerPAT(const edm::ParameterSet& jetParams, TTree* tmpAllData)
{ 
  mJetData = tmpAllData;

  minNJets_  = 1;
  


  debug_     = jetParams.getUntrackedParameter<int>("debugJets",0);
  prefix_    = jetParams.getUntrackedParameter<std::string>("prefixJets","Calo");
  jetMaxEta_ = jetParams.getUntrackedParameter<double >("jetMaxEta",5.);
  jetMinPt_  = jetParams.getUntrackedParameter<double >("jetMinPt",30.);
  jetMaxEMF_ = jetParams.getUntrackedParameter<double >("jetMaxEMF",0.99);
  jetMinEMF_ = jetParams.getUntrackedParameter<double >("jetMinEMF",0.01);

  htMaxEta_ = jetParams.getUntrackedParameter<double >("htMaxEta",jetMaxEta_);
  htMinPt_  = jetParams.getUntrackedParameter<double >("htMinPt",jetMinPt_);

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
  usePFJets_    = jetParams.getUntrackedParameter<bool>("usePFJets",false);
  useJPTJets_   = jetParams.getUntrackedParameter<bool>("useJPTJets",false);
  useCaloJets_  = jetParams.getUntrackedParameter<bool>("useCaloJets",false);
  useTrackJets_ = jetParams.getUntrackedParameter<bool>("useTrackJets",false);

  jetTag_     = jetParams.getUntrackedParameter<edm::InputTag>("jetTag");

  //calo jet id
  jetMaxHPD_ = jetParams.getUntrackedParameter<double >("jetMaxHPD",1.01);
  jetMinHPD_ = jetParams.getUntrackedParameter<double >("jetMinHPD",0.00);
  jetMaxRBX_ = jetParams.getUntrackedParameter<double >("jetMaxRBX",1.01);
  jetMinRBX_ = jetParams.getUntrackedParameter<double >("jetMinRBX",0.00);
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
  if (debug_) std::cout<< "Processing "<<jetHandle->size() <<" Jets for InputTag " << jetTag_<<std::endl;
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
  //map_s_vd_correctionFactor["raw"].resize(i_NJets);
  //map_s_vd_correctionFactor["off"].resize(i_NJets);
  //map_s_vd_correctionFactor["rel"].resize(i_NJets);
  //map_s_vd_correctionFactor["abs"].resize(i_NJets);
  //map_s_vd_correctionFactor["emf"].resize(i_NJets);
  //map_s_vd_correctionFactor["had:glu"].resize(i_NJets);
  //map_s_vd_correctionFactor["had:uds"].resize(i_NJets);
  //map_s_vd_correctionFactor["had:c"].resize(i_NJets);
  //map_s_vd_correctionFactor["had:b"].resize(i_NJets);
  //map_s_vd_correctionFactor["ue:glu"].resize(i_NJets);
  //map_s_vd_correctionFactor["ue:uds"].resize(i_NJets);
  //map_s_vd_correctionFactor["ue:c"].resize(i_NJets);
  //map_s_vd_correctionFactor["ue:b"].resize(i_NJets);
  //map_s_vd_correctionFactor["part:glu"].resize(i_NJets);
  //map_s_vd_correctionFactor["part:uds"].resize(i_NJets);
  //map_s_vd_correctionFactor["part:c"].resize(i_NJets);
  //map_s_vd_correctionFactor["part:b"].resize(i_NJets);

  //v_JetP4.resize(i_NJets);
  //v_JetDetectorP4.resize(i_NJets);
  //v_JetPhysicsP4.resize(i_NJets);
  for (int k=0;k<i_NJets;k++){
    const pat::Jet& theJet = (*jetHandle)[k];
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
	  
	  mat_d_JetTrackPt[mjet]          = 0;
	  mat_d_JetTrackPhi[mjet]         = 0;
	  mat_d_JetTrackPhiWeighted[mjet] = 0;
	  mat_i_JetTrackNo[mjet]          = 0;
	  
	  float JetPhi = theJet.phi();
	  
	  for (reco::TrackRefVector::iterator aIter = mrTracksInJet.begin();aIter!= mrTracksInJet.end();aIter++)
	    {
	      mat_d_JetTrackPt[mjet] += (*aIter)->pt();
	      float myPhi = (*aIter)->phi();
	      if( JetPhi > 2. ) {
		if(myPhi<0) myPhi = myPhi + 2*TMath::Pi();
	      }
	      if( JetPhi < -2. ) {
		if(myPhi>0) myPhi = myPhi - 2*TMath::Pi();
	      }
	      mat_d_JetTrackPhiWeighted[mjet] += (*aIter)->pt()*myPhi;
	      mat_d_JetTrackPhi[mjet]         += myPhi;
	      mat_i_JetTrackNo[mjet]++;
	      
	    }
	  
	  mat_d_JetTrackPhiWeighted[mjet] = mat_d_JetTrackPhiWeighted[mjet]/mat_d_JetTrackPt[mjet];
	  mat_d_JetTrackPhi[mjet]         = mat_d_JetTrackPhi[mjet]/float(mat_i_JetTrackNo[mjet]);
	}

	if (debug_) std::cout<<"\n\nGetting corrections for calo jets\n\n"<<std::endl;

	if (useCaloJets_) {
	  ////JES corrections for the RAW uncorrected jet (RAW)
	  //map_s_vd_correctionFactor["raw"].at(mjet) = uncorrJet.corrFactor("RAW");
	  ////JES corrections for the Offset (L1Offset)
	  //map_s_vd_correctionFactor["off"].at(mjet) = uncorrJet.corrFactor("OFF");
	  ////JES corrections for the Relative vs eta (L2Relative)
	  //map_s_vd_correctionFactor["rel"].at(mjet) = uncorrJet.corrFactor("REL");
	  ////JES corrections for the Absolute vs pT (L3Absolute)
	  //map_s_vd_correctionFactor["abs"].at(mjet) = uncorrJet.corrFactor("ABS");
	  ////JES corrections for the EM fraction (L4Emf)
	  //map_s_vd_correctionFactor["emf"].at(mjet) = uncorrJet.corrFactor("EMF");
	  ////JES corrections for the Hadrons (L5Flavour)
	  //map_s_vd_correctionFactor["had:glu"].at(mjet) = uncorrJet.corrFactor("HAD", "GLU");
	  //map_s_vd_correctionFactor["had:uds"].at(mjet) = uncorrJet.corrFactor("HAD", "UDS");
	  //map_s_vd_correctionFactor["had:c"].at(mjet)   = uncorrJet.corrFactor("HAD", "C");
	  //map_s_vd_correctionFactor["had:b"].at(mjet)   = uncorrJet.corrFactor("HAD", "B");
	  ////JES corrections for the Underlying Event (L6UE)
	  //map_s_vd_correctionFactor["ue:glu"].at(mjet)  = uncorrJet.corrFactor("UE", "GLU");
	  //map_s_vd_correctionFactor["ue:uds"].at(mjet)  = uncorrJet.corrFactor("UE", "UDS");
	  //map_s_vd_correctionFactor["ue:c"].at(mjet)    = uncorrJet.corrFactor("UE", "C");
	  //map_s_vd_correctionFactor["ue:b"].at(mjet)    = uncorrJet.corrFactor("UE", "B");
	  ////JES corrections for the Partons (L7Parton)
	  //map_s_vd_correctionFactor["part:glu"].at(mjet) = uncorrJet.corrFactor("PART", "GLU");
	  //map_s_vd_correctionFactor["part:uds"].at(mjet) = uncorrJet.corrFactor("PART", "UDS");
	  //map_s_vd_correctionFactor["part:c"].at(mjet)   = uncorrJet.corrFactor("PART", "C");
	  //map_s_vd_correctionFactor["part:b"].at(mjet)   = uncorrJet.corrFactor("PART", "B");

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
	  //map_s_vd_correctionFactor["raw"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["off"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["rel"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["abs"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["emf"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["had:glu"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["had:uds"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["had:c"].at(mjet)   = 1.;
	  //map_s_vd_correctionFactor["had:b"].at(mjet)   = 1.;
	  //map_s_vd_correctionFactor["ue:glu"].at(mjet)  = 1.;
	  //map_s_vd_correctionFactor["ue:uds"].at(mjet)  = 1.;
	  //map_s_vd_correctionFactor["ue:c"].at(mjet)    = 1.;
	  //map_s_vd_correctionFactor["ue:b"].at(mjet)    = 1.;
	  //map_s_vd_correctionFactor["part:glu"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["part:uds"].at(mjet) = 1.;
	  //map_s_vd_correctionFactor["part:c"].at(mjet)   = 1.;
	  //map_s_vd_correctionFactor["part:b"].at(mjet)   = 1.;

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

	//v_JetP4.at(mjet)     = theJet.p4();
	//v_JetRawP4.at(mjet)  = uncorrJet.p4();
	v_JetP4.push_back(theJet.p4());
	v_JetRawP4.push_back(uncorrJet.p4());
	//v_JetDetectorP4.at(mjet) = theJet.detectorP4();
	//v_JetPhysicsP4.at(mjet)  = theJet.physicsP4();
	mat_d_JetE[mjet]      = theJet.energy();
	mat_d_JetPt[mjet]     = theJet.pt();
	mat_d_JetEt[mjet]     = theJet.et();
	mat_d_JetPx[mjet]     = theJet.momentum().X();
	mat_d_JetPy[mjet]     = theJet.momentum().Y();
	mat_d_JetPz[mjet]     = theJet.momentum().Z();
	mat_d_JetEta[mjet]    = theJet.eta();
	mat_d_JetPhi[mjet]    = theJet.phi();
	mat_d_JetCharge[mjet] = theJet.jetCharge();
	mat_i_JetNConst[mjet] = theJet.nConstituents();
	
	//Uncorrected values
	mat_d_JetRawE[mjet]    = uncorrJet.energy();
	mat_d_JetRawPt[mjet]   = uncorrJet.pt();
	mat_d_JetRawEt[mjet]   = uncorrJet.et();
	mat_d_JetRawPx[mjet]   = uncorrJet.momentum().X();
	mat_d_JetRawPy[mjet]   = uncorrJet.momentum().Y();
	mat_d_JetRawPz[mjet]   = uncorrJet.momentum().Z();

	//Jet eta/phi moments
	mat_d_JetEtaEtaMoment[mjet] = theJet.etaetaMoment();
	mat_d_JetEtaPhiMoment[mjet] = theJet.etaphiMoment();
	mat_d_JetPhiPhiMoment[mjet] = theJet.phiphiMoment();

	//Calo jet type specific
	if (debug_) std::cout<<"\n\nSetting up jetid\n\n"<<std::endl;
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
	  mat_b_JetIDMinimal[mjet] = jetIDMinimal(theJet, retmin);
	  retloo.set(false);
	  mat_b_JetIDLoose[mjet]   = jetIDLoose(theJet, retloo);
	  rettig.set(false);
	  mat_b_JetIDTight[mjet]   = jetIDTight(theJet, rettig);
	  
	  mat_d_JetFem[mjet]  = theJet.emEnergyFraction();
	  mat_d_JetFhad[mjet] = theJet.energyFractionHadronic();
	}
	
	if (debug_) std::cout<<"\n\nDone with jetid for calo jets\n\n"<<std::endl;
	if (useCaloJets_ || useJPTJets_) {
	  if (debug_)
	    if (debug_) std::cout<<"\n\naccessing jetid information for fhpd, frbx, and n90hits\n\n"<<std::endl;
	  mat_d_JetN90[mjet]  = theJet.jetID().n90Hits;
	  mat_d_JetfHPD[mjet] = theJet.jetID().fHPD;
	  mat_d_JetfRBX[mjet] = theJet.jetID().fRBX;
	}

	if (useJPTJets_) {
	  if (debug_) std::cout<<"electron multiplicity"<<std::endl;
	  mat_d_JetElecMult[mjet]    = theJet.elecMultiplicity();
	}

	if (useJPTJets_ || usePFJets_) {
	  if (debug_) std::cout<<"charged em fraction"<<std::endl;
	  mat_d_JetChargedFem[mjet]  = theJet.chargedEmEnergyFraction();
	  if (debug_) std::cout<<"neutral em fraction"<<std::endl;
	  mat_d_JetNeutralFem[mjet]  = theJet.neutralEmEnergyFraction();
	  if (debug_) std::cout<<"charged hadron fraction"<<std::endl;
	  mat_d_JetChargedFhad[mjet] = theJet.chargedHadronEnergyFraction();
	  if (debug_) std::cout<<"neutral hadron fraction"<<std::endl;
	  mat_d_JetNeutralFhad[mjet] = theJet.neutralHadronEnergyFraction();

	  if (debug_) std::cout<<"chraged multiplicity"<<std::endl;
	  mat_d_JetChargedMult[mjet] = theJet.chargedMultiplicity();
	  if (debug_) std::cout<<"muon multiplicity"<<std::endl;
	  mat_d_JetMuonMult[mjet]    = theJet.muonMultiplicity();

	  if (debug_) std::cout<<"em fraction"<<std::endl;
	  mat_d_JetFem[mjet]  = theJet.neutralEmEnergyFraction()+
	    theJet.chargedEmEnergyFraction();
	  if (debug_) std::cout<<"hadron fraction"<<std::endl;
	  mat_d_JetFhad[mjet] = theJet.neutralHadronEnergyFraction()+
	    theJet.chargedHadronEnergyFraction();
	}

	//PF jet type specific variables
	if (usePFJets_) {
	  PFJetIDSelectionFunctor jetIDLoose( PFJetIDSelectionFunctor::FIRSTDATA,
					      PFJetIDSelectionFunctor::LOOSE );
	  
	  PFJetIDSelectionFunctor jetIDTight( PFJetIDSelectionFunctor::FIRSTDATA,
					      PFJetIDSelectionFunctor::TIGHT );
	  
	  pat::strbitset ret = jetIDLoose.getBitTemplate();
	
	  ret.set(false);
	  mat_b_JetIDLoose[mjet]   = jetIDLoose(theJet, ret);
	  ret.set(false);
	  mat_b_JetIDTight[mjet]   = jetIDTight(theJet, ret);

	  mat_d_JetChargedFmu[mjet]  = theJet.muonEnergyFraction();
	  mat_d_JetChargedFele[mjet] = theJet.electronEnergy() / theJet.energy();
	  mat_d_JetChargedFpho[mjet] = theJet.photonEnergyFraction();

	  mat_d_JetHFFem[mjet]  = theJet.HFEMEnergyFraction();
	  mat_d_JetHFFhad[mjet] = theJet.HFHadronEnergyFraction();
	  
	  if (debug_) std::cout<<"neutral multiplicity"<<std::endl;
	  mat_d_JetNeutralMult[mjet] = theJet.neutralMultiplicity();

	  mat_d_JetChargedHadMult[mjet] = theJet.chargedHadronMultiplicity();
	  mat_d_JetNeutralHadMult[mjet] = theJet.neutralHadronMultiplicity();
	  mat_d_JetPhotonMult[mjet]     = theJet.photonMultiplicity();
	  mat_d_JetElecMult[mjet]       = theJet.electronMultiplicity();
 	}
	
	//get jet flavour information
	mat_i_JetPartonFlavour[mjet]   = theJet.partonFlavour();

	//get b-tagging information
	mat_d_JetBTag_TCHE[mjet]           = theJet.bDiscriminator("trackCountingHighEffBJetTags");
	mat_d_JetBTag_TCHP[mjet]           = theJet.bDiscriminator("trackCountingHighPurBJetTags");
	mat_d_JetBTag_jetProb[mjet]        = theJet.bDiscriminator("jetProbabilityBJetTags");
	mat_d_JetBTag_jetBProb[mjet]       = theJet.bDiscriminator("jetBProbabilityBJetTags");
	mat_d_JetBTag_SSVHE[mjet]          = theJet.bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
	mat_d_JetBTag_SSVHP[mjet]          = theJet.bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
	mat_d_JetBTag_CSV[mjet]            = theJet.bDiscriminator("combinedSecondaryVertexBJetTags");
	mat_d_JetBTag_CSVMVA[mjet]         = theJet.bDiscriminator("combinedSecondaryVertexMVABJetTags");
	mat_d_JetBTag_SoftLepton[mjet]     = theJet.bDiscriminator("softMuonBJetTags");
	mat_d_JetBTag_SoftLeptonByIP[mjet] = theJet.bDiscriminator("softMuonByIP3dBJetTags");
	mat_d_JetBTag_SoftLeptonByPt[mjet] = theJet.bDiscriminator("softMuonByPtBJetTags");


	//Get gen information for jet	
	if(theJet.genJet()!= 0) {
	  mat_d_JetGenPt[mjet]  = theJet.genJet()->pt();
	  mat_d_JetGenE[mjet]   = theJet.genJet()->energy();
	  mat_d_JetGenEt[mjet]  = theJet.genJet()->et();
	  mat_d_JetGenPx[mjet]  = theJet.genJet()->momentum().X();
	  mat_d_JetGenPy[mjet]  = theJet.genJet()->momentum().Y();
	  mat_d_JetGenPz[mjet]  = theJet.genJet()->momentum().z();
	  mat_d_JetGenEta[mjet] = theJet.genJet()->eta();
	  mat_d_JetGenPhi[mjet] = theJet.genJet()->phi();
	}
	else {
	  mat_d_JetGenPt[mjet]  = -999;
	  mat_d_JetGenE[mjet]   = -999;
	  mat_d_JetGenEt[mjet]  = -999;
	  mat_d_JetGenPx[mjet]  = -999;
	  mat_d_JetGenPy[mjet]  = -999;
	  mat_d_JetGenPz[mjet]  = -999;
	  mat_d_JetGenEta[mjet] = -999;
	  mat_d_JetGenPhi[mjet] = -999;
	}

	if(theJet.genParton() != 0){
	  mat_i_JetPartonId[mjet]     = theJet.genParton()->pdgId();
	  mat_d_JetPartonPx[mjet]     = theJet.genParton()->px();
	  mat_d_JetPartonPy[mjet]     = theJet.genParton()->py();
	  mat_d_JetPartonPz[mjet]     = theJet.genParton()->pz();
	  mat_d_JetPartonEt[mjet]     = theJet.genParton()->et();
	  mat_d_JetPartonPhi[mjet]    = theJet.genParton()->phi();
	  mat_d_JetPartonEta[mjet]    = theJet.genParton()->eta();
	  mat_d_JetPartonEnergy[mjet] = theJet.genParton()->energy();
	  mat_i_JetPartonMother[mjet] = theJet.genParton()->mother()->pdgId();
	}
	else{
	  mat_i_JetPartonId[mjet]     = -999;
	  mat_d_JetPartonPx[mjet]     = -999;
	  mat_d_JetPartonPy[mjet]     = -999;
	  mat_d_JetPartonPz[mjet]     = -999;
	  mat_d_JetPartonEt[mjet]     = -999;
	  mat_d_JetPartonPhi[mjet]    = -999;
	  mat_d_JetPartonEta[mjet]    = -999;
	  mat_d_JetPartonEnergy[mjet] = -999;
	  mat_i_JetPartonMother[mjet] = -999;
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
  if (debug_)
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
  
  mJetData->Branch(prefix_+"JetP4",    &v_JetP4,         prefix_+"JetP4");
  mJetData->Branch(prefix_+"JetRawP4", &v_JetRawP4,      prefix_+"JetRawP4");
  mJetData->Branch(prefix_+"JetE",      mat_d_JetE,      prefix_+"JetE["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetEt",     mat_d_JetEt,     prefix_+"JetEt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetPt",     mat_d_JetPt,     prefix_+"JetPt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetPx",     mat_d_JetPx,     prefix_+"JetPx["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetPy",     mat_d_JetPy,     prefix_+"JetPy["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetPz",     mat_d_JetPz,     prefix_+"JetPz["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawE",   mat_d_JetRawE,   prefix_+"JetRawE["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawEt",  mat_d_JetRawEt,  prefix_+"JetRawEt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawPt",  mat_d_JetRawPt,  prefix_+"JetRawPt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawPx",  mat_d_JetRawPx,  prefix_+"JetRawPx["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawPy",  mat_d_JetRawPy,  prefix_+"JetRawPy["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetRawPz",  mat_d_JetRawPz,  prefix_+"JetRawPz["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetEta",    mat_d_JetEta,    prefix_+"JetEta["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetPhi",    mat_d_JetPhi,    prefix_+"JetPhi["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetFem",    mat_d_JetFem,    prefix_+"JetFem["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetFhad",   mat_d_JetFhad,   prefix_+"JetFhad["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetCharge", mat_d_JetCharge, prefix_+"JetCharge["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetNConst", mat_i_JetNConst, prefix_+"JetNConst["+prefix_+"NJets]/D");
  //mJetData->Branch(prefix_+"JetHemi", mat_i_JetHemi, prefix_+"JetHemi["+prefix_+"NJets]/I");
  mJetData->Branch(prefix_+"JetCorrFactor",   &map_s_vd_correctionFactor,  prefix_+"JetCorrFactor");
  mJetData->Branch(prefix_+"JetPreselection", &bool_JetPreselection, prefix_+"JetPreselection/O");
  mJetData->Branch(prefix_+"JetIDMinimal", mat_b_JetIDMinimal, prefix_+"JetIDMinimal["+prefix_+"NJets]/O");
  mJetData->Branch(prefix_+"JetIDLoose",   mat_b_JetIDLoose,   prefix_+"JetIDLoose["+prefix_+"NJets]/O");
  mJetData->Branch(prefix_+"JetIDTight",   mat_b_JetIDTight,   prefix_+"JetIDTight["+prefix_+"NJets]/O");
  
  //b-tagging information
  mJetData->Branch(prefix_+"JetBTag_TCHE",            mat_d_JetBTag_TCHE,            prefix_+"JetBTag_TCHE["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_TCHP",            mat_d_JetBTag_TCHP,            prefix_+"JetBTag_TCHP["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_jetProb",         mat_d_JetBTag_jetProb,         prefix_+"JetBTag_jetProb["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_jetBProb",        mat_d_JetBTag_jetBProb,        prefix_+"JetBTag_jetBProb["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_SSVHE",           mat_d_JetBTag_SSVHE,           prefix_+"JetBTag_SSVHE["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_SSVHP",           mat_d_JetBTag_SSVHP,           prefix_+"JetBTag_SSVHP["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_CSV",             mat_d_JetBTag_CSV,             prefix_+"JetBTag_CSV["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_CSVMVA",          mat_d_JetBTag_CSVMVA,          prefix_+"JetBTag_CSVMVA["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_SoftLepton",      mat_d_JetBTag_SoftLepton,      prefix_+"JetBTag_SoftLepton["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByIP",  mat_d_JetBTag_SoftLeptonByIP,  prefix_+"JetBTag_SoftLeptonByIP["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByPt",  mat_d_JetBTag_SoftLeptonByPt,  prefix_+"JetBTag_SoftLeptonByPt["+prefix_+"NJets]/D");
  
  //information about associated gen jets
  mJetData->Branch(prefix_+"GenHt",    &d_GenHt,     prefix_+"GenHt/D");
  mJetData->Branch(prefix_+"GenMHt",   &d_GenMHt,    prefix_+"GenMHt/D");
  mJetData->Branch(prefix_+"JetGenE" ,  mat_d_JetGenE,   prefix_+"JetGenE["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenEt",  mat_d_JetGenEt,  prefix_+"JetGenEt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenPt",  mat_d_JetGenPt,  prefix_+"JetGenPt["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenPx",  mat_d_JetGenPx,  prefix_+"JetGenPx["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenPy",  mat_d_JetGenPy,  prefix_+"JetGenPy["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenPz",  mat_d_JetGenPz,  prefix_+"JetGenPz["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenEta", mat_d_JetGenEta, prefix_+"JetGenEta["+prefix_+"NJets]/D");
  mJetData->Branch(prefix_+"JetGenPhi", mat_d_JetGenPhi, prefix_+"JetGenPhi["+prefix_+"NJets]/D");
    
  //information about associated partons
  mJetData->Branch(prefix_+"JetPartonId",         mat_i_JetPartonId,         prefix_+"JetPartonId["+prefix_+"NJets]/I"); 
  mJetData->Branch(prefix_+"JetPartonMother",     mat_i_JetPartonMother,     prefix_+"JetPartonMother["+prefix_+"NJets]/I"); 
  mJetData->Branch(prefix_+"JetPartonPx",         mat_d_JetPartonPx,         prefix_+"JetPartonPx["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonPy",         mat_d_JetPartonPy,         prefix_+"JetPartonPy["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonPz",         mat_d_JetPartonPz,         prefix_+"JetPartonPz["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonEt",         mat_d_JetPartonEt,         prefix_+"JetPartonEt["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonE" ,         mat_d_JetPartonEnergy,     prefix_+"JetPartonE["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonPhi",        mat_d_JetPartonPhi,        prefix_+"JetPartonPhi["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonEta",        mat_d_JetPartonEta,        prefix_+"JetPartonEta["+prefix_+"NJets]/D"); 
  mJetData->Branch(prefix_+"JetPartonFlavour",    mat_i_JetPartonFlavour,    prefix_+"JetPartonFlavour["+prefix_+"NJets]/I");
    
  
  if (useJPTJets_ ) {
    if (debug_) std::cout<<"Saving JPT specific information"<<std::endl;
  }
  
  if (useJPTJets_ || usePFJets_) {
    if (debug_) std::cout<<"Saving JPT/PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetChargedFem",  mat_d_JetChargedFem,  prefix_+"JetChargedFem["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetNeutralFem",  mat_d_JetNeutralFem,  prefix_+"JetNeutralFem["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetChargedFhad", mat_d_JetChargedFhad, prefix_+"JetChargedFhad["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetNeutralFhad", mat_d_JetNeutralFhad, prefix_+"JetNeutralFhad["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetChargedMult", mat_d_JetChargedMult, prefix_+"JetChargedMult["+prefix_+"NJets]/I");
    mJetData->Branch(prefix_+"JetElecMulti",   mat_d_JetElecMult,    prefix_+"JetElecMulti["+prefix_+"NJets]/I");
    mJetData->Branch(prefix_+"JetMuonMulti",   mat_d_JetMuonMult,    prefix_+"JetMuonMulti["+prefix_+"NJets]/I");
  }
  
  if (usePFJets_) {
    if (debug_) std::cout<<"Saving PF specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetChargedFmu",  mat_d_JetChargedFmu,  prefix_+"JetChargedFmu["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetChargedFele", mat_d_JetChargedFele, prefix_+"JetChargedFele["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetChargedFpho", mat_d_JetChargedFpho, prefix_+"JetChargedFpho["+prefix_+"NJets]/D");
  
    mJetData->Branch(prefix_+"JetHFFem",  mat_d_JetHFFem,  prefix_+"JetHFFem["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetHFFhad", mat_d_JetHFFhad, prefix_+"JetHFFhad["+prefix_+"NJets]/D");
  
    mJetData->Branch(prefix_+"JetChargedHadMult", mat_d_JetChargedHadMult, prefix_+"JetChargedHadMult["+prefix_+"NJets]/I");
    mJetData->Branch(prefix_+"JetNeutralHadMult", mat_d_JetNeutralHadMult, prefix_+"JetNeutralHadMult["+prefix_+"NJets]/I");
    mJetData->Branch(prefix_+"JetPhotonMult",     mat_d_JetPhotonMult,     prefix_+"JetPhotonMult["+prefix_+"NJets]/I");
    mJetData->Branch(prefix_+"JetNeutralMult",    mat_d_JetNeutralMult,    prefix_+"JetNeutralMult["+prefix_+"NJets]/I");
  }
  
  if (useTrackJets_) {
    if (debug_) std::cout<<"Saving Track specific information"<<std::endl;
    //mJetData->Branch(prefix_+"JetCharge",  mat_d_JetCharge,  prefix_+"JetCharge["+prefix_+"NJets]/D");
  }
  
  if (useCaloJets_ || useJPTJets_) {
    if (debug_) std::cout<<"Saving Calo/JPT specific information"<<std::endl;
    mJetData->Branch(prefix_+"JetfHPD", mat_d_JetfHPD, prefix_+"JetfHPD["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"JetfRBX", mat_d_JetfRBX, prefix_+"JetfRBX["+prefix_+"NJets]/D");
    mJetData->Branch(prefix_+"Jetn90",  mat_d_JetN90,  prefix_+"Jetn90["+prefix_+"NJets]/D");
  
    //information about associated tracks
    mJetData->Branch(prefix_+"JetTrackPt",          mat_d_JetTrackPt,          prefix_+"JetTrackPt["+prefix_+"NJets]/D"); 
    mJetData->Branch(prefix_+"JetTrackPhi",         mat_d_JetTrackPhi,         prefix_+"JetTrackPhi["+prefix_+"NJets]/D"); 
    mJetData->Branch(prefix_+"JetTrackPhiWeighted", mat_d_JetTrackPhiWeighted, prefix_+"JetTrackPhiWeighted["+prefix_+"NJets]/D"); 
    mJetData->Branch(prefix_+"JetTrackNo",          mat_i_JetTrackNo,          prefix_+"JetTrackNo["+prefix_+"NJets]/I");
  
  }
  
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_EDM_PLUGIN(JetAnalyzerPAT);

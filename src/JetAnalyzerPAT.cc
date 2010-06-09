
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
// $Id: JetAnalyzerPAT.cc,v 1.4 2010/05/20 19:39:52 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/JetAnalyzerPAT.h"

#include <TMath.h>
#include <sstream>

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


  m_JetPreselection = false;
  bool jet_result = true;
  edm::LogVerbatim("DiJetEvent::JetAnalyzerPAT") << " Start  " << std::endl;

  edm::Handle< std::vector<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetTag_, jetHandle);
  if ( !jetHandle.isValid() ) {
    edm::LogWarning("DiJetEvent::JetAnalyzerPAT") << "No Jet results for InputTag " << jetTag_;
    return false;
  }

  //get number of jets
  m_NJets = jetHandle->size();
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Processing Jets for InputTag " << jetTag_;
  if (debug_) std::cout<< "Processing "<<jetHandle->size() <<" Jets for InputTag " << jetTag_<<std::endl;
  if (debug_) {
    if (m_NJets) {
      std::cout<< "isCalo " <<(*jetHandle)[0].isCaloJet()  <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isJPT "  <<(*jetHandle)[0].isJPTJet()   <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isPF "   <<(*jetHandle)[0].isPFJet()    <<" Jets for InputTag " << jetTag_<<std::endl;
      //std::cout<< "isTrack "<<(*jetHandle)[0].isTrackJet() <<" Jets for InputTag " << jetTag_<<std::endl;
      std::cout<< "isBasic "<<(*jetHandle)[0].isBasicJet() <<" Jets for InputTag " << jetTag_<<std::endl;
    }
  }

  // Add the jets
  int i = 0;
  double jetsumpx = 0;
  double jetsumpy = 0;
  double jetsumpt = 0;

  double gensumpx = 0;
  double gensumpy = 0;
  double gensumpt = 0;

  if ( m_NJets >50 ) m_NJets = 50;
  for (int k=0;k<m_NJets;k++){
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

	if (debug_) std::cout<<"Passed minimum jet id requirements"<<std::endl;
	

	if (theJet.isCaloJet()) {
	  
	  if (debug_) std::cout<<"Getting track information from jets"<<std::endl;
	  const reco::TrackRefVector & mrTracksInJet = theJet.associatedTracks();
	  
	  m_JetTrackPt[k]          = 0;
	  m_JetTrackPhi[k]         = 0;
	  m_JetTrackPhiWeighted[k] = 0;
	  m_JetTrackNo[k]          = 0;
	  
	  float JetPhi = theJet.phi();
	  
	  for (reco::TrackRefVector::iterator aIter = mrTracksInJet.begin();aIter!= mrTracksInJet.end();aIter++)
	    {
	      m_JetTrackPt[k] += (*aIter)->pt();
	      float myPhi = (*aIter)->phi();
	      if( JetPhi > 2. ) {
		if(myPhi<0) myPhi = myPhi + 2*TMath::Pi();
	      }
	      if( JetPhi < -2. ) {
		if(myPhi>0) myPhi = myPhi - 2*TMath::Pi();
	      }
	      m_JetTrackPhiWeighted[k] += (*aIter)->pt()*myPhi;
	      m_JetTrackPhi[k]         += myPhi;
	      m_JetTrackNo[k]++;
	      
	    }
	  
	  m_JetTrackPhiWeighted[k] = m_JetTrackPhiWeighted[k]/m_JetTrackPt[k];
	  m_JetTrackPhi[k]         = m_JetTrackPhi[k]/float(m_JetTrackNo[k]);
	}

	m_JetE[i]      = theJet.energy();
	m_JetPt[i]     = theJet.pt();
	m_JetEt[i]     = theJet.et();
	m_JetPx[i]     = theJet.momentum().X();
	m_JetPy[i]     = theJet.momentum().Y();
	m_JetPz[i]     = theJet.momentum().Z();
	m_JetEta[i]    = theJet.eta();
	m_JetPhi[i]    = theJet.phi();
	m_JetCharge[i] = theJet.jetCharge();
	m_JetNConst[i] = theJet.nConstituents();
	
	//Uncorrected values
	m_JetRawE[i]    = uncorrJet.energy();
	m_JetRawPt[i]   = uncorrJet.pt();
	m_JetRawEt[i]   = uncorrJet.et();
	m_JetRawPx[i]   = uncorrJet.momentum().X();
	m_JetRawPy[i]   = uncorrJet.momentum().Y();
	m_JetRawPz[i]   = uncorrJet.momentum().Z();

	//Calo jet type specific
	if (useCaloJets_ ) {
	  JetIDSelectionFunctor jetIDMinimal( JetIDSelectionFunctor::PURE09,
					      JetIDSelectionFunctor::MINIMAL );
	  
	  JetIDSelectionFunctor jetIDLoose( JetIDSelectionFunctor::PURE09,
					    JetIDSelectionFunctor::LOOSE );
	  
	  JetIDSelectionFunctor jetIDTight( JetIDSelectionFunctor::PURE09,
					    JetIDSelectionFunctor::TIGHT );
	  
	  pat::strbitset ret = jetIDLoose.getBitTemplate();
	  
	  ret.set(false);
	  m_JetIDMinimal[k] = jetIDMinimal(theJet, ret);
	  ret.set(false);
	  m_JetIDLoose[k]   = jetIDLoose(theJet, ret);
	  ret.set(false);
	  m_JetIDTight[k]   = jetIDTight(theJet, ret);
	  
	  m_JetFem[i]  = theJet.emEnergyFraction();
	  m_JetFhad[i] = theJet.energyFractionHadronic();
	}

	if (useCaloJets_ || useJPTJets_) {
	  m_JetN90[i]  = theJet.jetID().n90Hits;
	  m_JetfHPD[i] = theJet.jetID().fHPD;
	  m_JetfRBX[i] = theJet.jetID().fRBX;
	}

	if (useJPTJets_ || usePFJets_) {
	  m_JetChargedFem[i]  = theJet.chargedEmEnergyFraction();
	  m_JetNeutralFem[i]  = theJet.neutralEmEnergyFraction();
	  m_JetChargedFhad[i] = theJet.chargedHadronEnergyFraction();
	  m_JetNeutralFhad[i] = theJet.neutralHadronEnergyFraction();

	  m_JetChargedMult[i] = theJet.chargedMultiplicity();
	  m_JetNeutralMult[i] = theJet.neutralMultiplicity();
	  m_JetElecMult[i]    = theJet.elecMultiplicity();
	  m_JetMuonMult[i]    = theJet.muonMultiplicity();

	  m_JetFem[i]  = theJet.neutralEmEnergyFraction()+
	    theJet.chargedEmEnergyFraction();
	  m_JetFhad[i] = theJet.neutralHadronEnergyFraction()+
	    theJet.chargedHadronEnergyFraction();
	}

	if (useJPTJets_) {
	}
	//PF jet type specific variables
	if (usePFJets_) {
	  PFJetIDSelectionFunctor jetIDLoose( JetIDSelectionFunctor::FIRSTDATA,
					      JetIDSelectionFunctor::LOOSE );
	  
	  PFJetIDSelectionFunctor jetIDTight( JetIDSelectionFunctor::FIRSTDATA,
					      JetIDSelectionFunctor::TIGHT );
	  
	  pat::strbitset ret = jetIDLoose.getBitTemplate();
	
	  ret.set(false);
	  m_JetIDLoose[k]   = jetIDLoose(theJet, ret);
	  ret.set(false);
	  m_JetIDTight[k]   = jetIDTight(theJet, ret);

	  m_JetChargedFmu[i]  = theJet.muonEnergyFraction();
	  m_JetChargedFele[i] = theJet.electronEnergy() / theJet.energy();
	  m_JetChargedFpho[i] = theJet.photonEnergyFraction();

	  m_JetHFFem[i]  = theJet.HFEMEnergyFraction();
	  m_JetHFFhad[i] = theJet.HFHadronEnergyFraction();
	  
	  m_JetChargedHadMult[i] = theJet.chargedHadronMultiplicity();
	  m_JetNeutralHadMult[i] = theJet.neutralHadronMultiplicity();
	  m_JetPhotonMult[i]     = theJet.photonMultiplicity();
	  m_JetElecMult[i]       = theJet.electronMultiplicity();
 	}
	
	//get jet flavour information
	m_JetPartonFlavour[i]   = theJet.partonFlavour();

	//get b-tagging information
	m_JetBTag_TCHE[i]           = theJet.bDiscriminator("trackCountingHighEffBJetTags");
	m_JetBTag_TCHP[i]           = theJet.bDiscriminator("trackCountingHighPurBJetTags");
	m_JetBTag_jetProb[i]        = theJet.bDiscriminator("jetProbabilityBJetTags");
	m_JetBTag_jetBProb[i]       = theJet.bDiscriminator("jetBProbabilityBJetTags");
	m_JetBTag_SSVHE[i]          = theJet.bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
	m_JetBTag_SSVHP[i]          = theJet.bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
	m_JetBTag_CSV[i]            = theJet.bDiscriminator("combinedSecondaryVertexBJetTags");
	m_JetBTag_CSVMVA[i]         = theJet.bDiscriminator("combinedSecondaryVertexMVABJetTags");
	m_JetBTag_SoftLepton[i]     = theJet.bDiscriminator("softMuonBJetTags");
	m_JetBTag_SoftLeptonByIP[i] = theJet.bDiscriminator("softMuonByIP3dBJetTags");
	m_JetBTag_SoftLeptonByPt[i] = theJet.bDiscriminator("softMuonByPtBJetTags");


	//Get gen information for jet	
	if(theJet.genJet()!= 0) {
	  m_JetGenPt[i]  = theJet.genJet()->pt();
	  m_JetGenE[i]   = theJet.genJet()->energy();
	  m_JetGenEt[i]  = theJet.genJet()->et();
	  m_JetGenPx[i]  = theJet.genJet()->momentum().X();
	  m_JetGenPy[i]  = theJet.genJet()->momentum().Y();
	  m_JetGenPz[i]  = theJet.genJet()->momentum().z();
	  m_JetGenEta[i] = theJet.genJet()->eta();
	  m_JetGenPhi[i] = theJet.genJet()->phi();
	}
	else {
	  m_JetGenPt[i]  = -999;
	  m_JetGenE[i]   = -999;
	  m_JetGenEt[i]  = -999;
	  m_JetGenPx[i]  = -999;
	  m_JetGenPy[i]  = -999;
	  m_JetGenPz[i]  = -999;
	  m_JetGenEta[i] = -999;
	  m_JetGenPhi[i] = -999;
	}

	if(theJet.genParton() != 0){
	  m_JetPartonId[i]     = theJet.genParton()->pdgId();
	  m_JetPartonPx[i]     = theJet.genParton()->px();
	  m_JetPartonPy[i]     = theJet.genParton()->py();
	  m_JetPartonPz[i]     = theJet.genParton()->pz();
	  m_JetPartonEt[i]     = theJet.genParton()->et();
	  m_JetPartonPhi[i]    = theJet.genParton()->phi();
	  m_JetPartonEta[i]    = theJet.genParton()->eta();
	  m_JetPartonEnergy[i] = theJet.genParton()->energy();
	  m_JetPartonMother[i] = theJet.genParton()->mother()->pdgId();
	}
	else{
	  m_JetPartonId[i]     = -999;
	  m_JetPartonPx[i]     = -999;
	  m_JetPartonPy[i]     = -999;
	  m_JetPartonPz[i]     = -999;
	  m_JetPartonEt[i]     = -999;
	  m_JetPartonPhi[i]    = -999;
	  m_JetPartonEta[i]    = -999;
	  m_JetPartonEnergy[i] = -999;
	  m_JetPartonMother[i] = -999;
	}
	i++;
      }
    }
  }
  
  m_NJets  = i;
  m_Ht     = jetsumpt;
  m_MHx    = -jetsumpx;
  m_MHy    = -jetsumpy;
  m_MHt    = -sqrt(jetsumpx*jetsumpx+jetsumpy*jetsumpy);
  
  m_GenHt  = gensumpt;
  m_GenMHx = -gensumpx;
  m_GenMHy = -gensumpy;
  m_GenMHt = -sqrt(gensumpx*gensumpx+gensumpy*gensumpy);
  
  jet_result = m_JetPreselection;
  return jet_result;
}


//________________________________________________________________________________________
void JetAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  

  mJetData->Branch(prefix_+"NJets",   &m_NJets,   prefix_+"NJets/int");  
  mJetData->Branch(prefix_+"Ht",      &m_Ht,      prefix_+"Ht/double");
  mJetData->Branch(prefix_+"MHx",     &m_MHx,     prefix_+"MHx/double");
  mJetData->Branch(prefix_+"MHy",     &m_MHy,     prefix_+"MHy/double");
  mJetData->Branch(prefix_+"MHt",     &m_MHt,     prefix_+"MHt/double");
    
  mJetData->Branch(prefix_+"JetE",      m_JetE,      prefix_+"JetE["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetEt",     m_JetEt,     prefix_+"JetEt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetPt",     m_JetPt,     prefix_+"JetPt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetPx",     m_JetPx,     prefix_+"JetPx["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetPy",     m_JetPy,     prefix_+"JetPy["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetPz",     m_JetPz,     prefix_+"JetPz["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawE",   m_JetRawE,   prefix_+"JetRawE["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawEt",  m_JetRawEt,  prefix_+"JetRawEt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawPt",  m_JetRawPt,  prefix_+"JetRawPt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawPx",  m_JetRawPx,  prefix_+"JetRawPx["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawPy",  m_JetRawPy,  prefix_+"JetRawPy["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetRawPz",  m_JetRawPz,  prefix_+"JetRawPz["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetEta",    m_JetEta,    prefix_+"JetEta["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetPhi",    m_JetPhi,    prefix_+"JetPhi["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetFem",    m_JetFem,    prefix_+"JetFem["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetFhad",   m_JetFhad,   prefix_+"JetFhad["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetCharge", m_JetCharge, prefix_+"JetCharge["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetNConst", m_JetNConst, prefix_+"JetNConst["+prefix_+"NJets]/double");
  //mJetData->Branch(prefix_+"JetHemi", m_JetHemi, prefix_+"JetHemi["+prefix_+"NJets]/int");
  mJetData->Branch(prefix_+"JetPreselection", &m_JetPreselection, prefix_+"JetPreselection/bool");
  mJetData->Branch(prefix_+"JetIDMinimal", m_JetIDMinimal, prefix_+"JetIDMinimal["+prefix_+"NJets]/bool");
  mJetData->Branch(prefix_+"JetIDLoose",   m_JetIDLoose,   prefix_+"JetIDLoose["+prefix_+"NJets]/bool");
  mJetData->Branch(prefix_+"JetIDTight",   m_JetIDTight,   prefix_+"JetIDTight["+prefix_+"NJets]/bool");

  //b-tagging information
  mJetData->Branch(prefix_+"JetBTag_TCHE",            m_JetBTag_TCHE,            prefix_+"JetBTag_TCHE["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_TCHP",            m_JetBTag_TCHP,            prefix_+"JetBTag_TCHP["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_jetProb",         m_JetBTag_jetProb,         prefix_+"JetBTag_jetProb["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_jetBProb",        m_JetBTag_jetBProb,        prefix_+"JetBTag_jetBProb["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_SSVHE",           m_JetBTag_SSVHE,           prefix_+"JetBTag_SSVHE["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_SSVHP",           m_JetBTag_SSVHP,           prefix_+"JetBTag_SSVHP["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_CSV",             m_JetBTag_CSV,             prefix_+"JetBTag_CSV["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_CSVMVA",          m_JetBTag_CSVMVA,          prefix_+"JetBTag_CSVMVA["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_SoftLepton",      m_JetBTag_SoftLepton,      prefix_+"JetBTag_SoftLepton["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByIP",  m_JetBTag_SoftLeptonByIP,  prefix_+"JetBTag_SoftLeptonByIP["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetBTag_SoftLeptonByPt",  m_JetBTag_SoftLeptonByPt,  prefix_+"JetBTag_SoftLeptonByPt["+prefix_+"NJets]/double");

  //information about associated gen jets
  mJetData->Branch(prefix_+"GenHt",    &m_GenHt,     prefix_+"GenHt/double");
  mJetData->Branch(prefix_+"GenMHt",   &m_GenMHt,    prefix_+"GenMHt/double");
  mJetData->Branch(prefix_+"JetGenE" ,  m_JetGenE,   prefix_+"JetGenE["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenEt",  m_JetGenEt,  prefix_+"JetGenEt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenPt",  m_JetGenPt,  prefix_+"JetGenPt["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenPx",  m_JetGenPx,  prefix_+"JetGenPx["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenPy",  m_JetGenPy,  prefix_+"JetGenPy["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenPz",  m_JetGenPz,  prefix_+"JetGenPz["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenEta", m_JetGenEta, prefix_+"JetGenEta["+prefix_+"NJets]/double");
  mJetData->Branch(prefix_+"JetGenPhi", m_JetGenPhi, prefix_+"JetGenPhi["+prefix_+"NJets]/double");
    
  //information about associated partons
  mJetData->Branch(prefix_+"JetPartonId",         m_JetPartonId,         prefix_+"JetPartonId["+prefix_+"NJets]/int"); 
  mJetData->Branch(prefix_+"JetPartonMother",     m_JetPartonMother,     prefix_+"JetPartonMother["+prefix_+"NJets]/int"); 
  mJetData->Branch(prefix_+"JetPartonPx",         m_JetPartonPx,         prefix_+"JetPartonPx["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonPy",         m_JetPartonPy,         prefix_+"JetPartonPy["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonPz",         m_JetPartonPz,         prefix_+"JetPartonPz["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonEt",         m_JetPartonEt,         prefix_+"JetPartonEt["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonE" ,         m_JetPartonEnergy,     prefix_+"JetPartonE["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonPhi",        m_JetPartonPhi,        prefix_+"JetPartonPhi["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonEta",        m_JetPartonEta,        prefix_+"JetPartonEta["+prefix_+"NJets]/double"); 
  mJetData->Branch(prefix_+"JetPartonFlavour",    m_JetPartonFlavour,    prefix_+"JetPartonFlavour["+prefix_+"NJets]/int");
    

  if (useJPTJets_ || usePFJets_) {
    mJetData->Branch(prefix_+"JetChargedFem",  m_JetChargedFem,  prefix_+"JetChargedFem["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetNeutralFem",  m_JetNeutralFem,  prefix_+"JetNeutralFem["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedFhad", m_JetChargedFhad, prefix_+"JetChargedFhad["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetNeutralFhad", m_JetNeutralFhad, prefix_+"JetNeutralFhad["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedMult", m_JetChargedMult, prefix_+"JetChargedMult["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetElecMulti",   m_JetElecMult,    prefix_+"JetElecMulti["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetMuonMulti",   m_JetMuonMult,    prefix_+"JetMuonMulti["+prefix_+"NJets]/int");
  }

  if (usePFJets_) {
    mJetData->Branch(prefix_+"JetChargedFmu",  m_JetChargedFmu,  prefix_+"JetChargedFmu["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedFele", m_JetChargedFele, prefix_+"JetChargedFele["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedFpho", m_JetChargedFpho, prefix_+"JetChargedFpho["+prefix_+"NJets]/double");

    mJetData->Branch(prefix_+"JetHFFem",  m_JetHFFem,  prefix_+"JetHFFem["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetHFFhad", m_JetHFFhad, prefix_+"JetHFFhad["+prefix_+"NJets]/double");

    mJetData->Branch(prefix_+"JetChargedHadMult", m_JetChargedHadMult, prefix_+"JetChargedHadMult["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetNeutralHadMult", m_JetNeutralHadMult, prefix_+"JetNeutralHadMult["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetPhotonMulti",    m_JetPhotonMult,     prefix_+"JetPhotonMulti["+prefix_+"NJets]/int");
  }

  if (useTrackJets_) {
    mJetData->Branch(prefix_+"JetCharge",  m_JetCharge,  prefix_+"JetCharge["+prefix_+"NJets]/double");
  }

  if (useCaloJets_ || useJPTJets_) {
    mJetData->Branch(prefix_+"JetfHPD", m_JetfHPD, prefix_+"JetfHPD["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetfRBX", m_JetfRBX, prefix_+"JetfRBX["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"Jetn90",  m_JetN90,  prefix_+"Jetn90["+prefix_+"NJets]/double");

    //information about associated tracks
    mJetData->Branch(prefix_+"JetTrackPt",          m_JetTrackPt,          prefix_+"JetTrackPt["+prefix_+"NJets]/double"); 
    mJetData->Branch(prefix_+"JetTrackPhi",         m_JetTrackPhi,         prefix_+"JetTrackPhi["+prefix_+"NJets]/double"); 
    mJetData->Branch(prefix_+"JetTrackPhiWeighted", m_JetTrackPhiWeighted, prefix_+"JetTrackPhiWeighted["+prefix_+"NJets]/double"); 
    mJetData->Branch(prefix_+"JetTrackNo",          m_JetTrackNo,          prefix_+"JetTrackNo["+prefix_+"NJets]/int");

  }
  
  edm::LogInfo("DiJetEvent::JetAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_EDM_PLUGIN(JetAnalyzerPAT);

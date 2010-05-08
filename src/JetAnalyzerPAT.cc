
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
// $Id: JetAnalyzerPAT.cc,v 1.4 2010/04/05 15:25:37 sturdy Exp $
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
  useCaloJets_  = jetParams.getUntrackedParameter<bool>("useCaloJets",true);
  useTrackJets_ = jetParams.getUntrackedParameter<bool>("useTrackJets",false);

  jetTag_     = jetParams.getUntrackedParameter<edm::InputTag>("jetTag");
  jptJetTag_  = jetParams.getUntrackedParameter<edm::InputTag>("jptTag");

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

  edm::Handle< std::vector<pat::Jet> > jptHandle;
  if (useJPTJets_) {
    // get the JPT-corrected pat::Jets
    iEvent.getByLabel(jptJetTag_, jptHandle);
    if ( !jptHandle.isValid() ) {
      edm::LogWarning("DiJetEvent::JetAnalyzerPAT") << "No JetCorrFactor results for InputTag " << jptJetTag_;
      return false;
    }
  }

  //get number of jets
  m_NJets = jetHandle->size();

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
    const pat::Jet& uncorrJet = ((*jetHandle)[k].isCaloJet())? (*jetHandle)[k].correctedJet("RAW"): (*jetHandle)[k];

    /******************Construct the HT/MHT from the jet collection***************************/
    if ((*jetHandle)[k].pt() > htMinPt_) {
      if (fabs((*jetHandle)[k].eta()) < htMaxEta_) {
	
	jetsumpt += (*jetHandle)[k].pt();
	jetsumpx += (*jetHandle)[k].momentum().X();
	jetsumpy += (*jetHandle)[k].momentum().Y();
	
	if((*jetHandle)[k].genJet()!= 0) {
	  gensumpt += (*jetHandle)[k].genJet()->pt();
	  gensumpx += (*jetHandle)[k].genJet()->momentum().X();
	  gensumpy += (*jetHandle)[k].genJet()->momentum().Y();
	}
      }
    }


    /******************Now collect all the Jet related variables***************************/
    if ((*jetHandle)[k].pt() > jetMinPt_) {
      if (fabs((*jetHandle)[k].eta()) < jetMaxEta_) {
	
	const reco::TrackRefVector & mrTracksInJet = (*jetHandle)[k].associatedTracks();
	
	m_JetTrackPt[k]          = 0;
	m_JetTrackPhi[k]         = 0;
	m_JetTrackPhiWeighted[k] = 0;
	m_JetTrackNo[k]          = 0;
	
	float JetPhi = (*jetHandle)[k].phi();
	
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
	
	m_JetE[i]    = (*jetHandle)[k].energy();
	m_JetPt[i]   = (*jetHandle)[k].pt();
	m_JetEt[i]   = (*jetHandle)[k].et();
	m_JetPx[i]   = (*jetHandle)[k].momentum().X();
	m_JetPy[i]   = (*jetHandle)[k].momentum().Y();
	m_JetPz[i]   = (*jetHandle)[k].momentum().Z();
	m_JetEta[i]  = (*jetHandle)[k].eta();
	m_JetPhi[i]  = (*jetHandle)[k].phi();
	
	//Uncorrected values
	m_JetRawE[i]    = uncorrJet.energy();
	m_JetRawPt[i]   = uncorrJet.pt();
	m_JetRawEt[i]   = uncorrJet.et();
	m_JetRawPx[i]   = uncorrJet.momentum().X();
	m_JetRawPy[i]   = uncorrJet.momentum().Y();
	m_JetRawPz[i]   = uncorrJet.momentum().Z();

	//Calo jet type specific
	if (useCaloJets_||useJPTJets_) {
	  m_JetN90[i]  = (*jetHandle)[k].jetID().n90Hits;
	  m_JetfHPD[i] = (*jetHandle)[k].jetID().fHPD;
	  m_JetfRBX[i] = (*jetHandle)[k].jetID().fRBX;
	  m_JetFem[i]  = (*jetHandle)[k].emEnergyFraction();
	  m_JetFhad[i] = (*jetHandle)[k].energyFractionHadronic();
	}
	
	//PF jet type specific variables
	if (usePFJets_) {
	  m_JetChargedFem[i]  = (*jetHandle)[k].chargedEmEnergyFraction();
	  m_JetNeutralFem[i]  = (*jetHandle)[k].neutralEmEnergyFraction();
	  m_JetChargedFhad[i] = (*jetHandle)[k].chargedHadronEnergyFraction();
	  m_JetNeutralFhad[i] = (*jetHandle)[k].neutralHadronEnergyFraction();
	  m_JetChargedFmu[i]  = (*jetHandle)[k].chargedMuEnergyFraction();
	  
	  m_JetChargedMult[i]  = (*jetHandle)[k].chargedMultiplicity();
	  m_JetNeutralMult[i]  = (*jetHandle)[k].neutralMultiplicity();
	  m_JetMuonMult[i]       = (*jetHandle)[k].muonMultiplicity();

	  m_JetFem[i] = (*jetHandle)[k].neutralEmEnergyFraction()+
	    (*jetHandle)[k].chargedEmEnergyFraction();
	  m_JetFhad[i] = (*jetHandle)[k].neutralHadronEnergyFraction()+
	    (*jetHandle)[k].chargedHadronEnergyFraction();
	}
	
	//get jet flavour information
	m_JetPartonFlavour[i]   = (*jetHandle)[k].partonFlavour();

	//get b-tagging information
	m_JetBTag_TCHE[i]           = (*jetHandle)[k].bDiscriminator("trackCountingHighEffBJetTags");
	m_JetBTag_TCHP[i]           = (*jetHandle)[k].bDiscriminator("trackCountingHighPurBJetTags");
	m_JetBTag_jetProb[i]        = (*jetHandle)[k].bDiscriminator("jetProbabilityBJetTags");
	m_JetBTag_jetBProb[i]       = (*jetHandle)[k].bDiscriminator("jetBProbabilityBJetTags");
	m_JetBTag_SSVHE[i]          = (*jetHandle)[k].bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
	m_JetBTag_SSVHP[i]          = (*jetHandle)[k].bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
	m_JetBTag_CSV[i]            = (*jetHandle)[k].bDiscriminator("combinedSecondaryVertexBJetTags");
	m_JetBTag_CSVMVA[i]         = (*jetHandle)[k].bDiscriminator("combinedSecondaryVertexMVABJetTags");
	m_JetBTag_SoftLepton[i]     = (*jetHandle)[k].bDiscriminator("softMuonBJetTags");
	m_JetBTag_SoftLeptonByIP[i] = (*jetHandle)[k].bDiscriminator("softMuonByIP3dBJetTags");
	m_JetBTag_SoftLeptonByPt[i] = (*jetHandle)[k].bDiscriminator("softMuonByPtBJetTags");


	//Get gen information for jet	
	if((*jetHandle)[k].genJet()!= 0) {
	  m_JetGenPt[i]  = (*jetHandle)[k].genJet()->pt();
	  m_JetGenE[i]   = (*jetHandle)[k].genJet()->energy();
	  m_JetGenEt[i]  = (*jetHandle)[k].genJet()->et();
	  m_JetGenPx[i]  = (*jetHandle)[k].genJet()->momentum().X();
	  m_JetGenPy[i]  = (*jetHandle)[k].genJet()->momentum().Y();
	  m_JetGenPz[i]  = (*jetHandle)[k].genJet()->momentum().z();
	  m_JetGenEta[i] = (*jetHandle)[k].genJet()->eta();
	  m_JetGenPhi[i] = (*jetHandle)[k].genJet()->phi();
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

	if((*jetHandle)[k].genParton() != 0){
	  m_JetPartonId[i]     = (*jetHandle)[k].genParton()->pdgId();
	  m_JetPartonPx[i]     = (*jetHandle)[k].genParton()->px();
	  m_JetPartonPy[i]     = (*jetHandle)[k].genParton()->py();
	  m_JetPartonPz[i]     = (*jetHandle)[k].genParton()->pz();
	  m_JetPartonEt[i]     = (*jetHandle)[k].genParton()->et();
	  m_JetPartonPhi[i]    = (*jetHandle)[k].genParton()->phi();
	  m_JetPartonEta[i]    = (*jetHandle)[k].genParton()->eta();
	  m_JetPartonEnergy[i] = (*jetHandle)[k].genParton()->energy();
	  m_JetPartonMother[i] = (*jetHandle)[k].genParton()->mother()->pdgId();
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

  //determine preselection requirement based on calo jets
  //if (m_NJets>int(selJetMaxEta_.size())) {
  //  m_JetPreselection = true;
  //  for (int caloj = 0; caloj < int(selJetMaxEta_.size()); ++caloj) {
  //    if (m_JetEta[caloj] > selJetMaxEta_.at(caloj)) m_JetPreselection = false;
  //    if (m_JetPt[caloj]  < selJetMinPt_.at(caloj))  m_JetPreselection = false;
  //    if (m_JetFem[caloj] > selJetMaxEMF_.at(caloj)) m_JetPreselection = false;
  //    if (m_JetFem[caloj] < selJetMinEMF_.at(caloj)) m_JetPreselection = false;
  //  }
  //}

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
    
  mJetData->Branch(prefix_+"JetE",     m_JetE,     prefix_+"JetE[NJets]/double");
  mJetData->Branch(prefix_+"JetEt",    m_JetEt,    prefix_+"JetEt[NJets]/double");
  mJetData->Branch(prefix_+"JetPt",    m_JetPt,    prefix_+"JetPt[NJets]/double");
  mJetData->Branch(prefix_+"JetPx",    m_JetPx,    prefix_+"JetPx[NJets]/double");
  mJetData->Branch(prefix_+"JetPy",    m_JetPy,    prefix_+"JetPy[NJets]/double");
  mJetData->Branch(prefix_+"JetPz",    m_JetPz,    prefix_+"JetPz[NJets]/double");
  mJetData->Branch(prefix_+"JetRawE",  m_JetRawE,  prefix_+"JetRawE[NJets]/double");
  mJetData->Branch(prefix_+"JetRawEt", m_JetRawEt, prefix_+"JetRawEt[NJets]/double");
  mJetData->Branch(prefix_+"JetRawPt", m_JetRawPt, prefix_+"JetRawPt[NJets]/double");
  mJetData->Branch(prefix_+"JetRawPx", m_JetRawPx, prefix_+"JetRawPx[NJets]/double");
  mJetData->Branch(prefix_+"JetRawPy", m_JetRawPy, prefix_+"JetRawPy[NJets]/double");
  mJetData->Branch(prefix_+"JetRawPz", m_JetRawPz, prefix_+"JetRawPz[NJets]/double");
  mJetData->Branch(prefix_+"JetEta",   m_JetEta,   prefix_+"JetEta[NJets]/double");
  mJetData->Branch(prefix_+"JetPhi",   m_JetPhi,   prefix_+"JetPhi[NJets]/double");
  mJetData->Branch(prefix_+"JetFem",   m_JetFem,   prefix_+"JetFem[NJets]/double");
  mJetData->Branch(prefix_+"JetFhad",  m_JetFhad,  prefix_+"JetFhad[NJets]/double");
  //mJetData->Branch(prefix_+"JetHemi", m_JetHemi, prefix_+"JetHemi[NJets]/int");
  mJetData->Branch(prefix_+"JetPreselection", &m_JetPreselection, prefix_+"JetPreselection/bool");

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
  mJetData->Branch(prefix_+"GenHt",   &m_GenHt,     prefix_+"GenHt/double");
  mJetData->Branch(prefix_+"GenMHt",  &m_GenMHt,    prefix_+"GenMHt/double");
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
    

  if (usePFJets_) {
    mJetData->Branch(prefix_+"JetChargedFhad", m_JetChargedFhad, prefix_+"JetChargedFhad["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetNeutralFhad", m_JetNeutralFhad, prefix_+"JetNeutralFhad["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedFem",  m_JetChargedFem,  prefix_+"JetChargedFem["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetNeutralFem",  m_JetNeutralFem,  prefix_+"JetNeutralFem["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedFmu",  m_JetChargedFmu,  prefix_+"JetChargedFmu["+prefix_+"NJets]/double");
    mJetData->Branch(prefix_+"JetChargedMult", m_JetChargedMult, prefix_+"JetChargedMult["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetNeutralMult", m_JetNeutralMult, prefix_+"JetNeutralMult["+prefix_+"NJets]/int");
    mJetData->Branch(prefix_+"JetMuonMulti",   m_JetMuonMult,    prefix_+"JetMuonMulti["+prefix_+"NJets]/int");
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


// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      HTMHTAnalyzerPAT
// 
/**\class HTMHTAnalyzerPAT HTMHTAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/HTMHTAnalyzerPAT.cc

Description: Collects variables related to jets, performs dijet preselection
             Energy of jets = (50,50,30...), |eta|<2.5, 0.05<emfrac<0.95
             If successful, it stores the variables and returns the value of the check

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: HTMHTAnalyzerPAT.cc,v 1.4 2010/04/05 15:25:37 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/HTMHTAnalyzerPAT.h"

#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
HTMHTAnalyzerPAT::HTMHTAnalyzerPAT(const edm::ParameterSet& mhtParams, TTree* tmpAllData)
{ 
  mHTMHTData = tmpAllData;
  //defaults
  doMCData_     = false;
  debug_        = 0;
  prefix_       = "";
  // Preselection parameters
  //Basic jet information, minimum number, eta and pt requirement for all jets

  jetMaxEta_ = 5.0;
  jetMinPt_  = 0.;
  

  if (mhtParams.exists("debugMHT"))  debug_      = mhtParams.getUntrackedParameter<int>("debugMHT");
  if (mhtParams.exists("prefixMHT")) prefix_     = mhtParams.getUntrackedParameter<int>("prefixMHT");
  if (mhtParams.exists("jetMaxEta"))  jetMaxEta_ = mhtParams.getUntrackedParameter<double >("jetMaxEta");
  if (mhtParams.exists("jetMinPt"))   jetMinPt_  = mhtParams.getUntrackedParameter<double >("jetMinPt");

  doMCData_ = true;
  if (mhtParams.exists("doMCJets"))     doMCData_     = mhtParams.getUntrackedParameter<bool>("doMCJets");
  if (doMCData_) 
    if (mhtParams.exists("genJetTag"))    genJetTag_    = mhtParams.getUntrackedParameter<edm::InputTag>("genJetTag");
 
  // get the data tags
  jetTag_  = mhtParams.getUntrackedParameter<edm::InputTag>("jetTag");

  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree();
}


//________________________________________________________________________________________
HTMHTAnalyzerPAT::~HTMHTAnalyzerPAT() {
  delete mHTMHTData;  
}


//________________________________________________________________________________________
// Method called to for each event
bool HTMHTAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;

  m_HTMHTPreselection = false;
  bool htmht_result = true;
  edm::LogVerbatim("DiJetEvent::HTMHTAnalyzerPAT") << " Start  " << std::endl;

  edm::Handle< std::vector<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetTag_, jetHandle);
  if ( !jetHandle.isValid() ) {
    edm::LogWarning("DiJetEvent::HTMHTAnalyzerPAT") << "No Jet results for InputTag " << jetTag_;
    return false;
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
    
    if ((*jetHandle)[k].pt() >= jetMinPt_) {
      if (fabs((*jetHandle)[k].eta()) <= jetMaxEta_) {
	
	jetsumpt += (*jetHandle)[k].pt();
	jetsumpx += (*jetHandle)[k].momentum().X();
	jetsumpy += (*jetHandle)[k].momentum().Y();
	
	if((*jetHandle)[k].genJet()!= 0) {
	  gensumpt += (*jetHandle)[k].genJet()->pt();
	  gensumpx += (*jetHandle)[k].genJet()->momentum().X();
	  gensumpy += (*jetHandle)[k].genJet()->momentum().Y();}
	i++;
      }
    }
  }
  
  m_NJets  = i;
  m_Ht     = jetsumpt;
  m_MHx    = -jetsumpx;
  m_MHy    = -jetsumpy;
  m_MHt    = -sqrt(jetsumpx*jetsumpx+jetsumpy*jetsumpy);
  m_MHtphi = atan2(m_MHy,m_MHx);

  m_GenHt     = gensumpt;
  m_GenMHx    = -gensumpx;
  m_GenMHy    = -gensumpy;
  m_GenMHt    = -sqrt(gensumpx*gensumpx+gensumpy*gensumpy);
  m_GenMHtphi = atan2(m_GenMHy,m_GenMHx);

  htmht_result = m_HTMHTPreselection;
  return htmht_result;
}


//________________________________________________________________________________________
void HTMHTAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  

  mHTMHTData->Branch(prefix_+"NHTJets", &m_NJets,   prefix_+"NHTJets/int");  
  mHTMHTData->Branch(prefix_+"Ht",      &m_Ht,      prefix_+"Ht/double");
  mHTMHTData->Branch(prefix_+"MHt",     &m_MHt,     prefix_+"MHt/double");
  mHTMHTData->Branch(prefix_+"MHx",     &m_MHx,     prefix_+"MHx/double");
  mHTMHTData->Branch(prefix_+"MHy",     &m_MHy,     prefix_+"MHy/double");
  mHTMHTData->Branch(prefix_+"MHtphi",  &m_MHtphi,  prefix_+"MHtphi/double");
    

  //information about associated gen jets
  mHTMHTData->Branch(prefix_+"GenHt",     &m_GenHt,     prefix_+"GenHt/double");
  mHTMHTData->Branch(prefix_+"GenMHt",    &m_GenMHt,    prefix_+"GenMHt/double");
  mHTMHTData->Branch(prefix_+"GenMHx",    &m_GenMHx,    prefix_+"GenMHx/double");
  mHTMHTData->Branch(prefix_+"GenMHy",    &m_GenMHy,    prefix_+"GenMHy/double");
  mHTMHTData->Branch(prefix_+"GenMHtphi", &m_GenMHtphi, prefix_+"GenMHtphi/double");
  
  edm::LogInfo("DiJetEvent::HTMHTAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_EDM_PLUGIN(HTMHTAnalyzerPAT);

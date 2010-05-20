
// -*- C++ -*-
//
// Package:    SusyAnalysisNtuplePAT
// Class:      TriggerAnalyzerPAT
// 
/**\class TriggerAnalyzerPAT TriggerAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/TriggerAnalyzerPAT.cc

Description: Collects the trigger results and performs a basic trigger selection


*/
//
// Original Author:  Jared Sturdy (from SusyAnalysisNtuplePAT)
//         Created:  Mon Feb 18 15:40:44 CET 2008
// $Id: TriggerAnalyzerPAT.cc,v 1.3 2010/05/12 22:35:47 sturdy Exp $
//
//
//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TriggerAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
TriggerAnalyzerPAT::TriggerAnalyzerPAT(const edm::ParameterSet& triggerParams, TTree* tmpAllData):
  pathNames_(0), nEvents_(0), nWasRun_(0),
  nAccept_(0), nErrors_(0), hlWasRun_(0),
  hlAccept_(0), hlErrors_(0), init_(false)
{ 

  mTriggerData = tmpAllData;

  debug_   = triggerParams.getUntrackedParameter<int>("debugTriggers",0);
  doMCData_  = triggerParams.getUntrackedParameter<bool>("doMCTriggers",false);
 
  // trigger stuff
  l1TriggerResults_ = triggerParams.getUntrackedParameter<edm::InputTag>("l1TriggerResults");
  hlTriggerResults_ = triggerParams.getUntrackedParameter<edm::InputTag>("hlTriggerResults");
  // trigger path names
  pathNames_ = triggerParams.getUntrackedParameter< std::vector<std::string> >("pathNames");

  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree();
}


//________________________________________________________________________________________
TriggerAnalyzerPAT::~TriggerAnalyzerPAT() {
  delete mTriggerData;
}


//________________________________________________________________________________________
// Method called to for each event
bool TriggerAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;

  //bool preselection = false;
  edm::LogVerbatim("TriggerEvent") << " Start  " << std::endl;

  std::ostringstream dbg;

  trigger_result = true;

  //Trigger results
  edm::LogVerbatim("TriggerEvent") << " Trigger decision  " << std::endl;

  //get the trigger decision
  m_HLT1JET    = false;
  m_HLT2JET    = false;
  m_HLT1MET    = false;
  m_HLT1HT     = false;
  m_HLT1HT1MHT = false;
  m_HLT1Muon   = false;

  m_L1Muon1 = false;
  m_L1Muon2 = false;
  m_L1Muon3 = false;
  m_L1Muon4 = false;

  //L1 trigger results
  edm::Handle<L1GlobalTriggerReadoutRecord> l1GtHandle;
  iEvent.getByLabel(l1TriggerResults_, l1GtHandle);
  if ( !l1GtHandle.isValid() ) {
    edm::LogWarning("L1TriggerSelector") << "No trigger results for InputTag " << l1TriggerResults_;
    return false;
  }
  
  m_nL1Technical = nMaxL1Tech;
  for ( int l1tech = 0; l1tech < nMaxL1Tech; ++l1tech) {    
    m_L1TechnicalArray[l1tech] = l1GtHandle->technicalTriggerWord()[l1tech] ? 1:0;
  }  
  
  
  m_nL1Physics = nMaxL1Algo;
  for ( int l1phys = 0; l1phys < nMaxL1Algo; ++l1phys) {    
    m_L1PhysicsArray[l1phys] = l1GtHandle->decisionWord()[l1phys] ? 1:0;
  }

  // Get the HLT results and check validity
  edm::Handle<edm::TriggerResults> hltHandle;
  iEvent.getByLabel(hlTriggerResults_, hltHandle);
  if ( !hltHandle.isValid() ) {
    edm::LogWarning("HLTEventSelector") << "No trigger results for InputTag " << hlTriggerResults_;
    return false;
  }

  //  std::cout << " get results " << std::endl;

  // Get results
  const edm::TriggerNames & trgNames = iEvent.triggerNames(*hltHandle);
    
  unsigned int trgSize = trgNames.size();
  
  // Example for OR of all specified triggers

  edm::LogWarning("HLTEventSelector") << " triggers " << trgNames.size() << std::endl;

  if (!hltHandle.isValid()) {
    // triggerExists = false;
    std::cout << "HLTriggerResult Not Valid!" << std::endl;
    return false;
  }
  else {  
    if (hltHandle->wasrun()) nWasRun_++;
    const bool accept(hltHandle->accept());
    LogDebug("") << "HL TriggerResults decision: " << accept;
    if (accept) ++nAccept_;
    if (hltHandle->error() ) nErrors_++;
  }

  // decision for each HL algorithm
  const unsigned int n(pathNames_.size());
  for (unsigned int i=0; i!=n; ++i) {
    if (hltHandle->wasrun(i)) hlWasRun_[i]++;
    if (hltHandle->accept(i)) hlAccept_[i]++;
    if (hltHandle->error(i) ) hlErrors_[i]++;
  }
  
  m_nHLT=static_cast<int>(n);
  for(unsigned int i=0; i!=n; ++i) {
    m_HLTArray[i] = hltHandle->accept(i);
    m_HLTNames[i] = hltHandle->name(i);
  }

  //looping over list of trig path names
  for ( std::vector<std::string>::const_iterator i=pathNames_.begin();
	i!=pathNames_.end(); ++i ) {
    // Get index
 
    unsigned int index = trgNames.triggerIndex(*i);
    if ( index==trgSize ) {
      edm::LogWarning("HLTEventSelector") << "Unknown trigger name " << *i;
      continue;
    }
    if ( hltHandle->accept(index) ) {
      LogDebug("HLTEventSelector") << "Event selected by " << *i ;
      std::string trigName = *i;
      //m_HLTNames[i] = trigName;

      if (trigName == "HLT_Jet180")       m_HLT1JET    = true;
      if (trigName == "HLT_DiJetAve130")  m_HLT2JET    = true;
      if (trigName == "HLT_MET60")        m_HLT1MET    = true;
      if (trigName == "HLT_HT200")        m_HLT1HT     = true;
      if (trigName == "HLT_HT300_MHT100") m_HLT1HT1MHT = true;
      if (trigName == "HLT_Mu9")          m_HLT1Muon   = true; 
      
    } 
  }

  bool bptx_result = m_L1TechnicalArray[0];
  bool bsc_result  = m_L1TechnicalArray[40] || m_L1TechnicalArray[41];
  bool beam_halo_result = m_L1TechnicalArray[36] || m_L1TechnicalArray[37] || m_L1TechnicalArray[38] || m_L1TechnicalArray[39];
  
  if (doMCData_) trigger_result = bsc_result && !beam_halo_result;
  else           trigger_result = bptx_result && bsc_result && !beam_halo_result;

  return trigger_result;
}


//________________________________________________________________________________________

void TriggerAnalyzerPAT::printHLTreport( void ) {

  // prints an HLT report -- associates trigger bits with trigger names (prints #events fired the trigger etc)
  const unsigned int n(pathNames_.size());
  std::cout << "\n";
  std::cout << "HLT-Report " << "---------- Event  Summary ------------\n";
  std::cout << "HLT-Report"
	    << " Events total = " << nEvents_
	    << " wasrun = " << nWasRun_
	    << " passed = " << nAccept_
	    << " errors = " << nErrors_
	    << "\n";

  std::cout << std::endl;
  std::cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
  std::cout << "HLT-Report "
	    << std::right << std::setw(10) << "HLT  Bit#" << " "
	    << std::right << std::setw(10) << "WasRun" << " "
	    << std::right << std::setw(10) << "Passed" << " "
	    << std::right << std::setw(10) << "Errors" << " "
	    << "Name" << "\n";

  if (init_) {
    for (unsigned int i=0; i!=n; ++i) {
      std::cout << "HLT-Report "
		<< std::right << std::setw(10) << i << " "
		<< std::right << std::setw(10) << hlWasRun_[i] << " "
		<< std::right << std::setw(10) << hlAccept_[i] << " "
		<< std::right << std::setw(10) << hlErrors_[i] << " "
		<< pathNames_[i] << "\n";
    }
  } else {
    std::cout << "HLT-Report - No HL TriggerResults found!" << std::endl;
  }
  
  std::cout << std::endl;
  std::cout << "HLT-Report end!" << std::endl;
  std::cout << std::endl;

}


//________________________________________________________________________________________
void TriggerAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  mTriggerData->Branch("nHLT",    &m_nHLT,     "nHLT/I");
  mTriggerData->Branch("HLTArray", m_HLTArray, "HLTArray[nHLT]/I");
  mTriggerData->Branch("HLTNames", m_HLTNames, "HLTNames[nHLT]/string");
  //Level-1 Technical Triggers
  mTriggerData->Branch("nL1Technical",    &m_nL1Technical,     "nL1Technical/I");
  mTriggerData->Branch("L1TechnicalArray", m_L1TechnicalArray, "L1TechnicalArray[nL1Technical]/I");
  mTriggerData->Branch("L1TechnicalNames", m_L1TechnicalNames, "L1TechnicalNames[nL1Technical]/string");
  //Level-1 Physics Triggers
  mTriggerData->Branch("nL1Physics",    &m_nL1Physics,     "nL1Physics/I");
  mTriggerData->Branch("L1PhysicsArray", m_L1PhysicsArray, "L1PhysicsArray[nL1Physics]/I");
  mTriggerData->Branch("L1PhysicsNames", m_L1PhysicsNames, "L1PhysicsNames[nL1Physics]/string");

  //Trigger information
  mTriggerData->Branch("HLT1JET",    &m_HLT1JET,    "HLT1JET/bool");
  mTriggerData->Branch("HLT2JET",    &m_HLT2JET,    "HLT2JET/bool");
  mTriggerData->Branch("HLT1MET",    &m_HLT1MET,    "HLT1MET/bool");
  mTriggerData->Branch("HLT11HT",    &m_HLT1HT,     "HLT1HT/bool");
  mTriggerData->Branch("HLT1HT1MHT", &m_HLT1HT1MHT, "HLT1HT1MHT/bool");
  mTriggerData->Branch("HLT1MUON",   &m_HLT1Muon,   "HLT1MUON/bool");

  mTriggerData->Branch("L1MUON1",   &m_L1Muon1,   "L1MUON1/bool");
  mTriggerData->Branch("L1MUON2",   &m_L1Muon2,   "L1MUON2/bool");
  mTriggerData->Branch("L1MUON3",   &m_L1Muon3,   "L1MUON3/bool");
  mTriggerData->Branch("L1MUON4",   &m_L1Muon4,   "L1MUON4/bool");

  edm::LogInfo("TriggerEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TriggerAnalyzerPAT);

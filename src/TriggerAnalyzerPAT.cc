
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
// $Id: TriggerAnalyzerPAT.cc,v 1.5 2010/06/21 22:45:38 sturdy Exp $
//
//
//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TriggerAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>

#ifdef __CINT__ 
#pragma link C++ class std::map<std::string, bool >+; 
#pragma link C++ class std::map<std::string, int >+; 
#endif

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
  m_HLTMinBias = false;

  m_L1Muon1 = false;
  m_L1Muon2 = false;
  m_L1Muon3 = false;
  m_L1Muon4 = false;



  /******************************************************************
   * Here we do all the L1 related trigger stuff
   *
   *
   ******************************************************************/
  //L1 trigger results
  if (debug_)
    std::cout<<"Getting the L1 trigger results"<<std::endl;

  edm::Handle<L1GlobalTriggerReadoutRecord> l1GtHandle;
  iEvent.getByLabel(l1TriggerResults_, l1GtHandle);

  edm::ESHandle<L1GtTriggerMenu> L1menu;
  iSetup.get<L1GtTriggerMenuRcd>().get(L1menu) ;
  const L1GtTriggerMenu* theMenu = L1menu.product();
  
  edm::ESHandle<L1GtPrescaleFactors> psAlgo;
  iSetup.get<L1GtPrescaleFactorsAlgoTrigRcd>().get(psAlgo);
  
  edm::ESHandle<L1GtPrescaleFactors> psTech;
  iSetup.get<L1GtPrescaleFactorsTechTrigRcd>().get(psTech);

  if (debug_)
    std::cout<<"Getting the L1 trigger map"<<std::endl;
  //const AlgorithmMap& algoMap = L1menu->gtAlgorithmMap();
  //const AlgorithmMap& techMap = L1menu->gtTechnicalTriggerMap();
  const AlgorithmMap& algoMap = theMenu->gtAlgorithmMap();
  const AlgorithmMap& techMap = theMenu->gtTechnicalTriggerMap();

  if ( !l1GtHandle.isValid() || !L1menu.isValid() ) {
    edm::LogWarning("L1TriggerSelector") << "No trigger results for InputTag " << l1TriggerResults_;
    if (debug_)
      std::cout<<"L1 trigger results not valid"<<std::endl;
    return false;
  }

  //Method 1
  int nBx = 1; //what does this do ???
  const std::vector<bool>& vAlgoBool = l1GtHandle->decisionWord(nBx);
  const std::vector<int>&  vAlgoInt  = psAlgo->gtPrescaleFactors().at(l1GtHandle->gtFdlWord(nBx).gtPrescaleFactorIndexAlgo());

  const std::vector<bool>& vTechBool = l1GtHandle->technicalTriggerWord(nBx);
  const std::vector<int>&  vTechInt  = psTech->gtPrescaleFactors().at(l1GtHandle->gtFdlWord(nBx).gtPrescaleFactorIndexTech());

  int l1phys = 0;
  if (debug_)
    std::cout<<"Getting the L1 Physics trigger results"<<std::endl;
  for( AlgorithmMap::const_iterator it = algoMap.begin(); it != algoMap.end(); ++it) {
    //std::string l1AlgName = it->first;
    std::string l1AlgName = (it->second).algoName();
    bool l1AlgBit = vAlgoBool.at(it->second.algoBitNumber());
    int  l1AlgPre = vAlgoInt.at(it->second.algoBitNumber());
    l1triggered[l1AlgName] = l1AlgBit;
    l1prescaled[l1AlgName] = l1AlgPre;
    m_L1PhysicsArray[l1phys] = l1AlgBit;
    m_L1PhysicsNames[l1phys] = l1AlgName;
    if (debug_)
    std::cout<<"L1AlgoBit named: "<<l1AlgName<<" with bit: "<<l1AlgBit<<" and prescale: "<<l1AlgPre<<std::endl;
    //l1triggered[it->first] = vAlgoBool.at(it->second.algoBitNumber());
    //l1prescaled[it->first] = vAlgoInt.at(it->second.algoBitNumber());
    ++l1phys;
  }
  
  int l1tech  = 0;
  if (debug_)
    std::cout<<"Getting the L1 Technical trigger results"<<std::endl;
  for( AlgorithmMap::const_iterator it = techMap.begin(); it != techMap.end(); ++it) {
    std::cout<<"Accessing L1 Technical trigger results"<<std::endl;
    //std::string l1TechName = it->first;
    std::string l1TechName = (it->second).algoName();
    bool l1TechBit = vTechBool.at(it->second.algoBitNumber());
    int  l1TechPre = vTechInt.at(it->second.algoBitNumber());
    l1triggered[l1TechName] = l1TechBit;
    l1prescaled[l1TechName] = l1TechPre;
    m_L1TechnicalArray[l1tech] = l1TechBit;
    m_L1TechnicalNames[l1tech] = l1TechName;
    if (debug_)
      std::cout<<"L1TechBit named: "<<l1TechName<<" with bit: "<<l1TechBit<<" and prescale: "<<l1TechPre<<std::endl;
    //l1triggered[it->first] = vTechBool.at(it->second.algoBitNumber());
    //l1prescaled[it->first] = vTechInt.at(it->second.algoBitNumber());
    ++l1tech;
  }
  

  //Method 2
  /*
  //L1 Technical algorithm bits
  m_nL1Technical = nMaxL1Tech;
  for ( int l1tech = 0; l1tech < nMaxL1Tech; ++l1tech) {    
    m_L1TechnicalArray[l1tech] = l1GtHandle->technicalTriggerWord()[l1tech] ? 1:0;
  }  
  
  //L1 Physics algorithm bits
  m_nL1Physics = nMaxL1Algo;
  for ( int l1phys = 0; l1phys < nMaxL1Algo; ++l1phys) {    
    m_L1PhysicsArray[l1phys] = l1GtHandle->decisionWord()[l1phys] ? 1:0;
  }
  */


  /******************************************************************
   * Here we do all the HLT related trigger stuff
   *
   *
   ******************************************************************/
  // Get the HLT results and check validity

  edm::Handle<edm::TriggerResults> hltHandle;
  iEvent.getByLabel(hlTriggerResults_, hltHandle);
  if ( !hltHandle.isValid() ) {
    edm::LogWarning("HLTEventSelector") << "No trigger results for InputTag " << hlTriggerResults_;
    if (debug_)
      std::cout<<"HLT results not valid"<<std::endl;
    return false;
  }

  //Method 1

  const edm::TriggerNames& trgNames = iEvent.triggerNames(*hltHandle);
  //trgNames.init(*hltHandle);
  
  for (unsigned int hltnum = 0; hltnum < trgNames.size(); ++hltnum) {
    std::string tmpName = trgNames.triggerName(hltnum);
    int trgIndex  = trgNames.triggerIndex(tmpName);
    int trgResult = hltHandle->accept(trgIndex);
    //unsigned int trgPrescale = prescaleValue(iEvent,iSetup,tmpName);
    hlttriggered[tmpName] = trgResult;
    //hltprescaled[tmpName] = trgResult;
    m_HLTNames[hltnum] = tmpName;
    m_HLTArray[hltnum] = trgResult;

    if(debug_) 
      std::cout<<"HLT trigger named: "<<tmpName<<" has result: "<<trgResult<<std::endl;
  }
 
  //Method 2
  /* 
  if (debug_)
    std::cout<<"Getting the HLT triggers"<<std::endl;
  const edm::TriggerNames& trgNames = iEvent.triggerNames(*hltHandle);
    
  if (debug_)
    std::cout<<"Getting the HLT trigger size"<<std::endl;
  unsigned int trgSize = trgNames.size();
  
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
  
  //// decision for each HL algorithm
  //const unsigned int n(pathNames_.size());
  //for (unsigned int i=0; i!=n; ++i) {
  //  if (hltHandle->wasrun(i)) hlWasRun_[i]++;
  //  if (hltHandle->accept(i)) hlAccept_[i]++;
  //  if (hltHandle->error(i) ) hlErrors_[i]++;
  //}
  
  //m_nHLT=static_cast<int>(n);
  m_nHLT = static_cast<int>(trgSize);
  if (debug_)
    std::cout<<"Number of HLT bits: "<<trgSize<<std::endl;
  for(unsigned int hltnum = 0; hltnum != trgSize; ++hltnum) {
    if (debug_)
      std::cout<<"Getting the HLT bit decision for bit: "<<hltnum<<std::endl;
    std::string tmpName   = hltHandle->name(hltnum);
    int         trgResult = hltHandle->accept(hltnum);
    //m_HLTArray[hltnum] = trgResult;
    //m_HLTNames[hltnum] = tmpName;
    //hlttriggered[tmpName] = trgResult;
    if (debug_) 
      std::cout<<"HLT trigger named: "<<tmpName<<" has result "<<trgResult<<std::endl;
    //if (tmpName == "HLT_Jet180")       m_HLT1JET    = true;
    //if (tmpName == "HLT_DiJetAve130")  m_HLT2JET    = true;
    //if (tmpName == "HLT_MET60")        m_HLT1MET    = true;
    //if (tmpName == "HLT_HT200")        m_HLT1HT     = true;
    //if (tmpName == "HLT_HT300_MHT100") m_HLT1HT1MHT = true;
    //if (tmpName == "HLT_Mu9")          m_HLT1Muon   = true; 
    //if (tmpName == "HLT_L1_BscMinBiasOR_BptxPlusORMinus")          m_HLTMinBias = true; 
  }
  */  
  ////looping over list of trig path names
  //for ( std::vector<std::string>::const_iterator i=pathNames_.begin();
  //	i!=pathNames_.end(); ++i ) {
  //  // Get index
  //
  //  unsigned int index = trgNames.triggerIndex(*i);
  //  if ( index==trgSize ) {
  //    edm::LogWarning("HLTEventSelector") << "Unknown trigger name " << *i;
  //    continue;
  //  }
  //  if ( hltHandle->accept(index) ) {
  //    LogDebug("HLTEventSelector") << "Event selected by " << *i ;
  //    std::string trigName = *i;
  //    //m_HLTNames[i] = trigName;
  //
  //    if (trigName == "HLT_Jet180")       m_HLT1JET    = true;
  //    if (trigName == "HLT_DiJetAve130")  m_HLT2JET    = true;
  //    if (trigName == "HLT_MET60")        m_HLT1MET    = true;
  //    if (trigName == "HLT_HT200")        m_HLT1HT     = true;
  //    if (trigName == "HLT_HT300_MHT100") m_HLT1HT1MHT = true;
  //    if (trigName == "HLT_Mu9")          m_HLT1Muon   = true; 
  //    if (trigName == "HLT_L1_BscMinBiasOR_BptxPlusORMinus")          m_HLTMinBias = true; 
  //    
  //  } 
  //}
  //Now done in the config file
  //bool bptx_result = m_L1TechnicalArray[0];
  //bool bsc_result  = m_L1TechnicalArray[40] || m_L1TechnicalArray[41];
  //bool beam_halo_result = m_L1TechnicalArray[36] || m_L1TechnicalArray[37] || m_L1TechnicalArray[38] || m_L1TechnicalArray[39];
  //
  //if (doMCData_) trigger_result = bsc_result && !beam_halo_result;
  //else           trigger_result = bptx_result && bsc_result && !beam_halo_result;

  if (debug_)
    std::cout<<"Done analyzing triggers"<<std::endl;
  return trigger_result;
}


//________________________________________________________________________________________

void TriggerAnalyzerPAT::printHLTreport( void ) {

  // prints an HLT report -- associates trigger bits with trigger names (prints #events fired the trigger etc)
  //const unsigned int n(pathNames_.size());
  //std::cout << "\n";
  //std::cout << "HLT-Report " << "---------- Event  Summary ------------\n";
  //std::cout << "HLT-Report"
  //	    << " Events total = " << nEvents_
  //	    << " wasrun = " << nWasRun_
  //	    << " passed = " << nAccept_
  //	    << " errors = " << nErrors_
  //	    << "\n";
  //
  //std::cout << std::endl;
  //std::cout << "HLT-Report " << "---------- HLTrig Summary ------------\n";
  //std::cout << "HLT-Report "
  //	    << std::right << std::setw(10) << "HLT  Bit#" << " "
  //	    << std::right << std::setw(10) << "WasRun" << " "
  //	    << std::right << std::setw(10) << "Passed" << " "
  //	    << std::right << std::setw(10) << "Errors" << " "
  //	    << "Name" << "\n";
  //
  //if (init_) {
  //  for (unsigned int i=0; i!=n; ++i) {
  //    std::cout << "HLT-Report "
  //		<< std::right << std::setw(10) << i << " "
  //		<< std::right << std::setw(10) << hlWasRun_[i] << " "
  //		<< std::right << std::setw(10) << hlAccept_[i] << " "
  //		<< std::right << std::setw(10) << hlErrors_[i] << " "
  //		<< pathNames_[i] << "\n";
  //  }
  //} else {
  //  std::cout << "HLT-Report - No HL TriggerResults found!" << std::endl;
  //}
  //
  //std::cout << std::endl;
  //std::cout << "HLT-Report end!" << std::endl;
  //std::cout << std::endl;

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

  //std::map access to L1 trigger information
  mTriggerData->Branch("L1Triggered", &l1triggered, "L1Triggered");
  mTriggerData->Branch("L1Prescaled", &l1prescaled, "L1Prescaled");

  //Trigger information
  mTriggerData->Branch("HLT1JET",    &m_HLT1JET,    "HLT1JET/O");
  mTriggerData->Branch("HLT2JET",    &m_HLT2JET,    "HLT2JET/O");
  mTriggerData->Branch("HLT1MET",    &m_HLT1MET,    "HLT1MET/O");
  mTriggerData->Branch("HLT11HT",    &m_HLT1HT,     "HLT1HT/O");
  mTriggerData->Branch("HLT1HT1MHT", &m_HLT1HT1MHT, "HLT1HT1MHT/O");
  mTriggerData->Branch("HLT1MUON",   &m_HLT1Muon,   "HLT1MUON/O");
  mTriggerData->Branch("HLTMINBIAS", &m_HLTMinBias, "HLTMINBIAS/O");

  mTriggerData->Branch("L1MUON1",   &m_L1Muon1,   "L1MUON1/O");
  mTriggerData->Branch("L1MUON2",   &m_L1Muon2,   "L1MUON2/O");
  mTriggerData->Branch("L1MUON3",   &m_L1Muon3,   "L1MUON3/O");
  mTriggerData->Branch("L1MUON4",   &m_L1Muon4,   "L1MUON4/O");

  edm::LogInfo("TriggerEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TriggerAnalyzerPAT);

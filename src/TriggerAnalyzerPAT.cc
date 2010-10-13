
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
// $Id: TriggerAnalyzerPAT.cc,v 1.7 2010/07/08 03:22:30 sturdy Exp $
//
//
//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TriggerAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>
#include <map>

#ifdef __CINT__ 

#pragma link C++ class std::map<std::string,  bool >+; 
#pragma link C++ class std::pair<std::string, bool >; 
#pragma link C++ class std::pair<const std::string, bool >; 

#pragma link C++ class std::map<std::string,  int >+; 
#pragma link C++ class std::pair<std::string, int >; 
#pragma link C++ class std::pair<const std::string, int >; 

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
  getHLTfromConfig_ = triggerParams.getUntrackedParameter<bool>("getHLTfromConfig",false);
  if (getHLTfromConfig_)
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
  i_nL1Physics = nMaxL1Algo;
  if (debug_)
    std::cout<<"Getting the L1 Physics trigger results"<<std::endl;
  for( AlgorithmMap::const_iterator it = algoMap.begin(); it != algoMap.end(); ++it) {
    //std::string l1AlgName = it->first;
    std::string l1AlgName = (it->second).algoName();
    bool l1AlgBit = vAlgoBool.at(it->second.algoBitNumber());
    int  l1AlgPre = vAlgoInt.at(it->second.algoBitNumber());
    l1triggered[l1AlgName] = l1AlgBit;
    l1prescaled[l1AlgName] = l1AlgPre;
    vi_L1PhysicsArray.push_back(l1AlgBit);
    vs_L1PhysicsNames.push_back(l1AlgName);
    if (debug_)
      std::cout<<"L1AlgoBit named: "<<l1AlgName<<" with bit: "<<l1AlgBit<<" and prescale: "<<l1AlgPre<<std::endl;
    //l1triggered[it->first] = vAlgoBool.at(it->second.algoBitNumber());
    //l1prescaled[it->first] = vAlgoInt.at(it->second.algoBitNumber());
    ++l1phys;
  }
  
  int l1tech  = 0;
  i_nL1Technical = nMaxL1Tech;
  if (debug_)
    std::cout<<"Getting the L1 Technical trigger results"<<std::endl;
  for( AlgorithmMap::const_iterator it = techMap.begin(); it != techMap.end(); ++it) {
    if (debug_)
      std::cout<<"Accessing L1 Technical trigger results"<<std::endl;
    std::string l1TechName = (it->second).algoName();
    bool l1TechBit = vTechBool.at(it->second.algoBitNumber());
    int  l1TechPre = vTechInt.at(it->second.algoBitNumber());
    l1triggered[l1TechName] = l1TechBit;
    l1prescaled[l1TechName] = l1TechPre;
    vi_L1TechnicalArray.push_back(l1TechBit);
    vs_L1TechnicalNames.push_back(l1TechName);
    if (debug_)
      std::cout<<"L1TechBit named: "<<l1TechName<<" with bit: "<<l1TechBit<<" and prescale: "<<l1TechPre<<std::endl;
    ++l1tech;
  }
  

  /******************************************************************
   * Here we do all the HLT related trigger stuff
   *
   *
   ******************************************************************/
  // Get the HLT results and check validity

  edm::Handle<edm::TriggerResults> hltHandle;
  if (!getHLTfromConfig_) {
    //iEvent.getByLabel(hlTriggerResults_, hltHandle);
    Handle<trigger::TriggerEvent> hltEventHandle;
    iEvent.getByLabel("hltTriggerSummaryAOD", hltEventHandle);
    
    hlTriggerResults_ = InputTag("TriggerResults","",hltEventHandle.provenance()->processName());
    
  }

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

  i_nHLT = trgNames.size();
  for (unsigned int hltnum = 0; hltnum < trgNames.size(); ++hltnum) {
    std::string tmpName = trgNames.triggerName(hltnum);
    int trgIndex  = trgNames.triggerIndex(tmpName);
    int trgResult = hltHandle->accept(trgIndex);
    //unsigned int trgPrescale = prescaleValue(iEvent,iSetup,tmpName);
    hlttriggered[tmpName] = trgResult;
    //hltprescaled[tmpName] = trgResult;
    vs_HLTNames.push_back(tmpName);
    vi_HLTArray.push_back(trgResult);

    if (debug_) 
      std::cout<<"HLT trigger named: "<<tmpName<<" has result "<<trgResult<<std::endl;
    if (tmpName == "HLT_Jet180")       m_HLT1JET    = true;
    if (tmpName == "HLT_DiJetAve130")  m_HLT2JET    = true;
    if (tmpName == "HLT_MET60")        m_HLT1MET    = true;
    if (tmpName == "HLT_HT200")        m_HLT1HT     = true;
    if (tmpName == "HLT_HT300_MHT100") m_HLT1HT1MHT = true;
    if (tmpName == "HLT_Mu9")          m_HLT1Muon   = true; 
    if (tmpName == "HLT_L1_BscMinBiasOR_BptxPlusORMinus")          m_HLTMinBias = true; 
  }

  if (debug_)
    std::cout<<"Done analyzing triggers"<<std::endl;
  return trigger_result;
}


//________________________________________________________________________________________

void TriggerAnalyzerPAT::printHLTreport( void ) {


}


//________________________________________________________________________________________
void TriggerAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Level-1 Technical Triggers
  mTriggerData->Branch("nL1Technical",     &i_nL1Technical,     "nL1Technical/I");
  mTriggerData->Branch("L1TechnicalArray", &vi_L1TechnicalArray);//, "L1TechnicalArray[nL1Technical]/I");
  mTriggerData->Branch("L1TechnicalNames", &vs_L1TechnicalNames);//, "L1TechnicalNames[nL1Technical]/string");
  //Level-1 Physics Triggers
  mTriggerData->Branch("nL1Physics",     &i_nL1Physics,     "nL1Physics/I");
  mTriggerData->Branch("L1PhysicsArray", &vi_L1PhysicsArray);//, "L1PhysicsArray[nL1Physics]/I");
  mTriggerData->Branch("L1PhysicsNames", &vs_L1PhysicsNames);//, "L1PhysicsNames[nL1Physics]/string");

  //std::map access to L1 trigger information
  mTriggerData->Branch("L1Triggered", &l1triggered);//, "L1Triggered");
  mTriggerData->Branch("L1Prescaled", &l1prescaled);//, "L1Prescaled");

  //HLT information
  mTriggerData->Branch("nHLT",     &i_nHLT,     "nHLT/I");
  mTriggerData->Branch("HLTArray", &vi_HLTArray);//, "HLTArray[nHLT]/I");
  mTriggerData->Branch("HLTNames", &vs_HLTNames);//, "HLTNames[nHLT]/string");

  mTriggerData->Branch("HLT1JET",    &m_HLT1JET,    "HLT1JET/O");
  mTriggerData->Branch("HLT2JET",    &m_HLT2JET,    "HLT2JET/O");
  mTriggerData->Branch("HLT1MET",    &m_HLT1MET,    "HLT1MET/O");
  mTriggerData->Branch("HLT11HT",    &m_HLT1HT,     "HLT1HT/O");
  mTriggerData->Branch("HLT1HT1MHT", &m_HLT1HT1MHT, "HLT1HT1MHT/O");
  mTriggerData->Branch("HLT1MUON",   &m_HLT1Muon,   "HLT1MUON/O");
  mTriggerData->Branch("HLTMINBIAS", &m_HLTMinBias, "HLTMINBIAS/O");

  //std::map access to HLT information
  mTriggerData->Branch("HLTTriggered", &hlttriggered);//, "HLTTriggered");
  mTriggerData->Branch("HLTPrescaled", &hltprescaled);//, "HLTPrescaled");

  edm::LogInfo("TriggerEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TriggerAnalyzerPAT);

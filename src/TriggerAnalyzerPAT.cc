
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
// $Id: TriggerAnalyzerPAT.cc,v 1.8 2010/10/13 16:46:09 sturdy Exp $
//
//
//#include "SusyAnalysis/EventSelector/interface/BJetEventSelector.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TriggerAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>
#include <map>

//#ifdef __CINT__ 
//
//#pragma link C++ class std::map<std::string,  bool >+; 
//#pragma link C++ class std::pair<std::string, bool >; 
//#pragma link C++ class std::pair<const std::string, bool >; 
//
//#pragma link C++ class std::map<std::string,  int >+; 
//#pragma link C++ class std::pair<std::string, int >; 
//#pragma link C++ class std::pair<const std::string, int >; 
//
//#endif

//________________________________________________________________________________________
TriggerAnalyzerPAT::TriggerAnalyzerPAT(const edm::ParameterSet& triggerParams, TTree* tmpAllData)
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

//
//________________________________________________________________________________________
void TriggerAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
  bool changed(true);
  if (hltConfig.init(run,es,"TriggerResults::HLT",changed)) {
    // if init returns TRUE, initialisation has succeeded!
    if (changed) {
      // The HLT config has actually changed wrt the previous Run, hence rebook your
      // histograms or do anything else dependent on the revised HLT config
    }
  }
  else {
    // if init returns FALSE, initialisation has NOT succeeded, which indicates a problem
    // with the file and/or code and needs to be investigated!
    edm::LogError("TriggerEvent") << " HLT config extraction failure with process name " << hlTriggerResults_;
    // In this case, all access methods will return empty values!
  }
}
//________________________________________________________________________________________
// Method called to for each event
bool TriggerAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  maintenance();
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
  ev.getByLabel(l1TriggerResults_, l1GtHandle);

  edm::ESHandle<L1GtTriggerMenu> L1menu;
  es.get<L1GtTriggerMenuRcd>().get(L1menu) ;
  const L1GtTriggerMenu* theMenu = L1menu.product();
  
  edm::ESHandle<L1GtPrescaleFactors> psAlgo;
  es.get<L1GtPrescaleFactorsAlgoTrigRcd>().get(psAlgo);
  
  edm::ESHandle<L1GtPrescaleFactors> psTech;
  es.get<L1GtPrescaleFactorsTechTrigRcd>().get(psTech);

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
    std::string l1AlgName = (it->second).algoName();
    bool l1AlgBit = vAlgoBool.at(it->second.algoBitNumber());
    int  l1AlgPre = vAlgoInt.at(it->second.algoBitNumber());
    l1triggered[l1AlgName] = l1AlgBit;
    l1prescaled[l1AlgName] = l1AlgPre;
    if (debug_)
      std::cout<<"L1AlgoBit named: "<<l1AlgName<<" with bit: "<<l1AlgBit<<" and prescale: "<<l1AlgPre<<std::endl;
    ++l1phys;
  }
  
  int l1tech  = 0;
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
    //ev.getByLabel(hlTriggerResults_, hltHandle);
    Handle<trigger::TriggerEvent> hltEventHandle;
    ev.getByLabel("hltTriggerSummaryAOD", hltEventHandle);
    
    hlTriggerResults_ = InputTag("TriggerResults","",hltEventHandle.provenance()->processName());
    
  }

  ev.getByLabel(hlTriggerResults_, hltHandle);
  
  if ( !hltHandle.isValid() ) {
    edm::LogWarning("HLTEventSelector") << "No trigger results for InputTag " << hlTriggerResults_;
    if (debug_)
      std::cout<<"HLT results not valid"<<std::endl;
    return false;
  }

  //Method 1

  const edm::TriggerNames& trgNames = ev.triggerNames(*hltHandle);

  for (unsigned int hltnum = 0; hltnum < trgNames.size(); ++hltnum) {
    std::string tmpName = trgNames.triggerName(hltnum);
    int trgIndex  = trgNames.triggerIndex(tmpName);
    int trgResult = hltHandle->accept(trgIndex);
    unsigned int trgPrescale = hltConfig.prescaleValue(ev,es,tmpName);
    hlttriggered[tmpName] = trgResult;
    hltprescaled[tmpName] = trgPrescale;

    if (debug_) 
      std::cout<<"HLT trigger named: "<<tmpName<<" has result "<<trgResult<<std::endl;
    if (tmpName == "HLT_Jet180")       m_HLT1JET    = trgResult;
    if (tmpName == "HLT_DiJetAve130")  m_HLT2JET    = trgResult;
    if (tmpName == "HLT_MET60")        m_HLT1MET    = trgResult;
    if (tmpName == "HLT_HT200")        m_HLT1HT     = trgResult;
    if (tmpName == "HLT_HT300_MHT100") m_HLT1HT1MHT = trgResult;
    if (tmpName == "HLT_Mu9")          m_HLT1Muon   = trgResult; 
    if (tmpName == "HLT_L1_BscMinBiasOR_BptxPlusORMinus")          m_HLTMinBias = trgResult; 
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

  //std::map access to L1 trigger information
  mTriggerData->Branch("L1Triggered", &l1triggered);
  mTriggerData->Branch("L1Prescaled", &l1prescaled);

  //HLT information
  mTriggerData->Branch("HLT1JET",    &m_HLT1JET,    "HLT1JET/O");
  mTriggerData->Branch("HLT2JET",    &m_HLT2JET,    "HLT2JET/O");
  mTriggerData->Branch("HLT1MET",    &m_HLT1MET,    "HLT1MET/O");
  mTriggerData->Branch("HLT11HT",    &m_HLT1HT,     "HLT1HT/O");
  mTriggerData->Branch("HLT1HT1MHT", &m_HLT1HT1MHT, "HLT1HT1MHT/O");
  mTriggerData->Branch("HLT1MUON",   &m_HLT1Muon,   "HLT1MUON/O");
  mTriggerData->Branch("HLTMINBIAS", &m_HLTMinBias, "HLTMINBIAS/O");

  //std::map access to HLT information
  mTriggerData->Branch("HLTTriggered", &hlttriggered);
  mTriggerData->Branch("HLTPrescaled", &hltprescaled);

  edm::LogInfo("TriggerEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TriggerAnalyzerPAT);

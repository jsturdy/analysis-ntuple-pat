
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
// $Id: TriggerAnalyzerPAT.cc,v 1.12 2011/03/08 21:11:36 sturdy Exp $
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

  debug_    = triggerParams.getUntrackedParameter<int>("debugTriggers",0);
  doMCData_ = triggerParams.getUntrackedParameter<bool>("doMCTriggers",false);
 
  // trigger stuff
  //L1 info
  getL1Info_          = triggerParams.getUntrackedParameter<bool>("getL1Info",false);
  if (getL1Info_)
    l1TriggerResults_ = triggerParams.getUntrackedParameter<edm::InputTag>("l1TriggerResults");

  //HLT info
  getHLTfromConfig_   = triggerParams.getUntrackedParameter<bool>("getHLTfromConfig",false);
  if (getHLTfromConfig_)
    hlTriggerResults_ = triggerParams.getUntrackedParameter<edm::InputTag>("hlTriggerResults");
  //key to help getting the hlt process from event provenance
  checkedProcess_ = false;
  processName_    = "";
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
  bool changed = false;
  if (hltConfig.init(run,es,"HLT",changed)) {
    if (changed) {
      edm::LogWarning("TriggerAnalyzerPAT") << "beginRun: The HLT config has changed!";
    }
  }
  else {
    edm::LogError("TriggerEvent") << " HLT config extraction failure";
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


  /******************************************************************
   * Here we do all the L1 related trigger stuff
   *
   *
   ******************************************************************/
  if (getL1Info_) {
    //L1 trigger results
    if (debug_>5)
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
    
    if (debug_>5)
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
    
    int nBx = 1; //what does this do ???
    const std::vector<bool>& vAlgoBool = l1GtHandle->decisionWord(nBx);
    const std::vector<int>&  vAlgoInt  = psAlgo->gtPrescaleFactors().at(l1GtHandle->gtFdlWord(nBx).gtPrescaleFactorIndexAlgo());
    
    const std::vector<bool>& vTechBool = l1GtHandle->technicalTriggerWord(nBx);
    const std::vector<int>&  vTechInt  = psTech->gtPrescaleFactors().at(l1GtHandle->gtFdlWord(nBx).gtPrescaleFactorIndexTech());
    
    int l1phys = 0;
    if (debug_>5)
      std::cout<<"Getting the L1 Physics trigger results"<<std::endl;
    for( AlgorithmMap::const_iterator it = algoMap.begin(); it != algoMap.end(); ++it) {
      std::string l1AlgName = (it->second).algoName();
      bool l1AlgBit = vAlgoBool.at(it->second.algoBitNumber());
      int  l1AlgPre = vAlgoInt.at(it->second.algoBitNumber());
      l1triggered[l1AlgName] = l1AlgBit;
      l1prescaled[l1AlgName] = l1AlgPre;
      if (debug_>5)
	std::cout<<"L1AlgoBit named: "<<l1AlgName<<" with bit: "<<l1AlgBit<<" and prescale: "<<l1AlgPre<<std::endl;
      ++l1phys;
    }
    
    int l1tech  = 0;
    if (debug_>5)
      std::cout<<"Getting the L1 Technical trigger results"<<std::endl;
    for( AlgorithmMap::const_iterator it = techMap.begin(); it != techMap.end(); ++it) {
      if (debug_>5)
	std::cout<<"Accessing L1 Technical trigger results"<<std::endl;
      std::string l1TechName = (it->second).algoName();
      bool l1TechBit = vTechBool.at(it->second.algoBitNumber());
      int  l1TechPre = vTechInt.at(it->second.algoBitNumber());
      l1triggered[l1TechName] = l1TechBit;
      l1prescaled[l1TechName] = l1TechPre;
      if (debug_>5)
	std::cout<<"L1TechBit named: "<<l1TechName<<" with bit: "<<l1TechBit<<" and prescale: "<<l1TechPre<<std::endl;
      ++l1tech;
    }
  }//end check on doing L1 trigger info

  /******************************************************************
   * Here we do all the HLT related trigger stuff
   *
   *
   ******************************************************************/
  // Get the HLT results and check validity
  
  //if (!getHLTfromConfig_ && !checkedProcess_) {
  if (!getHLTfromConfig_) 
    if (processName_=="") {
      Handle<trigger::TriggerEvent> hltEventHandle;
      ev.getByLabel("hltTriggerSummaryAOD", hltEventHandle);
      processName_ = hltEventHandle.provenance()->processName();
      if (debug_)
      std::cout<<processName_<<std::endl;
    }
  hlTriggerResults_ = InputTag("TriggerResults","",processName_);
  
  edm::LogInfo("HLTEventSelector") << "Using trigger results for InputTag " << hlTriggerResults_;

  edm::Handle<edm::TriggerResults> hltHandle;
  ev.getByLabel(hlTriggerResults_, hltHandle);
  
  if ( !hltHandle.isValid() ) {
    edm::LogWarning("HLTEventSelector") << "No trigger results for InputTag " << hlTriggerResults_;
    if (debug_)
      std::cout<<"HLT results not valid"<<std::endl;
    return false;
  }

  const edm::TriggerNames& trgNames = ev.triggerNames(*hltHandle);
  
  int          prescaleSet = hltConfig.prescaleSet(ev,es);
  if (debug_)
    std::cout<<"Prescale set is: "<<prescaleSet<<std::endl;
  for (unsigned int hltnum = 0; hltnum < trgNames.size(); ++hltnum) {
    std::string  tmpName     = trgNames.triggerName(hltnum);
    unsigned int trgIndex    = trgNames.triggerIndex(tmpName);
    int          trgResult   = hltHandle->accept(trgIndex);
    unsigned int trgPrescale = hltConfig.prescaleValue(ev,es,tmpName);
    hlttriggered[tmpName]    = trgResult;
    hltprescaled[tmpName]    = trgPrescale;

    if (debug_) 
      std::cout<<"HLT trigger named: "<<tmpName
	       <<" has index "<<trgIndex
	       <<" has result "<<trgResult
	       <<" has prescale "<<trgPrescale
	       <<std::endl;
  }
  
  if (debug_>5)
    std::cout<<"Done analyzing triggers"<<std::endl;
  //mTriggerData->Fill();
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


  if (getL1Info_) {
    //std::map access to L1 trigger information
    mTriggerData->Branch("L1Triggered", &l1triggered);
    mTriggerData->Branch("L1Prescaled", &l1prescaled);
  }

  //HLT information
  //std::map access to HLT information
  mTriggerData->Branch("HLTTriggered", &hlttriggered);
  mTriggerData->Branch("HLTPrescaled", &hltprescaled);

  edm::LogInfo("TriggerEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TriggerAnalyzerPAT);

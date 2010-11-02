#ifndef TRIGGERANALYZERPAT
#define TRIGGERANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//#include "DataFormats/L1Trigger/interface/L1ParticleMap.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
//#include "FWCore/Framework/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerNames.h"


//to access trigger names                                                                                                                                                                                                                   

#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "CondFormats/L1TObjects/interface/L1GtPrescaleFactors.h"
#include "CondFormats/DataRecord/interface/L1GtPrescaleFactorsAlgoTrigRcd.h"
#include "CondFormats/DataRecord/interface/L1GtPrescaleFactorsTechTrigRcd.h"
#include "boost/lexical_cast.hpp"

//
// Class declaration
//
class TriggerAnalyzerPAT {
 public:
  TriggerAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~TriggerAnalyzerPAT();
  
  //*** CMSSW interface
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );

  /// Print a summary of counts for all selectors
  void printHLTreport(void); // georgia
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  /// Define all plots
  void bookTTree();



private:

  bool doMCData_;                 /// switch to turn off generator level information
  bool getHLTfromConfig_; 

  char logmessage[128];

  // Plots
  TTree * mTriggerData;      /// Will contain the additional di-jet specific data

  std::map<std::string, bool> l1triggered;
  std::map<std::string, int>  l1prescaled;
  std::map<std::string, bool> hlttriggered;
  std::map<std::string, int>  hltprescaled;

  bool m_HLT1JET;
  bool m_HLT2JET;
  bool m_HLT1MET;
  bool m_HLT1HT;
  bool m_HLT1HT1MHT;
  bool m_HLT1Muon;

  bool m_HLTMinBias;

  bool trigger_result;

  // Data tags
  edm::InputTag l1TriggerResults_; 
  edm::InputTag hlTriggerResults_; 
  std::vector<std::string> pathNames_;

  edm::TriggerNames triggerNames_;     // TriggerNames class
  HLTConfigProvider hltConfig;

  int debug_;

  double localPi;

  void maintenance() {
    l1triggered.clear();
    l1prescaled.clear();
    hlttriggered.clear();
    hltprescaled.clear();
  }
};

#endif

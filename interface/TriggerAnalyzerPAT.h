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
//#include "FWCore/Framework/interface/EDAnalyzer.h"
//#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// SUSY include files
//#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"

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
 
  //*** Plotting
  /// Define all plots
  void bookTTree();



private:

  bool doMCData_;                 /// switch to turn off generator level information
  bool getHLTfromConfig_; 

  static const int nMaxL1Tech = 64;
  static const int nMaxL1Algo = 128;

  char logmessage[128];

  // Plots
  TTree * mTriggerData;      /// Will contain the additional di-jet specific data

  int m_nHLT;
  int m_nL1Technical;
  int m_nL1Physics;
  int m_HLTArray[200];
  int m_L1TechnicalArray[nMaxL1Tech];
  int m_L1PhysicsArray[nMaxL1Algo];

  std::string m_HLTNames[200];
  std::string m_L1TechnicalNames[nMaxL1Tech];
  std::string m_L1PhysicsNames[nMaxL1Algo];

  //boost::shared_ptr<std::map<std::string, bool> >  l1triggered (new std::map<std::string, bool>() );
  //boost::shared_ptr<std::map<std::string, int> >   l1prescaled (new std::map<std::string, int>() );
  //boost::shared_ptr<std::map<std::string, bool> >  hlttriggered (new std::map<std::string, bool>() );
  //boost::shared_ptr<std::map<std::string, int> >   hltprescaled (new std::map<std::string, int>() );

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

  bool m_L1Muon1;
  bool m_L1Muon2;
  bool m_L1Muon3;
  bool m_L1Muon4;

  bool trigger_result;

  // Data tags
  edm::InputTag l1TriggerResults_; 
  edm::InputTag hlTriggerResults_; 
  std::vector<std::string> pathNames_;

  edm::TriggerNames triggerNames_;     // TriggerNames class

  unsigned int  nEvents_;              // number of events processed

  unsigned int  nWasRun_;              // # where at least one HLT was run
  unsigned int  nAccept_;              // # of accepted events
  unsigned int  nErrors_;              // # where at least one HLT had error
  std::vector<unsigned int> hlWasRun_; // # where HLT[i] was run
  std::vector<unsigned int> hlAccept_; // # of events accepted by HLT[i]
  std::vector<unsigned int> hlErrors_; // # of events with error in HLT[i]
  bool init_;                          // vectors initialised or not
  
  int debug_;

  double localPi;
};

#endif

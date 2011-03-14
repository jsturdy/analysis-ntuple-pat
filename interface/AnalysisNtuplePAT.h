#ifndef ANALYSISNTUPLEPAT
#define ANALYSISNTUPLEPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Provenance/interface/EventAuxiliary.h"
#include "JSturdy/AnalysisNtuplePAT/interface/JetAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/METAnalyzerPAT.h"
//#include "JSturdy/AnalysisNtuplePAT/interface/HemisphereAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/LeptonAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/VertexAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/PhotonAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TrackAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/TriggerAnalyzerPAT.h"
#include "JSturdy/AnalysisNtuplePAT/interface/MCTruthAnalyzerPAT.h"


//
// Class declaration
//
class AnalysisNtuplePAT : public edm::EDAnalyzer {
public:
  explicit AnalysisNtuplePAT(const edm::ParameterSet&);
  ~AnalysisNtuplePAT();
  
private:
  //*** CMSSW interface
  /// Called once per job, at start
  void beginJob() ;
  /// Called once per run, at start
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  /// Called for each event
  void analyze(const edm::Event&, const edm::EventSetup&);
  /// Called once per job, at end
  void endJob();

  /// Print a summary of counts for all selectors
  void printSummary(void);
 
  //*** Plotting
  void initPlots();

private:

  // Event information
  int run_, event_;

  // Counters
  //unsigned int nrEventTotalRaw_;          ///< Raw number of events (+1 at each event)
  //double nrEventTotalWeighted_;           ///< Weighted #(events)
  //std::vector<float> nrEventSelected_;    ///< Selected #(events) for each module
  //std::vector<float> nrEventAllButOne_;   ///< All-but-one selected #(events) for each module
  //std::vector<float> nrEventCumulative_;  ///< Cumulative selected #(events) for each module
    
  // Plots
  TNtuple* ntuple_;      /// Will contain all the selector information we want to keep
  TTree * mEventData;      /// Will contain the additional di-jet specific data
  TTree * mAllData;      /// Will contain the additional di-jet specific data
  TTree * mLeptonData;      /// Will contain the additional di-jet specific data
  TTree * mJetData;      /// Will contain the additional di-jet specific data
  TTree * mMETData;      /// Will contain the additional di-jet specific data
  TTree * mPhotonData;      /// Will contain the additional di-jet specific data
  TTree * mTriggerData;      /// Will contain the additional di-jet specific data
  TTree * mVertexData;      /// Will contain the additional di-jet specific data
  TTree * mGenParticleData;      /// Will contain the additional di-jet specific data
  TTree * mTrackData;      /// Will contain the additional di-jet specific data

  //float* variables_;     ///< Container for the tree variables (from selectors)
  //bool   globalDec_;     ///< Global decision for event

  int m_Run;
  int m_Event;
  int m_OrbitN;
  int m_StoreN;
  int m_LumiSection;
  int m_BunchCrossing;

  bool m_IsData;

  unsigned int  nEvents_;              // number of events processed

  int  debug_;
  bool doMCTruth_;

  int passCaloJets[2];
  int passJPTJets[2];
  int passPFJets[2];
  int passPF2PATJets[2];
  //int passTrackJets[2];

  int passCaloMET[2];
  int passCaloTypeIIMET[2];
  int passPFMET[2];
  int passPFTypeIMET[2];
  int passTCMET[2];

  int passLeptons[2];
  int passPFLeptons[2];

  int passPhotons[2];
  //int passPFPhotons[2];

  int passVertex[2];
  int passTracks[2];
  int passTriggers[2];
  //int passHemispheres[2];
  
  JetAnalyzerPAT        *calojetinfo;
  JetAnalyzerPAT        *jptjetinfo;
  JetAnalyzerPAT        *pfjetinfo;
  JetAnalyzerPAT        *pf2patjetinfo;
  //JetAnalyzerPAT        *trackjetinfo;

  METAnalyzerPAT        *calometinfo;
  METAnalyzerPAT        *calomettypeiiinfo;

  METAnalyzerPAT        *pfmetinfo;
  METAnalyzerPAT        *pfmettypeiinfo;

  METAnalyzerPAT        *tcmetinfo;

  //HemisphereAnalyzerPAT *heminfo;

  PhotonAnalyzerPAT     *photons;
  //PhotonAnalyzerPAT     *pfphotons;

  LeptonAnalyzerPAT     *leptons;
  LeptonAnalyzerPAT     *pfleptons;

  VertexAnalyzerPAT     *vertex;
  TrackAnalyzerPAT      *tracks;
  TriggerAnalyzerPAT    *triggers;

  MCTruthAnalyzerPAT    *geninfo;

};
#endif

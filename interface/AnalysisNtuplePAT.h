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

  //*** Plotting
  void initPlots();

private:

  // Event information
  int run_, event_;

  // Counters
    
  // Plots
  TTree *mEventData;      /// Will contain the additional di-jet specific data
  TTree *mAllData;      /// Will contain the additional di-jet specific data
  TTree *mLeptonData;      /// Will contain the additional di-jet specific data
  TTree *mJetData;      /// Will contain the additional di-jet specific data
  TTree *mMETData;      /// Will contain the additional di-jet specific data
  TTree *mPhotonData;      /// Will contain the additional di-jet specific data
  TTree *mTriggerData;      /// Will contain the additional di-jet specific data
  TTree *mVertexData;      /// Will contain the additional di-jet specific data
  TTree *mGenParticleData;      /// Will contain the additional di-jet specific data
  //TTree *mTrackData;      /// Will contain the additional di-jet specific data

  int m_Run;
  int m_Event;
  int m_OrbitN;
  int m_StoreN;
  int m_LumiSection;
  int m_BunchCrossing;
  
  double m_susyScanA0           ;
  double m_susyScanCrossSection ;
  double m_susyScanM0           ;
  double m_susyScanM12          ;
  double m_susyScanMu           ;
  double m_susyScanRun          ;
  double m_susyScantanbeta      ;


  bool m_IsData;

  unsigned int  nEvents_;              // number of events processed

  int  debug_;
  bool doMCTruth_;

  JetAnalyzerPAT        *calojetinfo;
  //JetAnalyzerPAT        *jptjetinfo;
  JetAnalyzerPAT        *pf2patjetinfo;

  //METAnalyzerPAT        *calometinfo;
  METAnalyzerPAT        *calomettypeiiinfo;

  //METAnalyzerPAT        *pfmetinfo;
  METAnalyzerPAT        *pfmettypeiinfo;

  //METAnalyzerPAT        *tcmetinfo;

  //HemisphereAnalyzerPAT *heminfo;

  PhotonAnalyzerPAT     *photons;
  //PhotonAnalyzerPAT     *pfphotons;

  LeptonAnalyzerPAT     *leptons;
  LeptonAnalyzerPAT     *pfleptons;

  VertexAnalyzerPAT     *vertex;
  //TrackAnalyzerPAT      *tracks;
  TriggerAnalyzerPAT    *triggers;

  MCTruthAnalyzerPAT    *geninfo;

};
#endif

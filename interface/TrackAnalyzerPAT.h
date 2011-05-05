#ifndef TRACKANALYZERPAT
#define TRACKANALYZERPAT

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

// SUSY include files
//#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"

//
// Class declaration
//


class TrackAnalyzerPAT {
 public:
  TrackAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~TrackAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );

  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  void bookTTree(TTree*);

 private:

  // Data tags
  edm::InputTag  trackTag_;
  bool doMCData_;
  int  debug_;

  //TTree * mTrackData;      /// Will contain the additional track parameters

  bool track_result;

  // track info:
  double m_MPTPhi;
  double m_MPTPx;
  double m_MPTPy;
  double m_MPTPz;

  double localPi;
};

#endif

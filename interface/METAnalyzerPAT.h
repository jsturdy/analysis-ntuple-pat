#ifndef METANALYZERPAT
#define METANALYZERPAT

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
#include <TLorentzVector.h>
#include <TMath.h>

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

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/MET.h"


//
// Class declaration
//
class METAnalyzerPAT {
 public:
  METAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~METAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );

  //*** Plotting
  /// Define all plots
  void bookTTree();
  
 private:
  
  // configuration parameters
  //met tags
  edm::InputTag metTag_;
  edm::InputTag genTag_;

  bool doMCData_;
  int  debug_;
  
  TString prefix_;

  bool met_result;       /// result of the met cut

  char logmessage[128];

  TTree * mMETData;      /// Will contain the data passing the MET cut

  // Generated MET
  double m_METGen[3];

  int nFullMET;
  int nUncorrMET;
 
  //boost::shared_ptr<reco::Candidate::LorentzVector> mep4 ( new reco::Candidate::LorentzVector() );
  //boost::shared_ptr<std::map<std::string, float> > corrX ( new std::map<std::string, float>() );
  //boost::shared_ptr<std::map<std::string, float> > corrY ( new std::map<std::string, float>() );
  //boost::shared_ptr<std::map<std::string, float> > corrSumET ( new std::map<std::string, float>() );

  reco::Candidate::LorentzVector mep4;
  std::map<std::string, float> corrX;
  std::map<std::string, float> corrY;
  std::map<std::string, float> corrSumET;
  
  double m_MET_Fullcorr_nocc[3];
  double m_METpt_Fullcorr_nocc;
  double m_METphi_Fullcorr_nocc;
  double m_METsumEt_Fullcorr_nocc;
  double m_METsignificance_Fullcorr_nocc;

  double m_MET_Nocorr_nocc[2];
  double m_METpt_Nocorr_nocc;
  double m_METphi_Nocorr_nocc;
  double m_METsumEt_Nocorr_nocc;
  double m_METsignificance_Nocorr_nocc;

  double m_MET_Muoncorr_nocc[2];
  double m_METpt_Muoncorr_nocc;
  double m_METphi_Muoncorr_nocc;
  double m_METsumEt_Muoncorr_nocc;
  double m_METsignificance_Muoncorr_nocc;

  double m_MET_JEScorr_nocc[2];
  double m_METpt_JEScorr_nocc;
  double m_METphi_JEScorr_nocc;
  double m_METsumEt_JEScorr_nocc;
  double m_METsignificance_JEScorr_nocc;

  double localPi;
};

#endif

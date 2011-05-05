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

#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/METReco/interface/CaloMET.h"
#include "DataFormats/METReco/interface/GenMET.h"
#include "DataFormats/METReco/interface/GenMETFwd.h"
#include "DataFormats/METReco/interface/MET.h"


//
// Class declaration
//


class METAnalyzerPAT {
 public:
  METAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~METAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );

  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  /// Define all plots
  void bookTTree(TTree*);
  
 private:
  
  // configuration parameters
  //met tags
  edm::InputTag metTag_;
  edm::InputTag genTag_;

  bool doMCData_;
  bool useCaloMET_;
  bool usePFMET_;
  int  debug_;
  
  TString prefix_;

  bool met_result;       /// result of the met cut

  //TTree * mMETData;      /// Will contain the data passing the MET cut

  // Generated MET
  double m_METGen[3];
  double m_METGenTrue[3];
  double m_METGenCalo[3];

  int nFullMET;
  int nUncorrMET;
 
  std::auto_ptr<reco::Candidate::LorentzVector> mep4;
  std::auto_ptr<reco::Candidate::LorentzVector> genMETP4;
  std::auto_ptr<reco::Candidate::LorentzVector> genTrueMETP4;
  std::auto_ptr<reco::Candidate::LorentzVector> genCaloMETP4;

  double genSumEt;
  double genTrueSumEt;
  double genCaloSumEt;

  double genMetSig;
  double genTrueMetSig;
  double genCaloMetSig;

  double genSignificance;
  double genTrueSignificance;
  double genCaloSignificance;

  //std::auto_ptr<std::map<std::string, double> >  corrX;
  //std::auto_ptr<std::map<std::string, double> >  corrY;
  //std::auto_ptr<std::map<std::string, double> >  corrSumET;
  //std::auto_ptr<std::map<std::string, double> >  corrMETPhi;
  //std::auto_ptr<std::map<std::string, double> >  corrPt;
  
  double m_MET_Fullcorr[3];
  double m_METpt_Fullcorr;
  double m_METphi_Fullcorr;
  double m_METsumEt_Fullcorr;
  double m_METsignificance_Fullcorr;

  //specific to calo met
  double METmaxEt_em;
  double METmaxEt_had;
  double METetFrac_had;
  double METetFrac_em;
  double METmetSig;

  //specific to PF met
  double METFrac_neutralEM;
  double METFrac_neutralHad;
  double METFrac_chargedEM;
  double METFrac_chargedHad;
  double METFrac_muon;
  double METFrac_type6;
  double METFrac_type7;
  
  double m_MET_Nocorr[2];
  double m_METpt_Nocorr;
  double m_METphi_Nocorr;
  double m_METsumEt_Nocorr;
  double m_METsignificance_Nocorr;

  double m_MET_Muoncorr[2];
  double m_METpt_Muoncorr;
  double m_METphi_Muoncorr;
  double m_METsumEt_Muoncorr;
  double m_METsignificance_Muoncorr;

  double m_MET_JEScorr[2];
  double m_METpt_JEScorr;
  double m_METphi_JEScorr;
  double m_METsumEt_JEScorr;
  double m_METsignificance_JEScorr;

  double localPi;
  
  void maintenance() {
    //corrX->clear();
    //corrY->clear();
    //corrSumET->clear();
    //corrMETPhi->clear();
    //corrPt->clear();
  }
};

#endif

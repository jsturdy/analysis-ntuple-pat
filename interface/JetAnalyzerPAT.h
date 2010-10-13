#ifndef JETANALYZERPAT
#define JETANALYZERPAT

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

#include "DataFormats/PatCandidates/interface/Jet.h"

//#include "PhysicsTools/Utilities/interface/deltaPhi.h"
//#include "PhysicsTools/Utilities/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Hemisphere.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"


//
// Class declaration
//

class JetAnalyzerPAT {
 public:
  JetAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~JetAnalyzerPAT();
  
  bool filter(const edm::Event&, const edm::EventSetup&);
  
  //*** Plotting
  /// Define all plots
  void bookTTree();

 private:

  bool matchJetsByCaloTowers( const pat::Jet&, const pat::Jet& );

  // Configuration parameters
  TString prefix_;

  int    minNJets_;                  /// for preselection cuts on jets and to calculate HT and MHT
  double jetMaxEta_;
  double jetMinPt_;

  double htMaxEta_;
  double htMinPt_;

  //calo jet id
  double jetMaxEMF_;
  double jetMinEMF_;
  double jetMaxHPD_;
  double jetMinHPD_;
  double jetMaxRBX_;
  double jetMinRBX_;
  double jetMaxN90_;
  double jetMinN90_;

  //PF jet id
  double jetMaxCHF_;
  double jetMinCHF_;
  double jetMaxNHF_;
  double jetMinNHF_;
  double jetMaxCEF_;
  double jetMinCEF_;
  double jetMaxNEF_;
  double jetMinNEF_;
  double jetMaxCMF_;
  double jetMinCMF_;
  double jetMaxCMult_;
  double jetMinCMult_;
  double jetMaxNMult_;
  double jetMinNMult_;
  double jetMaxMuMult_;
  double jetMinMuMult_;

  std::vector<double> selJetMaxEta_;
  std::vector<double> selJetMinPt_;
  std::vector<double> selJetMaxEMF_;
  std::vector<double> selJetMinEMF_;

  int  debug_;
  bool doMCData_;
  bool usePFJets_;
  bool useJPTJets_;
  bool useCaloJets_;
  bool useTrackJets_;

  // Data tags
  edm::InputTag jetTag_;
  edm::InputTag genJetTag_;

  char logmessage[128];
    
  // Plots
  TTree * mJetData;      /// Will contain the data passing the jet selection

  std::map<std::string, std::vector<float> > map_s_vd_correctionFactor;
  std::vector<reco::Candidate::LorentzVector > v_JetP4;
  std::vector<reco::Candidate::LorentzVector > v_JetRawP4;
  std::vector<reco::Candidate::LorentzVector > v_GenJetP4;
  
  int    i_NJets;
  double d_Ht;
  double d_MHx;
  double d_MHy;
  double d_MHt;
  
  std::vector<double> vd_JetEtaEtaMoment;
  std::vector<double> vd_JetEtaPhiMoment;
  std::vector<double> vd_JetPhiPhiMoment;

  
  //JetID variables
  std::vector<double> vd_JetFem;
  std::vector<double> vd_JetFhad;
  std::vector<double> vd_JetCharge;
  std::vector<int>    vi_JetHemi;
  std::vector<int>    vi_JetNConst;
  std::vector<bool>   vb_JetIDMinimal;
  std::vector<bool>   vb_JetIDLoose;
  std::vector<bool>   vb_JetIDTight;
  //calo/jpt jet specific
  std::vector<double> vd_JetfHPD;
  std::vector<double> vd_JetfRBX;
  std::vector<double> vd_JetN90;

  //jpt jet specific

  //jpt/pf jet specific
  std::vector<double> vd_JetChargedFem;
  std::vector<double> vd_JetNeutralFem;
  std::vector<double> vd_JetChargedFhad;
  std::vector<double> vd_JetNeutralFhad;
  std::vector<double> vd_JetChargedMult;
  std::vector<double> vd_JetNeutralMult;
  std::vector<double> vd_JetElecMult;
  std::vector<double> vd_JetMuonMult;

  //pf jet specific
  std::vector<double> vd_JetChargedFmu;
  std::vector<double> vd_JetChargedFele;
  std::vector<double> vd_JetChargedFpho;
  std::vector<double> vd_JetHFFem;
  std::vector<double> vd_JetHFFhad;
  std::vector<double> vd_JetChargedHadMult;
  std::vector<double> vd_JetNeutralHadMult;
  std::vector<double> vd_JetHFHadMult;
  std::vector<double> vd_JetHFEMMult;
  std::vector<double> vd_JetHFMult;
  std::vector<double> vd_JetPhotonMult;

  // track info:
  std::vector<int>    vi_JetTrackNo;
  std::vector<double> vd_JetTrackPhi;
  std::vector<double> vd_JetTrackPhiWeighted;
  std::vector<double> vd_JetTrackPt;

  //calo jet corrections
  std::vector<double> vd_JetMCCorrFactor;
  std::vector<double> vd_JetJPTCorrFactor;

  //b-tagging
  std::vector<double> vd_JetBTag_TCHE;
  std::vector<double> vd_JetBTag_TCHP;
  std::vector<double> vd_JetBTag_jetProb;
  std::vector<double> vd_JetBTag_jetBProb;
  std::vector<double> vd_JetBTag_SSVHE;
  std::vector<double> vd_JetBTag_SSVHP;
  std::vector<double> vd_JetBTag_CSV;
  std::vector<double> vd_JetBTag_CSVMVA;
  std::vector<double> vd_JetBTag_SoftLepton;
  std::vector<double> vd_JetBTag_SoftLeptonByIP;
  std::vector<double> vd_JetBTag_SoftLeptonByPt;
  

  //Generator level information
  double d_GenHt;
  double d_GenMHx;
  double d_GenMHy;
  double d_GenMHt;

  //Parton level id for gen jets?
  std::vector<int>    vi_JetPartonId;
  std::vector<int>    vi_JetPartonMother;
  std::vector<int>    vi_JetPartonFlavour;
  std::vector<double> vd_JetPartonPx;
  std::vector<double> vd_JetPartonPy;
  std::vector<double> vd_JetPartonPz;
  std::vector<double> vd_JetPartonEt;
  std::vector<double> vd_JetPartonEnergy;
  std::vector<double> vd_JetPartonPhi;
  std::vector<double> vd_JetPartonEta;

  //Result of some predefined preselection
  bool   bool_JetPreselection;

  std::string outputFileName_;

  double localPi;
  //unsigned int *mSelectorResults;

};
#endif

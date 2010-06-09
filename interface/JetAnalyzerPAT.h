#ifndef JETANALYZERPAT
#define JETANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
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

  std::vector<double> selJetMaxEta_;  /// for preselection cuts on jets and to calculate HT and MHT
  std::vector<double> selJetMinPt_;   /// for preselection cuts on jets and to calculate HT and MHT
  std::vector<double> selJetMaxEMF_;   /// for preselection cuts on jets and to calculate HT and MHT
  std::vector<double> selJetMinEMF_;   /// for preselection cuts on jets and to calculate HT and MHT

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

  int    m_NJets;
  double m_Ht;
  double m_MHx;
  double m_MHy;
  double m_MHt;
  double m_JetEt[50];
  double m_JetPt[50];
  double m_JetPx[50];
  double m_JetPy[50];
  double m_JetPz[50];
  double m_JetE[50];
  double m_JetRawEt[50];
  double m_JetRawPt[50];
  double m_JetRawPx[50];
  double m_JetRawPy[50];
  double m_JetRawPz[50];
  double m_JetRawE[50];
  double m_JetEta[50];
  double m_JetPhi[50];
  double m_JetFem[50];
  double m_JetFhad[50];
  int    m_JetHemi[50];
  double m_JetCharge[50];
  int    m_JetNConst[50];
  bool   m_JetPreselection;
  bool   m_JetIDMinimal[50];
  bool   m_JetIDLoose[50];
  bool   m_JetIDTight[50];

  //calo/jpt jet specific
  double m_JetfHPD[50];
  double m_JetfRBX[50];
  double m_JetN90[50];

  //jpt jet specific

  //jpt/pf jet specific
  double m_JetChargedFem[50];
  double m_JetNeutralFem[50];
  double m_JetChargedFhad[50];
  double m_JetNeutralFhad[50];

  double m_JetChargedMult[50];
  double m_JetNeutralMult[50];
  double m_JetElecMult[50];
  double m_JetMuonMult[50];

  //pf jet specific
  double m_JetChargedFmu[50];
  double m_JetChargedFele[50];
  double m_JetChargedFpho[50];
  double m_JetHFFem[50];
  double m_JetHFFhad[50];
  
  double m_JetChargedHadMult[50];
  double m_JetNeutralHadMult[50];
  double m_JetHFHadMult[50];
  double m_JetHFEMMult[50];
  double m_JetHFMult[50];
  double m_JetPhotonMult[50];

  // track info:
  int    m_JetTrackNo[50];
  double m_JetTrackPhi[50];
  double m_JetTrackPhiWeighted[50];
  double m_JetTrackPt[50];

  //calo jet corrections
  double m_JetMCCorrFactor[50];
  double m_JetJPTCorrFactor[50];

  //b-tagging
  double m_JetBTag_TCHE[50];
  double m_JetBTag_TCHP[50];
  double m_JetBTag_jetProb[50];
  double m_JetBTag_jetBProb[50];
  double m_JetBTag_SSVHE[50];
  double m_JetBTag_SSVHP[50];
  double m_JetBTag_CSV[50];
  double m_JetBTag_CSVMVA[50];
  double m_JetBTag_SoftLepton[50];
  double m_JetBTag_SoftLeptonByIP[50];
  double m_JetBTag_SoftLeptonByPt[50];
  

  int    m_JetPartonId[50];
  int    m_JetPartonMother[50];
  int    m_JetPartonFlavour[50];
  double m_JetPartonPx[50];
  double m_JetPartonPy[50];
  double m_JetPartonPz[50];
  double m_JetPartonEt[50];
  double m_JetPartonEnergy[50];
  double m_JetPartonPhi[50];
  double m_JetPartonEta[50];

  //Generator level information
  double m_GenHt;
  double m_GenMHx;
  double m_GenMHy;
  double m_GenMHt;
  double m_JetGenEt[50];
  double m_JetGenPt[50];
  double m_JetGenE[50];
  double m_JetGenPx[50];
  double m_JetGenPy[50];
  double m_JetGenPz[50];
  double m_JetGenEta[50];
  double m_JetGenPhi[50];

  std::string outputFileName_;

  double localPi;
  //unsigned int *mSelectorResults;

};
#endif

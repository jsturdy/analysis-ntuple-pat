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

  //maps the correction level to a vector corresponding to the correction
  //applied to each jet
  //boost::shared_ptr<std::map<std::string, std::vector<float> > > map_s_vd_correctionFactor ( new std::map<std::string,std::vector<float> >() );
  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector > > v_JetP4    ( new std::vector<reco::Candidate::LorentzVector >() );
  //boost::shared_ptr<std::vector<reco::Candidate::LorentzVector > > v_JetRawP4 ( new std::vector<reco::Candidate::LorentzVector >() );
  ////boost::shared_ptr<std::vector<reco::Candidate::LorentzVector > > v_JetPhysicsP4  ( new std::vector<reco::Candidate::LorentzVector >() );
  ////boost::shared_ptr<std::vector<reco::Candidate::LorentzVector > > v_JetDetectorP4 ( new std::vector<reco::Candidate::LorentzVector >() );

  std::map<std::string, std::vector<float> > map_s_vd_correctionFactor;
  std::vector<reco::Candidate::LorentzVector > v_JetP4;
  std::vector<reco::Candidate::LorentzVector > v_JetRawP4;
  //std::vector<reco::Candidate::LorentzVector > v_JetPhysicsP4;
  //std::vector<reco::Candidate::LorentzVector > v_JetDetectorP4;
  
  int    i_NJets;
  double d_Ht;
  double d_MHx;
  double d_MHy;
  double d_MHt;
  //What of this is necessary if I save a PxPyPzE4D vector of the jet?
  //What of this is necessary if I save a PtEtaPhiE4D vector of the jet?
  double mat_d_JetEt[50];
  double mat_d_JetPt[50];
  double mat_d_JetPx[50];
  double mat_d_JetPy[50];
  double mat_d_JetPz[50];
  double mat_d_JetE[50];
  double mat_d_JetEta[50];
  double mat_d_JetPhi[50];
  //What of this is necessary if I save a PxPyPzE4D vector of the jet?
  double mat_d_JetRawEt[50];
  double mat_d_JetRawPt[50];
  double mat_d_JetRawPx[50];
  double mat_d_JetRawPy[50];
  double mat_d_JetRawPz[50];
  double mat_d_JetRawE[50];
  
  double mat_d_JetEtaEtaMoment[50];
  double mat_d_JetEtaPhiMoment[50];
  double mat_d_JetPhiPhiMoment[50];

  
  //JetID variables
  double mat_d_JetFem[50];
  double mat_d_JetFhad[50];
  double mat_d_JetCharge[50];
  int    mat_i_JetHemi[50];
  int    mat_i_JetNConst[50];
  bool   mat_b_JetIDMinimal[50];
  bool   mat_b_JetIDLoose[50];
  bool   mat_b_JetIDTight[50];
  //calo/jpt jet specific
  double mat_d_JetfHPD[50];
  double mat_d_JetfRBX[50];
  double mat_d_JetN90[50];

  //jpt jet specific

  //jpt/pf jet specific
  double mat_d_JetChargedFem[50];
  double mat_d_JetNeutralFem[50];
  double mat_d_JetChargedFhad[50];
  double mat_d_JetNeutralFhad[50];
  double mat_d_JetChargedMult[50];
  double mat_d_JetNeutralMult[50];
  double mat_d_JetElecMult[50];
  double mat_d_JetMuonMult[50];

  //pf jet specific
  double mat_d_JetChargedFmu[50];
  double mat_d_JetChargedFele[50];
  double mat_d_JetChargedFpho[50];
  double mat_d_JetHFFem[50];
  double mat_d_JetHFFhad[50];
  double mat_d_JetChargedHadMult[50];
  double mat_d_JetNeutralHadMult[50];
  double mat_d_JetHFHadMult[50];
  double mat_d_JetHFEMMult[50];
  double mat_d_JetHFMult[50];
  double mat_d_JetPhotonMult[50];

  // track info:
  int    mat_i_JetTrackNo[50];
  double mat_d_JetTrackPhi[50];
  double mat_d_JetTrackPhiWeighted[50];
  double mat_d_JetTrackPt[50];

  //calo jet corrections
  double mat_d_JetMCCorrFactor[50];
  double mat_d_JetJPTCorrFactor[50];

  //b-tagging
  double mat_d_JetBTag_TCHE[50];
  double mat_d_JetBTag_TCHP[50];
  double mat_d_JetBTag_jetProb[50];
  double mat_d_JetBTag_jetBProb[50];
  double mat_d_JetBTag_SSVHE[50];
  double mat_d_JetBTag_SSVHP[50];
  double mat_d_JetBTag_CSV[50];
  double mat_d_JetBTag_CSVMVA[50];
  double mat_d_JetBTag_SoftLepton[50];
  double mat_d_JetBTag_SoftLeptonByIP[50];
  double mat_d_JetBTag_SoftLeptonByPt[50];
  

  //Generator level information
  double d_GenHt;
  double d_GenMHx;
  double d_GenMHy;
  double d_GenMHt;
  double mat_d_JetGenEt[50];
  double mat_d_JetGenPt[50];
  double mat_d_JetGenE[50];
  double mat_d_JetGenPx[50];
  double mat_d_JetGenPy[50];
  double mat_d_JetGenPz[50];
  double mat_d_JetGenEta[50];
  double mat_d_JetGenPhi[50];

  //Parton level id for gen jets?
  int    mat_i_JetPartonId[50];
  int    mat_i_JetPartonMother[50];
  int    mat_i_JetPartonFlavour[50];
  double mat_d_JetPartonPx[50];
  double mat_d_JetPartonPy[50];
  double mat_d_JetPartonPz[50];
  double mat_d_JetPartonEt[50];
  double mat_d_JetPartonEnergy[50];
  double mat_d_JetPartonPhi[50];
  double mat_d_JetPartonEta[50];

  //Result of some predefined preselection
  bool   bool_JetPreselection;

  std::string outputFileName_;

  double localPi;
  //unsigned int *mSelectorResults;

};
#endif

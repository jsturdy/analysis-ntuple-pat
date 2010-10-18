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

  typedef struct {
    double Ht;
    double MHx;
    double MHy;
    double MHz;
    double MHE;
    double MHt;
  } MYMHT;

  typedef struct {
    bool   JetIDMinimal;
    bool   JetIDLoose;
    bool   JetIDTight;
  
    double JetFem;
    double JetFhad;
    double JetCharge;
    int    JetHemi;
    int    JetNConst;
    //calo/jpt jet specific
    double JetfHPD;
    double JetfRBX;
    double JetN90;
  
    //jpt/pf jet specific
    double JetChargedFem;
    double JetNeutralFem;
    double JetChargedFhad;
    double JetNeutralFhad;
    double JetChargedMult;
    double JetNeutralMult;
    double JetElecMult;
    double JetMuonMult;
  
    //pf jet specific
    double JetChargedFmu;
    double JetChargedFele;
    double JetChargedFpho;
    double JetHFFem;
    double JetHFFhad;
    double JetChargedHadMult;
    double JetNeutralHadMult;
    double JetHFHadMult;
    double JetHFEMMult;
    double JetHFMult;
    double JetPhotonMult;
  } MYJETID;

  typedef struct {
    double JetBTag_TCHE;
    double JetBTag_TCHP;
    double JetBTag_jetProb;
    double JetBTag_jetBProb;
    double JetBTag_SSVHE;
    double JetBTag_SSVHP;
    double JetBTag_CSV;
    double JetBTag_CSVMVA;
    double JetBTag_SoftLepton;
    double JetBTag_SoftLeptonByIP;
    double JetBTag_SoftLeptonByPt;
  } BTAGINFO;


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
  std::vector<reco::Candidate::LorentzVector > v_RawJetP4;
  std::vector<reco::Candidate::LorentzVector > v_GenJetP4;

  std::vector<double> vd_JetPx;
  std::vector<double> vd_JetPy;
  std::vector<double> vd_JetPz;
  std::vector<double> vd_JetE;
    
  std::vector<double> vd_RawJetPx;
  std::vector<double> vd_RawJetPy;
  std::vector<double> vd_RawJetPz;
  std::vector<double> vd_RawJetE;
    
  std::vector<double> vd_GenJetPx;
  std::vector<double> vd_GenJetPy;
  std::vector<double> vd_GenJetPz;
  std::vector<double> vd_GenJetE;
    
  int    i_NJets;

  MYMHT JetMHt;
  double d_Ht;
  double d_MHx;
  double d_MHy;
  double d_MHz;
  double d_MHE;
  double d_MHt;
  MYMHT GenMHt;
  double d_GenHt;
  double d_GenMHx;
  double d_GenMHy;
  double d_GenMHz;
  double d_GenMHE;
  double d_GenMHt;

  std::vector<double> vd_JetEtaEtaMoment;
  std::vector<double> vd_JetEtaPhiMoment;
  std::vector<double> vd_JetPhiPhiMoment;

  
  //JetIDSelectionFunctor   caloJetIDMinimal;
  //JetIDSelectionFunctor   caloJetIDLoose;
  //JetIDSelectionFunctor   caloJetIDTight;
  //PFJetIDSelectionFunctor pfJetIDLoose;
  //PFJetIDSelectionFunctor pfJetIDTight;

  pat::strbitset retmin;
  pat::strbitset retloo;
  pat::strbitset rettig;
  //pat::strbitset ret = jetIDLoose.getBitTemplate();

  //JetID variables
  std::vector<bool>   vb_JetIDMinimal;
  std::vector<bool>   vb_JetIDLoose;
  std::vector<bool>   vb_JetIDTight;
  
  std::vector<double> vd_JetFem;
  std::vector<double> vd_JetFhad;
  std::vector<double> vd_JetCharge;
  std::vector<int>    vi_JetHemi;
  std::vector<int>    vi_JetNConst;
  //calo/jpt jet specific
  std::vector<double> vd_JetfHPD;
  std::vector<double> vd_JetfRBX;
  std::vector<double> vd_JetN90;
  
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
  std::vector<MYJETID> vjid_JetID;
  
  // track info:
  std::vector<int>    vi_JetTrackNo;
  std::vector<double> vd_JetTrackPhi;
  std::vector<double> vd_JetTrackPhiWeighted;
  std::vector<double> vd_JetTrackPt;
  
  //calo jet corrections
  std::vector<double> vd_JetMCCorrFactor;
  std::vector<double> vd_JetJPTCorrFactor;

  //b-tagging
  std::vector<BTAGINFO> vbtag_JetBtag;
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
  
  //Parton level id for gen jets?
  std::vector<int>    vi_JetPartonId;
  std::vector<int>    vi_JetPartonMother;
  std::vector<int>    vi_JetPartonFlavour;
  std::vector<double> vd_JetPartonPx;
  std::vector<double> vd_JetPartonPy;
  std::vector<double> vd_JetPartonPz;
  std::vector<double> vd_JetPartonE;

  //Result of some predefined preselection
  bool   bool_JetPreselection;

  std::string outputFileName_;

  double localPi;
  //unsigned int *mSelectorResults;

  void maintenance(const int& nJets) {
    //Setup the vectors
    map_s_vd_correctionFactor.clear();
    
    v_JetP4.clear();
    v_RawJetP4.clear();
    v_GenJetP4.clear();
    
    vd_JetPx.clear();
    vd_JetPy.clear();
    vd_JetPz.clear();
    vd_JetE.clear();
    
    vd_RawJetPx.clear();
    vd_RawJetPy.clear();
    vd_RawJetPz.clear();
    vd_RawJetE.clear();
    
    vd_GenJetPx.clear();
    vd_GenJetPy.clear();
    vd_GenJetPz.clear();
    vd_GenJetE.clear();
    
    vd_JetEtaEtaMoment.clear();
    vd_JetEtaPhiMoment.clear();
    vd_JetPhiPhiMoment.clear();
    
    vb_JetIDMinimal.clear();
    vb_JetIDLoose.clear();
    vb_JetIDTight.clear();
    
    vd_JetFem.clear();
    vd_JetFhad.clear();
    vd_JetCharge.clear();
    vi_JetHemi.clear();
    vi_JetNConst.clear();
    vd_JetfHPD.clear();
    vd_JetfRBX.clear();
    vd_JetN90.clear();
    
    vd_JetChargedFem.clear();
    vd_JetNeutralFem.clear();
    vd_JetChargedFhad.clear();
    vd_JetNeutralFhad.clear();
    vd_JetChargedMult.clear();
    vd_JetNeutralMult.clear();
    vd_JetElecMult.clear();
    vd_JetMuonMult.clear();
    
    vd_JetChargedFmu.clear();
    vd_JetChargedFele.clear();
    vd_JetChargedFpho.clear();
    vd_JetHFFem.clear();
    vd_JetHFFhad.clear();
    vd_JetChargedHadMult.clear();
    vd_JetNeutralHadMult.clear();
    vd_JetHFHadMult.clear();
    vd_JetHFEMMult.clear();
    vd_JetHFMult.clear();
    vd_JetPhotonMult.clear();
    
    vi_JetTrackNo.clear();
    vd_JetTrackPhi.clear();
    vd_JetTrackPhiWeighted.clear();
    vd_JetTrackPt.clear();
    
    vd_JetMCCorrFactor.clear();
    vd_JetJPTCorrFactor.clear();
    
    vd_JetBTag_TCHE.clear();
    vd_JetBTag_TCHP.clear();
    vd_JetBTag_jetProb.clear();
    vd_JetBTag_jetBProb.clear();
    vd_JetBTag_SSVHE.clear();
    vd_JetBTag_SSVHP.clear();
    vd_JetBTag_CSV.clear();
    vd_JetBTag_CSVMVA.clear();
    vd_JetBTag_SoftLepton.clear();
    vd_JetBTag_SoftLeptonByIP.clear();
    vd_JetBTag_SoftLeptonByPt.clear();
    
    vi_JetPartonId.clear();
    vi_JetPartonMother.clear();
    vi_JetPartonFlavour.clear();
    vd_JetPartonPx.clear();
    vd_JetPartonPy.clear();
    vd_JetPartonPz.clear();
    vd_JetPartonE.clear();
    
    //v_JetP4.reservenJets;
    //v_RawJetP4.reservenJets;
    //v_GenJetP4.reservenJets;
    //
    //vd_JetPx.reservenJets;
    //vd_JetPy.reservenJets;
    //vd_JetPz.reservenJets;
    //vd_JetE.reservenJets;
    //
    //vd_RawJetPx.reservenJets;
    //vd_RawJetPy.reservenJets;
    //vd_RawJetPz.reservenJets;
    //vd_RawJetE.reservenJets;
    //
    //vd_GenJetPx.reservenJets;
    //vd_GenJetPy.reservenJets;
    //vd_GenJetPz.reservenJets;
    //vd_GenJetE.reservenJets;
    //
    //vd_JetEtaEtaMoment.reservenJets;
    //vd_JetEtaPhiMoment.reservenJets;
    //vd_JetPhiPhiMoment.reservenJets;
    //
    //vb_JetIDMinimal.reservenJets;
    //vb_JetIDLoose.reservenJets;
    //vb_JetIDTight.reservenJets;
    //
    //vd_JetFem.reservenJets;
    //vd_JetFhad.reservenJets;
    //vd_JetCharge.reservenJets;
    //vi_JetHemi.reservenJets;
    //vi_JetNConst.reservenJets;
    //vd_JetfHPD.reservenJets;
    //vd_JetfRBX.reservenJets;
    //vd_JetN90.reservenJets;
    //
    //vd_JetChargedFem.reservenJets;
    //vd_JetNeutralFem.reservenJets;
    //vd_JetChargedFhad.reservenJets;
    //vd_JetNeutralFhad.reservenJets;
    //vd_JetChargedMult.reservenJets;
    //vd_JetNeutralMult.reservenJets;
    //vd_JetElecMult.reservenJets;
    //vd_JetMuonMult.reservenJets;
    //
    //vd_JetChargedFmu.reservenJets;
    //vd_JetChargedFele.reservenJets;
    //vd_JetChargedFpho.reservenJets;
    //vd_JetHFFem.reservenJets;
    //vd_JetHFFhad.reservenJets;
    //vd_JetChargedHadMult.reservenJets;
    //vd_JetNeutralHadMult.reservenJets;
    //vd_JetHFHadMult.reservenJets;
    //vd_JetHFEMMult.reservenJets;
    //vd_JetHFMult.reservenJets;
    //vd_JetPhotonMult.reservenJets;
    //
    //vi_JetTrackNo.reservenJets;
    //vd_JetTrackPhi.reservenJets;
    //vd_JetTrackPhiWeighted.reservenJets;
    //vd_JetTrackPt.reservenJets;
    //
    //vd_JetMCCorrFactor.reservenJets;
    //vd_JetJPTCorrFactor.reservenJets;
    //
    //vd_JetBTag_TCHE.reservenJets;
    //vd_JetBTag_TCHP.reservenJets;
    //vd_JetBTag_jetProb.reservenJets;
    //vd_JetBTag_jetBProb.reservenJets;
    //vd_JetBTag_SSVHE.reservenJets;
    //vd_JetBTag_SSVHP.reservenJets;
    //vd_JetBTag_CSV.reservenJets;
    //vd_JetBTag_CSVMVA.reservenJets;
    //vd_JetBTag_SoftLepton.reservenJets;
    //vd_JetBTag_SoftLeptonByIP.reservenJets;
    //vd_JetBTag_SoftLeptonByPt.reservenJets;
    //
    //vi_JetPartonId.reservenJets;
    //vi_JetPartonMother.reservenJets;
    //vi_JetPartonFlavour.reservenJets;
    //vd_JetPartonPx.reservenJets;
    //vd_JetPartonPy.reservenJets;
    //vd_JetPartonPz.reservenJets;
    //vd_JetPartonE.reservenJets;
    
  }
};
#endif

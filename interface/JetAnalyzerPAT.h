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
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// SUSY include files
//#include "SusyAnalysis/EventSelector/interface/SusyEventSelector.h"
//#include "SusyAnalysis/EventSelector/interface/SelectorSequence.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
//Included for cross cleaning
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

//#include "PhysicsTools/Utilities/interface/deltaPhi.h"
//#include "PhysicsTools/Utilities/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Hemisphere.h"
#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"


#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

//
// Class declaration
//

class JetAnalyzerPAT {
 public:
  JetAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~JetAnalyzerPAT();
  
  bool filter(const edm::Event&, const edm::EventSetup&);
  
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
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
    //bool   JetIDMinimal;
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

  // Configuration parameters
  TString prefix_;

  int    minNJets_;                  /// for preselection cuts on jets and to calculate HT and MHT
  double jetMaxEta_;
  double jetMinPt_;

  double htMaxEta_;
  double htMinPt_;

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

  double electronPt_  ;
  double electronIso_ ;
  double tauPt_       ;
  double tauIso_      ;
  double muonPt_      ;
  double muonIso_     ;
  double photonPt_    ;
  double photonIso_   ;
  

  JetCorrectionUncertainty *jecUnc;
  
  // Data tags
  edm::InputTag jetTag_;
  edm::InputTag genJetTag_;

  std::string   jetCorTag_;

  char logmessage[128];

  // Plots
  TTree * mJetData;      /// Will contain the data passing the jet selection

  std::map<std::string, std::vector<float> > map_s_vf_correctionFactor;
  //std::map<std::string, std::vector<int> >   map_s_vi_JetOverlaps;
  //std::map<std::string, std::vector<int> >   map_s_vi_JetNOverlaps;
  std::vector<int>                           vi_JetElectronOverlaps;
  std::vector<int>                           vi_JetElectronNOverlaps;
  std::vector<int>                           vi_JetMuonOverlaps;
  std::vector<int>                           vi_JetMuonNOverlaps;
  std::vector<int>                           vi_JetTauOverlaps;
  std::vector<int>                           vi_JetTauNOverlaps;
  std::vector<int>                           vi_JetPhotonOverlaps;
  std::vector<int>                           vi_JetPhotonNOverlaps;

  std::vector<reco::Candidate::LorentzVector > v_JetP4;
  std::vector<reco::Candidate::LorentzVector > v_RawJetP4;
  std::vector<reco::Candidate::LorentzVector > v_GenJetP4;

  reco::Candidate::LorentzVector MHtP4;
  reco::Candidate::LorentzVector GenMHtP4;

  std::vector<float> vf_JECUncPlus;
  std::vector<float> vf_JECUncMinus;

  int    i_NJets;

  MYMHT JetMHt;
  double d_Ht;

  MYMHT GenMHt;
  double d_GenHt;

  std::vector<double> vd_JetEtaEtaMoment;
  std::vector<double> vd_JetEtaPhiMoment;
  std::vector<double> vd_JetPhiPhiMoment;

  //JetID variables
  //pat::strbitset retmin;
  pat::strbitset retloo;
  pat::strbitset rettig;

  //std::vector<bool>   vb_JetIDMinimal;
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
  std::vector<reco::Candidate::LorentzVector > v_JetPartonP4;
  std::vector<int>    vi_JetPartonId;
  std::vector<int>    vi_JetPartonStatus;
  std::vector<int>    vi_JetPartonMother;
  std::vector<int>    vi_JetPartonMotherStatus;
  std::vector<int>    vi_JetPartonFlavour;

  //Result of some predefined preselection
  bool   bool_JetPreselection;

  void maintenance(const int& nJets) {
    //Setup the vectors
    map_s_vf_correctionFactor.clear();

    //map_s_vi_JetNOverlaps.clear();
    //map_s_vi_JetOverlaps.clear();

    vi_JetElectronNOverlaps.clear();
    vi_JetElectronOverlaps.clear();
    vi_JetMuonNOverlaps.clear();
    vi_JetMuonOverlaps.clear();
    vi_JetTauNOverlaps.clear();
    vi_JetTauOverlaps.clear();
    vi_JetPhotonNOverlaps.clear();
    vi_JetPhotonOverlaps.clear();

    vf_JECUncPlus.clear();
    vf_JECUncMinus.clear();
    
    v_JetP4.clear();
    v_RawJetP4.clear();
    v_GenJetP4.clear();
    
    vd_JetEtaEtaMoment.clear();
    vd_JetEtaPhiMoment.clear();
    vd_JetPhiPhiMoment.clear();
    
    //vb_JetIDMinimal.clear();
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
    
    v_JetPartonP4.clear();
    vi_JetPartonId.clear();
    vi_JetPartonStatus.clear();
    vi_JetPartonMother.clear();
    vi_JetPartonMotherStatus.clear();
    vi_JetPartonFlavour.clear();

    ////
    std::map<std::string,std::vector<float> >().swap(map_s_vf_correctionFactor);

    //std::map<std::string,std::vector<int> >().swap(map_s_vi_JetNOverlaps);
    //std::map<std::string,std::vector<int> >().swap(map_s_vi_JetOverlaps);

    std::vector<int>().swap(vi_JetElectronNOverlaps);
    std::vector<int>().swap(vi_JetElectronOverlaps);
    std::vector<int>().swap(vi_JetMuonNOverlaps);
    std::vector<int>().swap(vi_JetMuonOverlaps);
    std::vector<int>().swap(vi_JetTauNOverlaps);
    std::vector<int>().swap(vi_JetTauOverlaps);
    std::vector<int>().swap(vi_JetPhotonNOverlaps);
    std::vector<int>().swap(vi_JetPhotonOverlaps);

    std::vector<float>().swap(vf_JECUncPlus);
    std::vector<float>().swap(vf_JECUncMinus);
    
    std::vector<reco::Candidate::LorentzVector>().swap(v_JetP4);
    std::vector<reco::Candidate::LorentzVector>().swap(v_RawJetP4);
    std::vector<reco::Candidate::LorentzVector>().swap(v_GenJetP4);
    
    std::vector<double>().swap(vd_JetEtaEtaMoment);
    std::vector<double>().swap(vd_JetEtaPhiMoment);
    std::vector<double>().swap(vd_JetPhiPhiMoment);
    
    //std::vector<bool>().swap(vb_JetIDMinimal);
    std::vector<bool>().swap(vb_JetIDLoose);
    std::vector<bool>().swap(vb_JetIDTight);
    
    std::vector<double>().swap(vd_JetFem);
    std::vector<double>().swap(vd_JetFhad);
    std::vector<double>().swap(vd_JetCharge);
    std::vector<int>().swap(vi_JetHemi);
    std::vector<int>().swap(vi_JetNConst);
    std::vector<double>().swap(vd_JetfHPD);
    std::vector<double>().swap(vd_JetfRBX);
    std::vector<double>().swap(vd_JetN90);
    
    std::vector<double>().swap(vd_JetChargedFem);
    std::vector<double>().swap(vd_JetNeutralFem);
    std::vector<double>().swap(vd_JetChargedFhad);
    std::vector<double>().swap(vd_JetNeutralFhad);
    std::vector<double>().swap(vd_JetChargedMult);
    std::vector<double>().swap(vd_JetNeutralMult);
    std::vector<double>().swap(vd_JetElecMult);
    std::vector<double>().swap(vd_JetMuonMult);
    
    std::vector<double>().swap(vd_JetChargedFmu);
    std::vector<double>().swap(vd_JetChargedFele);
    std::vector<double>().swap(vd_JetChargedFpho);
    std::vector<double>().swap(vd_JetHFFem);
    std::vector<double>().swap(vd_JetHFFhad);
    std::vector<double>().swap(vd_JetChargedHadMult);
    std::vector<double>().swap(vd_JetNeutralHadMult);
    std::vector<double>().swap(vd_JetHFHadMult);
    std::vector<double>().swap(vd_JetHFEMMult);
    std::vector<double>().swap(vd_JetHFMult);
    std::vector<double>().swap(vd_JetPhotonMult);
    
    std::vector<int>().swap(vi_JetTrackNo);
    std::vector<double>().swap(vd_JetTrackPhi);
    std::vector<double>().swap(vd_JetTrackPhiWeighted);
    std::vector<double>().swap(vd_JetTrackPt);
    
    std::vector<double>().swap(vd_JetMCCorrFactor);
    std::vector<double>().swap(vd_JetJPTCorrFactor);
    
    std::vector<double>().swap(vd_JetBTag_TCHE);
    std::vector<double>().swap(vd_JetBTag_TCHP);
    std::vector<double>().swap(vd_JetBTag_jetProb);
    std::vector<double>().swap(vd_JetBTag_jetBProb);
    std::vector<double>().swap(vd_JetBTag_SSVHE);
    std::vector<double>().swap(vd_JetBTag_SSVHP);
    std::vector<double>().swap(vd_JetBTag_CSV);
    std::vector<double>().swap(vd_JetBTag_CSVMVA);
    std::vector<double>().swap(vd_JetBTag_SoftLepton);
    std::vector<double>().swap(vd_JetBTag_SoftLeptonByIP);
    std::vector<double>().swap(vd_JetBTag_SoftLeptonByPt);
    
    std::vector<reco::Candidate::LorentzVector>().swap(v_JetPartonP4);
    std::vector<int>().swap(vi_JetPartonId);
    std::vector<int>().swap(vi_JetPartonStatus);
    std::vector<int>().swap(vi_JetPartonMother);
    std::vector<int>().swap(vi_JetPartonMotherStatus);
    std::vector<int>().swap(vi_JetPartonFlavour);
  }
};
#endif

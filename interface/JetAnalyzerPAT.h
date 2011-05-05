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
  void bookTTree(TTree*);

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

  // Plots
  //TTree * mJetData;      /// Will contain the data passing the jet selection

  //std::auto_ptr<std::map<std::string, std::auto_ptr<std::vector<double> > >  map_s_vd_correctionFactor;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorUnc;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL1;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL2;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL3;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL2L3;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL5uds;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL5c;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL5b;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL5glu;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL7uds;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL7c;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL7b;
  std::auto_ptr<std::vector<double> >  vd_correctionFactorL7glu;

  //std::auto_ptr<std::map<std::string, std::auto_ptr<std::vector<int> > >  map_s_vi_JetOverlaps;
  //std::auto_ptr<std::map<std::string, std::auto_ptr<std::vector<int> > >  map_s_vi_JetNOverlaps;

  std::auto_ptr<std::vector<int> >  vi_JetElectronOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetElectronNOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetMuonOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetMuonNOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetTauOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetTauNOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetPhotonOverlaps;
  std::auto_ptr<std::vector<int> >  vi_JetPhotonNOverlaps;

  std::auto_ptr<std::vector<reco::Candidate::LorentzVector > >  v_JetP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector > >  v_RawJetP4;
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector > >  v_GenJetP4;

  std::auto_ptr<reco::Candidate::LorentzVector> MHtP4;
  std::auto_ptr<reco::Candidate::LorentzVector> GenMHtP4;

  std::auto_ptr<std::vector<double> >  vd_JECUncPlus;
  std::auto_ptr<std::vector<double> >  vd_JECUncMinus;

  int    i_NJets;

  MYMHT JetMHt;
  double d_Ht;

  MYMHT GenMHt;
  double d_GenHt;

  std::auto_ptr<std::vector<double > >  vd_JetEtaEtaMoment;
  std::auto_ptr<std::vector<double > >  vd_JetEtaPhiMoment;
  std::auto_ptr<std::vector<double > >  vd_JetPhiPhiMoment;

  //JetID variables
  std::auto_ptr<std::vector<int> >  vb_JetIDMinimal;
  std::auto_ptr<std::vector<int> >  vb_JetIDLoose;
  std::auto_ptr<std::vector<int> >  vb_JetIDTight;
  
  std::auto_ptr<std::vector<double> >  vd_JetEFrac_em;
  std::auto_ptr<std::vector<double> >  vd_JetEFrac_had;
  std::auto_ptr<std::vector<double> >  vd_JetCharge;
  std::auto_ptr<std::vector<int> >     vi_JetHemi;
  std::auto_ptr<std::vector<int> >     vi_JetNConst;

  //calo/jpt jet specific
  std::auto_ptr<std::vector<double> >  vd_JetfHPD;
  std::auto_ptr<std::vector<double> >  vd_JetfRBX;
  std::auto_ptr<std::vector<double> >  vd_JetN90;
  
  //jpt/pf jet specific
  std::auto_ptr<std::vector<double> >  vd_JetChargedFrac_em;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralFrac_em;
  std::auto_ptr<std::vector<double> >  vd_JetChargedFrac_had;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralFrac_had;

  std::auto_ptr<std::vector<double> >  vd_JetChargedEn_em;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralEn_em;
  std::auto_ptr<std::vector<double> >  vd_JetChargedEn_had;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralEn_had;

  std::auto_ptr<std::vector<double> >  vd_JetChargedMult;
  std::auto_ptr<std::vector<double> >  vd_JetElectronMult;
  std::auto_ptr<std::vector<double> >  vd_JetMuonMult;
  
  //pf jet specific
  std::auto_ptr<std::vector<double> >  vd_JetHFMult_had;
  std::auto_ptr<std::vector<double> >  vd_JetHFMult_em;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralMult_had;
  std::auto_ptr<std::vector<double> >  vd_JetChargedMult_had;
  std::auto_ptr<std::vector<double> >  vd_JetPhotonMult;
  std::auto_ptr<std::vector<double> >  vd_JetNeutralMult;

  std::auto_ptr<std::vector<double> >  vd_JetHFFrac_em;
  std::auto_ptr<std::vector<double> >  vd_JetHFFrac_had;
  std::auto_ptr<std::vector<double> >  vd_JetEFrac_muon;
  std::auto_ptr<std::vector<double> >  vd_JetChargedFrac_muon;
  std::auto_ptr<std::vector<double> >  vd_JetEFrac_electron;
  std::auto_ptr<std::vector<double> >  vd_JetEFrac_photon;

  std::auto_ptr<std::vector<double> >  vd_JetHFEn_em;
  std::auto_ptr<std::vector<double> >  vd_JetHFEn_had;
  std::auto_ptr<std::vector<double> >  vd_JetEn_muon;
  std::auto_ptr<std::vector<double> >  vd_JetChargedEn_muon;
  std::auto_ptr<std::vector<double> >  vd_JetEn_electron;
  std::auto_ptr<std::vector<double> >  vd_JetEn_photon;

  // track info:
  std::auto_ptr<std::vector<int> >     vi_JetTrackNo;
  std::auto_ptr<std::vector<double> >  vd_JetTrackPhi;
  std::auto_ptr<std::vector<double> >  vd_JetTrackPhiWeighted;
  std::auto_ptr<std::vector<double> >  vd_JetTrackPt;
  
  //b-tagging
  //std::auto_ptr<std::vector<BTAGINFO> >  vbtag_JetBtag;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_TCHE;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_TCHP;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_jetProb;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_jetBProb;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_SSVHE;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_SSVHP;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_CSV;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_CSVMVA;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_SoftLepton;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_SoftLeptonByIP;
  std::auto_ptr<std::vector<double> >  vd_JetBTag_SoftLeptonByPt;
  
  //Parton level id for gen jets?
  std::auto_ptr<std::vector<reco::Candidate::LorentzVector> >  v_JetPartonP4;
  std::auto_ptr<std::vector<int> >  vi_JetPartonId;
  std::auto_ptr<std::vector<int> >  vi_JetPartonStatus;
  std::auto_ptr<std::vector<int> >  vi_JetPartonMother;
  std::auto_ptr<std::vector<int> >  vi_JetPartonMotherStatus;
  std::auto_ptr<std::vector<int> >  vi_JetPartonFlavour;

  //Result of some predefined preselection
  bool   bool_JetPreselection;

 public:
  void maintenance() {
    //Setup the vectors
    //map_s_vd_correctionFactor->clear();
    vd_correctionFactorUnc->clear();
    vd_correctionFactorL1->clear();
    vd_correctionFactorL2->clear();
    vd_correctionFactorL3->clear();
    vd_correctionFactorL2L3->clear();
    vd_correctionFactorL5uds->clear();
    vd_correctionFactorL5c->clear();
    vd_correctionFactorL5b->clear();
    vd_correctionFactorL5glu->clear();
    vd_correctionFactorL7uds->clear();
    vd_correctionFactorL7c->clear();
    vd_correctionFactorL7b->clear();
    vd_correctionFactorL7glu->clear();

    //map_s_vi_JetNOverlaps->clear();
    //map_s_vi_JetOverlaps->clear();

    vi_JetElectronNOverlaps->clear();
    vi_JetElectronOverlaps->clear();
    vi_JetMuonNOverlaps->clear();
    vi_JetMuonOverlaps->clear();
    vi_JetTauNOverlaps->clear();
    vi_JetTauOverlaps->clear();
    vi_JetPhotonNOverlaps->clear();
    vi_JetPhotonOverlaps->clear();

    v_JetP4->clear();
    v_RawJetP4->clear();
    v_GenJetP4->clear();
    
    //reco::Candidate::LorentzVector MHtP4;
    //reco::Candidate::LorentzVector GenMHtP4;

    vd_JECUncPlus->clear();
    vd_JECUncMinus->clear();
    
    vd_JetEtaEtaMoment->clear();
    vd_JetEtaPhiMoment->clear();
    vd_JetPhiPhiMoment->clear();
    
    vb_JetIDMinimal->clear();
    vb_JetIDLoose->clear();
    vb_JetIDTight->clear();
    
    vd_JetEFrac_em->clear();
    vd_JetEFrac_had->clear();
    vd_JetCharge->clear();
    vi_JetHemi->clear();
    vi_JetNConst->clear();

    vd_JetfHPD->clear();
    vd_JetfRBX->clear();
    vd_JetN90->clear();

    vd_JetChargedFrac_em->clear();
    vd_JetNeutralFrac_em->clear();
    vd_JetChargedFrac_had->clear();
    vd_JetNeutralFrac_had->clear();

    vd_JetChargedEn_em->clear();
    vd_JetNeutralEn_em->clear();
    vd_JetChargedEn_had->clear();
    vd_JetNeutralEn_had->clear();

    vd_JetChargedMult->clear();
    vd_JetElectronMult->clear();
    vd_JetMuonMult->clear();

    
    vd_JetHFMult_had->clear();
    vd_JetHFMult_em->clear();
    vd_JetNeutralMult_had->clear();
    vd_JetChargedMult_had->clear();
    vd_JetPhotonMult->clear();
    vd_JetNeutralMult->clear();
    
    vd_JetHFFrac_em->clear();
    vd_JetHFFrac_had->clear();
    vd_JetEFrac_muon->clear();
    vd_JetChargedFrac_muon->clear();
    vd_JetEFrac_electron->clear();
    vd_JetEFrac_photon->clear();

    vd_JetHFEn_em->clear();
    vd_JetHFEn_had->clear();
    vd_JetEn_muon->clear();
    vd_JetChargedEn_muon->clear();
    vd_JetEn_electron->clear();
    vd_JetEn_photon->clear();


    vi_JetTrackNo->clear();
    vd_JetTrackPhi->clear();
    vd_JetTrackPhiWeighted->clear();
    vd_JetTrackPt->clear();

    vd_JetBTag_TCHE->clear();
    vd_JetBTag_TCHP->clear();
    vd_JetBTag_jetProb->clear();
    vd_JetBTag_jetBProb->clear();
    vd_JetBTag_SSVHE->clear();
    vd_JetBTag_SSVHP->clear();
    vd_JetBTag_CSV->clear();
    vd_JetBTag_CSVMVA->clear();
    vd_JetBTag_SoftLepton->clear();
    vd_JetBTag_SoftLeptonByIP->clear();
    vd_JetBTag_SoftLeptonByPt->clear();
    
    //generator information
    v_JetPartonP4->clear();
    vi_JetPartonId->clear();
    vi_JetPartonStatus->clear();
    vi_JetPartonMother->clear();
    vi_JetPartonMotherStatus->clear();
    vi_JetPartonFlavour->clear();

  }
};
#endif

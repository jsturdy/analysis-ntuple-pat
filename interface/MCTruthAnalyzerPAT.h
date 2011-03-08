#ifndef MCTRUTHANALYZERPAT
#define MCTRUTHANALYZERPAT

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

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
//#include "DataFormats/PatCandidates/interface/PATObject.h"

//
// Class declaration
//
class MCTruthAnalyzerPAT {
 public:
  MCTruthAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~MCTruthAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& es );
  
  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  /// Define all plots
  void bookTTree();
  

private:
  
  //configuration parameters
  edm::ParameterSet genParams;
  edm::InputTag genParticleTag_;

  int    debug_;

  char logmessage[128];
    
  // Plots
  TTree * mMCTruthData;   /// Will contain the lepton data after cuts

  // Variables
  //int    m_AlpIdTest;
  //std::vector<double> vd_AlpPtScale;
  double d_Pthat;

  std::vector<reco::Candidate::LorentzVector> v_genP4;
  std::vector<reco::Candidate::LorentzVector> v_genParticleP4;
  int               i_genLength;
  std::vector<int>  vi_genIds;
  std::vector<int>  vi_genRefs;
  std::vector<int>  vi_genStatus;
  std::vector<int>  vi_genDaughters;

  int               i_genParticleLength;
  std::vector<int>  vi_genParticleIds;
  std::vector<int>  vi_genParticleRefs;
  std::vector<int>  vi_genParticleStatus;
  std::vector<int>  vi_genParticleDaughters;

  void maintenance(const int& nParts) {
    v_genP4        .clear();
    vi_genIds      .clear();
    vi_genRefs     .clear();
    vi_genStatus   .clear();
    vi_genDaughters.clear();
    
    v_genParticleP4        .clear();
    vi_genParticleIds      .clear();
    vi_genParticleRefs     .clear();
    vi_genParticleStatus   .clear();
    vi_genParticleDaughters.clear();
  }

};

#endif

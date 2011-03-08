
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      MCTruthAnalyzerPAT
// 
/**\class MCTruthAnalyzerPAT MCTruthAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/MCTruthAnalyzerPAT.cc

Description: Variable collector/ntupler for SUSY search with Jets + MET

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: MCTruthAnalyzerPAT.cc,v 1.2 2011/03/07 19:01:29 sturdy Exp $
//
//


#include "JSturdy/AnalysisNtuplePAT/interface/MCTruthAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>



MCTruthAnalyzerPAT::MCTruthAnalyzerPAT(const edm::ParameterSet& genParams, TTree* tmpAllData)
{ 

  mMCTruthData = tmpAllData;

  genParticleTag_ = genParams.getUntrackedParameter<edm::InputTag>("genParticleTag");
  debug_          = genParams.getUntrackedParameter<int>("debugTruth",0);
 
  // Initialise ntuple branches
  bookTTree();

}


//________________________________________________________________________________________
MCTruthAnalyzerPAT::~MCTruthAnalyzerPAT() 
{
  
}

//
//________________________________________________________________________________________
void MCTruthAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
}

//________________________________________________________________________________________
bool MCTruthAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace edm;
  using namespace reco;

  bool gen_result = true;

  edm::LogVerbatim("MCTruthEvent") << " Start  " << std::endl;

  std::ostringstream dbg;

  //get pthat of process
  d_Pthat = -999.;
  
  Handle<double> genEventScale;
  ev.getByLabel( "genEventScale", genEventScale );
  if ( genEventScale.isValid() ) d_Pthat = *genEventScale;

  //gen particle collection
  Handle<reco::GenParticleCollection>  genParticles;
  ev.getByLabel(genParticleTag_, genParticles);   
  
  int count=0;
  int partcount=0;

  if (debug_>1) edm::LogVerbatim("MCTruthEvent") << logmessage<< std::endl;
  
  maintenance(genParticles->size());
  
  for( size_t i = 0; i < genParticles->size(); ++ i ) {
    const reco::Candidate& pCand = (*genParticles)[ i ];
    
    int st = pCand.status();  
    
    //get status 3 particles
    if (st==3) {
      v_genP4.push_back(pCand.p4());
      vi_genIds.push_back(pCand.pdgId());
      vi_genStatus.push_back(pCand.status());
      vi_genDaughters.push_back(pCand.numberOfDaughters());
      
      if (pCand.numberOfMothers() > 0 ) { 
	const reco::Candidate * mom = pCand.mother();
	//why do we reset mom if pdgid is the same?
	//while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	
	for( size_t j = 0; j < i; ++ j ) {
	  const Candidate * ref = &((*genParticles)[j]);
	  //if (ref == mom) { vi_genRefs.push_back(ref->pdgId()); } //return mother's pdgId
	  if (ref == mom) { vi_genRefs.push_back(j); } //point to particle that is reference
	}  
      } else { vi_genRefs.push_back(-999);}
      
      if (debug_>1)  edm::LogVerbatim("MCTruthEvent") << logmessage<<std::endl;
      ++count;
    }
    else { // store also electrons or muons or taus or neutrinos  or photons of status 1 
      if ( ((abs(pCand.pdgId()) > 10) && (abs(pCand.pdgId()) < 19)) || (abs(pCand.pdgId()) == 22) ) {
	
	v_genParticleP4        .push_back(pCand.p4());
	vi_genParticleIds      .push_back(pCand.pdgId());
	vi_genParticleStatus   .push_back(pCand.status());
	vi_genParticleDaughters.push_back(pCand.numberOfDaughters());
	
	if (pCand.numberOfMothers() > 0 ) { 
	  const reco::Candidate * mom = pCand.mother();
	  //why do we reset mom if pdgid is the same?
	  //while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
	  
	  for( size_t j = 0; j < i; ++ j ) {
	    const reco::Candidate * ref = &((*genParticles)[j]);
	    //if (ref == mom) { vi_genParticleRefs.push_back(ref->pdgId()); }
	    if (ref == mom) { vi_genParticleRefs.push_back(j); }
	  }  
	} else { vi_genParticleRefs.push_back(-999);}
	
	if (debug_>1)  edm::LogVerbatim("MCTruthEvent")<<logmessage<<std::endl;
	++partcount;
      }
    }
  }
  i_genLength = count;
  i_genParticleLength = partcount;
  
  //mMCTruthData->Fill();
  if (debug_)
    std::cout<<"Done analyzing gen particles"<<std::endl;
  return gen_result;
  }

//________________________________________________________________________________________
void MCTruthAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Add the branches
  
  //generator leptons (electrons and muons and taus
  mMCTruthData->Branch("genP4",           &v_genP4);
  mMCTruthData->Branch("genN",            &i_genLength,        "genN/I");
  mMCTruthData->Branch("genId",           &vi_genIds);
  mMCTruthData->Branch("genStatus",       &vi_genStatus);
  mMCTruthData->Branch("genMother",       &vi_genRefs);
  mMCTruthData->Branch("genDaughters",    &vi_genDaughters);
  
  //generator leptons status (electrons and muons and taus
  mMCTruthData->Branch("genParticleP4",           &v_genParticleP4);
  mMCTruthData->Branch("genParticleN",            &i_genParticleLength, "genParticleN/I");
  mMCTruthData->Branch("genParticleId",           &vi_genParticleIds);
  mMCTruthData->Branch("genParticleStatus",       &vi_genParticleStatus);
  mMCTruthData->Branch("genParticleMother",       &vi_genParticleRefs);
  mMCTruthData->Branch("genParticleDaughters",    &vi_genParticleDaughters);
  
  mMCTruthData->Branch("pthat", &d_Pthat, "pthat/D");
  
  edm::LogInfo("MCTruthEvent") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(MCTruthAnalyzerPAT);

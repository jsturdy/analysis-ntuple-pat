
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
// $Id: MCTruthAnalyzerPAT.cc,v 1.4 2011/03/15 14:55:52 sturdy Exp $
//
//


#include "JSturdy/AnalysisNtuplePAT/interface/MCTruthAnalyzerPAT.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
#include <TMath.h>
#include <sstream>



MCTruthAnalyzerPAT::MCTruthAnalyzerPAT(const edm::ParameterSet& genParams, TTree* mMCTruthData)
  :
  v_genP4        (new std::vector<reco::Candidate::LorentzVector> ),
  v_genParticleP4(new std::vector<reco::Candidate::LorentzVector> ),

  vi_genIds      (new std::vector<int> ),
  vi_genRefs     (new std::vector<int> ),
  vi_genStatus   (new std::vector<int> ),
  vi_genDaughters(new std::vector<int> ),
  
  vi_genParticleIds      (new std::vector<int> ),
  vi_genParticleRefs     (new std::vector<int> ),
  vi_genParticleStatus   (new std::vector<int> ),
  vi_genParticleDaughters(new std::vector<int> )

{ 

  genParticleTag_ = genParams.getUntrackedParameter<edm::InputTag>("genParticleTag");
  debug_          = genParams.getUntrackedParameter<int>("debugTruth",0);
 
  // Initialise ntuple branches
  bookTTree(mMCTruthData);

}


//________________________________________________________________________________________
MCTruthAnalyzerPAT::~MCTruthAnalyzerPAT() 
{
  
}

//
//________________________________________________________________________________________
void MCTruthAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
  d_xs            = -999.;
  d_xsLO          = -999.;
  d_xsLOerr       = -999.;
  d_xsNLO         = -999.;
  d_xsNLOerr      = -999.;
  d_filterEff     = -999.;
  d_xsInternal    = -999.;
  d_xsInternalerr = -999.;
  
  edm::Handle<GenRunInfoProduct> genRunInfo;
  run.getByType( genRunInfo );
  //  run.getByLabel( "generator", genRunInfo );
  if ( genRunInfo.isValid() ){
    d_xs = genRunInfo->crossSection();
    
    d_xsLO     = genRunInfo->externalXSecLO().value();
    d_xsLOerr  = genRunInfo->externalXSecLO().error();
    d_xsNLO    = genRunInfo->externalXSecNLO().value();
    d_xsNLOerr = genRunInfo->externalXSecNLO().error();
    
    d_filterEff  = genRunInfo->filterEfficiency();
    
    d_xsInternal     = genRunInfo->internalXSec().value();
    d_xsInternalerr  = genRunInfo->internalXSec().error();
  }
}

//________________________________________________________________________________________
void MCTruthAnalyzerPAT::endRun(const edm::Run& run, const edm::EventSetup&es)
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

  maintenance();

  //get pthat of process
  d_pThat = -999.;
  
  //Handle<double> genEventScale;
  //ev.getByLabel( "genEventScale", genEventScale );
  //if ( genEventScale.isValid() )
  //  d_pThat = *genEventScale;

  d_weight   = -999.;
  d_alphaQCD = -999.;
  d_alphaQED = -999.;
  d_qScale   = -999.;
  d_scalePDF = -999.;
  d_x1       = -999.;
  d_x2       = -999.;
  d_x1PDF    = -999.;
  d_x2PDF    = -999.;

  Handle<GenEventInfoProduct> genEventInfo;
  ev.getByType( genEventInfo );
  if ( genEventInfo.isValid() ) {
    d_pThat = (genEventInfo->hasBinningValues()) ? (genEventInfo->binningValues())[0] : 0.0;
    
    d_weight = genEventInfo->weight();
    d_alphaQCD = genEventInfo->alphaQCD();
    d_alphaQED = genEventInfo->alphaQED();

    d_qScale = genEventInfo->qScale();
    d_scalePDF = genEventInfo->pdf()->scalePDF;
    d_x1 = genEventInfo->pdf()->x.first;
    d_x2 = genEventInfo->pdf()->x.second;
    d_x1PDF = genEventInfo->pdf()->xPDF.first;
    d_x2PDF = genEventInfo->pdf()->xPDF.second;

  }
  //gen particle collection
  Handle<reco::GenParticleCollection>  genParticles;
  ev.getByLabel(genParticleTag_, genParticles);   
  
  int count=0;
  int partcount=0;

  //Store only 250 max gen particles?
  unsigned int numParticles = genParticles->size();
  if (numParticles > 500)
    numParticles = 500;

  for( size_t i = 0; i < numParticles; ++ i ) {
    const reco::Candidate& pCand = (*genParticles)[ i ];
    
    int st = pCand.status();  
    
    //get status 3 particles
    if (st==3) {
      v_genP4->push_back(pCand.p4());
      vi_genIds->push_back(pCand.pdgId());
      vi_genStatus->push_back(pCand.status());
      vi_genDaughters->push_back(pCand.numberOfDaughters());
      
      if (pCand.numberOfMothers() > 0 ) { 
	const reco::Candidate * mom = pCand.mother();
	//why do we reset mom if pdgid is the same?
	//while (mom->pdgId() == pCand.pdgId()) {mom = mom->mother(); }
	
	for( size_t j = 0; j < i; ++ j ) {
	  const Candidate * ref = &((*genParticles)[j]);
	  //if (ref == mom) { vi_genRefs->push_back(ref->pdgId()); } //return mother's pdgId
	  if (ref == mom) { vi_genRefs->push_back(j); } //point to particle that is reference
	}  
      } else { vi_genRefs->push_back(-999);}
      
      ++count;
    }
    //else { // store also electrons or muons or taus or neutrinos  or photons of status 1 
    //if ( ((abs(pCand.pdgId()) > 10) && (abs(pCand.pdgId()) < 19)) || (abs(pCand.pdgId()) == 22) ) {
    
    v_genParticleP4        ->push_back(pCand.p4());
    vi_genParticleIds      ->push_back(pCand.pdgId());
    vi_genParticleStatus   ->push_back(pCand.status());
    vi_genParticleDaughters->push_back(pCand.numberOfDaughters());
    
    if (pCand.numberOfMothers() > 0 ) { 
      const reco::Candidate * mom = pCand.mother();
      //why do we reset mom if pdgid is the same?
      //while (mom->pdgId() == pCand.pdgId()) { mom = mom->mother(); }
      
      for( size_t j = 0; j < i; ++ j ) {
	const reco::Candidate * ref = &((*genParticles)[j]);
	//if (ref == mom) { vi_genParticleRefs->push_back(ref->pdgId()); }
	if (ref == mom) { vi_genParticleRefs->push_back(j); }
      }
    } else { vi_genParticleRefs->push_back(-999);}
    
    ++partcount;
    //}
    //}
  }
  i_genLength = count;
  i_genParticleLength = partcount;
  
  //mMCTruthData->Fill();
  if (debug_)
    std::cout<<"Done analyzing gen particles"<<std::endl;
  return gen_result;
  }

//________________________________________________________________________________________
void MCTruthAnalyzerPAT::bookTTree(TTree* mMCTruthData) {

  //Add the branches
  
  //generator leptons (electrons and muons and taus
  mMCTruthData->Branch("genP4",           &(*v_genP4.get() ) );
  mMCTruthData->Branch("genN",            &i_genLength,        "genN/I");
  mMCTruthData->Branch("genId",           &(*vi_genIds.get() ) );
  mMCTruthData->Branch("genStatus",       &(*vi_genStatus.get() ) );
  mMCTruthData->Branch("genMother",       &(*vi_genRefs.get() ) );
  mMCTruthData->Branch("genDaughters",    &(*vi_genDaughters.get() ) );
  
  //generator leptons status (electrons and muons and taus
  mMCTruthData->Branch("genParticleP4",           &(*v_genParticleP4.get() ) );
  mMCTruthData->Branch("genParticleN",            &i_genParticleLength, "genParticleN/I");
  mMCTruthData->Branch("genParticleId",           &(*vi_genParticleIds.get() ) );
  mMCTruthData->Branch("genParticleStatus",       &(*vi_genParticleStatus.get() ) );
  mMCTruthData->Branch("genParticleMother",       &(*vi_genParticleRefs.get() ) );
  mMCTruthData->Branch("genParticleDaughters",    &(*vi_genParticleDaughters.get() ) );
  
  mMCTruthData->Branch("pthat", &d_pThat, "pthat/D");

  mMCTruthData->Branch("samp_xsLO"         , &d_xsLO         , "samp_xsLO/D"         );
  mMCTruthData->Branch("samp_xsLOerr"      , &d_xsLOerr      , "samp_xsLOerr/D"      );
  mMCTruthData->Branch("samp_xsNLO"        , &d_xsNLO        , "samp_xsNLO/D"        );
  mMCTruthData->Branch("samp_xsNLOerr"     , &d_xsNLOerr     , "samp_xsNLOerr/D"     );
  mMCTruthData->Branch("samp_xsInternal"   , &d_xsInternal   , "samp_xsInternal/D"   );
  mMCTruthData->Branch("samp_xsInternalerr", &d_xsInternalerr, "samp_xsInternalerr/D");
  mMCTruthData->Branch("samp_xs"           , &d_xs           , "samp_xs/D"           );
  mMCTruthData->Branch("samp_filterEff"    , &d_filterEff    , "samp_filterEff/D"    );

  mMCTruthData->Branch("proc_weight",   &d_weight,   "proc_weight/D"  );
  mMCTruthData->Branch("proc_alphaQCD", &d_alphaQCD, "proc_alphaQCD/D");
  mMCTruthData->Branch("proc_alphaQED", &d_alphaQED, "proc_alphaQED/D");
  mMCTruthData->Branch("proc_qScale",   &d_qScale,   "proc_qScale/D"  );
  mMCTruthData->Branch("proc_scalePDF", &d_scalePDF, "proc_scalePDF/D");
  mMCTruthData->Branch("proc_x1",       &d_x1,       "proc_x1/D"      );
  mMCTruthData->Branch("proc_x2",       &d_x2,       "proc_x2/D"      );
  mMCTruthData->Branch("proc_x1PDF",    &d_x1PDF,    "proc_x1PDF/D"   );
  mMCTruthData->Branch("proc_x2PDF",    &d_x2PDF,    "proc_x2PDF/D"   );
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//
//DEFINE_EDM_PLUGIN(MCTruthAnalyzerPAT);

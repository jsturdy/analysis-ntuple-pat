
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      AnalysisNtuplePAT
// 
/**\class AnalysisNtuplePAT AnalysisNtuplePAT.cc JSturdy/AnalysisNtuplePAT/src/AnalysisNtuplePAT.cc

Description: Variable collector/ntupler for SUSY search with Jets + MET

Implementation:Uses the EventSelector interface for event selection and TFileService for plotting.

*/
//
// Original Author:  Markus Stoye, (modified by Jared Sturdy from SusyAnalysisNtuplePAT)
//         Created:  Mon Feb 18 15:40:44 CET 2008
// $Id: AnalysisNtuplePAT.cc,v 1.18 2011/03/18 10:58:50 sturdy Exp $
//
//
#include "JSturdy/AnalysisNtuplePAT/interface/AnalysisNtuplePAT.h"

#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
AnalysisNtuplePAT::AnalysisNtuplePAT(const edm::ParameterSet& pset)
{ 

  //default parameters
  debug_     = pset.getUntrackedParameter<int>("debugDiJets",0);
  doMCTruth_ = pset.getUntrackedParameter<bool>("doMCTruth",false);
 

  // Initialise plots [should improve in the future]
  initPlots();
    
  calojetinfo   = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("caloJetParameters"),   mJetData);
  //jptjetinfo    = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("jptJetParameters"),    mJetData);
  pf2patjetinfo = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pf2patJetParameters"), mJetData);
  
  //MET information
  //calometinfo       = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("calometParameters"),       mMETData);
  calomettypeiiinfo = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("calometTypeIIParameters"), mMETData);
  //pfmetinfo         = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfmetParameters"),         mMETData);
  pfmettypeiinfo    = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfmetTypeIParameters"),    mMETData);
  //tcmetinfo         = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("tcmetParameters"),         mMETData);

  //Photon information
  photons   = new PhotonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("photonParameters"), mPhotonData);
  //pfphotons = new PhotonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfphotonParameters"), mPhotonData);

  //Lepton information
  leptons   = new LeptonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("leptonParameters"),   mLeptonData);
  pfleptons = new LeptonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfleptonParameters"), mLeptonData);
  
  //Vertex information
  vertex   = new VertexAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("vertexParameters"),   mVertexData);
  
  //Track information
  //tracks   = new TrackAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("trackParameters"),     mTrackData);
  //Trigger information
  triggers = new TriggerAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("triggerParameters"), mTriggerData);
  
  //heminfo  = new HemisphereAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("hemisphereParameters"), mAllData));
  
  //MC truth  information
  if (doMCTruth_)
    geninfo  = new MCTruthAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("mcTruthParameters"), mGenParticleData);
  
  nEvents_ = 0;

}


//________________________________________________________________________________________
AnalysisNtuplePAT::~AnalysisNtuplePAT() {

  delete mEventData;
  delete mAllData;
  delete mLeptonData;
  delete mJetData;
  delete mMETData;
  delete mPhotonData;
  delete mTriggerData;
  delete mVertexData;

  mEventData       = 0;
  mAllData         = 0;
  mLeptonData      = 0;
  mJetData         = 0;
  mMETData         = 0;
  mPhotonData      = 0;
  mTriggerData     = 0;
  mVertexData      = 0;

  if (doMCTruth_) {
    delete mGenParticleData;
    mGenParticleData = 0;
  }

  delete calojetinfo;
  //delete jptjetinfo;
  delete pf2patjetinfo;
  //delete calometinfo;
  delete calomettypeiiinfo;
  //delete pfmetinfo;
  delete pfmettypeiinfo;
  //delete tcmetinfo;
  delete photons;
  delete leptons;
  delete pfleptons;
  delete vertex;
  delete triggers;

  calojetinfo   = 0;
  //jptjetinfo    = 0;
  pf2patjetinfo = 0;
  //calometinfo       = 0;
  calomettypeiiinfo = 0;
  //pfmetinfo      = 0;
  pfmettypeiinfo = 0;
  //tcmetinfo = 0;
  photons   = 0;
  leptons   = 0;
  pfleptons = 0;
  vertex    = 0;
  triggers  = 0;


  if (doMCTruth_) {
    delete geninfo;
    geninfo = 0;
  }

}


//________________________________________________________________________________________
// Method called to for each event
void
AnalysisNtuplePAT::analyze(const edm::Event& ev, const edm::EventSetup& sp)
{
  using namespace reco;
  using namespace edm;

  edm::LogVerbatim("AnalysisNtuplePAT") << " Start  " << std::endl;

  std::ostringstream dbg;

  //////////////////////////////////
  //       Event Auxiliary        //
  //////////////////////////////////

  m_Run           = ev.id().run();
  m_Event         = ev.id().event();
  m_OrbitN        = ev.orbitNumber();
  m_StoreN        = ev.eventAuxiliary().storeNumber();
  m_LumiSection   = ev.luminosityBlock();
  m_BunchCrossing = ev.bunchCrossing();

  m_IsData        = ev.isRealData();


  //////////////////////////////////
  //   SUSY scan Information      
  //   Thanks Arun!
  //////////////////////////////////

  edm::Handle<double> susyScanA0_H;
  edm::Handle<double> susyScanCrossSection_H;
  edm::Handle<double> susyScanM0_H;
  edm::Handle<double> susyScanM12_H;
  edm::Handle<double> susyScanMu_H;
  edm::Handle<double> susyScanRun_H;
  edm::Handle<double> susyScantanbeta_H;
  ev.getByLabel("susyScanA0",           susyScanA0_H);
  ev.getByLabel("susyScanCrossSection", susyScanCrossSection_H);
  ev.getByLabel("susyScanM0",           susyScanM0_H);
  ev.getByLabel("susyScanM12",          susyScanM12_H);
  ev.getByLabel("susyScanMu",           susyScanMu_H);
  ev.getByLabel("susyScanRun",          susyScanRun_H);
  ev.getByLabel("susyScantanbeta",      susyScantanbeta_H);

  if (susyScanA0_H.isValid()
      && susyScanCrossSection_H.isValid()
      && susyScanM0_H.isValid()
      && susyScanM12_H.isValid()
      && susyScanMu_H.isValid()
      && susyScanRun_H.isValid()
      && susyScantanbeta_H.isValid() ) {
    m_susyScanA0      = *susyScanA0_H;
    m_susyScanCrossSection = *susyScanCrossSection_H;
    m_susyScanM0      = *susyScanM0_H;
    m_susyScanM12     = *susyScanM12_H;
    m_susyScanMu      = *susyScanMu_H;
    m_susyScanRun     = *susyScanRun_H;
    m_susyScantanbeta = *susyScantanbeta_H;
  } 
  else {
    m_susyScanA0      = 100000.;
    m_susyScanCrossSection = -1.;
    m_susyScanM0      = -1.;
    m_susyScanM12     = -1.;
    m_susyScanMu      = 0.;
    m_susyScanRun     = -1;
    m_susyScantanbeta = -1.;
  }


  
  //Run filters

  if (debug_) 
    std::cout<<"Getting the calo jet result"<<std::endl;
  bool mycalojetresult  = calojetinfo->filter(ev, sp);
  //if (debug_) 
  //  std::cout<<"Getting the jpt jet result"<<std::endl;
  //bool myjptjetresult   = jptjetinfo->filter(ev, sp);
  if (debug_) 
    std::cout<<"Getting the pf2pat jet result"<<std::endl;
  bool mypf2patjetresult    = pf2patjetinfo->filter(ev, sp);
  

  if (debug_) 
    std::cout<<"Getting the calo met result"<<std::endl;
  //bool mycalometresult          = calometinfo->filter(ev, sp);
  bool mycalomettypeiiresult    = calomettypeiiinfo->filter(ev, sp);
  
  //
  if (debug_) 
    std::cout<<"Getting the pf met result"<<std::endl;
  //bool mypfmetresult      = pfmetinfo->filter(ev, sp);
  bool mypfmettypeiresult = pfmettypeiinfo->filter(ev, sp);

  
  //if (debug_) 
  //  std::cout<<"Getting the tc met result"<<std::endl;
  //bool mytcmetresult      = tcmetinfo->filter(ev, sp);

  
  if (debug_) 
    std::cout<<"Getting the reco photon result"<<std::endl;
  bool myphotonresult   = photons->filter(ev, sp);

  if (debug_) 
    std::cout<<"Getting the reco lepton result"<<std::endl;
  bool myleptonresult   = leptons->filter(ev, sp);

  
  if (debug_)
    std::cout<<"Getting the pf lepton result"<<std::endl;
  bool mypfleptonresult = pfleptons->filter(ev, sp);
  
  
  if (debug_) 
    std::cout<<"Getting the vertex result"<<std::endl;
  bool myvertexresult  = vertex->filter(ev, sp);
  
  if (debug_) 
    std::cout<<"Getting the track result"<<std::endl;
  bool mytriggerresult = triggers->filter(ev, sp);
  
  if (doMCTruth_) {
    if (debug_) 
      std::cout<<"Getting the mc truth result"<<std::endl;
    bool mymctruth = geninfo->filter(ev, sp);
  }
  
  ++nEvents_;

  
  if (mAllData)
    mAllData->Fill();
  if (mJetData)
    mJetData->Fill();
  if (mMETData)
    mMETData->Fill();
  if (mPhotonData)
    mPhotonData->Fill();
  if (mLeptonData)
    mLeptonData->Fill();
  if (mVertexData)
    mVertexData->Fill();
  if (mTriggerData)
    mTriggerData->Fill();
  
  if (doMCTruth_)
    if (mGenParticleData)
      mGenParticleData->Fill();
  //}
}

//________________________________________________________________________________________
void AnalysisNtuplePAT::beginRun(const edm::Run& run, const edm::EventSetup&es) {
  
  calojetinfo      ->beginRun(run, es);
  //jptjetinfo       ->beginRun(run, es);
  pf2patjetinfo    ->beginRun(run, es);
  
  //calometinfo      ->beginRun(run, es);
  calomettypeiiinfo->beginRun(run, es);
  //pfmetinfo        ->beginRun(run, es);
  pfmettypeiinfo   ->beginRun(run, es);
  //tcmetinfo        ->beginRun(run, es);

  photons          ->beginRun(run, es);
  //pfphotons        ->beginRun(run, es);

  leptons          ->beginRun(run, es);
  pfleptons        ->beginRun(run, es);

  vertex           ->beginRun(run, es);
  triggers         ->beginRun(run, es);
  geninfo          ->beginRun(run, es);

}

//________________________________________________________________________________________
void AnalysisNtuplePAT::beginJob() {
  nEvents_ = 0;
  //setup job before events
}

//________________________________________________________________________________________
void AnalysisNtuplePAT::endJob() {
  mEventData->Fill();
  //cleanup after all events
  //printSummary();
}

//________________________________________________________________________________________
void
AnalysisNtuplePAT::initPlots() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";
  
  // Register this ntuple
  edm::Service<TFileService> fs;
  mEventData = fs->make<TTree>( "EventData", "data after preselection" );
  mEventData->Branch("IsData",        &m_IsData,        "IsData/O");
  mEventData->Branch("TotalEvents",   &nEvents_,        "TotalEvents/I");

  mEventData->SetAutoSave(1);

  mAllData = fs->make<TTree>( "AllData", "data after preselection" );
  mAllData->SetAutoSave(10);

  mAllData->Branch("Run",           &m_Run,           "Run/I");
  mAllData->Branch("Event",         &m_Event,         "Event/I");
  mAllData->Branch("OrbitN",        &m_OrbitN,        "OrbitN/I");
  mAllData->Branch("StoreN",        &m_StoreN,        "StoreN/I");
  mAllData->Branch("LumiSection",   &m_LumiSection,   "LumiSection/I");
  mAllData->Branch("BunchCrossing", &m_BunchCrossing, "BunchCrossing/I");

  mAllData->Branch("susyScanA0",              &m_susyScanA0           ,        "m_susyScanA0/D"          );
  mAllData->Branch("susyScanCrossSection",    &m_susyScanCrossSection ,        "m_susyScanCrossSection/D");
  mAllData->Branch("susyScanM0",              &m_susyScanM0           ,        "m_susyScanM0/D"          );
  mAllData->Branch("susyScanM12",             &m_susyScanM12          ,        "m_susyScanM12/D"         );
  mAllData->Branch("susyScanMu",              &m_susyScanMu           ,        "m_susyScanMu/D"          );
  mAllData->Branch("susyScanRun",             &m_susyScanRun          ,        "m_susyScanRun/D"         );
  mAllData->Branch("susyScantanbeta",         &m_susyScantanbeta      ,        "m_susyScantanbeta/D"     );


  mJetData = fs->make<TTree>( "JetData", "Jet variables" );
  mJetData->SetAutoSave(250);
  
  mMETData = fs->make<TTree>( "METData", "MET variables" );
  mMETData->SetAutoSave(250);
  
  mLeptonData = fs->make<TTree>( "LeptonData", "Lepton variables" );
  mLeptonData->SetAutoSave(250);
  
  mPhotonData = fs->make<TTree>( "PhotonData", "Photon variables" );
  mPhotonData->SetAutoSave(250);
  
  mVertexData = fs->make<TTree>( "VertexData", "Vertex and beamspot variables" );
  mVertexData->SetAutoSave(250);
  
  //mTrackData = fs->make<TTree>( "TrackData", "Track variables" );
  //mTrackData->SetAutoSave(250);
  
  mTriggerData = fs->make<TTree>( "TriggerData", "Trigger variables" );
  mTriggerData->SetAutoSave(250);
  
  if (doMCTruth_) {
    mGenParticleData = fs->make<TTree>( "GenParticleData", "GenParticle variables" );
    mGenParticleData->SetAutoSave(250);
  }
    
  edm::LogInfo("AnalysisNtuplePAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________

// Define this as a plug-in

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(AnalysisNtuplePAT);

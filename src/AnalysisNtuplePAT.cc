
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
// $Id: AnalysisNtuplePAT.cc,v 1.14 2011/03/07 19:01:28 sturdy Exp $
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
    
  calojetinfo   = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("caloJetParameters"), mAllData);
  jptjetinfo    = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("jptJetParameters"), mAllData);
  pfjetinfo     = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfJetParameters"), mAllData);
  pf2patjetinfo = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pf2patJetParameters"), mAllData);
  //trackjetinfo  = new JetAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("trackJetParameters"), mAllData);

  //MET information
  calometinfo       = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("calometParameters"), mAllData);
  calomettypeiiinfo = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("calometTypeIIParameters"), mAllData);

  pfmetinfo      = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfmetParameters"), mAllData);
  pfmettypeiinfo = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfmetTypeIParameters"), mAllData);

  tcmetinfo      = new METAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("tcmetParameters"), mAllData);

  //Photon information
  photons   = new PhotonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("photonParameters"), mAllData);
  //pfphotons = new PhotonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfphotonParameters"), mAllData);

  //Lepton information
  leptons   = new LeptonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("leptonParameters"), mAllData);
  pfleptons = new LeptonAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("pfleptonParameters"), mAllData);

  //Vertex information
  vertex   = new VertexAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("vertexParameters"), mAllData);

  //Track information
  tracks   = new TrackAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("trackParameters"), mAllData);

  //Trigger information
  triggers = new TriggerAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("triggerParameters"), mAllData);
  //heminfo  = new HemisphereAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("hemisphereParameters"), mAllData));

  //MC truth  information
  if (doMCTruth_)
    geninfo  = new MCTruthAnalyzerPAT(pset.getUntrackedParameter<edm::ParameterSet>("mcTruthParameters"), mAllData);

  //Setup counters for filters
  passCaloJets[0]    = 0;
  passJPTJets[0]     = 0;
  passPFJets[0]      = 0;
  passPF2PATJets[0]  = 0;
  //passTrackJets[0]   = 0;
  passCaloMET[0]     = 0;
  passCaloTypeIIMET[0] = 0;
  passPFMET[0]         = 0;
  passPFTypeIMET[0]    = 0;
  passTCMET[0]       = 0;
  passLeptons[0]     = 0;
  passPFLeptons[0]   = 0;
  passPhotons[0]     = 0;
  //passPFPhotons[0]   = 0;
  passVertex[0]      = 0;
  passTracks[0]      = 0;
  passTriggers[0]    = 0;
  //passHemispheres[0] = 0;
  passCaloJets[1]    = 0;
  passJPTJets[1]     = 0;
  passPFJets[1]      = 0;
  passPF2PATJets[1]  = 0;
  //passTrackJets[1]   = 0;
  passCaloMET[1]     = 0;
  passCaloTypeIIMET[1] = 0;
  passPFMET[1]         = 0;
  passPFTypeIMET[1]    = 0;
  passTCMET[1]       = 0;
  passLeptons[1]     = 0;
  passPFLeptons[1]   = 0;
  passPhotons[1]     = 0;
  //passPFPhotons[1]   = 0;
  passVertex[1]      = 0;
  passTracks[1]      = 0;
  passTriggers[1]    = 0;
  //passHemispheres[1] = 0;

  nEvents_ = 0;

}


//________________________________________________________________________________________
AnalysisNtuplePAT::~AnalysisNtuplePAT() {}


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

  //Run filters

  if (debug_) 
    std::cout<<"Getting the calo jet result"<<std::endl;
  bool mycalojetresult  = calojetinfo->filter(ev, sp);
  if (debug_) 
    std::cout<<"Getting the jpt jet result"<<std::endl;
  bool myjptjetresult   = jptjetinfo->filter(ev, sp);
  if (debug_) 
    std::cout<<"Getting the pf jet result"<<std::endl;
  bool mypfjetresult    = pfjetinfo->filter(ev, sp);
  if (debug_) 
    std::cout<<"Getting the pf2pat jet result"<<std::endl;
  bool mypf2patjetresult    = pf2patjetinfo->filter(ev, sp);
  //if (debug_)
  //  std::cout<<"Getting the track jet result"<<std::endl;
  //bool mytrackjetresult = trackjetinfo->filter(ev, sp);

  if (debug_) 
    std::cout<<"Getting the calo met result"<<std::endl;
  bool mycalometresult          = calometinfo->filter(ev, sp);
  bool mycalomettypeiiresult    = calomettypeiiinfo->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the pf met result"<<std::endl;
  bool mypfmetresult      = pfmetinfo->filter(ev, sp);
  bool mypfmettypeiresult = pfmettypeiinfo->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the tc met result"<<std::endl;
  bool mytcmetresult      = tcmetinfo->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the reco photon result"<<std::endl;
  bool myphotonresult   = photons->filter(ev, sp);

  //
  //if (debug_)
  //  std::cout<<"Getting the pf photon result"<<std::endl;
  //bool mypfphotonresult = pfphotons->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the reco lepton result"<<std::endl;
  bool myleptonresult   = leptons->filter(ev, sp);

  //
  if (debug_)
    std::cout<<"Getting the pf lepton result"<<std::endl;
  bool mypfleptonresult = pfleptons->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the vertex result"<<std::endl;
  bool myvertexresult  = vertex->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the track result"<<std::endl;
  bool mytrackresult   = tracks->filter(ev, sp);

  //
  if (debug_) 
    std::cout<<"Getting the track result"<<std::endl;
  bool mytriggerresult = triggers->filter(ev, sp);
  //bool myhemresult     = heminfo->filter(ev, sp);

  //
  if (doMCTruth_) {
    if (debug_) 
      std::cout<<"Getting the mc truth result"<<std::endl;
    bool mymctruth = geninfo->filter(ev, sp);
  }
  
  if (mycalojetresult)   ++passCaloJets[0];
  if (myjptjetresult)    ++passJPTJets[0];
  if (mypfjetresult)     ++passPFJets[0];
  if (mypf2patjetresult) ++passPF2PATJets[0];
  //if (mytrackjetresult)  ++passTrackJets[0];

  if (mycalometresult)       ++passCaloMET[0];
  if (mycalomettypeiiresult) ++passCaloTypeIIMET[0];
  if (mypfmetresult)         ++passPFMET[0];
  if (mypfmettypeiresult)    ++passPFTypeIMET[0];
  if (mytcmetresult)         ++passTCMET[0];

  if (myleptonresult)   ++passLeptons[0];
  if (mypfleptonresult) ++passPFLeptons[0];

  if (myphotonresult)   ++passPhotons[0];
  //if (mypfphotonresult) ++passPFPhotons[0];

  if (myvertexresult)  ++passVertex[0];
  if (mytrackresult)   ++passTracks[0];
  if (mytriggerresult) ++passTriggers[0];
  //if (myhemresult)   ++passHemispheres[0];

  //if ( mymetresult && myleptonresult && myphotonresult
  //  && myvertexresult && mytrackresult && mytriggerresult ) ++passJets[1];
  //if ( myjetresult && myleptonresult && myphotonresult
  //  && myvertexresult && mytrackresult && mytriggerresult ) ++passMET[1];
  //if ( myjetresult && mymetresult && myphotonresult
  //  && myvertexresult && mytrackresult && mytriggerresult ) ++passLeptons[1];
  //if ( myjetresult && mymetresult && myleptonresult
  //  && myvertexresult && mytrackresult && mytriggerresult ) ++passPhotons[1];
  //if ( myjetresult && mymetresult && myleptonresult && myphotonresult
  //   && mytrackresult && mytriggerresult )                  ++passVertex[1];
  //if ( myjetresult && mymetresult && myleptonresult && myphotonresult
  //  && myvertexresult && mytriggerresult )                  ++passTracks[1];
  //if ( myjetresult && mymetresult && myleptonresult && myphotonresult
  //  && myvertexresult && mytrackresult )                    ++passTriggers[1];
  ////if ( myjetresult && mymetresult && myleptonresult && myphotonresult) \
  ////&&(myvertexresult && mytrackresult && mytriggerresult ) ++passHemispheres[1];
  
  ++nEvents_;

  
  mAllData->Fill();
  //}
}

//________________________________________________________________________________________
void 
AnalysisNtuplePAT::beginRun(const edm::Run& run, const edm::EventSetup&es) {
  
  calojetinfo      ->beginRun(run, es);
  jptjetinfo       ->beginRun(run, es);
  pfjetinfo        ->beginRun(run, es);
  pf2patjetinfo    ->beginRun(run, es);
  //trackjetinfo     ->beginRun(run, es);
  calometinfo      ->beginRun(run, es);
  calomettypeiiinfo->beginRun(run, es);
  pfmetinfo        ->beginRun(run, es);
  pfmettypeiinfo   ->beginRun(run, es);
  tcmetinfo        ->beginRun(run, es);
  photons          ->beginRun(run, es);
  //pfphotons        ->beginRun(run, es);
  leptons          ->beginRun(run, es);
  pfleptons        ->beginRun(run, es);
  vertex           ->beginRun(run, es);
  tracks           ->beginRun(run, es);
  triggers         ->beginRun(run, es);
  geninfo          ->beginRun(run, es);

}

//________________________________________________________________________________________
void 
AnalysisNtuplePAT::beginJob() {
  //setup job before events
}

//________________________________________________________________________________________
void 
AnalysisNtuplePAT::endJob() {
  //cleanup after all events
  //printSummary();
}

void
AnalysisNtuplePAT::printSummary( void ) {
  printf("============================Summary of DiJetAnalyzerPAT============================\n");
  printf("= Total number of events filtered:     %2d                                     =\n",nEvents_);
  printf("============================Jet results============================================\n");
  printf("= Events passing the calojet filter:        %2d                                =\n",passCaloJets[0]);
  printf("= Events passing the jptjet filter:         %2d                                =\n",passJPTJets[0]);
  printf("= Events passing the pfjet filter:          %2d                                =\n",passPFJets[0]);
  //printf("= Events passing the trackjet filter:       %2d                                =\n",passTrackJets[0]);
  printf("============================MET results============================================\n");
  printf("= Events passing the CaloMET filter:        %2d                                =\n",passCaloMET[0]);
  printf("= Events passing the PFMET filter:          %2d                                =\n",passPFMET[0]);
  printf("= Events passing the TCMET filter:          %2d                                =\n",passTCMET[0]);
  printf("============================Lepton results=========================================\n");
  printf("= Events passing the lepton veto:           %2d                                =\n",passLeptons[0]);
  printf("= Events passing the pflepton veto:         %2d                                =\n",passPFLeptons[0]);
  printf("============================Photon results=========================================\n");
  printf("= Events passing the photon veto:           %2d                                =\n",passPhotons[0]);
  //printf("= Events passing the pfphoton veto:         %2d                                =\n",passPFPhotons[0]);
  printf("============================Vertex results=========================================\n");
  printf("= Events passing the vertex filter:         %2d                                =\n",passVertex[0]);
  printf("============================Track results==========================================\n");
  printf("= Events passing the track filter:          %2d                                =\n",passTracks[0]);
  printf("============================Trigger results========================================\n");
  printf("= Events passing the trigger filter:        %2d                                =\n",passTriggers[0]);
  //printf("= Events passing the hemisphere filter:%2d                                     =\n",passHemispheres[0]);
  printf("=                                                                              =\n");
  printf("=                                                                              =\n");
  printf("=                                                                              =\n");
  printf("=                                                                              =\n");
  printf("=                                                                              =\n");
  printf("= Events passing all but the calojet filter:        %2d                        =\n",passCaloJets[1]);
  printf("= Events passing all but the jptjet filter:         %2d                        =\n",passJPTJets[1]);
  printf("= Events passing all but the pfjet filter:          %2d                        =\n",passPFJets[1]);
  //printf("= Events passing all but the trackjet filter:       %2d                        =\n",passTrackJets[1]);
  printf("= Events passing all but the CaloMET filter:        %2d                        =\n",passCaloMET[1]);
  printf("= Events passing all but the PFMET filter:          %2d                        =\n",passPFMET[1]);
  printf("= Events passing all but the TCMET filter:          %2d                        =\n",passTCMET[1]);
  printf("= Events passing all but the Lepton veto:           %2d                        =\n",passLeptons[1]);
  printf("= Events passing all but the PFLepton veto:         %2d                        =\n",passPFLeptons[1]);
  printf("= Events passing all but the photon veto:           %2d                        =\n",passPhotons[1]);
  //printf("= Events passing all but the pfphoton veto:         %2d                        =\n",passPFPhotons[1]);
  printf("= Events passing all but the vertex filter:         %2d                        =\n",passVertex[1]);
  printf("= Events passing all but the track filter:          %2d                        =\n",passTracks[1]);
  printf("= Events passing all but the trigger filter:        %2d                        =\n",passTriggers[1]);
  //printf("= Events passing all but the hemisphere filter:%2d                             =\n",passHemispheres[1]);
  printf("================================================================================\n");
}


//________________________________________________________________________________________
void
AnalysisNtuplePAT::initPlots() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";
  
  // Register this ntuple
  edm::Service<TFileService> fs;

  mAllData = fs->make<TTree>( "AllData", "data after preselection" );
  mAllData->SetAutoSave(10);

  mAllData->Branch("Run",           &m_Run,           "Run/I");
  mAllData->Branch("Event",         &m_Event,         "Event/I");
  mAllData->Branch("OrbitN",        &m_OrbitN,        "OrbitN/I");
  mAllData->Branch("StoreN",        &m_StoreN,        "StoreN/I");
  mAllData->Branch("LumiSection",   &m_LumiSection,   "LumiSection/I");
  mAllData->Branch("BunchCrossing", &m_BunchCrossing, "BunchCrossing/I");
  mAllData->Branch("IsData",        &m_IsData,        "IsData/O");

  //mJetData = fs->make<TTree>( "JetData", "Jet variables" );
  //mJetData->SetAutoSave(10);
  //
  //mMETData = fs->make<TTree>( "METData", "MET variables" );
  //mMETData->SetAutoSave(10);
  //
  //mLeptonData = fs->make<TTree>( "LeptonData", "Lepton variables" );
  //mLeptonData->SetAutoSave(10);
  //
  //mPhotonData = fs->make<TTree>( "PhotonData", "Photon variables" );
  //mPhotonData->SetAutoSave(10);
  //
  //mVertexData = fs->make<TTree>( "VertexData", "Vertex and beamspot variables" );
  //mVertexData->SetAutoSave(10);
  //
  //mTrackData = fs->make<TTree>( "TrackData", "Track variables" );
  //mTrackData->SetAutoSave(10);
  //
  //mTriggerData = fs->make<TTree>( "TriggerData", "Trigger variables" );
  //mTriggerData->SetAutoSave(10);
  //
  //if (doMCTruth_) {
  //  mGenParticleData = fs->make<TTree>( "GenParticleData", "GenParticle variables" );
  //  mGenParticleData->SetAutoSave(10);
  //}
    
  edm::LogInfo("AnalysisNtuplePAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________

// Define this as a plug-in

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(AnalysisNtuplePAT);

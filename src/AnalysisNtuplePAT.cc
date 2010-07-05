
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
// $Id: AnalysisNtuplePAT.cc,v 1.3 2010/05/20 19:40:21 sturdy Exp $
//
//
#include "JSturdy/AnalysisNtuplePAT/interface/AnalysisNtuplePAT.h"

#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
AnalysisNtuplePAT::AnalysisNtuplePAT(const edm::ParameterSet& iConfig)
{ 

  //default parameters
  debug_   = iConfig.getUntrackedParameter<int>("debugDiJets",0);
 

  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  initPlots();
    
  calojetinfo  = new JetAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("caloJetParameters"), mAllData);
  jptjetinfo   = new JetAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("jptJetParameters"), mAllData);
  pfjetinfo    = new JetAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("pfJetParameters"), mAllData);
  //trackjetinfo = new JetAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("trackJetParameters"), mAllData);

  calometinfo          = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometParameters"), mAllData);
  //calometoptinfo       = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometOptParameters"), mAllData);
  //calomettypeiiinfo    = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometTypeIIParameters"), mAllData);
  //calometopttypeiiinfo = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometOptTypeIIParameters"), mAllData);

  //calometcleaninfo          = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometCleanParameters"), mAllData);
  //calometcleanoptinfo       = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometCleanOptParameters"), mAllData);
  //calometcleantypeiiinfo    = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometCleanTypeIIParameters"), mAllData);
  //calometcleanopttypeiiinfo = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("calometCleanOptTypeIIParameters"), mAllData);

  pfmetinfo   = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("pfmetParameters"), mAllData);

  tcmetinfo      = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("tcmetParameters"), mAllData);
  //tcmetcleaninfo = new METAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("tcmetCleanParameters"), mAllData);

  photons   = new PhotonAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("photonParameters"), mAllData);
  pfphotons = new PhotonAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("pfphotonParameters"), mAllData);

  leptons   = new LeptonAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("leptonParameters"), mAllData);
  pfleptons = new LeptonAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("pfleptonParameters"), mAllData);

  vertex   = new VertexAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("vertexParameters"), mAllData);
  tracks   = new TrackAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("trackParameters"), mAllData);
  triggers = new TriggerAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("triggerParameters"), mAllData);
  //heminfo  = new HemisphereAnalyzerPAT(iConfig.getUntrackedParameter<edm::ParameterSet>("hemisphereParameters"), mAllData));

  //Setup counters for filters
  passCaloJets[0]    = 0;
  passJPTJets[0]     = 0;
  passPFJets[0]      = 0;
  //passTrackJets[0]   = 0;
  passCaloMET[0]     = 0;
  passPFMET[0]       = 0;
  passTCMET[0]       = 0;
  passLeptons[0]     = 0;
  //  passPFLeptons[0]   = 0;
  passPhotons[0]     = 0;
  //  passPFPhotons[0]   = 0;
  passVertex[0]      = 0;
  passTracks[0]      = 0;
  passTriggers[0]    = 0;
  //passHemispheres[0] = 0;
  passCaloJets[1]    = 0;
  passJPTJets[1]     = 0;
  passPFJets[1]      = 0;
  //passTrackJets[1]   = 0;
  passCaloMET[1]     = 0;
  passPFMET[1]       = 0;
  passTCMET[1]       = 0;
  passLeptons[1]     = 0;
  //  passPFLeptons[1]   = 0;
  passPhotons[1]     = 0;
  //  passPFPhotons[1]   = 0;
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
AnalysisNtuplePAT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;

  edm::LogVerbatim("AnalysisNtuplePAT") << " Start  " << std::endl;

  std::ostringstream dbg;

  //////////////////////////////////
  //       Event Auxiliary        //
  //////////////////////////////////

  m_Run           = iEvent.id().run();
  m_Event         = iEvent.id().event();
  m_OrbitN        = iEvent.orbitNumber();
  m_StoreN        = iEvent.eventAuxiliary().storeNumber();
  m_LumiSection   = iEvent.luminosityBlock();
  m_BunchCrossing = iEvent.bunchCrossing();

  //Run filters

  std::cout<<"Getting the calo jet result"<<std::endl;
  bool mycalojetresult  = calojetinfo->filter(iEvent, iSetup);
  std::cout<<"Getting the jpt jet result"<<std::endl;
  bool myjptjetresult   = jptjetinfo->filter(iEvent, iSetup);
  std::cout<<"Getting the pf jet result"<<std::endl;
  bool mypfjetresult    = pfjetinfo->filter(iEvent, iSetup);
  //std::cout<<"Getting the calo jet result"<<std::endl;
  //bool mytrackjetresult = trackjetinfo->filter(iEvent, iSetup);

  std::cout<<"Getting the calo met result"<<std::endl;
  bool mycalometresult          = calometinfo->filter(iEvent, iSetup);
  //bool mycalometoptresult       = calometoptinfo->filter(iEvent, iSetup);
  //bool mycalomettypeiiresult    = calomettypeiiinfo->filter(iEvent, iSetup);
  //bool mycalometopttypeiiresult = calometopttypeiiinfo->filter(iEvent, iSetup);

  //bool mycalometcleanresult          = calometcleaninfo->filter(iEvent, iSetup);
  //bool mycalometcleanoptresult       = calometcleanoptinfo->filter(iEvent, iSetup);
  //bool mycalometcleantypeiiresult    = calometcleantypeiiinfo->filter(iEvent, iSetup);
  //bool mycalometcleanopttypeiiresult = calometcleanopttypeiiinfo->filter(iEvent, iSetup);

  std::cout<<"Getting the pf met result"<<std::endl;
  bool mypfmetresult   = pfmetinfo->filter(iEvent, iSetup);

  std::cout<<"Getting the tc met result"<<std::endl;
  bool mytcmetresult      = tcmetinfo->filter(iEvent, iSetup);
  //bool mytcmetcleanresult = tcmetcleaninfo->filter(iEvent, iSetup);

  std::cout<<"Getting the reco photon result"<<std::endl;
  bool myphotonresult   = photons->filter(iEvent, iSetup);
  std::cout<<"Getting the pf photon result"<<std::endl;
  bool mypfphotonresult = pfphotons->filter(iEvent, iSetup);

  std::cout<<"Getting the reco lepton result"<<std::endl;
  bool myleptonresult   = leptons->filter(iEvent, iSetup);
  std::cout<<"Getting the pf lepton result"<<std::endl;
  bool mypfleptonresult = pfleptons->filter(iEvent, iSetup);

  std::cout<<"Getting the vertex result"<<std::endl;
  bool myvertexresult  = vertex->filter(iEvent, iSetup);
  std::cout<<"Getting the track result"<<std::endl;
  bool mytrackresult   = tracks->filter(iEvent, iSetup);
  bool mytriggerresult = triggers->filter(iEvent, iSetup);
  //bool myhemresult     = heminfo->filter(iEvent, iSetup);

  if (mycalojetresult)  ++passCaloJets[0];
  if (myjptjetresult)   ++passJPTJets[0];
  if (mypfjetresult)    ++passPFJets[0];
  //  if (mytrackjetresult) ++passTrackJets[0];

  if (mycalometresult) ++passCaloMET[0];
  if (mypfmetresult)   ++passPFMET[0];
  if (mytcmetresult)   ++passTCMET[0];

  if (myleptonresult)   ++passLeptons[0];
  if (mypfleptonresult) ++passPFLeptons[0];

  if (myphotonresult)   ++passPhotons[0];
  if (mypfphotonresult) ++passPFPhotons[0];

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
AnalysisNtuplePAT::beginJob() {
  //setup job before events
}

//________________________________________________________________________________________
void 
AnalysisNtuplePAT::endJob() {
  //cleanup after all events
  printSummary();
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
  printf("= Events passing the pfphoton veto:         %2d                                =\n",passPFPhotons[0]);
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
  printf("= Events passing all but the pfphoton veto:         %2d                        =\n",passPFPhotons[1]);
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

  mAllData->Branch("Run",           &m_Run,           "Run/int");
  mAllData->Branch("Event",         &m_Event,         "Event/int");
  mAllData->Branch("OrbitN",        &m_OrbitN,        "OrbitN/int");
  mAllData->Branch("StoreN",        &m_StoreN,        "StoreN/int");
  mAllData->Branch("LumiSection",   &m_LumiSection,   "LumiSection/int");
  mAllData->Branch("BunchCrossing", &m_BunchCrossing, "BunchCrossing/int");


    
  edm::LogInfo("AnalysisNtuplePAT") << "Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________

// Define this as a plug-in

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(AnalysisNtuplePAT);

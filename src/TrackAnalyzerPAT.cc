
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      TrackAnalyzerPAT
// 
/**\class TrackAnalyzerPAT TrackAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/TrackAnalyzerPAT.cc

Description: Collects variables related to tracks


*/
//
// Original Author:  Jared Sturdy (from SusyAnalysisNtuplePAT)
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: TrackAnalyzerPAT.cc,v 1.8 2011/03/08 21:11:36 sturdy Exp $
//
//
#include "JSturdy/AnalysisNtuplePAT/interface/TrackAnalyzerPAT.h"
#include <TMath.h>

//________________________________________________________________________________________
TrackAnalyzerPAT::TrackAnalyzerPAT(const edm::ParameterSet& trackParams, TTree* mTrackData)
{ 
  debug_   = trackParams.getUntrackedParameter<int>("debugTracks",0);
  //doMCData_  = trackParams.getUntrackedParameter<bool>("doMCTracks",false);
  //if (doMCData_)
  trackTag_  = trackParams.getUntrackedParameter<edm::InputTag>("trackTag");
 
  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree(mTrackData);
}


//________________________________________________________________________________________
TrackAnalyzerPAT::~TrackAnalyzerPAT() {
  //delete mTrackData;
}

//
//________________________________________________________________________________________
void TrackAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
}
//________________________________________________________________________________________
// Method called to for each event
bool TrackAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  doMCData_ = ev.isRealData();

  track_result = true;
  edm::LogVerbatim("TrackEvent") << " Start  " << std::endl;

  std::ostringstream dbg;

  
  //get tracks
  
  if (debug_)
    std::cout<<"Getting the tracks"<<std::endl;

  edm::Handle<View<reco::Track> >  myTracks;
  ev.getByLabel(trackTag_,myTracks);
  if (!myTracks.isValid()) {
    edm::LogVerbatim("TrackEvent") << " Unable to find reco::Tracks with label  "<<trackTag_ << std::endl;
    if (debug_)
      std::cout<<"No valid tracks"<<std::endl;
    return false;
  }

  double ptMax_ = 500;
  if (debug_)
    std::cout<<"Total p3"<<std::endl;
  math::XYZTLorentzVector totalP3;
  for(View<reco::Track>::const_iterator elem = myTracks->begin(); 
      elem != myTracks->end(); ++elem) {
    
    if (!(elem->quality(reco::TrackBase::highPurity))) continue;
    
    double elemPt = elem->pt();
    
    if ( elemPt > ptMax_) continue;
    
    if (debug_)
      std::cout<<"track p3"<<std::endl;
    math::XYZTLorentzVector p3(elem->px(),elem->py(),elem->pz(),elem->p());
    totalP3 -= p3;
    
  }
  
  //v_MPTP3 = totalP3;
  m_MPTPhi= totalP3.phi();
  m_MPTPx = totalP3.px();
  m_MPTPy = totalP3.py();
  m_MPTPz = totalP3.pz();
   
  if (debug_)
    std::cout<<"Done analyzing tracks"<<std::endl;
  return track_result;
}

//________________________________________________________________________________________
void TrackAnalyzerPAT::bookTTree(TTree* mTrackData) {

  ////mTrackData->Branch("MPTP3",  &v_MPTP3,  "MPTP3");
  mTrackData->Branch("MPTPhi", &m_MPTPhi, "MPTPhi/D");
  mTrackData->Branch("MPTPx",  &m_MPTPx,  "MPTPx/D");
  mTrackData->Branch("MPTPy",  &m_MPTPy,  "MPTPy/D");
  mTrackData->Branch("MPTPz",  &m_MPTPz,  "MPTPz/D");

}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(TrackAnalyzerPAT);

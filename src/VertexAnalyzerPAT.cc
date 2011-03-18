
// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      VertexAnalyzerPAT
// 
/**\class VertexAnalyzerPAT VertexAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/VertexAnalyzerPAT.cc

Description: Collects variables related to vertices, performs a primary vertex check, 
             If successful, it stores the variables and returns the value of the check

*/
//
// Original Author:  Jared Sturdy
//         Created:  Fri Jan 29 16:10:31 PDT 2010
// $Id: VertexAnalyzerPAT.cc,v 1.11 2011/03/15 14:55:52 sturdy Exp $
//
//

#include "JSturdy/AnalysisNtuplePAT/interface/VertexAnalyzerPAT.h"
#include <TMath.h>
#include <sstream>

//________________________________________________________________________________________
VertexAnalyzerPAT::VertexAnalyzerPAT(const edm::ParameterSet& vertexParams, TTree* tmpAllData)
{ 
  mVertexData = tmpAllData;

  //defaults
  _debug   = vertexParams.getUntrackedParameter<int>("debugVtx");

  _minNVtx    = vertexParams.getUntrackedParameter<int>("minNVtx",1);
  _minVtxTrks = vertexParams.getUntrackedParameter<int>("minVtxTrks",3);
  _minVtxNdof = vertexParams.getUntrackedParameter<int>("minVtxNdof",4);
  _maxVtxChi2 = vertexParams.getUntrackedParameter<double>("maxVtxChi2",999.);
  _maxVtxZ    = vertexParams.getUntrackedParameter<double>("maxVtxZ",15.);
  _maxVtxd0   = vertexParams.getUntrackedParameter<double>("maxVtxd0",2.);
    
  _vtxTag      = vertexParams.getUntrackedParameter<edm::InputTag>("vtxTag"); 
  _beamspotTag = vertexParams.getUntrackedParameter<edm::InputTag>("beamspotTag"); 

  bookTTree();
}


//________________________________________________________________________________________
VertexAnalyzerPAT::~VertexAnalyzerPAT() {
  delete mVertexData;
}

//
//________________________________________________________________________________________
void VertexAnalyzerPAT::beginRun(const edm::Run& run, const edm::EventSetup&es)
{
}

//________________________________________________________________________________________
// Method called to for each event
bool VertexAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  edm::LogVerbatim("VertexAnalyzerPAT") << " Start  " << std::endl;

  std::ostringstream dbg;
  vertexDecision = false;

  ///////////////////////////////////
  //          Beamspot             //
  ///////////////////////////////////
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
  ev.getByLabel(_beamspotTag,recoBeamSpotHandle);
  reco::BeamSpot bs = *recoBeamSpotHandle;   
  
  m_Beamspot_x0    = bs.x0();
  m_Beamspot_y0    = bs.y0();
  m_Beamspot_z0    = bs.z0();
  m_Beamspot_x0Err = bs.x0Error();
  m_Beamspot_y0Err = bs.y0Error();
  m_Beamspot_z0Err = bs.z0Error();

  m_Beamspot_WidthX    = bs.BeamWidthX();
  m_Beamspot_WidthY    = bs.BeamWidthY();
  m_Beamspot_WidthXErr = bs.BeamWidthXError();
  m_Beamspot_WidthYErr = bs.BeamWidthYError();

  m_Beamspot_dxdz    = bs.dxdz();
  m_Beamspot_dydz    = bs.dydz();
  m_Beamspot_dxdzErr = bs.dxdzError();
  m_Beamspot_dydzErr = bs.dydzError();

  m_Beamspot_SigmaZ0    = bs.sigmaZ();
  m_Beamspot_SigmaZ0Err = bs.sigmaZ0Error();

  m_Beamspot_EmittanceX = bs.emittanceX();
  m_Beamspot_EmittanceY = bs.emittanceY();
  m_Beamspot_BetaStar   = bs.betaStar();

  // get the Vertex collection

  edm::LogVerbatim("VertexAnalyzerPAT") << "Vertex results for InputTag" << _vtxTag;
  Handle<VertexCollection> vertices;
  ev.getByLabel(_vtxTag, vertices);

  if ( !vertices.isValid() ) {
    edm::LogWarning("VertexAnalyzerPAT") << "No Vertex results for InputTag" << _vtxTag;
    return vertexDecision;
  } 

  int tmpnVtx  = (*vertices).size();
  int numVtx   = 0;
  int tmpNtrks = 0;
  if (tmpnVtx > 50) tmpnVtx = 50;
  maintenance();
  vd_VtxSumTrkPt.resize(tmpnVtx);
  for (int i=0; i< tmpnVtx; i++){  
    const reco::Vertex& pVertex = (*vertices)[i];

    if(pVertex.isValid()) {
      vd_VtxNormalizedChi2.push_back(pVertex.normalizedChi2());
      vd_VtxIsValid       .push_back(pVertex.isValid());
      vd_VtxNRawTrks      .push_back(pVertex.tracksSize());
      vd_VtxChi2          .push_back(pVertex.chi2());
      vd_VtxNdof          .push_back(pVertex.ndof());
      vd_VtxX             .push_back(pVertex.x());
      vd_VtxY             .push_back(pVertex.y());
      vd_VtxZ             .push_back(pVertex.z());
      vd_VtxdX            .push_back(pVertex.xError());
      vd_VtxdY            .push_back(pVertex.yError());
      vd_VtxdZ            .push_back(pVertex.zError());
      vd_Vtxd0            .push_back(pVertex.position().rho());
            
      int cur_index = 0;
      vd_VtxSumTrkPt.at(numVtx) = 0.;
      for (Vertex::trackRef_iterator vertex_curTrack = pVertex.tracks_begin(); 
	   vertex_curTrack!=pVertex.tracks_end(); 
	   vertex_curTrack++) {

	vd_VtxSumTrkPt.at(numVtx) += (*vertex_curTrack)->pt();

	if (pVertex.trackWeight(*vertex_curTrack) > 0.5) 
	  ++tmpNtrks;

	++cur_index;
      }
      vd_VtxNTrks.push_back(tmpNtrks);
      ++numVtx;
    }
  }

  i_nVtx = numVtx;
  if (i_nVtx>=_minNVtx)
    //if (vd_VtxNTrks.at(0)>=_minVtxTrks)
    //if (vd_VtxSumTrkPt.at(0)>=_minVtxSumTrkPt)
    if (vd_VtxNdof.at(0)>=_minVtxNdof)
      if(vd_VtxChi2.at(0)<=_maxVtxChi2)
	if (vd_VtxZ.at(0)<=_maxVtxZ)
	  if (vd_Vtxd0.at(0)<=_maxVtxd0)
	  vertexDecision = true;

  
  //mVertexData->Fill();
  if (_debug)
    std::cout<<"Done analyzing vertices"<<std::endl;
  return vertexDecision;
}


//________________________________________________________________________________________
void VertexAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Beam spot parameters
  mVertexData->Branch("beamspotX0",        &m_Beamspot_x0,        "beamspotX0/D");
  mVertexData->Branch("beamspotY0",        &m_Beamspot_y0,        "beamspotY0/D");
  mVertexData->Branch("beamspotZ0",        &m_Beamspot_z0,        "beamspotZ0/D");
  mVertexData->Branch("beamspotX0Err",     &m_Beamspot_x0Err,     "beamspotX0Err/D");
  mVertexData->Branch("beamspotY0Err",     &m_Beamspot_y0Err,     "beamspotY0Err/D");
  mVertexData->Branch("beamspotZ0Err",     &m_Beamspot_z0Err,     "beamspotZ0Err/D");
  mVertexData->Branch("beamspotWidthX",    &m_Beamspot_WidthX,    "beamspotWidthX/D");
  mVertexData->Branch("beamspotWidthY",    &m_Beamspot_WidthY,    "beamspotWidthY/D");
  mVertexData->Branch("beamspotWidthXErr", &m_Beamspot_WidthXErr, "beamspotWidthXErr/D");
  mVertexData->Branch("beamspotWidthYErr", &m_Beamspot_WidthYErr, "beamspotWidthYErr/D");

  mVertexData->Branch("beamspotdxdz",       &m_Beamspot_dxdz,       "beamspotdxdz/D");
  mVertexData->Branch("beamspotdydz",       &m_Beamspot_dydz,       "beamspotdydz/D");
  mVertexData->Branch("beamspotdxdzErr",    &m_Beamspot_dxdzErr,    "beamspotdxdzErr/D");
  mVertexData->Branch("beamspotdydzErr",    &m_Beamspot_dydzErr,    "beamspotdydzErr/D");
  mVertexData->Branch("beamspotSigmaZ0",    &m_Beamspot_SigmaZ0,    "beamspotSigmaZ0/D");
  mVertexData->Branch("beamspotSigmaZ0Err", &m_Beamspot_SigmaZ0Err, "beamspotSigmaZ0Err/D");

  mVertexData->Branch("beamspotEmittanceX",      &m_Beamspot_EmittanceX,  "beamspotEmittanceX/D");
  mVertexData->Branch("beamspotEmittanceY",      &m_Beamspot_EmittanceY,  "beamspotEmittanceY/D");
  mVertexData->Branch("beamspotBetaStar",        &m_Beamspot_BetaStar,    "beamspotBetaStar/D");


  //Vertex parameters
  mVertexData->Branch("nVtx",                &i_nVtx,             "nVtx/I");
  mVertexData->Branch("VertexChi2",          &vd_VtxChi2);
  mVertexData->Branch("VertexNdof",          &vd_VtxNdof);
  mVertexData->Branch("VertexNTrks",         &vd_VtxNTrks);
  mVertexData->Branch("VertexNRawTrks",      &vd_VtxNRawTrks);
  mVertexData->Branch("VertexIsValid",       &vd_VtxIsValid);
  mVertexData->Branch("VertexNormalizedChi2",&vd_VtxNormalizedChi2);
  
  mVertexData->Branch("VertexX", &vd_VtxX);
  mVertexData->Branch("VertexY", &vd_VtxY);
  mVertexData->Branch("VertexZ", &vd_VtxZ);
  mVertexData->Branch("Vertexd0",&vd_Vtxd0);
  mVertexData->Branch("VertexdX",&vd_VtxdX);
  mVertexData->Branch("VertexdY",&vd_VtxdY);
  mVertexData->Branch("VertexdZ",&vd_VtxdZ);
  
  edm::LogInfo("VertexAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}

//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(VertexAnalyzerPAT);

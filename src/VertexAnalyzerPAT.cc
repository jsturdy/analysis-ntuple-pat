
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
// $Id: VertexAnalyzerPAT.cc,v 1.5 2010/04/05 15:25:37 sturdy Exp $
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


//________________________________________________________________________________________
// Method called to for each event
bool VertexAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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
  iEvent.getByLabel(_beamspotTag,recoBeamSpotHandle);
  reco::BeamSpot bs = *recoBeamSpotHandle;   

  m_Beamspot_x0 = bs.x0();
  m_Beamspot_x0Error = bs.x0Error();
  m_Beamspot_y0 = bs.y0();
  m_Beamspot_y0Error = bs.y0Error();
  m_Beamspot_z0 = bs.z0();
  m_Beamspot_z0Error = bs.z0Error();

  m_Beamspot_WidthX     = bs.BeamWidthX();
  m_Beamspot_WidthXError = bs.BeamWidthXError();
  m_Beamspot_WidthY     = bs.BeamWidthY();
  m_Beamspot_WidthYError = bs.BeamWidthYError();

  m_Beamspot_SigmaZ0 = bs.sigmaZ();
  m_Beamspot_SigmaZ0Error = bs.sigmaZ0Error();

  m_Beamspot_dxdz = bs.dxdz();
  m_Beamspot_dxdzError = bs.dxdzError();
  m_Beamspot_dydz = bs.dydz();
  m_Beamspot_dydzError = bs.dydzError();

  m_Beamspot_EmittanceX = bs.emittanceX();
  m_Beamspot_EmittanceY = bs.emittanceY();
  m_Beamspot_BetaStar   = bs.betaStar();

  // get the Vertex collection

  LogDebug("VertexAnalyzerPAT") << "Vertex results for InputTag" << _vtxTag;
  Handle<VertexCollection> vertices;
  iEvent.getByLabel(_vtxTag, vertices);
  if ( !vertices.isValid() ) {
    LogDebug("VertexAnalyzerPAT") << "No Vertex results for InputTag" << _vtxTag;
    return vertexDecision;
  } 

  int tmpnVtx = (*vertices).size();
  int numVtx = 0;
  if (tmpnVtx > 10) tmpnVtx = 10;
  for (int i=0; i< tmpnVtx; i++){  
    const reco::Vertex* pVertex = &(*vertices)[i];
    if(pVertex->isValid()) {
      m_VtxNormalizedChi2[i] = pVertex->normalizedChi2();
      m_VtxIsValid[i]        = pVertex->isValid();
      m_VtxNRawTrks[i]       = pVertex->tracksSize();
      m_VtxChi2[i]           = pVertex->chi2();
      m_VtxNdof[i]           = pVertex->ndof();
      m_VtxX[i]              = pVertex->x();
      m_VtxY[i]              = pVertex->y();
      m_VtxZ[i]              = pVertex->z();
      m_VtxdX[i]             = pVertex->xError();
      m_VtxdY[i]             = pVertex->yError();
      m_VtxdZ[i]             = pVertex->zError();
      m_Vtxd0[i]             = pVertex->position().rho();
      
      for (Vertex::trackRef_iterator vertex_curTrack = pVertex->tracks_begin(); vertex_curTrack!=pVertex->tracks_end(); vertex_curTrack++) {
	m_VtxSumTrkPt[i] += (*vertex_curTrack)->pt();
	if (pVertex->trackWeight(*vertex_curTrack) > 0.5) 
	  ++m_VtxNTrks[i];
      }
      
      ++numVtx;
    }
  } 
  m_nVtx = numVtx;
  if (m_nVtx>=_minNVtx)
    //if (m_VtxNTrks[0]>=_minVtxTrks)
    //if (m_VtxSumTrkPt[0]>=_minVtxSumTrkPt)
    if (m_VtxNdof[0]>=_minVtxNdof)
      if(m_VtxChi2[0]<=_maxVtxChi2)
	if (m_VtxZ[0]<=_maxVtxZ)
	  if (m_Vtxd0[0]<=_maxVtxd0)
	  vertexDecision = true;
  
  //mVertexData->Fill();
  return vertexDecision;
}


//________________________________________________________________________________________
void VertexAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  
  // 1. Event variables
  variables << "weight:process";

  //Beam spot parameters
  mVertexData->Branch("beamspotX0",                &m_Beamspot_x0,            "beamspotX0/double");
  mVertexData->Branch("beamspotY0",                &m_Beamspot_y0,            "beamspotY0/double");
  mVertexData->Branch("beamspotZ0",                &m_Beamspot_z0,            "beamspotZ0/double");
  mVertexData->Branch("beamspotWidthX",            &m_Beamspot_WidthX,        "beamspotWidthX/double");
  mVertexData->Branch("beamspotWidthY",            &m_Beamspot_WidthY,        "beamspotWidthY/double");
  mVertexData->Branch("beamspotX0Error",           &m_Beamspot_x0Error,       "beamspotX0Error/double");
  mVertexData->Branch("beamspotY0Error",           &m_Beamspot_y0Error,       "beamspotY0Error/double");
  mVertexData->Branch("beamspotZ0Error",           &m_Beamspot_z0Error,       "beamspotZ0Error/double");
  mVertexData->Branch("beamspotWidthXError",       &m_Beamspot_WidthXError,   "beamspotWidthXError/double");
  mVertexData->Branch("beamspotWidthYError",       &m_Beamspot_WidthYError,   "beamspotWidthYError/double");

  mVertexData->Branch("beamspotSigmaZ0",      &m_Beamspot_SigmaZ0,      "beamspotSigmaZ0/double");
  mVertexData->Branch("beamspotSigmaZ0Error", &m_Beamspot_SigmaZ0Error, "beamspotSigmaZ0Error/double");
  mVertexData->Branch("beamspotdxdz",         &m_Beamspot_dxdz,         "beamspotdxdz/double");
  mVertexData->Branch("beamspotdxdzError",    &m_Beamspot_dxdzError,    "beamspotdxdzError/double");
  mVertexData->Branch("beamspotdydz",         &m_Beamspot_dydz,         "beamspotdydz/double");
  mVertexData->Branch("beamspotdydzError",    &m_Beamspot_dydzError,    "beamspotdydzError/double");

  mVertexData->Branch("beamspotEmittanceX",      &m_Beamspot_EmittanceX,  "beamspotEmittanceX/double");
  mVertexData->Branch("beamspotEmittanceY",      &m_Beamspot_EmittanceY,  "beamspotEmittanceY/double");
  mVertexData->Branch("beamspotBetaStar",        &m_Beamspot_BetaStar,    "beamspotBetaStar/double");


  //Vertex parameters
  mVertexData->Branch("nVtx",               &m_nVtx,             "nVtx/int");
  mVertexData->Branch("VertexChi2",          m_VtxChi2,          "VertexChi2[nVtx]/double");
  mVertexData->Branch("VertexNdof",          m_VtxNdof,          "VertexNdof[nVtx]/double");
  mVertexData->Branch("VertexNTrks",          m_VtxNTrks,          "VertexNTrks[nVtx]/double");
  mVertexData->Branch("VertexNRawTrks",       m_VtxNRawTrks,       "VertexNRawTrks[nVtx]/double");
  mVertexData->Branch("VertexIsValid",       m_VtxIsValid,       "VertexIsValid[nVtx]/double");
  mVertexData->Branch("VertexNormalizedChi2",m_VtxNormalizedChi2,"VertexNormalizedChi2[nVtx]/double");

  mVertexData->Branch("VertexX", m_VtxX, "VertexX[nVtx]/double");
  mVertexData->Branch("VertexY", m_VtxY, "VertexY[nVtx]/double");
  mVertexData->Branch("VertexZ", m_VtxZ, "VertexZ[nVtx]/double");
  mVertexData->Branch("Vertexd0",m_Vtxd0,"Vertexd0[nVtx]/double");
  mVertexData->Branch("VertexdX",m_VtxdX,"VertexdX[nVtx]/double");
  mVertexData->Branch("VertexdY",m_VtxdY,"VertexdY[nVtx]/double");
  mVertexData->Branch("VertexdZ",m_VtxdZ,"VertexdZ[nVtx]/double");
  
  edm::LogInfo("VertexAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}

//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(VertexAnalyzerPAT);


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
// $Id: VertexAnalyzerPAT.cc,v 1.6 2010/06/21 22:45:38 sturdy Exp $
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

  m_Beamspot_x0      = bs.x0();
  m_Beamspot_x0Error = bs.x0Error();
  m_Beamspot_y0      = bs.y0();
  m_Beamspot_y0Error = bs.y0Error();
  m_Beamspot_z0      = bs.z0();
  m_Beamspot_z0Error = bs.z0Error();

  m_Beamspot_WidthX      = bs.BeamWidthX();
  m_Beamspot_WidthXError = bs.BeamWidthXError();
  m_Beamspot_WidthY      = bs.BeamWidthY();
  m_Beamspot_WidthYError = bs.BeamWidthYError();

  m_Beamspot_SigmaZ0      = bs.sigmaZ();
  m_Beamspot_SigmaZ0Error = bs.sigmaZ0Error();

  m_Beamspot_dxdz      = bs.dxdz();
  m_Beamspot_dxdzError = bs.dxdzError();
  m_Beamspot_dydz      = bs.dydz();
  m_Beamspot_dydzError = bs.dydzError();

  m_Beamspot_EmittanceX = bs.emittanceX();
  m_Beamspot_EmittanceY = bs.emittanceY();
  m_Beamspot_BetaStar   = bs.betaStar();

  // get the Vertex collection

  edm::LogVerbatim("VertexAnalyzerPAT") << "Vertex results for InputTag" << _vtxTag;
  Handle<VertexCollection> vertices;
  iEvent.getByLabel(_vtxTag, vertices);

  if ( !vertices.isValid() ) {
    edm::LogWarning("VertexAnalyzerPAT") << "No Vertex results for InputTag" << _vtxTag;
    return vertexDecision;
  } 

  int tmpnVtx  = (*vertices).size();
  int numVtx   = 0;
  int tmpNtrks = 0;
  if (tmpnVtx > 10) tmpnVtx = 10;
  for (int i=0; i< tmpnVtx; i++){  
    const reco::Vertex& pVertex = (*vertices)[i];

    if(pVertex.isValid()) {
      m_VtxNormalizedChi2[numVtx] = pVertex.normalizedChi2();
      m_VtxIsValid[numVtx]        = pVertex.isValid();
      m_VtxNRawTrks[numVtx]       = pVertex.tracksSize();
      m_VtxChi2[numVtx]           = pVertex.chi2();
      m_VtxNdof[numVtx]           = pVertex.ndof();
      m_VtxX[numVtx]              = pVertex.x();
      m_VtxY[numVtx]              = pVertex.y();
      m_VtxZ[numVtx]              = pVertex.z();
      m_VtxdX[numVtx]             = pVertex.xError();
      m_VtxdY[numVtx]             = pVertex.yError();
      m_VtxdZ[numVtx]             = pVertex.zError();
      m_Vtxd0[numVtx]             = pVertex.position().rho();
            
      int cur_index = 0;
      for (Vertex::trackRef_iterator vertex_curTrack = pVertex.tracks_begin(); 
	   vertex_curTrack!=pVertex.tracks_end(); 
	   vertex_curTrack++) {

	m_VtxSumTrkPt[numVtx] += (*vertex_curTrack)->pt();

	if (pVertex.trackWeight(*vertex_curTrack) > 0.5) 
	  ++tmpNtrks;

	++cur_index;
      }
      m_VtxNTrks[numVtx] = tmpNtrks;
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
  mVertexData->Branch("beamspotX0",                &m_Beamspot_x0,            "beamspotX0/D");
  mVertexData->Branch("beamspotY0",                &m_Beamspot_y0,            "beamspotY0/D");
  mVertexData->Branch("beamspotZ0",                &m_Beamspot_z0,            "beamspotZ0/D");
  mVertexData->Branch("beamspotWidthX",            &m_Beamspot_WidthX,        "beamspotWidthX/D");
  mVertexData->Branch("beamspotWidthY",            &m_Beamspot_WidthY,        "beamspotWidthY/D");
  mVertexData->Branch("beamspotX0Error",           &m_Beamspot_x0Error,       "beamspotX0Error/D");
  mVertexData->Branch("beamspotY0Error",           &m_Beamspot_y0Error,       "beamspotY0Error/D");
  mVertexData->Branch("beamspotZ0Error",           &m_Beamspot_z0Error,       "beamspotZ0Error/D");
  mVertexData->Branch("beamspotWidthXError",       &m_Beamspot_WidthXError,   "beamspotWidthXError/D");
  mVertexData->Branch("beamspotWidthYError",       &m_Beamspot_WidthYError,   "beamspotWidthYError/D");

  mVertexData->Branch("beamspotSigmaZ0",      &m_Beamspot_SigmaZ0,      "beamspotSigmaZ0/D");
  mVertexData->Branch("beamspotSigmaZ0Error", &m_Beamspot_SigmaZ0Error, "beamspotSigmaZ0Error/D");
  mVertexData->Branch("beamspotdxdz",         &m_Beamspot_dxdz,         "beamspotdxdz/D");
  mVertexData->Branch("beamspotdxdzError",    &m_Beamspot_dxdzError,    "beamspotdxdzError/D");
  mVertexData->Branch("beamspotdydz",         &m_Beamspot_dydz,         "beamspotdydz/D");
  mVertexData->Branch("beamspotdydzError",    &m_Beamspot_dydzError,    "beamspotdydzError/D");

  mVertexData->Branch("beamspotEmittanceX",      &m_Beamspot_EmittanceX,  "beamspotEmittanceX/D");
  mVertexData->Branch("beamspotEmittanceY",      &m_Beamspot_EmittanceY,  "beamspotEmittanceY/D");
  mVertexData->Branch("beamspotBetaStar",        &m_Beamspot_BetaStar,    "beamspotBetaStar/D");


  //Vertex parameters
  mVertexData->Branch("nVtx",               &m_nVtx,             "nVtx/I");
  mVertexData->Branch("VertexChi2",          m_VtxChi2,          "VertexChi2[nVtx]/D");
  mVertexData->Branch("VertexNdof",          m_VtxNdof,          "VertexNdof[nVtx]/D");
  mVertexData->Branch("VertexNTrks",         m_VtxNTrks,         "VertexNTrks[nVtx]/D");
  mVertexData->Branch("VertexNRawTrks",      m_VtxNRawTrks,      "VertexNRawTrks[nVtx]/D");
  mVertexData->Branch("VertexIsValid",       m_VtxIsValid,       "VertexIsValid[nVtx]/D");
  mVertexData->Branch("VertexNormalizedChi2",m_VtxNormalizedChi2,"VertexNormalizedChi2[nVtx]/D");

  mVertexData->Branch("VertexX", m_VtxX, "VertexX[nVtx]/D");
  mVertexData->Branch("VertexY", m_VtxY, "VertexY[nVtx]/D");
  mVertexData->Branch("VertexZ", m_VtxZ, "VertexZ[nVtx]/D");
  mVertexData->Branch("Vertexd0",m_Vtxd0,"Vertexd0[nVtx]/D");
  mVertexData->Branch("VertexdX",m_VtxdX,"VertexdX[nVtx]/D");
  mVertexData->Branch("VertexdY",m_VtxdY,"VertexdY[nVtx]/D");
  mVertexData->Branch("VertexdZ",m_VtxdZ,"VertexdZ[nVtx]/D");
  
  edm::LogInfo("VertexAnalyzerPAT") << "Ntuple variables " << variables.str();
  
}

//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(VertexAnalyzerPAT);

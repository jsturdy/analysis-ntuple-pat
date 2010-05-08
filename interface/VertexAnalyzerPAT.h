#ifndef VERTEXANALYZERPAT
#define VERTEXANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


//
// Class declaration
//
class VertexAnalyzerPAT {
 public:
  VertexAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~VertexAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup );

  //*** Plotting
  void bookTTree();


 private:
  
  //configuration parameters
  edm::InputTag _vtxTag;
  edm::InputTag _beamspotTag;
  double _minNVtx, _minVtxTrks, _minVtxNdof, _maxVtxChi2, _maxVtxZ, _maxVtxd0;   /// for primary vertex selection, can be moved to config file?
  int    _debug;

  char logmessage[128];
  
  // Plots
  TTree * mVertexData;    //Will contain the data passing the vertex selection

  bool   vertexDecision;
  
  double m_Beamspot_x0;
  double m_Beamspot_x0Error;
  double m_Beamspot_y0;
  double m_Beamspot_y0Error;
  double m_Beamspot_z0;
  double m_Beamspot_z0Error;
  double m_Beamspot_WidthX;
  double m_Beamspot_WidthXError;
  double m_Beamspot_WidthY;
  double m_Beamspot_WidthYError;

  double m_Beamspot_SigmaZ0;
  double m_Beamspot_SigmaZ0Error;
  double m_Beamspot_dxdz;
  double m_Beamspot_dxdzError;
  double m_Beamspot_dydz;
  double m_Beamspot_dydzError;

  double m_Beamspot_EmittanceX;
  double m_Beamspot_EmittanceY;
  double m_Beamspot_BetaStar;

  int    m_nVtx;
  int    m_VtxNTrks[10];
  int    m_VtxNRawTrks[10];
  double m_VtxChi2[10];
  double m_VtxNdof[10];
  double m_VtxIsValid[10];
  double m_VtxSumTrkPt[10];
  double m_VtxNormalizedChi2[10];
  double m_VtxX[10];
  double m_VtxY[10];
  double m_VtxZ[10];
  double m_VtxdX[10];
  double m_VtxdY[10];
  double m_VtxdZ[10];
  double m_Vtxd0[10];

};

#endif
















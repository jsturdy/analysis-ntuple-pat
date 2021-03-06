#ifndef VERTEXANALYZERPAT
#define VERTEXANALYZERPAT

// System include files
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <utility>

// ROOT includes
#include <TNtuple.h>

// Framework include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//#include <boost/shared_ptr.hpp>

//
// Class declaration
//
//#ifdef __MAKECINT__
//#pragma link C++ class    std::vector<double>+;
//#pragma link C++ class    std::vector<float >+;
//
//#pragma link C++ class    std::auto_ptr<std::vector<double> >+;
//#pragma link C++ class    std::auto_ptr<std::vector<float> >+;
//#endif

class VertexAnalyzerPAT {
 public:
  VertexAnalyzerPAT(const edm::ParameterSet&, TTree*);
  ~VertexAnalyzerPAT();
  
  bool filter(const edm::Event& evt,const edm::EventSetup& iSetup);

  void beginRun(const edm::Run& run, const edm::EventSetup& es);
  //*** Plotting
  void bookTTree(TTree*);


 private:
  
  //configuration parameters
  edm::InputTag _vtxTag;
  edm::InputTag _beamspotTag;
  double _minNVtx, _minVtxTrks, _minVtxNdof, _maxVtxChi2, _maxVtxZ, _maxVtxd0;   /// for primary vertex selection, can be moved to config file?
  int    _debug;

  // Plots
  //TTree * mVertexData;    //Will contain the data passing the vertex selection

  bool   vertexDecision;
  
  double m_Beamspot_x0;
  double m_Beamspot_y0;
  double m_Beamspot_z0;
  double m_Beamspot_x0Err;
  double m_Beamspot_y0Err;
  double m_Beamspot_z0Err;
  double m_Beamspot_WidthX;
  double m_Beamspot_WidthY;
  double m_Beamspot_WidthXErr;
  double m_Beamspot_WidthYErr;

  double m_Beamspot_dxdz;
  double m_Beamspot_dydz;
  double m_Beamspot_dxdzErr;
  double m_Beamspot_dydzErr;
  double m_Beamspot_SigmaZ0;
  double m_Beamspot_SigmaZ0Err;

  double m_Beamspot_EmittanceX;
  double m_Beamspot_EmittanceY;
  double m_Beamspot_BetaStar;

  int                 i_nVtx;

  std::auto_ptr<std::vector<double> > vd_VtxNTrks;
  std::auto_ptr<std::vector<double> > vd_VtxNRawTrks;
  std::auto_ptr<std::vector<double> > vd_VtxChi2;
  std::auto_ptr<std::vector<double> > vd_VtxNdof;
  std::auto_ptr<std::vector<double> > vd_VtxIsValid;
  std::auto_ptr<std::vector<double> > vd_VtxSumTrkPt;
  std::auto_ptr<std::vector<double> > vd_VtxSumTrkPt2;
  std::auto_ptr<std::vector<double> > vd_VtxNormalizedChi2;
  std::auto_ptr<std::vector<double> > vd_VtxX;
  std::auto_ptr<std::vector<double> > vd_VtxY;
  std::auto_ptr<std::vector<double> > vd_VtxZ;
  std::auto_ptr<std::vector<double> > vd_VtxdX;
  std::auto_ptr<std::vector<double> > vd_VtxdY;
  std::auto_ptr<std::vector<double> > vd_VtxdZ;
  std::auto_ptr<std::vector<double> > vd_Vtxd0;

  //std::vector<double> *vd_VtxNTrks;
  //std::vector<double> *vd_VtxNRawTrks;
  //std::vector<double> *vd_VtxChi2;
  //std::vector<double> *vd_VtxNdof;
  //std::vector<double> *vd_VtxIsValid;
  //std::vector<double> *vd_VtxSumTrkPt;
  //std::vector<double> *vd_VtxSumTrkPt2;
  //std::vector<double> *vd_VtxNormalizedChi2;
  //std::vector<double> *vd_VtxX;
  //std::vector<double> *vd_VtxY;
  //std::vector<double> *vd_VtxZ;
  //std::vector<double> *vd_VtxdX;
  //std::vector<double> *vd_VtxdY;
  //std::vector<double> *vd_VtxdZ;
  //std::vector<double> *vd_Vtxd0;

  //std::vector<double> vd_VtxNTrks;
  //std::vector<double> vd_VtxNRawTrks;
  //std::vector<double> vd_VtxChi2;
  //std::vector<double> vd_VtxNdof;
  //std::vector<double> vd_VtxIsValid;
  //std::vector<double> vd_VtxSumTrkPt;
  //std::vector<double> vd_VtxSumTrkPt2;
  //std::vector<double> vd_VtxNormalizedChi2;
  //std::vector<double> vd_VtxX;
  //std::vector<double> vd_VtxY;
  //std::vector<double> vd_VtxZ;
  //std::vector<double> vd_VtxdX;
  //std::vector<double> vd_VtxdY;
  //std::vector<double> vd_VtxdZ;
  //std::vector<double> vd_Vtxd0;

  void maintenance() {
    vd_VtxNTrks         ->clear();
    vd_VtxNRawTrks      ->clear();
    vd_VtxChi2          ->clear();
    vd_VtxNdof          ->clear();
    vd_VtxIsValid       ->clear();
    vd_VtxSumTrkPt      ->clear();
    vd_VtxSumTrkPt2     ->clear();
    vd_VtxNormalizedChi2->clear();
    vd_VtxX             ->clear();
    vd_VtxY             ->clear();
    vd_VtxZ             ->clear();
    vd_VtxdX            ->clear();
    vd_VtxdY            ->clear();
    vd_VtxdZ            ->clear();
    vd_Vtxd0            ->clear();
  }
};

#endif



// -*- C++ -*-
//
// Package:    AnalysisNtuplePAT
// Class:      METAnalyzerPAT
// 
/**\class METAnalyzerPAT METAnalyzerPAT.cc JSturdy/AnalysisNtuplePAT/src/METAnalyzerPAT.cc


*/
//
// Original Author:  Jared Sturdy
//         Created:  Tue Feb 2 12:11:44 PDT 2010
// $Id: METAnalyzerPAT.cc,v 1.4 2010/05/20 19:40:29 sturdy Exp $
//
//
#include "JSturdy/AnalysisNtuplePAT/interface/METAnalyzerPAT.h"

#include <TMath.h>

//________________________________________________________________________________________
METAnalyzerPAT::METAnalyzerPAT(const edm::ParameterSet& metParams, TTree* tmpAllData)
{ 
  mMETData = tmpAllData;


  debug_     = metParams.getUntrackedParameter<int>("debugMET",0);
  prefix_    = metParams.getUntrackedParameter<std::string>("prefixMET","Calo");

  // get the data tags
  doMCData_  = metParams.getUntrackedParameter<bool>("doMCMET",true);

  genTag_   = metParams.getUntrackedParameter<edm::InputTag>("genMETTag");
  metTag_   = metParams.getUntrackedParameter<edm::InputTag>("metTag");

  localPi = acos(-1.0);

  // Initialise plots [should improve in the future]
  bookTTree();
}


//________________________________________________________________________________________
METAnalyzerPAT::~METAnalyzerPAT() {
  delete mMETData;
}


//________________________________________________________________________________________
// Method called to for each event
bool METAnalyzerPAT::filter(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;

  met_result = true;
  edm::LogVerbatim("AnalysisNtuplePAT::METAnalyzerPAT") << " Start  " << std::endl;
  
  
  edm::Handle< std::vector<pat::MET> > metHandle;
  iEvent.getByLabel(metTag_, metHandle);
  if ( !metHandle.isValid() ) {
    edm::LogWarning("METEventSelector") << "No Met results for InputTag " << metTag_;
    return false;
  }

  //edm::Handle<reco::GenMETCollection> > genHandle;
  //iEvent.getByLabel(genTag_, genHandle);
  //if ( !genHandle.isValid() ) {
  //  edm::LogWarning("METEventSelector") << "No Met results for InputTag " << genTag_;
  //  return false;
  //}
  
  // sanity check on collection
  if ( metHandle->size()!=1 ) {
    edm::LogWarning("METEventSelector") << "MET collection size is "
					<< metHandle->size() << " instead of 1";
    return false;
  }

  const pat::MET& theMET = metHandle->front();
  if(theMET.genMET()!=NULL) {
    const reco::GenMET* myGenMet = theMET.genMET();
    m_METGen[0] = myGenMet->px();
    m_METGen[1] = myGenMet->py();
    m_METGen[2] = myGenMet->pz();
  }
  else{
    m_METGen[0] = -99999999;
    m_METGen[1] = -99999999;
    m_METGen[2] = -99999999;
  }
  
  double melong = theMET.e_longitudinal();
  double met    = theMET.et();
  double mex    = theMET.momentum().X();
  double mey    = theMET.momentum().Y();
  double mez    = theMET.momentum().z();
  double metphi = theMET.phi();         
  double sumet  = theMET.sumEt();       
  double metsig = theMET.mEtSig();      

  // Do the MET save for full corr no cc MET
  m_MET_Fullcorr_nocc[0]           = mex;
  m_MET_Fullcorr_nocc[1]           = mey;
  m_MET_Fullcorr_nocc[2]           = mez;
  m_METphi_Fullcorr_nocc           = metphi;
  m_METsumEt_Fullcorr_nocc         = sumet;
  m_METsignificance_Fullcorr_nocc  = metsig;

  if (debug_) std::cout<<"Number of corrections applied to MET object "<<metTag_<<"  "<<theMET.nCorrections()<<std::endl;
  // Do the MET save for no corr no cc MET
  m_MET_Nocorr_nocc[0]   = mex -   theMET.corEx(pat::MET::uncorrALL);
  m_MET_Nocorr_nocc[1]   = mey -   theMET.corEy(pat::MET::uncorrALL);
  m_METsumEt_Nocorr_nocc = sumet - theMET.corSumEt(pat::MET::uncorrALL);
  m_METpt_Nocorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrALL);
  m_METphi_Nocorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrALL);
  
  // Do the MET save for muon corr no cc MET
  // i.e., remove JES corrections
  m_MET_Muoncorr_nocc[0]   = mex -   theMET.corEx(pat::MET::uncorrJES);
  m_MET_Muoncorr_nocc[1]   = mey -   theMET.corEy(pat::MET::uncorrJES);
  m_METsumEt_Muoncorr_nocc = sumet - theMET.corSumEt(pat::MET::uncorrJES);
  m_METpt_Muoncorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrJES);
  m_METphi_Muoncorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrJES);
  
  // Do the MET save for JES corr no cc MET
  // i.e., remove muon corrections
  m_MET_JEScorr_nocc[0]   = mex -   theMET.corEx(pat::MET::uncorrMUON);
  m_MET_JEScorr_nocc[1]   = mey -   theMET.corEy(pat::MET::uncorrMUON);
  m_METsumEt_JEScorr_nocc = sumet - theMET.corSumEt(pat::MET::uncorrMUON);
  m_METpt_JEScorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrMUON);
  m_METphi_JEScorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrMUON);
  
  //
  // sanity check on collection
  //
  nUncorrMET = 2;
  nFullMET   = 3;

  // Fill the tree only if all preselection conditions are met
  return met_result;
}

//________________________________________________________________________________________
void METAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  

  // Add the branches
  //general MET information
  mMETData->Branch("nFull"+prefix_+"MET",   &nFullMET,   "nFull"+prefix_+"MET/int");
  mMETData->Branch("nUncorr"+prefix_+"MET", &nUncorrMET, "nUncorr"+prefix_+"MET/int");

  mMETData->Branch(prefix_+"MET_Fullcorr_nocc",              m_MET_Fullcorr_nocc,             prefix_+"MET_Fullcorr_nocc[nFull"+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METphi_Fullcorr_nocc",          &m_METphi_Fullcorr_nocc,          prefix_+"METphi_Fullcorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_Fullcorr_nocc",        &m_METsumEt_Fullcorr_nocc,        prefix_+"METsumEt_Fullcorr_nocc/double");
  mMETData->Branch(prefix_+"METsignificance_Fullcorr_nocc", &m_METsignificance_Fullcorr_nocc, prefix_+"METsignificance_Fullcorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_Nocorr_nocc",       m_MET_Nocorr_nocc,      prefix_+"MET_Nocorr_nocc[nUncorr"+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_Nocorr_nocc",    &m_METpt_Nocorr_nocc,    prefix_+"METpt_Nocorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_Nocorr_nocc",   &m_METphi_Nocorr_nocc,   prefix_+"METphi_Nocorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_Nocorr_nocc", &m_METsumEt_Nocorr_nocc, prefix_+"METsumEt_Nocorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_Muoncorr_nocc",       m_MET_Muoncorr_nocc,      prefix_+"MET_Muoncorr_nocc[nUncorr"+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_Muoncorr_nocc",    &m_METpt_Muoncorr_nocc,    prefix_+"METpt_Muoncorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_Muoncorr_nocc",   &m_METphi_Muoncorr_nocc,   prefix_+"METphi_Muoncorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_Muoncorr_nocc", &m_METsumEt_Muoncorr_nocc, prefix_+"METsumEt_Muoncorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_JEScorr_nocc",       m_MET_JEScorr_nocc,       prefix_+"MET_JEScorr_nocc[nUncorr"+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_JEScorr_nocc",    &m_METpt_JEScorr_nocc,     prefix_+"METpt_JEScorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_JEScorr_nocc",   &m_METphi_JEScorr_nocc,    prefix_+"METphi_JEScorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_JEScorr_nocc",  &m_METsumEt_JEScorr_nocc, prefix_+"METsumEt_JEScorr_nocc/double");
  
  mMETData->Branch(prefix_+"GenMET", &m_METGen, prefix_+"GenMET[3]/double",6400);
  
  
  edm::LogInfo("AnalysisNtuplePAT::METAnalyzerPAT") << "MET Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(METAnalyzerPAT);

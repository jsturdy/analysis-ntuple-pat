
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
// $Id: METAnalyzerPAT.cc,v 1.4 2010/04/05 15:25:37 sturdy Exp $
//
//
#include "JSturdy/AnalysisNtuplePAT/interface/METAnalyzerPAT.h"

#include <TMath.h>

//________________________________________________________________________________________
METAnalyzerPAT::METAnalyzerPAT(const edm::ParameterSet& metParams, TTree* tmpAllData)
{ 
  mMETData = tmpAllData;


  debug_     = metParams.getUntrackedParameter<int>("debugMET",0);
  prefix_    = metParams.getUntrackedParameter<std::string>("metprefix","Calo");

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
  
  if(metHandle->front().genMET()!=NULL) {
    const reco::GenMET* myGenMet = metHandle->front().genMET();
    m_METGen[0] = myGenMet->px();
    m_METGen[1] = myGenMet->py();
    m_METGen[2] = myGenMet->pz();
  }
  else{
    m_METGen[0] = -99999999;
    m_METGen[1] = -99999999;
    m_METGen[2] = -99999999;
  }
  
  // Do the MET save for full corr no cc MET
  m_MET_Fullcorr_nocc[0]           = metHandle->front().momentum().X();
  m_MET_Fullcorr_nocc[1]           = metHandle->front().momentum().Y();
  m_MET_Fullcorr_nocc[2]           = metHandle->front().momentum().z();
  m_METphi_Fullcorr_nocc           = metHandle->front().phi();
  m_METsumEt_Fullcorr_nocc         = metHandle->front().sumEt();
  m_METsignificance_Fullcorr_nocc  = metHandle->front().mEtSig();
  
  // Do the MET save for no corr no cc MET
  m_MET_Nocorr_nocc[0]   = metHandle->front().corEx(pat::MET::uncorrALL);
  m_MET_Nocorr_nocc[1]   = metHandle->front().corEy(pat::MET::uncorrALL);
  m_METpt_Nocorr_nocc    = metHandle->front().uncorrectedPt(pat::MET::uncorrALL);
  m_METphi_Nocorr_nocc   = metHandle->front().uncorrectedPhi(pat::MET::uncorrALL);
  m_METsumEt_Nocorr_nocc = metHandle->front().corSumEt(pat::MET::uncorrALL);
  
  // Do the MET save for muon corr no cc MET
  // i.e., remove JEC corrections
  m_MET_Muoncorr_nocc[0]   = metHandle->front().corEx(pat::MET::uncorrJES);
  m_MET_Muoncorr_nocc[1]   = metHandle->front().corEy(pat::MET::uncorrJES);
  m_METpt_Muoncorr_nocc    = metHandle->front().uncorrectedPt(pat::MET::uncorrJES);
  m_METphi_Muoncorr_nocc   = metHandle->front().uncorrectedPhi(pat::MET::uncorrJES);
  m_METsumEt_Muoncorr_nocc = metHandle->front().corSumEt(pat::MET::uncorrJES);
  
  // Do the MET save for JEC corr no cc MET
  // i.e., remove muon corrections
  m_MET_JECcorr_nocc[0]   = metHandle->front().corEx(pat::MET::uncorrMUON);
  m_MET_JECcorr_nocc[1]   = metHandle->front().corEy(pat::MET::uncorrMUON);
  m_METpt_JECcorr_nocc    = metHandle->front().uncorrectedPt(pat::MET::uncorrMUON);
  m_METphi_JECcorr_nocc   = metHandle->front().uncorrectedPhi(pat::MET::uncorrMUON);
  m_METsumEt_JECcorr_nocc = metHandle->front().corSumEt(pat::MET::uncorrMUON);
  
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

  mMETData->Branch(prefix_+"MET_fullcorr_nocc",              m_MET_Fullcorr_nocc,             prefix_+"MET_Fullcorr_nocc[nFull"+prefix_+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METphi_fullcorr_nocc",          &m_METphi_Fullcorr_nocc,          prefix_+"METphi_Fullcorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_fullcorr_nocc",        &m_METsumEt_Fullcorr_nocc,        prefix_+"METsumEt_Fullcorr_nocc/double");
  mMETData->Branch(prefix_+"METsignificance_Fullcorr_nocc", &m_METsignificance_Fullcorr_nocc, prefix_+"METsignificance_Fullcorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_nocorr_nocc",       m_MET_Nocorr_nocc,      prefix_+"MET_Nocorr_nocc[nUncorr"+prefix_+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_nocorr_nocc",    &m_METpt_Nocorr_nocc,    prefix_+"METpt_Nocorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_nocorr_nocc",   &m_METphi_Nocorr_nocc,   prefix_+"METphi_Nocorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_nocorr_nocc", &m_METsumEt_Nocorr_nocc, prefix_+"METsumEt_Nocorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_muoncorr_nocc",       m_MET_Muoncorr_nocc,      prefix_+"MET_Muoncorr_nocc[nUncorr"+prefix_+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_muoncorr_nocc",    &m_METpt_Muoncorr_nocc,    prefix_+"METpt_Muoncorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_muoncorr_nocc",   &m_METphi_Muoncorr_nocc,   prefix_+"METphi_Muoncorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_muoncorr_nocc", &m_METsumEt_Muoncorr_nocc, prefix_+"METsumEt_Muoncorr_nocc/double");
  
  mMETData->Branch(prefix_+"MET_jeccorr_nocc",       m_MET_JECcorr_nocc,       prefix_+"MET_JECcorr_nocc[nUncorr"+prefix_+prefix_+"MET]/double");
  mMETData->Branch(prefix_+"METpt_jeccorr_nocc",    &m_METpt_JECcorr_nocc,     prefix_+"METpt_JECcorr_nocc/double");
  mMETData->Branch(prefix_+"METphi_jeccorr_nocc",   &m_METphi_JECcorr_nocc,    prefix_+"METphi_JECcorr_nocc/double");
  mMETData->Branch(prefix_+"METsumEt_jeccorr_nocc",  &m_METsumEt_JECcorr_nocc, prefix_+"METsumEt_JECcorr_nocc/double");
  
  mMETData->Branch(prefix_+"GenMET", &m_METGen, prefix_+"GenMET[3]/double",6400);
  
  
  edm::LogInfo("AnalysisNtuplePAT::METAnalyzerPAT") << "MET Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(METAnalyzerPAT);
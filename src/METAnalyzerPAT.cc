
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
// $Id: METAnalyzerPAT.cc,v 1.10 2010/11/08 15:30:00 sturdy Exp $
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

  doMCData_  = metParams.getUntrackedParameter<bool>("doMCMET",false);
  // get the data tags
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
bool METAnalyzerPAT::filter(const edm::Event& ev, const edm::EventSetup& es)
{
  using namespace reco;
  using namespace edm;

  bool isData_ = ev.isRealData();

  maintenance();
  met_result = true;
  edm::LogVerbatim("AnalysisNtuplePAT::METAnalyzerPAT") << " Start  " << std::endl;

  edm::Handle< std::vector<pat::MET> > metHandle;
  ev.getByLabel(metTag_, metHandle);
  if ( !metHandle.isValid() ) {
    edm::LogWarning("METEventSelector") << "No Met results for InputTag " << metTag_;
    return false;
  }

  if ( metHandle->size()!=1 ) {
    edm::LogWarning("METEventSelector") << "MET collection size is "
					<< metHandle->size() << " instead of 1";
    return false;
  }
  
  const pat::MET& theMET = metHandle->front();

  
  mep4   = theMET.p4();
  double melong = theMET.e_longitudinal();
  double met    = theMET.et();
  double mex    = theMET.momentum().X();
  double mey    = theMET.momentum().Y();
  double mez    = theMET.momentum().z();
  double metphi = theMET.phi();         
  double sumet  = theMET.sumEt();       
  double metsig = theMET.mEtSig();      

  // Do the MET save for full corr no cc MET
  m_MET_Fullcorr_nocc[0]          = mex;
  m_MET_Fullcorr_nocc[1]          = mey;
  m_MET_Fullcorr_nocc[2]          = mez;
  m_METpt_Fullcorr_nocc           = met;
  m_METphi_Fullcorr_nocc          = metphi;
  m_METsumEt_Fullcorr_nocc        = sumet;
  m_METsignificance_Fullcorr_nocc = metsig;

  if (debug_>5) std::cout<<"Number of corrections applied to MET object "<<metTag_<<"  "<<theMET.nCorrections()<<std::endl;
  // Do the MET save for no corr no cc MET
  m_MET_Nocorr_nocc[0]   = theMET.corEx(pat::MET::uncorrALL);
  m_MET_Nocorr_nocc[1]   = theMET.corEy(pat::MET::uncorrALL);
  m_METsumEt_Nocorr_nocc = theMET.corSumEt(pat::MET::uncorrALL);
  m_METpt_Nocorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrALL);
  m_METphi_Nocorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrALL);
  
  // Do the MET save for muon corr no cc MET
  // i.e., remove JES corrections
  m_MET_Muoncorr_nocc[0]   = theMET.corEx(pat::MET::uncorrJES);
  m_MET_Muoncorr_nocc[1]   = theMET.corEy(pat::MET::uncorrJES);
  m_METsumEt_Muoncorr_nocc = theMET.corSumEt(pat::MET::uncorrJES);
  m_METpt_Muoncorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrJES);
  m_METphi_Muoncorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrJES);
  
  // Do the MET save for JES corr no cc MET
  // i.e., remove muon corrections
  m_MET_JEScorr_nocc[0]   = theMET.corEx(pat::MET::uncorrMUON);
  m_MET_JEScorr_nocc[1]   = theMET.corEy(pat::MET::uncorrMUON);
  m_METsumEt_JEScorr_nocc = theMET.corSumEt(pat::MET::uncorrMUON);
  m_METpt_JEScorr_nocc    = theMET.uncorrectedPt(pat::MET::uncorrMUON);
  m_METphi_JEScorr_nocc   = theMET.uncorrectedPhi(pat::MET::uncorrMUON);
  
  //
  // sanity check on collection
  //
  nUncorrMET = 2;
  nFullMET   = 3;

  //Gen level MET
  if (!isData_) {
    if (doMCData_) {
      edm::Handle<reco::GenMETCollection> genMetCaloHandle;
      ev.getByLabel("genMetCalo", genMetCaloHandle);
      if ( !genMetCaloHandle.isValid() ) {
	edm::LogWarning("METEventSelector") << "No genMetCalo results";
	return false;
      }
      const reco::GenMET& genMETCalo = genMetCaloHandle->front();
      // sanity check on collection
      if ( genMetCaloHandle->size()!=1 ) {
	edm::LogWarning("METEventSelector") << "MET collection size is "
					    << genMetCaloHandle->size() << " instead of 1";
	return false;
      }
    
      if ( genMetCaloHandle.isValid() ) {
	genCaloMETP4        = genMETCalo.p4();
	m_METGenCalo[0]     = genMETCalo.px();
	m_METGenCalo[1]     = genMETCalo.py();
	m_METGenCalo[2]     = genMETCalo.pz();
	genCaloSumEt        = genMETCalo.sumEt();
	genCaloMetSig       = genMETCalo.mEtSig();
	genCaloSignificance = genMETCalo.significance();
      }
      edm::Handle<reco::GenMETCollection> genMetTrueHandle;
      ev.getByLabel("genMetTrue", genMetTrueHandle);
      if ( !genMetTrueHandle.isValid() ) {
	edm::LogWarning("METEventSelector") << "No genMetTrue results";
	return false;
      }
    
      // sanity check on collection
      if ( genMetTrueHandle->size()!=1 ) {
	edm::LogWarning("METEventSelector") << "genMetTrue collection size is "
					    << genMetTrueHandle->size() << " instead of 1";
	return false;
      }
    
      const reco::GenMET& genMETTrue = genMetTrueHandle->front();
      if ( genMetTrueHandle.isValid() ) {
	genTrueMETP4        = genMETTrue.p4();
	m_METGenTrue[0]     = genMETTrue.px();
	m_METGenTrue[1]     = genMETTrue.py();
	m_METGenTrue[2]     = genMETTrue.pz();
	genTrueSumEt        = genMETTrue.sumEt();
	genTrueMetSig       = genMETTrue.mEtSig();
	genTrueSignificance = genMETTrue.significance();
      }
    
      ////Gen MET from the PAT MET object
      //if(theMET.genMET()!=NULL) {
      //	const reco::GenMET* myGenMet = theMET.genMET();
      //	genMETP4        = myGenMet->p4();
      //	m_METGen[0]     = myGenMet->px();
      //	m_METGen[1]     = myGenMet->py();
      //	m_METGen[2]     = myGenMet->pz();
      //	genSumEt        = myGenMet->sumEt();
      //	genMetSig       = myGenMet->mEtSig();
      //	genSignificance = myGenMet->significance();
      //}
      //else{
      //	genMETP4.SetPxPyPzE(-9999,-9999,-9999,-9999);
      //	m_METGen[0] = -9999;
      //	m_METGen[1] = -9999;
      //	m_METGen[2] = -9999;
      //	genSumEt    = -9999;
      //	genMetSig       = -9999;
      //	genSignificance = -9999;
      //}
    }
  }
  // Fill the tree only if all preselection conditions are met
  if (debug_)
    std::cout<<"Done analyzing MET"<<std::endl;
  return met_result;
}

//________________________________________________________________________________________
void METAnalyzerPAT::bookTTree() {

  std::ostringstream variables; // Container for all variables
  

  // Add the branches
  //general MET information
  mMETData->Branch("nFull"+prefix_+"MET",   &nFullMET,   "nFull"+prefix_+"MET/I");
  mMETData->Branch("nUncorr"+prefix_+"MET", &nUncorrMET, "nUncorr"+prefix_+"MET/I");

  mMETData->Branch(prefix_+"METP4",   &mep4);

  //mMETData->Branch(prefix_+"MET_Fullcorr_nocc",              m_MET_Fullcorr_nocc,             prefix_+"MET_Fullcorr_nocc[nFull"+prefix_+"MET]/D");
  //mMETData->Branch(prefix_+"METpt_Fullcorr_nocc",           &m_METpt_Fullcorr_nocc,           prefix_+"METpt_Fullcorr_nocc/D");
  //mMETData->Branch(prefix_+"METphi_Fullcorr_nocc",          &m_METphi_Fullcorr_nocc,          prefix_+"METphi_Fullcorr_nocc/D");
  mMETData->Branch(prefix_+"METsumEt_Fullcorr_nocc",        &m_METsumEt_Fullcorr_nocc,        prefix_+"METsumEt_Fullcorr_nocc/D");
  mMETData->Branch(prefix_+"METsignificance_Fullcorr_nocc", &m_METsignificance_Fullcorr_nocc, prefix_+"METsignificance_Fullcorr_nocc/D");
  
  mMETData->Branch(prefix_+"MET_Nocorr_nocc",       m_MET_Nocorr_nocc,      prefix_+"MET_Nocorr_nocc[nUncorr"+prefix_+"MET]/D");
  mMETData->Branch(prefix_+"METpt_Nocorr_nocc",    &m_METpt_Nocorr_nocc,    prefix_+"METpt_Nocorr_nocc/D");
  mMETData->Branch(prefix_+"METphi_Nocorr_nocc",   &m_METphi_Nocorr_nocc,   prefix_+"METphi_Nocorr_nocc/D");
  mMETData->Branch(prefix_+"METsumEt_Nocorr_nocc", &m_METsumEt_Nocorr_nocc, prefix_+"METsumEt_Nocorr_nocc/D");
  
  mMETData->Branch(prefix_+"MET_Muoncorr_nocc",       m_MET_Muoncorr_nocc,      prefix_+"MET_Muoncorr_nocc[nUncorr"+prefix_+"MET]/D");
  mMETData->Branch(prefix_+"METpt_Muoncorr_nocc",    &m_METpt_Muoncorr_nocc,    prefix_+"METpt_Muoncorr_nocc/D");
  mMETData->Branch(prefix_+"METphi_Muoncorr_nocc",   &m_METphi_Muoncorr_nocc,   prefix_+"METphi_Muoncorr_nocc/D");
  mMETData->Branch(prefix_+"METsumEt_Muoncorr_nocc", &m_METsumEt_Muoncorr_nocc, prefix_+"METsumEt_Muoncorr_nocc/D");
  
  mMETData->Branch(prefix_+"MET_JEScorr_nocc",       m_MET_JEScorr_nocc,      prefix_+"MET_JEScorr_nocc[nUncorr"+prefix_+"MET]/D");
  mMETData->Branch(prefix_+"METpt_JEScorr_nocc",    &m_METpt_JEScorr_nocc,    prefix_+"METpt_JEScorr_nocc/D");
  mMETData->Branch(prefix_+"METphi_JEScorr_nocc",   &m_METphi_JEScorr_nocc,   prefix_+"METphi_JEScorr_nocc/D");
  mMETData->Branch(prefix_+"METsumEt_JEScorr_nocc", &m_METsumEt_JEScorr_nocc, prefix_+"METsumEt_JEScorr_nocc/D");
  
  if (doMCData_) {
    //mMETData->Branch(prefix_+"GenMET",          &m_METGen,        prefix_+"GenMET[3]/D");
    //mMETData->Branch(prefix_+"GenSumEt",        &genSumEt,        prefix_+"GenSumEt/D");
    //mMETData->Branch(prefix_+"GenMetSig",       &genMetSig,       prefix_+"GenMetSig/D");
    //mMETData->Branch(prefix_+"GenSignificance", &genSignificance, prefix_+"GenSignificance/D");
    //mMETData->Branch(prefix_+"GenMETP4",        &genMETP4);
    
    mMETData->Branch("GenMETTrue",           m_METGenTrue,        "GenMETTrue[3]/D");
    mMETData->Branch("GenTrueSumEt",        &genTrueSumEt,        "GenTrueSumEt/D");
    mMETData->Branch("GenTrueMetSig",       &genTrueMetSig,       "GenTrueMetSig/D");
    mMETData->Branch("GenTrueSignificance", &genTrueSignificance, "GenTrueSignificance/D");
    mMETData->Branch("GenTrueMETP4",        &genTrueMETP4);
    
    mMETData->Branch("GenMETCalo",           m_METGenCalo,        "GenMETCalo[3]/D");
    mMETData->Branch("GenCaloSumEt",        &genCaloSumEt,        "GenCaloSumEt/D");
    mMETData->Branch("GenCaloMetSig",       &genCaloMetSig,       "GenCaloMetSig/D");
    mMETData->Branch("GenCaloSignificance", &genCaloSignificance, "GenCaloSignificance/D");
    mMETData->Branch("GenCaloMETP4",        &genCaloMETP4);
  }
  
  edm::LogInfo("AnalysisNtuplePAT::METAnalyzerPAT") << "MET Ntuple variables " << variables.str();
  
}


//_______________________________________________________________________________________
// Define this as a plug-in
//#include "FWCore/Framework/interface/MakerMacros.h"
//DEFINE_FWK_MODULE(METAnalyzerPAT);

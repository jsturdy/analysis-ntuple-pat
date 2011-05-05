#define DiJetStudy_cxx
#include "DiJetStudy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TStopwatch.h>

using namespace std;

DiJetStudy::DiJetStudy(TTree *allTree, //TTree *eventTree,
		       TTree *jetTree, TTree *metTree, 
		       TTree *leptonTree, TTree *photonTree, 
		       TTree *triggerTree, TTree *vertexTree, TTree *genTree,
		       std::string* sampleList, std::string* triggerList, std::string* cutFile,
		       const bool &isData,
		       const std::string &jetPrefix, const std::string &metPrefix,
		       const std::string &lepPrefix, const std::string &phtPrefix,
		       const std::string &sampleKey)
  :ntupleAnalysisPAT(allTree, //eventTree,
		     jetTree, metTree, 
		     leptonTree, photonTree, 
		     triggerTree, vertexTree, genTree,
		     sampleList, triggerList, cutFile, 
		     isData, 
		     jetPrefix, metPrefix,
		     lepPrefix, phtPrefix, 
		     sampleKey)
{
  cout<<"Executing DiJetStudy::DiJetStudy()"<<endl;
  sampleList_ = sampleList;
  sampleInfo sampVals = ReadInCrossSections(sampleList_,sampleKey);

  /*
  std::cout<<std::setw(15)<<"all"<<std::setw(15)<<
    "jet"<<std::setw(15)<<
    "met"<<std::setw(15)<<
    "lepton"<<std::setw(15)<<
    "photon"<<std::setw(15)<<
    "trigger"<<std::setw(15)<<
    "vertex"<<std::setw(15)<<
    "gen"<<std::setw(15)<<
    std::endl;

  std::cout<<std::setw(15)<<std::hex<<allTree<<std::setw(15)<<
    jetTree<<std::setw(15)<<
    metTree<<std::setw(15)<<
    leptonTree<<std::setw(15)<<
    photonTree<<std::setw(15)<<
    triggerTree<<std::setw(15)<<
    vertexTree<<std::setw(15)<<
    genTree<<std::setw(15)<<
    std::dec<<std::endl;
  */
  if (isData) {
    sampVals.xs      = 1.;
    sampVals.eff     = 1.;
    sampVals.numGen  = 1.;
  }
  
  sampVals.lumi = 1.;
  sampVals.scale = 1.;

  if (!isData)
    sampVals.scale = sampVals.lumi * sampVals.xs * sampVals.eff / sampVals.numGen;

  scale_            = sampVals.scale;
  luminosity_       = sampVals.lumi;
  cross_section_    = sampVals.xs;
  efficiency_       = sampVals.eff;
  generated_events_ = sampVals.numGen;

  cout<<"sample:"<<sampleKey<<endl;
  cout<<"lumi:  "<<sampVals.lumi<<endl;
  cout<<"xs:    "<<sampVals.xs<<endl;
  cout<<"eff:   "<<sampVals.eff<<endl;
  cout<<"gen:   "<<sampVals.numGen<<endl;
  cout<<"scale: "<<sampVals.scale<<endl;

  //Read in the trigger information
  triggerList_ = triggerList;
  ReadInTriggers();
  //read in the cuts
  cutFile_     = cutFile;
  ReadInCuts();
  setCuts();

  
}
DiJetStudy::~DiJetStudy()
{
  
  delete dijetVariables;
  dijetVariables = 0;
}

void DiJetStudy::printOutEventInfo()
{
  if (isData_) {
    cout<<"Event info for Run: "<<setw(8)<<Run<<endl
	<<" Lumi Section: "<<setw(5)<<LumiSection<<endl
	<<" Event: "<<setw(12)<<Event<<endl
	<<"passExclusive:"<<setw(2)<<passExclusiveDiJets
	<<"    passInclusive:"<<setw(2)<<passInclusiveDiJets<<endl<<endl;
    
    cout<<setw(8)<<"NJets"<<setw(8)<<"nGood"<<setw(8)<<"nBad"
	<<setw(8)<<"good10"<<setw(8)<<"good30"<<setw(8)<<"good50"
	<<setw(8)<<"bad10"<<setw(8)<<"bad30"<<setw(8)<<"bad50"<<setw(8)<<endl
	<<setw(8)<<mNJets<<setw(8)<<mNGoodJets<<setw(8)<<mNBadJets
	<<setw(8)<<mNGoodJets10<<setw(8)<<mNGoodJets30<<setw(8)<<mNGoodJets50
	<<setw(8)<<mNBadJets10<<setw(8)<<mNBadJets30<<setw(8)<<mNBadJets50<<endl<<endl;

    cout<<setw(5)<<"Jet"<<setw(12)<<"Pt"<<setw(12)<<"Eta"<<setw(12)<<"Phi"<<endl
	<<setw(5)<<"1"<<setw(12)<<JetP4->at(0).Pt()<<setw(12)<<JetP4->at(0).Eta()<<setw(12)<<JetP4->at(0).Phi()<<endl
	<<setw(5)<<"2"<<setw(12)<<JetP4->at(1).Pt()<<setw(12)<<JetP4->at(1).Eta()<<setw(12)<<JetP4->at(1).Phi()<<endl;
    if (mNJets>2)
      cout<<setw(5)<<"3"<<setw(12)<<JetP4->at(2).Pt()<<setw(12)<<JetP4->at(2).Eta()<<setw(12)<<JetP4->at(2).Phi()<<endl;
    if (mNJets>3)
      cout<<setw(5)<<"4"<<setw(12)<<JetP4->at(3).Pt()<<setw(12)<<JetP4->at(3).Eta()<<setw(12)<<JetP4->at(3).Phi()<<endl;
    if (mNJets>4)
      cout<<setw(5)<<"5"<<setw(12)<<JetP4->at(4).Pt()<<setw(12)<<JetP4->at(4).Eta()<<setw(12)<<JetP4->at(4).Phi()<<endl;
    cout<<endl;
    cout<<setw(12)<<"MET"<<setw(12)<<"MET Phi"<<setw(12)<<"SumEt"<<endl
	<<setw(12)<<METP4->Pt()<<setw(12)<<METP4->Phi()<<setw(12)<<METsumEt_Fullcorr<<endl<<endl;
    cout<<setw(12)<<"HT"<<setw(12)<<"MHT"<<setw(12)<<"dPhi*"<<endl
	<<setw(12)<<mHT<<setw(12)<<mMHT<<setw(12)<<mDPhiStar<<endl<<endl;
    cout<<setw(12)<<"HT(ID)"<<setw(12)<<"MHT(ID)"<<setw(12)<<"dPhi*(ID)"<<endl
	<<setw(12)<<mIDHT<<setw(12)<<mIDMHT<<setw(12)<<mIDDPhiStar<<endl<<endl;
  }
}
void DiJetStudy::Loop(const std::string &outputfile,
		      const double &cutJet1, const double &cutJet2,
		      const double &cutMET,
		      const bool   &debug)
{
  bool debug_ = debug;
  if (debug_)
    printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  \n",
	   outputfile.c_str(), cutJet1, cutJet2, cutMET);
  
  //gROOT->ProcessLine(".L /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/ntuplePragmas.so");
  gROOT->ProcessLine(".L ntuplePragmas.so");
  jet1_minpt = cutJet1;
  jet2_minpt = cutJet2;
  cut_met    = cutMET;

  outfilename_ = outputfile;
  
  //luminosity_       = lum;
  //cross_section_    = xs;
  //efficiency_       = eff;
  //generated_events_ = numGen;
  //
  //scale_       = luminosity_ * cross_section_ * efficiency_ / generated_events_;
  cout<<"Scale factor is: "<<scale_<<endl;
  mScaleFactor = scale_;

  if (debug_)
    printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  xs: %4.6f,  eff: %4.6f  num: %4.6f  scale: %4.6f\n",
	   outfilename_.c_str(), jet1_minpt, jet2_minpt, cut_met, luminosity_, cross_section_, efficiency_, generated_events_, scale_);
  //printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  scale: %4.6f\n",outfilename_.c_str(), jet1_minpt, jet2_minpt, cut_met, luminosity_, scale_);
  if (allChain == 0) return;

  char tmpfile[128];
  sprintf(tmpfile,"%s.root",outfilename_.c_str());
  TFile *file = new TFile(tmpfile,"RECREATE");
  file->cd();
  initializeTree();

  if (debug_)
    cout<<"getting the entries from the trees - "<<endl;
  //Long64_t nentries = allChain->GetEntriesFast();
  Long64_t nentries = allChain->GetEntries();
  //if (debug_)
  //  cout<<" done with allChain:"<<nentries<<" entries"<<endl;
  //Long64_t jentries = jetChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with jetChain:"<<jentries<<" entries"<<endl;
  //Long64_t mentries = metChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with metChain:"<<mentries<<" entries"<<endl;
  //Long64_t lentries = leptonChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with lepChain:"<<lentries<<" entries"<<endl;
  //Long64_t pentries = photonChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with phtChain:"<<pentries<<" entries"<<endl;
  //Long64_t tentries = triggerChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with trgChain:"<<tentries<<" entries"<<endl;
  //Long64_t ventries = vertexChain->GetEntriesFast();
  //if (debug_)
  //  cout<<" done with vertexChain:"<<ventries<<" entries"<<endl;
  
  mTotalEvents = 0;
  
  TStopwatch tsw ;
  //int tenthpcount(1) ;
  int onepcount(1) ;
  int tenpcount(1) ;
  
  Long64_t nbytes = 0, nb = 0;
  if ( debug_ ) {
    //nentries = 1642950 ;
    //nentries = 1;
    nentries = 1000;
  }
  cout<<nentries<<" entries to process"<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //for (Long64_t jentry=0; jentry<100;jentry++) {
    //Timing information
    if ( jentry==0) { tsw.Start() ; cout << "." << flush ; }
    if ((jentry*10)/nentries == tenpcount ) {
      tsw.Stop() ;
      Double_t time = tsw.RealTime() ;
      tsw.Start(kFALSE) ;
      Double_t finTime(0.) ;
      Double_t frac = (jentry*1.0)/(nentries*1.0) ;
      if (frac>0) finTime = time / frac - time ;
      Double_t finMin = finTime / 60. ;
      cout << tenpcount*10 << "% done.  "
	   << "t = " << setw(7) << time
	   << " projected finish =" << setw(7) << finTime << " s ("
	   << setprecision(1)
	   << finMin << " min).   "
	   << endl ;
      tenpcount++ ;
    } else if ( (jentry*100)/nentries == onepcount ) {
      //tsw.Stop() ;
      //Double_t time = tsw.RealTime() ;
      //tsw.Start(kFALSE) ;
      //Double_t finTime(0.) ;
      //Double_t frac = (jentry*1.0)/(nentries*1.0) ;
      //if (frac>0) finTime = time / frac - time ;
      //Double_t finMin = finTime / 60. ;
      //cout << onepcount*1 << "% done.  "
      //   << "t = " << setw(7) << time
      //   << " projected finish =" << setw(7) << finTime << " s ("
      //   << setprecision(1)
      //   << finMin << " min).   "
      //   << endl ;
      cout << "." ;
      cout << flush ;
      onepcount++ ;
    }// else if ( (jentry*1000)/nentries == tenthpcount ) {
    //  cout << "." ;
    //  cout << flush ;
    //  onepcount++ ;
    //}
    ///
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    //nb = fChain->GetEntry(jentry); nbytes += nb;
    nb = this->GetEntry(jentry); nbytes += nb;
    
    ++mTotalEvents;
    //++totalcounter;

    mRun = Run;
    mLS  = LumiSection;
    mEvent = Event;
    
    if (doSusyScan) {
      mSusyScanA0 =           susyScanA0;
      mSusyScanM0 =           susyScanM0;
      mSusyScanM12 =          susyScanM12;
      mSusyScanMu =           susyScanMu;
      mSusyScanRun =          susyScanRun;
      mSusyScantanbeta =      susyScantanbeta;
      mSusyScanCrossSection = susyScanCrossSection;
    }
    
    else {
      mSusyScanA0 =           -999;
      mSusyScanM0 =           -999;
      mSusyScanM12 =          -999;
      mSusyScanMu =           -999;
      mSusyScanRun =          -999;
      mSusyScantanbeta =      -999;
      mSusyScanCrossSection = -999;
    }

    int nJets  = NJets;
    int nElecs = ElecN;
    int nMuons = MuonN;
    int nTaus  = TauN;
    int nPhots = PhotN;
    int nVtxs  = nVtx;
    
    
    getVertexInfo(nVtxs);

    getMETInfo();

    getJetInfo(nJets);

    getHTMHTInfo();

    getLeptonInfo(nElecs,nMuons,nTaus);
    
    getPhotonInfo(nPhots);

    getTriggerInfo();

    getSelectionInfo(nJets);


    if ((passExclusiveAllButMET || passInclusiveAllButMET) && passMET) 
      printOutEventInfo();

    ///////////////////////
    dijetVariables->Fill();
    ///////////////////////
  }
  cout<<"Done looping events "<<endl;


  // scale histograms to desired values

  dijetVariables->Write();
  file->cd();
  file->Write();
}


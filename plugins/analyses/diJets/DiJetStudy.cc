#define DiJetStudy_cxx
#include "DiJetStudy.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#define NSTEPS       4
#define NUMHISTOS   26
#define NUMTESTHIST 13

DiJetStudy::DiJetStudy(TTree *tree, std::string* sampleList, std::string* triggerList, std::string* cutFile, const bool &isData, const std::string &jetPrefix, const std::string &metPrefix, const std::string &lepPrefix, const std::string &phtPrefix, const std::string &sampleKey)
  :ntupleAnalysisPAT(tree, sampleList, triggerList, cutFile, isData, jetPrefix, metPrefix, lepPrefix, phtPrefix, sampleKey)
{
  std::cout<<"Executing DiJetStudy::DiJetStudy()"<<std::endl;
  sampleList_ = sampleList;
  sampleInfo sampVals = ReadInEfficiencies(sampleList_,sampleKey);

  if (isData) {
    sampVals.xs      = 1.;
    sampVals.eff     = 1.;
    sampVals.numGen  = 1.;
  }
  
  sampVals.lumi = 35.;
  sampVals.scale = 1.;

  if (!isData)
    sampVals.scale = sampVals.lumi * sampVals.xs * sampVals.eff / sampVals.numGen;

  scale_            = sampVals.scale;
  luminosity_       = sampVals.lumi;
  cross_section_    = sampVals.xs;
  efficiency_       = sampVals.eff;
  generated_events_ = sampVals.numGen;

  std::cout<<"sample:"<<sampleKey<<std::endl;
  std::cout<<"lumi:  "<<sampVals.lumi<<std::endl;
  std::cout<<"xs:    "<<sampVals.xs<<std::endl;
  std::cout<<"eff:   "<<sampVals.eff<<std::endl;
  std::cout<<"gen:   "<<sampVals.numGen<<std::endl;
  std::cout<<"scale: "<<sampVals.scale<<std::endl;

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
}

void DiJetStudy::printOutEventInfo()
{
  if (isData_) {
    std::cout<<"Event info for Run: "<<std::setw(8)<<Run
	     <<" Lumi Section: "<<std::setw(5)<<LumiSection
	     <<" Event: "<<std::setw(12)<<Event<<std::endl;
    std::cout<<"NJets = "<<std::setw(5)<<NJets<<std::endl;
    std::cout<<"\nLeading Jet:"<<std::endl;
    std::cout<<"\tPt: " <<std::setw(5)<<JetP4->at(0).Pt();
    std::cout<<"  -  Eta: "<<std::setw(5)<<JetP4->at(0).Eta();
    std::cout<<"  -  Phi: "<<std::setw(5)<<JetP4->at(0).Phi()<<std::endl;
    std::cout<<"\nSecond Jet:"<<std::endl;
    std::cout<<"\tPt: " <<std::setw(5)<<JetP4->at(1).Pt();
    std::cout<<"  -  Eta: "<<std::setw(5)<<JetP4->at(1).Eta();
    std::cout<<"  -  Phi: "<<std::setw(5)<<JetP4->at(1).Phi()<<std::endl;
    std::cout<<"\nMET: "   <<std::setw(5)<<METP4->Pt();
    std::cout<<"  -  SumEt: " <<std::setw(5)<<METsumEt_Fullcorr<<std::endl;
  }
}
//void DiJetStudy::Loop(std::string outputfile, double lum, double xs, double eff, double numGen, double cutJet1, double cutJet2, double cutMET)
//void DiJetStudy::Loop(const std::string &outputfile, const double &cutJet1, const double &cutJet2, const double &cutMET)
void DiJetStudy::Loop(const std::string &outputfile, const double &cutJet1, const double &cutJet2, const double &cutMET, const bool& strictDiJets, const int& triggerPaths)
//void DiJetStudy::Loop(const std::string &outputfile,  const double lum,  const double scale, const double &cutJet1, const double &cutJet2, const double &cutMET)
{
  bool debug_ = false;
  printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  strictDiJets:  %d  triggerPaths:  %d\n",
	 outputfile.c_str(), cutJet1, cutJet2, cutMET, strictDiJets, triggerPaths);
  //printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  xs: %4.6f,  eff: %4.6f  num: %4.6f\n",
	 // outputfile.c_str(), cutJet1, cutJet2, cutMET, lum, xs, eff, numGen);
  //printf("received args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  scale: %4.6f\n",outputfile.c_str(), cutJet1, cutJet2, cutMET, lum, scale);
  
  //gROOT->ProcessLine(".L /uscms_data/d2/sturdy07/SUSY/CMSSW_3_8_7/src/JSturdy/AnalysisNtuplePAT/plugins/analyses/diJets/ntuplePragmas.so");
  gROOT->ProcessLine(".L ntuplePragmas.so");
  std::string analysisVer = "met";
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
  std::cout<<"Scale factor is: "<<scale_<<std::endl;

  printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  xs: %4.6f,  eff: %4.6f  num: %4.6f  scale: %4.6f\n",
	 outfilename_.c_str(), jet1_minpt, jet2_minpt, cut_met, luminosity_, cross_section_, efficiency_, generated_events_, scale_);
  //printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  scale: %4.6f\n",outfilename_.c_str(), jet1_minpt, jet2_minpt, cut_met, luminosity_, scale_);
  if (fChain == 0) return;

  char tmpfile[128];
  sprintf(tmpfile,"%s.root",outfilename_.c_str());
  TFile *file = new TFile(tmpfile,"RECREATE");
  file->cd();
   
  Long64_t nentries = fChain->GetEntriesFast();
   
  TH1D *h_selections[2];
  TH1D *h_Nelec[4], *h_Ngoodelec[4], *h_Nmuon[4], *h_Ngoodmuon[4];
   
  TH1D *h_Njets[4][2], *h_jet1eta[4], *h_jet2eta[4];
  TH1D *h_elecEta[4], *h_muonEta[4];
   
  TH1D *h_jet1emfrac[4], *h_jet2emfrac[4], *h_jetFem[4];
  TH1D *h_jet12dphi[4], *h_jet1metdphi[4], *h_jet2metdphi[4];
  TH1D *h_dphistar[4];
  // bins of 50 GeV
  TH1D *h_HT[4], *h_Meff[4];
  // bins of 50 GeV
  TH1D *h_MET[4], *h_jet1et[4], *h_jet2et[4], *h_jetallet[4];
  TH1D *h_MHT[4], *h_MT[2], *h_Minv[2], *h_SumEt[2];
  // bins of 25 and 1 GeV depending on plot
  TH1D *h_elecEt[4], *h_muonEt[4];
  //only plot these for pre cuts and post cuts
  //TH1D *h_jet1phi[2], *h_jet2phi[2], *h_METphi[2];
  TH1D *h_counters[4];

  char histtitle[NUMHISTOS][128];
  std::string histname[NUMHISTOS] = {
    "01_jet1et",
    "02_jet2et",
    "03_jetallet",
    "11_MET",
    "12_HT",
    "13_MHT",
    "14_Meff",
    "21_jet1metdphi",
    "22_jet2metdphi",
    "23_jet12dphi",
    "24_dphistar",
    "30_Njets",
    "31_Ngoodjets",
    "32_jet1eta",
    "33_jet2eta",
    "41_jetFem",
    "42_jet1emfrac",
    "43_jet2emfrac",
    "51a_Nelecs",
    "51b_Ngoodelecs",
    "52a_Nmuons",
    "52b_Ngoodmuons",
    "53_eleceta",
    "54_muoneta",
    "55_elecet",
    "56_muonet"
  };
  
  char plottitle[NUMHISTOS][128];
  std::string plotname[NUMHISTOS] = {
    jetPrefix_+" E_{T}^{J_{1}}",                               
    jetPrefix_+" E_{T}^{J_{2}}",
    jetPrefix_+" E_{T}^{J_{3+}}",
    metPrefix_+" #slash E_{T}",
    jetPrefix_+" H_{T}",
    jetPrefix_+" #slash H_{T}",
    jetPrefix_+" M_{eff}",
    "#Delta#phi(J_{1},#slash E_{T})",
    "#Delta#phi(J_{2},#slash E_{T})",
    "#Delta#phi(J_{1}, J_{2})",
    "#Delta#phi*",
    jetPrefix_+" N_{jets}",
    jetPrefix_+" N^{good}_{jets}",
    jetPrefix_+" #eta^{J_{1}}",
    jetPrefix_+" #eta^{J_{2}} ",
    jetPrefix_+" E^{J_{3+}}_{EM}/E^{J_{3+}}_{tot}",
    jetPrefix_+" E^{J_{1}}_{EM}/E^{J_{1}}_{tot}",
    jetPrefix_+" E^{J_{2}}_{EM}/E^{J_{2}}_{tot}",
    lepPrefix_+" N_{e}",
    lepPrefix_+" N^{good}_{e}",
    lepPrefix_+" N_{#mu}",
    lepPrefix_+" N^{good}_{#mu}",
    lepPrefix_+" #eta^{e}",
    lepPrefix_+" #eta^{#mu}",
    lepPrefix_+" E_{T}^{e}",
    lepPrefix_+" E_{T}^{#mu}"
  };

  
  //std::string histpre[4] = {"h_pre_cuts_","h_individual_cuts_","h_N1_cuts_","h_post_cuts_"};
  std::string histpre[4] = {"h_pre_cuts_","h_previous_cuts_","h_N1_cuts_","h_post_cuts_"};
  
  double bins[4][NUMHISTOS] = {
    //pre cuts
    // j1et,  j2et,  jallet, met,   ht ,   mht,   meff
    {2500., 2500., 1000.,  2000., 5000., 2000., 5000., 
     // j1mdp,   j2mdp,   j12dp,  dphistar   njets, ngood
     M_PI, M_PI, M_PI, M_PI, 20.,   20.,
     // jetetmultiplier, dummy values
     1.,   0.,   0.,   0.,   0.,
     // nelec, nmuon, dum6, dum7, elecet, muonet
     15.,   15.,   0.,   0.,   1500.,  1500.},
    
    /*
    //individual cuts
    // j1et,  j2et,  jallet, met,   ht ,   mht,   meff
    {2500., 2500., 100.,  5000., 5000., 2000., 5000.,
    // j1mdp,   j2mdp,   j12dp,   dphistar   njets, ngood
    M_PI, M_PI, M_PI, M_PI, 20.,   20.,
    // jetetmultiplier, dummy values
    10.,   0.,   0.,   0.,   0.,
    // nelec, nmuon, dum6, dum7, elecet, muonet
    15.,   15.,   0.,   0.,   2500.,  2500.},
    */
    
    //sequential cuts
    // j1et,  j2et,  jallet, met,   ht ,   mht,   meff
    {2500., 2500., 1000.,  2000., 5000., 2000., 5000.,
     // j1mdp,   j2mdp,   j12dp,   dphistar   njets, ngood
     M_PI, M_PI, M_PI, M_PI, 20.,   20.,
     // jetetmultiplier, dummy values
     1.,   0.,   0.,   0.,   0.,
     // nelec, nmuon, dum6, dum7, elecet, muonet
     15.,   15.,   0.,   0.,   1500.,  1500.},
    
    //N-1 cuts
    // j1et,  j2et,  jallet, met,   ht ,   mht,   meff
    {1500., 1500., 500.,  1500., 5000., 1500., 5000.,
     // j1mdp,   j2mdp,   j12dp,   dphistar   njets, ngood
     M_PI, M_PI, M_PI, M_PI, 20.,   20.,
     // jetetmultiplier, dummy values
     1.,   0.,   0.,   0.,   0.,
     // nelec, nmuon, dum6, dum7, elecet, muonet
     15.,   15.,   0.,   0.,   500.,  500.},
    
    //post cuts
    // j1et,  j2et,  jallet, met,   ht ,   mht,   meff
    {1500., 1500., 100.,  1500., 2500., 1500., 3000.,
     // j1mdp,   j2mdp,   j12dp,   dphistar   njets, ngood
     M_PI, M_PI, M_PI, M_PI, 20.,   20.,
     // jetetmultiplier, dummy values
     10.,   0.,   0.,   0.,   0.,
     // nelec, nmuon, dum6, dum7, elecet, muonet
     15.,   15.,   0.,   0.,   500.,  500.}};
  
  double binsize = 0.;

  for (int tt = 0; tt < 4; ++tt) {
    for (int hh = 0; hh < NUMHISTOS; ++hh) {
      sprintf(histtitle[hh],"%s%s",histpre[tt].c_str(),histname[hh].c_str());
      sprintf(plottitle[hh],"%s",plotname[hh].c_str());
    }
    //for (int hh = 0; hh < NUMTESTHIST; ++hh) {
    //  sprintf(testhisttitle[hh][0],"%s%s",histpre[tt].c_str(),testhistname[hh][0].c_str());
    //  sprintf(testplottitle[hh][0],"%s",  testplotname[hh][0].c_str());
    //  sprintf(testhisttitle[hh][1],"%s%s",histpre[tt].c_str(),testhistname[hh][1].c_str());
    //  sprintf(testplottitle[hh][1],"%s",  testplotname[hh][1].c_str());
    //}
    
    binsize = 25.;
    if (tt > 1)
      binsize = 5.;// bins of 5 GeV for N-1/post
    h_jetallet[tt]    = new TH1D(histtitle[2],plottitle[2],static_cast<int>(bins[tt][2]/binsize),0.,bins[tt][2]);

    binsize = 25.; // bins of 25 GeV
    h_jet1et[tt]  = new TH1D(histtitle[0],plottitle[0],static_cast<int>(bins[tt][0]/binsize),0.,bins[tt][0]);
    h_jet2et[tt]  = new TH1D(histtitle[1],plottitle[1],static_cast<int>(bins[tt][1]/binsize),0.,bins[tt][1]);

    binsize = 25.; // bins of 25 GeV
    h_MET[tt]     = new TH1D(histtitle[3],plottitle[3],static_cast<int>(bins[tt][3]/binsize),0.,bins[tt][3]);

    h_MHT[tt]     = new TH1D(histtitle[5],plottitle[5],static_cast<int>(bins[tt][5]/binsize),0.,bins[tt][5]);

    binsize = 50.; // bins of 50 GeV
    //binsize = 100.; // bins of 100 GeV
    h_HT[tt]      = new TH1D(histtitle[4],plottitle[4],static_cast<int>(bins[tt][4]/binsize),0.,bins[tt][4]);

    h_Meff[tt]    = new TH1D(histtitle[6],plottitle[6],static_cast<int>(bins[tt][6]/binsize),0.,bins[tt][6]);

    // fixed number of bins
    h_jet1metdphi[tt] = new TH1D(histtitle[7],plottitle[7],50,0.,bins[tt][7]);
    h_jet2metdphi[tt] = new TH1D(histtitle[8],plottitle[8],50,0.,bins[tt][8]);
    h_jet12dphi[tt]   = new TH1D(histtitle[9],plottitle[9],50,0.,bins[tt][9]);

    h_dphistar[tt]    = new TH1D(histtitle[10],plottitle[10],25,0.,bins[tt][10]);

    h_Njets[tt][0]  = new TH1D(histtitle[11],plottitle[11],static_cast<int>(bins[tt][11]),0.,bins[tt][11]);
    h_Njets[tt][1]  = new TH1D(histtitle[12],plottitle[12],static_cast<int>(bins[tt][12]),0.,bins[tt][12]);
    h_jet1eta[tt]   = new TH1D(histtitle[13],plottitle[13],50,-5.,5.);
    h_jet2eta[tt]   = new TH1D(histtitle[14],plottitle[14],50,-5.,5.);

    h_jetFem[tt]     = new TH1D(histtitle[15],plottitle[15],25,0.,1.);
    h_jet1emfrac[tt] = new TH1D(histtitle[16],plottitle[16],25,0.,1.);
    h_jet2emfrac[tt] = new TH1D(histtitle[17],plottitle[17],25,0.,1.);

    //lepton plots
    h_Nelec[tt]     = new TH1D(histtitle[18],plottitle[18],static_cast<int>(bins[tt][18]),0.,bins[tt][18]);
    h_Ngoodelec[tt] = new TH1D(histtitle[19],plottitle[19],static_cast<int>(bins[tt][18]),0.,bins[tt][18]);
    h_Nmuon[tt]     = new TH1D(histtitle[20],plottitle[20],static_cast<int>(bins[tt][19]),0.,bins[tt][19]);
    h_Ngoodmuon[tt] = new TH1D(histtitle[21],plottitle[21],static_cast<int>(bins[tt][19]),0.,bins[tt][19]);
    h_elecEta[tt]   = new TH1D(histtitle[22],plottitle[22],50,-5.,5.);
    h_muonEta[tt]   = new TH1D(histtitle[23],plottitle[23],50,-5.,5.);
    
    binsize = 25.;// bins of 25 GeV 
    if (tt > 1)
      binsize = 5.;
    h_elecEt[tt]   = new TH1D(histtitle[24],plottitle[24],static_cast<int>(bins[tt][22]/binsize),0.,bins[tt][22]);
    h_muonEt[tt]   = new TH1D(histtitle[25],plottitle[25],static_cast<int>(bins[tt][23]/binsize),0.,bins[tt][23]);
  }
  //Counters for selections
  for (int tt = 0; tt < 4; ++tt) {
    sprintf(histtitle[tt],"%sevents",histpre[tt].c_str());
    sprintf(plottitle[tt],"Events Passing Cuts");
    h_counters[tt] = new TH1D(histtitle[tt],plottitle[tt],25,0,25);
  }

  //pre cuts
  //h_jet1phi[0] = new TH1D("h_pre_cuts_9_jet1phi","",100,-M_PI,M_PI);
  //h_jet2phi[0] = new TH1D("h_pre_cuts_9_jet2phi","",100,-M_PI,M_PI);
  //h_METphi[0]  = new TH1D("h_pre_cuts_9_METphi", "",100,-M_PI,M_PI);
  h_MT[0]      = new TH1D("h_pre_cuts_9_MT",     "M_{T}",3000/50,0,3000);
  h_Minv[0]    = new TH1D("h_pre_cuts_9_Minv",   "M_{inv}",3000/50,0,3000);
  char myname[128];
  sprintf(myname,"%s #SigmaE_{T}",metPrefix_.c_str());
  h_SumEt[0]   = new TH1D("h_pre_cuts_9_SumEt",  myname,2500/50,0,2500);
  //post cuts
  //h_jet1phi[1] = new TH1D("h_post_cuts_9_jet1phi","",100,-M_PI,M_PI);
  //h_jet2phi[1] = new TH1D("h_post_cuts_9_jet2phi","",100,-M_PI,M_PI);
  //h_METphi[1]  = new TH1D("h_post_cuts_9_METphi", "",100,-M_PI,M_PI);
  h_MT[1]      = new TH1D("h_post_cuts_9_MT",     "M_{T}",3000/50,0,3000);
  h_Minv[1]    = new TH1D("h_post_cuts_9_Minv",   "M_{inv}",3000/50,0,3000);
  //sprintf(myname,"%s #SigmaE_{T}",metPrefix_.c_str());
  h_SumEt[1]   = new TH1D("h_post_cuts_9_SumEt",  myname,2500/50,0,2500);

  // individual cuts histos
  h_selections[0]   = new TH1D("h_selections","",25,0,25);
  // N-1 histos
  h_selections[1]   = new TH1D("h_N1_selections","",25,0,25);



  for (int step = 0; step < NSTEPS; ++step) {
    h_jetallet[step]->Sumw2();  

    h_jet1et[step]->Sumw2();
    h_jet2et[step]->Sumw2();
    h_MET[step]   ->Sumw2();
    h_MHT[step]   ->Sumw2();

    h_HT[step]  ->Sumw2();
    h_Meff[step]->Sumw2();
    
    h_jet1metdphi[step]->Sumw2();
    h_jet2metdphi[step]->Sumw2();
    h_jet12dphi[step]  ->Sumw2();
    h_dphistar[step]   ->Sumw2();

    h_Njets[step][0]->Sumw2();
    h_Njets[step][1]->Sumw2();
    h_jet1eta[step] ->Sumw2();
    h_jet2eta[step] ->Sumw2();

    h_jetFem[step]    ->Sumw2();
    h_jet1emfrac[step]->Sumw2();
    h_jet2emfrac[step]->Sumw2();

    h_Nelec[step]    ->Sumw2();
    h_elecEt[step]   ->Sumw2();
    h_elecEta[step]  ->Sumw2();
    h_Ngoodelec[step]->Sumw2();
    h_Nmuon[step]    ->Sumw2();
    h_muonEt[step]   ->Sumw2();
    h_muonEta[step]  ->Sumw2();
    h_Ngoodmuon[step]->Sumw2();
    h_counters[step] ->Sumw2();
  }

  for (int hist = 0; hist < 2; ++hist) {
    //h_jet1phi[hist]   ->Sumw2();
    //h_jet2phi[hist]   ->Sumw2();
    //h_METphi[hist]    ->Sumw2();
    h_MT[hist]        ->Sumw2();
    h_Minv[hist]      ->Sumw2();
    h_SumEt[hist]     ->Sumw2();
    h_selections[hist]->Sumw2();
  }
  // individual cuts histos


  // values to go into the selection table
  //  counter index     counter meaning
  //              0     events passing individual cut
  //              1     events passing previous cuts applied in a sequence
  //              2     events passing previous cuts and current cut
  //              3     events passing all other cuts
  //Current ordering of cuts
  int  totalcounter       = 0;  //preselection
  int  pscounter[4]       = {0};  //preselection
  int  trcounter[4]       = {0};  //trigger requirements
  int  fjcounter[4]       = {0};  //final jet requirements
  int  leptoncounter[4]   = {0};  //isolated lepton veto
  //Branch for MET based analysis
  int  dphicounter[4]     = {0};  //dphi beween jets and met
  int  metcounter[4]      = {0};  //met cut
  //Branch for HT/MHT based analysis
  int  htcounter[4]       = {0};  //ht cut
  int  dphistarcounter[4] = {0};  //dphi between jets and mht
  int  mhtcounter[4]      = {0};  //mht cut



  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  //for (Long64_t jentry=0; jentry<100;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry); nbytes += nb;
    ++totalcounter;
    h_selections[1]->Fill(20.5);
    h_counters[0]->Fill(10.5);
    h_counters[1]->Fill(10.5);
    h_counters[2]->Fill(10.5);
    h_counters[3]->Fill(10.5);

    int nJets  = NJets;
    int nElecs = ElecN;
    int nMuons = MuonN;
    int nTaus  = TauN;
    int nPhots = PhotN;

    double met    = METP4->Pt();
    double rawmet = METpt_Nocorr;
    double metphi = METP4->Phi();
    double sumEt  = METsumEt_Fullcorr;

    double         ht  = computeHT(ht_jet_minpt, ht_jet_maxeta, false);
    TLorentzVector mht = computeMHT(mht_jet_minpt, mht_jet_maxeta, false);

    //Calculate various dphi values
    double jet12dphi   = 0.;
    double jet1metdphi = 0.;
    double jet2metdphi = 0.;

    if (nJets > 1){
      jet1metdphi = JetP4->at(0).Phi()-metphi;
      jet12dphi   = JetP4->at(0).Phi()-JetP4->at(1).Phi();
      jet2metdphi = JetP4->at(1).Phi()-metphi;
    }
    
    jet12dphi   = (jet12dphi < 0)    ? -jet12dphi         : jet12dphi;
    jet12dphi   = (jet12dphi > M_PI) ? 2*M_PI - jet12dphi : jet12dphi;

    jet1metdphi = (jet1metdphi < 0)    ? -jet1metdphi         : jet1metdphi;
    jet1metdphi = (jet1metdphi > M_PI) ? 2*M_PI - jet1metdphi : jet1metdphi;
    jet2metdphi = (jet2metdphi < 0)    ? -jet2metdphi         : jet2metdphi;
    jet2metdphi = (jet2metdphi > M_PI) ? 2*M_PI - jet2metdphi : jet2metdphi;
      
    //calculated dphistar
    double dphistar = 0.;
    dphistar = computeDPhiStar(mht,mht_jet_minpt,mht_jet_maxeta,false);

    double Meff = ht + mht.Pt();
    double MT   = 0.;
    double Minv = 0.;

    if (nJets > 1) {
      TLorentzVector jet1, jet2;
      TLorentzVector dijet;
      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
      dijet = jet1 + jet2;
      MT   = dijet.Mt();
      Minv = dijet.M();
    }

    /*
      printf("*********************Full MET information*********************\n");
      printf("*phi            pt               metx               mety     *\n");
      printf("*%2.2f          %2.2f            %2.2f              %2.2f    *\n",metphi,met,mex,mey);
      //printf("*MET p4:   Pt()=%2.2f    Eta()=%2.2f     Phi()=%2.2f         *\n",METP4.Pt(), METP4.Eta(),METP4.Phi());
      printf("**************************************************************\n");
    */
      
    bool preselection      = true;// 2 jets pT > 50GeV, passing loose JetID
    bool triggerselection  = true;// trigger selection based on HLT/L1 trigger paths
    bool dijetselection    = true;// jet1 and jet2 pT>100GeV, |eta|<2.5
    bool finaljet          = true;// no other jet pT>50GeV, combine with dijet selection
    bool dphiselection     = true;// dphi(jet1, jet2, met) passes cuts
    bool leptonveto        = true;// true if no isolated leptons have pT>15GeV
    //not yet configured, reject jets where lepton energy is more than 50% jet energy within cone of 0.5
    bool metselection      = true;// MET of event > 200GeV//alternately 350GeV
    bool htselection       = true;// HT of event > 250GeV
    bool dphistarselection = true;// dphi(jet1, jet2, met) passes cuts
    bool mhtselection      = true;// MHT of event > 200GeV
      
    //for the selection variables false means we veto the event
    bool nJetSelection[2]       = {false,false};
    bool Preselection[2]        = {false,false};

    bool hltSingleJetTriggerSelection[2] = {false,false};
    bool hltDiJetTriggerSelection[2]     = {false,false};
    bool hltJetTriggerSelection[2]       = {false,false};
    bool hltMETTriggerSelection[2]       = {false,false};
    bool hltMHTTriggerSelection[2]       = {false,false};
    bool hltHTTriggerSelection[2]        = {false,false};
    bool hltTriggerSelection[2]          = {false,false};
      
    bool jet1PtSelection[2]     = {false,false};
    bool jet2PtSelection[2]     = {false,false};
    bool jet1IDSelection[2]     = {false,false};
    bool jet2IDSelection[2]     = {false,false};
    bool jet1EtaSelection[2]    = {false,false};
    bool jet2EtaSelection[2]    = {false,false};
    bool jet12dphiSelection[2]  = {false,false};
      
    bool excessiveJetVeto[2]    = {true,true};

    bool failedJetID[2]         = {false,false};// no jet fails jet ID with pT>30 and |eta|<5
      
    bool metSelection[2]         = {false,false};
    bool jet1metdphiSelection[2] = {false,false};
    bool jet2metdphiSelection[2] = {false,false};
    bool dphistarSelection[2]    = {false,false};
      
    bool htSelection[2]   = {false,false};
    bool mhtSelection[2]  = {false,false};
    bool meffSelection[2] = {false,false};
    //bool mptSelection[2] = {false,false};

    bool electronVeto[2]    = {true,true};
    bool muonVeto[2]        = {true,true};
    bool leptonVeto[2]      = {true,true};
    
    nJetSelection[0]    = (nJets >= cut_njet)      ? true : false;

    //Preselection 2 good jets, with Et > 50GeV
    if (nJets < 2) 
      Preselection[0] = false;
    else {
      if (JetP4->at(1).Pt() < 50.)
	Preselection[0] = false;
      else if ( !(jetID(0,false) && jetID(1,false) ) )
	Preselection[0] = false;
      else
	Preselection[0] = true;
    }

    //Trigger selection
    std::string dijetTriggerPath;
    std::string singlejetTriggerPath;
    std::string metTriggerPath;
    std::string muonTriggerPath;
    std::string electronTriggerPath;
    
    std::map<int,std::string>::iterator key = dijetTriggers.begin();
    while (key != dijetTriggers.end() ) {
      if (Run < key->first) {
	dijetTriggerPath = key->second;
	break;
      }
      ++key;
    }
    
    key = singlejetTriggers.begin();
    while (key != singlejetTriggers.end() ) {
      if (Run < key->first) {
	singlejetTriggerPath = key->second;
	break;
      }
      ++key;
    }
    
    key = metTriggers.begin();
    while (key != metTriggers.end() ) {
      if (Run < key->first) {
	metTriggerPath = key->second;
	break;
      }
      ++key;
    }
    
    key = muonTriggers.begin();
    while (key != muonTriggers.end() ) {
      if (Run < key->first) {
	muonTriggerPath = key->second;
	break;
      }
      ++key;
    }
    
    key = electronTriggers.begin();
    while (key != electronTriggers.end() ) {
      if (Run < key->first) {
	electronTriggerPath = key->second;
	break;
      }
      ++key;
    }

    if (debug_) std::cout<<"Using "<<dijetTriggerPath    <<" as the dijet trigger"    <<std::endl;
    if (debug_) std::cout<<"Using "<<singlejetTriggerPath<<" as the singlejet trigger"<<std::endl;
    if (debug_) std::cout<<"Using "<<metTriggerPath      <<" as the met trigger"      <<std::endl;
    if (debug_) std::cout<<"Using "<<muonTriggerPath     <<" as the muon trigger"     <<std::endl;
    if (debug_) std::cout<<"Using "<<electronTriggerPath <<" as the electron trigger" <<std::endl;

    stringtobool::iterator trigbit = HLTTriggered->find(dijetTriggerPath);
    if (trigbit!=HLTTriggered->end())
      hltDiJetTriggerSelection[0] = trigbit->second;

    trigbit = HLTTriggered->find(singlejetTriggerPath);
    if (trigbit!=HLTTriggered->end())
      hltSingleJetTriggerSelection[0] =  trigbit->second;

    trigbit = HLTTriggered->find(metTriggerPath);
    if (trigbit!=HLTTriggered->end())
      hltMETTriggerSelection[0] = trigbit->second;

    //trigbit = HLTTriggered->find(dijetTriggerPath);
    //if (trigbit!=HLTTriggered->end())
    //  hltJetTriggerSelection[0] = trigbit->second;
    //trigbit = HLTTriggered->find(dijetTriggerPath);
    //if (trigbit!=HLTTriggered->end())
    //  hltJetTriggerSelection[0] = trigbit->second;

    //hltDiJetTriggerSelection[0]     = true;
    //hltSingleJetTriggerSelection[0] = true;
    //hltJetTriggerSelection[0] = true;
    //hltMETTriggerSelection[0] = true;
    //hltMHTTriggerSelection[0] = true;
    //hltHTTriggerSelection[0]  = true;
    /*********************************
     * Trigger selection options
     * 0 AND of single jet, met
     * 1 AND of di jet, met
     * 2 single jet
     * 3 di jet
     * 4 met
     * 5 AND of ht, met
     * 6 AND of single jet, mht
     * 7 AND of di jet, mht
     * 8 ht
     * 9 mht
     *
     *
     *
     *********************************/
    //hltTriggerSelection[0] = 
    //  hltJetTriggerSelection[0] &&
    //  hltMETTriggerSelection[0] &&
    //  hltMHTTriggerSelection[0] &&
    //  hltHTTriggerSelection[0];

    //hltTriggerSelection[0] = 
    //  hltJetTriggerSelection[0] &&
    //  hltMETTriggerSelection[0] &&
    //  hltMHTTriggerSelection[0] &&
    //  hltHTTriggerSelection[0];

    if (triggerPaths == 0) {
    //trigger selection based on a single jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltSingleJetTriggerSelection[0] &
      hltMETTriggerSelection[0];
    }
    if (triggerPaths == 1) {
    //trigger selection based on a di jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltDiJetTriggerSelection[0] &&
      hltMETTriggerSelection[0];
    }

    if (triggerPaths == 2) {
    //trigger selection based on a single jet trigger
    hltTriggerSelection[0] = 
      hltSingleJetTriggerSelection[0];
    }

    if (triggerPaths == 3) {
    //trigger selection based on a dijet jet trigger
    hltTriggerSelection[0] = 
      hltDiJetTriggerSelection[0];
    }

    if (triggerPaths == 4) {
    //trigger selection based on a met trigger
    hltTriggerSelection[0] = 
      hltMETTriggerSelection[0];
    }

    if (triggerPaths == 5) {
    //trigger selection based on a single jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltHTTriggerSelection[0] &
      hltMETTriggerSelection[0];
    }
    if (triggerPaths == 6) {
    //trigger selection based on a di jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltSingleJetTriggerSelection[0] &&
      hltMHTTriggerSelection[0];
    }

    if (triggerPaths == 7) {
    //trigger selection based on a di jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltDiJetTriggerSelection[0] &&
      hltMHTTriggerSelection[0];
    }

    if (triggerPaths == 8) {
    //trigger selection based on a di jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltHTTriggerSelection[0];
    }

    if (triggerPaths == 9) {
    //trigger selection based on a di jet trigger and a met trigger
    hltTriggerSelection[0] = 
      hltMHTTriggerSelection[0];
    }

    //Jets
    if (nJets>0) {
      jet1PtSelection[0]  = (JetP4->at(0).Pt() >= jet1_minpt) ? true : false;
      jet1EtaSelection[0] = (fabs(JetP4->at(0).Eta()) <= jet1_maxeta) ? true : false;
      jet1IDSelection[0]  = jetID(0,false);
      jet1metdphiSelection[0] = (jet1metdphi >= cut_jet1metdphi) ? true : false;
    }
    if (nJets>1) {
      jet2PtSelection[0]  = (JetP4->at(1).Pt() >= jet2_minpt) ? true : false;
      jet2IDSelection[0]  = jetID(1,false);
      jet2EtaSelection[0] = (fabs(JetP4->at(1).Eta()) <= jet2_maxeta) ? true : false;
      jet12dphiSelection[0]   = (jet12dphi   >= cut_jet12dphi)   ? true : false;
      jet2metdphiSelection[0] = (jet2metdphi >= cut_jet2metdphi) ? true : false;
    }
    
    dphistarSelection[0] = (dphistar    >= cut_dphistar)    ? true : false;
    
    metSelection[0]   = (met      >= cut_met)  ? true : false;
    htSelection[0]    = (ht       >= cut_ht)   ? true : false;
    mhtSelection[0]   = (mht.Pt() >= cut_mht)  ? true : false;
    meffSelection[0]  = (Meff     >= cut_meff) ? true : false;

    UInt_t goodjetcount = 0;

    if (jet1IDSelection[0])
      goodjetcount +=1;
    if (jet2IDSelection[0])
      goodjetcount +=1;
    
    //switch for looking at exclusive vs inclusive dijet events
    if (strictDiJets) {
      for (int ijet = 2; ijet < nJets; ++ijet) 
	if (jetID(ijet,false)) {
	  if (JetP4->at(ijet).Pt() > jetall_minpt)
	    ++goodjetcount;
	  if (JetP4->at(ijet).Pt() > jetall_maxpt)
	    excessiveJetVeto[0] = false;
	}
    }

    for (int ijet = 0; ijet < nJets; ++ijet) 
      if (JetP4->at(ijet).Pt() > jetall_minpt)
	if (fabs(JetP4->at(ijet).Eta()) < jetall_maxeta)
	  if (!jetID(ijet,false)) 
	    failedJetID[0] = true;
    
    UInt_t goodeleccount = 0;
    for (int ielec = 0; ielec < nElecs; ++ielec) 
      if (electronID(ielec,false) ) {
	++goodeleccount;
	if (ElectronP4->at(ielec).Pt() > electron_maxpt)
	  electronVeto[0] = false;
      }
      
    UInt_t goodmuoncount = 0;
    for ( int imuon = 0; imuon < nMuons; ++imuon)
      if (muonID(imuon,1) ) {
	++goodmuoncount;
	if (MuonP4->at(imuon).Pt() > muon_maxpt)
	  muonVeto[0] = false;
      }
    leptonVeto[0] = electronVeto[0]&&muonVeto[0];
      
    //Final selections
    preselection     = Preselection[0];
    triggerselection = hltTriggerSelection[0];

    dijetselection = 
      jet1PtSelection[0]  && 
      jet1IDSelection[0]  && 
      jet1EtaSelection[0] &&
      jet2PtSelection[0]  && 
      jet2IDSelection[0]  && 
      jet2EtaSelection[0];

    finaljet       = dijetselection && excessiveJetVeto[0] && !failedJetID[0];
    leptonveto     = electronVeto[0] && muonVeto[0];
    metselection   = metSelection[0];
    dphiselection  = jet1metdphiSelection[0] && jet2metdphiSelection[0];
    htselection    = htSelection[0];
    mhtselection   = mhtSelection[0];
    dphistarselection  = dphistarSelection[0];
      
      
    //printf("preselect   triggers  dijet   finaljet   dphi   dphi*   met   lepton   ht   mht\n");
    //std::cout<<std::setw(8)<<"preselect"<<std::setw(10)<<"triggers"
    //	     <<std::setw(10)<<"dijet"<<std::setw(10)<<"finaljet"
    //	     <<std::setw(10)<<"dphi"<<std::setw(10)<<"dphi*"
    //	     <<std::setw(10)<<"met"<<std::setw(10)<<"lepton"
    //	     <<std::setw(10)<<"ht"<<std::setw(10)<<"mht"<<std::endl;
    ////printf("%d       %d       %d   %d   %d   %d   %d   %d   %d   %d\n",preselection,triggerselection,dijetselection,finaljet,dphiselection,dphistarselection,metselection,leptonveto,htselection,mhtselection);
    //std::cout<<std::setw(9)<<preselection;
    //std::cout<<std::setw(10)<<triggerselection;
    //std::cout<<std::setw(10)<<dijetselection;
    //std::cout<<std::setw(10)<<finaljet;
    //std::cout<<std::setw(10)<<dphiselection;
    //std::cout<<std::setw(10)<<dphistarselection;
    //std::cout<<std::setw(10)<<metselection;
    //std::cout<<std::setw(10)<<leptonveto;
    //std::cout<<std::setw(10)<<htselection;
    //std::cout<<std::setw(10)<<mhtselection<<std::endl;

    //**************************Individual cut counters***********************//
    if (preselection) {
      pscounter[0]++;
      h_counters[1]->Fill(0.5);
    }
    if (triggerselection) {
      trcounter[0]++;
      h_counters[1]->Fill(1.5);
    }
    if (finaljet) {
      fjcounter[0]++;
      h_counters[1]->Fill(2.5);
    }
    if (leptonveto) {
      leptoncounter[0]++;
      h_counters[1]->Fill(3.5);
    }
    if (dphiselection) {
      dphicounter[0]++;
      h_counters[1]->Fill(4.5);
    }
    //Selection based on MET/DPhi(Jet1,2,MET)
    if (metselection) {
      metcounter[0]++;
      h_counters[1]->Fill(5.5);
    }
    //Selection based on HT/MHT/DPhiStar
    if (dphistarselection) {
      dphistarcounter[0]++;
      h_counters[1]->Fill(6.5);
    }
    if (htselection) {
      htcounter[0]++;
      h_counters[1]->Fill(7.5);
    }
    if (mhtselection) {
      mhtcounter[0]++;
      h_counters[1]->Fill(8.5);
    }


    //**************************Sequential pre/post cut counters***********************//
    if (analysisVer=="met"||analysisVer=="mht") {
      pscounter[1]++;
      h_counters[0]->Fill(0.5);
      h_Njets[1][0]->Fill(nJets);
      h_Njets[1][1]->Fill(goodjetcount);
      if (preselection) {
	pscounter[2]++;
	h_counters[3]->Fill(0.5);
	trcounter[1]++;
	h_counters[0]->Fill(1.5);
	if (triggerselection) {
	  trcounter[2]++;
	  h_counters[3]->Fill(1.5);
	  fjcounter[1]++;
	  h_counters[0]->Fill(2.5);

	  /*
	    dijetselection = 
	    jet1PtSelection[0]  && 
	    jet1IDSelection[0]  && 
	    jet1EtaSelection[0] &&
	    jet2PtSelection[0]  && 
	    jet2IDSelection[0]  && 
	    jet2EtaSelection[0];
	    finaljet = dijetselection && 
	    excessiveJetVeto[0] &&
	    failedJetID;
	  */
	  h_jet1emfrac[1]->Fill(JetFem->at(0));
	  if ( jet1IDSelection[0] ) {
	    h_jet1eta[1]->Fill(JetP4->at(0).Eta());
	    if ( jet1EtaSelection[0]) {
	      h_jet1et[1]->Fill(JetP4->at(0).Pt());
	    }
	  }
	  h_jet2emfrac[1]->Fill(JetFem->at(1));
	  if ( jet2IDSelection[0]) {
	    h_jet2eta[1]->Fill(JetP4->at(1).Eta());
	    if ( jet2EtaSelection[0]) {
	      h_jet2et[1]->Fill(JetP4->at(1).Pt());
	    }
	  }
	  if (dijetselection) {
	    int ijet = 2;
	    while (ijet < nJets) {
	      if (jetID(ijet,false)) {
		if (JetP4->at(ijet).Pt()>jetall_minpt)
		  h_jetFem[1]->Fill(JetFem->at(ijet));
		  h_jetallet[1]->Fill(JetP4->at(ijet).Pt());
	      }
	      ijet++;
	    }
	  }

	  if (finaljet) {
	    fjcounter[2]++;
	    h_counters[3]->Fill(2.5);
	    leptoncounter[1]++;
	    h_counters[0]->Fill(3.5);

	    for ( int ielec = 0; ielec < nElecs; ++ielec) {
	      if (electronID(ielec,false) ) {
		h_elecEt[1]->Fill(ElectronP4->at(ielec).Pt());
		h_elecEta[1]->Fill(ElectronP4->at(ielec).Eta());
	      }
	    }
	    h_Nelec[1]->Fill(nElecs);
	    h_Ngoodelec[1]->Fill(goodeleccount);
	    for ( int imuon = 0; imuon < nMuons; ++imuon) {
	      if (muonID(imuon,1) ) {
		h_muonEt[1]->Fill(MuonP4->at(imuon).Pt());
		h_muonEta[1]->Fill(MuonP4->at(imuon).Eta());
	      }
	    }
	    h_Nmuon[1]->Fill(nMuons);
	    h_Ngoodmuon[1]->Fill(goodmuoncount);

	    if (leptonveto) {
	      leptoncounter[2]++;
	      h_counters[3]->Fill(3.5);
	      dphicounter[1]++;
	      h_counters[0]->Fill(4.5);

	      TLorentzVector jet1, jet2;
	      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
	      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
	      h_jet12dphi[1]->Fill(jet1.DeltaPhi(jet2) );

	      h_jet1metdphi[1]->Fill(jet1metdphi);
	      if (jet1metdphiSelection[0]) {
		h_jet2metdphi[1]->Fill(jet2metdphi);
	      }
	      if (dphiselection) {
		dphicounter[2]++;
		h_counters[3]->Fill(4.5);
		//Selection based on MET/DPhi(Jet1,2,MET)
		metcounter[1]++;
		h_counters[0]->Fill(5.5);
		
		h_MET[1]->Fill(met);
		
		if (metselection) {
		  metcounter[2]++;
		  h_counters[3]->Fill(5.5);}}}
	    //Selection based on HT/MHT/DPhiStar
	    dphistarcounter[1]++;
	    h_counters[0]->Fill(6.5);

	    h_dphistar[1]->Fill(dphistar);
	    
	    if (dphistarselection) {
	      dphistarcounter[2]++;
	      h_counters[3]->Fill(6.5);
	      htcounter[1]++;
	      h_counters[0]->Fill(7.5);
	      
	      h_HT[1]->Fill(ht);

	      if (htselection) {
		htcounter[2]++;
		h_counters[3]->Fill(7.5);
		mhtcounter[1]++;
		h_counters[0]->Fill(8.5);

		h_MHT[1]->Fill(mht.Pt());

		if (mhtselection) {
		  mhtcounter[2]++;
		  h_counters[3]->Fill(8.5);

		  h_Meff[1]->Fill(Meff);
		}}}}}}
      //**************************N-1 cut counters***********************//
      if (
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  dphiselection    &&
	  metselection
	  ) {
	pscounter[3]++;
	h_counters[2]->Fill(0.5);}
      if (
	  preselection     &&
	  finaljet         &&
	  leptonveto       &&
	  dphiselection    &&
	  metselection 
	  ) {
	trcounter[3]++;
	h_counters[2]->Fill(1.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  leptonveto       &&
	  dphiselection    &&
	  metselection
	  ) {
	fjcounter[3]++;
	h_counters[2]->Fill(2.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  dphiselection    &&
	  metselection
	  ) {
	leptoncounter[3]++;
	h_counters[2]->Fill(3.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  metselection
	  ) {
	dphicounter[3]++;
	h_counters[2]->Fill(4.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  dphiselection    &&
	  leptonveto   
	  ) {
	metcounter[3]++;
	h_counters[2]->Fill(5.5);}

      //Selection based on HT/MHT/DPhiStar
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  htselection     &&
	  mhtselection
	  ) {
	dphistarcounter[3]++;
	h_counters[2]->Fill(6.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  dphistarselection&&
	  mhtselection     
	  ) {
	htcounter[3]++;
	h_counters[2]->Fill(7.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  dphistarselection&&
	  htselection     
	  ) {
	mhtcounter[3]++;
	h_counters[2]->Fill(8.5);}
      
      ////////////
      
      nJetSelection[1] = 
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
      
      hltTriggerSelection[1] = 
	nJetSelection[0]     &&
	jet1PtSelection[0]   &&
	jet2PtSelection[0]   &&
	jet1EtaSelection[0]  &&
	jet2EtaSelection[0]  &&
	jet1IDSelection[0]   &&
	jet2IDSelection[0]   &&
	excessiveJetVeto[0]  &&
	!failedJetID[0]       &&
	jet12dphiSelection[0]&&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
      
      jet1PtSelection[1] =
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	//jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet2PtSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	//jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet1EtaSelection[1] = 
	nJetSelection[0]      && 
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1IDSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet2EtaSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet1IDSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet2IDSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      excessiveJetVeto[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
      
      failedJetID[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
      
      jet12dphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
      
      jet1metdphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet2metdphiSelection[0]&&
	metSelection[0]        &&
	leptonVeto[0];
    
      jet2metdphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet1metdphiSelection[0]&&
	metSelection[0]        &&

	leptonVeto[0];

      //MET based analysis
      metSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	leptonVeto[0];

      //HT/MHT based analysis
      htSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet1metdphiSelection[0]&&
	//jet2metdphiSelection[0]&&
	meffSelection[0]    &&
	mhtSelection[0]     &&
	dphistarSelection[0]&&

	leptonVeto[0];

      mhtSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet1metdphiSelection[0]&&
	//jet2metdphiSelection[0]&&
	htSelection[0]      &&
	meffSelection[0]    &&
	dphistarSelection[0]&&

	leptonVeto[0];

      meffSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet1metdphiSelection[0]&&
	//jet2metdphiSelection[0]&&
	htSelection[0]      &&
	mhtSelection[0]     &&
	dphistarSelection[0]&&

	leptonVeto[0];

      dphistarSelection[1] =
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	//jet1metdphiSelection[0]&&
	//jet2metdphiSelection[0]&&
	htSelection[0]  &&
	mhtSelection[0] &&
	meffSelection[0]&&
	leptonVeto[0];
      
      leptonVeto[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	!failedJetID[0]       &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0];

    }
    else {
      pscounter[1]++;
      h_counters[0]->Fill(0.5);
      if (preselection) {
	pscounter[2]++;
	h_counters[3]->Fill(0.5);
	trcounter[1]++;
	h_counters[0]->Fill(1.5);
	if (triggerselection) {
	  trcounter[2]++;
	  h_counters[3]->Fill(1.5);
	  fjcounter[1]++;
	  h_counters[0]->Fill(2.5);
	  if (finaljet) {
	    fjcounter[2]++;
	    h_counters[3]->Fill(2.5);
	    leptoncounter[1]++;
	    h_counters[0]->Fill(3.5);
	    if (leptonveto) {
	      leptoncounter[2]++;
	      h_counters[3]->Fill(3.5);
	      dphicounter[1]++;
	      h_counters[0]->Fill(4.5);
	      if (dphiselection) {
		dphicounter[2]++;
		h_counters[3]->Fill(4.5);
		metcounter[1]++;
		h_counters[0]->Fill(5.5);
		if (metselection) {
		  metcounter[2]++;
		  h_counters[3]->Fill(5.5);
		  dphistarcounter[1]++;
		  h_counters[0]->Fill(6.5);
		  if (dphistarselection) {
		    dphistarcounter[2]++;
		    h_counters[3]->Fill(6.5);
		    htcounter[1]++;
		    h_counters[0]->Fill(7.5);
		    if (htselection) {
		      htcounter[2]++;
		      h_counters[3]->Fill(7.5);
		      mhtcounter[1]++;
		      h_counters[0]->Fill(8.5);
		      if (mhtselection) {
			mhtcounter[2]++;
			h_counters[3]->Fill(8.5);}}}}}}}}}
      //**************************N-1 cut counters***********************//
      if (
	  triggerselection  &&
	  finaljet          &&
	  dphiselection     &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection  
	  ) {
	pscounter[3]++;
	h_counters[2]->Fill(0.5);}
      if (
	  preselection      &&
	  finaljet          &&
	  dphiselection     &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection  
	  ) {
	trcounter[3]++;
	h_counters[2]->Fill(1.5);}
      if (
	  preselection      &&
	  triggerselection  &&
	  dphiselection     &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection    
	  ) {
	fjcounter[3]++;
	h_counters[2]->Fill(2.5);}
      if (
	  preselection      &&
	  triggerselection  &&
	  finaljet          &&
	  dphiselection     &&
	  metselection      &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection    
	  ) {
	leptoncounter[3]++;
	h_counters[2]->Fill(3.5);}
      if (
	  preselection      &&
	  triggerselection  &&
	  finaljet          &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection    
	  ) {
	dphicounter[3]++;
	h_counters[2]->Fill(4.5);}
      //Selection based on MET/DPhi(Jet1,2,MET)
      if (
	  preselection      &&
	  triggerselection  &&
	  finaljet          &&
	  dphiselection     &&
	  leptonveto        &&
	  dphistarselection &&
	  htselection       &&
	  mhtselection    
	  ) {
	metcounter[3]++;
	h_counters[2]->Fill(5.5);}
      //Selection based on HT/MHT/DPhiStar
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  dphiselection    &&
	  leptonveto       &&
	  metselection     &&
	  htselection      &&
	  mhtselection
	  ) {
	dphistarcounter[3]++;
	h_counters[2]->Fill(8.5);}
      if (
	  preselection      &&
	  triggerselection  &&
	  finaljet          &&
	  dphiselection     &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  mhtselection  
	  ) {
	htcounter[3]++;
	h_counters[2]->Fill(6.5);}
      if (
	  preselection      &&
	  triggerselection  &&
	  finaljet          &&
	  dphiselection     &&
	  leptonveto        &&
	  metselection      &&
	  dphistarselection &&
	  htselection   
	  ) {
	mhtcounter[3]++;
	h_counters[2]->Fill(7.5);}
      
      ////////////
      
      nJetSelection[1] = 
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]        &&
	mhtSelection[0]       &&
	meffSelection[0]      &&
	dphistarSelection[0]  &&
	leptonVeto[0];
    
      hltTriggerSelection[1] = 
	nJetSelection[0]     &&
	jet1PtSelection[0]   &&
	jet2PtSelection[0]   &&
	jet1EtaSelection[0]  &&
	jet2EtaSelection[0]  &&
	jet1IDSelection[0]   &&
	jet2IDSelection[0]   &&
	excessiveJetVeto[0]  &&
	jet12dphiSelection[0]&&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet1PtSelection[1] =
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet2PtSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet1EtaSelection[1] = 
	nJetSelection[0]      && 
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet2EtaSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet1IDSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      jet2IDSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
    
      excessiveJetVeto[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
      
      jet12dphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&
	leptonVeto[0];
      
      //MET based analysis
      jet1metdphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
      
	metSelection[0]        &&
	jet2metdphiSelection[0]&&
      
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&

	leptonVeto[0];
    
      jet2metdphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&

	metSelection[0]        &&
	jet1metdphiSelection[0]&&

	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&

	leptonVeto[0];

      metSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
      
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&

	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0]&&

	leptonVeto[0];

      //HT/MHT based analysis
      htSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
      
	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&

	meffSelection[0]    &&
	mhtSelection[0]     &&
	dphistarSelection[0]&&

	leptonVeto[0];

      mhtSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&

	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&

	htSelection[0]      &&
	meffSelection[0]    &&
	dphistarSelection[0]&&

	leptonVeto[0];

      meffSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&

	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&

	htSelection[0]      &&
	mhtSelection[0]     &&
	dphistarSelection[0]&&

	leptonVeto[0];

      dphistarSelection[1] =
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&

	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&

	htSelection[0]  &&
	mhtSelection[0] &&
	meffSelection[0]&&

	leptonVeto[0];
      
      leptonVeto[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	jet1IDSelection[0]    &&
	jet2IDSelection[0]    &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	metSelection[0]        &&
	htSelection[0]      &&
	mhtSelection[0]     &&
	meffSelection[0]    &&
	dphistarSelection[0];
    }
      

    
    ///////////      
      
    ////////////////////////////////////
    //pre cut plots
    ////////////////////////////////////
    h_Njets[0][0]->Fill(nJets);
    
    if (nJets > 0) {
      h_jet1et[0]->Fill(JetP4->at(0).Pt());
      h_jet1eta[0]->Fill(JetP4->at(0).Eta());
      h_jet1emfrac[0]->Fill(JetFem->at(0));
      //h_jet1phi[0]->Fill(JetP4->at(0).Phi());
      h_jet1metdphi[0]->Fill(jet1metdphi);
    }

    if (nJets > 1) {
      h_jet2et[0]->Fill(JetP4->at(1).Pt());
      h_jet2eta[0]->Fill(JetP4->at(1).Eta());
      h_jet2emfrac[0]->Fill(JetFem->at(1));
      //h_jet2phi[0]->Fill(JetP4->at(1).Phi());
      h_jet2metdphi[0]->Fill(jet2metdphi);
      
      TLorentzVector jet1, jet2;
      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
      h_jet12dphi[0]->Fill(jet1.DeltaPhi(jet2) );
      
    }

    h_MT[0]->Fill(MT);
    h_Minv[0]->Fill(Minv);
    h_SumEt[0]->Fill(sumEt);

    int ijet = 2;
    while (ijet < nJets) {
      if (jetID(ijet,false)) {
	h_jetFem[0]->Fill(JetFem->at(ijet));
	h_jetallet[0]->Fill(JetP4->at(ijet).Pt());
      }
      ijet++;
    }
    
    h_Njets[0][1]->Fill(goodjetcount);

    h_dphistar[0]->Fill(dphistar);
    
    h_MET[0]->Fill(met);
    h_HT[0]->Fill(ht);
    h_MHT[0]->Fill(mht.Pt());
    h_Meff[0]->Fill(Meff);
    
    for ( int ielec = 0; ielec < nElecs; ++ielec) {
      if (electronID(ielec,false) ) {
	h_elecEt[0]->Fill(ElectronP4->at(ielec).Pt());
	h_elecEta[0]->Fill(ElectronP4->at(ielec).Eta());
      }
    }
    h_Nelec[0]->Fill(nElecs);
    h_Ngoodelec[0]->Fill(goodeleccount);

    for ( int imuon = 0; imuon < nMuons; ++imuon) {
      if (muonID(imuon,1) ) {
	h_muonEt[0]->Fill(MuonP4->at(imuon).Pt());
	h_muonEta[0]->Fill(MuonP4->at(imuon).Eta());
      }
    }
    h_Nmuon[0]->Fill(nMuons);
    h_Ngoodmuon[0]->Fill(goodmuoncount);
      
    
    ////////////////////////////////////
    //individual cut plots
    ////////////////////////////////////
    
    if (nJetSelection[0]) {
      //h_Njets[1][0]->Fill(nJets);
      h_selections[0]->Fill(0.5);}
    
    if (hltTriggerSelection[0]) {
      h_selections[0]->Fill(1.5);}
    
    if (leptonVeto[0]) {
      /*
      for ( int ielec = 0; ielec < nElecs; ++ielec) {
	if (electronID(ielec,false) ) {
	  h_elecEt[1]->Fill(ElectronP4->at(ielec).Pt());
	  h_elecEta[1]->Fill(ElectronP4->at(ielec).Eta());
	}
      }
      h_Nelec[1]->Fill(nElecs);
      h_Ngoodelec[1]->Fill(goodeleccount);
      for ( int imuon = 0; imuon < nMuons; ++imuon) {
	if (muonID(imuon,1) ) {
	  h_muonEt[1]->Fill(MuonP4->at(imuon).Pt());
	  h_muonEta[1]->Fill(MuonP4->at(imuon).Eta());
	}
      }
      h_Nmuon[1]->Fill(nMuons);
      h_Ngoodmuon[1]->Fill(goodmuoncount);
      */
      
      h_selections[0]->Fill(2.5);}
    
    
    if (jet1PtSelection[0]) {
      //h_jet1et[1]->Fill(JetP4->at(0).Pt());
      h_selections[0]->Fill(3.5);}
    
    if (jet2PtSelection[0]) {
      //h_jet2et[1]->Fill(JetP4->at(1).Pt());
      h_selections[0]->Fill(4.5);}

    if (jet1EtaSelection[0]) {
      //h_jet1eta[1]->Fill(JetP4->at(0).Eta());
      h_selections[0]->Fill(5.5);}

    if (jet2EtaSelection[0]) {
      //h_jet2eta[1]->Fill(JetP4->at(1).Eta());
      h_selections[0]->Fill(6.5);}

    if (jet1IDSelection[0]) {
      //h_jet1emfrac[1]->Fill(JetFem->at(0));
      h_selections[0]->Fill(7.5);}
    
    if (jet2IDSelection[0]) {
      //h_jet2emfrac[1]->Fill(JetFem->at(1));
      h_selections[0]->Fill(8.5);}
    
    /*
    //What's going on here???
    ijet = 2;
    while (ijet < nJets) {
      if (jetID(ijet,false)) {
	if (JetP4->at(ijet).Pt()>jetall_minpt)
	  h_jetFem[1]->Fill(JetFem->at(ijet));
      }
      ijet++;
    }
    */
    if (excessiveJetVeto[0]) {
      /*
	ijet = 2;
	while (ijet < nJets) {
	if (jetID(ijet,false)) {
	  if (JetP4->at(ijet).Pt()>jetall_minpt)
	    h_jetallet[1]->Fill(JetP4->at(ijet).Pt());
	}
	ijet++;
      }
      h_Njets[1][1]->Fill(goodjetcount);
      */
      h_selections[0]->Fill(9.5);}
    if (!failedJetID[0])
      h_selections[0]->Fill(10.5);
    if (jet12dphiSelection[0]) {
      TLorentzVector jet1, jet2;
      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
      
      //h_jet12dphi[1]->Fill(jet1.DeltaPhi(jet2) );
      h_selections[0]->Fill(11.5);}

    ///
    
    //MET analysis specific cuts    
    if (metSelection[0]) {
      //h_MET[1]->Fill(met);
      h_selections[0]->Fill(12.5);}

    if (jet1metdphiSelection[0]) {
      //h_jet1metdphi[1]->Fill(jet1metdphi);
      h_selections[0]->Fill(13.5);}

    if (jet2metdphiSelection[0]) {
      //h_jet2metdphi[1]->Fill(jet2metdphi);
      h_selections[0]->Fill(14.5);}
    

    //HT/MHT analysis specific cuts
    if (htSelection[0]) {

      //h_HT[1]->Fill(ht);
      h_selections[0]->Fill(16.5);}

    if (mhtSelection[0]) {

      //h_MHT[1]->Fill(mht.Pt());
      h_selections[0]->Fill(17.5);}

    if (meffSelection[0]) {

      //h_Meff[1]->Fill(Meff);
      h_selections[0]->Fill(18.5);}

    if (dphistarSelection[0]) {
      //h_dphistar[1]->Fill(dphistar);
      h_selections[0]->Fill(19.5);}
            
        
    //////////////////////////////////////
    ///////////////////////////////////////////
    //N-1 plots
    //////////////////////////////////////////
  
    if (nJetSelection[1]) {
      h_Njets[2][0]->Fill(nJets);
      h_selections[1]->Fill(0.5);}

    if (hltTriggerSelection[1]) {
      h_selections[1]->Fill(1.5);}
      
    if (leptonVeto[1]) {
      for ( int ielec = 0; ielec < nElecs; ++ielec) {
	if (electronID(ielec,false) ) {
	  h_elecEt[2]->Fill(ElectronP4->at(ielec).Pt());
	  h_elecEta[2]->Fill(ElectronP4->at(ielec).Eta());
	}
      }
      h_Nelec[2]->Fill(nElecs);
      h_Ngoodelec[2]->Fill(goodeleccount);

      for ( int imuon = 0; imuon < nMuons; ++imuon) {
	if (muonID(imuon,1) ) {
	  h_muonEt[2]->Fill(MuonP4->at(imuon).Pt());
	  h_muonEta[2]->Fill(MuonP4->at(imuon).Eta());
	}
      }
      h_Nmuon[2]->Fill(nMuons);
      h_Ngoodmuon[2]->Fill(goodmuoncount);

      h_selections[1]->Fill(2.5);
    }
      
    if (jet1PtSelection[1]) {
      h_jet1et[2]->Fill(JetP4->at(0).Pt());
      h_selections[1]->Fill(3.5);}
      
    if (jet2PtSelection[1]) {
      h_jet2et[2]->Fill(JetP4->at(1).Pt());
      h_selections[1]->Fill(4.5);}
      
    if (jet1EtaSelection[1]) {
      h_jet1eta[2]->Fill(JetP4->at(0).Eta());
      h_selections[1]->Fill(5.5);}
      
    if (jet2EtaSelection[1]) {
      h_jet2eta[2]->Fill(JetP4->at(1).Eta());
      h_selections[1]->Fill(6.5);}
      
    if (jet1IDSelection[1]) {
      h_jet1emfrac[2]->Fill(JetFem->at(0));
      h_selections[1]->Fill(7.5);}
      
    if (jet2IDSelection[1]) {
      h_jet2emfrac[2]->Fill(JetFem->at(1));
      h_selections[1]->Fill(8.5);}
        
    ijet = 2;
    while (ijet < nJets) {
      if (jetID(ijet,false)) {
	if (JetP4->at(ijet).Pt()>jetall_minpt)
	  h_jetFem[2]->Fill(JetFem->at(ijet));
      }
      ijet++;
    }

    if (excessiveJetVeto[1]) {
      ijet = 2;
      while (ijet < nJets) {
	if (jetID(ijet,false)) {
	  if (JetP4->at(ijet).Pt()>jetall_minpt)
	    h_jetallet[2]->Fill(JetP4->at(ijet).Pt());
	}
	ijet++;
      }
      h_Njets[2][1]->Fill(goodjetcount);
      //h_HT[2]->Fill(ht);//what to do about recalculating HT when some jets are rejected?
      h_selections[1]->Fill(9.5);}
    
    if (failedJetID[1])
      h_selections[0]->Fill(10.5);
    if (jet12dphiSelection[1]) {
      TLorentzVector jet1, jet2;
      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());

      h_jet12dphi[2]->Fill(jet1.DeltaPhi(jet2) );
      h_selections[1]->Fill(11.5);}
    

    //MET Analysis path
    if (metSelection[1]) {

      h_MET[2]->Fill(met);
      h_selections[1]->Fill(12.5);}

    if (jet1metdphiSelection[1]) {

      h_jet1metdphi[2]->Fill(jet1metdphi);
      h_selections[1]->Fill(13.5);}

    if (jet2metdphiSelection[1]) {
      h_jet2metdphi[2]->Fill(jet2metdphi);
      h_selections[1]->Fill(14.5);}
    

    //HT/MHT Analysis path
    if (htSelection[1]) {

      h_HT[2]->Fill(ht);
      h_selections[1]->Fill(16.5);}

    if (mhtSelection[1]) {

      h_MHT[2]->Fill(mht.Pt());
      h_selections[1]->Fill(17.5);}

    if (meffSelection[1]) {

      h_Meff[2]->Fill(Meff);
      h_selections[1]->Fill(18.5);}

    if (dphistarSelection[1]) {
      h_dphistar[2]->Fill(dphistar);
      h_selections[1]->Fill(19.5);}

    //////////////////////////////////////


  
    //Full selection
    ////////////////////////////////////////
    bool analysis_step;
    if (analysisVer=="met") 
      analysis_step = 
	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0];
    else if (analysisVer=="mht") 
      analysis_step = 
	htSelection[0]         &&
	mhtSelection[0]        &&
	meffSelection[0]       &&
	dphistarSelection[0];
    else {
      //std::cout<<"No analysis type selected, doing both MHT/MET"<<std::endl;
      analysis_step = 
	metSelection[0]        &&
	jet1metdphiSelection[0]&&
	jet2metdphiSelection[0]&&
	htSelection[0]         &&
	mhtSelection[0]        &&
	meffSelection[0]       &&
	dphistarSelection[0];
    }

    bool selections = 
      excessiveJetVeto[0]    &&
      hltTriggerSelection[0] &&
      nJetSelection[0]       &&
      jet1PtSelection[0]     &&
      jet2PtSelection[0]     &&
      jet1EtaSelection[0]    &&
      jet2EtaSelection[0]    &&
      jet1IDSelection[0]     &&
      jet2IDSelection[0]     &&
      jet12dphiSelection[0]  &&
      analysis_step          &&
      leptonVeto[0];
    
    if (selections) {
      
      //if (MET>1000) {
      //printf("MET %2.2f: x=%2.2f ,y=%2.2f, phi=%2.2f\ngenMET %2.2f: x=%2.2f ,y=%2.2f, phi=%2.2f\n",MET,METx,METy,METphi_fullcorr,genMET,genMETx,genMETy,genMETphi);
      //}
      
      h_selections[0]->Fill(20.5);
      h_Njets[3][0]->Fill(nJets);
      
      h_MT[1]->Fill(MT);
      h_Minv[1]->Fill(Minv);
      h_SumEt[1]->Fill(sumEt);
      
      h_jet1et[3]->Fill(JetP4->at(0).Pt());
      h_jet2et[3]->Fill(JetP4->at(1).Pt());
      
      h_MET[3]->Fill(met);

      h_HT[3]->Fill(ht);
      h_MHT[3]->Fill(mht.Pt());
      h_Meff[3]->Fill(Meff);

      for (int ijet = 2; ijet < nJets; ++ijet) {
	if (jetID(ijet,false)) {
	  if (JetP4->at(ijet).Pt() > jetall_minpt) {
	    h_jetFem[3]->Fill(JetFem->at(ijet));
	    h_jetallet[3]->Fill(JetP4->at(ijet).Pt());
	  }
	}
      }

      h_Njets[3][1]->Fill(goodjetcount);
      
      h_jet1eta[3]->Fill(JetP4->at(0).Eta());
      h_jet2eta[3]->Fill(JetP4->at(1).Eta());
      h_jet1emfrac[3]->Fill(JetFem->at(0));
      h_jet2emfrac[3]->Fill(JetFem->at(1));
      
      //total number of photons/leptons in event
      for ( int ielec = 0; ielec < nElecs; ++ielec) {
	if (electronID(ielec,false) ) {
	  h_elecEt[3]->Fill(ElectronP4->at(ielec).Pt());
	  h_elecEta[3]->Fill(ElectronP4->at(ielec).Eta());
	}
      }
      h_Nelec[3]->Fill(nElecs);
      h_Ngoodelec[3]->Fill(goodeleccount);
      
      for ( int imuon = 0; imuon < nMuons; ++imuon) {
	if (muonID(imuon,1) ) {
	  h_muonEt[3]->Fill(MuonP4->at(imuon).Pt());
	  h_muonEta[3]->Fill(MuonP4->at(imuon).Eta());
	}
      }
      h_Nmuon[3]->Fill(nMuons);
      h_Ngoodmuon[3]->Fill(goodmuoncount);
      
      TLorentzVector jet1, jet2;
      jet1.SetPxPyPzE(JetP4->at(0).Px(),JetP4->at(0).Py(),JetP4->at(0).Pz(),JetP4->at(0).E());
      jet2.SetPxPyPzE(JetP4->at(1).Px(),JetP4->at(1).Py(),JetP4->at(1).Pz(),JetP4->at(1).E());
      h_jet12dphi[3]->Fill(jet1.DeltaPhi(jet2) );
      
      h_jet1metdphi[3]->Fill(jet1metdphi);
      h_jet2metdphi[3]->Fill(jet2metdphi);
      h_dphistar[2]->Fill(dphistar);
      
      //h_jet1phi[1]->Fill(JetP4->at(0).Phi());
      //h_jet2phi[1]->Fill(JetP4->at(1).Phi());
      //h_METphi[1]->Fill(metphi);
      
      //print out event info for data that passes cuts
      printOutEventInfo();
      
    }
    //////////////////////////////////////
    
  }
  std::cout<<"Done looping events "<<std::endl;


  // scale histograms to desired values
  //h_selections[1]->SetBinContent(21,cross_section_);
  //h_selections[1]->SetBinContent(22,efficiency_);
  //h_selections[1]->SetBinContent(23,luminosity_);

  char ytitle[128];
  sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
  h_selections[0]->Scale(scale_);
  h_selections[0]->GetYaxis()->SetTitle(ytitle);
  h_selections[1]->Scale(scale_);
  h_selections[1]->GetYaxis()->SetTitle(ytitle);
  h_selections[0]->GetXaxis()->SetBinLabel(1,"nJets");
  h_selections[0]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");
  h_selections[0]->GetXaxis()->SetBinLabel(3,"e/#mu Veto");
  h_selections[0]->GetXaxis()->SetBinLabel(4,"E_{T}^{Jet_{1}}");
  h_selections[0]->GetXaxis()->SetBinLabel(5,"E_{T}^{Jet_{2}}");
  h_selections[0]->GetXaxis()->SetBinLabel(6,"#eta_{Jet_{1}}");
  h_selections[0]->GetXaxis()->SetBinLabel(7,"#eta_{Jet_{2}}");
  h_selections[0]->GetXaxis()->SetBinLabel(8,"EM_{FRAC}^{Jet_{1}}");
  h_selections[0]->GetXaxis()->SetBinLabel(9,"EM_{FRAC}^{Jet_{2}}");
  h_selections[0]->GetXaxis()->SetBinLabel(10,"E^{MAX}_{T}^{jets}");
  h_selections[0]->GetXaxis()->SetBinLabel(11,"Jets Failing JetID");
  h_selections[0]->GetXaxis()->SetBinLabel(12,"#Delta#phi(Jet_{1}, Jet_{2})");
  //h_selections[0]->GetXaxis()->SetBinLabel(12,"#slash E_{T} Type Cuts");
  h_selections[0]->GetXaxis()->SetBinLabel(13,"#slashE_{T}");
  h_selections[0]->GetXaxis()->SetBinLabel(14,"#Delta#phi(Jet_{1}, #slashE_{T})");
  h_selections[0]->GetXaxis()->SetBinLabel(15,"#Delta#phi(Jet_{2}, #slashE_{T})");
  h_selections[0]->GetXaxis()->SetBinLabel(16,"H_{T}/#slash H_{T} Type Cuts");
  h_selections[0]->GetXaxis()->SetBinLabel(17,"H_{T}");
  h_selections[0]->GetXaxis()->SetBinLabel(18,"#slashH_{T}");
  h_selections[0]->GetXaxis()->SetBinLabel(19,"M_{eff}");
  h_selections[0]->GetXaxis()->SetBinLabel(20,"#Delta#phi^{*}(Jets, #slashH_{T})");
  h_selections[0]->GetXaxis()->SetBinLabel(21,"ALL");
  h_selections[0]->SetStats(kFALSE);

  h_selections[1]->GetXaxis()->SetBinLabel(1,"nJets");
  h_selections[1]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");
  h_selections[1]->GetXaxis()->SetBinLabel(3,"e/#mu Veto");
  h_selections[1]->GetXaxis()->SetBinLabel(4,"E_{T}^{Jet_{1}}");
  h_selections[1]->GetXaxis()->SetBinLabel(5,"E_{T}^{Jet_{2}}");
  h_selections[1]->GetXaxis()->SetBinLabel(6,"#eta_{Jet_{1}}");
  h_selections[1]->GetXaxis()->SetBinLabel(7,"#eta_{Jet_{2}}");
  h_selections[1]->GetXaxis()->SetBinLabel(8,"EM_{FRAC}^{Jet_{1}}");
  h_selections[1]->GetXaxis()->SetBinLabel(9,"EM_{FRAC}^{Jet_{2}}");
  h_selections[1]->GetXaxis()->SetBinLabel(10,"E^{MAX}_{T}^{jets}");
  h_selections[1]->GetXaxis()->SetBinLabel(11,"Jets Failing JetID");
  h_selections[1]->GetXaxis()->SetBinLabel(12,"#Delta#phi(Jet_{1}, Jet_{2})");
  //h_selections[1]->GetXaxis()->SetBinLabel(12,"#slash E_{T} Type Cuts");
  h_selections[1]->GetXaxis()->SetBinLabel(13,"#slashE_{T}");
  h_selections[1]->GetXaxis()->SetBinLabel(14,"#Delta#phi(Jet_{1}, #slashE_{T})");
  h_selections[1]->GetXaxis()->SetBinLabel(15,"#Delta#phi(Jet_{2}, #slashE_{T})");
  h_selections[1]->GetXaxis()->SetBinLabel(16,"H_{T}/#slash H_{T} Type Cuts");
  h_selections[1]->GetXaxis()->SetBinLabel(17,"H_{T}");
  h_selections[1]->GetXaxis()->SetBinLabel(18,"#slashH_{T}");
  h_selections[1]->GetXaxis()->SetBinLabel(19,"#Delta#phi^{*}(Jets, #slashH_{T})");
  h_selections[1]->GetXaxis()->SetBinLabel(20,"M_{eff}");
  h_selections[1]->GetXaxis()->SetBinLabel(21,"Total Events");
  //h_selections[1]->GetXaxis()->SetBinLabel(22,"#sigma");
  //h_selections[1]->GetXaxis()->SetBinLabel(23,"#epsilon");
  //h_selections[1]->GetXaxis()->SetBinLabel(20,"#integralL dt");
  h_selections[1]->SetStats(kFALSE);

  for (int mine = 0; mine < 2; ++mine) {
    //sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    //h_jet1phi[mine]->Scale(scale_);
    //h_jet1phi[mine]->GetYaxis()->SetTitle(ytitle);
    //h_jet2phi[mine]->Scale(scale_);
    //h_jet2phi[mine]->GetYaxis()->SetTitle(ytitle);
    //h_METphi[mine]->Scale(scale_);
    //h_METphi[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 50 GeV / %2.0f pb^{-1}",luminosity_);
    h_MT[mine]->Scale(scale_);
    h_MT[mine]->GetYaxis()->SetTitle(ytitle);
    h_Minv[mine]->Scale(scale_);
    h_Minv[mine]->GetYaxis()->SetTitle(ytitle);
    h_SumEt[mine]->Scale(scale_);
    h_SumEt[mine]->GetYaxis()->SetTitle(ytitle);}
  
  for (int mine = 0; mine < 4; ++mine) {
    sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    //sprintf(ytitle,"Raw Events passing cuts");
    h_counters[mine]->Scale(scale_);
    h_counters[mine]->GetYaxis()->SetTitle(ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(1,"2 Loose ID Jets p_{T} > 50 GeV");
    h_counters[mine]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");
    if (strictDiJets)
      h_counters[mine]->GetXaxis()->SetBinLabel(3,"strict di-jet cuts");
    else
      h_counters[mine]->GetXaxis()->SetBinLabel(3,"loose di-jet cuts ");
    h_counters[mine]->GetXaxis()->SetBinLabel(4,"e/#mu Veto");
    sprintf(ytitle,"#Delta#phi(J_{1},#slashE_{T}) > %2.2f, #Delta#phi(J_{2},#slashE_{T}) > %2.2f",cut_jet1metdphi,cut_jet2metdphi);
    h_counters[mine]->GetXaxis()->SetBinLabel(5,ytitle);
    sprintf(ytitle,"#slashE_{T} > %2.2f",cut_met);
    h_counters[mine]->GetXaxis()->SetBinLabel(6,ytitle);
    sprintf(ytitle,"#Delta#phi* > %2.2f",cut_dphistar);
    h_counters[mine]->GetXaxis()->SetBinLabel(7,ytitle);
    sprintf(ytitle,"H_{T} > %2.2f",cut_ht);
    h_counters[mine]->GetXaxis()->SetBinLabel(8,ytitle);
    sprintf(ytitle,"#slashH_{T} > %2.2f",cut_mht);
    h_counters[mine]->GetXaxis()->SetBinLabel(9,ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(11,"Nevents");
    h_counters[mine]->SetStats(kFALSE);
    
    sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    for (int my = 0; my < 2; ++my) {
      h_Njets[mine][my]->Scale(scale_);
      h_Njets[mine][my]->GetYaxis()->SetTitle(ytitle);}
    
    h_Nelec[mine]->Scale(scale_);
    h_Nelec[mine]->GetYaxis()->SetTitle(ytitle);
    h_Ngoodelec[mine]->Scale(scale_);
    h_Ngoodelec[mine]->GetYaxis()->SetTitle(ytitle);

    h_Nmuon[mine]->Scale(scale_);
    h_Nmuon[mine]->GetYaxis()->SetTitle(ytitle);
    h_Ngoodmuon[mine]->Scale(scale_);
    h_Ngoodmuon[mine]->GetYaxis()->SetTitle(ytitle);
    
    h_jet1eta[mine]->Scale(scale_);
    h_jet1eta[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2eta[mine]->Scale(scale_);
    h_jet2eta[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet1emfrac[mine]->Scale(scale_);
    h_jet1emfrac[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2emfrac[mine]->Scale(scale_);
    h_jet2emfrac[mine]->GetYaxis()->SetTitle(ytitle);
      
    h_jetFem[mine]->Scale(scale_);    h_jetFem[mine]->GetYaxis()->SetTitle(ytitle);
      
    h_jet12dphi[mine]->Scale(scale_);
    h_jet12dphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet1metdphi[mine]->Scale(scale_);
    h_jet1metdphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2metdphi[mine]->Scale(scale_);
    h_jet2metdphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_dphistar[mine]->Scale(scale_);
    h_dphistar[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 25 GeV / %2.0f pb^{-1}",luminosity_);
    h_jet1et[mine]->Scale(scale_);
    h_jet1et[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2et[mine]->Scale(scale_);
    h_jet2et[mine]->GetYaxis()->SetTitle(ytitle);      

    sprintf(ytitle,"Events / 25 GeV / %2.0f pb^{-1}",luminosity_);
    h_MET[mine]->Scale(scale_);
    h_MET[mine]->GetYaxis()->SetTitle(ytitle);
    h_MHT[mine]->Scale(scale_);
    h_MHT[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 25 GeV / %2.0f pb^{-1}",luminosity_);
    if (mine > 1)
      sprintf(ytitle,"Events / 5 GeV / %2.0f pb^{-1}",luminosity_);
    h_jetallet[mine]->Scale(scale_);
    h_jetallet[mine]->GetYaxis()->SetTitle(ytitle);      
    h_elecEt[mine]->Scale(scale_);
    h_elecEt[mine]->GetYaxis()->SetTitle(ytitle);
    h_muonEt[mine]->Scale(scale_);
    h_muonEt[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 50 GeV / %2.0f pb^{-1}",luminosity_);

    h_HT[mine]->Scale(scale_);
    h_HT[mine]->GetYaxis()->SetTitle(ytitle);
    h_Meff[mine]->Scale(scale_);
    h_Meff[mine]->GetYaxis()->SetTitle(ytitle);

  }

  //
  int Nevents = totalcounter;
  std::cout<<std::setw(18)<<"Cut Series"<<std::setw(15)<<"Nevents"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"preselection"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"triggers"<<std::setw(3)<<" - "
	   <<std::setw(10)<<"finaljet"<<std::setw(3)<<" - "
	   <<std::setw(10)<<"leptonveto"<<std::setw(3)<<" - "
	   <<std::setw(14)<<"dphiselection"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"metselection"<<std::endl;
  std::cout<<std::setw(18)<<"Individual:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[0]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[0]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[0]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[0]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[0]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[0]<<std::endl;
  std::cout<<std::setw(18)<<"Sequential-Pre:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[1]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[1]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[1]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[1]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[1]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[1]<<std::endl;
  std::cout<<std::setw(18)<<"Sequential-Post:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[2]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[2]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[2]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[2]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[2]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[2]<<std::endl;
  std::cout<<std::setw(18)<<"N-1:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[3]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[3]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[3]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[3]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[3]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[3]<<std::endl;




  
  //Write out file and histograms
  for (int step = 0; step < NSTEPS; ++step) {
    h_jetallet[step]->Write();  
    
    h_jet1et[step]->Write();
    h_jet2et[step]->Write();
    h_MET[step]   ->Write();
    h_MHT[step]   ->Write();
    
    h_HT[step]  ->Write();
    h_Meff[step]->Write();
    
    h_jet1metdphi[step]->Write();
    h_jet2metdphi[step]->Write();
    h_jet12dphi[step]  ->Write();
    h_dphistar[step]   ->Write();

    h_Njets[step][0]->Write();
    h_Njets[step][1]->Write();
    h_jet1eta[step] ->Write();
    h_jet2eta[step] ->Write();
     
    h_jetFem[step]    ->Write();
    h_jet1emfrac[step]->Write();
    h_jet2emfrac[step]->Write();
     
    h_Nelec[step]    ->Write();
    h_elecEt[step]   ->Write();
    h_elecEta[step]  ->Write();
    h_Ngoodelec[step]->Write();
    h_Nmuon[step]    ->Write();
    h_muonEt[step]   ->Write();
    h_muonEta[step]  ->Write();
    h_Ngoodmuon[step]->Write();
    h_counters[step] ->Write();

  }
   
  for (int hist = 0; hist < 2; ++hist) {
    //h_jet1phi[hist]   ->Write();
    //h_jet2phi[hist]   ->Write();
    //h_METphi[hist]    ->Write();
    h_MT[hist]        ->Write();
    h_Minv[hist]      ->Write();
    h_SumEt[hist]     ->Write();
    h_selections[hist]->Write();
  }
   
  file->cd();
  file->Write();
}


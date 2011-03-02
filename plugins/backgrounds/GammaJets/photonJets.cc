#define photonJets_cxx
#include "photonJets.h"
#include "Math/GenVector/VectorUtil.h"
#include <TROOT.h>
#include <TMath.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#define NSTEPS       4
#define NUMHISTOS   24

using namespace ROOT;


photonJets::photonJets(TTree *tree, std::string* sampleList, std::string* triggerList, std::string* cutFile, const bool &isData, const std::string &jetPrefix, const std::string &metPrefix, const std::string &lepPrefix, const std::string &phtPrefix, const std::string &sampleKey)
  :ntupleAnalysisPAT(tree, sampleList, triggerList, cutFile, isData, jetPrefix, metPrefix, lepPrefix, phtPrefix, sampleKey)
{
  std::cout<<"Executing photonJets::photonJets()"<<std::endl;
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
photonJets::~photonJets()
{
}


void photonJets::Loop(const std::string &outputfile, const double &cutJet1, const double &cutJet2, const double &cutMET, const bool& strictDiJets, const int& triggerPaths)
{
  int debug_ = 0;
  printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  strictDiJets:  %d  triggerPaths:  %d\n",
	 outputfile.c_str(), cutJet1, cutJet2, cutMET, strictDiJets, triggerPaths);
  
  gROOT->ProcessLine(".L /uscms_data/d2/sturdy07/SUSY/new387/CMSSW_4_1_1/src/JSturdy/AnalysisNtuplePAT/plugins/common/ntuplePragmas.so");
  
  jet1_minpt = cutJet1;
  jet2_minpt = cutJet2;
  cut_met    = cutMET;

  outfilename_ = outputfile;
  
  std::cout<<"Scale factor is: "<<scale_<<std::endl;

  printf("converted args: %s  pT1: %4.6f  pT2: %4.6f  MET: %4.6f  lum: %4.6f,  xs: %4.6f,  eff: %4.6f  num: %4.6f  scale: %4.6f\n",
	 outfilename_.c_str(), jet1_minpt, jet2_minpt, cut_met, luminosity_, cross_section_, efficiency_, generated_events_, scale_);

  if (fChain == 0) return;

  char tmpfile[128];
  sprintf(tmpfile,"%s.root",outfilename_.c_str());
  TFile *file = new TFile(tmpfile,"RECREATE");
  file->cd();
  
  /////////histograms
  TH1D *h_selections[2];
  TH1D *h_Nelec[4], *h_Nmuon[4], *h_Nphoton[4];
   
  TH1D *h_Njets[4], *h_jet1eta[4], *h_jet2eta[4], *h_jetalleta[4];
  TH1D *h_elecEta[4], *h_muonEta[4], *h_photonEta[4];
   
  TH1D *h_jet1emfrac[4], *h_jet2emfrac[4], *h_jetFem[4];
  TH1D *h_jet12dphi[4], *h_jetmetdphi[4], *h_jet1metdphi[4], *h_jet2metdphi[4];
  // bins of 50 GeV
  TH1D *h_MET[4], *h_jet1et[4], *h_jet2et[4], *h_jetallet[4];
  // bins of 25 and 1 GeV depending on plot
  TH1D *h_elecEt[4], *h_muonEt[4], *h_photonEt[4];
  TH1D *h_counters[4];

  char histtitle[NUMHISTOS][128];
  std::string histname[NUMHISTOS] = {
    "00_Njets",
    "01_jet1et",
    "02_jet2et",
    "03_jetallet",
    "11_MET",
    "21_jet1metdphi",
    "22_jet2metdphi",
    "23_jetmetdphi",
    "24_jet12dphi",
    "31_jet1eta",
    "32_jet2eta",
    "33_jetalleta",
    "41_jet1emfrac",
    "42_jet2emfrac",
    "43_jetFem",
    "50_Nelecs",
    "51_eleceta",
    "52_elecet",
    "60_Nmuons",
    "61_muoneta",
    "62_muonet",
    "70_Nphotons",
    "71_photoneta",
    "72_photonet"
  };
  
  char plottitle[NUMHISTOS][128];
  std::string plotname[NUMHISTOS] = {
    jetPrefix_+" N_{jets}",
    jetPrefix_+" E_{T}^{J_{1}}",                               
    jetPrefix_+" E_{T}^{J_{2}}",
    jetPrefix_+" E_{T}^{J_{3+}}",
    metPrefix_+" #slash E_{T}",
    "#Delta#phi(J_{1},#slash E_{T})",
    "#Delta#phi(J_{2},#slash E_{T})",
    "#Delta#phi(J_{all},#slash E_{T})",
    "#Delta#phi(J_{1}, J_{2})",
    jetPrefix_+" #eta^{J_{1}}",
    jetPrefix_+" #eta^{J_{2}} ",
    jetPrefix_+" #eta^{J_{all}} ",
    jetPrefix_+" E^{J_{1}}_{EM}/E^{J_{1}}_{tot}",
    jetPrefix_+" E^{J_{2}}_{EM}/E^{J_{2}}_{tot}",
    jetPrefix_+" E^{J_{3+}}_{EM}/E^{J_{3+}}_{tot}",
    lepPrefix_+" N_{e}",
    lepPrefix_+" #eta^{e}",
    lepPrefix_+" E_{T}^{e}",
    lepPrefix_+" N_{#mu}",
    lepPrefix_+" #eta^{#mu}",
    lepPrefix_+" E_{T}^{#mu}",
    phtPrefix_+" N_{#gamma}",
    phtPrefix_+" #eta^{#gamma}",
    phtPrefix_+" E_{T}^{#gamma}"
  };

  
  //std::string histpre[4] = {"h_pre_cuts_","h_individual_cuts_","h_N1_cuts_","h_post_cuts_"};
  std::string histpre[4] = {"h_pre_cuts_","h_previous_cuts_","h_N1_cuts_","h_post_cuts_"};
  
  double bins[4][NUMHISTOS] = {
    //pre cuts
    // njets, j1et,  j2et,  jallet, met,   
    {10, 1500., 1500., 1000.,  1000., 
     // j1mdp,   j2mdp,   jallmdp,  j12dp
     M_PI, M_PI, M_PI, M_PI,
     // j1eta,  j2eta,  jalleta
     1.,   0.,   0., 
     // j1emf,  j2emf,  jallemf
     1.,   0.,   0., 
     // nelec, eleceta, elecet
     15.,  0.,   500.,
     // nmuon, muoneta, muonet
     15.,  0.,   500.,
     // nphot, photeta, photet
     15.,  0.,   500.},
    
    /*
    //individual cuts
    // njets, j1et,  j2et,  jallet, met,   
    {10, 1500., 1500., 1000.,  1000., 
     // j1mdp,   j2mdp,   jallmdp,  j12dp
     M_PI, M_PI, M_PI, M_PI,
     // j1eta,  j2eta,  jalleta
     1.,   0.,   0., 
     // j1emf,  j2emf,  jallemf
     1.,   0.,   0., 
     // nelec, eleceta, elecet
     15.,  0.,   500.,
     // nmuon, muoneta, muonet
     15.,  0.,   500.,
     // nphot, photeta, photet
     15.,  0.,   500.}
    */
    
    //sequential cuts
    // njets, j1et,  j2et,  jallet, met,   
    {10, 1500., 1500., 1000.,  1000., 
     // j1mdp,   j2mdp,   jallmdp,  j12dp
     M_PI, M_PI, M_PI, M_PI,
     // j1eta,  j2eta,  jalleta
     1.,   0.,   0., 
     // j1emf,  j2emf,  jallemf
     1.,   0.,   0., 
     // nelec, eleceta, elecet
     15.,  0.,   500.,
     // nmuon, muoneta, muonet
     15.,  0.,   500.,
     // nphot, photeta, photet
     15.,  0.,   500.},
    
    //N-1 cuts
    // njets, j1et,  j2et,  jallet, met,   
    {10, 1500., 1500., 1000.,  1000., 
     // j1mdp,   j2mdp,   jallmdp,  j12dp
     M_PI, M_PI, M_PI, M_PI,
     // j1eta,  j2eta,  jalleta
     1.,   0.,   0., 
     // j1emf,  j2emf,  jallemf
     1.,   0.,   0., 
     // nelec, eleceta, elecet
     15.,  0.,   500.,
     // nmuon, muoneta, muonet
     15.,  0.,   500.,
     // nphot, photeta, photet
     15.,  0.,   500.},
    
    //post cuts
    // njets, j1et,  j2et,  jallet, met,   
    {10, 1000., 1000., 750.,  1000., 
     // j1mdp,   j2mdp,   jallmdp,  j12dp
     M_PI, M_PI, M_PI, M_PI,
     // j1eta,  j2eta,  jalleta
     1.,   0.,   0., 
     // j1emf,  j2emf,  jallemf
     1.,   0.,   0., 
     // nelec, eleceta, elecet
     15.,  0.,   500.,
     // nmuon, muoneta, muonet
     15.,  0.,   500.,
     // nphot, photeta, photet
     15.,  0.,   500.}
  };
  
  double binsize = 0.;

  for (int tt = 0; tt < 4; ++tt) {
    for (int hh = 0; hh < NUMHISTOS; ++hh) {
      sprintf(histtitle[hh],"%s%s",histpre[tt].c_str(),histname[hh].c_str());
      sprintf(plottitle[hh],"%s",plotname[hh].c_str());
    }
    
    h_Njets[tt]  = new TH1D(histtitle[0],plottitle[0],static_cast<int>(bins[tt][0]),0.,bins[tt][0]);

    binsize = 5.; // bins of 5 GeV
    h_jet1et[tt]   = new TH1D(histtitle[1],plottitle[1],static_cast<int>(bins[tt][1]/binsize),0.,bins[tt][1]);
    h_jet2et[tt]   = new TH1D(histtitle[2],plottitle[2],static_cast<int>(bins[tt][2]/binsize),0.,bins[tt][2]);
    h_jetallet[tt] = new TH1D(histtitle[3],plottitle[3],static_cast<int>(bins[tt][3]/binsize),0.,bins[tt][3]);
    h_MET[tt]      = new TH1D(histtitle[4],plottitle[4],static_cast<int>(bins[tt][4]/binsize),0.,bins[tt][4]);

    // fixed number of bins
    h_jet1metdphi[tt] = new TH1D(histtitle[5],plottitle[5],50,0.,bins[tt][5]);
    h_jet2metdphi[tt] = new TH1D(histtitle[6],plottitle[6],50,0.,bins[tt][6]);
    h_jetmetdphi[tt]  = new TH1D(histtitle[7],plottitle[7],50,0.,bins[tt][7]);
    h_jet12dphi[tt]   = new TH1D(histtitle[8],plottitle[8],50,0.,bins[tt][8]);

    h_jet1eta[tt]   = new TH1D(histtitle[9], plottitle[9], 50,-5.,5.);
    h_jet2eta[tt]   = new TH1D(histtitle[10],plottitle[10],50,-5.,5.);
    h_jetalleta[tt] = new TH1D(histtitle[11],plottitle[11],50,-5.,5.);

    h_jet1emfrac[tt] = new TH1D(histtitle[12],plottitle[12],25,0.,1.);
    h_jet2emfrac[tt] = new TH1D(histtitle[13],plottitle[13],25,0.,1.);
    h_jetFem[tt]     = new TH1D(histtitle[14],plottitle[14],25,0.,1.);

    //lepton plots
    h_Nelec[tt]     = new TH1D(histtitle[15],plottitle[15],static_cast<int>(bins[tt][15]),0.,bins[tt][15]);
    h_elecEta[tt]   = new TH1D(histtitle[16],plottitle[16],50,-5.,5.);

    binsize = 10.;// bins of 10 GeV 
    if (tt > 1)
      binsize = 5.;
    h_elecEt[tt]   = new TH1D(histtitle[17],plottitle[17],static_cast<int>(bins[tt][17]/binsize),0.,bins[tt][17]);

    h_Nmuon[tt]     = new TH1D(histtitle[18],plottitle[18],static_cast<int>(bins[tt][18]),0.,bins[tt][18]);
    h_muonEta[tt]   = new TH1D(histtitle[19],plottitle[19],50,-5.,5.);
    
    binsize = 10.;// bins of 10 GeV 
    if (tt > 1)
      binsize = 5.;
    h_muonEt[tt]   = new TH1D(histtitle[20],plottitle[20],static_cast<int>(bins[tt][20]/binsize),0.,bins[tt][20]);

    h_Nphoton[tt]     = new TH1D(histtitle[21],plottitle[21],static_cast<int>(bins[tt][21]),0.,bins[tt][21]);
    h_photonEta[tt]   = new TH1D(histtitle[22],plottitle[22],50,-5.,5.);
    
    binsize = 10.;// bins of 10 GeV 
    if (tt > 1)
      binsize = 5.;
    h_photonEt[tt]   = new TH1D(histtitle[23],plottitle[23],static_cast<int>(bins[tt][23]/binsize),0.,bins[tt][23]);
  }
  //Counters for selections
  for (int tt = 0; tt < 4; ++tt) {
    sprintf(histtitle[tt],"%sevents",histpre[tt].c_str());
    sprintf(plottitle[tt],"Events Passing Cuts");
    h_counters[tt] = new TH1D(histtitle[tt],plottitle[tt],25,0,25);
  }

  //pre cuts
  char myname[128];
  // individual cuts histos
  h_selections[0]   = new TH1D("h_selections","",25,0,25);
  // N-1 histos
  h_selections[1]   = new TH1D("h_N1_selections","",25,0,25);



  for (int step = 0; step < NSTEPS; ++step) {
    h_Njets[step]   ->Sumw2();
    h_jetallet[step]->Sumw2();  
    h_jet1et[step]  ->Sumw2();
    h_jet2et[step]  ->Sumw2();

    h_MET[step]   ->Sumw2();

    h_jet1metdphi[step]->Sumw2();
    h_jet2metdphi[step]->Sumw2();
    h_jetmetdphi[step] ->Sumw2();
    h_jet12dphi[step]  ->Sumw2();

    h_jet1eta[step]  ->Sumw2();
    h_jet2eta[step]  ->Sumw2();
    h_jetalleta[step]->Sumw2();

    h_jet1emfrac[step]->Sumw2();
    h_jet2emfrac[step]->Sumw2();
    h_jetFem[step]    ->Sumw2();

    h_Nelec[step]    ->Sumw2();
    h_elecEt[step]   ->Sumw2();
    h_elecEta[step]  ->Sumw2();

    h_Nmuon[step]    ->Sumw2();
    h_muonEt[step]   ->Sumw2();
    h_muonEta[step]  ->Sumw2();

    h_Nphoton[step]    ->Sumw2();
    h_photonEt[step]   ->Sumw2();
    h_photonEta[step]  ->Sumw2();

    h_counters[step] ->Sumw2();
  }

  for (int hist = 0; hist < 2; ++hist) {
    h_selections[hist]->Sumw2();
  }

  ////////////////////

   
  Long64_t nentries = fChain->GetEntriesFast();
   
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
  int  photoncounter[4]   = {0};  //isolated photon
  int  dphicounter[4]     = {0};  //dphi beween jets and met
  int  metcounter[4]      = {0};  //met cut


  Long64_t nbytes = 0, nb = 0;
  //for (Long64_t jentry=0; jentry<nentries;jentry++) {
  for (Long64_t jentry=0; jentry<250000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry); nbytes += nb;
    ++totalcounter;

    int nJets  = NJets;
    int nElecs = ElecN;
    int nMuons = MuonN;
    int nPhots = PhotN;

    //Preselection

    bool preselection      = true;// 2 jets pT > 50GeV, passing loose JetID
    bool triggerselection  = true;// trigger selection based on HLT/L1 trigger paths
    bool dijetselection    = true;// jet1 and jet2 pT>100GeV, |eta|<2.5, need to check that jets aren't photons (done by JetID?)
    bool photisoselection  = true;// photon is isolated
    bool finaljet          = true;// no other jet pT>50GeV, combine with dijet selection
    bool dphiselection     = true;// dphi(jet1, jet2, met) passes cuts
    bool leptonveto        = true;// true if no isolated leptons have pT>15GeV
    //not yet configured, reject jets where lepton energy is more than 50% jet energy within cone of 0.5
    bool metselection      = true;// MET of event > 200GeV//alternately 350GeV
      
    //for the selection variables false means we veto the event
    bool Preselection[2]        = {false,false};
    bool nJetSelection[2]       = {false,false};

    bool hltPhotonTriggerSelection[2] = {false,false};
    bool hltTriggerSelection[2]       = {false,false};
      
    bool jet1PtSelection[2]     = {false,false};
    bool jet2PtSelection[2]     = {false,false};
    bool jet1EtaSelection[2]    = {false,false};
    bool jet2EtaSelection[2]    = {false,false};
    bool jet12dphiSelection[2]  = {false,false};
    bool jetmetdphiSelection[2] = {false,false};
      
    bool excessiveJetVeto[2]    = {true,true};

    bool photonSelection[2]      = {true,true};
     
    bool electronVeto[2]    = {true,true};
    bool muonVeto[2]        = {true,true};
    bool leptonVeto[2]      = {true,true};
    
    nJetSelection[0]    = (nJets >= cut_njet) ? true : false;

    //Find leading 2 jets and make sure that they pass jetID
    //Open Question:
    //Do we just search for the highest 2 pt jets passing loose jetID?
    //Or do we reject events where one of the leading 2 jets fails 
    //jetID and eta requirements?
    int jet1Index = -1;
    int jet2Index = -1;
    bool passdijetpreselection = false;

    int photIndexFail = -1;
    int photIndexPass = -1;
    int secondPhotonDRMatchPass    = 0;
    int photonDRMatchesPass[NJets];
    int secondPhotonDRMatchFail    = 0;
    int photonDRMatchesFail[NJets];
    
    //create a new collection of the jets passing loose jet id
    LorentzP4Vs goodJetP4;
    
    if (debug_)
      std::cout<<"creating good jet collection"<<std::endl;
    for (int jet = 0; jet < NJets; ++jet) {
      if (jet1Index < 0) {
	if ( jetID(jet,false) )
	  jet1Index = jet;
      }
      else {
	if (jet2Index < 0)
	  //if (jet1Index < jet)
	  if ( jetID(jet,false) ) {
	    jet2Index = jet;
	    passdijetpreselection = true;
	  }
      }
      
      if ( jetID(jet,false) )
	goodJetP4.push_back(JetP4->at(jet));
      
      photonDRMatchesFail[jet] = 0;
      photonDRMatchesPass[jet] = 0;

      if (debug_)
	std::cout<<"looping over photons to see if there are jet matchers"<<std::endl;
      for (int phot = 0; phot < nPhots; ++phot) {
	//currently searching for highest pt photon in jet cone
	//need to search for closeest?
	double jetPhotDeltaR = ROOT::Math::VectorUtil::DeltaR(PhotonP4->at(phot),JetP4->at(jet));
	if ( !jetID(jet,false) ){ //for jets failing loose jetID
	  if (photIndexFail < 0) {
	    if (jetPhotDeltaR < 0.1)
	      photIndexFail = jet;
	  }
	  else
	    if (jetPhotDeltaR < 0.1) {
	      if (photIndexFail == phot)
		++secondPhotonDRMatchFail;
	      ++photonDRMatchesFail[jet];
	    }
	}
	else { //for jets passing loose jetID
	  if (photIndexPass < 0) {
	    if (jetPhotDeltaR < 0.1)
	      photIndexPass = jet;
	  }
	  else
	    if (jetPhotDeltaR < 0.1) {
	      if (photIndexPass == phot)
		++secondPhotonDRMatchPass;
	      ++photonDRMatchesPass[jet];
	    }
	}
      }
    }
    
    int nGoodJets = goodJetP4.size();
    if (debug_) {
      std::cout<<"jet collection size "<<nJets<<std::endl;
      std::cout<<"good jet collection size "<<nGoodJets<<std::endl;
    }
    //Preselection 2 good jets, with Et > 50GeV
    //Photon with pT > 100GeV
    if (nJets < 2) {
      if (debug_)
	std::cout<<"fail selection nJets"<<std::endl;
      Preselection[0] = false;}
    else if (!passdijetpreselection) {
      if (debug_)
	std::cout<<"fail selection dijets selection"<<std::endl;
      Preselection[0] = false;}
    //else if (goodJetP4->at(1).Pt() < 50.)
    else if (JetP4->at(jet1Index).Pt() < 50.) {
      if (debug_)
	std::cout<<"fail selection jet1 selection"<<std::endl;
      Preselection[0] = false;}
    else if (JetP4->at(jet2Index).Pt() < 50.) {
      if (debug_)
	std::cout<<"fail selection jet2 selection"<<std::endl;
      Preselection[0] = false;}
    //else if ( !(jetID(0,false) && jetID(1,false) ) )
    //Preselection[0] = false;}
    else if (nPhots < 1) {
      if (debug_)
	std::cout<<"fail selection nPhots"<<std::endl;
      Preselection[0] = false;}
    //preselection on photon pt, should be verified by MC
    else if (PhotonP4->at(0).Pt() < 25) {
      if (debug_)
	std::cout<<"fail selection photon pt"<<std::endl;
      Preselection[0] = false;}
    else {
      if (debug_)
	std::cout<<"pass preselection"<<std::endl;
      Preselection[0] = true;}
    
    preselection     = Preselection[0];

    
    if (preselection) {//only doing the rest of the study for preselection, don't care about all cuts - preselection
      
      LorentzP4Vs goodElectronP4;
      for (int ielec = 0; ielec < nElecs; ++ielec) 
	if (electronID(ielec,false) ) 
	  goodElectronP4.push_back(ElectronP4->at(ielec));
      int nGoodElecs = goodElectronP4.size();

      LorentzP4Vs goodMuonP4;
      for (int imuon = 0; imuon < nMuons; ++imuon) 
	if (muonID(imuon,false) ) 
	  goodMuonP4.push_back(MuonP4->at(imuon));
      int nGoodMuons = goodMuonP4.size();
      
      
      if (debug_) {
	std::cout<<"Leading Jets are Jet("<<jet1Index<<") and Jet("<<jet2Index<<")"<<std::endl;
	std::cout<<secondPhotonDRMatchFail<<" matching bad Jets"<<std::endl;
	std::cout<<secondPhotonDRMatchPass<<" matching good Jets"<<std::endl;
      }
      for (int jet = 0; jet < NJets; ++jet)
	if (debug_) {
	  std::cout<<photonDRMatchesFail[jet]<<" matching bad Jet("<<jet<<")"<<std::endl;
	  std::cout<<photonDRMatchesPass[jet]<<" matching good Jet("<<jet<<")"<<std::endl;
	}      
      //Trigger selection
      std::string photonTriggerPath;
      
      std::map<int,std::string>::iterator key = photonTriggers.begin();
      while (key != photonTriggers.end() ) {
	if (Run < key->first) {
	  photonTriggerPath = key->second;
	  break;
	}
	++key;
      }
      
      if (debug_)
	std::cout<<"Using "<<photonTriggerPath    <<" as the photon trigger"    <<std::endl;
      
      stringtobool::iterator trigbit = HLTTriggered->find(photonTriggerPath);
      if (trigbit!=HLTTriggered->end())
	hltPhotonTriggerSelection[0] = trigbit->second;
      
      hltTriggerSelection[0] = 
	hltPhotonTriggerSelection[0];
      
      triggerselection = hltTriggerSelection[0];
      
      
      //get the met related variables
      double met    = METP4->Pt();
      double rawmet = METpt_Nocorr;
      double metphi = METP4->Phi();
      double sumEt  = METsumEt_Fullcorr;
      
      //calculate met-like (met + gamma)
      double metx = METP4->Px();
      double mety = METP4->Py();
      metx += PhotonP4->at(0).Px();
      mety += PhotonP4->at(0).Py();
      
      double metlike    = sqrt(metx*metx+mety*mety);
      double metlikephi = atan2(mety,metx);

      //Calculate various dphi values
      double jet12dphi   = 0.;
      
      double jetmetdphi[nGoodJets];
      
      //int photJetIndex = -1;
      
      jet12dphi   = goodJetP4.at(0).Phi()-goodJetP4.at(1).Phi();
      jet12dphi   = (jet12dphi < 0)    ? -jet12dphi         : jet12dphi;
      jet12dphi   = (jet12dphi > M_PI) ? 2*M_PI - jet12dphi : jet12dphi;
      
      for (int jet = 0; jet < nGoodJets; ++jet) {
	jetmetdphi[jet] = goodJetP4.at(jet).Phi()-metlikephi;
	jetmetdphi[jet] = (jetmetdphi[jet] < 0)    ? -jetmetdphi[jet]         : jetmetdphi[jet];
	jetmetdphi[jet] = (jetmetdphi[jet] > M_PI) ? 2*M_PI - jetmetdphi[jet] : jetmetdphi[jet];
      }
      
      
      //Jets
      jet1PtSelection[0]  = (goodJetP4.at(0).Pt() >= jet1_minpt) ? true : false;
      jet1EtaSelection[0] = (fabs(goodJetP4.at(0).Eta()) <= jet1_maxeta) ? true : false;

      jet2PtSelection[0]  = (goodJetP4.at(1).Pt() >= jet2_minpt) ? true : false;
      jet2EtaSelection[0] = (fabs(goodJetP4.at(1).Eta()) <= jet2_maxeta) ? true : false;

      jet12dphiSelection[0]   = (jet12dphi   >= cut_jet12dphi)   ? true : false;

      jetmetdphiSelection[0]  = (jetmetdphi[0] >= cut_jet1metdphi && jetmetdphi[1] >= cut_jet2metdphi)   ? true : false;
      
      //switch for looking at exclusive vs inclusive dijet events
      if (strictDiJets) {
	for (int ijet = 2; ijet < nGoodJets; ++ijet) 
	  if (goodJetP4.at(ijet).Pt() > jetall_maxpt)
	    excessiveJetVeto[0] = false;
      }
      
      for (int ielec = 0; ielec < nGoodElecs; ++ielec) 
	if (goodElectronP4.at(ielec).Pt() > electron_maxpt)
	  electronVeto[0] = false;
      
      for ( int imuon = 0; imuon < nGoodMuons; ++imuon)
	if (goodMuonP4.at(imuon).Pt() > muon_maxpt)
	  muonVeto[0] = false;

      leptonVeto[0] = electronVeto[0]&&muonVeto[0];
      
      //Final selections
      dijetselection = 
	jet1PtSelection[0]  && 
	jet1EtaSelection[0] &&
	jet2PtSelection[0]  && 
	jet2EtaSelection[0];
      
      finaljet       = dijetselection && excessiveJetVeto[0];
      photisoselection      = photonSelection[0];
      leptonveto     = electronVeto[0] && muonVeto[0];
      //figure out dphi(jeti,met) or met-like
      dphiselection  = jetmetdphiSelection[0];
      
      

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
      if (photisoselection) {
	photoncounter[0]++;
	h_counters[1]->Fill(3.5);
      }
      if (leptonveto) {
	leptoncounter[0]++;
	h_counters[1]->Fill(4.5);
      }
      if (dphiselection) {
	dphicounter[0]++;
	h_counters[1]->Fill(5.5);
      }
      //Selection based on MET/DPhi(Jet1,2,MET)


      //**************************Sequential pre/post cut counters***********************//
      pscounter[1]++;
      h_counters[0]->Fill(0.5);
      h_Njets[1]->Fill(nGoodJets);
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
	  
	  h_jet1emfrac[1]->Fill(JetFem->at(jet1Index));
	  h_jet1eta[1]->Fill(goodJetP4.at(0).Eta());
	  if ( jet1EtaSelection[0]) {
	    h_jet1et[1]->Fill(goodJetP4.at(0).Pt());
	  }
	  h_jet2emfrac[1]->Fill(JetFem->at(jet2Index));
	  h_jet2eta[1]->Fill(goodJetP4.at(1).Eta());
	  if ( jet2EtaSelection[0]) {
	    h_jet2et[1]->Fill(goodJetP4.at(1).Pt());
	  }
	  if (dijetselection) {
	    int ijet = 2;
	    while (ijet < nGoodJets) {
	      if (goodJetP4.at(ijet).Pt()>jetall_minpt) {
		h_jetFem[1]->Fill(JetFem->at(ijet));
		h_jetallet[1]->Fill(goodJetP4.at(ijet).Pt());
	      }
	      ijet++;
	    }
	  }
	  
	  if (finaljet) {
	    fjcounter[2]++;
	    h_counters[3]->Fill(2.5);

	    photoncounter[1]++;
	    h_counters[0]->Fill(3.5);
	    for ( int iphoton = 0; iphoton < nPhots; ++iphoton) {
	      if (photonID(iphoton,1) ) {
		h_photonEt[1]->Fill(PhotonP4->at(iphoton).Pt());
		h_photonEta[1]->Fill(PhotonP4->at(iphoton).Eta());
	      }
	    }
	    h_Nphoton[1]->Fill(nPhots);
	    
	    if (photisoselection) {
	      photoncounter[2]++;
	      h_counters[3]->Fill(3.5);

	      leptoncounter[1]++;
	      h_counters[0]->Fill(4.5);
	      
	      for ( int ielec = 0; ielec < nGoodElecs; ++ielec) {
		h_elecEt[1]->Fill(goodElectronP4.at(ielec).Pt());
		h_elecEta[1]->Fill(goodElectronP4.at(ielec).Eta());
	      }
	      h_Nelec[1]->Fill(nGoodElecs);
	      
	      for ( int imuon = 0; imuon < nGoodMuons; ++imuon) {
		h_muonEt[1]->Fill(goodMuonP4.at(imuon).Pt());
		h_muonEta[1]->Fill(goodMuonP4.at(imuon).Eta());
	      }
	      h_Nmuon[1]->Fill(nGoodMuons);
	      
	      if (leptonveto) {
		leptoncounter[2]++;
		h_counters[3]->Fill(4.5);
		dphicounter[1]++;
		h_counters[0]->Fill(5.5);
		
		h_jet12dphi[1]->Fill(ROOT::Math::VectorUtil::DeltaPhi(goodJetP4.at(0),goodJetP4.at(1)));
		
		for (int jet = 2; jet < nGoodJets; ++jet) 
		  h_jetmetdphi[1]->Fill(jetmetdphi[jet]);
		
		if (dphiselection) {
		  dphicounter[2]++;
		  h_counters[3]->Fill(5.5);
		  //Selection based on MET/DPhi(Jet1,2,MET)
		  metcounter[1]++;
		  h_counters[0]->Fill(6.5);
		  
		  h_MET[1]->Fill(metlike);
		}//dphi
	      }//leptons
	    }//photons
	  }//finaljets
	}//triggers
      }//presel
      //**************************N-1 cut counters***********************//
      if (
	  triggerselection &&
	  finaljet         &&
	  photisoselection &&
	  leptonveto       &&
	  dphiselection
	  ) {
	pscounter[3]++;
	h_counters[2]->Fill(0.5);}
      if (
	  preselection     &&
	  finaljet         &&
	  photisoselection &&
	  leptonveto       &&
	  dphiselection
	  ) {
	trcounter[3]++;
	h_counters[2]->Fill(1.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  photisoselection &&
	  leptonveto       &&
	  dphiselection
	  ) {
	fjcounter[3]++;
	h_counters[2]->Fill(2.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  leptonveto       &&
	  dphiselection
	  ) {
	photoncounter[3]++;
	h_counters[2]->Fill(3.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  photisoselection &&
	  dphiselection
	  ) {
	leptoncounter[3]++;
	h_counters[2]->Fill(4.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  photisoselection &&
	  leptonveto 
	  ) {
	dphicounter[3]++;
	h_counters[2]->Fill(5.5);}
      if (
	  preselection     &&
	  triggerselection &&
	  finaljet         &&
	  dphiselection    &&
	  photisoselection &&
	  leptonveto   
	  ) {
	metcounter[3]++;
	h_counters[2]->Fill(6.5);}
      
      ////////////
      
      nJetSelection[1] = 
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
      
      hltTriggerSelection[1] = 
	nJetSelection[0]      &&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	jetmetdphiSelection[0]&&
	photonSelection[0]     &&
	leptonVeto[0];
      
      jet1PtSelection[1] =
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1EtaSelection[0]    &&
	//jet2PtSelection[0]     &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
    
      jet2PtSelection[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	//jet1PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
    
      jet1EtaSelection[1] = 
	nJetSelection[0]       && 
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
    
      jet2EtaSelection[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2PtSelection[0]     &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
    
      excessiveJetVeto[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2PtSelection[0]     &&
	jet2EtaSelection[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
      
      jet12dphiSelection[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jetmetdphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
      
      jetmetdphiSelection[1] = 
	nJetSelection[0]      &&
	hltTriggerSelection[0]&&
	jet1PtSelection[0]    &&
	jet2PtSelection[0]    &&
	jet1EtaSelection[0]   &&
	jet2EtaSelection[0]   &&
	excessiveJetVeto[0]   &&
	jet12dphiSelection[0] &&
	photonSelection[0]     &&
	leptonVeto[0];
    
      photonSelection[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	leptonVeto[0];

      leptonVeto[1] = 
	nJetSelection[0]       &&
	hltTriggerSelection[0] &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	excessiveJetVeto[0]    &&
	jet12dphiSelection[0]  &&
	jetmetdphiSelection[0] &&
	photonSelection[0];
      
      ///////////      
      
      ////////////////////////////////////
      //pre cut plots
      ////////////////////////////////////
      h_Njets[0]->Fill(nGoodJets);
      
      if (nGoodJets > 0) {
	h_jet1et[0]->Fill(goodJetP4.at(0).Pt());
	h_jet1eta[0]->Fill(goodJetP4.at(0).Eta());
	h_jet1emfrac[0]->Fill(JetFem->at(jet1Index));
	h_jetmetdphi[0]->Fill(jetmetdphi[0]);
      }
      
      if (nGoodJets > 1) {
	h_jet2et[0]->Fill(goodJetP4.at(1).Pt());
	h_jet2eta[0]->Fill(goodJetP4.at(1).Eta());
	h_jet2emfrac[0]->Fill(JetFem->at(jet2Index));
	h_jetmetdphi[0]->Fill(jetmetdphi[1]);
      
	h_jet12dphi[0]->Fill(ROOT::Math::VectorUtil::DeltaPhi(goodJetP4.at(0),goodJetP4.at(1)));
      
      }

      int ijet = 2;
      while (ijet < nGoodJets) {
	h_jetFem[0]->Fill(JetFem->at(ijet));
	h_jetallet[0]->Fill(goodJetP4.at(ijet).Pt());
	ijet++;
      }
    
      h_MET[0]->Fill(met);
    
      for ( int ielec = 0; ielec < nGoodElecs; ++ielec) {
	h_elecEt[0]->Fill(goodElectronP4.at(ielec).Pt());
	h_elecEta[0]->Fill(goodElectronP4.at(ielec).Eta());
      }
      h_Nelec[0]->Fill(nGoodElecs);

      for ( int imuon = 0; imuon < nGoodMuons; ++imuon) {
	h_muonEt[0]->Fill(goodMuonP4.at(imuon).Pt());
	h_muonEta[0]->Fill(goodMuonP4.at(imuon).Eta());
      }
      h_Nmuon[0]->Fill(nGoodMuons);
      
      for ( int iphoton = 0; iphoton < nPhots; ++iphoton) {
	h_photonEt[0]->Fill(PhotonP4->at(iphoton).Pt());
	h_photonEta[0]->Fill(PhotonP4->at(iphoton).Eta());
      }
      h_Nphoton[0]->Fill(nPhots);
      
    
      ////////////////////////////////////
      //individual cut plots
      ////////////////////////////////////
    
      if (nJetSelection[0]) {
	//h_Njets[1][0]->Fill(nGoodJets);
	h_selections[0]->Fill(0.5);}
    
      if (hltTriggerSelection[0]) {
	h_selections[0]->Fill(1.5);}
    
      if (leptonVeto[0]) {
	/*
	  for ( int ielec = 0; ielec < nGoodElecs; ++ielec) {
	  h_elecEt[1]->Fill(goodElectronP4.at(ielec).Pt());
	  h_elecEta[1]->Fill(goodElectronP4.at(ielec).Eta());
	  }
	  h_Nelec[1]->Fill(nGoodElecs);
	  for ( int imuon = 0; imuon < nMuons; ++imuon) {
	  h_muonEt[1]->Fill(goodMuonP4.at(imuon).Pt());
	  h_muonEta[1]->Fill(goodMuonP4.at(imuon).Eta());
	  }
	  h_Nmuon[1]->Fill(nMuons);
	  for ( int iphoton = 0; iphoton < nPhots; ++iphoton) {
	  h_photonEt[1]->Fill(PhotonP4->at(iphoton).Pt());
	  h_photonEta[1]->Fill(PhotonP4->at(iphoton).Eta());
	  }
	  h_Nphoton[1]->Fill(nPhots);
	*/
      
	h_selections[0]->Fill(2.5);}
    
    
      if (jet1PtSelection[0]) {
	//h_jet1et[1]->Fill(goodJetP4.at(0).Pt());
	h_selections[0]->Fill(3.5);}
    
      if (jet2PtSelection[0]) {
	//h_jet2et[1]->Fill(goodJetP4.at(1).Pt());
	h_selections[0]->Fill(4.5);}

      if (jet1EtaSelection[0]) {
	//h_jet1eta[1]->Fill(goodJetP4.at(0).Eta());
	h_selections[0]->Fill(5.5);}

      if (jet2EtaSelection[0]) {
	//h_jet2eta[1]->Fill(goodJetP4.at(1).Eta());
	h_selections[0]->Fill(6.5);}

      /*
      //What's going on here???
      ijet = 2;
      while (ijet < nGoodJets) {
      if (goodJetP4.at(ijet).Pt()>jetall_minpt)
      h_jetFem[1]->Fill(JetFem->at(ijet));
      ijet++;
      }
      */
      if (excessiveJetVeto[0]) {
	/*
	  ijet = 2;
	  while (ijet < nGoodJets) {
	  if (goodJetP4.at(ijet).Pt()>jetall_minpt)
	  h_jetallet[1]->Fill(goodJetP4.at(ijet).Pt());
	  ijet++;
	  }
	*/
	h_selections[0]->Fill(7.5);}

      if (jet12dphiSelection[0]) {
	//h_jet12dphi[1]->Fill(ROOT::Math::VectorUtil::DeltaPhi(goodJetP4.at(0),goodJetP4.at(1));
	h_selections[0]->Fill(8.5);}

      ///
    
      if (jetmetdphiSelection[0]) {
	//h_jetmetdphi[1]->Fill(jetmetdphi);
	h_selections[0]->Fill(9.5);}

      if (photonSelection[0]) {
	//h_jetmetdphi[1]->Fill(jetmetdphi);
	h_selections[0]->Fill(10.5);}

      //////////////////////////////////////
      ///////////////////////////////////////////
      //N-1 plots
      //////////////////////////////////////////
  
      if (nJetSelection[1]) {
	h_Njets[2]->Fill(nGoodJets);
	h_selections[1]->Fill(0.5);}

      if (hltTriggerSelection[1]) {
	h_selections[1]->Fill(1.5);}
      
      if (leptonVeto[1]) {
	for ( int ielec = 0; ielec < nGoodElecs; ++ielec) {
	  h_elecEt[2]->Fill(goodElectronP4.at(ielec).Pt());
	  h_elecEta[2]->Fill(goodElectronP4.at(ielec).Eta());
	}
	h_Nelec[2]->Fill(nGoodElecs);

	for ( int imuon = 0; imuon < nMuons; ++imuon) {
	  h_muonEt[2]->Fill(goodMuonP4.at(imuon).Pt());
	  h_muonEta[2]->Fill(goodMuonP4.at(imuon).Eta());
	}
	h_Nmuon[2]->Fill(nMuons);

	for ( int iphoton = 0; iphoton < nPhots; ++iphoton) {
	  h_photonEt[2]->Fill(PhotonP4->at(iphoton).Pt());
	  h_photonEta[2]->Fill(PhotonP4->at(iphoton).Eta());
	}
	h_Nphoton[2]->Fill(nPhots);

	h_selections[1]->Fill(2.5);
      }
      
      if (jet1PtSelection[1]) {
	h_jet1et[2]->Fill(goodJetP4.at(0).Pt());
	h_selections[1]->Fill(3.5);}
      
      if (jet2PtSelection[1]) {
	h_jet2et[2]->Fill(goodJetP4.at(1).Pt());
	h_selections[1]->Fill(4.5);}
      
      if (jet1EtaSelection[1]) {
	h_jet1eta[2]->Fill(goodJetP4.at(0).Eta());
	h_jet1emfrac[2]->Fill(JetFem->at(jet1Index));
	h_selections[1]->Fill(5.5);}
      
      if (jet2EtaSelection[1]) {
	h_jet2eta[2]->Fill(goodJetP4.at(1).Eta());
	h_jet2emfrac[2]->Fill(JetFem->at(jet2Index));
	h_selections[1]->Fill(6.5);}
      
      ijet = 2;
      while (ijet < nGoodJets) {
	if (goodJetP4.at(ijet).Pt()>jetall_minpt)
	  h_jetFem[2]->Fill(JetFem->at(ijet));
	ijet++;
      }

      if (excessiveJetVeto[1]) {
	ijet = 2;
	while (ijet < nGoodJets) {
	  if (goodJetP4.at(ijet).Pt()>jetall_minpt)
	    h_jetallet[2]->Fill(goodJetP4.at(ijet).Pt());
	  ijet++;
	}
	h_selections[1]->Fill(7.5);}
    
      if (jet12dphiSelection[1]) {
	h_jet12dphi[2]->Fill(ROOT::Math::VectorUtil::DeltaPhi(goodJetP4.at(0),goodJetP4.at(1)));
	h_selections[1]->Fill(8.5);}
	  

      if (jetmetdphiSelection[1]) {
	for (int jet = 0; jet < nGoodJets; ++jet) 
	  h_jetmetdphi[2]->Fill(jetmetdphi[jet]);
	h_selections[1]->Fill(9.5);}
      
      if (photonSelection[1]) {
	for (int phot = 0; phot < nPhots; ++phot) {
	  h_photonEt[2]->Fill(PhotonP4->at(phot).Pt());
	  h_photonEta[2]->Fill(PhotonP4->at(phot).Eta());
	}
	h_selections[1]->Fill(10.5);}
      
      //////////////////////////////////////
      
      
  
      //Full selection
      ////////////////////////////////////////
      bool analysis_step;
      analysis_step = 
	jetmetdphiSelection[0];
      
      bool selections = 
	excessiveJetVeto[0]    &&
	hltTriggerSelection[0] &&
	nJetSelection[0]       &&
	jet1PtSelection[0]     &&
	jet2PtSelection[0]     &&
	jet1EtaSelection[0]    &&
	jet2EtaSelection[0]    &&
	jet12dphiSelection[0]  &&
	analysis_step          &&
	leptonVeto[0];
    
      if (selections) {
      
	//if (MET>1000) {
	//printf("MET %2.2f: x=%2.2f ,y=%2.2f, phi=%2.2f\ngenMET %2.2f: x=%2.2f ,y=%2.2f, phi=%2.2f\n",MET,METx,METy,METphi_fullcorr,genMET,genMETx,genMETy,genMETphi);
	//}
      
	h_selections[0]->Fill(20.5);
	h_Njets[3]->Fill(nGoodJets);
      
	h_jet1et[3]->Fill(goodJetP4.at(0).Pt());
	h_jet2et[3]->Fill(goodJetP4.at(1).Pt());
      
	h_MET[3]->Fill(met);

	for (int ijet = 2; ijet < nGoodJets; ++ijet) {
	  if (goodJetP4.at(ijet).Pt() > jetall_minpt) {
	    h_jetFem[3]->Fill(JetFem->at(ijet));
	    h_jetallet[3]->Fill(goodJetP4.at(ijet).Pt());
	  }
	}

	h_jet1eta[3]->Fill(goodJetP4.at(0).Eta());
	h_jet2eta[3]->Fill(goodJetP4.at(1).Eta());
	h_jet1emfrac[3]->Fill(JetFem->at(jet1Index));
	h_jet2emfrac[3]->Fill(JetFem->at(jet2Index));
      
	//total number of photons/leptons in event
	for ( int ielec = 0; ielec < nGoodElecs; ++ielec) {
	  h_elecEt[3]->Fill(goodElectronP4.at(ielec).Pt());
	  h_elecEta[3]->Fill(goodElectronP4.at(ielec).Eta());
	}
	h_Nelec[3]->Fill(nGoodElecs);
      
	for ( int imuon = 0; imuon < nMuons; ++imuon) {
	  h_muonEt[3]->Fill(goodMuonP4.at(imuon).Pt());
	  h_muonEta[3]->Fill(goodMuonP4.at(imuon).Eta());
	}
	h_Nmuon[3]->Fill(nMuons);
	
	for ( int iphoton = 0; iphoton < nPhots; ++iphoton) {
	  h_photonEt[3]->Fill(PhotonP4->at(iphoton).Pt());
	  h_photonEta[3]->Fill(PhotonP4->at(iphoton).Eta());
	}
	h_Nphoton[3]->Fill(nPhots);
	
	TLorentzVector jet1, jet2;
	h_jet12dphi[3]->Fill(ROOT::Math::VectorUtil::DeltaPhi(goodJetP4.at(0),goodJetP4.at(1)));
      
	for (int jet = 2; jet < nGoodJets; ++jet) 
	  h_jetmetdphi[3]->Fill(jetmetdphi[jet]);
      }//finished with final selection plots
    }//out of preselection
  }//end loop over all events
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
  h_selections[0]->GetXaxis()->SetBinLabel(8,"E^{MAX}_{T}^{jets}");
  h_selections[0]->GetXaxis()->SetBinLabel(9,"#Delta#phi(Jet_{1}, Jet_{2})");
  h_selections[0]->GetXaxis()->SetBinLabel(10,"#Delta#phi(Jet, #slashE_{T})");
  h_selections[0]->GetXaxis()->SetBinLabel(11,"#gamma p_{T} > 150 GeV");
  h_selections[0]->GetXaxis()->SetBinLabel(21,"ALL");
  h_selections[0]->SetStats(kFALSE);

  h_selections[1]->GetXaxis()->SetBinLabel(1,"nJets");
  h_selections[1]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");
  h_selections[1]->GetXaxis()->SetBinLabel(3,"e/#mu Veto");
  h_selections[1]->GetXaxis()->SetBinLabel(4,"E_{T}^{Jet_{1}}");
  h_selections[1]->GetXaxis()->SetBinLabel(5,"E_{T}^{Jet_{2}}");
  h_selections[1]->GetXaxis()->SetBinLabel(6,"#eta_{Jet_{1}}");
  h_selections[1]->GetXaxis()->SetBinLabel(7,"#eta_{Jet_{2}}");
  h_selections[1]->GetXaxis()->SetBinLabel(8,"E^{MAX}_{T}^{jets}");
  h_selections[1]->GetXaxis()->SetBinLabel(9,"#Delta#phi(Jet_{1}, Jet_{2})");
  h_selections[1]->GetXaxis()->SetBinLabel(10,"#Delta#phi(Jet, #slashE_{T})");
  h_selections[1]->GetXaxis()->SetBinLabel(11,"#gamma p_{T} > 150 GeV");
  h_selections[1]->GetXaxis()->SetBinLabel(21,"Total Events");
  //h_selections[1]->GetXaxis()->SetBinLabel(22,"#sigma");
  //h_selections[1]->GetXaxis()->SetBinLabel(23,"#epsilon");
  //h_selections[1]->GetXaxis()->SetBinLabel(20,"#integralL dt");
  h_selections[1]->SetStats(kFALSE);
  
  for (int mine = 0; mine < 4; ++mine) {
    sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    //sprintf(ytitle,"Raw Events passing cuts");
    h_counters[mine]->Scale(scale_);
    h_counters[mine]->GetYaxis()->SetTitle(ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(1,"2 Loose ID Jets p_{T} > 50 GeV, 1 #gamma p_{T} > 100 GeV");
    h_counters[mine]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");

    if (strictDiJets)
      h_counters[mine]->GetXaxis()->SetBinLabel(3,"strict di-jet cuts");
    else
      h_counters[mine]->GetXaxis()->SetBinLabel(3,"loose di-jet cuts ");

    h_counters[mine]->GetXaxis()->SetBinLabel(4,"#gamma iso");
    h_counters[mine]->GetXaxis()->SetBinLabel(5,"e/#mu Veto");
    sprintf(ytitle,"#Delta#phi(J_{1},#slashE_{T}) > %2.2f, #Delta#phi(J_{2},#slashE_{T}) > %2.2f",cut_jet1metdphi,cut_jet2metdphi);
    h_counters[mine]->GetXaxis()->SetBinLabel(6,ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(10,"Nevents");
    h_counters[mine]->SetStats(kFALSE);
    
    sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    h_Njets[mine]->Scale(scale_);
    h_Njets[mine]->GetYaxis()->SetTitle(ytitle);
    
    h_Nelec[mine]->Scale(scale_);
    h_Nelec[mine]->GetYaxis()->SetTitle(ytitle);

    h_Nmuon[mine]->Scale(scale_);
    h_Nmuon[mine]->GetYaxis()->SetTitle(ytitle);
    
    h_Nphoton[mine]->Scale(scale_);
    h_Nphoton[mine]->GetYaxis()->SetTitle(ytitle);
    
    h_jet1eta[mine]->Scale(scale_);
    h_jet1eta[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2eta[mine]->Scale(scale_);
    h_jet2eta[mine]->GetYaxis()->SetTitle(ytitle);
    h_jetalleta[mine]->Scale(scale_);
    h_jetalleta[mine]->GetYaxis()->SetTitle(ytitle);

    h_jet1emfrac[mine]->Scale(scale_);
    h_jet1emfrac[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2emfrac[mine]->Scale(scale_);
    h_jet2emfrac[mine]->GetYaxis()->SetTitle(ytitle);
    h_jetFem[mine]->Scale(scale_);
    h_jetFem[mine]->GetYaxis()->SetTitle(ytitle);
      
    h_jet12dphi[mine]->Scale(scale_);
    h_jet12dphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet1metdphi[mine]->Scale(scale_);
    h_jet1metdphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2metdphi[mine]->Scale(scale_);
    h_jet2metdphi[mine]->GetYaxis()->SetTitle(ytitle);
    h_jetmetdphi[mine]->Scale(scale_);
    h_jetmetdphi[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 5 GeV / %2.0f pb^{-1}",luminosity_);
    h_jet1et[mine]->Scale(scale_);
    h_jet1et[mine]->GetYaxis()->SetTitle(ytitle);
    h_jet2et[mine]->Scale(scale_);
    h_jet2et[mine]->GetYaxis()->SetTitle(ytitle);      

    sprintf(ytitle,"Events / 5 GeV / %2.0f pb^{-1}",luminosity_);
    h_MET[mine]->Scale(scale_);
    h_MET[mine]->GetYaxis()->SetTitle(ytitle);

    sprintf(ytitle,"Events / 5 GeV / %2.0f pb^{-1}",luminosity_);
    h_jetallet[mine]->Scale(scale_);
    h_jetallet[mine]->GetYaxis()->SetTitle(ytitle);      
    h_elecEt[mine]->Scale(scale_);
    h_elecEt[mine]->GetYaxis()->SetTitle(ytitle);
    h_muonEt[mine]->Scale(scale_);
    h_muonEt[mine]->GetYaxis()->SetTitle(ytitle);
    h_photonEt[mine]->Scale(scale_);
    h_photonEt[mine]->GetYaxis()->SetTitle(ytitle);

  }

  //
  int Nevents = totalcounter;
  std::cout<<std::setw(18)<<"Cut Series"<<std::setw(15)<<"Nevents"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"preselection"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"triggers"<<std::setw(3)<<" - "
	   <<std::setw(10)<<"finaljet"<<std::setw(3)<<" - "
	   <<std::setw(10)<<"photisosel"<<std::setw(3)<<" - "
	   <<std::setw(10)<<"leptonveto"<<std::setw(3)<<" - "
	   <<std::setw(14)<<"dphiselection"<<std::setw(3)<<" - "
	   <<std::setw(12)<<"metselection"<<std::endl;
  std::cout<<std::setw(18)<<"Individual:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[0]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[0]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[0]<<std::setw(3)<<" - "
	   <<std::setw(10)<<photoncounter[0]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[0]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[0]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[0]<<std::endl;
  std::cout<<std::setw(18)<<"Sequential-Pre:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[1]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[1]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[1]<<std::setw(3)<<" - "
	   <<std::setw(10)<<photoncounter[1]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[1]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[1]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[1]<<std::endl;
  std::cout<<std::setw(18)<<"Sequential-Post:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[2]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[2]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[2]<<std::setw(3)<<" - "
	   <<std::setw(10)<<photoncounter[2]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[2]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[2]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[2]<<std::endl;
  std::cout<<std::setw(18)<<"N-1:"<<std::setw(15)<<Nevents<<std::setw(3)<<" - "
	   <<std::setw(12)<<pscounter[3]<<std::setw(3)<<" - "
	   <<std::setw(12)<<trcounter[3]<<std::setw(3)<<" - "
	   <<std::setw(10)<<fjcounter[3]<<std::setw(3)<<" - "
	   <<std::setw(10)<<photoncounter[3]<<std::setw(3)<<" - "
	   <<std::setw(10)<<leptoncounter[3]<<std::setw(3)<<" - "
	   <<std::setw(14)<<dphicounter[3]<<std::setw(3)<<" - "
	   <<std::setw(12)<<metcounter[3]<<std::endl;




  
  //Write out file and histograms
  for (int step = 0; step < NSTEPS; ++step) {
    h_Njets[step]->Write();

    h_jet1et[step]  ->Write();
    h_jet2et[step]  ->Write();
    h_jetallet[step]->Write();  

    h_MET[step]   ->Write();
    
    h_jet1metdphi[step]->Write();
    h_jet2metdphi[step]->Write();
    h_jetmetdphi[step] ->Write();
    h_jet12dphi[step]  ->Write();

    h_jet1eta[step]  ->Write();
    h_jet2eta[step]  ->Write();
    h_jetalleta[step]->Write();
     
    h_jet1emfrac[step]->Write();
    h_jet2emfrac[step]->Write();
    h_jetFem[step]    ->Write();
     
    h_Nelec[step]    ->Write();
    h_elecEta[step]  ->Write();
    h_elecEt[step]   ->Write();

    h_Nmuon[step]    ->Write();
    h_muonEta[step]  ->Write();
    h_muonEt[step]   ->Write();

    h_Nphoton[step]    ->Write();
    h_photonEta[step]  ->Write();
    h_photonEt[step]   ->Write();

    h_counters[step] ->Write();

  }
   
  for (int hist = 0; hist < 2; ++hist) {
    h_selections[hist]->Write();
  }
   
  file->cd();
  file->Write();
}


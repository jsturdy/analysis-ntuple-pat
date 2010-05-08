#define firstData_cxx
#include "firstData.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "helperFunctions.h"

#define NBINS 1000
#define JETRANGE    100
#define JETDPTRANGE 100
#define METRANGE    100
//#define 
//#define 

void firstData::Loop() {
  if (fChain == 0) return;
  char tmpfile[128];
  sprintf(tmpfile,"%s",outfilename_.c_str());
  TFile *file = new TFile(tmpfile,"RECREATE");
  file->cd();

  Long64_t nentries = fChain->GetEntries();
  int numdijetevents[4] = {0};
  std::vector<int> calodijeteventnumbers;
  std::vector<int> jptdijeteventnumbers;
  std::vector<int> pfdijeteventnumbers;
  std::vector<int> trackdijeteventnumbers;

  fChain->SetBranchStatus("*",1);  // disable all branches


  //--- 1D histograms for plotting general varibles
  TH1F *h_jet12dPt[4];
  TH1F *h_jet12avgPt[4];
  TH1F *h_jet12dphi[4];
  TH1F *h_jet12dR[4];
  TH1F *h_jet1metdphi[4][3];
  TH1F *h_jet2metdphi[4][3];
  TH1F *h_metmhtdphi[4][3];
  TH1F *h_met[4][3];
  TH1F *h_metperp[4][3];
  TH1F *h_metpara[4][3];

  //--- 2D histograms for seeking trends
  //vs avg energy
  TH2F *h2_jet12dPtvsavgPt[2][4];
  //vs dphi
  TH2F *h2_jet12dPtvsdphi[4];
  //vs dR
  TH2F *h2_jet12dPtvsdR[4];
  //vs dPt
  TH2F *h2_jet1metdphivsdPt[4][3];
  TH2F *h2_jet2metdphivsdPt[4][3];
  TH2F *h2_metmhtdphivsdPt[4][3];
  //vs avg Pt
  TH2F *h2_jet1metdphivsavgPt[2][4][3];
  TH2F *h2_jet2metdphivsavgPt[2][4][3];
  TH2F *h2_jet1metdphivsdphi[4][3];
  TH2F *h2_jet2metdphivsdphi[4][3];
  TH2F *h2_metmhtdphivsavgPt[2][4][3];
  TH2F *h2_metvsdPt[4][3];
  TH2F *h2_metvsjet12dphi[4][3];
  TH2F *h2_metvsavgPt[2][4][3];
  TH2F *h2_mhtvsdPt[4];
  TH2F *h2_mhtvsavgPt[2][4];

  TH2F *h2_metvsdijetbisectorphi[4][3];
  TH2F *h2_metdijetbisectordphivsdPt[4][3];
  TH2F *h2_metdijetbisectordphivsavgPt[2][4][3];

  TH2F *h2_metperpvsdijetbisectorphi[4][3];
  TH2F *h2_metperpdijetbisectordphivsdPt[4][3];
  TH2F *h2_metperpdijetbisectordphivsavgPt[2][4][3];

  TH2F *h2_metparavsdijetbisectorphi[4][3];
  TH2F *h2_metparadijetbisectordphivsdPt[4][3];
  TH2F *h2_metparadijetbisectordphivsavgPt[2][4][3];

  //MET vs dEta between leading 2 jets with avg. Pt > 30 GeV
  TH2F *h2_metvsjet12deta[4][3];
  TH2F *h2_metperpvsjet12deta[4][3];
  TH2F *h2_metparavsjet12deta[4][3];

  //--- Special plots
  //MET perp to bisecting axis, bins of avg Pt and dphij12, plot mean and rms as well
  //define positive to be towards the jet with the higher Pt
  TH2F *h2_metperpvsjet12dphi[4][3];
  TH2F *h2_metperpvsavgPt[2][4][3];
  TH2F *h2_metperpvsmet[4][3];
  TH2F *h2_metperpvspara[4][3];
  //MET paralell to bisecting axis
  TH2F *h2_metparavsjet12dphi[4][3];
  TH2F *h2_metparavsavgPt[2][4][3];
  TH2F *h2_metparavsmet[4][3];
  //dphi jet1 met vs dphi jet2 met
  TH2F *h2_j1metdphivsj2metdphi[4][3];
  //dphi jet1 mht vs dphi jet2 mht
  TH2F *h2_j1mhtdphivsj2mhtdphi[4];
  //Difference in Pt (central, central-endcap, same endcaps, opposite endcaps)
  TH1F *h_jet12dPtbothcentral[4];
  TH1F *h_jet12dPtcentralendcaps[4];
  TH1F *h_jet12dPtsameendcaps[4];
  TH1F *h_jet12dPtoppositeendcaps[4];
  //difference in Pt function of eta
  TH2F *h2_jet12dPtvsetaj1[4];
  TH2F *h2_jet12dPtvsetaj2[4];
  //difference in Pt function of eta in bins of avg. Pt
  //find events with jet 1 having large EM fraction, plot above distributions
  //define positive to be towards the jet with the larger emfraction


  std::string jettitle[4] = {"Calo","JPT","PF","Track"};
  std::string jetnames[4] = {"calo","jpt","pf","track"};
  std::string metitile[3] = {"Calo","PF","TC"};
  std::string metnames[3] = {"calo","pf","tc"};

  char histname[128];
  char histtitle[128];
  
  //Calo Jet histograms
  //sprintf(histname,"",);
  //sprintf(histtitle,"",);
  h_jet12dPt[0]       = new TH1F("h_calojet12dPt",        "Calo Jet 12 #Deltap_{T}",     NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12avgPt[0]     = new TH1F("h_calojet12avgPt",      "Calo Jet 12 avg Pt",  NBINS, 0.,         JETRANGE);
  h_jet12dR[0]        = new TH1F("h_calojet12dR",         "Calo Jet 12 dR",      NBINS, 0.,         10.);
  h_jet12dphi[0]      = new TH1F("h_calojet12dphi",       "Calo Jet 12 #Delta#phi",    NBINS,0.,       M_PI);
  //calo met
  h_jet1metdphi[0][0] = new TH1F("h_calojet1calometdphi", "Calo #Delta#phi(Jet1, Calo MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[0][0] = new TH1F("h_calojet2calometdphi", "Calo #Delta#phi(Jet2, Calo MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[0][0]  = new TH1F("h_calometcalomhtdphi",  "Calo #Delta#phi(MHT, Calo MET)",  NBINS,0.,    M_PI);
  h_met[0][0]         = new TH1F("h_calometcalo",         "Calo MET Calo",             NBINS, 0.,      METRANGE);
  h_metperp[0][0]     = new TH1F("h_calometperpcalo",     "Calo MET perp Calo",        NBINS,-METRANGE,METRANGE);
  h_metpara[0][0]     = new TH1F("h_calometparacalo",     "Calo MET para Calo",        NBINS,-METRANGE,METRANGE);
  //pf met
  h_jet1metdphi[0][1] = new TH1F("h_calojet1pfmetdphi",   "Calo #Delta#phi(Jet1, PF MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[0][1] = new TH1F("h_calojet2pfmetdphi",   "Calo #Delta#phi(Jet2, PF MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[0][1]  = new TH1F("h_pfmetcalomhtdphi",    "Calo #Delta#phi(MHT, PF MET)",  NBINS,0.,    M_PI);
  h_met[0][1]         = new TH1F("h_pfmetcalo",           "PF MET Calo",             NBINS, 0.,      METRANGE);
  h_metperp[0][1]     = new TH1F("h_pfmetperpcalo",       "PF MET perp Calo",        NBINS,-METRANGE,METRANGE);
  h_metpara[0][1]     = new TH1F("h_pfmetparacalo",       "PF MET para Calo",        NBINS,-METRANGE,METRANGE);
  //tc met
  h_jet1metdphi[0][2] = new TH1F("h_calojet1tcmetdphi",   "Calo #Delta#phi(Jet1, TC MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[0][2] = new TH1F("h_calojet2tcmetdphi",   "Calo #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[0][2]  = new TH1F("h_tcmetcalomhtdphi",    "Calo #Delta#phi(MHT, TC MET)",  NBINS,0.,    M_PI);
  h_met[0][2]         = new TH1F("h_tcmetcalo",           "TC MET Calo",             NBINS, 0.,      METRANGE);
  h_metperp[0][2]     = new TH1F("h_tcmetperpcalo",       "TC MET perp Calo",        NBINS,-METRANGE,METRANGE);
  h_metpara[0][2]     = new TH1F("h_tcmetparacalo",       "TC MET para Calo",        NBINS,-METRANGE,METRANGE);

  //JPT Jet histograms
  h_jet12dPt[1]       = new TH1F("h_jptjet12dPt",        "JPT Jet 12 #Deltap_{T}",     NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12avgPt[1]     = new TH1F("h_jptjet12avgPt",      "JPT Jet 12 avg Pt",  NBINS, 0.,         JETRANGE);
  h_jet12dR[1]        = new TH1F("h_jptjet12dR",         "JPT Jet 12 dR",      NBINS, 0.,         10.);
  h_jet12dphi[1]      = new TH1F("h_jptjet12dphi",       "JPT Jet 12 #Delta#phi",    NBINS,0.,       M_PI);
  //calo met
  h_jet1metdphi[1][0] = new TH1F("h_jptjet1calometdphi", "JPT #Delta#phi(Jet1, Calo MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[1][0] = new TH1F("h_jptjet2calometdphi", "JPT #Delta#phi(Jet2, Calo MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[1][0]  = new TH1F("h_calometjptmhtdphi",  "JPT #Delta#phi(MHT, Calo MET)",  NBINS,0.,    M_PI);
  h_met[1][0]         = new TH1F("h_calometjpt",         "Calo MET JPT",             NBINS, 0.,      METRANGE);
  h_metperp[1][0]     = new TH1F("h_calometperpjpt",     "Calo MET perp JPT",        NBINS,-METRANGE,METRANGE);
  h_metpara[1][0]     = new TH1F("h_calometparajpt",     "Calo MET para JPT",        NBINS,-METRANGE,METRANGE);
  //pf met
  h_jet1metdphi[1][1] = new TH1F("h_jptjet1pfmetdphi",   "JPT #Delta#phi(Jet1, PF MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[1][1] = new TH1F("h_jptjet2pfmetdphi",   "JPT #Delta#phi(Jet2, PF MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[1][1]  = new TH1F("h_pfmetjptmhtdphi",    "JPT #Delta#phi(MHT, PF MET)",  NBINS,0.,    M_PI);
  h_met[1][1]         = new TH1F("h_pfmetjpt",           "PF MET JPT",             NBINS, 0.,      METRANGE);
  h_metperp[1][1]     = new TH1F("h_pfmetperpjpt",       "PF MET perp JPT",        NBINS,-METRANGE,METRANGE);
  h_metpara[1][1]     = new TH1F("h_pfmetparajpt",       "PF MET para JPT",        NBINS,-METRANGE,METRANGE);
  //tc met
  h_jet1metdphi[1][2] = new TH1F("h_jptjet1tcmetdphi",   "JPT #Delta#phi(Jet1, TC MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[1][2] = new TH1F("h_jptjet2tcmetdphi",   "JPT #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[1][2]  = new TH1F("h_tcmetjptmhtdphi",    "JPT #Delta#phi(MHT, TC MET)",  NBINS,0.,    M_PI);
  h_met[1][2]         = new TH1F("h_tcmetjpt",           "TC MET JPT",             NBINS, 0.,      METRANGE);
  h_metperp[1][2]     = new TH1F("h_tcmetperpjpt",       "TC MET perp JPT",        NBINS,-METRANGE,METRANGE);
  h_metpara[1][2]     = new TH1F("h_tcmetparajpt",       "TC MET para JPT",        NBINS,-METRANGE,METRANGE);

  //PF Jet histograms
  h_jet12dPt[2]       = new TH1F("h_pfjet12dPt",        "PF Jet 12 #Deltap_{T}",     NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12avgPt[2]     = new TH1F("h_pfjet12avgPt",      "PF Jet 12 avg Pt",  NBINS, 0.,         JETRANGE);
  h_jet12dR[2]        = new TH1F("h_pfjet12dR",         "PF Jet 12 dR",      NBINS, 0.,         10.);
  h_jet12dphi[2]      = new TH1F("h_pfjet12dphi",       "PF Jet 12 #Delta#phi",    NBINS,0.,       M_PI);
  //calo met
  h_jet1metdphi[2][0] = new TH1F("h_pfjet1calometdphi", "PF #Delta#phi(Jet1, Calo MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[2][0] = new TH1F("h_pfjet2calometdphi", "PF #Delta#phi(Jet2, Calo MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[2][0]  = new TH1F("h_calometpfmhtdphi",  "PF #Delta#phi(MHT, Calo MET)",  NBINS,0.,    M_PI);
  h_met[2][0]         = new TH1F("h_calometpf",         "Calo MET PF",             NBINS, 0.,      METRANGE);
  h_metperp[2][0]     = new TH1F("h_calometperppf",     "Calo MET perp PF",        NBINS,-METRANGE,METRANGE);
  h_metpara[2][0]     = new TH1F("h_calometparapf",     "Calo MET para PF",        NBINS,-METRANGE,METRANGE);
  //pf met
  h_jet1metdphi[2][1] = new TH1F("h_pfjet1pfmetdphi",   "PF #Delta#phi(Jet1, PF MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[2][1] = new TH1F("h_pfjet2pfmetdphi",   "PF #Delta#phi(Jet2, PF MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[2][1]  = new TH1F("h_pfmetpfmhtdphi",    "PF #Delta#phi(MHT, PF MET)",  NBINS,0.,    M_PI);
  h_met[2][1]         = new TH1F("h_pfmetpf",           "PF MET PF",             NBINS, 0.,      METRANGE);
  h_metperp[2][1]     = new TH1F("h_pfmetperppf",       "PF MET perp PF",        NBINS,-METRANGE,METRANGE);
  h_metpara[2][1]     = new TH1F("h_pfmetparapf",       "PF MET para PF",        NBINS,-METRANGE,METRANGE);
  //tc met
  h_jet1metdphi[2][2] = new TH1F("h_pfjet1tcmetdphi",   "PF #Delta#phi(Jet1, TC MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[2][2] = new TH1F("h_pfjet2tcmetdphi",   "PF #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[2][2]  = new TH1F("h_tcmetpfmhtdphi",    "PF #Delta#phi(MHT, TC MET)",  NBINS,0.,    M_PI);
  h_met[2][2]         = new TH1F("h_tcmetpf",           "TC MET PF",             NBINS, 0.,      METRANGE);
  h_metperp[2][2]     = new TH1F("h_tcmetperppf",       "TC MET perp PF",        NBINS,-METRANGE,METRANGE);
  h_metpara[2][2]     = new TH1F("h_tcmetparapf",       "TC MET para PF",        NBINS,-METRANGE,METRANGE);

  //Track Jet histograms
  h_jet12dPt[3]       = new TH1F("h_trackjet12dPt",        "Track Jet 12 #Deltap_{T}",     NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12avgPt[3]     = new TH1F("h_trackjet12avgPt",      "Track Jet 12 avg Pt",  NBINS, 0.,         JETRANGE);
  h_jet12dR[3]        = new TH1F("h_trackjet12dR",         "Track Jet 12 dR",      NBINS, 0.,         10.);
  h_jet12dphi[3]      = new TH1F("h_trackjet12dphi",       "Track Jet 12 #Delta#phi",    NBINS,0.,       M_PI);
  //calo met
  h_jet1metdphi[3][0] = new TH1F("h_trackjet1calometdphi", "Track #Delta#phi(Jet1, Calo MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[3][0] = new TH1F("h_trackjet2calometdphi", "Track #Delta#phi(Jet2, Calo MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[3][0]  = new TH1F("h_calomettrackmhtdphi",  "Track #Delta#phi(MHT, Calo MET)",  NBINS,0.,    M_PI);
  h_met[3][0]         = new TH1F("h_calomettrack",         "Calo MET Track",             NBINS, 0.,      METRANGE);
  h_metperp[3][0]     = new TH1F("h_calometperptrack",     "Calo MET perp Track",        NBINS,-METRANGE,METRANGE);
  h_metpara[3][0]     = new TH1F("h_calometparatrack",     "Calo MET para Track",        NBINS,-METRANGE,METRANGE);
  //pf met
  h_jet1metdphi[3][1] = new TH1F("h_trackjet1pfmetdphi",   "Track #Delta#phi(Jet1, PF MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[3][1] = new TH1F("h_trackjet2pfmetdphi",   "Track #Delta#phi(Jet2, PF MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[3][1]  = new TH1F("h_pfmettrackmhtdphi",    "Track #Delta#phi(MHT, PF MET)",  NBINS,0.,    M_PI);
  h_met[3][1]         = new TH1F("h_pfmettrack",           "PF MET Track",             NBINS, 0.,      METRANGE);
  h_metperp[3][1]     = new TH1F("h_pfmetperptrack",       "PF MET perp Track",        NBINS,-METRANGE,METRANGE);
  h_metpara[3][1]     = new TH1F("h_pfmetparatrack",       "PF MET para Track",        NBINS,-METRANGE,METRANGE);
  //tc met
  h_jet1metdphi[3][2] = new TH1F("h_trackjet1tcmetdphi",   "Track #Delta#phi(Jet1, TC MET)", NBINS,0.,    M_PI);
  h_jet2metdphi[3][2] = new TH1F("h_trackjet2tcmetdphi",   "Track #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI);
  h_metmhtdphi[3][2]  = new TH1F("h_tcmettrackmhtdphi",    "Track #Delta#phi(MHT, TC MET)",  NBINS,0.,    M_PI);
  h_met[3][2]         = new TH1F("h_tcmettrack",           "TC MET Track",             NBINS, 0.,      METRANGE);
  h_metperp[3][2]     = new TH1F("h_tcmetperptrack",       "TC MET perp Track",        NBINS,-METRANGE,METRANGE);
  h_metpara[3][2]     = new TH1F("h_tcmetparatrack",       "TC MET para Track",        NBINS,-METRANGE,METRANGE);


  //--- Setting up the 2d Histograms
  //Calo Jets
  h2_jet12dPtvsavgPt[0][0]   = new TH2F("h2_calojet12dPtvsavgPt",      "Calo #Deltap_{T}(Jet1, Jet2) vs. dijet Pt",         NBINS, 0.,         JETRANGE,    NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsavgPt[1][0]   = new TH2F("h2_genjet12dPtvsavgPt",       "Gen #Deltap_{T}(Jet1, Jet2) vs. dijet Pt",          NBINS, 0.,         JETRANGE,    NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdphi[0]       = new TH2F("h2_calojet12dPtvsdphi",       "Calo #Deltap_{T}(Jet1, Jet2) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,        NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdR[0]         = new TH2F("h2_calojet12dPtvsdR",         "Calo #Deltap_{T}(Jet1, Jet2) vs. dR(Jet1, Jet2)",   NBINS, 0.,         10. ,        NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj1[0]      = new TH2F("h2_calojet12dPtvsetaj1",      "Calo #Deltap_{T} vs. eta Jet 1",                    NBINS,-3.,         3.,          NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj2[0]      = new TH2F("h2_calojet12dPtvsetaj2",      "Calo #Deltap_{T} vs. eta Jet 2",                    NBINS,-3.,         3.,          NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_j1mhtdphivsj2mhtdphi[0] = new TH2F("h2_caloj1mhtdphivsj2mhtdphi", "Calo #Delta#phi(Jet1, MHT) vs. #Delta#phi(Jet2, MHT)",  NBINS,0.,       M_PI,        NBINS,0.,       M_PI);
  h2_mhtvsdPt[0]             = new TH2F("h2_calomhtvsdPt",             "Calo MHT vs. #Deltap_{T}",                          NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS, 0.,         METRANGE);
  h2_mhtvsavgPt[0][0]        = new TH2F("h2_calomhtvsavgPt",           "Calo MHT vs. dijet Pt",                     NBINS, 0.,         JETRANGE,    NBINS, 0.,         METRANGE);
  h2_mhtvsavgPt[1][0]        = new TH2F("h2_genmhtvsavgPt",            "Gen MHT vs. dijet Pt",                      NBINS, 0.,         JETRANGE,    NBINS, 0.,         METRANGE);
  //calo met
  h2_jet1metdphivsdPt[0][0]        = new TH2F("h2_calojet1calometdphivsdPt",       "Calo #Delta#phi(Jet 1, Calo MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[0][0]        = new TH2F("h2_calojet2calometdphivsdPt",       "Calo #Delta#phi(Jet 2, Calo MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[0][0][0]   = new TH2F("h2_calojet1calometdphivsavgPt",     "Calo #Delta#phi(Jet 1, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][0][0]   = new TH2F("h2_genjet1calometdphivsavgPt",     "Gen #Delta#phi(Jet 1, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[0][0][0]   = new TH2F("h2_calojet2calometdphivsavgPt",     "Calo #Delta#phi(Jet 2, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][0][0]   = new TH2F("h2_genjet2calometdphivsavgPt",     "Gen #Delta#phi(Jet 2, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[0][0]         = new TH2F("h2_calometcalomhtdphivsdPt",        "Calo #Delta#phi(Calo MET, MHT) vs. #Delta#p_{t}",           NBINS, -JETDPTRANGE,  JETDPTRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[0][0][0]    = new TH2F("h2_calometcalomhtdphivsavgPt",      "Calo #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][0][0]    = new TH2F("h2_genmetcalomhtdphivsavgPt",      "Gen #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsavgPt[0][0][0]           = new TH2F("h2_calometvscaloavgPt",             "Calo MET vs. Calo dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsavgPt[1][0][0]           = new TH2F("h2_calometvsgenavgPt",             "Calo MET vs. Gen dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdPt[0][0]             = new TH2F("h2_calometvscalodPt",               "Calo MET vs. Calo #Deltap_{T}",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_jet1metdphivsdphi[0][0]    = new TH2F("h2_calojet1calometdphivsjet12dphi", "Calo #Delta#phi(Jet 1, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[0][0]    = new TH2F("h2_calojet2calometdphivsjet12dphi", "Calo #Delta#phi(Jet 2, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metvsjet12dphi[0][0]       = new TH2F("h2_calometvscalojet12dphi",         "Calo MET vs. Calo #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0,   METRANGE);
  h2_metvsjet12deta[0][0]       = new TH2F("h2_calometvscalojet12deta",         "Calo MET vs. Calo #Delta#eta(Jet1, Jet2)",              NBINS,-3.,        3.,        NBINS, 0,   METRANGE);
  h2_metvsdijetbisectorphi[0][0]           = new TH2F("h2_calometvscalodijetbisectorphi",       "Calo MET vs. Calo dijet bisector Phi",             NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0./2,  M_PI/2);
  h2_metperpvsdijetbisectorphi[0][0]       = new TH2F("h2_calometperpvscalodijetbisectorphi",   "Calo MET perp vs. Calo dijet bisector Phi",        NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[0][0]       = new TH2F("h2_calometparavscalodijetbisectorphi",   "Calo MET para vs. Calo dijet bisector Phi",        NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[0][0]       = new TH2F("h2_calometcalodijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Calo dijet bisector) vs. #Deltap_{T}",      NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[0][0][0]     = new TH2F("h2_calometcalodijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Calo dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,    NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[1][0][0]     = new TH2F("h2_calometgendijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Gen dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,    NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[0][0]   = new TH2F("h2_calometperpvscalojet12dphi",   "Calo MET perp vs. Calo #Delta#phi(Jet1, Jet2)",            NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[0][0]   = new TH2F("h2_calometparavscalojet12dphi",   "Calo MET para vs. Calo #Delta#phi(Jet1, Jet2)",            NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsjet12deta[0][0]   = new TH2F("h2_calometperpvscalojet12deta",   "Calo MET perp vs. Calo #Delta#eta(Jet1, Jet2)",            NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12deta[0][0]   = new TH2F("h2_calometparavscalojet12deta",   "Calo MET para vs. Calo #Delta#eta(Jet1, Jet2)",            NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[0][0][0]    = new TH2F("h2_calometperpvscaloavgPt",       "Calo MET perp vs. dijet Pt",                         NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[1][0][0]    = new TH2F("h2_calometperpvsgenavgPt",        "Gen MET perp vs. dijet Pt",                         NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[0][0][0]    = new TH2F("h2_calometparavscaloavgPt",       "Calo MET para vs. dijet Pt",                         NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[1][0][0]    = new TH2F("h2_calometparavsgenavgPt",        "Gen MET para vs. dijet Pt",                         NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[0][0]        = new TH2F("h2_calometperpvsmetparacalo",     "Calo MET perp vs. MET para",                         NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[0][0]         = new TH2F("h2_calometperpvsmetcalo",         "Calo MET perp vs. MET",                              NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[0][0]         = new TH2F("h2_calometparavsmetcalo",         "Calo MET para vs. MET",                              NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[0][0] = new TH2F("h2_caloj1calometdphivsj2metdphi", "Calo #Delta#phi(Jet1, Calo MET) vs. #Delta#phi(Jet2, Calo MET)", NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //pf met
  h2_jet1metdphivsdPt[0][1]     = new TH2F("h2_calojet1pfmetdphivsdPt",      "Calo #Delta#phi(Jet 1, PF MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[0][1]     = new TH2F("h2_calojet2pfmetdphivsdPt",      "Calo #Delta#phi(Jet 2, PF MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[0][0][1]   = new TH2F("h2_calojet1pfmetdphivsavgPt",    "Calo #Delta#phi(Jet 1, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][0][1]   = new TH2F("h2_genjet1pfmetdphivsavgPt",     "Gen #Delta#phi(Jet 1, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[0][0][1]   = new TH2F("h2_calojet2pfmetdphivsavgPt",    "Calo #Delta#phi(Jet 2, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][0][1]   = new TH2F("h2_genjet2pfmetdphivsavgPt",     "Gen #Delta#phi(Jet 2, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[0][1]    = new TH2F("h2_calojet1pfmetdphivsjet12dphi","Calo #Delta#phi(Jet 1, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[0][1]    = new TH2F("h2_calojet2pfmetdphivsjet12dphi","Calo #Delta#phi(Jet 2, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[0][1]      = new TH2F("h2_pfmetcalomhtdphivsdPt",       "Calo #Delta#phi(PF MET, MHT) vs. #Deltap_{T}",           NBINS, -JETDPTRANGE,  JETDPTRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[0][0][1] = new TH2F("h2_pfmetcalomhtdphivsavgPt",     "Calo #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][0][1] = new TH2F("h2_pfmetgenmhtdphivsavgPt",      "Gen #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[0][1]             = new TH2F("h2_pfmetvscalodPt",              "PF MET vs. Calo #Deltap_{T}",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[0][1]       = new TH2F("h2_pfmetvscalojet12dphi",        "PF MET vs. Calo #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0,   METRANGE);
  h2_metvsjet12deta[0][1]       = new TH2F("h2_pfmetvscalojet12deta",        "PF MET vs. Calo #Delta#eta(Jet1, Jet2)",              NBINS,-3.,        3.,        NBINS, 0,   METRANGE);
  h2_metvsavgPt[0][0][1]        = new TH2F("h2_pfmetvscaloavgPt",            "PF MET vs. Calo dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsavgPt[1][0][1]        = new TH2F("h2_pfmetvsgenavgPt",             "PF MET vs. Gen dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[0][1]           = new TH2F("h2_pfmetvscalodijetbisectorphi",       "PF MET vs. Calo dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[0][1]       = new TH2F("h2_pfmetperpvscalodijetbisectorphi",   "PF MET perp vs. Calo dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[0][1]       = new TH2F("h2_pfmetparavscalodijetbisectorphi",   "PF MET para vs. Calo dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[0][1]       = new TH2F("h2_pfmetcalodijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Calo dijet bisector) vs. #Deltap_{T}",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[0][0][1]     = new TH2F("h2_pfmetcalodijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Calo dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[1][0][1]     = new TH2F("h2_pfmetgendijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Gen dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[0][1]   = new TH2F("h2_pfmetperpvscalojet12dphi",   "PF MET perp vs. Calo #Delta#phi(Jet1, Jet2)",          NBINS,0.,      M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[0][1]   = new TH2F("h2_pfmetparavscalojet12dphi",   "PF MET para vs. Calo #Delta#phi(Jet1, Jet2)",          NBINS,0.,      M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsjet12deta[0][1]   = new TH2F("h2_pfmetperpvscalojet12deta",   "PF MET perp vs. Calo #Delta#eta(Jet1, Jet2)",          NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12deta[0][1]   = new TH2F("h2_pfmetparavscalojet12deta",   "PF MET para vs. Calo #Delta#eta(Jet1, Jet2)",          NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[0][0][1]    = new TH2F("h2_pfmetperpvscaloavgPt",       "PF MET perp vs. Calo dijet Pt",                       NBINS,0.,         JETRANGE,NBINS,-METRANGE, METRANGE);
  h2_metperpvsavgPt[1][0][1]    = new TH2F("h2_pfmetperpvsgenavgPt",        "PF MET perp vs. Gen dijet Pt",                       NBINS,0.,         JETRANGE,NBINS,-METRANGE, METRANGE);
  h2_metparavsavgPt[0][0][1]    = new TH2F("h2_pfmetparavscaloavgPt",       "PF MET para vs. Calo dijet Pt",                       NBINS,0.,         JETRANGE,NBINS,-METRANGE, METRANGE);
  h2_metparavsavgPt[1][0][1]    = new TH2F("h2_pfmetparavsgrnavgPt",        "PF MET para vs. Gen dijet Pt",                       NBINS,0.,         JETRANGE,NBINS,-METRANGE, METRANGE);
  h2_metperpvspara[0][1]        = new TH2F("h2_pfmetperpvsmetparacalo",     "PF MET perp vs. MET para",                       NBINS,-METRANGE,-METRANGE,NBINS,-METRANGE, METRANGE);
  h2_metperpvsmet[0][1]         = new TH2F("h2_pfmetperpvsmetcalo",         "PF MET perp vs. MET",                            NBINS,0.,    METRANGE,NBINS,-METRANGE, METRANGE);
  h2_metparavsmet[0][1]         = new TH2F("h2_pfmetparavsmetcalo",         "PF MET para vs. MET",                            NBINS,0.,    METRANGE,NBINS,-METRANGE, METRANGE);
  h2_j1metdphivsj2metdphi[0][1] = new TH2F("h2_caloj1pfmetdphivsj2metdphi", "Calo #Delta#phi(Jet1, PF MET) vs. #Delta#phi(Jet2, PF MET)", NBINS,0.,M_PI,NBINS,0.,M_PI);
  //tc met
  h2_jet1metdphivsdPt[0][2]     = new TH2F("h2_calojet1tcmetdphivsdPt",      "Calo #Delta#phi(Jet 1, TC MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[0][2]     = new TH2F("h2_calojet2tcmetdphivsdPt",      "Calo #Delta#phi(Jet 2, TC MET) vs. #Deltap_{T}",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[0][0][2]   = new TH2F("h2_calojet1tcmetdphivsavgPt",    "Calo #Delta#phi(Jet 1, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][0][2]   = new TH2F("h2_genjet1tcmetdphivsavgPt",    "Gen #Delta#phi(Jet 1, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[0][0][2]   = new TH2F("h2_calojet2tcmetdphivsavgPt",    "Calo #Delta#phi(Jet 2, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][0][2]   = new TH2F("h2_genjet2tcmetdphivsavgPt",    "Gen #Delta#phi(Jet 2, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[0][2]    = new TH2F("h2_calojet1tcmetdphivsjet12dphi","Calo #Delta#phi(Jet 1, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[0][2]    = new TH2F("h2_calojet2tcmetdphivsjet12dphi","Calo #Delta#phi(Jet 2, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[0][2]      = new TH2F("h2_tcmetcalomhtdphivsdPt",       "Calo #Delta#phi(TC MET, MHT) vs. #Deltap_{T}",           NBINS, -JETDPTRANGE,  JETDPTRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[0][0][2]    = new TH2F("h2_tcmetcalomhtdphivsavgPt",     "Calo #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][0][2]    = new TH2F("h2_tcmetgenmhtdphivsavgPt",     "Gen #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[0][2]             = new TH2F("h2_tcmetvscalodPt",              "TC MET vs. Calo #Deltap_{T}",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[0][2]       = new TH2F("h2_tcmetvscalojet12dphi",        "TC MET vs. Calo #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0.,  METRANGE);
  h2_metvsjet12deta[0][2]       = new TH2F("h2_tcmetvscalojet12deta",        "TC MET vs. Calo #Delta#eta(Jet1, Jet2)",              NBINS,-3.,        3.,        NBINS, 0,   METRANGE);
  h2_metvsavgPt[0][0][2]           = new TH2F("h2_tcmetvscaloavgPt",            "TC MET vs. Calo dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsavgPt[1][0][2]           = new TH2F("h2_tcmetvsgenavgPt",            "TC MET vs. Gen dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[0][2]           = new TH2F("h2_tcmetvscalodijetbisectorphi",       "PF MET vs. Calo dijet bisector Phi",               NBINS,0./2,     M_PI/2,      NBINS, 0,       METRANGE);
  h2_metperpvsdijetbisectorphi[0][2]       = new TH2F("h2_tcmetperpvscalodijetbisectorphi",   "PF MET perp vs. Calo dijet bisector Phi",          NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[0][2]       = new TH2F("h2_tcmetparavscalodijetbisectorphi",   "PF MET para vs. Calo dijet bisector Phi",          NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[0][2]       = new TH2F("h2_tcmetcalodijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Calo dijet bisector) vs. #Deltap_{T}",      NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0.,  M_PI);
  h2_metdijetbisectordphivsavgPt[0][0][2]     = new TH2F("h2_tcmetcalodijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Calo dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,    NBINS,0.,  M_PI);
  h2_metdijetbisectordphivsavgPt[1][0][2]     = new TH2F("h2_tcmetgendijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Gen dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,    NBINS,0.,  M_PI);

  h2_metperpvsjet12dphi[0][2]   = new TH2F("h2_tcmetperpvscalojet12dphi",   "TC MET perp vs. Calo #Delta#phi(Jet1, Jet2)",          NBINS,0.,    M_PI,     NBINS,-METRANGE, METRANGE);
  h2_metparavsjet12dphi[0][2]   = new TH2F("h2_tcmetparavscalojet12dphi",   "TC MET para vs. Calo #Delta#phi(Jet1, Jet2)",          NBINS,0.,    M_PI,     NBINS,-METRANGE, METRANGE);
  h2_metperpvsjet12deta[0][2]   = new TH2F("h2_tcmetperpvscalojet12deta",   "TC MET perp vs. Calo #Delta#eta(Jet1, Jet2)",          NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12deta[0][2]   = new TH2F("h2_tcmetparavscalojet12deta",   "TC MET para vs. Calo #Delta#eta(Jet1, Jet2)",          NBINS,-3.,     3.,     NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[0][0][2]    = new TH2F("h2_tcmetperpvscaloavgPt",       "TC MET perp vs. Calo dijet Pt",                       NBINS, 0.,      JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metperpvsavgPt[1][0][2]    = new TH2F("h2_tcmetperpvsgenavgPt",        "TC MET perp vs. Gen dijet Pt",                       NBINS, 0.,      JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metparavsavgPt[0][0][2]    = new TH2F("h2_tcmetparavscaloavgPt",       "TC MET para vs. Calo dijet Pt",                       NBINS, 0.,      JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metparavsavgPt[1][0][2]    = new TH2F("h2_tcmetparavsgenavgPt",        "TC MET para vs. Gen dijet Pt",                       NBINS, 0.,      JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metperpvspara[0][2]        = new TH2F("h2_tcmetperpvsmetparacalo",     "TC MET perp vs. MET para",                       NBINS,-METRANGE,METRANGE, NBINS,-METRANGE, METRANGE);
  h2_metperpvsmet[0][2]         = new TH2F("h2_tcmetperpvsmetcalo",         "TC MET perp vs. MET",                            NBINS, 0.,      METRANGE, NBINS,-METRANGE, METRANGE);
  h2_metparavsmet[0][2]         = new TH2F("h2_tcmetparavsmetcalo",         "TC MET para vs. MET",                            NBINS, 0.,      METRANGE, NBINS,-METRANGE, METRANGE);
  h2_j1metdphivsj2metdphi[0][2] = new TH2F("h2_caloj1tcmetdphivsj2metdphi", "Calo #Delta#phi(Jet1, TC MET) vs. #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI,     NBINS,0.,     M_PI);
  //--- additional 1D histograms
  h_jet12dPtbothcentral[0]     = new TH1F("h_calojet12dPtbothcentral",     "Calo #Deltap_{T} Jets Central",           NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtcentralendcaps[0]  = new TH1F("h_calojet12dPtcentralendcaps",  "Calo #Deltap_{T} Jets Central and Endcap",NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtsameendcaps[0]     = new TH1F("h_calojet12dPtsameendcaps",     "Calo #Deltap_{T} Jets same Endcap",       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtoppositeendcaps[0] = new TH1F("h_calojet12dPtoppositeendcaps", "Calo #Deltap_{T} Jets opposite Endcaps",  NBINS,-JETDPTRANGE,JETDPTRANGE);
  //calo met

  /*
  //JPT jets
  h2_jet12dPtvsavgPt[1]      = new TH2F("h2_jptjet12dPtvsavgPt",      "JPT dPt(Jet1, Jet2) vs. dijet Pt",         NBINS, 0.,          JETRANGE,   NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdphi[1]       = new TH2F("h2_jptjet12dPtvsdphi",       "JPT dPt(Jet1, Jet2) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,        M_PI,       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdR[1]         = new TH2F("h2_jptjet12dPtvsdR",         "JPT dPt(Jet1, Jet2) vs. dR(Jet1, Jet2)",   NBINS, 0.,          10. ,       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj1[1]      = new TH2F("h2_jptjet12dPtvsetaj1",      "JPT dPt vs. eta Jet 1",                    NBINS,-3.,          3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj2[1]      = new TH2F("h2_jptjet12dPtvsetaj2",      "JPT dPt vs. eta Jet 2",                    NBINS,-3.,          3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_j1mhtdphivsj2mhtdphi[1] = new TH2F("h2_jptj1mhtdphivsj2mhtdphi", "JPT #Delta#phi(Jet1, MHT) vs. #Delta#phi(Jet2, MHT)",  NBINS,0.,        M_PI,       NBINS,0.,       M_PI);
  h2_mhtvsdPt[1]             = new TH2F("h2_jptmhtvsdPt",             "JPT MHT vs. dPt",                          NBINS,0., JETDPTRANGE,NBINS, 0.,         METRANGE);
  h2_mhtvsavgPt[1]           = new TH2F("h2_jptmhtvsavgPt",           "JPT MHT vs. dijet Pt",                     NBINS, 0.,          JETRANGE,   NBINS, 0.,         METRANGE);
  //calo met
  h2_jet1metdphivsdPt[1][0]     = new TH2F("h2_jptjet1calometdphivsdPt",      "JPT #Delta#phi(Jet 1, Calo MET) vs. dPt",             NBINS,0., JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[1][0]     = new TH2F("h2_jptjet2calometdphivsdPt",      "JPT #Delta#phi(Jet 2, Calo MET) vs. dPt",             NBINS,0., JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][0]   = new TH2F("h2_jptjet1calometdphivsavgPt",    "JPT #Delta#phi(Jet 1, Calo MET) vs. dijet Pt",        NBINS, 0.,          JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][0]   = new TH2F("h2_jptjet2calometdphivsavgPt",    "JPT #Delta#phi(Jet 2, Calo MET) vs. dijet Pt",        NBINS, 0.,          JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[1][0]    = new TH2F("h2_jptjet1calometdphivsjet12dphi","JPT #Delta#phi(Jet 1, Calo MET) vs. #Delta#phi(Jet1, Jet2)",NBINS,0.,        M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[1][0]    = new TH2F("h2_jptjet2calometdphivsjet12dphi","JPT #Delta#phi(Jet 2, Calo MET) vs. #Delta#phi(Jet1, Jet2)",NBINS,0.,        M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[1][0]      = new TH2F("h2_calometjptmhtdphivsdPt",       "JPT #Delta#phi(Calo MET, MHT) vs. dijet Pt",          NBINS, 0.,          JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][0]    = new TH2F("h2_calometjptmhtdphivsavgPt",     "JPT #Delta#phi(Calo MET, MHT) vs. dijet Pt",          NBINS, 0.,          JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[1][0]             = new TH2F("h2_calometvsjptdPt",              "Calo MET vs. JPT dPt",                          NBINS,0., JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[1][0]       = new TH2F("h2_calometvsjptjet12dphi",        "Calo MET vs. JPT #Delta#phi(Jet1, Jet2)",             NBINS,0.,        M_PI,       NBINS, 0.,  METRANGE);
  h2_metvsavgPt[1][0]           = new TH2F("h2_calometvsjptavgPt",            "Calo MET vs. JPT dijet Pt",                     NBINS, 0.,          JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[1][0]           = new TH2F("h2_calometvsjptdijetbisectorphi",       "Calo MET vs. JPT dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS, 0.,       METRANGE);
  h2_metperpvsdijetbisectorphi[1][0]       = new TH2F("h2_calometperpvsjptdijetbisectorphi",   "Calo MET perp vs. JPT dijet bisector Phi",        NBINS,0./2,     M_PI/2,     NBINS, -METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[1][0]       = new TH2F("h2_calometparavsjptdijetbisectorphi",   "Calo MET para vs. JPT dijet bisector Phi",        NBINS,0./2,     M_PI/2,     NBINS, -METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[1][0]       = new TH2F("h2_calometjptdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, JPT dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,     M_PI);
  h2_metdijetbisectordphivsavgPt[1][0]     = new TH2F("h2_calometjptdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, JPT dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,     M_PI);

  h2_metperpvsjet12dphi[1][0]   = new TH2F("h2_calometperpvsjptjet12dphi",   "Calo MET perp vs. JPT #Delta#phi(Jet1, Jet2)",            NBINS,0.,     M_PI,     NBINS, 0,        METRANGE);
  h2_metparavsjet12dphi[1][0]   = new TH2F("h2_calometparavsjptjet12dphi",   "Calo MET para vs. JPT #Delta#phi(Jet1, Jet2)",            NBINS,0.,     M_PI,     NBINS, 0,        METRANGE);
  h2_metperpvsavgPt[1][0]       = new TH2F("h2_calometperpvsjptavgPt",       "Calo MET perp vs. JPT dijet Pt",                    NBINS, 0.,       JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metparavsavgPt[1][0]       = new TH2F("h2_calometparavsjptavgPt",       "Calo MET para vs. JPT dijet Pt",                    NBINS, 0.,       JETRANGE, NBINS,-METRANGE, METRANGE);
  h2_metperpvspara[1][0]        = new TH2F("h2_calometperpvsmetparajpt",     "Calo MET perp vs. MET para",                        NBINS,-METRANGE, METRANGE, NBINS,-METRANGE, METRANGE);
  h2_metperpvsmet[1][0]         = new TH2F("h2_calometperpvsmetjpt",         "Calo MET perp vs. MET",                             NBINS, 0.,       METRANGE, NBINS,-METRANGE, METRANGE);
  h2_metparavsmet[1][0]         = new TH2F("h2_calometparavsmetjpt",         "Calo MET para vs. MET",                             NBINS, 0.,       METRANGE, NBINS,-METRANGE, METRANGE);
  h2_j1metdphivsj2metdphi[1][0] = new TH2F("h2_jptj1calometdphivsj2metdphi", "JPT #Delta#phi(Jet1, Calo MET) vs. #Delta#phi(Jet2, Calo MET)", NBINS,0.,     M_PI,     NBINS,0.,     M_PI);
  //pf met
  h2_jet1metdphivsdPt[1][1]     = new TH2F("h2_jptjet1pfmetdphivsdPt",      "JPT #Delta#phi(Jet 1, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[1][1]     = new TH2F("h2_jptjet2pfmetdphivsdPt",      "JPT #Delta#phi(Jet 2, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][1]   = new TH2F("h2_jptjet1pfmetdphivsavgPt",    "JPT #Delta#phi(Jet 1, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][1]   = new TH2F("h2_jptjet2pfmetdphivsavgPt",    "JPT #Delta#phi(Jet 2, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[1][1]    = new TH2F("h2_jptjet1pfmetdphivsjet12dphi","JPT #Delta#phi(Jet 1, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[1][1]    = new TH2F("h2_jptjet2pfmetdphivsjet12dphi","JPT #Delta#phi(Jet 2, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[1][1]      = new TH2F("h2_pfmetjptmhtdphivsdPt",       "JPT #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][1]    = new TH2F("h2_pfmetjptmhtdphivsavgPt",     "JPT #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[1][1]             = new TH2F("h2_pfmetvsjptdPt",              "PF MET vs. JPT dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[1][1]       = new TH2F("h2_pfmetvsjptjet12dphi",        "PF MET vs. JPT #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0.,  METRANGE);
  h2_metvsavgPt[1][1]           = new TH2F("h2_pfmetvsjptavgPt",            "PF MET vs. JPT dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[1][1]           = new TH2F("h2_pfmetvsjptdijetbisectorphi",       "PF MET vs. JPT dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[1][1]       = new TH2F("h2_pfmetperpvsjptdijetbisectorphi",   "PF MET perp vs. JPT dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[1][1]       = new TH2F("h2_pfmetparavsjptdijetbisectorphi",   "PF MET para vs. JPT dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[1][1]       = new TH2F("h2_pfmetjptdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, JPT dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[1][1]     = new TH2F("h2_pfmetjptdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, JPT dijet bisector) vs. dijet Pt", NBINS,0.,          JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[1][1]   = new TH2F("h2_pfmetperpvsjptjet12dphi",  "PF MET perp vs. JPT #Delta#phi(Jet1, Jet2)",         NBINS,0.,   M_PI,     NBINS, 0,       METRANGE);
  h2_metparavsjet12dphi[1][1]   = new TH2F("h2_pfmetparavsjptjet12dphi",  "PF MET para vs. JPT #Delta#phi(Jet1, Jet2)",         NBINS,0.,   M_PI,     NBINS, 0,       METRANGE);
  h2_metperpvsavgPt[1][1]       = new TH2F("h2_pfmetperpvsjptavgPt",      "PF MET perp vs. JPT dijet Pt",                 NBINS, 0.,     JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[1][1]       = new TH2F("h2_pfmetparavsjptavgPt",      "PF MET para vs. JPT dijet Pt",                 NBINS, 0.,     JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[1][1]        = new TH2F("h2_pfmetperpvsmetparajpt",    "PF MET perp vs. MET para",                     NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[1][1]         = new TH2F("h2_pfmetperpvsmetjpt",        "PF MET perp vs. MET",                          NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[1][1]         = new TH2F("h2_pfmetparavsmetjpt",        "PF MET para vs. MET",                          NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[1][1] = new TH2F("h2_jptj1pfmetdphivsj2metdphi","JPT #Delta#phi(Jet1, PF MET) vs. #Delta#phi(Jet2, PF MET)",NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //tc met
  h2_jet1metdphivsdPt[1][2]     = new TH2F("h2_jptjet1tcmetdphivsdPt",      "JPT #Delta#phi(Jet 1, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[1][2]     = new TH2F("h2_jptjet2tcmetdphivsdPt",      "JPT #Delta#phi(Jet 2, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[1][2]   = new TH2F("h2_jptjet1tcmetdphivsavgPt",    "JPT #Delta#phi(Jet 1, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,    NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[1][2]   = new TH2F("h2_jptjet2tcmetdphivsavgPt",    "JPT #Delta#phi(Jet 2, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,    NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[1][2]    = new TH2F("h2_jptjet1tcmetdphivsjet12dphi","JPT #Delta#phi(Jet 1, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,        NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[1][2]    = new TH2F("h2_jptjet2tcmetdphivsjet12dphi","JPT #Delta#phi(Jet 2, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,        NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[1][2]      = new TH2F("h2_tcmetjptmhtdphivsdPt",       "JPT #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,    NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[1][2]    = new TH2F("h2_tcmetjptmhtdphivsavgPt",     "JPT #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,    NBINS,0.,M_PI);
  h2_metvsdPt[1][2]             = new TH2F("h2_tcmetvsjptdPt",              "TC MET vs. JPT dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[1][2]       = new TH2F("h2_tcmetvsjptjet12dphi",        "TC MET vs. JPT #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,        NBINS, 0,   METRANGE);
  h2_metvsavgPt[1][2]           = new TH2F("h2_tcmetvsjptavgPt",            "TC MET vs. JPT dijet Pt",                      NBINS, 0.,         JETRANGE,    NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[1][2]           = new TH2F("h2_tcmetvsjptdijetbisectorphi",       "PF MET vs. JPT dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS,0.,       METRANGE);
  h2_metperpvsdijetbisectorphi[1][2]       = new TH2F("h2_tcmetperpvsjptdijetbisectorphi",   "PF MET perp vs. JPT dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[1][2]       = new TH2F("h2_tcmetparavsjptdijetbisectorphi",   "PF MET para vs. JPT dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[1][2]       = new TH2F("h2_tcmetjptdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, JPT dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[1][2]     = new TH2F("h2_tcmetjptdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, JPT dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[1][1]   = new TH2F("h2_tcmetperpvsjptjet12dphi",   "TC MET perp vs. JPT #Delta#phi(Jet1, Jet2)",          NBINS,0.,    M_PI,     NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[1][1]   = new TH2F("h2_tcmetparavsjptjet12dphi",   "TC MET para vs. JPT #Delta#phi(Jet1, Jet2)",          NBINS,0.,    M_PI,     NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[1][2]       = new TH2F("h2_tcmetperpvsjptavgPt",       "TC MET perp vs. dijet Pt",                      NBINS, 0.,      JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[1][2]       = new TH2F("h2_tcmetparavsjptavgPt",       "TC MET para vs. dijet Pt",                      NBINS, 0.,      JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[1][2]        = new TH2F("h2_tcmetperpvsmetparajpt",     "TC MET perp vs. MET para",                      NBINS,-METRANGE,METRANGE, NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[1][2]         = new TH2F("h2_tcmetperpvsmetjpt",         "TC MET perp vs. MET",                           NBINS, 0.,      METRANGE, NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[1][2]         = new TH2F("h2_tcmetparavsmetjpt",         "TC MET para vs. MET",                           NBINS, 0.,      METRANGE, NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[1][2] = new TH2F("h2_jptj1tcmetdphivsj2metdphi", "JPT #Delta#phi(Jet1, TC MET) vs. #Delta#phi(Jet2, TC MET)", NBINS,0.,    M_PI,     NBINS,0.,    M_PI);
  //--- additional 1D histograms
  h_jet12dPtbothcentral[1]     = new TH1F("h_jptjet12dPtbothcentral",     "JPT dPt Jets Central",           NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtcentralendcaps[1]  = new TH1F("h_jptjet12dPtcentralendcaps",  "JPT dPt Jets Central and Endcap",NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtsameendcaps[1]     = new TH1F("h_jptjet12dPtsameendcaps",     "JPT dPt Jets same Endcap",       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtoppositeendcaps[1] = new TH1F("h_jptjet12dPtoppositeendcaps", "JPT dPt Jets opposite Endcaps",  NBINS,-JETDPTRANGE,JETDPTRANGE);


  //PF Jets
  h2_jet12dPtvsavgPt[2]      = new TH2F("h2_pfjet12dPtvsavgPt",      "PF dPt(Jet1, Jet2) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdphi[2]       = new TH2F("h2_pfjet12dPtvsdphi",       "PF dPt(Jet1, Jet2) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdR[2]         = new TH2F("h2_pfjet12dPtvsdR",         "PF dPt(Jet1, Jet2) vs. dR(Jet1, Jet2)",   NBINS, 0.,         10.,        NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj1[2]      = new TH2F("h2_pfjet12dPtvsetaj1",      "PF dPt vs. eta Jet 1",                    NBINS,-3.,         3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj2[2]      = new TH2F("h2_pfjet12dPtvsetaj2",      "PF dPt vs. eta Jet 2",                    NBINS,-3.,         3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_j1mhtdphivsj2mhtdphi[2] = new TH2F("h2_pfj1mhtdphivsj2mhtdphi", "PF #Delta#phi(Jet1, MHT) vs. #Delta#phi(Jet2, MHT)",  NBINS,0.,       M_PI,       NBINS,0.,       M_PI);
  h2_mhtvsdPt[2]             = new TH2F("h2_pfmhtvsdPt",             "PF MHT vs. dPt",                          NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,         METRANGE);
  h2_mhtvsavgPt[2]           = new TH2F("h2_pfmhtvsavgPt",           "PF MHT vs. dijet Pt",                     NBINS, 0.,         JETRANGE,   NBINS, 0.,         METRANGE);
  //calo met
  h2_jet1metdphivsdPt[2][0]     = new TH2F("h2_pfjet1calometdphivsdPt",      "PF #Delta#phi(Jet 1, Calo MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[2][0]     = new TH2F("h2_pfjet2calometdphivsdPt",      "PF #Delta#phi(Jet 2, Calo MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[2][0]   = new TH2F("h2_pfjet1calometdphivsavgPt",    "PF #Delta#phi(Jet 1, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[2][0]   = new TH2F("h2_pfjet2calometdphivsavgPt",    "PF #Delta#phi(Jet 2, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[2][0]    = new TH2F("h2_pfjet1calometdphivsjet12dphi","PF #Delta#phi(Jet 1, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[2][0]    = new TH2F("h2_pfjet2calometdphivsjet12dphi","PF #Delta#phi(Jet 2, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[2][0]      = new TH2F("h2_calometpfmhtdphivsdPt",       "PF #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[2][0]    = new TH2F("h2_calometpfmhtdphivsavgPt",     "PF #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[2][0]             = new TH2F("h2_calometvspfdPt",              "Calo MET vs. PF dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[2][0]       = new TH2F("h2_calometvspfjet12dphi",        "Calo MET vs. PF #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0,   METRANGE);
  h2_metvsavgPt[2][0]           = new TH2F("h2_calometvspfavgPt",            "Calo MET vs. PF dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[2][0]           = new TH2F("h2_calometvspfdijetbisectorphi",       "Calo MET vs. PF dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[2][0]       = new TH2F("h2_calometperpvspfdijetbisectorphi",   "Calo MET vs. PF dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[2][0]       = new TH2F("h2_calometparavspfdijetbisectorphi",   "Calo MET vs. PF dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[2][0]       = new TH2F("h2_calometpfdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, PF dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[2][0]     = new TH2F("h2_calometpfdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, PF dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[2][0]   = new TH2F("h2_calometperpvspfjet12dphi",   "Calo MET perp vs. PF #Delta#phi(Jet1, Jet2)",           NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[2][0]   = new TH2F("h2_calometparavspfjet12dphi",   "Calo MET para vs. PF #Delta#phi(Jet1, Jet2)",           NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[2][0]       = new TH2F("h2_calometperpvspfavgPt",       "Calo MET perp vs. PF dijet Pt",                   NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[2][0]       = new TH2F("h2_calometparavspfavgPt",       "Calo MET para vs. PF dijet Pt",                   NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[2][0]        = new TH2F("h2_calometperpvsmetparapf",     "Calo MET perp vs. MET para",                      NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[2][0]         = new TH2F("h2_calometperpvsmetpf",         "Calo MET perp vs. MET",                           NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[2][0]         = new TH2F("h2_calometparavsmetpf",         "Calo MET para vs. MET",                           NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[2][0] = new TH2F("h2_pfj1calometdphivsj2metdphi", "PF #Delta#phi(Jet1, Calo MET) vs. #Delta#phi(Jet2, Calo MET)",NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //pf met
  h2_jet1metdphivsdPt[2][1]     = new TH2F("h2_pfjet1pfmetdphivsdPt",      "PF #Delta#phi(Jet 1, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[2][1]     = new TH2F("h2_pfjet2pfmetdphivsdPt",      "PF #Delta#phi(Jet 2, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[2][1]   = new TH2F("h2_pfjet1pfmetdphivsavgPt",    "PF #Delta#phi(Jet 1, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[2][1]   = new TH2F("h2_pfjet2pfmetdphivsavgPt",    "PF #Delta#phi(Jet 2, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[2][1]    = new TH2F("h2_pfjet1pfmetdphivsjet12dphi","PF #Delta#phi(Jet 1, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[2][1]    = new TH2F("h2_pfjet2pfmetdphivsjet12dphi","PF #Delta#phi(Jet 2, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[2][1]      = new TH2F("h2_pfmetpfmhtdphivsdPt",       "PF #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[2][1]    = new TH2F("h2_pfmetpfmhtdphivsavgPt",     "PF #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[2][1]             = new TH2F("h2_pfmetvspfdPt",              "PF MET vs. PF dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[2][1]       = new TH2F("h2_pfmetvspfjet12dphi",        "PF MET vs. PF #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0,   METRANGE);
  h2_metvsavgPt[2][1]           = new TH2F("h2_pfmetvspfavgPt",            "PF MET vs. PF dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[2][1]           = new TH2F("h2_pfmetvspfdijetbisectorphi",       "PF MET vs. PF dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[2][1]       = new TH2F("h2_pfmetperpvspfdijetbisectorphi",   "PF MET perp vs. PF dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[2][1]       = new TH2F("h2_pfmetparavspfdijetbisectorphi",   "PF MET para vs. PF dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[2][1]       = new TH2F("h2_pfmetpfdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, PF dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[2][1]     = new TH2F("h2_pfmetpfdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, PF dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[2][1]   = new TH2F("h2_pfmetperpvspfjet12dphi",  "PF MET perp vs. PF #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[2][1]   = new TH2F("h2_pfmetparavspfjet12dphi",  "PF MET para vs. PF #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[2][1]       = new TH2F("h2_pfmetperpvspfavgPt",      "PF MET perp vs. PF dijet Pt",                 NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[2][1]       = new TH2F("h2_pfmetparavspfavgPt",      "PF MET para vs. PF dijet Pt",                 NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[2][1]        = new TH2F("h2_pfmetperpvsmetparapf",    "PF MET perp vs. MET para",                    NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[2][1]         = new TH2F("h2_pfmetperpvsmetpf",        "PF MET perp vs. MET",                         NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[2][1]         = new TH2F("h2_pfmetparavsmetpf",        "PF MET para vs. MET",                         NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[2][1] = new TH2F("h2_pfj1pfmetdphivsj2metdphi","PF #Delta#phi(Jet1, PF MET) vs. #Delta#phi(Jet2, PF MET)",NBINS,0.,    M_PI,    NBINS,0.,M_PI);
  //tc met
  h2_jet1metdphivsdPt[2][2]     = new TH2F("h2_pfjet1tcmetdphivsdPt",      "PF #Delta#phi(Jet 1, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[2][2]     = new TH2F("h2_pfjet2tcmetdphivsdPt",      "PF #Delta#phi(Jet 2, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[2][2]   = new TH2F("h2_pfjet1tcmetdphivsavgPt",    "PF #Delta#phi(Jet 1, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[2][2]   = new TH2F("h2_pfjet2tcmetdphivsavgPt",    "PF #Delta#phi(Jet 2, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[2][2]    = new TH2F("h2_pfjet1tcmetdphivsjet12dphi","PF #Delta#phi(Jet 1, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[2][2]    = new TH2F("h2_pfjet2tcmetdphivsjet12dphi","PF #Delta#phi(Jet 2, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[2][2]      = new TH2F("h2_tcmetpfmhtdphivsdPt",       "PF #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[2][2]    = new TH2F("h2_tcmetpfmhtdphivsavgPt",     "PF #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[2][2]             = new TH2F("h2_tcmetvspfdPt",              "TC MET vs. PF dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[2][2]       = new TH2F("h2_tcmetvspfjet12dphi",        "TC MET vs. PF #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0.,  METRANGE);
  h2_metvsavgPt[2][2]           = new TH2F("h2_tcmetvspfavgPt",            "TC MET vs. PF dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[2][2]           = new TH2F("h2_tcmetvspfdijetbisectorphi",       "PF MET vs. PF dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS,0.,       METRANGE);
  h2_metperpvsdijetbisectorphi[2][2]       = new TH2F("h2_tcmetperpvspfdijetbisectorphi",   "PF MET perp vs. PF dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[2][2]       = new TH2F("h2_tcmetparavspfdijetbisectorphi",   "PF MET para vs. PF dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[2][2]       = new TH2F("h2_tcmetpfdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, PF dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[2][2]     = new TH2F("h2_tcmetpfdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, PF dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[2][1]   = new TH2F("h2_tcmetperpvspfjet12dphi",  "TC MET perp vs. PF #Delta#phi(Jet1, Jet2)",         NBINS,0.,   M_PI,     NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[2][1]   = new TH2F("h2_tcmetparavspfjet12dphi",  "TC MET para vs. PF #Delta#phi(Jet1, Jet2)",         NBINS,0.,   M_PI,     NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[2][2]       = new TH2F("h2_tcmetperpvspfavgPt",      "TC MET perp vs. dijet Pt",                    NBINS, 0.,     JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[2][2]       = new TH2F("h2_tcmetparavspfavgPt",      "TC MET para vs. dijet Pt",                    NBINS, 0.,     JETRANGE, NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[2][2]        = new TH2F("h2_tcmetperpvsmetparapf",    "TC MET perp vs. MET para",                    NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[2][2]         = new TH2F("h2_tcmetperpvsmetpf",        "TC MET perp vs. MET",                         NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[2][2]         = new TH2F("h2_tcmetparavsmetpf",        "TC MET para vs. MET",                         NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[2][2] = new TH2F("h2_pfj1tcmetdphivsj2metdphi","PF #Delta#phi(Jet1, TC MET) vs. #Delta#phi(Jet2, TC MET)",NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //--- additional 1D histograms
  h_jet12dPtbothcentral[2]     = new TH1F("h_pfjet12dPtbothcentral",     "PF dPt Jets Central",           NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtcentralendcaps[2]  = new TH1F("h_pfjet12dPtcentralendcaps",  "PF dPt Jets Central and Endcap",NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtsameendcaps[2]     = new TH1F("h_pfjet12dPtsameendcaps",     "PF dPt Jets same Endcap",       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtoppositeendcaps[2] = new TH1F("h_pfjet12dPtoppositeendcaps", "PF dPt Jets opposite Endcaps",  NBINS,-JETDPTRANGE,JETDPTRANGE);


  //Track Jets
  h2_jet12dPtvsavgPt[3]      = new TH2F("h2_trackjet12dPtvsavgPt",      "Track dPt(Jet1, Jet2) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdphi[3]       = new TH2F("h2_trackjet12dPtvsdphi",       "Track dPt(Jet1, Jet2) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsdR[3]         = new TH2F("h2_trackjet12dPtvsdR",         "Track dPt(Jet1, Jet2) vs. dR(Jet1, Jet2)",   NBINS, 0.,         10.,        NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj1[3]      = new TH2F("h2_trackjet12dPtvsetaj1",      "Track dPt vs. eta Jet 1",                    NBINS,-3.,         3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_jet12dPtvsetaj2[3]      = new TH2F("h2_trackjet12dPtvsetaj2",      "Track dPt vs. eta Jet 2",                    NBINS,-3.,         3.,         NBINS,-JETDPTRANGE,JETDPTRANGE);
  h2_j1mhtdphivsj2mhtdphi[3] = new TH2F("h2_trackj1mhtdphivsj2mhtdphi", "Track #Delta#phi(Jet1, MHT) vs. #Delta#phi(Jet2, MHT)",  NBINS,0.,       M_PI,       NBINS,0.,       M_PI);
  h2_mhtvsdPt[3]             = new TH2F("h2_trackmhtvsdPt",             "Track MHT vs. dPt",                          NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,          METRANGE);
  h2_mhtvsavgPt[3]           = new TH2F("h2_trackmhtvsavgPt",           "Track MHT vs. dijet Pt",                     NBINS, 0.,         JETRANGE,   NBINS,0.,          METRANGE);
  //calo met
  h2_jet1metdphivsdPt[3][0]     = new TH2F("h2_trackjet1calometdphivsdPt",      "Track #Delta#phi(Jet 1, Calo MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[3][0]     = new TH2F("h2_trackjet2calometdphivsdPt",      "Track #Delta#phi(Jet 2, Calo MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[3][0]   = new TH2F("h2_trackjet1calometdphivsavgPt",    "Track #Delta#phi(Jet 1, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[3][0]   = new TH2F("h2_trackjet2calometdphivsavgPt",    "Track #Delta#phi(Jet 2, Calo MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[3][0]    = new TH2F("h2_trackjet1calometdphivsjet12dphi","Track #Delta#phi(Jet 1, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[3][0]    = new TH2F("h2_trackjet2calometdphivsjet12dphi","Track #Delta#phi(Jet 2, Calo MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[3][0]      = new TH2F("h2_calomettrackmhtdphivsdPt",       "Track #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[3][0]    = new TH2F("h2_calomettrackmhtdphivsavgPt",     "Track #Delta#phi(Calo MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[3][0]             = new TH2F("h2_calometvstrackdPt",              "Calo MET vs. Track dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,   METRANGE);
  h2_metvsjet12dphi[3][0]       = new TH2F("h2_calometvstrackjet12dphi",        "Calo MET vs. Track #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS,0,    METRANGE);
  h2_metvsavgPt[3][0]           = new TH2F("h2_calometvstrackavgPt",            "Calo MET vs. Track dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS,0.,   METRANGE);
  h2_metvsdijetbisectorphi[3][0]           = new TH2F("h2_calometvstrackdijetbisectorphi",       "Calo MET vs. Track dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[3][0]       = new TH2F("h2_calometperpvstrackdijetbisectorphi",   "Calo MET vs. Track dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[3][0]       = new TH2F("h2_calometparavstrackdijetbisectorphi",   "Calo MET vs. Track dijet bisector Phi",             NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[3][0]       = new TH2F("h2_calomettrackdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Track dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[3][0]     = new TH2F("h2_calomettrackdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Track dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[3][0]   = new TH2F("h2_calometperpvstrackjet12dphi",   "Calo MET perp vs. Track #Delta#phi(Jet1, Jet2)",           NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[3][0]   = new TH2F("h2_calometparavstrackjet12dphi",   "Calo MET para vs. Track #Delta#phi(Jet1, Jet2)",           NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[3][0]       = new TH2F("h2_calometperpvstrackavgPt",       "Calo MET perp vs. Track dijet Pt",                   NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[3][0]       = new TH2F("h2_calometparavstrackavgPt",       "Calo MET para vs. Track dijet Pt",                   NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[3][0]        = new TH2F("h2_calometperpvsmetparatrack",     "Calo MET perp vs. MET para",                         NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[3][0]         = new TH2F("h2_calometperpvsmettrack",         "Calo MET perp vs. MET",                              NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[3][0]         = new TH2F("h2_calometparavsmettrack",         "Calo MET para vs. MET",                              NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[3][0] = new TH2F("h2_trackj1calometdphivsj2metdphi", "Track #Delta#phi(Jet1, Calo MET) vs. #Delta#phi(Jet2, Calo MET)",NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //pf met
  h2_jet1metdphivsdPt[3][1]     = new TH2F("h2_trackjet1pfmetdphivsdPt",      "Track #Delta#phi(Jet 1, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[3][1]     = new TH2F("h2_trackjet2pfmetdphivsdPt",      "Track #Delta#phi(Jet 2, PF MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[3][1]   = new TH2F("h2_trackjet1pfmetdphivsavgPt",    "Track #Delta#phi(Jet 1, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[3][1]   = new TH2F("h2_trackjet2pfmetdphivsavgPt",    "Track #Delta#phi(Jet 2, PF MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[3][1]    = new TH2F("h2_trackjet1pfmetdphivsjet12dphi","Track #Delta#phi(Jet 1, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[3][1]    = new TH2F("h2_trackjet2pfmetdphivsjet12dphi","Track #Delta#phi(Jet 2, PF MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[3][1]      = new TH2F("h2_pfmettrackmhtdphivsdPt",       "Track #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[3][1]    = new TH2F("h2_pfmettrackmhtdphivsavgPt",     "Track #Delta#phi(PF MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[3][1]             = new TH2F("h2_pfmetvstrackdPt",              "PF MET vs. Track dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS, 0.,  METRANGE);
  h2_metvsjet12dphi[3][1]       = new TH2F("h2_pfmetvstrackjet12dphi",        "PF MET vs. Track #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS, 0,   METRANGE);
  h2_metvsavgPt[3][1]           = new TH2F("h2_pfmetvstrackavgPt",            "PF MET vs. Track dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS, 0.,  METRANGE);
  h2_metvsdijetbisectorphi[3][1]           = new TH2F("h2_pfmetvstrackdijetbisectorphi",       "PF MET vs. Track dijet bisector Phi",               NBINS,0./2,     M_PI/2,     NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[3][1]       = new TH2F("h2_pfmetperpvstrackdijetbisectorphi",   "PF MET perp vs. Track dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[3][1]       = new TH2F("h2_pfmetparavstrackdijetbisectorphi",   "PF MET para vs. Track dijet bisector Phi",          NBINS,0./2,     M_PI/2,     NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[3][1]       = new TH2F("h2_pfmettrackdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Track dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[3][1]     = new TH2F("h2_pfmettrackdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Track dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,   NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[3][1]   = new TH2F("h2_pfmetperpvstrackjet12dphi",  "PF MET perp vs. Track #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[3][1]   = new TH2F("h2_pfmetparavstrackjet12dphi",  "PF MET para vs. Track #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[3][1]       = new TH2F("h2_pfmetperpvstrackavgPt",      "PF MET perp vs. Track dijet Pt",                 NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[3][1]       = new TH2F("h2_pfmetparavstrackavgPt",      "PF MET para vs. Track dijet Pt",                 NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[3][1]        = new TH2F("h2_pfmetperpvsmetparatrack",    "PF MET perp vs. MET para",                       NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[3][1]         = new TH2F("h2_pfmetperpvsmettrack",        "PF MET perp vs. MET",                            NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[3][1]         = new TH2F("h2_pfmetparavsmettrack",        "PF MET para vs. MET",                            NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[3][1] = new TH2F("h2_trackj1pfmetdphivsj2metdphi","Track #Delta#phi(Jet1, PF MET) vs. #Delta#phi(Jet2, PF MET)",NBINS,0.,    M_PI,    NBINS,0.,M_PI);
  //tc met
  h2_jet1metdphivsdPt[3][2]     = new TH2F("h2_trackjet1tcmetdphivsdPt",      "Track #Delta#phi(Jet 1, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet2metdphivsdPt[3][2]     = new TH2F("h2_trackjet2tcmetdphivsdPt",      "Track #Delta#phi(Jet 2, TC MET) vs. dPt",              NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,M_PI);
  h2_jet1metdphivsavgPt[3][2]   = new TH2F("h2_trackjet1tcmetdphivsavgPt",    "Track #Delta#phi(Jet 1, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet2metdphivsavgPt[3][2]   = new TH2F("h2_trackjet2tcmetdphivsavgPt",    "Track #Delta#phi(Jet 2, TC MET) vs. dijet Pt",         NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_jet1metdphivsdphi[3][2]    = new TH2F("h2_trackjet1tcmetdphivsjet12dphi","Track #Delta#phi(Jet 1, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_jet2metdphivsdphi[3][2]    = new TH2F("h2_trackjet2tcmetdphivsjet12dphi","Track #Delta#phi(Jet 2, TC MET) vs. #Delta#phi(Jet1, Jet2)", NBINS,0.,       M_PI,       NBINS,0.,M_PI);
  h2_metmhtdphivsdPt[3][2]      = new TH2F("h2_tcmettrackmhtdphivsdPt",       "Track #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metmhtdphivsavgPt[3][2]    = new TH2F("h2_tcmettrackmhtdphivsavgPt",     "Track #Delta#phi(TC MET, MHT) vs. dijet Pt",           NBINS, 0.,         JETRANGE,   NBINS,0.,M_PI);
  h2_metvsdPt[3][2]             = new TH2F("h2_tcmetvstrackdPt",              "TC MET vs. Track dPt",                           NBINS,-JETDPTRANGE,JETDPTRANGE,NBINS,0.,   METRANGE);
  h2_metvsjet12dphi[3][2]       = new TH2F("h2_tcmetvstrackjet12dphi",        "TC MET vs. Track #Delta#phi(Jet1, Jet2)",              NBINS,0.,       M_PI,       NBINS,0,    METRANGE);
  h2_metvsavgPt[3][2]           = new TH2F("h2_tcmetvstrackavgPt",            "TC MET vs. Track dijet Pt",                      NBINS, 0.,         JETRANGE,   NBINS,0.,   METRANGE);
  h2_metvsdijetbisectorphi[3][2]           = new TH2F("h2_tcmetvstrackdijetbisectorphi",       "PF MET vs. Track dijet bisector Phi",               NBINS,0./2,     M_PI/2,      NBINS, 0.,      METRANGE);
  h2_metperpvsdijetbisectorphi[3][2]       = new TH2F("h2_tcmetperpvstrackdijetbisectorphi",   "PF MET perp vs. Track dijet bisector Phi",          NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metparavsdijetbisectorphi[3][2]       = new TH2F("h2_tcmetparavstrackdijetbisectorphi",   "PF MET para vs. Track dijet bisector Phi",          NBINS,0./2,     M_PI/2,      NBINS,-METRANGE,METRANGE);
  h2_metdijetbisectordphivsdPt[3][2]       = new TH2F("h2_tcmettrackdijetbisectordphivsdPt",   "#Delta#phi(Calo MET, Track dijet bisector) vs. dPt",      NBINS,-JETDPTRANGE,JETDPTRANGE, NBINS,0.,    M_PI);
  h2_metdijetbisectordphivsavgPt[3][2]     = new TH2F("h2_tcmettrackdijetbisectordphivsavgPt", "#Delta#phi(Calo MET, Track dijet bisector) vs. dijet Pt", NBINS, 0.,         JETRANGE,    NBINS,0.,    M_PI);

  h2_metperpvsjet12dphi[3][1]   = new TH2F("h2_tcmetperpvstrackjet12dphi",  "TC MET perp vs. Track #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metparavsjet12dphi[3][1]   = new TH2F("h2_tcmetparavstrackjet12dphi",  "TC MET para vs. Track #Delta#phi(Jet1, Jet2)",         NBINS,0.,    M_PI,    NBINS,-METRANGE,METRANGE);
  h2_metperpvsavgPt[3][2]       = new TH2F("h2_tcmetperpvstrackavgPt",      "TC MET perp vs. dijet Pt",                       NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsavgPt[3][2]       = new TH2F("h2_tcmetparavstrackavgPt",      "TC MET para vs. dijet Pt",                       NBINS, 0.,      JETRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvspara[3][2]        = new TH2F("h2_tcmetperpvsmetparatrack",    "TC MET perp vs. MET para",                       NBINS,-METRANGE,METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metperpvsmet[3][2]         = new TH2F("h2_tcmetperpvsmettrack",        "TC MET perp vs. MET",                            NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_metparavsmet[3][2]         = new TH2F("h2_tcmetparavsmettrack",        "TC MET para vs. MET",                            NBINS, 0.,      METRANGE,NBINS,-METRANGE,METRANGE);
  h2_j1metdphivsj2metdphi[3][2] = new TH2F("h2_trackj1tcmetdphivsj2metdphi","Track #Delta#phi(Jet1, TC MET) vs. #Delta#phi(Jet2, TC MET)",NBINS,0.,    M_PI,    NBINS,0.,    M_PI);
  //--- additional 1D histograms
  h_jet12dPtbothcentral[3]     = new TH1F("h_trackjet12dPtbothcentral",     "Track dPt Jets Central",           NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtcentralendcaps[3]  = new TH1F("h_trackjet12dPtcentralendcaps",  "Track dPt Jets Central and Endcap",NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtsameendcaps[3]     = new TH1F("h_trackjet12dPtsameendcaps",     "Track dPt Jets same Endcap",       NBINS,-JETDPTRANGE,JETDPTRANGE);
  h_jet12dPtoppositeendcaps[3] = new TH1F("h_trackjet12dPtoppositeendcaps", "Track dPt Jets opposite Endcaps",  NBINS,-JETDPTRANGE,JETDPTRANGE);
  */

  Long64_t nbytes = 0, nb = 0;


  //double scale = luminosity_ * cross_section_ * efficiency_ / (double)nentries;
  double scale = 1.;

  cut_njet     = 2;  //require no more than 2 jets

  
  /******
   * Possibly need to get jetID tool into analysis?
   * Jet ID requirements
   * (Calo, JPT, PF, Track)
   * PT:  10, 8, 8, 5
   * Eta: 3,  2, 3, 2
   *** Calo/JPT Specific apply only for jets with eta > 2.4?
   * fRBX < 0.98
   * fHPD < 0.98
   * n90Hits > 1
   * EM Fraction > 0.1
   *** PF Specific
   * Neutral EM Fraction  < 1.
   * Charged EM Fraction  < 1.
   * Neutral Had Fraction < 1.
   * Charged Had Fraction > 0.
   * Charged Had Multiplicity > 0.
   * Muon Fraction        < 1.
   *** Track Specific
   *
  ******/


  //study effects of threshold for jet definintion
  cut_alljetet = 10.;     //min et of "jet"
  cut_alljeteta = 3.0;  //max eta of "jet"
  //cut_third_jetet = 10.; //max et of jets other than the di jet system
  cut_third_jetet = 10000000; //max et of jets other than the di jet system

  cut_jet1et = 20;  //min et of "jet"
  cut_jet1eta = 3.0;//max eta of "jet"
  
  cut_jet2et = 20;  //min et of "jet"
  cut_jet2eta = 3.0;//max eta of "jet"
  
  cut_jetemfrac[0] = 0.01;//min event em fraction
  cut_jetemfrac[1] = 1.;//min event em fraction

  cut_jethpdfrac[0] = 0.00;//min event em fraction
  cut_jethpdfrac[1] = 0.98;//min event em fraction

  cut_jetrbxfrac[0] = 0.00;//min event em fraction
  cut_jetrbxfrac[1] = 1.;//min event em fraction

  cut_jetn90[0] = 1.;//min number of calo towers containing 90% of the jet energy
  cut_jetn90[1] = 350.;//max number of calo towers containing 90% of the jet energy

  cut_jet12dphi    = 0.0; //min dphi(jet1, jet2)
  cut_jet12dR      = 1.;  //min dR(jet1,jet2)
  
  cut_elecpt = 15.0;
  cut_muonpt = 15.0;

  cut_eleceta = 2.4;
  cut_muoneta = 2.4;

  cut_eleciso = 0.5;
  cut_muoniso = 0.1;
  
  // values to go into the selection table
  //int  pscounter      = 0;
  //int  fjcounter      = 0;
  //int  htcounter      = 0;
  //int  mhtcounter     = 0;
  //int  dphicounter    = 0;
  //int  metcounter     = 0;
  //int  leptoncounter  = 0;
  //
  
  for (Long64_t jentry=0; jentry<nentries;++jentry) {
    Long64_t ientry = LoadTree(jentry);
    
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb; // nb = number of bytes read

    //std::cout<<"ientry: "<<ientry<<"run: "<<Run<<" event: "<<Event<<std::endl;
    
    double pfMETx   = 0.;
    double pfMETy   = 0.;
    double pfMETz   = 0.;
    double tcMETx   = 0.;
    double tcMETy   = 0.;
    double tcMETz   = 0.;
    double caloMETx = 0.;
    double caloMETy = 0.;
    double caloMETz = 0.;

    pfMETx   = pfMET_Fullcorr_nocc[0];
    pfMETy   = pfMET_Fullcorr_nocc[1];
    pfMETz   = pfMET_Fullcorr_nocc[2];

    tcMETx   = tcMET_Fullcorr_nocc[0];
    tcMETy   = tcMET_Fullcorr_nocc[1];
    tcMETz   = tcMET_Fullcorr_nocc[2];

    caloMETx   = caloMET_Fullcorr_nocc[0];
    caloMETy   = caloMET_Fullcorr_nocc[1];
    caloMETz   = caloMET_Fullcorr_nocc[2];



    double pfMET       = 0.;
    double pfMETphi2   = 0.;
    double pfMETeta    = 0.;
    double tcMET       = 0.;
    double tcMETphi2   = 0.;
    double tcMETeta    = 0.;
    double caloMET     = 0.;
    double caloMETphi2 = 0.;
    double caloMETeta  = 0.;

    pfMET     = sqrt( pfMETx*pfMETx + pfMETy*pfMETy );
    pfMETphi2 = atan2(pfMETy,pfMETx);
    pfMETeta  = calcEta(pfMETx,pfMETy,pfMETz);
    
    tcMET     = sqrt( tcMETx*tcMETx + tcMETy*tcMETy );
    tcMETphi2 = atan2(tcMETy,tcMETx);
    tcMETeta  = calcEta(tcMETx,tcMETy,tcMETz);
    
    caloMET     = sqrt( caloMETx*caloMETx + caloMETy*caloMETy );
    caloMETphi2 = atan2(caloMETy,caloMETx);
    caloMETeta  = calcEta(caloMETx,caloMETy,caloMETz);
    
    //Get the jetinformation
    //get the calo jets
    std::vector<double> tmpCaloJetPx;
    std::vector<double> tmpCaloJetPy;
    std::vector<double> tmpCaloJetPz;
    std::vector<double> tmpCaloJetPt;
    std::vector<double> tmpCaloJetEt;
    std::vector<double> tmpCaloJetE;
    std::vector<double> tmpCaloJetEta;
    std::vector<double> tmpCaloJetPhi;
    std::vector<double> tmpCaloJetFem;
    std::vector<double> tmpCaloJetfHPD;
    std::vector<double> tmpCaloJetfRBX;
    std::vector<double> tmpCaloJetn90;
    
    std::vector<double> tmpGenJetPx;
    std::vector<double> tmpGenJetPy;
    std::vector<double> tmpGenJetPz;
    std::vector<double> tmpGenJetPt;
    std::vector<double> tmpGenJetEt;
    std::vector<double> tmpGenJetE;
    std::vector<double> tmpGenJetEta;
    std::vector<double> tmpGenJetPhi;
    std::vector<double> tmpGenJetFem;
    
    double tmpGenHt    = 0.;
    double tmpGenMHt   = 0.;
    double tmpGenMHx   = 0.;
    double tmpGenMHy   = 0.;
    
    if (doGenInfo_) {
      tmpGenHt    = GenHt;   
      tmpGenMHt   = GenMHt;  
      tmpGenMHx   = GenMHx;  
      tmpGenMHy   = GenMHy;  
    }
    
    int    tmpCaloNJets = CaloNJets;
    double tmpCaloHt    = CaloHt;   
    double tmpCaloMHt   = CaloMHt;  
    double tmpCaloMHx   = CaloMHx;  
    double tmpCaloMHy   = CaloMHy;  

    int calojoffset = 0;
    if ( tmpCaloNJets>0 ) {
      tmpCaloJetPx.resize(tmpCaloNJets);
      tmpCaloJetPy.resize(tmpCaloNJets);
      tmpCaloJetPz.resize(tmpCaloNJets);
      tmpCaloJetPt.resize(tmpCaloNJets);
      tmpCaloJetEt.resize(tmpCaloNJets);
      tmpCaloJetE.resize(tmpCaloNJets);
      tmpCaloJetEta.resize(tmpCaloNJets);
      tmpCaloJetPhi.resize(tmpCaloNJets);
      tmpCaloJetFem.resize(tmpCaloNJets);
      tmpCaloJetfHPD.resize(tmpCaloNJets);
      tmpCaloJetfRBX.resize(tmpCaloNJets);
      tmpCaloJetn90.resize(tmpCaloNJets);

      if (doGenInfo_) {
	tmpGenJetPx.resize(tmpCaloNJets);
	tmpGenJetPy.resize(tmpCaloNJets);
	tmpGenJetPz.resize(tmpCaloNJets);
	tmpGenJetPt.resize(tmpCaloNJets);
	tmpGenJetEt.resize(tmpCaloNJets);
	tmpGenJetE.resize(tmpCaloNJets);
	tmpGenJetEta.resize(tmpCaloNJets);
	tmpGenJetPhi.resize(tmpCaloNJets);
      }
      
      for (int ijet = 0; ijet < tmpCaloNJets; ++ijet) {
	if (CaloJetEta[ijet]  < cut_alljeteta     &&
	    CaloJetEt[ijet]  > cut_alljetet       &&
	    (CaloJetEta[ijet] > 2.6 ||
	     CaloJetFem[ijet]  > cut_jetemfrac[0])&&
	    CaloJetFem[ijet]  < cut_jetemfrac[1]  && 
	    CaloJetfHPD[ijet] < cut_jethpdfrac[1] && 
	    //CaloJetfHPD[ijet] > cut_jethpdfrac[0] &&
	    CaloJetfRBX[ijet] < cut_jetrbxfrac[1] &&
	    //CaloJetfRBX[ijet] > cut_jetrbxfrac[0] &&
	    //CaloJetn90[ijet]  < cut_jetn90[1]     &&
	    CaloJetn90[ijet]  > cut_jetn90[0]
	    ) {
	  
	  tmpCaloJetE.at(ijet-calojoffset)    = CaloJetE[ijet];
	  tmpCaloJetEt.at(ijet-calojoffset)   = CaloJetEt[ijet];
	  tmpCaloJetPt.at(ijet-calojoffset)   = CaloJetPt[ijet];
	  tmpCaloJetPx.at(ijet-calojoffset)   = CaloJetPx[ijet];
	  tmpCaloJetPy.at(ijet-calojoffset)   = CaloJetPy[ijet];
	  tmpCaloJetPz.at(ijet-calojoffset)   = CaloJetPz[ijet];
	  tmpCaloJetEta.at(ijet-calojoffset)  = CaloJetEta[ijet];
	  tmpCaloJetPhi.at(ijet-calojoffset)  = CaloJetPhi[ijet];
	  tmpCaloJetFem.at(ijet-calojoffset)  = CaloJetFem[ijet];
	  tmpCaloJetfHPD.at(ijet-calojoffset) = CaloJetfHPD[ijet];
	  tmpCaloJetfRBX.at(ijet-calojoffset) = CaloJetfRBX[ijet];
	  tmpCaloJetn90.at(ijet-calojoffset)  = CaloJetn90[ijet];

	  if (doGenInfo_) {
	    tmpGenJetE.at(ijet-calojoffset)    = GenJetE[ijet];
	    tmpGenJetEt.at(ijet-calojoffset)   = GenJetEt[ijet];
	    tmpGenJetPt.at(ijet-calojoffset)   = GenJetPt[ijet];
	    tmpGenJetPx.at(ijet-calojoffset)   = GenJetPx[ijet];
	    tmpGenJetPy.at(ijet-calojoffset)   = GenJetPy[ijet];
	    tmpGenJetPz.at(ijet-calojoffset)   = GenJetPz[ijet];
	    tmpGenJetEta.at(ijet-calojoffset)  = GenJetEta[ijet];
	    tmpGenJetPhi.at(ijet-calojoffset)  = GenJetPhi[ijet];
	  }
	}
	else {
	  tmpCaloHt  = helperFunctions::correctHt(tmpCaloHt,   CaloJetPt[ijet]);
	  tmpCaloMHx = helperFunctions::correctMHx(tmpCaloMHx, CaloJetPx[ijet]);
	  tmpCaloMHy = helperFunctions::correctMHy(tmpCaloMHy, CaloJetPy[ijet]);

	  if (doGenInfo_) {
	    tmpGenHt  = helperFunctions::correctHt(tmpGenHt,   GenJetPt[ijet]);
	    tmpGenMHx = helperFunctions::correctMHx(tmpGenMHx, GenJetPx[ijet]);
	    tmpGenMHy = helperFunctions::correctMHy(tmpGenMHy, GenJetPy[ijet]);
	  }
	  ++calojoffset;
	}
      }
    }
    tmpCaloMHt = sqrt(tmpCaloMHx*tmpCaloMHx + tmpCaloMHx*tmpCaloMHx);
    if (doGenInfo_) 
      tmpGenMHt  = sqrt(tmpGenMHx*tmpGenMHx + tmpGenMHx*tmpGenMHx);
    tmpCaloNJets -= calojoffset;

    /*
    //get the jpt jets
    std::vector<double> tmpJPTJetPx;
    std::vector<double> tmpJPTJetPy;
    std::vector<double> tmpJPTJetPz;
    std::vector<double> tmpJPTJetPt;
    std::vector<double> tmpJPTJetEt;
    std::vector<double> tmpJPTJetE;
    std::vector<double> tmpJPTJetEta;
    std::vector<double> tmpJPTJetPhi;
    std::vector<double> tmpJPTJetFem;
    std::vector<double> tmpJPTJetfHPD;
    std::vector<double> tmpJPTJetfRBX;
    std::vector<double> tmpJPTJetn90;

    int    tmpJPTNJets = JPTNJets;
    double tmpJPTHt    = JPTHt;   
    double tmpJPTMHt   = JPTMHt;  
    double tmpJPTMHx   = JPTMHx;  
    double tmpJPTMHy   = JPTMHy;  
    
    int jptjoffset = 0;
    if ( tmpJPTNJets>0 ) {
      tmpJPTJetPx.resize(tmpJPTNJets);
      tmpJPTJetPy.resize(tmpJPTNJets);
      tmpJPTJetPz.resize(tmpJPTNJets);
      tmpJPTJetPt.resize(tmpJPTNJets);
      tmpJPTJetE.resize(tmpJPTNJets);
      tmpJPTJetEt.resize(tmpJPTNJets);
      tmpJPTJetEta.resize(tmpJPTNJets);
      tmpJPTJetPhi.resize(tmpJPTNJets);
      tmpJPTJetFem.resize(tmpJPTNJets);
      tmpJPTJetfHPD.resize(tmpJPTNJets);
      tmpJPTJetfRBX.resize(tmpJPTNJets);
      tmpJPTJetn90.resize(tmpJPTNJets);
      
      for (int ijet = 0; ijet < tmpJPTNJets; ++ijet) {
	if (JPTJetFem[ijet]  < cut_jetemfrac[1]  &&
	    JPTJetFem[ijet]  > cut_jetemfrac[0]  &&
	    JPTJetfHPD[ijet] < cut_jethpdfrac[1] &&
	    //JPTJetfHPD[ijet] > cut_jethpdfrac[0] &&
	    JPTJetfRBX[ijet] < cut_jetrbxfrac[1] &&
	    //JPTJetfRBX[ijet] > cut_jetrbxfrac[0] &&
	    //JPTJetn90[ijet]  < cut_jetn90[1]     &&
	    JPTJetn90[ijet]  > cut_jetn90[0]     &&
	    JPTJetEta[ijet]  < cut_alljeteta     &&
	    JPTJetEt[ijet]  > cut_alljetet) {
	  
	  tmpJPTJetE.at(ijet-jptjoffset)    = JPTJetE[ijet];
	  tmpJPTJetEt.at(ijet-jptjoffset)   = JPTJetEt[ijet];
	  tmpJPTJetPt.at(ijet-jptjoffset)   = JPTJetPt[ijet];
	  tmpJPTJetPx.at(ijet-jptjoffset)   = JPTJetPx[ijet];
	  tmpJPTJetPy.at(ijet-jptjoffset)   = JPTJetPy[ijet];
	  tmpJPTJetPz.at(ijet-jptjoffset)   = JPTJetPz[ijet];
	  tmpJPTJetEta.at(ijet-jptjoffset)  = JPTJetEta[ijet];
	  tmpJPTJetPhi.at(ijet-jptjoffset)  = JPTJetPhi[ijet];
	  tmpJPTJetFem.at(ijet-jptjoffset)  = JPTJetFem[ijet];
	  tmpJPTJetfHPD.at(ijet-jptjoffset) = JPTJetfHPD[ijet];
	  tmpJPTJetfRBX.at(ijet-jptjoffset) = JPTJetfRBX[ijet];
	  tmpJPTJetn90.at(ijet-jptjoffset)  = JPTJetn90[ijet];
	}
	else {
	  tmpJPTHt  = helperFunctions::correctHt(tmpJPTHt,   JPTJetPt[ijet]);
	  tmpJPTMHx = helperFunctions::correctMHx(tmpJPTMHx, JPTJetPx[ijet]);
	  tmpJPTMHy = helperFunctions::correctMHy(tmpJPTMHy, JPTJetPy[ijet]);
	  ++jptjoffset;
	}
      }
    }
    tmpJPTMHt = sqrt(tmpJPTMHx*tmpJPTMHx + tmpJPTMHx*tmpJPTMHx);
    tmpJPTNJets -= jptjoffset;
    
    //get the particle flow jets
    std::vector<double> tmpPFJetPx;
    std::vector<double> tmpPFJetPy;
    std::vector<double> tmpPFJetPz;
    std::vector<double> tmpPFJetPt;
    std::vector<double> tmpPFJetE;
    std::vector<double> tmpPFJetEt;
    std::vector<double> tmpPFJetEta;
    std::vector<double> tmpPFJetPhi;
    std::vector<double> tmpPFJetFem;
    std::vector<double> tmpPFJetCharge;

    int    tmpPFNJets = PFNJets;
    double tmpPFHt    = PFHt;   
    double tmpPFMHt   = PFMHt;  
    double tmpPFMHx   = PFMHx;  
    double tmpPFMHy   = PFMHy;  

    int pfjoffset = 0;
    if ( tmpPFNJets>0 ) {
      tmpPFJetPx.resize(tmpPFNJets);
      tmpPFJetPy.resize(tmpPFNJets);
      tmpPFJetPz.resize(tmpPFNJets);
      tmpPFJetPt.resize(tmpPFNJets);
      tmpPFJetE.resize(tmpPFNJets);
      tmpPFJetEt.resize(tmpPFNJets);
      tmpPFJetEta.resize(tmpPFNJets);
      tmpPFJetPhi.resize(tmpPFNJets);
      tmpPFJetFem.resize(tmpPFNJets);
      tmpPFJetCharge.resize(tmpPFNJets);
      
      for (int ijet = 0; ijet < tmpPFNJets; ++ijet) {
	if (PFJetEta[ijet]  < cut_alljeteta && PFJetEt[ijet]  > cut_alljetet) {
	  tmpPFJetPx.at(ijet-pfjoffset)  = PFJetPx[ijet];
	  tmpPFJetPy.at(ijet-pfjoffset)  = PFJetPy[ijet];
	  tmpPFJetPz.at(ijet-pfjoffset)  = PFJetPz[ijet];
	  tmpPFJetPt.at(ijet-pfjoffset)  = PFJetPt[ijet];
	  tmpPFJetE.at(ijet-pfjoffset)  = PFJetE[ijet];
	  tmpPFJetEt.at(ijet-pfjoffset)  = PFJetEt[ijet];
	  tmpPFJetEta.at(ijet-pfjoffset) = PFJetEta[ijet];
	  tmpPFJetPhi.at(ijet-pfjoffset) = PFJetPhi[ijet];
	  tmpPFJetFem.at(ijet-pfjoffset) = PFJetFem[ijet];
	  tmpPFJetCharge.at(ijet-pfjoffset) = PFJetCharge[ijet];
	}
	else {
	  tmpPFHt  = helperFunctions::correctHt(tmpPFHt,   PFJetPt[ijet]);
	  tmpPFMHx = helperFunctions::correctMHx(tmpPFMHx, PFJetPx[ijet]);
	  tmpPFMHy = helperFunctions::correctMHy(tmpPFMHy, PFJetPy[ijet]);
	  ++pfjoffset;
	}
      }
    }
    tmpPFMHt = sqrt(tmpPFMHx*tmpPFMHx + tmpPFMHy*tmpPFMHy);
    tmpPFNJets -= pfjoffset;
    
    //get the track jets
    std::vector<double> tmpTrackJetPx;
    std::vector<double> tmpTrackJetPy;
    std::vector<double> tmpTrackJetPz;
    std::vector<double> tmpTrackJetPt;
    std::vector<double> tmpTrackJetE;
    std::vector<double> tmpTrackJetEt;
    std::vector<double> tmpTrackJetEta;
    std::vector<double> tmpTrackJetPhi;
    std::vector<double> tmpTrackJetFem;
    std::vector<double> tmpTrackJetCharge;

    int    tmpTrackNJets = TrackNJets;
    double tmpTrackHt    = TrackHt;   
    double tmpTrackMHt   = TrackMHt;  
    double tmpTrackMHx   = TrackMHx;  
    double tmpTrackMHy   = TrackMHy;  

    int trackjoffset = 0;
    if ( tmpTrackNJets>0 ) {
      tmpTrackJetPx.resize(tmpTrackNJets);
      tmpTrackJetPy.resize(tmpTrackNJets);
      tmpTrackJetPz.resize(tmpTrackNJets);
      tmpTrackJetPt.resize(tmpTrackNJets);
      tmpTrackJetE.resize(tmpTrackNJets);
      tmpTrackJetEt.resize(tmpTrackNJets);
      tmpTrackJetEta.resize(tmpTrackNJets);
      tmpTrackJetPhi.resize(tmpTrackNJets);
      tmpTrackJetFem.resize(tmpTrackNJets);
      tmpTrackJetCharge.resize(tmpTrackNJets);
      
      for (int ijet = 0; ijet < tmpTrackNJets; ++ijet) {
	if (TrackJetEta[ijet]  < cut_alljeteta && TrackJetEt[ijet]  > cut_alljetet) {
	  tmpTrackJetPx.at(ijet-trackjoffset)  = TrackJetPx[ijet];
	  tmpTrackJetPy.at(ijet-trackjoffset)  = TrackJetPy[ijet];
	  tmpTrackJetPz.at(ijet-trackjoffset)  = TrackJetPz[ijet];
	  tmpTrackJetPt.at(ijet-trackjoffset)  = TrackJetPt[ijet];
	  tmpTrackJetE.at(ijet-trackjoffset)   = TrackJetE[ijet];
	  tmpTrackJetEt.at(ijet-trackjoffset)  = TrackJetEt[ijet];
	  tmpTrackJetEta.at(ijet-trackjoffset) = TrackJetEta[ijet];
	  tmpTrackJetPhi.at(ijet-trackjoffset) = TrackJetPhi[ijet];
	  tmpTrackJetFem.at(ijet-trackjoffset) = TrackJetFem[ijet];
	  tmpTrackJetCharge.at(ijet-trackjoffset) = TrackJetCharge[ijet];
	}
	else {
	  tmpTrackHt  = helperFunctions::correctHt(tmpTrackHt,   TrackJetPt[ijet]);
	  tmpTrackMHx = helperFunctions::correctMHx(tmpTrackMHx, TrackJetPx[ijet]);
	  tmpTrackMHy = helperFunctions::correctMHy(tmpTrackMHy, TrackJetPy[ijet]);
	  ++trackjoffset;
	}
      }
    }
    tmpTrackMHt = sqrt(tmpTrackMHx*tmpTrackMHx + tmpTrackMHx*tmpTrackMHx);
    tmpTrackNJets -= trackjoffset;
    */
    //if (tmpCaloNJets<2) // && tmpJPTNJets<2 && tmpPFNJets<2 && tmpTrackNJets<2)
    //  continue;

    bool caloJetVeto  = false;
    /*
      bool jptJetVeto   = false;
      bool pfJetVeto    = false;
      bool trackJetVeto = false;
    */

    if (tmpCaloNJets > 2 )
      if (tmpCaloJetEt[2]  > cut_third_jetet)
	caloJetVeto  = true;
    /*
      if (tmpJPTNJets > 2 )
      if (tmpJPTJetEt[2]   > cut_third_jetet)
      jptJetVeto   = true;
      if (tmpPFNJets > 2 )
      if (tmpPFJetEt[2]    > cut_third_jetet)
      pfJetVeto    = true;
      if (tmpTrackNJets > 2 )
      if (tmpTrackJetEt[2] > cut_third_jetet)
      trackJetVeto = true;
    */
    
    //if (tmpCaloNJets>2 && tmpJPTNJets>2 && tmpPFNJets>2 && tmpTrackNJets>2)
    if (caloJetVeto)// && jptJetVeto && pfJetVeto && trackJetVeto)
      continue;
    
    double genjet12deta   = 0., genjet12dphi   = 0., genjet1metdphi[3]   = {0.}, genjet2metdphi[3]   = {0.}, genmetmhtdphi[3]   = {0.}, genmetperp[3]   = {0.}, genmetpara[3]   = {0.};
    double calojet12deta  = 0., calojet12dphi  = 0., calojet1metdphi[3]  = {0.}, calojet2metdphi[3]  = {0.}, calometmhtdphi[3]  = {0.}, calometperp[3]  = {0.}, calometpara[3]  = {0.};
    //double jptjet12deta   = 0., jptjet12dphi   = 0., jptjet1metdphi[3]   = {0.}, jptjet2metdphi[3]   = {0.}, jptmetmhtdphi[3]   = {0.}, jptmetperp[3]   = {0.}, jptmetpara[3]   = {0.};
    //double pfjet12deta    = 0., pfjet12dphi    = 0., pfjet1metdphi[3]    = {0.}, pfjet2metdphi[3]    = {0.}, pfmetmhtdphi[3]    = {0.}, pfmetperp[3]    = {0.}, pfmetpara[3]    = {0.};
    //double trackjet12deta = 0., trackjet12dphi = 0., trackjet1metdphi[3] = {0.}, trackjet2metdphi[3] = {0.}, trackmetmhtdphi[3] = {0.}, trackmetperp[3] = {0.}, trackmetpara[3] = {0.};

    double genjet12dR = 0., calojet12dR = 0., jptjet12dR = 0, pfjet12dR = 0., trackjet12dR = 0.;

    double tmpGenMHtphi   = atan2(tmpGenMHy,tmpGenMHx);
    double tmpCaloMHtphi  = atan2(tmpCaloMHy,tmpCaloMHx);
    /*
    double tmpJPTMHtphi   = atan2(tmpJPTMHy,tmpJPTMHx);
    double tmpPFMHtphi    = atan2(tmpPFMHy,tmpPFMHx);
    double tmpTrackMHtphi = atan2(tmpTrackMHy,tmpTrackMHx);
    */

    double genjet1jet2dPt   = 0., calojet1jet2dPt   = 0., jptjet1jet2dPt   = 0., pfjet1jet2dPt   = 0., trackjet1jet2dPt   = 0.;
    double genjet1jet2avgPt = 0., calojet1jet2avgPt = 0., jptjet1jet2avgPt = 0., pfjet1jet2avgPt = 0., trackjet1jet2avgPt = 0.;



    if (tmpCaloNJets>1) {
      if ((fabs(tmpCaloJetEt[0]) > cut_jet1et && fabs(tmpCaloJetEta[0]) < cut_jet1eta ) &&
	  (fabs(tmpCaloJetEt[1]) > cut_jet2et && fabs(tmpCaloJetEta[1]) < cut_jet2eta ))
	{
	  calojet1jet2dPt = helperFunctions::deltaPt(tmpCaloJetPt[0],tmpCaloJetEta[0],tmpCaloJetPt[1],tmpCaloJetEta[1]);
	  calojet12dphi   = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[0],tmpCaloJetPhi[1]);
	  
	  //std::cout<<"Dphi Jet12 "<<calojet12dphi<<" dPt "<<calojet1jet2dPt<<std::endl;
	  
	  if (fabs(calojet12dphi) > cut_jet12dphi) {
	    
	    calojet1jet2avgPt = (tmpCaloJetPt[0]+tmpCaloJetPt[1])/2;
	    
	    calojet12dR     = helperFunctions::deltaR(tmpCaloJetEta[0],tmpCaloJetPhi[0],tmpCaloJetEta[1],tmpCaloJetPhi[1]);
	    calojet12deta   = fabs(tmpCaloJetEta[0]) - fabs(tmpCaloJetEta[1]);
	    
	    calojet1metdphi[0] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[0],caloMETphi_Fullcorr_nocc);
	    calojet2metdphi[0] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[1],caloMETphi_Fullcorr_nocc);
	    calometmhtdphi[0]  = helperFunctions::deltaPhiUnsigned(caloMETphi_Fullcorr_nocc,tmpCaloMHtphi);
	    calometperp[0]     = helperFunctions::perpComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],caloMETphi2)*caloMET;
	    calometpara[0]     = helperFunctions::paraComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],caloMETphi2)*caloMET;

	    calojet1metdphi[1] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[0],pfMETphi_Fullcorr_nocc);
	    calojet2metdphi[1] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[1],pfMETphi_Fullcorr_nocc);
	    calometmhtdphi[1]  = helperFunctions::deltaPhiUnsigned(pfMETphi_Fullcorr_nocc,tmpCaloMHtphi);
	    calometperp[1]     = helperFunctions::perpComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],pfMETphi2)*pfMET;
	    calometpara[1]     = helperFunctions::paraComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],pfMETphi2)*pfMET;

	    calojet1metdphi[2] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[0],tcMETphi_Fullcorr_nocc);
	    calojet2metdphi[2] = helperFunctions::deltaPhiUnsigned(tmpCaloJetPhi[1],tcMETphi_Fullcorr_nocc);
	    calometmhtdphi[2]  = helperFunctions::deltaPhiUnsigned(tcMETphi_Fullcorr_nocc,tmpCaloMHtphi);
	    calometperp[2]     = helperFunctions::perpComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],tcMETphi2)*tcMET;
	    calometpara[2]     = helperFunctions::paraComp(tmpCaloJetPhi[0],tmpCaloJetEta[0],tmpCaloJetPhi[1],tmpCaloJetEta[1],tcMETphi2)*tcMET;


	    h_jet12dPt[0]->Fill(calojet1jet2dPt);
	    h_jet12avgPt[0]->Fill(calojet1jet2avgPt);
	    h_jet12dphi[0]->Fill(calojet12dphi);
	    h_jet12dR[0]->Fill(calojet12dR);
	    //calo met
	    h_jet1metdphi[0][0]->Fill(calojet1metdphi[0]);
	    h_jet2metdphi[0][0]->Fill(calojet2metdphi[0]);
	    h_metmhtdphi[0][0]->Fill(calometmhtdphi[0]);
	    h_met[0][0]->Fill(caloMET);
	    h_metperp[0][0]->Fill(calometperp[0]);
	    h_metpara[0][0]->Fill(calometpara[0]);
	    //pf met
	    h_jet1metdphi[0][1]->Fill(calojet1metdphi[1]);
	    h_jet2metdphi[0][1]->Fill(calojet2metdphi[1]);
	    h_metmhtdphi[0][1]->Fill(calometmhtdphi[1]);
	    h_met[0][1]->Fill(pfMET);
	    h_metperp[0][1]->Fill(calometperp[1]);
	    h_metpara[0][1]->Fill(calometpara[1]);
	    //tc met
	    h_jet1metdphi[0][2]->Fill(calojet1metdphi[2]);
	    h_jet2metdphi[0][2]->Fill(calojet2metdphi[2]);
	    h_metmhtdphi[0][2]->Fill(calometmhtdphi[2]);
	    h_met[0][2]->Fill(tcMET);
	    h_metperp[0][2]->Fill(calometperp[2]);
	    h_metpara[0][2]->Fill(calometpara[2]);

	    //Calo Jets
	    h2_jet12dPtvsavgPt[0][0]->Fill(calojet1jet2avgPt,calojet1jet2dPt);
	    h2_jet12dPtvsdphi[0]->Fill(calojet12dphi,calojet1jet2dPt);
	    h2_jet12dPtvsdR[0]->Fill(calojet12dR,calojet1jet2dPt);
	    h2_jet12dPtvsetaj1[0]->Fill(tmpCaloJetEta.at(0),calojet1jet2dPt);
	    h2_jet12dPtvsetaj2[0]->Fill(tmpCaloJetEta.at(1),calojet1jet2dPt);
	    h2_mhtvsdPt[0]->Fill(calojet1jet2dPt,tmpCaloMHt);
	    h2_mhtvsavgPt[0][0]->Fill(calojet1jet2avgPt,tmpCaloMHt);

	    //Special for gen jets
	    if (doGenInfo_) {
	      h2_jet12dPtvsavgPt[1][0]->Fill(genjet1jet2avgPt,calojet1jet2dPt);
	      h2_mhtvsavgPt[1][0]->Fill(genjet1jet2avgPt,tmpCaloMHt);

	      h2_jet1metdphivsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calojet1metdphi[0]);
	      h2_jet2metdphivsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calojet2metdphi[0]);
	      h2_metmhtdphivsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calometmhtdphi[0]);
	      h2_metvsavgPt[1][0][0]->Fill(genjet1jet2avgPt,caloMET);
	      h2_metdijetbisectordphivsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calojet1metdphi[0]-(calojet12dphi/2));
	      h2_metperpvsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calometperp[0]);
	      h2_metparavsavgPt[1][0][0]->Fill(genjet1jet2avgPt,calometpara[0]);

	      h2_jet1metdphivsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calojet1metdphi[1]);
	      h2_jet2metdphivsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calojet2metdphi[1]);
	      h2_metmhtdphivsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calometmhtdphi[1]);
	      h2_metvsavgPt[1][0][1]->Fill(genjet1jet2avgPt,pfMET);
	      h2_metdijetbisectordphivsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calojet1metdphi[1]-(calojet12dphi/2));
	      h2_metperpvsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calometperp[1]);
	      h2_metparavsavgPt[1][0][1]->Fill(genjet1jet2avgPt,calometpara[1]);

	      h2_jet1metdphivsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calojet1metdphi[2]);
	      h2_jet2metdphivsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calojet2metdphi[2]);
	      h2_metmhtdphivsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calometmhtdphi[0]);
	      h2_metvsavgPt[1][0][2]->Fill(genjet1jet2avgPt,tcMET);
	      h2_metdijetbisectordphivsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calojet1metdphi[2]-(calojet12dphi/2));
	      h2_metperpvsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calometperp[2]);
	      h2_metparavsavgPt[1][0][2]->Fill(genjet1jet2avgPt,calometpara[2]);
	    }

	    //calo met
	    h2_jet1metdphivsdPt[0][0]->Fill(calojet1jet2dPt,calojet1metdphi[0]);
	    h2_jet2metdphivsdPt[0][0]->Fill(calojet1jet2dPt,calojet2metdphi[0]);
	    h2_jet1metdphivsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calojet1metdphi[0]);
	    h2_jet2metdphivsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calojet2metdphi[0]);
	    h2_jet1metdphivsdphi[0][0]->Fill(calojet12dphi,calojet1metdphi[0]);
	    h2_jet2metdphivsdphi[0][0]->Fill(calojet12dphi,calojet2metdphi[0]);
	    h2_metmhtdphivsdPt[0][0]->Fill(calojet1jet2dPt,calometmhtdphi[0]);
	    h2_metmhtdphivsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calometmhtdphi[0]);
	    h2_metvsdPt[0][0]->Fill(calojet1jet2dPt,caloMET);
	    h2_metvsjet12dphi[0][0]->Fill(calojet12dphi,caloMET);
	    h2_metvsavgPt[0][0][0]->Fill(calojet1jet2avgPt,caloMET);
	    h2_metvsdijetbisectorphi[0][0]->Fill(calojet12dphi/2,caloMET);
	    h2_metperpvsdijetbisectorphi[0][0]->Fill(calojet12dphi/2,calometperp[0]);
	    h2_metparavsdijetbisectorphi[0][0]->Fill(calojet12dphi/2,calometpara[0]);
	    h2_metdijetbisectordphivsdPt[0][0]->Fill(calojet1jet2dPt,calojet1metdphi[0]-(calojet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calojet1metdphi[0]-(calojet12dphi/2));
	    h2_metperpvsjet12dphi[0][0]->Fill(calojet12dphi,calometperp[0]);
	    h2_metparavsjet12dphi[0][0]->Fill(calojet12dphi,calometpara[0]);
	    h2_metperpvsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calometperp[0]);
	    h2_metparavsavgPt[0][0][0]->Fill(calojet1jet2avgPt,calometpara[0]);
	    h2_metperpvspara[0][0]->Fill(calometpara[0],calometperp[0]);
	    h2_metperpvsmet[0][0]->Fill(caloMET,calometperp[0]);
	    h2_metparavsmet[0][0]->Fill(caloMET,calometpara[0]);
	    h2_j1metdphivsj2metdphi[0][0]->Fill(calojet2metdphi[0],calojet1metdphi[0]);


	    //pf met
	    h2_jet1metdphivsdPt[0][1]->Fill(calojet1jet2dPt,calojet1metdphi[1]);
	    h2_jet2metdphivsdPt[0][1]->Fill(calojet1jet2dPt,calojet2metdphi[1]);
	    h2_jet1metdphivsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calojet1metdphi[1]);
	    h2_jet2metdphivsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calojet2metdphi[1]);
	    h2_jet1metdphivsdphi[0][1]->Fill(calojet12dphi,calojet1metdphi[1]);
	    h2_jet2metdphivsdphi[0][1]->Fill(calojet12dphi,calojet2metdphi[1]);
	    h2_metmhtdphivsdPt[0][1]->Fill(calojet1jet2dPt,calometmhtdphi[1]);
	    h2_metmhtdphivsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calometmhtdphi[1]);
	    h2_metvsdPt[0][1]->Fill(calojet1jet2dPt,pfMET);
	    h2_metvsjet12dphi[0][1]->Fill(calojet12dphi,pfMET);
	    h2_metvsavgPt[0][0][1]->Fill(calojet1jet2avgPt,pfMET);
	    h2_metvsdijetbisectorphi[0][1]->Fill(calojet12dphi/2,pfMET);
	    h2_metperpvsdijetbisectorphi[0][1]->Fill(calojet12dphi/2,calometperp[1]);
	    h2_metparavsdijetbisectorphi[0][1]->Fill(calojet12dphi/2,calometpara[1]);
	    h2_metdijetbisectordphivsdPt[0][1]->Fill(calojet1jet2dPt,calojet1metdphi[1]-(calojet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calojet1metdphi[1]-(calojet12dphi/2));
	    h2_metperpvsjet12dphi[0][1]->Fill(calojet12dphi,calometperp[1]);
	    h2_metparavsjet12dphi[0][1]->Fill(calojet12dphi,calometpara[1]);
	    h2_metperpvsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calometperp[1]);
	    h2_metparavsavgPt[0][0][1]->Fill(calojet1jet2avgPt,calometpara[1]);
	    h2_metperpvspara[0][1]->Fill(calometpara[1],calometperp[1]);
	    h2_metperpvsmet[0][1]->Fill(pfMET,calometperp[1]);
	    h2_metparavsmet[0][1]->Fill(pfMET,calometpara[1]);
	    h2_j1metdphivsj2metdphi[0][1]->Fill(calojet2metdphi[1],calojet1metdphi[1]);
	    //tc met
	    h2_jet1metdphivsdPt[0][2]->Fill(calojet1jet2dPt,calojet1metdphi[2]);
	    h2_jet2metdphivsdPt[0][2]->Fill(calojet1jet2dPt,calojet2metdphi[2]);
	    h2_jet1metdphivsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calojet1metdphi[2]);
	    h2_jet2metdphivsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calojet2metdphi[2]);
	    h2_jet1metdphivsdphi[0][2]->Fill(calojet12dphi,calojet1metdphi[2]);
	    h2_jet2metdphivsdphi[0][2]->Fill(calojet12dphi,calojet2metdphi[2]);
	    h2_metmhtdphivsdPt[0][2]->Fill(calojet1jet2dPt,calometmhtdphi[2]);
	    h2_metmhtdphivsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calometmhtdphi[2]);
	    h2_metvsdPt[0][2]->Fill(calojet1jet2dPt,tcMET);
	    h2_metvsjet12dphi[0][2]->Fill(calojet12dphi,tcMET);
	    h2_metvsavgPt[0][0][2]->Fill(calojet1jet2avgPt,tcMET);
	    h2_metvsdijetbisectorphi[0][2]->Fill(calojet12dphi/2,tcMET);
	    h2_metperpvsdijetbisectorphi[0][2]->Fill(calojet12dphi/2,calometperp[2]);
	    h2_metparavsdijetbisectorphi[0][2]->Fill(calojet12dphi/2,calometpara[2]);
	    h2_metdijetbisectordphivsdPt[0][2]->Fill(calojet1jet2dPt,calojet1metdphi[2]-(calojet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calojet1metdphi[2]-(calojet12dphi/2));
	    h2_metperpvsjet12dphi[0][2]->Fill(calojet12dphi,calometperp[2]);
	    h2_metparavsjet12dphi[0][2]->Fill(calojet12dphi,calometpara[2]);
	    h2_metperpvsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calometperp[2]);
	    h2_metparavsavgPt[0][0][2]->Fill(calojet1jet2avgPt,calometpara[2]);
	    h2_metperpvspara[0][2]->Fill(calometpara[2],calometperp[2]);
	    h2_metperpvsmet[0][2]->Fill(tcMET,calometperp[2]);
	    h2_metparavsmet[0][2]->Fill(tcMET,calometpara[2]);
	    h2_j1metdphivsj2metdphi[0][2]->Fill(calojet2metdphi[2],calojet1metdphi[2]);

	    if (calojet1jet2avgPt>30.) {
	      h2_metvsjet12deta[0][0]->Fill(calojet12deta,caloMET);
	      h2_metperpvsjet12deta[0][0]->Fill(calojet12deta,calometperp[0]);
	      h2_metparavsjet12deta[0][0]->Fill(calojet12deta,calometpara[0]);
	      h2_metvsjet12deta[0][1]->Fill(calojet12deta,pfMET);
	      h2_metperpvsjet12deta[0][1]->Fill(calojet12deta,calometperp[1]);
	      h2_metparavsjet12deta[0][1]->Fill(calojet12deta,calometpara[1]);
	      h2_metvsjet12deta[0][2]->Fill(calojet12deta,tcMET);
	      h2_metperpvsjet12deta[0][2]->Fill(calojet12deta,calometperp[2]);
	      h2_metparavsjet12deta[0][2]->Fill(calojet12deta,calometpara[2]);
	    }
	    
	    //--- additional 1D histograms
	    bool jet1central = fabs(tmpCaloJetEta.at(0)) < 1.4;
	    bool jet2central = fabs(tmpCaloJetEta.at(1)) < 1.4;
	    bool jet1endm    = tmpCaloJetEta.at(0) <= -1.4;
	    bool jet1endp    = tmpCaloJetEta.at(0) >=  1.4;
	    bool jet2endm    = tmpCaloJetEta.at(1) <= -1.4;
	    bool jet2endp    = tmpCaloJetEta.at(1) >=  1.4;

	    if (jet1central && jet2central)
	      h_jet12dPtbothcentral[0]->Fill(calojet1jet2dPt);
	    if ( (jet1central && (jet2endp || jet2endm)) ||
		 (jet2central && (jet1endp || jet1endm)))
	      h_jet12dPtcentralendcaps[0]->Fill(calojet1jet2dPt);
	    if ( (jet1endp && jet2endp) || (jet1endm && jet2endm))
	      h_jet12dPtsameendcaps[0]->Fill(calojet1jet2dPt);
	    if ( (jet1endp && jet2endm) || (jet1endm && jet2endp))
	      h_jet12dPtoppositeendcaps[0]->Fill(calojet1jet2dPt);
	    
	    calodijeteventnumbers.push_back(Event);
	    ++numdijetevents[0];
	    //std::cout<<"Event: "<<Event<<" Run: "<<Run<<" is a dijet event"<<std::endl;
	  }
	}
    }

    /*
    //JPT dijet events
    if (tmpJPTNJets>1) {
      if ((fabs(tmpJPTJetEt[0]) > cut_jet1et && fabs(tmpJPTJetEta[0]) < cut_jet1eta ) &&
	  (fabs(tmpJPTJetEt[1]) > cut_jet2et && fabs(tmpJPTJetEta[1]) < cut_jet2eta ))
	{
	  jptjet1jet2dPt = tmpJPTJetPt[1]-tmpJPTJetPt[0];
	  jptjet12dphi   = helperFunctions::deltaPhi(tmpJPTJetPhi[0],tmpJPTJetPhi[1]);

      	  if (fabs(jptjet12dphi) > cut_jet12dphi) {

	    jptjet1jet2avgPt = (tmpJPTJetPt[0]+tmpJPTJetPt[1])/2;

	    jptjet12dR     = helperFunctions::deltaR(tmpJPTJetEta[0],tmpJPTJetPhi[0],tmpJPTJetEta[1],tmpJPTJetPhi[1]);

	    jptjet1metdphi[0] = helperFunctions::deltaPhi(tmpJPTJetPhi[0],caloMETphi_Fullcorr_nocc);
	    jptjet2metdphi[0] = helperFunctions::deltaPhi(tmpJPTJetPhi[1],caloMETphi_Fullcorr_nocc);
	    jptmetmhtdphi[0]  = helperFunctions::deltaPhi(caloMETphi_Fullcorr_nocc,tmpJPTMHtphi);
	    jptmetperp[0]     = helperFunctions::perpComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],caloMETphi2)*caloMET;
	    jptmetpara[0]     = helperFunctions::paraComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],caloMETphi2)*caloMET;

	    jptjet1metdphi[1] = helperFunctions::deltaPhi(tmpJPTJetPhi[0],pfMETphi_Fullcorr_nocc);
	    jptjet2metdphi[1] = helperFunctions::deltaPhi(tmpJPTJetPhi[1],pfMETphi_Fullcorr_nocc);
	    jptmetmhtdphi[1]  = helperFunctions::deltaPhi(pfMETphi_Fullcorr_nocc,tmpJPTMHtphi);
	    jptmetperp[1]     = helperFunctions::perpComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],pfMETphi2)*pfMET;
	    jptmetpara[1]     = helperFunctions::paraComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],pfMETphi2)*pfMET;

	    jptjet1metdphi[2] = helperFunctions::deltaPhi(tmpJPTJetPhi[0],tcMETphi_Fullcorr_nocc);
	    jptjet2metdphi[2] = helperFunctions::deltaPhi(tmpJPTJetPhi[1],tcMETphi_Fullcorr_nocc);
	    jptmetmhtdphi[2]  = helperFunctions::deltaPhi(tcMETphi_Fullcorr_nocc,tmpJPTMHtphi);
	    jptmetperp[2]     = helperFunctions::perpComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],tcMETphi2)*tcMET;
	    jptmetpara[2]     = helperFunctions::paraComp(tmpJPTJetPhi[0],tmpJPTJetPhi[1],tcMETphi2)*tcMET;


	    h_jet12dPt[1]->Fill(jptjet1jet2dPt);
	    h_jet12avgPt[1]->Fill(jptjet1jet2avgPt);
	    h_jet12dphi[1]->Fill(jptjet12dphi);
	    h_jet12dR[1]->Fill(jptjet12dR);
	    //calo met
	    h_jet1metdphi[1][0]->Fill(jptjet1metdphi[0]);
	    h_jet2metdphi[1][0]->Fill(jptjet2metdphi[0]);
	    h_metmhtdphi[1][0]->Fill(jptmetmhtdphi[0]);
	    h_met[1][0]->Fill(caloMET);
	    h_metperp[1][0]->Fill(jptmetperp[0]);
	    h_metpara[1][0]->Fill(jptmetpara[0]);
	    //pf met
	    h_jet1metdphi[1][1]->Fill(jptjet1metdphi[1]);
	    h_jet2metdphi[1][1]->Fill(jptjet2metdphi[1]);
	    h_metmhtdphi[1][1]->Fill(jptmetmhtdphi[1]);
	    h_met[1][1]->Fill(pfMET);
	    h_metperp[1][1]->Fill(jptmetperp[1]);
	    h_metpara[1][1]->Fill(jptmetpara[1]);
	    //tc met
	    h_jet1metdphi[1][2]->Fill(jptjet1metdphi[2]);
	    h_jet2metdphi[1][2]->Fill(jptjet2metdphi[2]);
	    h_metmhtdphi[1][2]->Fill(jptmetmhtdphi[2]);
	    h_met[1][2]->Fill(tcMET);
	    h_metperp[1][2]->Fill(jptmetperp[2]);
	    h_metpara[1][2]->Fill(jptmetpara[2]);

	    //Calo Jets
	    h2_jet12dPtvsavgPt[1]->Fill(jptjet1jet2avgPt,jptjet1jet2dPt);
	    h2_jet12dPtvsdphi[1]->Fill(jptjet12dphi,jptjet1jet2dPt);
	    h2_jet12dPtvsdR[1]->Fill(jptjet12dR,jptjet1jet2dPt);
	    h2_jet12dPtvsetaj1[1]->Fill(tmpJPTJetEta.at(0),jptjet1jet2dPt);
	    h2_jet12dPtvsetaj2[1]->Fill(tmpJPTJetEta.at(1),jptjet1jet2dPt);
	    h2_mhtvsdPt[1]->Fill(jptjet1jet2dPt,tmpJPTMHt);
	    h2_mhtvsavgPt[1]->Fill(jptjet1jet2avgPt,tmpJPTMHt);
	    //calo met
	    h2_jet1metdphivsdPt[1][0]->Fill(jptjet1jet2dPt,jptjet1metdphi[0]);
	    h2_jet2metdphivsdPt[1][0]->Fill(jptjet1jet2dPt,jptjet2metdphi[0]);
	    h2_jet1metdphivsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptjet1metdphi[0]);
	    h2_jet2metdphivsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptjet2metdphi[0]);
	    h2_jet1metdphivsdphi[1][0]->Fill(jptjet12dphi,jptjet1metdphi[0]);
	    h2_jet2metdphivsdphi[1][0]->Fill(jptjet12dphi,jptjet2metdphi[0]);
	    h2_metmhtdphivsdPt[1][0]->Fill(jptjet1jet2dPt,jptmetmhtdphi[0]);
	    h2_metmhtdphivsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptmetmhtdphi[0]);
	    h2_metvsdPt[1][0]->Fill(jptjet1jet2dPt,caloMET);
	    h2_metvsjet12dphi[1][0]->Fill(jptjet12dphi,caloMET);
	    h2_metvsavgPt[1][0]->Fill(jptjet1jet2avgPt,caloMET);
	    h2_metvsdijetbisectorphi[1][0]->Fill(jptjet12dphi/2,caloMET);
	    h2_metperpvsdijetbisectorphi[1][0]->Fill(jptjet12dphi/2,jptmetperp[0]);
	    h2_metparavsdijetbisectorphi[1][0]->Fill(jptjet12dphi/2,jptmetpara[0]);
	    h2_metdijetbisectordphivsdPt[1][0]->Fill(jptjet1jet2dPt,jptjet1metdphi[0]-(jptjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptjet1metdphi[0]-(jptjet12dphi/2));
	    h2_metperpvsjet12dphi[1][0]->Fill(jptjet12dphi,jptmetperp[0]);
	    h2_metparavsjet12dphi[1][0]->Fill(jptjet12dphi,jptmetpara[0]);
	    h2_metperpvsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptmetperp[0]);
	    h2_metparavsavgPt[1][0]->Fill(jptjet1jet2avgPt,jptmetpara[0]);
	    h2_metperpvspara[1][0]->Fill(jptmetpara[0],jptmetperp[0]);
	    h2_metperpvsmet[1][0]->Fill(caloMET,jptmetperp[0]);
	    h2_metparavsmet[1][0]->Fill(caloMET,jptmetpara[0]);
	    h2_j1metdphivsj2metdphi[1][0]->Fill(jptjet2metdphi[0],jptjet1metdphi[0]);
	    //pf met
	    h2_jet1metdphivsdPt[1][1]->Fill(jptjet1jet2dPt,jptjet1metdphi[1]);
	    h2_jet2metdphivsdPt[1][1]->Fill(jptjet1jet2dPt,jptjet2metdphi[1]);
	    h2_jet1metdphivsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptjet1metdphi[1]);
	    h2_jet2metdphivsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptjet2metdphi[1]);
	    h2_jet1metdphivsdphi[1][1]->Fill(jptjet12dphi,jptjet1metdphi[1]);
	    h2_jet2metdphivsdphi[1][1]->Fill(jptjet12dphi,jptjet2metdphi[1]);
	    h2_metmhtdphivsdPt[1][1]->Fill(jptjet1jet2dPt,jptmetmhtdphi[1]);
	    h2_metmhtdphivsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptmetmhtdphi[1]);
	    h2_metvsdPt[1][1]->Fill(jptjet1jet2dPt,pfMET);
	    h2_metvsjet12dphi[1][1]->Fill(jptjet12dphi,pfMET);
	    h2_metvsavgPt[1][1]->Fill(jptjet1jet2avgPt,pfMET);
	    h2_metvsdijetbisectorphi[1][1]->Fill(jptjet12dphi/2,pfMET);
	    h2_metperpvsdijetbisectorphi[1][1]->Fill(jptjet12dphi/2,jptmetperp[1]);
	    h2_metparavsdijetbisectorphi[1][1]->Fill(jptjet12dphi/2,jptmetpara[1]);
	    h2_metdijetbisectordphivsdPt[1][1]->Fill(jptjet1jet2dPt,jptjet1metdphi[1]-(jptjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptjet1metdphi[1]-(jptjet12dphi/2));
	    h2_metperpvsjet12dphi[1][1]->Fill(jptjet12dphi,jptmetperp[1]);
	    h2_metparavsjet12dphi[1][1]->Fill(jptjet12dphi,jptmetpara[1]);
	    h2_metperpvsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptmetperp[1]);
	    h2_metparavsavgPt[1][1]->Fill(jptjet1jet2avgPt,jptmetpara[1]);
	    h2_metperpvspara[1][1]->Fill(jptmetpara[1],jptmetperp[1]);
	    h2_metperpvsmet[1][1]->Fill(pfMET,jptmetperp[1]);
	    h2_metparavsmet[1][1]->Fill(pfMET,jptmetpara[1]);
	    h2_j1metdphivsj2metdphi[1][1]->Fill(jptjet2metdphi[1],jptjet1metdphi[1]);
	    //tc met
	    h2_jet1metdphivsdPt[1][2]->Fill(jptjet1jet2dPt,jptjet1metdphi[2]);
	    h2_jet2metdphivsdPt[1][2]->Fill(jptjet1jet2dPt,jptjet2metdphi[2]);
	    h2_jet1metdphivsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptjet1metdphi[2]);
	    h2_jet2metdphivsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptjet2metdphi[2]);
	    h2_jet1metdphivsdphi[1][2]->Fill(jptjet12dphi,jptjet1metdphi[2]);
	    h2_jet2metdphivsdphi[1][2]->Fill(jptjet12dphi,jptjet2metdphi[2]);
	    h2_metmhtdphivsdPt[1][2]->Fill(jptjet1jet2dPt,jptmetmhtdphi[2]);
	    h2_metmhtdphivsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptmetmhtdphi[2]);
	    h2_metvsdPt[1][2]->Fill(jptjet1jet2dPt,tcMET);
	    h2_metvsjet12dphi[1][2]->Fill(jptjet12dphi,tcMET);
	    h2_metvsavgPt[1][2]->Fill(jptjet1jet2avgPt,tcMET);
	    h2_metvsdijetbisectorphi[1][2]->Fill(jptjet12dphi/2,tcMET);
	    h2_metperpvsdijetbisectorphi[1][2]->Fill(jptjet12dphi/2,jptmetperp[2]);
	    h2_metparavsdijetbisectorphi[1][2]->Fill(jptjet12dphi/2,jptmetpara[2]);
	    h2_metdijetbisectordphivsdPt[1][2]->Fill(jptjet1jet2dPt,jptjet1metdphi[2]-(jptjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptjet1metdphi[2]-(jptjet12dphi/2));
	    h2_metperpvsjet12dphi[1][1]->Fill(jptjet12dphi,jptmetperp[1]);
	    h2_metparavsjet12dphi[1][1]->Fill(jptjet12dphi,jptmetpara[1]);
	    h2_metperpvsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptmetperp[2]);
	    h2_metparavsavgPt[1][2]->Fill(jptjet1jet2avgPt,jptmetpara[2]);
	    h2_metperpvspara[1][2]->Fill(jptmetpara[2],jptmetperp[2]);
	    h2_metperpvsmet[1][2]->Fill(tcMET,jptmetperp[2]);
	    h2_metparavsmet[1][2]->Fill(tcMET,jptmetpara[2]);
	    h2_j1metdphivsj2metdphi[1][2]->Fill(jptjet2metdphi[2],jptjet1metdphi[2]);
	  
	    //--- additional 1D histograms
	    bool jet1central = fabs(tmpJPTJetEta.at(0)) < 1.4;
	    bool jet2central = fabs(tmpJPTJetEta.at(1)) < 1.4;
	    bool jet1endm    = tmpJPTJetEta.at(0) <= -1.4;
	    bool jet1endp    = tmpJPTJetEta.at(0) >=  1.4;
	    bool jet2endm    = tmpJPTJetEta.at(1) <= -1.4;
	    bool jet2endp    = tmpJPTJetEta.at(1) >=  1.4;

	    if (jet1central && jet2central)
	      h_jet12dPtbothcentral[1]->Fill(jptjet1jet2dPt);
	    if ( (jet1central && (jet2endp || jet2endm)) ||
		 (jet2central && (jet1endp || jet1endm)))
	      h_jet12dPtcentralendcaps[1]->Fill(jptjet1jet2dPt);
	    if ( (jet1endp && jet2endp) || (jet1endm && jet2endm))
	      h_jet12dPtsameendcaps[1]->Fill(jptjet1jet2dPt);
	    if ( (jet1endp && jet2endm) || (jet1endm && jet2endp))
	      h_jet12dPtoppositeendcaps[1]->Fill(jptjet1jet2dPt);
	    
	    jptdijeteventnumbers.push_back(Event);
	    ++numdijetevents[1];
	  }
	}
    }
    

    //PF dijet events
    if (tmpPFNJets>1) {
      if ((fabs(tmpPFJetEt[0]) > cut_jet1et && fabs(tmpPFJetEta[0]) < cut_jet1eta ) &&
	  (fabs(tmpPFJetEt[1]) > cut_jet2et && fabs(tmpPFJetEta[1]) < cut_jet2eta ))
	{
	  pfjet1jet2dPt = tmpPFJetPt[1]-tmpPFJetPt[0];
	  pfjet12dphi   = helperFunctions::deltaPhi(tmpPFJetPhi[0],tmpPFJetPhi[1]);
      
	  if (fabs(pfjet12dphi) > cut_jet12dphi) {
	    
	    pfjet1jet2avgPt = (tmpPFJetPt[0]+tmpPFJetPt[1])/2;

	    pfjet12dR     = helperFunctions::deltaR(tmpPFJetEta[0],tmpPFJetPhi[0],tmpPFJetEta[1],tmpPFJetPhi[1]);

	    pfjet1metdphi[0] = helperFunctions::deltaPhi(tmpPFJetPhi[0],caloMETphi_Fullcorr_nocc);
	    pfjet2metdphi[0] = helperFunctions::deltaPhi(tmpPFJetPhi[1],caloMETphi_Fullcorr_nocc);
	    pfmetmhtdphi[0]  = helperFunctions::deltaPhi(caloMETphi_Fullcorr_nocc,tmpPFMHtphi);
	    pfmetperp[0]     = helperFunctions::perpComp(tmpPFJetPhi[0],tmpPFJetPhi[1],caloMETphi2)*caloMET;
	    pfmetpara[0]     = helperFunctions::paraComp(tmpPFJetPhi[0],tmpPFJetPhi[1],caloMETphi2)*caloMET;

	    pfjet1metdphi[1] = helperFunctions::deltaPhi(tmpPFJetPhi[0],pfMETphi_Fullcorr_nocc);
	    pfjet2metdphi[1] = helperFunctions::deltaPhi(tmpPFJetPhi[1],pfMETphi_Fullcorr_nocc);
	    pfmetmhtdphi[1]  = helperFunctions::deltaPhi(pfMETphi_Fullcorr_nocc,tmpPFMHtphi);
	    pfmetperp[1]     = helperFunctions::perpComp(tmpPFJetPhi[0],tmpPFJetPhi[1],pfMETphi2)*pfMET;
	    pfmetpara[1]     = helperFunctions::paraComp(tmpPFJetPhi[0],tmpPFJetPhi[1],pfMETphi2)*pfMET;

	    pfjet1metdphi[2] = helperFunctions::deltaPhi(tmpPFJetPhi[0],tcMETphi_Fullcorr_nocc);
	    pfjet2metdphi[2] = helperFunctions::deltaPhi(tmpPFJetPhi[1],tcMETphi_Fullcorr_nocc);
	    pfmetmhtdphi[2]  = helperFunctions::deltaPhi(tcMETphi_Fullcorr_nocc,tmpPFMHtphi);
	    pfmetperp[2]     = helperFunctions::perpComp(tmpPFJetPhi[0],tmpPFJetPhi[1],tcMETphi2)*tcMET;
	    pfmetpara[2]     = helperFunctions::paraComp(tmpPFJetPhi[0],tmpPFJetPhi[1],tcMETphi2)*tcMET;


	    h_jet12dPt[2]->Fill(pfjet1jet2dPt);
	    h_jet12avgPt[2]->Fill(pfjet1jet2avgPt);
	    h_jet12dphi[2]->Fill(pfjet12dphi);
	    h_jet12dR[2]->Fill(pfjet12dR);
	    //calo met
	    h_jet1metdphi[2][0]->Fill(pfjet1metdphi[0]);
	    h_jet2metdphi[2][0]->Fill(pfjet2metdphi[0]);
	    h_metmhtdphi[2][0]->Fill(pfmetmhtdphi[0]);
	    h_met[2][0]->Fill(caloMET);
	    h_metperp[2][0]->Fill(pfmetperp[0]);
	    h_metpara[2][0]->Fill(pfmetpara[0]);
	    //pf met
	    h_jet1metdphi[2][1]->Fill(pfjet1metdphi[1]);
	    h_jet2metdphi[2][1]->Fill(pfjet2metdphi[1]);
	    h_metmhtdphi[2][1]->Fill(pfmetmhtdphi[1]);
	    h_met[2][1]->Fill(pfMET);
	    h_metperp[2][1]->Fill(pfmetperp[1]);
	    h_metpara[2][1]->Fill(pfmetpara[1]);
	    //tc met
	    h_jet1metdphi[2][2]->Fill(pfjet1metdphi[2]);
	    h_jet2metdphi[2][2]->Fill(pfjet2metdphi[2]);
	    h_metmhtdphi[2][2]->Fill(pfmetmhtdphi[2]);
	    h_met[2][2]->Fill(tcMET);
	    h_metperp[2][2]->Fill(pfmetperp[2]);
	    h_metpara[2][2]->Fill(pfmetpara[2]);

	    //PF Jets
	    h2_jet12dPtvsavgPt[2]->Fill(pfjet1jet2avgPt,pfjet1jet2dPt);
	    h2_jet12dPtvsdphi[2]->Fill(pfjet12dphi,pfjet1jet2dPt);
	    h2_jet12dPtvsdR[2]->Fill(pfjet12dR,pfjet1jet2dPt);
	    h2_jet12dPtvsetaj1[2]->Fill(tmpPFJetEta.at(0),pfjet1jet2dPt);
	    h2_jet12dPtvsetaj2[2]->Fill(tmpPFJetEta.at(1),pfjet1jet2dPt);
	    h2_mhtvsdPt[2]->Fill(pfjet1jet2dPt,tmpPFMHt);
	    h2_mhtvsavgPt[2]->Fill(pfjet1jet2avgPt,tmpPFMHt);
	    //calo met
	    h2_jet1metdphivsdPt[2][0]->Fill(pfjet1jet2dPt,pfjet1metdphi[0]);
	    h2_jet2metdphivsdPt[2][0]->Fill(pfjet1jet2dPt,pfjet2metdphi[0]);
	    h2_jet1metdphivsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfjet1metdphi[0]);
	    h2_jet2metdphivsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfjet2metdphi[0]);
	    h2_jet1metdphivsdphi[2][0]->Fill(pfjet12dphi,pfjet1metdphi[0]);
	    h2_jet2metdphivsdphi[2][0]->Fill(pfjet12dphi,pfjet2metdphi[0]);
	    h2_metmhtdphivsdPt[2][0]->Fill(pfjet1jet2dPt,pfmetmhtdphi[0]);
	    h2_metmhtdphivsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfmetmhtdphi[0]);
	    h2_metvsdPt[2][0]->Fill(pfjet1jet2dPt,caloMET);
	    h2_metvsjet12dphi[2][0]->Fill(pfjet12dphi,caloMET);
	    h2_metvsavgPt[2][0]->Fill(pfjet1jet2avgPt,caloMET);
	    h2_metvsdijetbisectorphi[2][0]->Fill(pfjet12dphi/2,caloMET);
	    h2_metperpvsdijetbisectorphi[2][0]->Fill(pfjet12dphi/2,pfmetperp[0]);
	    h2_metparavsdijetbisectorphi[2][0]->Fill(pfjet12dphi/2,pfmetpara[0]);
	    h2_metdijetbisectordphivsdPt[2][0]->Fill(pfjet1jet2dPt,pfjet1metdphi[0]-(pfjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfjet1metdphi[0]-(pfjet12dphi/2));
	    h2_metperpvsjet12dphi[2][0]->Fill(pfjet12dphi,pfmetperp[0]);
	    h2_metparavsjet12dphi[2][0]->Fill(pfjet12dphi,pfmetpara[0]);
	    h2_metperpvsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfmetperp[0]);
	    h2_metparavsavgPt[2][0]->Fill(pfjet1jet2avgPt,pfmetpara[0]);
	    h2_metperpvspara[2][0]->Fill(pfmetpara[0],pfmetperp[0]);
	    h2_metperpvsmet[2][0]->Fill(caloMET,pfmetperp[0]);
	    h2_metparavsmet[2][0]->Fill(caloMET,pfmetpara[0]);
	    h2_j1metdphivsj2metdphi[2][0]->Fill(pfjet2metdphi[0],pfjet1metdphi[0]);
	    //pf met
	    h2_jet1metdphivsdPt[2][1]->Fill(pfjet1jet2dPt,pfjet1metdphi[1]);
	    h2_jet2metdphivsdPt[2][1]->Fill(pfjet1jet2dPt,pfjet2metdphi[1]);
	    h2_jet1metdphivsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfjet1metdphi[1]);
	    h2_jet2metdphivsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfjet2metdphi[1]);
	    h2_jet1metdphivsdphi[2][1]->Fill(pfjet12dphi,pfjet1metdphi[1]);
	    h2_jet2metdphivsdphi[2][1]->Fill(pfjet12dphi,pfjet2metdphi[1]);
	    h2_metmhtdphivsdPt[2][1]->Fill(pfjet1jet2dPt,pfmetmhtdphi[1]);
	    h2_metmhtdphivsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfmetmhtdphi[1]);
	    h2_metvsdPt[2][1]->Fill(pfjet1jet2dPt,pfMET);
	    h2_metvsjet12dphi[2][1]->Fill(pfjet12dphi,pfMET);
	    h2_metvsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfMET);
	    h2_metvsdijetbisectorphi[2][1]->Fill(pfjet12dphi/2,pfMET);
	    h2_metperpvsdijetbisectorphi[2][1]->Fill(pfjet12dphi/2,pfmetperp[1]);
	    h2_metparavsdijetbisectorphi[2][1]->Fill(pfjet12dphi/2,pfmetpara[1]);
	    h2_metdijetbisectordphivsdPt[2][1]->Fill(pfjet1jet2dPt,pfjet1metdphi[1]-(pfjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfjet1metdphi[1]-(pfjet12dphi/2));
	    h2_metperpvsjet12dphi[2][1]->Fill(pfjet12dphi,pfmetperp[1]);
	    h2_metparavsjet12dphi[2][1]->Fill(pfjet12dphi,pfmetpara[1]);
	    h2_metperpvsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfmetperp[1]);
	    h2_metparavsavgPt[2][1]->Fill(pfjet1jet2avgPt,pfmetpara[1]);
	    h2_metperpvspara[2][1]->Fill(pfmetpara[1],pfmetperp[1]);
	    h2_metperpvsmet[2][1]->Fill(pfMET,pfmetperp[1]);
	    h2_metparavsmet[2][1]->Fill(pfMET,pfmetpara[1]);
	    h2_j1metdphivsj2metdphi[2][1]->Fill(pfjet2metdphi[1],pfjet1metdphi[1]);
	    //tc met
	    h2_jet1metdphivsdPt[2][2]->Fill(pfjet1jet2dPt,pfjet1metdphi[2]);
	    h2_jet2metdphivsdPt[2][2]->Fill(pfjet1jet2dPt,pfjet2metdphi[2]);
	    h2_jet1metdphivsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfjet1metdphi[2]);
	    h2_jet2metdphivsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfjet2metdphi[2]);
	    h2_jet1metdphivsdphi[2][2]->Fill(pfjet12dphi,pfjet1metdphi[2]);
	    h2_jet2metdphivsdphi[2][2]->Fill(pfjet12dphi,pfjet2metdphi[2]);
	    h2_metmhtdphivsdPt[2][2]->Fill(pfjet1jet2dPt,pfmetmhtdphi[2]);
	    h2_metmhtdphivsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfmetmhtdphi[2]);
	    h2_metvsdPt[2][2]->Fill(pfjet1jet2dPt,tcMET);
	    h2_metvsjet12dphi[2][2]->Fill(pfjet12dphi,tcMET);
	    h2_metvsavgPt[2][2]->Fill(pfjet1jet2avgPt,tcMET);
	    h2_metvsdijetbisectorphi[2][2]->Fill(pfjet12dphi/2,tcMET);
	    h2_metperpvsdijetbisectorphi[2][2]->Fill(pfjet12dphi/2,pfmetperp[2]);
	    h2_metparavsdijetbisectorphi[2][2]->Fill(pfjet12dphi/2,pfmetpara[2]);
	    h2_metdijetbisectordphivsdPt[2][2]->Fill(pfjet1jet2dPt,pfjet1metdphi[2]-(pfjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfjet1metdphi[2]-(pfjet12dphi/2));
	    h2_metperpvsjet12dphi[2][1]->Fill(pfjet12dphi,pfmetperp[1]);
	    h2_metparavsjet12dphi[2][1]->Fill(pfjet12dphi,pfmetpara[1]);
	    h2_metperpvsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfmetperp[2]);
	    h2_metparavsavgPt[2][2]->Fill(pfjet1jet2avgPt,pfmetpara[2]);
	    h2_metperpvspara[2][2]->Fill(pfmetpara[2],pfmetperp[2]);
	    h2_metperpvsmet[2][2]->Fill(tcMET,pfmetperp[2]);
	    h2_metparavsmet[2][2]->Fill(tcMET,pfmetpara[2]);
	    h2_j1metdphivsj2metdphi[2][2]->Fill(pfjet2metdphi[2],pfjet1metdphi[2]);
	  
	    //--- additional 1D histograms
	    bool jet1central = fabs(tmpPFJetEta.at(0)) < 1.4;
	    bool jet2central = fabs(tmpPFJetEta.at(1)) < 1.4;
	    bool jet1endm    = tmpPFJetEta.at(0) <= -1.4;
	    bool jet1endp    = tmpPFJetEta.at(0) >=  1.4;
	    bool jet2endm    = tmpPFJetEta.at(1) <= -1.4;
	    bool jet2endp    = tmpPFJetEta.at(1) >=  1.4;

	    if (jet1central && jet2central)
	      h_jet12dPtbothcentral[2]->Fill(pfjet1jet2dPt);
	    if ( (jet1central && (jet2endp || jet2endm)) ||
		 (jet2central && (jet1endp || jet1endm)))
	      h_jet12dPtcentralendcaps[2]->Fill(pfjet1jet2dPt);
	    if ( (jet1endp && jet2endp) || (jet1endm && jet2endm))
	      h_jet12dPtsameendcaps[2]->Fill(pfjet1jet2dPt);
	    if ( (jet1endp && jet2endm) || (jet1endm && jet2endp))
	      h_jet12dPtoppositeendcaps[2]->Fill(pfjet1jet2dPt);
	    
	    pfdijeteventnumbers.push_back(Event);
	    ++numdijetevents[2];
	  }
	}
    }
    
    //Track dijet events
    if (tmpTrackNJets>1) {
      if ((fabs(tmpTrackJetEt[0]) > cut_jet1et && fabs(tmpTrackJetEta[0]) < cut_jet1eta ) &&
	  (fabs(tmpTrackJetEt[1]) > cut_jet2et && fabs(tmpTrackJetEta[1]) < cut_jet2eta ))
	{
	  trackjet1jet2dPt = tmpTrackJetPt[1]-tmpTrackJetPt[0];
	  trackjet12dphi   = helperFunctions::deltaPhi(tmpTrackJetPhi[0],tmpTrackJetPhi[1]);

      	  if (fabs(trackjet12dphi) > cut_jet12dphi) {

	    trackjet1jet2avgPt = (tmpTrackJetPt[0]+tmpTrackJetPt[1])/2;

	    trackjet12dR     = helperFunctions::deltaR(tmpTrackJetEta[0],tmpTrackJetPhi[0],tmpTrackJetEta[1],tmpTrackJetPhi[1]);

	    trackjet1metdphi[0] = helperFunctions::deltaPhi(tmpTrackJetPhi[0],caloMETphi_Fullcorr_nocc);
	    trackjet2metdphi[0] = helperFunctions::deltaPhi(tmpTrackJetPhi[1],caloMETphi_Fullcorr_nocc);
	    trackmetmhtdphi[0]       = helperFunctions::deltaPhi(caloMETphi_Fullcorr_nocc,tmpTrackMHtphi);
	    trackmetperp[0]          = helperFunctions::perpComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],caloMETphi2)*caloMET;
	    trackmetpara[0]          = helperFunctions::paraComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],caloMETphi2)*caloMET;

	    trackjet1metdphi[1] = helperFunctions::deltaPhi(tmpTrackJetPhi[0],pfMETphi_Fullcorr_nocc);
	    trackjet2metdphi[1] = helperFunctions::deltaPhi(tmpTrackJetPhi[1],pfMETphi_Fullcorr_nocc);
	    trackmetmhtdphi[1]       = helperFunctions::deltaPhi(pfMETphi_Fullcorr_nocc,tmpTrackMHtphi);
	    trackmetperp[1]          = helperFunctions::perpComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],pfMETphi2)*pfMET;
	    trackmetpara[1]          = helperFunctions::paraComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],pfMETphi2)*pfMET;

	    trackjet1metdphi[2] = helperFunctions::deltaPhi(tmpTrackJetPhi[0],tcMETphi_Fullcorr_nocc);
	    trackjet2metdphi[2] = helperFunctions::deltaPhi(tmpTrackJetPhi[1],tcMETphi_Fullcorr_nocc);
	    trackmetmhtdphi[2]       = helperFunctions::deltaPhi(tcMETphi_Fullcorr_nocc,tmpTrackMHtphi);
	    trackmetperp[2]          = helperFunctions::perpComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],tcMETphi2)*tcMET;
	    trackmetpara[2]          = helperFunctions::paraComp(tmpTrackJetPhi[0],tmpTrackJetPhi[1],tcMETphi2)*tcMET;


	    h_jet12dPt[3]->Fill(trackjet1jet2dPt);
	    h_jet12avgPt[3]->Fill(trackjet1jet2avgPt);
	    h_jet12dphi[3]->Fill(trackjet12dphi);
	    h_jet12dR[3]->Fill(trackjet12dR);
	    //calo met
	    h_jet1metdphi[3][0]->Fill(trackjet1metdphi[0]);
	    h_jet2metdphi[3][0]->Fill(trackjet2metdphi[0]);
	    h_metmhtdphi[3][0]->Fill(trackmetmhtdphi[0]);
	    h_met[3][0]->Fill(caloMET);
	    h_metperp[3][0]->Fill(trackmetperp[0]);
	    h_metpara[3][0]->Fill(trackmetpara[0]);
	    //pf met
	    h_jet1metdphi[3][1]->Fill(trackjet1metdphi[1]);
	    h_jet2metdphi[3][1]->Fill(trackjet2metdphi[1]);
	    h_metmhtdphi[3][1]->Fill(trackmetmhtdphi[1]);
	    h_met[3][1]->Fill(pfMET);
	    h_metperp[3][1]->Fill(trackmetperp[1]);
	    h_metpara[3][1]->Fill(trackmetpara[1]);
	    //tc met
	    h_jet1metdphi[3][2]->Fill(trackjet1metdphi[2]);
	    h_jet2metdphi[3][2]->Fill(trackjet2metdphi[2]);
	    h_metmhtdphi[3][2]->Fill(trackmetmhtdphi[2]);
	    h_met[3][2]->Fill(tcMET);
	    h_metperp[3][2]->Fill(trackmetperp[2]);
	    h_metpara[3][2]->Fill(trackmetpara[2]);

	    //Track Jets
	    h2_jet12dPtvsavgPt[3]->Fill(trackjet1jet2avgPt,trackjet1jet2dPt);
	    h2_jet12dPtvsdphi[3]->Fill(trackjet12dphi,trackjet1jet2dPt);
	    h2_jet12dPtvsdR[3]->Fill(trackjet12dR,trackjet1jet2dPt);
	    h2_jet12dPtvsetaj1[3]->Fill(tmpTrackJetEta.at(0),trackjet1jet2dPt);
	    h2_jet12dPtvsetaj2[3]->Fill(tmpTrackJetEta.at(1),trackjet1jet2dPt);
	    h2_mhtvsdPt[3]->Fill(trackjet1jet2dPt,tmpTrackMHt);
	    h2_mhtvsavgPt[3]->Fill(trackjet1jet2avgPt,tmpTrackMHt);
	    //calo met
	    h2_jet1metdphivsdPt[3][0]->Fill(trackjet1jet2dPt,trackjet1metdphi[0]);
	    h2_jet2metdphivsdPt[3][0]->Fill(trackjet1jet2dPt,trackjet2metdphi[0]);
	    h2_jet1metdphivsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackjet1metdphi[0]);
	    h2_jet2metdphivsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackjet2metdphi[0]);
	    h2_jet1metdphivsdphi[3][0]->Fill(trackjet12dphi,trackjet1metdphi[0]);
	    h2_jet2metdphivsdphi[3][0]->Fill(trackjet12dphi,trackjet2metdphi[0]);
	    h2_metmhtdphivsdPt[3][0]->Fill(trackjet1jet2dPt,trackmetmhtdphi[0]);
	    h2_metmhtdphivsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackmetmhtdphi[0]);
	    h2_metvsdPt[3][0]->Fill(trackjet1jet2dPt,caloMET);
	    h2_metvsjet12dphi[3][0]->Fill(trackjet12dphi,caloMET);
	    h2_metvsavgPt[3][0]->Fill(trackjet1jet2avgPt,caloMET);
	    h2_metvsdijetbisectorphi[3][0]->Fill(trackjet12dphi/2,caloMET);
	    h2_metperpvsdijetbisectorphi[3][0]->Fill(trackjet12dphi/2,trackmetperp[0]);
	    h2_metparavsdijetbisectorphi[3][0]->Fill(trackjet12dphi/2,trackmetpara[0]);
	    h2_metdijetbisectordphivsdPt[3][0]->Fill(trackjet1jet2dPt,trackjet1metdphi[0]-(trackjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackjet1metdphi[0]-(trackjet12dphi/2));
	    h2_metperpvsjet12dphi[3][0]->Fill(trackjet12dphi,trackmetperp[0]);
	    h2_metparavsjet12dphi[3][0]->Fill(trackjet12dphi,trackmetpara[0]);
	    h2_metperpvsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackmetperp[0]);
	    h2_metparavsavgPt[3][0]->Fill(trackjet1jet2avgPt,trackmetpara[0]);
	    h2_metperpvspara[3][0]->Fill(trackmetpara[0],trackmetperp[0]);
	    h2_metperpvsmet[3][0]->Fill(caloMET,trackmetperp[0]);
	    h2_metparavsmet[3][0]->Fill(caloMET,trackmetpara[0]);
	    h2_j1metdphivsj2metdphi[3][0]->Fill(trackjet2metdphi[0],trackjet1metdphi[0]);
	    //pf met
	    h2_jet1metdphivsdPt[3][1]->Fill(trackjet1jet2dPt,trackjet1metdphi[1]);
	    h2_jet2metdphivsdPt[3][1]->Fill(trackjet1jet2dPt,trackjet2metdphi[1]);
	    h2_jet1metdphivsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackjet1metdphi[1]);
	    h2_jet2metdphivsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackjet2metdphi[1]);
	    h2_jet1metdphivsdphi[3][1]->Fill(trackjet12dphi,trackjet1metdphi[1]);
	    h2_jet2metdphivsdphi[3][1]->Fill(trackjet12dphi,trackjet2metdphi[1]);
	    h2_metmhtdphivsdPt[3][1]->Fill(trackjet1jet2dPt,trackmetmhtdphi[1]);
	    h2_metmhtdphivsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackmetmhtdphi[1]);
	    h2_metvsdPt[3][1]->Fill(trackjet1jet2dPt,pfMET);
	    h2_metvsjet12dphi[3][1]->Fill(trackjet12dphi,pfMET);
	    h2_metvsavgPt[3][1]->Fill(trackjet1jet2avgPt,pfMET);
	    h2_metvsdijetbisectorphi[3][1]->Fill(trackjet12dphi/2,pfMET);
	    h2_metperpvsdijetbisectorphi[3][1]->Fill(trackjet12dphi/2,trackmetperp[1]);
	    h2_metparavsdijetbisectorphi[3][1]->Fill(trackjet12dphi/2,trackmetpara[1]);
	    h2_metdijetbisectordphivsdPt[3][1]->Fill(trackjet1jet2dPt,trackjet1metdphi[1]-(trackjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackjet1metdphi[1]-(trackjet12dphi/2));
	    h2_metperpvsjet12dphi[3][1]->Fill(trackjet12dphi,trackmetperp[1]);
	    h2_metparavsjet12dphi[3][1]->Fill(trackjet12dphi,trackmetpara[1]);
	    h2_metperpvsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackmetperp[1]);
	    h2_metparavsavgPt[3][1]->Fill(trackjet1jet2avgPt,trackmetpara[1]);
	    h2_metperpvspara[3][1]->Fill(trackmetpara[1],trackmetperp[1]);
	    h2_metperpvsmet[3][1]->Fill(pfMET,trackmetperp[1]);
	    h2_metparavsmet[3][1]->Fill(pfMET,trackmetpara[1]);
	    h2_j1metdphivsj2metdphi[3][1]->Fill(trackjet2metdphi[1],trackjet1metdphi[1]);
	    //tc met
	    h2_jet1metdphivsdPt[3][2]->Fill(trackjet1jet2dPt,trackjet1metdphi[2]);
	    h2_jet2metdphivsdPt[3][2]->Fill(trackjet1jet2dPt,trackjet2metdphi[2]);
	    h2_jet1metdphivsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackjet1metdphi[2]);
	    h2_jet2metdphivsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackjet2metdphi[2]);
	    h2_jet1metdphivsdphi[3][2]->Fill(trackjet12dphi,trackjet1metdphi[2]);
	    h2_jet2metdphivsdphi[3][2]->Fill(trackjet12dphi,trackjet2metdphi[2]);
	    h2_metmhtdphivsdPt[3][2]->Fill(trackjet1jet2dPt,trackmetmhtdphi[2]);
	    h2_metmhtdphivsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackmetmhtdphi[2]);
	    h2_metvsdPt[3][2]->Fill(trackjet1jet2dPt,tcMET);
	    h2_metvsjet12dphi[3][2]->Fill(trackjet12dphi,tcMET);
	    h2_metvsavgPt[3][2]->Fill(trackjet1jet2avgPt,tcMET);
	    h2_metvsdijetbisectorphi[3][2]->Fill(trackjet12dphi/2,tcMET);
	    h2_metperpvsdijetbisectorphi[3][2]->Fill(trackjet12dphi/2,trackmetperp[2]);
	    h2_metparavsdijetbisectorphi[3][2]->Fill(trackjet12dphi/2,trackmetpara[2]);
	    h2_metdijetbisectordphivsdPt[3][2]->Fill(trackjet1jet2dPt,trackjet1metdphi[2]-(trackjet12dphi/2));
	    h2_metdijetbisectordphivsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackjet1metdphi[2]-(trackjet12dphi/2));
	    h2_metperpvsjet12dphi[3][1]->Fill(trackjet12dphi,trackmetperp[1]);
	    h2_metparavsjet12dphi[3][1]->Fill(trackjet12dphi,trackmetpara[1]);
	    h2_metperpvsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackmetperp[2]);
	    h2_metparavsavgPt[3][2]->Fill(trackjet1jet2avgPt,trackmetpara[2]);
	    h2_metperpvspara[3][2]->Fill(trackmetpara[2],trackmetperp[2]);
	    h2_metperpvsmet[3][2]->Fill(tcMET,trackmetperp[2]);
	    h2_metparavsmet[3][2]->Fill(tcMET,trackmetpara[2]);
	    h2_j1metdphivsj2metdphi[3][2]->Fill(trackjet2metdphi[2],trackjet1metdphi[2]);
	  
	    //--- additional 1D histograms
	    bool jet1central = fabs(tmpTrackJetEta.at(0)) < 1.4;
	    bool jet2central = fabs(tmpTrackJetEta.at(1)) < 1.4;
	    bool jet1endm    = tmpTrackJetEta.at(0) <= -1.4;
	    bool jet1endp    = tmpTrackJetEta.at(0) >=  1.4;
	    bool jet2endm    = tmpTrackJetEta.at(1) <= -1.4;
	    bool jet2endp    = tmpTrackJetEta.at(1) >=  1.4;

	    if (jet1central && jet2central)
	      h_jet12dPtbothcentral[3]->Fill(trackjet1jet2dPt);
	    if ( (jet1central && (jet2endp || jet2endm)) ||
		 (jet2central && (jet1endp || jet1endm)))
	      h_jet12dPtcentralendcaps[3]->Fill(trackjet1jet2dPt);
	    if ( (jet1endp && jet2endp) || (jet1endm && jet2endm))
	      h_jet12dPtsameendcaps[3]->Fill(trackjet1jet2dPt);
	    if ( (jet1endp && jet2endm) || (jet1endm && jet2endp))
	      h_jet12dPtoppositeendcaps[3]->Fill(trackjet1jet2dPt);
	    
	    
	    trackdijeteventnumbers.push_back(Event);
	    ++numdijetevents[3];
	  }
	}
    }
    */
  }
  int Nevents = nentries;
  std::cout<<"Number of pure calo dijet events/total: "<<numdijetevents[0]<<"/"<<Nevents<<" = "<<static_cast<double>(numdijetevents[0])/static_cast<double>(Nevents)*100<<"%"<<std::endl;
  /*
  std::cout<<"Number of pure jpt dijet events/total: "<<numdijetevents[1]<<"/"<<Nevents<<" = "<<static_cast<double>(numdijetevents[1])/static_cast<double>(Nevents)*100<<"%"<<std::endl;
  std::cout<<"Number of pure pf dijet events/total: "<<numdijetevents[2]<<"/"<<Nevents<<" = "<<static_cast<double>(numdijetevents[2])/static_cast<double>(Nevents)*100<<"%"<<std::endl;
  std::cout<<"Number of pure track dijet events/total: "<<numdijetevents[3]<<"/"<<Nevents<<" = "<<static_cast<double>(numdijetevents[3])/static_cast<double>(Nevents)*100<<"%"<<std::endl;
  */
  //---------------------------------------------------------
  //Write out root file with histograms
  //---------------------------------------------------------

  file->cd();
  file->Write();
  
}

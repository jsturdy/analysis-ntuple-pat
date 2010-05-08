void analyzeFirstData()
{
  
  static const double localpi = 3.1415926535897532384626;
  static const int NJETALGS   = 4;
  static const int NMETALGS   = 3;
  static const int NBINS      = 10;
  static const int NUMFILES   = 2;
  //Profile histograms
  TProfile* p_dPtvsdijetPt[NJETALGS];
  TProfile* p_dijetPtvsdphi[NJETALGS];
  TProfile* p_dijetPtvsdR[NJETALGS];

  TCanvas* c_met[2][NJETALGS];
  TCanvas* c_metperp[2][NJETALGS];
  TCanvas* c_metpara[2][NJETALGS];
  //TCanvas* c_metpara[2];
  //TCanvas* c_metpara[2];
  //TCanvas* c_metpara[2];

  TFile* file[2];
  std::cout<<"Getting files"<<std::endl;
  file[0] = new TFile("./7TeVCollisionData_v7_out.root");
  file[1] = new TFile("./7TeVMinBiasMC_out.root");

  std::cout<<"Setting up canvasses"<<std::endl;
  c_met[0][0]     = new TCanvas("Calo MET Distributions","metcalodist",800,800);
  c_met[1][0]     = new TCanvas("Calo MET Profiles","metcalodist",800,800);
  c_metperp[0][0] = new TCanvas("Calo MET perp Distributions","metcalodist",800,800);
  c_metperp[1][0] = new TCanvas("Calo MET perp Profiles","metcalodist",800,800);
  c_metpara[0][0] = new TCanvas("Calo MET para Distributions","metcalodist",800,800);
  c_metpara[1][0] = new TCanvas("Calo MET para Profiles","metcalodist",800,800);

  c_met[0][1]     = new TCanvas("JPT MET Distributions","metjptdist",800,800);
  c_met[1][1]     = new TCanvas("JPT MET Profiles","metjptdist",800,800);
  c_metperp[0][1] = new TCanvas("JPT MET perp Distributions","metjptdist",800,800);
  c_metperp[1][1] = new TCanvas("JPT MET perp Profiles","metjptdist",800,800);
  c_metpara[0][1] = new TCanvas("JPT MET para Distributions","metjptdist",800,800);
  c_metpara[1][1] = new TCanvas("JPT MET para Profiles","metjptdist",800,800);

  c_met[0][2]     = new TCanvas("PF MET Distributions","metpfdist",800,800);
  c_met[1][2]     = new TCanvas("PF MET Profiles","metpfdist",800,800);
  c_metperp[0][2] = new TCanvas("PF MET perp Distributions","metpfdist",800,800);
  c_metperp[1][2] = new TCanvas("PF MET perp Profiles","metpfdist",800,800);
  c_metpara[0][2] = new TCanvas("PF MET para Distributions","metpfdist",800,800);
  c_metpara[1][2] = new TCanvas("PF MET para Profiles","metpfdist",800,800);

  c_met[0][3]     = new TCanvas("Track MET Distributions","mettrackdist",800,800);
  c_met[1][3]     = new TCanvas("Track MET Profiles","mettrackdist",800,800);
  c_metperp[0][3] = new TCanvas("Track MET perp Distributions","mettrackdist",800,800);
  c_metperp[1][3] = new TCanvas("Track MET perp Profiles","mettrackdist",800,800);
  c_metpara[0][3] = new TCanvas("Track MET para Distributions","mettrackdist",800,800);
  c_metpara[1][3] = new TCanvas("Track MET para Profiles","mettrackdist",800,800);
  
  for (int pad = 0; pad < 2; ++pad) {
    for (int pad2 = 0; pad2 < NJETALGS; ++pad2) {
      std::cout<<"Dividing met canvasses"<<std::endl;
      c_met[pad][pad2]->cd();
      c_met[pad][pad2]->Divide(2,2);
      c_metperp[pad][pad2]->cd();
      c_metperp[pad][pad2]->Divide(2,2);
      c_metpara[pad][pad2]->cd();
      c_metpara[pad][pad2]->Divide(2,2);
    }
  }
  //rebin dijet Pt into 12 bins from 10 to 40

  // MET Plots
  TProfile* p_metvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TProfile* p_metvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metmeanvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metmeanvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metrmsvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metrmsvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1F*     h_met_lo_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt < 25 GeV
  TH1F*     h_met_med_dijetPt[NUMFILES][NJETALGS][NMETALGS];//25 GeV < dijetPt < 50 GeV
  TH1F*     h_met_hi_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt > 50 GeV
  //MET perp projection plots
  TProfile* p_metperpvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TProfile* p_metperpvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metperpmeanvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metperpmeanvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metperprmsvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metperprmsvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1F*     h_metperpperp_lo_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt < 25 GeV
  TH1F*     h_metperp_med_dijetPt[NUMFILES][NJETALGS][NMETALGS];//25 GeV < dijetPt < 50 GeV
  TH1F*     h_metperp_hi_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt > 50 GeV

  //MET perp projection plots
  TProfile* p_metparavsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TProfile* p_metparavsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metparameanvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metparameanvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metpararmsvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH1D*     p_metpararmsvsdphi[NUMFILES][NJETALGS][NMETALGS];
  TH1F*     h_metpara_lo_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt < 25 GeV
  TH1F*     h_metpara_med_dijetPt[NUMFILES][NJETALGS][NMETALGS];//25 GeV < dijetPt < 50 GeV
  TH1F*     h_metpara_hi_dijetPt[NUMFILES][NJETALGS][NMETALGS]; //dijetPt > 50 GeV
  
  
  //Plotted distributions
  UInt_t markerstyle[NUMFILES];
  Color_t metcolor[NMETALGS];
  Color_t jetcolor[NJETALGS];

  markerstyle[0] = 2;
  markerstyle[1] = 4;

  metcolor[0] = kYellow;
  metcolor[1] = kBlue;
  metcolor[2] = kRed;

  jetcolor[0] = kYellow;
  jetcolor[1] = kOrange;
  jetcolor[2] = kBlue;
  jetcolor[3] = kRed;

  std::string jetname[4]       = {"CaloJets", "JPTJets","PFJets","TrackJets"};
  std::string metname[3]       = {"CaloMET", "PFMET","TCMET"};
  std::string jettype[4]       = {"calo", "jpt","pf","track"};
  std::string mettype[3]       = {"calo", "pf","tc"};

  TH2* h2_dPtvsdijetPt[NUMFILES][NJETALGS];
  TH2* h2_dPtvsjet12dphi[NUMFILES][NJETALGS];
  TH2* h2_metvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_metvsjet12dphi[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_metperpvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_metperpvsjet12dphi[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_metparavsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_metparavsjet12dphi[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_jet1metdphivsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_jet1metdphivsjet12dphi[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_jet2metdphivsdijetPt[NUMFILES][NJETALGS][NMETALGS];
  TH2* h2_jet2metdphivsjet12dphi[NUMFILES][NJETALGS][NMETALGS];

  char histname[512];
  char histtitle[512];

  double scale[NUMFILES] = {0.};
  double plotintegral[NUMFILES] = {0.};
  std::cout<<"Getting histograms"<<std::endl;

  for (int fi = 0; fi < NUMFILES; ++fi) {

    std::cout<<"File:"<<fi<<std::endl;
    plotintegral[fi] = ((TH1F*)file[fi]->Get("h_calojet12avgPt"))->Integral(-1,501);

    for (int ja = 0; ja < NJETALGS-3; ++ja) {
      std::cout<<"Jet algorithm:"<<ja<<std::endl;
      sprintf(histname,"h2_%sjet12dPtvsavgPt",jettype[ja].c_str());
      sprintf(histtitle,"%sjet12dPtvsavgPt",jettype[ja].c_str());
      h2_dPtvsdijetPt[fi][ja] = ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      sprintf(histname,"h2_%sjet12dPtvsdphi",jettype[ja].c_str());
      sprintf(histtitle,"%sjet12dPtvsdphi",jettype[ja].c_str());
      h2_dPtvsjet12dphi[fi][ja] =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      
      for (int ma = 0; ma < NMETALGS; ++ma) {
      	//std::cout<<"MET algorithm:"<<ma<<std::endl;
      	//sprintf(histname,"h2_%smetvs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//sprintf(histtitle,"%smetvs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_metvsdPt[fi][ja][ma]               =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetvs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetvs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metvsdijetPt[fi][ja][ma]           =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetvs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetvs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metvsjet12dphi[fi][ja][ma]         =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%smetperpvs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//sprintf(histtitle,"%smetperpvs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_metperpvsdPt[fi][ja][ma]           =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetperpvs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetperpvs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metperpvsdijetPt[fi][ja][ma]       =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetperpvs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetperpvs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metperpvsjet12dphi[fi][ja][ma]     =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%smetparavs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//sprintf(histtitle,"%smetparavs%sdPt",mettype[ma].c_str(),jettype[ja].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_metparavsdPt[fi][ja][ma]           =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetparavs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetparavs%savgPt",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metparavsdijetPt[fi][ja][ma]       =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	sprintf(histname,"h2_%smetparavs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	sprintf(histtitle,"%smetparavs%sjet12dphi",mettype[ma].c_str(),jettype[ja].c_str());
      	std::cout<<"Getting histogram named "<<histname<<std::endl;
      	h2_metparavsjet12dphi[fi][ja][ma]     =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet1%smetdphivsdPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet1%smetdphivsdPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet1metdphivsdPt[fi][ja][ma]       =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet1%smetdphivsavgPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet1%smetdphivsavgPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet1metdphivsdijetPt[fi][ja][ma]   =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet1%smetdphivsjet12dphi",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet1%smetdphivsjet12dphi",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet1metdphivsjet12dphi[fi][ja][ma] =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet2%smetdphivsdPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet2%smetdphivsdPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet2metdphivsdPt[fi][ja][ma]       =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet2%smetdphivsavgPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet2%smetdphivsavgPt",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet2metdphivsdijetPt[fi][ja][ma]   =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      	//sprintf(histname,"h2_%sjet2%smetdphivsjet12dphi",jettype[ja].c_str(),mettype[ma].c_str());
      	//sprintf(histtitle,"%sjet2%smetdphivsjet12dphi",jettype[ja].c_str(),mettype[ma].c_str());
      	//std::cout<<"Getting histogram named "<<histname<<std::endl;
      	//h2_jet2metdphivsjet12dphi[fi][ja][ma] =  ((TH2*)file[fi]->Get(histname))->Rebin2D(500/NBINS,10,histtitle);
      }
    }
  }

  std::cout<<"Setting scale"<<std::endl;
  scale[0] = 1.;
  scale[1] = plotintegral[1]/plotintegral[0];

  //Slices of 2D histograms
  //jet plots
  TH1D* s_dPtvsjet12dphi[NUMFILES][NJETALGS][NBINS];
  TH1D* s_dPtvsdijetPt[NUMFILES][NJETALGS][NBINS];
  //  TH1D* s_jet12dphivsdPt[NUMFILES][NJETALGS][NBINS];
  //  TH1D* s_jet12dphivsdijetPt[NUMFILES][NJETALGS][NBINS];

  //met plots
  /*
  TH1D* s_metvsdijetPt[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_metvsjet12dphi[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_metperpdijetPt[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_metperpjet12dphi[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_metparadijetPt[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_metparajet12dphi[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_jet1metdphidijetPt[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_jet1metdphijet12dphi[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_jet2metdphidijetPt[NUMFILES][NJETALGS][NMETALGS][NBINS];
  TH1D* s_jet2metdphijet12dphi[NUMFILES][NJETALGS][NMETALGS][NBINS];
  */
  int lowbin[13][NBINS]     = {0};
  int highbin[13][NBINS]    = {0};
  double lowval[13][NBINS]  = {0.};
  double highval[13][NBINS] = {0.};

  int step = 500/NBINS;
  double hist_min[13] = {0.};
  double hist_max[13] = {0.};
  //  = th2fhist[hi]->GetXaxis()->GetXmax();;
  double hist_step[13] = {0.};
  //= (hist_max - hist_min)/NBINS;
  hist_min[0]  = h2_dPtvsdijetPt[0][0]->GetXaxis()->GetXmin();
  hist_max[0]  = h2_dPtvsdijetPt[0][0]->GetXaxis()->GetXmax();
  hist_min[1]  = h2_dPtvsjet12dphi[0][0]->GetXaxis()->GetXmin();
  hist_max[1]  = h2_dPtvsjet12dphi[0][0]->GetXaxis()->GetXmax();
  //  hist_min[2]  = h2_jet12dphivsdijetPt[0][0]->GetXaxis()->GetXmin();
  //  hist_max[2]  = h2_jet12dphivsdijetPt[0][0]->GetXaxis()->GetXmax();
  
  hist_min[3]  = h2_metvsdijetPt[0][0][0]->GetXaxis()->GetXmin();
  hist_max[3]  = h2_metvsdijetPt[0][0][0]->GetXaxis()->GetXmax();
  hist_min[4]  = h2_metvsjet12dphi[0][0][0]->GetXaxis()->GetXmin();
  hist_max[4]  = h2_metvsjet12dphi[0][0][0]->GetXaxis()->GetXmax();
  hist_min[5]  = h2_metperpvsdijetPt[0][0][0]->GetXaxis()->GetXmin();
  hist_max[5]  = h2_metperpvsdijetPt[0][0][0]->GetXaxis()->GetXmax();
  hist_min[6]  = h2_metperpvsjet12dphi[0][0][0]->GetXaxis()->GetXmin();
  hist_max[6]  = h2_metperpvsjet12dphi[0][0][0]->GetXaxis()->GetXmax();
  hist_min[7]  = h2_metparavsdijetPt[0][0][0]->GetXaxis()->GetXmin();
  hist_max[7]  = h2_metparavsdijetPt[0][0][0]->GetXaxis()->GetXmax();
  hist_min[8]  = h2_metparavsjet12dphi[0][0][0]->GetXaxis()->GetXmin();
  hist_max[8]  = h2_metparavsjet12dphi[0][0][0]->GetXaxis()->GetXmax();
  //hist_min[9]  = h2_jet1metdphivsdijetPt[0][0][0]->GetXaxis()->GetXmin();
  //hist_max[9]  = h2_jet1metdphivsdijetPt[0][0][0]->GetXaxis()->GetXmax();
  //hist_min[10] = h2_jet1metdphivsjet12dphi[0][0][0]->GetXaxis()->GetXmin();
  //hist_max[10] = h2_jet1metdphivsjet12dphi[0][0][0]->GetXaxis()->GetXmax();
  //hist_min[11] = h2_jet2metdphivsdijetPt[0][0][0]->GetXaxis()->GetXmin();
  //hist_max[11] = h2_jet2metdphivsdijetPt[0][0][0]->GetXaxis()->GetXmax();
  //hist_min[12] = h2_jet2metdphivsjet12dphi[0][0][0]->GetXaxis()->GetXmin();
  //hist_max[12] = h2_jet2metdphivsjet12dphi[0][0][0]->GetXaxis()->GetXmax();
  
  std::cout<<"setting up binning for projections"<<std::endl;

  for (int hist = 0; hist < 13; ++hist ) {
    hist_step[hist]  = (hist_max[hist] - hist_min[hist])/NBINS;
    
    for (int st = 0; st < NBINS; ++st) {
      lowbin[hist][st]  = st*step+1;
      highbin[hist][st] = (st+1)*step+1;
      lowval[hist][st]  = hist_min[hist] + st*hist_step[hist];
      highval[hist][st] = hist_min[hist] + (st+1)*hist_step[hist];
    }
  }
  
  for (int fi = 0; fi < NUMFILES; ++fi) {
    for (int ja = 0; ja < NJETALGS-3; ++ja) {
      for (int bin = 0; bin < NBINS; ++bin) {

	sprintf(histname,"%sdptvsdijetpt%dto%d",jettype[ja].c_str(),(int)lowval[0][bin],(int)highval[0][bin]);
	s_dPtvsdijetPt[fi][ja][bin]         = h2_dPtvsdijetPt[fi][ja]->ProjectionY(histname,lowbin[0][bin],highbin[0][bin]-1,"e");
	sprintf(histname,"%sdptvsjet12dphi%dto%d",jettype[ja].c_str(),(int)lowval[0][bin],(int)highval[0][bin]);
	s_dPtvsjet12dphi[fi][ja][bin]       = h2_dPtvsjet12dphi[fi][ja]->ProjectionY(histname,lowbin[0][bin],highbin[0][bin]-1,"e");
	//sprintf(histname,"%sdptvsdijetdphi%dto%d",jettype[ja].c_str(),(int)lowval[1][bin],(int)highval[1][bin]);
	//std::cout<<"getting plot: "<<histname<<" for bin "<<lowbin[1][bin]<<" or high "<<highbin[1][bin]-1<<std::endl;
	//s_dijetPt[fi][ja][bin]     = h2_dPtvsjet12dphi[fi][ja]->ProjectionY(histname,lowbin[1][bin],highbin[1][bin]-1,"e");
	//sprintf(histname,"%sdijetdphivsdijetpt%dto%d",jettype[ja].c_str(),(int)lowval[2][bin],(int)highval[2][bin]);
	//s_jet12dphi[fi][ja][bin]   = h2_jet12dphivsdijetPt[fi][ja]->ProjectionY(histname,lowbin[2][bin],highbin[2][bin]-1,"e");
      }

      
      std::cout<<"setting up met plots for projections"<<std::endl;
      for (int ma = 0; ma < NMETALGS; ++ma) {

	sprintf(histname,"%smetmeanvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s Mean vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metmeanvsdijetPt[fi][ja][ma]     = new TH1D(histname,histtitle,NBINS,hist_min[3],hist_max[3]);
	sprintf(histname,"%smetrmsvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s RMS vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metrmsvsdijetPt[fi][ja][ma]      = new TH1D(histname,histtitle,NBINS,hist_min[3],hist_max[3]);
	sprintf(histname,"%smetperpmeanvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s Perpendicular Mean vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metperpmeanvsdijetPt[fi][ja][ma] = new TH1D(histname,histtitle,NBINS,hist_min[5],hist_max[5]);
	sprintf(histname,"%smetperprmsvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s Perpendicular RMS vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metperprmsvsdijetPt[fi][ja][ma]  = new TH1D(histname,histtitle,NBINS,hist_min[5],hist_max[5]);
	sprintf(histname,"%smetparameanvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s Paralell Mean vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metparameanvsdijetPt[fi][ja][ma] = new TH1D(histname,histtitle,NBINS,hist_min[5],hist_max[5]);
	sprintf(histname,"%smetpararmsvs%sdijetpt",mettype[ma].c_str(),jettype[ja].c_str());
	sprintf(histtitle,"%s Paralell RMS vs. %s Avg. Pt",metname[ma].c_str(),jetname[ja].c_str());
	p_metpararmsvsdijetPt[fi][ja][ma]  = new TH1D(histname,histtitle,NBINS,hist_min[5],hist_max[5]);
	
	sprintf(histname,"%smetvs%sdijetptprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metvsdijetPt[fi][ja][ma]     = h2_metvsdijetPt[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	sprintf(histname,"%smetvs%sjet12dphiprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metvsdphi[fi][ja][ma]        = h2_metvsjet12dphi[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	sprintf(histname,"%smetperpvs%sdijetptprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metvsdijetPt[fi][ja][ma]     = h2_metperpvsdijetPt[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	sprintf(histname,"%smetperpvs%sjet12dphiprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metvsdphi[fi][ja][ma]        = h2_metperpvsjet12dphi[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	sprintf(histname,"%smetparavs%sdijetptprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metparavsdijetPt[fi][ja][ma] = h2_metparavsdijetPt[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	sprintf(histname,"%smetparavs%sjet12dphiprofile",mettype[ma].c_str(),jettype[ja].c_str());
	std::cout<<"getting profile plot: "<<histname<<std::endl;
	p_metparavsdphi[fi][ja][ma]    = h2_metparavsjet12dphi[fi][ja][ma]->ProfileY(histname, 1, -1, "");
	
	std::cout<<"Setting up projections along y axis"<<std::endl;
	for (int bin = 0; bin < NBINS-NBINS+1; ++bin) {
	  sprintf(histname,"%smetvs%sdijetpt%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),static_cast<int>(lowval[3][bin]),static_cast<int>(highval[3][bin]));
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_met[fi][ja][ma][bin] = h2_metvsdijetPt[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  sprintf(histname,"%smetvs%sjet12dphi%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[4][bin],(int)highval[4][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_met[fi][ja][ma][bin] = h2_metvsjet12dphi[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  
	  sprintf(histname,"%smetperpvs%sdijetpt%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),static_cast<int>(lowval[5][bin]),static_cast<int>(highval[5][bin]));
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_metperp[fi][ja][ma][bin] = h2_metperpvsdijetPt[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  sprintf(histname,"%smetperpvs%sjet12dphi%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[6][bin],(int)highval[6][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_metperp[fi][ja][ma][bin] = h2_metperpvsjet12dphi[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  
	  sprintf(histname,"%smetparavs%sdijetpt%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),static_cast<int>(lowval[7][bin]),static_cast<int>(highval[7][bin]));
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_metpara[fi][ja][ma][bin] = h2_metparavsdijetPt[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  sprintf(histname,"%smetparavs%sjet12dphi%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[8][bin],(int)highval[8][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_metpara[fi][ja][ma][bin] = h2_metparavsjet12dphi[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  
	  sprintf(histname,"jet1%smetdphivs%sdijetpt%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[9][bin],(int)highval[9][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_jet1metdphi[fi][ja][ma][bin] = h2_jet1metdphivsdijetPt[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  sprintf(histname,"jet1%smetdphivs%sjet12dphi%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[10][bin],(int)highval[10][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_jet1metdphi[fi][ja][ma][bin] = h2_jet1metdphivsjet12dphi[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  
	  sprintf(histname,"jet2%smetdphivs%sdijetpt%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[11][bin],(int)highval[11][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_jet2metdphi[fi][ja][ma][bin] = h2_jet2metdphivsdijetPt[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  sprintf(histname,"jet2%smetdphivs%sjet12dphi%dto%d",mettype[ma].c_str(),jettype[ja].c_str(),(int)lowval[12][bin],(int)highval[12][bin]);
	  std::cout<<"getting projection plot: "<<histname<<" for bin: "<<bin+1<<std::endl;
	  s_jet2metdphi[fi][ja][ma][bin] = h2_jet2metdphivsjet12dphi[fi][ja][ma]->ProjectionY(histname,bin+1,bin+1,"e");
	  std::cout<<"done with projections for bin: "<<bin+1<<std::endl;
	}

	for (int bin = 0; bin < NBINS-NBINS+1; ++bin) {
	  std::cout<<"getting statistics for bin "<<bin+1<<" self profiles"<<std::endl;
	  double metmean   = s_met[fi][ja][ma][bin]->GetMean();
	  std::cout<<"obtained met mean"<<std::endl;
	  double metmeaner = s_met[fi][ja][ma][bin]->GetMeanError();
	  std::cout<<"obtained met mean er"<<std::endl;
	  double metrms    = s_met[fi][ja][ma][bin]->GetRMS();
	  std::cout<<"obtained met rms"<<std::endl;
	  double metrmser  = s_met[fi][ja][ma][bin]->GetRMSError();
	  std::cout<<"obtained met rms er"<<std::endl;
	  
	  double metperpmean   = s_metperp[fi][ja][ma][bin]->GetMean();
	  std::cout<<"obtained met perp mean"<<std::endl;
	  double metperpmeaner = s_metperp[fi][ja][ma][bin]->GetMeanError();
	  std::cout<<"obtained met perp mean er"<<std::endl;
	  double metperprms    = s_metperp[fi][ja][ma][bin]->GetRMS();
	  std::cout<<"obtained met perp rms"<<std::endl;
	  double metperprmser  = s_metperp[fi][ja][ma][bin]->GetRMSError();
	  std::cout<<"obtained met perp rms er"<<std::endl;
	  
	  double metparamean   = s_metpara[fi][ja][ma][bin]->GetMean();
	  std::cout<<"obtained met para mean"<<std::endl;
	  double metparameaner = s_metpara[fi][ja][ma][bin]->GetMeanError();
	  std::cout<<"obtained met para mean er"<<std::endl;
	  double metpararms    = s_metpara[fi][ja][ma][bin]->GetRMS();
	  std::cout<<"obtained met para rms"<<std::endl;
	  double metpararmser  = s_metpara[fi][ja][ma][bin]->GetRMSError();
	  std::cout<<"obtained met para rms er"<<std::endl;
	  
	  p_metmeanvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metmean);
	  p_metmeanvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metmeaner);
	  p_metrmsvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metrms);
	  p_metrmsvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metrmser);
	  
	  p_metperpmeanvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metperpmean);
	  p_metperpmeanvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metperpmeaner);
	  p_metperprmsvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metperprms);
	  p_metperprmsvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metperprmser);
	  
	  p_metparameanvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metparamean);
	  p_metparameanvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metparameaner);
	  p_metpararmsvsdijetPt[fi][ja][ma]->SetBinContent(bin+1,metpararms);
	  p_metpararmsvsdijetPt[fi][ja][ma]->SetBinerror(bin+1,metpararmser);
	}
      }
    }
  }


  //create the canvasses for display
  /*
    c_met[0] = new TCanvas("MET Distributions","metdist",800,800);
    c_met[1] = new TCanvas("MET Profiles","metdist",800,800);
    c_metperp[0] = new TCanvas("MET perp Distributions","metdist",800,800);
    c_metperp[1] = new TCanvas("MET perp Profiles","metdist",800,800);
    c_metpara[0] = new TCanvas("MET para Distributions","metdist",800,800);
    c_metpara[1] = new TCanvas("MET para Profiles","metdist",800,800);
  
  
    TProfile* p_metvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
    TProfile* p_metvsdphi[NUMFILES][NJETALGS][NMETALGS];
    TH1D*     p_metmeanvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
    TH1D*     p_metmeanvsdphi[NUMFILES][NJETALGS][NMETALGS];
    TH1D*     p_metrmsvsdijetPt[NUMFILES][NJETALGS][NMETALGS];
    TH1D*     p_metrmsvsdphi[NUMFILES][NJETALGS][NMETALGS];
  */

  for (int fi = 0; fi < NUMFILES; ++fi) {
    for (int ja = 0; ja < NJETALGS-3-1; ++ja) {
      /*
      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_met[0][ja]->cd(ma);
	s_met[fi][ja][ma][2]->Scale(scale[fi]);
	s_met[fi][ja][ma][2]->SetLineColor(metcolor[ma]);
	s_met[fi][ja][ma][2]->SetLineWidth(2.5);
	s_met[fi][ja][ma][2]->SetMarkerColor(metcolor[ma]);
	s_met[fi][ja][ma][2]->SetMarkerStyle(markerstyle[fi]);
	s_met[fi][ja][ma][2]->SetMarkerSize(2.5);
  	s_met[fi][ja][ma][2]->Draw("same");

	s_met[fi][ja][ma][4]->Scale(scale[fi]);
	s_met[fi][ja][ma][4]->SetLineColor(metcolor[ma]);
	s_met[fi][ja][ma][4]->SetLineWidth(2.5);
	s_met[fi][ja][ma][4]->SetMarkerColor(metcolor[ma]);
	s_met[fi][ja][ma][4]->SetMarkerStyle(markerstyle[fi]);
	s_met[fi][ja][ma][4]->SetMarkerSize(2.5);
  	s_met[fi][ja][ma][4]->Draw("same");

	s_met[fi][ja][ma][6]->Scale(scale[fi]);
	s_met[fi][ja][ma][6]->SetLineColor(metcolor[ma]);
	s_met[fi][ja][ma][6]->SetLineWidth(2.5);
	s_met[fi][ja][ma][6]->SetMarkerColor(metcolor[ma]);
	s_met[fi][ja][ma][6]->SetMarkerStyle(markerstyle[fi]);
	s_met[fi][ja][ma][6]->SetMarkerSize(2.5);
  	s_met[fi][ja][ma][6]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metperp[0][ja]->cd(ma);
	s_metperp[fi][ja][ma][2]->Scale(scale[fi]);
	s_metperp[fi][ja][ma][2]->SetLineColor(metcolor[ma]);
	s_metperp[fi][ja][ma][2]->SetLineWidth(2.5);
	s_metperp[fi][ja][ma][2]->SetMarkerColor(metcolor[ma]);
	s_metperp[fi][ja][ma][2]->SetMarkerStyle(markerstyle[fi]);
	s_metperp[fi][ja][ma][2]->SetMarkerSize(2.5);
  	s_metperp[fi][ja][ma][2]->Draw("same");

	s_metperp[fi][ja][ma][4]->Scale(scale[fi]);
	s_metperp[fi][ja][ma][4]->SetLineColor(metcolor[ma]);
	s_metperp[fi][ja][ma][4]->SetLineWidth(2.5);
	s_metperp[fi][ja][ma][4]->SetMarkerColor(metcolor[ma]);
	s_metperp[fi][ja][ma][4]->SetMarkerStyle(markerstyle[fi]);
	s_metperp[fi][ja][ma][4]->SetMarkerSize(2.5);
  	s_metperp[fi][ja][ma][4]->Draw("same");

	s_metperp[fi][ja][ma][6]->Scale(scale[fi]);
	s_metperp[fi][ja][ma][6]->SetLineColor(metcolor[ma]);
	s_metperp[fi][ja][ma][6]->SetLineWidth(2.5);
	s_metperp[fi][ja][ma][6]->SetMarkerColor(metcolor[ma]);
	s_metperp[fi][ja][ma][6]->SetMarkerStyle(markerstyle[fi]);
	s_metperp[fi][ja][ma][6]->SetMarkerSize(2.5);
  	s_metperp[fi][ja][ma][6]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metpara[0][ja]->cd(ma);
	s_metpara[fi][ja][ma][2]->Scale(scale[fi]);
	s_metpara[fi][ja][ma][2]->SetLineColor(metcolor[ma]);
	s_metpara[fi][ja][ma][2]->SetLineWidth(2.5);
	s_metpara[fi][ja][ma][2]->SetMarkerColor(metcolor[ma]);
	s_metpara[fi][ja][ma][2]->SetMarkerStyle(markerstyle[fi]);
	s_metpara[fi][ja][ma][2]->SetMarkerSize(2.5);
  	s_metpara[fi][ja][ma][2]->Draw("same");

	s_metpara[fi][ja][ma][4]->Scale(scale[fi]);
	s_metpara[fi][ja][ma][4]->SetLineColor(metcolor[ma]);
	s_metpara[fi][ja][ma][4]->SetLineWidth(2.5);
	s_metpara[fi][ja][ma][4]->SetMarkerColor(metcolor[ma]);
	s_metpara[fi][ja][ma][4]->SetMarkerStyle(markerstyle[fi]);
	s_metpara[fi][ja][ma][4]->SetMarkerSize(2.5);
  	s_metpara[fi][ja][ma][4]->Draw("same");

	s_metpara[fi][ja][ma][6]->Scale(scale[fi]);
	s_metpara[fi][ja][ma][6]->SetLineColor(metcolor[ma]);
	s_metpara[fi][ja][ma][6]->SetLineWidth(2.5);
	s_metpara[fi][ja][ma][6]->SetMarkerColor(metcolor[ma]);
	s_metpara[fi][ja][ma][6]->SetMarkerStyle(markerstyle[fi]);
	s_metpara[fi][ja][ma][6]->SetMarkerSize(2.5);
  	s_metpara[fi][ja][ma][6]->Draw("same");
      }

      //Mean plots
      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_met[1][ja]->cd(1);
	p_metmeanvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metmeanvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metmeanvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metmeanvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metmeanvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metmeanvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metmeanvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metperp[1][ja]->cd(1);
	p_metperpmeanvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metperpmeanvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metperpmeanvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metperpmeanvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metperpmeanvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metperpmeanvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metperpmeanvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metpara[1][ja]->cd(1);
	p_metparameanvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metparameanvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metparameanvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metparameanvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metparameanvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metparameanvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metparameanvsdijetPt[fi][ja][ma]->Draw("same");
      }
      //RMS plots
      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_met[1][ja]->cd(2);
	p_metrmsvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metrmsvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metrmsvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metrmsvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metrmsvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metrmsvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metrmsvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metperp[1][ja]->cd(2);
	p_metperprmsvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metperprmsvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metperprmsvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metperprmsvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metperprmsvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metperprmsvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metperprmsvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metpara[1][ja]->cd(2);
	p_metpararmsvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metpararmsvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metpararmsvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metpararmsvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metpararmsvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metpararmsvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metpararmsvsdijetPt[fi][ja][ma]->Draw("same");
      }

      //Profile plots
      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_met[1][ja]->cd(3);
	p_metvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metperp[1][ja]->cd(3);
	p_metperpvsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metperpvsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metperpvsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metperpvsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metperpvsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metperpvsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metperpvsdijetPt[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metpara[1][ja]->cd(3);
	p_metparavsdijetPt[fi][ja][ma]->Scale(scale[fi]);
	p_metparavsdijetPt[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metparavsdijetPt[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metparavsdijetPt[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metparavsdijetPt[fi][ja][ma]->SetMarkerSize(2.5);
	p_metparavsdijetPt[fi][ja][ma]->SetLineWidth(2.5);
  	p_metparavsdijetPt[fi][ja][ma]->Draw("same");
      }
      //Profile plots
      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_met[1][ja]->cd(4);
	p_metvsdphi[fi][ja][ma]->Scale(scale[fi]);
	p_metvsdphi[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metvsdphi[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metvsdphi[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metvsdphi[fi][ja][ma]->SetMarkerSize(2.5);
	p_metvsdphi[fi][ja][ma]->SetLineWidth(2.5);
  	p_metvsdphi[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metperp[1][ja]->cd(4);
	p_metperpvsdphi[fi][ja][ma]->Scale(scale[fi]);
	p_metperpvsdphi[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metperpvsdphi[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metperpvsdphi[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metperpvsdphi[fi][ja][ma]->SetMarkerSize(2.5);
	p_metperpvsdphi[fi][ja][ma]->SetLineWidth(2.5);
  	p_metperpvsdphi[fi][ja][ma]->Draw("same");
      }

      for (int ma = 0; ma < NMETALGS; ++ma) {
	c_metpara[1][ja]->cd(4);
	p_metparavsdphi[fi][ja][ma]->Scale(scale[fi]);
	p_metparavsdphi[fi][ja][ma]->SetLineColor(metcolor[ma]);
	p_metparavsdphi[fi][ja][ma]->SetMarkerColor(metcolor[ma]);
	p_metparavsdphi[fi][ja][ma]->SetMarkerStyle(markerstyle[fi]);
	p_metparavsdphi[fi][ja][ma]->SetMarkerSize(2.5);
	p_metparavsdphi[fi][ja][ma]->SetLineWidth(2.5);
  	p_metparavsdphi[fi][ja][ma]->Draw("same");
      }
      */
    }
  }
}

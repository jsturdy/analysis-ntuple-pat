#define optimizeCuts_cxx
#include "optimizeCuts.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#define NSTEPS     4
#define NUMHISTOS 26

void optimizeCuts::Loop(std::string outputfile, std::string analysisVer, double lum, double xs, double eff, double numGen)
{
  outfilename_ = outputfile;
  
  luminosity_    = lum;
  cross_section_ = xs;
  efficiency_    = eff;
  generated_events_ = numGen;

  printf("version: %s  lum: %2.2f,  xs: %2.2f,  eff: %2.2f\n",outfilename_.c_str(), lum, xs, eff);
  if (fChain == 0) return;

  char tmpfile[128];
  sprintf(tmpfile,"%s",outfilename_.c_str());
  TFile *file = new TFile(tmpfile,"RECREATE");
  file->cd();
   
  Long64_t nentries = fChain->GetEntriesFast();
   
  double localpi  = acos(-1);
  TH1D *h_counters[4];

  char histtitle[NSTEPS][128];

  char plottitle[NSTEPS][128];
  string histpre[4] = {"h_pre_cuts_","h_individual_cuts_","h_N1_cuts_","h_post_cuts_"};
  //Counters for selections
  for (int tt = 0; tt < 4; ++tt) {
    sprintf(histtitle[tt],"%sevents",histpre[tt].c_str());
    sprintf(plottitle[tt],"Events Passing Cuts");
    h_counters[tt] = new TH1D(histtitle[tt],plottitle[tt],30,0,30);
  }


  for (int step = 0; step < NSTEPS; ++step) 
    h_counters[step] ->Sumw2();
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
  int  leptoncounter[4]   = {0};//isolated lepton veto
  int  fjcounter[4]       = {0};  //final jet requirements
  //Branch for MET based analysis
  int  metcounter[4][9]      = {{0}};  //met cut
  int  dphicounter[4]     = {0};  //dphi beween jets and met
  //Branch for HT/MHT based analysis
  int  mhtcounter[4][9]      = {{0}};  //mht cut
  int  dphistarcounter[4] = {0};  //dphi between jets and mht


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry); nbytes += nb;
    ++totalcounter;
    h_counters[0]->Fill(24.5);
    h_counters[1]->Fill(24.5);
    h_counters[2]->Fill(24.5);
    h_counters[3]->Fill(24.5);
    //if (Preselection(ientry) < 0) continue;
    //++preselection;
    // if (TriggerSelection(ientry) < 0) continue;
    // if (JetSelection(ientry) < 0) continue;
    // if (DiJetSelection(ientry) < 0) continue;
    // if (METSelection(ientry) < 0) continue;
    // if (HTSelection(ientry) < 0) continue;
    // if (MHTSelection(ientry) < 0) continue;
    // if (LeptonVeto(ientry) < 0) continue;

    double nJets  = NJets;
    double nElecs = ElecN;
    double nMuons = MuonN;

    double met    = METpt_Fullcorr_nocc;
    //TLorentzVector met
    //double mex = MET_Fullcorr_nocc[0];
    //double mex = MET_Fullcorr_nocc[1];
    //double mex = MET_Fullcorr_nocc[2];
    //met.SetPxPyPzE(mex,mey,mez,en);
    double metphi = METphi_Fullcorr_nocc;
    //double mex    = met*cos(metphi);
    //double mey    = met*sin(metphi);

    double         ht  = computeHT(ht_jet_minpt, ht_jet_maxeta, false);
    TLorentzVector mht = computeMHT(mht_jet_minpt, mht_jet_maxeta, false);

    //Calculate various dphi values
    double jet12dphi   = 0.;
    double jet1metdphi = 0.;
    double jet2metdphi = 0.;

    if (nJets > 1){
      jet1metdphi = JetPhi[0]-metphi;//uses JE corrections, but not muons (for LQ samples)
      jet12dphi   = JetPhi[0]-JetPhi[1];
      jet2metdphi = JetPhi[1]-metphi;//uses JE corrections, but not muons (for LQ samples)
    }
    
    jet12dphi   = (jet12dphi < 0)       ? -jet12dphi            : jet12dphi;
    jet12dphi   = (jet12dphi > localpi) ? 2*localpi - jet12dphi : jet12dphi;

    jet1metdphi = (jet1metdphi < 0)       ? -jet1metdphi            : jet1metdphi;
    jet1metdphi = (jet1metdphi > localpi) ? 2*localpi - jet1metdphi : jet1metdphi;
    jet2metdphi = (jet2metdphi < 0)       ? -jet2metdphi            : jet2metdphi;
    jet2metdphi = (jet2metdphi > localpi) ? 2*localpi - jet2metdphi : jet2metdphi;
      
    //calculated dphistar
    double dphistar = 0.;
    dphistar = computeDPhiStar(mht,mht_jet_minpt,mht_jet_maxeta,false);

    double Meff = ht + mht.Pt();
    double MT   = 0.;
    double Minv = 0.;

    if (nJets > 1) {
      LorentzV jet1, jet2, dijet;
      jet1.SetPxPyPzE(JetPx[0],JetPy[0],JetPz[0],JetE[0]);
      jet2.SetPxPyPzE(JetPx[1],JetPy[1],JetPz[1],JetE[1]);
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
    bool leptonveto        = true;// true if no leptons have pT>15GeV
    bool dijetselection    = true;// jet1 and jet2 pT>100GeV, |eta|<2.5
    bool finaljet          = true;// no other jet pT>50GeV, combine with dijet selection
    bool metselection      = true;// MET of event > 200GeV//alternately 350GeV
    bool dphiselection     = true;// dphi(jet1, jet2, met) passes cuts
    bool htselection       = true;// HT of event > 250GeV
    bool mhtselection      = true;// MHT of event > 200GeV
    bool dphistarselection = true;// dphi(jet1, jet2, met) passes cuts
      
    //for the selection variables false means we veto the event
    bool nJetSelection[2]       = {false,false};
    bool Preselection[2]        = {false,false};

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
      if (JetPt[1] < 50.)
	Preselection[0] = false;
      else if ( !(jetID(0,false) && jetID(1,false) ) )
	Preselection[0] = false;
      else
	Preselection[0] = true;
    }

    //Trigger selection
    hltJetTriggerSelection[0] = true;
    hltMETTriggerSelection[0] = true;
    hltMHTTriggerSelection[0] = true;
    hltHTTriggerSelection[0]  = true;

    hltTriggerSelection[0] = 
      hltJetTriggerSelection[0] &&
      hltMETTriggerSelection[0] &&
      hltMHTTriggerSelection[0] &&
      hltHTTriggerSelection[0];

    //Jets
    if (nJets>0) jet1PtSelection[0]  = (JetPt[0] >= jet1_minpt) ? true : false;
    if (nJets>1) jet2PtSelection[0]  = (JetPt[1] >= jet2_minpt) ? true : false;

    if (nJets>0) jet1IDSelection[0]  = jetID(0,false);
    if (nJets>1) jet2IDSelection[0]  = jetID(1,false);

    if (nJets>0) jet1EtaSelection[0]  = (fabs(JetEta[0]) <= jet1_maxeta) ? true : false;
    if (nJets>1) jet2EtaSelection[0]  = (fabs(JetEta[1]) <= jet2_maxeta) ? true : false;
      
    if (nJets>1) jet12dphiSelection[0]   = (jet12dphi   >= cut_jet12dphi)   ? true : false;
    if (nJets>0) jet1metdphiSelection[0] = (jet1metdphi >= cut_jet1metdphi) ? true : false;
    if (nJets>1) jet2metdphiSelection[0] = (jet2metdphi >= cut_jet2metdphi) ? true : false;
    dphistarSelection[0]                 = (dphistar    >= cut_dphistar)    ? true : false;

    metSelection[0]   = (met      >= cut_met)  ? true : false;
    htSelection[0]    = (ht       >= cut_ht)   ? true : false;
    mhtSelection[0]   = (mht.Pt() >= cut_mht)  ? true : false;
    meffSelection[0]  = (Meff     >= cut_meff) ? true : false;

    UInt_t goodjetcount = 0;

    if (jet1IDSelection[0])
      goodjetcount +=1;
    if (jet2IDSelection[0])
      goodjetcount +=1;
    
    for (int ijet = 2; ijet < nJets; ++ijet) 
      if (jetID(ijet,false)) {
	++goodjetcount;
	if (JetPt[ijet] > jetall_maxpt)
	  excessiveJetVeto[0] = false;
      }
      
    UInt_t goodeleccount = 0;
    for (int ielec = 0; ielec < nElecs; ++ielec) 
      if (electronID(ielec,false) ) {
	++goodeleccount;
	if (ElecPt[ielec] > electron_maxpt)
	  electronVeto[0] = false;
      }
      
    UInt_t goodmuoncount = 0;
    for ( int imuon = 0; imuon < nMuons; ++imuon)
      if (muonID(imuon,1) ) {
	++goodmuoncount;
	if (MuonPt[imuon] > muon_maxpt)
	  muonVeto[0] = false;
      }
    leptonVeto[0] = electronVeto[0]||muonVeto[0];
      
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

    finaljet       = dijetselection && excessiveJetVeto[0];
    leptonveto     = electronVeto[0] || muonVeto[0];
    metselection   = metSelection[0];
    dphiselection  = jet1metdphiSelection[0] && jet2metdphiSelection[0];
    htselection    = htSelection[0];
    mhtselection   = mhtSelection[0];
    dphistarselection  = dphistarSelection[0];
      
      
    //    printf("preselect   triggers  dijet   finaljet   dphi   dphi*   met   lepton   ht   mht\n");
    //    printf("%d       %d       %d   %d   %d   %d   %d   %d   %d   %d\n",preselection,triggerselectiondijetselection,finaljet,dphiselection,dphistarselection,metselection,leptonveto,htselection,mhtselection);

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
    //Selection based on MET/DPhi(Jet1,2,MET)
    if (dphiselection) {
      dphicounter[0]++;
      h_counters[1]->Fill(4.5);
    }
    if (met > 200) {
      metcounter[0][0]++;
      h_counters[1]->Fill(5.5);
    }
    if (met > 225) {
      metcounter[0][1]++;
      h_counters[1]->Fill(6.5);
    }
    if (met > 250) {
      metcounter[0][2]++;
      h_counters[1]->Fill(7.5);
    }
    if (met > 275) {
      metcounter[0][3]++;
      h_counters[1]->Fill(8.5);
    }
    if (met > 300) {
      metcounter[0][4]++;
      h_counters[1]->Fill(9.5);
    }
    if (met > 325) {
      metcounter[0][5]++;
      h_counters[1]->Fill(10.5);
    }
    if (met > 350) {
      metcounter[0][6]++;
      h_counters[1]->Fill(11.5);
    }
    if (met > 375) {
      metcounter[0][7]++;
      h_counters[1]->Fill(12.5);
    }
    if (met > 400) {
      metcounter[0][8]++;
      h_counters[1]->Fill(13.5);
    }
    //Selection based on HT/MHT/DPhiStar
    if (dphistarselection) {
      dphistarcounter[0]++;
      h_counters[1]->Fill(14.5);
    }
    if (mht.Pt() > 200) {
      mhtcounter[0][0]++;
      h_counters[1]->Fill(15.5);
    }
    if (mht.Pt() > 225) {
      mhtcounter[0][1]++;
      h_counters[1]->Fill(16.5);
    }
    if (mht.Pt() > 250) {
      mhtcounter[0][2]++;
      h_counters[1]->Fill(17.5);
    }
    if (mht.Pt() > 275) {
      mhtcounter[0][3]++;
      h_counters[1]->Fill(18.5);
    }
    if (mht.Pt() > 300) {
      mhtcounter[0][4]++;
      h_counters[1]->Fill(19.5);
    }
    if (mht.Pt() > 325) {
      mhtcounter[0][5]++;
      h_counters[1]->Fill(20.5);
    }
    if (mht.Pt() > 350) {
      mhtcounter[0][6]++;
      h_counters[1]->Fill(21.5);
    }
    if (mht.Pt() > 375) {
      mhtcounter[0][7]++;
      h_counters[1]->Fill(22.5);
    }
    if (mht.Pt() > 400) {
      mhtcounter[0][8]++;
      h_counters[1]->Fill(23.5);
    }


    //**************************Sequential pre/post cut counters***********************//
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
	    //Selection based on MET/DPhi(Jet1,2,MET)
	    dphicounter[1]++;
	    h_counters[0]->Fill(4.5);
	    if (dphiselection) {
	      dphicounter[2]++;
	      h_counters[3]->Fill(4.5);
	      metcounter[1][0]++;
	      h_counters[0]->Fill(5.5);
	      if (met > 200) {
		metcounter[2][0]++;
		h_counters[3]->Fill(5.5);
		metcounter[1][1]++;
		h_counters[0]->Fill(6.5);
		if (met > 225) {
		  metcounter[2][1]++;
		  h_counters[3]->Fill(6.5);
		  metcounter[3][2]++;
		  h_counters[0]->Fill(7.5);
		  if (met > 250) {
		    metcounter[2][2]++;
		    h_counters[3]->Fill(7.5);
		    metcounter[1][3]++;
		    h_counters[0]->Fill(8.5);
		    if (met > 275) {
		      metcounter[2][3]++;
		      h_counters[3]->Fill(8.5);
		      metcounter[1][4]++;
		      h_counters[0]->Fill(9.5);
		      if (met > 300) {
			metcounter[2][4]++;
			h_counters[3]->Fill(9.5);
			metcounter[1][5]++;
			h_counters[0]->Fill(10.5);
			if (met > 325) {
			  metcounter[2][5]++;
			  h_counters[3]->Fill(10.5);
			  metcounter[1][6]++;
			  h_counters[0]->Fill(11.5);
			  if (met > 350) {
			    metcounter[2][6]++;
			    h_counters[3]->Fill(11.5);
			    metcounter[1][7]++;
			    h_counters[0]->Fill(12.5);
			    if (met > 375) {
			      metcounter[2][7]++;
			      h_counters[3]->Fill(12.5);
			      metcounter[1][8]++;
			      h_counters[0]->Fill(13.5);
			      if (met > 400) {
				metcounter[2][8]++;
				h_counters[3]->Fill(13.5);}}}}}}}}}}
	    //Selection based on HT/MHT/DPhiStar
	    dphistarcounter[1]++;
	    h_counters[0]->Fill(14.5);
	    if (dphistarselection) {
	      dphistarcounter[2]++;
	      h_counters[3]->Fill(14.5);
	      mhtcounter[1][0]++;
	      h_counters[0]->Fill(15.5);
	      if (mht.Pt() > 200) {
		mhtcounter[2][0]++;
		h_counters[3]->Fill(15.5);
		mhtcounter[1][1]++;
		h_counters[0]->Fill(16.5);
		if (mht.Pt() > 225) {
		  mhtcounter[2][1]++;
		  h_counters[3]->Fill(16.5);
		  mhtcounter[1][2]++;
		  h_counters[0]->Fill(17.5);
		  if (mht.Pt() > 250) {
		    mhtcounter[2][2]++;
		    h_counters[3]->Fill(17.5);
		    mhtcounter[1][3]++;
		    h_counters[0]->Fill(18.5);
		    if (mht.Pt() > 275) {
		      mhtcounter[2][3]++;
		      h_counters[3]->Fill(18.5);
		      mhtcounter[1][4]++;
		      h_counters[0]->Fill(19.5);
		      if (mht.Pt() > 300) {
			mhtcounter[2][4]++;
			h_counters[3]->Fill(19.5);
			mhtcounter[1][5]++;
			h_counters[0]->Fill(20.5);
			if (mht.Pt() > 325) {
			  mhtcounter[2][5]++;
			  h_counters[3]->Fill(20.5);
			  mhtcounter[1][6]++;
			  h_counters[0]->Fill(21.5);
			  if (mht.Pt() > 350) {
			    mhtcounter[2][6]++;
			    h_counters[3]->Fill(21.5);
			    mhtcounter[1][7]++;
			    h_counters[0]->Fill(22.5);
			    if (mht.Pt() > 375) {
			      mhtcounter[2][7]++;
			      h_counters[3]->Fill(22.5);
			      mhtcounter[1][8]++;
			      h_counters[0]->Fill(23.5);
			      if (mht.Pt() > 400) {
				mhtcounter[2][8]++;
				h_counters[3]->Fill(23.5);}}}}}}}}}}}}}}

    //**************************N-1 cut counters***********************//
    if (
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	(
	 (
	  metselection    &&
	  dphiselection
	  )  ||
	 (
	  mhtselection    &&
	  dphistarselection
	  )
	 )
	) {
      pscounter[3]++;
      h_counters[2]->Fill(0.5);}
    if (
	preselection     &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	(
	 (
	  metselection    &&
	  dphiselection
	  )  ||
	 (
	  mhtselection    &&
	  dphistarselection
	  )
	 )
	) {
      trcounter[3]++;
      h_counters[2]->Fill(1.5);}
    if (
	preselection     &&
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	(
	 (
	  metselection    &&
	  dphiselection
	  )  ||
	 (
	  mhtselection    &&
	  dphistarselection
	  )
	 )
	) {
      fjcounter[3]++;
      h_counters[2]->Fill(2.5);}
    if (
	preselection     &&
	triggerselection &&
	//dijetselection   &&
	finaljet         &&
	(
	 (
	  metselection    &&
	  dphiselection
	  )  ||
	 (
	  mhtselection    &&
	  dphistarselection
	  )
	 )
	) {
      leptoncounter[3]++;
      h_counters[2]->Fill(3.5);}
    //Selection based on MET/DPhi(Jet1,2,MET)
    if (
	preselection     &&
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	metselection
	) {
      dphicounter[3]++;
      h_counters[2]->Fill(4.5);}
    if (
	preselection     &&
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	dphiselection
	) {
      metcounter[3][0]++;
      metcounter[3][1]++;
      metcounter[3][2]++;
      metcounter[3][3]++;
      metcounter[3][4]++;
      metcounter[3][5]++;
      metcounter[3][6]++;
      metcounter[3][7]++;
      metcounter[3][8]++;
      h_counters[2]->Fill(5.5);
      h_counters[2]->Fill(6.5);
      h_counters[2]->Fill(7.5);
      h_counters[2]->Fill(8.5);
      h_counters[2]->Fill(9.5);
      h_counters[2]->Fill(10.5);
      h_counters[2]->Fill(11.5);
      h_counters[2]->Fill(12.5);
      h_counters[2]->Fill(13.5);}
    //Selection based on HT/MHT/DPhiStar
    if (
	preselection     &&
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	mhtselection
	) {
      dphistarcounter[3]++;
      h_counters[2]->Fill(14.5);}
    if (
	preselection     &&
	triggerselection &&
	leptonveto       &&
	//dijetselection   &&
	finaljet         &&
	dphistarselection
	) {
      mhtcounter[3][0]++;
      mhtcounter[3][1]++;
      mhtcounter[3][2]++;
      mhtcounter[3][3]++;
      mhtcounter[3][4]++;
      mhtcounter[3][5]++;
      mhtcounter[3][6]++;
      mhtcounter[3][7]++;
      mhtcounter[3][8]++;
      h_counters[2]->Fill(15.5);
      h_counters[2]->Fill(16.5);
      h_counters[2]->Fill(17.5);
      h_counters[2]->Fill(18.5);
      h_counters[2]->Fill(19.5);
      h_counters[2]->Fill(20.5);
      h_counters[2]->Fill(21.5);
      h_counters[2]->Fill(22.5);
      h_counters[2]->Fill(23.5);}
  }

  // scale histograms to desired values
  double scale = luminosity_ * cross_section_ * efficiency_ / generated_events_;

  char ytitle[128];
  
  for (int mine = 0; mine < 4; ++mine) {
    //sprintf(ytitle,"Events / %2.0f pb^{-1}",luminosity_);
    sprintf(ytitle,"Raw Events passing cuts");
    //h_counters[mine]->Scale(scale);
    h_counters[mine]->GetYaxis()->SetTitle(ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(1,"2 Loose ID Jets p_{T} > 50 GeV");
    h_counters[mine]->GetXaxis()->SetBinLabel(2,"hlt Trigger Cuts");
    h_counters[mine]->GetXaxis()->SetBinLabel(3,"Jet 2 p_{T} > 100 GeV no third jet");
    h_counters[mine]->GetXaxis()->SetBinLabel(4,"e/#mu Veto");
    sprintf(ytitle,"#Delta#phi(J_{1},#slashE_{T}) > %2.2f, #Delta#phi(J_{2},#slashE_{T}) > %2.2f",cut_jet1metdphi,cut_jet2metdphi);
    h_counters[mine]->GetXaxis()->SetBinLabel(5,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",200);
    h_counters[mine]->GetXaxis()->SetBinLabel(6,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",225);
    h_counters[mine]->GetXaxis()->SetBinLabel(7,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",250);
    h_counters[mine]->GetXaxis()->SetBinLabel(8,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",275);
    h_counters[mine]->GetXaxis()->SetBinLabel(9,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",300);
    h_counters[mine]->GetXaxis()->SetBinLabel(10,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",325);
    h_counters[mine]->GetXaxis()->SetBinLabel(11,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",350);
    h_counters[mine]->GetXaxis()->SetBinLabel(12,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",375);
    h_counters[mine]->GetXaxis()->SetBinLabel(13,ytitle);
    sprintf(ytitle,"#slashE_{T} > %d",400);
    h_counters[mine]->GetXaxis()->SetBinLabel(14,ytitle);
    sprintf(ytitle,"#Delta#phi* > %2.2f",cut_dphistar);
    h_counters[mine]->GetXaxis()->SetBinLabel(15,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",200);
    h_counters[mine]->GetXaxis()->SetBinLabel(16,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",225);
    h_counters[mine]->GetXaxis()->SetBinLabel(17,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",250);
    h_counters[mine]->GetXaxis()->SetBinLabel(18,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",275);
    h_counters[mine]->GetXaxis()->SetBinLabel(19,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",300);
    h_counters[mine]->GetXaxis()->SetBinLabel(20,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",325);
    h_counters[mine]->GetXaxis()->SetBinLabel(21,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",350);
    h_counters[mine]->GetXaxis()->SetBinLabel(22,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",375);
    h_counters[mine]->GetXaxis()->SetBinLabel(23,ytitle);
    sprintf(ytitle,"#slashH_{T} > %d",400);
    h_counters[mine]->GetXaxis()->SetBinLabel(24,ytitle);
    h_counters[mine]->GetXaxis()->SetBinLabel(25,"Nevents");
    h_counters[mine]->SetStats(kFALSE);
    
  }

  //
  int Nevents = totalcounter;
  printf("Cut Series        Nevents - preselection - triggers - finaljet - leptonveto - dphiselection - metselection - dphistarselection - mhtselection\n");
  printf("- dphiselection - met > 200 - met > 225 - met > 250 - met > 275 - met > 300 - met > 325 - met > 350 - met > 375 - met > 400\n");
  printf("- dphiselection - mht > 200 - mht > 225 - mht > 250 - mht > 275 - mht > 300 - mht > 325 - mht > 350 - mht > 375 - mht > 400\n");
  printf("Individual:       %7d - %12d - %8d - %8d - %16d\n",
	 Nevents,pscounter[0],trcounter[0],fjcounter[0],leptoncounter[0]);
  printf(" - %12d - %13d - %13d - %13d - %13d - %13d - %13d - %13d - %13d - %13d\n",
	 dphicounter[0],metcounter[0][0],metcounter[0][1],metcounter[0][2],metcounter[0][3],metcounter[0][4],metcounter[0][5],metcounter[0][6],metcounter[0][7],metcounter[0][8]);
  printf(" - %12d - %17d - %17d - %17d - %17d - %17d - %17d - %17d - %17d - %17d\n",
	 dphistarcounter[0],mhtcounter[0][0],mhtcounter[0][1],mhtcounter[0][2],mhtcounter[0][3],mhtcounter[0][4],mhtcounter[0][5],mhtcounter[0][6],mhtcounter[0][7],mhtcounter[0][8]);
  printf("Sequential-post:  %7d - %12d - %8d - %8d - %16d\n",
	 Nevents,pscounter[2],trcounter[2],fjcounter[2],leptoncounter[2]);
  printf(" - %12d - %13d - %13d - %13d - %13d - %13d - %13d - %13d - %13d - %13d\n",
	 dphicounter[2],metcounter[2][0],metcounter[2][1],metcounter[2][2],metcounter[2][3],metcounter[2][4],metcounter[2][5],metcounter[2][6],metcounter[2][7],metcounter[2][8]);
  printf(" - %12d - %17d - %17d - %17d - %17d - %17d - %17d - %17d - %17d - %17d\n",
	 dphistarcounter[2],mhtcounter[2][0],mhtcounter[2][1],mhtcounter[2][2],mhtcounter[2][3],mhtcounter[2][4],mhtcounter[2][5],mhtcounter[2][6],mhtcounter[2][7],mhtcounter[2][8]);
  
  //Write out file and histograms
  for (int step = 0; step < NSTEPS; ++step) 
    h_counters[step] ->Write();
   
  file->cd();
  file->Write();
}


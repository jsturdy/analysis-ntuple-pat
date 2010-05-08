#define compareDataMC_cxx
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "/home/nguyenh/Analysis/MC-Data/Root/FirstData/compareDataMC.h"

// 1 = pf
// 2 = calo
// 3 = jpt
// 4 = tc

//void compareDataMC(TString hist, TString title, int alg)
void compareDataMC::plot(TString hist, TString name, TString title, int alg, bool logscale)


{

TString LegendMC = "MC MinBias START3X_V26A_356";
TString LegendData = "Data 7TeV";

// gStyle->SetOptStat("nimou");
 gStyle->SetOptFit(0000);  
 gStyle->SetCanvasColor(kWhite);



//Create histograms
TH1F* pfMET_data;
TH1F* pfMET_mc;

// An example of how to call histograms:
//((TH1F*)file[fi]->Get("h_calojet12avgPt"))->Integral(-1,501);

// Get the histograms from the mc file and data file

TFile* f_data = new TFile("/home/nguyenh/Analysis/MC-Data/Root/FirstData/Histograms_datatest.root");
//pfMET_data = ((TH1F*)f_data->Get("PF_MET_fullcorr_nocc"));
pfMET_data = ((TH1F*)f_data->Get(hist));

TFile* f_mc = new TFile("/home/nguyenh/Analysis/MC-Data/Root/FirstData/Histograms_mctest.root");
//pfMET_mc = ((TH1F*)f_mc->Get("PF_MET_fullcorr_nocc"));
pfMET_mc = ((TH1F*)f_mc->Get(hist));


//Get the errors of the data for each bin:
/*
for(int i = 1; i < binsize+1; ++i)
{
	double pfMET_error = pfMET_data->GetBinContent(i);
	pfMET_data->SetBinError(i,sqrt(pfMET_error));
}
*/

// Get the scales from Data. We find the area under data curve and make sure MC has same area.

Double_t pfMET_data_area = pfMET_data->Integral();
Double_t pfMET_mc_area = pfMET_mc->Integral();
Double_t pfMETscale = (pfMET_data_area / pfMET_mc_area);
pfMET_mc->Scale(pfMETscale);

// Plot logistics

//Filling different color depending on algorithm
if(alg == 1) {
pfMET_mc->SetLineColor(38);
pfMET_mc->SetLineWidth(1);
pfMET_mc->SetFillColor(38);
}

if(alg == 2) {
pfMET_mc->SetLineColor(46);
pfMET_mc->SetLineWidth(1);
pfMET_mc->SetFillColor(46);
}

if(alg == 3) {
pfMET_mc->SetLineColor(5);
pfMET_mc->SetLineWidth(1);
pfMET_mc->SetFillColor(5);
}

if(alg == 4) {
pfMET_mc->SetLineColor(3);
pfMET_mc->SetLineWidth(1);
pfMET_mc->SetFillColor(3);
}

pfMET_data->SetMarkerStyle(20);
pfMET_data->SetMarkerColor(kBlack);

//pfMET_mc->SetTitle(title);
pfMET_mc->SetTitle(title);
pfMET_mc->SetMinimum(0.1);

// Legends (xmin, ymin, xmax, ymax)
TLegend *leg_pfMET = new TLegend(.75, .85, 1, 1);
leg_pfMET->SetFillColor(kWhite);
leg_pfMET->AddEntry(pfMET_mc, LegendMC, "f");
leg_pfMET->AddEntry(pfMET_data, LegendData, "lep");


// Drawing our canvas and our plot

//TCanvas *pfMET = new TCanvas(title,title);
TCanvas *pfMET = new TCanvas(title,title);
if(logscale)
gPad->SetLogy(kTRUE);
if(!logscale)
gPad->SetLogy(kFALSE);
 gStyle->SetOptStat("kFALSE");
// gStyle->SetOptFit(0000);  
 gStyle->SetCanvasColor(kWhite);

pfMET_mc->Draw("");
pfMET_data->Draw("esame");
leg_pfMET->Draw("");

// Saving file
pfMET->SaveAs("/home/nguyenh/Analysis/MC-Data/Root/FirstData/plots/"+name+".png");
//pfMET->SaveAs("/home/nguyenh/Analysis/MC-Data/Root/FirstData/plots/test.eps");









}

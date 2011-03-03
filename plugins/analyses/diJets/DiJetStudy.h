//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef DiJetStudy_h
#define DiJetStudy_h

#include "../../common/ntupleAnalysisPAT.h"

class DiJetStudy : public ntupleAnalysisPAT {
 public :
  
  DiJetStudy(TTree *tree=0, std::string* sampleList=0, std::string* triggerList=0, std::string* cutFile=0, const bool &isData=false, const std::string &jetPrefix="Calo", const std::string &metPrefix="CaloTypeI", const std::string &lepPrefix="", const std::string &phtPrefix="", const std::string &sampleKey="");
  virtual ~DiJetStudy();
  
  //virtual Int_t    TriggerSelection(Long64_t entry);
  //virtual Int_t    Preselection(Long64_t entry);
  //virtual Int_t    JetSelection(Long64_t entry);
  //virtual Int_t    DiJetSelection(Long64_t entry);
  //virtual Int_t    LeptonVeto(Long64_t entry);
  //virtual Int_t    METSelection(Long64_t entry);
  //virtual Int_t    HTSelection(Long64_t entry);
  //virtual Int_t    MHTSelection(Long64_t entry);
  //virtual Int_t    Cut(Long64_t entry);
  
  //virtual void     Loop(std::string outfilename="outfile.root", double lum=35., double xs=1., double eff=1., double numGen=1., double cutJet1=100., double cutJet2=100., double cutMET=200.);
  virtual void     Loop(const std::string &outfilename="outfile.root", const double &cutJet1=100., const double &cutJet2=100., const double &cutMET=200., const bool& strictDiJets=true, const int& triggerPaths=2);
  //virtual void     Loop(const std::string& outfilename="outfile.root", const double& lum=1., const double& scale=1., const double& cutJet1=100., const double& cutJet2=100., const double& cutMET=250.);
  //virtual void     Loop(const std::string &outfilename="outfile.root", const double lum=35., const double scale=1., const double &cutJet1=100., const double &cutJet2=100., const double &cutMET=200.);
  
  //print out the event information for events that pass our cuts
  //if the event is real data, print out extra information
  void printOutEventInfo();
};

#endif

#ifdef DiJetStudy_cxx

#endif // #ifdef DiJetStudy_cxx

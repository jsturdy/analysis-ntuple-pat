//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef photonJets_h
#define photonJets_h

#include "../../common/ntupleAnalysisPAT.h"
#include "../../common/ntuplePragmas.h"

class photonJets : public ntupleAnalysisPAT {
 public :
  
  photonJets(TTree *tree=0, 
	     std::string* sampleList=0, 
	     std::string* triggerList=0, 
	     std::string* cutFile=0, 
	     const bool &isData=false, 
	     const std::string &jetPrefix="PF2PAT", 
	     const std::string &metPrefix="PFTypeI", 
	     const std::string &lepPrefix="PF", 
	     const std::string &phtPrefix="", 
	     const std::string &sampleKey="");

  virtual ~photonJets();
  
  virtual void     Loop(const std::string &outfilename="outfile.root", 
			const bool& strictDiJets=true, 
			const int& triggerPaths=2
			);
  
  //print out the event information for events that pass our cuts
  //if the event is real data, print out extra information
  bool passPhotonID(const int&);

};

#endif

#ifdef photonJets_cxx
bool photonJets::passPhotonID(const int& phot) 
{
  bool passPhotID = true;
  //pass tracker iso
  passPhotID &= PhotTrkIso->at(phot)  < 2.0 + 0.001*PhotonP4->at(phot).pt();
  //pass ecal iso
  passPhotID &= PhotECalIso->at(phot) < 4.2 + 0.003*PhotonP4->at(phot).pt();
  //pass hcal iso
  passPhotID &= PhotHCalIso->at(phot) < 2.2 + 0.001*PhotonP4->at(phot).pt();
  std::cout<<"photon ID result is "<<passPhotID<<std::endl;
  return passPhotID;
}

#endif // #ifdef photonJets_cxx

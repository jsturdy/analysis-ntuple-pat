//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 15 07:10:50 2010 by ROOT version 5.22/00d
// from TTree AllData/data after preselection
// found on file: PATtuple_V9_DATA_Run2010A_June9thReReco_32_1_TaF.root
//////////////////////////////////////////////////////////

#ifndef CountProcessedEvents_h
#define CountProcessedEvents_h

#include "../../common/ntupleAnalysisPAT.h"

class CountProcessedEvents : public ntupleAnalysisPAT {
  public :

  CountProcessedEvents(TTree *tree=0);
    virtual ~CountProcessedEvents();
    virtual void     Loop();

    //print out the event information for events that pass our cuts
    //if the event is real data, print out extra information
};

#endif

#ifdef CountProcessedEvents_cxx

#endif // #ifdef CountProcessedEvents_cxx

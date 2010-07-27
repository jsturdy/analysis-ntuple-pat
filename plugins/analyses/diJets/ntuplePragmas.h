#include <map>
#include <vector>
#include <string>

#include <Math/LorentzVector.h>

//Thanks Ted

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzV;
typedef std::vector<LorentzV>                                     LorentzVs;
typedef std::map<std::string, bool>                               trigger_b;
typedef std::map<std::string, int>                                trigger_i;
typedef std::map<std::string, std::vector<float> >                jetcorrs;

#ifdef __CINT__

#pragma link C++ typedef  LorentzV;
#pragma link C++ typedef  LorentzVs;
#pragma link C++ typedef  trigger_b;
#pragma link C++ typedef  trigger_i;
#pragma link C++ typedef  jetcorrs;

//#pragma link C++ class    LorentzV+;
#pragma link C++ class    LorentzVs+;
#pragma link C++ class    trigger_b+;
#pragma link C++ class    trigger_i+;
#pragma link C++ class    jetcorrs+;

#pragma link C++ class    std::map<std::string,std::vector<float> >+;
#pragma link C++ class    std::map<std::string,bool>+;
#pragma link C++ class    std::map<std::string,int>+;
#pragma link C++ class    std::vector<TLorentzVector>+;

//#pragma link C++ class    std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >+;

//#pragma link C++ class    std::map<const std::string,std::vector<float> >+;
//#pragma link C++ class    std::map<const std::string,bool>+;
//#pragma link C++ class    std::map<const std::string,int>+;
//#pragma link C++ class    std::vector<const TLorentzVector>+;

#endif

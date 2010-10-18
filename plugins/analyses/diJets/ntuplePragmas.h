#include <map>
#include <vector>
#include <string>

#include <Math/LorentzVector.h>
#include "TLorentzVector.h"

//For some reason this is necessaray, would like to not have to include it
using namespace ROOT;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzP4;
typedef std::vector<LorentzP4>                                    LorentzP4s;
typedef std::map<std::string, bool>                               stringtobool;
typedef std::map<std::string, int>                                stringtoint;
typedef std::map<std::string, std::vector<float> >                stringtovfloat;

#ifdef __CINT__

#pragma link C++ typedef  LorentzP4;
#pragma link C++ typedef  LorentzP4s;
#pragma link C++ typedef  stringtobool;
#pragma link C++ typedef  stringtoint;
#pragma link C++ typedef  stringtovfloat;

#pragma link C++ class    LorentzP4s+;
#pragma link C++ class    LorentzP4s::iterator;
#pragma link C++ class    stringtobool+;
#pragma link C++ class    stringtobool::iterator;
#pragma link C++ class    std::pair<std::string,bool>+;
#pragma link C++ class    stringtovfloat+;
#pragma link C++ class    stringtovfloat::iterator;
#pragma link C++ class    std::pair<std::string,std::vector<float> >+;


#endif

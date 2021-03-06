#include <map>
#include <vector>
#include <string>

#include <Math/LorentzVector.h>
#include "TLorentzVector.h"

//For some reason this is necessaray, would like to not have to include it
using namespace ROOT;

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > LorentzP4V;
typedef std::vector<LorentzP4V>                                   LorentzP4Vs;
//typedef TLorentzVector                             LorentzP4V;
//typedef std::vector<LorentzP4V>                    LorentzP4Vs;
typedef std::map<std::string, bool>                stringtobool;
typedef std::map<std::string, int>                 stringtoint;
typedef std::map<std::string, std::vector<float> > stringtovfloat;

#ifdef __MAKECINT__

#pragma link C++ typedef  LorentzP4V;
#pragma link C++ typedef  LorentzP4Vs;
#pragma link C++ typedef  stringtobool;
#pragma link C++ typedef  stringtoint;
#pragma link C++ typedef  stringtovfloat;

#pragma link C++ class    LorentzP4Vs+;
#pragma link C++ class    LorentzP4Vs::iterator;
#pragma link C++ class    LorentzP4Vs::const_iterator;

#pragma link C++ class    stringtobool+;
#pragma link C++ class    stringtobool::iterator;
#pragma link C++ class    stringtobool::const_iterator;
#pragma link C++ class    std::pair<std::string,bool>+;
#pragma link C++ class    std::pair<const std::string,bool>+;

//#pragma link C++ class    stringtoint+;
//#pragma link C++ class    stringtoint::iterator;
//#pragma link C++ class    stringtoint::const_iterator;
//#pragma link C++ class    std::pair<std::string,int>+;
//#pragma link C++ class    std::pair<const std::string,int>+;

#pragma link C++ class    stringtovfloat+;
#pragma link C++ class    stringtovfloat::iterator;
#pragma link C++ class    stringtovfloat::const_iterator;
#pragma link C++ class    std::pair<std::string,std::vector<float> >+;
#pragma link C++ class    std::pair<const std::string,std::vector<float> >+;


#endif

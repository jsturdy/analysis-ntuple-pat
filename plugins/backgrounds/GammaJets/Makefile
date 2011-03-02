PROGNAME    = gammaJets.exe
SOURCEFILES = photonJets.cc gammaJets.cc ../../common/ntupleAnalysisPAT.cc
INCLUDES    = ../../common/ntuplePragmas.h photonJets.h ../../common/ntupleAnalysisPAT.h
OBJS        = $(patsubst %.cc, %.o, $(SOURCEFILES))

ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)


LDFLAGS       = -O
LIBS         += $(ROOTLIBS)
CFLAGS       += $(ROOTCFLAGS)# -Wall -pedantic -g3 -O0 -fno-inline

#  Not sure why Minuit isn't being included -- put in by hand
#
LIBS         += -lMinuit
LIBS    += -L$(CMSSW_RELEASE_BASE)/external/$(SCRAM_ARCH)/lib

#MyDict.cxx: $(HEADERS) ../LinkDef.h
#	rootcint -f $@ -c $(CXXFLAGS) -p $^
#
#libMyLib.so: MyDict.cxx $(SOURCES)
#	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^

###%Cint.cxx:Include.h ../LinkDef.h
###    rootcint -f $@ -c $^


%.o: %.cc
	g++ ${CFLAGS} -c -g -o $@ $<

$(PROGNAME):    $(OBJS) $(INCLUDES)
	g++ -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

clean:  
	-rm -f ${PROGNAME} ${OBJS}

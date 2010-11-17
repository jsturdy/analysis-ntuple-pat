PROGNAME    = METResolution.exe
SOURCEFILES = METResolutionStudy.cc METResolution.cc 
INCLUDES    = ../ntuplePragmas.h METResolutionStudy.h
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

%.o: %.cc
	g++ ${CFLAGS} -c -g -o $@ $<

$(PROGNAME):    $(OBJS) $(INCLUDES)
	g++ -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

clean:  
	-rm -f ${PROGNAME} ${OBJS}

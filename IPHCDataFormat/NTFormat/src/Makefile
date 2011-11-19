ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)

# Linux with egcs
DEFINES       = -DNO_ORCA_CLASSES
CXX           = g++
CXXFLAGS	= -O -Wall -fPIC $(DEFINES)
LD			= g++
LDFLAGS		= -g
SOFLAGS		= -shared

CXXFLAGS	+= $(ROOTCFLAGS)
#LIBS		= $(ROOTLIBS) 
LIBS		= -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -lGenVector
GLIBS		= $(ROOTGLIBS)
#------------------------------------------------------------------------------
SOURCES		= $(wildcard NT*.cc DisplayTool.cc MultiCollection.cc) 
HEADERS		= $(wildcard ../interface/NT*.h ../interface/KeyedCollection.h ../interface/MultiCollection.h ../interface/TransientData.h ../interface/DisplayTool.h) 
OBJECTS		= $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
DEPENDS		= $(SOURCES:.$(SrcSuf)=.d)
SOBJECTS	= $(SOURCES:.$(SrcSuf)=.$(DllSuf))


#PROGRAMS	=  $(SOBJECTS)

all: libNTuple.so; cp libNTuple.so ~/lib/.;
	@echo "Cleaning...";
	@rm -f $(OBJECTS) $(DEPENDS) *Dict.* core;

.SUFFIXES: .$(SrcSuf) .C .o .so

###

Dict.$(SrcSuf): $(HEADERS) ./LinkDef.h
	@echo "Generating dictionary Dict..."
	@$(ROOTSYS)/bin/rootcint -f Dict.$(SrcSuf) -c $(DEFINES) $(HEADERS) ./LinkDef.h

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) -c $<

libNTuple.so: $(OBJECTS) Dict.o
	$(LD) -L${ROOTSYS}/lib $(LIBS) $(SOFLAGS) $(LDFLAGS) $+ -o $@
	@echo "$@ done"

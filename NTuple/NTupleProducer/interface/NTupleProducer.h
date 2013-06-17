#ifndef __NTupleProducer_H__
#define __NTupleProducer_H__

// system include files
#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <TH1F.h>

//----------------- NTuple producer
#include "NTuple/NTupleProducer/interface/SkimTopDiLepton.h"
#include "NTuple/NTupleProducer/interface/FillNTuple.h"

//----------------- cmssw includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/Run.h>
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "JetMETCorrections/JetVertexAssociation/interface/JetVertexMain.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//--------------------PAT includes
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

//--------------------ROOT includes
#include "TTree.h"

//--------------------IPHC Tree includes
#include "IPHCDataFormat/NTFormat/interface/NTEvent.h"
#include "IPHCDataFormat/NTFormat/interface/NTSampleInfo.h"
#include "IPHCDataFormat/MTFormat/interface/MTEvent.h"

//--------------------STL includes
#include <vector>

#define ERROR(title)   edm::LogError(title)   << "[" << __FILE__ <<", line=" << __LINE__ <<"] "
#define WARNING(title) edm::LogWarning(title) << "[" << __FILE__ <<", line=" << __LINE__ <<"] "


// Class declaration ----------------------------------

class NTupleProducer:public edm::EDAnalyzer
{
public:
  explicit NTupleProducer (const edm::ParameterSet &);
   ~NTupleProducer ();

private:
  
  void   endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void beginJob ();
  virtual void analyze (const edm::Event &, const edm::EventSetup &);
  virtual void endJob ();
  bool FillSampleInfo(IPHCTree::NTSampleInfo* info);

  TTree *output;
  IPHCTree::NTEvent* ntuple;
  edm::Service<TFileService> fs;

  unsigned int verbose;
  std::vector<std::string> traceability; 

  TH1F * theNormHisto;
  TH1F * theNormHistoByTMEME;
  TH1F * numberOfEventsBeforeMTSkimmer;

  SkimTopDiLepton top_filter;
  FillNTuple ntuple_filler;

  unsigned long ntotal;
  unsigned long nfiltered;

};




#endif

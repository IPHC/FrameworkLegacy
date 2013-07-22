#ifndef __MiniTreeConfigSkimming_H__
#define __MiniTreeConfigSkimming_H__

#include "FWCore/ParameterSet/interface/ParameterSet.h"

typedef std::vector<edm::ParameterSet> VParameters;

struct ConfigSkimming
{

  // Extract MiniTreeProducer settings
  unsigned int  verbose;

  // Config. for lepton skimming
  edm::InputTag electron_collection;
  double        electron_cutPt;
  double        electron_cutEta;
  
  edm::InputTag muon_collection;
  double        muon_cutPt;
  double        muon_cutEta;
  
  unsigned int  minNumberOfLeptons;

  // Config. for jet skimming
  edm::InputTag jets_collection;
  double        jets_cutPt;
  double        jets_cutEta;
  
  unsigned int  minNumberOfJets;

};

#endif

#ifndef __NTUPLE_SkimTopDiLepton_H__
#define __NTUPLE_SkimTopDiLepton_H__

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


//----------------- cmssw includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/Run.h>
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

//--------------------ROOT includes
#include "TTree.h"

//--------------------TopTree includes
#include "IPHCDataFormat/NTFormat/interface/NTEvent.h"
#include "IPHCDataFormat/MTFormat/interface/MTEvent.h"

#include <vector>

#define ERROR(title)   edm::LogError(title) << "[" << __FILE__ <<", line=" << __LINE__ <<"] "
#define WARNING(title) edm::LogWarning(title) << "[" << __FILE__ <<", line=" << __LINE__ <<"] "


class SkimTopDiLepton
{
public:

  /// Constructor without arguments
  SkimTopDiLepton()
  { }

  /// Destructor
  virtual ~SkimTopDiLepton()
  { }

  /// Initialize
  virtual bool Initialize(const edm::ParameterSet& parameters);

  /// Filter
  virtual bool Filter(const IPHCTree::NTEvent* event);

 private:

  int GetNumberOfIDMuons(const IPHCTree::NTEvent* event);
  int GetNumberOfMuons(const IPHCTree::NTEvent* event);
  int GetNumberOfIDElectrons(const IPHCTree::NTEvent* event);
  int GetNumberOfElectrons(const IPHCTree::NTEvent* event);
  int GetNumberOfTaus(const IPHCTree::NTEvent* event);
  int GetNumberOfJets(const IPHCTree::NTEvent* event);

  int numberOfLept;

  int numberOfMuon;
  bool useMuonIdSkim;
  double muon_cut_pt;
  double muon_cut_iso;

  int numberOfElec;
  bool useElectronIdSkim;
  double electron_cut_pt;
  double electron_cut_iso;

  bool doTMEMESkimming;
  std::vector<int> TMEMESkimList;
  bool doMCDiLepSkimming;
  std::vector<string> MCDiLepList;

  bool doTriggerSkimming;
  std::vector<std::string> triggerSkimList;

  bool doTauSkimming;
  int numberOfTau;
  double tau_cut_pt;
  std::string tau_algo;

  bool doJetSkimming;
  int numberOfJet;
  double jet_cut_pt;
  double jet_cut_eta;
  std::string jet_algo;
  
};

#endif

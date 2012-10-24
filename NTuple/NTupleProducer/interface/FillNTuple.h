#ifndef __NTUPLE_FillNTuple_H__
#define __NTUPLE_FillNTuple_H__

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


class FillNTuple
{
public:

  /// Constructor without arguments
  FillNTuple()
  { }

  /// Destructor
  virtual ~FillNTuple()
  { }

  /// Initialize
  virtual bool Initialize(const edm::ParameterSet& parameters);

  /// Filter
  virtual void Fill(const IPHCTree::MTEvent* minitree, IPHCTree::NTEvent* ntuple);

 private:

  unsigned int verbose;

  // Muon
  bool                     skimTrigger;
  std::vector<std::string> triggerList;

  // Monte Carlo
  bool                     skimGenParticles;
  bool                     skimGenTaus;

  // Muon
  bool                     skimMuons;
  bool                     muon_keepAllCollections;
  std::vector<std::string> muon_collectionList;
  double                    muon_pt;
  double                    muon_eta;
  int    numberOfMuon;
  bool   useMuonId;
  double muon_cut_iso;

  // Electron
  bool                     skimElectrons;
  bool                     electron_keepAllCollections;
  std::vector<std::string> electron_collectionList;
  double                    electron_pt;
  double                    electron_eta;
  bool   useElectronId;
  double electron_iso;
  int    numberOfElec;

  // Photon
  bool                     skimPhotons;
  bool                     photon_keepAllCollections;
  std::vector<std::string> photon_collectionList;
  double                    photon_pt;
  double                    photon_eta;

  // Tau
  bool                     skimTaus;
  bool                     tau_keepAllCollections;
  std::vector<std::string> tau_collectionList;
  double                    tau_pt;
  double                    tau_eta;
  int    tau_N;
  
  // Jet
  bool                     skimJets;
  bool                     jet_keepAllCollections;
  std::vector<std::string> jet_collectionList;
  double                    jet_pt;
  double                    jet_eta;
  int numberOfJet4Skim;


  // Tracks
  bool                     skimTracks;
  bool                     track_keepAllCollections;
  std::vector<std::string> track_collectionList;
  double                    track_pt;
  double                    track_eta;

  // PFCandidates
  bool						skimPFCandidates;
  bool						pfcandidate_keepAllCollections;
  std::vector<std::string>  pfcandidate_collectionList;
  double					pfcandidate_pt;
  double					pfcandidate_eta;

  // Vertices
  bool                     skimVertices;
  bool                     vertex_keepAllCollections;
  std::vector<std::string> vertex_collectionList;
  
};

#endif


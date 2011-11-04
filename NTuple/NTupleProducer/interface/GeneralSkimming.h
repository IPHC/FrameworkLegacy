#ifndef __NTupleGeneralSkimmingType_H__
#define __NTupleGeneralSkimmingType_H__

#include "FWCore/ParameterSet/interface/ParameterSet.h"

typedef std::vector<edm::ParameterSet> VParameters;

struct GeneralSkimming
{
  // Lepton
  int numberOfLept;

  // Muon
  bool                     skimTrigger;
  std::vector<std::string> triggerList;

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

  // Vertices
  bool                     skimVertices;
  bool                     vertex_keepAllCollections;
  std::vector<std::string> vertex_collectionList;

  // TMEME
  bool doTMEME;
  std::vector<int> TMEME;

  // Dilepton skimming
  bool doMCDiLep;
  std::vector<std::string> MCDiLepList; 

 
};

#endif

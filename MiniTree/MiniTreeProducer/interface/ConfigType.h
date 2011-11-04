#ifndef __MiniTreeConfigType_H__
#define __MiniTreeConfigType_H__

#include "FWCore/ParameterSet/interface/ParameterSet.h"

typedef std::vector<edm::ParameterSet> VParameters;

struct ConfigType
{
  // Extract MiniTreeProducer settings
  unsigned int  verbose;
  bool          isAOD; 
  bool          isData; 

  // Extract info for Triggers
  bool          doTrigger;
  bool	        saveAllTriggers;
  std::string   hltJetsMatcher;
  std::vector<std::string> triggerList;

  // Extract info for Electrons
  bool          doElectrons;
  double	      electron_cut_pt;
  double	      electron_cut_eta;
  bool          electron_saveAllID;
  std::vector<std::string> electronHLTmatching;
  std::vector<std::string> electron_IDlist;
  std::vector<edm::InputTag> electronProducer;

  // Extract info for Photons
  bool 	       	doPhotons;
  double	      photon_cut_pt;
  double	      photon_cut_eta;
  std::vector<std::string> photonHLTmatching;
  std::vector<edm::InputTag> photonProducer;

  // Extract info for Muons
  bool 		      doMuons;
  double        muon_cut_pt;
  double 	      muon_cut_eta;
  bool          muon_cut_sta;
  bool          muon_cut_trk;
  bool          muon_cut_glb;
  bool          muon_cut_cal;
  std::vector<std::string> muonHLTmatching;
  std::vector<std::string> muon_IDlist;
  std::vector<edm::InputTag>  muonProducer;

  // Extract info for Taus
  bool     		  doTaus;
  double        tau_cut_pt;
  double 	      tau_cut_eta;
  bool          tau_saveAllID;
  std::vector<std::string> tauHLTmatching;
  std::vector<std::string> tau_IDlist;
  std::vector<edm::InputTag> tauProducer;

  // Extract info for Tracks
  bool          doTracks;
  double	      track_cut_pt;
  double	      track_cut_eta;
  std::vector<edm::InputTag>      trackProducer; 

  // Extract info for Vertices
  bool          doVertices;
  bool		      saveAllVertex;
  std::vector<edm::InputTag>      vertexProducer;

  // Extract info for BeamSpot
  bool          doBeamSpot; 
  edm::InputTag	beamSpotProducer; 

  // Extract info for JetMET
  bool          doJetMet;
  bool          doMuonCorrection;
  double 	      jet_cut_pt;
  double 	      jet_cut_eta;
  std::vector<std::string> jetBTagList;
  std::vector<std::string> jetHLTmatching;
  VParameters   jetmetProducer;

  // Extract info for Pile-Up
  bool           doPileUp; 
  edm::InputTag	 rho_PUUE_dens;
  edm::InputTag	 neutralRho_PUUE_dens;

  // Extract info for Monte Carlo
  bool 	      	doGenParticleCollection;
  unsigned int  mcDescentMax;
  unsigned int  mcNGenPartMax;
};

#endif
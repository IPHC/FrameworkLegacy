#include "../interface/Event.h"


// ----------------------------------------------------------------------------
// Copy constructor
// ----------------------------------------------------------------------------
Event::Event(const Event& evt)
{
  general_   = evt.general_;
  mc_        = evt.mc_;
  pileup_    = evt.pileup_;
  trigger_   = evt.trigger_;
  jetmet_    = evt.jetmet_;
  photons_   = evt.photons_;
  electrons_ = evt.electrons_;
  muons_     = evt.muons_;
  taus_      = evt.taus_;
  tracks_    = evt.tracks_; 
  vertices_  = evt.vertices_; 
 
  PhotonType_   = evt.PhotonType_;
  JetMetType_   = evt.JetMetType_;
  ElectronType_ = evt.ElectronType_;
  MuonType_     = evt.MuonType_;
  TauType_      = evt.TauType_;
  TrackType_    = evt.TrackType_;
  VertexType_   = evt.VertexType_;
}


// ----------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void Event::Reset()
{
  general_   = 0;
  mc_        = 0;
  pileup_    = 0;
  trigger_   = 0;
  photons_   = 0;
  jetmet_    = 0;
  electrons_ = 0;
  muons_     = 0;
  taus_      = 0;
  tracks_    = 0; 
  vertices_  = 0; 
 
  PhotonType_   = "";
  JetMetType_   = "";
  ElectronType_ = "";
  MuonType_     = "";
  TauType_      = "";
  TrackType_    = "";
  VertexType_   = "";
}


// ----------------------------------------------------------------------------
// LoadEvent
// ----------------------------------------------------------------------------
void Event::LoadEvent(const IPHCTree::NTEvent* evt)
{
  // general info
  general_ = &(evt->general);
  mc_      = &(evt->mc);
  trigger_ = &(evt->trigger);
  pileup_  = &(evt->pileup);

  // get only one photon collection 
  photons_ = evt->photons.GetCollection(PhotonType_);
  if(photons_==0) std::cerr<<"The photon collection was not found !"<<std::endl;

  // get only one JetMet collection 
  jetmet_ = evt->jetMet.GetCollection(JetMetType_);
  if(jetmet_==0) std::cerr<<"The jet collection was not found !"<<std::endl;

  // get only one electron collection 
  electrons_ = evt->electrons.GetCollection(ElectronType_);
  if(electrons_==0) std::cerr<<"The electron collection was not found !"<<std::endl;

  // get only one muon collection 
  muons_ = evt->muons.GetCollection(MuonType_);
  if(muons_==0) std::cerr<<"The muon collection was not found !"<<std::endl;

  // get only one tau collection 
  taus_ = evt->taus.GetCollection(TauType_);
  if(taus_==0) std::cerr<<"The tau collection was not found !"<<std::endl;

  // get only one track collection 
  tracks_ = evt->tracks.GetCollection(TrackType_); 
  if(tracks_==0) std::cerr<<"The track collection was not found !"<<std::endl;

  // get only one vertex collection 
  vertices_ = evt->vertices.GetCollection(VertexType_); 
  if(vertices_==0) std::cerr<<"The vertex collection was not found !"<<std::endl;

}

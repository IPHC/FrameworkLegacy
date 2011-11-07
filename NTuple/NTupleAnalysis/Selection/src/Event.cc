#include "Selection/interface/Event.h"


// ----------------------------------------------------------------------------
// Copy constructor
// ----------------------------------------------------------------------------
Event::Event(const Event& evt)
{
  general_   = evt.general_;
  mc_        = evt.mc_;
  pileup_    = evt.pileup_;
  trigger_   = evt.trigger_;
  jets_      = evt.jets_;
  met_       = evt.met_;
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
  jets_      = 0;
  met_       = 0;
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
bool Event::LoadEvent(const IPHCTree::NTEvent* evt)
{
  // safety : input pointer is null ?
  if (evt==0)
  {
    std::cerr << "The pointer to NTuple event is null !!!!" << std::endl;
    return false; 
  }

  // Declaring indicator for the success of event reading
  bool success=true;

  // general info
  general_ = &(evt->general);
  mc_      = &(evt->mc);
  trigger_ = &(evt->trigger);
  pileup_  = &(evt->pileup);

  // get only one photon collection 
  photons_ = evt->photons.GetCollection(PhotonType_);
  if(photons_==0)
  {
    success=false;
    std::cerr<<"The photon collection was not found !"<<std::endl;
  }

  // get only one Jet collection 
  jets_ = evt->jets.GetCollection(JetMetType_);
  if(jets_==0)
  {
    success=false;
    std::cerr<<"The jet collection was not found !"<<std::endl;
  }

  // get only one Met collection 
  const std::vector<IPHCTree::NTMET>* mets = 
                                  evt->met.GetCollection(JetMetType_);
  if(mets==0)
  {
    success=false;
    std::cerr<<"The MET was not found !"<<std::endl;
  }
  else
  {
    met_ = &((*mets)[0]);
  }

  // get only one electron collection 
  electrons_ = evt->electrons.GetCollection(ElectronType_);
  if(electrons_==0)
  {
    success=false;
    std::cerr<<"The electron collection was not found !"<<std::endl;
  }

  // get only one muon collection 
  muons_ = evt->muons.GetCollection(MuonType_);
  if(muons_==0)
  {
    success=false;
    std::cerr<<"The muon collection was not found !"<<std::endl;
  }

  // get only one tau collection 
  taus_ = evt->taus.GetCollection(TauType_);
  if(taus_==0)
  {
    success=false;
    std::cerr<<"The tau collection was not found !"<<std::endl;
  }

  // get only one track collection 
  tracks_ = evt->tracks.GetCollection(TrackType_); 
  if(tracks_==0)
  {
    success=false;
    std::cerr<<"The track collection was not found !"<<std::endl;
  }

  // get only one vertex collection 
  vertices_ = evt->vertices.GetCollection(VertexType_); 
  if(vertices_==0)
  {
    success=false;
    std::cerr<<"The vertex collection was not found !"<<std::endl;
  }

  return success;

}

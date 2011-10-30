#ifndef IPHC_Event_h
#define IPHC_Event_h

// IPHC headers
#include "../../../../IPHCDataFormat/NTFormat/interface/NTEvent.h"

// STL headers
#include <memory>
#include <vector>
#include <string>

//! \class Event
class Event
{

  // -------------------------------------------------------------
  //                       method members
  // -------------------------------------------------------------
 public:

  //! Constructor without argument
  Event() 
  { Reset(); }

  //! Copy constructor
  Event(const Event&);

  //! Destructor
  ~Event()
  {}
   
  //! Clear collections but parameters are cleared
  void Reset();

  //! Collections of objects are updated
  void LoadEvent(const IPHCTree::NTEvent*event);


  // ------------- accessor to collection ( copy ) ---------------

  //! Get a copy of the vertex collection
  std::vector<IPHCTree::NTVertex> GetVertex() const
  { if (vertices_!=0) return (*vertices_); 
    else return std::vector<IPHCTree::NTVertex>(); }

  //! Get a copy of the track collection
  std::vector<IPHCTree::NTTrack> GetTracks() const
  { if (tracks_!=0) return (*tracks_); 
    else return std::vector<IPHCTree::NTTrack>(); }

  //! Get a copy of the photon collection
  std::vector<IPHCTree::NTPhoton> GetPhotons() const
  { if (photons_!=0) return (*photons_); 
    else return std::vector<IPHCTree::NTPhoton>(); }

  //! Get a copy of the jet collection
  std::vector<IPHCTree::NTJet> GetJets() const
  { if (jetmet_!=0) return (*jetmet_)[0].jets; 
    else return std::vector<IPHCTree::NTJet>(); }

  //! Get a copy of the electron collection
  std::vector<IPHCTree::NTElectron> GetElectrons() const
  { if (electrons_!=0) return (*electrons_); 
    else return std::vector<IPHCTree::NTElectron>(); }

  //! Get a copy of the muon collection
  std::vector<IPHCTree::NTMuon> GetMuons() const   
  { if (muons_!=0) return (*muons_); 
    else return std::vector<IPHCTree::NTMuon>(); }

  //! Get a copy of the tau collection
  std::vector<IPHCTree::NTTau> GetTaus() const   
  { if (taus_!=0) return (*taus_); 
    else return std::vector<IPHCTree::NTTau>(); }

  //! Get a copy of the GenTaus collection
  std::vector<TLorentzVector> GetGenTaus() const
  { if (mc_!=0) return mc_->Generatedtaus; 
    else return std::vector<TLorentzVector>(); }

  //! Get a copy of the GenATaus collection
  std::vector<TLorentzVector> GetGenATaus() const
  { if (mc_!=0) return mc_->GeneratedAtaus; 
    else return std::vector<TLorentzVector>(); }


  // ------------- accessor to collection (pointer) --------------

  //! Get a const pointer to the vertex collection
  const std::vector<IPHCTree::NTVertex>* GetPointer2Vertex() const
  { return vertices_; }

  //! Get a const pointer to the track collection
  const std::vector<IPHCTree::NTTrack>* GetPointer2Tracks() const
  { return tracks_; }

  //! Get a const pointer to the photon collection
  const std::vector<IPHCTree::NTPhoton>* GetPointer2Photons() const
  { return photons_; }

  //! Get a const pointer to the jet collection
  const std::vector<IPHCTree::NTJet>* GetPointer2Jets() const
  { if (jetmet_==0) return 0;
    else return &((*jetmet_)[0].jets); }

  //! Get a const pointer to the electron collection
  const std::vector<IPHCTree::NTElectron>* GetPointer2Electrons() const
  { return electrons_; }

  //! Get a const pointer to the muon collection
  const std::vector<IPHCTree::NTMuon>* GetPointer2Muons() const   
  { return muons_; }

  //! Get a const pointer to the tau collection
  const std::vector<IPHCTree::NTTau>* GetPointer2Taus() const   
  { return taus_; }

  //! Get a const pointer to the GenTaus collection
  const std::vector<TLorentzVector>* GetPointer2GenTaus() const
  { if(mc_!=0) return &(mc_->Generatedtaus); 
    else return 0; }

  //! Get a const pointer to the GenATaus collection
  const std::vector<TLorentzVector>* GetPointer2GenATaus() const
  { if (mc_!=0) return &(mc_->GeneratedAtaus); 
    else return 0; }


  // ------------- mutator to collection labels ------------------

  //! Initialize the JetMet collection label
  void SetJetMetCollectionLabel(const std::string& label)
  { JetMetType_=label; }

  //! Initialize the photon collection label
  void SetPhotonCollectionLabel(const std::string& label)
  { PhotonType_=label; }

  //! Initialize the electron collection label
  void SetElectronCollectionLabel(const std::string& label)
  { ElectronType_=label; }

  //! Initialize the muon collection label
  void SetMuonCollectionLabel(const std::string& label)
  { MuonType_=label; }

  //! Initialize the tau collection label
  void SetTauCollectionLabel(const std::string& label)
  { TauType_=label; }

  //! Initialize the track collection label
  void SetTrackCollectionLabel(const std::string& label)
  { TrackType_=label; }

  //! Initialize the vertex collection label
  void SetVertexCollectionLabel(const std::string& label)
  { VertexType_=label; }


  // ------------- acessor to collection labels ------------------

  //! Access to the JetMet collection label
  std::string GetJetMetCollectionLabel() const
  { return JetMetType_; }

  //! Access to the photon collection label
  std::string GetPhotonCollectionLabel() const
  { return PhotonType_; }

  //! Access to the electron collection label
  std::string GetElectronCollectionLabel() const
  { return ElectronType_; }

  //! Access to the muon collection label
  std::string GetMuonCollectionLabel() const
  { return MuonType_; }

  //! Access to the tau collection label
  std::string GetTauCollectionLabel() const
  { return TauType_; }

  //! Access to the track collection label
  std::string GetTrackCollectionLabel() const
  { return TrackType_; }

  //! Access to the vertex collection label
  std::string GetVertexCollectionLabel() const
  { return VertexType_; }


  // -------------------------------------------------------------
  //                        data members
  // -------------------------------------------------------------
 private:

  const IPHCTree::NTGeneral*               general_;
  const IPHCTree::NTMonteCarlo*            mc_;
  const IPHCTree::NTTrigger*               trigger_;
  const IPHCTree::NTPileUp*                pileup_;
  const std::vector<IPHCTree::NTJetMet>*   jetmet_;
  const std::vector<IPHCTree::NTPhoton>*   photons_;
  const std::vector<IPHCTree::NTElectron>* electrons_;
  const std::vector<IPHCTree::NTMuon>*     muons_;
  const std::vector<IPHCTree::NTTau>*      taus_;
  const std::vector<IPHCTree::NTTrack>*    tracks_; 
  const std::vector<IPHCTree::NTVertex>*   vertices_; 
 
  std::string PhotonType_;
  std::string JetMetType_;
  std::string ElectronType_;
  std::string MuonType_;
  std::string TauType_;
  std::string TrackType_;
  std::string VertexType_;

};

#endif

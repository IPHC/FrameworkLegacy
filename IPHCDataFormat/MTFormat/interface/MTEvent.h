#ifndef __IPHC_TREE_MTEVENT_H__
#define __IPHC_TREE_MTEVENT_H__

// STL headers
#include <string>
#include <vector>
#include <map>

// IPHC headers (Ntuple format)
#include "../../NTFormat/interface/MultiCollection.h"
#include "../../NTFormat/interface/NTGeneral.h"
#include "../../NTFormat/interface/NTTrack.h"
#include "../../NTFormat/interface/NTTrigger.h"
#include "../../NTFormat/interface/NTMonteCarlo.h"
#include "../../NTFormat/interface/TransientData.h"

// IPHC headers 
#include "MTJet.h"
#include "MTElectron.h"
#include "MTPhoton.h"
#include "MTMuon.h"
#include "MTTau.h"
#include "MTMET.h"
#include "MTJetMet.h"
#include "MTVertex.h"
#include "MTMonteCarlo.h"
#include "MTPileUp.h"
#include "MTBeamSpot.h"


namespace IPHCTree
{
  //! \class MTEvent
  //! Main class stored in the MiniTree
  //! It contains leptons, Jet/MET collections, tracks, PV, BS, triggers,
  //! event info, detailled MC info are stored.
  class MTEvent
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    NTGeneral    general; //! General information about the event
    NTTrigger    trigger; //! Trigger information
    MTMonteCarlo mc;      //! Monte Carlo information
    MTPileUp     pileup;  //! Pile-Up information

    MultiCollection<MTElectron> electrons; //! Electron collection
    MultiCollection<MTMuon>     muons;     //! Muon collection
    MultiCollection<MTTau>      taus;      //! Tau collection
    MultiCollection<MTPhoton>   photons;	 //! Photon collection
    MultiCollection<MTMET>      met;       //! Met collection (only one)
    MultiCollection<MTJet>      jets;      //! Jet collection

    MultiCollection<NTTrack>    tracks;    //! Track collection
    MultiCollection<MTVertex>   vertices;  //! Primary vertex collection
    MTBeamSpot                  beamSpot;  //! Beam Spot

    KeyedCollection<Float_t>    others;    //! Additionnal variables

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without argument
    MTEvent()
    { }

		//! Destructor
    ~MTEvent()
    { }

		//! Reset all event information
    void Reset();

		//! Display information related to the event
    //! \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    // methods to instanciate a new object
    MTElectron* NewElectron()
    { return electrons.New(); }

    MTPhoton* NewPhoton()
    { return photons.New(); }

    MTMuon* NewMuon()
    { return muons.New(); }

    MTTau* NewTau()
    { return taus.New(); }

    MTVertex* NewVertex()
    { return vertices.New(); }

    MTJet* NewJet()
    { return jets.New(); }

    MTMET* NewMet()
    { return met.New(); }

    NTTrack* NewTrack()
    { return tracks.New(); }

    // methods to instanciate a new object
    void NewElectron (const MTElectron& electron)
    { electrons.push_back(electron); }

    void NewPhoton   (const MTPhoton& photon  )
    { photons.push_back(photon); }

    void NewMuon     (const MTMuon&  muon    )
    { muons.push_back(muon); }

    void NewTau      (const MTTau& tau     )
    { taus.push_back(tau); }

    void NewVertex   (const MTVertex& vertex  )
    { vertices.push_back(vertex); }

    void NewTrack    (const MTTrack& track   )
    { tracks.push_back(track); }

    void NewJet      (const MTJet& myjet  )
    { jets.push_back(myjet); }

    void NewMET      (const MTMET& mymet  )
    { met.push_back(mymet); }

  };
}
#endif


#ifndef __IPHC_TREE_NTEVENT_H__
#define __IPHC_TREE_NTEVENT_H__

// STL headers
#include <iostream>
#include <string>
#include <vector>

// IPHC headers
#include "NTMET.h"
#include "NTJet.h"
#include "NTElectron.h"
#include "NTPhoton.h"
#include "NTMuon.h"
#include "NTTau.h"
#include "NTVertex.h"
#include "NTTrack.h"
#include "NTPFCandidate.h"
#include "NTTrigger.h"
#include "NTGeneral.h"
#include "NTMonteCarlo.h"
#include "NTPileUp.h"
#include "KeyedCollection.h"
#include "MultiCollection.h"
#include "NTEventDescriptor.h"
#include "NTTransient.h"

namespace IPHCTree
{

  class NTTransient;

  /// \class NTEvent
  /// main class stored in the NTuple.
  /// Selected objects [leptons, Jet/MET collections, tracks, PV, BS],
  /// triggers, event info, basic MC info are stored.
  /// Useless information might be deleted to keep the size of the
  /// NTuple reasonnable. Addtional information could be found in the MiniTree
  class NTEvent
  {
    friend class NTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    NTGeneral    general; /// General information about the event
    NTPileUp     pileup;  /// Pile-Up information
    NTMonteCarlo mc;      /// Monte Carlo information
    NTTrigger    trigger; /// Trigger information

    MultiCollection<NTElectron> electrons; /// Electron collection
    MultiCollection<NTMuon>     muons;     /// Muon collection
    MultiCollection<NTTau>      taus;      /// Tau collection
    MultiCollection<NTPhoton>   photons;	 /// Photon collection
    MultiCollection<NTMET>      met;       /// Met collection (only one)
    MultiCollection<NTJet>      jets;      /// Jet collection

    MultiCollection<NTTrack>    tracks;    /// Track collection
    MultiCollection<NTPFCandidate>    pfcandidates;    /// PFCandidate collection
    MultiCollection<NTVertex>   vertices;  /// Primary vertex collection

    KeyedCollection<Float_t>    others;    /// Additionnal variables

  protected :

    NTEventDescriptor           descriptor; /// Info related to variables name

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:
  
    /// Constructor without argument
    NTEvent()
    { }

		/// Destructor
    ~NTEvent()
    { }

		/// Reset all event information
    void Reset();

		/// Display information related to the event
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    // methods to instanciate a new object
    NTElectron* NewElectron()
    { return electrons.New(); }

    NTPhoton* NewPhoton()
    { return photons.New(); }

    NTMuon* NewMuon()
    { return muons.New(); }

    NTTau* NewTau()
    { return taus.New(); }

    NTVertex* NewVertex()
    { return vertices.New(); }

    NTJet* NewJet()
    { return jets.New(); }

    NTMET* NewMet()
    { return met.New(); }

    NTTrack* NewTrack()
    { return tracks.New(); }

    NTPFCandidate* NewPFCandidate()
    { return pfcandidates.New(); }

    // methods to instanciate a new object
    void NewElectron (const NTElectron& electron)
    { electrons.push_back(electron); }

    void NewPhoton   (const NTPhoton& photon  )
    { photons.push_back(photon); }

    void NewMuon     (const NTMuon&  muon    )
    { muons.push_back(muon); }

    void NewTau      (const NTTau& tau     )
    { taus.push_back(tau); }

    void NewVertex   (const NTVertex& vertex  )
    { vertices.push_back(vertex); }

    void NewTrack    (const NTTrack& track   )
    { tracks.push_back(track); }

    void NewPFCandidate		(const NTPFCandidate& pfcandidate   )
    { pfcandidates.push_back(pfcandidate); }

    void NewJet      (const NTJet& myjet  )
    { jets.push_back(myjet); }

    void NewMet      (const NTMET& mymet  )
    { met.push_back(mymet); }


  };
}

#endif

#ifndef __IPHC_TREE_NTEVENT_H__
#define __IPHC_TREE_NTEVENT_H__

// STL headers
#include <iostream>
#include <string>
#include <vector>

// IPHC headers
#include "NTElectron.h"
#include "NTPhoton.h"
#include "NTMuon.h"
#include "NTTau.h"
#include "NTJetMet.h"
#include "NTVertex.h"
#include "NTTrack.h"
#include "NTTrigger.h"
#include "NTGeneral.h"
#include "NTMonteCarlo.h"
#include "NTPileUp.h"
#include "KeyedCollection.h"
#include "MultiCollection.h"
#include "TransientData.h"


namespace IPHCTree
{

  //! \class NTEvent
  //! main class stored in the NTuple.
  //! Selected objects [leptons, Jet/MET collections, tracks, PV, BS],
  //! triggers, event info, basic MC info are stored.
  //! Useless information might be deleted to keep the size of the
  //! NTuple reasonnable. Addtional information could be found in the MiniTree
  class NTEvent
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    NTGeneral    general; //! General information about the event
    NTMonteCarlo mc;      //! Monte Carlo information
    NTTrigger    trigger; //! Trigger information
    NTPileUp     pileup;  //! Pile-Up information

    MultiCollection<NTElectron> electrons; //! Electron collection
    MultiCollection<NTMuon>     muons;     //! Muon collection
    MultiCollection<NTTau>      taus;      //! Tau collection
    MultiCollection<NTPhoton>   photons;	 //! Photon collection
    MultiCollection<NTJetMet>   jetMet;    //! JetMet collection

    MultiCollection<NTTrack>    tracks;    //! Track collection
    MultiCollection<NTVertex>   vertices;  //! Primary vertex collection

    KeyedCollection<Float_t>    others;    //! Additionnal variables

  private :
    TransientData               transient; //! Handle transient data

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without argument
    NTEvent()
    { }

		//! Destructor
    ~NTEvent()
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

    NTJetMet* NewJetMet()
    { return jetMet.New(); }

    NTTrack* NewTrack()
    { return tracks.New(); }


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

    void NewJetMet   (const NTJetMet& jetmet  )
    { jetMet.push_back(jetmet); }

    void PrintTriggerPassed(std::ostream & os) const
    {
      /*      os << "Triggers passed : ";
      for(unsigned int i=0;i<triggers.size();i++)
      {
        if(triggers[i].second) os << triggers[i].first << " ";
      }
      os <<endl;*/
    }

    void PrintTriggerList(std::ostream & os) const
    {
      /*      os << "List of triggers"<<endl;
      for(unsigned int i=0;i<triggers.size();i++)
      {
        os << triggers[i].first << " ";
      }
      os << endl;*/
    }

    bool TriggerPassed(std::string trigName) const
    {
      /*      for(unsigned int i=0;i<triggers.size();i++)
      {
        if(triggers[i].first == trigName)
          return triggers[i].second;
          }*/
      return false;
    }

    bool TriggerStored(std::string trigName) const
    {
      /*      for(unsigned int i=0;i<triggers.size();i++)
      {
        if(triggers[i].first == trigName)
          return true;
          }*/
      return false;
    }


  };
}

#endif

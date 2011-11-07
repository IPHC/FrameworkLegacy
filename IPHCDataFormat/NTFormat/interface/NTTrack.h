#ifndef __IPHC_TREE_NTTRACK_H__
#define __IPHC_TREE_NTTRACK_H__

// STL headers
#include <iostream>

// ROOT headers
#include "TLorentzVector.h"


namespace IPHCTree
{

  class NTTransient;
  class MTTransient;

  // \class NTTrack
  // class related to recoTrack for NTuple.
  class NTTrack
  {
    friend class IPHCTree::NTTransient;
    friend class IPHCTree::MTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// 4-vector momentum
    TLorentzVector p4;

    /// electric charge (transient)
    mutable Float_t charge; //! TRANSIENT

    /// normalized chi2
    Float_t chi2;

    /// number of valid hits in the tracker
    UInt_t nHitTracker;

    /// transverse impact parameter wrt to (0,0,0)
    /// ONLY if refPoint is close to (0,0,0)
    Float_t dxy;

    /// transverse impact parameter wrt to the beam spot
    /// Warning : only be interpreted as a minimum transverse
    /// distance if the beam spot is reasonably clost to the refPoint
    Float_t dxy_BS;

    /// error on transverse impact parameter
    Float_t dxyError;

    /// track z0 wrt (0,0,0) only if the refPoint is close to (0,0,0)
    /// = dsz/cos(lambda) 
    Float_t dz;

    /// error on dz
    Float_t dzError;

  protected :

    /// electric charge (persistent)
    Bool_t charge_bit_;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTTrack()
    { Reset(true); }

    /// Destructor
    ~NTTrack ()
    { }

		/// Clear all information related to the track
    void Reset(bool constructor_call=false);

		/// Display information related to the track
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Access to d0 track parameter
    const Float_t d0() const
    { return -dxy; }

    /// Access to the error on d0 track parameter
    const Float_t d0Error() const
    { return dxyError; }
  
  };
}
#endif

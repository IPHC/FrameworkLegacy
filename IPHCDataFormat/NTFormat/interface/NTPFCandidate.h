#ifndef __IPHC_TREE_NTPFCANDIDATE_H__
#define __IPHC_TREE_NTPFCANDIDATE_H__

// STL headers
#include <iostream>

// Include NTTrack header
#include "NTTrack.h"

// ROOT headers
#include "TLorentzVector.h"

// IPHC headers
#include "KeyedCollection.h"

namespace IPHCTree
{

  class NTTransient;
  class MTTransient;

  // \class NTPFCandidate
  // class related to PFCandidates for NTuple.
  class NTPFCandidate : public NTTrack
  {
    friend class IPHCTree::NTTransient;
    friend class IPHCTree::MTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// dz w.r.t. "first good vertex"
    float dz_firstGoodVertex;

    /// track (of the PFCandidate) isolation w.r.t. other tracks
    float trackIso;

    /// Container for adding easly variables without changing dataformat code
    KeyedCollection<Float_t> others;

	// -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------

  public:

    /// Constructor without arguments
    NTPFCandidate()
    { Reset(true); }

    /// Destructor
    ~NTPFCandidate ()
    { }

	/// Clear all information related to the track
    void Reset(bool constructor_call=false);

	/// Display information related to the PFCandidate
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

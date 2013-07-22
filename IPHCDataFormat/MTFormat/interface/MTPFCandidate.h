
#ifndef __IPHC_TREE_MTPFCANDIDATE_H__
#define __IPHC_TREE_MTPFCANDIDATE_H__

// IPHC headers (Ntuple format)
#include "../../NTFormat/interface/NTPFCandidate.h"

namespace IPHCTree
{

  /// \class MTPFCandidate
  /// class PFCandidate for MiniTree - inherit from NTPFCandidate
  /// Contains nHits for subdectectors and IPs.
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTPFCandidate : public NTPFCandidate
  {

  public:

    /// Constructor without arguments
    MTPFCandidate ()
    { Reset(true); }

    /// Destructor
    virtual ~MTPFCandidate ()
    { }

	/// Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

	/// Display information related to the lepton
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

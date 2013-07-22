#ifndef __IPHC_TREE_MTTau_H__
#define __IPHC_TREE_MTTau_H__

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTTau.h"

// IPHC headers
#include "MTLepton.h"


namespace IPHCTree
{

  /// \class MTTau
  /// class tau for MiniTree - inherit from NTTau
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTTau : public NTTau, public MTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTTau()
    { Reset(true); }

    /// Destructor
    virtual ~MTTau()
    { }

		/// Clear all information related to the tau
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the tau
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

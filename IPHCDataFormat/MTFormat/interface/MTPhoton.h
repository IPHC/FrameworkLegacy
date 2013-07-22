#ifndef __IPHC_TREE_MTPHOTON_H__
#define __IPHC_TREE_MTPHOTON_H__

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTPhoton.h"

namespace IPHCTree
{

  /// \class MTPhoton
  /// This is an extension of NTPhoton
  class MTPhoton : public NTPhoton
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
    MTPhoton ()
    { Reset(true); }

    /// Destructor
    virtual ~MTPhoton ()
    { }

    /// Clear all information related to the photon
    virtual void Reset(bool constructor_call);
    
    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

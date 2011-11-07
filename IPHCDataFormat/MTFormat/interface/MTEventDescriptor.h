#ifndef __IPHC_TREE_MTEventDescriptor_H__
#define __IPHC_TREE_MTEventDescriptor_H__

// STL headers
#include <iostream>
#include <string>
#include <set>

// ROOT headers
#include <TROOT.h>

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTEventDescriptor.h"


namespace IPHCTree
{

  /// \class MTEventDescriptor
  /// MTEventDescriptor contains all information about event id
  class MTEventDescriptor : public NTEventDescriptor
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
    MTEventDescriptor()
    { }

    /// Destructor
    ~MTEventDescriptor()
    { }

		/// Clear all information
    void Reset()
    { NTEventDescriptor::Reset(); }

    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const
    { NTEventDescriptor::Dump(os); }

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

#ifndef __IPHC_TREE_MTBEAMSPOT_H__
#define __IPHC_TREE_MTBEAMSPOT_H__

// STL headers
#include <iostream>

// ROOT headers
#include <TVector3.h>

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTParticle.h"
#include "../../NTFormat/interface/DisplayTool.h"


namespace IPHCTree
{

  /// \class MTBeamSpot
  /// MTBeamSpot contains all information related to Pile-Up
  class MTBeamSpot
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    TVector3 p3;      /// Beam spot position
    TVector3 p3Err;   /// Beam spot position error


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTBeamSpot()
    { }

    /// Destructor
    ~MTBeamSpot()
    { }

    /// Clear all information related to the BeamSpot
    void Reset()
    {
      p3.SetXYZ(0.,0.,0.);
      p3Err.SetXYZ(0.,0.,0.);
    }

    /// Display information related to the BeamSpot
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const
    {
      os << "BeamSpot info : " << p3;
      os << " with error " << p3Err << std::endl;
    }

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

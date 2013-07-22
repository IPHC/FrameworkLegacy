#ifndef __IPHC_TREE_MTMONTECARLO_H__
#define __IPHC_TREE_MTMONTECARLO_H__

// STL headers
#include <map>

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTMonteCarlo.h"


namespace IPHCTree
{

  /// \class MTMonteCarlo
  /// Extension of NTMonteCarlo with GeneratedParticles
  class MTMonteCarlo : public NTMonteCarlo
  {
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTMonteCarlo()
    { Reset(true); }

    /// Destructor
    ~MTMonteCarlo()
    { }

    /// Clear all information related to the Monte Carlo
    virtual void Reset(bool constructor_call=false);

    /// Display information related to Monte Carlo
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

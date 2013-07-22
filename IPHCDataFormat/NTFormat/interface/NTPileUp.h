#ifndef __IPHC_TREE_NTPILEUP_H__
#define __IPHC_TREE_NTPILEUP_H__

// STL headers
#include <iostream>

// ROOT headers
#include <TROOT.h>

namespace IPHCTree
{

  /// \class NTPileUp
  /// NTPileUp contains all information related to Pile-Up
  class NTPileUp
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    /// Pile-Up correction : neutral and charged particle densities
    Float_t rho_PUUE_dens;

    /// Pile-Up correction : neutral particle densities
    Float_t neutralRho_PUUE_dens;

    /// current number of interactions
    UChar_t intime_npu;

    /// number of interactions of the previous bunch
    UChar_t before_npu;

    /// number of interactions of the next bunch
    UChar_t after_npu;

	/// 'true' number of interactions - used in 2012 in replacement of intime/before/after_npu
    UChar_t Tnpv;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTPileUp()
    { Reset(true); }

    /// Destructor
    virtual ~NTPileUp()
    { }

    /// Clear all information related to the Pile-Up
    virtual void Reset(bool constructor_call=false);

    /// Display information related to the Pile-Up
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }


  };
}
#endif

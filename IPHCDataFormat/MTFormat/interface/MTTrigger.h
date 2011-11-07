#ifndef __IPHC_TREE_MTTRIGGER_H__
#define __IPHC_TREE_MTTRIGGER_H__

// IPHC headers (Ntuple format)
#include "../../NTFormat/interface/NTTrigger.h"


namespace IPHCTree
{

  /// \class MTTrigger
  /// class for MiniTree - inherit from NTTrigger
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTTrigger : public NTTrigger
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
    MTTrigger()
    { }

    /// Destructor
    virtual ~MTTrigger()
    { }

    /// Clear all information related to MET
    virtual void Reset();

    /// Display information related to MET
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

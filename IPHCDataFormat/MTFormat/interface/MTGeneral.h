#ifndef __IPHC_TREE_MTGENERAL_H__
#define __IPHC_TREE_MTGENERAL_H__

// IPHC headers (Ntuple format)
#include "../../NTFormat/interface/NTGeneral.h"


namespace IPHCTree
{

  /// \class MTGeneral
  /// class for MiniTree - inherit from NTGeneral
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTGeneral : public NTGeneral
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
    MTGeneral()
    { }

    /// Destructor
    virtual ~MTGeneral()
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

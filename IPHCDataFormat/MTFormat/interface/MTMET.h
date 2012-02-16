#ifndef __IPHC_TREE_MTMET_H__
#define __IPHC_TREE_MTMET_H__

// IPHC headers (Ntuple format)
#include "../../NTFormat/interface/NTMET.h"


namespace IPHCTree
{

  /// \class MTMET
  /// class MET for MiniTree - inherit from NTMET
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTMET : public NTMET
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
    MTMET()
    { Reset(true); }

    /// Destructor
    virtual ~MTMET()
    { }

    /// Clear all information related to MET
    virtual void Reset(bool constructor_call=false);

    /// Display information related to MET
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

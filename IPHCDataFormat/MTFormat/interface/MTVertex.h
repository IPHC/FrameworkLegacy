#ifndef __IPHC_TREE_MTVERTEX_H__
#define __IPHC_TREE_MTVERTEX_H__

// IPHC headers 
#include "../../NTFormat/interface/NTVertex.h"


namespace IPHCTree
{

  /// \class MTVertex
  /// class vertex for MiniTree - inherit from NTVertex
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTVertex : public NTVertex
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    TVector3 p3Err;		///  error on vertex position


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTVertex()
    { Reset(true); }

    /// Destructor
    virtual ~MTVertex()
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

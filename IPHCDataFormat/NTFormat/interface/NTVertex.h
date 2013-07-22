#ifndef __IPHC_TREE_NTVERTEX_H__
#define __IPHC_TREE_NTVERTEX_H__

// STL headers
#include <iostream>

// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"


namespace IPHCTree
{

  /// \class NTVertex
  /// class related to primary vertices for NTuple.
  class NTVertex
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    TVector3 p3;             /// vertex position (x,y,z)
    Float_t  chi2;           /// chi-square
    Bool_t   isFake;         /// tells whether the vertex is fake
    Bool_t   isValid;        /// tells whether the vertex is valid
    UInt_t   ndof;           /// number of degree of freedom
    UInt_t   NumberOfTracks; /// number of tracks


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTVertex()
    { Reset(true); }

    /// Destructor
    ~NTVertex()
    { }

		/// Clear all information related to the tau
    void Reset(bool constructor_call=false);

		/// Display information related to the tau
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Access to Rho parameter (position)
    const float Rho() const
    { return p3.Perp(); }

    /// Access to normalized chi2
    const float normalizedChi2() const
    { return chi2/static_cast<float>(ndof); }

  };
}
#endif

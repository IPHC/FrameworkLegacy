#ifndef __IPHC_TREE_NTMET_H__
#define __IPHC_TREE_NTMET_H__

// STL headers
#include <iostream>
#include <math.h>

// ROOT headers
#include "TVector2.h"


namespace IPHCTree
{

  /// \class NTMET
  /// NTMET describes Missing Transverse Energy in the NTuple format
  class NTMET
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// 2-vector describing UNCORRECTED missing ET
    TVector2 p2;

    /// 2-vector describing MET with muon correction
    TVector2 p2MuonCorr;

    /// correction : muon contribution
    Float_t correction;

    /// MET uncorrection on Ex
    Float_t dmEx; 

    /// MET uncorrection on Ey
    Float_t dmEy; 

    /// uncorrection on ET
    Float_t uncmisEt;

    /// scalar sum ET
    Float_t sumEt;


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTMET()
    { Reset(true); }

    /// Destructor
    ~NTMET()
    { }

    /// Clear all information related to MET
    void Reset(bool constructor_call=false);

    /// Display information related to MET
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Accessing to PT of MET
    float misEt() const 
    { return p2.Mod(); }

    /// Accessing to PT of MET
    float met() const 
    { return p2.Mod(); }

    /// Apply correction
    void doCorrection (float SumMuMetCorrX, float SumMuMetCorrY)
    { 
      correction = sqrt(  pow ((p2.Px() + SumMuMetCorrX), 2) 
                          + pow ((p2.Py() + SumMuMetCorrY), 2) ) - misEt();
    }

  };
}
#endif

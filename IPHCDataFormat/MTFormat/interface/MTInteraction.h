#ifndef __IPHC_TREE_MTINTERACTION_H__
#define __IPHC_TREE_MTINTERACTION_H__

// STL headers
#include <iostream>

//  ROOT headers
#include <TROOT.h>

namespace IPHCTree
{

  /// \class MTInteraction
  /// MTInteraction contains all information related to each 
  /// interaction contained in the Pile-Up
  class MTInteraction
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    /// the true primary vertex position along the z axis for each
    /// added interaction
    Float_t zpositions;   

    /// ---------------------- PT high_cut --------------------------
    /// high_cut is set to 0.5 GeV [date : 19/05/2011]

    /// the sum of the transverse momentum of the tracks originating
    /// from each interaction, where track pT > high_cut
    Float_t sumpT_highpT;    

    /// the number of tracks originating from each interaction,
    /// where track pT > high_cut
    Int_t ntrks_highpT;   

    // ---------------------- PT low_cut ---------------------------
    // low_cut is set to 0.1 GeV [date : 19/05/2011]

    /// the sum of the transverse momentum of the tracks originating 
    /// from each interaction, where track pT > low_cut
    Float_t sumpT_lowpT;     

    /// the number of tracks originating from each interaction,
    /// where track pT > low_cut
    Int_t ntrks_lowpT;    


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTInteraction()
    { Reset(); }

    /// Destructor
    ~MTInteraction()
    { }

    /// Clear all information related to the Pile-Up
    void Reset();

    /// Display information related to the Pile-Up
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

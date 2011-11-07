#ifndef __IPHC_TREE_NTJET_H__
#define __IPHC_TREE_NTJET_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTParticle.h"
#include "KeyedCollection.h"

namespace IPHCTree
{

  /// \class NTJet
  /// Class jet for NTuple. Contains info on identification,
  /// b-tagging, partonFlavour, SV.
  class NTJet : public NTParticle
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    /// 4-vector of the matched generated jet
    TLorentzVector p4Gen;

    /// 4-vector of the generated parton
    TLorentzVector p4Parton;

    /// parton flavour (MC info)  
    Char_t partonFlavour;

    // --------------- variables related to tracks -------------------

    UInt_t nTracks;      /// number of tracks associated to the jet
    Float_t sumPtTracks; /// the scalar sum of Pt of the nTracks tracks
   
    // ------------------ b-tagging discriminator --------------------

    /// b-tagging discriminators for different algorithms
    KeyedCollection<Float_t> bTag; 

   
    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTJet()
    { Reset(true); }

		/// Destructor
    virtual ~NTJet()
    {}

		/// Clear all information related to the particle
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the jet
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

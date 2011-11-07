#ifndef __IPHC_TREE_NTPhoton_H__
#define __IPHC_TREE_NTPhoton_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTParticle.h"
#include "KeyedCollection.h"

namespace IPHCTree
{

  /// \class NTPhoton
  /// NTPhoton should contain the minimal common information as p4, charge,
  /// isolation, d0, chi2, PhotonOrigin.
  class NTPhoton : public NTParticle
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    /// Is the photon reconstructed from Barrel calorimeter ?
    /// true = Barrel, false = End-Cap
    Bool_t isEB; 
    
    // ------------------ isolation variables ----------------------

    /// summed track pt in a cone of deltaR<0.4
    Float_t TrkIso;    

    /// ECAL summed ET in a cone of deltaR<0.4 iso deposit from
    /// RecHits with electron footprint removed (cone = 0.4)
    Float_t ECaloIso;  
                     
    /// HCAL iso deposit from calo Towers (cone = 0.4) summed Et in
    /// a cone of deltaR<0.4 
    Float_t HCaloIso; 

    // ---------------- shower shape variables ---------------------

    Float_t e1x5;
    Float_t e2x5;
    Float_t e3x3;
    Float_t e5x5;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:
 
    /// Constructor without arguments
    NTPhoton ()
    { Reset(true); }

    /// Destructor
    virtual ~NTPhoton ()
    { }

    /// Clear all information related to the photon
    virtual void Reset(bool constructor_call);
    
    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };

}

#endif

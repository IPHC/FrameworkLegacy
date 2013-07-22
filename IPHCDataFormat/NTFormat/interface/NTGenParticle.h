#ifndef __IPHC_TREE_NTGENPARTICLE_H__
#define __IPHC_TREE_NTGENPARTICLE_H__

// ROOT headers
#include <TLorentzVector.h>

// STL headers
#include <iostream>
#include <vector>

namespace IPHCTree
{

  /// \class NTGenParticle
  /// Mother class for Generated Particle
  class NTGenParticle
  {
    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------

  public :

    /// 4-vector momentum
    TLorentzVector p4;

    /// PDG identity
    Int_t id;

    /// StatusCode
    bool isStatus3;

    /// Mother index
    Int_t motherIndex_;

    /// Mother of the particle
    mutable IPHCTree::NTGenParticle* mother;  //! TRANSIENT

    /// Collection of pointers to the particle daughters
    /// Transient !!!
    mutable std::vector<NTGenParticle*> daughters;  //! TRANSIENT

    /// Type of decay (for taus and heavy quarks (c,b))
	// For taus :
	// decayMode = leptonFlavor   * 1      (0 = none ; 1 = elec ; 2 = muon) (hypothesis made of n(lepton) <= 1)
	//           + n(Pi_0)        * 10
	//           + n(Pi_charged)  * 100
	//           + n(K _0)        * 1000
	//           + n(K _charged)  * 10000
	//           + n(Gamma)       * 100000
	UInt_t decayMode;

  public :
 
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTGenParticle()
    { Reset(true); }

		/// Destructor
    virtual ~NTGenParticle()
    { }

		/// Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the lepton
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}

#endif

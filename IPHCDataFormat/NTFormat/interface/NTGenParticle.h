#ifndef __IPHC_TREE_NTGENPARTICLE_H__
#define __IPHC_TREE_NTGENPARTICLE_H__

// ROOT headers
#include <TLorentzVector.h>

// STL headers
#include <iostream>
#include <vector>

namespace IPHCTree
{

  //! \class NTGenParticle
  //! Mother class for Generated Particle
  class NTGenParticle
  {
    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------

  public :

    //! 4-vector momentum
    TLorentzVector p4;

    //! PDG identity
    Int_t id;

    //! StatusCode
    bool isStatus3;

    //! Mother index
    Int_t motherIndex_;

    //! Mother of the particle
    //! Transient !!!
    IPHCTree::NTGenParticle* mother;

    //! Collection of pointers to the particle daughters
    //! Transient !!!
    std::vector<NTGenParticle*> daughters;

  public :
 
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    NTGenParticle()
    { Reset(true); }

		//! Destructor
    virtual ~NTGenParticle()
    { }

		//! Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

		//! Display information related to the lepton
    //! \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}

#endif

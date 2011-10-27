#ifndef __IPHC_TREE_NTPARTICLE_H__
#define __IPHC_TREE_NTPARTICLE_H__

// STL headers
#include <iostream>

// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"

// IPHC headers
#include "KeyedCollection.h"


namespace IPHCTree
{

  //! \class NTParticle
  //! Mother class to all particles
  //! Contains momentum vector, 
  class NTParticle
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //! 4-vector momentum
    TLorentzVector p4; 

    //! 4-vector momentum @ HLT
    KeyedCollection<TLorentzVector> p4HLT;

    //! Container for adding easly variables without changing dataformat code
    KeyedCollection<Float_t> others;

    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    NTParticle()
    { 
      // By default, TLorentzVector are initialized to (0.,0.,0.,0.)
    }

		//! Destructor
    virtual ~NTParticle()
    { }

		//! Clear all information related to the particle
    virtual void Reset()
		{
      p4.SetPxPyPzE    (0., 0., 0., 0.);
      p4HLT.Reset();
      others.Reset();
		}

		//! Display information related to the particle
    //! \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const
    {
      NTParticle::PrintP4(p4,os);
      os << std::endl << "HLT";
      p4HLT.Dump(os);
      os << std::endl;
    }

    //! Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    //! Display a 4-vector momentum
    //! \param[in]     a    a 4-vector momentum to display
    //! \param[in,out] os   a log stream
    static void PrintP4(const TLorentzVector& a,
                        std::ostream & os = std::cout)
		{
			os << " p4 = ("<< a.Px() << "," << a.Py() << "," << a.Pz() 
         << "," << a.E() << ") & pT = " << a.Pt() << " ";
    }

    //! Display 3-vector momentum
    //! \param[in]     a    a 3-vector momentum to display
    //! \param[in,out] os   a log stream
    static void PrintP3(const TVector3& a, std::ostream & os = std::cout)
    {
			os << " p3 = ("<< a.X() << "," << a.Y() << "," << a.Z() << ") ";
    }


  };
}
#endif

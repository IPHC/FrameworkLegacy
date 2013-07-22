#ifndef __IPHC_TREE_NTPARTICLE_H__
#define __IPHC_TREE_NTPARTICLE_H__

// STL headers
#include <iostream>

// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"

// IPHC headers
#include "KeyedCollection.h"
#include "DisplayTool.h"

namespace IPHCTree
{

  /// \class NTParticle
  /// Mother class to all particles
  /// Contains momentum vector, 
  class NTParticle
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// 4-vector momentum
    TLorentzVector p4; 

    /// 4-vector momentum @ HLT
    KeyedCollection<TLorentzVector> p4HLT;

    /// Container for adding easly variables without changing dataformat code
    KeyedCollection<Float_t> others;

    /// Collection of ID
    KeyedCollection<Float_t> ID;

    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTParticle()
    { 
      // By default, TLorentzVector are initialized to (0.,0.,0.,0.)
    }

		/// Destructor
    virtual ~NTParticle()
    { }

		/// Clear all information related to the particle
    virtual void Reset()
		{
      p4.SetPxPyPzE    (0., 0., 0., 0.);
      p4HLT.Reset();
      others.Reset();
		}

		/// Display information related to the particle
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const
    {
      os << " p4 = " << p4 << std::endl;

      os << " HLT p4 collection content : " << p4HLT.size();
      os << " items" << std::endl;
      p4HLT.Dump(os);

      os << " ID collection content : " << ID.size();
      ID.Dump(os);

      os << " 'others' collection content : " << others.size();
      os << " items" << std::endl;
      others.Dump(os);
    }

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

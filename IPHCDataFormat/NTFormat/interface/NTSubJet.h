#ifndef __IPHC_TREE_NTSUBJET_H__
#define __IPHC_TREE_NTSUBJET_H__

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

  /// \class NTSubJet
  /// Mother class to all particles
  /// Contains momentum vector, 
  class NTSubJet
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// 4-vector momentum
    TLorentzVector p4; 

    /// b-tagging discriminators for different algorithms
    KeyedCollection<Float_t> bTag; 
    
    /// Container for adding easly variables without changing dataformat code
    KeyedCollection<Float_t> others;

    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTSubJet()
    { 
      // By default, TLorentzVector are initialized to (0.,0.,0.,0.)
    }

		/// Destructor
    virtual ~NTSubJet()
    { }

		/// Clear all information related to the particle
    virtual void Reset()
		{
      p4.SetPxPyPzE    (0., 0., 0., 0.);
		}

		/// Display information related to the particle
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const
    {
      os << " p4 = " << p4 << std::endl;
      others.Dump(os);
    }

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

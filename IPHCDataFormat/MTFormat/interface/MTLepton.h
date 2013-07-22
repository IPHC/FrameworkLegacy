#ifndef __IPHC_TREE_MTLEPTON_H__
#define __IPHC_TREE_MTLEPTON_H__

// STL headers
#include <map>
#include <vector>
#include <string>

// ROOT headers
#include "TLorentzVector.h"
#include "TVector3.h"

// CMSSW headers
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

namespace IPHCTree
{

  /// \class MTLepton
  /// This is an extension of NTLepton which contains additionnaly
  ///  - MC information
  ///  - Vertex information
  /// MTLepton doesn't inherit from NTLepton.
  class MTLepton
  {
  public:

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// 4-vector momentum of the matched generated particle
    TLorentzVector p4Gen;

    /// IP wrt the beamline (?)
    Float_t DB;

    /// Generated Particle, mother of the particle
    reco::GenParticle GenMother;

    /// Generated Particle, grand mother of the particle
    reco::GenParticle GenGrandMother;

    /// Generated Particle, grand grand mother of the particle
    reco::GenParticle GenGGrandMother;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------

    /// Constructor without arguments
    MTLepton()
    { Reset(true); }

		/// Destructor
    ~MTLepton()
    { }

		/// Clear all information related to lepton
    void Reset(bool constructor_call=false);

		/// Display information related to the lepton
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

#ifndef __IPHC_TREE_MTMONTECARLO_H__
#define __IPHC_TREE_MTMONTECARLO_H__

// STL headers
#include <map>

// CMSSW headers
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTMonteCarlo.h"


namespace IPHCTree
{

  //! \class MTMonteCarlo
  //! Extension of NTMonteCarlo with GeneratedParticles
  class MTMonteCarlo : public NTMonteCarlo
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //! Skimmed GenParticleCollection
    reco::GenParticleCollection GPC;

    //! List of GeneratedParticle daughters 
    std::map < unsigned int, std::vector < signed int > > GPC_list_index_dau;

    //! List of GeneratedParticle daughters 
    std::map < unsigned int, std::vector < signed int > > GPC_list_index_mot;


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    MTMonteCarlo()
    { Reset(true); }

    //! Destructor
    ~MTMonteCarlo()
    { }

    //! Clear all information related to the Monte Carlo
    virtual void Reset(bool constructor_call=false);

    //! Display information related to Monte Carlo
    //! \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    //! Filling the GeneratedParticle collection 
    void fillGenInfo(reco::GenParticleCollection* genParticles);
  };
}
#endif

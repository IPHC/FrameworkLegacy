#ifndef __IPHC_TREE_NTJETMET_H__
#define __IPHC_TREE_NTJETMET_H__

// STL headers
#include <string>
#include <vector>

// IPHC headers
#include "../interface/NTMET.h"
#include "../interface/NTJet.h"


namespace IPHCTree
{

  //! \class NTJetMet
  //! Class jet/met for NTuple. Contains for a given algorithm the jet
  //! collection & the associated MET.
  class NTJetMet
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //! Missing transverse energy
    IPHCTree::NTMET met;

    //! Sum of the corrected jet's ET
    Float_t sumEtJet;

    //! Sum of the raw jet's ET
    Float_t sumEtJetRaw;

    //! Collection of jets
    std::vector<NTJet> jets; 


    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:
    
    //! Constructor without arguments
    NTJetMet()
    { Reset(true); }

		//! Destructor
    ~NTJetMet()
    { }

		//! Clear all information related to the particle
    void Reset(bool constructor_call=false);

		//! Display information related to the jet
    //! \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

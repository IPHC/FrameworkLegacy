#ifndef __TOP_TREE_MTJETMET_H__
#define __TOP_TREE_MTJETMET_H__

// STL headers
#include <vector>

// IPHC headers 
#include "MTMET.h"
#include "MTJet.h"

namespace IPHCTree
{

  //! \class MTJetMet
  //! Class jet/met for MiniTree
  class MTJetMet
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //! Missing transverse energy
    IPHCTree::MTMET met;

    //! Sum of the corrected jet's ET
    Float_t sumEtJet;

    //! Sum of the raw jet's ET
    Float_t sumEtJetRaw;

    //! Collection of jets
    std::vector<MTJet> jets; 


    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:
    
    //! Constructor without arguments
    MTJetMet()
    { Reset(true); }

		//! Destructor
    ~MTJetMet()
    { }

		//! Clear all information related to the particle
    void Reset(bool constructor_call=false);

		//! Display information related to the jet
    //! \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    // methods to instanciate a new object
    MTJet* NewJet()
    { jets.push_back(MTJet());
      return &jets.back(); }

    // methods to instanciate a new object
    void NewJet (const MTJet& jet)
    { jets.push_back(jet); }

    //! Give the number of jets
    unsigned int size() const
    { return jets.size(); }

    //! Add a new jets
    void push_back(const IPHCTree::MTJet& myjet)
    { jets.push_back(myjet); }

    //! Give the first jet
    const IPHCTree::MTJet& front() const
    { return jets.front(); }

    IPHCTree::MTJet& front()
    { return jets.front(); }

    //! Give the last jet
    const IPHCTree::MTJet& back() const
    { return jets.back(); }

    IPHCTree::MTJet& back()
    { return jets.back(); }

    //! operator [] overlaoding
    const IPHCTree::MTJet& operator[] (unsigned int i) const
    { return jets[i]; }

    IPHCTree::MTJet& operator[] (unsigned int i)
    { return jets[i]; }


  };
}


#endif

#ifndef __IPHC_TREE_MTPILEUP_H__
#define __IPHC_TREE_MTPILEUP_H__

// STL headers
#include <iostream>
#include <vector>
#include <map>

// IPHC headers
#include "MTInteraction.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTPileUp.h"


namespace IPHCTree
{

  /// \class MTPileUp
  /// Extension of NTPileUp with details about interaction
  class MTPileUp : public NTPileUp
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    /// information related to each interaction
    std::map<Char_t, std::vector<MTInteraction> > interactions;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTPileUp()
    { Reset(true); }

    /// Destructor
    virtual ~MTPileUp()
    { }

    /// Clear all information related to the Pile-Up
    virtual void Reset(bool constructor_call=false);

    /// Display information related to the Pile-Up
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    std::vector<MTInteraction>* NewPUbunch(signed int bunch)
    {
      interactions[bunch] = std::vector<MTInteraction>();
      return &(interactions[bunch]);
    }

  };
}
#endif

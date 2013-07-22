#ifndef __IPHC_TREE_NTGeneral_H__
#define __IPHC_TREE_NTGeneral_H__

// STL headers
#include <iostream>

// ROOT headers
#include <TROOT.h>

namespace IPHCTree
{

  /// \class NTGeneral
  /// NTGeneral contains all information about event id
  class NTGeneral
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    UInt_t runNb;     /// run number
    UInt_t eventNb;   /// event number 
    UInt_t lumiblock; /// luminosity block number


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTGeneral()
    { Reset(); }

    /// Destructor
    ~NTGeneral()
    { }

    /// Clear all information related to the Pile-Up
    void Reset()
    { runNb=0; eventNb=0; lumiblock=0; }

    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const
    { 
      os << " -- Event " << eventNb << " from run " << runNb
         << " & lumiBlock " << lumiblock<< std::endl;
    }

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

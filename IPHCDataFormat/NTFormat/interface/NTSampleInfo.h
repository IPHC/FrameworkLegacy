#ifndef __IPHC_TREE_NTSampleInfo_H__
#define __IPHC_TREE_NTSampleInfo_H__

// STL headers
#include <iostream>

// ROOT headers
#include <TROOT.h>
#include <TClonesArray.h>
#include <TString.h>


namespace IPHCTree
{

  /// \class NTSampleInfo
  /// NTSampleInfo contains all information about the sample
  class NTSampleInfo
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    TString version;     /// NTuple format version
    TString script;      /// Script name
    TString folder;      /// Folder name
    TString user;        /// Login of the guy who launch the production 
    TString machine;     /// Machine name
    TString time_crab;   /// Time of crab submit    
    TClonesArray* config;   /// Configuration script

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTSampleInfo()
    { config = new TClonesArray("TObjString"); }

    /// Destructor
    ~NTSampleInfo()
    { delete config; }

    /// Clear all information
    void Reset()
    { version=""; script=""; folder=""; 
      user=""; machine=""; time_crab=""; 
      config->Clear("C"); }

    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const
    { 
      /*      os << " -- Event " << eventNb << " from run " << runNb
              << " & lumiBlock " << lumiblock<< std::endl;*/
    }

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

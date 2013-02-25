#ifndef __IPHC_TREE_NTEventDescriptor_H__
#define __IPHC_TREE_NTEventDescriptor_H__

// STL headers
#include <iostream>
#include <string>
#include <set>

// ROOT headers
#include <TROOT.h>

namespace IPHCTree
{

  /// \class NTEventDescriptor
  /// NTEventDescriptor contains all information about event id
  class NTEventDescriptor
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    std::set<std::string> jet_p4HLT;
    std::set<std::string> electron_p4HLT;
    std::set<std::string> muon_p4HLT;
    std::set<std::string> tau_p4HLT;
    std::set<std::string> photon_p4HLT;

    std::set<std::string> jet_others;
    std::set<std::string> electron_others;
    std::set<std::string> muon_others;
    std::set<std::string> tau_others;
    std::set<std::string> photon_others;
    std::set<std::string> pfcandidate_others;
    std::set<std::string> event_others;

    std::set<std::string> electron_ID;
    std::set<std::string> muon_ID;
    std::set<std::string> tau_ID;
    std::set<std::string> jet_ID;
    std::set<std::string> jet_bTag;
    std::set<std::string> jet_HeavyTag;

    std::set<std::string> electron_isolation;
    std::set<std::string> muon_isolation;
    std::set<std::string> tau_isolation;
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTEventDescriptor()
    { }

    /// Destructor
    ~NTEventDescriptor()
    { }

		/// Clear all information
    void Reset();

    /// Display information related to the photon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

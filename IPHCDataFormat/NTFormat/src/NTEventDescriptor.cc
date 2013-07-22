#include "../interface/NTEventDescriptor.h"


using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTEventDescriptor::Reset()
{
  jet_p4HLT.clear();
  electron_p4HLT.clear();
  muon_p4HLT.clear();
  tau_p4HLT.clear();
  photon_p4HLT.clear();

  jet_others.clear();
  electron_others.clear();
  muon_others.clear();
  tau_others.clear();
  photon_others.clear();
  pfcandidate_others.clear();
  event_others.clear();

  electron_ID.clear();
  muon_ID.clear();
  tau_ID.clear();
  jet_ID.clear();
  jet_bTag.clear();
}


// ---------------------------------------------------------------------------
// Dump
// ---------------------------------------------------------------------------
void NTEventDescriptor::Dump(std::ostream & os) const
{
	os << "Object: NTEventDescriptor " << std::endl;

  os << "jet_p4HLT names      = " << jet_p4HLT.size()      << std::endl;
  os << "electron_p4HLT names = " << electron_p4HLT.size() << std::endl;
  os << "muon_p4HLT names     = " << muon_p4HLT.size()     << std::endl;
  os << "tau_p4HLT names      = " << tau_p4HLT.size()      << std::endl;
  os << "photon_p4HLT names   = " << photon_p4HLT.size()   << std::endl;

  os << "jet_others names         = " << jet_others.size()         << std::endl;
  os << "electron_others names    = " << electron_others.size()    << std::endl;
  os << "muon_others names        = " << muon_others.size()        << std::endl;
  os << "tau_others names         = " << tau_others.size()         << std::endl;
  os << "photon_others names      = " << photon_others.size()      << std::endl;
  os << "pfcandidate_others names = " << pfcandidate_others.size() << std::endl;
  os << "event_others names       = " << event_others.size()       << std::endl;

  os << "electron_ID names = " << electron_ID.size() << std::endl;
  os << "muon_ID names     = " << muon_ID.size()     << std::endl;
  os << "tau_ID names      = " << tau_ID.size()      << std::endl;
  os << "jet_ID names      = " << jet_ID.size()      << std::endl;
  os << "jet_bTag names    = " << jet_bTag.size()    << std::endl;
}

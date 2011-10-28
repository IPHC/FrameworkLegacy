#include "../interface/MTJetMet.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTJetMet::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    jets.clear();
    met.Reset();
  }
  sumEtJet    = -999.;
  sumEtJetRaw = -999.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTJetMet::Dump(std::ostream & os) const
{
	os << "Object: JetMet " << std::endl;
  met.Dump(os);
  os << " jets container size = " << jets.size() << std::endl;
  os << " sumEtJet = "            << sumEtJet;
  os << " sumEtJetRaw = "         << sumEtJetRaw << std::endl;
}

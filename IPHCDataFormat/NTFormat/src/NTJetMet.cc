#include "../interface/NTJetMet.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTJetMet::Reset(bool constructor_call)
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
void NTJetMet::Dump(std::ostream & os) const
{
	os << "Object: JetMet " << std::endl;
  met.Dump(os);
  os << " jets container size = " << jets.size() << std::endl;
  os << " sumEtJet = "            << sumEtJet;
  os << " sumEtJetRaw = "         << sumEtJetRaw << std::endl;
}

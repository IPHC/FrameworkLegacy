#include "../interface/NTMuon.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTMuon::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTLepton::Reset();
  }
  isGlobalMuon     = false;
  isStandaloneMuon = false;
  isTrackerMuon    = false;
  isCaloMuon       = false;
  NValidHits       = 0;
  NTrValidHits     = 0;
  NOfMatches       = 0;
  D0Inner          = 0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTMuon::Dump(std::ostream & os) const
{
	os << "Object: Muon " << std::endl;
	NTLepton::Dump(os);
	os << " MuonType = " << MuonType() << " (";
  os << "isGlobalMuon = " << static_cast<unsigned int>(isGlobalMuon);
  os << "isStandaloneMuon = " << static_cast<unsigned int>(isStandaloneMuon);
  os << "isTrackerMuon = " << static_cast<unsigned int>(isTrackerMuon);
  os << "isCaloMuon = " << static_cast<unsigned int>(isCaloMuon);
  os << ")" << std::endl;
	os << " NValidHits = " << NValidHits;
  os << " NTrValidHits = " << NTrValidHits;
  os << " NOfMatches = " << NOfMatches;
  os << " D0Inner = " << D0Inner << std::endl;
}

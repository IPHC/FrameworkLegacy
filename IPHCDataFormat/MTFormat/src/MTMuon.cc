#include "../interface/MTMuon.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTMuon::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    MTLepton::Reset();
    NTMuon::Reset();
  }
  IP3D    = -999;
  IP3DErr = -999;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTMuon::Dump(std::ostream & os) const
{
  NTMuon::Dump(os);
  MTLepton::Dump(os);
	os << " TrackMu pT = " << TrackMu.pt() << std::endl;
	os << " StaMu pT = "   << StaMu.pt() << std::endl;
	os << " ComMu pT = "   << ComMu.pt() << std::endl;
  os << " IP3D = " << IP3D << " with error " << IP3DErr << std::endl;
}

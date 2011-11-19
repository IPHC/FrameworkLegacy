#include "../interface/NTTrack.h"
#include "../interface/NTParticle.h"
#include "../interface/DisplayTool.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTTrack::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p4.SetPxPyPzE(0.,0.,0.,0.);
  }
  charge_bit_  = false;
  charge   = 0;
  chi2     = -999.;
  dxy      = -999.;
  dxy_BS   = -999.;
  dxyError = -999.;
  dz       = -999.;
  dzError  = -999.;
  nHitTracker = 0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTTrack::Dump(std::ostream & os) const
{
	os << "Object: Track " << std::endl;
  os << " p4 = " << p4 << std::endl;
	os << " charge = "      << charge;
	os << " chi2 = "        << chi2 << std::endl;
	os << " dxy = "         << dxy_BS;
	os << " dxy_BS = "      << dxy_BS;
	os << " dxyError = "    << dxyError << std::endl;
	os << " d0 = "          << d0();
	os << " d0Error  = "    << d0Error();
	os << " dz = "          << dz;
	os << " dzError = "     << dzError;
	os << " NHitTracker = " << nHitTracker;
	os << std::endl;
}

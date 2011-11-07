#include "../interface/NTTrack.h"
#include "../interface/NTParticle.h"

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
  nHitTracker = 0.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTTrack::Dump(std::ostream & os) const
{
	os << "Object: Track " << std::endl;
  NTParticle::PrintP4(p4, os);
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

#include "../interface/NTPhoton.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTPhoton::Reset (bool constructor_call)
{
  if (!constructor_call)
  {
    p4.SetPxPyPzE (0.0, 0.0, 0.0, 0.0);
  }
  ECaloIso = -999.;
  HCaloIso = -999.;
  TrkIso   = -999.;
  isEB     = false;
  e1x5     = -999.;
  e2x5     = -999.;
  e3x3     = -999.;
  e5x5     = -999.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTPhoton::Dump(std::ostream & os) const
{
	os << "Object: Photon " << std::endl;
	NTParticle::Dump(os);
  os << " isEB = "     << static_cast<unsigned int>(isEB);
  os << " ECaloIso = " << ECaloIso;
  os << " HCaloIso = " << HCaloIso;
  os << " TrkIso = "   << TrkIso;
  os << " e1x5 = "     << e1x5;
  os << " e2x5 = "     << e2x5;
  os << " e3x3 = "     << e3x3;
  os << " e5x5 = "     << e5x5 << std::endl;
}


#include "../interface/NTVertex.h"
#include "../interface/NTParticle.h"
#include "../interface/DisplayTool.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTVertex::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p3.SetXYZ(0.,0.,0.);
  }
  chi2           = -999;
  isFake         = false;
  isValid        = false;
  ndof           = 0;
  NumberOfTracks = 0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTVertex::Dump(std::ostream & os) const
{
	os << "Object: Vertex " << std::endl;
	os << " vertex = " << p3 << std::endl;
	os << " rho = " << Rho() << std::endl;
	os << " chi2 = "    << chi2;
	os << " ndof = "    << ndof;
	os << " normalizedChi2 = " << normalizedChi2() << std::endl;
	os << " isFake = "  << static_cast<unsigned int>(isFake);
	os << " isValid = " << static_cast<unsigned int>(isValid);
	os << " NumberOfTracks = " << NumberOfTracks << std::endl;
}

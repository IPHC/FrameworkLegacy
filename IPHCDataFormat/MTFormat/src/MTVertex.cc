#include "../interface/MTVertex.h"
#include "../../NTFormat/interface/NTParticle.h"


using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTVertex::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p3Err.SetXYZ(0.,0.,0.);
    Reset(constructor_call);
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTVertex::Dump(std::ostream & os) const
{
  NTVertex::Dump(os);
	os << " error on vertex : ";
  NTParticle::PrintP3(p3Err,os);
}

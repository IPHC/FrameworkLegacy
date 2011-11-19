#include "../interface/MTVertex.h"
#include "../../NTFormat/interface/NTParticle.h"
#include "../../NTFormat/interface/DisplayTool.h"


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
	os << " error on vertex position = " << p3Err << std::endl;
}

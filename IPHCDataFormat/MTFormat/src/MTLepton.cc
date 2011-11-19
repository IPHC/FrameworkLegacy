#include "../interface/MTLepton.h"
#include "../../NTFormat/interface/NTParticle.h"
#include "../../NTFormat/interface/DisplayTool.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTLepton::Reset(bool constructor_called)
{
  if (!constructor_called)
  {
    p4Gen.SetPxPyPzE (0.0, 0.0, 0.0, 0.0);
  }
  DB = -999.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTLepton::Dump(std::ostream & os) const
{
  os << " p4Gen = " << p4Gen << std::endl;
  os << "pgdID-mother = "   << GenMother.pdgId();
  os << "pgdID-Gmother = "  << GenGrandMother.pdgId();
  os << "pgdID-GGmother = " << GenGGrandMother.pdgId();
  os << std::endl;
}

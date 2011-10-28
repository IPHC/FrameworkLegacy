#include "../interface/MTMET.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTMET::Reset(bool constructor_call)
{
  NTMET::Reset(constructor_call);
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTMET::Dump(std::ostream & os) const
{
  NTMET::Dump(os);
}

#include "../interface/MTMonteCarlo.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTMonteCarlo::Reset(bool constructor_call)
{
  NTMonteCarlo::Reset(constructor_call);
  if (!constructor_call)
  {
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTMonteCarlo::Dump(std::ostream & os) const
{
  NTMonteCarlo::Dump(os);
}


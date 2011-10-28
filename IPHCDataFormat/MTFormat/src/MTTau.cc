#include "../interface/MTTau.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTTau::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    MTLepton::Reset(constructor_call);
    NTTau::Reset(constructor_call);
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTTau::Dump(std::ostream & os) const
{
  NTTau::Dump(os);
  MTLepton::Dump(os);
}



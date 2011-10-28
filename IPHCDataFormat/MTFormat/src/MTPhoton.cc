#include "../interface/MTPhoton.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTPhoton::Reset (bool constructor_call)
{
  if (!constructor_call)
  {
    NTPhoton::Reset(constructor_call);
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTPhoton::Dump(std::ostream & os) const
{
  NTPhoton::Dump(os);
}


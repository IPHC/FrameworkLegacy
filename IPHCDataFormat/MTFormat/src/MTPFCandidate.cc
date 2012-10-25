#include "../interface/MTPFCandidate.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTPFCandidate::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTPFCandidate::Reset(constructor_call);
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTPFCandidate::Dump(std::ostream & os) const
{
  NTPFCandidate::Dump(os);
}

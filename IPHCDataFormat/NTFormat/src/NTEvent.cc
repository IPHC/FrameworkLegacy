#include "../interface/NTEvent.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTEvent::Reset()
{
  general.Reset();        mc.Reset();
  pileup.Reset();         vertices.Reset();
  electrons.Reset();      muons.Reset();
  taus.Reset();           photons.Reset();
  jets.Reset();           met.Reset(); 
  tracks.Reset();
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTEvent::Dump(std::ostream & os) const
{
  general.Dump(os);        mc.Dump(os);
  pileup.Dump(os);         vertices.Dump(os);
  electrons.Dump(os);      muons.Dump(os);
  taus.Dump(os);           photons.Dump(os);
  jets.Dump(os);           met.Dump(os);
         tracks.Dump(os);
}






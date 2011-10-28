#include "../interface/MTEvent.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ---------------------------------------------------------------------------
void MTEvent::Reset()
{
  general.Reset();  trigger.Reset();
  mc.Reset();
  pileup.Reset();
  electrons.Reset();      muons.Reset();
  taus.Reset();           photons.Reset();
  jetMet.Reset();       tracks.Reset();
  vertices.Reset();       beamSpot.Reset();
  others.Reset();
}


// ---------------------------------------------------------------------------
// Dump
// ---------------------------------------------------------------------------
void MTEvent::Dump(std::ostream & os) const
{
  general.Dump(os); trigger.Dump(os);
  mc.Dump(os);
  pileup.Dump(os);
  electrons.Dump(os);      muons.Dump(os);
  taus.Dump(os);           photons.Dump(os);
  jetMet.Dump(os);         tracks.Dump(os);
  vertices.Dump(os);       beamSpot.Dump(os);
  others.Dump(os);
}







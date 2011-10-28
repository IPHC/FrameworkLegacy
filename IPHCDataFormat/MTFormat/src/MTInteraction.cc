#include "../interface/MTInteraction.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTInteraction::Reset()
 {
  zpositions    = -999; 
  sumpT_lowpT   = -999; 
  sumpT_highpT  = -999; 
  ntrks_lowpT   = -999;   
  ntrks_highpT  = -999;
}

  
// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTInteraction::Dump(std::ostream & os) const
{
  os << "Object: interation "   << std::endl;
  os << " zpositions = "    << zpositions;
  os << " sumpT_lowpT = "   << sumpT_lowpT;
  os << " sumpT_highpT = "  << sumpT_highpT << std::endl;
  os << " ntrks_lowpT = "   << ntrks_lowpT;
  os << " ntrks_highpT = "  << ntrks_highpT << std::endl;
}


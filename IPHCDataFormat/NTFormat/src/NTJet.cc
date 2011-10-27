#include "../interface/NTJet.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTJet::Reset (bool constructor_call)
{
  if (!constructor_call)
  {
    NTParticle::Reset();
    p4Gen.SetPxPyPzE    (0., 0., 0., 0.);
    p4Parton.SetPxPyPzE (0., 0., 0., 0.);
    bTag.Reset();
  }
  partonFlavour = 0;
  nTracks       = 0; 
  sumPtTracks   = -999.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTJet::Dump(std::ostream & os) const
{
	os << "Object: Jet " << std::endl;
  NTParticle::Dump(os);
  os << " p4Gen    : "; NTParticle::PrintP4(p4Gen,os);    os << std::endl;
  os << " p4Parton : "; NTParticle::PrintP4(p4Parton,os); os << std::endl;
  os << " partonFlavour = " << partonFlavour;
  os << " nTracks = "      << nTracks;
  os << " sumPtTracks = "  << sumPtTracks << std::endl;
  bTag.Dump(os);
}

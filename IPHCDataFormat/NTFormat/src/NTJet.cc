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
  jetCharge = -999.0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTJet::Dump(std::ostream & os) const
{
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: Jet" << std::endl;

  NTParticle::Dump(os);

  os << " Gen p4    = " << p4Gen << std::endl;
  os << " Parton p4 = " << p4Parton << std::endl;

  os << " partonFlavour = " << static_cast<signed int>(partonFlavour) << " ;";
  os << " nTracks = "       << nTracks << " ;";
  os << " sumPtTracks = "   << sumPtTracks << std::endl;
  os << " jetCharge = "     << jetCharge << std::endl;

  os << " bTag collection content : " << bTag.size();
  os << " items" << std::endl;
  bTag.Dump(os);

  os << " Heavy Tag collection content : " << HeavyTag.size();
  os << " items" << std::endl;
  HeavyTag.Dump(os);

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

}

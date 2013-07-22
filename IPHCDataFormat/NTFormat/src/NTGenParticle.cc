#include "../interface/NTGenParticle.h"
#include "../interface/NTParticle.h"
#include "../interface/DisplayTool.h"


using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTGenParticle::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p4.SetPxPyPzE(0., 0., 0., 0.);
    daughters.clear();
  }
  id        = 0;
  isStatus3 = false;
  mother    = 0;
  motherIndex_ = -1;
  decayMode = -1;
}


// ---------------------------------------------------------------------------
// Dump
// ---------------------------------------------------------------------------
void NTGenParticle::Dump(std::ostream & os) const
{
	os << "Object: NTGenParticle " << std::endl;
  os << " PDG id = " << id;
  os << " isStatus3 = " << static_cast<unsigned int>(isStatus3);
  os << " p4 = " << p4;
  os << std::endl;
  os << " mother @ ";
  if (mother==0) os << "NULL";
  else os << mother;
  os << std::endl;
  os << " decayMode = " << decayMode;
  os << std::endl;
  os << " nb daughters = " << daughters.size() << std::endl;
}

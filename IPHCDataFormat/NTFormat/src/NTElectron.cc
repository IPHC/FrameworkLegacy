#include "../interface/NTElectron.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTElectron::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTLepton::Reset();
  }
  isEcalDriven  = false;
  isGsfElectron = false;
  isEB          = false;
  ET_SC         = 0.;
  deltaCotTheta   = -999;
  deltaDistance   = -999;
  nLost           = 0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTElectron::Dump(std::ostream & os) const
{
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: Electron " << std::endl;
  NTLepton::Dump(os);

  os << " isEB = "          << static_cast<unsigned int>(isEB) << " ;"; 
  os << " isEcalDriven = "  << static_cast<unsigned int>(isEcalDriven) << " ;";
  os << " ET_SC = "         << ET_SC << std::endl;

  os << " deltaCotTheta = " << deltaCotTheta << " ;";
  os << " deltaDistance = " << deltaDistance << std::endl;

	os << " isGsfElectron = " << isGsfElectron << " ;";
  os << " nLost = " << nLost << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}
 
  

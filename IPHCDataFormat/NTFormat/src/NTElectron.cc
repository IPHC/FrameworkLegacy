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
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTElectron::Dump(std::ostream & os) const
{
	os << "Object: Electron " << std::endl;
  NTLepton::Dump(os);
  os << " isEB = "          << isEB; 
	os << " isGsfElectron = " << isGsfElectron;
  os << " isEcalDriven = "  << isEcalDriven;
  os << " ET_SC = "         << ET_SC << std::endl;
}
 
  

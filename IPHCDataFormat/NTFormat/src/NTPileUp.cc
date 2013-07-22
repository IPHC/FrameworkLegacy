#include "../interface/NTPileUp.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTPileUp::Reset(bool constructor_call)
{
  rho_PUUE_dens        = -999.;
  neutralRho_PUUE_dens = -999.;
  intime_npu           = 0;
  before_npu           = 0;
  after_npu            = 0;
  Tnpv                 = 0;
}

  
// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTPileUp::Dump(std::ostream & os) const
{
  os << "Object: Pileup "   << std::endl;
  os << " rho_PUUE_dens = "         << rho_PUUE_dens << " ;";
  os << " neutralRho_PUUE_dens = "  << neutralRho_PUUE_dens;
  os << std::endl;

  os << " intime_npu = " << static_cast<unsigned int>(intime_npu) << " ;";
  os << " before_npu = " << static_cast<unsigned int>(before_npu) << " ;";
  os << " after_npu = "  << static_cast<unsigned int>(after_npu)  << " ;";
  os << " Tnpv = "  << static_cast<unsigned int>(Tnpv);
  os << std::endl;
}


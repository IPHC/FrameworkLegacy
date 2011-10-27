#include "../interface/NTMET.h"
#include "../interface/NTParticle.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTMET::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p2.Set        (0., 0.);
    p2MuonCorr.Set(0., 0.);
  }
  correction = -999;
  dmEx       = -999; 
  dmEy       = -999; 
  uncmisEt   = -999;
  sumEt      = -999;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTMET::Dump(std::ostream & os) const
{
	os << "Object: MET " << std::endl;
  os << "p2 : px=" << p2.Px() << " ; py=" << p2.Py();
  os << std::endl << "MuonCorr "; 
  os << "p2 : px=" << p2MuonCorr.Px() << " ; py=" << p2MuonCorr.Py();
  os << std::endl;

	os << " correction = " << correction;
	os << " dmEx = "       << dmEx;
	os << " dmEy = "       << dmEy         << std::endl;
  os << " misEt = "      << misEt();
  os << " uncmisEt = "   << uncmisEt;
  os << " sumEt = "      << sumEt        << std::endl;
}

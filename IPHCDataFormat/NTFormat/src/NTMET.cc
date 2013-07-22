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
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: MET" << std::endl;

  os << " p2 = ( " << p2.Px() << " , " << p2.Py() << " )";
  os << " ; met = " << met() << std::endl;

  os << " MuonCorr p2 = ( " << p2MuonCorr.Px(); 
  os << " , " << p2MuonCorr.Py() << " ) ; met = " << p2MuonCorr.Mod();
  os << std::endl;

	os << " correction = " << correction << " ;";
	os << " dmEx = "       << dmEx << " ;";
	os << " dmEy = "       << dmEy << std::endl;

  os << " misEt = "      << misEt() << " ;";
  os << " uncmisEt = "   << uncmisEt << " ;";
  os << " sumEt = "      << sumEt  << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}

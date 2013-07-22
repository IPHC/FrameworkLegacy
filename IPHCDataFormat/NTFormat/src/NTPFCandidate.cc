#include "../interface/NTPFCandidate.h"
#include "../interface/NTParticle.h"
#include "../interface/DisplayTool.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTPFCandidate::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    p4.SetPxPyPzE(0.,0.,0.,0.);
  }
  
  dz_firstGoodVertex = 999.;
  trackIso  = 999.;
  others.Reset();
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTPFCandidate::Dump(std::ostream & os) const
{
	os << "Object: PFCandidate " << std::endl;
    os << " p4 = " << p4 << std::endl;
	os << " charge = "      << charge;
	os << " chi2 = "        << chi2 << std::endl;
	os << " dxy = "         << dxy_BS;
	os << " dxy_BS = "      << dxy_BS;
	os << " dxyError = "    << dxyError << std::endl;
	os << " d0 = "          << d0();
	os << " d0Error  = "    << d0Error();
	os << " dz = "          << dz;
	os << " dzError = "     << dzError;
	os << " NHitTracker = " << nHitTracker << std::endl;
 	
	os << " dz_firstGoodVertex = " << dz_firstGoodVertex << std::endl;
	os << " trackIso = " << trackIso << std::endl;
    os << " 'others' collection content : " << others.size();
    others.Dump(os);
	
	os << std::endl;
}

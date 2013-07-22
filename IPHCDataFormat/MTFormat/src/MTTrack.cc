#include "../interface/MTTrack.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTTrack::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTTrack::Reset(constructor_call);
  }
  withFirstPixel = false;	
  nHitPXB        = 0;
  nHitPXF        = 0;
  nHitTIB        = 0;
  nHitTOB        = 0;
  nHitTID        = 0;
  nHitTEC        = 0;
  IP3Dsig        = -999;	 
  IP3D           = -999;		   
  IP3Derr        = -999;	 
  IP2Dsig        = -999;	 
  IP2D           = -999;      
  IP2Derr        = -999;   
  Prob3D         = -999;	   
  Prob2D         = -999;	   
  DecayLength    = -999;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTTrack::Dump(std::ostream & os) const
{
  NTTrack::Dump(os);
	os << " withFirstPixel = " << withFirstPixel;
	os << " nHitPixel = "      << nHitPixel() << " ( ";
	os << " nHitPXB = "        << nHitPXB;
	os << " nHitPXF = "        << nHitPXF << " )" << std::endl;
	os << " nHitTracker = "    << nHitTracker() << " ( ";
	os << " nHitTIB = "        << nHitTIB;
	os << " nHitTOB = "        << nHitTOB;
	os << " nHitTID = "        << nHitTID;
	os << " nHitTEC = "        << nHitTEC << " )" << std::endl;
	os << " IP3Dsig = "        << IP3Dsig;
	os << " IP3D = "           << IP3D;
	os << " IP3Derr = "        << IP3Derr << std::endl;
	os << " IP2Dsig = "        << IP2Dsig;
	os << " IP2D = "           << IP2D;
	os << " IP2Derr = "        << IP2Derr << std::endl;
	os << " Prob3D = "         << Prob3D;
	os << " Prob2D = "         << Prob2D;
	os << " DecayLength = "    << DecayLength << std::endl;
}

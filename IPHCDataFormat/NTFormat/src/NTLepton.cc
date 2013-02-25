#include "../interface/NTLepton.h"
#include "../interface/DisplayTool.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTLepton::Reset(bool constructor_called)
{
  if (!constructor_called)
  {
    NTParticle::Reset();
    vertex.SetXYZ(0.,0.,0.);
    ID.Reset();
  }

  isolation.Reset();

   // ------------------ general variables ------------------------
  charge_bit_ = false;
  charge  = 0.;
  LeptonOrigin = -999;

  // ------------- Information related to the track ----------------
  D0   = -999.;
  Chi2 = -999.;

  // ------------- Information related to vertex ----------------
  dxy_vertex = 999.0;
  dz_vertex = 999.0;

}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTLepton::Dump(std::ostream & os) const
{
    NTParticle::Dump(os);
  
    os << " isolation collection content : " << isolation.size();
    isolation.Dump(os);

    os << " vertex = " << vertex << std::endl;

	os << " Charge = " << charge << " ;";
	os << " D0 = "<< D0 << " ;";
	os << " Chi2 = "<< Chi2 <<" ;";
	os << " LeptonOrigin =  " << LeptonOrigin << std::endl;

  	os << " dxy_vertex = " << dxy_vertex << " ;";
 	os << " dz_vertex = " << dz_vertex << std::endl;

	os << std::endl;
}


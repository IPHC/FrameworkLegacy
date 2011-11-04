#include "../interface/NTLepton.h"

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

   // ------------------ general variables ------------------------
  charge_ = false;
  charge  = 0.;
  LeptonOrigin = -999;

  // ---------- isolation variables (cone of deltaR<0.3) -----------
  TrkIso03   = -999.;
  ECaloIso03 = -999.;
  HCaloIso03 = -999.;

  // ------------ ParticleFlow isolation variables -----------------
  PATNeutralHadronIso = -999.;
  PATChargedHadronIso = -999.;
  PATPhotonIso        = -999.;
  PATTrackIso         = -999.; 

  // ------------- Information related to the track ----------------
  D0   = -999.;
  Chi2 = -999.;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTLepton::Dump(std::ostream & os) const
{
  NTParticle::Dump(os);
  os << "vertex: ";
  NTParticle::PrintP3(vertex, os); 
 	os << std::endl;
	os << " Charge = "<< getCharge() <<" ";
	os << " D0 =  "<< D0 <<" ";
	os << " Chi2 =  "<< Chi2 <<" ";
	os << " LeptonOrigin =  " << LeptonOrigin << " " << std::endl;
	os << " CaloIso03 = " << CaloIso03() <<" (";
	os << " ECaloIso03 = " << ECaloIso03 <<" + ";
	os << " HCaloIso03 = " << HCaloIso03 <<" )";
	os << " TrkIso03 = " << TrkIso03 <<std::endl;
	os << " PATNeutralHadronIso = " << PATNeutralHadronIso << " ";
	os << " PATChargedHadronIso = " << PATChargedHadronIso << " ";
	os << " PATPhotonIso = " << PATPhotonIso << " ";
	os << " PATTrackIso = " << PATTrackIso << std::endl;
	os << std::endl;
  ID.Dump(os);
}


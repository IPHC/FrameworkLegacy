#include "../interface/NTMonteCarlo.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTMonteCarlo::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    eventType    = "";
    partonFlavor = std::make_pair(0,0);
    x            = std::make_pair(0.,0.);

    // Clearing containers
    Generatedtaus.clear();
    GeneratedAtaus.clear();
    genBquarks.clear();
    genCquarks.clear();
    genLquarks.clear();
    genGquarks.clear();
    wAndDecays.clear();
    zAndDecays.clear();
    topAndDecays.clear();
  }
  procId               = 0;
  ptHat                = 0;
  Q_scale              = 0.;
  TMEME                = 0;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTMonteCarlo::Dump(std::ostream & os) const
{
  // Global information
	os << "MonteCarlo global information : " << std::endl;
	os << " EventType: "  << eventType;
  os << " ProcessId = " << procId;
	os << "Initial partons (pdgId) = " << partonFlavor.first;
  os << " & " << partonFlavor.second << std::endl; 
  os << " x = " << x.first << " & " << x.second << std::endl;
  os << " ptHat = "  << ptHat;
  os << " Qscale = " << Q_scale;
  os << " TMEME = "  << TMEME << std::endl;
}

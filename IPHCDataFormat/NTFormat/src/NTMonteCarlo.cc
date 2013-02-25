#include "../interface/NTMonteCarlo.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTMonteCarlo::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    partonFlavor = std::make_pair(0,0);
    x            = std::make_pair(0.,0.);
    xpdf         = std::make_pair(0.,0.);

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
  ptHat                = -999.;
  Q_scale              = -999.;
  TMEME                = -999;
 
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTMonteCarlo::Dump(std::ostream & os) const
{
  // Global information
	os << "MonteCarlo global information : " << std::endl;
	os << " Initial partons (pdgId) = "; 
  os << static_cast<signed int>(partonFlavor.first);
  os << " & " << static_cast<signed int>(partonFlavor.second);
  os << std::endl; 
  os << " x = " << x.first << " & " << x.second << std::endl;
  os << " ptHat = "  << ptHat << " ;";
  os << " Qscale = " << Q_scale << " ;";
  os << " TMEME = "  << TMEME << std::endl;
  os << " Nb genParticles saved = " << genParticles.size() << std::endl;
  os << " ------------------- old monte carlo ------------------- " << std::endl;
  os << " Nb taus = "  << Generatedtaus.size() << " ;";
  os << " Nb ataus = " << GeneratedAtaus.size() << std::endl;
  os << " Nb Bquarks = " << genBquarks.size() << " ;";
  os << " Nb Cquarks = " << genCquarks.size() << " ;";
  os << " Nb Lquarks = " << genLquarks.size() << " ;";
  os << " Nb Gquarks = " << genGquarks.size() << std::endl;
  os << " Nb wAndDecays = " << wAndDecays.size() << " ;";
  os << " Nb zAndDecays = " << zAndDecays.size() << " ;";
  os << " Nb topAndDecays = " << topAndDecays.size();
  os << std::endl;
}


// ---------------------------------------------------------------------------
// PrintParticleDaughters
// ----------------------------------------------------------------------------
void NTMonteCarlo::PrintParticleDaughters(const IPHCTree::NTGenParticle* part, 
                            unsigned int descent,
                            std::ostream & os)
{
  if (part==0) {os << std::endl; return;}

  for (unsigned int i=0;i<part->daughters.size();i++)
  {
    for (unsigned int j=0;j<descent;j++) {os.width(10); os << std::left << " ";}
    os.width(10); os << std::left;
    os << (part->daughters)[i]->id << " -> " << std::endl;
    PrintParticleDaughters((part->daughters)[i],descent+1,os);
  }
}


// ---------------------------------------------------------------------------
// DumpGenParticles
// ----------------------------------------------------------------------------
void NTMonteCarlo::DumpGenParticles(std::ostream & os) const
{
	os << "Cascade process : " << std::endl;
  if (genParticles.size()<2) return;

  const IPHCTree::NTGenParticle* currentPart = &(genParticles[0]); 
  PrintParticleDaughters(currentPart,0,os);
 
  currentPart = &(genParticles[1]); 
  PrintParticleDaughters(currentPart,0,os);
}

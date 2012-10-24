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
  deltaCotTheta   = -999;
  deltaDistance   = -999;
  nLost           = 0;

  isEE = false;

  etaSuperCluster = 999.0;
  hadOverEM = 999.0;
  abs_deltaPhi = 999.0;
  abs_deltaEta = 999.0;
  sigmaIetaIeta = 999.0;

  conversionRejection = false;
			
  // Isolation-related infos
  Aeff = 999.0;
  chargedIso = 999.0;
  photonIso = 999.0;
  neutralIso = 999.0;
  rho = 999.0;

  missingHits = 999.0; 
  dxy_vertex = 999.0;
  dz_vertex = 999.0;

  // Matching between reco and PF infos
  bestRecoMatch_eta = 999.0;
  bestRecoMatch_phi = 0.0;
  bestRecoMatch_dR = 999.0;
  bestRecoMatch_pT = -999.0;

}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTElectron::Dump(std::ostream & os) const
{
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: Electron " << std::endl;
  NTLepton::Dump(os);

  os << " isEB = "          << static_cast<unsigned int>(isEB) << " ;"; 
  os << " isEE = " 			<< static_cast<unsigned int>(isEE) << " ; ";
  os << " isEcalDriven = "  << static_cast<unsigned int>(isEcalDriven) << " ;";
  os << " ET_SC = "         << ET_SC << std::endl;

  os << " deltaCotTheta = " << deltaCotTheta << " ;";
  os << " deltaDistance = " << deltaDistance << std::endl;

  os << " isGsfElectron = " << isGsfElectron << " ;";
  os << " nLost = " << nLost << std::endl;

  os << " etaSuperCluster = " << etaSuperCluster << " ;";
  os << " hadOverEM = " << hadOverEM << " ;";
  os << " missingHits = " << missingHits << " ;"; 
  os << " abs_deltaPhi = " << abs_deltaPhi << " ;";
  os << " abs_deltaEta = " << abs_deltaEta << " ;";
  os << " sigmaIetaIeta = " << sigmaIetaIeta << std::endl;

  os << " conversionRejection = " << static_cast<unsigned int>(conversionRejection) << std::endl;

  // Isolation-related infos
  os << " Aeff = " << Aeff << " ; ";
  os << " chargedIso = " << chargedIso << " ;";
  os << " photonIso = " << photonIso << " ;";
  os << " neutralIso = " << neutralIso << " ;";
  os << " rho = " << rho << std::endl;

  os << " dxy_vertex = " << dxy_vertex << " ;";
  os << " dz_vertex = " << dz_vertex << std::endl;

  // Matching between reco and PF infos
  os << " bestRecoMatch_eta = " << bestRecoMatch_eta << " ;";
  os << " bestRecoMatch_phi = " << bestRecoMatch_phi << " ;";
  os << " bestRecoMatch_dR = " << bestRecoMatch_dR << " ;";
  os << " bestRecoMatch_pT = " << bestRecoMatch_pT << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}
 
  

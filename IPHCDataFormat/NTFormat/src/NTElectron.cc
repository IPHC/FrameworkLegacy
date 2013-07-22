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

  deltaEtaSuperClusterTrackAtVtx = 999.0;
  deltaPhiSuperClusterTrackAtVtx = 999.0;

  hadronicOverEm = 999.0;
  sigmaIetaIeta = 999.0;

  EmEnergy_ = 999.0;
  eSuperClusterOverP = 999.0;

  isEE = false;

  etaSuperCluster = 999.0;

  passConversionVeto = false;
  missingHits = 999.0; 
			
  // Matching between reco and PF infos
  bestMatch_eta = 999.0;
  bestMatch_phi = 0.0;
  bestMatch_dR = 999.0;
  bestMatch_pT = -999.0;

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

  os << " deltaEtaSuperClusterTrackAtVtx = " << deltaEtaSuperClusterTrackAtVtx << " ;";
  os << " deltaPhiSuperClusterTrackAtVtx = " << deltaPhiSuperClusterTrackAtVtx << std::endl;

  os << " hadronicOverEm = " << hadronicOverEm << " ;";
  os << " sigmaIetaIeta = " << sigmaIetaIeta << std::endl;

  os << " EmEnergy_ = " << EmEnergy_ << " ;";
  os << " eSuperClusterOverP = " << eSuperClusterOverP << std::endl;

  os << " etaSuperCluster = " << etaSuperCluster << " ;";
  os << " missingHits = " << missingHits << " ;"; 

  os << " passConversionVeto = " << static_cast<unsigned int>(passConversionVeto) << std::endl;

  // Matching between reco and PF infos
  os << " bestRecoMatch_eta = " << bestMatch_eta << " ;";
  os << " bestRecoMatch_phi = " << bestMatch_phi << " ;";
  os << " bestRecoMatch_dR = " << bestMatch_dR << " ;";
  os << " bestRecoMatch_pT = " << bestMatch_pT << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}
 
  

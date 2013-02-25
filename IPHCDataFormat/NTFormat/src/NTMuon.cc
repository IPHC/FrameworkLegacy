#include "../interface/NTMuon.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTMuon::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTLepton::Reset();
  }
  isGlobalMuon     = false;
  isStandaloneMuon = false;
  isTrackerMuon    = false;
  isCaloMuon       = false;
  NValidHits       = 0;
  NTrValidHits     = 0;
  NOfMatches       = 0;
  D0Inner          = 0;

  isPFMuon		   = false;

  numMatchedStations = 0;
  numTrackerLayersWithMeasurement = 0;
  pixelHits = 0;

  bestMatch_eta = 0.0;
  bestMatch_phi = 0.0;
  bestMatch_dR = 999.0;
  bestMatch_pT = 0.0;

}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTMuon::Dump(std::ostream & os) const
{
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: Muon " << std::endl;
	NTLepton::Dump(os);

	os << " MuonType = " << MuonType() << " ( ";
  os << "Global=" << static_cast<unsigned int>(isGlobalMuon);
  os << " , ";
  os << "Standalone=" << static_cast<unsigned int>(isStandaloneMuon);
  os << " , ";
  os << "Tracker=" << static_cast<unsigned int>(isTrackerMuon);
  os << " , ";
  os << "Calo=" << static_cast<unsigned int>(isCaloMuon);
  os << " )" << std::endl;

  os << " NValidHits = " << NValidHits << " ;";
  os << " NTrValidHits = " << NTrValidHits << " ;";
  os << " NOfMatches = " << NOfMatches << " ;";
  os << " D0Inner = " << D0Inner << std::endl;

  os << " isPFMuon = " << static_cast<unsigned int>(isPFMuon) << std::endl;

  os << " numMatchedStations = " << numMatchedStations << " ;";
  os << " numTrackerLayersWithMeasurement = " << numTrackerLayersWithMeasurement << " ;";
  os << " pixelHits = " << pixelHits << std::endl;

  os << " bestRecoMatch_eta = " << bestMatch_eta << " ;";
  os << " bestRecoMatch_phi = " << bestMatch_phi << " ;";
  os << " bestRecoMatch_dR = " << bestMatch_dR << " ;";
  os << " bestRecoMatch_pT = " << bestMatch_pT << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}

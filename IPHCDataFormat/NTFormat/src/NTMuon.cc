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
  pfIsoCharged     = 999.0;
  pfIsoNeutral     = 999.0;
  pfIsoPhoton      = 999.0;
  pfIsoPU          = 999.0;

  numMatchedStations = 0;
  numTrackerLayersWithMeasurement = 0;
  nValMuonHits = 0;
  pixelHits = 0;

  dxy_vertex = 999.0;
  dz_vertex = 999.0;

  bestRecoMatch_eta = 0.0;
  bestRecoMatch_phi = 0.0;
  bestRecoMatch_dR = 999.0;
  bestRecoMatch_pT = 0.0;

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
  os << " pfIsoCharged = " << pfIsoCharged << " ;";
  os << " pfIsoNeutral = " << pfIsoNeutral << " ;";
  os << " pfIsoPhoton = " << pfIsoPhoton << " ;";
  os << " pfIsoPU = " << pfIsoPU << std::endl;

  os << " numMatchedStations = " << numMatchedStations << " ;";
  os << " numTrackerLayersWithMeasurement = " << numTrackerLayersWithMeasurement << " ;";
  os << " nValMuonHits = " << nValMuonHits << " ;";
  os << " pixelHits = " << pixelHits << std::endl;

  os << " dxy_vertex = " << dxy_vertex << " ;";
  os << " dz_vertex = " << dz_vertex << std::endl;

  os << " bestRecoMatch_eta = " << bestRecoMatch_eta << " ;";
  os << " bestRecoMatch_phi = " << bestRecoMatch_phi << " ;";
  os << " bestRecoMatch_dR = " << bestRecoMatch_dR << " ;";
  os << " bestRecoMatch_pT = " << bestRecoMatch_pT << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}

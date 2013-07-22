#include "../interface/MTJet.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/DisplayTool.h"

using namespace IPHCTree;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTJet::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    uncorrJet.SetPxPyPzE(0.,0.,0.,0.);
    TracksOfJet.clear();
    trackassociatedVec.clear();
    vertex.SetXYZ(0.,0.,0.);
  }
  NTJet::Reset(constructor_call);
  scale                = -999.;		
  isLOOSE              = false;		
  isTIGHT              = false;		
  jetArea              = -999.;
  emEnergyFraction_    = -999.;	
  CHEF                 = -999.;
  CEEF                 = -999.;		
  NHEF                 = -999.;		
  NEEF                 = -999.;		
  n90Hits              = 0;	
  fHPD                 = -999.;		
  nTracksSVX           = 0;		
  nSVX                 = 0;			
  chi2SVX              = -999.;		
  ndofSVX              = 0;		
  flightDistanceSVX    = -999.;
  flightDistanceSigSVX = -999.;
  flightDistanceErrSVX = -999.;
  MassSVX              = -999.;	
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTJet::Dump(std::ostream & os) const
{
  NTJet::Dump(os);
  os << " uncorrJet p4 = " << uncorrJet << std::endl;
  os << " vertex = " << vertex << std::endl;
  os << " container 'TracksOfJet' size = " << TracksOfJet.size();
  os << " container 'trackassociatedVec' size = " << trackassociatedVec.size();
  os << std::endl;
  os << " scale = " << scale;
  os << " isLOOSE = " << isLOOSE;
  os << " isTIGHT = " << isTIGHT << std::endl;
  os << " jetArea = " << jetArea;
  os << " emEnergyFraction = " << emEnergyFraction();
  os << " hadEnergyFraction = " << hadEnergyFraction() << std::endl;
  os << " CHEF = " << CHEF;
  os << " CEEF = " << CEEF; 
  os << " NHEF = " << NHEF;
  os << " NEEF = " << NEEF << std::endl;
  os << " n90Hits = " << n90Hits;
  os << " fHPD = "    << fHPD;
  os << " nTracksSVX" << nTracksSVX;
  os << " nSVX"       << nSVX;
  os << " chi2SVX"    << chi2SVX;
  os << " ndofnSVX"   << ndofSVX << std::endl;
  os << " flightDistanceSVX = "    << flightDistanceSVX;   
  os << " flightDistanceSigSVX = " << flightDistanceSigSVX;
  os << " flightDistanceErrSVX = " << flightDistanceErrSVX;
  os << " MassSVX = "              << MassSVX << std::endl;           
}


// ---------------------------------------------------------------------------
// setTracks
// ----------------------------------------------------------------------------
void MTJet::setTracks (const reco::TrackRefVector & trk_)
{
  for (unsigned int itk = 0; itk < trk_.size (); itk++)
  {
    const reco::Track tk = *trk_[itk];
    TracksOfJet.push_back (tk);
  }
}

#include "../interface/NTTau.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTTau::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    NTLepton::Reset(constructor_call);
  }
  leadTrackPt                      = -999.;
  numSigConeTracks                 =   999;
  numIsoConeTracks                 =   999;
  isolationPFChargedHadrCandsPtSum = -999.;
  isolationPFGammaCandsEtSum       = -999.;
  maximumHCALPFClusterEt           = -999.;
  emFraction                       = -999.;
  hcalTotOverPLead                 = -999.;
  hcalMaxOverPLead                 = -999.;
  hcal3x3OverPLead                 = -999.;
  ecalStripSumEOverPLead           = -999.; 
  decayMode                        =  -999;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTTau::Dump(std::ostream & os) const
{
  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;

	os << "Object: Tau " << std::endl;
  NTLepton::Dump(os);

  os << " decay mode = "               << decayMode << std::endl;

	os << " leadTrackPt = "              << leadTrackPt << " ;";
	os << " numSigConeTracks = "         << numSigConeTracks << " ;";
	os << " numIsoConeTracks = "         << numIsoConeTracks << std::endl;
  os << " maximumHCALPFClusterEt = "   << maximumHCALPFClusterEt << " ,";
	os << " emFraction = "               << emFraction << std::endl;
	os << " hcalTotOverPLead = "         << hcalTotOverPLead << " ;";
	os << " hcalMaxOverPLead = "         << hcalMaxOverPLead << " ;";
	os << " hcal3x3OverPLead = "         << hcal3x3OverPLead << " ;";
	os << " ecalStripSumEOverPLead = "   << ecalStripSumEOverPLead << std::endl;

  for (unsigned int i=0;i<80;i++) os << "-"; os << std::endl;
}



#include "../interface/MTElectron.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTElectron::Reset(bool constructor_call)
{
  if (!constructor_call)
  {
    MTLepton::Reset();
    NTElectron::Reset();
  }
  hcalOverEcal    = -999;
  e2x5Max         = -999;
  e5x5            = -999;
  fbrem           = -999;
  caloEnergy      = -999;
  deltaEtaSeedClusterTrackAtCalo = -999;
  deltaPhiSeedClusterTrackAtCalo = -999;
  rawSCEnergy     = -999;
  classification  = -999;
  TrkIso04        = -999;
  ECaloIso04      = -999;
  HCaloIso04      = -999;
  TrkPt           = -999;
  TrkZ0           = -999;
  IP3D            = -999;
  IP3DErr         = -999;
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTElectron::Dump(std::ostream & os) const
{
  NTElectron::Dump(os);
  MTLepton::Dump(os);
  os << " TrackEl pT = " << TrackEl.pt() << std::endl;
  os << " hcalOverEcal = " << hcalOverEcal;
  os << " e2x5Max = " << e2x5Max;
  os << " e5x5 = " << e5x5 << std::endl; 
  os << " fbrem = " << fbrem << std::endl;
  os << " caloEnergy = " << caloEnergy;
  os << " deltaEtaSeedClusterTrackAtCalo = " << deltaEtaSeedClusterTrackAtCalo;
  os << " deltaPhiSeedClusterTrackAtCalo = " << deltaPhiSeedClusterTrackAtCalo;
  os << std::endl;
  os << " rawSCEnergy = " << rawSCEnergy;
  os << " classification = " << classification << std::endl;
  os << " emEnergyFraction = " << emEnergyFraction();
  os << " hadEnergyFraction = " << hadEnergyFraction() << std::endl;
  os << " TrkIso04 = " << TrkIso04;
  os << " ECaloIso04 = " << ECaloIso04;
  os << " HCaloIso04 = " << HCaloIso04 << std::endl; 
  os << " TrkPt = " << TrkPt;
  os << " TrkZ0 = " << TrkZ0 << std::endl;
  os << " IP3D = " << IP3D << " with error ";
  os << IP3DErr << std::endl;
}

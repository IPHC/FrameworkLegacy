#ifndef __IPHC_TREE_MTELECTRON_H__
#define __IPHC_TREE_MTELECTRON_H__

// CMSSW headers
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"

// IPHC headers
#include "MTLepton.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTElectron.h"


namespace IPHCTree
{

  /// \class MTElectron
  /// Class electron for MiniTree - inherit from NTElectron 
  /// default track = gsfTrack
  /// D0 = Transverse IP of gsfTrack  wrt BS (or 0 if !BS)
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTElectron : public NTElectron, public MTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// to do
    Float_t hcalOverEcal;

    /// to do
    Float_t e2x5Max;

    /// to do
    Float_t e5x5;

    /// to do
    Float_t fbrem;
    
    /// to do
    Float_t caloEnergy;

    /// to do
    Float_t deltaEtaSeedClusterTrackAtCalo;

    /// to do
    Float_t deltaPhiSeedClusterTrackAtCalo;

    /// to do
    Float_t rawSCEnergy;

    /// to do
    Int_t classification;

    // ---------- isolation variables (cone of deltaR<0.3) -----------

     /// Summed track PT (in a cone of deltaR<0.4)
    Float_t TrkIso04;

    /// ECAL isolation depositfrom RecHits
    /// with electron footprint removed (in a cone of deltaR<0.4)
    Float_t ECaloIso04;

    /// HCAL isolation deposit from Calo Towers (in a cone of deltaR<0.4)
    Float_t HCaloIso04;

    // ------------------------ Track --------------------------------

    reco::GsfTrack TrackEl;	/// associated GsfTrack to the electron
    Float_t TrkPt;            /// track PT 
    Float_t TrkZ0;            /// track z0  

    // IP variables   
    Float_t IP3D;          /// 3D impact parameter wrt primary vertex
    Float_t IP3DErr;       /// 3D impact parameter error 


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTElectron()
    { Reset(true); }

		/// Destructor
    virtual ~MTElectron()
    { }

		/// Clear all information related to electron
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the electron
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Get the Sum of ECaloIso04 and HCaloIso04
    float CaloIso04() const
    { return ECaloIso04 + HCaloIso04; }

    /// Get energy fraction which is hadronic
    float hadEnergyFraction() const
    { 
      if (EmEnergy_==-999) return -999;
      else return 1-EmEnergy_;
    }

    /// Get energy fraction which is electromagnetic
    float emEnergyFraction() const
    { return EmEnergy_; }


  };
}
#endif

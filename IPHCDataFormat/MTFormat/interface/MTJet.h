#ifndef __IPHC_TREE_MTJET_H__
#define __IPHC_TREE_MTJET_H__

// STL headers
#include <map>
#include <vector>
#include <string>

// ROOT headers
#include "TVector3.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTJet.h"

// IPHC headers (NTuple format)
#include "MTTrack.h"

// CMSSW headers
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/JetReco/interface/JetTracksAssociation.h"
#include "DataFormats/TrackReco/interface/Track.h"


namespace IPHCTree
{

  /// \class MTJet
  /// class jet for MiniTree - inherit from NTJet 
  /// Contains collections of tracks and the vertex.
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTJet : public NTJet
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// Jet correction factor(from L1+L2+L3 corrections to raw)
    Float_t scale;		

    /// JetId criteria (LOOSE PURE09 for CaloJet, LOOSE FIRSTDATA for PFJet)  
    Bool_t isLOOSE;		

    /// JetId criteria (TIGHT PURE09 for CaloJet, TIGHT FIRSTDATA for PFJet)  
    Bool_t isTIGHT;		

    /// Add the possibility to recorrect at NTuple level
    /// (while producing NTUple from Minitree)
    TLorentzVector uncorrJet;

    /// jet Area
    Float_t jetArea;

    /// vertex
    TVector3 vertex;

    /// Tracks associated to the jet
    std::vector<reco::Track> TracksOfJet;

    /// Tracks associated to the jet from the IP taggerr
    std::vector<MTTrack> trackassociatedVec;

    /// Constituents of the jets (might come from PfCandidates
    std::vector<TLorentzVector> constituents;

    // ---------------------- jet identification ---------------------

    /// jet electromagnetic energy fraction  // ( not defined for pfjet)
    Float_t emEnergyFraction_;	

    /// Charged Hadronic Energy Fraction
    Float_t CHEF;		

    /// Charged Electromagnetic Energy Fraction  (for Pf jet ID) 
    Float_t CEEF;		

    /// Neutral Hadronic Energy Fraction
    Float_t NHEF;		

    /// Neutral Electromagnetic Energy Fraction
    Float_t NEEF;		

    /// Number of recHits (i.e. cells) needed to make up 90% of 
    /// the jet's energy (!= n90 == Number of towers (i.e. cells)
    /// needed to make up 90% of the jet's energy(not for pfjet)
    UInt_t n90Hits;	

    /// fraction of jet energy from the highest energy 
    /// Hybrid Photo Diode (not for pfjet)
    Float_t fHPD;		

    /// ------------------ info on secondary vertex -------------------

    /// number of tracks from SV tagger (== IP tagger)
    UInt_t nTracksSVX;		

    /// number of Secondary Vertices
    UInt_t nSVX;			

    /// chi2 of the best secondary vertex
    Float_t chi2SVX;		

    /// ndof of the best secondary vertex
    UInt_t ndofSVX;		

    /// distance (3D)  between primary and best secondary vertex
    Float_t flightDistanceSVX;

    /// distance significance (3D) between primary and secondary vertex
    Float_t flightDistanceSigSVX;

    /// distance error (3D) between primary and secondary vertex
    Float_t flightDistanceErrSVX;

    /// invariant mass of the best secondary vertex
    Float_t MassSVX;	


    // -------------------------------------------------------------
    //                         method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTJet()
    { Reset(true); }

		/// Destructor
    virtual ~MTJet()
    {}

		/// Clear all information related to the particle
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the jet
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Fill the Track collection
    void setTracks (const reco::TrackRefVector &);

    /// Get energy fraction which is hadronic
    float hadEnergyFraction() const
    { 
      if (emEnergyFraction_==-999) return -999;
      else return 1-emEnergyFraction_;
    }

    /// Get energy fraction which is electromagnetic
    float emEnergyFraction() const
    { return emEnergyFraction_; }

    /// methods to instanciate a new object
    MTTrack* NewTrack()
    { trackassociatedVec.push_back(MTTrack());
      return &trackassociatedVec.back(); }

    /// methods to instanciate a new object
    void NewTrack (const MTTrack& track)
    { trackassociatedVec.push_back(track); }

  };
}
#endif

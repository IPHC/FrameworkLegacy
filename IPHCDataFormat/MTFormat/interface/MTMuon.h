#ifndef __IPHC_TREE_MTMUON_H__
#define __IPHC_TREE_MTMUON_H__

// CMSSW headers
#include "DataFormats/TrackReco/interface/Track.h"

// IPHC headers (NTuple format)
#include "../../NTFormat/interface/NTMuon.h"

// IPHC headers
#include "MTLepton.h"


namespace IPHCTree
{

  /// \class MTMuon: 
  /// \brief class muon for MiniTree - inherit from NTMuon
  /// default track = globalTrack (tracker+mu)
  /// D0   =   Transverse IP of globalTrack (tracker+mu) wrt BS (or 0 if !BS)
  /// Chi2 =   Normalized chi2 of globalTrack wrt BS (or 0 if !BS)
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTMuon : public NTMuon, public MTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //Tracks 
    reco::Track TrackMu;	/// associated track (tracker only) for muon
    reco::Track StaMu;		/// associated standalone track
    reco::Track ComMu;		/// associated combined track

    //IP variables
    Float_t IP3D;    /// Impact parameter    
    Float_t IP3DErr; /// Impact parameter error


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTMuon()
    { Reset(true); }

		/// Destructor
    virtual ~MTMuon()
    { }

		/// Clear all information related to the muon
    void Reset(bool constructor_call=false);

		/// Display information related to the muon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

  };
}
#endif

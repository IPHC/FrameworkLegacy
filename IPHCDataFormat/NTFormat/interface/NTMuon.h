#ifndef __IPHC_TREE_NTMUON_H__
#define __IPHC_TREE_NTMUON_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTLepton.h"


namespace IPHCTree
{

  /// \class NTMuon
  /// class muon for NTuple.
  /// default track = globalTrack (tracker+mu)
  class NTMuon : public NTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

   	Bool_t isGlobalMuon;
    Bool_t isStandaloneMuon;
    Bool_t isTrackerMuon;
    Bool_t isCaloMuon;

    // ------------------- associated track ------------------------

    UShort_t  NValidHits;  /// Nb of valid hits associated to the global track
    UShort_t  NTrValidHits;/// Nb of valid hits associated to the innerTrack
    UShort_t  NOfMatches;  /// Nb of matches 
    Float_t   D0Inner;		 /// Transverse IP from tracks

    // ----------- Infos used is SUSYstop selection ----------------
	
	// Is the muon coming from particle flow ?
	Bool_t isPFMuon;

	// Infos from muon->pfIsolationR03()
	Float_t pfIsoCharged;
	Float_t pfIsoNeutral;
	Float_t pfIsoPhoton;
	Float_t pfIsoPU;

	// 
	UShort_t numMatchedStations;
	UShort_t numTrackerLayersWithMeasurement;
	UShort_t nValMuonHits;
	UShort_t pixelHits;

	// dxy, dz with respect to the primary vertex (not the beamspot)
	Float_t dxy_vertex;
	Float_t dz_vertex;

	// Info for matching with reco objects
	Float_t bestRecoMatch_eta;
	Float_t bestRecoMatch_phi;
	Float_t bestRecoMatch_dR;
	Float_t bestRecoMatch_pT;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTMuon()
    { Reset(true); }

		/// Destructor
    virtual ~NTMuon()
    { }

		/// Clear all information related to the muon
    void Reset(bool constructor_call=false);

		/// Display information related to the muon
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    unsigned int MuonType() const
		{
      // MuonType =   IsGlobalMuon     * 100 
      //            + IsStandAloneMuon * 10
      //            + IsTrackerMuon    * 1; 
			unsigned id=0;
      if (isTrackerMuon)    id += 1;
      if (isStandaloneMuon) id += 10;
      if (isGlobalMuon)     id += 100;
			return id;
		}

  };
}
#endif

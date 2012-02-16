
#ifndef __IPHC_TREE_MTTRACK_H__
#define __IPHC_TREE_MTTRACK_H__

// IPHC headers (Ntuple format)
#include "../..//NTFormat/interface/NTTrack.h"

namespace IPHCTree
{

  /// \class MTTrack
  /// class track for MiniTree - inherit from NTTrack
  /// Contains nHits for subdectectors and IPs.
  /// Add all relevant information that should be saved in MiniTree
  /// but not in the NTuple
  class MTTrack : public NTTrack
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // --------------------- number of hits ------------------------

    Bool_t withFirstPixel;	  // Has Valid Hit in first Pixel Barrel ?
    UInt_t nHitPXB;		// Number of Valid Hits in Pixel Barrel
    UInt_t nHitPXF;		// Number of Valid Hits in Pixel EndCap
    UInt_t nHitTIB;		// Number of Valid Hits in Strip TIB
    UInt_t nHitTOB;		// Number of Valid Hits in Strip TOB
    UInt_t nHitTID;		// Number of Valid Hits in Strip TID
    UInt_t nHitTEC;		// Number of Valid Hits in Strip TEC

    // ------------------- impact parameter ------------------------

    Float_t IP3Dsig;	    // track 3D signed impact parameter significance
    Float_t IP3D;		      // track 3D signed impact parameter
    Float_t IP3Derr;	    // track 3D impact parameter error
    Float_t IP2Dsig;	    // track 2D signed impact parameter significance
    Float_t IP2D;         // track 2D signed impact parameter
    Float_t IP2Derr;      // track 2D impact parameter error
    Float_t Prob3D;	      // 2D track probability (IP)
    Float_t Prob2D;	      // 3D track probability (IP)
    Float_t DecayLength;	// track decay length (from PV)

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    MTTrack ()
    { Reset(true); }

    /// Destructor
    virtual ~MTTrack ()
    { }

		/// Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the lepton
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Number of Valid Hits
    unsigned int nHitPixel() const
    { return nHitPXB + nHitPXF; }

    /// Number of Valid Pixel Hits
    unsigned int nHitTracker() const
    { return nHitTIB + nHitTOB + nHitTID + nHitTEC; }

  };
}
#endif

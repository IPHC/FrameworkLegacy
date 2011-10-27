#ifndef __IPHC_TREE_NTMUON_H__
#define __IPHC_TREE_NTMUON_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTLepton.h"


namespace IPHCTree
{

  //! \class NTMuon
  //! class muon for NTuple.
  //! default track = globalTrack (tracker+mu)
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

    UInt_t  NValidHits;  //! Nb of valid hits associated to the global track
    UInt_t  NTrValidHits;//! Nb of valid hits associated to the innerTrack
    UInt_t  NOfMatches;  //! Nb of matches 
    Float_t D0Inner;		 //! Transverse IP from tracks


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    NTMuon()
    { Reset(true); }

		//! Destructor
    virtual ~NTMuon()
    { }

		//! Clear all information related to the muon
    void Reset(bool constructor_call=false);

		//! Display information related to the muon
    //! \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    unsigned int MuonType() const
		{
      // MuonType =   IsGlobalMuon     * 100 
      //            + IsStandAloneMuon * 10
      //            + IsTrackerMuon    * 1; 
			unsigned id=0;
      if (isTrackerMuon)    id = id | 1;
      if (isStandaloneMuon) id = id | 2;
      if (isGlobalMuon)     id = id | 4;
			return id;
		}

  };
}
#endif

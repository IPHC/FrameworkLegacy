#ifndef __IPHC_TREE_NTTRACK_H__
#define __IPHC_TREE_NTTRACK_H__

// STL headers
#include <iostream>

// ROOT headers
#include "TLorentzVector.h"


namespace IPHCTree
{

  // \class NTTrack
  // class related to recoTrack for NTuple.
  class NTTrack
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    //! 4-vector momentum
    TLorentzVector p4;

    //! electric charge
    Bool_t charge_;

    //! normalized chi2
    Float_t chi2;

    //! number of valid hits in the tracker
    UInt_t nHitTracker;

    //! transverse impact parameter wrt to (0,0,0)
    //! ONLY if refPoint is close to (0,0,0)
    Float_t dxy;

    //! transverse impact parameter wrt to the beam spot
    //! Warning : only be interpreted as a minimum transverse
    //! distance if the beam spot is reasonably clost to the refPoint
    Float_t dxy_BS;

    //! error on transverse impact parameter
    Float_t dxyError;

    //! track z0 wrt (0,0,0) only if the refPoint is close to (0,0,0)
    //! = dsz/cos(lambda) 
    Float_t dz;

    //! error on dz
    Float_t dzError;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    NTTrack()
    { Reset(true); }

    //! Destructor
    ~NTTrack ()
    { }

		//! Clear all information related to the track
    void Reset(bool constructor_call=false);

		//! Display information related to the track
    //! \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    //! Access to d0 track parameter
    const Float_t d0() const
    { return -dxy; }

    //! Access to the error on d0 track parameter
    const Float_t d0Error() const
    { return dxyError; }

		//! Get the charge of the particle
    Float_t charge() const
		{
			if (charge_) return +1.;
			else return -1.;
		}

		//! Set the charge of the particle
    void setCharge(Float_t charge)
		{
      if (charge<0) charge_=false;
      else charge_=true;
		}
  
  };
}
#endif

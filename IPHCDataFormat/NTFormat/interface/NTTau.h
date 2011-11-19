#ifndef __IPHC_TREE_NTTAU_H__
#define __IPHC_TREE_NTTAU_H__

#include "NTLepton.h"


namespace IPHCTree
{

  // \class NTTau
  // class tau for NTuple.
  class NTTau : public NTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    /// Transverse momentum of the leading track
    Float_t leadTrackPt;

    /// Number of signal tracks
    UShort_t numSigConeTracks;

    /// Number of isolation tracks
    UShort_t numIsoConeTracks;

    /// PT sum of charged candidates in isolation region
    Float_t isolationPFChargedHadrCandsPtSum;

    /// ET sum of gamma candidates in isolation region
    Float_t isolationPFGammaCandsEtSum;

    /// Maximum ET of HCALcluster
    Float_t maximumHCALPFClusterEt;

    /// Electromagnetic fraction
    Float_t emFraction;

    /// to do
    Float_t hcalTotOverPLead;

    /// to do
    Float_t hcalMaxOverPLead;

    /// to do
    Float_t hcal3x3OverPLead;

    /// to do
    Float_t ecalStripSumEOverPLead;

    /// Hadronic decay id (see enumeration PFTau::HadronicDecayMode)
    Short_t decayMode;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTTau()
    { Reset(true); }

    /// Destructor
    virtual ~NTTau()
    { }

		/// Clear all information related to the tau
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the tau
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Access to a tau descriminator
    int GetDiscriminator(std::string discriminatorName)
    {
      //      float* value = ID.find(discriminatorName);
      //if (value==0) return -1;
      //else return (*value);
      return -1;
    }
    
  };
}
#endif

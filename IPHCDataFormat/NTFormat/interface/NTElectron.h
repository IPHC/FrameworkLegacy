#ifndef __IPHC_TREE_NTELECTRON_H__
#define __IPHC_TREE_NTELECTRON_H__

// IPHC headers
#include "NTLepton.h"
#include "KeyedCollection.h"

namespace IPHCTree
{
  /// \class NTElectron
  /// class electron for NTuple( default track = gsfTrack,
  /// D0 = Transverse IP of gsfTrack  wrt BS (or 0 if !BS) )
  class NTElectron: public NTLepton
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ---------------------- general info -------------------------

    /// Is coming from Ecal Barrel ?
    Bool_t isEB;

    /// Correspond to elec->ecalDrivenSeed() in PAT
    Bool_t isEcalDriven;

    /// ET of the SuperCluster
    Float_t ET_SC;

    // ---------------------- track info ---------------------------

    /// Is there a GSF track linked to the electron ?
    Bool_t isGsfElectron;

    /// Number of lost hits for the GSF tracks
    Short_t nLost;
 
    // ------------------- conversion info -------------------------

    /// to do
    Float_t deltaCotTheta;

    /// to do
    Float_t deltaDistance;


  public:
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------

    /// Constructor without arguments
    NTElectron()
    { Reset(true); }

		/// Destructor
    virtual ~NTElectron()
    { }

		/// Clear all information related to electron
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the electron
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Is not converted ?
    static bool isNotConv(int elecId) { return (elecId & 0x4);};

    /// Had Id ?
    static bool hadId(int elecId)     { return (elecId & 0x1);};
    
    // Isolation variable considering Barrel & EndCap
    float CombinedRelIso03() const
    {
      if (isEB)
      {
        return (TrkIso03 + TMath::Max(0.,ECaloIso03-1.) + HCaloIso03)
          / TMath::Max(20.,p4.Et());
      }
      else
      {
        return (TrkIso03 + ECaloIso03 +  HCaloIso03)
          / TMath::Max(20.,p4.Et());
      }
    }

  };
}
#endif

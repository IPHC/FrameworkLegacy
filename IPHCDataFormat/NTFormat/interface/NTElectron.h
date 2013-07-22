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

	// Eta for the superCluster
    Float_t etaSuperCluster;

    /// Is coming from Ecal Barrel ?
    Bool_t isEB;

	/// Is coming from Ecal Endcap ?
    Bool_t isEE;

    /// Correspond to elec->ecalDrivenSeed() in PAT
    Bool_t isEcalDriven;

    /// ET of the SuperCluster
    Float_t ET_SC;

	// deltaEta and deltaPhi
    Float_t deltaEtaSuperClusterTrackAtVtx;
    Float_t deltaPhiSuperClusterTrackAtVtx;

	// H/E
	Float_t hadronicOverEm;

	// Info related to shower shape
	Float_t sigmaIetaIeta;

    /// energy fraction which is electomagnetic
    Float_t EmEnergy_;

    /// to do (also called E/Pin)
    Float_t eSuperClusterOverP;

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
	
	Bool_t passConversionVeto;
	UShort_t missingHits;
			
    // -------- Matching with another electron collection ----------
	
	Float_t bestMatch_eta;
	Float_t bestMatch_phi;
	Float_t bestMatch_dR;
	Float_t bestMatch_pT;

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
        return (isolation["Trk03"] + TMath::Max(0.,isolation["ECalo03"]-1.) + isolation["HCalo03"])
          / TMath::Max(20.,p4.Et());
      }
      else
      {
        return (isolation["Trk03"] + isolation["ECalo03"] + isolation["HCalo03"])
          / TMath::Max(20.,p4.Et());
      }
    }

  };
}
#endif

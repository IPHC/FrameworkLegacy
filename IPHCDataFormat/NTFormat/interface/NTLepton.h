#ifndef __IPHC_TREE_NTLEPTON_H__
#define __IPHC_TREE_NTLEPTON_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTParticle.h"

namespace IPHCTree
{

  class NTTransient;
  class MTTransient;

  /// \class NTLepton
  /// Mother class for all leptons: NTElectron, NTMuon, NTTau. 
  /// It should contain the minimal common information as p4, charge,
  /// isolation, d0, chi2, leptonOrigin
  class NTLepton : public NTParticle
  {

    friend class IPHCTree::NTTransient;
    friend class IPHCTree::MTTransient;

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    // p4 and p4HLT coming from NTParticle

    /// vertex origin
    TVector3 vertex;
	
	Float_t dxy_vertex;
	Float_t dz_vertex;

    /// electric charge (transient)
    mutable Float_t charge; //! TRANSIENT

    /// MC information : origin of the lepton 
    Short_t LeptonOrigin;

    // Isolation informations
    KeyedCollection<Float_t> isolation;

    // ---------- isolation variables (cone of deltaR<0.3) -----------
/* 
	/// Summed track PT (in a cone of deltaR<0.3)
    Float_t isolation["Trk03"];

    /// ECAL isolation depositfrom RecHits
    /// with electron footprint removed (in a cone of deltaR<0.3)
    Float_t isolation["ECalo03"];

    /// HCAL isolation deposit from Calo Towers (in a cone of deltaR<0.3)
    Float_t isolation["HCalo03"];

    // ------------ ParticleFlow isolation variables -----------------

    /// to do
    Float_t isolation["PATNeutH"];

    /// to do
    Float_t isolation["PATCharH"];

    /// to do
    Float_t isolation["PATPhoto"];

    /// to do 
    Float_t isolation["PATTrack"];
*/
    // ------------- Information related to the track ----------------

    /// Transverse impact parameter
    Float_t D0;

    /// Normalize Chi2 (divided by ndof)
    Float_t Chi2;

  protected :

    /// electric charge (persistent)
    Bool_t charge_bit_;


    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTLepton()
    { Reset(true); }

		/// Destructor
    virtual ~NTLepton()
    { }

		/// Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

		/// Display information related to the lepton
    /// \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Get the Sum of isolation["ECalo03"] and isolation["HCalo03"]
    float CaloIso03() const
    { return isolation["ECalo03"] + isolation["HCalo03"]; }
    
	/// to do
    double RelIso03() const
    {
      if (p4.Pt()>0)
        return (isolation["Trk03"] + isolation["ECalo03"] + isolation["HCalo03"]) / p4.Pt();
      else return -999.;
    }

    double RelIso03PF() const
    {
      if (p4.Pt()>0) 
        // return( ((isolation["PATNeutH"]+isolation["PATCharH"]+isolation["PATTrack"])/p4.Pt()));
        // modification (from Denis): avoid to duplicate TrackIso
        // (included in ChargedHadron) and take into account photons
        return (isolation["PATNeutH"] + isolation["PATCharH"] + isolation["PATPhoto"]) 
               / p4.Pt();
      else return -999.;
    }

    double RelIso03RhoCorrected(double rho) const
    {
      if (p4.Pt()>0) 
        return (isolation["Trk03"] + isolation["ECalo03"] + isolation["HCalo03"] - rho*M_PI*0.3*0.3)
                / p4.Pt();
      else return -999.;
    }

    double RelIso03PFRhoCorrected(double rho) const
    {
      if (p4.Pt()>0) 
        return (isolation["PATNeutH"] + isolation["PATCharH"] + isolation["PATTrack"] 
                - rho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

    double RelIso03NeutralRhoCorrected(double neutralRho) const
    {
      if (p4.Pt()>0) 
        return (isolation["Trk03"] + isolation["ECalo03"] + isolation["HCalo03"] 
                - neutralRho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

    double RelIso03PFNeutralRhoCorrected(double neutralRho) const
    {
      if(p4.Pt()>0)
        return (isolation["PATNeutH"] + isolation["PATCharH"] + isolation["PATTrack"]
                - neutralRho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

  };
}
#endif

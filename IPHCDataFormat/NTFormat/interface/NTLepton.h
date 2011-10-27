#ifndef __IPHC_TREE_NTLEPTON_H__
#define __IPHC_TREE_NTLEPTON_H__

// STL headers
#include <iostream>

// IPHC headers
#include "NTParticle.h"

namespace IPHCTree
{

  //! \class NTLepton
  //! Mother class for all leptons: NTElectron, NTMuon, NTTau. 
  //! It should contain the minimal common information as p4, charge,
  //! isolation, d0, chi2, leptonOrigin
  class NTLepton : public NTParticle
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    // ------------------ general variables ------------------------

    // p4 and p4HLT coming from NTParticle

    //! vertex origin
    TVector3 vertex;

    //! electric charge
    Bool_t charge_;

    //! MC information : origin of the lepton 
    Int_t LeptonOrigin;

    // ---------- isolation variables (cone of deltaR<0.3) -----------

    //! Summed track PT (in a cone of deltaR<0.3)
    Float_t TrkIso03;

    //! ECAL isolation depositfrom RecHits
    //! with electron footprint removed (in a cone of deltaR<0.3)
    Float_t ECaloIso03;

    //! HCAL isolation deposit from Calo Towers (in a cone of deltaR<0.3)
    Float_t HCaloIso03;

    // ------------ ParticleFlow isolation variables -----------------

    //! to do
    Float_t PATNeutralHadronIso;

    //! to do
    Float_t PATChargedHadronIso;

    //! to do
    Float_t PATPhotonIso;

    //! to do 
    Float_t PATTrackIso;
    
    // ------------- Information related to the track ----------------

    //! Transverse impact parameter
    Float_t D0;

    //! Normalize Chi2 (divided by ndof)
    Float_t Chi2;

    //! Collection of ID
    KeyedCollection<Float_t> ID;

    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    //! Constructor without arguments
    NTLepton()
    { Reset(true); }

		//! Destructor
    virtual ~NTLepton()
    { }

		//! Clear all information related to lepton
    virtual void Reset(bool constructor_call=false);

		//! Display information related to the lepton
    //! \param[in,out] os   a log stream
    virtual void Dump(std::ostream & os = std::cout) const;

    //! Alias to Dump method
    virtual void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

		//! Get the charge of the particle
    signed int charge() const
		{
			if (charge_) return +1.;
			else return -1.;
		}

		//! Set the charge of the particle
    void setCharge(float charge)
		{
      if (charge<0) charge_=false;
      else charge_=true;
		}

    //! Get the Sum of ECaloIso03 and HCaloIso03
    float CaloIso03() const
    { return ECaloIso03 + HCaloIso03; }

    //! to do
    double RelIso03() const
    {
      if (p4.Pt()>0)
        return (TrkIso03 + ECaloIso03 + HCaloIso03) / p4.Pt();
      else return -999.;
    }

    double RelIso03PF() const
    {
      if (p4.Pt()>0) 
        // return( ((PATNeutralHadronIso+PATChargedHadronIso+PATTrackIso)/p4.Pt()));
        // modification (from Denis): avoid to duplicate TrackIso
        // (included in ChargedHadron) and take into account photons
        return (PATNeutralHadronIso + PATChargedHadronIso + PATPhotonIso) 
               / p4.Pt();
      else return -999.;
    }

    double RelIso03RhoCorrected(double rho) const
    {
      if (p4.Pt()>0) 
        return (TrkIso03 + ECaloIso03 + HCaloIso03 - rho*M_PI*0.3*0.3)
                / p4.Pt();
      else return -999.;
    }

    double RelIso03PFRhoCorrected(double rho) const
    {
      if (p4.Pt()>0) 
        return (PATNeutralHadronIso + PATChargedHadronIso + PATTrackIso 
                - rho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

    double RelIso03NeutralRhoCorrected(double neutralRho) const
    {
      if (p4.Pt()>0) 
        return (TrkIso03 + ECaloIso03 + HCaloIso03 
                - neutralRho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

    double RelIso03PFNeutralRhoCorrected(double neutralRho) const
    {
      if(p4.Pt()>0)
        return (PATNeutralHadronIso + PATChargedHadronIso + PATTrackIso
                - neutralRho*M_PI*0.3*0.3) / p4.Pt();
      else return -999.;
    }

  };
}
#endif

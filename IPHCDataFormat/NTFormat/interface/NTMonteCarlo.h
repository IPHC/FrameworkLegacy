#ifndef __IPHC_TREE_NTMONTECARLO_H__
#define __IPHC_TREE_NTMONTECARLO_H__

// STL headers
#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

// ROOT headers
#include <TLorentzVector.h>

// IPHC headers
#include "WDecaysMC.h"
#include "ZDecaysMC.h"
#include "topDecaysMC.h"
#include "NTGenParticle.h"


namespace IPHCTree
{

  /// \class NTMonteCarlo
  /// History for generated event
  class NTMonteCarlo
  {

    // -------------------------------------------------------------
    //                        data members
    // -------------------------------------------------------------
  public:

    Float_t          ptHat;        /// Pythia ptHat value
    std::pair<Float_t,Float_t> x;  /// Feynman variable (p_L / p)
    Float_t          Q_scale;      /// Q scale

	// Info from pdf (asked by Jean-Eric)
    std::pair<Float_t,Float_t> xpdf;

    /// PDG id of partons involved in collision
    std::pair<Char_t,Char_t> partonFlavor;

    /// Collection of generated particles
    std::vector<IPHCTree::NTGenParticle> genParticles; 

    /// Characterizes W decay mode
    //  T = # of taus from W decays 	
    //  M = # of muons from W->tau->muon	
    //  E = # of electrons from W->tau->electron
    //  M = # of muons from W->muon	
    //  E = # of electrons from W->electron
    //  By default = -999
    Int_t TMEME;
  
    // --- generated taus
    std::vector<TLorentzVector> Generatedtaus;
    std::vector<TLorentzVector> GeneratedAtaus;
    
    // --- generated quarks flavour
    std::vector<TLorentzVector > genBquarks;
    std::vector<TLorentzVector > genCquarks;
    std::vector<TLorentzVector > genLquarks;
    std::vector<TLorentzVector > genGquarks;
    
    // --- specific decays
    std::vector<WDecaysMC >   wAndDecays;
    std::vector<ZDecaysMC >   zAndDecays;
    std::vector<TopDecaysMC > topAndDecays;

    
    // -------------------------------------------------------------
    //                       method members
    // -------------------------------------------------------------
  public:

    /// Constructor without arguments
    NTMonteCarlo()
    { Reset(true); }

    /// Destructor
    ~NTMonteCarlo()
    { }

    /// Clear all information related to the Monte Carlo
    void Reset(bool constructor_call=false);

    /// Display information related to Monte Carlo
    /// \param[in,out] os   a log stream
    void Dump(std::ostream & os = std::cout) const;

    /// Alias to Dump method
    void PrintInfo(std::ostream & os = std::cout) const
    { Dump(os); }

    /// Dump only genparticles
    void DumpGenParticles(std::ostream & os) const;

    NTGenParticle* NewGenParticle()
    { 
      genParticles.push_back(NTGenParticle());
      return &genParticles.back();
    }

    void NewGenParticle(const NTGenParticle& part)
    { genParticles.push_back(part); }

  protected:

    static void PrintParticleDaughters(const IPHCTree::NTGenParticle* part, 
                                       unsigned int descent,
                                       std::ostream & os);


  };
}
#endif

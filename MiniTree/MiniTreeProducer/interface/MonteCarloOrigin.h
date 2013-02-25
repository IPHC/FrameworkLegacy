#ifndef __MonteCarloOrigin_H__
#define __MonteCarloOrigin_H__

#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"

#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

#include "IPHCDataFormat/MTFormat/interface/MTEvent.h"

struct MonteCarloOrigin
{
  static void setGenParticleFromCandidate (reco::GenParticle& gen,
                                           const reco::Candidate* reco);

  static int getMuonOrigin (
                        const reco::GenParticleCollection* genParticles,
                        const pat::Muon* thePatMuon,
                        reco::GenParticle & MotherGenMuon,
                        reco::GenParticle & GrandMotherGenMuon,
                        reco::GenParticle & GGrandMotherGenMuon);

  static int getElectronOrigin(
                   const reco::GenParticleCollection* genParticles,
                   const pat::Electron* thePatElectron,
                   reco::GenParticle & MotherGenElectron,
                   reco::GenParticle & GrandMotherGenElectron,
                   reco::GenParticle & GGrandMotherGenElectron);

  static int getTauDecay(
                     const reco::GenParticleCollection* genParticles, 
                     const pat::Tau* thePatTau);

  static int getTauDecayFromGenParticle(
                     reco::GenParticleCollection::const_iterator genTau);

  static int getHeavyQuarkDecayFromGenParticle(
                     reco::GenParticleCollection::const_iterator genQuark);
 
  static void getTauDecayProducts(
                     const reco::Candidate* inputParticle, 
					 std::vector<const reco::Candidate*>* output);

  static void getHeavyQuarkDecayProducts(
		             const reco::Candidate* inputParticle, 
					 std::vector<const reco::Candidate*>* output);

  static void fillGenInfo(std::auto_ptr<IPHCTree::MTEvent>& evt,
                          const edm::Handle<reco::GenParticleCollection>& genParticles);

};

#endif

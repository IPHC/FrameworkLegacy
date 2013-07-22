#include "../interface/NTEvent.h"
#include "../interface/NTSampleInfo.h"

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// STL containers

// IPHC containers
#pragma link C++ function operator<<(std::ostream&, const TLorentzVector&)+;
#pragma link C++ function operator<<(std::ostream&, const TVector3&)+;
#pragma link C++ function operator<<(std::ostream&, const TVector2&)+;
#pragma link C++ class IPHCTree::KeyedCollection<Float_t>+;
#pragma link C++ class IPHCTree::KeyedCollection<UInt_t>+;
#pragma link C++ class IPHCTree::KeyedCollection<TLorentzVector>+;
#pragma link C++ class std::pair<Char_t,Char_t>+;

// SampleInfo
#pragma link C++ class IPHCTree::NTSampleInfo+;

// General
#pragma link C++ class IPHCTree::NTEvent+;
#pragma link C++ class IPHCTree::NTGeneral+;
#pragma link C++ class IPHCTree::NTTrigger+;
#pragma link C++ class IPHCTree::NTPileUp+;
#pragma link C++ class IPHCTree::NTEventDescriptor+;

// Monte Carlo
#pragma link C++ class IPHCTree::NTMonteCarlo+;
#pragma link C++ class IPHCTree::NTGenParticle+;
#pragma link C++ class IPHCTree::WDecaysMC+;
#pragma link C++ class IPHCTree::ZDecaysMC+;
#pragma link C++ class IPHCTree::TopDecaysMC+;

// Particle
#pragma link C++ class IPHCTree::NTParticle+;
#pragma link C++ class IPHCTree::NTLepton+;
#pragma link C++ class IPHCTree::NTMuon+;
#pragma link C++ class IPHCTree::NTElectron+;
#pragma link C++ class IPHCTree::NTPhoton+;
#pragma link C++ class IPHCTree::NTTau+;
#pragma link C++ class IPHCTree::NTJet+;
#pragma link C++ class IPHCTree::NTSubJet+;
#pragma link C++ class IPHCTree::NTMET+;
#pragma link C++ class IPHCTree::NTPhoton+;

// Reconstructed objects
#pragma link C++ class IPHCTree::NTTrack+;
#pragma link C++ class IPHCTree::NTPFCandidate+;
#pragma link C++ class IPHCTree::NTVertex+;

// Multicollection
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTJet>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTMET>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTElectron>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTMuon>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTTau>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTPhoton>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTVertex>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTTrack>+;
#pragma link C++ class IPHCTree::MultiCollection<IPHCTree::NTPFCandidate>+;

// Vector
#pragma link C++ class std::vector<IPHCTree::NTGenParticle>+;
#pragma link C++ class std::vector<IPHCTree::NTJet>+;
#pragma link C++ class std::vector<IPHCTree::NTMET>+;
#pragma link C++ class std::vector<IPHCTree::NTElectron>+;
#pragma link C++ class std::vector<IPHCTree::NTMuon>+;
#pragma link C++ class std::vector<IPHCTree::NTTau>+;
#pragma link C++ class std::vector<IPHCTree::NTPhoton>+;
#pragma link C++ class std::vector<IPHCTree::NTVertex>+;
#pragma link C++ class std::vector<IPHCTree::NTTrack>+;
#pragma link C++ class std::vector<IPHCTree::NTPFCandidate>+;
#pragma link C++ class std::vector<IPHCTree::WDecaysMC>+;
#pragma link C++ class std::vector<IPHCTree::ZDecaysMC>+;
#pragma link C++ class std::vector<IPHCTree::TopDecaysMC>+;

// Vector of vector
#pragma link C++ class std::vector<std::vector< IPHCTree::NTJet> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTMET> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTElectron> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTMuon> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTTau> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTPhoton> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTVertex> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTTrack> >+;
#pragma link C++ class std::vector<std::vector< IPHCTree::NTPFCandidate> >+;

#endif

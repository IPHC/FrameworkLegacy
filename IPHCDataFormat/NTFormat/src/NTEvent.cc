#include "../interface/NTEvent.h"

using namespace IPHCTree;


// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void NTEvent::Reset()
{
  general.Reset();        mc.Reset();
  pileup.Reset();         vertices.Reset();
  electrons.Reset();      muons.Reset();
  taus.Reset();           photons.Reset();
  jets.Reset();           met.Reset(); 
  tracks.Reset();         descriptor.Reset();
  pfcandidates.Reset();
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void NTEvent::Dump(std::ostream & os) const
{
  os << "------------------------------------------------------" << std::endl;
  general.Dump(os);       
  os << " # generated particles = " << mc.genParticles.size() << std::endl;
  os << " # intime pileup  = " << pileup.intime_npu << std::endl;

  // Track summary display
  os << " # track collections = ";
  std::set<std::string> names;
  tracks.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    tracks.SelectLabel(*it); 
    os << tracks.size();
    os << " items) ; ";
  }
  os << std::endl;

  // PFCandidate summary display
  os << " # pfcandidate collections = ";
  pfcandidates.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    pfcandidates.SelectLabel(*it); 
    os << pfcandidates.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Vertex summary display
  os << " # vertex collections = ";
  vertices.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    vertices.SelectLabel(*it); 
    os << vertices.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Electron summary display
  os << " # electron collections = ";
  electrons.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    electrons.SelectLabel(*it); 
    os << electrons.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Muon summary display
  os << " # muon collections = ";
  muons.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    muons.SelectLabel(*it); 
    os << muons.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Tau summary display
  os << " # tau collections = ";
  taus.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    taus.SelectLabel(*it); 
    os << taus.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Jet summary display
  os << " # jet collections = ";
  jets.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    jets.SelectLabel(*it); 
    os << jets.size();
    os << " items) ; ";
  }
  os << std::endl;
 
  // Met summary display
  os << " # met collections = ";
  met.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    met.SelectLabel(*it); 
    os << met.size();
    os << " items) ; ";
  }
  os << std::endl;

  // Photon summary display
  os << " # photon collections = ";
  photons.GetCollectionList(names);
  if (names.empty()) os << "empty";
  else
  for (std::set<std::string>::const_iterator it = names.begin();
       it != names.end(); it++)
  {
    os << "'" << *it << "'(";
    photons.SelectLabel(*it); 
    os << photons.size();
    os << " items) ; ";
  }
  os << std::endl;

  os << "------------------------------------------------------" << std::endl;

}





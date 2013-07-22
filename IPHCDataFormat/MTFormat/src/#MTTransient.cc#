#include "../interface/MTTransient.h"
#include "../interface/MTEvent.h"


using namespace IPHCTree;

// ---------------------------------------------------------------------------
// readmode_SetLeptonCharge
// ----------------------------------------------------------------------------
void MTTransient::readmode_SetLeptonCharge(const IPHCTree::MTEvent* event)
{
  for (unsigned int i=0;i<event->electrons.names_.size();i++)
    for (unsigned int j=0;j<event->electrons.collections_[i].size();j++)
  {
    if (event->electrons.collections_[i][j].charge_bit_) event->electrons.collections_[i][j].charge=+1.0;
    else event->electrons.collections_[i][j].charge=-1.0;
  }
  for (unsigned int i=0;i<event->muons.names_.size();i++)
    for (unsigned int j=0;j<event->muons.collections_[i].size();j++)
  {
    if (event->muons.collections_[i][j].charge_bit_) event->muons.collections_[i][j].charge=+1.0;
    else event->muons.collections_[i][j].charge=-1.0;
  }
  for (unsigned int i=0;i<event->taus.names_.size();i++)
    for (unsigned int j=0;j<event->taus.collections_[i].size();j++)
  {
    if (event->taus.collections_[i][j].charge_bit_) event->taus.collections_[i][j].charge=+1.0;
    else event->taus.collections_[i][j].charge=-1.0;
  }
  for (unsigned int i=0;i<event->tracks.names_.size();i++)
    for (unsigned int j=0;j<event->tracks.collections_[i].size();j++)
  {
    if (event->tracks.collections_[i][j].charge_bit_) event->tracks.collections_[i][j].charge=+1.0;
    else event->tracks.collections_[i][j].charge=-1.0;
  }

}


// ---------------------------------------------------------------------------
// writemode_SetLeptonCharge
// ----------------------------------------------------------------------------
void MTTransient::writemode_SetLeptonCharge(IPHCTree::MTEvent* event)
{
  for (unsigned int i=0;i<event->electrons.names_.size();i++)
    for (unsigned int j=0;j<event->electrons.collections_[i].size();j++)
  {
    if  (event->electrons.collections_[i][j].charge>=0) event->electrons.collections_[i][j].charge_bit_=true;
    else event->electrons.collections_[i][j].charge_bit_=false;
  }
  for (unsigned int i=0;i<event->muons.names_.size();i++)
    for (unsigned int j=0;j<event->muons.collections_[i].size();j++)
  {
    if  (event->muons.collections_[i][j].charge>=0) event->muons.collections_[i][j].charge_bit_=true;
    else event->muons.collections_[i][j].charge_bit_=false;
  }
  for (unsigned int i=0;i<event->taus.names_.size();i++)
    for (unsigned int j=0;j<event->taus.collections_[i].size();j++)
  {
    if  (event->taus.collections_[i][j].charge>=0) event->taus.collections_[i][j].charge_bit_=true;
    else event->taus.collections_[i][j].charge_bit_=false;
  }
  for (unsigned int i=0;i<event->tracks.names_.size();i++)
    for (unsigned int j=0;j<event->tracks.collections_[i].size();j++)
  {
    if  (event->tracks.collections_[i][j].charge>=0) event->tracks.collections_[i][j].charge_bit_=true;
    else event->tracks.collections_[i][j].charge_bit_=false;
  }
}


// ---------------------------------------------------------------------------
// readmode_SetGenParticleFamily
// ---------------------------------------------------------------------------
void MTTransient::readmode_SetGenParticleFamily(const IPHCTree::MTEvent* event)
{
  for (unsigned int i=0;i<event->mc.genParticles.size();i++)
  {
    // Set mother pointer
    if (event->mc.genParticles[i].motherIndex_<0)
    {
      event->mc.genParticles[i].mother=0;
    }
    else
    { 
      event->mc.genParticles[i].mother= const_cast<IPHCTree::NTGenParticle*>( 
        &(event->mc.genParticles[ event->mc.genParticles[i].motherIndex_ ] ));

    }

    // Set daughter pointer
    event->mc.genParticles[i].daughters.clear();
    for (unsigned int j=i+1;j<event->mc.genParticles.size();j++)
    {
      if (event->mc.genParticles[j].motherIndex_==static_cast<signed int>(i)) 
        event->mc.genParticles[i].daughters.push_back(
           const_cast<IPHCTree::NTGenParticle*>(&(event->mc.genParticles[j])));
    }

  }
}


// ---------------------------------------------------------------------------
// readmode_SetKeyedCollectionName
// ---------------------------------------------------------------------------
void MTTransient::readmode_SetKeyedCollectionName(const IPHCTree::MTEvent* event)
{
  if (!event->descriptor.jet_p4HLT.empty() || !event->descriptor.jet_others.empty() || !event->descriptor.jet_bTag.empty() )
  {
    for (unsigned int i=0;i<event->jets.names_.size();i++)
      for (unsigned int j=0;j<event->jets.collections_[i].size();j++)
      {
        event->jets.collections_[i][j].p4HLT.names_  = event->descriptor.jet_p4HLT; 
        event->jets.collections_[i][j].bTag.names_   = event->descriptor.jet_bTag; 
        event->jets.collections_[i][j].others.names_ = event->descriptor.jet_others; 
      }
  }

  if (!event->descriptor.electron_p4HLT.empty() || !event->descriptor.electron_others.empty() || !event->descriptor.electron_ID.empty())
  {
    for (unsigned int i=0;i<event->electrons.names_.size();i++)
      for (unsigned int j=0;j<event->electrons.collections_[i].size();j++)
      {
        event->electrons.collections_[i][j].p4HLT.names_  = event->descriptor.electron_p4HLT; 
        event->electrons.collections_[i][j].ID.names_     = event->descriptor.electron_ID;
        event->electrons.collections_[i][j].others.names_ = event->descriptor.electron_others; 
      }
  }

  if (!event->descriptor.muon_p4HLT.empty() || !event->descriptor.muon_others.empty() || !event->descriptor.muon_ID.empty())
  {
    for (unsigned int i=0;i<event->muons.names_.size();i++)
      for (unsigned int j=0;j<event->muons.collections_[i].size();j++)
      {
        event->muons.collections_[i][j].p4HLT.names_  = event->descriptor.muon_p4HLT; 
        event->muons.collections_[i][j].ID.names_     = event->descriptor.muon_ID;
        event->muons.collections_[i][j].others.names_ = event->descriptor.muon_others; 
      }
  }

  if (!event->descriptor.tau_p4HLT.empty() || !event->descriptor.tau_others.empty() || !event->descriptor.tau_ID.empty())
  {
    for (unsigned int i=0;i<event->taus.names_.size();i++)
      for (unsigned int j=0;j<event->taus.collections_[i].size();j++)
      {
        event->taus.collections_[i][j].p4HLT.names_  = event->descriptor.tau_p4HLT; 
        event->taus.collections_[i][j].ID.names_     = event->descriptor.tau_ID;
        event->taus.collections_[i][j].others.names_ = event->descriptor.tau_others; 
      }
  }

  if (!event->descriptor.photon_p4HLT.empty() || !event->descriptor.photon_others.empty())
  {
    for (unsigned int i=0;i<event->photons.names_.size();i++)
      for (unsigned int j=0;j<event->photons.collections_[i].size();j++)
      {
        event->photons.collections_[i][j].p4HLT.names_  = event->descriptor.photon_p4HLT; 
        event->photons.collections_[i][j].others.names_  = event->descriptor.photon_others; 
      }
  }

  if (!event->descriptor.event_others.empty())
    event->others.names_ = event->descriptor.event_others;

}

// ---------------------------------------------------------------------------
// readmode_SetKeyedCollectionName
// ---------------------------------------------------------------------------
void MTTransient::writemode_SetKeyedCollectionName(IPHCTree::MTEvent* event)
{
  // Reset the descriptor
  event->descriptor.Reset();

  // Jets
  for (unsigned int i=0;i<event->jets.names_.size();i++)
    for (unsigned int j=0;j<event->jets.collections_[i].size();j++)
    {
      if (!event->jets.collections_[i][j].p4HLT.names_.empty())
      {
        if ( event->descriptor.jet_p4HLT.empty() ) event->descriptor.jet_p4HLT = event->jets.collections_[i][j].p4HLT.names_;
        else if (event->descriptor.jet_p4HLT != event->jets.collections_[i][j].p4HLT.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->jets.collections_[i][j].bTag.names_.empty())
      {
        if ( event->descriptor.jet_bTag.empty() ) event->descriptor.jet_bTag = event->jets.collections_[i][j].bTag.names_;
        else if (event->descriptor.jet_bTag != event->jets.collections_[i][j].bTag.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->jets.collections_[i][j].others.names_.empty())
      {
        if ( event->descriptor.jet_others.empty() ) event->descriptor.jet_others = event->jets.collections_[i][j].others.names_;
        else if (event->descriptor.jet_others != event->jets.collections_[i][j].others.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }
    }


  // Electrons
  for (unsigned int i=0;i<event->electrons.names_.size();i++)
    for (unsigned int j=0;j<event->electrons.collections_[i].size();j++)
    {
      if (!event->electrons.collections_[i][j].p4HLT.names_.empty())
      {
        if ( event->descriptor.electron_p4HLT.empty() ) event->descriptor.electron_p4HLT = event->electrons.collections_[i][j].p4HLT.names_;
        else if (event->descriptor.electron_p4HLT != event->electrons.collections_[i][j].p4HLT.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->electrons.collections_[i][j].ID.names_.empty())
      {
        if ( event->descriptor.electron_ID.empty() ) event->descriptor.electron_ID = event->electrons.collections_[i][j].ID.names_;
        else if (event->descriptor.electron_ID != event->electrons.collections_[i][j].ID.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->electrons.collections_[i][j].others.names_.empty())
      {
        if ( event->descriptor.electron_others.empty() ) event->descriptor.electron_others = event->electrons.collections_[i][j].others.names_;
        else if (event->descriptor.electron_others != event->electrons.collections_[i][j].others.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }
    }


  for (unsigned int i=0;i<event->muons.names_.size();i++)
    for (unsigned int j=0;j<event->muons.collections_[i].size();j++)
    {
      if (!event->muons.collections_[i][j].p4HLT.names_.empty())
      {
        if ( event->descriptor.muon_p4HLT.empty() ) event->descriptor.muon_p4HLT = event->muons.collections_[i][j].p4HLT.names_;
        else if (event->descriptor.muon_p4HLT != event->muons.collections_[i][j].p4HLT.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->muons.collections_[i][j].ID.names_.empty())
      {
        if ( event->descriptor.muon_ID.empty() ) event->descriptor.muon_ID = event->muons.collections_[i][j].ID.names_;
        else if (event->descriptor.muon_ID != event->muons.collections_[i][j].ID.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->muons.collections_[i][j].others.names_.empty())
      {
        if ( event->descriptor.muon_others.empty() ) event->descriptor.muon_others = event->muons.collections_[i][j].others.names_;
        else if (event->descriptor.muon_others != event->muons.collections_[i][j].others.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }
    }

  for (unsigned int i=0;i<event->taus.names_.size();i++)
    for (unsigned int j=0;j<event->taus.collections_[i].size();j++)
    {
      if (!event->taus.collections_[i][j].p4HLT.names_.empty())
      {
        if ( event->descriptor.tau_p4HLT.empty() ) event->descriptor.tau_p4HLT = event->taus.collections_[i][j].p4HLT.names_;
        else if (event->descriptor.tau_p4HLT != event->taus.collections_[i][j].p4HLT.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->taus.collections_[i][j].ID.names_.empty())
      {
        if ( event->descriptor.tau_ID.empty() ) event->descriptor.tau_ID = event->taus.collections_[i][j].ID.names_;
        else if (event->descriptor.tau_ID != event->taus.collections_[i][j].ID.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->taus.collections_[i][j].others.names_.empty())
      {
        if ( event->descriptor.tau_others.empty() ) event->descriptor.tau_others = event->taus.collections_[i][j].others.names_;
        else if (event->descriptor.tau_others != event->taus.collections_[i][j].others.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }
    }


  for (unsigned int i=0;i<event->photons.names_.size();i++)
    for (unsigned int j=0;j<event->photons.collections_[i].size();j++)
    {
      if (!event->photons.collections_[i][j].p4HLT.names_.empty())
      {
        if ( event->descriptor.photon_p4HLT.empty() ) event->descriptor.photon_p4HLT = event->photons.collections_[i][j].p4HLT.names_;
        else if (event->descriptor.photon_p4HLT != event->photons.collections_[i][j].p4HLT.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }

      if (!event->photons.collections_[i][j].others.names_.empty())
      {
        if ( event->descriptor.photon_others.empty() ) event->descriptor.photon_others = event->photons.collections_[i][j].others.names_;
        else if (event->descriptor.photon_others != event->photons.collections_[i][j].others.names_)
        { std::cout << "ERROR : some KeyedCollection are different" << std::endl; exit(1); }
      }
    }


  if (!event->others.names_.empty()) event->descriptor.event_others = event->others.names_;

}

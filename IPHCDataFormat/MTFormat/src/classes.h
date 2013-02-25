// CMSSW edm::Wrapper
#include "DataFormats/Common/interface/Wrapper.h"

// All IPHC classes
#include "IPHCDataFormat/MTFormat/interface/MTEvent.h"

namespace{
  namespace{

    // General
    edm::Wrapper<IPHCTree::MTEvent>            MTEvent; 
    edm::Wrapper<IPHCTree::MTGeneral>          MTGeneral;
    edm::Wrapper<IPHCTree::MTTrigger>          MTTrigger;
    edm::Wrapper<IPHCTree::MTMonteCarlo>       MTMonteCarlo;
    edm::Wrapper<IPHCTree::MTEventDescriptor>  MTEventDescriptor;

    // Pile Up
    edm::Wrapper<IPHCTree::MTPileUp> MTPU;
    edm::Wrapper<std::vector<std::pair<Char_t, std::vector<IPHCTree::MTInteraction> > > >   MTint1;
    edm::Wrapper<std::pair<Char_t,std::vector<IPHCTree::MTInteraction> > >                  MTint2;
    edm::Wrapper<std::vector<IPHCTree::MTInteraction> >                                     MTInt3;
    edm::Wrapper<IPHCTree::MTInteraction>                                                   MTInt4;
    edm::Wrapper<std::map<Char_t,std::vector<IPHCTree::MTInteraction> > >                   MTInt5; 

    // Physics Object
    edm::Wrapper<IPHCTree::MTLepton>           MTLep;
    edm::Wrapper<IPHCTree::MTJet>              MTJet;
    edm::Wrapper<IPHCTree::MTMET>              MTMET;
    edm::Wrapper<IPHCTree::MTPhoton>           MTPhoton;
    edm::Wrapper<IPHCTree::MTElectron>         MTElec;
    edm::Wrapper<IPHCTree::MTMuon>             MTMuon;
    edm::Wrapper<IPHCTree::MTTau>              MTTau;

    // Reconstructed objects
    edm::Wrapper<IPHCTree::MTVertex>           MTVertex;
    edm::Wrapper<IPHCTree::MTBeamSpot>         MTBeamSpot;
    edm::Wrapper<IPHCTree::MTTrack>            MTTrack;

    // MultiCollection
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTJet> >     MultiMTJet; 
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTMET> >     MultiMTMET; 
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTElectron> >MultiMTElectron;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTMuon> >    MultiMTMuon;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTTau> >     MultiMTTau;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTTrack> >   MultiMTTrack;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTVertex> >  MultiMTVertex;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::MTPhoton> >  MultiMTPhoton;

    // Vector
    edm::Wrapper<std::vector<IPHCTree::MTJet> >      VMTJet; 
    edm::Wrapper<std::vector<IPHCTree::MTMET> >      VMTMET;
    edm::Wrapper<std::vector<IPHCTree::MTElectron> > VMTElectron;
    edm::Wrapper<std::vector<IPHCTree::MTMuon> >     VMTMuon;
    edm::Wrapper<std::vector<IPHCTree::MTTau> >      VMTTau;
    edm::Wrapper<std::vector<IPHCTree::MTPhoton> >   VMTPhoton;
    edm::Wrapper<std::vector<IPHCTree::MTVertex> >   VMTVertex;
    edm::Wrapper<std::vector<IPHCTree::MTTrack> >    VMTTrack;


    // Vector of vector
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTJet> > >      VVMTJet; 
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTMET> > >      VVMTMET; 
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTElectron> > > VVMTElectron;
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTMuon> > >     VVMTMuon;
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTTau> > >      VVMTTau;
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTPhoton> > >   VVMTPhoton;
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTVertex> > >   VVMTVertex;
    edm::Wrapper<std::vector<std::vector<IPHCTree::MTTrack> > >    VVMTTrack;

  }
}

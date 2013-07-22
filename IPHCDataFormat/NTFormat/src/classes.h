#include "DataFormats/Common/interface/Wrapper.h"
#include "IPHCDataFormat/NTFormat/interface/NTEvent.h"
#include "IPHCDataFormat/NTFormat/interface/NTSampleInfo.h"

namespace{
  namespace{

    // STL containers 
    edm::Wrapper<std::map<Int_t   , std::vector<Int_t> > >       dummy1;
    edm::Wrapper<std::pair<Float_t, std::string> >               dummy2;
    edm::Wrapper<std::vector<std::pair<Float_t, std::string> > > dummy3;
    edm::Wrapper<std::set<std::string> >                         dummy4;
    edm::Wrapper<std::vector<TLorentzVector> >                   dummy5;
    edm::Wrapper<std::map<UInt_t,std::vector<Int_t> > >          dummy6;
    edm::Wrapper<std::pair<Char_t,Char_t> >                      dummy7;

    // IPHC containers
    edm::Wrapper<IPHCTree::KeyedCollection<Float_t> > kCollection;
    edm::Wrapper<IPHCTree::KeyedCollection<TLorentzVector> > kCollection2;
    edm::Wrapper<IPHCTree::KeyedCollection<UInt_t> > kCollection3;

    // SampleInfo
    edm::Wrapper<IPHCTree::NTSampleInfo>   NTSampleInfo;

    // General
    edm::Wrapper<IPHCTree::NTEvent>        NTEvent;
    edm::Wrapper<IPHCTree::NTGeneral>      NTGeneral;
    edm::Wrapper<IPHCTree::NTTrigger>      NTTrigger;
    edm::Wrapper<IPHCTree::NTPileUp>       NTPileUp;
    edm::Wrapper<IPHCTree::NTEventDescriptor>       NTEventDescriptor;

    // Monte Carlo
    edm::Wrapper<IPHCTree::NTMonteCarlo>   NTMonteCarlo_;
    edm::Wrapper<IPHCTree::NTGenParticle>  NTGenParticle_;
    edm::Wrapper<IPHCTree::TopDecaysMC>    TopDecays;
    edm::Wrapper<IPHCTree::WDecaysMC>      WDecays;
    edm::Wrapper<IPHCTree::ZDecaysMC>      ZDecays;

    // Particle
    edm::Wrapper<IPHCTree::NTParticle>     NTPart;
    edm::Wrapper<IPHCTree::NTLepton>       NTLep;
    edm::Wrapper<IPHCTree::NTElectron>     NTElec;
    edm::Wrapper<IPHCTree::NTMuon>         NTMuon;
    edm::Wrapper<IPHCTree::NTTau>          NTTau;
    edm::Wrapper<IPHCTree::NTJet>          NTJet;
    edm::Wrapper<IPHCTree::NTSubJet>       NTSubJet;
    edm::Wrapper<IPHCTree::NTMET>          NTMET;
    edm::Wrapper<IPHCTree::NTPhoton>       NTPhoton;

    // Reconstructed objects
    edm::Wrapper<IPHCTree::NTVertex>       NTVertex;
    edm::Wrapper<IPHCTree::NTTrack>        NTTrack;
    edm::Wrapper<IPHCTree::NTPFCandidate>        NTPFCandidate;

    // Multiparticles
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTJet> >      MultiNTJet; 
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTSubJet> >   MultiNTSubJet; 
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTMET> >      MultiNTMET; 
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTElectron> > MultiNTElectron;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTMuon> >     MultiNTMuon;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTTau> >      MultiNTTau;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTPhoton> >   MultiNTPhoton;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTTrack> >    MultiNTTrack;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTPFCandidate> >    MultiNTPFCandidate;
    edm::Wrapper<IPHCTree::MultiCollection<IPHCTree::NTVertex> >   MultiNTVertex;

    // Vector
    edm::Wrapper<std::vector<IPHCTree::NTJet> >      VNTJet; 
    edm::Wrapper<std::vector<IPHCTree::NTSubJet> >   VNTSubJet; 
    edm::Wrapper<std::vector<IPHCTree::NTMET> >      VNTMET; 
    edm::Wrapper<std::vector<IPHCTree::NTElectron> > VNTElectron;
    edm::Wrapper<std::vector<IPHCTree::NTMuon> >     VNTMuon;
    edm::Wrapper<std::vector<IPHCTree::NTTau> >      VNTTau;
    edm::Wrapper<std::vector<IPHCTree::NTPhoton> >   VNTPhoton;
    edm::Wrapper<std::vector<IPHCTree::NTTrack> >    VNTTrack;
    edm::Wrapper<std::vector<IPHCTree::NTPFCandidate> >    VNTPFCandidate;
    edm::Wrapper<std::vector<IPHCTree::NTVertex> >   VNTVertex;

    edm::Wrapper<std::vector<IPHCTree::NTGenParticle> >VecNTGenParticle;
    edm::Wrapper<std::vector<IPHCTree::NTGenParticle*> >VecNTGenParticle2;
    edm::Wrapper<std::vector<IPHCTree::TopDecaysMC> >  VecTopDecays;
    edm::Wrapper<std::vector<IPHCTree::WDecaysMC> >    VecWDecays;
    edm::Wrapper<std::vector<IPHCTree::ZDecaysMC> >    VecZDecays;

    // Vector of vector
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTJet> > >      VVNTJet; 
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTSubJet> > >   VVNTSubJet; 
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTMET> > >      VVNTMET; 
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTElectron> > > VVNTElectron;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTMuon> > >     VVNTMuon;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTTau> > >      VVNTTau;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTPhoton> > >   VVNTPhoton;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTTrack> > >    VVNTTrack;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTPFCandidate> > >    VVNTPFCandidate;
    edm::Wrapper<std::vector<std::vector<IPHCTree::NTVertex> > >   VVNTVertex;

  }
}

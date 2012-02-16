#include "NTuple/NTupleProducer/interface/FillNTuple.h"


// ----------------------------------------------------------------------------
// Initialize
// ----------------------------------------------------------------------------
bool FillNTuple::Initialize(const edm::ParameterSet & iConfig)
{
  // Read configuration file 
  verbose         = iConfig.getParameter <unsigned int>("verbose");

  // Trigger
  skimTrigger = iConfig.getParameter<bool>("skimTrigger");
  triggerList = iConfig.getParameter<std::vector<std::string> >
                                      ("triggerList");

  // Monte Carlo
  skimGenParticles = iConfig.getParameter<bool>("skimGenParticles");
  skimGenTaus      = iConfig.getParameter<bool>("skimGenTaus");

  // Muon
  skimMuons = iConfig.getParameter<bool>("skimMuons");
  muon_keepAllCollections = iConfig.getParameter<bool>
                                      ("muon_keepAllCollections");
  muon_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("muon_collectionList");
  muon_pt = iConfig.getParameter<double>("muon_pt");
  muon_eta = iConfig.getParameter<double>("muon_eta");

  // Electron
  skimElectrons = iConfig.getParameter<bool>("skimElectrons");
  electron_keepAllCollections = iConfig.getParameter<bool>
                                      ("electron_keepAllCollections");
  electron_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("electron_collectionList");
  electron_pt = iConfig.getParameter<double>("electron_pt");
  electron_eta = iConfig.getParameter<double>("electron_eta");

  // Tau
  skimTaus = iConfig.getParameter<bool>("skimTaus");
  tau_keepAllCollections = iConfig.getParameter<bool>
                                      ("tau_keepAllCollections");
  tau_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("tau_collectionList");
  tau_pt = iConfig.getParameter<double>("tau_pt");
  tau_eta = iConfig.getParameter<double>("tau_eta");

  // Jet
  skimJets = iConfig.getParameter<bool>("skimJets");
  jet_keepAllCollections = iConfig.getParameter<bool>
                                      ("jet_keepAllCollections");
  jet_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("jet_collectionList");
  jet_pt = iConfig.getParameter<double>("jet_pt");
  jet_eta = iConfig.getParameter<double>("jet_eta");

  // Track
  skimTracks = iConfig.getParameter<bool>("skimTracks");
  track_keepAllCollections = iConfig.getParameter<bool>
                                      ("track_keepAllCollections");
  track_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("track_collectionList");
  track_pt = iConfig.getParameter<double>("track_pt");
  track_eta = iConfig.getParameter<double>("track_eta");

  // Vertices
  skimVertices = iConfig.getParameter<bool>("skimVertices");
  vertex_keepAllCollections = iConfig.getParameter<bool>
                                      ("vertex_keepAllCollections");
  vertex_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("vertex_collectionList");
  return true;
} 


// ----------------------------------------------------------------------------
// Fill
// ----------------------------------------------------------------------------
void FillNTuple::Fill(const IPHCTree::MTEvent* minitree, IPHCTree::NTEvent* ntuple)
{
  // -------------------------------------
  // General info
  // -------------------------------------
  ntuple->general = 
          dynamic_cast<const IPHCTree::NTGeneral&>(minitree->general);
  ntuple->pileup  = 
          dynamic_cast<const IPHCTree::NTPileUp&>(minitree->pileup);
  ntuple->mc      = 
          dynamic_cast<const IPHCTree::NTMonteCarlo&>(minitree->mc);

  // -------------------------------------
  // GenParticle 
  // -------------------------------------
  if (skimGenParticles)
  {
    ntuple->mc.genParticles.clear();
  }
  if (skimGenTaus)
  {
    ntuple->mc.Generatedtaus.clear();
    ntuple->mc.GeneratedAtaus.clear();
  }

  // -------------------------------------
  // Trigger
  // -------------------------------------
  if (!skimTrigger)
  {
    if (verbose > 0) std::cout << "Filling trigger (no skim) ..." << std::endl;
    ntuple->trigger = minitree->trigger;
  }
  else
  {
    if (verbose > 0) std::cout << "Filling trigger (skim) ..." << std::endl;

    // Getting trigger data in a comfortable format
    std::vector<IPHCTree::NTTriggerPathType> paths;
    minitree->trigger.GetSubTable("*",paths); 

    // Declaring a new container for trigger bits and prescales
    std::map<std::string, std::pair<UInt_t,Bool_t> > skimmed;

    for (unsigned int i=0;i<paths.size();i++)
    {
      for (unsigned int j=0;j<triggerList.size();j++)
      {
        if (triggerList[j]==paths[i].name)
        {
          skimmed[paths[i].name] = std::make_pair( paths[i].prescale, 
                                                   paths[i].fired ); 
          break;
        }
      }
    }

    // Save trigger bits and prescales
    ntuple->trigger.FillTrigger(skimmed);
  }
  

  // -------------------------------------
  // Electrons
  // -------------------------------------
  if (!skimElectrons) {if (verbose > 0) std::cout << "Filling electrons (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling electrons (skim) ..." << std::endl;}

  // Get list of electron collection names
  std::set<std::string> labels;
  if (!skimElectrons || electron_keepAllCollections)
  {
    minitree->electrons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<electron_collectionList.size();i++)
    {
      if (electron_collectionList[i]=="") continue;
      if (minitree->electrons.DoYouKnowCollection
             (electron_collectionList[i]))
                   labels.insert(electron_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->electrons.Reserve(labels);

  // Fill electrons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->electrons.SelectLabel(*theLabel);
    minitree->electrons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->electrons.size(); i++) 
    {
      if (!skimElectrons || 
          (minitree->electrons[i].p4.Pt() > electron_pt && 
           fabs(minitree->electrons[i].p4.Eta()) < electron_eta) )
        ntuple -> NewElectron(dynamic_cast<const IPHCTree::NTElectron&>(minitree->electrons[i]));
    }
  }


  // -------------------------------------
  // Photons
  // -------------------------------------
  if (!skimPhotons) {if (verbose > 0) std::cout << "Filling photons (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling photons (skim) ..." << std::endl;}

  // Get list of photon collection names
  labels.clear();
  if (!skimPhotons || photon_keepAllCollections)
  {
    minitree->photons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<photon_collectionList.size();i++)
    {
      if (photon_collectionList[i]=="") continue;
      if (minitree->photons.DoYouKnowCollection
             (photon_collectionList[i]))
                   labels.insert(photon_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->photons.Reserve(labels);

  // Fill photons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->photons.SelectLabel(*theLabel);
    minitree->photons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->photons.size(); i++) 
    {
      if (!skimPhotons || 
          (minitree->photons[i].p4.Pt() > photon_pt && 
           fabs(minitree->photons[i].p4.Eta()) < photon_eta) )
        ntuple -> NewPhoton(dynamic_cast<const IPHCTree::NTPhoton&>(minitree->photons[i]));
    }
  }


  // -------------------------------------
  // Muons
  // -------------------------------------
  if (!skimMuons) {if (verbose > 0) std::cout << "Filling muons (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling muons (skim) ..." << std::endl;}

  // Get list of muon collection names
  labels.clear();
  if (!skimMuons || muon_keepAllCollections)
  {
    minitree->muons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<muon_collectionList.size();i++)
    {
      if (muon_collectionList[i]=="") continue;
      if (minitree->muons.DoYouKnowCollection
             (muon_collectionList[i]))
                   labels.insert(muon_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->muons.Reserve(labels);

  // Fill muons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->muons.SelectLabel(*theLabel);
    minitree->muons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->muons.size(); i++) 
    {
      if (!skimMuons || 
          (minitree->muons[i].p4.Pt() > muon_pt && 
           fabs(minitree->muons[i].p4.Eta()) < muon_eta) )
        ntuple -> NewMuon(dynamic_cast<const IPHCTree::NTMuon&>(minitree->muons[i]));
    }
  }



  // -------------------------------------
  // Taus
  // -------------------------------------
  if (!skimTaus) {if (verbose > 0) std::cout << "Filling taus (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling taus (skim) ..." << std::endl;}

  // Get list of tau collection names
  labels.clear();
  if (!skimTaus || tau_keepAllCollections)
  {
    minitree->taus.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<tau_collectionList.size();i++)
    {
      if (tau_collectionList[i]=="") continue;
      if (minitree->taus.DoYouKnowCollection
             (tau_collectionList[i]))
                   labels.insert(tau_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->taus.Reserve(labels);

  // Fill taus
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->taus.SelectLabel(*theLabel);
    minitree->taus.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->taus.size(); i++) 
    {
      if (!skimTaus || 
          (minitree->taus[i].p4.Pt() > tau_pt && 
           fabs(minitree->taus[i].p4.Eta()) < tau_eta) )
        ntuple -> NewTau(dynamic_cast<const IPHCTree::NTTau&>(minitree->taus[i]));
    }
  }


  // -------------------------------------
  // Jets
  // -------------------------------------
  if (!skimJets) {if (verbose > 0)std::cout << "Filling jets (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling jets (skim) ..." << std::endl;}

  // Get list of jet collection names
  labels.clear();
  if (!skimJets || jet_keepAllCollections)
  {
    minitree->jets.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<jet_collectionList.size();i++)
    {
      if (jet_collectionList[i]=="") continue;
      if (minitree->jets.DoYouKnowCollection
             (jet_collectionList[i]))
                   labels.insert(jet_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->jets.Reserve(labels);

  // Fill jets
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->jets.SelectLabel(*theLabel);
    minitree->jets.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->jets.size(); i++) 
    {
      if (!skimJets || 
          (minitree->jets[i].p4.Pt() > jet_pt && 
           fabs(minitree->jets[i].p4.Eta()) < jet_eta) )
        ntuple -> NewJet(dynamic_cast<const IPHCTree::NTJet&>(minitree->jets[i]));
    }
  }


  // -------------------------------------
  // Met
  // -------------------------------------
  if (!skimJets) {if (verbose > 0)std::cout << "Filling met (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling met (skim) ..." << std::endl;}

  // Get list of met collection names
  labels.clear();
  if (!skimJets || jet_keepAllCollections)
  {
    minitree->met.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<jet_collectionList.size();i++)
    {
      if (jet_collectionList[i]=="") continue;
      if (minitree->met.DoYouKnowCollection
             (jet_collectionList[i]))
                   labels.insert(jet_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->met.Reserve(labels);

  // Fill met
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->met.SelectLabel(*theLabel);
    minitree->met.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->met.size(); i++) 
    {
      ntuple -> NewMet(dynamic_cast<const IPHCTree::NTMET&>(minitree->met[i]));
    }
  }


  // -------------------------------------
  // Tracks
  // -------------------------------------
  if (!skimTracks) {if (verbose > 0) std::cout << "Filling tracks (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling tracks (skim) ..." << std::endl;}

  // Get list of track collection names
  labels.clear();
  if (!skimTracks || track_keepAllCollections)
  {
    minitree->tracks.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<track_collectionList.size();i++)
    {
      if (track_collectionList[i]=="") continue;
      if (minitree->tracks.DoYouKnowCollection
             (track_collectionList[i]))
                   labels.insert(track_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->tracks.Reserve(labels);

  // Fill tracks
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->tracks.SelectLabel(*theLabel);
    minitree->tracks.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->tracks.size(); i++) 
    {
      if (!skimTracks || 
          (minitree->tracks[i].p4.Pt() > track_pt && 
           fabs(minitree->tracks[i].p4.Eta()) < track_eta) )
        ntuple -> NewTrack(dynamic_cast<const IPHCTree::NTTrack&>(minitree->tracks[i]));
    }
  }

  
  // -------------------------------------
  // Vertices
  // -------------------------------------
  if (!skimVertices) {if (verbose > 0) std::cout << "Filling vertices (no skim) ..." << std::endl;}
  else {if (verbose > 0) std::cout << "Filling vertices (skim) ..." << std::endl;}

  // Get list of vertex collection names
  labels.clear();
  if (!skimVertices || vertex_keepAllCollections)
  {
    minitree->vertices.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<vertex_collectionList.size();i++)
    {
      if (vertex_collectionList[i]=="") continue;
      if (minitree->vertices.DoYouKnowCollection
             (vertex_collectionList[i]))
                   labels.insert(vertex_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->vertices.Reserve(labels);

  // Fill vertices
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->vertices.SelectLabel(*theLabel);
    minitree->vertices.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->vertices.size(); i++) 
    {
      ntuple -> NewVertex(dynamic_cast<const IPHCTree::NTVertex&>(minitree->vertices[i]));
    }
  }

}

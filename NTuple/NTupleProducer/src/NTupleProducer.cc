#include "NTuple/NTupleProducer/interface/NTupleProducer.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
NTupleProducer::NTupleProducer (const edm::ParameterSet & iConfig)
{
  std::cout << "Constructor of NTupleProducer - BEGIN" << std::endl;

  // Creating some histos
  theNormHisto        = fs->make<TH1F> ("theNormHisto", 
                                        "theNormHisto", 1, 0.5, 1.5);
  theNormHistoByTMEME = fs->make<TH1F> ("theNormHistoByTMEME",
                                        "theNormHistoByTMEME", 
                                        22223, -0.5, 22222.5);

  // Declaring the ntuple
  output = fs->make<TTree> ("Event", "");
  ntuple = new IPHCTree::NTEvent();
  output->Branch("NTEvent", "IPHCTree::NTEvent", &ntuple, 32000, 3);
  // compress= 3 seems to be the optimal !

  // Read configuration file 
  verbose         = iConfig.getParameter <unsigned int>("verbose");
 
  // Trigger
  skim.skimTrigger = iConfig.getParameter<bool>("skimTrigger");
  skim.triggerList = iConfig.getParameter<std::vector<std::string> >
                                      ("triggerList");

  // Muon
  skim.skimMuons = iConfig.getParameter<bool>("skimMuons");
  skim.muon_keepAllCollections = iConfig.getParameter<bool>
                                      ("muon_keepAllCollections");
  skim.muon_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("muon_collectionList");
  skim.muon_pt = iConfig.getParameter<double>("muon_pt");
  skim.muon_eta = iConfig.getParameter<double>("muon_eta");

  // Electron
  skim.skimElectrons = iConfig.getParameter<bool>("skimElectrons");
  skim.electron_keepAllCollections = iConfig.getParameter<bool>
                                      ("electron_keepAllCollections");
  skim.electron_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("electron_collectionList");
  skim.electron_pt = iConfig.getParameter<double>("electron_pt");
  skim.electron_eta = iConfig.getParameter<double>("electron_eta");

  // Tau
  skim.skimTaus = iConfig.getParameter<bool>("skimTaus");
  skim.tau_keepAllCollections = iConfig.getParameter<bool>
                                      ("tau_keepAllCollections");
  skim.tau_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("tau_collectionList");
  skim.tau_pt = iConfig.getParameter<double>("tau_pt");
  skim.tau_eta = iConfig.getParameter<double>("tau_eta");

  // Jet
  skim.skimJets = iConfig.getParameter<bool>("skimJets");
  skim.jet_keepAllCollections = iConfig.getParameter<bool>
                                      ("jet_keepAllCollections");
  skim.jet_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("jet_collectionList");
  skim.jet_pt = iConfig.getParameter<double>("jet_pt");
  skim.jet_eta = iConfig.getParameter<double>("jet_eta");

  // Track
  skim.skimTracks = iConfig.getParameter<bool>("skimTracks");
  skim.track_keepAllCollections = iConfig.getParameter<bool>
                                      ("track_keepAllCollections");
  skim.track_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("track_collectionList");
  skim.track_pt = iConfig.getParameter<double>("track_pt");
  skim.track_eta = iConfig.getParameter<double>("track_eta");

  // Vertices
  skim.skimVertices = iConfig.getParameter<bool>("skimVertices");
  skim.vertex_keepAllCollections = iConfig.getParameter<bool>
                                      ("vertex_keepAllCollections");
  skim.vertex_collectionList = iConfig.getParameter<std::vector<std::string> >
                                      ("vertex_collectionList");

  std::cout << "Constructor of NTupleProducer - END" << std::endl;
} 



// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
NTupleProducer::~NTupleProducer ()
{
}


// ----------------------------------------------------------------------------
// Analyze
// ----------------------------------------------------------------------------
void NTupleProducer::analyze (const edm::Event & iEvent, 
                              const edm::EventSetup & iSetup)
{

  using namespace edm;
  using namespace IPHCTree;
  using namespace std;


  // -------------------------------------
  // Getting th event from minitree 
  // -------------------------------------
  edm::Handle <IPHCTree::MTEvent> minitreeHandle;
  iEvent.getByType (minitreeHandle);
  if (!minitreeHandle.isValid())
  {
    ERROR("Produce") << "IPHCTree::MTEvent is not found." << std::endl;
    return;
  }
  const IPHCTree::MTEvent* minitree = minitreeHandle.product ();


  // -------------------------------------
  // Reseting ntuple current event
  // -------------------------------------
  ntuple->Reset();
  if (verbose > 0)
  {
    std::cout << " ----- New event  ---- " << std::endl;
    std::cout << "EventNumber =" << minitree->general.eventNb << std::endl;
  }
  

  // -------------------------------------
  // Saving event into histo
  // -------------------------------------
  theNormHisto->Fill(1);
  theNormHistoByTMEME->Fill(minitree->mc.TMEME);

 
  // -------------------------------------
  // General info
  // -------------------------------------
  ntuple->general = minitree->general;
  ntuple->mc      = minitree->mc;
  ntuple->pileup  = minitree->pileup;


  // -------------------------------------
  // Trigger
  // -------------------------------------
  if (!skim.skimTrigger)
  {
    std::cout << "Filling trigger (no skim) ..." << std::endl;
    ntuple->trigger = minitree->trigger;
  }
  else
  {
    std::cout << "Filling trigger (skim) ..." << std::endl;

    // Getting trigger data in a comfortable format
    std::vector<IPHCTree::NTTriggerPathType> paths;
    minitree->trigger.GetSubTable("*",paths); 

    // Declaring a new container for trigger bits and prescales
    std::map<std::string, std::pair<UInt_t,Bool_t> > skimmed;

    for (unsigned int i=0;i<paths.size();i++)
    {
      for (unsigned int j=0;j<skim.triggerList.size();j++)
      {
        if (skim.triggerList[j]==paths[i].name)
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
  if (!skim.skimElectrons) std::cout << "Filling electrons (no skim) ..." << std::endl;
  else std::cout << "Filling electrons (skim) ..." << std::endl;

  // Get list of electron collection names
  std::set<std::string> labels;
  if (!skim.skimElectrons || skim.electron_keepAllCollections)
  {
    minitree->electrons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.electron_collectionList.size();i++)
    {
      if (skim.electron_collectionList[i]=="") continue;
      if (minitree->electrons.DoYouKnowCollection
             (skim.electron_collectionList[i]))
                   labels.insert(skim.electron_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->electrons.Reserve(labels);

  // Fill electrons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->electrons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->electrons.size(); i++) 
    {
      if (!skim.skimElectrons || 
          (minitree->electrons[i].p4.Pt() > skim.electron_pt && 
           fabs(minitree->electrons[i].p4.Eta()) < skim.electron_eta) )
        ntuple -> NewElectron(dynamic_cast<const IPHCTree::NTElectron&>(minitree->electrons[i]));
    }
  }


  // -------------------------------------
  // Photons
  // -------------------------------------
  if (!skim.skimPhotons) std::cout << "Filling photons (no skim) ..." << std::endl;
  else std::cout << "Filling photons (skim) ..." << std::endl;

  // Get list of photon collection names
  labels.clear();
  if (!skim.skimPhotons || skim.photon_keepAllCollections)
  {
    minitree->photons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.photon_collectionList.size();i++)
    {
      if (skim.photon_collectionList[i]=="") continue;
      if (minitree->photons.DoYouKnowCollection
             (skim.photon_collectionList[i]))
                   labels.insert(skim.photon_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->photons.Reserve(labels);

  // Fill photons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->photons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->photons.size(); i++) 
    {
      if (!skim.skimPhotons || 
          (minitree->photons[i].p4.Pt() > skim.photon_pt && 
           fabs(minitree->photons[i].p4.Eta()) < skim.photon_eta) )
        ntuple -> NewPhoton(dynamic_cast<const IPHCTree::NTPhoton&>(minitree->photons[i]));
    }
  }


  // -------------------------------------
  // Muons
  // -------------------------------------
  if (!skim.skimMuons) std::cout << "Filling muons (no skim) ..." << std::endl;
  else std::cout << "Filling muons (skim) ..." << std::endl;

  // Get list of muon collection names
  labels.clear();
  if (!skim.skimMuons || skim.muon_keepAllCollections)
  {
    minitree->muons.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.muon_collectionList.size();i++)
    {
      if (skim.muon_collectionList[i]=="") continue;
      if (minitree->muons.DoYouKnowCollection
             (skim.muon_collectionList[i]))
                   labels.insert(skim.muon_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->muons.Reserve(labels);

  // Fill muons
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->muons.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->muons.size(); i++) 
    {
      if (!skim.skimMuons || 
          (minitree->muons[i].p4.Pt() > skim.muon_pt && 
           fabs(minitree->muons[i].p4.Eta()) < skim.muon_eta) )
        ntuple -> NewMuon(dynamic_cast<const IPHCTree::NTMuon&>(minitree->muons[i]));
    }
  }



  // -------------------------------------
  // Taus
  // -------------------------------------
  if (!skim.skimTaus) std::cout << "Filling taus (no skim) ..." << std::endl;
  else std::cout << "Filling taus (skim) ..." << std::endl;

  // Get list of tau collection names
  labels.clear();
  if (!skim.skimTaus || skim.tau_keepAllCollections)
  {
    minitree->taus.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.tau_collectionList.size();i++)
    {
      if (skim.tau_collectionList[i]=="") continue;
      if (minitree->taus.DoYouKnowCollection
             (skim.tau_collectionList[i]))
                   labels.insert(skim.tau_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->taus.Reserve(labels);

  // Fill taus
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->taus.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->taus.size(); i++) 
    {
      if (!skim.skimTaus || 
          (minitree->taus[i].p4.Pt() > skim.tau_pt && 
           fabs(minitree->taus[i].p4.Eta()) < skim.tau_eta) )
        ntuple -> NewTau(dynamic_cast<const IPHCTree::NTTau&>(minitree->taus[i]));
    }
  }


  // -------------------------------------
  // Jets
  // -------------------------------------
  if (!skim.skimJets) std::cout << "Filling jets (no skim) ..." << std::endl;
  else std::cout << "Filling jets (skim) ..." << std::endl;

  // Get list of jet collection names
  labels.clear();
  if (!skim.skimJets || skim.jet_keepAllCollections)
  {
    minitree->jets.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.jet_collectionList.size();i++)
    {
      if (skim.jet_collectionList[i]=="") continue;
      if (minitree->jets.DoYouKnowCollection
             (skim.jet_collectionList[i]))
                   labels.insert(skim.jet_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->jets.Reserve(labels);

  // Fill jets
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->jets.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->jets.size(); i++) 
    {
      if (!skim.skimJets || 
          (minitree->jets[i].p4.Pt() > skim.jet_pt && 
           fabs(minitree->jets[i].p4.Eta()) < skim.jet_eta) )
        ntuple -> NewJet(dynamic_cast<const IPHCTree::NTJet&>(minitree->jets[i]));
    }
  }


  // -------------------------------------
  // Met
  // -------------------------------------
  if (!skim.skimJets) std::cout << "Filling met (no skim) ..." << std::endl;
  else std::cout << "Filling met (skim) ..." << std::endl;

  // Get list of met collection names
  labels.clear();
  if (!skim.skimJets || skim.jet_keepAllCollections)
  {
    minitree->met.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.jet_collectionList.size();i++)
    {
      if (skim.jet_collectionList[i]=="") continue;
      if (minitree->met.DoYouKnowCollection
             (skim.jet_collectionList[i]))
                   labels.insert(skim.jet_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->met.Reserve(labels);

  // Fill met
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->met.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->met.size(); i++) 
    {
      ntuple -> NewMet(dynamic_cast<const IPHCTree::NTMET&>(minitree->met[i]));
    }
  }


  // -------------------------------------
  // Tracks
  // -------------------------------------
  if (!skim.skimTracks) std::cout << "Filling tracks (no skim) ..." << std::endl;
  else std::cout << "Filling tracks (skim) ..." << std::endl;

  // Get list of track collection names
  labels.clear();
  if (!skim.skimTracks || skim.track_keepAllCollections)
  {
    minitree->tracks.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.track_collectionList.size();i++)
    {
      if (skim.track_collectionList[i]=="") continue;
      if (minitree->tracks.DoYouKnowCollection
             (skim.track_collectionList[i]))
                   labels.insert(skim.track_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->tracks.Reserve(labels);

  // Fill tracks
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->tracks.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->tracks.size(); i++) 
    {
      if (!skim.skimTracks || 
          (minitree->tracks[i].p4.Pt() > skim.track_pt && 
           fabs(minitree->tracks[i].p4.Eta()) < skim.track_eta) )
        ntuple -> NewTrack(dynamic_cast<const IPHCTree::NTTrack&>(minitree->tracks[i]));
    }
  }

  
  // -------------------------------------
  // Vertices
  // -------------------------------------
  if (!skim.skimVertices) std::cout << "Filling vertices (no skim) ..." << std::endl;
  else std::cout << "Filling vertices (skim) ..." << std::endl;

  // Get list of vertex collection names
  labels.clear();
  if (!skim.skimVertices || skim.vertex_keepAllCollections)
  {
    minitree->vertices.GetCollectionList(labels);
  }
  else
  {
    for (unsigned int i=0;i<skim.vertex_collectionList.size();i++)
    {
      if (skim.vertex_collectionList[i]=="") continue;
      if (minitree->vertices.DoYouKnowCollection
             (skim.vertex_collectionList[i]))
                   labels.insert(skim.vertex_collectionList[i]);
    }
  }

  // Reseve collection names for ntuple
  ntuple->vertices.Reserve(labels);

  // Fill vertices
  for (std::set<std::string>::const_iterator theLabel = labels.begin();
       theLabel != labels.end(); theLabel++)
  {
    ntuple->vertices.SelectLabel(*theLabel);
    for (unsigned int i=0; i<minitree->vertices.size(); i++) 
    {
      ntuple -> NewVertex(dynamic_cast<const IPHCTree::NTVertex&>(minitree->vertices[i]));
    }
  }




  /*  
  //apply skimming
  
  int nmuon = 0; 
  int nelec = 0; 
  
  int passSkim = false;
  int passSkimMuon = false;
  int passSkimElec = false;
  
  if(numberOfLept4Skim != -1){
    if(useMuonIdSkim) nmuon = GetNumberOfIDMuons(*ntevt, muon_cut_pt_skim, muon_cut_iso_skim);
    else nmuon = GetNumberOfMuons(*ntevt, muon_cut_pt_skim, muon_cut_iso_skim);
    if(useElectronIdSkim) nelec = GetNumberOfIDElectrons(*ntevt, electron_cut_pt_skim, electron_cut_iso_skim);
    else nelec = GetNumberOfElectrons(*ntevt, electron_cut_pt_skim, electron_cut_iso_skim);
    if(nmuon >= numberOfMuon4Skim) passSkimMuon = true;
    if(nelec >= numberOfElec4Skim) passSkimElec = true;
  }//else passSkim = true;
  
  int ntotlepton = nmuon+nelec;
  if(ntotlepton >= numberOfLept4Skim && passSkimMuon && passSkimElec )passSkim = true;
 
 
  int passTauSkim = false;
  if(doTauSkimming){
    int ntau = GetNumberOfTaus(*ntevt, tau_cut_pt_skim, tau_algo_skim);
    if(ntau >= numberOfTau4Skim) passTauSkim = true;
  }
  
  int passVerticeskim = false;
  if(doJetSkimming){
    int njet = GetNumberOfJets(*ntevt, jet_cut_pt_skim, jet_cut_eta_skim, jet_algo_skim);
    if(njet >= numberOfJet4Skim) passJetSkim = true;
  }
  
  bool passTMEME = false;
  if(doTMEMESkimming){
  	for(unsigned int x = 0; x<TMEMESkimList.size(); x++){
		if(ntevt->TMEME== TMEMESkimList[x])
			passTMEME = true;
	} 
	//if(!passTMEME) passSkim = false;
  }
  bool passChannel = false;
  if(doMCDiLepSkimming){
	for(unsigned int x = 0 ; x<MCDiLepList.size(); x++){
		int TMEME = ntevt->TMEME;
		if(MCDiLepList[x] == string("ee") && (TMEME == 2  || TMEME == 10101 || TMEME == 20200 )) passChannel = true;
        	if(MCDiLepList[x] == string("mumu") && (TMEME == 20 || TMEME == 11010 || TMEME == 22000 )) passChannel = true;
        	if(MCDiLepList[x] == string("emu") && (TMEME == 11 || TMEME == 11001 || TMEME == 10110 || TMEME == 21100 )) passChannel = true;
        	if(MCDiLepList[x] == string("tautau") && (TMEME == 20000 )) passChannel = true;
        	if(MCDiLepList[x] == string("ljets") && (TMEME == 1 || TMEME == 10 || TMEME == 10000 || TMEME == 11000 || TMEME == 10100 )) passChannel = true;
		if(MCDiLepList[x] == string("had") && (TMEME == 0 )) passChannel = true;
	}
	//if(!passChannel) passSkim = false;
  }
  

  // --- Filling tree
  if ((numberOfLept4Skim == -1 && !doTMEMESkimming && !doMCDiLepSkimming && !doTriggerSkimming && !doTauSkimming && !doJetSkimming)||
      (numberOfLept4Skim != -1 && passSkim)|| 
      (doTMEMESkimming   && passTMEME)|| 
      (doMCDiLepSkimming && passChannel)|| 
      (doTriggerSkimming && passTriggerSkim)|| 
      (doTauSkimming     && passTauSkim)||
      (doJetSkimming     && passJetSkim))
  */

  std::cout << "Store the event into the ntuple ..." << std::endl; 
  output->Fill ();
  std::cout << "--> the event is successfully stored into the ntuple.";
  std::cout << std::endl;

}



void NTupleProducer::beginJob ()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void NTupleProducer::endJob ()
{ 
}

/*
void NTupleProducer::beginJob ()
{
  std::cout << "BeginJob of NTupleProducer" << std::endl;
  std::cout << "=========================================================== " << std::endl;
  std::cout << " " << std::endl;
  
  int nSkim = 0;
  if(numberOfLept4Skim!=-1)   {nSkim++; std::cout << "You are about to skim events according to the presence of reconstructed electrons and muons : numberOfLept4Skim!=-1" << std::endl;}
  if(doTMEMESkimming==true)   {nSkim++; std::cout << "You are about to skim events according to TMEME : doTMEMESkimming==true" << std::endl;}
  if(doMCDiLepSkimming==true) {nSkim++; std::cout << "You are about to skim events according to MCDiLepSkimming information : doMCDiLepSkimming==true" << std::endl;}
  if(doTauSkimming==true)     {nSkim++; std::cout << "You are about to skim events according to the presence of reconstructed taus : doTauSkimming==true" << std::endl;}
  if(doTriggerSkimming==true) {nSkim++; std::cout << "You are about to skim events according to trigger information : doTriggerSkimming==true" << std::endl;}
  
  std::cout << " " << std::endl;
  if (nSkim>0) std::cout << "YOU ARE ABOUT TO FILTER EVENTS ACCORDING TO MULTIPLE SKIM CRITERIA, IS THIS WHAT YOU WANT TO DO ? " << std::endl;
  std::cout << " " << std::endl;
  std::cout << "=========================================================== " << std::endl;

}

// ------------ method called once each job just after ending the event loop  ------------
void NTupleProducer::endJob ()
{ 
  std::cout << "EndJob of NTupleProducer" << std::endl; 
  std::cout << "=========================================================== " << std::endl;
  std::cout << " " << std::endl;
  if(numberOfLept4Skim!=-1)    std::cout << "Events have been skimmed according to the presence of reconstructed electrons and muons : numberOfLept4Skim!=-1" << std::endl;
  if(doTMEMESkimming==true)    std::cout << "Events have been skimmed according to TMEME : doTMEMESkimming==true" << std::endl;
  if(doMCDiLepSkimming==true)  std::cout << "Events have been skimmed according to MCDiLepSkimming information : doMCDiLepSkimming==true" << std::endl;
  if(doTauSkimming==true)      std::cout << "Events have been skimmed according to the presence of reconstructed taus : doTauSkimming==true" << std::endl;
  if(doTriggerSkimming==true)  std::cout << "Events have been skimmed according to trigger information : doTriggerSkimming==true" << std::endl;
  std::cout << " " << std::endl;
  std::cout << "=========================================================== " << std::endl;
}





int NTupleProducer::GetNumberOfIDMuons(IPHCTree::NTEvent     event, double muon_cut_pt_skim, double muon_cut_iso_skim){

  int nmuons = 0;
  std::vector<NTMuon> themuons = event.muons;
  for(unsigned int imuon=0; imuon< themuons.size(); imuon++){
    NTMuon muon = themuons[imuon];// to avoid const problem while calling NTLepton methods!
    if(muon.MuonType<100)                           continue; // isGlobalMuon
    if((muon.MuonType-(muon.MuonType/10)*10) ==0)   continue; //isTrackerMuon
    if(muon.Chi2           >= 10)        continue;
    if(muon.NTrValidHits   <= 10)        continue;
    if(muon.NValidHits     <=  0)        continue;
    if(fabs(muon.D0Inner)  >= 0.02)      continue;
    if(fabs(muon.p4.Eta()) >= 2.4)       continue;
    if(muon_cut_pt_skim>0 && muon.p4.Pt() < muon_cut_pt_skim) continue;
    if(muon_cut_iso_skim>0 && muon.RelIso03() > muon_cut_iso_skim) continue;
    nmuons++;
  }
  
  return nmuons;
  
}

int NTupleProducer::GetNumberOfMuons(IPHCTree::NTEvent     event, double muon_cut_pt_skim, double muon_cut_iso_skim){

  int nmuons = 0;
  std::vector<NTMuon> themuons = event.muons;
  for(unsigned int imuon=0; imuon< themuons.size(); imuon++){
    NTMuon muon = themuons[imuon];// to avoid const problem while calling NTLepton methods!
    if(muon_cut_pt_skim>0 && muon.p4.Pt() < muon_cut_pt_skim) continue;
    if(muon_cut_iso_skim>0 && muon.RelIso03() > muon_cut_iso_skim) continue;
    nmuons++;
  }
  return nmuons;
  
}



int NTupleProducer::GetNumberOfIDElectrons(IPHCTree::NTEvent    event, double electron_cut_pt_skim, double electron_cut_iso_skim){


  int nelectrons = 0;
  
  std::vector<NTElectron> theelecs = event.electrons;
  for(unsigned int ielec=0; ielec< theelecs.size(); ielec++){
    NTElectron electron = theelecs[ielec];// to avoid const problem while calling NTLepton methods
    
    bool hadId(electron.elecIdWP90_r & 0x1);
    bool isNotConv(electron.elecIdWP90_r & 0x4);    
    
    if(!electron.isGsfElectron)                    continue; 
    if(!hadId)                                     continue; //hadId
    if(!isNotConv)                                 continue; //isNotConv
    //if(electron.elspike>0.95)             continue;
    if(electron.isEcalDriven!=1)                   continue;
    if(fabs(electron.D0)      >=0.04)    continue; 
    if(fabs(electron.p4.Eta())>=2.5)     continue;
    if(electron.ET_SC         <=15)      continue;
    if(electron_cut_pt_skim>0 && electron.p4.Pt() < electron_cut_pt_skim) continue;
    if(electron_cut_iso_skim>0 && electron.RelIso03() > electron_cut_iso_skim) continue;
    nelectrons++;
  }
  
  
  return nelectrons;
  

}

int NTupleProducer::GetNumberOfElectrons(IPHCTree::NTEvent    event, double electron_cut_pt_skim, double electron_cut_iso_skim){


  int nelectrons = 0;
  
  std::vector<NTElectron> theelecs = event.electrons;
  for(unsigned int ielec=0; ielec< theelecs.size(); ielec++){
    NTElectron electron = theelecs[ielec];// to avoid const problem while calling NTLepton methods
    if(electron_cut_pt_skim>0 && electron.p4.Pt() < electron_cut_pt_skim) continue;
    if(electron_cut_iso_skim>0 && electron.RelIso03() > electron_cut_iso_skim) continue;
    nelectrons++;
  }
  
  
  return nelectrons;
  

}


int NTupleProducer::GetNumberOfTaus(IPHCTree::NTEvent event, double tau_cut_pt_skim, std::string algo){

  int ntaus = 0;
  std::vector<IPHCTree::NTCollection <NTTau> > tausVec = event.tausVec;
  for(unsigned int ivec=0; ivec< tausVec.size(); ivec++){
     if(tausVec[ivec].algo == algo){
       for(unsigned int itau=0; itau< tausVec[ivec].objects.size(); itau++){
          NTTau tau = tausVec[ivec].objects[itau];
          if(tau_cut_pt_skim>0 && tau.p4.Pt() < tau_cut_pt_skim) continue;
          ntaus++;
       }
     }
  }
  return ntaus;
  
}

int NTupleProducer::GetNumberOfJets(IPHCTree::NTEvent event, double jet_cut_pt_skim, double jet_cut_eta_skim, std::string algo){

  int njets = 0;
  std::vector <IPHCTree::NTJetMet > jetMetVec = event.jetMetVec;
  for(unsigned int ivec=0; ivec< jetMetVec.size(); ivec++){
     if(jetMetVec[ivec].algo == algo){
       for(unsigned int ijet=0; ijet< jetMetVec[ivec].objects.size(); ijet++){
          NTJet jet = jetMetVec[ivec].objects[ijet];
          if(jet_cut_pt_skim>0 && jet.p4.Pt() < jet_cut_pt_skim) continue;
	  if(fabs(jet.p4.Eta()) > jet_cut_eta_skim) continue;
          njets++;
       }
     }
  }
  return njets;
  
}
*/


DEFINE_FWK_MODULE (NTupleProducer);

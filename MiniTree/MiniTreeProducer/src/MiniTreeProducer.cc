#include "MiniTree/MiniTreeProducer/interface/MiniTreeProducer.h"
#include "MiniTree/MiniTreeProducer/interface/MonteCarloOrigin.h"
#include "IPHCDataFormat/MTFormat/interface/MTTransient.h"

#define DEBUG_MSG cout << "DEBUG (" << __FILE__ << ", l." << __LINE__ << ") "

#define ALEX_ERIC_CARO

// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
MiniTreeProducer::MiniTreeProducer (const edm::ParameterSet & iConfig)
{
  // Measuring Start time
  StartTime = std::clock();

  // Display Beginning
  std::cout << "Constructor of MiniTreeProducer - BEGIN" << std::endl;

  // Extract MiniTreeProducer settings
  cfg.verbose           = iConfig.getParameter<unsigned int>  ("verbose");
  cfg.isAOD             = iConfig.getParameter<bool>          ("isAOD");
  cfg.isData            = iConfig.getParameter<bool>          ("isData");

  // Extract info for Triggers
  cfg.doTrigger         = iConfig.getParameter<bool>         ("doTrigger");
  cfg.saveAllTriggers   = iConfig.getParameter<bool>         ("saveAllTriggers");
  cfg.triggerList       = iConfig.getParameter<std::vector<std::string> >
                      ("triggerList");

  // Extract info for Electrons
  cfg.doElectrons       = iConfig.getParameter<bool>     ("doElectrons");
  cfg.electron_cut_pt   = iConfig.getParameter<double>   ("electron_cut_pt");
  cfg.electron_cut_eta  = iConfig.getParameter<double>   ("electron_cut_eta");
  cfg.electron_saveAllID= iConfig.getParameter<bool>     ("electron_saveAllID");
  cfg.electron_IDlist   = iConfig.getParameter<std::vector<std::string> >     ("electron_IDlist");
  cfg.electronHLTmatching = iConfig.getParameter<std::vector<std::string> >   ("electronHLTmatching");
  cfg.electronProducer    = iConfig.getParameter<std::vector<edm::InputTag> > ("electronProducer");
  cfg.electron_Isolist    = iConfig.getParameter<std::vector<std::string> >   ("electron_Isolist"); 
  cfg.electron_rhoCorrSrc = iConfig.getParameter<std::vector<std::string> >   ("electron_rhoCorrSrc");
  cfg.doElectronMatch     = iConfig.getParameter<edm::InputTag>               ("doElectronMatch");

  // Extract info for Photons
  cfg.doPhotons         = iConfig.getParameter<bool>     ("doPhotons");
  cfg.photon_cut_pt     = iConfig.getParameter<double>   ("photon_cut_pt");
  cfg.photon_cut_eta    = iConfig.getParameter<double>   ("photon_cut_eta");
  cfg.photonHLTmatching = iConfig.getParameter<std::vector<std::string> >
                      ("photonHLTmatching");
  cfg.photonProducer    = iConfig.getParameter<std::vector<edm::InputTag> >
                      ("photonProducer");

  // Extract info for Muons
  cfg.doMuons         = iConfig.getParameter<bool>     ("doMuons");
  cfg.muon_cut_pt     = iConfig.getParameter<double>   ("muon_cut_pt");
  cfg.muon_cut_eta    = iConfig.getParameter<double>   ("muon_cut_eta");
  cfg.muon_cut_sta    = iConfig.getParameter<bool>     ("muon_cut_keepStandaloneMu");
  cfg.muon_cut_trk    = iConfig.getParameter<bool>     ("muon_cut_keepTrackerMu");
  cfg.muon_cut_cal    = iConfig.getParameter<bool>     ("muon_cut_keepCaloMu");
  cfg.muon_cut_glb    = iConfig.getParameter<bool>     ("muon_cut_keepGlobalMu");
  cfg.muon_IDlist     = iConfig.getParameter<std::vector<std::string> >   ("muon_IDlist");
  cfg.muonHLTmatching = iConfig.getParameter<std::vector<std::string> >   ("muonHLTmatching");
  cfg.muonProducer    = iConfig.getParameter<std::vector<edm::InputTag> > ("muonProducer");
  cfg.muon_Isolist    = iConfig.getParameter<std::vector<std::string> >   ("muon_Isolist"); 
  cfg.doMuonMatch     = iConfig.getParameter<edm::InputTag >              ("doMuonMatch");

  // Extract info for Taus
  cfg.doTaus            = iConfig.getParameter<bool>     ("doTaus");
  cfg.tau_cut_pt        = iConfig.getParameter<double>   ("tau_cut_pt");
  cfg.tau_cut_eta       = iConfig.getParameter<double>   ("tau_cut_eta");
  cfg.tau_saveAllID     = iConfig.getParameter<bool>     ("tau_saveAllID");
  cfg.tau_IDlist        = iConfig.getParameter<std::vector<std::string> >
                      ("tau_IDlist");
  cfg.tauHLTmatching    = iConfig.getParameter<std::vector<std::string> > ("tauHLTmatching");
  cfg.tauProducer       = iConfig.getParameter<std::vector<edm::InputTag> >
                      ("tauProducer");

  // Extract info for Tracks
  cfg.doTracks          = iConfig.getParameter<bool>     ("doTracks");
  cfg.track_cut_pt      = iConfig.getParameter<double>   ("track_cut_pt");
  cfg.track_cut_eta     = iConfig.getParameter<double>   ("track_cut_eta");
  cfg.trackProducer     = iConfig.getParameter<std::vector<edm::InputTag> >
                      ("trackProducer");

  // Extract info for PFCandidates
  cfg.doPFCandidates        = iConfig.getParameter<bool>     ("doPFCandidates");
  cfg.pfcandidate_cut_dR    = iConfig.getParameter<double>   ("pfcandidate_cut_dR");
  cfg.pfcandidate_cut_dz    = iConfig.getParameter<double>   ("pfcandidate_cut_dz");
  cfg.pfcandidate_cut_minPt = iConfig.getParameter<double>   ("pfcandidate_cut_minPt");
  cfg.pfcandidate_VertexTag = iConfig.getParameter<std::vector<edm::InputTag> >
                            ("pfcandidate_VertexTag");
  cfg.pfcandidate_InputTag  = iConfig.getParameter<std::vector<edm::InputTag> >
                            ("pfcandidate_InputTag");

  // Extract info for Vertices
  cfg.doVertices       = iConfig.getParameter<bool>     ("doVertices");  
  cfg.saveAllVertex    = iConfig.getParameter<bool>     ("saveAllVertex");
  cfg.vertexProducer   = iConfig.getParameter<std::vector<edm::InputTag> >
                     ("vertexProducer");

  // Extract info for BeamSpot
  cfg.doBeamSpot       = iConfig.getParameter<bool>          ("doBeamSpot");  
  cfg.beamSpotProducer = iConfig.getParameter<edm::InputTag> ("beamSpotProducer");

  // Extract info for JetMET
  cfg.doJetMet         = iConfig.getParameter<bool>        ("doJetMet");  
  cfg.doMuonCorrection = iConfig.getParameter<bool>        ("doMuonCorrection");
  cfg.jet_cut_pt       = iConfig.getParameter<double>      ("jet_cut_pt");
  cfg.jet_cut_eta      = iConfig.getParameter<double>      ("jet_cut_eta");
  cfg.jetIDList        = iConfig.getParameter<std::vector<std::string> > ("jetIDList"); 
  cfg.jetBTagList      = iConfig.getParameter<std::vector<std::string> > ("jetBTagList"); 
  cfg.jetHLTmatching   = iConfig.getParameter<std::vector<std::string> > ("jetHLTmatching");
  cfg.jetmetProducer   = iConfig.getParameter<VParameters> ("jetmetProducer");

  // Extract info for Pile-Up
  cfg.doPileUp              = iConfig.getParameter<bool>          ("doPileUp");
  cfg.rho_PUUE_dens         = iConfig.getParameter<edm::InputTag> ("rho_PUUE_dens");
  cfg.neutralRho_PUUE_dens  = iConfig.getParameter<edm::InputTag> ("neutralRho_PUUE_dens");

  // Extract info for Monte Carlo
  cfg.doGenParticleCollection = iConfig.getParameter<bool> ("doGenParticleCollection");
  cfg.mcDescentMax            = iConfig.getParameter<unsigned int> ("mcDescentMax");
  cfg.mcNGenPartMax           = iConfig.getParameter<unsigned int> ("mcNGenPartMax");
  cfg.mcTauDecayMode          = iConfig.getParameter<unsigned int> ("mcTauDecayMode");
  cfg.mcHeavyQuarkDecayMode   = iConfig.getParameter<unsigned int> ("mcHeavyQuarkDecayMode");

  // Register the final product : the MiniTree Event
  produces<IPHCTree::MTEvent> (); 

  std::cout << "Constructor of MiniTreeProducer - END" << std::endl;
}


// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
MiniTreeProducer::~MiniTreeProducer()
{
  // Measuring Start time
  std::clock_t EndTime = std::clock();

  // Failure with clock measurements
  if (StartTime==-1 || EndTime==-1)
  {
    std::cout << "Elapsed time not available" << std::endl;
  }

  // Success with clock measurements
  else
  {
    // Computing elapsed time (in second)
    unsigned long ElapsedTime = (EndTime - StartTime) / CLOCKS_PER_SEC;

    // Converting elapsed time in day-hour-minute-second format
    unsigned int nday  = ElapsedTime/(24*3600); ElapsedTime %= 24*3600;
    unsigned int nhour = ElapsedTime/3600;      ElapsedTime %= 3600;
    unsigned int nmin  = ElapsedTime/60;        
    unsigned int nsec  = ElapsedTime%60;

    // Displaying elapsed time
    std::cout << "Elapsed time with MiniTreeProducer : ";
    if (nday !=0) std::cout << nday  << "d";
    if (nhour!=0) std::cout << nhour << "h";
    if (nmin !=0) std::cout << nmin  << "m";
    std::cout << nsec  << "s"<< std::endl;
  }

  // Program end with SUCCESS code
  std::cout << "Normal end of program" << std::endl;
}


// ----------------------------------------------------------------------------
// Method called once each job just before starting event loop
// ----------------------------------------------------------------------------
void MiniTreeProducer::beginJob()
{
  std::cout << "BeginJob for MiniTreeProducer " << std::endl;
}


// ----------------------------------------------------------------------------
// Method called once each job just after ending the event loop
// ----------------------------------------------------------------------------
void MiniTreeProducer::endJob()
{
  std::cout << "EndJob for MiniTreeProducer" << std::endl;
}


// ----------------------------------------------------------------------------
// Produce method (method executed for each event)
// ----------------------------------------------------------------------------
void MiniTreeProducer::produce(edm::Event& iEvent, 
                               const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace IPTools;

 if (cfg.verbose > 0) std::cout << "--------- new event ---------" << std::endl;

  // -----------------------------
  // Creating a new MTEvent
  // -----------------------------
  if (cfg.verbose > 1) std::cout << "Creating a new MTEvent ..." << std::endl;
  std::auto_ptr<IPHCTree::MTEvent> evt(new IPHCTree::MTEvent);

  // -----------------------------
  // Defining common pointer
  // -----------------------------
  const reco::BeamSpot* bs = 0;
  const reco::Vertex*   vp = 0;
  const TransientTrackBuilder* trackBuilder = 0;
  const reco::GenParticleCollection * genParticles = 0;
  const pat::TriggerEvent* patTriggerEvent = 0;
  edm::Handle<std::vector<reco::Track> > trackHandle;

  // --------------------
  // Fill Event info 
  // --------------------
  if (cfg.verbose > 1) std::cout << "Filling event info ..." << std::endl;
  
  fillGeneralInfo(iEvent,iSetup,evt);

  // --------------------
  // Fill MC Truth 
  // --------------------
  if (!cfg.isData)
  {

    // -------------------------------------
    // Gen Event Info
    // -------------------------------------
    if (cfg.verbose > 1) std::cout << "Filling MC event info ..." << std::endl;

    edm::Handle<GenEventInfoProduct> theGenEventInfo;
    iEvent.getByType(theGenEventInfo);
    if (theGenEventInfo.isValid())
    {
      fillGenEventInfo(iEvent,iSetup,evt,theGenEventInfo);
    }
    else
    {
      ERROR("Produce") << "GenEventInfoProduct is missing." << std::endl; 
    }

    // -------------------------------------
    // Pileup summary info
    // -------------------------------------
    if (cfg.doPileUp)
    {
      if (cfg.verbose > 1) std::cout << "Filling Pile-Up ..." << std::endl;

      edm::Handle<std::vector< PileupSummaryInfo> > PupInfo;
      iEvent.getByLabel("addPileupInfo", PupInfo);
      if (PupInfo.isValid())
      {
        fillPileUp(iEvent,iSetup,evt,PupInfo);
      }
      else
      {
        ERROR("Produce") << "PileupSummaryInfo is missing." << std::endl; 
      }
    }

    // -------------------------------------
    // Fill skimmed GenparticleCollection 
    // -------------------------------------
    if (cfg.doGenParticleCollection)
    {
      if (cfg.verbose > 1) std::cout << "Filling GenParticles ..." << std::endl;
      edm::Handle<reco::GenParticleCollection> genParticlesHandle;
      iEvent.getByLabel ("genParticles", genParticlesHandle);
      if (genParticlesHandle.isValid())
      {
        fillGenParticles(iEvent,iSetup,evt,genParticlesHandle);
        genParticles = genParticlesHandle.product();
      }
      else
      {
        ERROR("Produce") << "GenParticles collection is missing." << std::endl; 
      }
    }
  }

  // --------------------
  // Fill PU/UE densities
  // --------------------

  // Rho
  edm::Handle<double> h_rho;
  iEvent.getByLabel( cfg.rho_PUUE_dens, h_rho);
  if (!h_rho.isValid())
  {  ERROR("Produce") << "cfg.rho_PUUE_dens is missing." << std::endl; return; }
  
  evt->pileup.rho_PUUE_dens = (*h_rho);

  // Neutral Rho
  edm::Handle<double> h_neutralRho;
  iEvent.getByLabel( cfg.neutralRho_PUUE_dens, h_neutralRho);
  if (!h_neutralRho.isValid())
  {  ERROR("Produce") << "cfg.neutralRho_PUUE_dens is missing." << std::endl; return; }
  
  evt->pileup.neutralRho_PUUE_dens = (*h_neutralRho);

  // ------------------------
  //  Fill TriggerResults
  // ------------------------
  if (cfg.doTrigger)
  {

    if (cfg.verbose>1) std::cout << "Filling trigger ..." << std::endl;

    // Getting Trigger products
     
    edm::Handle< pat::TriggerEvent > triggerHandle;
    iEvent.getByLabel("patTriggerEvent", triggerHandle);

    // Filling Minitree if TriggerResults is available
    if (triggerHandle.isValid())
    {
      patTriggerEvent = triggerHandle.product();
      fillTriggerInfo(iEvent,iSetup,evt,patTriggerEvent);
    }
    else
    { 
      ERROR("Produce") << "pat::TriggerEvent product is missing." << std::endl;
    }
  }

  // ------------------------
  //  Fill BeamSpot position
  // ------------------------
  if (cfg.doBeamSpot)
  {
    if (cfg.verbose>1) std::cout << "Filling beamspot ..." << std::endl;

    // Getting BeamSpot  
    edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
    iEvent.getByType(recoBeamSpotHandle);

    // Filling Minitree if BeamSpot is available
    if (recoBeamSpotHandle.isValid())
    {
      bs = recoBeamSpotHandle.product();
      evt->beamSpot.p3.SetXYZ( bs->x0(),
                               bs->y0(),
                               bs->z0() );
      evt->beamSpot.p3Err.SetXYZ( bs->x0Error(),
                                  bs->y0Error(),
                                  bs->z0Error()  );
    }
    else
    { 
      ERROR("Produce") << "BeamSpot product is missing." << std::endl;
    }
  }

  // ------------------------
  //  Fill Tracks
  // ------------------------
  if (cfg.doTracks)
  {
    if (cfg.verbose>1) std::cout << "Filling tracks ..." << std::endl;

    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.trackProducer.size();i++)
    {
      labels.insert(cfg.trackProducer[i].label());//+":"+
      //                    cfg.trackProducer[i].instance()+":"+
      //                    cfg.trackProducer[i].process());
    }
    evt->tracks.Reserve(labels);

    // Loop over the different taus collection
    for (unsigned int m=0 ; m<cfg.trackProducer.size(); m++) 
    {
      evt->tracks.SelectLabel(cfg.trackProducer[m].label()); //+":"+
      //                              cfg.trackProducer[m].instance()+":"+
      //                              cfg.trackProducer[m].process());

      // Getting tracks
      iEvent.getByLabel(cfg.trackProducer[m], trackHandle);

      // Filling MiniTree if tracks are available
      if (trackHandle.isValid()) 
        fillTracks(iEvent,iSetup,evt,trackHandle.product(),bs);
      else
      { 
        ERROR("Produce") << "Track collection '" 
                         << cfg.trackProducer[m] << "' is missing." << std::endl;
      }
    }
  }

  // ------------------------
  //  Fill PFCandidates
  // ------------------------
  
  if (cfg.doPFCandidates)
  {
    if (cfg.verbose>1) std::cout << "Filling PFCandidates ..." << std::endl;

    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.pfcandidate_InputTag.size();i++)
    {
      labels.insert(cfg.pfcandidate_InputTag[i].label());//+":"+
      //                    cfg.pfcandidateProducer[i].instance()+":"+
      //                    cfg.pfcandidateProducer[i].process());
    }
    evt->pfcandidates.Reserve(labels);

    // Loop over the different taus collection
    for (unsigned int m=0 ; m<  cfg.pfcandidate_InputTag.size() ; m++) 
    {

      evt->pfcandidates.SelectLabel(cfg.pfcandidate_InputTag[m].label()); //+":"+
      //                              cfg.pfcandidate_InputTag[m].instance()+":"+
      //                              cfg.pfcandidate_InputTag[m].process());

      // Getting pfcandidates
      edm::Handle<reco::PFCandidateCollection> pfcandidateHandle;
      iEvent.getByLabel(cfg.pfcandidate_InputTag[m], pfcandidateHandle);
  
      const reco::PFCandidateCollection* pfCandidatesProduct;
      pfCandidatesProduct = pfcandidateHandle.product();

      // Filling MiniTree if pfcandidates are available
      if (pfcandidateHandle.isValid()) 
        fillPFCandidates(iEvent,iSetup,evt,pfCandidatesProduct,bs);
      else
      { 
        ERROR("Produce") << "PFCandidate collection '" 
                         << cfg.pfcandidate_InputTag[m] << "' is missing." << std::endl;
      }
    }
  }

  // ------------------------
  //  Fill Vertices
  // ------------------------
  if (cfg.doVertices)
  {
    if (cfg.verbose>1) std::cout << "Filling vertices ..." << std::endl;
  
    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.vertexProducer.size();i++)
    {
      labels.insert(cfg.vertexProducer[i].label()); //+":"+
      //                       cfg.vertexProducer[i].instance()+":"+
      //                       cfg.vertexProducer[i].process());
    }
    evt->vertices.Reserve(labels);

    // Loop over the different vertices collection
    for (unsigned int m=0 ; m<cfg.vertexProducer.size(); m++) 
    {
      // 
      evt->vertices.SelectLabel(cfg.vertexProducer[m].label());//+":"+
      //                       cfg.vertexProducer[m].instance()+":"+
      //                       cfg.vertexProducer[m].process());

      // Getting vertices
      edm::Handle< vector<reco::Vertex> > vertices;
      iEvent.getByLabel(cfg.vertexProducer[m], vertices);

      // Filling MiniTree if vertices are available
      if (vertices.isValid()) fillVertices(iEvent,iSetup,evt,vertices.product(),vp);
      else
      { 
        ERROR("Produce") << "Vertex collection '" 
                         << cfg.vertexProducer[m] << "' is missing." << std::endl;
      }
    }
  }

  // ------------------------
  //  Fill Photons
  // ------------------------
  if (cfg.doPhotons)
  {
    if (cfg.verbose>1) std::cout << "Filling photons ..." << std::endl;
      
    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.photonProducer.size();i++)
    {
      labels.insert(cfg.photonProducer[i].label());//+":"+
      //                    cfg.photonProducer[i].instance()+":"+
      //                    cfg.photonProducer[i].process());
    }
    evt->photons.Reserve(labels);

    // Loop over the different photons collection
    for (unsigned int m=0 ; m<cfg.photonProducer.size(); m++) 
    {

      evt->photons.SelectLabel(cfg.photonProducer[m].label());//+":"+
      //                               cfg.photonProducer[m].instance()+":"+
      //                               cfg.photonProducer[m].process());

      // Getting photons
      edm::Handle< std::vector<pat::Photon> > phHa;
      iEvent.getByLabel(cfg.photonProducer[m], phHa);

      // Filling MiniTree if photons are available
      if (phHa.isValid()) fillPhotons(iEvent,iSetup,evt,phHa,patTriggerEvent);
      else
      { 
        ERROR("Produce") << "Photon collection '" 
                         << cfg.photonProducer[m] << "' is missing." << std::endl;
      }
    }
  }

 
  // Get TrackBuilder
  edm::ESHandle<TransientTrackBuilder> trackBuilderHa;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilderHa);

  // Set the pointer if valid
  if (trackBuilderHa.isValid()) trackBuilder=trackBuilderHa.product();
  else
  { 
    ERROR("Produce") << "TransientTrackBuilder is missing." << std::endl;
  }


  // ------------------------
  //  Fill Electrons
  // ------------------------
  if (cfg.doElectrons)
  {
    if (cfg.verbose>1) std::cout << "Filling electrons ..." << std::endl;
      
    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.electronProducer.size();i++)
    {
      labels.insert(cfg.electronProducer[i].label());//+":"+
      //                    cfg.electronProducer[i].instance()+":"+
      //                    cfg.electronProducer[i].process());
    }
    evt->electrons.Reserve(labels);

    // Loop over the different electrons collection
    for (unsigned int m=0 ; m<cfg.electronProducer.size(); m++) 
    {

      evt->electrons.SelectLabel(cfg.electronProducer[m].label());//+":"+
      //                                 cfg.electronProducer[m].instance()+":"+
      //                                 cfg.electronProducer[m].process());
 
      // Getting bField
      float bField;
      if (cfg.isData) 
      {
        if (!getBfieldFromDCS(iEvent,iSetup,bField))
        {
          if (!getBfieldFromIDEAL(iEvent,iSetup,bField)) bField=0;
        }
      }
      else
      {
        if (!getBfieldFromIDEAL(iEvent,iSetup,bField)) bField=0;
      } 

      // Getting electrons
      edm::Handle< std::vector<pat::Electron> > elHa;
      iEvent.getByLabel(cfg.electronProducer[m], elHa);

      // Getting tracks if not initialized
      if (!cfg.doTracks)
      {
        if (cfg.trackProducer.size()>0) 
              iEvent.getByLabel(cfg.trackProducer[0], trackHandle);
        if (!trackHandle.isValid())
        {
          ERROR("Produce") << "Track collection is missing." << std::endl;
        }
      }

      // Filling MiniTree if electrons are available
      if (elHa.isValid()) fillElectrons(iEvent,iSetup,evt,elHa,trackBuilder,genParticles,bs,vp,bField,trackHandle,patTriggerEvent);
      else
      { 
        ERROR("Produce") << "Electron collection '" 
                         << cfg.electronProducer[m] << "' is missing." << std::endl;
      }
    }
  }
 

  // ------------------------
  //  Fill Muons
  // ------------------------
  if (cfg.doMuons)
  {
    if (cfg.verbose>1) std::cout << "Filling muons ..." << std::endl;

    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.muonProducer.size();i++)
    {
      labels.insert(cfg.muonProducer[i].label());//+":"+
      //                    cfg.muonProducer[i].instance()+":"+
      //                    cfg.muonProducer[i].process());
    }
    evt->muons.Reserve(labels);
      
    // Loop over the different muons collection
    for (unsigned int m=0 ; m<cfg.muonProducer.size(); m++) 
    {

      evt->muons.SelectLabel(cfg.muonProducer[m].label());//+":"+
      //                             cfg.muonProducer[m].instance()+":"+
      //                             cfg.muonProducer[m].process());

      // Getting muons 
      edm::Handle< std::vector<pat::Muon> > muHa;
      iEvent.getByLabel(cfg.muonProducer[m], muHa);

      // Filling MiniTree if muons are available
      if (muHa.isValid()) fillMuons(iEvent, iSetup, evt, muHa, trackBuilder, genParticles, bs, vp, patTriggerEvent);
      else
      { 
        ERROR("Produce") << "Muon collection '" 
                         << cfg.muonProducer[m] << "' is missing." << std::endl;
      }
    }
  }

  // ------------------------
  //  Fill Taus
  // ------------------------
  if (cfg.doTaus)
  {
    if (cfg.verbose>1) std::cout << "Filling taus ..." << std::endl;

    std::set<std::string> labels;
    for (unsigned int i=0;i<cfg.tauProducer.size();i++)
    {
      labels.insert(cfg.tauProducer[i].label());//+":"+
      //                    cfg.tauProducer[i].instance()+":"+
      //                    cfg.tauProducer[i].process());
    }
    evt->taus.Reserve(labels);
      
    // Loop over the different taus collection
    for (unsigned int m=0;m<cfg.tauProducer.size();m++) 
    {

      labels.insert(cfg.tauProducer[m].label());//+":"+
      //                    cfg.tauProducer[m].instance()+":"+
      //                    cfg.tauProducer[m].process());

      // Getting taus 
      edm::Handle< std::vector<pat::Tau> > tauHandle;
      iEvent.getByLabel(cfg.tauProducer[m], tauHandle);

      // Filling MiniTree if taus are available
      if (tauHandle.isValid()) fillTaus(iEvent,iSetup,evt,tauHandle,genParticles,bs,patTriggerEvent);
      else
      { 
        ERROR("Produce") << "Tau collection '" 
                         << cfg.tauProducer[m] << "' is missing." << std::endl;
      }
    }
  }


  // ------------------------
  //  Fill JetMET
  // ------------------------
  if (cfg.doJetMet)
  {
    std::pair<float,float> SumMuMetCorr(0,0);
 
    if (cfg.doMuonCorrection)
    {
      if (cfg.verbose>1) std::cout << "Filling muon correction for MET ..."  << std::endl;

      edm::Handle<edm::ValueMap<reco::MuonMETCorrectionData> > muMEThandle;
      iEvent.getByLabel("muonTCMETValueMapProducer", "muCorrData", muMEThandle);

      if (!muMEThandle.isValid())
      {
        ERROR("Produce") << "MuonMETCorrectionData collection "
                         << "is missing." << std::endl;
      }

      edm::Handle<std::vector<reco::Muon> > recoMuonHandle;
      iEvent.getByLabel("muons", recoMuonHandle);

      if (!recoMuonHandle.isValid())
      {
        ERROR("Produce") << "reco::Muon collection "
                         << "is missing." << std::endl;
      }

      if (recoMuonHandle.isValid() && muMEThandle.isValid())
      {
        SumMuMetCorr = 
          fillMuonMET(muMEThandle,recoMuonHandle);
      }
    }

    if (cfg.verbose>1) std::cout << "Filling jet MET ..."  << std::endl;

    std::set<std::string> labels;
    for (VParameters::iterator ijetmet = cfg.jetmetProducer.begin();
         ijetmet != cfg.jetmetProducer.end(); ijetmet++)
    {
      labels.insert(ijetmet->getUntrackedParameter<std::string>("algo"));
    }
    evt->jets.Reserve(labels);
    evt->met.Reserve(labels);

    // Loop over the different jet/met collection 
    for (VParameters::iterator ijetmet = cfg.jetmetProducer.begin();
         ijetmet != cfg.jetmetProducer.end(); ijetmet++)
    {
      std::string jet_    = ijetmet->getUntrackedParameter<std::string>("jet");
      std::string met_    = ijetmet->getUntrackedParameter<std::string>("met",   std::string());
      std::string pfmet1_ = ijetmet->getUntrackedParameter<std::string>("pfmet1",std::string());
      std::string pfmet2_ = ijetmet->getUntrackedParameter<std::string>("pfmet2",std::string());
      std::string algo_   = ijetmet->getUntrackedParameter<std::string>("algo");
      bool fillJetConstituents_    = ijetmet->getUntrackedParameter<bool>("fillJetConstituents");
      bool fillSubJetConstituents_ = ijetmet->getUntrackedParameter<bool>("fillSubJetConstituents");

      evt->jets.SelectLabel(algo_);
      evt->met.SelectLabel(algo_);

      // Getting MET
      const pat::MET    *met = 0;
      const reco::PFMET *pfmet1 = 0;
      const reco::PFMET *pfmet2 = 0;

      edm::Handle< std::vector<pat::MET> > metHandle;
      edm::Handle< std::vector<reco::PFMET> > pfmetHandle1;
      edm::Handle< std::vector<reco::PFMET> > pfmetHandle2;

   if( met_.size() ){
      iEvent.getByLabel(met_, metHandle);

      if (!metHandle.isValid())
      {
         ERROR("Produce") << "MET collection '"
                          << met_ << "' is missing." << std::endl;
         continue;
      } else

      // Check MET is not empty
      if (metHandle->size()==0) 
      {
        ERROR("JetMET") << "edm::View<pat::MET> is empty" << std::endl;
        continue;
      }

      met = &(metHandle->front());
   }

   if( pfmet1_.size() ){

      iEvent.getByLabel(pfmet1_, pfmetHandle1);

      if (!pfmetHandle1.isValid())
      {
         ERROR("Produce") << "PFMET collection '"
                          << pfmet1_ << "' is missing." << std::endl;
         continue;
      } else

      // Check MET is not empty
      if (pfmetHandle1->size()==0) 
      {
        ERROR("JetMET") << "edm::View<reco::PFMET> ("<<pfmet1_<<") is empty" << std::endl;
        continue;
      }

      pfmet1 = &(pfmetHandle1->front());
   }

   if( pfmet2_.size() ){
      iEvent.getByLabel(pfmet2_, pfmetHandle2);

      if (!pfmetHandle2.isValid())
      {
         ERROR("Produce") << "PFMET collection '"
                          << pfmet2_ << "' is missing." << std::endl;
         continue;
      } else

      // Check MET is not empty
      if (pfmetHandle2->size()==0) 
      {
        ERROR("JetMET") << "edm::View<reco::PFMET> ("<<pfmet2_<<") is empty" << std::endl;
        continue;
      }

      pfmet2 = &(pfmetHandle2->front());
   }


      // Getting Jet
      edm::Handle<std::vector<pat::Jet> > jetHandle;
      iEvent.getByLabel(jet_, jetHandle);

      // Filling MiniTree if MET is available
      if (jetHandle.isValid())
      {
        fillJetMET(iEvent, iSetup, evt,
                   met, pfmet1, pfmet2, jetHandle, algo_, 
                   fillJetConstituents_, fillSubJetConstituents_, 
                   SumMuMetCorr, patTriggerEvent);
      }
      else
      { 
         ERROR("Produce") << "JET collection '"
                          << jet_ << "' is missing." << std::endl;
      }
    }
  }
    
  // Save the event 
  if (cfg.verbose>1) std::cout << "Optimize space occupied by the event ..." << std::endl;
  IPHCTree::MTTransient::InitializeBeforeWriting(evt.get());
  if (cfg.verbose>1) std::cout << "Save the event in the root file ..." << std::endl; 
  iEvent.put(evt);
  if (cfg.verbose>0) std::cout << "-> The event is successfully saved in the MiniTree" << std::endl;
}



// ----------------------------------------------------------------------------
//        ___                         _       _           ___      
//       (  _`\                      ( )_    (_)        /'___)     
//       | (_(_) _   _    __    ___  | ,_)   | |  ___  | (__   _   
//       |  _)_ ( ) ( ) /'__`\/' _ `\| |     | |/' _ `\| ,__)/'_`\ 
//       | (_( )| \_/ |(  ___/| ( ) || |_    | || ( ) || |  ( (_) )
//       (____/'`\___/'`\____)(_) (_)`\__)   (_)(_) (_)(_)  `\___/'
//       
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillGeneralInfo(edm::Event& iEvent, 
                                       const edm::EventSetup& iSetup,
                                       std::auto_ptr<IPHCTree::MTEvent>& evt)
{
  evt->general.runNb       = iEvent.id().run();
  evt->general.eventNb     = iEvent.id().event();
  evt->general.lumiblock   = iEvent.id().luminosityBlock();
}


// ----------------------------------------------------------------------------
//                _____                                   
//               (_   _)     _                            
//                 | | _ __ (_)   __     __     __   _ __ 
//                 | |( '__)| | /'_ `\ /'_ `\ /'__`\( '__)
//                 | || |   | |( (_) |( (_) |(  ___/| |   
//                 (_)(_)   (_)`\__  |`\__  |`\____)(_)   
//                             ( )_) |( )_) |             
//                              \___/' \___/'   
//
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillTriggerInfo(edm::Event& iEvent, 
                                       const edm::EventSetup& iSetup,
                                       std::auto_ptr<IPHCTree::MTEvent>& evt,
                                       const pat::TriggerEvent* triggerEvent)
{
  // Saving the name of the trigger tables
  evt->trigger.FillTableName(triggerEvent->nameL1Menu(), 
                             triggerEvent->nameHltTable()); 

  // Declaring a new container for trigger bits and prescales
  std::map<std::string, std::pair<UInt_t,Bool_t> > output;

  // Getting trigger bits and prescales for the whole table
  if (cfg.saveAllTriggers) 
  {
    const std::vector<pat::TriggerPath>* paths = triggerEvent->paths(); 
    for (unsigned int i=0; i<paths->size(); i++)
    {
      if ((*paths)[i].name()=="") continue;
      output[(*paths)[i].name()] = std::make_pair( (*paths)[i].prescale(),
                                                   (*paths)[i].wasAccept() );
    }
  }

  // Getting trigger bits and prescales for a given path selection  
  else
  {

    for (unsigned int j=0; j<cfg.triggerList.size(); j++)
    {
      const pat::TriggerPath* path = triggerEvent->path(cfg.triggerList[j]);
      if (path==0)
      {
        ERROR("Produce") << "trigger bit called '" << cfg.triggerList[j]
                         << "' is not found" << std::endl;
      }
      else
      {
        output[path->name()] = std::make_pair( path->prescale(),
                                               path->wasAccept() );
      }
    }
  }

  // Save trigger bits and prescales
  evt->trigger.FillTrigger(output); 

  float match_pTHLTElectron15 = -1.;

  // get all trigger objects corresponding to this module.
  // loop through them and see how many objects match the selection
  pat::TriggerObjectRefVector theObjects = triggerEvent -> 
             filterObjects("hltL1NonIsoHLTNonIsoSingleElectronEt10PixelMatchFilter");
  for (pat::TriggerObjectRefVectorIterator iObject = theObjects.begin();
       iObject != theObjects.end(); ++iObject )
  {
    if ((*iObject)->pt() >= 15) match_pTHLTElectron15 = (*iObject)->pt();
  }
}


// ----------------------------------------------------------------------------
//             _   _               _                          
//            ( ) ( )             ( )_  _                     
//            | | | |   __   _ __ | ,_)(_)   ___    __    ___ 
//            | | | | /'__`\( '__)| |  | | /'___) /'__`\/',__)
//            | \_/ |(  ___/| |   | |_ | |( (___ (  ___/\__, \
//            `\___/'`\____)(_)   `\__)(_)`\____)`\____)(____/
//                                                    
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillVertices(edm::Event& iEvent, 
                                    const edm::EventSetup& iSetup,
                                    std::auto_ptr<IPHCTree::MTEvent>& evt,
                                    const std::vector<reco::Vertex>* vertices,
                                    const reco::Vertex*& vp)
{
  // Loop over Vertices
  for (std::vector<reco::Vertex>::const_iterator 
       itv = vertices->begin(); itv!=vertices->end(); itv++)
  {
    // Get the primary vertex used in the following 
    // the first of the collection !
    if (itv == vertices->begin()) vp = &(*itv);

    // Get a new vertex
    IPHCTree::MTVertex* pvx = evt->NewVertex();

    // Fill position and its error 
    pvx->p3.SetXYZ(itv->x(), itv->y(), itv->z());
    pvx->p3Err.SetXYZ (itv->xError (), itv->yError (), itv->zError ());

    // Fill the vertex
    pvx->chi2           = itv->chi2();
    pvx->isFake         = itv->isFake();
    pvx->isValid        = itv->isValid();
    pvx->ndof           = itv->ndof();
    pvx->NumberOfTracks = itv->tracksSize();

    // Keep only the first vertex ?
    if (!cfg.saveAllVertex) break;
  }
}


// ----------------------------------------------------------------------------
//                     _____                   _           
//                    (_   _)                 ( )          
//                      | | _ __   _ _    ___ | |/')   ___ 
//                      | |( '__)/'_` ) /'___)| , <  /',__)
//                      | || |  ( (_| |( (___ | |\`\ \__,
//                      (_)(_)  `\__,_)`\____)(_) (_)(____/
//                                     
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillTracks(edm::Event& iEvent, 
                                  const edm::EventSetup& iSetup,
                                  std::auto_ptr<IPHCTree::MTEvent>& evt,
                                  const std::vector<reco::Track>* tracks,
                                  const reco::BeamSpot* & bs)
{
  
  if (tracks == 0) return;

  //Loop over tracks
  for (std::vector<reco::Track>::const_iterator
         it=tracks->begin(); it!=tracks->end(); it++)
  {
    const reco::Track* track = &*it;

    // Applying a preselection based on on pT, eta 
    if ( track->pt () < cfg.track_cut_pt || 
         fabs (track->eta ()) > cfg.track_cut_eta ) continue;

    IPHCTree::NTTrack* myTrack = evt->NewTrack ();

    // Set 4-vector momentum
    myTrack->p4.SetPxPyPzE( track->px(),
                            track->py(),
                            track->pz(),
                            track->p()  );
    // Components 
    myTrack->chi2        = track->chi2()/track->ndof();
    myTrack->nHitTracker = track->hitPattern().numberOfValidHits();
    myTrack->dz          = track->dz();
    myTrack->dzError     = track->dzError();
    myTrack->dxy         = track->dxy();
    myTrack->dxyError    = track->dxyError();

    // Charge
    myTrack->charge = track->charge();
  
    // dxy wrt BeamSpot (if BeamSpot is available)
      if (cfg.doBeamSpot && bs!=0)  myTrack->dxy_BS = track->dxy(bs->position());
  }
}


// ----------------------------------------------------------------------------
//
//                    PFCandidates
//                                     
// ----------------------------------------------------------------------------


void MiniTreeProducer::fillPFCandidates(edm::Event& iEvent, 
                  const edm::EventSetup& iSetup,
                  std::auto_ptr<IPHCTree::MTEvent>& evt,
                  const reco::PFCandidateCollection* pfCandidates,
                  const reco::BeamSpot* & bs)
{


  // Adapted from 
  // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/benhoob/TrackIsolationMaker/TrackIsolationMaker.cc?view=markup

  //---------------------------------
  // get Vertex Collection
  //---------------------------------
   
  edm::Handle<reco::VertexCollection> vertex_h;
  iEvent.getByLabel(cfg.pfcandidate_VertexTag[0], vertex_h);
  const reco::VertexCollection *vertices = vertex_h.product();
  
  //-----------------------------------
  // Find 1st good vertex
  //-----------------------------------
    
  reco::VertexCollection::const_iterator firstGoodVertex = vertices->end();
    
  int firstGoodVertexIdx = 0;
    
  for (reco::VertexCollection::const_iterator vtx = vertices->begin(); vtx != vertices->end(); ++vtx, ++firstGoodVertexIdx) 
  {
    if (!vtx->isFake() && vtx->ndof()>=4. && vtx->position().Rho()<=2.0 && fabs(vtx->position().Z())<=24.0) 
    {
      firstGoodVertex = vtx;
      break;
    }
  }
  
  //-------------------------------------------------------------------------------------------------
  // loop over PFCandidates and calculate the trackIsolation and dz w.r.t. 1st good PV for each one
  //-------------------------------------------------------------------------------------------------
  
  for( reco::PFCandidateCollection::const_iterator pf_it = pfCandidates->begin(); pf_it != pfCandidates->end(); pf_it++ ) 
  {

    //-------------------------------------------------------------------------------------
    // only store PFCandidate values if pt > minPt
    // also skip if we can't get the track
    //-------------------------------------------------------------------------------------
    
    // Get gsf track (nonNull in case of electrons)
    reco::GsfTrackRef pf_it_gsftrackref = pf_it->gsfTrackRef();
    float pf_it_gsfpt = -9999.0;
    if ( pf_it_gsftrackref.isNonnull() )
      pf_it_gsfpt  = pf_it_gsftrackref.get()->pt();
    
    if (( pf_it->pt() < cfg.pfcandidate_cut_minPt  ) 
     && ( pf_it_gsfpt < cfg.pfcandidate_cut_minPt )) continue;

    if ( !pf_it->trackRef().isNonnull() )   continue; 
    const reco::Track* track = (pf_it->trackRef()).get();
    //-------------------------------------------------------------------------------------
    // if there's no good vertex in the event, we can't calculate anything so store 999999
    //-------------------------------------------------------------------------------------
                                  
    if ( firstGoodVertex==vertices->end() ) continue;
    if( pf_it->charge() == 0 ) continue;

    // Else : create the PFCandidate
    IPHCTree::NTPFCandidate* myPFCandidate = evt->NewPFCandidate();
    
    //-------------------------------------------------------------------------------------
    // Fill track of PFCandidate info
    //-------------------------------------------------------------------------------------

      // Set 4-vector momentum
    myPFCandidate->p4.SetPxPyPzE( pf_it->px(),
                                  pf_it->py(),
                                  pf_it->pz(),
                                  pf_it->p()    );
    // Components 
    myPFCandidate->chi2        = track->chi2()/track->ndof();
    myPFCandidate->nHitTracker = track->hitPattern().numberOfValidHits();
    myPFCandidate->dz          = track->dz();
    myPFCandidate->dzError     = track->dzError();
    myPFCandidate->dxy         = track->dxy();
    myPFCandidate->dxyError    = track->dxyError();

    // Charge
    myPFCandidate->charge = track->charge();
  
    // dxy wrt BeamSpot (if BeamSpot is available)
      if (cfg.doBeamSpot && bs!=0)  myPFCandidate->dxy_BS = track->dxy(bs->position());
    
    //----------------------------------------------------------------------------
    // now loop over other PFCandidates in the event to calculate trackIsolation
    //----------------------------------------------------------------------------
    
    float trkiso = 0.0;

    for( reco::PFCandidateCollection::const_iterator pf_other = pfCandidates->begin(); pf_other != pfCandidates->end(); pf_other++ )
    {
    
      // don't count the PFCandidate in its own isolation sum
      if( pf_it == pf_other       ) continue;

      // cut on dR between the PFCandidates
      float dR = deltaR(pf_it->eta(), pf_it->phi(), pf_other->eta(), pf_other->phi());

      // cut on the PFCandidate dz
      float dz_other = 100;
      if ( pf_other->trackRef().isNonnull()) 
      {
        dz_other = pf_other->trackRef()->dz( firstGoodVertex->position() );
      }
      if( fabs(dz_other) > cfg.pfcandidate_cut_dz ) continue;
  
      // require the PFCandidate to be charged
      if( pf_other->charge() == 0 ) continue;
    
      if ( dR < cfg.pfcandidate_cut_dR )  { trkiso += pf_other->pt(); }
    }
     
    // calculate the dz of this candidate
    float dz_it = 100; 
    if ( pf_it->trackRef().isNonnull())
    {
      dz_it = pf_it->trackRef()->dz( firstGoodVertex->position() );
    }
    
    float dz_it_gsf = 100; 
    if ( pf_it_gsftrackref.isNonnull())
    {
      dz_it_gsf = pf_it_gsftrackref.get()->dz( firstGoodVertex->position() );
    }
  
    // Store dz and isolation
    myPFCandidate->dz_firstGoodVertex = dz_it;
    myPFCandidate->trackIso = trkiso;
  
    // Other data
    std::map<std::string,Float_t> others;

    others["charge_fromPF"] = pf_it->charge();
    int pf_it_pdgid = pf_it->pdgId();
    others["id"]           = pf_it_pdgid;

         if ((pf_it_pdgid == 211) || (pf_it_pdgid == -11) || (pf_it_pdgid == -13))
        others["charge_fromID"] =  1;
    else if ((pf_it_pdgid == -211) || (pf_it_pdgid == 11) || (pf_it_pdgid == 13))
        others["charge_fromID"] = -1;
    else    
        others["charge_fromID"] =  0;
    
    others["gsfPt"] = pf_it_gsfpt;
    others["gsfdz"] = dz_it_gsf;
    
    // Saving others
    myPFCandidate->others.Fill(others);
    

  }
}

// ----------------------------------------------------------------------------
//                          _              ___                _          
//    /'\_/`\              ( )_           (  _`\             (_ )        
//    |     |   _     ___  | ,_)   __     | ( (_)   _ _  _ __ | |    _   
//    | (_) | /'_`\ /' _ `\| |   /'__`\   | |  _  /'_` )( '__)| |  /'_`\ 
//    | | | |( (_) )| ( ) || |_ (  ___/   | (_( )( (_| || |   | | ( (_) )
//    (_) (_)`\___/'(_) (_)`\__)`\____)   (____/'`\__,_)(_)  (___)`\___/'
//                                                                   
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillGenEventInfo(edm::Event& iEvent, 
                                        const edm::EventSetup& iSetup,
                                        std::auto_ptr<IPHCTree::MTEvent>& evt,
                                        const edm::Handle<GenEventInfoProduct>& genEventInfo)
{
  //********************************************************
  // Safety
  //********************************************************
  if (genEventInfo->pdf()==0)
  {
    ERROR("fillGenInfo") << "GenEventInfoProduct->pdf()" 
                         << " is not found" <<std::endl;
    return;
  }

  //********************************************************
  // Calculate PDF weight 
  //********************************************************
  evt->mc.partonFlavor.first  = genEventInfo->pdf()->id.first;
  evt->mc.partonFlavor.second = genEventInfo->pdf()->id.second;
  evt->mc.x.first             = genEventInfo->pdf()->x.first;
  evt->mc.x.second            = genEventInfo->pdf()->x.second;
  evt->mc.Q_scale             = genEventInfo->pdf()->scalePDF;

  evt->mc.xpdf.first          = genEventInfo->pdf()->xPDF.first;
  evt->mc.xpdf.second         = genEventInfo->pdf()->xPDF.second;

  //********************************************************
  // Extract ptHat
  //********************************************************
  if (genEventInfo->binningValues().size() > 0 )
     evt->mc.ptHat = genEventInfo->binningValues()[0];
}
              

// ----------------------------------------------------------------------------
//                ___       _                   _   _        
//               (  _`\  _ (_ )                ( ) ( )       
//               | |_) )(_) | |    __   ______ | | | | _ _   
//               | ,__/'| | | |  /'__`\(______)| | | |( '_`\ 
//               | |    | | | | (  ___/        | (_) || (_) )
//               (_)    (_)(___)`\____)        (_____)| ,__/'
//                                                    | |    
//                                                    (_)    
//                                                                   
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillPileUp(edm::Event& iEvent, 
                                  const edm::EventSetup& iSetup,
                                  std::auto_ptr<IPHCTree::MTEvent>& evt,
                                  edm::Handle<std::vector<PileupSummaryInfo> >& PupInfo)
{

  // Loop over pile-up
  for(std::vector<PileupSummaryInfo>::const_iterator
      PVI = PupInfo->begin(); PVI != PupInfo->end(); PVI++)
  {
    // Get bunchcrossing number
    signed int n_bc=PVI->getBunchCrossing();

    // Fill pile-up

    if (n_bc==0)       
    {
      evt->pileup.intime_npu = PVI->getPU_NumInteractions();
      evt->pileup.Tnpv = PVI->getTrueNumInteractions();
    }
    else if (n_bc==-1) evt->pileup.before_npu = PVI->getPU_NumInteractions();
    else if (n_bc==+1) evt->pileup.after_npu  = PVI->getPU_NumInteractions();
    
    // Create a new container for interaction data in the MiniTree
    std::vector<IPHCTree::MTInteraction>* pu_info = 
                                              evt->pileup.NewPUbunch(n_bc);

    // Loop over interaction
    for (unsigned int ipu=0; ipu<PVI->getPU_zpositions().size(); ipu++)
    {
      // Create a new interaction in the MiniTree
      pu_info->push_back(IPHCTree::MTInteraction());
      IPHCTree::MTInteraction* inter = &pu_info->back();

      // Fill the interaction data
      inter->zpositions   = (PVI->getPU_zpositions())[ipu];
      inter->sumpT_lowpT  = (PVI->getPU_sumpT_lowpT())[ipu]; 
      inter->sumpT_highpT = (PVI->getPU_sumpT_highpT())[ipu];
      inter->ntrks_lowpT  = (PVI->getPU_ntrks_lowpT())[ipu];
      inter->ntrks_highpT = (PVI->getPU_ntrks_highpT())[ipu];
    }
  }
}


// ----------------------------------------------------------------------------
//   ___                  ___                _              _                
//  (  _`\               (  _`\             ( )_  _        (_ )              
//  | ( (_)   __    ___  | |_) )  _ _  _ __ | ,_)(_)   ___  | |    __    ___ 
//  | |___  /'__`\/' _ `\| ,__/'/'_` )( '__)| |  | | /'___) | |  /'__`\/',__)
//  | (_, )(  ___/| ( ) || |   ( (_| || |   | |_ | |( (___  | | (  ___/\__, \
//  (____/'`\____)(_) (_)(_)   `\__,_)(_)   `\__)(_)`\____)(___)`\____)(____/
//                                                                           
// ---------------------------------------------------------------------------- 
void MiniTreeProducer::fillGenParticles(edm::Event& iEvent, 
                                        const edm::EventSetup& iSetup,
                                        std::auto_ptr<IPHCTree::MTEvent>& evt,
                                        const edm::Handle<std::vector<reco::GenParticle> >& GenParticles)
{

  // Minimal Check : at least the two initial protons
  if (GenParticles->size()<2)
  {
    if (GenParticles->empty())
      WARNING("fillGenParticles") << "GenParticles container is empty !" << std::endl; 
    else
      WARNING("fillGenParticles") << "GenParticles contains only 2 or less particles !" << std::endl; 
    return;
  }

  // Save taus and heavy quarks to add daughters after this loop
  reco::GenParticleCollection taus;
  reco::GenParticleCollection heavyQuarks;

  reco::GenParticleCollection genParticlesCollection = *GenParticles;
  reco::GenParticleCollection::const_iterator genParticleSrc;
  for (genParticleSrc = genParticlesCollection.begin(); genParticleSrc != genParticlesCollection.end(); genParticleSrc++)
  {

    if (genParticleSrc->status()!=3) continue;

    // Add the genParticle to the event
    IPHCTree::NTGenParticle* mypart = evt->mc.NewGenParticle();

    TLorentzVector p4Mother;
    int idMother = -1;
    if ((genParticleSrc->mother() != 0) && (genParticleSrc->mother()->px() != 0) && (genParticleSrc->mother()->py() != 0))
    {
        p4Mother.SetPxPyPzE(genParticleSrc->mother()->px(),
                            genParticleSrc->mother()->py(),
                            genParticleSrc->mother()->pz(),
                            genParticleSrc->mother()->energy());
        idMother = genParticleSrc->mother()->pdgId();
    }    
    fillOneGenParticle(&(*genParticleSrc),p4Mother,idMother,mypart,evt->mc.genParticles);
    
    // Save decay mode for taus
    if ((cfg.mcTauDecayMode >= 1) && (abs(genParticleSrc->pdgId()) == 15))
    {
        mypart->decayMode = MonteCarloOrigin::getTauDecayFromGenParticle(genParticleSrc);
        taus.push_back(*genParticleSrc);
    }
    // Save decay mode for heavy quarks
    if ((cfg.mcHeavyQuarkDecayMode >= 1) && ((abs(genParticleSrc->pdgId()) == 4) || (abs(genParticleSrc->pdgId()) == 5)))
    {
        mypart->decayMode = MonteCarloOrigin::getHeavyQuarkDecayFromGenParticle(genParticleSrc);
        heavyQuarks.push_back(*genParticleSrc);
    }

  }

  // Add tau daughters at the end of MiniTree's genParticle collection
  if (cfg.mcTauDecayMode >= 2)
  for (genParticleSrc = taus.begin(); genParticleSrc != taus.end(); genParticleSrc++)
  {
    // Get tau index, used to fill motherIndex_ later
    TLorentzVector p4Tau(genParticleSrc->px(),
                         genParticleSrc->py(),
                         genParticleSrc->pz(),
                         genParticleSrc->energy());
    int idTau = genParticleSrc->pdgId();
      
    // Get the vector containing the decay products
    std::vector<const reco::Candidate*> decayProducts;
    MonteCarloOrigin::getTauDecayProducts(&(*genParticleSrc),&decayProducts);
    
    // Loop on tau decay products
    int nDecayProducts = decayProducts.size();
    for (int i = 0 ; i < nDecayProducts ; i++)
    {
       // Save the current product
       IPHCTree::NTGenParticle* mypart = evt->mc.NewGenParticle();
       fillOneGenParticle(dynamic_cast<const reco::GenParticle*>(decayProducts[i]),p4Tau,idTau,mypart,evt->mc.genParticles);
       //mypart->motherIndex_ = tauIndex;
    }
  }
  
  // Add quarks decay products at the end of MiniTree's genParticle collection
  if (cfg.mcHeavyQuarkDecayMode >= 2)
  for (genParticleSrc = heavyQuarks.begin(); genParticleSrc != heavyQuarks.end(); genParticleSrc++)
  {

      TLorentzVector p4Quark(genParticleSrc->px(),
                             genParticleSrc->py(),
                             genParticleSrc->pz(),
                             genParticleSrc->energy());
      int idQuark = genParticleSrc->pdgId();

      // Get the vector containing the decay products
      std::vector<const reco::Candidate*> decayProducts;
      MonteCarloOrigin::getHeavyQuarkDecayProducts(&(*genParticleSrc),&decayProducts);
     
      // Loop on quark decay products
      int nDecayProducts = decayProducts.size();
      for (int i = 0 ; i < nDecayProducts ; i++)
      {
         // Save the current product
         IPHCTree::NTGenParticle* mypart = evt->mc.NewGenParticle();
         // Force mother to be the quark
         fillOneGenParticle(dynamic_cast<const reco::GenParticle*>(decayProducts[i]),p4Quark,idQuark,mypart,evt->mc.genParticles);
      }
  }


  // New Format
  /*
  // Look for the two initial protons
  std::vector<const reco::Candidate*> mothers;
  std::vector<const reco::Candidate*> all;
  for (unsigned int i=0;i<2; i++)
  {
    if ( (*GenParticles)[i].status()==3 && 
         (*GenParticles)[i].pdgId()==2212) mothers.push_back(&(*GenParticles)[i]);
  }
  if (mothers.size()!=2)
  {
    WARNING("fillGenParticles") << "The two initial protons are not"
                                << " found in the GenParticles container"
                                << std::endl; 
    return;
  }

  // Fill the MiniTree with the two initial protons
  for (unsigned int i=0;i<mothers.size();i++)
  {
    IPHCTree::NTGenParticle* mypart = evt->mc.NewGenParticle();
    mypart->p4.SetPxPyPzE(mothers[i]->px(),
                          mothers[i]->py(),
                          mothers[i]->pz(),
                          mothers[i]->energy());
    mypart->isStatus3 = (mothers[i]->status()==3);
    mypart->id        = mothers[i]->pdgId();
    all.push_back(mothers[i]);
  }

  // Fill other particles
  unsigned int nIter=0;
  std::vector<const reco::Candidate*> daughters;
  while (nIter < cfg.mcDescentMax)
  {

    // Get daughters for all mothers
    for (unsigned int i=0;i<mothers.size();i++)
    {
      for (unsigned int j=0;j<mothers[i]->numberOfDaughters();j++)
      {
        // Save the pointer to the daughter only if it is non null 
        if (mothers[i]->daughter(j)!=0) 
            daughters.push_back(mothers[i]->daughter(j));
      }
    }

    // End of the loop ?
    // 2 possible cases to break the loop :
    //  - no daughters found (no more particles)
    //  - mcNGenPartMax is reached
    if ( daughters.size()==0 || 
         evt->mc.genParticles.size()+daughters.size() > cfg.mcNGenPartMax) break;

    // Fill the MiniTree
    for (unsigned int i=0;i<daughters.size();i++)
    {
      IPHCTree::NTGenParticle* mypart = evt->mc.NewGenParticle();
      mypart->p4.SetPxPyPzE(daughters[i]->px(),
                            daughters[i]->py(),
                            daughters[i]->pz(),
                            daughters[i]->energy());
      mypart->isStatus3 = (daughters[i]->status()==3);
      mypart->id        = daughters[i]->pdgId();
      all.push_back(daughters[i]);
    }
   
    // Prepare for a new loop : 
    //  1. daughters become mothers
    //  2. daughters container is cleaned
    mothers = daughters;
    daughters.clear();

    // Increment the iteration counter
    nIter++;
  }

  // Fill mother links
  for (unsigned int i=0;i<all.size();i++)
  {
    evt->mc.genParticles[i].motherIndex_=-1;
    for (unsigned int j=0;j<i;j++)
    {
      if (all[i]->mother() == all[j])
        evt->mc.genParticles[i].motherIndex_=j;
    }
  }
*/

  // Fill taus
  for (unsigned int i=0;i<GenParticles->size(); i++)
  {
    if ( (*GenParticles)[i].pdgId () == 15 )
    {  
      TLorentzVector p4( (*GenParticles)[i].px(),
                         (*GenParticles)[i].py(),
                         (*GenParticles)[i].pz(),
                         (*GenParticles)[i].energy() );
      evt->mc.Generatedtaus.push_back(p4);
    }
   
    if ( (*GenParticles)[i].pdgId () == -15 )
    {  
      TLorentzVector p4( (*GenParticles)[i].px(),
                         (*GenParticles)[i].py(),
                         (*GenParticles)[i].pz(),
                         (*GenParticles)[i].energy() );
      evt->mc.GeneratedAtaus.push_back(p4);
    }
  }

  // OLD Gen info
  MonteCarloOrigin::fillGenInfo(evt,GenParticles);
}

void MiniTreeProducer::fillOneGenParticle(const reco::GenParticle* src,
                                          TLorentzVector p4Mother,  
                                          int idMother,  
                                          IPHCTree::NTGenParticle* dest, 
                                          std::vector<IPHCTree::NTGenParticle> collection)
{
    dest->p4.SetPxPyPzE(src->px(),
                        src->py(),
                        src->pz(),
                        src->energy());
    dest->isStatus3 = (src->status()==3);
    dest->id        = src->pdgId();
    dest->motherIndex_ = -1;
    if (idMother == -1) return;

    for (unsigned int i = 0 ; i < collection.size() ; i++)
    {
      if (collection[i].id != idMother) continue;
      if (p4Mother.DeltaR(collection[i].p4) < 0.001)
      {
        dest->motherIndex_=i;
        break;
      }
    }

}

              
// ----------------------------------------------------------------------------
//                ___    _             _                       
//               (  _`\ ( )           ( )_                     
//               | |_) )| |__     _   | ,_)   _     ___    ___ 
//               | ,__/'|  _ `\ /'_`\ | |   /'_`\ /' _ `\/',__)
//               | |    | | | |( (_) )| |_ ( (_) )| ( ) |\__, \
//               (_)    (_) (_)`\___/'`\__)`\___/'(_) (_)(____/
//
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillPhotons(edm::Event& iEvent, 
                                   const edm::EventSetup& iSetup,
                                   std::auto_ptr<IPHCTree::MTEvent>& evt,
                                   const edm::Handle<std::vector<pat::Photon> >& gammas,
                                   const pat::TriggerEvent* patTriggerEvent)
{
  // Loop over photons
  for (std::vector <pat::Photon>::const_iterator
       it = gammas->begin (); it != gammas->end (); it++)
  {
    // Getting pointer to the current photon
    const pat::Photon* thephoton = &*it;

    // Applying preselection based on pT, eta, ID
    if ( thephoton->p4().pt () < cfg.photon_cut_pt  || 
         fabs(thephoton->p4().eta()) > cfg.photon_cut_eta ) continue;

    // Create a new photon [no delete to do !]
    IPHCTree::MTPhoton *myphoton = evt->NewPhoton();

    // Set 4-vector momentum
    myphoton->p4.SetPxPyPzE( thephoton->p4().px(),
                             thephoton->p4().py(),
                             thephoton->p4().pz(),
                             thephoton->p4().energy() );
   
    // Set isolation properties
    myphoton->ECaloIso = thephoton->ecalIso();
    myphoton->HCaloIso = thephoton->hcalIso();
    myphoton->TrkIso   = thephoton->trackIso();

    // Calorimeter type
    myphoton->isEB = thephoton->isEB();
      
    // Shower shape variables
    myphoton->e1x5 = thephoton->e1x5();
    myphoton->e2x5 = thephoton->e2x5();
    myphoton->e3x3 = thephoton->e3x3();
    myphoton->e5x5 = thephoton->e5x5();

    // Other data
    std::map<std::string,Float_t> others;

    // Fill data
    // Example : others["myvariables"]=1.0;

    // Saving others
    myphoton->others.Fill(others);

    // --------------------- HLT-object matching -----------------------
    if (cfg.doTrigger)
    {
      std::map<std::string,TLorentzVector> matched;

      const pat::helper::TriggerMatchHelper matchHelper;

      for (unsigned int i=0;i<cfg.photonHLTmatching.size();i++)
      {
        if (cfg.photonHLTmatching[i]=="") continue;
        const pat::TriggerObjectRef trigRef ( 
               matchHelper.triggerMatchObject(gammas, std::distance(gammas->begin(),it), cfg.photonHLTmatching[i], iEvent, *patTriggerEvent ) );
        if ( trigRef.isAvailable() )
        {
          TLorentzVector q;
          q.SetPxPyPzE(trigRef->px(), trigRef->py(), trigRef->pz(), trigRef->energy());
        }
      }

      myphoton->p4HLT.Fill(matched);
    }

  }
}
        

// ----------------------------------------------------------------------------
//          ___    _                  _                            
//         (  _`\ (_ )               ( )_                          
//          | (_(_) | |    __     ___ | ,_) _ __   _     ___    ___ 
//          |  _)_  | |  /'__`\ /'___)| |  ( '__)/'_`\ /' _ `\/',__)
//          | (_( ) | | (  ___/( (___ | |_ | |  ( (_) )| ( ) |\__, \
//         (____/'(___)`\____)`\____)`\__)(_)  `\___/'(_) (_)(____/
//                                                         
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillElectrons(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const edm::Handle< std::vector<pat::Electron> >& electrons,
                 const TransientTrackBuilder* trackBuilder,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const reco::Vertex* & vp,
                 const float& bField,
                 const edm::Handle<std::vector<reco::Track> >& tracks,
                 const pat::TriggerEvent* patTriggerEvent)
{
  // Loop over electrons
  for (vector < pat::Electron >::const_iterator
      it = electrons->begin (); it != electrons->end (); it++) 
  {
    const pat::Electron * patelec = &*it;

    // --------------------- Preselection -----------------------

    // Applying preselection based on pT, eta, ID
    if ( patelec->pt() < cfg.electron_cut_pt || 
      fabs(patelec->eta()) > cfg.electron_cut_eta) continue;

    // --------------------- General info -----------------------

    // Create a new electron [no delete to do!]
    IPHCTree::MTElectron *myelec = evt->NewElectron();

    // Set 4-vector momentum
    myelec->p4.SetPxPyPzE( patelec->px(),
                           patelec->py(),
                           patelec->pz(),
                           patelec->energy() );

    // Set electron vertex
    myelec->vertex.SetXYZ( patelec->vx(),
                           patelec->vy(),
                           patelec->vz() );

    // Set charge
    myelec->charge = patelec->charge();

    // Electron DB
    myelec->DB = patelec->dB();

    // is GSF electron ?
    myelec->isGsfElectron = patelec->gsfTrack().isNonnull();

    // ------------------ Isolation info -----------------------

  // Init map
  std::map<std::string,Float_t> isoInfos;

  // Fill map
  
    // ######################################################
    // > Feel free to add your own isolation tags if needed !
    // ######################################################

  for (unsigned int i = 0 ; i < cfg.electron_Isolist.size() ; i++)
  {
    string isoFlag = cfg.electron_Isolist[i];
    
    // Individual isos
    
         if (isoFlag == "Trk03")    isoInfos["Trk03"]    = patelec->dr03TkSumPt();
    else if (isoFlag == "ECalo03")  isoInfos["ECalo03"]  = patelec->dr03EcalRecHitSumEt();
    else if (isoFlag == "HCalo03")  isoInfos["HCalo03"]  = patelec->dr03HcalTowerSumEt();

    else if (isoFlag == "Trk04")    isoInfos["Trk04"]    = patelec->trackIso();
    else if (isoFlag == "ECalo04")  isoInfos["ECalo04"]  = patelec->ecalIso();
    else if (isoFlag == "HCalo04")  isoInfos["HCalo04"]  = patelec->hcalIso();

    else if (isoFlag == "PATNeutH") isoInfos["PATNeutH"] = patelec->neutralHadronIso();
    else if (isoFlag == "PATCharH") isoInfos["PATCharH"] = patelec->chargedHadronIso();
    else if (isoFlag == "PATPhoto") isoInfos["PATPhoto"] = patelec->photonIso();
    else if (isoFlag == "PATTrack") isoInfos["PATTrack"] = patelec->trackIso();

    // Group of isos (to avoid having to put a long list of tags in the cfg.py)

    else if (isoFlag == "TrkAndCalo03")
    {
        isoInfos["Trk03"]    = patelec->dr03TkSumPt();
        isoInfos["ECalo03"]  = patelec->dr03EcalRecHitSumEt();
        isoInfos["HCalo03"]  = patelec->dr03HcalTowerSumEt();
    }
    else if (isoFlag == "TrkAndCalo04")
    {
      isoInfos["Trk04"]    = patelec->trackIso();
      isoInfos["ECalo04"]  = patelec->ecalIso();
      isoInfos["HCalo04"]  = patelec->hcalIso();
    }
    else if (isoFlag == "PAT")
    {
      isoInfos["PATNeutH"] = patelec->neutralHadronIso();
      isoInfos["PATCharH"] = patelec->chargedHadronIso();
      isoInfos["PATPhoto"] = patelec->photonIso();
      isoInfos["PATTrack"] = patelec->trackIso();
    }

    // "RA4" iso

    else if ((isoFlag == "RA4") 
          || (isoFlag == "RA4Charg") || (isoFlag == "RA4Photo") || (isoFlag == "RA4Neutr"))
    {
  
      // Charged / photon / neutral iso
      IsoDepositVals electronIsoValPFId(3);
      iEvent.getByLabel("elPFIsoValueCharged03PFIdPFIso", electronIsoValPFId[0]);
      iEvent.getByLabel("elPFIsoValueGamma03PFIdPFIso",   electronIsoValPFId[1]);
      iEvent.getByLabel("elPFIsoValueNeutral03PFIdPFIso", electronIsoValPFId[2]);
      edm::Ptr< reco::GsfElectron > gsfel = (edm::Ptr< reco::GsfElectron >) patelec->originalObjectRef();    

      if ((isoFlag == "RA4") || (isoFlag == "RA4Charg")) isoInfos["RA4Charg"] = (*(electronIsoValPFId[0]))[gsfel];
      if ((isoFlag == "RA4") || (isoFlag == "RA4Photo")) isoInfos["RA4Photo"] = (*(electronIsoValPFId[1]))[gsfel];
      if ((isoFlag == "RA4") || (isoFlag == "RA4Neutr")) isoInfos["RA4Neutr"] = (*(electronIsoValPFId[2]))[gsfel];
    }

    // Infos for rho-corrected isolation
    
    else if (isoFlag == "rho")
    {
      edm::InputTag tagRhoCorr(cfg.electron_rhoCorrSrc[0], "rho");
      edm::Handle<double> h_rho;
      iEvent.getByLabel(tagRhoCorr, h_rho);
      
      if (!h_rho.isValid()) 
        ERROR("Produce") << "Input collection '" << cfg.electron_rhoCorrSrc[0] << "' for electron rho-correction is missing." << std::endl;
      else
        isoInfos["rho"] = (*h_rho);  
    }

    else if (isoFlag == "Aeff")
    {
      string AeffTypeTag   = cfg.electron_rhoCorrSrc[1];
      string AeffTargetTag = cfg.electron_rhoCorrSrc[2];
      
      ElectronEffectiveArea::ElectronEffectiveAreaType AeffType;
      ElectronEffectiveArea::ElectronEffectiveAreaTarget AeffTarget;

      // Feel free to add new tags if needed

      if (AeffTypeTag == "GammaAndNeutralHadronIso03") AeffType = ElectronEffectiveArea::kEleGammaAndNeutralHadronIso03;
      else                  ERROR("Produce") << "Type-tag for Aeff '" << AeffTypeTag << "' unknown." << std::endl;

               if (AeffTargetTag == "NoCorr")     AeffTarget = ElectronEffectiveArea::kEleEANoCorr;
      else if (AeffTargetTag == "Data2011")   AeffTarget = ElectronEffectiveArea::kEleEAData2011;
      else if (AeffTargetTag == "Summer11MC") AeffTarget = ElectronEffectiveArea::kEleEASummer11MC;
      else if (AeffTargetTag == "Fall11MC")   AeffTarget = ElectronEffectiveArea::kEleEAFall11MC;
      else if (AeffTargetTag == "Data2012")   AeffTarget = ElectronEffectiveArea::kEleEAData2012;
      else                  ERROR("Produce") << "Target-tag for Aeff '" << AeffTargetTag << "' unknown." << std::endl;

      // Fill Aeff
      isoInfos["Aeff"] = ElectronEffectiveArea::GetElectronEffectiveArea(AeffType,
                               fabs(patelec->superCluster()->eta()),AeffTarget);
    }
  }
  
  // Saving map
  myelec->isolation.Fill(isoInfos);

  /*
   * This is the old iso format :
   *
    myelec->TrkIso04    = patelec->trackIso();
    myelec->ECaloIso04  = patelec->ecalIso();
    myelec->HCaloIso04  = patelec->hcalIso();

    myelec->TrkIso03    = patelec->dr03TkSumPt();
    myelec->ECaloIso03  = patelec->dr03EcalRecHitSumEt();
    myelec->HCaloIso03  = patelec->dr03HcalTowerSumEt();

    myelec->PATNeutralHadronIso =  patelec->neutralHadronIso();
    myelec->PATChargedHadronIso =  patelec->chargedHadronIso();
    myelec->PATPhotonIso        =  patelec->photonIso();
    myelec->PATTrackIso         =  patelec->trackIso();
  */

  // --------- [Begin] Infos for SUSYstop analysis ---------
  
  // Is electron from endcap ?
    myelec->isEE = patelec->isEE();

  // Eta for the superCluster
    myelec->etaSuperCluster = patelec->superCluster()->eta();

  // Check gsfTrack isn't null before filling variables
    if (patelec->gsfTrack().isNonnull())
  {
    myelec->missingHits = patelec->gsfTrack()->trackerExpectedHitsInner().numberOfHits();
    if (cfg.doVertices && vp!=0)
    {
      myelec->dxy_vertex = fabs(patelec->gsfTrack()->dxy((*vp).position() ));
      myelec->dz_vertex = fabs(patelec->gsfTrack()->dz((*vp).position() ));
    }

  }

  // Matching between reco and PF infos
  if (!(cfg.doElectronMatch == edm::InputTag("")))
  {
    // Getting reco electrons
    edm::Handle< std::vector<pat::Electron> > recoElectrons;
    iEvent.getByLabel(cfg.doElectronMatch, recoElectrons);

    const pat::Electron* bestMatch;
    float dR_bestMatch = 9999.0;

    // Find best recoElectron match for current electron
    for (vector < pat::Electron >::const_iterator
           it_reco = recoElectrons->begin(); it_reco != recoElectrons->end(); it_reco++) 
    {
      const pat::Electron * recoElec = &*it_reco;

      float dR_test = deltaR(patelec->eta(), patelec->phi(), recoElec->eta(), recoElec->phi());

      if (dR_test < dR_bestMatch)
      {
        dR_bestMatch = dR_test;
        bestMatch = recoElec;
      }
    }

    // Save infos about it
    if (recoElectrons->size() >= 1)
    {
      myelec->bestMatch_eta = bestMatch->eta();
      myelec->bestMatch_phi = bestMatch->phi();
      myelec->bestMatch_pT = bestMatch->pt();
    }
    else
    {
      myelec->bestMatch_eta = 999.0;
      myelec->bestMatch_phi = 999.0;
      myelec->bestMatch_pT = 999999.0; 
    }
    myelec->bestMatch_dR = dR_bestMatch;
  }

  // --------- [End] Infos for SUSYstop analysis ----------



  // ------------------- Track info -----------------------

    if (patelec->gsfTrack().isNonnull())
    {
      myelec->nLost = patelec->gsfTrack()-> 
                    trackerExpectedHitsInner().numberOfLostHits();
      if (cfg.doBeamSpot && bs!=0) myelec->D0 = patelec->gsfTrack()->dxy(*bs);
      myelec->Chi2 = patelec->gsfTrack()->normalizedChi2();

      // REMARK: pour avoir acces a la trace il faut lors de la creation du
      // patlayer1 mettre a true l'acces a la trace!
      myelec->TrackEl = *(patelec->gsfTrack());

      // 3D impact parameter if primary vertex is available
      if (cfg.doVertices && vp!=0)
      {
        // Building transientTrack from inner Track
        reco::TransientTrack tt = trackBuilder->build(patelec->gsfTrack());

        // Get 3D impact parameter and its error
        myelec->IP3D = 
          IPTools::absoluteImpactParameter3D(tt,*vp).second.value(); 
        myelec->IP3DErr =
          IPTools::absoluteImpactParameter3D(tt,*vp).second.error();
      }

    }

    // --------------------- Conversion ---------------------
 
    // returns the best candidate partner
    ConversionFinder convFinder;

    ConversionInfo convInfo = 
            convFinder.getConversionInfo(*patelec, tracks, bField);

    // fill informations 
    myelec->deltaDistance = convInfo.dist();
    myelec->deltaCotTheta = convInfo.dcot();

    // Conversion veto
    myelec->passConversionVeto = patelec->passConversionVeto();

    // --------------------- Electron ID -----------------------

    std::map<std::string,Float_t> ids;

    // Fill all the available IDs
    if (cfg.electron_saveAllID)
    {
      const std::vector< std::pair<std::string,float> > patids 
          = patelec->electronIDs();
      for (unsigned int i=0;i<patids.size();i++)
      {
        if (patids[i].first=="") continue;
        ids[patids[i].first] = patids[i].second;
      }
    }

    // Fill only selected IDs
    else
    {
      for (unsigned int i=0;i<cfg.electron_IDlist.size();i++)
      {
        ids[cfg.electron_IDlist[i]] = patelec->electronID(cfg.electron_IDlist[i]);
      }
    }

    // Possibility to add other data
    // Examples : ids["toto"]=1.0;

    // Saving ids
    myelec->ID.Fill(ids);

    // --------------------- Electron energy -----------------------

    myelec->EmEnergy_           = patelec->ecalEnergy();
    myelec->caloEnergy          = patelec->caloEnergy();
    myelec->eSuperClusterOverP  = patelec->eSuperClusterOverP();

    myelec->deltaEtaSeedClusterTrackAtCalo = patelec->deltaEtaSeedClusterTrackAtCalo();
    myelec->deltaPhiSeedClusterTrackAtCalo = patelec->deltaPhiSeedClusterTrackAtCalo();
    myelec->deltaEtaSuperClusterTrackAtVtx = patelec->deltaEtaSuperClusterTrackAtVtx();
    myelec->deltaPhiSuperClusterTrackAtVtx = patelec->deltaPhiSuperClusterTrackAtVtx();

    myelec->TrkZ0          = patelec->TrackPositionAtVtx().Z();
    myelec->TrkPt          = sqrt(patelec->trackMomentumAtVtx().perp2());
    myelec->hadronicOverEm = patelec->hadronicOverEm();
    myelec->hcalOverEcal   = patelec->hcalOverEcal();
    myelec->sigmaIetaIeta  = patelec->sigmaIetaIeta();
    myelec->e2x5Max        = patelec->e2x5Max();
    myelec->e5x5           = patelec->e5x5();
    myelec->fbrem          = patelec->fbrem();
    myelec->classification = patelec->classification();
    myelec->isEB           = patelec->isEB();
    myelec->isEcalDriven   = patelec->ecalDrivenSeed ();
    myelec->rawSCEnergy    = patelec->superCluster()->rawEnergy();

    double theta = 2*atan(exp(-1*patelec->superCluster()->eta()));
    myelec->ET_SC = patelec->superCluster()->energy()*sin(theta);

    // --------------------- HLT-object matching -----------------------
    if (cfg.doTrigger)
    {
      std::map<std::string,TLorentzVector> matched;

      const pat::helper::TriggerMatchHelper matchHelper;

      for (unsigned int i=0;i<cfg.electronHLTmatching.size();i++)
      {
        if (cfg.electronHLTmatching[i]=="") continue;
        const pat::TriggerObjectRef trigRef ( 
               matchHelper.triggerMatchObject(electrons, std::distance(electrons->begin(),it),
                                              cfg.electronHLTmatching[i], iEvent, *patTriggerEvent ) );
        if ( trigRef.isAvailable() )
        {
          TLorentzVector q;
          q.SetPxPyPzE(trigRef->px(), trigRef->py(), trigRef->pz(), trigRef->energy());
        }
      }

      myelec->p4HLT.Fill(matched);
    }

    // --------------------- Monte Carlo Info -----------------------

    if (!cfg.isData)
    {
      // Get 4-vector momentum with pat matched MC particle
      if ((patelec->genLepton()!=0))
      {
        myelec->p4Gen.SetPxPyPzE( patelec->genLepton()->px(),
                                  patelec->genLepton()->py(),
                                  patelec->genLepton()->pz(),
                                  patelec->genLepton()->energy() );
      }

      // Get mother, grandmother and grandgrandmother particles
      if (cfg.doGenParticleCollection && genParticles!=0)
      { 
        reco::GenParticle genmother;
        reco::GenParticle gengrandmother;
        reco::GenParticle genggrandmother;
        myelec->LeptonOrigin = MonteCarloOrigin::getElectronOrigin(
                                     genParticles, patelec,
                                     genmother,
                                     gengrandmother,
                                     genggrandmother);
        myelec->GenMother       = genmother;
        myelec->GenGrandMother  = gengrandmother;
        myelec->GenGGrandMother = genggrandmother;
      }
    }

  }
}


// ----------------------------------------------------------------------------
//             
//                  /'\_/`\                           
//                  |     | _   _    _     ___    ___ 
//                  | (_) |( ) ( ) /'_`\ /' _ `\/',__)
//                  | | | || (_) |( (_) )| ( ) |\__, \
//                  (_) (_)`\___/'`\___/'(_) (_)(____/
//                                                         
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillMuons(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const edm::Handle< std::vector<pat::Muon> >& muons,
                 const TransientTrackBuilder* trackBuilder,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const reco::Vertex* & vp,
                 const pat::TriggerEvent* patTriggerEvent)
{
  // Loop over Muons
  for (std::vector<pat::Muon>::const_iterator
         it = muons->begin (); it != muons->end (); it++)
  {
    const pat::Muon * patmuon = &*it;


    // --------------------- Preselection -----------------------

    // Applying a preselectin on muons based on lep pT, eta, iso
    if ( patmuon->pt() < cfg.muon_cut_pt || 
         fabs (patmuon->eta()) > cfg.muon_cut_eta ) continue;

    // Applying a preselection on muons kind
    if (! ((patmuon->isGlobalMuon()     && cfg.muon_cut_glb ) ||
           (patmuon->isTrackerMuon()    && cfg.muon_cut_trk ) ||
           (patmuon->isStandAloneMuon() && cfg.muon_cut_sta ) ||
           (patmuon->isCaloMuon()       && cfg.muon_cut_cal )) ) continue;

    // --------------------- General info -----------------------

    IPHCTree::MTMuon* mymuon = evt->NewMuon();

    // Set 4-vector momentum
    mymuon->p4.SetPxPyPzE( patmuon->px(), 
                           patmuon->py(),
                           patmuon->pz(),
                           patmuon->energy() );

    // Set muon vertex
    mymuon->vertex.SetXYZ( patmuon->vx(),
                           patmuon->vy(),
                           patmuon->vz() );

    // Charge
    mymuon->charge = patmuon->charge();

    // Muon type
    mymuon->isGlobalMuon     = patmuon->isGlobalMuon();
    mymuon->isStandaloneMuon = patmuon->isStandAloneMuon();
    mymuon->isTrackerMuon    = patmuon->isTrackerMuon();
    mymuon->isCaloMuon       = patmuon->isCaloMuon();

    // Muon DB
    mymuon->DB = patmuon->dB();
 
    // ------------------ Isolation info -----------------------
  
  // Init map
  std::map<std::string,Float_t> isoInfos;

  // Fill map
  
    // 
    // > Feel free to add your own isolation tags if needed
    //

  for (unsigned int i = 0 ; i < cfg.muon_Isolist.size() ; i++)
  {
    string isoFlag = cfg.muon_Isolist[i];
    
    // Individual isos
    
         if (isoFlag == "Trk03")    isoInfos["Trk03"]    = patmuon->trackIso();
    else if (isoFlag == "ECalo03")  isoInfos["ECalo03"]  = patmuon->ecalIso();
    else if (isoFlag == "HCalo03")  isoInfos["HCalo03"]  = patmuon->hcalIso();
  
    else if (isoFlag == "PF03Char") isoInfos["PF03Char"] = patmuon->pfIsolationR03().sumChargedHadronPt;
    else if (isoFlag == "PF03Neut") isoInfos["PF03Neut"] = patmuon->pfIsolationR03().sumNeutralHadronEt;
    else if (isoFlag == "PF03Phot") isoInfos["PF03Phot"] = patmuon->pfIsolationR03().sumPhotonEt;
    else if (isoFlag == "PF03PU")   isoInfos["PF03PU"]   = patmuon->pfIsolationR03().sumPUPt;  

    else if (isoFlag == "PF04Char") isoInfos["PF04Char"] = patmuon->pfIsolationR04().sumChargedHadronPt;
    else if (isoFlag == "PF04Neut") isoInfos["PF04Neut"] = patmuon->pfIsolationR04().sumNeutralHadronEt;
    else if (isoFlag == "PF04Phot") isoInfos["PF04Phot"] = patmuon->pfIsolationR04().sumPhotonEt;
    else if (isoFlag == "PF04PU")   isoInfos["PF04PU"]   = patmuon->pfIsolationR04().sumPUPt;  

    else if (isoFlag == "PATNeutH") isoInfos["PATNeutH"] = patmuon->neutralHadronIso();
    else if (isoFlag == "PATCharH") isoInfos["PATCharH"] = patmuon->chargedHadronIso();
    else if (isoFlag == "PATPhoto") isoInfos["PATPhoto"] = patmuon->photonIso();
    else if (isoFlag == "PATTrack") isoInfos["PATTrack"] = patmuon->trackIso();

    // Group of isos (to avoid having to put a long list of tags in the cfg.py)

    else if (isoFlag == "TrkAndCalo03")
    {
      isoInfos["Trk03"]    = patmuon->trackIso();
      isoInfos["ECalo03"]  = patmuon->ecalIso();
      isoInfos["HCalo03"]  = patmuon->hcalIso();
    }
    else if (isoFlag == "PF03")
    {
      isoInfos["PF03Char"] = patmuon->pfIsolationR03().sumChargedHadronPt;
      isoInfos["PF03Neut"] = patmuon->pfIsolationR03().sumNeutralHadronEt;
      isoInfos["PF03Phot"] = patmuon->pfIsolationR03().sumPhotonEt;
      isoInfos["PF03PU"]   = patmuon->pfIsolationR03().sumPUPt;  
    }
    else if (isoFlag == "PF04")
    {
      isoInfos["PF04Char"] = patmuon->pfIsolationR04().sumChargedHadronPt;
      isoInfos["PF04Neut"] = patmuon->pfIsolationR04().sumNeutralHadronEt;
      isoInfos["PF04Phot"] = patmuon->pfIsolationR04().sumPhotonEt;
      isoInfos["PF04PU"]   = patmuon->pfIsolationR04().sumPUPt;  
    }
    else if (isoFlag == "PAT")
    {
      isoInfos["PATNeutH"] = patmuon->neutralHadronIso();
      isoInfos["PATCharH"] = patmuon->chargedHadronIso();
      isoInfos["PATPhoto"] = patmuon->photonIso();
      isoInfos["PATTrack"] = patmuon->trackIso();
    }
  }

    mymuon->isolation.Fill(isoInfos);
  /*
   * This is the old format :
   *
    // Muon Isolation
    mymuon->TrkIso03   = patmuon->trackIso();
    mymuon->ECaloIso03 = patmuon->ecalIso();
    mymuon->HCaloIso03 = patmuon->hcalIso();
   
    mymuon->PATNeutralHadronIso =  patmuon->neutralHadronIso();
    mymuon->PATChargedHadronIso =  patmuon->chargedHadronIso() ;
    mymuon->PATPhotonIso        =  patmuon->photonIso() ;
    mymuon->PATTrackIso         =  patmuon->trackIso();     
  */

    // --------------------- Muon ID -----------------------

    std::map<std::string,Float_t> ids;

    // Fill with IDs
    for (unsigned int i=0;i<cfg.muon_IDlist.size();i++)
    {
      if (cfg.muon_IDlist[i]=="") continue;
      ids[cfg.muon_IDlist[i]] = patmuon->muonID(cfg.muon_IDlist[i]);
    }

    // Possibility to add other data
    // Examples : ids["toto"]=1.0;

    // Saving ids
    mymuon->ID.Fill(ids);

  // --------- [Begin] Infos for SUSYstop analysis ---------

    mymuon->isPFMuon = patmuon->isPFMuon();

  mymuon->numMatchedStations = patmuon->numberOfMatchedStations();
  
  mymuon->numTrackerLayersWithMeasurement = 0.0;
    if (patmuon->track().isNonnull())
  {
    mymuon->numTrackerLayersWithMeasurement = patmuon->track()->hitPattern().trackerLayersWithMeasurement();
  }

  // Check innerTrack isn't null before filling variables
  if (patmuon->innerTrack().isNonnull())
  {
    mymuon->pixelHits = patmuon->innerTrack()->hitPattern().numberOfValidPixelHits();

    // If primary vertex is available
        if (cfg.doVertices && vp!=0)
    {
      mymuon->dxy_vertex = fabs(patmuon->innerTrack()->dxy((*vp).position()));
      mymuon->dz_vertex = fabs(patmuon->innerTrack()->dz((*vp).position()));
    }
  }

  // Matching between reco and PF infos
  if (!(cfg.doMuonMatch == edm::InputTag("")))
  {
    // Getting reco muons
    edm::Handle< std::vector<pat::Muon> > recoMuons;
    iEvent.getByLabel(cfg.doMuonMatch, recoMuons);

    const pat::Muon* bestMatch;
    float dR_bestMatch = 9999.0;

    // Find best recoMuon match for current muon
    for (vector < pat::Muon >::const_iterator
           it_reco = recoMuons->begin(); it_reco != recoMuons->end(); it_reco++) 
    {
      const pat::Muon* recoMuon = &*it_reco;

      float dR_test = deltaR(patmuon->eta(), patmuon->phi(), recoMuon->eta(), recoMuon->phi());

      if (dR_test < dR_bestMatch)
      {
        dR_bestMatch = dR_test;
        bestMatch = recoMuon;
      }
    }

    // Save infos about it
    if (recoMuons->size() >= 1)
    {
      mymuon->bestMatch_eta = bestMatch->eta();
      mymuon->bestMatch_phi = bestMatch->phi();
      mymuon->bestMatch_pT = bestMatch->pt();
    }
    else
    {
      mymuon->bestMatch_eta = 999.0;
      mymuon->bestMatch_phi = 999.0; 
      mymuon->bestMatch_pT = 999999.0; 
    }
    mymuon->bestMatch_dR = dR_bestMatch;
  }

  // ---------- [End] Infos for SUSYstop analysis ----------

    // --------------------- TrackInfo -----------------------

    // Global Track
    if (patmuon->globalTrack().isNonnull())
    {
      if (cfg.doBeamSpot && bs!=0) mymuon->D0 = patmuon->globalTrack()->dxy(*bs);
      mymuon->Chi2 = patmuon->globalTrack()->normalizedChi2();
    }

    // Inner Track
    if (patmuon->innerTrack().isNonnull())
    {
      if (cfg.doBeamSpot && bs!=0) mymuon->D0Inner = patmuon->innerTrack()->dxy(*bs);
       mymuon->NTrValidHits = patmuon->innerTrack()->numberOfValidHits();
    }

    // Get all information from track

      if (patmuon->track().isNonnull())
      mymuon->TrackMu = *(patmuon->track());
    if (patmuon->isStandAloneMuon())
         mymuon->StaMu = *(patmuon->standAloneMuon());

    if (patmuon->isGlobalMuon())
         mymuon->ComMu = *(patmuon->combinedMuon());

    // Number of hits
    mymuon->NOfMatches   = patmuon->numberOfMatches();

    // Specific variables in the GlobalMuon case
    if (patmuon->isGlobalMuon())
    {
      // Number of valid hits 
      mymuon->NValidHits = 
             patmuon->globalTrack()->hitPattern().numberOfValidMuonHits();

      // 3D impact parameter if primary vertex is available
      if (cfg.doVertices && vp!=0)
      {
        // Building transientTrack from inner Track
        reco::TransientTrack tt = trackBuilder->build(it->innerTrack());

        // Get 3D impact parameter and its error
        mymuon->IP3D = 
              IPTools::absoluteImpactParameter3D(tt,*vp).second.value(); 
        mymuon->IP3DErr =
              IPTools::absoluteImpactParameter3D(tt,*vp).second.error();
      }
    }

    // --------------------- HLT-object matching -----------------------
    if (cfg.doTrigger)
    {
      std::map<std::string,TLorentzVector> matched;

      const pat::helper::TriggerMatchHelper matchHelper;

      for (unsigned int i=0;i<cfg.muonHLTmatching.size();i++)
      {
        if (cfg.muonHLTmatching[i]=="") continue;
        const pat::TriggerObjectRef trigRef ( 
               matchHelper.triggerMatchObject(muons, std::distance(muons->begin(),it), cfg.muonHLTmatching[i], iEvent, *patTriggerEvent ) );
        if ( trigRef.isAvailable() )
        {
          TLorentzVector q;
          q.SetPxPyPzE(trigRef->px(), trigRef->py(), trigRef->pz(), trigRef->energy());
        }
      }

      mymuon->p4HLT.Fill(matched);
    }

    // --------------------- Monte Carlo Info -----------------------
    if (!cfg.isData)
    {
      // Get 4-vector momentum with pat matched MC particle
      if ((patmuon->genLepton()!=0))
      {
        mymuon->p4Gen.SetPxPyPzE( patmuon->genLepton()->px(),
                                  patmuon->genLepton()->py(),
                                  patmuon->genLepton()->pz(),
                                  patmuon->genLepton()->energy() );
      }

      // Get mother, grandmother and grandgrandmother particles
      if (cfg.doGenParticleCollection && genParticles!=0)
      { 
        reco::GenParticle genmother;
        reco::GenParticle gengrandmother;
        reco::GenParticle genggrandmother;
        mymuon->LeptonOrigin = MonteCarloOrigin::getMuonOrigin(
                                    genParticles, patmuon,
                                    genmother,
                                    gengrandmother,
                                    genggrandmother);
        mymuon->GenMother       = genmother;
        mymuon->GenGrandMother  = gengrandmother;
        mymuon->GenGGrandMother = genggrandmother;
      }
    
    }
  }
}


// ----------------------------------------------------------------------------
//                         _____                   
//                        (_   _)                  
//                          | |   _ _  _   _   ___ 
//                          | | /'_` )( ) ( )/',__)
//                          | |( (_| || (_) |\__, \
//                          (_)`\__,_)`\___/'(____/
//                                                         
// ----------------------------------------------------------------------------
void MiniTreeProducer::fillTaus(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const edm::Handle<std::vector<pat::Tau> >& taus,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const pat::TriggerEvent* patTriggerEvent)
{
  // Loop over taus
  for (std::vector<pat::Tau>::const_iterator
       it = taus->begin (); it != taus->end (); it++)
  {
    // Getting a pointer to the current tau
    const pat::Tau * patTau = &*it;

    // --------------------- Preselection -----------------------

    // Applying preselection based  on pT, eta, ID
    if ( patTau->pt () < cfg.tau_cut_pt || 
         fabs (patTau->eta ()) > cfg.tau_cut_eta ) continue;

    IPHCTree::MTTau *mytau = evt->NewTau();

    // Set 4-vector momentum
    mytau->p4.SetPxPyPzE( patTau->px(),
                          patTau->py(),
                          patTau->pz(),
                          patTau->energy() );

    // Set vertex position
    mytau->vertex.SetXYZ( patTau->vx(), 
                          patTau->vy(), 
                          patTau->vz() );

    // Electric charge
    mytau->charge = patTau->charge();

    // Leading track
    if (patTau->leadPFChargedHadrCand().isAvailable())
    {
      if (patTau->leadPFChargedHadrCand()->trackRef().isNonnull())
      {
        mytau->leadTrackPt = patTau->leadPFChargedHadrCand()->trackRef()->pt();
        if (cfg.doBeamSpot && bs!=0) mytau->D0 = patTau->leadPFChargedHadrCand()->trackRef()->dxy(*bs);
      }
      else if (patTau->leadPFChargedHadrCand()->gsfTrackRef().isNonnull())
      {
        mytau->leadTrackPt = patTau->leadPFChargedHadrCand()->gsfTrackRef()->pt();
        if (cfg.doBeamSpot && bs!=0) mytau->D0 = patTau->leadPFChargedHadrCand()->gsfTrackRef()->dxy(*bs);
      }
    }

    // Cone Tracks 
    mytau->numSigConeTracks = patTau->signalTracks().size();
    mytau->numIsoConeTracks = patTau->isolationTracks().size();

    // Isolation
    mytau->isolationPFChargedHadrCandsPtSum = patTau -> 
                                    isolationPFChargedHadrCandsPtSum();
    mytau->isolationPFGammaCandsEtSum = patTau->isolationPFGammaCandsEtSum();
    mytau->maximumHCALPFClusterEt = patTau->maximumHCALPFClusterEt();
    mytau->emFraction = patTau->emFraction();

    // Lead
    mytau->hcalTotOverPLead       = patTau->hcalTotOverPLead ();
    mytau->hcalMaxOverPLead       = patTau->hcalMaxOverPLead ();
    mytau->hcal3x3OverPLead       = patTau->hcal3x3OverPLead ();
    mytau->ecalStripSumEOverPLead = patTau->ecalStripSumEOverPLead ();
     
    // Decay mode
    mytau->decayMode = patTau->decayMode();
    
    // --------------------- Tau ID -----------------------
  
    std::map<std::string,Float_t> ids;

    // Fill all the available IDs
    if (cfg.tau_saveAllID)
    {
      const std::vector<std::pair<std::string,float> > patids 
          = patTau->tauIDs();
      for (unsigned int i=0;i<patids.size();i++)
      {
        if (patids[i].first=="") continue;
        ids[patids[i].first] = patids[i].second;
      }
    }

    // Fill only selected IDs
    else
    {
      for (unsigned int i=0;i<cfg.tau_IDlist.size();i++)
      {
        ids[cfg.tau_IDlist[i]] = patTau->tauID(cfg.tau_IDlist[i]);
      }
    }

    // Possibility to add other data
    // Examples : ids["toto"]=1.0;

    // Saving ids
    mytau->ID.Fill(ids);

 
    // --------------------- HLT-object matching -----------------------
    if (cfg.doTrigger)
    {
      std::map<std::string,TLorentzVector> matched;

      const pat::helper::TriggerMatchHelper matchHelper;

      for (unsigned int i=0;i<cfg.tauHLTmatching.size();i++)
      {
        if (cfg.tauHLTmatching[i]=="") continue;
        const pat::TriggerObjectRef trigRef ( 
               matchHelper.triggerMatchObject(taus, std::distance(taus->begin(),it), cfg.tauHLTmatching[i], iEvent, *patTriggerEvent ) );
        if ( trigRef.isAvailable() )
        {
          TLorentzVector q;
          q.SetPxPyPzE(trigRef->px(), trigRef->py(), trigRef->pz(), trigRef->energy());
        }
      }

      mytau->p4HLT.Fill(matched);
    }

    // --------------------- Monte Carlo Info -----------------------

    if (!cfg.isData)
    {
      // Get 4-vector momentum with pat matched MC particle
      if ((patTau->genLepton()!=0))
      {
        mytau->p4Gen.SetPxPyPzE( patTau->genLepton()->px(),
                                  patTau->genLepton()->py(),
                                  patTau->genLepton()->pz(),
                                  patTau->genLepton()->energy() );
      }

      // Get mother, grandmother and grandgrandmother particles
      if (cfg.doGenParticleCollection && genParticles!=0)
      { 
        reco::GenParticle genmother;
        reco::GenParticle gengrandmother;
        reco::GenParticle genggrandmother;
        /*        mytau->LeptonOrigin = MonteCarloOrigin::getMuonOrigin(
                                  genParticles, patTau,
                                  genmother,
                                  gengrandmother,
                                  genggrandmother);*/
        mytau->GenMother       = genmother;
        mytau->GenGrandMother  = gengrandmother;
        mytau->GenGGrandMother = genggrandmother;
      }
    }
  }
}



bool MiniTreeProducer::getBfieldFromDCS(edm::Event& iEvent, const edm::EventSetup& iSetup, float& evt_bField)
{
  edm::Handle<DcsStatusCollection> dcsHandle;
  iEvent.getByLabel("scalersRawToDigi", dcsHandle);

  // Safety : dcsStatus exist ?
  if (!dcsHandle.isValid())
  {
    edm::LogError("DetStatus") << "Error! dcsStatus not found";
    return false;
  }

  // scale factor = 3.801/18166.0 which are
  // average values taken over a stable two
  // week period
  float currentToBFieldScaleFactor = 2.09237036221512717e-04;
  float current = (*dcsHandle)[0].magnetCurrent();
  evt_bField = current*currentToBFieldScaleFactor;
  return true;
}


// ----------------------------------------------------------------------------
//                   _____         _           ___   _____ 
//                  (___  )       ( )_ /'\_/`\(  _`\(_   _)
//                      | |   __  | ,_)|     || (_(_) | |  
//                   _  | | /'__`\| |  | (_) ||  _)_  | |  
//                  ( )_| |(  ___/| |_ | | | || (_( ) | |  
//                  `\___/'`\____)`\__)(_) (_)(____/' (_)  
//
// ----------------------------------------------------------------------------
std::pair<float,float> MiniTreeProducer::fillMuonMET(
         const edm::Handle<edm::ValueMap<reco::MuonMETCorrectionData> >& muMET, 
         const edm::Handle<std::vector<reco::Muon> >& muons )

{
  // Reseting output variables
  float SumMuMetCorrX = 0.;
  float SumMuMetCorrY = 0.;

  // Loop over muons
  for (unsigned int mus=0; mus<muons->size(); mus++)
  {
    reco::MuonRef muref (muons, mus);
    reco::MuonMETCorrectionData muCorrData = (*muMET)[muref];
    if ( muCorrData.type()==0 || muCorrData.type()==4 )
    {
      SumMuMetCorrX += muCorrData.corrX() - muref->px();
      SumMuMetCorrY += muCorrData.corrY() - muref->py();
    }
  }

  // return output
  return std::pair<float,float>(SumMuMetCorrX,SumMuMetCorrY); 
}



void MiniTreeProducer::fillJetMET(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const pat::MET* met,
                 const reco::PFMET* pfmet1,
                 const reco::PFMET* pfmet2,
                 const edm::Handle<std::vector<pat::Jet> >& jets,
                 const std::string& algo,
                 bool fillJetConstituents_, 
                 bool fillSubJetConstituents_, 
                 const std::pair<float,float>& SumMuMetCorr,
                 const pat::TriggerEvent* patTriggerEvent)
{

  if( met )
  {
      IPHCTree::MTMET* mymet = evt->NewMet();

      // ---------------------------------------------------------------
      //                           MET   
      // ---------------------------------------------------------------

      // This is global (JES+muon) corrected MET
      mymet->p2.Set(met->px(), met->py());
      mymet->uncmisEt = met->uncorrectedPt();
      mymet->sumEt    = met->sumEt();

      // NB: met - globaluncorrection = uncorrectedmet : 
      // px() - met.corEx(uc0) = uncmisEt.px(), idem for py

      // { uncorrALL, uncorrJES, uncorrMUON, uncorrMAXN }
      pat::MET::UncorrectionType uc0 = pat::MET::UncorrectionType(0);
      //pat::MET::UncorrectionType uc1 = pat::MET::UncorrectionType(1);
      //pat::MET::UncorrectionType uc2 = pat::MET::UncorrectionType(2);

      // MET global uncorrections (to be added if needed):
      mymet->dmEx = met->corEx(uc0);
      mymet->dmEy = met->corEy(uc0);

      if (algo == "tc")
      {
        mymet -> doCorrection(SumMuMetCorr.first,
                              SumMuMetCorr.second);
        mymet -> p2MuonCorr.Set(met->px() + SumMuMetCorr.first,
                                 met->py() + SumMuMetCorr.second);
      }
  }

  if( pfmet1 )
  {
      const reco::PFMET *met = pfmet1;

      IPHCTree::MTMET* mymet = evt->NewMet();

      // ---------------------------------------------------------------
      //                           MET   
      // ---------------------------------------------------------------

      // This is global (JES+muon) corrected MET
      mymet->p2.Set(met->px(), met->py());
      mymet->uncmisEt = 0;
      mymet->sumEt    = met->sumEt();

      // NB: met - globaluncorrection = uncorrectedmet : 
      // px() - met.corEx(uc0) = uncmisEt.px(), idem for py

      // { uncorrALL, uncorrJES, uncorrMUON, uncorrMAXN }
      pat::MET::UncorrectionType uc0 = pat::MET::UncorrectionType(0);
      //pat::MET::UncorrectionType uc1 = pat::MET::UncorrectionType(1);
      //pat::MET::UncorrectionType uc2 = pat::MET::UncorrectionType(2);

      // MET global uncorrections (to be added if needed):
      mymet->dmEx = 0; //met->corEx(uc0);
      mymet->dmEy = 0; //met->corEy(uc0);

      if (algo == "tc")
      {
        mymet -> doCorrection(SumMuMetCorr.first,
                              SumMuMetCorr.second);
        mymet -> p2MuonCorr.Set(met->px() + SumMuMetCorr.first,
                                 met->py() + SumMuMetCorr.second);
      }
  }

  if( pfmet2 )
  {
      const reco::PFMET *met = pfmet2;

      IPHCTree::MTMET* mymet = evt->NewMet();

      // ---------------------------------------------------------------
      //                           MET   
      // ---------------------------------------------------------------

        // This is global (JES+muon) corrected MET
        mymet->p2.Set(met->px(), met->py());
        mymet->uncmisEt = 0;//met->uncorrectedPt();
        mymet->sumEt    = met->sumEt();

        // NB: met - globaluncorrection = uncorrectedmet : 
        // px() - met.corEx(uc0) = uncmisEt.px(), idem for py

      // { uncorrALL, uncorrJES, uncorrMUON, uncorrMAXN }
        pat::MET::UncorrectionType uc0 = pat::MET::UncorrectionType(0);
        //pat::MET::UncorrectionType uc1 = pat::MET::UncorrectionType(1);
        //pat::MET::UncorrectionType uc2 = pat::MET::UncorrectionType(2);

        // MET global uncorrections (to be added if needed):
        mymet->dmEx = 0;//met->corEx(uc0);
        mymet->dmEy = 0;//met->corEy(uc0);

        if (algo == "tc")
        {
            mymet -> doCorrection(SumMuMetCorr.first,
                              SumMuMetCorr.second);
            mymet -> p2MuonCorr.Set(met->px() + SumMuMetCorr.first,
                                                        met->py() + SumMuMetCorr.second);
        }
  }

  // ---------------------------------------------------------------
  //                           JET
  // ---------------------------------------------------------------

  JetIDSelectionFunctor   jetIDLoose   (JetIDSelectionFunctor::PURE09,      
                                        JetIDSelectionFunctor::LOOSE);
  PFJetIDSelectionFunctor PfjetIDLoose (PFJetIDSelectionFunctor::FIRSTDATA, 
                                        PFJetIDSelectionFunctor::LOOSE);
  JetIDSelectionFunctor   jetIDTight   (JetIDSelectionFunctor::PURE09,
                                        JetIDSelectionFunctor::TIGHT);
  PFJetIDSelectionFunctor PfjetIDTight (PFJetIDSelectionFunctor::FIRSTDATA,
                                        PFJetIDSelectionFunctor::TIGHT);

  for (std::vector<pat::Jet>::const_iterator
       it = jets->begin(); it !=jets->end (); it++)
  {
    // Getting a pointer to the current jet
    const pat::Jet* patJet = &*it;

    // --------------------- Preselection -----------------------

    // Applying a preselection based on pT, eta
    if (patJet->pt() < cfg.jet_cut_pt || 
        abs(patJet->eta()) > cfg.jet_cut_eta)  continue;

    // -------- Creating a new jet in MiniTree -----------------

    IPHCTree::MTJet* myjet = evt->NewJet();

    // ------------------------ General ------------------------

    // Fill 4-vector momentum
    myjet->p4.SetPxPyPzE(patJet->px(),
                         patJet->py(),
                         patJet->pz(),
                         patJet->energy());

    // Fill vertex 
    myjet->vertex.SetXYZ(patJet->vx(), patJet->vy(), patJet->vz());

    // scale factor from current jet with correction (abs=L1+L2+L3) to raw jet

       // Other data
     std::map<std::string,Float_t> others;

     // Fill data

      others["corr_L1FastJet"] = patJet->jecFactor("L1FastJet");
     
     #ifdef ALEX_ERIC_CARO
      others["corr_Uncorr"] = patJet->jecFactor("Uncorrected");
      others["corr_L2Relative"] = patJet->jecFactor("L2Relative");
      others["corr_L3Absolute"] = patJet->jecFactor("L3Absolute");
      if (cfg.isData) others["corr_L2L3Residual"] = patJet->jecFactor("L2L3Residual");
     #endif

      // Saving others
      myjet->others.Fill(others);

    double scale = patJet->jecFactor("Uncorrected");     
    myjet->scale  = scale;

    // Fill identity info
    myjet->n90Hits = patJet->jetID().n90Hits;
    myjet->fHPD    = patJet->jetID().fHPD;
     
    // add uncorr jet
    myjet->uncorrJet.SetPxPyPzE(patJet->correctedP4(0).Px(),
                                patJet->correctedP4(0).Py(),
                                patJet->correctedP4(0).Pz(),
                                patJet->correctedP4(0).E());
    
    myjet->jetArea   = patJet->jetArea();

    myjet->jetCharge = patJet->jetCharge(); 

    // --------------------- JetEnergy -----------------------

    if (patJet->isCaloJet() || patJet->isJPTJet() )
    {
      myjet->emEnergyFraction_  = patJet->emEnergyFraction();
    }
    if (patJet->isPFJet())
    {
      myjet->emEnergyFraction_ = -99;
      myjet->CHEF = patJet->chargedHadronEnergyFraction();
      myjet->CEEF = patJet->chargedEmEnergyFraction();
      myjet->NHEF = patJet->neutralHadronEnergyFraction();
      myjet->NEEF = patJet->neutralEmEnergyFraction();
    }

    // --------------------- Jet & W-tagging ----------------------
    /*
     * Test area of Eric Chabby
     *
        std::map<std::string,Float_t> HeavyTagIds;
        cout<<"Compute volatility"<<endl;
        if(!patJet->isPFJet()) cout<<"the jet is not a pfjet"<<endl;
        HeavyTagIds["volatility"] = GetVolatility(patJet,  iEvent.id().event(), ijet);
        // WARNING: the size of the cone should not be hardcoded
        cout<<"Compute Njettiness"<<endl;
        HeavyTagIds["tau1"] = getNjettinessTau(1,patJet,0.8);
        HeavyTagIds["tau2"] = getNjettinessTau(2,patJet,0.8);
        HeavyTagIds["tau3"] = getNjettinessTau(3,patJet,0.8);
        cout<<"Fill heavytag"<<endl;
        myjet->HeavyTag.Fill(HeavyTagIds); 
    */

    // ----- Looking for the jet constituents (ie subjets) -----
    if (fillSubJetConstituents_)
    {
      for(unsigned isub=0;isub<patJet->getJetConstituentsQuick().size();isub++)
      {
         const reco::Candidate* subj = patJet->getJetConstituentsQuick()[isub];
         IPHCTree::NTSubJet subjet;
         subjet.p4 = TLorentzVector(subj->px(),subj->py(),subj->pz(),subj->energy());
         //shoud we fill other values ?
         myjet->subjets.push_back(subjet);
       }
    }

    // ---- Looking for the constituents (pf or calo) ----
    if (fillJetConstituents_)
    {
      if(patJet->isPFJet())
      {
        //std::cout<<"Before accessing getPFConsistuents"<<std::endl;
        for(unsigned int ic=0;ic<patJet->getPFConstituents().size();ic++)
        {
          const reco::Candidate* constit = patJet->getPFConstituents()[ic].get();
          myjet->constituents.push_back(TLorentzVector(constit->px(),constit->py(),constit->pz(),constit->energy()));
        }
        //std::cout<<"After accessing getPFConsistuents"<<std::endl;
      }
      else
      {
        if(patJet->isCaloJet())
        {
          for(unsigned int ic=0;ic<patJet->getCaloConstituents().size();ic++)
          {
            CaloTower constit = (*patJet->getCaloConstituents()[ic].get());
            myjet->constituents.push_back(TLorentzVector(constit.px(),constit.py(),constit.pz(),constit.energy()));
          }
        }
      }
    }

    // --------------------- Jet & Tracks ----------------------

    myjet->nTracks = patJet->associatedTracks().size();
    myjet->setTracks(patJet->associatedTracks());
    myjet->sumPtTracks = 0.;
    for(unsigned int tr=0;tr<patJet->associatedTracks().size();tr++)
       myjet->sumPtTracks+=patJet->associatedTracks()[tr]->pt();


    // ##################### ONLY FOR RECO FORMAT - BEGIN ##########################

    if (!cfg.isAOD)
    {
      const reco::TrackIPTagInfo * TIP = patJet->tagInfoTrackIP();
      const reco::TrackRefVector & T   = TIP->selectedTracks();
        
      std::vector< reco::TrackIPTagInfo::TrackIPData > ip = TIP->impactParameterData();
     
      // retrieve the "secondary vertex tag infos"
      const reco::SecondaryVertexTagInfo * SVT = patJet->tagInfoSecondaryVertex ();
      const reco::TrackRefVector & S = SVT->vertexTracks();
        
      std::vector<float> prob2d, prob3d;
  
      if (TIP->hasProbabilities ())
      {
        prob2d = TIP->probabilities(0);
        prob3d = TIP->probabilities(1);
      }

      for (unsigned int itk = 0; itk < T.size (); itk++)
      {
    
        const reco::Track tk = *T[itk];
        IPHCTree::MTTrack *mytrack = myjet->NewTrack();
        mytrack->p4.SetPxPyPzE (tk.px (), tk.py (), tk.pz (), tk.p ());
        mytrack->chi2 = tk.chi2 () / tk.ndof ();
        mytrack->withFirstPixel = tk.hitPattern ().hasValidHitInFirstPixelBarrel ();
        mytrack->nHitPXB = tk.hitPattern ().numberOfValidPixelBarrelHits ();
        mytrack->nHitPXF = tk.hitPattern ().numberOfValidPixelEndcapHits ();
        mytrack->nHitTIB = tk.hitPattern ().numberOfValidStripTIBHits ();
        mytrack->nHitTOB = tk.hitPattern ().numberOfValidStripTOBHits ();
        mytrack->nHitTID = tk.hitPattern ().numberOfValidStripTIDHits ();
        mytrack->nHitTEC = tk.hitPattern ().numberOfValidStripTECHits ();
        mytrack->charge  = tk.charge();
        mytrack->IP3Dsig = ip[itk].ip3d.significance ();
        mytrack->IP3D    = ip[itk].ip3d.value ();
        mytrack->IP3Derr = ip[itk].ip3d.error ();
        mytrack->IP2Dsig = ip[itk].ip2d.significance ();
        mytrack->IP2D    = ip[itk].ip2d.value ();
        mytrack->IP2Derr = ip[itk].ip2d.error ();
        if (itk < prob3d.size()) mytrack->Prob3D = prob3d[itk];
        if (itk < prob2d.size()) mytrack->Prob2D = prob2d[itk];
        GlobalPoint pv (TIP->primaryVertex()->position().x(), 
                        TIP->primaryVertex()->position().y(), 
                        TIP->primaryVertex()->position().z());
        mytrack->DecayLength = (ip[itk].closestToJetAxis - pv).mag ();
      }
  
      // -------------------- jets & secondary vertex -----------------------

      myjet->nTracksSVX = S.size();
      myjet->nSVX       = SVT->nVertices ();
      if (SVT->nVertices() >= 1)
      {
        // pick the first secondary vertex (the "best" one)
        const reco::Vertex & sv = SVT->secondaryVertex (0);
        myjet->chi2SVX = sv.chi2 ();
        myjet->ndofSVX = sv.ndof ();

        myjet->flightDistanceSVX    = SVT->flightDistance (0, false).value ();
        myjet->flightDistanceSigSVX = SVT->flightDistance (0, false).significance ();
        myjet->flightDistanceErrSVX = SVT->flightDistance (0, false).error ();

        // compute the invariant mass from a four-vector sum
        TLorentzVector trackFourVectorSum;

        // loop over all tracks in the vertex
        for (reco::Vertex::trackRef_iterator track = sv.tracks_begin();
             track != sv.tracks_end(); ++track)
        {
          TLorentzVector vec;
          vec.SetXYZM ((*track)->px (), (*track)->py (), (*track)->pz (), 0.13957);  // pion mass
          trackFourVectorSum += vec;
        }
        myjet->MassSVX = trackFourVectorSum.M ();
   
      }
    }

    // ##################### ONLY FOR RECO FORMAT - END ############################

    // --------------------- Monte Carlo Info -----------------------
    // Fill MC 4-vector momentum
    if (!cfg.isData)
    {
      myjet->partonFlavour = patJet->partonFlavour();
      if (patJet->genJet()!=0)
              myjet->p4Gen.SetPxPyPzE( patJet->genJet()->px(),
                                       patJet->genJet()->py(),
                                       patJet->genJet()->pz(),
                                       patJet->genJet()->energy() );
      if (patJet->genParton()!=0)
              myjet->p4Parton.SetPxPyPzE( patJet->genParton()->px(),
                                          patJet->genParton()->py(),
                                          patJet->genParton()->pz(),
                                          patJet->genParton()->energy() );
    }

    // --------------------- B tagging -----------------------
    std::map<std::string,Float_t> ids;
    for (unsigned int i=0;i<cfg.jetBTagList.size();i++)
    {
      if (cfg.jetBTagList[i]=="") continue;
      ids[cfg.jetBTagList[i]] = patJet->bDiscriminator(cfg.jetBTagList[i]);
    }
 
    // Saving ids
    myjet->bTag.Fill(ids);

    // --------------------- JET ID -----------------------

    // Two available id : LOOSE & TIGHT
    if (patJet->isCaloJet() || patJet->isJPTJet())
    {
      pat::strbitset ret = jetIDLoose.getBitTemplate();
      pat::strbitset rett = jetIDTight.getBitTemplate();
      ret.set(false);
      rett.set(false);
      myjet->isLOOSE = jetIDLoose (*it, ret);
      myjet->isTIGHT = jetIDTight (*it, rett);
    }
    if (patJet->isPFJet())
    {
      pat::strbitset retpf = PfjetIDLoose.getBitTemplate();
      pat::strbitset rettpf = PfjetIDTight.getBitTemplate();
      retpf.set(false);
      rettpf.set(false);
      myjet->isLOOSE = PfjetIDLoose (*it, retpf);
      myjet->isTIGHT = PfjetIDTight (*it, rettpf);
    }

    ids.clear();
    for (unsigned int i=0;i<cfg.jetIDList.size();i++)
    {
      if (cfg.jetIDList[i]=="LOOSE") { ids["LOOSE"]=myjet->isLOOSE; }
      else if (cfg.jetIDList[i]=="TIGHT") { ids["TIGHT"]=myjet->isTIGHT; }
      else { ERROR("FillJetMET") << "Jet ID labeled '" << cfg.jetIDList[i] << "' is not found" << std::endl; }
    }

    #ifdef ALEX_ERIC_CARO
        bool looseId_Jacob = true;

        if (patJet->isPFJet())
        {
            if (myjet->NEEF >= 0.99) looseId_Jacob = false;
            if (myjet->NHEF >= 0.99) looseId_Jacob = false;
            if (patJet->neutralMultiplicity() + patJet->chargedMultiplicity() < 2) looseId_Jacob = false;

            if (fabs(myjet->p4.Eta()) < 2.4)
            {
              if (myjet->CHEF < 1e-6) looseId_Jacob = false;
              if (patJet->chargedMultiplicity() < 1) looseId_Jacob = false;
              if (myjet->CEEF >= 0.99) looseId_Jacob = false;
            }
        }
        else
        {
            looseId_Jacob = false;
        }

        ids["LOOSE_JACOB"]= looseId_Jacob;
    #endif

    // Saving ids
    myjet->ID.Fill(ids);

    // --------------------- HLT-object matching -----------------------
    if (cfg.doTrigger)
    {
      std::map<std::string,TLorentzVector> matched;

      const pat::helper::TriggerMatchHelper matchHelper;

      for (unsigned int i=0;i<cfg.jetHLTmatching.size();i++)
      {
        if (cfg.jetHLTmatching[i]=="") continue;
        const pat::TriggerObjectRef trigRef ( 
               matchHelper.triggerMatchObject(jets, std::distance(jets->begin(),it), cfg.jetHLTmatching[i], iEvent, *patTriggerEvent ) );
        if ( trigRef.isAvailable() )
        {
          TLorentzVector q;
          q.SetPxPyPzE(trigRef->px(), trigRef->py(), trigRef->pz(), trigRef->energy());
        }
      }

      myjet->p4HLT.Fill(matched);
    }

    // --------------------- sumET -----------------------

    //    myjetmet->sumEtJet    += patJet->et();
    //    myjetmet->sumEtJetRaw += patJet->et()/myjet->scale;
  }    
}



bool MiniTreeProducer::getBfieldFromIDEAL(edm::Event& iEvent, const edm::EventSetup& iSetup, float& evt_bField)
{
  edm::ESHandle<MagneticField> magneticField;
  iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
  evt_bField = magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
  return true;
}



//define this as a plug-in
DEFINE_FWK_MODULE (MiniTreeProducer);

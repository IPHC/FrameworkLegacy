

#include "MiniTree/MiniTreeSkimmer/interface/MiniTreeSkimmer.h"


// ----------------------------------------------------------------------------
// Constructors and destructor
// ----------------------------------------------------------------------------
MiniTreeSkimmer::MiniTreeSkimmer(const edm::ParameterSet& iConfig)
{

  std::cout << "Constructor of MiniTreeSkimmer - BEGIN" << std::endl;

  // Extract MiniTreeSkimmer settings
  cfg.verbose             = iConfig.getParameter<unsigned int>("verbose");
  
  cfg.electron_collection = iConfig.getParameter<edm::InputTag>("electron_collection");
  cfg.electron_cutPt      = iConfig.getParameter<double>      ("electron_cutPt");
  cfg.electron_cutEta     = iConfig.getParameter<double>      ("electron_cutEta");

  cfg.muon_collection     = iConfig.getParameter<edm::InputTag>("muon_collection");
  cfg.muon_cutPt          = iConfig.getParameter<double>       ("muon_cutPt");
  cfg.muon_cutEta         = iConfig.getParameter<double>       ("muon_cutEta");
  
  cfg.minNumberOfLeptons  = iConfig.getParameter<unsigned int>("minNumberOfLeptons");
  
  cfg.jets_collection     = iConfig.getParameter<edm::InputTag>("jets_collection");
  cfg.jets_cutPt          = iConfig.getParameter<double>       ("jets_cutPt");
  cfg.jets_cutEta         = iConfig.getParameter<double>       ("jets_cutEta");

  cfg.minNumberOfJets     = iConfig.getParameter<unsigned int>("minNumberOfJets");


  nEventsInit = 0;
  nEventsDrop = 0;
  nEventsKept = 0;
  
  //produces<IPHCTree::MTSkimmerInfo, edm::InLumi>(); 
  produces<edm::MergeableCounter, edm::InLumi>(); 

  std::cout << "Constructor of MiniTreeSkimmer - END" << std::endl;

}


MiniTreeSkimmer::~MiniTreeSkimmer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

bool MiniTreeSkimmer::keepEvent(edm::Event& iEvent)
{
    nEventsKept++;
    return true;
}
bool MiniTreeSkimmer::dropEvent(edm::Event& iEvent)
{
    nEventsDrop++;
    return false;
}

// ----------------------------------------------------------------------------
// Method called when starting to processes a luminosity block
// ----------------------------------------------------------------------------
bool MiniTreeSkimmer::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  // Reset the SkimmerInfo
  nEventsProcessedInLumi = 0;
  return true;
}

// ----------------------------------------------------------------------------
// Method called on each new Event
// ----------------------------------------------------------------------------
bool
MiniTreeSkimmer::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  nEventsInit++;
  nEventsProcessedInLumi++;
  
  using namespace edm;

  if (cfg.verbose > 1) 
      std::cout << " --[ New event for MiniTreeSkimmer ]-- " << std::endl;

  if (cfg.minNumberOfLeptons > 0)
  {
    unsigned int numberOfElectrons = 0;
    unsigned int numberOfMuons = 0;

    // ,---------------,
    // |   Electrons   |
    // `---------------`

        if (cfg.verbose > 2) 
            std::cout << "Checking number of electrons ..." << std::endl;

        // Create handler
        edm::Handle< std::vector<pat::Electron> > electronsH;
        iEvent.getByLabel(cfg.electron_collection, electronsH);
        
        // Check the collection has been found
        if (!electronsH.isValid())
        {
            std::cout << "Error : electron collection " << cfg.electron_collection;
            std::cout << " not found. Event won't be skimmed." << std::endl;
            return keepEvent(iEvent);
        }
        
        // Loop over electrons and count how many there are
        for (vector<pat::Electron>::const_iterator it = electronsH->begin() ; 
             it != electronsH->end() ; 
             it++)  
        {
            const pat::Electron * patelec = &*it;

            // Apply cuts
            if (     (patelec->pt()   < cfg.electron_cutPt) 
            ||  (fabs(patelec->eta()) > cfg.electron_cutEta) ) continue;

            numberOfElectrons++;
        }

    // ,-----------,
    // |   Muons   |
    // '-----------'

        if (cfg.verbose > 2) 
            std::cout << "Checking number of muons ..." << std::endl;

        // Create handler
        edm::Handle< std::vector<pat::Muon> > muonsH;
        iEvent.getByLabel(cfg.muon_collection, muonsH);
        
        // Check the collection has been found
        if (!muonsH.isValid())
        {
            std::cout << "Error : muon collection " << cfg.muon_collection;
            std::cout << " not found. Event won't be skimmed." << std::endl;
            return keepEvent(iEvent);
        }
        
        // Loop over muons and count how many there are
        for (vector<pat::Muon>::const_iterator it = muonsH->begin() ; 
             it != muonsH->end() ; 
             it++)  
        {
            const pat::Muon * patmuon = &*it;

            // Apply cuts
            if (     (patmuon->pt()   < cfg.muon_cutPt) 
            ||  (fabs(patmuon->eta()) > cfg.muon_cutEta) ) continue;

            numberOfMuons++;
        }

    // ,-----------------------------------------------,
    // |    Skim event if numberOfLeptons is too low   |
    // '-----------------------------------------------'
    
        if (numberOfElectrons + numberOfMuons < cfg.minNumberOfLeptons)
        {
            return dropEvent(iEvent);
        }

  }

  if (cfg.minNumberOfJets > 0)
  {
      unsigned int numberOfJets = 0;

    // ,----------,
    // |   Jets   |
    // '----------'
        
        if (cfg.verbose > 2) 
            std::cout << "Checking number of jets ..." << std::endl;

        // Create handler
        edm::Handle< std::vector<pat::Jet> > jetsH;
        iEvent.getByLabel(cfg.jets_collection, jetsH);

        // Check the collection has been found
        if (!jetsH.isValid())
        {
                std::cout << "Error : jets collection " << cfg.jets_collection;
                std::cout << " not found. Event won't be skimmed." << std::endl;
                return keepEvent(iEvent);
        }
        
        // Loop over jets and count how many there are
        for (vector<pat::Jet>::const_iterator it = jetsH->begin(); 
             it !=jetsH->end(); 
             it++)
        {
            const pat::Jet* patjet = &*it;
                
            // Apply cuts
            if (     (patjet->pt()  < cfg.jets_cutPt) 
            || (fabs(patjet->eta()) > cfg.jets_cutEta) ) continue;

            numberOfJets++;
        }
            
    // ,--------------------------------------------,
    // |    Skim event if numberOfJets is too low   |
    // '--------------------------------------------'
    
        if (numberOfJets < cfg.minNumberOfJets)
        {
            return dropEvent(iEvent);
        }

  }
   
  return keepEvent(iEvent);
}

// ----------------------------------------------------------------------------
// Method called when ending the processing of a luminosity block
// ----------------------------------------------------------------------------
bool MiniTreeSkimmer::endLuminosityBlock(edm::LuminosityBlock& theLumiBlock, edm::EventSetup const&)
{
  auto_ptr<edm::MergeableCounter> nEventsProcessedInLumiPtr(new edm::MergeableCounter);
  nEventsProcessedInLumiPtr->value = nEventsProcessedInLumi++;
  theLumiBlock.put(nEventsProcessedInLumiPtr);
  return true;
}


// ----------------------------------------------------------------------------
// Method called once each job just before starting event loop
// ----------------------------------------------------------------------------
void MiniTreeSkimmer::beginJob()
{
  std::cout << "BeginJob for MiniTreeSkimmer " << std::endl;
}

// ----------------------------------------------------------------------------
// Method called once each job just after ending the event loop
// ----------------------------------------------------------------------------
void MiniTreeSkimmer::endJob() 
{
    std::cout << "[MiniTreeSkimmer] # of events  : " << nEventsInit << endl;;
    std::cout << "[MiniTreeSkimmer]   > rejected : " << nEventsDrop << " (" << 100 * (float) nEventsDrop / (float) nEventsInit << "%)" << endl;
    std::cout << "[MiniTreeSkimmer]   > kept     : " << nEventsKept     << " (" << 100 * (float) nEventsKept     / (float) nEventsInit << "%)" << endl;
  
  std::cout << "EndJob for MiniTreeSkimmer" << std::endl;
}

// ----------------------------------------------------------------------------
// Method called when starting to processes a run
// ----------------------------------------------------------------------------
bool MiniTreeSkimmer::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ----------------------------------------------------------------------------
// Method called when ending the processing of a run
// ----------------------------------------------------------------------------
bool MiniTreeSkimmer::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ----------------------------------------------------------------------------
// Method fills 'descriptions' with the allowed parameters for the module
// ----------------------------------------------------------------------------
void MiniTreeSkimmer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MiniTreeSkimmer);

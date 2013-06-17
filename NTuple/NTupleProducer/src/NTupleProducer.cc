#include "NTuple/NTupleProducer/interface/NTupleProducer.h"
#include "IPHCDataFormat/MTFormat/interface/MTTransient.h"
#include "IPHCDataFormat/NTFormat/interface/NTTransient.h"


// ----------------------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------------------
NTupleProducer::NTupleProducer (const edm::ParameterSet & iConfig)
{
  std::cout << "Constructor of NTupleProducer - BEGIN" << std::endl;

  // Read configuration file 
  verbose         = iConfig.getParameter<unsigned int>("verbose");
  traceability    = iConfig.getParameter<std::vector<std::string> >("traceability");

  // topfilter
  top_filter.Initialize(iConfig.getParameter<edm::ParameterSet> ("topdilepton_skim"));
  ntuple_filler.Initialize(iConfig.getParameter<edm::ParameterSet> ("general_skim"));

  // Creating some histos
  theNormHisto        = fs->make<TH1F> ("theNormHisto", 
                                        "theNormHisto", 1, 0.5, 1.5);
  theNormHistoByTMEME = fs->make<TH1F> ("theNormHistoByTMEME",
                                        "theNormHistoByTMEME", 
                                        22223, -0.5, 22222.5);
  numberOfEventsBeforeMTSkimmer = fs->make<TH1F> ("numberOfEventsBeforeMTSkimmer", 
                                            "numberOfEventsBeforeMTSkimmer", 1, 0.5, 1.5);
  // Declaring the global info
  TTree* preoutput = fs->make<TTree> ("SampleInfo", "");
  IPHCTree::NTSampleInfo* sampleInfo = new IPHCTree::NTSampleInfo();
  preoutput->Branch("NTSampleInfo", "IPHCTree::NTSampleInfo", &sampleInfo, 32000, 3);
  std::cout << "----------------------------------------------------------------" << std::endl;
  std::cout << " Fill Sample Info ......" << std::endl;
  FillSampleInfo(sampleInfo);
  preoutput->Fill();
  std::cout << " ...... complete" << std::endl;
  std::cout << "----------------------------------------------------------------" << std::endl;

  // Declaring the ntuple
  output = fs->make<TTree> ("Event", "");
  ntuple = new IPHCTree::NTEvent();
  output->Branch("NTEvent", "IPHCTree::NTEvent", &ntuple, 32000, 3);
  // compress= 3 seems to be the optimal !

  ntotal=0;
  nfiltered=0;
  std::cout << "Constructor of NTupleProducer - END" << std::endl;
} 



// ----------------------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------------------
NTupleProducer::~NTupleProducer ()
{
}


// ----------------------------------------------------------------------------
// FillSampleInfo
// ----------------------------------------------------------------------------
bool NTupleProducer::FillSampleInfo(IPHCTree::NTSampleInfo* info)
{
  // safety
  if (traceability.size()<6)
  {
    std::cout << "TraceabilityError: missing information" << std::endl;
    return false;
  }

  // filling global info
  info->version   = traceability[0].c_str();
  info->script    = traceability[1].c_str();
  info->folder    = traceability[2].c_str();
  info->user      = traceability[3].c_str();
  info->machine   = traceability[4].c_str();
  info->time_crab = traceability[5].c_str();

  // configuration info missing ?
  if (traceability.size()==6) return false;

  // filling configuration
  TClonesArray &config = *(info->config);
  for (UInt_t i=0;i<(traceability.size()-6);i++)
  {
    new(config[i]) TObjString(traceability[i+6].c_str());
  }

  // Ok
  return true;
}


// ----------------------------------------------------------------------------
// Analyze
// ----------------------------------------------------------------------------
void NTupleProducer::analyze (const edm::Event & iEvent, 
                              const edm::EventSetup & iSetup)
{
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
  const IPHCTree::MTEvent* minitree = minitreeHandle.product();
  IPHCTree::MTTransient::InitializeAfterReading(minitree);


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
  // Saving event info into histo
  // -------------------------------------
  
  theNormHisto->Fill(1);
  theNormHistoByTMEME->Fill(minitree->mc.TMEME);

 
  // -------------------------------------
  // Filling NTuple
  // -------------------------------------
  ntuple_filler.Fill(minitree,ntuple);


  // -------------------------------------
  // Skimming 
  // -------------------------------------
  ntotal++;
  if (verbose > 0) std::cout << "Skimming ..." << std::endl;
  if (!top_filter.Filter(ntuple))
  {
    if (verbose > 0) std::cout << "--> the event is skimmed" << std::endl;
    return;
  }
  nfiltered++;

  // -------------------------------------
  // Saving event in NTuple
  // -------------------------------------
  if (verbose > 0) std::cout << "Store the event into the ntuple ..." << std::endl; 
  IPHCTree::NTTransient::InitializeBeforeWriting(ntuple);
  output->Fill ();
  if (verbose > 0) std::cout << "--> the event is successfully stored into the ntuple.";
  if (verbose > 0) std::cout << std::endl;
}

void NTupleProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{

}

void NTupleProducer::endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const&)
{
    edm::Handle<edm::MergeableCounter> nEventsProcessedForLumi;
    lumi.getByLabel("MiniTreeSkimming",nEventsProcessedForLumi);

    if (!nEventsProcessedForLumi.isValid()) return;

    numberOfEventsBeforeMTSkimmer->Fill(1,nEventsProcessedForLumi->value);
    numberOfEventsBeforeMTSkimmer->SetEntries(
                            numberOfEventsBeforeMTSkimmer->GetEntries()
                           +nEventsProcessedForLumi->value);

}



void NTupleProducer::beginJob ()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void NTupleProducer::endJob ()
{ 
  std::cout << "Nb total events    = " << ntotal    << std::endl;
  std::cout << "Nb filtered events = " << nfiltered << std::endl;
  std::cout << "--> efficiency = " << static_cast<float>(nfiltered) / 
                                      static_cast<float>(ntotal)*100. << "%" << std::endl;
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

*/



DEFINE_FWK_MODULE (NTupleProducer);

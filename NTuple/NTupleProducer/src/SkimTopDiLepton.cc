#include "NTuple/NTupleProducer/interface/SkimTopDiLepton.h"


// ----------------------------------------------------------------------------
// Initialize
// ----------------------------------------------------------------------------
bool SkimTopDiLepton::Initialize(const edm::ParameterSet & iConfig)
{
  numberOfLept = iConfig.getParameter<int>("numberOfLept");
  numberOfMuon = iConfig.getParameter<int>("numberOfMuon");
  useMuonIdSkim     = iConfig.getParameter<bool>("useMuonIdSkim");
  muon_cut_pt  = iConfig.getParameter<double>("muon_cut_pt");
  muon_cut_iso = iConfig.getParameter<double>("muon_cut_iso");
  numberOfElec = iConfig.getParameter<int>("numberOfElec");
  useElectronIdSkim = iConfig.getParameter<bool>("useElectronIdSkim");
  electron_cut_pt = iConfig.getParameter<double>("electron_cut_pt");
  electron_cut_iso = iConfig.getParameter<double>("electron_cut_iso");

  doTMEMESkimming = iConfig.getParameter<bool>("doTMEMESkimming");
  TMEMESkimList = iConfig.getParameter< std::vector < int > >("TMEMESkimList");
  doMCDiLepSkimming = iConfig.getParameter < bool >("doMCDiLepSkimming");
  MCDiLepList = iConfig.getParameter < std::vector < string > >("MCDiLepList");

  doTriggerSkimming = iConfig.getParameter < bool >("doTriggerSkimming");
  triggerSkimList   = iConfig.getParameter < std::vector < string > >("triggerSkimList");

  doTauSkimming = iConfig.getParameter < bool >("doTauSkimming");
  numberOfTau = iConfig.getParameter < int >("numberOfTau");
  tau_cut_pt = iConfig.getParameter < double >("tau_cut_pt");
  tau_algo = iConfig.getParameter < std::string >("tau_algo");

  doJetSkimming = iConfig.getParameter < bool >("doJetSkimming");
  numberOfJet = iConfig.getParameter < int >("numberOfJet");
  jet_cut_pt = iConfig.getParameter < double >("jet_cut_pt");
  jet_cut_eta = iConfig.getParameter < double >("jet_cut_eta");
  jet_algo = iConfig.getParameter < std::string >("jet_algo");

  return true;
} 


// ----------------------------------------------------------------------------
// Filter
// ----------------------------------------------------------------------------
bool SkimTopDiLepton::Filter(const IPHCTree::NTEvent* event)
{
  // Trigger Skimming
  bool passTriggerSkim = false;

  if (doTriggerSkimming)
  {
    for (unsigned int i=0;i<triggerSkimList.size();i++)
    {
      if (event->trigger.IsFired(triggerSkimList[i]))
      {
        passTriggerSkim=true;
        break;
      }
    }
  }

  //apply skimming
  int nmuon = 0;
  int nelec = 0;
  int passSkim = false;
  int passSkimMuon = false;
  int passSkimElec = false;

  if(numberOfLept != -1)
  {
    // filtering on Muon
    if (useMuonIdSkim) nmuon = GetNumberOfIDMuons(event);
    else nmuon = GetNumberOfMuons(event);
    if (nmuon>=numberOfMuon) passSkimMuon = true;

    // filtering on Electron
    if (useElectronIdSkim) nelec = GetNumberOfIDElectrons(event);
    else nelec = GetNumberOfElectrons(event);
    if (nelec>=numberOfElec) passSkimElec = true;
  }


  // Filtering on muon + electron
  int ntotlepton = nmuon+nelec;
  if (ntotlepton >= numberOfLept &&
                    passSkimMuon &&
                    passSkimElec) passSkim = true;

  // Filtering on taus
  bool passTauSkim = false;
  if(doTauSkimming)
  {
    int ntau = GetNumberOfTaus(event);
    if(ntau >= numberOfTau) passTauSkim = true;
  }

  // Filtering on jets
  bool passJetSkim = false;
  if (doJetSkimming)
  {
    int njet = GetNumberOfJets(event);
    if (njet>=numberOfJet) passJetSkim = true;
  }

  // Filtering on TMEME variable
  bool passTMEME = false;
  if(doTMEMESkimming)
  {
    for(unsigned int x=0; x<TMEMESkimList.size(); x++)
    {
      if(event->mc.TMEME== TMEMESkimList[x])
      { passTMEME = true; break; }
    }
  }

  // Filtering on channel
  bool passChannel = false;
  if(doMCDiLepSkimming)
  {
    for(unsigned int x = 0 ; x<MCDiLepList.size(); x++)
    {
      int TMEME = event->mc.TMEME;
      if(MCDiLepList[x] == "ee" &&
        (TMEME == 2  || TMEME == 10101 || TMEME == 20200 )) passChannel = true;
      if(MCDiLepList[x] == "mumu" &&
        (TMEME == 20 || TMEME == 11010 || TMEME == 22000 )) passChannel = true;
      if(MCDiLepList[x] == "emu" && 
        (TMEME == 11 || TMEME == 11001 || TMEME == 10110 || TMEME == 21100 )) passChannel = true;
      if(MCDiLepList[x] == "tautau" && (TMEME == 20000 )) passChannel = true;
      if(MCDiLepList[x] == "ljets"  && 
        (TMEME == 1 || TMEME == 10 || TMEME == 10000 || TMEME == 11000 || TMEME == 10100 )) passChannel = true;
      if(MCDiLepList[x] == "had" && TMEME==0) passChannel = true;
      if (passChannel) break;
    }
  }

  // Decision
  // Keep event if result = true
  return( (numberOfLept == -1 && !doTMEMESkimming && 
                                 !doMCDiLepSkimming && 
                                 !doTriggerSkimming &&
                                 !doTauSkimming && 
                                 !doJetSkimming) ||
          (numberOfLept != -1 &&  passSkim) ||
          (doTMEMESkimming    &&  passTMEME) ||
          (doMCDiLepSkimming  &&  passChannel) ||
          (doTriggerSkimming  &&  passTriggerSkim) ||
          (doTauSkimming      &&  passTauSkim) ||
          (doJetSkimming      &&  passJetSkim) ); 
}


// ----------------------------------------------------------------------------
// GetNumberOfIDMuons
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfIDMuons(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->muons.GetCollectionList(names);
  if (names.size()==0) return 0;
  else if (names.size()!=1)
  {
    std::cout << "Error : several collections are saved" << std::endl;
  }
  else event->muons.SelectLabel(*names.begin());

  int nmuons=0;
  for(unsigned int i=0; i<event->muons.size(); i++)
  {
    if(!event->muons[i].isGlobalMuon)                             continue;
    if(!event->muons[i].isTrackerMuon)                            continue;
    if(event->muons[i].Chi2           >= 10)                      continue;
    if(event->muons[i].NTrValidHits   <= 10)                      continue;
    if(event->muons[i].NValidHits     <=  0)                      continue;
    if(fabs(event->muons[i].D0Inner)  >= 0.02)                    continue;
    if(fabs(event->muons[i].p4.Eta()) >= 2.4)                     continue;
    if(muon_cut_pt>0 && event->muons[i].p4.Pt()<muon_cut_pt)      continue;
    if(muon_cut_iso>0 && event->muons[i].RelIso03()>muon_cut_iso) continue;
    nmuons++;
  }
  return nmuons;
}


// ----------------------------------------------------------------------------
// GetNumberOfIDMuons
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfMuons(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->muons.GetCollectionList(names);
  if (names.size()==0) return 0;
  else if (names.size()!=1)
  {
    std::cout << "Error : several collections are saved" << std::endl;
  }
  else event->muons.SelectLabel(*names.begin());

  int nmuons = 0;
  for(unsigned int i=0; i<event->muons.size(); i++)
  {
    if(muon_cut_pt>0 && event->muons[i].p4.Pt()     < muon_cut_pt)  continue;
    if(muon_cut_iso>0 && event->muons[i].RelIso03() > muon_cut_iso) continue;
    nmuons++;
  }
  return nmuons;
}


// ----------------------------------------------------------------------------
// GetNumberOfIDElectrons
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfIDElectrons(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->electrons.GetCollectionList(names);
  if (names.size()==0) return 0;
  else if (names.size()!=1)
  {
    std::cout << "Error : several collections are saved" << std::endl;
  }
  else event->electrons.SelectLabel(*names.begin());

  int nelectrons = 0;
  for(unsigned int i=0; i<event->electrons.size(); i++)
  {
    unsigned int elecIdWP90_r = event->electrons[i].ID["simpleEleId90relIso"];
    bool hadId(elecIdWP90_r & 0x1);
    bool isNotConv(elecIdWP90_r & 0x4);    
    
    if(!event->electrons[i].isGsfElectron)          continue; 
    if(!hadId)                                      continue;
    if(!isNotConv)                                  continue;
    if(event->electrons[i].isEcalDriven!=1)         continue;
    if(fabs(event->electrons[i].D0)      >=0.04)    continue; 
    if(fabs(event->electrons[i].p4.Eta())>=2.5)     continue;
    if(event->electrons[i].ET_SC         <=15)      continue;
    if(electron_cut_pt>0 && event->electrons[i].p4.Pt() < electron_cut_pt)      continue;
    if(electron_cut_iso>0 && event->electrons[i].RelIso03() > electron_cut_iso) continue;
    nelectrons++;
  }
  return nelectrons;
}


// ----------------------------------------------------------------------------
// GetNumberOfElectrons
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfElectrons(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->electrons.GetCollectionList(names);
  if (names.size()==0) return 0;
  else if (names.size()!=1)
  {
    std::cout << "Error : several collections are saved" << std::endl;
  }
  else event->electrons.SelectLabel(*names.begin());

  int nelectrons = 0;
  for(unsigned int i=0; i< event->electrons.size(); i++)
  {
    if (electron_cut_pt>0  && 
        event->electrons[i].p4.Pt() < electron_cut_pt) continue;
    if (electron_cut_iso>0 && 
        event->electrons[i].RelIso03() > electron_cut_iso) continue;
    nelectrons++;
  }
  
  return nelectrons;
}


// ----------------------------------------------------------------------------
// GetNumberOfTaus
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfTaus(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->taus.GetCollectionList(names);
  if (names.size()==0) return 0;

  int ntaus = 0;
 
  event->taus.SelectLabel(tau_algo);
  for(unsigned int i=0; i<event->taus.size(); i++)
  {
    if(tau_cut_pt>0 && event->taus[i].p4.Pt() < tau_cut_pt) continue;
    ntaus++;
  }
  return ntaus;
}


// ----------------------------------------------------------------------------
// GetNumberOfJets
// ----------------------------------------------------------------------------
int SkimTopDiLepton::GetNumberOfJets(const IPHCTree::NTEvent* event)
{
  std::set<std::string> names;
  event->jets.GetCollectionList(names);
  if (names.size()==0) return 0;

  int njets = 0;
  event->jets.SelectLabel(jet_algo);
  for(unsigned int i=0; i< event->jets.size(); i++)
  {
    if(jet_cut_pt>0 && event->jets[i].p4.Pt() < jet_cut_pt) continue;
    if(fabs(event->jets[i].p4.Eta()) > jet_cut_eta) continue;
    njets++;
  }
  return njets;  
}


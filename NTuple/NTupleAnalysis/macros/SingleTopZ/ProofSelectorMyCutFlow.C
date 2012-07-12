#define ProofSelectorMyCutFlow_cxx

//////////////////////////////////////////////////////////
//
// Example of TSelector implementation to do a Monte Carlo
// generation using Pythia8.
// See tutorials/proof/runProof.C, option "pythia8", for an
// example of how to run this selector.
//
//////////////////////////////////////////////////////////

#include <TCanvas.h>
#include <TFrame.h>
#include <TPaveText.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1F.h>
#include <TMath.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TParameter.h>
#include "TClonesArray.h"
#include "TParticle.h"
#include "TDatabasePDG.h"

#include "ProofSelectorMyCutFlow.h"

//_____________________________________________________________________________
ProofSelectorMyCutFlow::ProofSelectorMyCutFlow()
{
  // Constructor
  
  
  
  /*
  string ofilenametex = "HighHTEvents.txt";
  ofile = ofstream(ofilenametex.c_str());

  ofile.precision(3);
  ofile.setf(ios::fixed);
  
  */
  
  fChain     = 0;
  branch     = 0;
  event      = 0;
  dataset    = 0;
  anaEL      = 0;
  verbosity  = 0;
  DataType   = 0;
  Luminosity = 0;
  //histos
  fHist      = 0;
   
  
  
  applyDYscale = true ;
  applyFakescale = true  ;
  
  IReweight		= true;
  IDYestimateWithMetCut = true;
  IReweight_puUp	= false;
  IReweight_puDown	= false;
  
  
  useNonIsoWcand = false;
  
  rand.SetSeed(102994949221);

}

//_____________________________________________________________________________
ProofSelectorMyCutFlow::~ProofSelectorMyCutFlow()
{
  // Destructor
  
  //SafeDelete(fHist);
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses of the tree
  // will be set. It is normaly not necessary to make changes to the
  // generated code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running with PROOF.
  
  //fChain point to the loading tree 
  fChain = tree;
  cout << "start init tree " << endl;
  // Set branch addresses
  branch = (TBranch *) tree->GetBranch("NTEvent");
  event = new IPHCTree::NTEvent();
   branch->SetAddress(&event);
   //event is now retrieved and could be used in Process
   cout << "end init tree " << endl;
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Begin(TTree * /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  cout << "start Begin " << endl;
  TString option = GetOption();
  cout << "end  Begin" << endl;
  
  
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::SlaveBegin(TTree * tree)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  
  
  cout << "start SlaveBegin " << endl;
  TString option = GetOption();
  //--------------------------------------//
  //       Loading the xml file
  //--------------------------------------//
  TNamed *dsname = (TNamed *) fInput->FindObject("PROOF_DATASETNAME"); 
  datasetName = dsname->GetTitle();
  cout << "dataset name " << datasetName << endl;
  cout << "dataset name " << datasetName << endl;
  cout << "dataset name " << datasetName << endl;
  cout << "dataset name " << datasetName << endl;
  cout << "dataset name " << datasetName << endl;
  cout << "dataset name " << datasetName << endl;
  TNamed *xfname = (TNamed *) fInput->FindObject("PROOF_XMLFILENAME");
  string xmlFileName = xfname->GetTitle();
  anaEL = new AnalysisEnvironmentLoader(xmlFileName.c_str());
  anaEL->LoadSamples (datasets, datasetName); // now the list of datasets written in the xml file is known
  
  
  
  //retrieve the current dataset according to its name
  for(unsigned int d=0;d<datasets.size();d++){
    cout << "datasets.size() " << datasets.size()<< "  datasets[d].Name()" << datasets[d].Name()  << " datasetName "
	 <<datasetName  << endl;
    if(datasets[d].Name()==datasetName)dataset = &datasets[d];
  }
  cout << "load datasets "  << endl;
  anaEL->LoadDiLeptonSelection (sel); // now the parameters for the selection are given to the selection
  cout << "datasets loaded "  << endl;
  //anaEL->LoadGeneralInfo(DataType, Luminosity, verbosity );
  anaEL->LoadGeneralInfo(DataType, Luminosity, LumiError, PUWeightFileName, verbosity );
  anaEL->LoadWeight (sel); // now the parameters for SFBweight are initialized (for b-tag!)
  
  //Load for PU:
  sel.GeneratePUWeight(PUWeightFileName);
  
  //******************************************
  //Load Scale Factors for lepton efficiencies
  //********d**********************************
  sel.LoadElScaleFactors();
  sel.LoadMuScaleFactors();
  
   //--------------------------------------//
   //   Fill cuts and channels  	
   //--------------------------------------//
  CutName.push_back("Cut1");
   
  //--------------------------------------//
  //   Initializing variables 	
  //--------------------------------------//
  
  
  
  
  
  
  
  SF_trig_mu = 0.977; 
  SF_trig_emu= 1.008; 
  SF_trig_ee = 0.962; 
  
  SF_trig_mu_error  = 0.014; 
  SF_trig_emu_error = 0.007; 
  SF_trig_ee_error  = 0.016; 
  
  SF_e  =1.0; 
  SF_mu =1.0; 
  
  /*SF_met_mumu = 1.00237;
    SF_met_emu  = 1.0;
    SF_met_ee   = 1.00237;
    
    
    SF_met_mumu_error = 0.00629333;
    SF_met_emu_error  = 0;
    SF_met_ee_error   = 0.00629333;*/
  
  
  //**************************************
  //**************************************
  //******* DY DD estimate ***************
  //**************************************
  //**************************************
  
  
  // for PLR plot
  SF_DY_ee = 1.;
  SF_DY_mm = 1.;
  SF_DY_em = 1.;
  
  double lumisf = 1./1.037;
  
  if(applyDYscale){ 
    
    
    //after dilept invMass
    vSF_DY_ee.push_back(1) ;
    vSF_DY_ee_error.push_back(0) ;
    //after jet cut
    vSF_DY_ee.push_back(1.169*lumisf) ;
    vSF_DY_ee_error.push_back(0.077*lumisf) ;
    //after met cut
    vSF_DY_ee.push_back( 1.9281*lumisf/vSF_DY_ee[1]) ;
    vSF_DY_ee_error.push_back(0.404145*lumisf) ;
    //for 1 btag 
    vSF_DY_ee.push_back(2.11816*lumisf/(1.9281*lumisf)) ;
    vSF_DY_ee_error.push_back(0.53244*lumisf) ;
    //for E btag 
    vSF_DY_ee.push_back(2.1314*lumisf/(1.9281*lumisf)) ;
    vSF_DY_ee_error.push_back(1.06501*lumisf) ;
    
    //after dilept invMass
    vSF_DY_mm.push_back(1) ;
    vSF_DY_mm_error.push_back(0) ;
    //after jet cut
    vSF_DY_mm.push_back(1.257*lumisf) ;
    vSF_DY_mm_error.push_back(0.078*lumisf) ;
    //after met cut
    vSF_DY_mm.push_back(1.82219*lumisf/vSF_DY_mm[1]) ;
    vSF_DY_mm_error.push_back(0.365828*lumisf) ;
    //for 1 btag 
    vSF_DY_mm.push_back(1.73089*lumisf/(1.82219*lumisf)) ;
    vSF_DY_mm_error.push_back(0.428215*lumisf) ;
    //for E btag 
    vSF_DY_mm.push_back(0.819327*lumisf/(1.82219*lumisf)) ;
    vSF_DY_mm_error.push_back(0.667288*lumisf) ;
    
    
    
    
    //after dilept invMass
    vSF_DY_em.push_back(1) ;
    vSF_DY_em_error.push_back(0) ;
    //after jet cut
    vSF_DY_em.push_back(1.38872*lumisf) ;
    vSF_DY_em_error.push_back(0.296232*lumisf) ;
    //after met cut
    vSF_DY_em.push_back(1) ;
    vSF_DY_em_error.push_back(0.296232*lumisf) ;
    //for 1 btag 
    vSF_DY_em.push_back(1) ;
    vSF_DY_em_error.push_back(0.296232*lumisf) ;
    //for E btag 
    vSF_DY_em.push_back(1) ;
    vSF_DY_em_error.push_back(0.296232*lumisf) ;
    
    
    // for PLR plot
    SF_DY_ee = 1.9281*lumisf;
    SF_DY_mm = 1.82219*lumisf;
    SF_DY_em = 1.38872*lumisf;
    
    
  }else{
    
    
    for(unsigned int i=0; i< 5; i++){
      vSF_DY_em.push_back(1.) ;
      vSF_DY_em_error.push_back(0.) ;
      vSF_DY_ee.push_back(1.) ;
      vSF_DY_ee_error.push_back(0.) ;
      vSF_DY_mm.push_back(1.) ;
      vSF_DY_mm_error.push_back(0.) ;
    }
    
    
    
  }
  SF_BranchingRatio_ll = (0.108*9.)*(0.108*9.);
  SF_BranchingRatio_lj = (0.108*9.)*(0.676*1.5);
  SF_BranchingRatio_had = (0.676*1.5)*(0.676*1.5);
  
  
  
  
  
  //**************************************
  //**************************************
  //******* fakes DD estimate ************
  //**************************************
  //**************************************
  
  
  if(applyFakescale){  
    //after MET selection
    vSF_FakeBck_ee.push_back(0.966*lumisf); 
    vSF_FakeBck_ee_error.push_back(0.674*lumisf); 
    //after 1 b jet
    vSF_FakeBck_ee.push_back(0.35*lumisf/vSF_FakeBck_ee[0]); 
    vSF_FakeBck_ee_error.push_back(0.615*lumisf); 
    //after 2 b jet
    vSF_FakeBck_ee.push_back(0.35*lumisf/vSF_FakeBck_ee[0]); 
    vSF_FakeBck_ee_error.push_back(0.615*lumisf); 
    
    
    
    //after MET selection
    vSF_FakeBck_mm.push_back(4.9*lumisf); 
    vSF_FakeBck_mm_error.push_back(2.3*lumisf); 
   //after 1 b jet
    vSF_FakeBck_mm.push_back(4.0*lumisf/vSF_FakeBck_mm[0]); 
    vSF_FakeBck_mm_error.push_back(2.2*lumisf); 
    //after 2 b jet
    vSF_FakeBck_mm.push_back(4.0*lumisf/vSF_FakeBck_mm[0]); 
    vSF_FakeBck_mm_error.push_back(2.2*lumisf);
    
   
    
    //after MET selection
    vSF_FakeBck_em.push_back(3.8*lumisf); 
    vSF_FakeBck_em_error.push_back(0.9*lumisf); 
    //after 1 b jet
    vSF_FakeBck_em.push_back(2.5*lumisf/vSF_FakeBck_em[0]); 
    vSF_FakeBck_em_error.push_back(0.25*lumisf); 
    //after 2 b jet
    vSF_FakeBck_em.push_back(2.5*lumisf/vSF_FakeBck_em[0]); 
    vSF_FakeBck_em_error.push_back(0.25*lumisf); 
    
    
    
    
    
    SF_Wjets_ee = 0.966*lumisf ;
    SF_Wjets_mm = 4.9*lumisf ;
    SF_Wjets_em = 3.8*lumisf;
    
    SF_QCD_ee = 1.;
    SF_QCD_mm = 1.;
    SF_QCD_em = 1.;
    
  }else{
    
    
    for(unsigned int i=0; i< 5; i++){
      vSF_FakeBck_em.push_back(1.) ;
      vSF_FakeBck_em_error.push_back(0.) ;
      vSF_FakeBck_ee.push_back(1.) ;
      vSF_FakeBck_ee_error.push_back(0.) ;
      vSF_FakeBck_mm.push_back(1.) ;
      vSF_FakeBck_mm_error.push_back(0.) ;
    }
  }
  
  
  
  //**************************************
  //**************************************
  //******* MET DD estimate **************
  //**************************************
  //**************************************
  
  //SF_met_mumu = 1.00237;
  //SF_met_emu  = 1.0;
  //SF_met_ee   = 1.00237;
  //SF_met_mumu_error = 0.00629333;
  //SF_met_emu_error  = 0;
  //SF_met_ee_error   = 0.00629333;
   
  
  vSF_met_ee.push_back(1.0029);
  vSF_met_ee_error.push_back(0.0167596);
  vSF_met_ee.push_back(1.00839/vSF_met_ee[0]);
  vSF_met_ee_error.push_back(0.0159795);
  vSF_met_ee.push_back(1.01456/vSF_met_ee[0]);
  vSF_met_ee_error.push_back(0.017556);
  
  vSF_met_mumu.push_back(1.0029);
  vSF_met_mumu_error.push_back(0.0135555);
  vSF_met_mumu.push_back(1.00839/vSF_met_mumu[0]);
  vSF_met_mumu_error.push_back(0.012474);
  vSF_met_mumu.push_back(1.01456/vSF_met_mumu[0]);
  vSF_met_mumu_error.push_back(0.0179107);
  
  vSF_met_emu.push_back(1.);
  vSF_met_emu_error.push_back(0.);
  vSF_met_emu.push_back(1.);
  vSF_met_emu_error.push_back(0.);
  vSF_met_emu.push_back(1.);
  vSF_met_emu_error.push_back(0.);
  
  sumSFlept_ee    = 0;
  sumSFlept_mumu  = 0;
  sumSFlept_emu   = 0;
  
  nEvents_ee   = 0;
  nEvents_mumu   = 0;
  nEvents_emu   = 0;
  
  
  scaleElec = 1.0; // 1 to switch off
  resolElec = 0.0; // 0 to switch off
  
  ApplyLeptonSF = true;
  
  ITypeMC     = -1;
  ICut        = -1;  
  
  
  //************************************
  //For trigger systematics 
  
  if(datasetName=="TTbarTriggerUp"){
    SF_trig_mu += SF_trig_mu_error;
    SF_trig_emu+= SF_trig_emu_error;  
    SF_trig_ee += SF_trig_ee_error; 
  } 
  if(datasetName=="TTbarTriggerDown"){
    SF_trig_mu  -= SF_trig_mu_error;
    SF_trig_emu -= SF_trig_emu_error;  
    SF_trig_ee  -= SF_trig_ee_error; 
  } 
  
  //************************************
  
  //************************************
  //For MET systematics 
  
  
  /*if(datasetName=="TTbarMETUp"){
    SF_met_mumu  += SF_met_mumu_error;
    SF_met_emu += SF_met_emu_error;  
    SF_met_ee  += SF_met_ee_error; 
    } 
    if(datasetName=="TTbarMETDown"){
    SF_met_mumu  -= SF_met_mumu_error;
     SF_met_emu -= SF_met_emu_error;  
     SF_met_ee  -= SF_met_ee_error; 
     } */
  
  
  
  for(unsigned int d=0;d<datasets.size();d++){
    cout << "datasets.size() " << datasets.size()<< "  datasets[d].Name()" << datasets[d].Name()  << " datasetName "
	 <<datasetName  << endl;
    if(datasets[d].Name()==datasetName)dataset = &datasets[d];
  }
  
  
  
  
  
  
  //--------------------------------------//
  //   Managing histos  	
  //--------------------------------------//
  MyhistoManager.LoadDatasets(datasets);   
  MyhistoManager.LoadSelectionSteps(CutName);
  MyhistoManager.LoadChannels(ChannelName);
  //example
  
  nbins = 200;
  minx = 0.;
  maxx = 350;
  
  
  //***********************
  // initiate lumi reweighting
  
  
  
  MyhistoManager.CreateHisto(CutFlow_mumumu,  "CutFlow_mumumu" ,datasetName,"CutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(CutFlow_mumue,   "CutFlow_mumue"  ,datasetName,"CutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(CutFlow_eemu,    "CutFlow_eemu"   ,datasetName,"CutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(CutFlow_eee,     "CutFlow_eee"    ,datasetName,"CutFlow","Entries",15,-0.5,14.5);
  
  
  MyhistoManager.SetCutFlowAxisTitleFCNCMonotop(CutFlow_mumumu,   "CutFlow_mumumu"  ,datasetName);
  MyhistoManager.SetCutFlowAxisTitleFCNCMonotop(CutFlow_mumue,    "CutFlow_mumue"   ,datasetName);
  MyhistoManager.SetCutFlowAxisTitleFCNCMonotop(CutFlow_eemu,     "CutFlow_eemu"    ,datasetName);
  MyhistoManager.SetCutFlowAxisTitleFCNCMonotop(CutFlow_eee,      "CutFlow_eee"     ,datasetName);
  
  
  
  
  
  
  MyhistoManager.CreateHisto(ErrCutFlow_mumumu,  "ErrCutFlow_mumumu"  ,datasetName,"ErrCutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(ErrCutFlow_mumue,   "ErrCutFlow_mumue"   ,datasetName,"ErrCutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(ErrCutFlow_eemu,    "ErrCutFlow_eemu"    ,datasetName,"ErrCutFlow","Entries",15,-0.5,14.5);
  MyhistoManager.CreateHisto(ErrCutFlow_eee,     "ErrCutFlow_eee"     ,datasetName,"ErrCutFlow","Entries",15,-0.5,14.5);
  
  
  
  MyhistoManager.CreateHisto(Mt_mumumu_afterbtagsel, "Mt_mumumu_afterbtagsel", datasetName,"Mt","Entries", 50, 0, 300); 
  MyhistoManager.CreateHisto(Mt_mumue_afterbtagsel , "Mt_mumue_afterbtagsel" , datasetName,"Mt","Entries", 50, 0, 300);
  MyhistoManager.CreateHisto(Mt_eemu_afterbtagsel  , "Mt_eemu_afterbtagsel"  , datasetName,"Mt","Entries", 50, 0, 300);
  MyhistoManager.CreateHisto(Mt_eee_afterbtagsel   , "Mt_eee_afterbtagsel"   , datasetName,"Mt","Entries", 50, 0, 300);
   
  
  MyhistoManager.CreateHisto(NJet_mumumu_afterZsel, "NJet_mumumu_afterZsel", datasetName,"Njets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NJet_mumue_afterZsel , "NJet_mumue_afterZsel" , datasetName,"Njets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NJet_eemu_afterZsel  , "NJet_eemu_afterZsel"  , datasetName,"Njets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NJet_eee_afterZsel   , "NJet_eee_afterZsel"   , datasetName,"Njets", "Entries",5,-0.5,4.5);
  
  MyhistoManager.CreateHisto(NBJet_mumumu_afterZsel, "NBJet_mumumu_afterZsel", datasetName,"NBjets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NBJet_mumue_afterZsel , "NBJet_mumue_afterZsel" , datasetName,"NBjets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NBJet_eemu_afterZsel  , "NBJet_eemu_afterZsel"  , datasetName,"NBjets", "Entries",5,-0.5,4.5);
  MyhistoManager.CreateHisto(NBJet_eee_afterZsel   , "NBJet_eee_afterZsel"   , datasetName,"NBjets", "Entries",5,-0.5,4.5);
  
  MyhistoManager.CreateHisto(NBJet_mumumu_afterjetsel, "NBJet_mumumu_afterjetsel", datasetName,"NBjets", "Entries",2,-0.5,1.5);
  MyhistoManager.CreateHisto(NBJet_mumue_afterjetsel , "NBJet_mumue_afterjetsel" , datasetName,"NBjets", "Entries",2,-0.5,1.5);
  MyhistoManager.CreateHisto(NBJet_eemu_afterjetsel  , "NBJet_eemu_afterjetsel"  , datasetName,"NBjets", "Entries",2,-0.5,1.5);
  MyhistoManager.CreateHisto(NBJet_eee_afterjetsel   , "NBJet_eee_afterjetsel"   , datasetName,"NBjets", "Entries",2,-0.5,1.5);	
  
  
   
  
  MyhistoManager.CreateHisto(InvM_ll_mumumu_afterleptsel_highSumPt, "InvM_ll_mumumu_afterleptsel_highSumPt" , datasetName,"Minv",
  "Entries",100,0.,1000);                     
  MyhistoManager.CreateHisto(InvM_ll_mumue_afterleptsel_highSumPt,  "InvM_ll_mumue_afterleptsel_highSumPt"  , datasetName,"Minv",
  "Entries",100,0.,1000);
  MyhistoManager.CreateHisto(InvM_ll_eemu_afterleptsel_highSumPt,   "InvM_ll_eemu_afterleptsel_highSumPt"   , datasetName,"Minv",
  "Entries",100,0.,1000);
  MyhistoManager.CreateHisto(InvM_ll_eee_afterleptsel_highSumPt,    "InvM_ll_eee_afterleptsel_highSumPt"    , datasetName,"Minv",
  "Entries",100,0.,1000);

 
  MyhistoManager.CreateHisto(InvM_ll_mumumu_afterleptsel, "InvM_ll_mumumu_afterleptsel" , datasetName,"Minv", "Entries",350,0.,1000);
  MyhistoManager.CreateHisto(InvM_ll_mumue_afterleptsel,  "InvM_ll_mumue_afterleptsel"  , datasetName,"Minv", "Entries",350,0.,1000);
  MyhistoManager.CreateHisto(InvM_ll_eemu_afterleptsel,   "InvM_ll_eemu_afterleptsel"   , datasetName,"Minv", "Entries",350,0.,1000);
  MyhistoManager.CreateHisto(InvM_ll_eee_afterleptsel,    "InvM_ll_eee_afterleptsel"    , datasetName,"Minv", "Entries",350,0.,1000);

  MyhistoManager.CreateHisto(InvM_ll_mumumu_afterjetsel, "InvM_ll_mumumu_afterjetsel" , datasetName,"Minv", "Entries",350, 0., 350);
  MyhistoManager.CreateHisto(InvM_ll_mumue_afterjetsel,  "InvM_ll_mumue_afterjetsel"  , datasetName,"Minv", "Entries",350, 0., 350);
  MyhistoManager.CreateHisto(InvM_ll_eemu_afterjetsel,   "InvM_ll_eemu_afterjetsel"   , datasetName,"Minv", "Entries",350, 0., 350);
  MyhistoManager.CreateHisto(InvM_ll_eee_afterjetsel,    "InvM_ll_eee_afterjetsel"    , datasetName,"Minv", "Entries",350, 0., 350);
  
  MyhistoManager.CreateHisto(InvM_ll_mumumu_afterbjetsel, "InvM_ll_mumumu_afterbjetsel" , datasetName,"Minv", "Entries",350,0.,350);
  MyhistoManager.CreateHisto(InvM_ll_mumue_afterbjetsel,  "InvM_ll_mumue_afterbjetsel"  , datasetName,"Minv", "Entries",350,0.,350);
  MyhistoManager.CreateHisto(InvM_ll_eemu_afterbjetsel,   "InvM_ll_eemu_afterbjetsel"   , datasetName,"Minv", "Entries",350,0.,350);
  MyhistoManager.CreateHisto(InvM_ll_eee_afterbjetsel,    "InvM_ll_eee_afterbjetsel"    , datasetName,"Minv", "Entries",350,0.,350);

    
  
  MyhistoManager.CreateHisto(LeptPt_mumumu_afterleptsel, "LeptPt_mumumu_afterleptsel", datasetName, "LeptPt", "Entries",350,0., 1000) ;
  MyhistoManager.CreateHisto(LeptPt_mumue_afterleptsel,  "LeptPt_mumue_afterleptsel",  datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eemu_afterleptsel,   "LeptPt_eemu_afterleptsel",   datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eee_afterleptsel,    "LeptPt_eee_afterleptsel",    datasetName, "LeptPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptPt_mumumu_afterjetsel, "LeptPt_mumumu_afterjetsel", datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_mumue_afterjetsel,  "LeptPt_mumue_afterjetsel",  datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eemu_afterjetsel,   "LeptPt_eemu_afterjetsel",   datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eee_afterjetsel,    "LeptPt_eee_afterjetsel",    datasetName, "LeptPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptPt_mumumu_afterbjetsel, "LeptPt_mumumu_afterbjetsel", datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_mumue_afterbjetsel,  "LeptPt_mumue_afterbjetsel",  datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eemu_afterbjetsel,   "LeptPt_eemu_afterbjetsel",   datasetName, "LeptPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptPt_eee_afterbjetsel,    "LeptPt_eee_afterbjetsel",    datasetName, "LeptPt", "Entries",350,0., 1000);
    
  MyhistoManager.CreateHisto(LeptZPt_mumumu_afterleptsel, "LeptZPt_mumumu_afterleptsel", datasetName, "LeptZPt", "Entries",350,0., 1000) ;
  MyhistoManager.CreateHisto(LeptZPt_mumue_afterleptsel,  "LeptZPt_mumue_afterleptsel",  datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eemu_afterleptsel,   "LeptZPt_eemu_afterleptsel",   datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eee_afterleptsel,    "LeptZPt_eee_afterleptsel",    datasetName, "LeptZPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptZPt_mumumu_afterjetsel, "LeptZPt_mumumu_afterjetsel", datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_mumue_afterjetsel,  "LeptZPt_mumue_afterjetsel",  datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eemu_afterjetsel,   "LeptZPt_eemu_afterjetsel",   datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eee_afterjetsel,    "LeptZPt_eee_afterjetsel",    datasetName, "LeptZPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptZPt_mumumu_afterbjetsel, "LeptZPt_mumumu_afterbjetsel", datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_mumue_afterbjetsel,  "LeptZPt_mumue_afterbjetsel",  datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eemu_afterbjetsel,   "LeptZPt_eemu_afterbjetsel",   datasetName, "LeptZPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptZPt_eee_afterbjetsel,    "LeptZPt_eee_afterbjetsel",    datasetName, "LeptZPt", "Entries",350,0., 1000);
    
  MyhistoManager.CreateHisto(LeptWPt_mumumu_afterleptsel, "LeptWPt_mumumu_afterleptsel", datasetName, "LeptWPt", "Entries",350,0., 1000) ;
  MyhistoManager.CreateHisto(LeptWPt_mumue_afterleptsel,  "LeptWPt_mumue_afterleptsel",  datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eemu_afterleptsel,   "LeptWPt_eemu_afterleptsel",   datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eee_afterleptsel,    "LeptWPt_eee_afterleptsel",    datasetName, "LeptWPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptWPt_mumumu_afterjetsel, "LeptWPt_mumumu_afterjetsel", datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_mumue_afterjetsel,  "LeptWPt_mumue_afterjetsel",  datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eemu_afterjetsel,   "LeptWPt_eemu_afterjetsel",   datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eee_afterjetsel,    "LeptWPt_eee_afterjetsel",    datasetName, "LeptWPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(LeptWPt_mumumu_afterbjetsel, "LeptWPt_mumumu_afterbjetsel", datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_mumue_afterbjetsel,  "LeptWPt_mumue_afterbjetsel",  datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eemu_afterbjetsel,   "LeptWPt_eemu_afterbjetsel",   datasetName, "LeptWPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(LeptWPt_eee_afterbjetsel,    "LeptWPt_eee_afterbjetsel",    datasetName, "LeptWPt", "Entries",350,0., 1000);

  
  MyhistoManager.CreateHisto(JetPt_mumumu_afterleptsel, "JetPt_mumumu_afterleptsel", datasetName, "JetPt", "Entries",350,0., 1000) ;
  MyhistoManager.CreateHisto(JetPt_mumue_afterleptsel,  "JetPt_mumue_afterleptsel",  datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eemu_afterleptsel,   "JetPt_eemu_afterleptsel",   datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eee_afterleptsel,    "JetPt_eee_afterleptsel",    datasetName, "JetPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(JetPt_mumumu_afterjetsel, "JetPt_mumumu_afterjetsel", datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_mumue_afterjetsel,  "JetPt_mumue_afterjetsel",  datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eemu_afterjetsel,   "JetPt_eemu_afterjetsel",   datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eee_afterjetsel,    "JetPt_eee_afterjetsel",    datasetName, "JetPt", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(JetPt_mumumu_afterbjetsel, "JetPt_mumumu_afterbjetsel", datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_mumue_afterbjetsel,  "JetPt_mumue_afterbjetsel",  datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eemu_afterbjetsel,   "JetPt_eemu_afterbjetsel",   datasetName, "JetPt", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(JetPt_eee_afterbjetsel,    "JetPt_eee_afterbjetsel",    datasetName, "JetPt", "Entries",350,0., 1000);
  
    
  MyhistoManager.CreateHisto(JetEta_mumumu_afterleptsel, "JetEta_mumumu_afterleptsel", datasetName, "JetEta", "Entries",26, -2.5, 2.5) ;
  MyhistoManager.CreateHisto(JetEta_mumue_afterleptsel,  "JetEta_mumue_afterleptsel",  datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eemu_afterleptsel,   "JetEta_eemu_afterleptsel",   datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eee_afterleptsel,    "JetEta_eee_afterleptsel",    datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  
  MyhistoManager.CreateHisto(JetEta_mumumu_afterjetsel, "JetEta_mumumu_afterjetsel", datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_mumue_afterjetsel,  "JetEta_mumue_afterjetsel",  datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eemu_afterjetsel,   "JetEta_eemu_afterjetsel",   datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eee_afterjetsel,    "JetEta_eee_afterjetsel",    datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  
  MyhistoManager.CreateHisto(JetEta_mumumu_afterbjetsel, "JetEta_mumumu_afterbjetsel", datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_mumue_afterbjetsel,  "JetEta_mumue_afterbjetsel",  datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eemu_afterbjetsel,   "JetEta_eemu_afterbjetsel",   datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  MyhistoManager.CreateHisto(JetEta_eee_afterbjetsel,    "JetEta_eee_afterbjetsel",    datasetName, "JetEta", "Entries",26, -2.5, 2.5 );
  
 
  
  MyhistoManager.CreateHisto(HT_mumumu_afterleptsel, "HT_mumumu_afterleptsel", datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_mumue_afterleptsel,  "HT_mumue_afterleptsel",  datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eemu_afterleptsel,   "HT_eemu_afterleptsel",   datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eee_afterleptsel,    "HT_eee_afterleptsel",    datasetName, "HT", "Entries",350,0., 1000);
  
  
  MyhistoManager.CreateHisto(HT_mumumu_afterjetsel, "HT_mumumu_afterjetsel", datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_mumue_afterjetsel,  "HT_mumue_afterjetsel",  datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eemu_afterjetsel,   "HT_eemu_afterjetsel",   datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eee_afterjetsel,    "HT_eee_afterjetsel",    datasetName, "HT", "Entries",350,0., 1000);
  
  MyhistoManager.CreateHisto(HT_mumumu_afterbjetsel, "HT_mumumu_afterbjetsel", datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_mumue_afterbjetsel,  "HT_mumue_afterbjetsel",  datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eemu_afterbjetsel,   "HT_eemu_afterbjetsel",   datasetName, "HT", "Entries",350,0., 1000);
  MyhistoManager.CreateHisto(HT_eee_afterbjetsel,    "HT_eee_afterbjetsel",    datasetName, "HT", "Entries",350,0., 1000);
  
  
  
  MyhistoManager.CreateHisto(MET_mumumu_afterleptsel, "MET_mumumu_afterleptsel", datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_mumue_afterleptsel,  "MET_mumue_afterleptsel",  datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eemu_afterleptsel,   "MET_eemu_afterleptsel",   datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eee_afterleptsel,    "MET_eee_afterleptsel",    datasetName, "MET", "Entries",100,0., 500);
  
  
  MyhistoManager.CreateHisto(MET_mumumu_afterjetsel, "MET_mumumu_afterjetsel", datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_mumue_afterjetsel,  "MET_mumue_afterjetsel",  datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eemu_afterjetsel,   "MET_eemu_afterjetsel",   datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eee_afterjetsel,    "MET_eee_afterjetsel",    datasetName, "MET", "Entries",100,0., 500);
  
  MyhistoManager.CreateHisto(MET_mumumu_afterbjetsel, "MET_mumumu_afterbjetsel", datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_mumue_afterbjetsel,  "MET_mumue_afterbjetsel",  datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eemu_afterbjetsel,   "MET_eemu_afterbjetsel",   datasetName, "MET", "Entries",100,0., 500);
  MyhistoManager.CreateHisto(MET_eee_afterbjetsel,    "MET_eee_afterbjetsel",    datasetName, "MET", "Entries",100,0., 500);
  
   
  MyhistoManager.CreateHisto(Asym_mumumu_afterbjetsel, "Asym_mumumu_afterbjetsel", datasetName, "Asym", "Entries", 20, -3.2, 3.2);
  MyhistoManager.CreateHisto(Asym_mumue_afterbjetsel , "Asym_mumue_afterbjetsel" , datasetName, "Asym", "Entries", 20, -3.2, 3.2);
  MyhistoManager.CreateHisto(Asym_eemu_afterbjetsel  , "Asym_eemu_afterbjetsel"  , datasetName, "Asym", "Entries", 20, -3.2, 3.2);
  MyhistoManager.CreateHisto(Asym_eee_afterbjetsel   , "Asym_eee_afterbjetsel"   , datasetName, "Asym", "Entries", 20, -3.2, 3.2);
  
  MyhistoManager.CreateHisto(RecoPtZ_mumumu_afterbjetsel, "RecoPtZ_mumumu_afterbjetsel", datasetName, "RecoPtZ", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto(RecoPtZ_mumue_afterbjetsel , "RecoPtZ_mumue_afterbjetsel" , datasetName, "RecoPtZ", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto(RecoPtZ_eemu_afterbjetsel  , "RecoPtZ_eemu_afterbjetsel"  , datasetName, "RecoPtZ", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto(RecoPtZ_eee_afterbjetsel   , "RecoPtZ_eee_afterbjetsel"   , datasetName, "RecoPtZ", "Entries", 200, 0, 500);
  
  MyhistoManager.CreateHisto( RecoTopMass_mumumu_afterbjetsel, "RecoTopMass_mumumu_afterbjetsel", datasetName, "TopMass", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto( RecoTopMass_mumue_afterbjetsel,  "RecoTopMass_mumue_afterbjetsel" , datasetName, "TopMass", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto( RecoTopMass_eemu_afterbjetsel,   "RecoTopMass_eemu_afterbjetsel"  , datasetName, "TopMass", "Entries", 200, 0, 500);
  MyhistoManager.CreateHisto( RecoTopMass_eee_afterbjetsel,    "RecoTopMass_eee_afterbjetsel"   , datasetName, "TopMass", "Entries", 200, 0, 500);
  
  
  MyhistoManager.CreateHisto(deltaPhilb_mumumu_afterbjetsel ,"deltaPhilb_mumumu_afterbjetsel", datasetName, "deltaPhilb", "Entries", 200, 0, 3.2);
  MyhistoManager.CreateHisto(deltaPhilb_mumue_afterbjetsel  ,"deltaPhilb_mumue_afterbjetsel", datasetName, "deltaPhilb", "Entries", 200, 0, 3.2);
  MyhistoManager.CreateHisto(deltaPhilb_eemu_afterbjetsel   ,"deltaPhilb_eemu_afterbjetsel", datasetName, "deltaPhilb", "Entries", 200, 0, 3.2);
  MyhistoManager.CreateHisto(deltaPhilb_eee_afterbjetsel    ,"deltaPhilb_eee_afterbjetsel", datasetName, "deltaPhilb", "Entries", 200, 0, 3.2);

  
  //**********************
  //initiate 2D histograms
  //**********************
  
  MyhistoManager.CreateHisto2D(HT_vs_MET_mumumu_afterleptsel, "HT_vs_MET_mumumu_afterleptsel", datasetName, "HT",100,0., 1000., "MET",  100,0., 1000.)  ;
  MyhistoManager.CreateHisto2D(HT_vs_MET_mumue_afterleptsel , "HT_vs_MET_mumue_afterleptsel", datasetName, "HT", 100,0., 1000., "MET",  100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_MET_eemu_afterleptsel  , "HT_vs_MET_eemu_afterleptsel",  datasetName, "HT", 100,0., 1000., "MET",  100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_MET_eee_afterleptsel   , "HT_vs_MET_eee_afterleptsel",   datasetName, "HT", 100,0., 1000., "MET",  100,0., 1000.);
  
  MyhistoManager.CreateHisto2D(HT_vs_NJet_mumumu_afterleptsel, "HT_vs_NJet_mumumu_afterleptsel", datasetName, "HT", 100,0., 1000,"Njets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NJet_mumue_afterleptsel , "HT_vs_NJet_mumue_afterleptsel",  datasetName, "HT", 100,0., 1000,"Njets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NJet_eemu_afterleptsel  , "HT_vs_NJet_eemu_afterleptsel",   datasetName, "HT", 100,0., 1000,"Njets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NJet_eee_afterleptsel   , "HT_vs_NJet_eee_afterleptsel",    datasetName, "HT", 100,0., 1000,"Njets", 5,-0.5,4.5);
  
  MyhistoManager.CreateHisto2D(HT_vs_NBJet_mumumu_afterleptsel, "HT_vs_NBJet_mumumu_afterleptsel", datasetName, "HT", 100,0., 1000,"NBjets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NBJet_mumue_afterleptsel , "HT_vs_NBJet_mumue_afterleptsel",  datasetName, "HT", 100,0., 1000,"NBjets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NBJet_eemu_afterleptsel  , "HT_vs_NBJet_eemu_afterleptsel",   datasetName, "HT", 100,0., 1000,"NBjets", 5,-0.5,4.5);
  MyhistoManager.CreateHisto2D(HT_vs_NBJet_eee_afterleptsel   , "HT_vs_NBJet_eee_afterleptsel",    datasetName, "HT", 100,0., 1000,"NBjets", 5,-0.5,4.5);
  
  MyhistoManager.CreateHisto2D(HT_vs_LeptPt_mumumu_afterleptsel, "HT_vs_LeptPt_mumumu_afterleptsel", datasetName, "HT", 100,0., 1000, "LeptPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_LeptPt_mumue_afterleptsel , "HT_vs_LeptPt_mumue_afterleptsel",  datasetName, "HT", 100,0., 1000, "LeptPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_LeptPt_eemu_afterleptsel  , "HT_vs_LeptPt_eemu_afterleptsel",   datasetName, "HT", 100,0., 1000, "LeptPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_LeptPt_eee_afterleptsel   , "HT_vs_LeptPt_eee_afterleptsel",    datasetName, "HT", 100,0., 1000, "LeptPt",100,0., 1000.);
  
  MyhistoManager.CreateHisto2D(HT_vs_JetPt_mumumu_afterleptsel, "HT_vs_JetPt_mumumu_afterleptsel", datasetName, "HT", 100,0., 1000, "JetPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_JetPt_mumue_afterleptsel  , "HT_vs_JetPt_mumue_afterleptsel",   datasetName, "HT", 100,0., 1000, "JetPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_JetPt_eemu_afterleptsel   , "HT_vs_JetPt_eemu_afterleptsel",    datasetName, "HT", 100,0., 1000, "JetPt",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_JetPt_eee_afterleptsel    , "HT_vs_JetPt_eee_afterleptsel",     datasetName, "HT", 100,0., 1000, "JetPt",100,0., 1000.);
  
  
  MyhistoManager.CreateHisto2D(HT_vs_Mll_mumumu_afterleptsel, "HT_vs_Mll_mumumu_afterleptsel", datasetName, "HT", 100,0., 1000, "Mll",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_Mll_mumue_afterleptsel  , "HT_vs_Mll_mumue_afterleptsel",   datasetName, "HT", 100,0., 1000, "Mll",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_Mll_eemu_afterleptsel   , "HT_vs_Mll_eemu_afterleptsel",    datasetName, "HT", 100,0., 1000, "Mll",100,0., 1000.);
  MyhistoManager.CreateHisto2D(HT_vs_Mll_eee_afterleptsel    , "HT_vs_Mll_eee_afterleptsel",     datasetName, "HT", 100,0., 1000, "Mll",100,0., 1000.);
  
  
  
  
  
  
  
  TString treename = "Ttree_"+datasetName;
  
  TheTree = new TTree(treename.Data(),treename.Data());
  TheTree->Branch("tree_topMass",     &tree_topMass,     "tree_topMass/F"   );
  TheTree->Branch("tree_deltaPhilb",  &tree_deltaPhilb,  "tree_deltaPhilb/F");
  TheTree->Branch("tree_asym",        &tree_asym,        "tree_asym/F"      );
  TheTree->Branch("tree_Zpt",         &tree_Zpt,         "tree_Zpt/F"       );
  TheTree->Branch("tree_EvtWeight",   &tree_EvtWeight,   "tree_EvtWeight/F" );
  TheTree->Branch("tree_SampleType",  &tree_SampleType,  "tree_SampleType/I");
  TheTree->Branch("tree_Channel",     &tree_Channel,     "tree_Channel/I"   );
  
  
  
  
  
  
  
  
  
  
  
  if (IReweight ) {
    
    if(datasetName == "DYToLL_M10-50" || datasetName == "FCNCkut" ){
      string datafile = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/PUdata.root";
      string mcfile   = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/PU3DMC_Fall11.root";
      
      LumiWeights    = new reweight::LumiReWeighting(mcfile, datafile, "histoMCPU", "pileup" );
    }
    else{
      string datafile = "";
      if(!IReweight_puUp && !IReweight_puDown){
	datafile = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/default73.5mb.root";
      }
      
      if( IReweight_puUp)   datafile = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/default73.5mbUp.root";
      if( IReweight_puDown) datafile = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/default73.5mbDown.root";
      
      string mcfile   = "/opt/sbg/data/data1/cms/jandrea/TopIPHC_2012_01_25/CMSSW_4_2_8_patch7/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/PU3DMC.root";
      
      LumiWeights    = new reweight::LumiReWeighting(mcfile, datafile, "histoMCPU", "pileup" );
      if(!IReweight_puUp && !IReweight_puDown)  LumiWeights->weight3D_init( 1. );
      if( IReweight_puDown                   )  LumiWeights->weight3D_init( 1. );
      if( IReweight_puUp                     )  LumiWeights->weight3D_init( 1. );
      
    }
  }
  
  JEC_L2L3Residuals.LoadCorrections();

  //************************************
  
  //cout << "618 " <<  endl;
  //--------------------------------------//
  //   Output file 	
  //--------------------------------------//
  //retrieve info from the input:
  TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE");
  //this file will be THE file which will contains all the histograms
  fProofFile = new TProofOutputFile(out->GetTitle());
  // Open the file
  TDirectory *savedir = gDirectory;
  fFile = fProofFile->OpenFile("UPDATE");
  if (fFile && fFile->IsZombie()) SafeDelete(fFile);
  savedir->cd();
  
  
  //this file is very important !!!
  fFile->Write();
  //It is required to add in fOutput the histos you want to feedback
  //fOutput->Add(fHist);
  fOutput->Add(fFile);
  cout << "end SlaveBegin " << endl;
}

//_____________________________________________________________________________
Bool_t ProofSelectorMyCutFlow::Process(Long64_t entry)
{
  
  //---------------------------------------------------//
  // Main event loop: get entry
  //---------------------------------------------------//
  fChain->GetTree()->GetEntry(entry); 
  branch->GetEntry(entry);
  
  IPHCTree::NTTransient::InitializeAfterReading(event);

  bool isData = false;    
  if(datasetName=="DataEG" || datasetName=="DataMu" || 
     datasetName=="DataMuEG" || datasetName=="DataEGMu" ||
     datasetName=="MET1" || datasetName=="MET2") isData = true;
  if(isData) JEC_L2L3Residuals.ApplyCorrections(event); // n'appliquer la correction que pour les donnees
    
  // cout << "line 646 " << endl;
  
  //---------------------------------------------------//
  //         Doing the analysis event by event
  //---------------------------------------------------//
  int debugcc=1000;
  int maxdebugcc=10;
  //cout<<"Entry "<<entry<<endl;
  sel.LoadEvent(event);
  // cout << "Evt loaded " << endl;
  
  //Collection of selected objects
  vector<NTVertex>   selVertices  = sel.GetSelectedVertex();
  // cout << "Vertices loaded " << endl;
  // cout<<sel.GetPointer2Electrons()<<endl;
  vector<IPHCTree::NTElectron> selElectrons = sel.GetSelectedElectrons();
  // cout << "Electrons loaded " << endl;
  vector<NTMuon>     selMuons     = sel.GetSelectedMuons();
  // cout << "Muons loaded " << endl;
  
  vector<NTElectron> selElectronsNonIso = sel.GetSelectedElectronsNoIso();
  // cout << "No iso electrons loaded " << endl;
  vector<NTMuon>     selMuonsNonIso     = sel.GetSelectedMuonsNoIso();
  // cout << "No iso muons loaded " << endl;
  
  vector<NTElectron> ZeeCand; 
  vector<NTMuon>     ZmumuCand; 
  
  vector<NTElectron> WeCand; 
  vector<NTMuon>     WmuCand; 
 
  NTMET met			   = sel.GetMET(); 
  // cout << "MET loaded " << endl;

  tree_topMass	  = -100000;
  tree_deltaPhilb = -100000;
  tree_asym	  = -100000;
  tree_Zpt	  = -100000;
  tree_SampleType = -100000;
  tree_Channel    = -100000;
  tree_EvtWeight  = -100000;

  
 
  double Dweight[101];
  for(int k1=0; k1<101; k1++) {
    Dweight[k1] = 0.;
  }   
  
   
  double weightITypeMC_save = Luminosity*dataset->Xsection()/dataset->getNSkimmedEvent();
  double weightITypeMC=0;
  
  
  //*****************************************************************
  // Loop over the datasets (lepton pairs which triggered the events)
  //*****************************************************************
  
  double EventYieldWeightError = 0;
  
  // cout << "line 686 " << endl;
  for (int IChannel=0; IChannel<4; IChannel++) {
    //      for (int IChannel=1; IChannel<2; IChannel++) {
    string ChannelName = "";
    if      (IChannel==0) ChannelName= "mumumu"; 
    else if (IChannel==1) ChannelName= "mumue" ; 
    else if (IChannel==2) ChannelName= "eemu"  ;  
    else if (IChannel==3) ChannelName= "eee"   ; 
    
    if (IChannel==0 && (datasetName=="DataEG" || datasetName=="DataMuEG")) continue;
    if (IChannel==1 && (datasetName=="DataEG" || datasetName=="DataMu")  ) continue;
    if (IChannel==2 && (datasetName=="DataMu" || datasetName=="DataEG")  ) continue;
    if (IChannel==3 && (datasetName=="DataMu" || datasetName=="DataMuEG")) continue;
   
    
    
    //*****************************************************************
    // calcul the MC weights
    //*****************************************************************    
    if ( datasetName!="DataEG"   && datasetName!="DataMu" && 
	 datasetName!="DataMuEG" && datasetName!="DataEGMu" 
	 && datasetName!="MET1"  && datasetName!="MET2") {
      
      
      if(IReweight ){
	
	
	if(datasetName != "DYToLL_M10-50" && datasetName != "FCNCkut" ){
	  weightITypeMC = weightITypeMC_save*LumiWeights->weight3D(event->pileup.before_npu, event->pileup.intime_npu, event->pileup.after_npu);
	}               
	if( datasetName == "DYToLL_M10-50" || datasetName == "FCNCkut")  {
	  double ave_npu = (event->pileup.before_npu+event->pileup.intime_npu+event->pileup.after_npu)/3.;
	  weightITypeMC = weightITypeMC_save*LumiWeights->ITweight3BX(ave_npu);
	}
	
	
      }
      else weightITypeMC = weightITypeMC_save;
    }
    else weightITypeMC = 1;
    
    
    //*****************************************************************
    // determine top decay channel
    //*****************************************************************    
    
    bool IsTTbarDilept = false;
    bool IsSignal = false;
    double WeightForBranchingRatio = 1.;
    bool IsLJ = false;
    
    
    //cout << "line 737 " << endl;
    if ( datasetName=="TTbar" ) {
      
      if ( IChannel==0) { // "mumu" 
	if ( event->mc.TMEME==20 || event->mc.TMEME==11010 || event->mc.TMEME==22000 )    IsTTbarDilept = true;
	if ( !(event->mc.TMEME==20 || event->mc.TMEME==11010 || event->mc.TMEME==22000) ) IsTTbarDilept = false;
      }      
      else if ( IChannel==1) {  // "ee" 
	if ( event->mc.TMEME==2 || event->mc.TMEME==10101 || event->mc.TMEME==20200 )     IsTTbarDilept = true;
	if ( !(event->mc.TMEME==2 || event->mc.TMEME==10101 || event->mc.TMEME==20200) )  IsTTbarDilept = false;
      }      
      else if ( IChannel==2) { // "emu" 
	if ( event->mc.TMEME==11 || event->mc.TMEME==21100 || event->mc.TMEME==11001 || event->mc.TMEME==10110 )     IsTTbarDilept = true;
	if ( !(event->mc.TMEME==11 || event->mc.TMEME==21100 || event->mc.TMEME==11001 || event->mc.TMEME==10110) )  IsTTbarDilept = false;
      }      
      if ( !IsTTbarDilept && event->mc.TMEME!=0 )     IsLJ = true;
      if ( IsTTbarDilept ) {
        WeightForBranchingRatio = SF_BranchingRatio_ll;
      } else {
        if ( event->mc.TMEME==0 ){
	  WeightForBranchingRatio = SF_BranchingRatio_had;
	} else{
	  WeightForBranchingRatio = SF_BranchingRatio_lj;
	} 
      } 
      
    }
    
    
    //cout << "line 766 " << endl;
    //*****************************************************************
    // fill cutflow before any selection
    //*****************************************************************    
    
    
    
    if ( datasetName=="TTbar" ) { 
      //cout << " Dweight[ITypeMC] 689 " <<weightITypeMC_save << "  ITypeMC " << ITypeMC << endl;
      ITypeMC = 1; 
      Dweight[ITypeMC]= weightITypeMC * WeightForBranchingRatio;
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];


      
      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
      //cout << " weightITypeMC " << weightITypeMC << " Dweight[ITypeMC] 693 " << Dweight[ITypeMC]<< "  ITypeMC " << ITypeMC << endl;
    }
    
    else if ( datasetName=="Zjets" || datasetName=="DYToLL_M10-50"
	      ) { 
      ITypeMC = 2; IsSignal = false; Dweight[ITypeMC]= weightITypeMC;  
      
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];
      
      

      
      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
    }
    else if (  datasetName=="Wjets"  ) { 
      ITypeMC = 3; IsSignal = false;  Dweight[ITypeMC]= weightITypeMC; 
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];
      
      
 
      
      
      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
    }
    else if ( datasetName=="SingleToptW" || datasetName=="TtW" || datasetName=="TbartW"
	      || datasetName=="TtWScaleUp" || datasetName=="TtWScaleDown"
	      || datasetName=="TbartWScaleUp" || datasetName=="TbartWScaleDown"
	      ) { 
      ITypeMC = 4; IsSignal = false;  Dweight[ITypeMC]= weightITypeMC; 
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];
      
      
 
      
      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
    }
    else if ( datasetName=="WZ" || datasetName=="WW" || datasetName=="ZZ"  || datasetName=="VV") { 
      ITypeMC = 5; IsSignal = false;  Dweight[ITypeMC]= weightITypeMC; 
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];

      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
     
    }  else if ( datasetName=="FCNCkut") { 
      ITypeMC = 6; IsSignal = false;  Dweight[ITypeMC]= weightITypeMC; 
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];

      //TabFlow1[IChannel][ITypeMC][0]+=Dweight[ITypeMC];
      //TabFlow2[IChannel][ITypeMC][0]+=Dweight[ITypeMC]*Dweight[ITypeMC];
     
    }
    
    //cout << "834 " << endl;
    if ( datasetName=="DataEG" || datasetName=="DataMu" || 
	 datasetName=="DataMuEG" || datasetName=="DataEGMu" ||
	 datasetName=="MET1" || datasetName=="MET2") { 
      ITypeMC = 100;  Dweight[ITypeMC]= weightITypeMC; 
      EventYieldWeightError = Dweight[ITypeMC]*Dweight[ITypeMC];   
      
      
    }
    
    //cout << "line 648 " << endl;
    //*****************************************************************
    // determine lepton scale factors
    //*****************************************************************    
    
    
    if(ApplyLeptonSF){
      //to be updated for 3 leptons selection
    }
   
    //cout << "line 854  " << endl;
    //*****************************************************************
    // pass trigger selection
    //*****************************************************************   
    
    bool passtrigger = false;
    
    if(ChannelName == "mumumu" ) passtrigger = sel.passTriggerSelection ( dataset, "mumu");
    if(ChannelName == "mumue"  ) passtrigger = sel.passTriggerSelection ( dataset, "emu" );
    if(ChannelName == "eemu"   ) passtrigger = sel.passTriggerSelection ( dataset, "emu" );
    if(ChannelName == "eee"    ) passtrigger = sel.passTriggerSelection ( dataset, "ee"  );
    
    
    if (   passtrigger   ) {
      //cout << "line 859, pass trigger selection " << endl;
      if(IChannel == 0) MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 0, datasetName, IsSignal, Dweight[ITypeMC]);
      if(IChannel == 1) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 0, datasetName, IsSignal, Dweight[ITypeMC]);
      if(IChannel == 2) MyhistoManager.FillHisto(CutFlow_eemu,	 "CutFlow_eemu"  , 0, datasetName, IsSignal, Dweight[ITypeMC]);
      if(IChannel == 3) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 0, datasetName, IsSignal, Dweight[ITypeMC]);
      if(IChannel == 0) MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu" , 0, datasetName, IsSignal, EventYieldWeightError);
      if(IChannel == 1) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"  , 0, datasetName, IsSignal, EventYieldWeightError);
      if(IChannel == 2) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"   , 0, datasetName, IsSignal, EventYieldWeightError);
      if(IChannel == 3) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"    , 0, datasetName, IsSignal, EventYieldWeightError);
	
      
      //*****************************************************************
      // pass 3 lepton requirements
      //*****************************************************************    
      
      
      //*****************************************************************
      // select Z->ee candidate
      //*****************************************************************    
      
      ZeeCand.clear(); 
      ZmumuCand.clear(); 
  
      WeCand.clear(); 
      WmuCand.clear(); 

      if(selElectrons.size() >=2 ) {
        int theel1 = -1;
	int theel2 = -1;
	double mInv = 1000000;
	for(unsigned int iel1 = 0; iel1 < selElectrons.size(); iel1++){
	  for(unsigned int iel2 = 0; iel2 < selElectrons.size(); iel2++){
	    if(iel1 == iel2) continue;
	    TLorentzVector zeecand = selElectrons[iel1].p4 + selElectrons[iel2].p4;
	    if( fabs(zeecand.M() - 91) < fabs(mInv-91) ){
	      theel1 = iel1;
	      theel2 = iel2;
	      mInv = zeecand.M();
	    }
	  }
	}
	
	if(theel1>=0 && theel2>=0){ //JLA
	  ZeeCand.push_back(selElectrons[theel1]);
	  ZeeCand.push_back(selElectrons[theel2]);
	}
      }
         
      //*****************************************************************
      // select W->enu candidate
      //*****************************************************************    
      
      if(!useNonIsoWcand){
        for(unsigned int iel1 = 0; iel1 < selElectrons.size(); iel1++){
	  bool matchElec=false;
          for(unsigned int iel2 = 0; iel2 < ZeeCand.size(); iel2++){
             
	     if(fabs(selElectrons[iel1].p4.Pt() - ZeeCand[iel2].p4.Pt()) <  0.0001)  matchElec=true;
	   
          }
	  if(!matchElec) WeCand.push_back(selElectrons[iel1]);
        }
      }else{
        for(unsigned int iel1 = 0; iel1 < selElectronsNonIso.size(); iel1++){
	  bool matchElec=false;
          for(unsigned int iel2 = 0; iel2 < ZeeCand.size(); iel2++){
             
	     if(fabs(selElectronsNonIso[iel1].p4.Pt() - ZeeCand[iel2].p4.Pt()) <  0.0001)  matchElec=true;
	   
          }
	  if(!matchElec) WeCand.push_back(selElectronsNonIso[iel1]);
        }
      }
      

      
      //*****************************************************************
      // select Z->mumu candidate
      //*****************************************************************  
      if(selMuons.size() >=2 ) {
        int themu1 = -1;
	int themu2 = -1;
	double mInv = 1000000;
	for(unsigned int imu1 = 0; imu1 < selMuons.size(); imu1++){
	  for(unsigned int imu2 = 0; imu2 < selMuons.size(); imu2++){
	    if(imu1 == imu2) continue;
	    TLorentzVector zmumucand = selMuons[imu1].p4 + selMuons[imu2].p4;
	    if( fabs(zmumucand.M() - 91) < fabs(mInv-91) ){
	      themu1 = imu1;
	      themu2 = imu2;
	      mInv = zmumucand.M();
	    }
	  }
	}
	if(themu1>=0 && themu2>=0){ //JLA  
	  ZmumuCand.push_back(selMuons[themu1]);
	  ZmumuCand.push_back(selMuons[themu2]);
	}
         
      }
      
       
       
      //*****************************************************************
      // select W->munu candidate
      //*****************************************************************    
      
      if(!useNonIsoWcand){
        //cout << "in sel W " << endl;
        for(unsigned int imu1 = 0; imu1 < selMuons.size(); imu1++){
	  bool matchMuon = false;
          for(unsigned int imu2 = 0; imu2 < ZmumuCand.size(); imu2++){
             
	     if(fabs(selMuons[imu1].p4.Pt() - ZmumuCand[imu2].p4.Pt()) <  0.0001) matchMuon = true;
	     
          } 
	  if(!matchMuon) WmuCand.push_back(selMuons[imu1]);
        }
      }else{
        for(unsigned int imu1 = 0; imu1 < selMuonsNonIso.size(); imu1++){
	  bool matchMuon = false;
          for(unsigned int imu2 = 0; imu2 < ZmumuCand.size(); imu2++){
             
	     if(fabs(selMuonsNonIso[imu1].p4.Pt() - ZmumuCand[imu2].p4.Pt())  < 0.0001) matchMuon = true;
	 
          }
	  if(!matchMuon) WmuCand.push_back(selMuonsNonIso[imu1]);
        }
      }
      
      
      //*****************************************************************
      // apply lepton selection
      //*****************************************************************    
      
      if( (WmuCand.size()+ZmumuCand.size()+WeCand.size()+ZeeCand.size()) == 3) {
       
	string cand3leptonChannel = "";
	if( ZmumuCand.size() == 2 ) {
	  if(WmuCand.size() == 1 ) cand3leptonChannel = "mumumu";
	  if(WeCand.size()  == 1 ) cand3leptonChannel = "mumue";
	}
	
	if( ZeeCand.size() == 2 ) {
	  if(WmuCand.size() == 1 ) cand3leptonChannel = "eemu";
	  if(WeCand.size() == 1 ) cand3leptonChannel = "eee";
	}
		
	//cout << "line 921 , " << cand3leptonChannel << endl;
 	if(IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 1, datasetName, IsSignal, Dweight[ITypeMC]);
 	if(IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 1, datasetName, IsSignal, Dweight[ITypeMC]);
 	if(IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(CutFlow_eemu,   "CutFlow_eemu"  , 1, datasetName, IsSignal, Dweight[ITypeMC]);
 	if(IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 1, datasetName, IsSignal, Dweight[ITypeMC]);
 	if(IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu"  , 1, datasetName, IsSignal, EventYieldWeightError);
 	if(IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"   , 1, datasetName, IsSignal, EventYieldWeightError);
 	if(IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"    , 1, datasetName, IsSignal, EventYieldWeightError);
 	if(IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"     , 1, datasetName, IsSignal, EventYieldWeightError);
	
	 //ccout << "line 935" << endl;
	
	//*****************************************************************
        // select Z candidate
        //*****************************************************************    
	
	
	
	double lept3_Charge = 0;
	
	TLorentzVector dilept;
	TLorentzVector lept1, lept2, lept3;
	
	string theleptpair = "";
	
	if(cand3leptonChannel == "mumue") {
	  lept1 = ZmumuCand[0].p4;
	  lept2 = ZmumuCand[1].p4;
	  lept3 = WeCand[0].p4;
	  lept3_Charge= WeCand[0].charge;
	  dilept = lept1+lept2;
	}
	
	
	if(cand3leptonChannel == "eemu") {
	  lept1 = ZeeCand[0].p4;
	  lept2 = ZeeCand[1].p4;
	  lept3 = WmuCand[0].p4;
	  lept3_Charge= WmuCand[0].charge;
	  dilept = lept1+lept2;
	}
	
	if(cand3leptonChannel == "mumumu") {
	  
	  lept1 = ZmumuCand[0].p4;
	  lept2 = ZmumuCand[1].p4;
	  lept3 = WmuCand[0].p4;
	  lept3_Charge= WmuCand[0].charge;
	  dilept = lept1+lept2;
	  
	}
	
	if(cand3leptonChannel == "eee") {
	  
	  lept1 = ZeeCand[0].p4;
	  lept2 = ZeeCand[1].p4;
	  lept3 = WeCand[0].p4;
	  lept3_Charge= WeCand[0].charge;
	  dilept = lept1+lept2;
	  
	}
	
	
	
	
	
	
        //cout << "line 1025" << endl;
	vector<NTJet>      selJets = sel.GetSelectedJets(selMuons, selElectrons);
	double dileptonIvM = dilept.M();
	
	double sumPtLeptJet = lept1.Pt() + lept2.Pt() + lept3.Pt();
	for(unsigned int i=0 ; i< selJets.size(); i++) sumPtLeptJet += selJets[i].p4.Pt();
	double theMET = met.p2.Mod();
		
	int NBtaggedJets = 0;
	int idxBtag      = 0;
	int AlgoBtag = sel.GetbtagAlgo();
	float btagDiscriCut = sel.GetbtagDiscriCut ();
	//cout << "***********************" << endl;
	for(unsigned int ijet = 0; ijet < selJets.size(); ijet++){
	  
	  if ( AlgoBtag==0 &&  selJets[ijet].bTag["trackCountingHighEffBJetTags"]	  >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==1 &&  selJets[ijet].bTag["simpleSecondaryVertexHighEffBJetTags"]    >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==2 &&  selJets[ijet].bTag["trackCountingHighPurBJetTags"]	  >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==3 &&  selJets[ijet].bTag["simpleSecondaryVertexHighPurBJetTags"]    >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==4 &&  selJets[ijet].bTag["jetProbabilityBJetTags"]		  >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==5 &&  selJets[ijet].bTag["jetBProbabilityBJetTags"]		  >= btagDiscriCut) NBtaggedJets++;
	  if ( AlgoBtag==6 &&  selJets[ijet].bTag["combinedSecondaryVertexBJetTags"]	  >= btagDiscriCut){
	     NBtaggedJets++;
	     idxBtag = ijet;
	  }
	
	  //cout << "jet " << ijet << " has a flavor " << selJets[ijet].partonFlavour << endl;
	  //cout << "NBtaggedJets " << NBtaggedJets << endl;
	}  
	
	
	if(IChannel == 0 && cand3leptonChannel == "mumumu"){
	
	  MyhistoManager.FillHisto(InvM_ll_mumumu_afterleptsel, "InvM_ll_mumumu_afterleptsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptZPt_mumumu_afterleptsel, "LeptZPt_mumumu_afterleptsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptZPt_mumumu_afterleptsel, "LeptZPt_mumumu_afterleptsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptWPt_mumumu_afterleptsel, "LeptWPt_mumumu_afterleptsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  
	  MyhistoManager.FillHisto(HT_mumumu_afterleptsel, "HT_mumumu_afterleptsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(MET_mumumu_afterleptsel, "MET_mumumu_afterleptsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  for(unsigned int i=0 ; i< selJets.size(); i++){ 
	    MyhistoManager.FillHisto(JetPt_mumumu_afterleptsel, "JetPt_mumumu_afterleptsel",selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	    MyhistoManager.FillHisto(JetEta_mumumu_afterleptsel, "JetEta_mumumu_afterleptsel",selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	    MyhistoManager.FillHisto2D(HT_vs_JetPt_mumumu_afterleptsel  ,"HT_vs_JetPt_mumumu_afterleptsel"  , sumPtLeptJet, selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  }
	  MyhistoManager.FillHisto2D(HT_vs_MET_mumumu_afterleptsel    ,"HT_vs_MET_mumumu_afterleptsel"    , sumPtLeptJet, theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NJet_mumumu_afterleptsel   ,"HT_vs_NJet_mumumu_afterleptsel"   , sumPtLeptJet, selJets.size(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NBJet_mumumu_afterleptsel  ,"HT_vs_NBJet_mumumu_afterleptsel"  , sumPtLeptJet, NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumumu_afterleptsel ,"HT_vs_LeptPt_mumumu_afterleptsel" , sumPtLeptJet, lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumumu_afterleptsel ,"HT_vs_LeptPt_mumumu_afterleptsel" , sumPtLeptJet, lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumumu_afterleptsel ,"HT_vs_LeptPt_mumumu_afterleptsel" , sumPtLeptJet, lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  if(selJets.size() == 1 && dilept.M() > 20) MyhistoManager.FillHisto2D(HT_vs_Mll_mumumu_afterleptsel	,"HT_vs_Mll_mumumu_afterleptsel"   , sumPtLeptJet, dilept.M(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	}
        if(IChannel == 1 && cand3leptonChannel == "mumue" ){
	
	  MyhistoManager.FillHisto(InvM_ll_mumue_afterleptsel,  "InvM_ll_mumue_afterleptsel",  dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);	  
	  
	  MyhistoManager.FillHisto(LeptZPt_mumue_afterleptsel, "LeptZPt_mumue_afterleptsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptZPt_mumue_afterleptsel, "LeptZPt_mumue_afterleptsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptWPt_mumue_afterleptsel, "LeptWPt_mumue_afterleptsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  MyhistoManager.FillHisto(HT_mumue_afterleptsel, "HT_mumue_afterleptsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(MET_mumue_afterleptsel, "MET_mumue_afterleptsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  for(unsigned int i=0 ; i< selJets.size(); i++){
	   MyhistoManager.FillHisto(JetPt_mumue_afterleptsel, "JetPt_mumue_afterleptsel",
	  selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	   MyhistoManager.FillHisto(JetEta_mumue_afterleptsel, "JetEta_mumue_afterleptsel",
	  selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	    MyhistoManager.FillHisto2D(HT_vs_JetPt_mumue_afterleptsel  ,"HT_vs_JetPt_mumue_afterleptsel"  , sumPtLeptJet, selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  }
	  
	  MyhistoManager.FillHisto2D(HT_vs_MET_mumue_afterleptsel    ,"HT_vs_MET_mumue_afterleptsel"    , sumPtLeptJet, theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NJet_mumue_afterleptsel   ,"HT_vs_NJet_mumue_afterleptsel"   , sumPtLeptJet, selJets.size(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NBJet_mumue_afterleptsel  ,"HT_vs_NBJet_mumue_afterleptsel"  , sumPtLeptJet, NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumue_afterleptsel ,"HT_vs_LeptPt_mumue_afterleptsel" , sumPtLeptJet, lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumue_afterleptsel ,"HT_vs_LeptPt_mumue_afterleptsel" , sumPtLeptJet, lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_mumue_afterleptsel ,"HT_vs_LeptPt_mumue_afterleptsel" , sumPtLeptJet, lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  if(selJets.size() == 1 && dilept.M() > 20) MyhistoManager.FillHisto2D(HT_vs_Mll_mumue_afterleptsel   ,"HT_vs_Mll_mumue_afterleptsel"   , sumPtLeptJet, dilept.M(), datasetName, IsSignal, Dweight[ITypeMC]);
	
	  
	}
        if(IChannel == 2 && cand3leptonChannel == "eemu"  ){ 
	
	  MyhistoManager.FillHisto(InvM_ll_eemu_afterleptsel,   "InvM_ll_eemu_afterleptsel",   dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);  
	  
	  MyhistoManager.FillHisto(LeptZPt_eemu_afterleptsel, "LeptZPt_eemu_afterleptsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptZPt_eemu_afterleptsel, "LeptZPt_eemu_afterleptsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptWPt_eemu_afterleptsel, "LeptWPt_eemu_afterleptsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  MyhistoManager.FillHisto(HT_eemu_afterleptsel, "HT_eemu_afterleptsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(MET_eemu_afterleptsel, "MET_eemu_afterleptsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  for(unsigned int i=0 ; i< selJets.size(); i++){
	   MyhistoManager.FillHisto(JetPt_eemu_afterleptsel, "JetPt_eemu_afterleptsel",
	  selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	   MyhistoManager.FillHisto(JetEta_eemu_afterleptsel, "JetEta_eemu_afterleptsel",
	  selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
           MyhistoManager.FillHisto2D(HT_vs_JetPt_eemu_afterleptsel  ,"HT_vs_JetPt_eemu_afterleptsel"  , sumPtLeptJet, selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
  
	  }
          
	  MyhistoManager.FillHisto2D(HT_vs_MET_eemu_afterleptsel    ,"HT_vs_MET_eemu_afterleptsel"    , sumPtLeptJet, theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NJet_eemu_afterleptsel   ,"HT_vs_NJet_eemu_afterleptsel"   , sumPtLeptJet, selJets.size(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NBJet_eemu_afterleptsel  ,"HT_vs_NBJet_eemu_afterleptsel"  , sumPtLeptJet, NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eemu_afterleptsel ,"HT_vs_LeptPt_eemu_afterleptsel" , sumPtLeptJet, lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eemu_afterleptsel ,"HT_vs_LeptPt_eemu_afterleptsel" , sumPtLeptJet, lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eemu_afterleptsel ,"HT_vs_LeptPt_eemu_afterleptsel" , sumPtLeptJet, lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  if(selJets.size() == 1 && dilept.M() > 20) MyhistoManager.FillHisto2D(HT_vs_Mll_eemu_afterleptsel   ,"HT_vs_Mll_eemu_afterleptsel"   , sumPtLeptJet, dilept.M(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	}
	if(IChannel == 3 && cand3leptonChannel == "eee"   ){ 
	
	  MyhistoManager.FillHisto(InvM_ll_eee_afterleptsel,    "InvM_ll_eee_afterleptsel",    dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  MyhistoManager.FillHisto(LeptZPt_eee_afterleptsel, "LeptZPt_eee_afterleptsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptZPt_eee_afterleptsel, "LeptZPt_eee_afterleptsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(LeptWPt_eee_afterleptsel, "LeptWPt_eee_afterleptsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  
	  MyhistoManager.FillHisto(HT_eee_afterleptsel, "HT_eee_afterleptsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto(MET_eee_afterleptsel, "MET_eee_afterleptsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  for(unsigned int i=0 ; i< selJets.size(); i++){
	   MyhistoManager.FillHisto(JetPt_eee_afterleptsel, "JetPt_eee_afterleptsel",
	  selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	   MyhistoManager.FillHisto(JetEta_eee_afterleptsel, "JetEta_eee_afterleptsel",
	  selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	   MyhistoManager.FillHisto2D(HT_vs_JetPt_eee_afterleptsel  ,"HT_vs_JetPt_eee_afterleptsel"  , sumPtLeptJet, selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
 
	  }
	  
	  MyhistoManager.FillHisto2D(HT_vs_MET_eee_afterleptsel    ,"HT_vs_MET_eee_afterleptsel"    , sumPtLeptJet, theMET, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NJet_eee_afterleptsel   ,"HT_vs_NJet_eee_afterleptsel"   , sumPtLeptJet, selJets.size(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_NBJet_eee_afterleptsel  ,"HT_vs_NBJet_eee_afterleptsel"  , sumPtLeptJet, NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eee_afterleptsel ,"HT_vs_LeptPt_eee_afterleptsel" , sumPtLeptJet, lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eee_afterleptsel ,"HT_vs_LeptPt_eee_afterleptsel" , sumPtLeptJet, lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  MyhistoManager.FillHisto2D(HT_vs_LeptPt_eee_afterleptsel ,"HT_vs_LeptPt_eee_afterleptsel" , sumPtLeptJet, lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  if(selJets.size() == 1 && dilept.M() > 20) MyhistoManager.FillHisto2D(HT_vs_Mll_eee_afterleptsel   ,"HT_vs_Mll_eee_afterleptsel"   , sumPtLeptJet, dilept.M(), datasetName, IsSignal, Dweight[ITypeMC]);
	  
	}
	
	
	
	//*****************************************************************
        // pass Z mass
        //*****************************************************************  
	
	
	
	
	if(sumPtLeptJet  > 300 && fabs(dilept.M()-91) > 15){
	  
	  if(isData){
	    /*cout << "******************************************************************* "<< endl;
	    cout << "lepton 1 pt/eta/phi " << lept1.Pt() << " " << lept1.Eta() << " " <<  lept1.Phi() << endl;
	    cout << "lepton 2 pt/eta/phi " << lept2.Pt() << " " << lept2.Eta() << " " <<  lept2.Phi() << endl;
	    cout << "lepton 3 pt/eta/phi " << lept3.Pt() << " " << lept3.Eta() << " " <<  lept3.Phi() << endl;
	    cout << "dilepton Z cand     " <<  dileptonIvM << endl; 
	    cout << "sum pT		   " << sumPtLeptJet  << endl; 
	    cout << "MET		   " <<  theMET << endl; 
	    cout << "Njets		   " <<  selJets.size() << endl; 
	    for(unsigned int i=0 ; i< selJets.size(); i++) cout << " jet " << i << " pt/eta/phi " << selJets[i].p4.Pt() << " " << selJets[i].p4.Eta() << " " <<  selJets[i].p4.Phi()
	     << "  btag discri " << selJets[i].GetDiscri(string("combinedSecondaryVertexBJetTags"))     << endl;
	    */
          }
	  if( IChannel == 0 && cand3leptonChannel == "mumumu")  MyhistoManager.FillHisto(InvM_ll_mumumu_afterleptsel_highSumPt, "InvM_ll_mumumu_afterleptsel_highSumPt", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 1 && cand3leptonChannel == "mumue" )  MyhistoManager.FillHisto(InvM_ll_mumue_afterleptsel_highSumPt,  "InvM_ll_mumue_afterleptsel_highSumPt",  dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);	  
          if( IChannel == 2 && cand3leptonChannel == "eemu"  )  MyhistoManager.FillHisto(InvM_ll_eemu_afterleptsel_highSumPt,   "InvM_ll_eemu_afterleptsel_highSumPt",   dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);  
	  if( IChannel == 3 && cand3leptonChannel == "eee"   )  MyhistoManager.FillHisto(InvM_ll_eee_afterleptsel_highSumPt,    "InvM_ll_eee_afterleptsel_highSumPt",    dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	}  
	
	
	if( fabs(dilept.M()-91) < 15){
	
 	  if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 2, datasetName, IsSignal, Dweight[ITypeMC]);
 	  if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 2, datasetName, IsSignal, Dweight[ITypeMC]);
 	  if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(CutFlow_eemu,   "CutFlow_eemu"  , 2, datasetName, IsSignal, Dweight[ITypeMC]);
 	  if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 2, datasetName, IsSignal, Dweight[ITypeMC]);
 	  if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu"  , 2, datasetName, IsSignal, EventYieldWeightError);
 	  if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"   , 2, datasetName, IsSignal, EventYieldWeightError);
 	  if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"    , 2, datasetName, IsSignal, EventYieldWeightError);
 	  if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"     , 2, datasetName, IsSignal, EventYieldWeightError);
	
	
	  
	  //*****************************************************************
	  // pass jet selection
	  //*****************************************************************  
	  int NSeljets = selJets.size() ;
	  if(NSeljets>4) NSeljets = 4;

	    
	  if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(NJet_mumumu_afterZsel , "NJet_mumumu_afterZsel",NSeljets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(NJet_mumue_afterZsel  , "NJet_mumue_afterZsel" ,NSeljets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(NJet_eemu_afterZsel   , "NJet_eemu_afterZsel"  ,NSeljets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(NJet_eee_afterZsel    , "NJet_eee_afterZsel"   ,NSeljets, datasetName, IsSignal, Dweight[ITypeMC]);
	  
	  if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(NBJet_mumumu_afterZsel , "NBJet_mumumu_afterZsel",NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(NBJet_mumue_afterZsel  , "NBJet_mumue_afterZsel" ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(NBJet_eemu_afterZsel   , "NBJet_eemu_afterZsel"  ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
          if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(NBJet_eee_afterZsel    , "NBJet_eee_afterZsel"   ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	   

	  if(selJets.size() >= 1 ){

        //if( IChannel == 0 && cand3leptonChannel == "mumumu")
        // cout<<"RUN "<<event->general.runNb<<" EVT "<<event->general.eventNb<<endl;
	    	  	
 	    if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 3, datasetName, IsSignal, Dweight[ITypeMC]);
 	    if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 3, datasetName, IsSignal, Dweight[ITypeMC]);
 	    if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(CutFlow_eemu,   "CutFlow_eemu"  , 3, datasetName, IsSignal, Dweight[ITypeMC]);
 	    if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 3, datasetName, IsSignal, Dweight[ITypeMC]);
 	    if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu"  , 3, datasetName, IsSignal, EventYieldWeightError);
 	    if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"   , 3, datasetName, IsSignal, EventYieldWeightError);
 	    if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"    , 3, datasetName, IsSignal, EventYieldWeightError);
 	    if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"     , 3, datasetName, IsSignal, EventYieldWeightError);
	
		   
	    if( IChannel == 0 && cand3leptonChannel == "mumumu"){
	    
	      MyhistoManager.FillHisto(InvM_ll_mumumu_afterjetsel, "InvM_ll_mumumu_afterjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(NBJet_mumumu_afterjetsel ,  "NBJet_mumumu_afterjetsel",NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
              
	      MyhistoManager.FillHisto(LeptZPt_mumumu_afterjetsel,  "LeptZPt_mumumu_afterjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptZPt_mumumu_afterjetsel,  "LeptZPt_mumumu_afterjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptWPt_mumumu_afterjetsel,  "LeptWPt_mumumu_afterjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      
	      MyhistoManager.FillHisto(HT_mumumu_afterjetsel,      "HT_mumumu_afterjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
 	      MyhistoManager.FillHisto(MET_mumumu_afterjetsel, "MET_mumumu_afterjetsel",theMET , datasetName, IsSignal, Dweight[ITypeMC]);
              for(unsigned int i=0 ; i< selJets.size(); i++){ 
	        MyhistoManager.FillHisto(JetPt_mumumu_afterjetsel, "JetPt_mumumu_afterjetsel",
	        selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(JetEta_mumumu_afterjetsel, "JetEta_mumumu_afterjetsel",
	        selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	      }
	
	    }
	    if( IChannel == 1 && cand3leptonChannel == "mumue" ){
	      
	      MyhistoManager.FillHisto(InvM_ll_mumue_afterjetsel, "InvM_ll_mumue_afterjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	    
	      MyhistoManager.FillHisto(NBJet_mumue_afterjetsel  , "NBJet_mumue_afterjetsel" ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
              MyhistoManager.FillHisto(LeptPt_mumue_afterjetsel, "LeptPt_mumue_afterjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptPt_mumue_afterjetsel, "LeptPt_mumue_afterjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptPt_mumue_afterjetsel, "LeptPt_mumue_afterjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(HT_mumue_afterjetsel, "HT_mumue_afterjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(MET_mumue_afterjetsel, "MET_mumue_afterjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
              for(unsigned int i=0 ; i< selJets.size(); i++){
	         MyhistoManager.FillHisto(JetPt_mumue_afterjetsel, "JetPt_mumue_afterjetsel",
	      selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	         MyhistoManager.FillHisto(JetEta_mumue_afterjetsel, "JetEta_mumue_afterjetsel",
	      selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	      }

	    }
	    if( IChannel == 2 && cand3leptonChannel == "eemu"  ){
	    
	      MyhistoManager.FillHisto(InvM_ll_eemu_afterjetsel, "InvM_ll_eemu_afterjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
              MyhistoManager.FillHisto(NBJet_eemu_afterjetsel   , "NBJet_eemu_afterjetsel"  ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
              
	      MyhistoManager.FillHisto(LeptZPt_eemu_afterjetsel, "LeptZPt_eemu_afterjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptZPt_eemu_afterjetsel, "LeptZPt_eemu_afterjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptWPt_eemu_afterjetsel, "LeptWPt_eemu_afterjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      
	      MyhistoManager.FillHisto(HT_eemu_afterjetsel, "HT_eemu_afterjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(MET_eemu_afterjetsel, "MET_eemu_afterjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
              for(unsigned int i=0 ; i< selJets.size(); i++){ 
	        MyhistoManager.FillHisto(JetPt_eemu_afterjetsel, "JetPt_eemu_afterjetsel",
	        selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(JetEta_eemu_afterjetsel, "JetEta_eemu_afterjetsel",
	        selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	      }

	    }
	    
	    if( IChannel == 3 && cand3leptonChannel == "eee"   ){
	    
	      MyhistoManager.FillHisto(InvM_ll_eee_afterjetsel, "InvM_ll_eeee_afterjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(NBJet_eee_afterjetsel    , "NBJet_eee_afterjetsel"   ,NBtaggedJets, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptZPt_eee_afterjetsel, "LeptZPt_eee_afterjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptZPt_eee_afterjetsel, "LeptZPt_eee_afterjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(LeptWPt_eee_afterjetsel, "LeptWPt_eee_afterjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(HT_eee_afterjetsel, "HT_eee_afterjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	      MyhistoManager.FillHisto(MET_eee_afterjetsel, "MET_eee_afterjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
              for(unsigned int i=0 ; i< selJets.size(); i++){
	        MyhistoManager.FillHisto(JetPt_eee_afterjetsel, "JetPt_eee_afterjetsel",
	        selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(JetEta_eee_afterjetsel, "JetEta_eee_afterjetsel",
	        selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
	      }

	    }
	   
	   
    
	    if(NBtaggedJets == 1 ){
	      	  	   
	      if( IChannel == 0 && cand3leptonChannel == "mumumu"){
  
	        MyhistoManager.FillHisto(InvM_ll_mumumu_afterbjetsel, "InvM_ll_mumumu_afterbjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(LeptZPt_mumumu_afterbjetsel, "LeptZPt_mumumu_afterbjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptZPt_mumumu_afterbjetsel, "LeptZPt_mumumu_afterbjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptWPt_mumumu_afterbjetsel, "LeptWPt_mumumu_afterbjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(HT_mumumu_afterbjetsel, "HT_mumumu_afterbjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(MET_mumumu_afterbjetsel, "MET_mumumu_afterbjetsel",theMET , datasetName, IsSignal, Dweight[ITypeMC]);
                for(unsigned int i=0 ; i< selJets.size(); i++){
		  MyhistoManager.FillHisto(JetPt_mumumu_afterbjetsel, "JetPt_mumumu_afterbjetsel",
	          selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
		  MyhistoManager.FillHisto(JetEta_mumumu_afterbjetsel, "JetEta_mumumu_afterbjetsel",
	          selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
		}

	  
	      }
	      if( IChannel == 1 && cand3leptonChannel == "mumue" ){
	    
	        MyhistoManager.FillHisto(InvM_ll_mumue_afterbjetsel, "InvM_ll_mumue_afterbjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(LeptZPt_mumue_afterbjetsel, "LeptZPt_mumue_afterbjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptZPt_mumue_afterbjetsel, "LeptZPt_mumue_afterbjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptWPt_mumue_afterbjetsel, "LeptWPt_mumue_afterbjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(HT_mumue_afterbjetsel, "HT_mumue_afterbjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(MET_mumue_afterbjetsel, "MET_mumue_afterbjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
                for(unsigned int i=0 ; i< selJets.size(); i++){
		  MyhistoManager.FillHisto(JetPt_mumue_afterbjetsel, "JetPt_mumue_afterbjetsel",
	          selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
		  MyhistoManager.FillHisto(JetEta_mumue_afterbjetsel, "JetEta_mumue_afterbjetsel",
	          selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
		}


	      }
	      if( IChannel == 2 && cand3leptonChannel == "eemu"  ){
	    
	        MyhistoManager.FillHisto(InvM_ll_eemu_afterbjetsel, "InvM_ll_eemu_afterbjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(LeptZPt_eemu_afterbjetsel, "LeptZPt_eemu_afterbjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptZPt_eemu_afterbjetsel, "LeptZPt_eemu_afterbjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptWPt_eemu_afterbjetsel, "LeptWPt_eemu_afterbjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(HT_eemu_afterbjetsel, "HT_eemu_afterbjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(MET_eemu_afterbjetsel, "MET_eemu_afterbjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
                for(unsigned int i=0 ; i< selJets.size(); i++){
		  MyhistoManager.FillHisto(JetPt_eemu_afterbjetsel, "JetPt_eemu_afterbjetsel",
	          selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
		  MyhistoManager.FillHisto(JetEta_eemu_afterbjetsel, "JetEta_eemu_afterbjetsel",
	          selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
		}


	      }
	    
	      if( IChannel == 3 && cand3leptonChannel == "eee"   ){

  	        MyhistoManager.FillHisto(InvM_ll_eee_afterbjetsel, "InvM_ll_eee_afterbjetsel", dileptonIvM, datasetName, IsSignal, Dweight[ITypeMC]);	    
	        MyhistoManager.FillHisto(LeptZPt_eee_afterbjetsel, "LeptZPt_eee_afterbjetsel", lept1.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptZPt_eee_afterbjetsel, "LeptZPt_eee_afterbjetsel", lept2.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(LeptWPt_eee_afterbjetsel, "LeptWPt_eee_afterbjetsel", lept3.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(HT_eee_afterbjetsel, "HT_eee_afterbjetsel", sumPtLeptJet, datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(MET_eee_afterbjetsel, "MET_eee_afterbjetsel", theMET, datasetName, IsSignal, Dweight[ITypeMC]);
                for(unsigned int i=0 ; i< selJets.size(); i++){
		  MyhistoManager.FillHisto(JetPt_eee_afterbjetsel, "JetPt_eee_afterbjetsel",
	          selJets[i].p4.Pt(), datasetName, IsSignal, Dweight[ITypeMC]);
		  MyhistoManager.FillHisto(JetEta_eee_afterbjetsel, "JetEta_eee_afterbjetsel",
	          selJets[i].p4.Eta(), datasetName, IsSignal, Dweight[ITypeMC]);
		}


	      }  	  	

              //if( IChannel == 0 && cand3leptonChannel == "mumumu")      
                //   cout<<"RUN "<<event->general.runNb<<" EVT "<<event->general.eventNb<<endl;
	      
 	      if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 4, datasetName, IsSignal, Dweight[ITypeMC]);
 	      if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 4, datasetName, IsSignal, Dweight[ITypeMC]);
 	      if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(CutFlow_eemu,   "CutFlow_eemu"  , 4, datasetName, IsSignal, Dweight[ITypeMC]);
 	      if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 4, datasetName, IsSignal, Dweight[ITypeMC]);
 	      if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu"  , 4, datasetName, IsSignal, EventYieldWeightError);
 	      if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"   , 4, datasetName, IsSignal, EventYieldWeightError);
 	      if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"    , 4, datasetName, IsSignal, EventYieldWeightError);
 	      if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"     , 4, datasetName, IsSignal, EventYieldWeightError);
	

	      TLorentzVector metP4(met.p2.Px(), met.p2.Py(), 0, sqrt(met.p2.Px()*met.p2.Px() + met.p2.Py()*met.p2.Py()));
	      TLorentzVector transTop = lept3 + selJets[0].p4 + metP4;
	      
	      if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(Mt_mumumu_afterbtagsel, "Mt_mumumu_afterbtagsel" , transTop.Mt() ,datasetName, IsSignal, Dweight[ITypeMC]);
              if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(Mt_mumue_afterbtagsel , "Mt_mumue_afterbtagsel"  , transTop.Mt() ,datasetName, IsSignal, Dweight[ITypeMC]);
              if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(Mt_eemu_afterbtagsel  , "Mt_eemu_afterbtagsel"   , transTop.Mt() ,datasetName, IsSignal, Dweight[ITypeMC]);
              if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(Mt_eee_afterbtagsel   , "Mt_eee_afterbtagsel"    , transTop.Mt() ,datasetName, IsSignal, Dweight[ITypeMC]);
	       //cout << "line 1103" << endl;
	      
	      
	        
	       //lept3 + selJets[0].p4 + met.p4;
	       
	      double term1 = lept3.Pz()*(lept3.Px()*met.p2.Px() + lept3.Py()*met.p2.Py() + (80.399)*(80.399)/2.);
	      double det = lept3.Px()*met.p2.Px() + lept3.Py()*met.p2.Py() + (80.399)*(80.399)/2.
				- met.met()*met.met()*(lept3.E()*lept3.E() - lept3.Pz()*lept3.Pz());
	      if(det<0) det=0;
	      double term2 = lept3.E()*pow(det, 0.5);
	      double denom = lept3.E()*lept3.E() - lept3.Pz()*lept3.Pz();
	      
	      
	      double sol1 = (term1 - term2)/denom;
	      //double sol2 = (term1 + term2)/denom;
	      
	      double neutrE = pow( pow(met.p2.Px(),2) + pow(met.p2.Py(),2) + sol1*sol1, 0.5);//neglecting neut mass
	      
	      TLorentzVector neutrino;
	      neutrino.SetPxPyPzE( met.p2.Px(), met.p2.Py(), sol1, neutrE);
	      
	      TLorentzVector topCand = neutrino + lept3 + selJets[idxBtag].p4 ;
	
	      
	      
	      
	      tree_EvtWeight  = Dweight[ITypeMC];
              tree_topMass    = topCand.M();
              tree_deltaPhilb = fabs(lept3.DeltaPhi(selJets[idxBtag].p4));
              tree_asym       = lept3_Charge*fabs(lept3.Eta());
              tree_Zpt        = (lept1+lept2).Pt();
	      
	      
	      if(datasetName=="DataMu" || datasetName=="DataMu" || datasetName=="DataMuEG")  tree_SampleType   = 0;
	      if(datasetName=="FCNCkut" )        tree_SampleType   = 1;
	      if(datasetName=="TTbar" )          tree_SampleType   = 2;
	      if(datasetName=="DYToLL_M10-50" )  tree_SampleType   = 3;
	      if(datasetName=="Zjets" )          tree_SampleType   = 4;
	      if(datasetName=="Wjets" )          tree_SampleType   = 5;
	      if(datasetName=="TtW" )            tree_SampleType   = 6;
	      if(datasetName=="TbartW" )         tree_SampleType   = 7;
	      if(datasetName=="WZ" )             tree_SampleType   = 8;
	      if(datasetName=="ZZ" )             tree_SampleType   = 9;
	      if(datasetName=="WW" )             tree_SampleType   = 10;
	      
	      if( IChannel == 0 && cand3leptonChannel == "mumumu") {
	        tree_Channel = 0; TheTree->Fill();
		MyhistoManager.FillHisto(Asym_mumumu_afterbjetsel,       "Asym_mumumu_afterbjetsel",         tree_asym,    datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoPtZ_mumumu_afterbjetsel,     "RecoPtZ_mumumu_afterbjetsel",     tree_Zpt,     datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoTopMass_mumumu_afterbjetsel, "RecoTopMass_mumumu_afterbjetsel", tree_topMass ,datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(deltaPhilb_mumumu_afterbjetsel , "deltaPhilb_mumumu_afterbjetsel",  tree_deltaPhilb ,    datasetName, IsSignal, Dweight[ITypeMC]);

		
	      }
	      if( IChannel == 1 && cand3leptonChannel == "mumue" ) {
	        tree_Channel = 1; TheTree->Fill();
		MyhistoManager.FillHisto(Asym_mumue_afterbjetsel,         "Asym_mumue_afterbjetsel",          tree_asym,    datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoPtZ_mumue_afterbjetsel,      "RecoPtZ_mumue_afterbjetsel",       tree_Zpt,     datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoTopMass_mumue_afterbjetsel,  "RecoTopMass_mumue_afterbjetsel" ,  tree_topMass ,datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(deltaPhilb_mumue_afterbjetsel ,  "deltaPhilb_mumue_afterbjetsel",    tree_deltaPhilb ,    datasetName, IsSignal, Dweight[ITypeMC]);
 
		
	      }
	      if( IChannel == 2 && cand3leptonChannel == "eemu"  ) {
	        tree_Channel = 2; TheTree->Fill();
		MyhistoManager.FillHisto(Asym_eemu_afterbjetsel,          "Asym_eemu_afterbjetsel",           tree_asym,    datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoPtZ_eemu_afterbjetsel,       "RecoPtZ_eemu_afterbjetsel",        tree_Zpt,     datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoTopMass_eemu_afterbjetsel,   "RecoTopMass_eemu_afterbjetsel" ,   tree_topMass ,datasetName, IsSignal, Dweight[ITypeMC]);
                MyhistoManager.FillHisto(deltaPhilb_eemu_afterbjetsel ,   "deltaPhilb_eemu_afterbjetsel",     tree_deltaPhilb ,    datasetName, IsSignal, Dweight[ITypeMC]);

	      }
	      if( IChannel == 3 && cand3leptonChannel == "eee"   ) {
	        tree_Channel = 3; TheTree->Fill();
		MyhistoManager.FillHisto(Asym_eee_afterbjetsel,           "Asym_eee_afterbjetsel",            tree_asym,    datasetName, IsSignal, Dweight[ITypeMC]);
		MyhistoManager.FillHisto(RecoPtZ_eee_afterbjetsel,        "RecoPtZ_eee_afterbjetsel",         tree_Zpt,     datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(RecoTopMass_eee_afterbjetsel,    "RecoTopMass_eee_afterbjetsel" ,    tree_topMass ,datasetName, IsSignal, Dweight[ITypeMC]);
	        MyhistoManager.FillHisto(deltaPhilb_eee_afterbjetsel ,    "deltaPhilb_eee_afterbjetsel",      tree_deltaPhilb ,    datasetName, IsSignal, Dweight[ITypeMC]);
	   
		
	      }
	      
  
	      
	      
	      
	      
	      
	      
	      if(transTop.Mt() > 150){

                if( IChannel == 0 && cand3leptonChannel == "mumumu")
                   //cout<<"RUN "<<event->general.runNb<<" EVT "<<event->general.eventNb<<endl;

		if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(CutFlow_mumumu, "CutFlow_mumumu", 5, datasetName, IsSignal, Dweight[ITypeMC]);
 	        if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(CutFlow_mumue,  "CutFlow_mumue" , 5, datasetName, IsSignal, Dweight[ITypeMC]);
 	        if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(CutFlow_eemu,   "CutFlow_eemu"  , 5, datasetName, IsSignal, Dweight[ITypeMC]);
 	        if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(CutFlow_eee,    "CutFlow_eee"   , 5, datasetName, IsSignal, Dweight[ITypeMC]);
 	        if( IChannel == 0 && cand3leptonChannel == "mumumu") MyhistoManager.FillHisto(ErrCutFlow_mumumu,   "ErrCutFlow_mumumu"  , 5, datasetName, IsSignal, EventYieldWeightError);
 	        if( IChannel == 1 && cand3leptonChannel == "mumue" ) MyhistoManager.FillHisto(ErrCutFlow_mumue,    "ErrCutFlow_mumue"   , 5, datasetName, IsSignal, EventYieldWeightError);
 	        if( IChannel == 2 && cand3leptonChannel == "eemu"  ) MyhistoManager.FillHisto(ErrCutFlow_eemu,     "ErrCutFlow_eemu"    , 5, datasetName, IsSignal, EventYieldWeightError);
 	        if( IChannel == 3 && cand3leptonChannel == "eee"   ) MyhistoManager.FillHisto(ErrCutFlow_eee,      "ErrCutFlow_eee"     , 5, datasetName, IsSignal, EventYieldWeightError);
	      }
	    } // end selection btag 
	  } // end selection njet
	} //end selection Z cand    
      } // end selection 3 leptons
    } // end selection trigger
  } //end loops on datasets
  
  
  return kTRUE;
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  
  if(fProofFile) fProofFile->Print();
  if (fFile) {
    Bool_t cleanup = kFALSE;
    TDirectory *savedir = gDirectory;
    fFile->cd();
    
    
    
    
  
  MyhistoManager.WriteMyHisto(CutFlow_mumumu, "all" );
  MyhistoManager.WriteMyHisto(CutFlow_mumue,  "all" );
  MyhistoManager.WriteMyHisto(CutFlow_eemu,   "all" );
  MyhistoManager.WriteMyHisto(CutFlow_eee,    "all" );
  
  
  
  MyhistoManager.WriteMyHisto(ErrCutFlow_mumumu,  "all");
  MyhistoManager.WriteMyHisto(ErrCutFlow_mumue,   "all");
  MyhistoManager.WriteMyHisto(ErrCutFlow_eemu,    "all");
  MyhistoManager.WriteMyHisto(ErrCutFlow_eee,     "all");
  
  
  
  MyhistoManager.WriteMyHisto(Mt_mumumu_afterbtagsel, "all"); 
  MyhistoManager.WriteMyHisto(Mt_mumue_afterbtagsel , "all");
  MyhistoManager.WriteMyHisto(Mt_eemu_afterbtagsel  , "all");
  MyhistoManager.WriteMyHisto(Mt_eee_afterbtagsel   , "all");
    
    
  
  MyhistoManager.WriteMyHisto(NJet_mumumu_afterZsel,"all");
  MyhistoManager.WriteMyHisto(NJet_mumue_afterZsel, "all");
  MyhistoManager.WriteMyHisto(NJet_eemu_afterZsel,  "all");
  MyhistoManager.WriteMyHisto(NJet_eee_afterZsel,   "all");
  
  MyhistoManager.WriteMyHisto(NBJet_mumumu_afterZsel, "all");
  MyhistoManager.WriteMyHisto(NBJet_mumue_afterZsel,  "all");
  MyhistoManager.WriteMyHisto(NBJet_eemu_afterZsel,   "all");
  MyhistoManager.WriteMyHisto(NBJet_eee_afterZsel,    "all");
  
  
  MyhistoManager.WriteMyHisto(NBJet_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(NBJet_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(NBJet_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(NBJet_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(InvM_ll_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eee_afterleptsel,    "all");
    
  
  MyhistoManager.WriteMyHisto(InvM_ll_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(InvM_ll_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eee_afterbjetsel,    "all");
    
    
  MyhistoManager.WriteMyHisto(LeptPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(LeptPt_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(LeptPt_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(LeptPt_eee_afterleptsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptPt_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptPt_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptPt_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptPt_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptPt_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptPt_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptPt_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptPt_eee_afterbjetsel,    "all");
  
    
    
  MyhistoManager.WriteMyHisto(LeptZPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(LeptZPt_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eee_afterleptsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptZPt_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptZPt_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptZPt_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptZPt_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptZPt_eee_afterbjetsel,    "all");
  
    
    
  MyhistoManager.WriteMyHisto(LeptWPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(LeptWPt_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eee_afterleptsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptWPt_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptWPt_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(LeptWPt_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(LeptWPt_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(LeptWPt_eee_afterbjetsel,    "all");
  
    
    
  MyhistoManager.WriteMyHisto(JetPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(JetPt_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(JetPt_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(JetPt_eee_afterleptsel,    "all");
  
  MyhistoManager.WriteMyHisto(JetPt_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(JetPt_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(JetPt_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(JetPt_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(JetPt_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(JetPt_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(JetPt_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(JetPt_eee_afterbjetsel,    "all");
  
    
    
  MyhistoManager.WriteMyHisto(JetEta_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(JetEta_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(JetEta_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(JetEta_eee_afterleptsel,    "all");
  
  MyhistoManager.WriteMyHisto(JetEta_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(JetEta_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(JetEta_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(JetEta_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(JetEta_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(JetEta_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(JetEta_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(JetEta_eee_afterbjetsel,    "all");
  
  
  MyhistoManager.WriteMyHisto(HT_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(HT_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(HT_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(HT_eee_afterleptsel,    "all");
  
  
  MyhistoManager.WriteMyHisto(HT_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(HT_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(HT_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(HT_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(HT_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(HT_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(HT_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(HT_eee_afterbjetsel,    "all");
  
  
  
  
  
  MyhistoManager.WriteMyHisto(MET_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto(MET_mumue_afterleptsel,  "all");
  MyhistoManager.WriteMyHisto(MET_eemu_afterleptsel,   "all");
  MyhistoManager.WriteMyHisto(MET_eee_afterleptsel,    "all");
  
  
  MyhistoManager.WriteMyHisto(MET_mumumu_afterjetsel, "all");
  MyhistoManager.WriteMyHisto(MET_mumue_afterjetsel,  "all");
  MyhistoManager.WriteMyHisto(MET_eemu_afterjetsel,   "all");
  MyhistoManager.WriteMyHisto(MET_eee_afterjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(MET_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(MET_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(MET_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(MET_eee_afterbjetsel,    "all");
  
  
  
  MyhistoManager.WriteMyHisto(InvM_ll_mumumu_afterleptsel_highSumPt, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_mumue_afterleptsel_highSumPt, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eemu_afterleptsel_highSumPt, "all");
  MyhistoManager.WriteMyHisto(InvM_ll_eee_afterleptsel_highSumPt, "all");
  
  
  
  
  MyhistoManager.WriteMyHisto(Asym_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(Asym_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(Asym_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(Asym_eee_afterbjetsel,    "all");
  
  
  
  MyhistoManager.WriteMyHisto(RecoPtZ_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(RecoPtZ_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(RecoPtZ_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(RecoPtZ_eee_afterbjetsel,    "all");
  
  MyhistoManager.WriteMyHisto(RecoTopMass_mumumu_afterbjetsel  , "all");
  MyhistoManager.WriteMyHisto(RecoTopMass_mumue_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(RecoTopMass_eemu_afterbjetsel,    "all");
  MyhistoManager.WriteMyHisto(RecoTopMass_eee_afterbjetsel,     "all");
  
  
  
  MyhistoManager.WriteMyHisto(deltaPhilb_mumumu_afterbjetsel, "all");
  MyhistoManager.WriteMyHisto(deltaPhilb_mumue_afterbjetsel,  "all");
  MyhistoManager.WriteMyHisto(deltaPhilb_eemu_afterbjetsel,   "all");
  MyhistoManager.WriteMyHisto(deltaPhilb_eee_afterbjetsel,    "all");
  
  
    
  MyhistoManager.WriteMyHisto2D(HT_vs_MET_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_MET_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_MET_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_MET_eee_afterleptsel, "all");
 
  MyhistoManager.WriteMyHisto2D(HT_vs_NJet_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NJet_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NJet_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NJet_eee_afterleptsel, "all");
 
  MyhistoManager.WriteMyHisto2D(HT_vs_NBJet_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NBJet_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NBJet_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_NBJet_eee_afterleptsel, "all");
 
  MyhistoManager.WriteMyHisto2D(HT_vs_LeptPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_LeptPt_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_LeptPt_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_LeptPt_eee_afterleptsel, "all");
 
  MyhistoManager.WriteMyHisto2D(HT_vs_JetPt_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_JetPt_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_JetPt_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_JetPt_eee_afterleptsel, "all");
  
  
  
  MyhistoManager.WriteMyHisto2D(HT_vs_Mll_mumumu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_Mll_mumue_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_Mll_eemu_afterleptsel, "all");
  MyhistoManager.WriteMyHisto2D(HT_vs_Mll_eee_afterleptsel, "all");
  
  
  
  
  
  TheTree->Write();
  
  
  
  
   //The following line is mandatory to copy everythin in a common RootFile
    fOutput->Add(fProofFile);
    
  CutFlow_mumumu.clear();
  CutFlow_mumue.clear();
  CutFlow_eemu.clear();
  CutFlow_eee.clear();
  ErrCutFlow_mumumu.clear();
  ErrCutFlow_mumue.clear();
  ErrCutFlow_eemu.clear();
  ErrCutFlow_eee.clear();
  
  
  Mt_mumumu_afterbtagsel.clear();
  Mt_mumue_afterbtagsel.clear();
  Mt_eemu_afterbtagsel.clear();
  Mt_eee_afterbtagsel.clear();
  
  
  NJet_mumumu_afterZsel.clear();
  NJet_mumue_afterZsel.clear();
  NJet_eemu_afterZsel.clear();
  NJet_eee_afterZsel.clear();
  
  NBJet_mumumu_afterZsel.clear();
  NBJet_mumue_afterZsel.clear();
  NBJet_eemu_afterZsel.clear();
  NBJet_eee_afterZsel.clear();
  
  
  NBJet_mumumu_afterjetsel.clear();
  NBJet_mumue_afterjetsel.clear();
  NBJet_eemu_afterjetsel.clear();
  NBJet_eee_afterjetsel.clear();
  
  InvM_ll_mumumu_afterleptsel.clear();
  InvM_ll_mumue_afterleptsel.clear();
  InvM_ll_eemu_afterleptsel.clear();
  InvM_ll_eee_afterleptsel.clear();
  
  
  InvM_ll_mumumu_afterjetsel.clear();
  InvM_ll_mumue_afterjetsel.clear();
  InvM_ll_eemu_afterjetsel.clear();
  InvM_ll_eee_afterjetsel.clear();
  
  InvM_ll_mumumu_afterbjetsel.clear();
  InvM_ll_mumue_afterbjetsel.clear();
  InvM_ll_eemu_afterbjetsel.clear();
  InvM_ll_eee_afterbjetsel.clear();
  
  LeptPt_mumumu_afterleptsel.clear();
  LeptPt_mumue_afterleptsel.clear();
  LeptPt_eemu_afterleptsel.clear();
  LeptPt_eee_afterleptsel.clear();
  
  LeptPt_mumumu_afterjetsel.clear();
  LeptPt_mumue_afterjetsel.clear();
  LeptPt_eemu_afterjetsel.clear();
  LeptPt_eee_afterjetsel.clear();
  
  LeptPt_mumumu_afterbjetsel.clear();
  LeptPt_mumue_afterbjetsel.clear();
  LeptPt_eemu_afterbjetsel.clear();
  LeptPt_eee_afterbjetsel.clear();
  
  
  HT_mumumu_afterleptsel.clear();
  HT_mumue_afterleptsel.clear();
  HT_eemu_afterleptsel.clear();
  HT_eee_afterleptsel.clear();
  
  
  HT_mumumu_afterjetsel.clear();
  HT_mumue_afterjetsel.clear();
  HT_eemu_afterjetsel.clear();
  HT_eee_afterjetsel.clear();
  
  HT_mumumu_afterbjetsel.clear();
  HT_mumue_afterbjetsel.clear();
  HT_eemu_afterbjetsel.clear();
  HT_eee_afterbjetsel.clear();
  
  
  
  MET_mumumu_afterleptsel.clear();
  MET_mumue_afterleptsel.clear();
  MET_eemu_afterleptsel.clear();
  MET_eee_afterleptsel.clear();
  
  
  MET_mumumu_afterjetsel.clear();
  MET_mumue_afterjetsel.clear();
  MET_eemu_afterjetsel.clear();
  MET_eee_afterjetsel.clear();
  
  MET_mumumu_afterbjetsel.clear();
  MET_mumue_afterbjetsel.clear();
  MET_eemu_afterbjetsel.clear();
  MET_eee_afterbjetsel.clear();
  
    //delete file1  ;
    //delete hPUMC ;  
    //delete file2 ; 
    delete anaEL;
    delete LumiWeights;
  }
}

//_____________________________________________________________________________
void ProofSelectorMyCutFlow::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  
  //Possibility to retrieve information from the merged file and perform some calculation or plotting tasks
  delete event ;
  //
  // Create canvas
  //
  //TList* list = fOutput->GetOutputList() ;
  /*
    TIter next_object((TList*) fOutput);
    TObject* obj ;
    cout << "-- Retrieved objects:" << endl ;
    while ((obj = next_object())) { TString objname = obj->GetName() ; cout << " " << objname << endl ; }
    
    if ((fi = dynamic_cast<TFile *>(fOutput->FindObject("blabla.root")))) {
    cout<<"Warning"<<endl;
    fi->Write("toto.root");
    cout<<"Warning"<<endl;
    }
    // Final update
    c1->cd();
    c1->Update();
  */
}

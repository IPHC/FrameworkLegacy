
//////////////////////////////////////////////////////////
//
// Example of TSelector implementation to do a Monte Carlo
// generation using Pythia8.
// See tutorials/proof/runProof.C, option "pythia8", for an
// example of how to run this selector.
//
//////////////////////////////////////////////////////////

#ifndef ProofSelectorMyCutFlow_h
#define ProofSelectorMyCutFlow_h

#include <TSelector.h>
#include <TTree.h>
#include <TFile.h>
#include <TProofOutputFile.h>
#include <TRandom.h>

#include "NTFormat/interface/NTEvent.h"
#include "Plots/interface/HistoManager.h"



#include "Tools/interface/Dataset.h"
#include "Tools/interface/AnalysisEnvironmentLoader.h"
#include "Selection/interface/DiLeptonSelection.h"
#include "Plots/interface/DiLepAnaHistoManager.h"
//#include "BckgdEstimation/interface/DYEstimation.h"
//#include "../../BckgdEstimation/interface/MMEstimation.h"
//#include "Measurements/interface/PLRPlotsFurnisher.h"
#include "Tools/interface/PUWeighting.h"
#include "Tools/interface/LumiReweightingStandAlone.h"


#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1.h>
#include <TH2.h> 
#include <TH3.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TLorentzVector.h>
//#include <iostream>

class TH1F;
class TBranch;
class TTree;

class AnalysisEnvironmentLoader;
class DiLeptonSelection;

class ProofSelectorMyCutFlow : public TSelector {
 public :
  
  // Specific members
  //Access to the tree and outputs
  TTree* fChain;
  TBranch* branch;
  IPHCTree::NTEvent* event;
  TFile            *fFile;
  TProofOutputFile *fProofFile; // For optimized merging of the ntuple
  //Pointer on results from xml file  reading
  AnalysisEnvironmentLoader* anaEL; 
  //Minimimal info
  vector<Dataset> datasets;
  Dataset* dataset;
  vector<string> CutName;
  vector<string> ChannelName;
  vector<string> VecChannelName;
  DiLeptonSelection sel; 
  float Luminosity;
  int verbosity;
  // 0: MC - 1: Data - 2 Data & MC
  int DataType;
  //Info analysis macro specific 
  
  
  
  reweight::LumiReWeighting *LumiWeights;
  float LumiError ;
  string PUWeightFileName;
  reweight::PoissonMeanShifter PShiftUp_;
  reweight::PoissonMeanShifter PShiftDown_;

  bool producePLRPlots ;
  
  
  // Here define the studied channel (ee/mumu/emu)
  //  string ChannelName  = "ee";  // "mumu", "ee", "emu"
  // on va tourner sur les 3 canaux en meme temps!!!
  
  bool IReweight             ;
  bool IReweight_puUp        ;
  bool IReweight_puDown      ;
  bool IDYestimateWithMetCut ;
  
  bool useNonIsoWcand;
  
  bool applyDYscale ;
  bool applyFakescale ;
  
  //Here define Scale Factors
  //SF_trigger applied for mumu
  double SF_trig_mu ;  
  double SF_trig_emu;  
  double SF_trig_ee ;  
  
  double SF_trig_mu_error ;  
  double SF_trig_emu_error;  
  double SF_trig_ee_error ;  
  
  double SF_e  ;  
  double SF_mu ; 
    
  double SF_BranchingRatio_ll ; 
  double SF_BranchingRatio_lj ; 
  double SF_BranchingRatio_had ; 
    
  double SF_DY_ee ;
  double SF_DY_mm ;
  double SF_DY_em ;
  
  double  SF_DY_Njets_ee ;
  double  SF_DY_Njets_mm ;
  double  SF_DY_Njets_em ;
  
  /*double SF_met_mumu;
  double SF_met_emu;
  double SF_met_ee;

  double SF_met_mumu_error;
  double SF_met_emu_error;
  double SF_met_ee_error;*/
   
  
  std::vector<double> vSF_met_ee ;
  std::vector<double> vSF_met_mumu ;
  std::vector<double> vSF_met_emu ;
  
  std::vector<double> vSF_met_ee_error ;
  std::vector<double> vSF_met_mumu_error ;
  std::vector<double> vSF_met_emu_error ;
  
  
  bool PUup;
  bool PUdown;
  
  TRandom rand;
  bool doLinearity;
  
   
  std::vector<double> vSF_DY_ee ;
  std::vector<double> vSF_DY_mm ;
  std::vector<double> vSF_DY_em ;
   
  std::vector<double> vSF_DY_ee_error ;
  std::vector<double> vSF_DY_mm_error ;
  std::vector<double> vSF_DY_em_error ;
  
  std::vector<double> vSF_FakeBck_ee; 
  std::vector<double> vSF_FakeBck_mm; 
  std::vector<double> vSF_FakeBck_em; 
  
  
  std::vector<double> vSF_FakeBck_ee_error; 
  std::vector<double> vSF_FakeBck_mm_error; 
  std::vector<double> vSF_FakeBck_em_error; 
  
  double sumSFlept_ee;
  double sumSFlept_mumu;
  double sumSFlept_emu;
  
  double nEvents_ee;
  double nEvents_mumu;
  double nEvents_emu;
  
   
   
  double SF_Wjets_ee;
  double SF_Wjets_mm;
  double SF_Wjets_em;
  
  double SF_QCD_ee;
  double SF_QCD_mm;
  double SF_QCD_em;
  
  double scaleElec; // 1 to switch off
  double resolElec; // 0 to switch off
  
  
  bool ApplyLeptonSF;
  
  
  int ITypeMC ;
  int ICut    ;  
  
  
  //For PLR plots
  //PLRPlotsFurnisher plotsFurnisher;
  
  
  
  
  TH1F* fHist;
  
  std::vector<TH1F> CutFlow_mumumu;
  std::vector<TH1F> CutFlow_mumue;
  std::vector<TH1F> CutFlow_eemu;
  std::vector<TH1F> CutFlow_eee;
  std::vector<TH1F> ErrCutFlow_mumumu;
  std::vector<TH1F> ErrCutFlow_mumue;
  std::vector<TH1F> ErrCutFlow_eemu;
  std::vector<TH1F> ErrCutFlow_eee;
  
  
  std::vector<TH1F> Mt_mumumu_afterbtagsel;
  std::vector<TH1F> Mt_mumue_afterbtagsel;
  std::vector<TH1F> Mt_eemu_afterbtagsel;
  std::vector<TH1F> Mt_eee_afterbtagsel;
   
  
  std::vector<TH1F> NJet_mumumu_afterZsel;
  std::vector<TH1F> NJet_mumue_afterZsel;
  std::vector<TH1F> NJet_eemu_afterZsel;
  std::vector<TH1F> NJet_eee_afterZsel;
  
  std::vector<TH1F> NBJet_mumumu_afterZsel;
  std::vector<TH1F> NBJet_mumue_afterZsel;
  std::vector<TH1F> NBJet_eemu_afterZsel;
  std::vector<TH1F> NBJet_eee_afterZsel;
  
  
  std::vector<TH1F> NBJet_mumumu_afterjetsel;
  std::vector<TH1F> NBJet_mumue_afterjetsel;
  std::vector<TH1F> NBJet_eemu_afterjetsel;
  std::vector<TH1F> NBJet_eee_afterjetsel;
  
  
  
  //to be filled
  
  std::vector<TH1F> InvM_ll_mumumu_afterleptsel;
  std::vector<TH1F> InvM_ll_mumue_afterleptsel;
  std::vector<TH1F> InvM_ll_eemu_afterleptsel;
  std::vector<TH1F> InvM_ll_eee_afterleptsel;
  
  std::vector<TH1F> InvM_ll_mumumu_afterleptsel_highSumPt;
  std::vector<TH1F> InvM_ll_mumue_afterleptsel_highSumPt;
  std::vector<TH1F> InvM_ll_eemu_afterleptsel_highSumPt;
  std::vector<TH1F> InvM_ll_eee_afterleptsel_highSumPt;
  
  std::vector<TH1F> InvM_ll_mumumu_afterjetsel;
  std::vector<TH1F> InvM_ll_mumue_afterjetsel;
  std::vector<TH1F> InvM_ll_eemu_afterjetsel;
  std::vector<TH1F> InvM_ll_eee_afterjetsel;
  
  std::vector<TH1F> InvM_ll_mumumu_afterbjetsel;
  std::vector<TH1F> InvM_ll_mumue_afterbjetsel;
  std::vector<TH1F> InvM_ll_eemu_afterbjetsel;
  std::vector<TH1F> InvM_ll_eee_afterbjetsel;
  
  std::vector<TH1F> LeptPt_mumumu_afterleptsel;
  std::vector<TH1F> LeptPt_mumue_afterleptsel;
  std::vector<TH1F> LeptPt_eemu_afterleptsel;
  std::vector<TH1F> LeptPt_eee_afterleptsel;
  
  std::vector<TH1F> LeptPt_mumumu_afterjetsel;
  std::vector<TH1F> LeptPt_mumue_afterjetsel;
  std::vector<TH1F> LeptPt_eemu_afterjetsel;
  std::vector<TH1F> LeptPt_eee_afterjetsel;
  
  std::vector<TH1F> LeptPt_mumumu_afterbjetsel;
  std::vector<TH1F> LeptPt_mumue_afterbjetsel;
  std::vector<TH1F> LeptPt_eemu_afterbjetsel;
  std::vector<TH1F> LeptPt_eee_afterbjetsel;
  
  
  
  std::vector<TH1F> LeptZPt_mumumu_afterleptsel;
  std::vector<TH1F> LeptZPt_mumue_afterleptsel;
  std::vector<TH1F> LeptZPt_eemu_afterleptsel;
  std::vector<TH1F> LeptZPt_eee_afterleptsel;
  
  std::vector<TH1F> LeptZPt_mumumu_afterjetsel;
  std::vector<TH1F> LeptZPt_mumue_afterjetsel;
  std::vector<TH1F> LeptZPt_eemu_afterjetsel;
  std::vector<TH1F> LeptZPt_eee_afterjetsel;
  
  std::vector<TH1F> LeptZPt_mumumu_afterbjetsel;
  std::vector<TH1F> LeptZPt_mumue_afterbjetsel;
  std::vector<TH1F> LeptZPt_eemu_afterbjetsel;
  std::vector<TH1F> LeptZPt_eee_afterbjetsel;
  
  
  
  std::vector<TH1F> LeptWPt_mumumu_afterleptsel;
  std::vector<TH1F> LeptWPt_mumue_afterleptsel;
  std::vector<TH1F> LeptWPt_eemu_afterleptsel;
  std::vector<TH1F> LeptWPt_eee_afterleptsel;
  
  std::vector<TH1F> LeptWPt_mumumu_afterjetsel;
  std::vector<TH1F> LeptWPt_mumue_afterjetsel;
  std::vector<TH1F> LeptWPt_eemu_afterjetsel;
  std::vector<TH1F> LeptWPt_eee_afterjetsel;
  
  std::vector<TH1F> LeptWPt_mumumu_afterbjetsel;
  std::vector<TH1F> LeptWPt_mumue_afterbjetsel;
  std::vector<TH1F> LeptWPt_eemu_afterbjetsel;
  std::vector<TH1F> LeptWPt_eee_afterbjetsel;
  
  
  
  
  std::vector<TH1F> JetPt_mumumu_afterleptsel;
  std::vector<TH1F> JetPt_mumue_afterleptsel;
  std::vector<TH1F> JetPt_eemu_afterleptsel;
  std::vector<TH1F> JetPt_eee_afterleptsel;
  
  std::vector<TH1F> JetPt_mumumu_afterjetsel;
  std::vector<TH1F> JetPt_mumue_afterjetsel;
  std::vector<TH1F> JetPt_eemu_afterjetsel;
  std::vector<TH1F> JetPt_eee_afterjetsel;
  
  std::vector<TH1F> JetPt_mumumu_afterbjetsel;
  std::vector<TH1F> JetPt_mumue_afterbjetsel;
  std::vector<TH1F> JetPt_eemu_afterbjetsel;
  std::vector<TH1F> JetPt_eee_afterbjetsel;
  
  std::vector<TH1F> JetEta_mumumu_afterleptsel;
  std::vector<TH1F> JetEta_mumue_afterleptsel;
  std::vector<TH1F> JetEta_eemu_afterleptsel;
  std::vector<TH1F> JetEta_eee_afterleptsel;
  
  std::vector<TH1F> JetEta_mumumu_afterjetsel;
  std::vector<TH1F> JetEta_mumue_afterjetsel;
  std::vector<TH1F> JetEta_eemu_afterjetsel;
  std::vector<TH1F> JetEta_eee_afterjetsel;
  
  std::vector<TH1F> JetEta_mumumu_afterbjetsel;
  std::vector<TH1F> JetEta_mumue_afterbjetsel;
  std::vector<TH1F> JetEta_eemu_afterbjetsel;
  std::vector<TH1F> JetEta_eee_afterbjetsel;
  
  std::vector<TH1F> HT_mumumu_afterleptsel;
  std::vector<TH1F> HT_mumue_afterleptsel;
  std::vector<TH1F> HT_eemu_afterleptsel;
  std::vector<TH1F> HT_eee_afterleptsel;
  
  
  std::vector<TH1F> HT_mumumu_afterjetsel;
  std::vector<TH1F> HT_mumue_afterjetsel;
  std::vector<TH1F> HT_eemu_afterjetsel;
  std::vector<TH1F> HT_eee_afterjetsel;
  
  std::vector<TH1F> HT_mumumu_afterbjetsel;
  std::vector<TH1F> HT_mumue_afterbjetsel;
  std::vector<TH1F> HT_eemu_afterbjetsel;
  std::vector<TH1F> HT_eee_afterbjetsel;
  
  
  
  
  
  std::vector<TH1F> MET_mumumu_afterleptsel;
  std::vector<TH1F> MET_mumue_afterleptsel;
  std::vector<TH1F> MET_eemu_afterleptsel;
  std::vector<TH1F> MET_eee_afterleptsel;
  
  
  std::vector<TH1F> MET_mumumu_afterjetsel;
  std::vector<TH1F> MET_mumue_afterjetsel;
  std::vector<TH1F> MET_eemu_afterjetsel;
  std::vector<TH1F> MET_eee_afterjetsel;
  
  std::vector<TH1F> MET_mumumu_afterbjetsel;
  std::vector<TH1F> MET_mumue_afterbjetsel;
  std::vector<TH1F> MET_eemu_afterbjetsel;
  std::vector<TH1F> MET_eee_afterbjetsel;
  
  
  std::vector<TH2D> HT_vs_MET_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_MET_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_MET_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_MET_eee_afterleptsel;
  
  std::vector<TH2D> HT_vs_NJet_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_NJet_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_NJet_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_NJet_eee_afterleptsel;
  
  std::vector<TH2D> HT_vs_NBJet_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_NBJet_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_NBJet_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_NBJet_eee_afterleptsel;
  
  std::vector<TH2D> HT_vs_LeptPt_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_LeptPt_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_LeptPt_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_LeptPt_eee_afterleptsel;
  
  std::vector<TH2D> HT_vs_JetPt_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_JetPt_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_JetPt_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_JetPt_eee_afterleptsel;
  
  
  
  std::vector<TH2D> HT_vs_Mll_mumumu_afterleptsel;
  std::vector<TH2D> HT_vs_Mll_mumue_afterleptsel;
  std::vector<TH2D> HT_vs_Mll_eemu_afterleptsel;
  std::vector<TH2D> HT_vs_Mll_eee_afterleptsel;
  
  
  ofstream ofile;
  
  //------------------------------------
  //Definition of the various histograms
  //------------------------------------
  int nbins ;
  float minx;
  float maxx;
  HistoManager MyhistoManager;
  
  
  std::map<TString, int> initMCevents;
  std::map<TString, int> skimMCevents;
 
  //------------------------------------
  // for PileUP reweighting
  //------------------------------------
  PUWeighting  thePUReweighter;
  
  
  string datasetName ;
  
  
  //------------------------------------
  //definition of member functions
  //------------------------------------
  ProofSelectorMyCutFlow();
  virtual ~ProofSelectorMyCutFlow();
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual void    SlaveBegin(TTree *tree);
  virtual Bool_t  Process(Long64_t entry);
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();
  
  ClassDef(ProofSelectorMyCutFlow,0);
};

#endif

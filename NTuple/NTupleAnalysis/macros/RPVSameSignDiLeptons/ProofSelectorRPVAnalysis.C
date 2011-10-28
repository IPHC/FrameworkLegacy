#define ProofSelectorRPVAnalysis_cxx

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

#include "ProofSelectorRPVAnalysis.h"


//_____________________________________________________________________________
ProofSelectorRPVAnalysis::ProofSelectorRPVAnalysis(): idataset(0)
{
   // Constructor

   fChain = 0;
   branch = 0;
   event = 0;
   dataset = 0;
   //idataset = 0;
   anaEL = 0;
   verbosity = 0;
   DataType = 0;
   Luminosity = 0;
   //histos
   fHist = 0;
   histoManager = 0;
   selTable_allChannels = 0;
   selTable_ee = 0;
   selTable_emu = 0;
   selTable_mumu = 0;
}

//_____________________________________________________________________________
ProofSelectorRPVAnalysis::~ProofSelectorRPVAnalysis()
{
   // Destructor

   //SafeDelete(fHist);
}

//_____________________________________________________________________________
void ProofSelectorRPVAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.
 
   //fChain point to the loading tree 
   fChain = tree;

   // Set branch addresses
   branch = (TBranch *) tree->GetBranch("NTEvent");
   event = new TopTree::NTEvent();
   branch->SetAddress(&event);
   //event is now retrieved and could be used in Process
}

//_____________________________________________________________________________
void ProofSelectorRPVAnalysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();


}

//_____________________________________________________________________________
void ProofSelectorRPVAnalysis::SlaveBegin(TTree * tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   //--------------------------------------//
   //       Loading the xml file
   //--------------------------------------//
   TNamed *dsname = (TNamed *) fInput->FindObject("PROOF_DATASETNAME");
   string datasetName = dsname->GetTitle();
   cout << "dataset name " << datasetName << endl;
   TNamed *xfname = (TNamed *) fInput->FindObject("PROOF_XMLFILENAME");
   string xmlFileName = xfname->GetTitle();
   anaEL = new AnalysisEnvironmentLoader(xmlFileName.c_str());
   anaEL->LoadSamples (datasets); // now the list of datasets written in the xml file is known
   vector<Dataset> onedatasetonly;
   //retrieve the current dataset according to its name
   for(unsigned int d=0;d<datasets.size();d++){
	onedatasetonly.push_back(datasets[d]);
	if(datasets[d].Name()==datasetName) { 
	dataset = &datasets[d]; idataset = (int) d; 
//	onedatasetonly.push_back(datasets[d]);
	cout<<" SlaveBegin on dataset : "<<dataset->Name()<<" "<<idataset<<" "<<datasets[idataset].Name()<<endl; 
	}
   }
   anaEL->LoadSSDiLeptonSelection (sel); // now the parameters for the selection are given to the selection
   anaEL->LoadGeneralInfo(DataType, Luminosity, verbosity );


   //--------------------------------------//
   //   Selection tables
   //--------------------------------------//
   // Only 1 dataset per job with PROOF
   selTable_allChannels = new SelectionTable(sel.GetCutList (), onedatasetonly, string ("*"));
   selTable_ee = new SelectionTable(sel.GetCutList (), onedatasetonly, string ("ee"));
   selTable_emu = new SelectionTable(sel.GetCutList (), onedatasetonly, string ("emu"));
   selTable_mumu = new SelectionTable(sel.GetCutList (), onedatasetonly, string ("mumu"));
   /*selTable_allChannels = new SelectionTable(sel.GetCutList (), datasets, string ("*"));
   selTable_ee = new SelectionTable(sel.GetCutList (), datasets, string ("ee"));
   selTable_emu = new SelectionTable(sel.GetCutList (), datasets, string ("emu"));
   selTable_mumu = new SelectionTable(sel.GetCutList (), datasets, string ("mumu"));*/

   //--------------------------------------//
   //   Managing histos  	
   //--------------------------------------//
   histoManager = new SSDiLepAnaHistoManager();
   // Only 1 dataset per job with PROOF
   //idataset = 1;
   histoManager->LoadDatasets (onedatasetonly);
   //histoManager->LoadDatasets (datasets);
   cout<<" Ndatasets  "<<datasets.size()<<endl;
   histoManager->LoadSelectionSteps (sel.GetCutList ());
   histoManager->LoadChannels (sel.GetChannelList ());
   histoManager->CreateHistos ();

   //cout<<" Datasets in HistoManager : size = "<<histoManager->Datasets.size()<<endl;

   //////////////////////

   cout << "The verbosity mode is " << verbosity << endl;
   cout << "The luminosity is equal to " << Luminosity << endl;
   cout << "The DataType is ";
   switch (DataType) {
   case 0:
     cout << "MC" << endl;
     break;
   case 1:
     cout << "Data" << endl;
     break;
   case 2:
     cout << "Data & MC" << endl;
     break;
   default:
     cout << " unknown" << endl;
     break;
   }
   //////////////////////


   //example
   //fHist = new TH1F("fHist", "jet pt", 50, 0., 200.);

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

   //this line is very important !!!
   fFile->Write();
   //It is required to add in fOutput the histos you want to feedback
   fOutput->Add(fHist);
   fOutput->Add(fFile);

}

//_____________________________________________________________________________
Bool_t ProofSelectorRPVAnalysis::Process(Long64_t entry)
{
   //---------------------------------------------------//
   // Main event loop: get entry
   //---------------------------------------------------//
   fChain->GetTree()->GetEntry(entry); 
   branch->GetEntry(entry);
  
   float weight=1;
   if(dataset->isData() == false) weight = dataset->NormFactor()*Luminosity; //if Data , weight = 1

   //---------------------------------------------------//
   //         Doing the analysis event by event
   //---------------------------------------------------//

   //cout<<"Entry "<<entry<<endl;
   sel.LoadEvent(event);
   
   //cout<<sel.GetSelectedJets().size()<<endl;
   //for(unsigned int i=0;i<sel.GetSelectedJets().size();i++)
	//fHist->Fill(sel.GetSelectedJets()[i].p4.Pt());
   
   //Collection of selected objects
   vector<TopTree::NTVertex>   selVertices  = sel.GetSelectedVertex();
   vector<TopTree::NTElectron> selElectrons = sel.GetSelectedElectrons();
   vector<TopTree::NTMuon>     selMuons     = sel.GetSelectedMuons();
   vector<TopTree::NTJet>      selJets      = sel.GetSelectedJets();
   TopTree::NTMET met                       = sel.GetMET(); 
      
   //Candidate pair of lepton
   string CandType; // ee - emu - mumu or false
   vector<TopTree::NTElectron> candElec;
   vector<TopTree::NTMuon> candMuon;
   sel.GetLeptonPair (candMuon, candElec, CandType);	// fill the variables 

   int selLastStep = 2;
   int step = 0;

   //////////////////////////////////   
   //   Fill the selection table
   //////////////////////////////////   

   /*step = sel.FillTable (*selTable_ee, dataset, idataset, weight);
   if (CandType=="ee") selLastStep = step;
   step = sel.FillTable (*selTable_emu, dataset, idataset, weight);
   if (CandType=="emu") selLastStep = step;
   step = sel.FillTable (*selTable_mumu, dataset, idataset, weight);
   if (CandType=="mumu") selLastStep = step;*/
   
   /////////////////
   // Fill histos 
   /////////////////

   histoManager->Fill(sel, event, selMuons, selElectrons, selLastStep, sel.GetChannel(CandType), idataset, weight);


   return kTRUE;
}

//_____________________________________________________________________________
void ProofSelectorRPVAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
 
   if(fProofFile) fProofFile->Print();
   if (fFile) {
      fFile->cd();
      //fHist->Write();
      histoManager->Write(fFile);
      fFile->Write();
      //The following line is mandatory to copy everything in a common RootFile
      fOutput->Add(fProofFile);
   }
   
   cout << "end SlaveTerminate " << endl;

   delete selTable_allChannels;
   delete selTable_ee;
   delete selTable_emu;
   delete selTable_mumu;
   delete histoManager;
   delete anaEL;
}

//_____________________________________________________________________________
void ProofSelectorRPVAnalysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   //Possibility to retrieve information from the merged file and perform some calculation or plotting tasks


//histoManager.Compute (); // Merge channels, datasets, plots cut by cut


    /*TList* list = fOutput->GetOutputList() ;
    TIter next_object((TList*) fOutput);
    TObject* obj ;
    cout << "-- Retrieved objects:" << endl ;
    while ((obj = next_object())) { TString objname = obj->GetName() ; cout << " " << objname << endl ; }

   if ((fi = dynamic_cast<TFile *>(fOutput->FindObject("blabla.root")))) {
	cout<<"Warning"<<endl;
	fi->Write("toto.root");
	cout<<"Warning"<<endl;
   }
   */
}

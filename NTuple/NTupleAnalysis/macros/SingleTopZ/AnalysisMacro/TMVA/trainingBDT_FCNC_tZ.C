#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "test/TMVAGui.C"

#include "TMVA/Factory.h"
#include "TMVA/Tools.h"


void doBDT_FCNC_tZ(TString thevertex, bool doScan,  double Vut=0, double Vct=0, TString syst = ""){

   
   
   
   
   
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

  TString outfileName( "trainingBDT_FCNC_" );
  outfileName+=thevertex+".root";
  TString sVut;
  TString sVct;
  if(doScan){
  
   std::ostringstream ossVut;
   ossVut << Vut ;
   sVut = ossVut.str();
  
   std::ostringstream ossVct;
   ossVct << Vct ;
   sVct = ossVct.str();
  
   outfileName =  "ScanRootFiles/ScanTrainingBDT_FCNC_"+thevertex+"_"+sVut+"_"+sVct+".root";
  }
  
  
  
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  
  
  
  
  TMVA::Factory *factory ;
  
  
  if(!doScan){ 
    if(thevertex == "zut")      factory = new TMVA::Factory( "BDT_trainning_zut", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "zct") factory = new TMVA::Factory( "BDT_trainning_zct", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "kut") factory = new TMVA::Factory( "BDT_trainning_kut", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "kct") factory = new TMVA::Factory( "BDT_trainning_kct", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "xut") factory = new TMVA::Factory( "BDT_trainning_xut", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "xct") factory = new TMVA::Factory( "BDT_trainning_xct", outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
  }else{
    if(thevertex == "zut")      factory = new TMVA::Factory( TString("BDT_trainning_zut")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "zct") factory = new TMVA::Factory( TString("BDT_trainning_zct")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "kut") factory = new TMVA::Factory( TString("BDT_trainning_kut")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "kct") factory = new TMVA::Factory( TString("BDT_trainning_kct")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "xut") factory = new TMVA::Factory( TString("BDT_trainning_xut")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
    else if(thevertex == "xct") factory = new TMVA::Factory( TString("BDT_trainning_xct")+"_"+sVut+"_"+sVct+"_"+syst, outputFile,"!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  }

   
   //TFile *input_sig1   = TFile::Open( "../../RootFiles/proof_woWZSF.root" );
   TFile *input_sig1   = TFile::Open( "../../backup_outputProof29-04-13_11-38_nom/proof_merged.root" );
   if(doScan){
     if(thevertex == "zut") input_sig1   = TFile::Open( "FilesBenchmark/TreeMVA_benchmark_"+sVut+"_"+sVct+"_"+syst+"_"+"zqt.root" );
     if(thevertex == "kut") input_sig1   = TFile::Open( "FilesBenchmark/TreeMVA_benchmark_"+sVut+"_"+sVct+"_"+syst+"_"+"kqt.root" );
   }
   //TFile *input_wz    = TFile::Open( "../../RootFiles/proof_woWZSF.root" );
   TFile *input_wz    = TFile::Open( "../../backup_outputProof29-04-13_11-38_nom/proof_merged.root" );
   
   cout << "line 74 " <<  "FilesBenchmark/TreeMVA_benchmark_"+sVut+"_"+sVct+"_"+syst+"_"+"zqt.root"   << endl;
   
   TTree *signal1;
   if(thevertex == "zut") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCzut");
   else if(thevertex == "zct") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCzct");
   else if(thevertex == "kut") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCkut");
   else if(thevertex == "kct") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCkct");
   else if(thevertex == "xut") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCxut");
   else if(thevertex == "xct") signal1 = (TTree*)input_sig1->Get("Ttree_FCNCxct");
   if(doScan){
     if(thevertex == "zut") signal1 = (TTree*)input_sig1->Get( ("TreeMVA_benchmark_"+sVut+"_"+sVct+"_zqt").Data());
     if(thevertex == "kut") signal1 = (TTree*)input_sig1->Get( ("TreeMVA_benchmark_"+sVut+"_"+sVct+"_kqt").Data());
   }
   
   cout << "line 87 " << ("TreeMVA_benchmark_"+sVut+"_"+sVct+"_"+thevertex).Data() << endl;
   
   
   TTree *background_WZ     = (TTree*)input_wz->Get("Ttree_WZ");
   
   
   Double_t signalWeight1     = 1;
   Double_t signalWeight2     = 1;
   
   Double_t backgroundWeight  = 1;
   
   double sumWeight1 = 0.;
   double sumWeight2 = 0.;
   /*
   if(doScan){
     
     TTree* thesignal1Weights = (TTree*)input_sig1->Get("Ttree_FCNCzut");
     TTree* thesignal2Weights = (TTree*)input_sig2->Get("Ttree_FCNCzct");
     
     Float_t weight1, weight2;
     
     
     
     	
     thesignal1Weights->SetBranchAddress( "tree_EvtWeight",  &weight1); 
     thesignal2Weights->SetBranchAddress( "tree_EvtWeight",  &weight2); 
     
     
     
     for(int ievent = 0; ievent < thesignal1Weights->GetEntries(); ievent++){
       thesignal1Weights->GetEntry(ievent);
       sumWeight1+=weight1;
     }
     
     for(int ievent = 0; ievent < thesignal2Weights->GetEntries(); ievent++){
       thesignal2Weights->GetEntry(ievent);
       sumWeight2+=weight2;
     }
     
     
     double integral = Vut*sumWeight1+Vct*sumWeight2;
     
     
     signalWeight1  = Vut*sumWeight1/integral;
     signalWeight2  = Vct*sumWeight2/integral;
     
   }
   
   cout << "signalWeight1 " << signalWeight1 << " sumWeight1 " << sumWeight1 << endl;
   cout << "signalWeight2 " << signalWeight2 << " sumWeight2 " << sumWeight2 << endl;
   */
    // You can add an arbitrary number of signal or background trees
   factory->AddSignalTree               ( signal1,            signalWeight1     );
   //if(doScan) factory->AddSignalTree    ( signal2,            signalWeight2     );
   factory->AddBackgroundTree( background_WZ,     backgroundWeight );
     
   
   factory->AddVariable("tree_topMass",    'F'); 
   //factory->AddVariable("tree_totMass",    'F');  
   factory->AddVariable("tree_deltaPhilb", 'F');
   factory->AddVariable("tree_deltaRlb",   'F');
   //factory->AddVariable("tree_deltaRTopZ", 'F');
   factory->AddVariable("tree_asym",       'F');
   factory->AddVariable("tree_Zpt",        'F');
   factory->AddVariable("tree_ZEta",       'F');
   //factory->AddVariable("tree_topPt",      'F');
   factory->AddVariable("tree_topEta",     'F');
   factory->AddVariable("tree_NJets",        'F');
   factory->AddVariable("tree_NBJets",         'F');
   factory->AddVariable("tree_deltaRZl ",     'F');   
   factory->AddVariable("tree_deltaPhiZmet",  'F');
   factory->AddVariable("tree_btagDiscri",    'F');  	    
   //factory->AddVariable("tree_leptWPt",       'F');  		   
   //factory->AddVariable("tree_leptWEta",      'F');  		   
   factory->AddVariable("tree_leadJetPt",     'F');  	     
   factory->AddVariable("tree_leadJetEta",    'F');  	    
   //factory->AddVariable("tree_deltaRZleptW",  'F');  	  
   factory->AddVariable("tree_deltaPhiZleptW",'F');  	
   
   
   
         
   
   // to set weights. The variable must exist in the tree
   factory->SetSignalWeightExpression	 ("tree_EvtWeight");
   factory->SetBackgroundWeightExpression("tree_EvtWeight");
   
   
   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   factory->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
   
   
   
   if(thevertex == "zut")      factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
   else if(thevertex == "zct") factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
   else if(thevertex == "kut") factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
   else if(thevertex == "kct") factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );
   else factory->BookMethod( TMVA::Types::kBDT, "BDT", "!H:!V:NTrees=100:nEventsMin=100:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning:VarTransform=Decorrelate" );



   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;

   // Launch the GUI for the root macros
   //if (!gROOT->IsBatch() && !doScan) TMVAGui( outfileName );


   cout << "signalWeight1 " << signalWeight1 << " sumWeight1 " << sumWeight1 << endl;
   cout << "signalWeight2 " << signalWeight2 << " sumWeight2 " << sumWeight2 << endl;
}



void trainingBDT_FCNC_tZ(){



   TString thevertex_zut = "zut";
   TString thevertex_zct = "zct";
   TString thevertex_kut = "kut";
   TString thevertex_kct = "kct";
   TString thevertex_xut = "xut";
   TString thevertex_xct = "xct";

   doBDT_FCNC_tZ (thevertex_zut, false);
   doBDT_FCNC_tZ (thevertex_zct, false);
   doBDT_FCNC_tZ (thevertex_kut, false);
   doBDT_FCNC_tZ (thevertex_kct, false);
   
   //doBDT_FCNC_tZ ( thevertex_zct,  false);
   //doBDT_FCNC_tZ ( thevertex_zut,  true, 0., 1., "nom");
   
   
   /*
   
   std::vector<double> bench_vut, bench_vct;
 
   for(int bench=0; bench<6;   bench++){
     bench_vut.push_back((bench)*0.00004);
   }
   for(int bench=0; bench<6; bench++){
     bench_vct.push_back((bench)*0.0004);
   }
   
   for(unsigned int ibench = 0; ibench<bench_vut.size(); ibench++){
     for(unsigned int jbench = 0; jbench<bench_vct.size(); jbench++){
     
       if(bench_vut[ibench] == 0 & bench_vct[jbench]==0 ) continue;
       doBDT_FCNC_tZ ( thevertex_zut, true, bench_vut[ibench], bench_vct[jbench], "nom");
   
     } 
   }*/
   
   

}




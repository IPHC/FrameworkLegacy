


#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>


#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TRandom.h"



std::pair<double, double>  calculCrossSection(double Zut, double Zct){
  
  std::pair<double, double> xspair;
  xspair.first = 2682000*Zut*Zut;
  xspair.second = 195000*Zct*Zct;
  
  return xspair;
}



void produceBenchmark(TTree* theZutTree, TTree* theZctTree, double Zut, double Zct, TString syst){
  
  std::cout << "producing becnhmark for Zut = " << Zut << "  , Zct = " << Zct << std::endl;
  
  TRandom r;
  r.SetSeed(int( (Zut+Zct)*10000)*123 );
  
  std::pair<double, double>  theCrossSections = calculCrossSection(Zut, Zct);
  
  std::ostringstream ossZut;
  ossZut << Zut ;
  TString sZut = ossZut.str();
  
  std::ostringstream ossZct;
  ossZct << Zct ;
  TString sZct = ossZct.str();
  
  double NZut_ini = 392000;
  double NZct_ini = 399901;
  
  double eff_Zut = theZutTree->GetEntries()/NZut_ini;
  double eff_Zct = theZctTree->GetEntries()/NZct_ini;
  
  int nstop = theZutTree->GetEntries();
  if(nstop >  theZctTree->GetEntries()) nstop = theZctTree->GetEntries(); 
  
  //-----------------------------------------------------------------------
  //defined the variables used by the BDT reader
  // tree to fill 
  //-----------------------------------------------------------------------
  
  TFile * output = new TFile( ("FilesBenchmark/TreeMVA_benchmark_"+sZut+"_"+sZct+"_"+syst+".root").Data(), "recreate");
  
  output->cd();
  TTree *outputTree = new TTree(("TreeMVA_benchmark_"+sZut+"_"+sZct).Data(), ("TreeMVA_benchmark_"+sZut+"_"+sZct).Data());
  
  Float_t topMass,deltaPhilb,asym,Zpt, deltaRlb, deltaRTopZ, ZEta, topPt, topEta, totPt, totEta;
  Float_t totMass, deltaRZl, deltaPhiZmet, btagDiscri, NJets, NBJets, EvtWeight;
  Float_t leptWPt,leptWEta,leadJetPt,leadJetEta,deltaRZleptW,deltaPhiZleptW;
  
  outputTree->Branch("tree_topMass",     &topMass,     "tree_topMass/F"   );
  outputTree->Branch("tree_totMass",     &totMass,     "tree_totMass/F"   );
  outputTree->Branch("tree_deltaPhilb",  &deltaPhilb,  "tree_deltaPhilb/F");
  outputTree->Branch("tree_deltaRlb",    &deltaRlb,    "tree_deltaRlb/F"  );
  outputTree->Branch("tree_deltaRTopZ",  &deltaRTopZ,  "tree_deltaRTopZ/F");
  outputTree->Branch("tree_asym",        &asym,        "tree_asym/F"	  );
  outputTree->Branch("tree_Zpt",         &Zpt,         "tree_Zpt/F"	  );
  outputTree->Branch("tree_ZEta",        &ZEta,        "tree_ZEta/F"	  );
  outputTree->Branch("tree_topPt",       &topPt,       "tree_topPt/F"	  );
  outputTree->Branch("tree_topEta",      &topEta,      "tree_topEta/F"    );
  outputTree->Branch("tree_NJets",       &NJets,       "tree_NJets/F"	  );
  outputTree->Branch("tree_NBJets",      &NBJets,      "tree_NBJets/F"    );
  outputTree->Branch("tree_deltaRZl",    &deltaRZl,    "tree_deltaRZl/F"     );
  outputTree->Branch("tree_deltaPhiZmet",&deltaPhiZmet,"tree_deltaPhiZmet/F" );
  outputTree->Branch("tree_btagDiscri",  &btagDiscri,  "tree_btagDiscri/F"   );
  
  outputTree->Branch("tree_totPt",      &totPt,      "tree_totPt/F"   );
  outputTree->Branch("tree_totEta",     &totEta,     "tree_totEta/F"   );
  
  
  outputTree->Branch("tree_leptWPt",        &leptWPt	    , "tree_leptWPt/F"        );
  outputTree->Branch("tree_leptWEta",       &leptWEta	    , "tree_leptWEta/F"       );
  outputTree->Branch("tree_leadJetPt",      &leadJetPt      , "tree_leadJetPt/F"      ); 
  outputTree->Branch("tree_leadJetEta",     &leadJetEta     , "tree_leadJetEta/F"     );
  outputTree->Branch("tree_deltaRZleptW",   &deltaRZleptW   , "tree_deltaRZleptW/F"   );
  outputTree->Branch("tree_deltaPhiZleptW", &deltaPhiZleptW , "tree_deltaPhiZleptW/F" );
  
  
  
  outputTree->Branch("tree_EvtWeight",   &EvtWeight,   "tree_EvtWeight/F" );
  
  
  //-----------------------------------------------------------------------
  //defined the variables used by the BDT reader
  // tree to read 
  //-----------------------------------------------------------------------
  Float_t topMass_tmp,deltaPhilb_tmp,asym_tmp,Zpt_tmp, deltaRlb_tmp, deltaRTopZ_tmp, ZEta_tmp, topPt_tmp, topEta_tmp;
  Float_t totMass_tmp, deltaRZl_tmp, deltaPhiZmet_tmp, btagDiscri_tmp, NJets_tmp, NBJets_tmp, EvtWeight_tmp;
  Float_t leptWPt_tmp,leptWEta_tmp,leadJetPt_tmp,leadJetEta_tmp,deltaRZleptW_tmp,deltaPhiZleptW_tmp, totPt_tmp, totEta_tmp;
  Float_t EvtWeight_tmp;
  
  
  theZutTree->SetBranchAddress( "tree_topMass",	       &topMass_tmp);
  theZutTree->SetBranchAddress( "tree_totMass",	       &totMass_tmp );
  theZutTree->SetBranchAddress( "tree_deltaPhilb",     &deltaPhilb_tmp );
  theZutTree->SetBranchAddress( "tree_deltaRlb",       &deltaRlb_tmp);
  theZutTree->SetBranchAddress( "tree_deltaRTopZ",     &deltaRTopZ_tmp);
  theZutTree->SetBranchAddress( "tree_asym",	       &asym_tmp );
  theZutTree->SetBranchAddress( "tree_Zpt", 	       &Zpt_tmp );
  theZutTree->SetBranchAddress( "tree_ZEta",	       &ZEta_tmp);
  theZutTree->SetBranchAddress( "tree_topPt",	       &topPt_tmp);
  theZutTree->SetBranchAddress( "tree_topEta",	       &topEta_tmp);
  theZutTree->SetBranchAddress( "tree_NJets",	       &NJets_tmp);
  theZutTree->SetBranchAddress( "tree_NBJets",	       &NBJets_tmp);	      
  theZutTree->SetBranchAddress( "tree_deltaRZl",       &deltaRZl_tmp);   
  theZutTree->SetBranchAddress( "tree_deltaPhiZmet",   &deltaPhiZmet_tmp);
  theZutTree->SetBranchAddress( "tree_btagDiscri",     &btagDiscri_tmp);
  
  theZutTree->SetBranchAddress( "tree_leptWPt",	       &leptWPt_tmp);	       
  theZutTree->SetBranchAddress( "tree_leptWEta",       &leptWEta_tmp);	       
  theZutTree->SetBranchAddress( "tree_leadJetPt",      &leadJetPt_tmp);		 
  theZutTree->SetBranchAddress( "tree_leadJetEta",     &leadJetEta_tmp); 	
  theZutTree->SetBranchAddress( "tree_deltaPhiZleptW", &deltaPhiZleptW_tmp);
  theZutTree->SetBranchAddress( "tree_EvtWeight_tmp",  &EvtWeight_tmp);
  
  
  
  cout << "theCrossSections.first " << theCrossSections.first  << endl;
  cout << "theCrossSections.second " << theCrossSections.second  << endl;
  cout << " xs ratio " << theCrossSections.first/ (theCrossSections.first + theCrossSections.second) << endl;
  
  for (Long64_t ievt=0; ievt<theZutTree->GetEntries();ievt++) { 
    if(ievt > nstop) break;
    double ratio = (theCrossSections.first*eff_Zut/ (theCrossSections.first*eff_Zut + theCrossSections.second*eff_Zct) );
    if( r.Uniform() >  ratio ) continue;
    
    theZutTree->GetEntry(ievt); 
    
    topMass        = topMass_tmp;
    deltaPhilb     = deltaPhilb_tmp;
    asym           = asym_tmp;
    Zpt            = Zpt_tmp; 
    deltaRlb       = deltaRlb_tmp;
    deltaRTopZ     = deltaRTopZ_tmp;
    ZEta           = ZEta_tmp; 
    topPt          = topPt_tmp;
    topEta         = topEta_tmp;
    totMass        = totMass_tmp;
    deltaRZl       = deltaRZl_tmp; 
    deltaPhiZmet   = deltaPhiZmet_tmp; 
    btagDiscri     = btagDiscri_tmp; 
    NJets          = NJets_tmp; 
    NBJets         = NBJets_tmp; 
    EvtWeight      = EvtWeight_tmp;
    leptWPt        = leptWPt_tmp;
    leptWEta       = leptWEta_tmp;
    leadJetPt      = leadJetPt_tmp;
    leadJetEta     = leadJetEta_tmp;
    deltaRZleptW   = deltaRZleptW_tmp;
    deltaPhiZleptW = deltaPhiZleptW_tmp;
    EvtWeight      = EvtWeight_tmp*ratio* ( nstop/double(theZutTree->GetEntries())  ) ;
    
    outputTree->Fill();
  }
  
  
  
  
  //-----------------------------------------------------------------------
  //defined the variables used by the BDT reader
  // tree to read 
  //-----------------------------------------------------------------------
   
  theZctTree->SetBranchAddress( "tree_topMass",	      &topMass_tmp);
  theZctTree->SetBranchAddress( "tree_totMass",	      &totMass_tmp );
  theZctTree->SetBranchAddress( "tree_deltaPhilb",    &deltaPhilb_tmp );
  theZctTree->SetBranchAddress( "tree_deltaRlb",      &deltaRlb_tmp);
  theZctTree->SetBranchAddress( "tree_deltaRTopZ",    &deltaRTopZ_tmp);
  theZctTree->SetBranchAddress( "tree_asym",	      &asym_tmp );
  theZctTree->SetBranchAddress( "tree_Zpt", 	      &Zpt_tmp );
  theZctTree->SetBranchAddress( "tree_ZEta",	      &ZEta_tmp);
  theZctTree->SetBranchAddress( "tree_topPt",	      &topPt_tmp);
  theZctTree->SetBranchAddress( "tree_topEta",	      &topEta_tmp);
  theZctTree->SetBranchAddress( "tree_NJets",	      &NJets_tmp);
  theZctTree->SetBranchAddress( "tree_NBJets",	      &NBJets_tmp);		
  theZctTree->SetBranchAddress( "tree_deltaRZl",      &deltaRZl_tmp);   
  theZctTree->SetBranchAddress( "tree_deltaPhiZmet",  &deltaPhiZmet_tmp);
  theZctTree->SetBranchAddress( "tree_btagDiscri",    &btagDiscri_tmp);
  
  theZctTree->SetBranchAddress("tree_leptWPt",	      &leptWPt_tmp);	       
  theZctTree->SetBranchAddress("tree_leptWEta",	      &leptWEta_tmp);	       
  theZctTree->SetBranchAddress("tree_leadJetPt",      &leadJetPt_tmp);		 
  theZctTree->SetBranchAddress("tree_leadJetEta",     &leadJetEta_tmp); 	
  theZctTree->SetBranchAddress("tree_deltaPhiZleptW", &deltaPhiZleptW_tmp);
  theZctTree->SetBranchAddress("tree_EvtWeight",      &EvtWeight_tmp);
  
  
  
  
  for (Long64_t ievt=0; ievt<theZctTree->GetEntries();ievt++) { 
    
    if(ievt > nstop) break;
    double ratio = (theCrossSections.first*eff_Zut/ (theCrossSections.first*eff_Zut + theCrossSections.second*eff_Zct) );
    if( r.Uniform() <  ratio ) continue;
    
    theZctTree->GetEntry(ievt);
    
    topMass        = topMass_tmp;
    deltaPhilb     = deltaPhilb_tmp;
    asym           = asym_tmp;
    Zpt            = Zpt_tmp; 
    deltaRlb       = deltaRlb_tmp;
    deltaRTopZ     = deltaRTopZ_tmp;
    ZEta           = ZEta_tmp; 
    topPt          = topPt_tmp;
    topEta         = topEta_tmp;
    totMass        = totMass_tmp;
    deltaRZl       = deltaRZl_tmp; 
    deltaPhiZmet   = deltaPhiZmet_tmp; 
    btagDiscri     = btagDiscri_tmp; 
    NJets          = NJets_tmp; 
    NBJets         = NBJets_tmp; 
    EvtWeight      = EvtWeight_tmp;
    leptWPt        = leptWPt_tmp;
    leptWEta       = leptWEta_tmp;
    leadJetPt      = leadJetPt_tmp;
    leadJetEta     = leadJetEta_tmp;
    deltaRZleptW   = deltaRZleptW_tmp;
    deltaPhiZleptW = deltaPhiZleptW_tmp;
    EvtWeight      = EvtWeight_tmp* ( nstop/double(theZctTree->GetEntries())  ) ;
    outputTree->Fill();
  }
  
  
  
  
  outputTree->Write();
  
  std::cout << "production done "<< std::endl;
  
  delete outputTree;
  delete  output;
}





void produceBenchmark(TFile *input_FCNC, TString syst){

  
 TTree* theTree_Zut = (TTree*)input_FCNC->Get("Ttree_FCNCzut");
 TTree* theTree_Zct = (TTree*)input_FCNC->Get("Ttree_FCNCzct");
 
 std::vector<double> bench_Zut, bench_Zct;
 
 for(int bench=0; bench<6;   bench++){
   bench_Zut.push_back((bench)*0.00004);
 }
 for(int bench=0; bench<6; bench++){
   bench_Zct.push_back((bench)*0.0004);
 }
 
 for(unsigned int ibench = 0; ibench<bench_Zut.size(); ibench++){
   for(unsigned int jbench = 0; jbench<bench_Zct.size(); jbench++){
     
     if(bench_Zut[ibench] == 0 & bench_Zct[jbench]==0 ) continue;
     
     produceBenchmark(theTree_Zut, theTree_Zct, bench_Zut[ibench], bench_Zct[jbench], syst); 
   } 
 }
 
}



void produceBenchmark(){

 TFile *input_FCNC    = new TFile("../RootFiles/backup_outputProof22-12-12_12-00-55_nom_FakeSFOnly/proof_merged_FakeSFOnly.root", "read");
 produceBenchmark(input_FCNC, "nom");
 
 
}




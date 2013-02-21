#include "TH1F.h"
#include "TFile.h"

#include "TString.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include <iostream>

void prodtemplate(){
  
  // using namespace RooFit;
  // using namespace RooStats;
  
  
  //////////////////////////////////////////////////////////////////////////////////////////////////
  
  
  double WZscaleFacor = 4.0;
  double datasf       = 4.0;
  double ZjetscaleFacor = 4.0;
  double ZZscaleFacor   = 4.0;
  double TTbarscaleFacor= 4.0;
  
  
  TFile * nomFile       = new TFile("inputFiles/TMVApp_zut_nom.root"      );
  TFile * nomJES_up     = new TFile("inputFiles/TMVApp_zut_JESup.root"    );
  TFile * nomJES_down   = new TFile("inputFiles/TMVApp_zut_JESdown.root"  );
  TFile * nomJER        = new TFile("inputFiles/TMVApp_zut_JER.root"      );
  TFile * nomLept       = new TFile("inputFiles/TMVApp_zut_LeptSF.root"   );
  TFile * nomPU_up      = new TFile("inputFiles/TMVApp_zut_PUup.root"     );
  TFile * nomPU_down    = new TFile("inputFiles/TMVApp_zut_PUdown.root"   );
  TFile * nomBTag_up    = new TFile("inputFiles/TMVApp_zut_btagup.root"   );
  TFile * nomBTag_down  = new TFile("inputFiles/TMVApp_zut_btagdown.root" );
  
  
  
  //-----------------------------------------------
  //nominal templates 
  TH1F histo_Data;
  TH1F histo_Zjets;
  TH1F histo_ZjetsMC;
  TH1F histo_WZ ;
  TH1F histo_Sig;
  TH1F histo_TTbar;
  TH1F histo_ZZ;       
  
  
  //-----------------------------------------------
  //templates for JES
  TH1F  histo_TTbar_JES_up;
  TH1F  histo_TTbar_JES_down;
  TH1F  histo_ZZ_JES_up;
  TH1F  histo_ZZ_JES_down;
  TH1F  histo_WZ_JES_up;
  TH1F  histo_WZ_JES_down;
  TH1F  histo_Sig_JES_up;
  TH1F  histo_Sig_JES_down;
  
  
  //-----------------------------------------------
  //templates for JER
  TH1F  histo_TTbar_JER_up;
  TH1F  histo_ZZ_JER_up;
  TH1F  histo_WZ_JER_up;
  TH1F  histo_Sig_JER_up;
  
  TH1F  histo_TTbar_JER_down;
  TH1F  histo_ZZ_JER_down;
  TH1F  histo_WZ_JER_down;
  TH1F  histo_Sig_JER_down;
  
  
  
  //-----------------------------------------------
  //templates for BTag
  TH1F  histo_TTbar_BTag_up;
  TH1F  histo_TTbar_BTag_down;
  TH1F  histo_ZZ_BTag_up;
  TH1F  histo_ZZ_BTag_down;
  TH1F  histo_WZ_BTag_up;
  TH1F  histo_WZ_BTag_down;
  TH1F  histo_Sig_BTag_up;
  TH1F  histo_Sig_BTag_down;
  
  
  
  //-----------------------------------------------
  //templates for PU
  TH1F  histo_TTbar_PU_up;
  TH1F  histo_TTbar_PU_down;
  TH1F  histo_ZZ_PU_up;
  TH1F  histo_ZZ_PU_down;
  TH1F  histo_WZ_PU_up;
  TH1F  histo_WZ_PU_down;
  TH1F  histo_Sig_PU_up;
  TH1F  histo_Sig_PU_down;
  
  
  
  //-----------------------------------------------
  //templates for LeptSF
  TH1F  histo_TTbar_Lept_up;
  TH1F  histo_TTbar_Lept_down;
  TH1F  histo_ZZ_Lept_up;
  TH1F  histo_ZZ_Lept_down;
  TH1F  histo_WZ_Lept_up;
  TH1F  histo_WZ_Lept_down;
  TH1F  histo_Sig_Lept_up;
  TH1F  histo_Sig_Lept_down;
  
  cout << "line 113 " << endl;
  
  //-----------------------------------------------
  //templates for DY
  TH1F * histo_DataZjets;
  
  nomFile->cd();
  cout << "line 121 " << endl;
  //histo_Data = *(TH1F*)nomFile->Get("MVA_BDT_Data");
  //histo_Data.Scale(datasf);
  histo_Zjets               = *(TH1F*)nomFile->Get("MVA_BDT_DataZjets");
  histo_ZjetsMC             = *(TH1F*)nomFile->Get("MVA_BDT_Zjets");
  histo_Zjets.Scale(histo_ZjetsMC.Integral()/histo_Zjets.Integral());
  histo_Zjets.Scale(ZjetscaleFacor);
  
  histo_WZ                  = *(TH1F*)nomFile->Get("MVA_BDT_WZ");
  histo_WZ.Scale(WZscaleFacor);  
  histo_Sig                 = *(TH1F*)nomFile->Get("MVA_BDT_FCNC_zut");
  histo_TTbar               = *(TH1F*)nomFile->Get("MVA_BDT_TTbarSig");
  histo_TTbar.Scale(TTbarscaleFacor);
  histo_ZZ                  = *(TH1F*)nomFile->Get("MVA_BDT_ZZ");
  histo_ZZ.Scale(ZZscaleFacor);
  
  
  histo_Data = histo_WZ;
  histo_Data.Add(&histo_TTbar);
  histo_Data.Add(&histo_ZZ);
  histo_Data.Add(&histo_Zjets);
  
  
  //histo_Data.Scale(datasf);
  
  cout << "line 132 " << endl;
  //-----------------------------------------------
  //template for JES up
  nomJES_up->cd();
  
  histo_TTbar_JES_up = *(TH1F*)nomJES_up->Get("MVA_BDT_TTbarSig");
  histo_ZZ_JES_up    = *(TH1F*)nomJES_up->Get("MVA_BDT_ZZ"   );
  histo_WZ_JES_up    = *(TH1F*)nomJES_up->Get("MVA_BDT_WZ"   );
  histo_WZ_JES_up.Scale(WZscaleFacor);  
  histo_Sig_JES_up   = *(TH1F*)nomJES_up->Get("MVA_BDT_FCNC_zut"  );
  
  
  //-----------------------------------------------
  //template for JES down
  nomJES_down->cd();
  
  histo_TTbar_JES_down = *(TH1F*)nomJES_down->Get("MVA_BDT_TTbarSig");
  histo_ZZ_JES_down    = *(TH1F*)nomJES_down->Get("MVA_BDT_ZZ"   );
  histo_WZ_JES_down    = *(TH1F*)nomJES_down->Get("MVA_BDT_WZ"   );
  histo_WZ_JES_down.Scale(WZscaleFacor);  
  histo_Sig_JES_down   = *(TH1F*)nomJES_down->Get("MVA_BDT_FCNC_zut"  );
  
  
  
  cout << "line 154 " << endl;
  //-----------------------------------------------
  //template for JER
  nomJER->cd();
  
  histo_TTbar_JER_up = *(TH1F*)nomJER->Get("MVA_BDT_TTbarSig");
  histo_ZZ_JER_up    = *(TH1F*)nomJER->Get("MVA_BDT_ZZ"   );
  histo_WZ_JER_up    = *(TH1F*)nomJER->Get("MVA_BDT_WZ"   );
  histo_WZ_JER_up.Scale(WZscaleFacor);  
  histo_Sig_JER_up   = *(TH1F*)nomJER->Get("MVA_BDT_FCNC_zut"  );
  
  
  nomFile->cd();
  histo_TTbar_JER_down = *(TH1F*)nomFile->Get("MVA_BDT_TTbarSig");
  histo_ZZ_JER_down    = *(TH1F*)nomFile->Get("MVA_BDT_ZZ"   );
  histo_WZ_JER_down    = *(TH1F*)nomFile->Get("MVA_BDT_WZ"   );
  histo_WZ_JER_down.Scale(WZscaleFacor);  
  histo_Sig_JER_down   = *(TH1F*)nomFile->Get("MVA_BDT_FCNC_zut"  );
  
  
  cout << "line 172 " << endl;
  //-----------------------------------------------
  //template for BTag up
  nomBTag_up->cd();
  
  histo_TTbar_BTag_up = *(TH1F*)nomBTag_up->Get("MVA_BDT_TTbarSig");
  histo_ZZ_BTag_up    = *(TH1F*)nomBTag_up->Get("MVA_BDT_ZZ"   );
  histo_WZ_BTag_up    = *(TH1F*)nomBTag_up->Get("MVA_BDT_WZ"   );
  histo_WZ_BTag_up.Scale(WZscaleFacor);  
  histo_Sig_BTag_up   = *(TH1F*)nomBTag_up->Get("MVA_BDT_FCNC_zut"  );
  
  
  //-----------------------------------------------
  //template for BTag down
  nomBTag_down->cd();
  
  histo_TTbar_BTag_down = *(TH1F*)nomBTag_down->Get("MVA_BDT_TTbarSig");
  histo_ZZ_BTag_down    = *(TH1F*)nomBTag_down->Get("MVA_BDT_ZZ"   );
  histo_WZ_BTag_down    = *(TH1F*)nomBTag_down->Get("MVA_BDT_WZ"   );
  histo_WZ_BTag_down.Scale(WZscaleFacor);  
  histo_Sig_BTag_down   = *(TH1F*)nomBTag_down->Get("MVA_BDT_FCNC_zut"  );
  
  
  cout << "line 193 " << endl;
  
  //-----------------------------------------------
  //template for PU up
  nomPU_up->cd();
  
  histo_TTbar_PU_up = *(TH1F*)nomPU_up->Get("MVA_BDT_TTbarSig");
  histo_ZZ_PU_up    = *(TH1F*)nomPU_up->Get("MVA_BDT_ZZ"   );
  histo_WZ_PU_up    = *(TH1F*)nomPU_up->Get("MVA_BDT_WZ"   );
  histo_WZ_PU_up.Scale(WZscaleFacor);  
  histo_Sig_PU_up   = *(TH1F*)nomPU_up->Get("MVA_BDT_FCNC_zut"  );
  
  
  //-----------------------------------------------
  //template for PU down
  nomPU_down->cd();
  
  histo_TTbar_PU_down = *(TH1F*)nomPU_down->Get("MVA_BDT_TTbarSig");
  histo_ZZ_PU_down    = *(TH1F*)nomPU_down->Get("MVA_BDT_ZZ"   );
  histo_WZ_PU_down    = *(TH1F*)nomPU_down->Get("MVA_BDT_WZ"   );
  histo_WZ_PU_down.Scale(WZscaleFacor);  
  histo_Sig_PU_down   = *(TH1F*)nomPU_down->Get("MVA_BDT_FCNC_zut"  );
  
  
  
    
  cout << "line 217" << endl;
  
  //-----------------------------------------------
  //template for Lept up
  nomLept->cd();
  
  histo_TTbar_Lept_up = *(TH1F*)nomLept->Get("MVA_BDT_TTbarSig");
  histo_ZZ_Lept_up    = *(TH1F*)nomLept->Get("MVA_BDT_ZZ"   );
  histo_WZ_Lept_up    = *(TH1F*)nomLept->Get("MVA_BDT_WZ"   );
  histo_WZ_Lept_up.Scale(WZscaleFacor);  
  histo_Sig_Lept_up   = *(TH1F*)nomLept->Get("MVA_BDT_FCNC_zut"  );
  
  
  //-----------------------------------------------
  //template for Lept down
  nomFile->cd();
  
  histo_TTbar_Lept_down = *(TH1F*)nomFile->Get("MVA_BDT_TTbarSig");
  histo_ZZ_Lept_down    = *(TH1F*)nomFile->Get("MVA_BDT_ZZ"   );
  histo_WZ_Lept_down    = *(TH1F*)nomFile->Get("MVA_BDT_WZ"   );
  histo_WZ_Lept_down.Scale(WZscaleFacor);  
  histo_Sig_Lept_down   = *(TH1F*)nomFile->Get("MVA_BDT_FCNC_zut"  );
  
  
  
  
  
  cout << "125 " << endl;
  
  // Needed by Theta: correct empty bins of the model corresponding to non empty bins for the data (if not, Theta crashs)
  for (int k = 1; k < histo_Sig.GetNbinsX()+1; k++) {
  
    if ( histo_Sig.GetBinContent(k)  <=0 ) histo_Sig.SetBinContent(  k,0.000001);
    if ( histo_Data.GetBinContent(k) <=0 ) histo_Data.SetBinContent( k,0.000001);
    if ( histo_Zjets.GetBinContent(k)<=0 ) histo_Zjets.SetBinContent(k,0.000001);
    if ( histo_WZ.GetBinContent(k)   <=0 ) histo_WZ.SetBinContent(   k,0.000001);
    if ( histo_ZZ.GetBinContent(k)   <=0 ) histo_ZZ.SetBinContent(   k,0.000001);    
    if ( histo_TTbar.GetBinContent(k)<=0 ) histo_TTbar.SetBinContent(k,0.000001);
    
    
    if ( histo_TTbar_JES_up.GetBinContent(k)  <=0 ) histo_TTbar_JES_up.SetBinContent(k,0.000001);
    if ( histo_ZZ_JES_up.GetBinContent(k)     <=0 ) histo_ZZ_JES_up.SetBinContent(   k,0.000001); 
    if ( histo_WZ_JES_up.GetBinContent(k)     <=0 ) histo_WZ_JES_up.SetBinContent(   k,0.000001); 
    if ( histo_Sig_JES_up.GetBinContent(k)    <=0 ) histo_Sig_JES_up.SetBinContent(  k,0.000001);
    
    if ( histo_TTbar_JES_down.GetBinContent(k)  <=0 ) histo_TTbar_JES_down.SetBinContent(k,0.000001);
    if ( histo_ZZ_JES_down.GetBinContent(k)     <=0 ) histo_ZZ_JES_down.SetBinContent(   k,0.000001);
    if ( histo_WZ_JES_down.GetBinContent(k)     <=0 ) histo_WZ_JES_down.SetBinContent(   k,0.000001);  
    if ( histo_Sig_JES_down.GetBinContent(k)    <=0 ) histo_Sig_JES_down.SetBinContent(  k,0.000001);
    
    
   
    if ( histo_TTbar_JER_up.GetBinContent(k)  <=0 ) histo_TTbar_JER_up.SetBinContent(k,0.000001);
    if ( histo_ZZ_JER_up.GetBinContent(k)     <=0 ) histo_ZZ_JER_up.SetBinContent(   k,0.000001);
    if ( histo_WZ_JER_up.GetBinContent(k)     <=0 ) histo_WZ_JER_up.SetBinContent(   k,0.000001);
    if ( histo_Sig_JER_up.GetBinContent(k)    <=0 ) histo_Sig_JER_up.SetBinContent(  k,0.000001);
    
    if ( histo_TTbar_JER_down.GetBinContent(k)  <=0 ) histo_TTbar_JER_down.SetBinContent(k,0.000001);
    if ( histo_ZZ_JER_down.GetBinContent(k)     <=0 ) histo_ZZ_JER_down.SetBinContent(   k,0.000001);	
    if ( histo_WZ_JER_down.GetBinContent(k)     <=0 ) histo_WZ_JER_down.SetBinContent(   k,0.000001);	
    if ( histo_Sig_JER_down.GetBinContent(k)    <=0 ) histo_Sig_JER_down.SetBinContent(  k,0.000001);	
     
    
    if ( histo_TTbar_BTag_up.GetBinContent(k)  <=0 ) histo_TTbar_BTag_up.SetBinContent(k,0.000001);
    if ( histo_ZZ_BTag_up.GetBinContent(k)     <=0 ) histo_ZZ_BTag_up.SetBinContent(   k,0.000001); 
    if ( histo_WZ_BTag_up.GetBinContent(k)     <=0 ) histo_WZ_BTag_up.SetBinContent(   k,0.000001); 
    if ( histo_Sig_BTag_up.GetBinContent(k)    <=0 ) histo_Sig_BTag_up.SetBinContent(  k,0.000001);
    
    if ( histo_TTbar_BTag_down.GetBinContent(k)  <=0 ) histo_TTbar_BTag_down.SetBinContent(k,0.000001);
    if ( histo_ZZ_BTag_down.GetBinContent(k)     <=0 ) histo_ZZ_BTag_down.SetBinContent(   k,0.000001);
    if ( histo_WZ_BTag_down.GetBinContent(k)     <=0 ) histo_WZ_BTag_down.SetBinContent(   k,0.000001);  
    if ( histo_Sig_BTag_down.GetBinContent(k)    <=0 ) histo_Sig_BTag_down.SetBinContent(  k,0.000001);
     
    
    if ( histo_TTbar_PU_up.GetBinContent(k)  <=0 ) histo_TTbar_PU_up.SetBinContent(k,0.000001);
    if ( histo_ZZ_PU_up.GetBinContent(k)     <=0 ) histo_ZZ_PU_up.SetBinContent(   k,0.000001); 
    if ( histo_WZ_PU_up.GetBinContent(k)     <=0 ) histo_WZ_PU_up.SetBinContent(   k,0.000001); 
    if ( histo_Sig_PU_up.GetBinContent(k)    <=0 ) histo_Sig_PU_up.SetBinContent(  k,0.000001);
    
    if ( histo_TTbar_PU_down.GetBinContent(k)  <=0 ) histo_TTbar_PU_down.SetBinContent(k,0.000001);
    if ( histo_ZZ_PU_down.GetBinContent(k)     <=0 ) histo_ZZ_PU_down.SetBinContent(   k,0.000001);
    if ( histo_WZ_PU_down.GetBinContent(k)     <=0 ) histo_WZ_PU_down.SetBinContent(   k,0.000001);  
    if ( histo_Sig_PU_down.GetBinContent(k)    <=0 ) histo_Sig_PU_down.SetBinContent(  k,0.000001);
     
    
    if ( histo_TTbar_Lept_up.GetBinContent(k)  <=0 ) histo_TTbar_Lept_up.SetBinContent(k,0.000001);
    if ( histo_ZZ_Lept_up.GetBinContent(k)     <=0 ) histo_ZZ_Lept_up.SetBinContent(   k,0.000001); 
    if ( histo_WZ_Lept_up.GetBinContent(k)     <=0 ) histo_WZ_Lept_up.SetBinContent(   k,0.000001); 
    if ( histo_Sig_Lept_up.GetBinContent(k)    <=0 ) histo_Sig_Lept_up.SetBinContent(  k,0.000001);
    
    if ( histo_TTbar_Lept_down.GetBinContent(k)  <=0 ) histo_TTbar_Lept_down.SetBinContent(k,0.000001);
    if ( histo_ZZ_Lept_down.GetBinContent(k)     <=0 ) histo_ZZ_Lept_down.SetBinContent(   k,0.000001);
    if ( histo_WZ_Lept_down.GetBinContent(k)     <=0 ) histo_WZ_Lept_down.SetBinContent(   k,0.000001);  
    if ( histo_Sig_Lept_down.GetBinContent(k)    <=0 ) histo_Sig_Lept_down.SetBinContent(  k,0.000001);
  }
  
  
  histo_Sig.SetName  ("MVABDT__FCNC_zut57" );
  histo_Data.SetName ("MVABDT__DATA"      );
  histo_Zjets.SetName("MVABDT__DataZjets" );
  histo_WZ.SetName   ("MVABDT__WZ"        );
  histo_ZZ.SetName   ("MVABDT__ZZ"        );
  histo_TTbar.SetName("MVABDT__TTbar"     );
  
  
  
  
  
  histo_Sig_JES_up.SetName  ("MVABDT__FCNC_zut57__JES__plus" );
  histo_WZ_JES_up.SetName   ("MVABDT__WZ__JES__plus"        );
  histo_ZZ_JES_up.SetName   ("MVABDT__ZZ__JES__plus"        );
  histo_TTbar_JES_up.SetName("MVABDT__TTbar__JES__plus"     );
  
  histo_Sig_JES_down.SetName  ("MVABDT__FCNC_zut57__JES__minus" );
  histo_WZ_JES_down.SetName   ("MVABDT__WZ__JES__minus"        );
  histo_ZZ_JES_down.SetName   ("MVABDT__ZZ__JES__minus"        );
  histo_TTbar_JES_down.SetName("MVABDT__TTbar__JES__minus"     );
  
  
  
  histo_Sig_JER_up.SetName  ("MVABDT__FCNC_zut57__JER__plus" );
  histo_WZ_JER_up.SetName   ("MVABDT__WZ__JER__plus"        );
  histo_ZZ_JER_up.SetName   ("MVABDT__ZZ__JER__plus"        );
  histo_TTbar_JER_up.SetName("MVABDT__TTbar__JER__plus"     );
  
  
  
  
  histo_Sig_JER_down.SetName  ("MVABDT__FCNC_zut57__JER__minus" );
  histo_WZ_JER_down.SetName   ("MVABDT__WZ__JER__minus"        );
  histo_ZZ_JER_down.SetName   ("MVABDT__ZZ__JER__minus"        );
  histo_TTbar_JER_down.SetName("MVABDT__TTbar__JER__minus"     );
 
  
  
  
  histo_Sig_BTag_up.SetName  ("MVABDT__FCNC_zut57__BTag__plus" );
  histo_WZ_BTag_up.SetName   ("MVABDT__WZ__BTag__plus"        );
  histo_ZZ_BTag_up.SetName   ("MVABDT__ZZ__BTag__plus"        );
  histo_TTbar_BTag_up.SetName("MVABDT__TTbar__BTag__plus"     );
  
  histo_Sig_BTag_down.SetName  ("MVABDT__FCNC_zut57__BTag__minus" );
  histo_WZ_BTag_down.SetName   ("MVABDT__WZ__BTag__minus"        );
  histo_ZZ_BTag_down.SetName   ("MVABDT__ZZ__BTag__minus"        );
  histo_TTbar_BTag_down.SetName("MVABDT__TTbar__BTag__minus"     );
  
  
  
  
  histo_Sig_PU_up.SetName  ("MVABDT__FCNC_zut57__PU__plus" );
  histo_WZ_PU_up.SetName   ("MVABDT__WZ__PU__plus"        );
  histo_ZZ_PU_up.SetName   ("MVABDT__ZZ__PU__plus"        );
  histo_TTbar_PU_up.SetName("MVABDT__TTbar__PU__plus"     );
  
  histo_Sig_PU_down.SetName  ("MVABDT__FCNC_zut57__PU__minus" );
  histo_WZ_PU_down.SetName   ("MVABDT__WZ__PU__minus"        );
  histo_ZZ_PU_down.SetName   ("MVABDT__ZZ__PU__minus"        );
  histo_TTbar_PU_down.SetName("MVABDT__TTbar__PU__minus"     );
  
  
  
  histo_Sig_Lept_up.SetName  ("MVABDT__FCNC_zut57__Lept__plus" );
  histo_WZ_Lept_up.SetName   ("MVABDT__WZ__Lept__plus"        );
  histo_ZZ_Lept_up.SetName   ("MVABDT__ZZ__Lept__plus"        );
  histo_TTbar_Lept_up.SetName("MVABDT__TTbar__Lept__plus"     );
  
  histo_Sig_Lept_down.SetName  ("MVABDT__FCNC_zut57__Lept__minus" );
  histo_WZ_Lept_down.SetName   ("MVABDT__WZ__Lept__minus"        );
  histo_ZZ_Lept_down.SetName   ("MVABDT__ZZ__Lept__minus"        );
  histo_TTbar_Lept_down.SetName("MVABDT__TTbar__Lept__minus"     );
  
  // Add 2 additionnal points  
  
  
  TH1F *  histo_Sig_05   = new TH1F ("histo_Sig_05", "histo_Sig_05", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10   = new TH1F ("histo_Sig_10", "histo_Sig_10", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20   = new TH1F ("histo_Sig_20", "histo_Sig_20", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30   = new TH1F ("histo_Sig_30", "histo_Sig_30", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50   = new TH1F ("histo_Sig_50", "histo_Sig_50", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
  
  
  TH1F *  histo_Sig_05_JES_up   = new TH1F ("histo_Sig_05_JES_up", "histo_Sig_05_JES_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_JES_up   = new TH1F ("histo_Sig_10_JES_up", "histo_Sig_10_JES_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_JES_up   = new TH1F ("histo_Sig_20_JES_up", "histo_Sig_20_JES_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_JES_up   = new TH1F ("histo_Sig_30_JES_up", "histo_Sig_30_JES_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_JES_up   = new TH1F ("histo_Sig_50_JES_up", "histo_Sig_50_JES_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
 
 
  
  TH1F *  histo_Sig_05_JES_down   = new TH1F ("histo_Sig_05_JES_down", "histo_Sig_05_JES_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_JES_down   = new TH1F ("histo_Sig_10_JES_down", "histo_Sig_10_JES_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_JES_down   = new TH1F ("histo_Sig_20_JES_down", "histo_Sig_20_JES_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_JES_down   = new TH1F ("histo_Sig_30_JES_down", "histo_Sig_30_JES_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_JES_down   = new TH1F ("histo_Sig_50_JES_down", "histo_Sig_50_JES_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
 
  
  TH1F *  histo_Sig_05_JER_up   = new TH1F ("histo_Sig_05_JER_up", "histo_Sig_05_JER_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_JER_up   = new TH1F ("histo_Sig_10_JER_up", "histo_Sig_10_JER_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_JER_up   = new TH1F ("histo_Sig_20_JER_up", "histo_Sig_20_JER_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_JER_up   = new TH1F ("histo_Sig_30_JER_up", "histo_Sig_30_JER_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_JER_up   = new TH1F ("histo_Sig_50_JER_up", "histo_Sig_50_JER_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
 
 
  
  TH1F *  histo_Sig_05_JER_down   = new TH1F ("histo_Sig_05_JER_down", "histo_Sig_05_JER_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_JER_down   = new TH1F ("histo_Sig_10_JER_down", "histo_Sig_10_JER_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_JER_down   = new TH1F ("histo_Sig_20_JER_down", "histo_Sig_20_JER_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_JER_down   = new TH1F ("histo_Sig_30_JER_down", "histo_Sig_30_JER_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_JER_down   = new TH1F ("histo_Sig_50_JER_down", "histo_Sig_50_JER_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  


   
  TH1F *  histo_Sig_05_BTag_up   = new TH1F ("histo_Sig_05_BTag_up", "histo_Sig_05_BTag_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_BTag_up   = new TH1F ("histo_Sig_10_BTag_up", "histo_Sig_10_BTag_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_BTag_up   = new TH1F ("histo_Sig_20_BTag_up", "histo_Sig_20_BTag_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_BTag_up   = new TH1F ("histo_Sig_30_BTag_up", "histo_Sig_30_BTag_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_BTag_up   = new TH1F ("histo_Sig_50_BTag_up", "histo_Sig_50_BTag_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );

  
  TH1F *  histo_Sig_05_BTag_down   = new TH1F ("histo_Sig_05_BTag_down", "histo_Sig_05_BTag_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_BTag_down   = new TH1F ("histo_Sig_10_BTag_down", "histo_Sig_10_BTag_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_BTag_down   = new TH1F ("histo_Sig_20_BTag_down", "histo_Sig_20_BTag_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_BTag_down   = new TH1F ("histo_Sig_30_BTag_down", "histo_Sig_30_BTag_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_BTag_down   = new TH1F ("histo_Sig_50_BTag_down", "histo_Sig_50_BTag_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
   
  TH1F *  histo_Sig_05_PU_up   = new TH1F ("histo_Sig_05_PU_up", "histo_Sig_05_PU_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_PU_up   = new TH1F ("histo_Sig_10_PU_up", "histo_Sig_10_PU_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_PU_up   = new TH1F ("histo_Sig_20_PU_up", "histo_Sig_20_PU_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_PU_up   = new TH1F ("histo_Sig_30_PU_up", "histo_Sig_30_PU_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_PU_up   = new TH1F ("histo_Sig_50_PU_up", "histo_Sig_50_PU_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
 
 
  
  TH1F *  histo_Sig_05_PU_down   = new TH1F ("histo_Sig_05_PU_down", "histo_Sig_05_PU_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_PU_down   = new TH1F ("histo_Sig_10_PU_down", "histo_Sig_10_PU_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_PU_down   = new TH1F ("histo_Sig_20_PU_down", "histo_Sig_20_PU_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_PU_down   = new TH1F ("histo_Sig_30_PU_down", "histo_Sig_30_PU_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_PU_down   = new TH1F ("histo_Sig_50_PU_down", "histo_Sig_50_PU_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
   
  TH1F *  histo_Sig_05_Lept_up   = new TH1F ("histo_Sig_05_Lept_up", "histo_Sig_05_Lept_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_Lept_up   = new TH1F ("histo_Sig_10_Lept_up", "histo_Sig_10_Lept_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_Lept_up   = new TH1F ("histo_Sig_20_Lept_up", "histo_Sig_20_Lept_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_Lept_up   = new TH1F ("histo_Sig_30_Lept_up", "histo_Sig_30_Lept_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_Lept_up   = new TH1F ("histo_Sig_50_Lept_up", "histo_Sig_50_Lept_up", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
 
 
  
  TH1F *  histo_Sig_05_Lept_down   = new TH1F ("histo_Sig_05_Lept_down", "histo_Sig_05_Lept_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_10_Lept_down   = new TH1F ("histo_Sig_10_Lept_down", "histo_Sig_10_Lept_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_20_Lept_down   = new TH1F ("histo_Sig_20_Lept_down", "histo_Sig_20_Lept_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_30_Lept_down   = new TH1F ("histo_Sig_30_Lept_down", "histo_Sig_30_Lept_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  TH1F *  histo_Sig_50_Lept_down   = new TH1F ("histo_Sig_50_Lept_down", "histo_Sig_50_Lept_down", histo_Sig.GetXaxis()->GetNbins(),histo_Sig.GetXaxis()->GetXmin(),       histo_Sig.GetXaxis()->GetXmax() );
  
   
  

 

  for (int k = 1; k < histo_Sig.GetNbinsX()+1; k++) {
  
  
    histo_Sig_05->SetBinContent(k,05.*histo_Sig.GetBinContent(k)/histo_Sig.Integral());
    histo_Sig_10->SetBinContent(k,10.*histo_Sig.GetBinContent(k)/histo_Sig.Integral());
    histo_Sig_20->SetBinContent(k,20.*histo_Sig.GetBinContent(k)/histo_Sig.Integral());
    histo_Sig_30->SetBinContent(k,30.*histo_Sig.GetBinContent(k)/histo_Sig.Integral());
    histo_Sig_50->SetBinContent(k,50.*histo_Sig.GetBinContent(k)/histo_Sig.Integral());
    
    
    histo_Sig_05_JES_up->SetBinContent(k,05.*histo_Sig_JES_up.GetBinContent(k)/histo_Sig_JES_up.Integral());
    histo_Sig_10_JES_up->SetBinContent(k,10.*histo_Sig_JES_up.GetBinContent(k)/histo_Sig_JES_up.Integral());
    histo_Sig_20_JES_up->SetBinContent(k,20.*histo_Sig_JES_up.GetBinContent(k)/histo_Sig_JES_up.Integral());
    histo_Sig_30_JES_up->SetBinContent(k,30.*histo_Sig_JES_up.GetBinContent(k)/histo_Sig_JES_up.Integral());
    histo_Sig_50_JES_up->SetBinContent(k,50.*histo_Sig_JES_up.GetBinContent(k)/histo_Sig_JES_up.Integral());
    
    histo_Sig_05_JES_down->SetBinContent(k,05.*histo_Sig_JES_down.GetBinContent(k)/histo_Sig_JES_down.Integral());
    histo_Sig_10_JES_down->SetBinContent(k,10.*histo_Sig_JES_down.GetBinContent(k)/histo_Sig_JES_down.Integral());
    histo_Sig_20_JES_down->SetBinContent(k,20.*histo_Sig_JES_down.GetBinContent(k)/histo_Sig_JES_down.Integral());
    histo_Sig_30_JES_down->SetBinContent(k,30.*histo_Sig_JES_down.GetBinContent(k)/histo_Sig_JES_down.Integral());
    histo_Sig_50_JES_down->SetBinContent(k,50.*histo_Sig_JES_down.GetBinContent(k)/histo_Sig_JES_down.Integral());
    
    histo_Sig_05_JER_up->SetBinContent(k,05.*histo_Sig_JER_up.GetBinContent(k)/histo_Sig_JER_up.Integral());
    histo_Sig_10_JER_up->SetBinContent(k,10.*histo_Sig_JER_up.GetBinContent(k)/histo_Sig_JER_up.Integral());
    histo_Sig_20_JER_up->SetBinContent(k,20.*histo_Sig_JER_up.GetBinContent(k)/histo_Sig_JER_up.Integral());
    histo_Sig_30_JER_up->SetBinContent(k,30.*histo_Sig_JER_up.GetBinContent(k)/histo_Sig_JER_up.Integral());
    histo_Sig_50_JER_up->SetBinContent(k,50.*histo_Sig_JER_up.GetBinContent(k)/histo_Sig_JER_up.Integral());
    
    histo_Sig_05_JER_down->SetBinContent(k,05.*histo_Sig_JER_down.GetBinContent(k)/histo_Sig_JER_down.Integral());
    histo_Sig_10_JER_down->SetBinContent(k,10.*histo_Sig_JER_down.GetBinContent(k)/histo_Sig_JER_down.Integral());
    histo_Sig_20_JER_down->SetBinContent(k,20.*histo_Sig_JER_down.GetBinContent(k)/histo_Sig_JER_down.Integral());
    histo_Sig_30_JER_down->SetBinContent(k,30.*histo_Sig_JER_down.GetBinContent(k)/histo_Sig_JER_down.Integral());
    histo_Sig_50_JER_down->SetBinContent(k,50.*histo_Sig_JER_down.GetBinContent(k)/histo_Sig_JER_down.Integral());
    
    
    histo_Sig_05_BTag_up->SetBinContent(k,05.*histo_Sig_BTag_up.GetBinContent(k)/histo_Sig_BTag_up.Integral());
    histo_Sig_10_BTag_up->SetBinContent(k,10.*histo_Sig_BTag_up.GetBinContent(k)/histo_Sig_BTag_up.Integral());
    histo_Sig_20_BTag_up->SetBinContent(k,20.*histo_Sig_BTag_up.GetBinContent(k)/histo_Sig_BTag_up.Integral());
    histo_Sig_30_BTag_up->SetBinContent(k,30.*histo_Sig_BTag_up.GetBinContent(k)/histo_Sig_BTag_up.Integral());
    histo_Sig_50_BTag_up->SetBinContent(k,50.*histo_Sig_BTag_up.GetBinContent(k)/histo_Sig_BTag_up.Integral());
    
    histo_Sig_05_BTag_down->SetBinContent(k,05.*histo_Sig_BTag_down.GetBinContent(k)/histo_Sig_BTag_down.Integral());
    histo_Sig_10_BTag_down->SetBinContent(k,10.*histo_Sig_BTag_down.GetBinContent(k)/histo_Sig_BTag_down.Integral());
    histo_Sig_20_BTag_down->SetBinContent(k,20.*histo_Sig_BTag_down.GetBinContent(k)/histo_Sig_BTag_down.Integral());
    histo_Sig_30_BTag_down->SetBinContent(k,30.*histo_Sig_BTag_down.GetBinContent(k)/histo_Sig_BTag_down.Integral());
    histo_Sig_50_BTag_down->SetBinContent(k,50.*histo_Sig_BTag_down.GetBinContent(k)/histo_Sig_BTag_down.Integral());
    
    histo_Sig_05_Lept_up->SetBinContent(k,05.*histo_Sig_Lept_up.GetBinContent(k)/histo_Sig_Lept_up.Integral());
    histo_Sig_10_Lept_up->SetBinContent(k,10.*histo_Sig_Lept_up.GetBinContent(k)/histo_Sig_Lept_up.Integral());
    histo_Sig_20_Lept_up->SetBinContent(k,20.*histo_Sig_Lept_up.GetBinContent(k)/histo_Sig_Lept_up.Integral());
    histo_Sig_30_Lept_up->SetBinContent(k,30.*histo_Sig_Lept_up.GetBinContent(k)/histo_Sig_Lept_up.Integral());
    histo_Sig_50_Lept_up->SetBinContent(k,50.*histo_Sig_Lept_up.GetBinContent(k)/histo_Sig_Lept_up.Integral());
    
    histo_Sig_05_Lept_down->SetBinContent(k,05.*histo_Sig_Lept_down.GetBinContent(k)/histo_Sig_Lept_down.Integral());
    histo_Sig_10_Lept_down->SetBinContent(k,10.*histo_Sig_Lept_down.GetBinContent(k)/histo_Sig_Lept_down.Integral());
    histo_Sig_20_Lept_down->SetBinContent(k,20.*histo_Sig_Lept_down.GetBinContent(k)/histo_Sig_Lept_down.Integral());
    histo_Sig_30_Lept_down->SetBinContent(k,30.*histo_Sig_Lept_down.GetBinContent(k)/histo_Sig_Lept_down.Integral());
    histo_Sig_50_Lept_down->SetBinContent(k,50.*histo_Sig_Lept_down.GetBinContent(k)/histo_Sig_Lept_down.Integral());
    
    
  }
  
  histo_Sig_05->SetName("MVABDT__FCNC_zut05");
  histo_Sig_10->SetName("MVABDT__FCNC_zut10");
  histo_Sig_20->SetName("MVABDT__FCNC_zut20");
  histo_Sig_30->SetName("MVABDT__FCNC_zut30");
  histo_Sig_50->SetName("MVABDT__FCNC_zut50");
  
  histo_Sig_05_JES_up->SetName("MVABDT__FCNC_zut05__JES__plus");
  histo_Sig_10_JES_up->SetName("MVABDT__FCNC_zut10__JES__plus");
  histo_Sig_20_JES_up->SetName("MVABDT__FCNC_zut20__JES__plus");
  histo_Sig_30_JES_up->SetName("MVABDT__FCNC_zut30__JES__plus");
  histo_Sig_50_JES_up->SetName("MVABDT__FCNC_zut50__JES__plus");
  
  histo_Sig_05_JES_down->SetName("MVABDT__FCNC_zut05__JES__minus");
  histo_Sig_10_JES_down->SetName("MVABDT__FCNC_zut10__JES__minus");
  histo_Sig_20_JES_down->SetName("MVABDT__FCNC_zut20__JES__minus");
  histo_Sig_30_JES_down->SetName("MVABDT__FCNC_zut30__JES__minus");
  histo_Sig_50_JES_down->SetName("MVABDT__FCNC_zut50__JES__minus");
  
  
  histo_Sig_05_JER_up->SetName("MVABDT__FCNC_zut05__JER__plus");
  histo_Sig_10_JER_up->SetName("MVABDT__FCNC_zut10__JER__plus");
  histo_Sig_20_JER_up->SetName("MVABDT__FCNC_zut20__JER__plus");
  histo_Sig_30_JER_up->SetName("MVABDT__FCNC_zut30__JER__plus");
  histo_Sig_50_JER_up->SetName("MVABDT__FCNC_zut50__JER__plus");
  
  histo_Sig_05_JER_down->SetName("MVABDT__FCNC_zut05__JER__minus");
  histo_Sig_10_JER_down->SetName("MVABDT__FCNC_zut10__JER__minus");
  histo_Sig_20_JER_down->SetName("MVABDT__FCNC_zut20__JER__minus");
  histo_Sig_30_JER_down->SetName("MVABDT__FCNC_zut30__JER__minus");
  histo_Sig_50_JER_down->SetName("MVABDT__FCNC_zut50__JER__minus");
  
  
  histo_Sig_05_BTag_up->SetName("MVABDT__FCNC_zut05__BTag__plus");
  histo_Sig_10_BTag_up->SetName("MVABDT__FCNC_zut10__BTag__plus");
  histo_Sig_20_BTag_up->SetName("MVABDT__FCNC_zut20__BTag__plus");
  histo_Sig_30_BTag_up->SetName("MVABDT__FCNC_zut30__BTag__plus");
  histo_Sig_50_BTag_up->SetName("MVABDT__FCNC_zut50__BTag__plus");
  
  histo_Sig_05_BTag_down->SetName("MVABDT__FCNC_zut05__BTag__minus");
  histo_Sig_10_BTag_down->SetName("MVABDT__FCNC_zut10__BTag__minus");
  histo_Sig_20_BTag_down->SetName("MVABDT__FCNC_zut20__BTag__minus");
  histo_Sig_30_BTag_down->SetName("MVABDT__FCNC_zut30__BTag__minus");
  histo_Sig_50_BTag_down->SetName("MVABDT__FCNC_zut50__BTag__minus");
  
  histo_Sig_05_Lept_up->SetName("MVABDT__FCNC_zut05__Lept__plus");
  histo_Sig_10_Lept_up->SetName("MVABDT__FCNC_zut10__Lept__plus");
  histo_Sig_20_Lept_up->SetName("MVABDT__FCNC_zut20__Lept__plus");
  histo_Sig_30_Lept_up->SetName("MVABDT__FCNC_zut30__Lept__plus");
  histo_Sig_50_Lept_up->SetName("MVABDT__FCNC_zut50__Lept__plus");
  
  histo_Sig_05_Lept_down->SetName("MVABDT__FCNC_zut05__Lept__minus");
  histo_Sig_10_Lept_down->SetName("MVABDT__FCNC_zut10__Lept__minus");
  histo_Sig_20_Lept_down->SetName("MVABDT__FCNC_zut20__Lept__minus");
  histo_Sig_30_Lept_down->SetName("MVABDT__FCNC_zut30__Lept__minus");
  histo_Sig_50_Lept_down->SetName("MVABDT__FCNC_zut50__Lept__minus");
  
  
  //TFile * outputfile = new TFile("NewFileToBeUsedForThetaWithAutoNamingConvention.root","new");
  TFile * outputfile = new TFile("NewFileToBeUsedForThetaWithAutoNamingConvention_allpoints.root","new");
  
  outputfile->cd();
  
    
  
  // add histo for making bands
  
  /*
  histo_Sig_05->Rebin(4);
  histo_Sig_10->Rebin(4);
  histo_Sig_20->Rebin(4);
  histo_Sig_30->Rebin(4);
  histo_Sig_50->Rebin(4);
  histo_Sig.Rebin(4);
  
  histo_Data.Rebin(4);
  histo_Zjets.Rebin(4);
  histo_WZ.Rebin(4);
  histo_ZZ.Rebin(4);
  histo_TTbar.Rebin(4);
  */
  
  
  
  // add histo for making bands
  
  
  histo_Sig_05->Write();
  histo_Sig_10->Write();
  histo_Sig_20->Write();
  histo_Sig_30->Write();
  histo_Sig_50->Write();
  histo_Sig.Write();
  /*
  histo_Sig_05_JES_up->Write();
  histo_Sig_10_JES_up->Write();
  histo_Sig_20_JES_up->Write();
  histo_Sig_30_JES_up->Write();
  histo_Sig_50_JES_up->Write();
  histo_Sig_JES_up.Write();
  
  histo_Sig_05_JES_down->Write();
  histo_Sig_10_JES_down->Write();
  histo_Sig_20_JES_down->Write();
  histo_Sig_30_JES_down->Write();
  histo_Sig_50_JES_down->Write();
  histo_Sig_JES_down.Write();
  
  histo_Sig_05_JER_up->Write();
  histo_Sig_10_JER_up->Write();
  histo_Sig_20_JER_up->Write();
  histo_Sig_30_JER_up->Write();
  histo_Sig_50_JER_up->Write();
  histo_Sig_JER_up.Write();
  
  histo_Sig_05_JER_down->Write();
  histo_Sig_10_JER_down->Write();
  histo_Sig_20_JER_down->Write();
  histo_Sig_30_JER_down->Write();
  histo_Sig_50_JER_down->Write();
  histo_Sig_JER_down.Write(); 
  
  histo_Sig_05_BTag_up->Write();
  histo_Sig_10_BTag_up->Write();
  histo_Sig_20_BTag_up->Write();
  histo_Sig_30_BTag_up->Write();
  histo_Sig_50_BTag_up->Write();
  histo_Sig_BTag_up.Write();
  
  histo_Sig_05_BTag_down->Write();
  histo_Sig_10_BTag_down->Write();
  histo_Sig_20_BTag_down->Write();
  histo_Sig_30_BTag_down->Write();
  histo_Sig_50_BTag_down->Write();
  histo_Sig_BTag_down.Write();
  
  
  histo_Sig_05_Lept_up->Write();
  histo_Sig_10_Lept_up->Write();
  histo_Sig_20_Lept_up->Write();
  histo_Sig_30_Lept_up->Write();
  histo_Sig_50_Lept_up->Write();
  histo_Sig_Lept_up.Write();
  
  histo_Sig_05_Lept_down->Write();
  histo_Sig_10_Lept_down->Write();
  histo_Sig_20_Lept_down->Write();
  histo_Sig_30_Lept_down->Write();
  histo_Sig_50_Lept_down->Write();
  histo_Sig_Lept_down.Write();
  */
  histo_Data.Write();
  histo_Zjets.Write();
  histo_WZ.Write();
  histo_ZZ.Write();
  histo_TTbar.Write();
 /*
  histo_WZ_JES_up.Write();
  histo_ZZ_JES_up.Write();
  histo_TTbar_JES_up.Write();
  
  histo_WZ_JES_down.Write();
  histo_ZZ_JES_down.Write();
  histo_TTbar_JES_down.Write();
 
  histo_WZ_JER_up.Write();
  histo_ZZ_JER_up.Write();
  histo_TTbar_JER_up.Write();
 
  histo_WZ_JER_down.Write();
  histo_ZZ_JER_down.Write();
  histo_TTbar_JER_down.Write();
  
  
  histo_WZ_BTag_up.Write();
  histo_ZZ_BTag_up.Write();
  histo_TTbar_BTag_up.Write();
  
  histo_WZ_BTag_down.Write();
  histo_ZZ_BTag_down.Write();
  histo_TTbar_BTag_down.Write();
  
  
  histo_WZ_Lept_up.Write();
  histo_ZZ_Lept_up.Write();
  histo_TTbar_Lept_up.Write();
  
  histo_WZ_Lept_down.Write();
  histo_ZZ_Lept_down.Write();
  histo_TTbar_Lept_down.Write();
*/
  outputfile->Close();  
  
} 

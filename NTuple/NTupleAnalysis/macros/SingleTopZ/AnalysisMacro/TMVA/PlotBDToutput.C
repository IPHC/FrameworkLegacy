
#include "TString.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"
#include <iostream>

static bool doSyst= false;
bool doBtagUncerOnly   = false;
bool doPDFUncerOnly    = false;
bool doJESUncerOnly    = false;
bool doMatchUncerOnly  = false;
bool doScaleUncerOnly  = false;



static bool plotFCNC= true;

void PlotBDToutput(TString theVertex, TString theVariable, TString theFile){
  
  
  
  if(doSyst){
  
    doBtagUncerOnly   = false;
    doPDFUncerOnly    = false;
    doJESUncerOnly    = false;
    doMatchUncerOnly  = false;
    doScaleUncerOnly  = false;
  
  }
  
  
  
  
  double WZscale = 1.;
  double TZqscale = 0.27;
  
  
  Int_t stati=0;
  Bool_t  fit=1;
  Bool_t logy=0;
  
  bool setlogy = 0;
  
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(0); // must be kWhite but I dunno how to do that in PyROOT
  gStyle->SetCanvasDefH(600); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //POsition on screen
  gStyle->SetCanvasDefY(0);
  
  
  // For the Pad:
  gStyle->SetPadBorderMode(0);
  // ROOT . gStyle . SetPadBorderSize(Width_t size = 1);
  gStyle->SetPadColor(0); // kWhite
  gStyle->SetPadGridX(0); //false
  gStyle->SetPadGridY(0); //false
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  // For the frame:
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetFrameLineStyle(1);
  gStyle->SetFrameLineWidth(1);
  
  // For the histo:
  // ROOT . gStyle . SetHistFillColor(1);
  // ROOT . gStyle . SetHistFillStyle(0);
  gStyle->SetHistLineColor(1);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(1);
  // ROOT . gStyle . SetLegoInnerR(Float_t rad = 0.5);
  // ROOT . gStyle . SetNumberContours(Int_t number = 20);
  
  gStyle->SetEndErrorSize(2);
  //ROOT . gStyle . SetErrorMarker(20);   /// I COMMENTED THIS OUT
  //ROOT . gStyle . SetErrorX(0.);
  
  //ROOT . gStyle . SetMarkerStyle(20);
  
  
  //For the fit/function:
  gStyle->SetOptFit(1011);
  gStyle->SetFitFormat("5.4g");
  gStyle->SetFuncColor(2);
  gStyle->SetFuncStyle(1);
  gStyle->SetFuncWidth(1);
  
  //For the date:
  gStyle->SetOptDate(0);
  // ROOT . gStyle . SetDateX(Float_t x = 0.01);
  // ROOT . gStyle . SetDateY(Float_t y = 0.01);
  
  // For the statistics box:
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  gStyle->SetStatColor(0); // kWhite
  gStyle->SetStatFont(42);
  //ROOT . gStyle . SetStatFontSize(0.025);
  gStyle->SetStatFontSize(0.04);
  gStyle->SetStatTextColor(1);
  gStyle->SetStatFormat("6.4g");
  gStyle->SetStatBorderSize(1);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);
  // ROOT . gStyle . SetStatStyle(Style_t style = 1001);
  // ROOT . gStyle . SetStatX(Float_t x = 0);
  // ROOT . gStyle . SetStatY(Float_t y = 0);
  
  // Margins:
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetPadLeftMargin(0.16);
  //ROOT . gStyle . SetPadRightMargin(0.12);
  gStyle->SetPadRightMargin(0.03);
  
  // For the Global title:
  
  gStyle->SetOptTitle(0);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);
  gStyle->SetTitleFontSize(0.05);
  // ROOT . gStyle . SetTitleH(0); // Set the height of the title box
  // ROOT . gStyle . SetTitleW(0); // Set the width of the title box
  // ROOT . gStyle . SetTitleX(0); // Set the position of the title box
  // ROOT . gStyle . SetTitleY(0.985); // Set the position of the title box
  // ROOT . gStyle . SetTitleStyle(Style_t style = 1001);
  // ROOT . gStyle . SetTitleBorderSize(2);
  
  // For the axis titles:
  
  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // ROOT . gStyle . SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // ROOT . gStyle . SetTitleYSize(Float_t size = 0.02);
  gStyle->SetTitleXOffset(0.9);
  gStyle->SetTitleYOffset(1.25);
  // ROOT . gStyle . SetTitleOffset(1.1, "Y"); // Another way to set the Offset
  
  // For the axis labels:
  
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");
  
  // For the axis:
  
  gStyle->SetAxisColor(1, "XYZ");
  gStyle->SetStripDecimals(1); // kTRUE
  gStyle->SetTickLength(0.03, "XYZ");
  gStyle->SetNdivisions(510, "XYZ");
  gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  gStyle->SetPadTickY(1);
  
  // Change for log plots:
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(0);
  gStyle->SetOptLogz(0);
  
  // Postscript options:
  gStyle->SetPaperSize(20.,20.);
  // ROOT . gStyle . SetLineScalePS(Float_t scale = 3);
  // ROOT . gStyle . SetLineStyleString(Int_t i, const char* text);
  // ROOT . gStyle . SetHeaderPS(const char* header);
  // ROOT . gStyle . SetTitlePS(const char* pstitle);
  
  // ROOT . gStyle . SetBarOffset(Float_t baroff = 0.5);
  // ROOT . gStyle . SetBarWidth(Float_t barwidth = 0.5);
  // ROOT . gStyle . SetPaintTextFormat(const char* format = "g");
  // ROOT . gStyle . SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // ROOT . gStyle . SetTimeOffset(Double_t toffset);
  // ROOT . gStyle . SetHistMinimumZero(kTRUE);
  
  
  //TCanvas *c1 = new TCanvas("c1", "c1",10,32,782,552);
  TCanvas *c1 = new TCanvas("c1","c1", 1000, 800);
  c1->SetBottomMargin(0.3);
  c1->SetLogy(setlogy);
  c1->cd();
  
  
  
   TFile * filechannel ;
   
   filechannel = new TFile(theFile.Data());

   std::cout << "file " << theFile << std::endl;
   
   
   TH1F * histBdt_Data      = (TH1F*)filechannel->Get( (theVariable+"_Data"     ).Data());
   TH1F * histBdt_WZ        = (TH1F*)filechannel->Get( (theVariable+"_WZ"       ).Data());
   TH1F * histBdt_ZZ        = (TH1F*)filechannel->Get( (theVariable+"_ZZ"       ).Data());
   TH1F * histBdt_Zjets     = (TH1F*)filechannel->Get( (theVariable+"_Zjets"    ).Data());
   TH1F * histBdt_DataZjets = (TH1F*)filechannel->Get( (theVariable+"_DataZjets").Data());  
   //TH1F * histBdt_DataZjets = (TH1F*)filechannel->Get( (theVariable+"_Zjets").Data());  
   TH1F * histBdt_TTbar     = (TH1F*)filechannel->Get( (theVariable+"_TTbarSig" ).Data());
   TH1F * histBdt_TZq       = (TH1F*)filechannel->Get( (theVariable+"_TZq"      ).Data());
   
   
   TH1F * histBdt_FCNC ;     
   if(theVariable == "MVA_BDT"){
     histBdt_FCNC = (TH1F*)filechannel->Get((theVariable+"_FCNC_"+theVertex).Data());	 
   }
   else{
     histBdt_FCNC = (TH1F*)filechannel->Get((theVariable+"_Signal").Data());	 
   } 
  
  
  histBdt_FCNC->Scale(10);
  histBdt_Data->SetLineColor(1);
  int rebin = 1;
  if(theVariable!="NJets" && theVariable!="NBJets"){
    histBdt_Data->Rebin(rebin);  
    histBdt_WZ->Rebin(rebin);	     
    histBdt_ZZ->Rebin(rebin);	     
    histBdt_TTbar->Rebin(rebin);	     
    histBdt_Zjets->Rebin(rebin);	     
    histBdt_FCNC->Rebin(rebin);  
    histBdt_DataZjets->Rebin(rebin);
    histBdt_TZq->Rebin(rebin);
  }
  
  //histBdt_WZ->Scale(0.905713);
  histBdt_WZ->Scale(WZscale);
  histBdt_WZ->Add(histBdt_ZZ);
  //histBdt_DataZjets->Add(histBdt_DataZjets, histBdt_TTbar, 1, -0.05*histBdt_DataZjets->Integral()/histBdt_TTbar->Integral());
  histBdt_DataZjets->Scale(histBdt_Zjets->Integral()/histBdt_DataZjets->Integral());
  
  histBdt_TZq->Scale(TZqscale);
  
  
  
  histBdt_WZ->SetFillColor(13);
  histBdt_DataZjets->SetFillColor(kAzure-2);
  histBdt_TZq->SetFillColor(kAzure+8);
  
  THStack* hs= new THStack();
  
  histBdt_WZ->GetXaxis()->SetLabelSize(0.);
  histBdt_DataZjets->GetXaxis()->SetLabelSize(0.);
  
  histBdt_TTbar->SetFillColor(kRed-7);
  
  
  hs->Add(histBdt_WZ);
  hs->Add(histBdt_TTbar);
  hs->Add(histBdt_TZq);
  hs->Add(histBdt_DataZjets);



  
  hs->Draw("histo");
  hs->GetXaxis()->SetLabelSize(0.);
  hs->SetMaximum(histBdt_Data->GetMaximum()*1.7);
  hs->SetMinimum(0.1);
  hs->GetYaxis()->SetLabelSize(0.04);
  
  
  
  histBdt_Data->SetMarkerStyle(20);
  histBdt_Data->SetMarkerSize(1.2);
  histBdt_Data->GetXaxis()->SetLabelSize(0.);
  histBdt_Data->Draw("epsame");
  
  
  histBdt_FCNC->SetLineWidth(2.0);
  histBdt_FCNC->SetLineColor(1.);
  histBdt_FCNC->GetXaxis()->SetLabelSize(0.);
  if(plotFCNC) histBdt_FCNC->Draw("histosame");
  
  double theWZscale = 1.0;
   if(theVertex == "zut") theWZscale = 0.72;
   if(theVertex == "zct") theWZscale = 0.64; 
   if(theVertex == "kut") theWZscale = 0.82; 
   if(theVertex == "kct") theWZscale = 0.90; 
   
   double theWZscale_err = 1.;
   if(theVertex == "zut") theWZscale_err = 0.24;
   if(theVertex == "zct") theWZscale_err = 0.30; 
   if(theVertex == "kut") theWZscale_err = 0.23; 
   if(theVertex == "kct") theWZscale_err = 0.21; 
   
  
  TH1F* herrorband =  (TH1F*) histBdt_WZ->Clone();
  herrorband->Add(histBdt_DataZjets);
  herrorband->Add(histBdt_TTbar);
  herrorband->Add(histBdt_TZq);
 
  
  TH1F* herrorband_btagup ;
  TH1F* herrorband_btagdown   ;
  TH1F* herrorband_norw   ;
  
  
  TH1F* herrorband_PDFup ;
  TH1F* herrorband_PDFdown ;
  
  TH1F* herrorband_JESup ;
  TH1F* herrorband_JESdown ;
  
  TH1F* herrorband_Matchup ;
  TH1F* herrorband_Matchdown ;
  
  TH1F* herrorband_Scaleup ;
  TH1F* herrorband_Scaledown ;
  
  
  
  cout << "histBdt_WZ->Integral()        " << histBdt_WZ->Integral() << endl;
  cout << "histBdt_DataZjets->Integral() " << histBdt_DataZjets->Integral() << endl;
  cout << "histBdt_TTbar->Integral()     " << histBdt_TTbar->Integral() << endl;
  cout << "histBdt_TZq->Integral()       " << histBdt_TZq->Integral() << endl;
  
  
  TFile * filebta_btagup   = new TFile("HistoBDToutput/TMVApp_zut_btagUp.root");
  TFile * filebta_btagdown = new TFile("HistoBDToutput/TMVApp_zut_btagdown.root");
  //TFile * filebta_norw     = new TFile("HistoBDToutput/TMVApp_zut_noreweight.root");
  
  TFile * filebta_PDFup  = new TFile("HistoBDToutput/TMVApp_zut_PDFup.root");
  TFile * filebta_PDFdown = new TFile("HistoBDToutput/TMVApp_zut_PDFdown.root");
  
  TFile * filebta_JESup  = new TFile("HistoBDToutput/TMVApp_zut_JESup.root");
  TFile * filebta_JESdown = new TFile("HistoBDToutput/TMVApp_zut_JESdown.root");
  
  TFile * filebta_Matchup   = new TFile("HistoBDToutput/TMVApp_zut_Matchup.root");
  TFile * filebta_Matchdown = new TFile("HistoBDToutput/TMVApp_zut_Matchdown.root");
  
  TFile * filebta_Scaleup   = new TFile("HistoBDToutput/TMVApp_zut_Scaleup.root");
  TFile * filebta_Scaledown = new TFile("HistoBDToutput/TMVApp_zut_Scaledown.root");
  
   
  if(!doSyst){
    for (int ierr=1; ierr<=herrorband->GetNbinsX(); ierr++) {
    double error_all = pow(histBdt_WZ->GetBinError(ierr), 2) // stat
                        + pow(histBdt_WZ->GetBinContent(ierr)*theWZscale_err/theWZscale, 2) // syst SF 
                        + pow(histBdt_DataZjets->GetBinError(ierr), 2) // stat
                        + pow(histBdt_DataZjets->GetBinContent(ierr)*0.30, 2) // syst SF
                        + pow(histBdt_ZZ->GetBinContent(ierr)*0.30, 2) // syst SF 
                        + pow(histBdt_TTbar->GetBinContent(ierr)*2.60, 2) // syst SF 
                        + pow(histBdt_TZq->GetBinContent(ierr)*0.50, 2) // syst SF 
                        + pow(
				(histBdt_ZZ->GetBinContent(ierr)+histBdt_TTbar->GetBinContent(ierr)+histBdt_TZq->GetBinContent(ierr))
				
				*0.025, 2); // syst lumi
				cout << "error_all 1 " << error_all << endl;
				cout << "theVariable " << theVariable << endl;
			if(theVariable == "NBJets" || theVariable == "NBJets_BDTcut" )	{
			   cout << "in " << endl;
			  if(ierr == 1) error_all=error_all+pow(histBdt_WZ->GetBinContent(ierr)*0.11, 2); 
			  if(ierr == 2) error_all=error_all+pow(histBdt_WZ->GetBinContent(ierr)*0.41, 2); 
			
			
			}
			
				cout << "error_all 2 " << error_all << endl;	
    herrorband->SetBinError(ierr, sqrt(error_all));
    
    }
  }
  else{
  
    //------------------------------------------
    //adding btag systematics
    //------------------------------------------
     
    TH1F * histBdt_WZ_btagup        = (TH1F*)filebta_btagup->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_btagup        = (TH1F*)filebta_btagup->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_btagup     = (TH1F*)filebta_btagup->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_btagup     = (TH1F*)filebta_btagup->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_btagup       = (TH1F*)filebta_btagup->Get( (theVariable+"_TZq"      ).Data());
    
    
    histBdt_WZ_btagup->Scale(histBdt_WZ->Integral()/histBdt_WZ_btagup->Integral());
    histBdt_TTbar_btagup->Scale(histBdt_TTbar->Integral()/histBdt_TTbar_btagup->Integral());
    histBdt_TZq_btagup->Scale(histBdt_TZq->Integral()/histBdt_TZq_btagup->Integral());
    
    
    
    herrorband_btagup =  (TH1F*) histBdt_WZ_btagup->Clone();
    herrorband_btagup->Add(histBdt_DataZjets);
    herrorband_btagup->Add(histBdt_TTbar_btagup);
    herrorband_btagup->Add(histBdt_TZq_btagup);
    
    TH1F * histBdt_WZ_btagdown        = (TH1F*)filebta_btagdown->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_btagdown        = (TH1F*)filebta_btagdown->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_btagdown     = (TH1F*)filebta_btagdown->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_btagdown     = (TH1F*)filebta_btagdown->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_btagdown       = (TH1F*)filebta_btagdown->Get( (theVariable+"_TZq"      ).Data());
    
    
    histBdt_WZ_btagdown->Scale(histBdt_WZ->Integral()/histBdt_WZ_btagdown->Integral());
    histBdt_TTbar_btagdown->Scale(histBdt_TTbar->Integral()/histBdt_TTbar_btagdown->Integral());
    histBdt_TZq_btagdown->Scale(histBdt_TZq->Integral()/histBdt_TZq_btagdown->Integral());
    
    
    
    herrorband_btagdown =  (TH1F*) histBdt_WZ_btagdown->Clone();
    herrorband_btagdown->Add(histBdt_DataZjets);
    herrorband_btagdown->Add(histBdt_TTbar_btagdown);
    herrorband_btagdown->Add(histBdt_TZq_btagdown);
    
    
    /*TH1F * histBdt_WZ_norw        = (TH1F*)filebta_norw->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_norw        = (TH1F*)filebta_norw->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_norw     = (TH1F*)filebta_norw->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_norw     = (TH1F*)filebta_norw->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_norw       = (TH1F*)filebta_norw->Get( (theVariable+"_TZq"      ).Data());
    
    
    herrorband_norw =  (TH1F*) histBdt_WZ_norw->Clone();
    herrorband_norw->Add(histBdt_DataZjets);
    herrorband_norw->Add(histBdt_TTbar_norw);
    herrorband_norw->Add(histBdt_TZq_norw);
    */
    
    //------------------------------------------
    //adding PDF systematics
    //------------------------------------------
     
    TH1F * histBdt_WZ_PDFup        = (TH1F*)filebta_PDFup->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_PDFup        = (TH1F*)filebta_PDFup->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_PDFup     = (TH1F*)filebta_PDFup->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_PDFup     = (TH1F*)filebta_PDFup->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_PDFup       = (TH1F*)filebta_PDFup->Get( (theVariable+"_TZq"      ).Data());
    
    
    histBdt_WZ_PDFup->Scale(histBdt_WZ->Integral()/histBdt_WZ_PDFup->Integral());
    histBdt_TTbar_PDFup->Scale(histBdt_TTbar->Integral()/histBdt_TTbar_PDFup->Integral());
    histBdt_TZq_PDFup->Scale(histBdt_TZq->Integral()/histBdt_TZq_PDFup->Integral());

    
    cout << "histBdt_WZ_PDFup    " << histBdt_WZ_PDFup->Integral() << endl;
    cout << "histBdt_TTbar_PDFup " << histBdt_TTbar_PDFup->Integral() << endl;
    cout << "histBdt_TZq_PDFup   " << histBdt_TZq_PDFup->Integral() << endl;
    
    
    
    herrorband_PDFup =  (TH1F*) histBdt_WZ_PDFup->Clone();
    cout << "herrorband_PDFup->Integral() 1 " << herrorband_PDFup->Integral() << endl;
    herrorband_PDFup->Add(histBdt_DataZjets);
    herrorband_PDFup->Add(histBdt_TTbar_PDFup);
    herrorband_PDFup->Add(histBdt_TZq_PDFup);
    cout << "herrorband_PDFup->Integral() 2 "  << herrorband_PDFup->Integral()<< endl;
    
    
    
    
    TH1F * histBdt_WZ_PDFdown        = (TH1F*)filebta_PDFdown->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_PDFdown        = (TH1F*)filebta_PDFdown->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_PDFdown     = (TH1F*)filebta_PDFdown->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_PDFdown     = (TH1F*)filebta_PDFdown->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_PDFdown       = (TH1F*)filebta_PDFdown->Get( (theVariable+"_TZq"      ).Data());
    
    
    histBdt_WZ_PDFdown->Scale(histBdt_WZ->Integral()/histBdt_WZ_PDFdown->Integral());
    histBdt_TTbar_PDFdown->Scale(histBdt_TTbar->Integral()/histBdt_TTbar_PDFdown->Integral());
    histBdt_TZq_PDFdown->Scale(histBdt_TZq->Integral()/histBdt_TZq_PDFdown->Integral());
    
    herrorband_PDFdown =  (TH1F*) histBdt_WZ_PDFdown->Clone();
    herrorband_PDFdown->Add(histBdt_DataZjets);
    herrorband_PDFdown->Add(histBdt_TTbar_PDFdown);
    herrorband_PDFdown->Add(histBdt_TZq_PDFdown);
    
    //------------------------------------------
    //adding JES systematics
    //------------------------------------------
    
     
    TH1F * histBdt_WZ_JESup        = (TH1F*)filebta_JESup->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_JESup        = (TH1F*)filebta_JESup->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_JESup     = (TH1F*)filebta_JESup->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_JESup     = (TH1F*)filebta_JESup->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_JESup       = (TH1F*)filebta_JESup->Get( (theVariable+"_TZq"      ).Data());
    
    histBdt_WZ_JESup->Scale(histBdt_WZ->Integral()/histBdt_WZ_JESup->Integral());
    
    herrorband_JESup =  (TH1F*) histBdt_WZ_JESup->Clone();
    herrorband_JESup->Add(histBdt_DataZjets);
    herrorband_JESup->Add(histBdt_TTbar_JESup);
    herrorband_JESup->Add(histBdt_TZq_JESup);
    
    TH1F * histBdt_WZ_JESdown        = (TH1F*)filebta_JESdown->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_JESdown        = (TH1F*)filebta_JESdown->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_JESdown     = (TH1F*)filebta_JESdown->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_JESdown     = (TH1F*)filebta_JESdown->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_JESdown       = (TH1F*)filebta_JESdown->Get( (theVariable+"_TZq"      ).Data());
    
    histBdt_WZ_JESdown->Scale(histBdt_WZ->Integral()/histBdt_WZ_JESdown->Integral());
    
    herrorband_JESdown =  (TH1F*) histBdt_WZ_JESdown->Clone();
    herrorband_JESdown->Add(histBdt_DataZjets);
    herrorband_JESdown->Add(histBdt_TTbar_JESdown);
    herrorband_JESdown->Add(histBdt_TZq_JESdown);
    
    //------------------------------------------
    //adding Match systematics
    //------------------------------------------
    
     
    TH1F * histBdt_WZ_Matchup        = (TH1F*)filebta_Matchup->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_Matchup        = (TH1F*)filebta_Matchup->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_Matchup     = (TH1F*)filebta_Matchup->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_Matchup     = (TH1F*)filebta_Matchup->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_Matchup       = (TH1F*)filebta_Matchup->Get( (theVariable+"_TZq"      ).Data());
    
    
    //cout << "histBdt_WZ_Matchup->Integral() " << histBdt_WZ_Matchup->Integral() << endl;
    histBdt_WZ_Matchup->Scale(histBdt_WZ->Integral()/histBdt_WZ_Matchup->Integral());
    //cout << "histBdt_WZ->Integral() " << histBdt_WZ->Integral() << endl;
    //cout << "histBdt_WZ_Matchup->Integral() " << histBdt_WZ_Matchup->Integral() << endl;
    
    
    herrorband_Matchup =  (TH1F*) histBdt_WZ_Matchup->Clone();
    herrorband_Matchup->Add(histBdt_DataZjets);
    herrorband_Matchup->Add(histBdt_TTbar);
    herrorband_Matchup->Add(histBdt_TZq);
    
    TH1F * histBdt_WZ_Matchdown        = (TH1F*)filebta_Matchdown->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_Matchdown        = (TH1F*)filebta_Matchdown->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_Matchdown     = (TH1F*)filebta_Matchdown->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_Matchdown     = (TH1F*)filebta_Matchdown->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_Matchdown       = (TH1F*)filebta_Matchdown->Get( (theVariable+"_TZq"      ).Data());
    
    
    histBdt_WZ_Matchdown->Scale(histBdt_WZ->Integral()/histBdt_WZ_Matchdown->Integral());
    
    herrorband_Matchdown =  (TH1F*) histBdt_WZ_Matchdown->Clone();
    herrorband_Matchdown->Add(histBdt_DataZjets);
    herrorband_Matchdown->Add(histBdt_TTbar);
    herrorband_Matchdown->Add(histBdt_TZq);
    
    
    //------------------------------------------
    //adding Scale systematics
    //------------------------------------------
    
    TFile * filebta_Scaleup   = new TFile("HistoBDToutput/TMVApp_zut_Scaleup.root");
    TFile * filebta_Scaledown = new TFile("HistoBDToutput/TMVApp_zut_Scaledown.root");
     
    TH1F * histBdt_WZ_Scaleup        = (TH1F*)filebta_Scaleup->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_Scaleup        = (TH1F*)filebta_Scaleup->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_Scaleup     = (TH1F*)filebta_Scaleup->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_Scaleup     = (TH1F*)filebta_Scaleup->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_Scaleup       = (TH1F*)filebta_Scaleup->Get( (theVariable+"_TZq"      ).Data());
    
    histBdt_WZ_Scaleup->Scale(histBdt_WZ->Integral()/histBdt_WZ_Scaleup->Integral());
    
    herrorband_Scaleup =  (TH1F*) histBdt_WZ_Scaleup->Clone();
    herrorband_Scaleup->Add(histBdt_DataZjets);
    herrorband_Scaleup->Add(histBdt_TTbar);
    herrorband_Scaleup->Add(histBdt_TZq);
    
    TH1F * histBdt_WZ_Scaledown        = (TH1F*)filebta_Scaledown->Get( (theVariable+"_WZ"       ).Data());
    TH1F * histBdt_ZZ_Scaledown        = (TH1F*)filebta_Scaledown->Get( (theVariable+"_ZZ"       ).Data());
    TH1F * histBdt_Zjets_Scaledown     = (TH1F*)filebta_Scaledown->Get( (theVariable+"_Zjets"    ).Data()); 
    TH1F * histBdt_TTbar_Scaledown     = (TH1F*)filebta_Scaledown->Get( (theVariable+"_TTbarSig" ).Data());
    TH1F * histBdt_TZq_Scaledown       = (TH1F*)filebta_Scaledown->Get( (theVariable+"_TZq"      ).Data());
    
    histBdt_WZ_Scaledown->Scale(histBdt_WZ->Integral()/histBdt_WZ_Scaledown->Integral());
    
    herrorband_Scaledown =  (TH1F*) histBdt_WZ_Scaledown->Clone();
    herrorband_Scaledown->Add(histBdt_DataZjets);
    herrorband_Scaledown->Add(histBdt_TTbar);
    herrorband_Scaledown->Add(histBdt_TZq);
    
  }
  
  
  
  
  
  
  

  TGraphAsymmErrors *thegraph = new TGraphAsymmErrors(herrorband);
  thegraph->SetFillStyle(3005);
  thegraph->SetFillColor(1);
  if(doSyst){
    for(int i=0; i<herrorband->GetNbinsX(); i++){
    
    
    
    
    double theYup_error = pow(thegraph->GetErrorY(i)/2., 2);
    double theYdown_error = pow(thegraph->GetErrorY(i)/2., 2);
    
    double thevar=0;
    
    thevar = (herrorband_btagup->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
    
    
    
    thevar = (herrorband_PDFup->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2); 
    thevar = (herrorband_JESup->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2); 
    
    thevar = (herrorband_Matchup->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
     
    thevar = (herrorband_Scaleup->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
  
    
    thevar = (herrorband_btagdown->GetBinContent(i+1)-herrorband->GetBinContent(i+1)) ;
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
    thevar = (herrorband_PDFdown->GetBinContent(i+1)-herrorband->GetBinContent(i+1)) ;
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2); 
    thevar = (herrorband_JESdown->GetBinContent(i+1)-herrorband->GetBinContent(i+1))  ;
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
    thevar = (herrorband_Matchdown->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
    thevar = (herrorband_Scaledown->GetBinContent(i+1)-herrorband->GetBinContent(i+1));
    if(thevar > 0) theYup_error  +=pow(thevar, 2);
    else theYdown_error+=pow( thevar, 2);
    
    thegraph->SetPointEYhigh( i, pow(theYup_error, 0.5));
    thegraph->SetPointEYlow( i, pow(theYdown_error, 0.5));
    

	
    }
  }
  thegraph->Draw("e2same");
  //thegraph->Draw("lsame");
  /*if(doBtagUncerOnly) {
    herrorband_norw->SetLineWidth(2);
    herrorband_norw->Draw("hsame");
  }*/
  
  
  
  TH1F * histo_ratio = (TH1F*) histBdt_Data->Clone();
  TH1F * histo_mc    = (TH1F*) histBdt_WZ->Clone();
  histo_mc->Add(histBdt_DataZjets);
  histo_mc->Add(histBdt_TTbar);
  histo_mc->Add(histBdt_TZq);
  histo_ratio->Sumw2();
  histo_mc->Sumw2();
  histo_ratio->Divide(histo_ratio, histo_mc, 1, 1, "b");
  
  for (int ierr=1; ierr<=histo_ratio->GetNbinsX(); ierr++) {
    
    double num     = histBdt_Data->GetBinContent(ierr);
    double num_err = histBdt_Data->GetBinError(ierr);
    
    double denom     = histo_mc ->GetBinContent(ierr);
    double denom_err = herrorband->GetBinError(ierr);
    
    
    
    double error = pow(
       pow(num_err/denom, 2)+
       pow(num*denom_err/(denom*denom), 2)
    , 0.5);
    if(denom!=0){
    /*cout << "***************" << endl;
    cout << "num   " << num    << " pm " <<num_err  << endl;
    cout << "denom " <<  denom << " pm " <<denom_err  << endl;
    cout << "bin content       " << num/denom << endl;
    cout << "bin content error " <<  error << endl;*/
    }
    if(denom == 0 && num == 0) histo_ratio->SetBinContent(ierr, -10);
    
    histo_ratio->SetBinError(ierr,error );
  }
  
  /*
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  cout << theVariable << endl;
  */
  if(theVariable == "MVA_BDT"       ) histo_ratio->GetXaxis()->SetTitle("BDT output");
  if(theVariable == "topMass"       ) histo_ratio->GetXaxis()->SetTitle("m_{top} [GeV]");
  if(theVariable == "totMass"       ) histo_ratio->GetXaxis()->SetTitle("m_{tot} [GeV]");
  if(theVariable == "deltaPhilb"    ) histo_ratio->GetXaxis()->SetTitle("#Delta #phi(l_{W}-b)");
  if(theVariable == "deltaRlb"      ) histo_ratio->GetXaxis()->SetTitle("#Delta R(l_{W}-b)");
  if(theVariable == "deltaRTopZ"    ) histo_ratio->GetXaxis()->SetTitle("#Delta R(Z-t)");
  if(theVariable == "asym"          ) histo_ratio->GetXaxis()->SetTitle("q|#eta|");
  if(theVariable == "Zpt"           ) histo_ratio->GetXaxis()->SetTitle("p_{T}(Z) [GeV]");
  if(theVariable == "ZEta"          ) histo_ratio->GetXaxis()->SetTitle("#eta(Z)");
  if(theVariable == "topPt"         ) histo_ratio->GetXaxis()->SetTitle("p_{T}(t) [GeV]");
  if(theVariable == "topEta"        ) histo_ratio->GetXaxis()->SetTitle("#eta(t)");
  if(theVariable == "NJets"         ) histo_ratio->GetXaxis()->SetTitle("N_{jets}");
  if(theVariable == "NBJets"        ) histo_ratio->GetXaxis()->SetTitle("N_{bjets}");
  if(theVariable == "deltaRZl"      ) histo_ratio->GetXaxis()->SetTitle("#Delta R(l_{W}-Z)");
  if(theVariable == "deltaPhiZmet"  ) histo_ratio->GetXaxis()->SetTitle("#Delta #phi(Z-met)");
  if(theVariable == "btagDiscri"    ) histo_ratio->GetXaxis()->SetTitle("CSV discr.");
  if(theVariable == "leptWPt"       ) histo_ratio->GetXaxis()->SetTitle("p_{T}(l_{W}) [GeV]");
  if(theVariable == "leptWEta"      ) histo_ratio->GetXaxis()->SetTitle("#eta(l_{W})");
  if(theVariable == "leadJetPt"     ) histo_ratio->GetXaxis()->SetTitle("Leading jet p_{T} [GeV]");
  if(theVariable == "leadJetEta"    ) histo_ratio->GetXaxis()->SetTitle("Leading jet #eta");
  if(theVariable == "deltaPhiZleptW") histo_ratio->GetXaxis()->SetTitle("#Delta #phi(Z-l_{W})");
  
  
  
  
  if(theVariable == "topMass_BDTcut"       ) histo_ratio->GetXaxis()->SetTitle("m_{top} [GeV]");
  if(theVariable == "totMass_BDTcut"       ) histo_ratio->GetXaxis()->SetTitle("m_{tot} [GeV]");
  if(theVariable == "deltaPhilb_BDTcut"    ) histo_ratio->GetXaxis()->SetTitle("#Delta #phi(l_{W}-b)");
  if(theVariable == "deltaRlb_BDTcut"      ) histo_ratio->GetXaxis()->SetTitle("#Delta R(l_{W}-b)");
  if(theVariable == "deltaRTopZ_BDTcut"    ) histo_ratio->GetXaxis()->SetTitle("#Delta R(Z-t)");
  if(theVariable == "asym_BDTcut"          ) histo_ratio->GetXaxis()->SetTitle("q|#eta|");
  if(theVariable == "Zpt_BDTcut"           ) histo_ratio->GetXaxis()->SetTitle("p_{T}(Z) [GeV]");
  if(theVariable == "ZEta_BDTcut"          ) histo_ratio->GetXaxis()->SetTitle("#eta(Z)");
  if(theVariable == "topPt_BDTcut"         ) histo_ratio->GetXaxis()->SetTitle("p_{T}(t) [GeV]");
  if(theVariable == "topEta_BDTcut"        ) histo_ratio->GetXaxis()->SetTitle("#eta(t)");
  if(theVariable == "NJets_BDTcut"         ) histo_ratio->GetXaxis()->SetTitle("N_{jets}");
  if(theVariable == "NBJets_BDTcut"        ) histo_ratio->GetXaxis()->SetTitle("N_{bjets}");
  if(theVariable == "deltaRZl_BDTcut"      ) histo_ratio->GetXaxis()->SetTitle("#Delta R(l_{W}-Z)");
  if(theVariable == "deltaPhiZmet_BDTcut"  ) histo_ratio->GetXaxis()->SetTitle("#Delta #phi(Z-met)");
  if(theVariable == "btagDiscri_BDTcut"    ) histo_ratio->GetXaxis()->SetTitle("CSV discr.");
  if(theVariable == "leptWPt_BDTcut"       ) histo_ratio->GetXaxis()->SetTitle("p_{T}(l_{W}) [GeV]");
  if(theVariable == "leptWEta_BDTcut"      ) histo_ratio->GetXaxis()->SetTitle("#eta(l_{W})");
  if(theVariable == "leadJetPt_BDTcut"     ) histo_ratio->GetXaxis()->SetTitle("Leading jet p_{T} [GeV]");
  if(theVariable == "leadJetEta_BDTcut"    ) histo_ratio->GetXaxis()->SetTitle("Leading jet #eta");
  if(theVariable == "deltaPhiZleptW_BDTcut") histo_ratio->GetXaxis()->SetTitle("#Delta #phi(Z-l_{W})");
  
  
  
  
  
  
  histo_ratio->GetXaxis()->SetLabelSize(0.07);
  
  
  
  
  
  TPad *canvas_2 = new TPad("canvas_2", "canvas_2", 0.0, 0.0, 1.0, 1.0);
  canvas_2->SetTopMargin(0.7);
  canvas_2->SetFillColor(0);
  canvas_2->SetFillStyle(0);
  canvas_2->SetGridy(1);
  canvas_2->Draw();
  canvas_2->cd(0);
  histo_ratio->SetTitle("");
  
  histo_ratio->SetMarkerStyle(20);
  histo_ratio->SetMarkerSize(1.2);
  histo_ratio->SetMaximum( 1.5 );
  histo_ratio->SetMinimum(0.5);
  histo_ratio->GetYaxis()->SetTitle("");
  histo_ratio->GetXaxis()->SetLabelSize(0.04);
  histo_ratio->GetYaxis()->SetLabelSize(0.04);
  histo_ratio->GetYaxis()->SetNdivisions(6);
  
  histo_ratio->GetYaxis()->SetTitleSize(0.03);
  histo_ratio->SetMarkerSize(1.2);
  //histo_ratio->GetYaxis()->SetNdivisions(5);
  //ratio.Draw("e")
  
  histo_ratio->SetMinimum(0.0);
  histo_ratio->SetMaximum(2.0);
  histo_ratio->Draw("E1X0");

  
  
  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.04);
  latex->SetTextAlign(31); 
  latex->DrawLatex(0.45, 0.95, "CMS Preliminary");
  TLatex *latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.04);
  latex2->SetTextAlign(31); 
  latex2->DrawLatex(0.87, 0.95, "4.9 fb^{-1} at #sqrt{s} = 7 TeV");

  TString info_data = "eee, #mu#mu#mu, e#mu#mu, ee#mu channels";; 
 
  
  //text2 = new TLatex(0.15,0.8, info_data);
  TLatex * text2 = new TLatex(0.45,0.98, info_data);
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.18);
  text2->SetY(0.92);
  //text2->SetLineWidth(2);
  text2->SetTextFont(42);
  text2->SetTextSize(0.0610687);
  //    text2->SetTextSizePixels(24);// dflt=28
  text2->Draw();
  
  
  
  
  
  
  
  
  
  
  
  
  TLegend* qw = new TLegend(.80,.70,.95,.90);
  
  
  if(theVariable == "deltaPhilb"     ||
     theVariable == "deltaPhiZleptW" || 
     theVariable == "deltaPhiZmet"   ||
     theVariable == "deltaRlb"	     ||
     theVariable == "deltaRTopZ"     ||
     theVariable == "deltaRZl"	   ) qw = new TLegend(.20,.60,.35,.80);
   
  qw->SetShadowColor(0);
  qw->SetFillColor(0);
  qw->SetLineColor(0);
  qw->AddEntry(histBdt_Data,         "Data" ,                "ep");
  qw->AddEntry(histBdt_WZ,           "VV "                  ,"f");
  qw->AddEntry(histBdt_DataZjets,    "non-prompt Lept. "                  ,"f");
  qw->AddEntry(histBdt_TTbar    ,    "t#bar{t}, single top"                  ,"f");
  qw->AddEntry(histBdt_TZq    ,    "tZq SM"                  ,"f");
  if(!doBtagUncerOnly) qw->AddEntry(histBdt_FCNC,     " tZ 0.1 pb"     ,"l");
  else qw->AddEntry(histBdt_FCNC,     " All Background, no btag reweighting "     ,"l");

  
  qw->SetFillColor(0);
  qw->SetTextFont(42);
  qw->Draw();
  
  
  
  c1->SaveAs( ("plots/"+theVariable+"_"+theVertex+".pdf").Data());
  c1->SaveAs( ("plots/"+theVariable+"_"+theVertex+".gif").Data());
  
  
}
  

void PlotBDToutput(){




   TString thevertex_zut = "zut";
   TString thevertex_zct = "zct";
   TString thevertex_kut = "kut";
   TString thevertex_kct = "kct";
   TString thevertex_xut = "xut";
   TString thevertex_xct = "xct";
   
   TString theFile_zut = "HistoBDToutput/TMVApp_zut_nom.root";
   
   //TString theFile_zut_btagup   = "HistoBDToutput/TMVApp_zut_btagup.root";
   //TString theFile_zut_btagdown = "HistoBDToutput/TMVApp_zut_btagdown.root";
   
   TString theFile_zct = "HistoBDToutput/TMVApp_zct_nom.root";
   TString theFile_kut = "HistoBDToutput/TMVApp_kut_nom.root";
   TString theFile_kct = "HistoBDToutput/TMVApp_kct_nom.root";
   //TString theFile_zut = "HistoBDToutput/TMVApp_zut_bdtcutnom.root";
   //TString theFile_zut = "HistoBDToutput/TMVApp_zut_btagup.root";
   //TString theFile_zut = "HistoBDToutput/TMVApp_zut_btagdown.root";
   
   //PlotBDToutput(thevertex_zut, "btagDiscri"    , theFile_zut);
   //PlotBDToutput(thevertex_zut, "btagDiscri"    , theFile_zut_btagup);
   //PlotBDToutput(thevertex_zut, "btagDiscri"    , theFile_zut_btagdown);
   
   //PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut); 
   //PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut_btagup); 
    //PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut_btagdown); 
   
    
/*TString theFile_zct = "HistoBDToutput/TMVApp_zct_nom.root";
   TString theFile_kut = "HistoBDToutput/TMVApp_kut_nom.root";
   TString theFile_kct = "HistoBDToutput/TMVApp_kct_nom.root";
   TString theFile_xut = "HistoBDToutput/TMVApp_xut_nom.root";
   TString theFile_xct = "HistoBDToutput/TMVApp_xct_nom.root";*/
   //PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut);  
   /*
   PlotBDToutput(thevertex_zut, "MVA_BDT"       , theFile_zut);
   PlotBDToutput(thevertex_zct, "MVA_BDT"       , theFile_zct);
   PlotBDToutput(thevertex_kut, "MVA_BDT"       , theFile_kut);
   PlotBDToutput(thevertex_kct, "MVA_BDT"       , theFile_kct);
   */
   
   /*
   
   PlotBDToutput(thevertex_zut, "topMass"       , theFile_zut);
   //PlotBDToutput(thevertex_zut, "totMass"       , theFile_zut);
   PlotBDToutput(thevertex_zut, "deltaPhilb"    , theFile_zut);
   //PlotBDToutput(thevertex_zut, "deltaRlb"      , theFile_zut);
   //PlotBDToutput(thevertex_zut, "deltaRTopZ"    , theFile_zut);
   PlotBDToutput(thevertex_zut, "asym"          , theFile_zut);
   PlotBDToutput(thevertex_zut, "Zpt"           , theFile_zut);
   PlotBDToutput(thevertex_zut, "ZEta"          , theFile_zut);
   //PlotBDToutput(thevertex_zut, "topPt"         , theFile_zut);
   //PlotBDToutput(thevertex_zut, "topEta"        , theFile_zut);
   PlotBDToutput(thevertex_zut, "NJets"         , theFile_zut);   
   PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut);  
   PlotBDToutput(thevertex_zut, "deltaRZl"      , theFile_zut); 
   PlotBDToutput(thevertex_zut, "deltaPhiZmet"  , theFile_zut);
   PlotBDToutput(thevertex_zut, "btagDiscri"    , theFile_zut);
   //PlotBDToutput(thevertex_zut, "leptWPt"       , theFile_zut);
   //PlotBDToutput(thevertex_zut, "leptWEta"      , theFile_zut);	    
   PlotBDToutput(thevertex_zut, "leadJetPt"     , theFile_zut);	      
   PlotBDToutput(thevertex_zut, "leadJetEta"    , theFile_zut);         
   PlotBDToutput(thevertex_zut, "deltaPhiZleptW", theFile_zut);
   */
   
   /*PlotBDToutput(thevertex_zct, "topMass"       , theFile_zct);
   PlotBDToutput(thevertex_zct, "totMass"       , theFile_zct);
   PlotBDToutput(thevertex_zct, "deltaPhilb"    , theFile_zct);
   PlotBDToutput(thevertex_zct, "deltaRlb"      , theFile_zct);
   PlotBDToutput(thevertex_zct, "deltaRTopZ"    , theFile_zct);
   PlotBDToutput(thevertex_zct, "asym"          , theFile_zct);
   PlotBDToutput(thevertex_zct, "Zpt"           , theFile_zct);
   PlotBDToutput(thevertex_zct, "ZEta"          , theFile_zct);
   PlotBDToutput(thevertex_zct, "topPt"         , theFile_zct);
   PlotBDToutput(thevertex_zct, "topEta"        , theFile_zct);
   PlotBDToutput(thevertex_zct, "NJets"         , theFile_zct);   
   PlotBDToutput(thevertex_zct, "NBJets"        , theFile_zct);  
   PlotBDToutput(thevertex_zct, "deltaRZl"      , theFile_zct); 
   PlotBDToutput(thevertex_zct, "deltaPhiZmet"  , theFile_zct);
   PlotBDToutput(thevertex_zct, "btagDiscri"    , theFile_zct);
   PlotBDToutput(thevertex_zct, "leptWPt"       , theFile_zct);
   PlotBDToutput(thevertex_zct, "leptWEta"      , theFile_zct);	    
   PlotBDToutput(thevertex_zct, "leadJetPt"     , theFile_zct);	      
   PlotBDToutput(thevertex_zct, "leadJetEta"    , theFile_zct);         
   PlotBDToutput(thevertex_zct, "deltaPhiZleptW", theFile_zct);
   */


}


#include "TString.h"
#include "TH1F.h"
#include "TStyle.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include <iostream>





void PlotBDToutput(TString theVertex, TString theVariable, TString theFile){
  
  double WZscale = 1.;
  
  
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
   TH1F * histBdt_TTbar     = (TH1F*)filechannel->Get( (theVariable+"_TTbarSig" ).Data());
   TH1F * histBdt_TZq       = (TH1F*)filechannel->Get( (theVariable+"_TZq"      ).Data());
   
   
   TH1F * histBdt_FCNC ;     
   if(theVariable == "MVA_BDT"){
     histBdt_FCNC = (TH1F*)filechannel->Get((theVariable+"_FCNC_"+theVertex).Data());	 
   }
   else{
     histBdt_FCNC = (TH1F*)filechannel->Get((theVariable+"_Signal").Data());	 
   } 
  
  
  histBdt_FCNC->Scale(0.1);
  histBdt_Data->SetLineColor(1);
  
  if(theVariable!="NJets" && theVariable!="NBJets"){
    histBdt_Data->Rebin(2);  
    histBdt_WZ->Rebin(2);	     
    histBdt_ZZ->Rebin(2);	     
    histBdt_TTbar->Rebin(2);	     
    histBdt_Zjets->Rebin(2);	     
    histBdt_FCNC->Rebin(2);  
    histBdt_DataZjets->Rebin(2);
    histBdt_TZq->Rebin(2);
  }
  
  //histBdt_WZ->Scale(0.905713);
  histBdt_WZ->Scale(WZscale);
  histBdt_WZ->Add(histBdt_ZZ);
  histBdt_DataZjets->Scale(histBdt_Zjets->Integral()/histBdt_DataZjets->Integral());
  
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



  
  hs->Draw();
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
  histBdt_FCNC->Draw("same");
  
  
  
  TH1F* herrorband =  (TH1F*) histBdt_WZ->Clone();
  herrorband->Add(histBdt_DataZjets);
  for (int ierr=0; ierr<herrorband->GetNbinsX(); ierr++) {
    double error_all = pow(histBdt_WZ->GetBinError(ierr), 2) // stat
                        + pow(histBdt_WZ->GetBinContent(ierr)*0.17/WZscale, 2) // syst SF 
                        + pow(histBdt_DataZjets->GetBinError(ierr), 2) // stat
                        + pow(histBdt_DataZjets->GetBinContent(ierr)*0.30, 2) // syst SF
                        + pow(histBdt_ZZ->GetBinContent(ierr)*0.30, 2) // syst SF 
                        + pow(histBdt_TTbar->GetBinContent(ierr)*0.30, 2) // syst SF 
                        + pow(histBdt_TZq->GetBinContent(ierr)*0.30, 2) // syst SF 
                        + pow(herrorband->GetBinContent(ierr)*0.025, 2); // syst lumi
    herrorband->SetBinError(ierr, sqrt(error_all));
    
  }
  
  
  

  TGraphErrors *thegraph = new TGraphErrors(herrorband);
  thegraph->SetFillStyle(3005);
  thegraph->SetFillColor(1);
  
  thegraph->Draw("e2same");
  
  
  
  
  
  TH1F * histo_ratio = (TH1F*) histBdt_Data->Clone();
  TH1F * histo_mc    = (TH1F*) histBdt_WZ->Clone();
  histo_mc->Add(histBdt_DataZjets);
  histo_mc->Add(histBdt_TTbar);
  histo_mc->Add(histBdt_TZq);
  histo_ratio->Sumw2();
  histo_mc->Sumw2();
  histo_ratio->Divide(histo_ratio, histo_mc, 1, 1, "b");
  
  for (int ierr=0; ierr<histo_ratio->GetNbinsX(); ierr++) {
    
    double num     = histBdt_Data->GetBinContent(ierr);
    double num_err = histBdt_Data->GetBinError(ierr);
    
    double denom     = herrorband->GetBinContent(ierr);
    double denom_err = herrorband->GetBinError(ierr);
    
    double error = pow(
       pow(num_err/denom, 2)+
       pow(num*num_err/(denom*denom), 2)
    , 0.5);
    histo_ratio->SetBinError(ierr,error );
  }
  
  
  
  
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
  qw->AddEntry(histBdt_DataZjets,    "Fake Lept. "                  ,"f");
  qw->AddEntry(histBdt_TTbar    ,    "t#bar{t}, single top"                  ,"f");
  qw->AddEntry(histBdt_TZq    ,    "tZq SM"                  ,"f");
  qw->AddEntry(histBdt_FCNC,     " tZ "     ,"l");

  
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
   TString theFile_zct = "HistoBDToutput/TMVApp_zct_nom.root";
   TString theFile_kut = "HistoBDToutput/TMVApp_kut_nom.root";
   TString theFile_kct = "HistoBDToutput/TMVApp_kct_nom.root";
   TString theFile_xut = "HistoBDToutput/TMVApp_xut_nom.root";
   TString theFile_xct = "HistoBDToutput/TMVApp_xct_nom.root";
   
   PlotBDToutput(thevertex_zut, "MVA_BDT"       , theFile_zut);
   /*PlotBDToutput(thevertex_zut, "topMass"       , theFile_zut);
   PlotBDToutput(thevertex_zut, "totMass"       , theFile_zut);
   PlotBDToutput(thevertex_zut, "deltaPhilb"    , theFile_zut);
   PlotBDToutput(thevertex_zut, "deltaRlb"      , theFile_zut);
   PlotBDToutput(thevertex_zut, "deltaRTopZ"    , theFile_zut);
   PlotBDToutput(thevertex_zut, "asym"          , theFile_zut);
   PlotBDToutput(thevertex_zut, "Zpt"           , theFile_zut);
   PlotBDToutput(thevertex_zut, "ZEta"          , theFile_zut);
   PlotBDToutput(thevertex_zut, "topPt"         , theFile_zut);
   PlotBDToutput(thevertex_zut, "topEta"        , theFile_zut);
   PlotBDToutput(thevertex_zut, "NJets"         , theFile_zut);   
   PlotBDToutput(thevertex_zut, "NBJets"        , theFile_zut);  
   PlotBDToutput(thevertex_zut, "deltaRZl"      , theFile_zut); 
   PlotBDToutput(thevertex_zut, "deltaPhiZmet"  , theFile_zut);*/
   PlotBDToutput(thevertex_zut, "btagDiscri"    , theFile_zut);/*
   PlotBDToutput(thevertex_zut, "leptWPt"       , theFile_zut);
   PlotBDToutput(thevertex_zut, "leptWEta"      , theFile_zut);	    
   PlotBDToutput(thevertex_zut, "leadJetPt"     , theFile_zut);	      
   PlotBDToutput(thevertex_zut, "leadJetEta"    , theFile_zut);         
   PlotBDToutput(thevertex_zut, "deltaPhiZleptW", theFile_zut);*/
   
   
   PlotBDToutput(thevertex_zct, "MVA_BDT"       , theFile_zct);
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

   PlotBDToutput(thevertex_kut, "MVA_BDT"       , theFile_kut);
   PlotBDToutput(thevertex_kct, "MVA_BDT"       , theFile_kct);
}

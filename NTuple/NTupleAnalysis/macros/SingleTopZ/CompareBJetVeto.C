{

  gROOT->ProcessLine(".L Compare.C");
 
  char* rootfile="backup_outputProof05-10-12_19-28-30/proof.root"; 
  bool log=false;
  char* filename="";
  bool print=false;
  bool ratio=true;

  char* channel[4] = {"mumumu", "mumue", "eemu", "eee"};


  for(int i=0; i<4; i++)
  {
  cout<<"Channel "<<channel[i]<<endl;

  Draw2Histos(Form("RecoPtZ_%s_afterbjetsel_FCNCkut", channel[i]), Form("RecoPtZ_%s_afterbjetveto_FCNCkut", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);


  Draw2Histos(Form("mWT_%s_afterbjetsel_WZ", channel[i]), Form("mWT_%s_afterbjetveto_WZ", channel[i]), 
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("RecoPtZ_%s_afterbjetsel_WZ", channel[i]), Form("RecoPtZ_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);
 
  Draw2Histos(Form("HT_%s_afterbjetsel_WZ", channel[i]), Form("HT_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("deltaPhilb_%s_afterbjetsel_WZ", channel[i]), Form("deltaPhilj_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("Mt_%s_afterbjetsel_WZ", channel[i]), Form("Mt_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("RecoTopMass_%s_afterbjetsel_WZ", channel[i]), Form("RecoTopMass_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("LeptWPt_%s_afterbjetsel_WZ", channel[i]), Form("LeptWPt_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);

  Draw2Histos(Form("JetPt_%s_afterbjetsel_WZ", channel[i]), Form("JetPt_%s_afterbjetveto_WZ", channel[i]),
              rootfile, "1 b", "no b", log, filename, print, ratio);
  }

}

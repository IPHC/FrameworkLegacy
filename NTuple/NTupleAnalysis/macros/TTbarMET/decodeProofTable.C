{


TFile *_file0 = TFile::Open("backup_outputProof10-07-12_15-50-25/proof.root");

const int DataSetMax=2;
int DataSetNumber=1;
const int chan=3;
const int cut=10;

TH1F* ha1[DataSetMax];
TH1F* ha2[DataSetMax];
TH1F* ha3[DataSetMax];

float table[DataSetMax][chan][cut];
float error[DataSetMax][chan][cut];
TString DataSetName[DataSetMax];


for (int i=0; i<DataSetNumber; i++) {
 if (i==0) DataSetName[i]="signal";
 TString ha1_name="TTbarMetAnaPlots/NofEvents/lepton/All/"+DataSetName[i]+"/NofEvents";
 TString ha2_name="TTbarMetAnaPlots/NofEvents/e/All/"+DataSetName[i]+"/NofEvents";
 TString ha3_name="TTbarMetAnaPlots/NofEvents/mu/All/"+DataSetName[i]+"/NofEvents";
 ha1[i] = (TH1F*)_file0->Get(ha1_name);
 ha2[i] = (TH1F*)_file0->Get(ha2_name);
 ha3[i] = (TH1F*)_file0->Get(ha3_name);
 int Ncut=ha1[i].GetNbinsX();
 cout << DataSetName[i] <<   "  1lepton          e           mu " <<  endl;
 for (int j=0; j<Ncut; j++) {
   table[i][0][j]= ha2[i].GetBinContent(j+1); // e
   table[i][1][j]= ha3[i].GetBinContent(j+1); // mu
   table[i][2][j]= ha1[i].GetBinContent(j+1); // lepton
   error[i][0][j]= ha2[i].GetBinError(j+1); // e
   error[i][1][j]= ha3[i].GetBinError(j+1); // mu
   error[i][2][j]= ha1[i].GetBinError(j+1); // lepton
   cout << " cut "<< j <<  "   " << ha1[i].GetBinContent(j+1) << "      " << ha2[i].GetBinContent(j+1) << "       " << ha3[i].GetBinContent(j+1) << endl;
 }
}
for (int j=0; j<Ncut; j++) {
   table[DataSetNumber][0][j]=0.;
   table[DataSetNumber][1][j]=0.;
   table[DataSetNumber][2][j]=0.;
   error[DataSetNumber][0][j]=0.;
   error[DataSetNumber][1][j]=0.;
   error[DataSetNumber][2][j]=0.;
}

// ecriture de la table 
    string ofilenametex = "table.tex";
    ofstream ofile(ofilenametex.c_str());
        
    ofile<<"\\documentclass[8pt]{article}"<<endl;
    ofile<<"\\usepackage{lscape}"<<endl;
    ofile<<"\\begin{document}"<<endl;


    ofile.setf(ios::fixed);
    ofile.precision(1);
    
    vector<string> CutName;
    CutName.push_back ("All");
    CutName.push_back ("Trigger");
    CutName.push_back ("1 Lepton");
    CutName.push_back ("Veto on other leptons");
    CutName.push_back ("NJets $\\ge$ 4");
    CutName.push_back ("NbtagJets $\\ge$ 1");
    CutName.push_back ("NbtagJets $\\ge$ 2");

    float tabtotmc[chan][cut];
    float errtotmc[chan][cut];
    float tabtotbg[chan][cut];
    float errtotbg[chan][cut];
    //**************************
    //Compute total mc & bg
    for(int k1=0; k1<chan; ++k1) {
      for(int k2=0; k2<CutName.size(); ++k2) {
        for(int k0=0; k0<DataSetNumber; ++k0) {
            if (DataSetNumber>1) {
              tabtotbg[k1][k2] += table[k0][k1][k2];
              errtotbg[k1][k2] += error[k0][k1][k2]*error[k0][k1][k2];
            }
            else {
              tabtotbg[k1][k2] =0.;
              errtotbg[k1][k2] =0.;
            }
            tabtotmc[k1][k2] += table[k0][k1][k2];
            errtotmc[k1][k2] += error[k0][k1][k2]*error[k0][k1][k2];
         }  
         errtotbg[k1][k2] = sqrt(errtotbg[k1][k2]);
         errtotmc[k1][k2] = sqrt(errtotmc[k1][k2]);
      }
    }
    //*********************************

    for (int IChannel=0; IChannel<chan; IChannel++) {
      
    // Summary tables
//     ofile << "\\clearpage" << endl;
//     ofile << "\\begin{landscape}" << endl;
     ofile << "\\begin{table}[p]" << endl;
      
     ofile << "\\begin{tabular}{|l|c|c|c|c|c|}" << endl;
     ofile << "\\hline" << endl;
     ofile << "\\hline" << endl; 
     ofile << "Cut & Data & Total MC & Signal  & Total Background & S/B \\\\" << endl;
     ofile << "\\hline" << endl;
     for(int ic=0; ic<CutName.size(); ++ic) {
          // en attendant d'avoir toutes les infos; [DataSetNumber]--> 0.
          ofile.precision(1);
          ofile << CutName[ic]
                << " & " <<  table[DataSetNumber][IChannel][ic] << " $\\pm$ "<<  error[DataSetNumber][IChannel][ic] ;
//          ofile.precision(3);
          ofile.precision(1);
          ofile << " & " <<  tabtotmc[IChannel][ic] << " $\\pm$ "<<  errtotmc[IChannel][ic]
                << " & " <<  table[0][IChannel][ic] << " $\\pm$ "<<  error[0][IChannel][ic]
                << " & " <<  tabtotbg[IChannel][ic] << " $\\pm$ "<<  errtotbg[IChannel][ic] ;
          if (tabtotbg[IChannel][ic]>0.) ofile << " & " <<  table[0][IChannel][ic]/tabtotbg[IChannel][ic] ;
          else ofile << " &  --- " ;
          ofile  << " \\\\" << endl;
      }
      ofile << "\\hline" << endl;
      ofile << "\\hline" << endl;
      ofile << "\\end{tabular}" << endl;


      if (DataSetNumber>1) {
       ofile << "\\begin{tabular}{|l|c|c|c|c|c|}" << endl;
       ofile << "\\hline" << endl;
       ofile << "\\hline" << endl;
       ofile << "Cut " ;
       int idmax=DataSetNumber;
       if (DataSetNumber>6) idmax=6;
       for(int id=1; id<idmac; ++id) {
          ofile << " & " << DataSetName[id];
       }
       if (DataSetNumber<6) {
        for(int id=idmax; id<6; ++id) {
          ofile << " & " ;
        }
       }
       ofile << endl;
       ofile << "\\hline" << endl;
       for(int ic=0; ic<CutName.size(); ++ic) {
          // en attendant d'avoir toutes les infos; [DataSetNumber]--> 0.
          ofile.precision(1);
          ofile << CutName[ic];
          for(int id=1; id<idmac; ++id) { 
               ofile << " & " <<  table[id][IChannel][ic] << " $\\pm$ "<<  error[id][IChannel][ic] ;
          }
          if (DataSetNumber<6) {
            for(int id=idmax; id<6; ++id) {
              ofile << " & " ;
            }
          }
          //ofile.precision(3);
          ofile.precision(1);
          ofile  << " \\\\" << endl;
       }
       ofile << "\\hline " << endl;
       ofile << "\\hline" << endl;
       ofile << "\\end{tabular}" << endl;
      }
      if (IChannel==0) {
      ofile << "\\caption{Number of events - channel e}" << endl;
      ofile << "\\label{tab:SelectionTable_e}" << endl;
      }
      else if (IChannel==1) {
      ofile << "\\caption{Number of events - channel $\\mu$}" << endl;
      ofile << "\\label{tab:SelectionTable_mu}" << endl;
      }
      else if (IChannel==2) {
      ofile << "\\caption{Number of events - channel lepton} " << endl;
      ofile << "\\label{tab:SelectionTable_lep}" << endl;
      }
      ofile << "\\end{table}" << endl;
//      ofile << "\\end{landscape}" << endl;
    } // end loop IChannel
    ofile<<"\\end{document}"<<endl;
    string prodpdf = string("pdflatex ")+ofilenametex;
    system(prodpdf.c_str());

}

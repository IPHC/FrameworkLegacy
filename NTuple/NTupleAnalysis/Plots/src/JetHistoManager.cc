#include "Plots/interface/JetHistoManager.h"




JetHistoManager::JetHistoManager(){
}

JetHistoManager::~JetHistoManager(){
}


void JetHistoManager::CreateHistos(){
	AddHisto(string("Multiplicity"),string("#(jets)"),string("Nof jets"),10,0,10);	
	AddHisto(string("Pt"),string("Pt(jet)"),string("p_{T}(jet)"),50,0,100);	
	AddHisto(string("Eta"),string("Eta(jet)"),string("#eta(jet)"),60,-3,3);	
	AddHisto(string("Phi"),string("Phi(jet)"),string("#phi(jet)"),64,-3.2,3.2);	
	AddHisto(string("TCDisc"),string("TCDisc(jet)"),string("TCDisc(jet)"),10,-50,50);	
	AddHisto(string("SVDisc"),string("SVDisc(jet)"),string("SVDisc(jet)"),10,-50,50);	
	AddHisto(string("SMDisc"),string("SMDisc(jet)"),string("SMDisc(jet)"),10,-50,50);	
}

void JetHistoManager::Fill(const vector<NTJet>& jets, const int& maxSelStep, const int& iChannel, const int& iDataset, const float& weight){
	if(!Check(iChannel, iDataset)) return;
	for(unsigned int i=0;i<SelectionSteps.size();i++){
		if(maxSelStep>=(int)i) FillSelStep(jets, i , iChannel, iDataset, weight);	
	}	
}

void JetHistoManager::FillSelStep(const vector<NTJet>& jets, const int& iSelStep, const int& iChannel, const int& iDataset, const float& weight){
        if(!Check(iChannel, iSelStep, iDataset, 0) ) return;
	Histos[0][iChannel][iSelStep][iDataset].Fill(jets.size(),weight);
	for(int i=0;i<(int) jets.size();i++){
		//very important:
		//respect the order of the function CreateHistos to fill the histograms
		Histos[1][iChannel][iSelStep][iDataset].Fill(jets[i].p4.Pt(),weight);
		Histos[2][iChannel][iSelStep][iDataset].Fill(jets[i].p4.Eta(),weight);
		Histos[3][iChannel][iSelStep][iDataset].Fill(jets[i].p4.Phi(),weight);
		Histos[4][iChannel][iSelStep][iDataset].Fill(jets[i].bTag["TCDiscri"],weight);
		Histos[5][iChannel][iSelStep][iDataset].Fill(jets[i].bTag["SVDiscri"],weight);
		Histos[6][iChannel][iSelStep][iDataset].Fill(jets[i].bTag["SMDiscri"],weight);
	}
}



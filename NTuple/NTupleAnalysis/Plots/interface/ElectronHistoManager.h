#ifndef ElectronHistoManager_h
#define ElectronHistoManager_h

#include "NTFormat/interface/NTElectron.h"
#include "Plots/interface/HistoManager.h"


using namespace IPHCTree;

class ElectronHistoManager: public HistoManager{

  public:
	ElectronHistoManager();
	~ElectronHistoManager();

	//Initialisation methods

	void CreateHistos(); /** Create a bunch of standard histos */

	//Fill methods
	void Fill(const vector<NTElectron>& electrons, const int& maxSelStep, const int& iChannel, const int& iDataset, const float& weight);
	void FillSelStep(const vector<NTElectron>& electrons, const int& iSelStep, const int& iChannel, const int& iDataset, const float& weight);


};

#endif

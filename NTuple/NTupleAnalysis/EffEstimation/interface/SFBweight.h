#ifndef SFBweight_h
#define SFBweight_h

#include "../../../../IPHCDataFormat/NTFormat/interface/NTEvent.h"

// system include files
#include <memory>
#include <vector>
#include <fstream>
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TFile.h"



using namespace std;
using namespace IPHCTree;

class SFBweight {

   public:
	SFBweight();
	SFBweight(int, float, int );
        ~SFBweight();

	void SFBinit(int, float, int );
        void LoadInfo();
        void LoadInfo2();
        float GetWeight(int, int, float, float);
        vector<float> GetWeigth4BSel(int,  int, const std::vector<NTJet> &  selJets);
        vector<float> GetWeigth4BSel(int method_b,  int syst_b, const std::vector<NTJet> &  selJets, float sf_val_for_b, float sf_val_for_l);
        TH2D* GetHistoSFB();

   private:
        std::string method_origin1_;
        std::string method_origin2_;

        TH2D* histo_sfvalb_;
        TH2D* histo_sferrb_;
        TH2D* histo_sfvall_;
        TH2D* histo_sferrl_;

        TH2D* histo_effvalb_;
        TH2D* histo_efferrb_;
        TH2D* histo_effvall_;
        TH2D* histo_efferrl_;

        TH2D* histo_effmcb_;
        TH2D* histo_effmcc_;
        TH2D* histo_effmcl_;

        TH2D* histo_errmcb_;
        TH2D* histo_errmcc_;
        TH2D* histo_errmcl_;

        int btag_algo_;
        float btag_discri_;
        int n_bjets_;

};

#endif



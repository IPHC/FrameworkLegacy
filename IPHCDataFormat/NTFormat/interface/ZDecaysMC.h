#ifndef __TOP_TREE_ZDECAY_EVTMC_H__
#define __TOP_TREE_ZDECAY_EVTMC_H__

#include <vector>
#include "TLorentzVector.h"

using namespace std;

namespace IPHCTree
{

  class ZDecaysMC
  {

  public:

    //methods
    ZDecaysMC ()
	{
		Q_Lep1_gen = -99.0;
		Q_Lep2_gen = -99.0;
		Lep1_pdgID = -99;
		Lep2_pdgID = -99;
		Tmeme      = -99;
		Zgtobb     = -99;
		mcMotherId = -99;
	};

    ~ZDecaysMC (){};

    //data memebers  
    TLorentzVector p4_Z_gen;
    TLorentzVector p4_Lep1_gen;
    TLorentzVector p4_Lep2_gen;
    TLorentzVector p4_SumTauNeu_gen;
    TLorentzVector p4_SumTauANeu_gen;
    
	double Q_Lep1_gen;
    double Q_Lep2_gen;
    
	int Lep1_pdgID;
    int Lep2_pdgID;
    int Tmeme;
    int Zgtobb;
	int mcMotherId;
  
  };
}




#endif				//__TOP_TREE_ZDECAY_PARTON_EVT_H__

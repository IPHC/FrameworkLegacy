#ifndef __TOP_TREE_WDECAY_EVTMC_H__
#define __TOP_TREE_WDECAY_EVTMC_H__

#include <vector>
#include "TLorentzVector.h"

using namespace std;

namespace IPHCTree
{

  class WDecaysMC
  {

  public:

    //methods
    WDecaysMC (){Q_Lep_gen=-99.;Tmeme=-99;mcLepId=-99;};
    ~WDecaysMC (){};
    
    /// Clear all information related to the photon
    //virtual void Reset(bool constructor_call=false);
    
    //data members
    double Q_Lep_gen;
    TLorentzVector p4_W_gen;
    TLorentzVector p4_Lep_gen;
    TLorentzVector p4_Neu_gen;
    TLorentzVector p4_SumTauNeu_gen;
    int Tmeme;
    int mcLepId;

  };
}




#endif				//__TOP_TREE_WDECAY_PARTON_EVT_H__

#include "Selection/interface/TTbarMetSelection.h"
using namespace std;


// ----------------------------------------------------------------------------
// Default constructor
// ----------------------------------------------------------------------------
TTbarMetSelection::TTbarMetSelection ()
{
  btagAlgo_       = -1;
  btagDiscriCut_  = -999.;
  NofBtagJets_    = 0;

  //Fill the table of cuts
  cuts_.push_back ("All");
  cuts_.push_back ("Trigger");
  cuts_.push_back ("1 Lepton");
  cuts_.push_back ("Veto on other leptons");
  cuts_.push_back ("NJets cut");
  cuts_.push_back ("NbtagJets cut1");
  cuts_.push_back ("NbtagJets cut2");

  //Fill Channels
  channels_.push_back (string ("e"));
  channels_.push_back (string ("mu"));
}


// ----------------------------------------------------------------------------
// Copy constructor
// ----------------------------------------------------------------------------
TTbarMetSelection::TTbarMetSelection(const TTbarMetSelection & s):
                                                                 Selection (s)
{
  cuts_          = s.cuts_;
  channels_      = s.channels_;
  btagAlgo_      = s.btagAlgo_;
  btagDiscriCut_ = s.btagDiscriCut_;
  NofBtagJets_   = s.NofBtagJets_;
}


// ----------------------------------------------------------------------------
// SetParameters
// ----------------------------------------------------------------------------
void TTbarMetSelection::SetParameters(  int btagAlgo,
                                        float btagDiscriCut,
                                        int NofBtagJets)
{
  btagAlgo_      = btagAlgo;
  btagDiscriCut_ = btagDiscriCut;
  NofBtagJets_   = NofBtagJets;
}



int TTbarMetSelection::doFullSelection (Dataset * dataset, string channelName, bool print, 
	  bool applyJES, float JESParam, bool applyEES, float EESParam, bool applyMES, float MESParam, bool applyJER, float JERFactor, bool applyMETS, float METScale)
{
 
  //clear object collections
  jetsAna.clear();
  bjetsAna.clear();
  electronsAna.clear();
  muonsAna.clear();

  //boolean for the selection step: true = pass the cut
  bool step_trigger = false;
  bool step_trigger_e = false;
  bool step_trigger_mu = false;
  bool step_1lepton = false;
  bool step_1lepton_e = false;
  bool step_1lepton_mu = false;
  bool step_vetomu = false;
  bool step_jets = false;
  bool step_bjets1 = false;
  bool step_bjets2 = false;


  //Collection of selected objects
  NTMET themet = GetSelectedMET(applyJES, JESParam, applyMETS, METScale);
  //Top projection pour l+jets mais probleme le muon est souvent confondu comme un jet????
  vector < NTJet > selJetsPourDuBeurre =  GetSelectedJetsForLJets (applyJES, JESParam, applyJER, JERFactor);
  electronsAna = GetSelectedElectronsForLJets (selJetsPourDuBeurre, applyEES, EESParam);
  muonsAna = GetSelectedMuonsForLJets (selJetsPourDuBeurre, applyMES, MESParam);
  jetsAna = GetSelectedJetsForLJets (muonsAna, electronsAna, applyJES, JESParam, applyJER, JERFactor);

/*
  electronsAna = GetSelectedElectrons (applyEES, EESParam);
  muonsAna = GetSelectedMuons (applyMES, MESParam);
  jetsAna = GetSelectedJets (muonsAna, electronsAna, applyJES, JESParam, applyJER, JERFactor);
*/

  int FinalStep = 0;

  //Step 1        Trigger
/*
  step_trigger_e = passTriggerSelection (dataset, string("e") );
  step_trigger_mu = passTriggerSelection (dataset, string("mu") );
*/
// ici a true pour le moment!
  step_trigger_e=true;
  step_trigger_mu=true;
  if (step_trigger_e || step_trigger_mu) step_trigger= true;
  if (step_trigger) {
    //Step 2        Le Lepton Isole
     if (electronsAna.size()+muonsAna.size()==1) {
//        && ( (channelName=="mu" && muonsAna.size()==1) || (channelName=="e" && electronsAna.size()==1)) ) {
      step_1lepton = true;
      if (electronsAna.size()==1) {
         step_1lepton_e = true;
         LeptonType="e";
      }
      else if (muonsAna.size()==1) {
         step_1lepton_mu = true;
         LeptonType="mu";
      }
//      LeptonType=channelName;

      // Step 3 Veto muon
      std::vector < NTMuon > muVeto = GetVetoMuonsForLJets (applyMES, MESParam);
      std::vector < NTElectron > elVeto = GetVetoElectronsForLJets (applyEES, EESParam);
      bool veto_mu=false;
      bool veto_el=false;
      if (muVeto.size()-muonsAna.size()==0) veto_mu=true;
       if (LeptonType=="e") {
         if (elVeto.size()==1) veto_el=true;
         else {
           // en fait pour les electrons le thr en pt est a 20 GeV!
           if (elVeto[1].p4.Pt()<20) veto_el=true;
         }
      }
      else {
         if (elVeto.size()==0) veto_el=true;
      }
      if (veto_mu && veto_el) {
       step_vetomu = true; 
      
       //Step 4    Minimal jet multiplicity 
       if (jetsAna.size () >= 4) {
  	 step_jets = true;
         FillKinematicP4(muonsAna, electronsAna, themet, jetsAna) ;

        //Step 5 btagging   // a terme mettre ca dans le xml
        //cas CSV ou JP : recommandation de BTV  
        // CSVL wp = 0.244 ; CSVM wp = 0.679 ; CSVT wp = 0.898 combinedSecondaryVertexBJetTags 
        // JPL  wp = 0.275 ; JPM  wp = 0.545 ; JPT  wp = 0.790 jetProbabilityBJetTags
        string btag_algo = "combinedSecondaryVertexBJetTags";
        float btag_DiscriCut=0.244;
        NofBtagJets_=1;
        vector < float >btagDiscri;
        for (unsigned int j = 0; j < jetsAna.size (); j++) {
         if (jetsAna[j].bTag[btag_algo] >= btag_DiscriCut) {
            bjetsAna.push_back (jetsAna[j]);
            btagDiscri.push_back (jetsAna[j].bTag[btag_algo]);
         }
        }
        if ((int) bjetsAna.size () >= NofBtagJets_) step_bjets1 = true;
        if ((int) bjetsAna.size () >= 2) step_bjets2 = true;
       } // step 4
      } // step 3
    } // step 2
  } // step 1


  //compute FinalStep
  if (step_trigger) {
    FinalStep++;
    if (step_1lepton) {
      FinalStep++;
      if (step_vetomu) {
       FinalStep++;
       if (step_jets) {
	  FinalStep++;
	  if (step_bjets1) {
	    FinalStep++;
	    if (step_bjets2) {
	      FinalStep++;
	    }
	  }
       }
      }
    }
  }
  if (step_trigger_e) {
    FinalStep+=10;
  }
  if (step_trigger_mu) {
    FinalStep+=20;
  }

  return FinalStep;
}

void TTbarMetSelection::FillKinematicP4(const std::vector < IPHCTree::NTMuon >& muon_kin,
                      const std::vector < IPHCTree::NTElectron >& elec_kin,
                      const IPHCTree::NTMET& met_kin,
                      const std::vector < IPHCTree::NTJet >& jet_kin) {

      // 0. Reset
      TLorentzVector resetvector(0.,0.,0.,0.);
      the_lepton=resetvector;
      all_hadronic=resetvector;
      top_hadronic=resetvector;
      the_met=resetvector;
      the_lepton=resetvector;
      the_4thjet=resetvector;
      w_leptonic=resetvector;
      top_leptonic=resetvector;
      


      // 1. The Lepton
      if (muon_kin.size()==1) {
	the_lepton=muon_kin[0].p4;
      }
      else if (elec_kin.size()==1) {
        the_lepton=elec_kin[0].p4;
      }
      
      // 2. The leptonic W
      TLorentzVector met_initial(met_kin.p2.Px(),met_kin.p2.Py(),0.,met_kin.p2.Mod());
      the_met=met_initial;
      w_leptonic = the_lepton + the_met;

      // 3. Total hadronic activity
      for (UInt_t ind=0;ind<jet_kin.size();ind++) {
         all_hadronic+=jet_kin[ind].p4;
      }


      // 4. The hadronic Top (from M3)
      // 5. The 4th jet (after M3)

      float test_pt=0;
      float test_pt_2=0;

      for (UInt_t ind=0;ind<jet_kin.size();ind++) {
         for (UInt_t ind1=ind+1; ind1<jet_kin.size();ind1++) {
          for (UInt_t ind2=ind1+1; ind2<jet_kin.size();ind2++) {
             TLorentzVector combi_test;
             combi_test=jet_kin[ind].p4;
             combi_test+=jet_kin[ind1].p4;
             combi_test+=jet_kin[ind2].p4;
             if (combi_test.Pt()>test_pt) {
               test_pt=combi_test.Pt();
               top_hadronic=combi_test;
               for (UInt_t ind3=0; ind3<jet_kin.size();ind3++) {
                if (ind3!=ind && ind3!=ind1 && ind3!=ind2 && jet_kin[ind3].p4.Pt()>test_pt_2) {
                    test_pt_2=jet_kin[ind3].p4.Pt();
                    the_4thjet=jet_kin[ind3].p4;
                }
               }
             }
          }
         }
      }    
           
      //5. The leptonic Top
      top_leptonic = w_leptonic + the_4thjet;




}



int TTbarMetSelection::FillTable (SelectionTable & selTable,
                                    Dataset * dataset,
                                    int idataset, float weight)
{

  int sel = doFullSelection (dataset, selTable.Channel (), false);	// true-> has to be modified !!
  for (unsigned int i = 0; i < cuts_.size () + 1; i++)
    if (sel >= (int) i)
      selTable.Fill (idataset, i, weight);
  return sel;
}




bool TTbarMetSelection::passTriggerSelection (Dataset * dataset, string channelName)
{

  bool passEl = false;
  bool passMu = false;
  int skim = -1;

  string datasetName = dataset->Name ();
  if (datasetName.compare(0,6,"DataMu")==0)
    skim = 0;
  if (datasetName.compare(0,6,"DataEG")==0)
    skim = 1;
  
  // cout << " datasetName " << datasetName << endl;A
  // from https://twiki.cern.ch/twiki/bin/view/CMS/TWikiTop2011DataMCTrig#For_MC_spring11
  
  
  if (!dataset->isData ()) 	//MC
  {
    passMu = GetPointer2Trigger()->IsFired("HLT_Mu21_v1") || GetPointer2Trigger()->IsFired("HLT_Mu25_v1") 
             || GetPointer2Trigger()->IsFired("HLT_IsoMu17_v4");

    passEl = GetPointer2Trigger()->IsFired("HLT_Ele32_SW_TighterEleId_L1R_v2");
  }
  else
  {
      // Mu+jets : from AN2011_210_v7 && 
      if (160431<= getRunNumber() && getRunNumber() < 173692 && GetPointer2Trigger()->IsFired("HLT_Mu30_v*")) passMu = true;      // Run2011A
    
      // E+jets : from Lukasz Kreczko 22 mai 2012
      if (160404<= getRunNumber() && getRunNumber() < 163869 && GetPointer2Trigger()->IsFired("HLT_Ele25_CaloIdVT_TrkIdT_CentralTriJet30_v*")) passEl = true;
      else if (163869<= getRunNumber() && getRunNumber() < 165633 && GetPointer2Trigger()->IsFired("HLT_Ele25_CaloIdVT_TrkIdT_TriCentralJet30_v*")) passEl = true;
      else if (165633<= getRunNumber() && getRunNumber() < 178380 && GetPointer2Trigger()->IsFired("HLT_Ele25_CaloIdVT+CaloIsoT_TrkIdT_TrkIsoT_TriCentralJet30_v*")) passEl = true;
      else if (178380<= getRunNumber()                            && GetPointer2Trigger()->IsFired("HLT_Ele25_CaloIdVT+CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30_v*")) passEl = true;

  }

  //if (channelName == string ("ee")) 
  if (channelName.find("e")!=string::npos) 
  {
    if (passEl)
      return true;
    else
      return false;
  }
//  if (channelName == string ("mumu")) 
  if (channelName.find("mu")!=string::npos) 
  {
    if (passMu)
      return true;
    else
      return false;
  }
  return false;

}












     int TTbarMetSelection::GetbtagAlgo () const
     {
       return btagAlgo_;
     }

     float TTbarMetSelection::GetbtagDiscriCut () const
     {
       return btagDiscriCut_;
     }

     int TTbarMetSelection::GetNofBtagJetsCut () const
     {
       return NofBtagJets_;
     }






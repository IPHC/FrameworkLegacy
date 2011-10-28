#include "../interface/SSDiLeptonSelection.h"


SSDiLeptonSelection::SSDiLeptonSelection ()
{
  selCode_ = -1;
  MinMassCut_ = 0.;
  ZMassWindow_ = pair < float, float >(9999., 0.);
  METCuts_ = pair < float, float >(9999., 0.);
  btagAlgo_ = -1;
  btagDiscriCut_ = -999.;
  NofBtagJets_ = 0;
  //Fill the table of cuts
  cuts_.push_back ("All");
  cuts_.push_back ("All dilept");
  cuts_.push_back ("Trigger");
  cuts_.push_back ("DiLepton SS pair");
  cuts_.push_back ("Z mass veto");
  cuts_.push_back ("NJets cut");
  cuts_.push_back ("MET cuts");
  cuts_.push_back ("NbtagJets cut");
  //Fill Channels
  channels_.push_back (string ("ee"));
  channels_.push_back (string ("emu"));
  channels_.push_back (string ("mumu"));

}


int SSDiLeptonSelection::GetChannel (string & CandPairType)
{
  for (unsigned int i = 0; i < channels_.size (); i++) {
    if (channels_[i] == CandPairType)
      return (int) i;
  }
  return -999;
}

SSDiLeptonSelection::SSDiLeptonSelection (const SSDiLeptonSelection & s):Selection (s)
{
  selCode_ = s.selCode_;
//  channel_ = s.channel_;	//
  MinMassCut_ = s.MinMassCut_;
  METCuts_ = s.METCuts_;
  ZMassWindow_ = s.ZMassWindow_;
  cuts_ = s.cuts_;
  channels_ = s.channels_;	//
  btagAlgo_ = s.btagAlgo_;
  btagDiscriCut_ = s.btagDiscriCut_;
  NofBtagJets_ = s.NofBtagJets_;

}

SSDiLeptonSelection::~SSDiLeptonSelection ()
{
}


void SSDiLeptonSelection::SetParameters (float MinValue, pair < float, float >METCuts, pair < float, float >ZMassWindow, int btagAlgo, float btagDiscriCut, int NofBtagJets)
{
  MinMassCut_ = MinValue;
  METCuts_ = METCuts;
  ZMassWindow_ = ZMassWindow;
  btagAlgo_ = btagAlgo;
  btagDiscriCut_ = btagDiscriCut;
  NofBtagJets_ = NofBtagJets;
}



void SSDiLeptonSelection::LoadEvent (const NTEvent * event)
{
  Selection::LoadEvent (event);
//  channel_.LoadEvent (event);
}

bool SSDiLeptonSelection::GetLeptonPair (std::vector < NTMuon > muon_in, std::vector < IPHCTree::NTElectron > elec_in, std::vector < NTMuon > &muon_out, std::vector < NTElectron > &elec_out,
				       string & CandPairType)
{

  //important: reset the out collections
  muon_out.clear ();
  elec_out.clear ();

  float sum_pT_ee = 0.;
  bool pass_elec = false;
  int ie1 = -1;
  int ie2 = -1;
  if (elec_in.size () >= 2) {
    for (unsigned int i = 0; i < elec_in.size (); i++) {
      for (unsigned int j = i + 1; j < elec_in.size (); j++) {
	if (pass_elec)
	  continue;
	if ((elec_in[i].Charge == elec_in[j].Charge))
        {
	  pass_elec = true;
	  sum_pT_ee = elec_in[i].p4.Pt () + elec_in[j].p4.Pt ();
	  ie1 = i;
	  ie2 = j;
	}
      }
    }
  }

  float sum_pT_mumu = 0.;
  bool pass_muon = false;
  int imu1 = -1;
  int imu2 = -1;
  if (muon_in.size () >= 2) {
    for (unsigned int i = 0; i < muon_in.size (); i++) {
      for (unsigned int j = i + 1; j < muon_in.size (); j++) {
	if (pass_muon)
	  continue;
	if ((muon_in[i].Charge == muon_in[j].Charge))
        {
	  pass_muon = true;
	  sum_pT_mumu = muon_in[i].p4.Pt () + muon_in[j].p4.Pt ();
	  imu1 = i;
	  imu2 = j;
	}
      }
    }
  }


  float sum_pT_emu_start = 0.;
  float sum_pT_emu = 0.;
  int je1 = -1;
  int jmu2 = -1;
  if (muon_in.size () >= 1 && elec_in.size () >= 1) {
    for (unsigned int i = 0; i < muon_in.size (); i++) {
      for (unsigned int j = 0; j < elec_in.size (); j++) {
	if ((muon_in[i].Charge == elec_in[j].Charge))
        {
	  sum_pT_emu = muon_in[i].p4.Pt () + elec_in[j].p4.Pt ();
	  if (sum_pT_emu > sum_pT_emu_start) {
	    sum_pT_emu_start = sum_pT_emu;
	    je1 = j;
	    jmu2 = i;
	  }
	}
      }
    }
  }


  float sum[3] = { sum_pT_ee, sum_pT_mumu, sum_pT_emu };
  int sortedIndices[3];
  TMath::Sort (3, sum, sortedIndices);
  if (sortedIndices[0] == 0 && sum_pT_ee != 0.) {
    elec_out.push_back (elec_in[ie1]);
    elec_out.push_back (elec_in[ie2]);
  }
  else if (sortedIndices[0] == 1 && sum_pT_mumu != 0.) {
    muon_out.push_back (muon_in[imu1]);
    muon_out.push_back (muon_in[imu2]);
  }
  else if (sortedIndices[0] == 2 && sum_pT_emu != 0.) {
    elec_out.push_back (elec_in[je1]);
    muon_out.push_back (muon_in[jmu2]);
  }





  if (elec_out.size () + muon_out.size () == 2) {
    if (muon_out.size () == 2) {
	CandPairType = "mumu";
    }
    if (elec_out.size () == 2) {
      CandPairType = "ee";
    }
    if (muon_out.size () == 1 && elec_out.size () == 1) {
	CandPairType = "emu";
      }
  }
  else CandPairType="false";

  if (CandPairType == "ee" || CandPairType == "emu" || CandPairType == "mumu")
    return true;
  else
    return false;

}



bool SSDiLeptonSelection::GetLeptonPair (std::vector < NTMuon > &muon_out, std::vector < NTElectron > &elec_out, string & CandPairType)
{
  return GetLeptonPair (GetSelectedMuons (), GetSelectedElectrons (), muon_out, elec_out, CandPairType);
}


bool SSDiLeptonSelection::TestIsolationOfPair (float iso1_in, float iso2_in, std::vector < NTMuon > muon_in, std::vector < IPHCTree::NTElectron > elec_in)
{

  bool pass_elec = false;
  if (elec_in.size () == 2) {
    for (unsigned int i = 0; i < elec_in.size (); i++) {
      for (unsigned int j = i + 1; j < elec_in.size (); j++) {
	if (pass_elec)
	  continue;
	if ((elec_in[i].RelIso03PF () < iso1_in && elec_in[j].RelIso03PF () < iso2_in) || (elec_in[i].RelIso03PF () < iso2_in && elec_in[j].RelIso03PF () < iso1_in)) {
	  pass_elec = true;
	}
      }
    }
  }



  bool pass_muon = false;
  if (muon_in.size () == 2) {
    for (unsigned int i = 0; i < muon_in.size (); i++) {
      for (unsigned int j = i + 1; j < muon_in.size (); j++) {
	if (pass_muon)
	  continue;
	if ((muon_in[i].RelIso03PF () < iso1_in && muon_in[j].RelIso03PF () < iso2_in) || (muon_in[i].RelIso03PF () < iso2_in && muon_in[j].RelIso03PF () < iso1_in)) {
	  pass_muon = true;
	}
      }
    }
  }


  bool pass_emu = false;
  if ((muon_in.size () + elec_in.size ()) == 2) {
    for (unsigned int i = 0; i < muon_in.size (); i++) {
      for (unsigned int j = 0; j < elec_in.size (); j++) {
	if (pass_emu)
	  continue;
	if (muon_in[i].RelIso03PF () < iso1_in && elec_in[j].RelIso03PF () < iso2_in) {
	  pass_emu = true;
	}
      }
    }
  }

  if (pass_elec || pass_muon || pass_emu)
    return true;
  else
    return false;

}


TLorentzVector SSDiLeptonSelection::DiLeptonCand (const std::vector < NTMuon > &muons_cand, const std::vector < NTElectron > &electrons_cand)
{
  TLorentzVector DiLepton;
  if (muons_cand.size () + electrons_cand.size () != 2)
    return DiLepton;
  for (unsigned int i = 0; i < muons_cand.size (); i++)
    DiLepton += muons_cand[i].p4;
  for (unsigned int i = 0; i < electrons_cand.size (); i++)
    DiLepton += electrons_cand[i].p4;
  return DiLepton;
}

float SSDiLeptonSelection::DiLeptonMass (const std::vector < NTMuon > &muons_cand, const std::vector < NTElectron > &electrons_cand)
{
  return DiLeptonCand (muons_cand, electrons_cand).M ();
}

float SSDiLeptonSelection::DiLeptonMT (const std::vector < NTMuon > &muons_cand, const std::vector < NTElectron > &electrons_cand)
{
  return DiLeptonCand (muons_cand, electrons_cand).Mt ();
}

bool SSDiLeptonSelection::DiLeptonMassCut (float MinValue, pair < float, float >ZMassWindow, const std::vector < NTMuon > &muons_cand, const std::vector < NTElectron > &electrons_cand,
					 string channelName)
{


  string leptonpairname;
  if (channelName != string ("") && channelName != string ("*") && channelName != string ("allChannels")) {
    leptonpairname = channelName;
  }
  else {
    if (electrons_cand.size () == 2)
      leptonpairname = "ee";
    if (muons_cand.size () == 2)
      leptonpairname = "mumu";
    if (muons_cand.size () == 1 && electrons_cand.size () == 1)
      leptonpairname = "emu";
  }

  bool iresult = true;
  float mass = DiLeptonMass (muons_cand, electrons_cand);

  // reject low DY mass;
  if (mass < MinValue)
    iresult = false;
  // Z veto;
  if (leptonpairname != "emu" && ZMassWindow.first < mass && mass < ZMassWindow.second)
    iresult = false;

  return iresult;

}

bool SSDiLeptonSelection::DiLeptonMassCut (const std::vector < NTMuon > &muons_cand, const std::vector < NTElectron > &electrons_cand, string channelName)
{
  return DiLeptonMassCut (MinMassCut_, ZMassWindow_, muons_cand, electrons_cand, channelName);
}


int SSDiLeptonSelection::doFullSelection (Dataset * dataset, string channelName, bool print, bool applyJES, float JESParam, bool applyEES, float EESParam, bool applyMES, float MESParam, bool applyJER, float JERFactor, bool applyMETS, float METScale)
{
 
  //clear object collections
  jetsAna.clear();
  bjetsAna.clear();
  electronsAna.clear();
  muonsAna.clear();

  bool applyChannel = false;
  if (channelName != string ("") && channelName != string ("*") && channelName != string ("allChannels"))
    applyChannel = true;
  //boolean for the selection step: true = pass the cut
  bool step_trigger = false;
  bool step_pair = false;
  bool step_Zveto = false;
  bool step_jets = false;
  bool step_met = false;
  bool step_bjets = false;

  TString dump;
  ostringstream runNumber_oss;
  ostringstream eventNumber_oss;
  runNumber_oss << runNumber;
  eventNumber_oss << eventNumber;
//  dump = channel_.ChannelName () + string (" | ") + runNumber_oss.str () + string (" | ") + eventNumber_oss.str () + string (" | ");
  //dump+=string("")+runNumberS;  

  //double METEMu = METCuts_.first;
  double METLL = METCuts_.second;
  std::vector < NTMuon > muon_cand;
  std::vector < NTElectron > elec_cand;
  pairType_ = "";
  dimass_=0.;

  int FinalStep = 0;
  //Step 1        MC-match
    FinalStep++;
    //Step 2        Trigger
    if (passTriggerSelection (dataset, channelName)) {
      step_trigger = true;
    //Step 3        Dilepton pair choice
    if ((GetLeptonPair (GetSelectedMuons(applyMES, MESParam), GetSelectedElectrons(applyEES, EESParam), muon_cand, elec_cand, pairType_) == true) 
	&& (!applyChannel || (applyChannel && pairType_ == channelName))) {
      step_pair = true;
      muonsAna = muon_cand;
      electronsAna = elec_cand;

      float lep1PtxCharge = 0;
      float lep2PtxCharge = 0;
      float lep1RelIso = 0;
      float lep2RelIso = 0;
      ostringstream lep1PtxCharge_oss;
      ostringstream lep2PtxCharge_oss;
      ostringstream lep1RelIso_oss;
      ostringstream lep2RelIso_oss;
      if (pairType_ == "mumu") {
	lep1PtxCharge = muon_cand[0].p4.Pt () * muon_cand[0].Charge;
	lep2PtxCharge = muon_cand[1].p4.Pt () * muon_cand[1].Charge;
	lep1RelIso = muon_cand[0].RelIso03PF ();
	lep2RelIso = muon_cand[1].RelIso03PF ();
      }
      if (pairType_ == "ee") {
	lep1PtxCharge = elec_cand[0].p4.Pt () * elec_cand[0].Charge;
	lep2PtxCharge = elec_cand[1].p4.Pt () * elec_cand[1].Charge;
	lep1RelIso = elec_cand[0].RelIso03PF ();
	lep2RelIso = elec_cand[1].RelIso03PF ();
      }
      if (pairType_ == "emu") {
	if (elec_cand[0].p4.Pt () > muon_cand[0].p4.Pt ()) {

	  lep1PtxCharge = elec_cand[0].p4.Pt () * elec_cand[0].Charge;
	  lep2PtxCharge = muon_cand[0].p4.Pt () * muon_cand[0].Charge;
	  lep1RelIso = elec_cand[0].RelIso03PF ();
	  lep2RelIso = muon_cand[0].RelIso03PF ();
	}
	else {
	  lep2PtxCharge = elec_cand[0].p4.Pt () * elec_cand[0].Charge;
	  lep1PtxCharge = muon_cand[0].p4.Pt () * muon_cand[0].Charge;
	  lep2RelIso = elec_cand[0].RelIso03PF ();
	  lep1RelIso = muon_cand[0].RelIso03PF ();
	}
      }
      dimass_ = DiLeptonMass (muon_cand, elec_cand);
      ostringstream dimass_oss;
      dimass_oss << dimass_;
      lep1PtxCharge_oss << lep1PtxCharge;
      lep2PtxCharge_oss << lep2PtxCharge;
      lep1RelIso_oss << lep1RelIso;
      lep2RelIso_oss << lep2RelIso;
      dump += lep1PtxCharge_oss.str () + "," + lep2PtxCharge_oss.str () + " | " + lep1RelIso_oss.str () + "," + lep2RelIso_oss.str () + " | " + dimass_oss.str () + " | ";
      //Step 4     Z mass veto 
      if (DiLeptonMassCut (muon_cand, elec_cand, channelName)) {
	step_Zveto = true;
      }
      //Step 5    Minimal jet multiplicity 
      vector < NTJet > SelectedJets = GetSelectedJets (muon_cand, elec_cand, applyJES, JESParam, applyJER, JERFactor);
      jetsAna = SelectedJets;

      if (SelectedJets.size () >= 2) {
	step_jets = true;
      }
      //Step 6  MET cuts
      if (GetMET (applyJES, JESParam, applyMETS, METScale).p4.Et () < METLL) {
	  step_met = true;
      }
      //Step 7 btagging
      vector < NTJet > btagjets;
      vector < float >btagDiscri;
      ostringstream jet1pt_oss;
      ostringstream jet2pt_oss;
      ostringstream jet1bdisc_oss;
      ostringstream jet2bdisc_oss;
      ostringstream met_oss;
      if(step_jets){
      	jet1pt_oss << SelectedJets[0].p4.Pt ();
      	jet2pt_oss << SelectedJets[1].p4.Pt ();
      	jet1bdisc_oss << SelectedJets[0].TCDiscri;
      	jet2bdisc_oss << SelectedJets[1].TCDiscri;
     	 met_oss << GetMET ().p4.Et ();
      	dump += jet1pt_oss.str () + " , " + jet2pt_oss.str () + " | " + met_oss.str () + " | " + jet1bdisc_oss.str () + " , " + jet2bdisc_oss.str () + " | " + pairType_;
      }

      for (unsigned int j = 0; j < SelectedJets.size (); j++) {
	switch (btagAlgo_) {
	case 0:
	  if (SelectedJets[j].TCDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].TCDiscri);
	  }
	  break;
	case 1:
	  if (SelectedJets[j].SVDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].SVDiscri);
	  }
	  break;
	case 2:
	  if (SelectedJets[j].SMDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].SMDiscri);
	  }
	  break;
	default:
	  cerr << "btagAlgo doesn't exist !" << endl;
	  break;
	}
      }
      bjetsAna = btagjets;
      if ((int) btagjets.size () == NofBtagJets_) {
	//FinalStep++;
	step_bjets = true;
      }
    }
  }

  //Compute a collection of jets and b-jets and a weight even if the selection of pair fails
  if(!step_pair){
      vector < NTJet > SelectedJets = GetSelectedJets (GetSelectedMuons(), GetSelectedElectrons(), applyJES, JESParam);
      jetsAna = SelectedJets;
      vector < NTJet > btagjets;
      vector < float >btagDiscri;
      for (unsigned int j = 0; j < SelectedJets.size (); j++) {
	switch (btagAlgo_) {
	case 0:
	  if (SelectedJets[j].TCDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].TCDiscri);
	  }
	  break;
	case 1:
	  if (SelectedJets[j].SVDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].SVDiscri);
	  }
	  break;
	case 2:
	  if (SelectedJets[j].SMDiscri >= btagDiscriCut_) {
	    btagjets.push_back (SelectedJets[j]);
	    btagDiscri.push_back (SelectedJets[j].SMDiscri);
	  }
	  break;
	default:
	  cerr << "btagAlgo doesn't exist !" << endl;
	  break;
	}
      }
      bjetsAna = btagjets;
  }


  //compute FinalStep
  if (step_trigger) {
    FinalStep++;
    if (step_pair) {
      FinalStep++;
      if (step_Zveto) {
	FinalStep++;
	if (step_jets) {
	  FinalStep++;
	  if (step_met) {
	    FinalStep++;
	    if (step_bjets) {
	      FinalStep++;
	      //the event is selected
	      if (print)
		cout << dump << endl;
	    }
	  }
	}
      }
    }
  }
  selCode_ = step_trigger*maskTriggerCut + step_pair*maskPairCut + 
	step_Zveto * maskZvetoCut + step_jets * maskJetCut + 
	step_met * maskMETCut + step_bjets * maskBjetsCut;

  return FinalStep;
}



int SSDiLeptonSelection::FillTable (SelectionTable & selTable, Dataset * dataset, int idataset, float weight)
{

  int sel = doFullSelection (dataset, selTable.Channel (), false);	// true-> has to be modified !!
  for (unsigned int i = 0; i < cuts_.size () + 1; i++)
    if (sel >= (int) i)
      selTable.Fill (idataset, i, weight);
  return sel;
}




//bool SSDiLeptonSelection::passTriggerSelection(string datasetName, string channelName){
bool SSDiLeptonSelection::passTriggerSelection (Dataset * dataset, string channelName)
{

  //bool match_HLT_Ele10_LW_L1R_recoEl = eleHLTMatch;
//cout << "start TS\n";
  ////cout << eleHLTMatch << endl;
  bool passEl = false;
  bool passMu = false;
  bool passElMu = false;
  int skim = -1;

  string datasetName = dataset->Name ();
//   if (datasetName == "MuData")
//     skim = 0;
//   if (datasetName == "EGData")
//     skim = 1;
// to be compatible with MyCutFlow and others
  if (datasetName.compare(0,6,"DataMu")==0)
    skim = 0;
  if (datasetName.compare(0,6,"DataEG")==0)
    skim = 1;
//  if (datasetName == "DataMuEG" || datasetName == "DataEGMu")
  if ( datasetName.compare(0,8,"DataMuEG")==0 || datasetName.compare(0,8,"DataEGMu")==0 )
    skim = 2;
  
  
  //cout << " datasetName " << datasetName << endl;
  
  
//  if(runNumber == 1){
  if (!dataset->isData ()) {	//MC
    //cout << " test trigger list --------------------------------" << endl;
    for (unsigned int i = 0; i < triggerList.size (); i++) {

   //   cout << "trigger list " << triggerList[i].second << " "<<triggerList[i].first << endl;
// //2010
//       if ((triggerList[i].first == "HLT_Mu9" && triggerList[i].second == true))
// 	passMu = true;
// 
//       if ((triggerList[i].first == "HLT_Ele10_SW_L1R" && triggerList[i].second == true && eleHLTMatch > 15))
// 	passEl = true;
//2011
//      if ((triggerList[i].first == "HLT_DoubleMu5_v1" && triggerList[i].second == true)) // Spring11
      if ((triggerList[i].first == "HLT_DoubleMu6_v1" && triggerList[i].second == true))   //Summer11
	passMu = true;

//      if ((triggerList[i].first == "HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2" && triggerList[i].second ==true )) //Spring11
      if ((triggerList[i].first == "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2" && triggerList[i].second == true )) //Summer11
	passEl = true;

// WARNING : Ces 2 triggers sont corrompus (~ facteur 2 trop faible!!!)
//      if (( (triggerList[i].first == "HLT_Mu8_Ele8_v1" || triggerList[i].first == "HLT_Mu11_Ele8_v1") && triggerList[i].second == true ))
//      if (( ( triggerList[i].first.compare(0,12,"HLT_Mu8_Ele8")==0 || triggerList[i].first.compare(0,13,"HLT_Mu11_Ele8")==0) && triggerList[i].second == true ))
      //if (( (triggerList[i].first == "HLT_Mu5_Ele13_v2" ) && triggerList[i].second == true ))
      //if (( (triggerList[i].first == "HLT_Mu8_Ele8_v1" || triggerList[i].first == "HLT_Mu11_Ele8_v1" ) && triggerList[i].second == true ))

// Spring11
//	if( ((triggerList[i].first == "HLT_Mu5_Ele17_v2" && GetMuons().size()>0 && GetMuons()[0].p4.Pt()>8) || (triggerList[i].first == "HLT_Mu11_Ele8_v1" && GetMuons().size()>0  && GetMuons()[0].p4.Pt()>17)) && triggerList[i].second == true)
// Summer11
	if( ((triggerList[i].first == "HLT_Mu8_Ele17_CaloIdL_v2" ) || (triggerList[i].first == "HLT_Mu10_Ele10_CaloIdL_v3" )) && triggerList[i].second == true)
	passElMu = true;

    }

  }
  else {
    // DATA --> Taken from TopDileptonRefAnalysis2010Pass6
    // WARNING : COULD SOMEONE CHECK THE < AND <= FOR THE RUN NUMBER????

    for (unsigned int i = 0; i < triggerList.size (); i++) {
// //2010
      // Muon
//       if (runNumber < 145000 && triggerList[i].first == "HLT_Mu9" && triggerList[i].second == true)
// 	passMu = true;
//       else if (  145000 < runNumber  && runNumber < 147120 && triggerList[i].first == "HLT_Mu11" && triggerList[i].second == true)
// 	passMu = true;
//       else if ( 147120 < runNumber  && triggerList[i].first == "HLT_Mu15_v1" && triggerList[i].second == true)
// 	passMu = true;
//       // Electron
//       if (runNumber < 138000 && triggerList[i].first == "HLT_Ele10_LW_L1R" && triggerList[i].second == true && eleHLTMatch > 15)
// 	passEl = true;
//       else if ( 138000 <= runNumber && runNumber < 141900 && triggerList[i].first == "HLT_Ele15_LW_L1R" && triggerList[i].second == true)
// 	passEl = true;
//       else if ( 141900 <= runNumber && runNumber < 144000 && triggerList[i].first == "HLT_Ele15_SW_L1R" && triggerList[i].second == true)
// 	passEl = true;
//       else if (144000 < runNumber && runNumber <= 144114 && ((triggerList[i].first == "HLT_Ele15_SW_CaloEleId_L1R" && triggerList[i].second == true)
// 							     || (triggerList[i].first == "HLT_Ele20_SW_L1R" && triggerList[i].second == true)
// 							     || (triggerList[i].first == "HLT_DoubleEle10_SW_L1R" && triggerList[i].second == true)))
// 	passEl = true;
//       else if (146000 < runNumber && runNumber < 147120 && ((triggerList[i].first == "HLT_DoubleEle10_SW_L1R" && triggerList[i].second == true)
// 							    || (triggerList[i].first == "HLT_Ele17_SW_CaloEleId_L1R" && triggerList[i].second == true)))
// 	passEl = true;
//       else if (147120 < runNumber && runNumber < 148100 && ((triggerList[i].first == "HLT_DoubleEle15_SW_L1R_v1" && triggerList[i].second == true)
// 							    || (triggerList[i].first == "HLT_Ele17_SW_TightCaloEleId_SC8HE_L1R_v1" && triggerList[i].second == true)
// 							    || (triggerList[i].first == "HLT_Ele17_SW_TightEleId_L1R" && triggerList[i].second == true)))
// 	passEl = true;
//       else if (148100 < runNumber && ((triggerList[i].first == "HLT_DoubleEle17_SW_L1R_v1" && triggerList[i].second == true)
// 				      || ((triggerList[i].first == "HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v2" && triggerList[i].second == true)
// 					  || (triggerList[i].first == "HLT_Ele17_SW_TightCaloEleId_Ele8HE_L1R_v1" && triggerList[i].second == true))
// 				      || ((triggerList[i].first == "HLT_Ele22_SW_TighterEleId_L1R_v3" && triggerList[i].second == true)
// 					  || (triggerList[i].first == "HLT_Ele22_SW_TighterEleId_L1R_v2" && triggerList[i].second == true))
// 				      || ((triggerList[i].first == "HLT_Ele17_SW_TighterEleIdIsol_L1R_v3" && triggerList[i].second == true)
// 					  || (triggerList[i].first == "HLT_Ele17_SW_TighterEleIdIsol_L1R_v2" && triggerList[i].second == true))))
// 	passEl = true;


      //if(triggerList[i].first.find("DoubleMu")!=string::npos)  
      //cout << "trigger list " <<triggerList[i].first<<"   "<< triggerList[i].second << endl;

/* T. Speer

      if ( 160329 <= runNumber && runNumber < 163262 && 
	( triggerList[i].first.compare(0,13,"HLT_DoubleMu6")==0  && triggerList[i].second == true)  )
	passMu = true;
      else if ( 160329 <= runNumber && runNumber < 164237 && 
	( triggerList[i].first.compare(0,13,"HLT_DoubleMu7")==0  && triggerList[i].second == true)  )
	passMu = true;
      else if ( 165088 <= runNumber && 
	( triggerList[i].first.compare(0,13,"HLT_DoubleMu8")==0  && triggerList[i].second == true)  )
	passMu = true;

      if (( triggerList[i].first.compare(0,50,"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL")==0  && triggerList[i].second == true)  )
//      if ((triggerList[i].first == "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1" && triggerList[i].second == true))
	passEl = true;

      if (160329 <= runNumber && runNumber < 164237 && 
	(  triggerList[i].first.compare(0,22,"HLT_Mu10_Ele10_CaloIdL")==0  && triggerList[i].second == true))
//      if ((triggerList[i].first == "HLT_Mu10_Ele10_CaloIdL_v2" && triggerList[i].second == true))
	passElMu = true;
      if (160329 <= runNumber  &&
	( ( triggerList[i].first.compare(0,21,"HLT_Mu17_Ele8_CaloIdL")==0  && triggerList[i].second == true)
	  || ( triggerList[i].first.compare(0,21,"HLT_Mu8_Ele17_CaloIdL")==0  && triggerList[i].second == true) ) )
//      if ((triggerList[i].first == "HLT_Mu10_Ele10_CaloIdL_v2" && triggerList[i].second == true))
	passElMu = true;
*/

// Caro for the top dilepton x-sect, same as for H->WW
      if ( 160329 <= runNumber && runNumber < 164237 && 
        ( triggerList[i].first.compare(0,13,"HLT_DoubleMu7")==0  && triggerList[i].second == true)  )
        passMu = true;
      else if ( 165085 <= runNumber && 
        ( triggerList[i].first.compare(0,14,"HLT_Mu13_Mu8_v")==0  && triggerList[i].second == true)  )
        passMu = true;

      if (( triggerList[i].first.compare(0,50,"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL")==0  && triggerList[i].second == true)  )
        passEl = true;

      if (160329 <= runNumber  &&
        ( ( triggerList[i].first.compare(0,21,"HLT_Mu17_Ele8_CaloIdL")==0  && triggerList[i].second == true)
          || ( triggerList[i].first.compare(0,21,"HLT_Mu8_Ele17_CaloIdL")==0  && triggerList[i].second == true) ) )
        passElMu = true;
	
    }
  }

  if (channelName == string ("ee")) {
    if (passEl)
      return true;
    else
      return false;
  }
  if (channelName == string ("mumu")) {
    if (passMu)
      return true;
    else
      return false;
  }
  if (channelName == string ("emu")) {
     bool thereturn = false;
//     if (  (passEl && skim==1 ) || ( passMu && skim==0 && !passEl ) ) thereturn = true;
//     if ( skim == -1 && (passEl  || passMu ) ) thereturn = true;
    if ( skim == -1 &&  passElMu) return true;
    if ( skim == 2 && (passElMu) )
      thereturn = true;
    return thereturn;
  }
  if (channelName == string ("") || channelName == string ("*") || channelName == string ("allChannels")) {
    if (passEl || passMu)
      return true;
    return false;
  }

  return false;

}




float SSDiLeptonSelection::GetMinValueMassCut ()
{
  return MinMassCut_;
}

pair < float, float >SSDiLeptonSelection::GetMETCut ()
{
  return METCuts_;
}

pair < float, float >SSDiLeptonSelection::GetZmassWindowCut ()
{
  return ZMassWindow_;
}

     int SSDiLeptonSelection::GetbtagAlgo () const
     {
       return btagAlgo_;
     }

     float SSDiLeptonSelection::GetbtagDiscriCut () const
     {
       return btagDiscriCut_;
     }

     int SSDiLeptonSelection::GetNofBtagJetsCut () const
     {
       return NofBtagJets_;
     }


bool SSDiLeptonSelection::passBtagSelection(const NTJet & jet) const
{
  return (getBtagDiscr(jet) >= btagDiscriCut_);
}

double SSDiLeptonSelection::getBtagDiscr(const NTJet & jet) const
{
  switch (btagAlgo_) {
  case 0:
    return jet.TCDiscri;
    break;
  case 1:
    return jet.SVDiscri;
    break;
  case 2:
    return jet.SMDiscri;
    break;
  default:
    cerr << "btagAlgo doesn't exist !" << endl;
    return -10000000;
  }
}



double SSDiLeptonSelection::getLeptonScaleFactor(double pt1, double eta1, double pt2, double eta2, string channel){
  double the_getScaleFactor = 0;
  
  if(pt1 > 100) pt1 = 99;
  if(fabs(eta1) > 2.5) eta1 = 2.4;
  
  if(pt2 > 100) pt2 = 99;
  if(fabs(eta2) > 2.5) eta2 = 2.4;
  if(channel == "ee"){
     int binx1 = getScaleFactEl()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta1) );
     
     int binx2 = getScaleFactEl()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactEl()->GetBinContent( binx1, biny1 )*getScaleFactEl()->GetBinContent( binx2, biny2 );

  }
  
  if(channel == "mumu"){
     int binx1 = getScaleFactMu()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta1) );
     int binx2 = getScaleFactMu()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactMu()->GetBinContent( binx1, biny1 )*getScaleFactMu()->GetBinContent( binx2, biny2 );
  }

  if(channel == "emu"){
  
     int binx1 = getScaleFactEl()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta1) );
     
     int binx2 = getScaleFactMu()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactEl()->GetBinContent( binx1, biny1 )*getScaleFactMu()->GetBinContent( binx2, biny2 );
  }
  
  
  return the_getScaleFactor;
}





double SSDiLeptonSelection::getLeptonScaleFactorError(double pt1, double eta1, double pt2, double eta2, string channel){
  double the_getScaleFactor = 0;
  
  if(pt1 > 100) pt1 = 99;
  if(fabs(eta1) > 2.5) eta1 = 2.4;
  
  if(pt2 > 100) pt2 = 99;
  if(fabs(eta2) > 2.5) eta2 = 2.4;
  
  if(channel == "ee"){
     int binx1 = getScaleFactEl()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta1) );
     
     int binx2 = getScaleFactEl()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactEl()->GetBinError( binx1, biny1 )*getScaleFactEl()->GetBinContent( binx2, biny2 );

  }
  
  if(channel == "mumu"){
  
     int binx1 = getScaleFactMu()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta1) );
     
     int binx2 = getScaleFactMu()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactMu()->GetBinError( binx1, biny1 )*getScaleFactMu()->GetBinContent( binx2, biny2 );
  }

  if(channel == "emu"){
  
     int binx1 = getScaleFactEl()->GetXaxis()->FindBin( pt1 );
     int biny1 = getScaleFactEl()->GetYaxis()->FindBin( fabs(eta1) );
     
     int binx2 = getScaleFactMu()->GetXaxis()->FindBin( pt2 );
     int biny2 = getScaleFactMu()->GetYaxis()->FindBin( fabs(eta2) );
     
     the_getScaleFactor = getScaleFactEl()->GetBinError( binx1, biny1 )*getScaleFactMu()->GetBinContent( binx2, biny2 );
  }
  
  
  return the_getScaleFactor;
}













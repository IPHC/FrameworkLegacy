#ifndef SSDiLeptonSelection_h
#define SSDiLeptonSelection_h

#include "Selection.h"
#include "SelectionTable.h"
//#include "DiLeptonChannel.h"
#include "SSDiLeptonSelection.h"
#include "../../Tools/interface/Dataset.h"


// system include files
#include <memory>
#include <vector>
#include <sstream>


using namespace std;
using namespace IPHCTree;

/**
	Steps of the selection: (integer returned by doFullSelection() or FillTable(...))
	- Step 1        MC-match
	- Step 2        Trigger
	- Step 3  	Dilepton pair choice
	- Step 4 	Z mass veto 
	- Step 5 	Minimal jet multiplicity 
	- Step 6 	MET cuts
	- Step 7 	btagging cuts

*/

class SSDiLeptonSelection: public Selection{


   public:
      SSDiLeptonSelection();
      SSDiLeptonSelection(const SSDiLeptonSelection &);
      ~SSDiLeptonSelection();

      void SetParameters(float MinValue, pair<float,float> METCuts, pair<float,float> ZMassWindow, int btagAlgo, float btagDiscriCut, int NofBtagJets);
      vector<string> GetCutList() const {return cuts_;};
      vector<string> GetChannelList(){return channels_;};
      int GetChannel(string& CandPairType);

      void LoadEvent(const NTEvent*event);

      //Getter which return the objects which pass the selection once the doFullSelection methods has been called. Collection are rewritten each time that the doFullSelection method is called
      std::vector<NTJet> GetJetsForAna() const{return jetsAna;};
      std::vector<NTJet> GetBJetsForAna() const{return bjetsAna;};
      std::vector<NTElectron> GetElectronsForAna() const { return electronsAna;};
      std::vector<NTMuon> GetMuonsForAna() const {return muonsAna;};

      bool GetLeptonPair(std::vector<NTMuon> muon_in,std::vector<IPHCTree::NTElectron> elec_in, std::vector<NTMuon>& muon_out,std::vector<NTElectron>& elec_out,  string& CandPairType);
      /** muon_out & elec_out will be filled with the 2 di-leptons candidates \n Returns true if a lepton pair is found \n
      	  CandPairType = "ee" or "emu" or "mumu" or "false"
	*/
      bool GetLeptonPair(std::vector<NTMuon>& muon_out,std::vector<NTElectron>& elec_out,  string& CandPairType); /** Idem with default GetSelected Electrons & Muons as input*/


      int FillTable(SelectionTable& selTable, Dataset* dataset, int idataset, float weight); /** Fill the selectionTable according to the result of doFullSelection  for an 
event of weight "weight" of a given dataset idataset - Returns the integer of doFullSelection() */


     bool TestIsolationOfPair(float iso1_in , float iso2_in, std::vector<NTMuon> muon_in,std::vector<IPHCTree::NTElectron> elec_in); /** It allows to test the isolation of the pair of leptons selected by GetLeptonPairForMM (or by GetLeptonPair).*/


      float DiLeptonMass(const std::vector<NTMuon>& muons_cand, const std::vector<NTElectron>& electrons_cand); /** Return the mass of the di-lepton candidate */
      float DiLeptonMT(const std::vector<NTMuon>& muons_cand, const std::vector<NTElectron>& electrons_cand); /** Return MT of the di-lepton candidate */
      TLorentzVector DiLeptonCand(const std::vector<NTMuon>& muons_cand, const std::vector<NTElectron>& electrons_cand); /** Return the p4 of the di-lepton candidate */
      bool DiLeptonMassCut(float MinValue, pair<float,float> ZMassWindow, const std::vector<NTMuon>& muons_cand, const std::vector<NTElectron>& electrons_cand,string channelName); /** Return true if dilepton candidate passes the  mass cuts */
      bool DiLeptonMassCut(const std::vector<NTMuon>& muons_cand, const std::vector<NTElectron>& electrons_cand, string channelName); /** Idem with defaults mass cuts */

    /**
     * return a integer which correspond to the last step that the event passes in the selection 
     * - possibility to check if the candPair correspond to the correct channel 
     *  & to cut at gen level for a given channel 
     * -  compute also the weight associated to btag
     */

      int doFullSelection(Dataset* dataset, string channelName=string(""), bool print = false, bool applyJES = false, float JESParam = 1., bool applyEES = false, float EESParam = 1., bool applyMES = false, float MESParam = 1., bool applyJER = false, float JERFactor = 0., bool applyMETS = false, float METScale = 1.);


      bool passTriggerSelection(Dataset* dataset, string channelName = string(""));
     
     float GetMinValueMassCut();
     pair<float,float> GetMETCut();
     pair<float,float> GetZmassWindowCut();
     int GetbtagAlgo() const;
     float GetbtagDiscriCut() const;
     int GetNofBtagJetsCut() const; 


       /**
	* Returns the 32-bit selection cote. It is only filled during the doFullSelection method.
	* Each bit (from the LSB) represents the
	* outcome of a particular filter step. It can be probed with the masks,
	* e.g. GetSelCode()&SSDiLeptonSelection::maskZvetoCut tells whether the Z-veto cut 
	* was successful.
	*/
      int GetSelCode() const {return selCode_;};

      static const int maskTriggerCut = 0x1;
      static const int maskPairCut = 0x2;
      static const int maskZvetoCut = 0x4;
      static const int maskJetCut = 0x8;
      static const int maskMETCut = 0x10;
      static const int maskBjetsCut = 0x20;

      /**
       * Dilepton type. It is only filled during the doFullSelection method.
       */
      string pairType() const {return pairType_;}

      /** Invariant mass of the two leptons.
       *  It is only filled during the doFullSelection method.
       */
      float dileptonMass() const {return dimass_;}

      /**
       * Tells whether a particular jet passes the b-tagging requirement
       */
      bool passBtagSelection(const NTJet & jet) const;

      /**
       *  Returns the b-tagging discriminant of a particular jet according to
       *  the algorithm specified in the config file.
       */

      double getBtagDiscr(const NTJet & jet) const;
      
      
      double getLeptonScaleFactor(double pt1, double eta1, double pt2, double eta2, string channel);
      double getLeptonScaleFactorError(double pt1, double eta1, double pt2, double eta2, string channel);

    private:
//      DiLeptonChannel channel_;
      float MinMassCut_;
      pair<float,float> ZMassWindow_;
      pair<float,float> METCuts_;
      vector<string> cuts_;
      vector<string> channels_;
      int btagAlgo_;
      float btagDiscriCut_;
      int NofBtagJets_;

      string pairType_;

      /** invariant mass of the two leptons*/
      float dimass_;// 

      /** 32-bit outcome of the full selection */
      int selCode_;

      //Objects for ana
      std::vector<NTElectron> electronsAna;
      std::vector<NTMuon> muonsAna;
      std::vector<NTJet> jetsAna;
      std::vector<NTJet> bjetsAna;

};

#endif

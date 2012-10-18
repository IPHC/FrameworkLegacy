#ifndef __MiniTreeProducer_H__
#define __MiniTreeProducer_H__

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/MuonReco/interface/MuonMETCorrectionData.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include <SimDataFormats/GeneratorProducts/interface/PdfInfo.h>
#include <SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h>
#include <RecoEgamma/EgammaTools/interface/ConversionFinder.h>
 
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"

//For electron-conversion
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/Scalers/interface/DcsStatus.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

// Add System header
#include <ctime>


typedef math::XYZPoint Point;


#define ERROR(title)   edm::LogError(title) << "[" << __FILE__ <<", line=" << __LINE__ <<"] "
#define WARNING(title) edm::LogWarning(title) << "[" << __FILE__ <<", line=" << __LINE__ <<"] "


// -*- C++ -*-
//
// Package:    MiniTreeProducer
// Class:      MiniTreeProducer
// 
/**\class MiniTreeProducer MiniTreeProducer.cc TMP/MiniTreeProducer/src/MiniTreeProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jeremy ANDREA
//         Created:  Sun Nov  1 21:30:20 CET 2009
// $Id: MiniTreeProducer.h,v 1.4 2012/02/16 14:47:20 econte Exp $
//
//

//----------------- system include files
#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

//----------------- cmssw includes

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include <FWCore/Framework/interface/Run.h>

#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"
#include "FWCore/ServiceRegistry/interface/Service.h" 

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "JetMETCorrections/JetVertexAssociation/interface/JetVertexMain.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"


#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"



//--------------------PAT includes
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HepMCCandidate/interface/PdfInfo.h"
#include "MiniTree/MiniTreeProducer/interface/ConfigType.h" 

//--------------------ROOT includes
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TRandom.h"

//--------------------CLASS includes
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"

#include "IPHCDataFormat/MTFormat/interface/MTEvent.h"
//#include "erictest/DataFormat/NTFormat/interface/NTSampleInfo.h"


//using namespace std;
//using namespace edm;
//using namespace reco;

//MiniTree classes
/*typedef TopTree::MTEvent        TopTreeEvent;
typedef TopTree::MTJet 	        TopTreeJet;
typedef TopTree::MTMET 	        TopTreeMET;
typedef TopTree::MTJetMet       TopTreeJetMet;
typedef TopTree::MTElectron     TopTreeElectron;
typedef TopTree::MTPhoton       TopTreePhoton;
typedef TopTree::MTMuon         TopTreeMuon;
typedef TopTree::MTTau          TopTreeTau;
typedef TopTree::MTTrack	TopTreeTrack;
typedef TopTree::MTVertex       TopTreePVx;
typedef TopTree::MTVertex       TopTreeBS;

typedef TopTree::NTSampleInfo   TopTreeSampleInfo;*/



// LHAPDF stuff
extern "C" {
  void initpdfset_ (char *, int len);
  void initpdfsetm_(int &, char *);
  void initpdf_(int &);
  void evolvepdf_(double &, double &, double *);
  void numberpdf_(int &);
}
  
//class pat::TriggerEvent;


class MiniTreeProducer : public edm::EDProducer
{
 public:
  explicit MiniTreeProducer(const edm::ParameterSet&);
  ~MiniTreeProducer();
  
  
 private:
  virtual void 	beginJob() ;
  virtual void 	produce(edm::Event&, const edm::EventSetup&);
  virtual void 	endJob() ;
  /*  bool         	MyJetCleaner(const vector<pat::Electron>*, pat::Jet);
  void         	EventInfo();  
  int 		getMuonOrigin(edm::Handle<reco::GenParticleCollection> , const pat::Muon * , reco::GenParticle&, reco::GenParticle&, reco::GenParticle&);
  int 		getElectronOrigin(edm::Handle<reco::GenParticleCollection> particles, const pat::Electron * thePatElec,reco::GenParticle&, reco::GenParticle&, reco::GenParticle&);
  int           getTauDecay(edm::Handle<reco::GenParticleCollection> particles, const pat::Tau * thePatTau);
  void 		setGenParticleFromCandidate(reco::GenParticle&, const reco::Candidate *);
  */  



  // ----------member data ---------------------------

  ConfigType cfg;
  std::clock_t StartTime;
  std::clock_t EndTime;

 


  JetVertexMain* vertexAlgo;
  std::string	cftbjetstring;
 
  void fillGeneralInfo(edm::Event& iEvent, 
                       const edm::EventSetup& iSetup,
                       std::auto_ptr<IPHCTree::MTEvent>& evt);

  void fillTriggerInfo(edm::Event& iEvent, 
                       const edm::EventSetup& iSetup,
                       std::auto_ptr<IPHCTree::MTEvent>& evt,
											 const pat::TriggerEvent* triggerEvent);

  void fillVertices(edm::Event& iEvent, 
                    const edm::EventSetup& iSetup,
                    std::auto_ptr<IPHCTree::MTEvent>& evt,
                    const std::vector<reco::Vertex>* vertices,
                    const reco::Vertex* & vp);
  void fillTracks(edm::Event& iEvent, 
                  const edm::EventSetup& iSetup,
                  std::auto_ptr<IPHCTree::MTEvent>& evt,
  	           		const std::vector<reco::Track>* tracks,
                  const reco::BeamSpot* & bs);
  void fillPhotons(edm::Event& iEvent, 
                   const edm::EventSetup& iSetup,
                   std::auto_ptr<IPHCTree::MTEvent>& evt,
                   const edm::Handle<std::vector<pat::Photon> >& gammas,
                   const pat::TriggerEvent* patTriggerEvent);
  void fillMuons(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
  	           	 const edm::Handle< std::vector<pat::Muon> >& muons,
                 const TransientTrackBuilder* trackBuilder,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const reco::Vertex* & vp,
                 const pat::TriggerEvent* patTriggerEvent);
  void fillElectrons(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const edm::Handle< std::vector<pat::Electron> >& electrons,
                 const TransientTrackBuilder* trackBuilder,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const reco::Vertex* & vp,
                 const float& bField,
                 const edm::Handle<std::vector<reco::Track> >& tracks,
                 const pat::TriggerEvent* patTriggerEvent);

  void fillTaus(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 const edm::Handle<std::vector<pat::Tau> >& taus,
                 const reco::GenParticleCollection* genParticles,
                 const reco::BeamSpot* & bs,
                 const pat::TriggerEvent* patTriggerEvent);
  std::pair<float,float> fillMuonMET(
      const edm::Handle<edm::ValueMap<reco::MuonMETCorrectionData> >& muMET, 
      const edm::Handle<std::vector<reco::Muon> >& muons );
  void fillJetMET(edm::Event& iEvent, 
                  const edm::EventSetup& iSetup,
                  std::auto_ptr<IPHCTree::MTEvent>& evt,
                  const pat::MET*    met,
                  const reco::PFMET* pfmet1,
                  const reco::PFMET* pfmet2,
                  const edm::Handle<std::vector<pat::Jet> >& jets,
                  const std::string& algo,
                  const std::pair<float,float>& SumMuMetCorr,
                  const pat::TriggerEvent* patTriggerEvent);
void fillGenEventInfo(edm::Event& iEvent, 
                      const edm::EventSetup& iSetup,
                      std::auto_ptr<IPHCTree::MTEvent>& evt,
                      const edm::Handle<GenEventInfoProduct>& genEventInfo);

 void fillPileUp(edm::Event& iEvent, 
                 const edm::EventSetup& iSetup,
                 std::auto_ptr<IPHCTree::MTEvent>& evt,
                 edm::Handle<double>& h_rho,
                 edm::Handle<double>& h_neutralRho,
                 edm::Handle<std::vector<PileupSummaryInfo> >& PupInfo);

void fillGenParticles(edm::Event& iEvent, 
                      const edm::EventSetup& iSetup,
                      std::auto_ptr<IPHCTree::MTEvent>& evt,
                      const edm::Handle<std::vector<reco::GenParticle> >& GenParticles);



  bool getBfieldFromDCS(edm::Event& iEvent, const edm::EventSetup& iSetup, float& evt_bField);
  bool getBfieldFromIDEAL(edm::Event& iEvent, const edm::EventSetup& iSetup, float& evt_bField);
  

};

#endif

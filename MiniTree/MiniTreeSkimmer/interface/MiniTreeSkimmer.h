// -*- C++ -*-
//
// Package:    MiniTreeSkimmer
// Class:      MiniTreeSkimmer
// 
/**\class MiniTreeSkimmer MiniTreeSkimmer.cc MiniTree/MiniTreeSkimmer/src/MiniTreeSkimmer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Aubin Alexandre
//         Created:  Wed Apr 17 18:39:03 CEST 2013
// $Id$
//
//

#ifndef __MiniTreeSkimmer_H__
#define __MiniTreeSkimmer_H__


#include <iostream>
#include <vector>
#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

#include "MiniTree/MiniTreeSkimmer/interface/ConfigSkimming.h" 

using namespace std;


class MiniTreeSkimmer : public edm::EDFilter 
{

   public:

      explicit MiniTreeSkimmer(const edm::ParameterSet&);
      ~MiniTreeSkimmer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
  
      unsigned int nEventsInit;
      unsigned int nEventsDrop;
      unsigned int nEventsKept;
      
      unsigned nEventsProcessedInLumi;
      
      ConfigSkimming cfg;

      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      bool dropEvent(edm::Event& iEvent);
      bool keepEvent(edm::Event& iEvent);

      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

};

#endif

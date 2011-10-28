#include "MiniTree/MiniTreeProducer/interface/MonteCarloOrigin.h"

/*

void MiniTreeProducer::setGenParticleFromCandidate (reco::GenParticle & genp, const reco::Candidate * recoc)
{
  genp.setCharge (recoc->charge ());
  genp.setP4 (recoc->p4 ());
  genp.setMass (recoc->mass ());
  genp.setPdgId (recoc->pdgId ());
  genp.setStatus (recoc->status ());
  genp.setVertex (recoc->vertex ());
}


int
  MiniTreeProducer::getMuonOrigin (edm::Handle < reco::GenParticleCollection > genParticles, const pat::Muon * thePatMuon,
				   reco::GenParticle & MotherGenMuon, reco::GenParticle & GrandMotherGenMuon, reco::GenParticle & GGrandMotherGenMuon)
{

  int muonOrigin = -99;
  const reco::Candidate * theGenMuon;
  reco::GenParticle test;
  bool matchedGenLepton = false;

  for (reco::GenParticleCollection::const_iterator p = genParticles->begin (); p != genParticles->end (); ++p) {
    const reco::Candidate * aGenMuon = (dynamic_cast < reco::Candidate * >(const_cast < reco::GenParticle * >(&*p)));

    if (abs (p->pdgId ()) == 13 && p->status () == 1) {
      if ((thePatMuon->genLepton () != NULL) && abs (thePatMuon->genLepton ()->pt () - aGenMuon->pt ()) < 0.00001) {
	theGenMuon = aGenMuon;
	matchedGenLepton = true;
      }
    }
  }

  if (matchedGenLepton) {
    muonOrigin = 0;
    bool isFromBDecay = false;
    bool isFromCDecay = false;
    if (theGenMuon->mother () != 0 && abs (theGenMuon->pdgId ()) == 13) {
      const reco::Candidate * aMotherGenMuon1 = theGenMuon->mother ();
      const reco::Candidate * aMotherGenMuon2 = theGenMuon->mother ();
      setGenParticleFromCandidate (MotherGenMuon, theGenMuon->mother ());
      //                        MotherGenMuon = *theGenMuon->mother();
      int gm = 0;
      while (aMotherGenMuon2->mother () != 0) {
	gm++;
	aMotherGenMuon2 = aMotherGenMuon2->mother ();
	if (abs (aMotherGenMuon2->pdgId ()) == 24 && abs (aMotherGenMuon1->pdgId ()) == 13)
	  muonOrigin = muonOrigin + 1;	// muon from W
	if (abs (aMotherGenMuon2->pdgId ()) == 24 && abs (aMotherGenMuon1->pdgId ()) == 15)
	  muonOrigin = muonOrigin + 1;	// muon from W->tau
	if (abs (aMotherGenMuon2->pdgId ()) == 23 && abs (aMotherGenMuon1->pdgId ()) == 13)
	  muonOrigin = muonOrigin + 10;
	if (abs (aMotherGenMuon1->pdgId ()) == 4 || (abs (aMotherGenMuon1->pdgId ()) > 39 && abs (aMotherGenMuon1->pdgId ()) < 50)
	    || (abs (aMotherGenMuon1->pdgId ()) > 390 && abs (aMotherGenMuon1->pdgId ()) < 500) || (abs (aMotherGenMuon1->pdgId ()) > 3900 && abs (aMotherGenMuon1->pdgId ()) < 5000))
	  isFromCDecay = true;
	if (abs (aMotherGenMuon1->pdgId ()) == 5 || (abs (aMotherGenMuon1->pdgId ()) > 49 && abs (aMotherGenMuon1->pdgId ()) < 60)
	    || (abs (aMotherGenMuon1->pdgId ()) > 490 && abs (aMotherGenMuon1->pdgId ()) < 600) || (abs (aMotherGenMuon1->pdgId ()) > 4900 && abs (aMotherGenMuon1->pdgId ()) < 6000))
	  isFromBDecay = true;
	//                              if (gm==1) GrandMotherGenMuon = *aMotherGenMuon2;
	//                              if (gm==2) GGrandMotherGenMuon = *aMotherGenMuon2;
	if (gm == 1)
	  setGenParticleFromCandidate (GrandMotherGenMuon, aMotherGenMuon2);
	if (gm == 2)
	  setGenParticleFromCandidate (GGrandMotherGenMuon, aMotherGenMuon2);
      }
      aMotherGenMuon1 = aMotherGenMuon2;
    }
    if (isFromCDecay)
      muonOrigin = muonOrigin + 1000;
    if (isFromBDecay)
      muonOrigin = muonOrigin + 100;
  }
  return muonOrigin;		//REMARK : cbZW format!
}

int
  MiniTreeProducer::getElectronOrigin (edm::Handle < reco::GenParticleCollection > genParticles, const pat::Electron * thePatElectron, reco::GenParticle & MotherGenElectron,
				       reco::GenParticle & GrandMotherGenElectron, reco::GenParticle & GGrandMotherGenElectron)
{

  int electronOrigin = -99;
  reco::Candidate * theGenElectron;
  bool matchedGenLepton = false;

  for (reco::GenParticleCollection::const_iterator p = genParticles->begin (); p != genParticles->end (); ++p) {
    reco::Candidate * aGenElectron = (dynamic_cast < reco::Candidate * >(const_cast < reco::GenParticle * >(&*p)));

    if (abs (p->pdgId ()) == 11 && p->status () == 1) {
      if ((thePatElectron->genLepton () != NULL) && abs (thePatElectron->genLepton ()->pt () - aGenElectron->pt ()) < 0.00001) {
	theGenElectron = aGenElectron;
	matchedGenLepton = true;
      }
    }
  }

  if (matchedGenLepton) {
    electronOrigin = 0;
    bool isFromBDecay = false;
    bool isFromCDecay = false;
    if (theGenElectron->mother () != 0 && abs (theGenElectron->pdgId ()) == 11) {
      const reco::Candidate * aMotherGenElectron1 = theGenElectron->mother ();
      const reco::Candidate * aMotherGenElectron2 = theGenElectron->mother ();
      setGenParticleFromCandidate (MotherGenElectron, theGenElectron->mother ());
      //                        MotherGenElectron = *theGenElectron->mother();
      int gm = 0;
      while (aMotherGenElectron2->mother () != 0) {
	gm++;
	aMotherGenElectron2 = aMotherGenElectron2->mother ();
	if (abs (aMotherGenElectron2->pdgId ()) == 24 && abs (aMotherGenElectron1->pdgId ()) == 11)
	  electronOrigin = electronOrigin + 1;
	if (abs (aMotherGenElectron2->pdgId ()) == 24 && abs (aMotherGenElectron1->pdgId ()) == 15)
	  electronOrigin = electronOrigin + 1;
	if (abs (aMotherGenElectron2->pdgId ()) == 23 && abs (aMotherGenElectron1->pdgId ()) == 11)
	  electronOrigin = electronOrigin + 10;
	if (abs (aMotherGenElectron1->pdgId ()) == 4 || (abs (aMotherGenElectron1->pdgId ()) > 39 && abs (aMotherGenElectron1->pdgId ()) < 50)
	    || (abs (aMotherGenElectron1->pdgId ()) > 390 && abs (aMotherGenElectron1->pdgId ()) < 500) || (abs (aMotherGenElectron1->pdgId ()) > 3900 && abs (aMotherGenElectron1->pdgId ()) < 5000))
	  isFromCDecay = true;
	if (abs (aMotherGenElectron1->pdgId ()) == 5 || (abs (aMotherGenElectron1->pdgId ()) > 49 && abs (aMotherGenElectron1->pdgId ()) < 60)
	    || (abs (aMotherGenElectron1->pdgId ()) > 490 && abs (aMotherGenElectron1->pdgId ()) < 600) || (abs (aMotherGenElectron1->pdgId ()) > 4900 && abs (aMotherGenElectron1->pdgId ()) < 6000))
	  isFromBDecay = true;
	//                              if (gm==1) GrandMotherGenElectron = *aMotherGenElectron2;
	//                              if (gm==2) GGrandMotherGenElectron = *aMotherGenElectron2;
	if (gm == 1)
	  setGenParticleFromCandidate (GrandMotherGenElectron, aMotherGenElectron2);
	if (gm == 2)
	  setGenParticleFromCandidate (GGrandMotherGenElectron, aMotherGenElectron2);
      }
      aMotherGenElectron1 = aMotherGenElectron2;
    }

    if (isFromCDecay)
      electronOrigin = electronOrigin + 1000;
    if (isFromBDecay)
      electronOrigin = electronOrigin + 100;
  }
  return electronOrigin;
}

int 
  MiniTreeProducer::getTauDecay(edm::Handle<reco::GenParticleCollection> genParticles, 
                                const pat::Tau *thePatTau)
{
  
  int tauDecay = -999;
  bool matchedGenLepton = false;
  reco::GenParticleCollection::const_iterator pMatched; 
    
  for (reco::GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p){
    reco::Candidate * aGenTau = (dynamic_cast<reco::Candidate *>(const_cast<reco::GenParticle *>(&*p)));
   
  
    if (abs(p->pdgId()) == 15 && p->status() == 2){
#if DEBUG
      cout << "getTauOrigin: thePatElectron->genLepton() " << thePatTau->genLepton() <<endl;
#endif
      if ((thePatTau->genLepton() != NULL) && abs(thePatTau->genLepton()->pt()-aGenTau->pt()) < 0.00001){
        matchedGenLepton = true;
	pMatched = p;
      }
    }
  } 
  
#if DEBUG
  cout << "getTauDecay: matchedGenLepton " << matchedGenLepton<<endl;
#endif
  if (matchedGenLepton){
    tauDecay = -99;
   
    int tau_children_n = pMatched->numberOfDaughters(); 
    int sumPdgId = 0;
      
       for (int k=0; k<tau_children_n; k++)
       { 
  	 int dpdgId = abs(pMatched->daughter(k)->pdgId());
	 sumPdgId += dpdgId;
  	 
  	 if (dpdgId == 223 || dpdgId == 221 || dpdgId == 213 || dpdgId == 113 || dpdgId == 323)
  	 {				       
  	   if(pMatched->daughter(k)->status() != 1)
  	   {			       
  	   sumPdgId -= dpdgId;
   
  	   for (unsigned int ww=0; ww<pMatched->daughter(k)->numberOfDaughters(); ww++) 
 	   {
 	    sumPdgId += abs(pMatched->daughter(k)->daughter(ww)->pdgId());
	  
	    if (abs(pMatched->daughter(k)->daughter(ww)->pdgId())==311 && pMatched->daughter(k)->daughter(ww)->status()!=1)
	    { 
	      sumPdgId -= 311;
	      for (unsigned int v=0; v<pMatched->daughter(k)->daughter(ww)->numberOfDaughters(); v++) 
 	      {
	       sumPdgId += pMatched->daughter(k)->daughter(ww)->daughter(v)->pdgId();
	      }
	     }
	    }
 	   }
          }
         }     
       
    
      if (sumPdgId ==227)				     	 	                        { tauDecay = 0;  }//pi+nu
      if (sumPdgId ==229)		   	 	                                        { tauDecay = 1;  }//pi+pi0nu
      if (sumPdgId ==449 || sumPdgId ==338 || sumPdgId ==340)				        { tauDecay = 2;  }//pi+2pi0nu
      if (sumPdgId ==560)				     	 	                        { tauDecay = 3;  }//pi+3pi0nu
      if (sumPdgId ==671)				     	 	                        { tauDecay = 4;  }//pi+4pi0nu
      if (sumPdgId ==315)				                                        { tauDecay = 5;  }//pi+gammanu
      if (sumPdgId ==360 || sumPdgId ==382)			 	                        { tauDecay = 6;  }//pi+pi0nugamma(s)
      if (sumPdgId ==537 || sumPdgId ==357 || sumPdgId ==538)                                   { tauDecay = 7;  }//pi+k0nu
      if (sumPdgId ==468 || sumPdgId ==648 || sumPdgId ==487 || sumPdgId==667 || sumPdgId ==847){ tauDecay = 8;  }//pi+2n(w K0)nu  
      if (sumPdgId ==760 || sumPdgId ==769 || sumPdgId ==759)	    	                        { tauDecay = 9;  }//pi+3n(w pi0)nu
      if (sumPdgId ==471)				    	    	                        { tauDecay = 10; }//pi+2pi0nugamma
   							    	    	                        
      if (sumPdgId ==649)			                	                        { tauDecay = 30; }//3pi+nu
      if (sumPdgId ==760)				    	    	                        { tauDecay = 31; }//3pi+pi0nu
      if (sumPdgId ==782)				    	    	                        { tauDecay = 34; }//3pi+pi0nugamma
      if (sumPdgId ==871)				    	    	                        { tauDecay = 32; }//3pi+2pi0nu
      if (sumPdgId ==982)				    	    	                        { tauDecay = 33; }//3pi+3pi0nu
      						    	    	      
      if (sumPdgId ==337)				    	    	                        { tauDecay = 20; }//k+nu
      if (sumPdgId ==448)				    	    	                        { tauDecay = 21; }//k+pi0nu
      if (sumPdgId ==467 || sumPdgId ==647)		    	    	                        { tauDecay = 22; }//k+k0nu
      if (sumPdgId ==559)				    	    	                        { tauDecay = 23; }//k+2pi0nu   
      if (sumPdgId ==578 || sumPdgId ==758)		    	    	                        { tauDecay = 24; }//k+pi0k0nu	 
      if (sumPdgId ==670)			            	    	                        { tauDecay = 25; }//k+3pi0nu  
           						    	    	                        
      if (sumPdgId ==869)				    	    	                        { tauDecay = 40; }//k+k+pi+nu
     							    	    	                        
      if (sumPdgId ==1071)				    	    	                        { tauDecay = 50; }//5pinu
      if (sumPdgId ==1182)				    	    	                        { tauDecay = 51; }//5pipi0nu
 							    	    	                        
      if (sumPdgId ==39)				    	    	                        { tauDecay = 100;}//enunu
      if (sumPdgId ==43)				                                        { tauDecay = 200;}//mununu
  
   }		 
 
  return tauDecay;
}
*/

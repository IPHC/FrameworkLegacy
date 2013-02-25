#include "MiniTree/MiniTreeProducer/interface/MonteCarloOrigin.h"



// ----------------------------------------------------------------------------
// setGenParticleFromCandidate
// ----------------------------------------------------------------------------
void MonteCarloOrigin::setGenParticleFromCandidate (reco::GenParticle& gen,
                                                    const reco::Candidate* reco)
{
  gen.setCharge(reco->charge());
  gen.setP4    (reco->p4()    );
  gen.setMass  (reco->mass()  );
  gen.setPdgId (reco->pdgId() );
  gen.setStatus(reco->status());
  gen.setVertex(reco->vertex());
}


// ----------------------------------------------------------------------------
// getMuonOrigin
// ----------------------------------------------------------------------------
int MonteCarloOrigin::getMuonOrigin (
            const reco::GenParticleCollection* genParticles,
            const pat::Muon* thePatMuon,
				    reco::GenParticle & MotherGenMuon,
            reco::GenParticle & GrandMotherGenMuon,
            reco::GenParticle & GGrandMotherGenMuon)
{
  int muonOrigin = -99;
  const reco::Candidate * theGenMuon=0;
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


// ----------------------------------------------------------------------------
// getElectronOrigin
// ----------------------------------------------------------------------------
int MonteCarloOrigin::getElectronOrigin(
            const reco::GenParticleCollection* genParticles,
            const pat::Electron* thePatElectron,
				    reco::GenParticle & MotherGenElectron,
            reco::GenParticle & GrandMotherGenElectron,
            reco::GenParticle & GGrandMotherGenElectron)
{

  int electronOrigin = -99;
  reco::Candidate * theGenElectron =0;
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


// ----------------------------------------------------------------------------
// getTauDecay
// ----------------------------------------------------------------------------
#define DEBUG_MSG cout << "DEBUG (" << __FILE__ << ", l." << __LINE__ << ") "
int MonteCarloOrigin::getTauDecay(
             const reco::GenParticleCollection* genParticles, 
             const pat::Tau* thePatTau)
{
  int tauDecay = -999;
  bool matchedGenLepton = false;
  reco::GenParticleCollection::const_iterator pMatched; 

  for (reco::GenParticleCollection::const_iterator p = genParticles->begin(); p != genParticles->end(); ++p)
  {
    reco::Candidate* aGenTau = (dynamic_cast<reco::Candidate *>(const_cast<reco::GenParticle *>(&*p)));
    if (abs(p->pdgId()) == 15 && p->status() == 2)
	{
      #if DEBUG
         cout << "getTauOrigin: thePatElectron->genLepton() " << thePatTau->genLepton() <<endl;
      #endif
      if ((thePatTau->genLepton() != NULL) && abs(thePatTau->genLepton()->pt()-aGenTau->pt()) < 0.00001)
      {
        matchedGenLepton = true;
	    pMatched = p;
      }
    }
  } 
  
  #if DEBUG
    cout << "getTauDecay: matchedGenLepton " << matchedGenLepton<<endl;
  #endif
  if (matchedGenLepton) tauDecay = getTauDecayFromGenParticle(pMatched);
 
  return tauDecay;
}

void MonteCarloOrigin::getTauDecayProducts(const reco::Candidate* inputParticle, std::vector<const reco::Candidate*>* output)
{

	int pdgId = abs(inputParticle->pdgId());

	// If the particle is of a certain kind, we just add it to the outputVector, 
	// which will be used to compute an ID for the tau decay

	if (   (pdgId == 111) // Pi0
		|| (pdgId == 211) // Pi +/-
		|| (pdgId == 11 ) || (pdgId == 13)  // e, mu
		|| (pdgId == 12 ) || (pdgId == 14) || (pdgId == 16) // nu
		|| (pdgId == 321) // K +/-
		|| (pdgId == 130) || (pdgId == 310) || (pdgId == 311) // K_0
		|| (pdgId == 22 )) // gamma
	{
		output->push_back(inputParticle);
	}
	// Otherwise, we run this function on the decay product, recursively
	else 
	{
		int numberOfDaughters = inputParticle->numberOfDaughters();
		if (numberOfDaughters == 0)
			cout << "WARNING (" << __FILE__ << ", l." << __LINE__ << ") Ignored tau decay product with no daughters !" << endl;
		for (int i = 0 ; i < numberOfDaughters ; i++)
			getTauDecayProducts(inputParticle->daughter(i),output);
	}

}

int MonteCarloOrigin::getTauDecayFromGenParticle(reco::GenParticleCollection::const_iterator genTau_)
{
	int tauDecay = 0;

	// Certain generator add a "second tau" as the daughter, 
	// then the daughters of it are the actual decay products. 
	const reco::Candidate* genTau;
	if ((genTau_->numberOfDaughters() == 1) && (abs(genTau_->daughter(0)->pdgId()) == 15))
		genTau = genTau_->daughter(0);
	else
		genTau = &(*genTau_);
	
	// Get the vector containing the decay products
	std::vector<const reco::Candidate*> decayProducts;
	getTauDecayProducts(genTau,&decayProducts);

	// Recover the number of leptons, Pi, K and gammas
	
	//int numberOfNeutrino = 0;
	int leptonFlavor = 0;
	int numberOfPiZero = 0;
	int numberOfPiCharged = 0;
	int numberOfKZero = 0;
	int numberOfKCharged = 0;
	int numberOfGamma = 0;
	
	int nDecayProducts = decayProducts.size();
	for (int i = 0 ; i < nDecayProducts ; i++)
	{
		int pdgId = abs(decayProducts[i]->pdgId());

		//if ((pdgId == 12 ) || (pdgId == 14) || (pdgId == 16)) numberOfNeutrino++;
		     if (pdgId == 111) numberOfPiZero++;
		else if (pdgId == 211) numberOfPiCharged++;
		else if ((pdgId == 130) || (pdgId == 310) || (pdgId == 311)) numberOfKZero++;
		else if (pdgId == 321) numberOfKCharged++;
		else if (pdgId == 22 ) numberOfGamma++;
		else if ((pdgId == 11 ) || (pdgId == 13))
		{
			if (pdgId == 11) leptonFlavor = 1;
			else leptonFlavor = 2;
		}
	}

	// Compute the final tau decay number
	tauDecay = leptonFlavor      * 1
			 + numberOfPiZero    * 10
			 + numberOfPiCharged * 100 
			 + numberOfKZero     * 1000
			 + numberOfKCharged  * 10000
			 + numberOfGamma     * 100000;

  return tauDecay;
}

// ----------------------------------------------------------------------------
// getHeavyQuarkDecay
// ----------------------------------------------------------------------------
void MonteCarloOrigin::getHeavyQuarkDecayProducts(const reco::Candidate* inputParticle, std::vector<const reco::Candidate*>* output)
{

	int pdgId = abs(inputParticle->pdgId());

	// If the particle is of a certain kind, we just add it to the outputVector, 
	// which will be used to compute an ID for the quark decay

	if (   (pdgId == 11 ) || (pdgId == 13)                   // e, mu
		|| (pdgId == 12 ) || (pdgId == 14) || (pdgId == 16)) // nu
	{
		output->push_back(inputParticle);
	}
	// Otherwise, we run this function on the decay product, recursively
	else 
	{
		int numberOfDaughters = inputParticle->numberOfDaughters();
		for (int i = 0 ; i < numberOfDaughters ; i++)
			getHeavyQuarkDecayProducts(inputParticle->daughter(i),output);
	}

}

int MonteCarloOrigin::getHeavyQuarkDecayFromGenParticle(reco::GenParticleCollection::const_iterator genQuark)
{
	int quarkDecay = -99;
	int quarkFlavor = genQuark->pdgId();
   
	// Get the vector containing the decay products
	std::vector<const reco::Candidate*> decayProducts;
	getHeavyQuarkDecayProducts(&(*genQuark),&decayProducts);

	// Recover the number of leptons
	
	//int numberOfNeutrino = 0;
	int numberOfElectron = 0;
	int numberOfMuon = 0;

	int nDecayProducts = decayProducts.size();

	for (int i = 0 ; i < nDecayProducts ; i++)
	{
		int pdgId = abs(decayProducts[i]->pdgId());

		     if (pdgId == 11) numberOfElectron++;
		else if (pdgId == 13) numberOfMuon++;
	}

	// Compute the final tau decay number
	quarkDecay = numberOfElectron * 1
			   + numberOfMuon     * 10;

	return quarkDecay;
}

// ----------------------------------------------------------------------------
// fillGenInfo
// ----------------------------------------------------------------------------
void MonteCarloOrigin::fillGenInfo(std::auto_ptr<IPHCTree::MTEvent>& evt,
                                   const edm::Handle<reco::GenParticleCollection>& genParticles)
{
 
  using namespace IPHCTree;
  using namespace edm;
  using namespace reco;

  // Safety : check if pointer is null
  if (!genParticles.isValid()) return;

  int tmeme = 0;
  int idum = 0;

  // Loop over GeneratedParticle collection 
  for (reco::GenParticleCollection::const_iterator
         p = genParticles->begin (); p != genParticles->end (); ++p)
  {
    
    idum +=1;
   
    TLorentzVector thequark;
    thequark.SetPxPyPzE( p->p4().Px(), 
                         p->p4().Py(),
                         p->p4().Pz(),
                         p->p4().E());
    if ( abs(p->pdgId()) == 5 && p->status() == 3 ) evt->mc.genBquarks.push_back(thequark);
    if ( abs(p->pdgId()) == 4 && p->status() == 3 ) evt->mc.genCquarks.push_back(thequark);
    if ((abs(p->pdgId () ) == 1 
         || abs(p->pdgId () ) == 2 
         || abs(p->pdgId () ) == 3 )
        &&p->status() == 3 && p->p4().Pt() > 10) evt->mc.genLquarks.push_back(thequark);
    if ( abs(p->pdgId () ) == 22 && p->p4().Pt() > 10 ) evt->mc.genGquarks.push_back(thequark);
    
    
    //******************************
    //****** add top
    //******************************
    if ( abs(p->pdgId () ) == 6 )
    {
      // rewritte the info twice top/anti-top but it was checked that their mothers are the same
      if(p->numberOfMothers()>=1) evt->mc.partonFlavor.first = p->mother(0)->pdgId();
      if(p->numberOfMothers()>=2) evt->mc.partonFlavor.second = p->mother(1)->pdgId();
      TopDecaysMC topQuark;
      topQuark.p4_t_gen.SetPxPyPzE (p->p4 ().Px (), p->p4 ().Py (), p->p4 ().Pz (), p->p4 ().E ());
      topQuark.Q_gen = p->charge();
      const GenParticle & paIt = *p;
      for (unsigned int j = 0; j < paIt.numberOfDaughters (); j++) {
        if ( abs(paIt.daughter (j)->pdgId ()) == 5) topQuark.p4_b_gen.SetPxPyPzE (paIt.daughter(j)->p4().Px(),paIt.daughter(j)->p4().Py(),paIt.daughter(j)->p4().Pz(), paIt.daughter(j)->p4().E());
      }
      evt->mc.topAndDecays.push_back(topQuark);
    }
   
    //******************************
    //****** add Z
    //******************************
 
 
    if (abs (p->pdgId ()) == 23 && p->status() == 3)
    { 
     
      const reco::Candidate * ZDaughter = 0;
      const reco::Candidate * Tau = 0;
      const reco::Candidate * TauDaughter = 0;
      const reco::Candidate * TauNu1 = 0;
      const reco::Candidate * TauNu2 = 0;
      const reco::Candidate * TauANu1 = 0;
      const reco::Candidate * TauANu2 = 0;
      TLorentzVector v;
     
      bool Ztobb = false;
      ZDecaysMC zBoson;
      zBoson.p4_Z_gen.SetPxPyPzE (p->p4().Px(), p->p4().Py(), p->p4().Pz(), p->p4().E());
 
	  if (p->mother() != 0) zBoson.mcMotherId = p->mother()->pdgId(); 

      for (unsigned int d = 0; d < p->numberOfDaughters (); d++)
      {
        //ZDaughter = const_cast<reco::Candidate*> (p->daughter(d));
        ZDaughter = p->daughter (d);
        if (abs (ZDaughter->pdgId ()) == 5)
          Ztobb = true;
        if (ZDaughter->status () == 3) {
          if (ZDaughter->pdgId () == 11 || ZDaughter->pdgId () == 13 || ZDaughter->pdgId () == 15) {
            zBoson.p4_Lep1_gen.SetPxPyPzE (ZDaughter->p4 ().Px (), ZDaughter->p4 ().Py (), ZDaughter->p4 ().Pz (), ZDaughter->p4 ().E ());
            zBoson.Q_Lep1_gen = -1;
            zBoson.Lep1_pdgID = ZDaughter->pdgId ();	   
          }
          if (ZDaughter->pdgId () == -11 || ZDaughter->pdgId () == -13 || ZDaughter->pdgId () == -15) {
            zBoson.p4_Lep2_gen.SetPxPyPzE (ZDaughter->p4 ().Px (), ZDaughter->p4 ().Py (), ZDaughter->p4 ().Pz (), ZDaughter->p4 ().E ());
            zBoson.Q_Lep2_gen = 1;
            zBoson.Lep2_pdgID = ZDaughter->pdgId (); 
          }
	   
          if (abs (ZDaughter->pdgId ()) == 11)
            tmeme = tmeme + 1;
          if (abs (ZDaughter->pdgId ()) == 13)
            tmeme = tmeme + 10;
	 
          if (abs (ZDaughter->pdgId ()) == 15) {
            Tau = ZDaughter; 
            TauDaughter = ZDaughter->daughter (0);
            //while (abs (TauDaughter->pdgId ()) == 15 && TauDaughter->numberOfDaughters ()>0) {
            while (abs (TauDaughter->pdgId ()) == 15 && TauDaughter->numberOfDaughters()>0) {	     
              Tau = TauDaughter;
              //TauDaughter = const_cast<reco::Candidate*> (TauDaughter->daughter(0));
              TauDaughter = TauDaughter->daughter (0);
            }
	    
            if (Tau) 
            {
              bool lepDecay = false; 
              bool stableTau = false;
	    
              for (unsigned int k = 0; k < Tau->numberOfDaughters (); k++) {
                //if      ( Tau->daughter(k)->pdgId() == 16)  { TauNu1  = const_cast<reco::Candidate*> (Tau->daughter(k));
                if (Tau->daughter (k)->pdgId () == 16) {
                  TauNu1 = Tau->daughter (k);
                }
                //else if ( Tau->daughter(k)->pdgId() == -16) { TauANu1 = const_cast<reco::Candidate*> (Tau->daughter(k));
                else if (Tau->daughter (k)->pdgId () == -16) {
                  TauANu1 = Tau->daughter (k);
                }
                else if (Tau->daughter (k)->pdgId () == 12 ||
                         //Tau->daughter(k)->pdgId() == 14)   { TauNu2 = const_cast<reco::Candidate*> (Tau->daughter(k));
                         Tau->daughter (k)->pdgId () == 14) {
                  TauNu2 = Tau->daughter (k);
                }
                else if (Tau->daughter (k)->pdgId () == -12 ||
                         //Tau->daughter(k)->pdgId() == -14)  { TauANu2 = const_cast<reco::Candidate*> (Tau->daughter(k));
                         Tau->daughter (k)->pdgId () == -14) {
                  TauANu2 = Tau->daughter (k);
                }
                else if (abs (Tau->daughter (k)->pdgId ()) == 11) {
                  tmeme = tmeme + 10100;
                  lepDecay = true;
                }
                else if (abs (Tau->daughter (k)->pdgId ()) == 13) {
                  tmeme = tmeme + 11000;
                  lepDecay = true;
                }
                else if  (abs (Tau->daughter (k)->pdgId ()) == 15){	  
                  stableTau = true;
                }
              }
	      
              if (lepDecay == false && stableTau == false) {
                tmeme = tmeme + 10000;
              }
              if (stableTau == true) {
                tmeme += -99999;
              }
	     
            }
          }
        }
      }
     
      evt->mc.zAndDecays.push_back(zBoson);
    }
   
    //******************************
    //****** add W
    //******************************
    if ( abs(p->pdgId () ) == 24 && p->status() == 3)
    {
   
      const Candidate *WDaughter = 0;
      const Candidate *TauDaughter = 0;
      const Candidate *Tau = 0;
      const Candidate *TauNu1 = 0;
      const Candidate *TauNu2 = 0;
     
      WDecaysMC wBosons;
      wBosons.p4_W_gen.SetPxPyPzE (p->p4 ().Px (), p->p4 ().Py (), p->p4 ().Pz (), p->p4 ().E ());
      if(p->pdgId () == 24) wBosons.Q_Lep_gen = -1;
      else                  wBosons.Q_Lep_gen = 1;
    	  
	  if (p->mother() != 0) wBosons.mcMotherId = p->mother()->pdgId();

      for (unsigned int d = 0; d < p->numberOfDaughters (); d++) {
        WDaughter = p->daughter (d);
      
        if (WDaughter->status () == 3) 
        {
       
          if (abs (WDaughter->pdgId ()) == 11 || abs (WDaughter->pdgId ()) == 13 || abs (WDaughter->pdgId ()) == 15) 
          {
            wBosons.p4_Lep_gen.SetPxPyPzE (WDaughter->p4 ().Px (), WDaughter->p4 ().Py (), WDaughter->p4 ().Pz (), WDaughter->p4 ().E ());
            wBosons.Q_Lep_gen = (WDaughter->pdgId () > 0) ? -1 : 1;
            wBosons.mcLepId = WDaughter->pdgId ();
            if (abs (WDaughter->pdgId ()) == 11)
              tmeme = tmeme + 1;
            if (abs (WDaughter->pdgId ()) == 13)
              tmeme = tmeme + 10;
          }
	 
          if (abs (WDaughter->pdgId ()) == 12 || abs (WDaughter->pdgId ()) == 14 || abs (WDaughter->pdgId ()) == 16) {
            wBosons.p4_Neu_gen.SetPxPyPzE (WDaughter->p4 ().Px (), WDaughter->p4 ().Py (), WDaughter->p4 ().Pz (), WDaughter->p4 ().E ());
          }
	 
          if (abs (WDaughter->pdgId ()) == 15) 
          {
            Tau = WDaughter->daughter (0);
            TauDaughter = WDaughter->daughter (0);
            while (abs (TauDaughter->pdgId ()) == 15 && TauDaughter->numberOfDaughters()>0) {
              Tau = TauDaughter;
              TauDaughter = TauDaughter->daughter (0);
	    
            }
	   
            if (Tau) 
            {
              bool lepDecay = false;
              bool stableTau = false;
	     
              for (unsigned int k = 0; k < Tau->numberOfDaughters (); k++) { 
	        
                if (abs (Tau->daughter (k)->pdgId ()) == 11) {
                  tmeme = tmeme + 10100;
                  lepDecay = true;
                }
                else if (abs (Tau->daughter (k)->pdgId ()) == 13) {
                  tmeme = tmeme + 11000;
                  lepDecay = true;
                }
                else if (abs (Tau->daughter (k)->pdgId ()) == 16) {
                  TauNu1 = Tau->daughter (k);//what for, one should store anti-nu as well... 
                }
	       
                else if (abs (Tau->daughter (k)->pdgId ()) == 12 || abs (Tau->daughter (k)->pdgId () == 14)) {
                  TauNu2 = Tau->daughter (k);//what for, one should store anti-nu as well...
                }
                else if (abs (Tau->daughter (k)->pdgId ()) == 15) {	
                  stableTau = true;
                }	     
              }
              if (lepDecay == false)
                tmeme = tmeme + 10000;
              if (stableTau == true)
                tmeme = -99999;	     
            }
	   	   
          }
	  
        }
      } 
     
      evt->mc.wAndDecays.push_back(wBosons);
    }
 
   
  }
 
  evt->mc.TMEME = tmeme;
}


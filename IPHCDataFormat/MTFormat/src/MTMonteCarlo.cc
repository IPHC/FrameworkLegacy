#include "../interface/MTMonteCarlo.h"

using namespace IPHCTree;
using namespace edm;
using namespace reco;

// ---------------------------------------------------------------------------
// Reset
// ----------------------------------------------------------------------------
void MTMonteCarlo::Reset(bool constructor_call)
{
  NTMonteCarlo::Reset(constructor_call);
  if (!constructor_call)
  {
    GPC.clear();
    GPC_list_index_dau.clear();
    GPC_list_index_mot.clear();
  }
}


// ---------------------------------------------------------------------------
// Dump
// ----------------------------------------------------------------------------
void MTMonteCarlo::Dump(std::ostream & os) const
{
  NTMonteCarlo::Dump(os);
  os << " Number of GenParticles : " << GPC.size() << std::endl;
}


// ---------------------------------------------------------------------------
// fillGenInfo
// ----------------------------------------------------------------------------
void MTMonteCarlo::fillGenInfo(reco::GenParticleCollection* genParticles)
{
 
  // Safety : check if pointer is null
  if (genParticles==0) return;

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
    if ( abs(p->pdgId()) == 5 && p->status() == 3 ) genBquarks.push_back(thequark);
    if ( abs(p->pdgId()) == 4 && p->status() == 3 ) genCquarks.push_back(thequark);
    if ((abs(p->pdgId () ) == 1 
         || abs(p->pdgId () ) == 2 
         || abs(p->pdgId () ) == 3 )
        &&p->status() == 3 && p->p4().Pt() > 10) genLquarks.push_back(thequark);
    if ( abs(p->pdgId () ) == 22 && p->p4().Pt() > 10 ) genGquarks.push_back(thequark);
    
    
    //******************************
    //****** add top
    //******************************
    if ( abs(p->pdgId () ) == 6 )
    {
      // rewritte the info twice top/anti-top but it was checked that their mothers are the same
      if(p->numberOfMothers()>=1) this->partonFlavor.first = p->mother(0)->pdgId();
      if(p->numberOfMothers()>=2) this->partonFlavor.second = p->mother(1)->pdgId();
      TopDecaysMC topQuark;
      topQuark.p4_t_gen.SetPxPyPzE (p->p4 ().Px (), p->p4 ().Py (), p->p4 ().Pz (), p->p4 ().E ());
      topQuark.Q_gen = p->charge();
      const GenParticle & paIt = *p;
      for (unsigned int j = 0; j < paIt.numberOfDaughters (); j++) {
        if ( abs(paIt.daughter (j)->pdgId ()) == 5) topQuark.p4_b_gen.SetPxPyPzE (paIt.p4 ().Px (), paIt.p4 ().Py (), paIt.p4 ().Pz (), paIt.p4 ().E ());
      }
      this->topAndDecays.push_back(topQuark);
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
      zBoson.p4_Z_gen.SetPxPyPzE (p->p4 ().Px (), p->p4 ().Py (), p->p4 ().Pz (), p->p4 ().E ());
    
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
     
      this->zAndDecays.push_back(zBoson);
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
	  
          /*
            int indxtau = -1;
            for (unsigned int k = 0; k < W->numberOfDaughters (); k++) { 
            std::cout << "Second Loop over W daughters " << W->daughter (k)->pdgId ()<< " " <<  W->daughter (k)->status ()<<std::endl; 
            if (abs (W->daughter (k)->pdgId ()) == 15)
            indxtau = k;
            }
            while (indxtau >= 0) {
            if (!W)
            cout << "NULL " << endl;
            std::cout <<"indxtau " << std::endl;
            bool FoundTau = false;
            for (unsigned int k = 0; k < W->numberOfDaughters (); k++) {
            if (abs (W->daughter (k)->pdgId ()) == 24)
            continue;
            if (abs (W->daughter (k)->pdgId ()) == 11 || abs (W->daughter (k)->pdgId ()) == 13) {
            if (abs (W->daughter (k)->pdgId ()) == 11)
            tmeme += 100;
            if (abs (W->daughter (k)->pdgId ()) == 13)
            tmeme += 1000;
            indxtau = -1;
            }
            if (abs (W->daughter (k)->pdgId ()) == 15) {
            indxtau = k;
            FoundTau = true;
            }

            if (abs (W->pdgId ()) == 15) {
            if ( abs(W->daughter (k)->pdgId ()) == 16) {
            TauNu1 = W->daughter (k);
            }
            // 	      else if (W->daughter (k)->pdgId () == -16) {
            // 		TauANu1 = W->daughter (k);
            // 	      }
            else if (abs(W->daughter (k)->pdgId ()) == 12 || abs(W->daughter (k)->pdgId ()) == 14) {
            TauNu2 = W->daughter (k);
            }
            // 	      else if (W->daughter (k)->pdgId () == -12 || W->daughter (k)->pdgId () == -14) {
            // 		TauANu2 = W->daughter (k);
            // 	      }
            }
            }
            if (FoundTau) {
            W = W->daughter (indxtau);
            }
            else {
            indxtau = -1;
            }
            }*/

        }
      } 
     
      this->wAndDecays.push_back(wBosons);
    }
   
   
    //******************************
    //****** add taus
    //******************************
   
    if ( p->pdgId () == 15 ){  
      TLorentzVector p4(p->px(),p->py(),p->pz(),p->energy());
      this->Generatedtaus.push_back(p4);}
   
    if ( p->pdgId () == -15 ){  
      TLorentzVector p4(p->px(),p->py(),p->pz(),p->energy());
      this->GeneratedAtaus.push_back(p4);}
   
  }
 
  this->TMEME = tmeme;
}

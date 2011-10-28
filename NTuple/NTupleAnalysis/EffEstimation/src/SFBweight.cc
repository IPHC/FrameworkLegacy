#include "../interface/SFBweight.h"

SFBweight::SFBweight(){
  btag_algo_=-1;
  btag_discri_=-999.;
  n_bjets_= 0;
  method_origin1_="default";
  method_origin2_="default";

  histo_sfvalb_=0;
  histo_sferrb_=0;
  histo_sfvall_=0;
  histo_sferrl_=0;

  histo_effvalb_=0;
  histo_efferrb_=0;
  histo_effvall_=0;         
  histo_efferrl_=0;

  histo_effmcb_=0;
  histo_effmcc_=0;
  histo_effmcl_=0;
  histo_errmcb_=0;
  histo_errmcc_=0;
  histo_errmcl_=0;

}

SFBweight::SFBweight(int btag_algo, float btag_discri, int n_bjets){
         SFBinit(btag_algo,btag_discri,n_bjets);
}


SFBweight::~SFBweight(){
}

void SFBweight::SFBinit(int btag_algo, float btag_discri, int n_bjets){

         std::cout << " initialisation of SFBweight " << std::endl;
         btag_algo_=btag_algo;
         btag_discri_=btag_discri;
         n_bjets_=n_bjets;
         std::string algoname; 
         std ::cout << " ALGO " <<  btag_algo << " & DISCRI CUT " << btag_discri << std::endl;
         if (btag_algo==0) {
             // TrackCounting
             algoname="TCHE";
             if (btag_discri>1.69 &&  btag_discri<1.71) { 
                    method_origin1_="BTAG"+algoname+"L";
                    method_origin2_="MISTAG"+algoname+"L";
             }
             else if (btag_discri>3.29 && btag_discri<3.3) { 
                    method_origin1_="BTAG"+algoname+"M";
                    method_origin2_="MISTAG"+algoname+"M";
             }
             else {
                    method_origin1_="default";
                    method_origin2_="default";
             }
         }
         else if (btag_algo==1) {
              // SecondaryVertex
              algoname="SSVHE";
              if (btag_discri>1.73 && btag_discri<1.75) { 
//                    method_origin1_="BTAG"+algoname+"M";
//                    method_origin2_="MISTAG"+algoname+"M";
                    method_origin1_="default";
                    method_origin2_="default";
              }
              else {
                    method_origin1_="default";
                    method_origin2_="default";
              }
         }
         else if (btag_algo==2) {
              // SM : non code!
             std::cout << " SM : no information for the moment " << std::endl;
 
         }
         else {
             std::cout << " WHICH B-TAG ALGO DO YOU WANT??? " << std::endl;
             method_origin1_="default";
             method_origin2_="default";
         }
         std::cout << " --> ALGO : " << algoname << ", METHODS for SF&Eff : " << method_origin1_ << " and " << method_origin2_ << std::endl;
//         std::cout << " !! ATTENTION : For the moment, no SF(b-quark) information in MCCalo !!  " << std::endl; 
//         std::cout << " !! ATTENTION : --> 0.95 +/- 0.10 (hard coded for TCHEL) !!  " << std::endl; 
}

void SFBweight::LoadInfo(){



        TFile* f = TFile::Open("/opt/sbg/data/data1/cms/ccollard/CMSSW/CMSSW_4_2_5/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/efficacite_btag.root");

        std::string histo_name1= "h_" + method_origin1_ + "_BTAG" + "B" +"EFFCORR";
        std::string histo_name2= "h_" + method_origin1_ + "_BTAG" + "B" +"ERRCORR";
//        std::string histo_name3= "h_" + method_origin1_ + "_BTAG" + "B" +"EFF";
//        std::string histo_name4= "h_" + method_origin1_ + "_BTAG" + "B" +"ERR";
        std::string histo_name3= "h_" + method_origin1_ + "_BTAG" + "B" +"EFFCORR";
        std::string histo_name4= "h_" + method_origin1_ + "_BTAG" + "B" +"ERRCORR";
        std::string histo_name5= "h_" + method_origin2_ + "_BTAG" + "L" +"EFFCORR";
        std::string histo_name6= "h_" + method_origin2_ + "_BTAG" + "L" +"ERRCORR";
//        std::string histo_name7= "h_" + method_origin2_ + "_BTAG" + "L" +"EFF";
//        std::string histo_name8= "h_" + method_origin2_ + "_BTAG" + "L" +"ERR";
        std::string histo_name7= "h_" + method_origin2_ + "_BTAG" + "L" +"EFFCORR";
        std::string histo_name8= "h_" + method_origin2_ + "_BTAG" + "L" +"ERRCORR";
 
        if (method_origin1_ !="default" && method_origin2_!="default") {
         histo_sfvalb_    = (TH2D*) gDirectory->Get( histo_name1.c_str() ) ;
         histo_sferrb_    = (TH2D*) gDirectory->Get( histo_name2.c_str() ) ;
         histo_effvalb_   = (TH2D*) gDirectory->Get( histo_name3.c_str() ) ;
         histo_efferrb_   = (TH2D*) gDirectory->Get( histo_name4.c_str() ) ;
         histo_sfvall_    = (TH2D*) gDirectory->Get( histo_name5.c_str() ) ;
         histo_sferrl_    = (TH2D*) gDirectory->Get( histo_name6.c_str() ) ;
         histo_effvall_   = (TH2D*) gDirectory->Get( histo_name7.c_str() ) ;
         histo_efferrl_   = (TH2D*) gDirectory->Get( histo_name8.c_str() ) ;



         histo_sfvalb_->SetDirectory(0); // 
         histo_sferrb_->SetDirectory(0); // 
         histo_effvalb_->SetDirectory(0); // 
         histo_efferrb_->SetDirectory(0); // 
         histo_sfvall_->SetDirectory(0); // 
         histo_sferrl_->SetDirectory(0); // 
         histo_effvall_->SetDirectory(0); // 
         histo_efferrl_->SetDirectory(0); // 

         std::cout << " loaded histo: " <<  histo_name1.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name2.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name3.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name4.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name5.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name6.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name7.c_str() << std::endl;
         std::cout << " loaded histo: " <<  histo_name8.c_str() << std::endl;
        }
        else {
         std::cout << " no histogram loaded : not the correct methods! " << std::endl;
        }

        f->Close();
}



void SFBweight::LoadInfo2(){

/*

//        TFile* f2 = TFile::Open("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_skimlept.root");

	bool found = false;
	string filename;
	// The values are hard-coded ... This could be changed in the future.
	if(btag_algo_ == 0 && fabs(btag_discri_-0.7)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_0.7.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-0.9)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_0.9.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-1.1)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_1.1.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-1.3)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_1.3.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-1.5)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_1.5.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-1.7)<0.00001){
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_l.root");
//		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_414_tchel.root");
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root2011/eff_from_ttmadgraph_summer11.root");
		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_TCHEL.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-3.3)<0.00001){
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_m.root");
		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_TCHEM.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-5.0)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_5.0.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-7.5)<0.00001){
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_7.5.root");
		found = true;
	}
	if(btag_algo_ == 0 && fabs(btag_discri_-10.2)<0.00001){
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_tche_t.root");
		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_TCHET.root");
		found = true;
	}
	if(btag_algo_ == 1 && fabs(btag_discri_-1.74)<0.00001){
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_ssvhe_m.root");
		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_SSVHEL.root");
		found = true;
	}
	if(btag_algo_ == 1 && fabs(btag_discri_-3.05)<0.00001){
		//filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph_ssvhe_t.root");
		filename = string("/opt/sbg/data/data1/cms/echabert/RootFiles/eff_from_ttmadgraph_SSVHET.root");
		found = true;
	}
	if(!found){ 
//		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root/eff_from_ttmadgraph.root");
		filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/fichier_root2011/eff_from_ttmadgraph_summer11.root");
		cerr<<"SFBweight::LoadInfo2:: Uses the default file. No specification of b-tagging algo & W.P. given"<<endl;
	}
	cout<<"SFBweight::LoadInfo2:: Loading the file "<<filename<<endl;
        TFile* f2 = TFile::Open(filename.c_str());

//        gDirectory->ls(); 
        
//        histo_effmcb_  = (TH2D*) gDirectory->Get( "histo_eff_bq" ) ;
//        histo_effmcl_  = (TH2D*) gDirectory->Get( "histo_eff_lq" ) ;
        histo_effmcb_  = (TH2D*) f2->Get( "h_eff_bq" ) ;
        histo_effmcc_  = (TH2D*) f2->Get( "h_eff_cq" ) ;
        histo_effmcl_  = (TH2D*) f2->Get( "h_eff_lq" ) ;
        histo_errmcb_  = (TH2D*) f2->Get( "h_err_bq" ) ;
        histo_errmcc_  = (TH2D*) f2->Get( "h_err_cq" ) ;
        histo_errmcl_  = (TH2D*) f2->Get( "h_err_lq" ) ;

*/

        string filename; 
        filename = string("/opt/sbg/data/data1/cms/ccollard/CMSSW/CMSSW_4_2_5/src/MiniTreeAnalysis/NTupleAnalysis/macros/data/eff_from_ttmadgraph_summer11_multiwp.root");
	cout<<"SFBweight::LoadInfo2:: Loading the file "<<filename<<endl;
        TFile* f2 = TFile::Open(filename.c_str());
        char newdirname[30];
        sprintf(newdirname,"algo_%i_discri_%4.2f",btag_algo_,btag_discri_);
        TDirectoryFile* newdir= (TDirectoryFile*) f2->Get(newdirname);
        if (newdir==0) { 
          cerr<<"SFBweight::LoadInfo2:: No btag efficiency computed for the given b-tagging algo & W.P. --> use TCHEL info by default"<<endl;
          sprintf(newdirname,"algo_0_discri_1.70");
        }
        cout << "used directory in the file " << newdirname << endl;

        newdir->cd();
        histo_effmcb_  = (TH2D*) newdir->Get( "h_eff_bq" ) ;
        histo_effmcc_  = (TH2D*) newdir->Get( "h_eff_cq" ) ;
        histo_effmcl_  = (TH2D*) newdir->Get( "h_eff_lq" ) ;
        histo_errmcb_  = (TH2D*) newdir->Get( "h_err_bq" ) ;
        histo_errmcc_  = (TH2D*) newdir->Get( "h_err_cq" ) ;
        histo_errmcl_  = (TH2D*) newdir->Get( "h_err_lq" ) ;


        if (histo_effmcb_!=0) std::cout << " loaded histo: h_eff_bq " << std::endl;
        if (histo_effmcc_!=0) std::cout << " loaded histo: h_eff_cq " << std::endl;
        if (histo_effmcl_!=0) std::cout << " loaded histo: h_eff_lq " << std::endl;
        if (histo_errmcb_!=0) std::cout << " loaded histo: h_err_bq " << std::endl;
        if (histo_errmcc_!=0) std::cout << " loaded histo: h_err_cq " << std::endl;
        if (histo_errmcl_!=0) std::cout << " loaded histo: h_err_lq " << std::endl;

/*

        histo_effmcb_->SetDirectory(0); // 
        histo_effmcc_->SetDirectory(0); // 
        histo_effmcl_->SetDirectory(0); // 


//        f2->Close();
*/

}

float SFBweight::GetWeight(int info,  int quarkorigin, float pt, float eta){



//         std::cout << "debug " << info << " " << quarkorigin << "--> " ;

         std::string whichquark;
         if (quarkorigin==5) {
           whichquark="B";
         }
         else if (quarkorigin==0) {
           whichquark="L";
         }
         else if (quarkorigin==4) {
              whichquark="C";
         }
         else {
            whichquark="N";
            std::cout << " Choose another value for quarkorigin (5 =b or 0= light or 4=c) " << quarkorigin << std::endl;
            return -1.;
        }

//        std::cout << " Extraction of weight for info = " << info << ", pt = " << pt << ", eta = " << eta 
//                  << " (" << whichquark << "-jet) " << std::endl;

        if (info<4 && method_origin1_=="default" && method_origin2_=="default") {
            std::cout << " NOT THE CORRECT METHODS ==> return -1!" << std::endl;
            return -1.;
        }
 
        TH2D* histo_local;

        if (quarkorigin==5 || quarkorigin==4) {
          if (info==0){ histo_local= histo_sfvalb_; }
          else if (info==1) { histo_local= histo_sferrb_; }
          else if (info==2) { histo_local= histo_effvalb_; }
          else if (info==3) { histo_local= histo_efferrb_; }
          else if (info==4) {
               if (quarkorigin==5) histo_local= histo_effmcb_; 
               else  histo_local= histo_effmcc_; 
          }
          else if (info==5) {
               if (quarkorigin==5) histo_local= histo_errmcb_; 
               else  histo_local= histo_errmcc_; 
          }
          else { std::cout << "This option for info doesn't exist ! Choose another info value : [0,4]"<< std::endl;
                return -1.;
          }
        }
        else {
          // case : quarkorigin==0
          if (info==0){ histo_local= histo_sfvall_; }   
          else if (info==1) { histo_local=  histo_sferrl_; }
          else if (info==2) { histo_local=  histo_effvall_; }
          else if (info==3) { histo_local=  histo_efferrl_; }
          else if (info==4) { histo_local= histo_effmcl_; }
          else if (info==5) { histo_local= histo_errmcl_; }
          else { std::cout << "This option for info doesn't exist ! Choose another info value : [0,4]"<< std::endl;
                return -1.;
          }
        }

        float aa = -1.;
//      No guaranty that the binWidth is constant!
/*
        bool found = false;
        for( int binX = 1; binX <= histo_local->GetNbinsX(); binX++ )
        {
               for( int binY = 1; binY <= histo_local->GetNbinsY(); binY++ )
               {
                  if  (histo_local->GetXaxis()->GetBinLowEdge( binX ) <= pt &&
                       pt < histo_local->GetXaxis()->GetBinUpEdge( binX )   &&
                       histo_local->GetYaxis()->GetBinLowEdge( binY ) <= eta &&
                       eta < histo_local->GetYaxis()->GetBinUpEdge( binY ) )
                   {
                      aa= histo_local->GetBinContent( binX, binY);
		      found = true;
		      break;
                   }
               }
	       if(found) break;
        }
*/

        if (quarkorigin==5 && pt>=240) pt=239;  // because limit in DB
	if (quarkorigin==0 && pt>=520) pt=519;  // because limit in DB
        aa= histo_local->GetBinContent( histo_local->FindBin(pt,eta) );

        histo_local= new TH2D("aa","",10,0,1,10,0,1);
        histo_local->Delete();
        
//        if ((quarkorigin==5 || quarkorigin==4) && info==0) aa=1.0;
//        if (quarkorigin==0 && info==0) aa=1.0;
/*
        // hard coded here : SF(b-quark) +/- error
        if ((quarkorigin==5 || quarkorigin==4) && info==0) aa=0.95;
        if ((quarkorigin==5 || quarkorigin==4) && info==1) aa=0.095;

        // hard coded here : SF(l-quark) +/- error
        if (quarkorigin==0 && info==0) aa=1.11;
        if (quarkorigin==0 && info==1) aa=0.12;
*/

//        if (info==0) std::cout << "debug quarkorigin" << quarkorigin << " SF= " << aa << std::endl;
//        else if (info==1) std::cout << "debug quarkorigin" << quarkorigin << " Error= " << aa << std::endl;

        return aa;
}
vector<float> SFBweight::GetWeigth4BSel(int method_b,  int syst_b, const std::vector<NTJet> &  selJets){
      return GetWeigth4BSel(method_b,  syst_b, selJets, -1., -1.);
}

vector<float> SFBweight::GetWeigth4BSel(int method_b,  int syst_b, const std::vector<NTJet> &  selJets, float sf_val_for_b, float sf_val_for_l){
       std::vector<float> proba_jetb;
       vector<float> weight;
       weight.push_back(1); // weightb of the event
       weight.push_back(0); // probability to get 0 jet
       weight.push_back(0); // probability to get 1 jet
       weight.push_back(0); // probability to get 2 jet
       weight.push_back(0); // probability to get at least 3 jet
       for(unsigned int j=0;j<selJets.size();j++){
             // only quark from a defined quarkorigin_
             int sectectedflavour=0;
             int quarkorigin=-1;
             // LIGHT QUARKS 
             if (abs(selJets[j].partonFlavour)==1) sectectedflavour=1; //d quark
             if (abs(selJets[j].partonFlavour)==2) sectectedflavour=1; //u quark
             if (abs(selJets[j].partonFlavour)==3) sectectedflavour=1; //s quark
             if (abs(selJets[j].partonFlavour)==21) sectectedflavour=1; //gluon 
             if (abs(selJets[j].partonFlavour)==21) sectectedflavour=1; //gluon 
             if (sectectedflavour==1) quarkorigin=0;
             // B QUARKS
             if (abs(selJets[j].partonFlavour)==5) {
                  sectectedflavour=1;
                  quarkorigin=5;
             }
             // C QUARKS 
             else if (abs(selJets[j].partonFlavour)==4) {
                  sectectedflavour=1;
                  quarkorigin=4;

             }
             // NOT RECOGNIZED --> LIGHT QUARKS, for the moment
             else if (selJets[j].partonFlavour ==0) {
                  sectectedflavour=1;
                  quarkorigin=0;
             }

             if (sectectedflavour==0) {
                //DEBUG
                std::cout << " partonFlavour " << selJets[j].partonFlavour << std::endl;
             }
             float discri_val=0.;
             switch(btag_algo_){
                         case 0 :
                                 discri_val=selJets[j].TCDiscri;
                                 break;
                         case 1 :
                                 discri_val=selJets[j].SVDiscri;
                                 break;
                         case 2 :
                                 discri_val=selJets[j].SMDiscri;
                                 break;
                         default:
                                 cerr << "btagAlgo doesn't exist !"<<endl;
                                 break;
              }


              float pt_val_jet = selJets[j].p4.Pt();
              if (pt_val_jet>1000.) pt_val_jet=997.;
              float eta_val_jet = selJets[j].p4.Eta();
              if (eta_val_jet<0) eta_val_jet*=-1.;
              if (eta_val_jet>=2.4) eta_val_jet=2.399;

              float pt_val_jet_orig = selJets[j].p4.Pt();
              float eta_val_jet_orig = selJets[j].p4.Eta();

              int info_b=method_b;
              if (method_b>=2) info_b=0;

              // Compute the weight, depending of method_b 
              // method_b = 0 : SF
              // method_b = 1 : Eff_Data
              // method_b = 2 : SF*Eff_MC
              // method_b = 3 : SF*Eff_MC with error depending on SF and Eff

              float weight_jet=0;
              //impose value for SF from outside
              if      (info_b==0 && quarkorigin==5 && sf_val_for_b>-1.) weight_jet=sf_val_for_b;  //b
              else if (info_b==0 && quarkorigin==4 && sf_val_for_b>-1.) weight_jet=sf_val_for_b;  //c
              else if (info_b==0 && quarkorigin==0 && sf_val_for_l>-1.) weight_jet=sf_val_for_l;  //udsg
              // take value from root files
              else weight_jet=GetWeight(info_b*2,quarkorigin,pt_val_jet,eta_val_jet);

              float ptvaleff=pt_val_jet;
              if (pt_val_jet>200.) ptvaleff=199.;
              float eff_mc=GetWeight(4,quarkorigin,ptvaleff,eta_val_jet);
              float sf1=weight_jet;
              float ersf1=0;
              float eref1=0;
              float errw=0;
              if (method_b==3 && syst_b>0) {
                          ersf1=GetWeight(1,quarkorigin,pt_val_jet,eta_val_jet);
                          eref1=GetWeight(5,quarkorigin,ptvaleff,eta_val_jet);
                          errw=sqrt(ersf1*ersf1*eff_mc*eff_mc + sf1*sf1*eref1*eref1)/eff_mc;  // from SF and Eff
              }
              if (method_b==4 && syst_b>0) {
                          eref1=GetWeight(5,quarkorigin,ptvaleff,eta_val_jet);  // from Eff only
              }


              if (syst_b==1) { //+ all
                    if (method_b==3) {
                          weight_jet+=errw;
                    }
                    else if (method_b==4) {
                          eff_mc+=eref1;
                    }
                    else {
                       weight_jet+=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
              }
              else if (syst_b==2) { //- all
                    if (method_b==3) {
                          weight_jet-=errw;
                    }
                    else if (method_b==4) {
                          eff_mc-=eref1;
                    }
                    else {
                       weight_jet-=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
              }
              else if (syst_b==3) { //+ only b!
                  if (quarkorigin==4|| quarkorigin==5) {
                    if (method_b==3) {
                          weight_jet+=errw;
                    }
                    else if (method_b==4) {
                          eff_mc+=eref1;
                    }
                    else {
                         weight_jet+=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }
              else if (syst_b==4) { //- only b!
                  if (quarkorigin==4|| quarkorigin==5) {
                    if (method_b==3) {
                          weight_jet-=errw;
                    }
                    else if (method_b==4) {
                          eff_mc-=eref1;
                    }
                    else {
                      weight_jet-=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }
              else if (syst_b==5) { //+ only light!
                  if (quarkorigin==0) {
                    if (method_b==3) {
                          weight_jet+=errw;
                    }
                    else if (method_b==4) {
                          eff_mc+=eref1;
                    }
                    else {
                      weight_jet+=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }
              else if (syst_b==6) { //- only light!
                  if (quarkorigin==0) {
                    if (method_b==3) {
                          weight_jet-=errw;
                    }
                    else if (method_b==4) {
                          eff_mc-=eref1;
                    }
                    else {
                       weight_jet-=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }
              else if (syst_b==7) { //+ b and - light!
                  if (quarkorigin==4|| quarkorigin==5) {
                    if (method_b==3) {
                          weight_jet+=errw;
                    }
                    else if (method_b==4) {
                          eff_mc+=eref1;
                    }
                    else {
                          weight_jet+=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
                  else if (quarkorigin==0) {
                    if (method_b==3) {
                          weight_jet-=errw;
                    }
                    else if (method_b==4) {
                          eff_mc-=eref1;
                    }
                    else {
                         weight_jet-=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }
              else if (syst_b==8) { //- b and + light!
                  if (quarkorigin==4|| quarkorigin==5) {
                    if (method_b==3) {
                          weight_jet-=errw;
                    }
                    else if (method_b==4) {
                          eff_mc-=eref1;
                    }
                    else {
                         weight_jet-=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
                  else if (quarkorigin==0) {
                    if (method_b==3) {
                          weight_jet+=errw;
                    }    
                    else if (method_b==4) {
                          eff_mc+=eref1;
                    }
                    else {
                          weight_jet+=GetWeight(info_b*2+1,quarkorigin,pt_val_jet,eta_val_jet);
                    }
                  }
              }



              if (method_b==0)  {
                // APPLY THE SCALE FACTOR
                if (discri_val>=btag_discri_) {
                   weight[0]*=weight_jet;
                }
                else {
                   //SF (notag) = (1-Eff_data)/(1-Eff_MC) = (1- SF * Eff_MC)/(1-Eff_MC)
                   if (eff_mc<1) weight[0]*=(1 - weight_jet*eff_mc)/(1-eff_mc);
                   else weight[0]*=1.;
                }
              }
              else {
                 // APPLY THE EFFICIENCY or SF*EFF
                 // ATTENTION : in that case, the Selection should stop at Step 6
                 if (method_b>=2) {
                    weight_jet*=eff_mc;
                   if (weight_jet>1.) weight_jet=1.;
                   if (weight_jet<0.) weight_jet=0.;
                 }
                 proba_jetb.push_back(weight_jet);
                 if (weight_jet<0) std::cout << " weight_jet " << weight_jet << " quark "<< quarkorigin 
                                   <<" eta " << eta_val_jet_orig << " pt " << pt_val_jet_orig
                                   << " eff_mc " << eff_mc << std::endl;
                 if (weight_jet>1) std::cout << " weight_jet " << weight_jet << " eta " << eta_val_jet << " pt " << pt_val_jet << std::endl;

              }



       }
       //         btag_nbjet;

       if (method_b>=1) {

           // combinatory
           float proba_0jet = 1.;
           float proba_1jet = 0.;
           float proba_2jet = 0.;
           float proba_atleast3jet = 0.;
           for (unsigned int ijet=0; ijet<proba_jetb.size(); ijet++) {
               proba_0jet *= (1-proba_jetb[ijet]);
               float pp1 = 1;
               for (unsigned int kjet=0; kjet<proba_jetb.size(); kjet++) {
                  if (kjet!=ijet) {
                      pp1 *= (1-proba_jetb[kjet]);
                   }

                   if (kjet>ijet) {
                       float pp2 = 1;
                       for (unsigned int ljet=0; ljet<proba_jetb.size(); ljet++) {
                          if (ljet!=ijet && ljet!=kjet) {
                             pp2 *= (1-proba_jetb[ljet]);
                           }
                        }
                        proba_2jet+=proba_jetb[ijet]*proba_jetb[kjet]*pp2;
                   }
               }
               proba_1jet+=proba_jetb[ijet]*pp1;
            }
            if(proba_jetb.size()>2) proba_atleast3jet= 1- proba_0jet - proba_1jet - proba_2jet;
            if (n_bjets_==0) {
              weight[0]*=1.;
            }
            else if (n_bjets_==1) {
              weight[0]*=1 - proba_0jet;
            }
            else if (n_bjets_==2) {
              weight[0]*=1 - proba_0jet - proba_1jet;
            }
            if (weight[0]<0)  {
                 // not good! :(
                 if (n_bjets_>0 && (proba_0jet<0 || proba_0jet>1 )) std::cout << " P0 " << proba_0jet << std::endl;
                 if (n_bjets_>1 && (proba_1jet<0 || proba_1jet>1 )) {
                       std::cout << " P1 " << proba_1jet << std::endl;
                 }
            }
            weight[1]=proba_0jet;
            weight[2]=proba_1jet;
            weight[3]=proba_2jet;
            weight[4]=proba_atleast3jet;

            if (weight[3]>1.) {
                 // not good! :(
                 std::cout << " weight[3]>1!!!??? " <<std::endl;
            }

       }


       return weight;


}


TH2D* SFBweight::GetHistoSFB(){
    return histo_sfvalb_;
}

#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"
const int kData = 0;
const int kSig  = 1;
const int kSBB  = 2;
const int kSumIso = 1;
const int k3dIso =  2;
const int kFisher = 3;

void getTemplate(TH1D* h1=0, TString fname1="forest/barrelHiForestPhoton_MCphoton50_25k.root", int isoChoice =kSumIso, int iTemp=kData, int lowCent=0, int highCent =3, TCut addCut="");

TCut getIsoCut( int isoChoice=0 ) {
   if         (isoChoice == kSumIso) return isoSumCut;
   else    if (isoChoice == k3dIso ) return iso3dCut;
   else    if (isoChoice == kFisher) return FisherCut;
   else   cout << "!!!!!!! No such isolation choice" << endl;
}

void photonTemplateProducer(int isoChoice = kSumIso) {
   
   
   TCanvas* c1  = new TCanvas("c1","",1000,700);
   makeMultiPanelCanvas(c1,3,2,0.0,0.0,0.2,0.15,0.02);
   
   TH1D* hData[5];
   TH1D* hSig[5];
   TH1D* hBkg[5];
   
   for ( int icent = 1 ; icent<=nCent_std ; icent++) { 
      int lowCent = centBin_std[icent-1];    
      int highCent = centBin_std[icent]-1;
      
      hData[icent]  = new TH1D(Form("hData_cent%d",icent),";shower shape (#sigma_{#eta#eta});Entries per photon candidate;",25,0,0.025);
      hSig[icent]   = (TH1D*)hData[icent]->Clone(Form("hSig_cent%d",icent));
      hBkg[icent]   = (TH1D*)hData[icent]->Clone(Form("hBkg_cent%d",icent));
	 
      getTemplate(hSig[icent],"barrelHiForestPhoton_MCphoton50_25k.root",isoChoice,kSig,lowCent,highCent);
      getTemplate(hData[icent],"barrelHiForestPhoton_Skim2011-Dec07-withTracks.root",isoChoice,kData,lowCent,highCent);
      getTemplate(hBkg[icent],"barrelHiForestPhoton_Skim2011-Dec07-withTracks.root",isoChoice,kSBB,lowCent,highCent);
      
   }
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      
      double nSig, nSigErr, chisq,purity10;
      c1->cd(nCent_std-icent+1);
      double purity = doFit ( hSig[icent], hBkg[icent], hData[icent], nSig, nSigErr, 0,0.025, (icent==3),chisq,purity10);
      cout << " purity = " << purity << endl;
      drawText(Form("%.0f % ~ %.0f %", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5980963,0.4569118);
      TString aa = "";
      if (isoChoice == kSumIso)  aa = "Sum Iso Method";
      if (isoChoice == k3dIso)   aa = "3d Cut Method";
      if (isoChoice == kFisher)  aa = "Fisher Method";
      
      if ( icent==2) drawText(aa.Data(),0.1980963,0.8569118,1,20);
 
   }   
   c1->cd(2*nCent_std);
   
   // efficiency plots
   const int nPtBin = 5;
   double ptBin[nPtBin+1] = {60,70,90,110,140,200};
   TH1D* heff[7][5];
   TGraphAsymmErrors* geff[7][5];
   for (int icent = 1; icent <=nCent_std; icent++) {
      for ( int iid=1 ; iid<=5; iid++) {
         heff[icent][iid] = new TH1D(Form("heff_icent%d_id%d",icent,iid),";Leading Photon E_{T} (GeV);",nPtBin, ptBin);
         geff[icent][iid] = new TGraphAsymmErrors();
         geff[icent][iid]->SetName(Form("geff_%s",heff[icent][iid]->GetName()));
      }
   }
   
   TCut srIsoCut = getIsoCut(isoChoice);
   int nId=0;
   for (int icent = 1; icent <=nCent_std; icent++) {
      int lowCent = centBin_std[icent-1];
      int highCent = centBin_std[icent]-1;
      TCut centCut      = Form("yEvt.hiBin >= %d && yEvt.hiBin<= %d",lowCent,highCent);
      nId=1;
      getEff(heff[icent][nId],geff[icent][nId],centCut, "swissCrx<0.90 && seedTime<4");
      nId++;
      getEff(heff[icent][nId],geff[icent][nId],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1");
      nId++;
      getEff(heff[icent][nId],geff[icent][nId],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1" && srIsoCut);
      nId++;
      getEff(heff[icent][nId],geff[icent][nId],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1 && sigmaIetaIeta<0.010"&& srIsoCut);
   }
   
   for (int icent = 1; icent <=nCent_std; icent++) {
      for ( int iid=1 ; iid<=nId ; iid++) {
         handsomeTH1(heff[icent][iid],color[iid]);
         handsomeTGraph(geff[icent][iid],color[iid]);
      }
   }
  
   TH1D* htmp = (TH1D*)heff[1][1]->Clone("htmp");
   htmp->Reset();
   htmp->SetAxisRange(0,1.3,"Y");
   htmp->SetYTitle("Efficiency");
   handsomeTH1(htmp);

   for (int icent = 1; icent <=nCent_std; icent++) {
      c1->cd(2*nCent_std - icent + 1);
      htmp->DrawCopy();
      for ( int iid=1 ; iid<=nId ; iid++) {
         heff[icent][iid]->Draw("p same");
         geff[icent][iid]->Draw("p");
	 
      }
      if ( icent == 3 )
         {
            TLegend* leg1 =  new TLegend(0.25,0.20,0.95,0.55,NULL,"brNDC");
            easyLeg(leg1,"Photon ID efficiency");
            leg1->AddEntry(heff[icent][1],"spike rejection","lp");
            leg1->AddEntry(heff[icent][2],"+ H/E < 0.2","lp");
            leg1->AddEntry(heff[icent][3],"+ Calo Isolation","lp");
            leg1->AddEntry(heff[icent][4],"+ #sigma_{#eta#eta} <0.010","lp");
            leg1->Draw();
         }
   }
   
   
}

void getTemplate(TH1D* h1, TString fname1, int isoChoice, int iTemp, int lowCent, int highCent, TCut addCut) { 
   
   TFile *f1  =new TFile(fname1.Data());
   TTree *photon1 = (TTree*)f1->Get("yongsunPhotonTree");
   photon1->AddFriend("yEvt=yongsunHiEvt"    ,fname1.Data());
   photon1->AddFriend("tgj",                   fname1.Data());
   
   TCut evtSelCut = "tgj.anaEvtSel";
   TCut centCut     = Form("(yEvt.hiBin >= %d) && (yEvt.hiBin<= %d)",lowCent,highCent);
   TCut photonJetCut  = "tgj.photonEt>60  &&  tgj.jetEt>30";
   TCut dphiCut= "acos(cos(tgj.photonPhi-tgj.jetPhi))>2.0944";
   TCut lPhotCut= "leading==1";
   
   TCut generalCutMC   = photonJetCut && dphiCut && lPhotCut && centCut && addCut; 
   TCut generalCutData = generalCutMC && evtSelCut;
   
   TCut sbIsoCut ="(cc4+cr4+ct4PtCut20)/0.9>6";
   TCut srIsoCut = getIsoCut(isoChoice);
   
   TCut finalCut="";
   if ( iTemp == kData ) 
      finalCut = generalCutData && srIsoCut ;
   if ( iTemp == kSig ) 
      finalCut = generalCutMC && genMatchCut1  && srIsoCut ; 
   if ( iTemp == kSBB )
      finalCut = generalCutData && sbIsoCut;
   
   h1->Reset();
   h1->Sumw2();
   TH1D* htemp = (TH1D*)h1->Clone("htemp");
   photon1->Draw(Form("sigmaIetaIeta>>%s",htemp->GetName()),finalCut);
   h1->Add(htemp);
   htemp->Reset();
   
}

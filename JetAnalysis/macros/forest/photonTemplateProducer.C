#include "CutAndBinCollection2011.h"
#include "photonIDEfficiency.C"
const int kData =  0;
const int kSig  =  1;
const int kSBB  =  2;
const int kMCBsr = 3;
const int kMCBsb = 4;

const int kSumIso = 1;
const int k3dIso =  2;
const int kFisher = 3;
const int kNoIso  = 4;
void getTemplate(TH1D* h1=0, TString fname1="forest/barrelHiForestPhoton_MCphoton50_25k.root", int isoChoice =kSumIso, int iTemp=kData, int lowCent=0, int highCent =3, TCut addCut="");

TCut getIsoCut( int isoChoice=0 ) {
   if         (isoChoice == kSumIso) return isoSumCut;
   else    if (isoChoice == k3dIso ) return iso3dCut;
   else    if (isoChoice == kFisher) return FisherCut;
   else    if (isoChoice == kNoIso) return "";
   else   cout << "!!!!!!! No such isolation choice" << endl;
}
TString getIsoLabel ( int isoChoice=0) {
   if ( isoChoice == kSumIso) return "sumIso";
   if ( isoChoice == k3dIso)  return "3dIso";
   if ( isoChoice == kFisher) return "fisherIso";
   else   cout << "!!!!!!! No such isolation choice" << endl;
}
void photonTemplateProducer(int isoChoice = kSumIso) {
   
   
   TCanvas* c1  = new TCanvas("c1","",1000,400);
   makeMultiPanelCanvas(c1,3,1,0.0,0.0,0.2,0.15,0.02);
   
   TH1D* hData[5];
   TH1D* hSig[5];
   TH1D* hBkg[5];
   
   TH1D* hPurity = new TH1D(Form("hPurity_%s",getIsoLabel(isoChoice).Data()),";Cent Bin;purity",3,0.5,3.5);
   TH1D* hNsig   = (TH1D*)hPurity->Clone(Form("hNsig_%s",getIsoLabel(isoChoice).Data()));
   hNsig->SetYTitle("number of signals");
   TH1D* hEff   = (TH1D*)hPurity->Clone(Form("hEff_%s",getIsoLabel(isoChoice).Data()));
   hEff->SetYTitle("Calo Iso Efficiency");
   
   TH1D* hN   = (TH1D*)hPurity->Clone(Form("hN_%s",getIsoLabel(isoChoice).Data()));
   hN->SetYTitle("Efficiency corrected photon counts");
   hN->Sumw2();

   
   TH1D* htemp3 = new TH1D("htemp3","",25,0,0.250);
   getTemplate(htemp3,"barrelHiForestPhotonV3.root",kNoIso ,kData,0,39);
   
   for ( int icent = 1 ; icent<=nCent_std ; icent++) { 
      int lowCent = centBin_std[icent-1];    
      int highCent = centBin_std[icent]-1;
      
      hData[icent]  = new TH1D(Form("hData_cent%d",icent),";shower shape (#sigma_{#eta#eta});Entries per photon candidate;",25,0,0.025);
      hSig[icent]   = (TH1D*)hData[icent]->Clone(Form("hSig_cent%d",icent));
      hBkg[icent]   = (TH1D*)hData[icent]->Clone(Form("hBkg_cent%d",icent));
	 
      getTemplate(hSig[icent],"meaningless",isoChoice,kSig,lowCent,highCent);
      getTemplate(hData[icent],"barrelHiForestPhotonV3.root",isoChoice,kData,lowCent,highCent);
      getTemplate(hBkg[icent], "barrelHiForestPhotonV3.root",isoChoice,kMCBsb,lowCent,highCent);
      
   }
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      
      double nSig, nSigErr, chisq,purity10;
      c1->cd(nCent_std-icent+1);
      fitResult fitr = doFit ( hSig[icent], hBkg[icent], hData[icent], nSig, nSigErr, 0.005,0.018, (icent==3),chisq,purity10);
      cout << " purity = " << fitr.purity010 << endl;
      cout << " nSig   = " << fitr.nSig << endl;
      drawText(Form("%.0f % ~ %.0f %", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.4569118);
      if ( icent == 3) 
	 drawText(Form("Purity(#sigma_{#eta#eta} < 0.01) : %.0f%%", (float)fitr.purity010*100),0.5680963,0.3569118,1,15);
      else 
	 drawText(Form("Purity(#sigma_{#eta#eta} < 0.01) : %.0f%%", (float)fitr.purity010*100),0.4680963,0.3569118,1,15);
      hPurity->SetBinContent(icent, fitr.purity010);
      hPurity->SetBinError  (icent, fitr.purity010* fitr.nSigErr/fitr.nSig);
      hNsig->SetBinContent(icent, fitr.nSig);
      hNsig->SetBinError  (icent, fitr.nSigErr);

      TString aa = "";
      if (isoChoice == kSumIso)  aa = "Sum Iso Method";
      if (isoChoice == k3dIso)   aa = "3d Cut Method";
      if (isoChoice == kFisher)  aa = "Fisher Method";
      
      if ( icent==2) drawText(aa.Data(),0.1980963,0.8569118,1,20);
      
      
      if ( icent!=3) drawPatch(0,0,0.05,0.14,0,1001,"NDC");
      drawPatch(0.9,0.05,1.01,0.14,0,1001,"NDC");
   }   


   TCanvas* c2  = new TCanvas("c2","",1000,400);
   makeMultiPanelCanvas(c2,3,1,0.0,0.0,0.2,0.15,0.02);

   
   // efficiency plots
   const int nPtBin = 3;
   double ptBin[nPtBin+1] = {60,80,110,200};
   TH1D* heff[7][5];
   TH1D* effSingleBin = new TH1D("effSingleBin","",1,60,100000);
   TGraphAsymmErrors* geff[7][5];
   TGraphAsymmErrors* gSingleBin = new TGraphAsymmErrors();

   for (int icent = 1; icent <=nCent_std; icent++) {
      for ( int iid=1 ; iid<=5; iid++) {
         heff[icent][iid] = new TH1D(Form("heff_icent%d_id%d",icent,iid),";photon E_{T} (GeV);Efficiency",nPtBin, ptBin);
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
      effSingleBin->Reset();
      getEff(effSingleBin, gSingleBin, centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1" && srIsoCut);
      hEff->SetBinContent(icent, effSingleBin->GetBinContent(1));
      hEff->SetBinError(icent,0.05);
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
      c2->cd(nCent_std - icent + 1);
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
            leg1->AddEntry(heff[icent][2],"+ H/E < 0.1","lp");
            leg1->AddEntry(heff[icent][3],"+ Calo Isolation","lp");
            leg1->AddEntry(heff[icent][4],"+ #sigma_{#eta#eta} <0.010","lp");
            leg1->Draw();
         }

      if ( icent!=3) drawPatch(0,0,0.05,0.14,0,1001,"NDC");
      drawPatch(0.9,0.05,1.01,0.14,0,1001,"NDC");
   }
   c1->SaveAs(Form("fittingPurity_%s.eps",getIsoLabel(isoChoice).Data()));
   c1->SaveAs(Form("fittingPurity_%s.gif",getIsoLabel(isoChoice).Data()));
   c2->SaveAs(Form("photonID_efficiency_%s.eps",getIsoLabel(isoChoice).Data()));
   c2->SaveAs(Form("photonID_efficiency_%s.gif",getIsoLabel(isoChoice).Data()));
  
   TCanvas* c3 = new TCanvas("cPurity","",1000,500);
   c3->Divide(2,1);
   c3->Draw();
   c3->cd(1);
   handsomeTH1(hPurity);
   hPurity->SetAxisRange(0,1.1,"Y");
   hPurity->Draw();
   handsomeTH1(hEff,2);
   hEff->Draw("same");

   c3->cd(2);
   hN->Reset();
   hN->Add(hNsig);
   hN->Divide(hEff);
   hN->Draw();
   
   c3->SaveAs(Form("crossSection_%s.gif",getIsoLabel(isoChoice).Data()));
   TFile outf = TFile("photonPurityCollection.root","update");
   hN->Write();
   hEff->Write();
   hPurity->Write();
   outf.Close();
   
   
}

void getTemplate(TH1D* h1, TString fname1, int isoChoice, int iTemp, int lowCent, int highCent, TCut addCut) { 
 
   char* fnamePho50 = "barrelHiForestPhoton_MCphoton50_51k.root";
   float nEvtPho50     = 50720;
   char* fnamePho80 = "barrelHiForestPhoton_MCphoton80_26k.root";
   float nEvtPho80     = 26000;


   char* fnameEmj80 = "barrelHiForestPhoton_MCemJet800_60k.root";
   char* fnameEmj120 = "barrelHiForestPhoton_MCemJet120_14k.root";
   double csDij80 = 9.869e-5;
   float nEvtEmj80     = 60000;
   float effEmj80     = 0.204;
   float weightEmj80 = csDij80*effEmj80/nEvtEmj80;
   float nEvtEmj120     = 14000;
   double csDij120 = 1.127e-5;
   float effEmj120     = 0.54;
   float weightEmj120 = csDij120*effEmj120/nEvtEmj120;
   
   char* fnameData  = "barrelHiForestPhoton_Skim2011-Dec07-withTracks.root";
   
   TCut evtSelCut = "tgj.anaEvtSel";
   TCut centCut     = Form("(yEvt.hiBin >= %d) && (yEvt.hiBin<= %d)",lowCent,highCent);
   TCut photonJetCut  = "tgj.photonEt>60  &&  tgj.jetEt>30";
   TCut dphiCut= "acos(cos(tgj.photonPhi-tgj.jetPhi))>2.0944";
   TCut lPhotCut= "leading==1";
   TCut generalCutMC   = photonJetCut && dphiCut && lPhotCut && centCut && addCut;
   TCut generalCutData = generalCutMC && evtSelCut;
   
   TCut sbIsoCut ="(cc4+cr4+ct4PtCut20)/0.9>6 && (cc4+cr4+ct4PtCut20)/0.9 < 11 ";
   TCut srIsoCut = getIsoCut(isoChoice);

   TCut finalCut="";
   if ( iTemp == kData )
      finalCut = generalCutData && srIsoCut ;
   if ( iTemp == kSig )
      finalCut = generalCutMC && genMatchCut1  && srIsoCut ;
   if ( iTemp == kSBB )
      finalCut = generalCutData && sbIsoCut;
   if ( iTemp == kMCBsr )
      finalCut = generalCutMC && srIsoCut;
   if ( iTemp == kMCBsb )
      finalCut = generalCutMC && sbIsoCut;

   multiTreeUtil* photon1 = new multiTreeUtil();
   
   float csPho50 = 6.663e-7;
   float csPho80 = 8.731e-8;
   float weightPho50 = csPho50/nEvtPho50;
   float weightPho80 = csPho80/nEvtPho80;
   
   TString weightBit = "";
   if ( iTemp  == kSig) {
      photon1->addFile( fnamePho50,  "yongsunPhotonTree", "" , weightPho50);
      photon1->addFile( fnamePho80,  "yongsunPhotonTree", "" , weightPho80);
      weightBit = "ncoll";
   }
   else if ( (iTemp == kSBB) || (iTemp == kData)) {
      // if this is data
      photon1->addFile( fname1 , "yongsunPhotonTree", "" ,1);
      weightBit = "";
   }
   
   else if ( (iTemp == kMCBsr) || (iTemp == kMCBsb)){
      photon1->addFile(fnameEmj80,  "yongsunPhotonTree", "" , weightEmj80);
      photon1->addFile(fnameEmj120, "yongsunPhotonTree", "" , weightEmj120);
      weightBit = "ncoll";
   }
   
   
   
   photon1->AddFriend("yEvt=yongsunHiEvt");
   photon1->AddFriend("tgj");
   
   
   h1->Reset();
   h1->Sumw2();
   TH1D* htemp = (TH1D*)h1->Clone("htemp");
   htemp->Reset();
   htemp->Sumw2();
   photon1->Draw2(htemp,  "sigmaIetaIeta",   finalCut,  weightBit);
   TH1D* hcBins = new TH1D("hncoll","",40,-.5,39.5);
   if ( iTemp == kData ) {
      cout << "Data entries = "<<  htemp->Integral() << endl;
      cout << "cut = " << finalCut.GetTitle() <<  endl;
      photon1->Draw2(hcBins,  "yEvt.hiBin",   finalCut);
   }
   
   h1->Add(htemp);
   htemp->Reset();
   
      
   delete photon1;
   
   
}

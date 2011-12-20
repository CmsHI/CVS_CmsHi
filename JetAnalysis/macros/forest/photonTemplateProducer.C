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
const int kSumIso2= 5;
void getTemplate(TH1D* h1=0, TString fname1="forest/barrelHiForestPhoton_MCphoton50_25k.root", int isoChoice =kSumIso, float isoCut=-100, int iTemp=kData, int lowCent=0, int highCent =3, TCut addCut="",bool onlygjEvents=true);

TCut getIsoCut( int isoChoice=0, float isoCut = -100 ) {
   
   if ( (isoChoice== kSumIso2) && ( isoCut > -99))
      return Form("(cc4+cr4+ct4PtCut20)/0.9 < %f",isoCut);
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
   if ( isoChoice == kSumIso2) return "sumIso";
   
   else   cout << "!!!!!!! No such isolation choice" << endl;
}
void photonTemplateProducer(int isoChoice = kSumIso, int isoCut = -100, bool onlygjEvents=true) {
   

   TCanvas* c1[5];
    
   TH1D* hData[5][5];
   TH1D* hSig[5][5];
   TH1D* hBkg[5][5];
   
   TH1D* hBkgMCsr[5][5];
   TH1D* hBkgMCsb[5][5];

   TH1D* rawSpectra[5];
   TH1D* finSpectra[5];
   for ( int icent = 1 ; icent<=nCent_std ; icent++) {
      rawSpectra[icent] = new TH1D(Form("rawSpec_icent%d_%s",icent,getIsoLabel(isoChoice).Data()),"",nPtBin,ptBin);
   }
   
   
   
   TH1D* hPurity = new TH1D(Form("hPurity_%s",getIsoLabel(isoChoice).Data()),";Cent Bin;purity",3,0.5,3.5);
   TH1D* hNsig   = (TH1D*)hPurity->Clone(Form("hNsig_%s",getIsoLabel(isoChoice).Data()));
   hNsig->SetYTitle("number of signals");
   TH1D* hEff   = (TH1D*)hPurity->Clone(Form("hEff_%s",getIsoLabel(isoChoice).Data()));
   hEff->SetYTitle("Calo Iso Efficiency");
   
   TH1D* hN   = (TH1D*)hPurity->Clone(Form("hN_%s",getIsoLabel(isoChoice).Data()));
   hN->SetYTitle("Efficiency corrected photon counts");
   hN->Sumw2();

   
   for (int ipt = 1; ipt <= nPtBin ; ipt++) { 
      c1[ipt] = new TCanvas(Form("c1_ipt%d",ipt),"",700,700);
      makeMultiPanelCanvas(c1[ipt],nCent_std/2,2,0.0,0.0,0.2,0.15,0.02);
      
      TCut ptCut = Form("corrPt>%.2f && corrPt<%.2f",(float)ptBin[ipt-1],(float)ptBin[ipt]); 
      for ( int icent = 1 ; icent<=nCent_std ; icent++) { 
	 int lowCent = centBin_std[icent-1];    
	 int highCent = centBin_std[icent]-1;
	 
	 hData[icent][ipt]  = new TH1D(Form("hData_cent%d_pt%d",icent,ipt),";shower shape (#sigma_{#eta#eta});Entries per photon candidate;",25,0,0.025);
	 hSig[icent][ipt]   = (TH1D*)hData[icent][ipt]->Clone(Form("hSig_cent%d_pt%d",icent,ipt));
	 hBkg[icent][ipt]   = (TH1D*)hData[icent][ipt]->Clone(Form("hBkg_cent%d_pt%d",icent,ipt));
	 hBkgMCsr[icent][ipt] = (TH1D*)hData[icent][ipt]->Clone(Form("hBkgMCsr_cent%d_pt%d",icent,ipt));
	 hBkgMCsb[icent][ipt] =(TH1D*)hData[icent][ipt]->Clone(Form("hBkgMCsb_cent%d_pt%d",icent,ipt));

	 getTemplate(hSig[icent][ipt],"meaningless",isoChoice,isoCut, kSig,lowCent,highCent,ptCut,onlygjEvents);
	 getTemplate(hData[icent][ipt],"barrelHiForestPhotonV5.root",isoChoice,isoCut, kData,lowCent,highCent,ptCut,onlygjEvents);
	 getTemplate(hBkg[icent][ipt], "barrelHiForestPhotonV5.root",isoChoice,isoCut, kSBB,lowCent,highCent,ptCut,onlygjEvents);
	 
	 // getTemplate(hBkg[icent][ipt], "barrelHiForestPhotonV3.root",isoChoice,kMCBsr,lowCent,highCent,ptCut,onlygjEvents);
	 
      }
      for ( int icent = 1 ; icent<=nCent_std ; icent++) {
	 int lowerCent = centBin_std[icent-1];
	 int upperCent = centBin_std[icent]-1;
	 

	 double nSig, nSigErr, chisq,purity10;
	 c1[ipt]->cd(nCent_std-icent+1);
	 fitResult fitr = doFit ( hSig[icent][ipt], hBkg[icent][ipt], hData[icent][ipt], nSig, nSigErr, 0.005,0.025, (icent==nCent_std),chisq,purity10);
	 cout << " purity = " << fitr.purity010 << endl;
	 cout << " nSig   = " << fitr.nSig << endl;
	 if ( ptBin[ipt]> 200)
	    drawText(Form(" E_{T}^{#gamma} > %d GeV", (int)ptBin[ipt-1]),0.5680963,0.529118);
	 else
	    drawText(Form("%d - %d GeV", (int)ptBin[ipt-1], (int)ptBin[ipt]),0.5680963,0.529118);
	 drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.4369118);
	 
	 //      TCut ptCut = Form("corrPt>%.2f && corrPt<%.2f",(float)ptBin[ipt-1],(float)ptBin[ipt]);
	 
	 if ( (icent == nCent_std) || (icent == 2)) 
	 drawText(Form("Purity(#sigma_{#eta#eta} < 0.01) : %.0f%%", (float)fitr.purity010*100),0.5680963,0.3569118,1,15);
	 else 
	    drawText(Form("Purity(#sigma_{#eta#eta} < 0.01) : %.0f%%", (float)fitr.purity010*100),0.4680963,0.3569118,1,15);
	 drawText(Form("#pm %.0f%% (stat)", float( 100. * fitr.purity010 * (float)fitr.nSigErr / (float)fitr.nSig ) ),0.6680963,0.2869118,1,15);
	 
	 hPurity->SetBinContent(icent, fitr.purity010);
	 hPurity->SetBinError  (icent, fitr.purity010* fitr.nSigErr/fitr.nSig);
	 //	 hNsig->SetBinContent(icent, fitr.nSig);
	 //	 hNsig->SetBinError  (icent, fitr.nSigErr);
	 rawSpectra[icent]->SetBinContent( ipt, fitr.nSig);
	 rawSpectra[icent]->SetBinError(   ipt,fitr.nSigErr);

	 TString aa = "";
	 if (isoChoice == kSumIso)  aa = "Sum Iso Method";
	 if (isoChoice == k3dIso)   aa = "3d Cut Method";
	 if (isoChoice == kFisher)  aa = "Fisher Method";
	 
	 if ( icent==nCent_std -1) drawText(aa.Data(),0.1980963,0.8569118,1,20);
	 
	 
	 if ( icent<= 2) drawPatch(0,0,0.05,0.14,0,1001,"NDC");
	 //	 drawPatch(0.9,0.05,1.01,0.14,0,1001,"NDC");
      }   
      
      c1[ipt]->SaveAs(Form("fittingPurity_%s_pt%d.pdf",getIsoLabel(isoChoice).Data(),ipt));
      
   }
   
   
   // efficiency plots          
   TCanvas* c2  = new TCanvas("c2","",700,700); //100 + nCent_std*300,400);
   makeMultiPanelCanvas(c2,nCent_std/2,2,0.0,0.0,0.2,0.15,0.02);
   
   //   const int nPtBin = 3;
   //   double ptBin[nPtBin+1] = {60,80,110,200};
   TH1D* heff[7][5];
   TH1D* effSingleBin = new TH1D("effSingleBin","",1,60,100000);
   TGraphAsymmErrors* geff[7][5];
   TGraphAsymmErrors* gSingleBin = new TGraphAsymmErrors();

   for (int icent = 1; icent <=nCent_std; icent++) {
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      for ( int iid=1 ; iid<=5; iid++) {
         heff[icent][iid] = new TH1D(Form("heff_icent%d_id%d",icent,iid),";photon E_{T} (GeV);Efficiency",nPtBin, ptBin);
         geff[icent][iid] = new TGraphAsymmErrors();
         geff[icent][iid]->SetName(Form("geff_%s",heff[icent][iid]->GetName()));
      }
   }
   
   TCut srIsoCut = getIsoCut(isoChoice,isoCut);
   int nId=4;
   for (int icent = 1; icent <=nCent_std; icent++) {
      int lowCent = centBin_std[icent-1];
      int highCent = centBin_std[icent]-1;
      TCut centCut      = Form("yEvt.hiBin >= %d && yEvt.hiBin<= %d",lowCent,highCent);
      getEff(heff[icent][1],geff[icent][1],centCut, "swissCrx<0.90 && seedTime<4");
      getEff(heff[icent][2],geff[icent][2],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1");
      getEff(heff[icent][3],geff[icent][3],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1" && srIsoCut);
      getEff(heff[icent][4],geff[icent][4],centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1 && sigmaIetaIeta<0.010"&& srIsoCut);
      effSingleBin->Reset();
      getEff(effSingleBin, gSingleBin, centCut, "swissCrx<0.90 && seedTime<4 && hadronicOverEm<0.1" && srIsoCut);
      hEff->SetBinContent(icent, effSingleBin->GetBinContent(1));
      hEff->SetBinError(icent,0.05);
      for (int ipt = 1 ; ipt<=nPtBin ; ipt++) 
	 heff[icent][3]->SetBinError(ipt,0);
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
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      c2->cd(nCent_std - icent + 1);
      htmp->DrawCopy();
      for ( int iid=1 ; iid<=nId ; iid++) {
         heff[icent][iid]->Draw("p same");
         geff[icent][iid]->Draw("p");
	 
      }
      if ( icent == nCent_std )
         {
            TLegend* leg1 =  new TLegend(0.25,0.20,0.95,0.55,NULL,"brNDC");
            easyLeg(leg1,"Photon ID efficiency");
            leg1->AddEntry(heff[icent][1],"spike rejection","lp");
            leg1->AddEntry(heff[icent][2],"+ H/E < 0.1","lp");
            leg1->AddEntry(heff[icent][3],"+ Calo Isolation","lp");
            leg1->AddEntry(heff[icent][4],"+ #sigma_{#eta#eta} <0.010","lp");
            leg1->Draw();
         }
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.5680963,0.8369118);
      if ( icent<=2) drawPatch(0,0,0.05,0.14,0,1001,"NDC");
      //  drawPatch(0.9,0.05,1.01,0.14,0,1001,"NDC");
      
   }
   //   c1[ipt]->SaveAs(Form("fittingPurity_%s.eps",getIsoLabel(isoChoice).Data()));
   //  c2[ipt]->SaveAs(Form("photonID_efficiency_%s.eps",getIsoLabel(isoChoice).Data()));
   //  c2[ipt]->SaveAs(Form("photonID_efficiency_%s.gif",getIsoLabel(isoChoice).Data()));

   c2->SaveAs(Form("photonID_efficiency_%s.pdf",getIsoLabel(isoChoice).Data()));  
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
   
   
   TCanvas* c4 = new TCanvas("efficienycCorrection","",1000,500);
   c4->Divide(2,1);
   c4->cd(1);
   for (int icent = 1; icent <=nCent_std; icent++) {
      TH1ScaleByWidth(rawSpectra[icent]);    // divide by width
      finSpectra[icent] = (TH1D*)rawSpectra[icent]->Clone(Form("finSpec_icent%d_%s",icent,getIsoLabel(isoChoice).Data()));
      if ( isoChoice == kSumIso2)
	 finSpectra[icent]->SetName(Form("finSpec_icent%d_%s_isoCut%d",icent,getIsoLabel(isoChoice).Data(),(int)isoCut));
      
      finSpectra[icent]->Divide(heff[icent][3]);
   }
   handsomeTH1(finSpectra[1],1);
   handsomeTH1(finSpectra[2],2);
   handsomeTH1(finSpectra[3],4);
   handsomeTH1(finSpectra[4],6);
  // TAA and centrality 
   finSpectra[1]->Scale( 1 / (0.1*taa[1]));
   finSpectra[2]->Scale( 1 / (0.2*taa[2]));
   finSpectra[3]->Scale( 1 / (0.2*taa[3]));
   finSpectra[4]->Scale( 1 / (0.5*taa[4]));

   finSpectra[1]->SetXTitle("E_{T} (GeV)");
   finSpectra[1]->SetYTitle("Photon Yield / T_{AA} (Arbitrary Unit)");
   
   finSpectra[1]->SetAxisRange(1.e8,1.e11,"Y");
   finSpectra[1]->Draw();
   finSpectra[2]->Draw("same");
   finSpectra[3]->Draw("same");
   finSpectra[4]->Draw("same");
   jumSun(60,1.e8,60,1.e11,2);

   TLegend* leg2 =  new TLegend(0.458871,0.6440678,0.9919355,0.8707627,NULL,"brNDC");
   easyLeg(leg2,"dN/dE_{T} of isolated photons");
   leg2->AddEntry(finSpectra[1],"0-10%","pl");
   leg2->AddEntry(finSpectra[2],"10-30%","pl");
   leg2->AddEntry(finSpectra[3],"30-50%","pl");
   leg2->AddEntry(finSpectra[4],"50-100%","pl");
   leg2->Draw();


   gPad->SetLogy();
   //   gPad->SetLogx();

   c4->cd(2);
   TH1D* finSpectraMB = (TH1D*)finSpectra[1]->Clone("finSpectraMB");
   finSpectraMB->Reset();
   finSpectraMB->Add( finSpectra[1], taa[1]*0.1);
   finSpectraMB->Add( finSpectra[2], taa[2]*0.2);
   finSpectraMB->Add( finSpectra[3], taa[3]*0.2);
   finSpectraMB->Add( finSpectra[4], taa[4]*0.5);
   finSpectraMB->Scale(1./(taa[1]*0.1+ taa[2]*0.2 + taa[3]*0.2 + taa[4]*0.5));
   TH1D* finSpectraR[10];
   for ( int icent =1 ; icent<= nCent_std; icent++) {
      finSpectraR[icent] = (TH1D*)finSpectra[icent]->Clone(Form("finSpectraR_icent%d",icent));
      finSpectraR[icent]->Divide(finSpectraMB);
   }
   finSpectraR[1]->SetYTitle("dN/dE_{T} / dN/dE_{T}^{MB} after T_{AA} scaling"); 
   finSpectraR[1]->SetAxisRange(0,2,"Y");
   finSpectraR[1]->Draw();
   finSpectraR[2]->Draw("same");
   finSpectraR[3]->Draw("same");
   finSpectraR[4]->Draw("same");
   jumSun(60,0,60,2,2);
   c4->SaveAs("taaScaling.pdf");

   TCanvas* c5 = new TCanvas("c5","",700,700);
   makeMultiPanelCanvas(c5,nCent_std/2,2,0.0,0.0,0.2,0.15,0.02);
   for (int icent = 1; icent <=nCent_std; icent++) {
      int lowCent = centBin_std[icent-1];
      int highCent = centBin_std[icent]-1;
      getTemplate(hBkgMCsr[icent][1], "meaningless",isoChoice,isoCut,kMCBsr,lowCent,highCent,"corrPt>60",onlygjEvents);
      getTemplate(hBkgMCsb[icent][1], "meaningless",isoChoice,isoCut,kMCBsb,lowCent,highCent,"corrPt>60",onlygjEvents);
      handsomeTH1(hBkgMCsb[icent][1],2);
      handsomeTH1(hBkgMCsr[icent][1],1);
      scaleInt(hBkgMCsb[icent][1]);
      scaleInt(hBkgMCsr[icent][1]);
   }
   for (int icent = 1; icent <=nCent_std; icent++) {
      int lowerCent = centBin_std[icent-1];
      int upperCent = centBin_std[icent]-1;
      c5->cd(nCent_std - icent+1);
      hBkgMCsb[icent][1]->SetAxisRange(0,0.4,"Y");
      hBkgMCsb[icent][1]->SetYTitle("Event Fraction");
      hBkgMCsb[icent][1]->Draw("hist");
      hBkgMCsr[icent][1]->Draw("same");
      drawText(Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),0.3680963,0.8369118);
      if (  icent == nCent_std) {
	 TLegend* leg1 =  new  TLegend(0.5977464,0.6159073,0.9986159,0.8138776,NULL,"brNDC");
	 easyLeg(leg1,"MC Bkg template");
	 leg1->AddEntry(hBkgMCsr[icent][1],"signal region","pl");
	 leg1->AddEntry(hBkgMCsb[icent][1],"side-band","l");
	 leg1->Draw();
      }
   }
   
   c5->SaveAs(Form("backgroundTemplateInMC_%s.pdf",getIsoLabel(isoChoice).Data()));   

   c3->SaveAs(Form("crossSection_%s.gif",getIsoLabel(isoChoice).Data()));
   TFile outf = TFile("photonPurityCollection.root","update");
   hN->Write();
   hEff->Write();
   hPurity->Write();
   for ( int icent =1 ; icent<=nCent_std ; icent++) {
      finSpectra[icent]->Write();
   }
   outf.Close();

   
   
   
   
}

void getTemplate(TH1D* h1, TString fname1, int isoChoice, float isoCut, int iTemp, int lowCent, int highCent, TCut addCut,bool onlygjEvents) { 
 
   char* fnamePho50 = "barrelHiForestPhoton_MCphoton50_37k.root";
   float nEvtPho50     = 37188;
   char* fnamePho80 = "barrelHiForestPhoton_MCphoton80_25k.root";
   float nEvtPho80     = 25308;


   char* fnameEmj80 = "barrelHiForestPhoton_MCemJet80_41007events.root";
   char* fnameEmj120 = "barrelHiForestPhoton_MCemJet120_25308events.root";
   char* fnameEmj80_cent10 = "barrelHiForestPhoton_emJet80_cent10_10016evnts.root";
   char* fnameEmj120_cent10 = "barrelHiForestPhoton_emJet120_cent10_9540Evts.root";

   
   double csDij80 = 9.869e-5;
   float nEvtEmj80     = 41007;
   float effEmj80     = 0.204;
   float weightEmj80 = csDij80*effEmj80/nEvtEmj80;
   float nEvtEmj120     = 25308;
   double csDij120 = 1.127e-5;
   float effEmj120     = 0.54;
   float weightEmj120 = csDij120*effEmj120/nEvtEmj120;
   
   float nEvtEmj80_cent10      = 9540;
   float nEvtEmj120_cent10     = 10016;
   float weightEmj80_cent10 = csDij80*effEmj80/nEvtEmj80_cent10;
   float weightEmj120_cent10 = csDij120*effEmj120/nEvtEmj120_cent10;
   
   
   TCut evtSelCut = "tgj.anaEvtSel";
   TCut centCut     = Form("(yEvt.hiBin >= %d) && (yEvt.hiBin<= %d)",lowCent,highCent);
   TCut photonJetCut  = "tgj.photonEt>50  &&  tgj.jetEt>30";
   TCut dphiCut= "acos(cos(tgj.photonPhi-tgj.jetPhi))>2.0944";
   TCut lPhotCut= "leading==1";
   TCut generalCutMC   = lPhotCut && centCut && addCut;
   if (onlygjEvents)
      generalCutMC = generalCutMC && photonJetCut && dphiCut;
    
   TCut generalCutData = generalCutMC && evtSelCut;

   TCut srIsoCut = getIsoCut(isoChoice,isoCut);

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
      weightBit = "tgj.reweight";
   }
   else if ( (iTemp == kSBB) || (iTemp == kData)) {
      // if this is data
      photon1->addFile( fname1 , "yongsunPhotonTree", "" ,1);
      weightBit = "";
   }
   
   else if ( (iTemp == kMCBsr) || (iTemp == kMCBsb)){
      photon1->addFile(fnameEmj80,  "yongsunPhotonTree", "" , weightEmj80);
      photon1->addFile(fnameEmj120, "yongsunPhotonTree", "" , weightEmj120);
      photon1->addFile(fnameEmj80_cent10,  "yongsunPhotonTree", "yEvt.hiBin<4" , weightEmj80_cent10);
      photon1->addFile(fnameEmj120_cent10,  "yongsunPhotonTree", "yEvt.hiBin<4" , weightEmj120_cent10);
      weightBit = "tgj.reweight";
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

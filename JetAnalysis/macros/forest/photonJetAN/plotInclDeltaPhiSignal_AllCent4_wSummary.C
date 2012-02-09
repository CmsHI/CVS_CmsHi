#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"

#include "commonUtility.h"
#include "SignalCorrector.h"
#include "npart.h"
#endif

TString outfname;

//---------------------------------------------------------------------
void getHistograms(vector<SignalCorrector*> & vana,
                   vector<TCut> vcutCent, TCut mycut, int isolScheme, int normMode,
                   TString infname,
                   TString weight,
                   int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                   int dataType, // 0=mc gen, 1=reco
                   int subDPhiSide = 1,
                   int subSShapeSide = 1,
                   float minPhoton=60,
                   float minJet=30,
                   float sigDPhi=2.0944
                   )
{
   // open the data file
   TFile *inf = TFile::Open(infname);
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << endl << "# " << endl;
   cout << "# " << infname << ": useWeight: " << weight << " dataSrcType: " << dataSrcType << " photon: " << minPhoton << " jet: " << minJet << endl;
   cout << "# " << endl;

   TString mixfname="../output-data-Photon-v7_v24mixmb_akPu3PF.root";
   bool doMixBkg=true;
   if (doMixBkg) nt->AddFriend("tmix=tgj",mixfname);
   
   // loop over centrality bins
   for (int ib=0; ib<vcutCent.size(); ++ib) {
      TString name = Form("dataSrc%d_reco%d_cent%d",dataSrcType,dataType,ib);
      int cBin = ib;
      if (dataSrcType>1) cBin==vcutCent.size()-1;
      vana.push_back(new SignalCorrector(nt,name,"acos(cos(photonPhi-inclJetPhi))",Form("photonEt>%.3f",minPhoton)&&mycut&&vcutCent[ib],weight,cBin,dataSrcType));
      vana[ib]->cutBkgDPhi= Form("inclJetPt>%.3f&&acos(cos(photonPhi-inclJetPhi))>0.7 && acos(cos(photonPhi-inclJetPhi))<3.14159/2. && sigmaIetaIeta<0.01",minJet);
      vana[ib]->cutSShape= Form("inclJetPt>%.3f&&acos(cos(photonPhi-inclJetPhi))>%f && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet,sigDPhi);
      vana[ib]->cutSShapeDPhi= Form("inclJetPt>%.3f&&acos(cos(photonPhi-inclJetPhi))>0.7 && acos(cos(photonPhi-inclJetPhi))<3.14159/2. && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet);
      if (doMixBkg) {
         vana[ib]->cutBkgDPhi= Form("tmix.inclJetPt>%.03f && acos(cos(photonPhi-tmix.inclJetPhi))>%f && sigmaIetaIeta<0.01",minJet,sigDPhi);
         vana[ib]->cutSShapeDPhi= Form("tmix.inclJetPt>%.03f && acos(cos(photonPhi-tmix.inclJetPhi))>%f && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017",minJet,sigDPhi);
         vana[ib]->rBkgDPhi.var = "acos(cos(photonPhi-tmix.inclJetPhi))";
         vana[ib]->rBkgSShapeDPhi.var = "acos(cos(photonPhi-tmix.inclJetPhi))";
      }

      // analyze tree
      if (doMixBkg&&dataSrcType>1) {
         subDPhiSide = false;
      }
      if (dataType==0) {
         vana[ib]->subDPhiSide = false;
         vana[ib]->subSShapeSide = false;
         vana[ib]->subSShapeSideDPhiSide = false;
         vana[ib]->MakeHistograms(Form("inclJetPt>%.03f && acos(cos(photonPhi-inclJetPhi))>%f",minJet,sigDPhi),20,0.0001,3.1415926);
      } else {
         vana[ib]->subDPhiSide = subDPhiSide;
         vana[ib]->subSShapeSide = subSShapeSide;
         vana[ib]->subSShapeSideDPhiSide = subDPhiSide&&subSShapeSide;
         vana[ib]->SetPhotonIsolation(isolScheme);
         vana[ib]->MakeHistograms(Form("inclJetPt>%.03f && acos(cos(photonPhi-inclJetPhi))>%f && sigmaIetaIeta<0.01",minJet,sigDPhi),20,0.0001,3.1415926);
      }
      
      if (doMixBkg) {
         vana[ib]->Extrapolate(sigDPhi,false,0.1);
      } else {
         vana[ib]->Extrapolate(sigDPhi,true);
         vana[ib]->ExtrapolateDPhiHist(sigDPhi);
      }
      vana[ib]->SubtractBkg();
      vana[ib]->Normalize(normMode);
   }
//   inf->Close();
}

void plotHistograms(const SignalCorrector* ana,
                    int cbin,
                    int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                    int dataType, // 0=mc gen, 1=reco
                    int drawCheck = 0,
                    TString opt = "sameE"
                    );

TGraphAsymmErrors * getSummary(
                               int nBin,
                               float * npart,
                               const vector<SignalCorrector*> & vana,
                               int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                               int dataType, // 0=mc gen, 1=reco
                               int drawCheck = 0
                               );

//---------------------------------------------------------------------
void plotInclDeltaPhiSignal_AllCent4_wSummary(
                                         int isolScheme=0, // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                         int normMode=1, // 1=unity, 2=per photon
                                         int subDPhiSide = 1,
                                         int subSShapeSide = 1,
                                         float minPhoton=60,
                                         float minJet=30,
                                         int log=1,
                                         int drawCheck = 0,
                                         TString outdir = "./fig/02.09_paper"
                                         )
{
   TH1::SetDefaultSumw2();
   float sigDPhi=0.7;
   
   outfname=Form("%s/HisOutput_Photonv7_v24_akPu3PF_InclDeltaPhi_gamma%.0fjet%.0fdphiSig%.0f_Isol%d_Norm%d.root",outdir.Data(),minPhoton,minJet,sigDPhi*1000,isolScheme,normMode);
   TFile* hout = new TFile(outfname,"RECREATE");
   hout->Close();

   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};

   vector<TCut> vcutCent,vcutCentPp;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   vcutCentPp.push_back("1==1");
   
   vector<SignalCorrector*> vanahi;
   getHistograms(vanahi, vcutCent,"anaEvtSel",isolScheme,normMode,"../output-data-Photon-v7_v24_akPu3PF.root","1==1",1,1,subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi);

   vector<SignalCorrector*> vanahypho;
   getHistograms(vanahypho, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",isolScheme,normMode,"../output-hy18qcdpho30and50merge_v24_xsec_akPu3PF.root","weight",0,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);

//   vector<SignalCorrector*> vanahygj;
//   getHistograms(vanahygj, vcutCent, "offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)==22",isolScheme,normMode,"../output-hy18qcdpho30and50merge_v24_xsec_akPu3PF.root","weight",0,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);

   vector<SignalCorrector*> vanapp;
   getHistograms(vanapp, vcutCentPp,"anaEvtSel",isolScheme,normMode,"../output-data-pp2010-prod3-photon_v24_akPu3PF.root","1==1",2,1,subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi);

//   vector<SignalCorrector*> vanapp7;
//   getHistograms(vanapp7, vcutCentPp,"anaEvtSel",isolScheme,normMode,"../output-pp-photon-7TeV-v4_v24_akPu3PF.root","1==1",3,1,subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi);

   vector<SignalCorrector*> vanapyz2;
   getHistograms(vanapyz2, vcutCentPp,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",isolScheme,normMode,"../output-py2760z2_v24_akPu3PF.root","weight*sampleWeight",10,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);
   
   vector<SignalCorrector*> vanapyd6t;
   getHistograms(vanapyd6t, vcutCentPp,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",isolScheme,normMode,"../output-py2760d6t_v24_akPu3PF.root","weight*sampleWeight",12,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);
   
//   vector<SignalCorrector*> vanapy7z2;
//   getHistograms(vanapy7z2, vcutCentPp,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",isolScheme,normMode,"../output-py7TeV-pho30-v1_v24_akPu3PF.root","weight*sampleWeight",13,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);
   
   TCanvas *c1 = new TCanvas("c1","",1000,300);
   makeMultiPanelCanvas(c1,4,1,0.0,0.0,0.2,0.2,0.02);

   TH1D * hFrame = (TH1D*)vanahi[0]->rSubtracted.hExtrapNorm->Clone("hFrame");
   hFrame->Reset();
   hFrame->SetAxisRange(0.0001,3.1415926,"X");
   if (normMode>0) hFrame->SetAxisRange(-0.2,1,"Y");
   else hFrame->SetAxisRange(-100,500,"Y");
   if (log) hFrame->SetAxisRange(1e-3,1,"Y");
   hFrame->SetStats(0);
   hFrame->SetMarkerStyle(kOpenSquare);
   hFrame->SetXTitle("|#Delta#phi|");
   hFrame->SetYTitle("N_{#gamma}^{-1} dN/d|#Delta#phi|");
   if (normMode==1) hFrame->SetYTitle("Event Fraction");
   hFrame->GetXaxis()->SetLabelSize(22);
   hFrame->GetXaxis()->SetLabelFont(43);
   hFrame->GetXaxis()->SetTitleSize(24);
   hFrame->GetXaxis()->SetTitleFont(43);
   hFrame->GetXaxis()->SetTitleOffset(1);
   hFrame->GetXaxis()->CenterTitle();
   hFrame->GetXaxis()->SetNdivisions(505,true);
   hFrame->GetYaxis()->SetLabelSize(22);
   hFrame->GetYaxis()->SetLabelFont(43);
   hFrame->GetYaxis()->SetTitleSize(22);
   hFrame->GetYaxis()->SetTitleFont(43);
   hFrame->GetYaxis()->SetTitleOffset(1.2);
   hFrame->GetYaxis()->CenterTitle();
   hFrame->GetYaxis()->SetNdivisions(505,true);   
   TH1D * hFrameNoY = (TH1D*)hFrame->Clone("hFrameNoY");
   hFrameNoY->SetYTitle("");
   
   c1->cd(1);
   if (log==1) gPad->SetLogy();
   hFrame->DrawClone();
   int cbin=3;
   plotHistograms(vanapyz2[0],cbin,10,1,0,"");
   plotHistograms(vanapyd6t[0],cbin,12,1,0,"");
//   plotHistograms(vanapy7z2[0],cbin,0,1,0,"");
   plotHistograms(vanahypho[cbin],cbin,0,1,0,"samehistE");
//   plotHistograms(vanahygj[cbin],cbin,0,1,0,"");
   plotHistograms(vanapp[0],cbin,2,1,drawCheck,"sameE");
//   plotHistograms(vanapp7[0],cbin,3,1,drawCheck,"");
   plotHistograms(vanahi[cbin],cbin,1,1,drawCheck,"sameE");   
   drawText("50-100%",0.8,0.25);
   drawText("(a)",0.25,0.885);

   TLegend *t2=new TLegend(0.44,0.66,0.91,0.94);
   t2->AddEntry(hFrame,"CMS Preliminary","");
   t2->AddEntry(hFrame,"#intL dt = 150 #mub^{-1}","");
   t2->AddEntry(hFrame,"#sqrt{s}_{_{NN}}=2.76 TeV","");
   t2->SetFillColor(0);
   t2->SetBorderSize(0);
   t2->SetFillStyle(0);
   t2->SetTextFont(63);
   t2->SetTextSize(17);
   t2->Draw();
   drawText("Ak PF, R=0.3",0.56,0.61,15);

   c1->cd(2);
   if (log==1) gPad->SetLogy();
   hFrameNoY->DrawClone();
   cbin=2;
   plotHistograms(vanahypho[cbin],cbin,0,1,0,"samehistE");
//   plotHistograms(vanahygj[cbin],cbin,0,1,0,"");
   plotHistograms(vanahi[cbin],cbin,1,1,drawCheck,"sameE");   
   drawText("30-50%",0.75,0.25);
   drawText("(b)",0.05,0.885);

   TLegend *t3=new TLegend(0.34,0.62,0.81,0.94); 
   t3->AddEntry(vanahi[cbin]->rSubtracted.hExtrapNorm,"PbPb","p");
   t3->AddEntry(vanapp[0]->rSubtracted.hExtrapNorm,"pp 2.76 TeV","p");
//   t3->AddEntry(vanapp7[0]->rSubtracted.hExtrapNorm,"pp 7 TeV","p");
   //t3->AddEntry(hFrameData,"PYQUEN_Quen+HYDJET","p");
   if (drawCheck>=1) t3->AddEntry(vanahi[cbin]->rSigAll.hExtrapNorm,"No Subtraction","l");
//   if (subDPhiSide&&drawCheck) t3->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
//   if (subSShapeSide&&drawCheck) t3->AddEntry(hFrameDataBkg2,"#sigma_{#eta#eta} sideband","p");
   t3->AddEntry(vanahypho[cbin]->rSubtracted.hExtrapNorm,"PYTHIA + HYDJET","lf");
//   t3->AddEntry(vanahypho[cbin]->rSubtracted.hExtrapNorm,"Isol. #gamma + HYDJET","lf");
   //t3->AddEntry(hFrameGen,"MC: Frag. #gamma","lf");
   t3->SetFillColor(0);
   t3->SetBorderSize(0);
   t3->SetFillStyle(0);
   t3->SetTextFont(63);
   t3->SetTextSize(15);
   t3->Draw();

   c1->cd(3);
   if (log==1) gPad->SetLogy();
   hFrame->DrawClone();
   cbin=1;
   plotHistograms(vanahypho[cbin],cbin,0,1,0,"samehistE");
//   plotHistograms(vanahygj[cbin],cbin,0,1,0,"");
   plotHistograms(vanahi[cbin],cbin,1,1,drawCheck,"sameE");
   drawText("10-30%",0.75,0.25);
   drawText("(c)",0.05,0.885);

   TLegend *t4=new TLegend(0.43,0.7,0.91,0.94);
   t4->AddEntry(hFrame,Form("p_{T}^{#gamma} > %.0f GeV/c",minPhoton),"");
   t4->AddEntry(hFrame,Form("p_{T}^{jet} > %.0f GeV/c",minJet),"");
   t4->AddEntry(hFrame,Form("#Delta#phi_{12} > %.1f",sigDPhi),"");
   t4->SetFillColor(0);
   t4->SetBorderSize(0);
   t4->SetFillStyle(0);
   t4->SetTextFont(63);
   t4->SetTextSize(15);
   t4->Draw();

   c1->cd(4);
   if (log==1) gPad->SetLogy();
   hFrameNoY->DrawClone();
   cbin=0;
   plotHistograms(vanahypho[cbin],cbin,0,1,0,"samehistE");
//   plotHistograms(vanahygj[cbin],cbin,0,1,0,"");
   plotHistograms(vanahi[cbin],cbin,1,1,drawCheck,"sameE");
   drawText("0-10%",0.75,0.25);
   drawText("(d)",0.05,0.885);

   c1->Print(Form("%s/Photonv7_v24_akPu3PF_isolPho_gamma%.0fjet%.0fdphiSig%.0f_InclDeltaPhi_all_cent4_subDPhi%dSS%d_Isol%d_Norm%d_drawChk%d_log%d.gif",outdir.Data(),minPhoton,minJet,sigDPhi*1000,subDPhiSide,subSShapeSide,isolScheme,normMode,drawCheck,log));
   c1->Print(Form("%s/Photonv7_v24_akPu3PF_isolPho_gamma%.0fjet%.0fdphiSig%.0f_InclDeltaPhi_all_cent4_subDPhi%dSS%d_Isol%d_Norm%d_drawChk%d_log%d.pdf",outdir.Data(),minPhoton,minJet,sigDPhi*1000,subDPhiSide,subSShapeSide,isolScheme,normMode,drawCheck,log));

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Summary Plot
   ////////////////////////////////////////////////////////////////////////////////////////////////
   float npart[nBin];
   GetNPartBins("../output-data-Photon-v7_v24_akPu3PF.root", nBin, npart, m, minPhoton,1);
   cout << "got npart" << endl;

   TH1D *hNpartFrame = new TH1D("hNpartFrame","",100,-10,400);
   hNpartFrame->SetXTitle("N_{part}");
   hNpartFrame->SetYTitle("#sigma(|#Delta#phi|)");
   hNpartFrame->GetXaxis()->CenterTitle();
   hNpartFrame->GetYaxis()->CenterTitle();
   hNpartFrame->GetYaxis()->SetTitleOffset(1.4);
   hNpartFrame->GetYaxis()->SetTitleSize(0.05);
   float ymin=0,ymax=0.5;
   hNpartFrame->SetAxisRange(ymin,ymax,"Y");
   TCanvas *c2 = new TCanvas("c","",500,500);
   hNpartFrame->Draw();
   
   cout << endl << "     MC Isol Pho" << endl;
   TGraphAsymmErrors * ghypho = getSummary(nBin,npart,vanahypho,0,1,0);
   ghypho->SetMarkerSize(1.25);
   ghypho->SetMarkerStyle(kOpenSquare);
   ghypho->Draw("p same");
   
//   cout << endl << "     MC Gamma-jet" << endl;
//   TGraphAsymmErrors * ghygj = getSummary(nBin,npart,vanahygj,0,1,0);
//   ghygj->SetMarkerSize(1.25);
//   ghygj->SetMarkerStyle(kOpenCircle);
//   ghygj->Draw("p same");
   
   cout << endl << "     pythia z2" << endl;
   TGraphAsymmErrors * gpyz2 = getSummary(1,npart,vanapyz2,10,1,0);
   gpyz2->SetMarkerSize(1.25);
   gpyz2->SetMarkerStyle(kOpenSquare);
   gpyz2->SetMarkerColor(kBlue);
   gpyz2->Draw("p same");
   
   cout << endl << "     pythia d6t" << endl;
   TGraphAsymmErrors * gpyd6t = getSummary(1,npart,vanapyd6t,12,1,0);
   gpyd6t->SetMarkerSize(1.25);
   gpyd6t->SetMarkerStyle(kOpenCircle);
   gpyd6t->SetMarkerColor(kBlue);
   gpyd6t->Draw("p same");
   
//   cout << endl << "     pythia 7 TeV z2" << endl;
//   TGraphAsymmErrors * gpy7z2 = getSummary(1,npart,vanapy7z2,2,1,99);
//   gpy7z2->SetMarkerSize(1.25);
//   gpy7z2->SetMarkerStyle(kOpenCross);
//   gpy7z2->SetMarkerColor(kBlue);
//   gpy7z2->Draw("p same");
      
   cout << endl << "     pp 2.76" << endl;
   TGraphAsymmErrors * gpp = getSummary(1,npart,vanapp,2,1,drawCheck);
   gpp->SetMarkerSize(1.25);
   gpp->SetMarkerStyle(kOpenStar);
   gpp->SetMarkerColor(kRed);
   gpp->SetLineColor(kRed);
   gpp->Draw("p same");
   
//   cout << endl << "     pp 7" << endl;
//   TGraphAsymmErrors * gpp7 = getSummary(1,npart,vanapp7,3,1,drawCheck);
//   gpp7->SetMarkerSize(1.25);
//   gpp7->SetMarkerStyle(kOpenCross);
//   gpp7->SetMarkerColor(kOrange+2);
//   gpp7->SetLineColor(kOrange+2);
//   gpp7->Draw("p same");
   
   cout << endl << "     Data" << endl;
   TGraphAsymmErrors * gdata = getSummary(nBin,npart,vanahi,1,1,drawCheck);
   gdata->SetMarkerSize(1.25);
   gdata->SetMarkerColor(2);
   gdata->SetLineColor(2);
   gdata->Draw("p same");
   
   // Annotation
   drawText("CMS Preliminary",0.198,0.89,17);
   TLine* pline = new TLine(0,ghypho->GetY()[4],400,ghypho->GetY()[4]);
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();   
   
   TLegend *leg=new TLegend(0.55,0.64,0.85,0.91);
   leg->AddEntry(gdata,"#intL dt = 150 #mub^{-1}","");
   leg->AddEntry(gdata,"PbPb  #sqrt{s}_{_{NN}}=2.76 TeV","p");
//   leg->AddEntry(hFrameDataSigAll,"No Subtraction","p");
//   if (drawCheck&&subDPhiSide) leg->AddEntry(hFrameDataBkg1,"|#Delta#phi| sideband","p");
//   if (drawCheck&&subSShapeSide) leg->AddEntry(hFrameDataBkg2,"#sigma_{#eta#eta} sideband","p");
   leg->AddEntry(ghypho,"PYTHIA + HYDJET1.8","p");
//   leg->AddEntry(ghypho,"Isol. #gamma + HYDJET1.8","p");
//   leg->AddEntry(ghygj,"LO #gamma + HYDJET1.8","p");
   leg->AddEntry(gpp,"pp 2.76 TeV","p");
//   leg->AddEntry(gpp7,"pp 7 TeV","p");
   leg->AddEntry(gpyz2,"PYTHIA 2.76 TeV Z2","p");
   leg->AddEntry(gpyd6t,"PYTHIA 2.76 TeV D6T","p");
//   leg->AddEntry(gpy7z2,"PYTHIA 7 TeV z2","p");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->SetTextFont(63);
   leg->SetTextSize(17);
   leg->Draw();
   
   TLegend *leg2=new TLegend(0.54,0.17,0.86,0.35);
   leg2->AddEntry(hNpartFrame,Form("p_{T,#gamma} > %.0f GeV/c",minPhoton),"");
   leg2->AddEntry(hNpartFrame,Form("p_{T,jet} > %.0f GeV/c",minJet),"");
   leg2->AddEntry(hNpartFrame,Form("#Delta#phi_{12} > %.1f",sigDPhi),"");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0);
   leg2->SetTextFont(63);
   leg2->SetTextSize(17);
   leg2->Draw();
   
   c2->Print(Form("%s/Photonv7_v24_akPu3PF_isolPho_InclDeltaPhiSubDPhi%dSS%d_gamma%.0fjet%.0fdphiSig%.0f_vs_Npart_Isol%d_Norm%d_drawChk%d.gif",outdir.Data(),subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi*1000,isolScheme,normMode,drawCheck));
   c2->Print(Form("%s/Photonv7_v24_akPu3PF_isolPho_InclDeltaPhiSubDPhi%dSS%d_gamma%.0fjet%.0fdphiSig%.0f_vs_Npart_Isol%d_Norm%d_drawChk%d.pdf",outdir.Data(),subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi*1000,isolScheme,normMode,drawCheck));
}

void plotHistograms(const SignalCorrector* ana,
                    int cbin,
                    int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                    int dataType, // 0=mc gen, 1=reco
                    int drawCheck,
                    TString opt
                    )
{
   cout << "plot ana: " << ana->name << endl;
   if (dataSrcType) {
      if (dataSrcType==1) {
         ana->rSubtracted.hExtrapNorm->SetLineColor(kRed);
         ana->rSubtracted.hExtrapNorm->SetMarkerColor(kRed);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(20);
      } else if (dataSrcType==2) {
         ana->rSubtracted.hExtrapNorm->SetLineColor(kBlack);
         ana->rSubtracted.hExtrapNorm->SetMarkerColor(kBlack);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(kOpenSquare);
      } else if (dataSrcType==3) {
         ana->rSubtracted.hExtrapNorm->SetLineColor(kOrange+2);
         ana->rSubtracted.hExtrapNorm->SetMarkerColor(kOrange+2);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(kOpenStar);
      }
   } else {
      if (dataType==0) {
         ana->rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         ana->rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         ana->rSubtracted.hExtrapNorm->SetFillStyle(3005);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      } else if (dataType==1) {   
         ana->rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         ana->rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         ana->rSubtracted.hExtrapNorm->SetFillStyle(3005);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      } else if (dataType==2) {
         ana->rSubtracted.hExtrapNorm->SetLineColor(kBlue);
         ana->rSubtracted.hExtrapNorm->SetFillColor(kAzure-8);
         ana->rSubtracted.hExtrapNorm->SetFillStyle(3004);
         ana->rSubtracted.hExtrapNorm->SetStats(0);
         ana->rSubtracted.hExtrapNorm->SetLineStyle(2);
         ana->rSubtracted.hExtrapNorm->SetMarkerStyle(0);
      }
   }
   
   if (opt!="") ana->rSubtracted.hExtrapNorm->Draw(opt);
   float mean=ana->rSubtracted.hExtrapNorm->GetMean();
   
   // output histograms
   TFile* hout = new TFile(outfname,"update");
   ana->rSubtracted.hExtrapNorm->Write();
   hout->Close();
   
   // fit width
   float fitxmin=3.1415926*2./3;
   //float fitxmin=2.2;
   //TF1 *fdphi = new TF1("fdphi","[0]+[1]*exp(-(3.1415926-x)/[2])",2.0944,3.1415926);
   TF1 *fdphi = new TF1("fdphi","[0]*exp(-(3.1415926-x)/[1])",fitxmin,3.1415926);
   //TF1 *fdphi = new TF1("fdphi","[0]*exp(-(3.1415926-x)/[0])",fitxmin,3.1415926);
   fdphi->SetParName(0,"norm");
   fdphi->SetParName(1,"width");
   fdphi->SetParameter("norm",1);
   fdphi->SetParameter("width",0.2);
   ana->rSubtracted.hExtrapNorm->Fit("fdphi","0em","",fitxmin,3.1415926);
   fdphi->SetLineWidth(1);
   fdphi->SetLineStyle(2);
   if (dataSrcType) {
      if (dataSrcType==1) fdphi->SetLineColor(kRed);
      else if (dataSrcType==3) fdphi->SetLineColor(kOrange+2);
   } else fdphi->SetLineColor(kBlue);
//   if (opt!="") fdphi->Draw("same");
   float dphiWidth = fdphi->GetParameter("width");
   
   // check subtraction
   if (drawCheck>=2) {
      if (ana->rBkgDPhi.hExtrapNorm) {
         ana->rBkgDPhi.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         ana->rBkgDPhi.hExtrapNorm->SetMarkerColor(kGreen+2);
         ana->rBkgDPhi.hExtrapNorm->Draw("sameE");
      }
      if (ana->rBkgSShape.hExtrapNorm) {
         ana->rBkgSShape.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         ana->rBkgSShape.hExtrapNorm->SetMarkerColor(kViolet);
         ana->rBkgSShape.hExtrapNorm->Draw("sameE");
         ana->rBkgSShapeDPhi.hExtrapNorm->SetMarkerSize(0.8);
         ana->rBkgSShapeDPhi.hExtrapNorm->SetMarkerStyle(kOpenCircle);
         ana->rBkgSShapeDPhi.hExtrapNorm->SetMarkerColor(kYellow+2);
         ana->rBkgSShapeDPhi.hExtrapNorm->Draw("sameE");
      }
   }
   
   if (dataSrcType&&drawCheck>=1) {
      // Draw count
      float nPhotonJet = ana->rSubtracted.nExtrap;
      float dx = 0,dy = 0;
      if (cbin==2||cbin==0) dx=-0.2;
      if (cbin<=1) dy = 0.04;
      TLegend *t3=new TLegend(0.13+dx,0.65+dy,0.5+dx,0.85+dy);
      if (dataSrcType==1) {
         ana->rSigAll.hExtrapNorm->SetLineStyle(2);
         ana->rSigAll.hExtrapNorm->Draw("same hist");
         if (cbin==0) t3->AddEntry(ana->rSigAll.h,ana->nameIsol,"");
         t3->AddEntry(ana->rSigAll.h,Form("#gamma purity %.2f",1-ana->fracPhotonBkg),"");
         t3->AddEntry(ana->rSigAll.h,Form("%.0f #gamma-j",nPhotonJet),"");
         t3->AddEntry(ana->rSigAll.h,Form("  #sigma(|#Delta#phi|): %.2f",dphiWidth),"");
      }
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();

      TLegend *t4=new TLegend(0.13+dx,0.4+dy,0.5+dx,0.58+dy);
      if (cbin==2) {
         if (dataSrcType==2) {
            t4->AddEntry(ana->rSigAll.h,Form("pp2.76TeV: %.0f #gamma-j",nPhotonJet),"");
            t4->AddEntry(ana->rSigAll.h,Form("  #sigma(|#Delta#phi|): %.2f",dphiWidth),"");
            t4->AddEntry(ana->rSigAll.h,"","");
            t4->AddEntry(ana->rSigAll.h,"","");
         } else if (dataSrcType==3) {
            t4->AddEntry(ana->rSigAll.h,"","");
            t4->AddEntry(ana->rSigAll.h,"","");
            t4->AddEntry(ana->rSigAll.h,Form("pp7TeV: %.0f #gamma-j",nPhotonJet),"");
            t4->AddEntry(ana->rSigAll.h,Form("  #sigma(|#Delta#phi|): %.2f",dphiWidth),"");
         }
         t4->SetFillColor(0);
         t4->SetBorderSize(0);
         t4->SetFillStyle(0);
         t4->SetTextFont(63);
         t4->SetTextSize(15);
         t4->Draw();
      }
   }
}

TGraphAsymmErrors * getSummary(
                               int nBin,
                               float * npart,
                               const vector<SignalCorrector*> & vana,
                               int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                               int dataType, // 0=mc gen, 1=reco
                               int drawCheck
                               )
{
   // make graph
   TGraphAsymmErrors * gAve = new TGraphAsymmErrors(nBin);
   TString name = Form("dataSrc%d_reco%d_dphi_Summary_0",dataSrcType,dataType);
   gAve->SetName(name);
   
   float nPhotonJet=0;
   for (int ib=0;ib<gAve->GetN();++ib)
   {
      float y=0,errYL=0,errYH=0;
//      float y=vana[ib]->rSubtracted.hExtrapNorm->GetMean();
//      float errYL = vana[ib]->rSubtracted.hExtrapNorm->GetMeanError();
//      float errYH = vana[ib]->rSubtracted.hExtrapNorm->GetMeanError();
      TF1 * fdphi = vana[ib]->rSubtracted.hExtrapNorm->GetFunction("fdphi");
      if (fdphi) {
         y=fdphi->GetParameter("width");
         errYL = fdphi->GetParError(fdphi->GetParNumber("width"));
         errYH = fdphi->GetParError(fdphi->GetParNumber("width"));
      }
      
      gAve->SetPointError(ib,0,0,errYL,errYH);
      if (dataSrcType<=1) gAve->SetPoint(ib,npart[ib],y);
      else {
         gAve->SetPoint(ib,2,y);
         cout<<" Setting PYTHIA point to npart=2 by hand"<<endl;
      }
      cout <<"bin: " << ib <<" npart: "<<npart[ib]<< " y: " << y << " yerr: " << errYH << endl;
      nPhotonJet+=vana[ib]->rSubtracted.nExtrap;
   }

   TFile* hout = new TFile(outfname,"update");
   gAve->Write();
   hout->Close();
   
   // Draw count
   TLegend *t3=new TLegend(0.1,0.68,0.51,0.89);
   if (drawCheck>=1) {
      if (dataSrcType==1) {
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,vana[0]->nameIsol,"");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("PbPb: %.0f #gamma-j",nPhotonJet),"");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         //      for (int ib=nBin-1;ib>=0;--ib) {
         //         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("%.0f to %.0f \%: %.0f #gamma-j",m[ib]*2.5,m[ib+1]*2.5,vana[ib]->rSubtracted.nExtrap),"");
         //      }
      } else if (dataSrcType==2) {
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("pp 2.76GeV: %.0f #gamma-j",nPhotonJet),"");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         //      for (int ib=nBin-1;ib>=0;--ib) { t3->AddEntry("","",""); }
      } else if (dataSrcType==3) {
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,"","");
         t3->AddEntry(vana[0]->rSubtracted.hExtrapNorm,Form("pp 7TeV: %.0f #gamma-j",nPhotonJet),"");
         //      for (int ib=nBin-1;ib>=0;--ib) { t3->AddEntry("","",""); }
      }
      t3->SetFillColor(0);
      t3->SetBorderSize(0);
      t3->SetFillStyle(0);
      t3->SetTextFont(63);
      t3->SetTextSize(15);
      t3->Draw();
   }
   
   return gAve;
}

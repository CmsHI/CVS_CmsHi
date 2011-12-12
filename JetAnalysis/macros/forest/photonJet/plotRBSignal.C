#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TLine.h"
#include "DrawTick.C"

using namespace std;

class EvtSel {
public:
   int run;
   int evt;
   int cBin;
   int nG;
   int nJ;
   int nT;
   bool trig;
   bool offlSel;
   bool noiseFilt;
   bool anaEvtSel;
   float vz,weight;
};

static const int MAXTRK = 10000;

class GammaJet{
public:
   GammaJet() :
   photonEt(-99),photonEta(0),photonPhi(0),
   jetEt(-99),jetEta(0),jetPhi(0),
   deta(-99),dphi(-99), Aj(-99),
   sigmaIetaIeta(-99),
   nTrk(0)
   {}
   float photonEt,photonRawEt;
   float photonEta;
   float photonPhi;
   float jetEt;
   float jetEta;
   float jetPhi;
   float deta;
   float dphi;
   float Aj;
   float hovere,sigmaIetaIeta,sumIsol;
   int nTrk;
   float trkPt[MAXTRK];
   float trkEta[MAXTRK];
   float trkPhi[MAXTRK];   
   void clear() {
      photonEt=-99; photonEta=0; photonPhi=0;
      jetEt=-99; jetEta=0; jetPhi=0;
      deta=-99; dphi=-99; Aj=-99;
      sigmaIetaIeta=-99;
      nTrk=0;
   }
};

TGraphAsymmErrors *divideGraph(TGraphAsymmErrors *a,TGraphAsymmErrors *b)
{
   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors();
   for (int i=0;i<a->GetN();i++)
   {
      double x,y;
      double x2,y2;
      a->GetPoint(i,x,y);
      b->GetPoint(i,x2,y2);
      double errYL = a->GetErrorYlow(i);
      double errYH = a->GetErrorYhigh(i);
      double errYL2 = b->GetErrorYlow(i);
      double errYH2 = b->GetErrorYhigh(i);
      gEfficiency->SetPointError(i,0,0,sqrt(errYL*errYL+errYL2*errYL2),sqrt(errYH*errYH+errYH2*errYH2));
      gEfficiency->SetPoint(i,x,y/y2);
   }
   return gEfficiency;
}

TGraphAsymmErrors *calcEff(TH1* h1, TH1* hCut,double *npart)
{
   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors();
   gEfficiency->BayesDivide(hCut,h1);
   cout << "graph N points: " << gEfficiency->GetN()<<endl;
   for (int i=0;i<gEfficiency->GetN();i++)
   {
      double x,y;
      gEfficiency->GetPoint(i,x,y);
      double errYL = gEfficiency->GetErrorYlow(i);
      double errYH = gEfficiency->GetErrorYhigh(i);
      gEfficiency->SetPointError(i,0,0,errYL,errYH);
      gEfficiency->SetPoint(i,npart[h1->FindBin(x)-1],y);
      cout <<"x: " << x<<" "<<h1->FindBin(x)<<" "<<npart[h1->FindBin(x)-1]<< " y: " << y << endl;
   }
   return gEfficiency;
}

TGraphAsymmErrors *calcEffpythia(TH1* h1, TH1* hCut,double *npart)
{
   TGraphAsymmErrors *gEfficiency = new TGraphAsymmErrors();
   gEfficiency->BayesDivide(hCut,h1);
   cout <<gEfficiency->GetN()<<endl;
   for (int i=0;i<gEfficiency->GetN();i++)
   {
      double x,y;
      gEfficiency->GetPoint(i,x,y);
      double errYL = gEfficiency->GetErrorYlow(i);
      double errYH = gEfficiency->GetErrorYhigh(i);
      gEfficiency->SetPointError(i,0,0,errYL,errYH);
      gEfficiency->SetPoint(i,2,y);
      cout<<" Setting PYTHIA point to npart=2 by hand, Yen-Jie please check -Matt "<<endl;
   }
   return gEfficiency;
}

void GetNPartBins(TTree * nt, EvtSel & evt, GammaJet & gj, int nBin, double * npart, double * m, double threshold1, int dataType)
{
   double npartValue[40];
   npartValue[0] = 393.633;
   npartValue[1] = 368.819;
   npartValue[2] = 343.073;
   npartValue[3] = 317.625;
   npartValue[4] = 292.932;
   npartValue[5] = 271.917;
   npartValue[6] = 249.851;
   npartValue[7] = 230.72;
   npartValue[8] = 212.465;
   npartValue[9] = 194.752;
   npartValue[10] = 178.571;
   npartValue[11] = 163.23;
   npartValue[12] = 149.187;
   npartValue[13] = 136.011;
   npartValue[14] = 123.414;
   npartValue[15] = 111.7;
   npartValue[16] = 100.831;
   npartValue[17] = 90.7831;
   npartValue[18] = 80.9823;
   npartValue[19] = 72.6236;
   npartValue[20] = 64.1508;
   npartValue[21] = 56.6284;
   npartValue[22] = 49.9984;
   npartValue[23] = 43.3034;
   npartValue[24] = 37.8437;
   npartValue[25] = 32.6659;
   npartValue[26] = 27.83;
   npartValue[27] = 23.7892;
   npartValue[28] = 20.1745;
   npartValue[29] = 16.8453;
   npartValue[30] = 14.0322;
   npartValue[31] = 11.602;
   npartValue[32] = 9.52528;
   npartValue[33] = 7.6984;
   npartValue[34] = 6.446;
   npartValue[35] = 4.96683;
   npartValue[36] = 4.23649;
   npartValue[37] = 3.50147;
   npartValue[38] = 3.16107;
   npartValue[39] = 2.7877;
   
   TH1D *hStat = new TH1D("hStat","",nBin,m);
   TH1D *hNpartSum = new TH1D("hNpartSum","",nBin,m);

   for (int i=0;i<nt->GetEntries();i++)
   {
      nt->GetEntry(i);
      if (i%10000==0) {
         if (dataType==1) { // data
            if (!evt.anaEvtSel) continue;
         }
         else if (dataType==0) { //mc
            if (!evt.offlSel) continue;
         }
         if (gj.photonEt>0) cout <<i<<" / "<< nt->GetEntries() << " run: " << evt.run << " evt: " << evt.evt << " bin: " << evt.cBin << " gamma pt: " << gj.photonEt <<endl;
      }
      
      if (gj.photonEt>threshold1) {
         hNpartSum->Fill(evt.cBin,npartValue[evt.cBin]);
         hStat->Fill(evt.cBin); 
      }
   }
   
   hNpartSum->Divide(hStat);
   
   for (int i=1;i<nBin;i++)
   {
      cout <<hNpartSum->GetBinContent(i+1)<<endl;
      npart[i]=hNpartSum->GetBinContent(i+1);
   }
}


TGraphAsymmErrors * getRBSignal(
                                double threshold1 = 60,
                                double ajCut= 1,
                                TString infname = "../output-data-Photon-v3_v10.root",
                                int dataType=0 // 0=mc, 1=data
)
{		
   TString name=Form("photon%.0fAj%.0fdata%d",threshold1,ajCut,dataType);
   TCut evtSel="offlSel";
   if (dataType==1) evtSel="anaEvtSel";
   TCut cut1=evtSel&&Form("photonEt>%.3f",threshold1);
   TCut cutAna = cut1&&Form("jetEt>0&&acos(cos(photonPhi-jetPhi))>3.14159*2/3&&Agj<%.3f",ajCut);
   cout <<cut1<<endl;
   cout <<cutAna<<endl;
   
   // open the data file
   TFile *inf = new TFile(infname.Data());
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   
   // open output
   //TFile *outfile = new TFile("output.root","recreate");
   //TNtuple *ntOut = new TNtuple("ntOut","","npart");
   
   const int nBin = 6;
   double m[nBin+1] = {-1.5,-0.5,3.5,7.5,11.5,20.5,40.5};
   double npart[nBin] = {2,358.623,232.909,97.9521};
   EvtSel evt;
   GammaJet gj;
   nt->SetBranchAddress("evt",&evt.run);
   nt->SetBranchAddress("jet",&gj.photonEt);
   GetNPartBins(nt, evt, gj, nBin, npart, m, threshold1,dataType);
   cout << "got npart" << endl;
  
   TH1D *h1 = new TH1D("h1","",nBin,m);
   TH1D *hAna = new TH1D("hAna","",nBin,m);
   
   //TCanvas *c0 = new TCanvas("c0","",500,500);
   nt->Draw("cBin>>h1",cut1,"goff");
   nt->Draw("cBin>>hAna",cutAna,"sameEgoff");
   TGraphAsymmErrors *g = calcEff(h1,hAna,npart);
   
   return g;
}

void plotRBSignal(
                  double ajCut= 0.15
)
{
   TCanvas *c2 = new TCanvas("c","",500,500);
   TH1D *hTmp = new TH1D("hTmp","",100,-10,400);
   hTmp->SetXTitle("N_{part}");
   hTmp->SetYTitle(Form("R_{B}(A_{GJ} < %.2f)",ajCut));
   hTmp->GetXaxis()->CenterTitle();
   hTmp->GetYaxis()->CenterTitle();
   hTmp->GetYaxis()->SetTitleOffset(1.4);
   hTmp->GetYaxis()->SetTitleSize(0.05);
   hTmp->SetAxisRange(0,1.4,"Y");
   hTmp->Draw();

   TGraphAsymmErrors * gdata = getRBSignal(60,ajCut,"../output-data-Photon-v2_v11.root",1);
   gdata->SetMarkerSize(1.25);
   gdata->SetMarkerColor(2);
   gdata->SetLineColor(2);
   gdata->Draw("p same");

   TGraphAsymmErrors * ghypho = getRBSignal(60,ajCut,"../output-hypho50v2_50kyongsun_v11.root",0);
   ghypho->SetMarkerSize(1.25);
   ghypho->SetMarkerStyle(kOpenSquare);
   ghypho->Draw("p same");
   
   // Annotation
   TLine* pline = new TLine(0,ghypho->GetY()[4],400,ghypho->GetY()[4]);
   pline->SetLineColor(4);
   pline->SetLineStyle(4);
   pline->Draw();
   
   TLatex *cms = new TLatex(0.1,0.91,"CMS Preliminary");
   cms->SetTextFont(63);
   cms->SetTextSize(17);
   cms->Draw();
   TLegend *leg=new TLegend(0.55,0.81,0.85,0.91);
   //leg->AddEntry(gdata,"#intL dt = 84 #mub^{-1}","");
   leg->AddEntry(gdata,"PbPb  #sqrt{s}_{_{NN}}=2.76 TeV","p");
   leg->AddEntry(ghypho,"PYTHIA+HYDJET","p");
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->SetTextFont(63);
   leg->SetTextSize(17);
   leg->Draw();
   
   TLegend *leg2=new TLegend(0.16,0.27,0.49,0.35);
   leg2->AddEntry(gdata,"p_{T,#gamma} > 60 GeV/c","");
   //leg2->AddEntry(gdata,"p_{T,jet} > 30 GeV/c","");
   //leg2->AddEntry(gdata,"#Delta#phi_{12} > #frac{2}{3}#pi","");
   leg2->SetFillColor(0);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0);
   leg2->SetTextFont(63);
   leg2->SetTextSize(17);
   leg2->Draw();

   c2->Print(Form("fig/12.12/RB_Ratio_%.0f_vs_Npart.gif",ajCut*100));
   c2->Print(Form("fig/12.12/RB_Ratio_%.0f_vs_Npart.pdf",ajCut*100));
}

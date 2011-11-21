#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TString.h"
#include "TCut.h"
#include "TLegend.h"
#include "TLine.h"
#include "commonUtility.h"
#include "compare.h"
using namespace std;

void hcalValTree(
                 TString infdataname="/d00/yjlee/hiForest/PromptReco2011/Run181611/merged_Run181611_HIMinBiasUPC_PromptReco.root",
                 TString infrefname="/d00/yjlee/hiForest/HIData2010/merged_hiForest_HIData2010_EB200MeV.root",
                 TString tag="181611"
                 )
{
   TH1::SetDefaultSumw2();
   
   // inputs
   TFile * infdata = new TFile(infdataname);
   TFile * infref = new TFile(infrefname);
   cout << "compare: " << infdata->GetName() << " " << infref->GetName() << endl;
   
   TTree * tdata = (TTree*)infdata->Get("hltanalysis/HltTree");
   tdata->AddFriend("skim=skimanalysis/HltTree",infdataname);
   tdata->AddFriend("ev=hiEvtAnalyzer/HiTree");
   tdata->AddFriend("rh=rechitanalyzer/hbhe",infdataname);
   TTree * tref = (TTree*)infref->Get("hltanalysis/HltTree");
   tref->AddFriend("skim=skimanalysis/HltTree",infrefname);
   tref->AddFriend("ev=hiEvtAnalyzer/HiTree");
   tref->AddFriend("rh=rechitanalyzer/hbhe",infrefname);
   
   TCut sel = "HLT_HIMinBiasHfOrBSC_v1&&skim.pcollisionEventSelection";
   TCut selref = "HLT_HIMinBiasHfOrBSC&&skim.pcollisionEventSelection";
   
   
   
   // histograms
   TCanvas * c2 = new TCanvas("c2","c2",600,600);
   makeMultiPanelCanvas(c2,2,2,0,0,0.25);
   c2->cd(1);
   c2->GetPad(1)->SetLogy();
   Compare comp2_1("hEtCen1_hb",tdata,tref,sel&&"ev.hiNpix>30000",selref&&"ev.hiNpix>30000","abs(rh.eta)<2&&abs(rh.eta)<2");
   comp2_1.Init(100,0,40);
   comp2_1.Project("rh.et>>");
   comp2_1.Draw(";rechit E_{T} (GeV);a.u.",0,0,"2011 Data "+tag,"2010 Data",1,0.5,0.8,0.9,0.9);
   c2->cd(2);
   c2->GetPad(2)->SetLogy();
   Compare comp2_2("hEtCen2_hb",tdata,tref,sel&&"ev.hiNpix<1000",selref&&"ev.hiNpix<1000","abs(rh.eta)<2&&abs(rh.eta)<2");
   comp2_2.Init(100,0,40);
   comp2_2.Project("rh.et>>");
   comp2_2.Draw(";rechit E_{T} (GeV);a.u.");
   c2->cd(3);
   TH1D * hRat2_1 = comp2_1.Ratio("Ratio of 2011/2010");
   hRat2_1->SetAxisRange(0,1.4,"Y");
   hRat2_1->Draw();
   TLine * l = new TLine(0,1,40,1); l->SetLineStyle(2);
   l->Draw();
   c2->cd(4);
   TH1D * hRat2_2 = comp2_2.Ratio("Ratio of 2011/2010");
   hRat2_2->SetAxisRange(0,1.4,"Y");
   hRat2_2->Draw();
   l->Draw();
   c2->Print("out/RechitEt"+tag+"EtaLt2.gif");
}

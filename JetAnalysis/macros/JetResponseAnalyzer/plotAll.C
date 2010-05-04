#include <string>
#include <vector>
#include <iostream>
#include <TH2D.h>
#include <TH1D.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>

using namespace std;


void formatPlot(TGraphErrors * g, int i){
  TF1 * f = g->GetFunction("fit");
  if(f) f->SetLineColor(i);
  g->SetMarkerColor(i);
  g->SetLineColor(i);
}

void plotAll(){

  bool barrel = false;
  static const int nb = 6;
  static const int nAlgos = 2;

  string algos[3] = {"akPu5calo","akPu7calo",""};
  //  string algos[nAlgos] = {"icPu5calo","akPu5calo","ktPu6calo"};
  string bbins[6] = {"0-10","10-20","20-30","60-70","70-80","80-90"};
  int b[6] = {0,1,2,6,7,8};

 TGraphErrors* rsp[nAlgos][nb]; 
 TGraphErrors* res[nAlgos][nb];

 TFile* inf[nb];
 for(int i = 0; i < nb; ++i){
   inf[i] = new TFile(Form("resp_jra_all_bin%d.root",b[i]));
 }

 TFile* outf = new TFile("final_plots.root","recreate");
 TH1D* corPad = new TH1D("corPad",";p_{T}^{GenJet} [GeV];<p_{T}^{CaloJet}/p_{T}^{GenJet}>",10,0,200);
 corPad->SetMaximum(2.5);
 corPad->SetStats(0);
 TH1D* uncPad = new TH1D("uncPad",";p_{T}^{GenJet} [GeV];#sigma<ratio>/<ratio> and <p_{T}^{CaloJet}/p_{T}^{GenJet}>",10,0,200);
 uncPad->SetMaximum(1.);
 TH1D* resPad = new TH1D("resPad",";p_{T}^{GenJet} [GeV];#sigma(p_{T}^{RecoJet}/p_{T}^{GenJet})/<p_{T}^{RecoJet}/p_{T}^{GenJet}>",10,0,200);
 resPad->SetMaximum(.5);
 TCanvas * c1 = new TCanvas("c1","c1",900,800);
 c1->Divide(3,2);

 for(int i = 0; i < nb; ++i){
   c1->cd(i+1);

   TLegend* leg =  new TLegend(0.20,0.68,0.46,0.91,NULL,"brNDC");
   leg->SetFillColor(0);
   leg->SetTextSize(0.035);
   leg->SetBorderSize(0);
   leg->AddEntry("Centrality",Form("Centrality : %s",bbins[i].data()),"");
   leg->Draw();

   TLegend* leg2 =  new TLegend(0.68,0.68,0.94,0.91,NULL,"brNDC");
   leg2->SetFillColor(0);
   leg2->SetTextSize(0.025);
   leg2->SetBorderSize(0);

   corPad->Draw();
   for(int ia = 0; ia < nAlgos; ++ia){
     
     if(barrel){
       rsp[ia][i] = (TGraphErrors*)inf[i]->Get(Form("%s/RelRspVsRefPt_JetEta0to1.3",algos[ia].data()));
       res[ia][i] = (TGraphErrors*)inf[i]->Get(Form("%s/RelResVsRefPt_JetEta0to1.3",algos[ia].data()));
     }else{
       rsp[ia][i] = (TGraphErrors*)inf[i]->Get(Form("%s/RelRspVsRefPt",algos[ia].data()));
       res[ia][i] = (TGraphErrors*)inf[i]->Get(Form("%s/RelResVsRefPt",algos[ia].data()));
       cout<<Form("%s/RelRspVsRefPt",algos[ia].data())<<endl;
     }

     leg2->AddEntry((rsp[ia][i]),Form("Response %s",algos[ia].data()),"p");
     leg2->AddEntry((res[ia][i]),Form("Resolution %s",algos[ia].data()),"pl");

     rsp[ia][i]->SetMarkerStyle(20);
     res[ia][i]->SetMarkerStyle(20);
     rsp[ia][i]->SetMarkerSize(0.8);
     res[ia][i]->SetMarkerSize(0.6);
     rsp[ia][i]->SetName(Form("Response_%s_%d",algos[ia].data(),i));
     res[ia][i]->SetName(Form("Resolution_%s_%d",algos[ia].data(),i));
     formatPlot(res[ia][i],ia+1);
     formatPlot(rsp[ia][i],ia+1);
     rsp[ia][i]->Draw("p");
     res[ia][i]->Draw("p");
     rsp[ia][i]->Write();
     res[ia][i]->Write();

   }
   leg->Draw();
   leg2->Draw();
 }

 outf->Write();

}


/*
   if(i == nb - 1){
     TLegend* leg2 =  new TLegend(0.68,0.68,0.94,0.91,NULL,"brNDC");
     leg2->SetFillColor(0);
     leg2->SetTextSize(0.015);
     leg2->SetBorderSize(0);

     leg2->AddEntry("Response","Response","");
     for(int i = 0; i < nAlgos; ++i){
       leg2->AddEntry((rsp[i][0]),algos[i].data(),"p");
     }

     leg2->AddEntry("Resolution","Resolution","");
     for(int i = 0; i < nAlgos; ++i){
       leg2->AddEntry((res[i][0]),algos[i].data(),"pl");
     }

     leg2->Draw();
   }
 }
*/






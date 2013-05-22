
#include <string>
#include <vector>
#include <iostream> //or iostream.h
#include <cmath> // or math.h
#include <TH2D.h>
#include "TNtuple.h"
#include <TH1D.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TSystem.h>
#include <TF1.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TLegend.h>
#include <TCut.h>
#include <TLine.h>
#include "hiForest.h"

void validate(){

TH1::SetDefaultSumw2();
using namespace std;

 HiForest * t = new HiForest("/mnt/hadoop/cms/store/user/icali/HIJING_GEN-SIM_revrese_betap/Hijing_reverse_Dijet30_5p02TeV_FOREST_v1/21a8c2f559597277c134da8e35f2233d/forest_150_1_FWZ.root","",cPPb,1);

 t->InitTree();

 // VERTEX VALIDATION
 TCanvas* cv1 = new TCanvas("cv1","",600,600);
 t->Draw("nVtx","","");

 TCanvas* cv2 = new TCanvas("cv2","",600,600);
 t->Draw("zVtx[maxVtx]","","");

 TCanvas* cv3 = new TCanvas("cv3","",600,600);
 t->Draw("yVtx[maxVtx]:xVtx[maxVtx]","","colz");

 TCanvas* cv4 = new TCanvas("cv4","",600,600);
 t->Draw("maxVtx","","");

 TCanvas* cv5 = new TCanvas("cv5","",600,600);
 t->Draw("zVtx[1]:zVtx[0]","","colz");


 // GEN VALIDATION
 TCut bkg("sube != 0");
 TCut sig("sube == 0");
 TCut chg("chg != 0 && sta == 1");
 TCut genPtMin("refpt > 30");

 // Background
 TCanvas* cg1 = new TCanvas("cg1","",600,600);
 t->Draw("eta",bkg&&chg,"");

 TCanvas* cg2 = new TCanvas("cg2","",600,600);

 TCanvas* cg3 = new TCanvas("cg3","",600,600);

 TCanvas* cg4 = new TCanvas("cg4","",600,600);

 TCanvas* cg5 = new TCanvas("cg5","",600,600);


 // Signal
 TCanvas* cgs1 = new TCanvas("cgs1","",600,600);
 t->Draw("eta",sig&&chg,"");

 TCanvas* cgs2 = new TCanvas("cgs2","",600,600);

 TCanvas* cgs3 = new TCanvas("cgs3","",600,600);

 TCanvas* cgs4 = new TCanvas("cgs4","",600,600);

 TCanvas* cgs5 = new TCanvas("cgs5","",600,600);


 // Simple JES VALIDATION
 TCanvas* cj1 = new TCanvas("cj1","",600,600);
 t->Draw("jpt/refpt:refpt",genPtMin,"colz");
 t->Draw("jpt/refpt:refpt",genPtMin,"prof same");




  TLegend *t4=new TLegend(0.57,0.65,0.49,0.83);
  //    t4->AddEntry(h2,"1 < |#eta| < 2 ","t");
   t4->SetFillColor(0);
    t4->SetBorderSize(0);
    t4->SetFillStyle(0);
    t4->SetTextFont(25);
    t4->SetTextSize(24);


}

#include <TStyle.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TNtuple.h>
#include <iostream>
#include <TLine.h>
#include <TMath.h>
#include <math.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TCut.h>
#include <TClonesArray.h>
#include "commonUtility.h"
#include <TRandom3.h>
#include "CutAndBinCollection2011.h"
#define PI 3.141592653589

struct valPair {
  double val;
  double err;
};


valPair drawDphiDiff(TCut addCut="corrPt>60 && abs(eta)<1.44 && hadronicOverEm<0.1"){
  
  TString fname1 = "barrelHiForestPhoton_MCphoton_all.root";
  TFile *f1=new TFile(fname1.Data());
  TTree *photon1 = (TTree*)f1->Get("yongsunPhotonTree");
  photon1->AddFriend("yEvt=yongsunHiEvt"       ,fname1.Data());
  photon1->AddFriend("ySkim=yongsunSkimTree"   ,fname1.Data());
  photon1->AddFriend("yHlt=yongsunHltTree"     ,fname1.Data());

  TCut generalCut  = etaCut && genMatchCut1 ;
  
  TH1D* hdphi = new TH1D ("hdphi","",100,-0.1,0.05);
  hdphi->Reset();
  photon1->Draw("phi - genMatchedPhi>>hdphi",generalCut && addCut);
  // TF1* ff =  cleverGaus(hdphi,"h",1.8);
  //  double *ps = ff->GetParameters();
  // valPair ret;
  // ret.val = ps[2];
  // ret.err = ff->GetParError(2);
  valPair ret;
  ret.val = hdphi->GetRMS();
  ret.err = hdphi->GetRMSError();
  
  cout << ret.val << " +-" << ret.err << endl;
  hdphi->DrawCopy();
  
  delete hdphi;
  return ret;
}


void drawDphi() { 
 
  TH1D* hdPhi[10];
  for ( int icent = 1 ; icent<=nCent_std ; icent++) 
    hdPhi[icent]    = new TH1D(Form("hdPhi_icent%d",icent),"",nPtBin,ptBin);
  
  for (int icent = 1; icent <=nCent_std; icent++) {
    int lowCent = centBin_std[icent-1];
    int highCent = centBin_std[icent]-1;
    TCut centCut      = Form("yEvt.hiBin >= %d && yEvt.hiBin<= %d",lowCent,highCent);
    for ( int ipt = 1; ipt <= nPtBin ; ipt++){
      TCut ptCut = Form("corrPt>%.2f && corrPt<%.2f",(float)ptBin[ipt-1],(float)ptBin[ipt]);
      valPair aa = drawDphiDiff(centCut && ptCut && "abs(eta)<1.44 && hadronicOverEm<0.1");
      hdPhi[icent]->SetBinContent(ipt,aa.val);
      hdPhi[icent]->SetBinError   (ipt,aa.err);
    }
  }

  TCanvas* c1 = new TCanvas("c1","",500,500);
  c1->SetLeftMargin(0.2);
  TH1D* temp = (TH1D*)hdPhi[1]->Clone("tempTH");
  temp->Reset();
  handsomeTH1(temp,1);
  temp->SetXTitle("pT (Gev)");
  temp->SetYTitle("Resolution of #phi (rad)");
  temp->SetAxisRange(0,0.01,"Y");
  temp->SetAxisRange(60,200,"X");
  temp->GetYaxis()->SetTitleOffset(1.5);
  temp->Draw();
  for (int icent = 1; icent <=nCent_std; icent++) {
    handsomeTH1(hdPhi[icent],color[icent]);
    hdPhi[icent]->Draw("same");
  }
  
  TLegend* legPurity = new TLegend(0.3563218,0.6504237,0.8908046,0.8771186,NULL,"brNDC");
  easyLeg(legPurity,"#phi resolution");
  
  for (int icent = 1; icent <=nCent_std; icent++){
    int lowerCent = centBin_std[icent-1];     int upperCent = centBin_std[icent]-1;
    legPurity->AddEntry(hdPhi[icent],Form("%.0f%% - %.0f%%", float((float)lowerCent*2.5), float((float)(upperCent+1)*2.5)),"pl");
  }
  legPurity->Draw();
  
  c1->SaveAs("dphiOfPhoton.pdf");
}

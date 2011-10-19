
#include "hiForest.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH1D.h"

#include "TCut.h"
#include <string>
using namespace std;
static const bool christof = 0;

void scaleAlongX(TH2* h,int bin, double a, double ea){

  for(int i = 0; i < h->GetNbinsX()+1; ++i){
    double v = h->GetBinContent(i,bin);
    if(v <= 0 ) continue;
    double e = h->GetBinError(i,bin)/v;
    double es = v*sqrt(ea*ea+e*e);

    h->SetBinContent(i,bin,a*v);
    h->SetBinError(i,bin,a*es);
  }
}

void reweightPt(TH2* h1, TH2* h2, TH1* hpt1, TH1* hpt2){

  int nx = h1->GetNbinsX();
  int ny = h1->GetNbinsY();

  for(int i= 0; i < ny+1; ++i){

    double dpt1 = 0, dpt2 = 0, e = 0;

    if(christof){
      dpt1 = h1->Integral(0,nx,i,i);
      dpt2 = h2->Integral(0,nx,i,i);
      h2->IntegralAndError(0,nx,i,i,e);
    }else{
      dpt1 = hpt1->GetBinContent(i);
      dpt2 = hpt2->GetBinContent(i);      
      e = hpt2->GetBinError(i);
    }
     if(dpt2 <= 0) e = 0;
     if(dpt1 > 0)
       scaleAlongX(h1,i,dpt2/dpt1,e/dpt1);
  }
}

void getProjections(TH2* h1, TH1D*& xsi1,TH1D*& norm1, const char* label = "",int i = 0){
  xsi1 = h1->ProjectionX();
  xsi1->SetName(Form("xsi%s%d",label,i));
  norm1 = h1->ProjectionY();
  norm1->SetName(Form("norm%s%d",label,i));
}

void plotXsi(int centIndex = 0){

  bool remake = 1;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TH2D *hin[100], *hia[100], *hinmc[100], *hiamc[100];
  TH1D *xsia[100], *norma[100], *xsin[100], *normn[100];
  TH1D *xsiamc[100], *normamc[100], *xsinmc[100], *normnmc[100];
  TH1D *hptn[100], *hpta[100], *hptnmc[100], *hptamc[100], *hpt[100], *hptmc[100];

  string name[10] = {"central","peripheral","pp"};

  TFile* outf = new TFile(Form("results_xsi_%s.root",name[centIndex].data()),"recreate");

  TH2D* hSmear = new TH2D("hSmear",";;p_{T} (GeV/c);p_{T} fluctuation (GeV/c)",100,0,1000,100,-50,50);

  TH1D* hAJ = new TH1D("hAJ",";A_{J};",10,0,1);
  TH1D* hAJmc = new TH1D("hAJmc",";A_{J};",10,0,1);

  TH2D* heta = new TH2D("heta",";#eta_{Lead};#eta_{Sublead}",50,-5,5,50,-5,5);
  TH2D* hetamc = new TH2D("hetamc",";#eta_{Lead};#eta_{Sublead}",50,-5,5,50,-5,5);

  TH1D* hDphi = new TH1D("hDphi",";#Delta#phi;",160,-8,8);
  TH1D* hDphimc = new TH1D("hDphimc",";#Delta#phi;",160,-8,8);

  bool pp = 0;

  int nAJ = 5;
  double ajMin[10] = {0,    0.13, 0.24, 0.35, 0. , 0, 0};
  double ajMax[10] = {0.13, 0.24, 0.35, 1.,   1. , 0 ,0};

  if(remake){
    
    //    TFile* outf = new TFile(Form("output3.root"),"recreate");

    HiForest * t;
    //    t = new HiForest("dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yjlee/hiForest/merged_HI2010_SD_Jet35_prod05_full.root");
    //    t = new HiForest("./sd_prod05_410.root");
    t = new HiForest("/Users/yetkinyilmaz/analysis/forest_d20101017/skim_Dijet_PbPb.root");
    t->sortJets(t->akPu3jetTree, t->akPu3PF, 2., 40, 1); // add smearing in here. save input as ref  
    t->correlateTracks(t->akPu3jetTree, t->akPu3PF);

    TCut etaLead("1 || abs(akPu3PF.jteta[Lead])>0.5");
    TCut etaSubLead("1 || abs(akPu3PF.jteta[SubLead])>0.5");
   TCut dijet("akPu3PF.HasDijet");
   TCut leadingCone("track.tjDRlead < 0.3");
   TCut subleadingCone("track.tjDRsublead < 0.3");
   TCut track4("track.trkPt > 4");

   TCut c0to30("hiBin < 12");
   TCut c30to100("hiBin >= 12");
   TCut c0to10("hiBin < 4");
   TCut c0to100("1");

   TCut runSelection("0");
   int runs[100] = {150883, 150886, 150887, 151020, 151027, 
		    151058, 151059, 151076, 151077, 151088, 
	
		    151126, 151153, 151211, 151217, 151238, 
		    151239, 151240, 151350, 151351, 151352, 
		    
		    151353, 151878, 151922, 151923, 151935, 
		    151968, 151969, 151975, 152047, 152112, 
		    
		    152113, 152349, 152350, 152391, 152431, 
		    152474, 152477, 152484, 152485, 152652, 
		    
		    152670, 152699, 152705, 152706, 152721, 
		    152722, 152741, 152745, 152751, 152760, 
		    
		    152766, 152785, 152791, 152955, 152957
   };

   for(int r = 0; r < 55; ++r){
     runSelection = runSelection || Form("Run == %d",runs[r]);
   }
   
   TCut evtSel(t->eventSelection());
   evtSel = evtSel && runSelection;

   vector<TCut> cent;
   cent.push_back(c0to30);
   cent.push_back(c30to100);
   cent.push_back(c0to100);

   TCanvas * c1 = new TCanvas("c2","",400,400);
   outf->cd();

   int NxsiBin = 20;

   for(  int i = 0; i < nAJ; ++i){

      hin[i] = new TH2D(Form("hin%d",i),";#xi;",NxsiBin,-1,9,100,0,1000);
      hia[i] = new TH2D(Form("hia%d",i),";#xi;",NxsiBin,-1,9,100,0,1000);
      hpt[i] = new TH1D(Form("hpt%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hptn[i] = new TH1D(Form("hptn%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hpta[i] = new TH1D(Form("hpta%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);

      TCut AJlead(Form("%f <= akPu3PF.AJ && akPu3PF.AJ < %f",ajMin[i],ajMax[i]));
      TCut AJsublead(Form("%f <= akPu3PF.AJ && akPu3PF.AJ < %f",ajMin[i],ajMax[i]));
      
      t->Draw(Form("akPu3PF.jtpt[akPu3PF.Lead]:-log(track.zLead)>>%s",hin[i]->GetName()),
	      dijet&&leadingCone&&cent[centIndex]&&track4&&AJlead&&evtSel&&etaLead);
      
      t->Draw(Form("akPu3PF.jtpt[akPu3PF.SubLead]:-log(track.zSubLead)>>%s",hia[i]->GetName()),
	      dijet&&subleadingCone&&cent[centIndex]&&track4&&AJsublead&&evtSel&&etaSubLead);

      t->Draw(Form("akPu3PF.jtpt[akPu3PF.Lead]>>%s",hptn[i]->GetName()),
              dijet&&cent[centIndex]&&AJlead&&evtSel&&etaLead);

      t->Draw(Form("akPu3PF.jtpt[akPu3PF.SubLead]>>%s",hpta[i]->GetName()),
              dijet&&cent[centIndex]&&AJsublead&&evtSel&&etaSubLead);

   }      

   t->Draw("akPu3PF.AJ>>hAJ",dijet&&cent[centIndex]&&evtSel);
   t->Draw("akPu3PF.jtphi[akPu3PF.Lead]-akPu3PF.jtphi[akPu3PF.SubLead]>>hDphi",dijet&&cent[centIndex]&&evtSel);
   t->Draw("akPu3PF.jteta[akPu3PF.SubLead]:akPu3PF.jteta[akPu3PF.Lead]>>heta",dijet&&cent[centIndex]&&evtSel);
   hDphi->Scale(1./hAJ->Integral());
   heta->Scale(1./hAJ->Integral());
   hAJ->Scale(1./hAJ->Integral());

   delete t;
   //   t = new HiForest("dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yjlee/hiForest/merged_pp2760_AllPhysics_NoPhoyon_Prod02.root","ppForest",1);
   //   t = new HiForest("./sd_prod05_410.root","ppForest",1);                        
   t = new HiForest("/Users/yetkinyilmaz/analysis/forest_d20101017/skim_Dijet_pp1.root","ppForest",1);
   outf->cd();

   evtSel = t->eventSelection();   

   int smear = 0;
   if(centIndex != 0) smear = -1;
   t->sortJets(t->akPu3jetTree, t->akPu3PF, 2., 0, 1, smear); // add smearing in here. save input as ref                 
   t->correlateTracks(t->akPu3jetTree, t->akPu3PF, 1, smear != -1);
   if(centIndex != 0){
     t->tree->SetAlias("smpt","akPu3PF.jtpt");
   }
   t->tree->SetAlias("sAJ","(smpt[akPu3PF.Lead]-smpt[akPu3PF.SubLead])/(smpt[akPu3PF.Lead]+smpt[akPu3PF.SubLead])");

   for(  int i = 0; i < nAJ; ++i){

      hinmc[i] = new TH2D(Form("hinmc%d",i),"",NxsiBin,-1,9,100,0,1000);
      hiamc[i] = new TH2D(Form("hiamc%d",i),"",NxsiBin,-1,9,100,0,1000);

      hptmc[i] = new TH1D(Form("hptmc%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hptnmc[i] = new TH1D(Form("hptnmc%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hptamc[i] = new TH1D(Form("hptamc%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);

      TCut AJlead(Form("%f <= sAJ && sAJ < %f",ajMin[i],ajMax[i]));
      TCut AJsublead(Form("%f <= sAJ && sAJ < %f",ajMin[i],ajMax[i]));
	 
      t->Draw(Form("smpt[akPu3PF.Lead]:-log(track.zLead)>>%s",hinmc[i]->GetName()),
	      dijet&&leadingCone&&track4&&evtSel&&etaLead);
      
      t->Draw(Form("smpt[akPu3PF.SubLead]:-log(track.zSubLead)>>%s",hiamc[i]->GetName()),
	      dijet&&subleadingCone&&track4&&evtSel&&etaSubLead);

      t->Draw(Form("smpt[akPu3PF.Lead]>>%s",hptnmc[i]->GetName()),
              dijet&&evtSel&&etaLead);

      t->Draw(Form("smpt[akPu3PF.SubLead]>>%s",hptamc[i]->GetName()),
              dijet&&evtSel&&etaSubLead);
   
   }
   outf->cd();

   t->Draw("smpt-akPu3PF.jtpt:akPu3PF.jtpt>>hSmear","abs(akPu3PF.jteta) < 2 && akPu3PF.jtpt > 40");
   t->Draw("sAJ>>hAJmc",dijet&&evtSel);
   t->Draw("akPu3PF.jtphi[akPu3PF.Lead]-akPu3PF.jtphi[akPu3PF.SubLead]>>hDphimc",dijet&&evtSel);
   t->Draw("akPu3PF.jteta[akPu3PF.SubLead]:akPu3PF.jteta[akPu3PF.Lead]>>hetamc",dijet&&evtSel);
   hDphimc->Scale(1./hAJmc->Integral());
   hetamc->Scale(1./hAJmc->Integral());
   hAJmc->Scale(1./hAJmc->Integral());

   delete t;
  }else{

    TFile* inf = new TFile("output.root");
    TFile* infMC = new TFile("output.root");

    for(  int i = 0; i < nAJ; ++i){

    hin[i] = (TH2D*)inf->Get(Form("hin%d",i));
    hinmc[i] = (TH2D*)inf->Get(Form("hinmc%d",i));
    hia[i] = (TH2D*)inf->Get(Form("hia%d",i));
    hiamc[i] = (TH2D*)inf->Get(Form("hiamc%d",i));
    }
  }

  cout<<"Draws done"<<endl;
  //  outf->cd();


  for(  int i = 0; i < nAJ; ++i){

    double binwidth = hin[i]->GetXaxis()->GetBinWidth(1);
    bool weightScaled = 0;

    if(weightScaled){
      hin[i]->Scale(1./hptn[i]->Integral()/binwidth);
      hia[i]->Scale(1./hpta[i]->Integral()/binwidth);
      hinmc[i]->Scale(1./hptnmc[i]->Integral()/binwidth);
      hiamc[i]->Scale(1./hptamc[i]->Integral()/binwidth);
      
      hptn[i]->Scale(1./hptn[i]->Integral("width"));
      hpta[i]->Scale(1./hpta[i]->Integral("width"));
      hptnmc[i]->Scale(1./hptnmc[i]->Integral("width"));
      hptamc[i]->Scale(1./hptamc[i]->Integral("width"));
    }

    if(centIndex != 2){
      reweightPt(hinmc[i],hin[i],hptnmc[i],hptn[i]);
      reweightPt(hiamc[i],hia[i],hptamc[i],hpta[i]);
    }


    if(!weightScaled){
      hin[i]->Scale(1./hptn[i]->Integral()/binwidth);
      hia[i]->Scale(1./hpta[i]->Integral()/binwidth);
      hinmc[i]->Scale(1./hptn[i]->Integral()/binwidth);
      hiamc[i]->Scale(1./hpta[i]->Integral()/binwidth);

      hptn[i]->Scale(1./hptn[i]->Integral("width"));
      hpta[i]->Scale(1./hpta[i]->Integral("width"));
      hptnmc[i]->Scale(1./hptnmc[i]->Integral("width"));
      hptamc[i]->Scale(1./hptamc[i]->Integral("width"));
    }

    getProjections(hin[i],xsin[i],normn[i],"n",i);
    getProjections(hinmc[i],xsinmc[i],normnmc[i],"nmc",i);

    getProjections(hia[i],xsia[i],norma[i],"a",i);
    getProjections(hiamc[i],xsiamc[i],normamc[i],"amc",i);

    if(1){
    normn[i]->Reset();
    normn[i]->Add(hptn[i]);
    norma[i]->Reset();
    norma[i]->Add(hpta[i]);

    normnmc[i]->Reset();
    normnmc[i]->Add(hptnmc[i]);
    normamc[i]->Reset();
    normamc[i]->Add(hptamc[i]);
    }

    cout<<"Got projections."<<endl;

  TCanvas* c1 = new TCanvas("c1","",900,900);
  c1->Divide(2,2);

  c1->cd(1);
  xsin[i]->Draw("p");  
  xsinmc[i]->Draw("hist same");

  c1->cd(3);
  normn[i]->Draw("p");
  normnmc[i]->Draw("hist same");

   c1->Print("Fragmentations.gif");
  }

   outf->Write();

   cout<<"Congrats!!!"<<endl;
}


void fragmentation(){

  plotXsi(0);
  plotXsi(1);
  //  plotXsi(2);


}




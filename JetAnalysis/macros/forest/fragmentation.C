
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
static const bool centralOnly = 0;

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

void plotXsi(int centIndex = 0, int etaBin = 0){

  bool remake = 1;
  bool shortCut = 0;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();

  TH2D *hin[100], *hia[100], *hinmc[100], *hiamc[100];
  TH1D *xsia[100], *norma[100], *xsin[100], *normn[100];
  TH1D *xsiamc[100], *normamc[100], *xsinmc[100], *normnmc[100];
  TH1D *hptn[100], *hpta[100], *hptnmc[100], *hptamc[100], *hpt[100], *hptmc[100];
  TH1D *hchn[100], *hcha[100], *hchnmc[100], *hchamc[100], *hch[100], *hchmc[100];
  TH1D* hetan[100], *hetaa[100], *hetaDijet[100],* hetanmc[100], *hetaamc[100], *hetaDijetmc[100];

  TH2D *hTrkWeightN[100], *hTrkWeightA[100], *hTrkWeightNmc[100], *hTrkWeightAmc[100];

  string name[10] = {"central","peripheral","pp"};

  TFile* outf = new TFile(
			  Form("results_xsi_%s%s.root",
			       name[centIndex].data(),
			       etaBin == 0 ? "" : Form("_eta%d",etaBin)
			       ),"recreate");

  TH2D* hSmear = new TH2D("hSmear",";;p_{T} (GeV/c);p_{T} fluctuation (GeV/c)",100,0,1000,100,-50,50);

  TH1D* hAJ = new TH1D("hAJ",";A_{J};",20,-1,1);
  TH1D* hAJmc = new TH1D("hAJmc",";A_{J};",20,-1,1);

  TH2D* hpt2D = new TH2D("hpt2D",";p_{T}^{Lead} (GeV/c);p_{T}^{SubLead} (GeV/c)",100,0,1000,100,0,1000);

  TH2D* heta = new TH2D("heta",";#eta_{Lead};#eta_{Sublead}",50,-5,5,50,-5,5);
  TH2D* hetamc = new TH2D("hetamc",";#eta_{Lead};#eta_{Sublead}",50,-5,5,50,-5,5);

  TH2D* hAJeta = new TH2D("hAJeta","",100,-5,5,10,0,1);
  TH2D* hAJetamc = new TH2D("hAJetamc","",100,-5,5,10,0,1);

  TH1D* hDphi = new TH1D("hDphi",";#Delta#phi;",160,-8,8);
  TH1D* hDphimc = new TH1D("hDphimc",";#Delta#phi;",160,-8,8);

  TH1D* hRun = new TH1D("hRun",";Run;N_{dijets}",3400,150600,154000);

  TH2D* hZ = new TH2D("hZ",";old;new",120,0,1.2,120,0,1.2);
  TH2D* hXsi = new TH2D("hXsi",";old;new",120,0,6,120,0,6);

  TH2D* hCorrelationLead = new TH2D("hCorrelationLead",";#Delta#eta;#Delta#phi",100,-5,5,100,-5,5);

  bool pp = 0;

  int nAJ = 5;
  double ajMin[10] = {0,    0.13, 0.24, 0.35, 0. , 0, 0};
  double ajMax[10] = {0.13, 0.24, 0.35, 1.,   1. , 0 ,0};

  int nEta = 4;
  double etaMin[10] = {0,  0,    0.5,  1.};
  double etaMax[10] = {5., 0.5,  1.,   2.};

  if(remake){
    
    TCut etaLead("1 || abs(akPu3PF.jteta[Lead])>0.5");
    TCut etaSubLead("1 || abs(akPu3PF.jteta[SubLead])>0.5");

    TCut etaEvent(Form("abs(akPu3PF.dijetEta) >= %f && abs(akPu3PF.dijetEta) <= %f",etaMin[etaBin],etaMax[etaBin]));

    TCut dijet("akPu3PF.HasDijet");
    TCut leadingCone("track.tjDRlead < 0.3");
   TCut subleadingCone("track.tjDRsublead < 0.3");
   TCut track4("track.trkPt > 4");

   TCut correctionLead("track.corrLead");
   TCut correctionSubLead("track.corrSubLead");

   dijet = dijet&&etaEvent; 

   if(0){
     correctionLead = "1";
     correctionSubLead = "1";
   }

   TCut c0to30("hiBin < 12");
   TCut c30to100("hiBin >= 12");
   TCut c0to10("hiBin < 4");
   TCut c0to100("1");

   TCut runSelection("1");
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
   
   vector<TCut> cent;
   cent.push_back(c0to30);
   cent.push_back(c30to100);
   cent.push_back(c0to100);

   TCanvas * c1 = new TCanvas("c2","",400,400);
   outf->cd();

   int NxsiBin = 20;

   HiForest * t;
   t = new HiForest("/Users/yetkinyilmaz/analysis/forest_d20101025/skim_Dijet_PbPb1.root");
   outf->cd();

   TCut evtSel(t->eventSelection());
   evtSel = evtSel && runSelection;

   t->sortJets(t->akPu3jetTree, t->akPu3PF, 2., 40, 1); // add smearing in here. save input as ref 
   t->correlateTracks(t->akPu3jetTree, t->akPu3PF);

   if(!shortCut){

   for(  int i = 0; i < nAJ; ++i){

      hin[i] = new TH2D(Form("hin%d",i),";#xi;",NxsiBin,-1,9,100,0,1000);
      hia[i] = new TH2D(Form("hia%d",i),";#xi;",NxsiBin,-1,9,100,0,1000);
      hpt[i] = new TH1D(Form("hpt%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hptn[i] = new TH1D(Form("hptn%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);
      hpta[i] = new TH1D(Form("hpta%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,1000);

      hch[i] = new TH1D(Form("hch%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,100);

      hetan[i] = new TH1D(Form("hetan%d",i),"",20,0,2);
      hetaa[i] = new TH1D(Form("hetaa%d",i),"",20,0,2);
      hetaDijet[i] = new TH1D(Form("hetaDijet%d",i),"",20,0,2);

      hTrkWeightN[i] = new TH2D(Form("hTrkWeightN%d",i),";p_{T}^{Track} (GeV/c); weight",100,0,100,200,0,4);
      hTrkWeightA[i] = new TH2D(Form("hTrkWeightA%d",i),";p_{T}^{Track} (GeV/c); weight",100,0,100,200,0,4);

      TCut AJ(Form("%f <= akPu3PF.AJ && akPu3PF.AJ < %f",ajMin[i],ajMax[i]));
      
      t->Draw(Form("akPu3PF.jtpt[akPu3PF.Lead]:-log(track.zLead)>>%s",hin[i]->GetName()),
	      (
	       dijet
               &&cent[centIndex]
	       &&AJ
	       &&evtSel
	       &&etaLead
               &&track4
	       &&leadingCone
	       )
	      *correctionLead
	      );
      
      t->Draw(Form("akPu3PF.jtpt[akPu3PF.SubLead]:-log(track.zSubLead)>>%s",hia[i]->GetName()),
	      (	       
	       dijet
	       &&cent[centIndex]
	       &&AJ
	       &&evtSel
	       &&etaSubLead
	       &&track4	       
	       &&subleadingCone
		       )
	      *correctionSubLead
              );
      
      cout<<"Weight and Selection : "<<(const char*)correctionSubLead*(dijet&&subleadingCone&&cent[centIndex]&&track4&&AJ&&evtSel&&etaSubLead)<<endl;

      t->Draw(Form("akPu3PF.jtpt[akPu3PF.Lead]>>%s",hptn[i]->GetName()),
              dijet&&cent[centIndex]&&AJ&&evtSel&&etaLead);
      
      t->Draw(Form("akPu3PF.jtpt[akPu3PF.SubLead]>>%s",hpta[i]->GetName()),
              dijet&&cent[centIndex]&&AJ&&evtSel&&etaSubLead);

      t->Draw(Form("abs(akPu3PF.jteta[akPu3PF.Lead])>>%s",hetan[i]->GetName()),
              dijet&&cent[centIndex]&&AJ&&evtSel&&etaLead);

      t->Draw(Form("abs(akPu3PF.jteta[akPu3PF.SubLead])>>%s",hetaa[i]->GetName()),
              dijet&&cent[centIndex]&&AJ&&evtSel&&etaLead);

      t->Draw(Form("abs(akPu3PF.dijetEta)>>%s",hetaDijet[i]->GetName()),
              dijet&&cent[centIndex]&&AJ&&evtSel);

      t->Draw(Form("track.corrLead:track.trkPt>>%s",hTrkWeightN[i]->GetName()),
	      (
               dijet
               &&cent[centIndex]
               &&AJ
               &&evtSel
               &&etaLead
               &&track4
               &&leadingCone
               )
              *correctionLead
	      );

      t->Draw(Form("track.corrSubLead:track.trkPt>>%s",hTrkWeightA[i]->GetName()),
              (
               dijet
               &&cent[centIndex]
               &&AJ
               &&evtSel
               &&etaSubLead
               &&track4
               &&subleadingCone
               )
              *correctionSubLead
              );

      t->Draw(Form("track.trkPt>>%s",hch[i]->GetName()),
	      (
               dijet
               &&cent[centIndex]
               &&AJ
               &&evtSel
               &&etaLead
               &&track4
               &&leadingCone
               )
              *correctionLead
              );

   }      

   

   t->Draw("akPu3PF.jtpt[akPu3PF.SubLead]:akPu3PF.jtpt[akPu3PF.Lead]>>hpt2D",dijet&&cent[centIndex]&&evtSel);

   t->Draw("akPu3PF.AJ>>hAJ",dijet&&cent[centIndex]&&evtSel);

   t->Draw("akPu3PF.AJ:akPu3PF.dijetEta>>hAJeta",dijet&&cent[centIndex]&&evtSel);

   t->Draw("akPu3PF.jtphi[akPu3PF.Lead]-akPu3PF.jtphi[akPu3PF.SubLead]>>hDphi",dijet&&cent[centIndex]&&evtSel);
   t->Draw("akPu3PF.jteta[akPu3PF.SubLead]:akPu3PF.jteta[akPu3PF.Lead]>>heta",dijet&&cent[centIndex]&&evtSel);

   t->Draw("Run>>hRun",dijet&&evtSel);

   t->Draw("track.zSubLead:track.zOldSubLead>>hZ",dijet&&evtSel&&subleadingCone&&track4);

   t->Draw("-log(track.zSubLead):-log(track.zOldSubLead)>>hXsi",dijet&&evtSel&&subleadingCone&&track4);

   cout<<"Event selection : "<<(const char*)(dijet&&cent[centIndex]&&evtSel)<<endl;

   hDphi->Scale(1./hAJ->Integral("width"));
   heta->Scale(1./hAJ->Integral("width"));
   hAJ->Scale(1./hAJ->Integral("width"));

   }   

   TCanvas* cEvtDebug = new TCanvas("cEvtDebug","cEvtDebug",900,400);
   cEvtDebug->Divide(2,1);
   cEvtDebug->cd(1);
   t->tree->Scan("Event:akPu3PF.jtpt",evtSel&&dijet&&c0to30&&"akPu3PF.AJ > 0.24 && akPu3PF.AJ < 0.35"&&"-log(track.zOldLead)>4"&&leadingCone&&track4);
   t->tree->Scan("Event:track.trkPt",evtSel&&dijet&&c0to30&&"akPu3PF.AJ > 0.24 && akPu3PF.AJ < 0.35"&&"-log(track.zOldLead)>4"&&leadingCone&&track4);

   cEvtDebug->cd(2);
   
   t->tree->Scan("Event:akPu3PF.jtpt",(evtSel&&dijet&&c0to30&&"akPu3PF.AJ > 0.35")&&"-log(track.zOldLead)>4"&&leadingCone&&track4);
   t->tree->Scan("Event:track.trkPt",(evtSel&&dijet&&c0to30&&"akPu3PF.AJ > 0.35")&&"-log(track.zOldLead)>4"&&leadingCone&&track4);

   if(shortCut) return;

   TCanvas* cEvtDebug2 = new TCanvas("cEvtDebug2","cEvtDebug2",900,400);
   cEvtDebug2->Divide(2,1);
   cEvtDebug2->cd(1);

   delete t;
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
      hchmc[i] = new TH1D(Form("hchmc%d",i),";p_{T} (GeV/c);dN/dp_{T}",100,0,100);
      hTrkWeightNmc[i] = new TH2D(Form("hTrkWeightNmc%d",i),";p_{T}^{Track} (GeV/c); weight",100,0,100,200,0,4);
      hTrkWeightAmc[i] = new TH2D(Form("hTrkWeightAmc%d",i),";p_{T}^{Track} (GeV/c); weight",100,0,100,200,0,4);

      hetanmc[i] = new TH1D(Form("hetanmc%d",i),"",20,0,2);
      hetaamc[i] = new TH1D(Form("hetaamc%d",i),"",20,0,2);
      hetaDijetmc[i] = new TH1D(Form("hetaDijetmc%d",i),"",20,0,2);


   }

   for(  int i = nAJ-1; i < nAJ; ++i){

      t->Draw(Form("smpt[akPu3PF.Lead]:-log(track.zLead)>>%s",hinmc[i]->GetName()),
	      (
               dijet
               &&evtSel
               &&etaLead
               &&track4
               &&leadingCone
               )
              *correctionLead
              );
      
      t->Draw(Form("smpt[akPu3PF.SubLead]:-log(track.zSubLead)>>%s",hiamc[i]->GetName()),
	      (
               dijet
               &&evtSel
               &&etaSubLead
               &&track4
               &&subleadingCone
               )
              *correctionSubLead
              );

      t->Draw(Form("smpt[akPu3PF.Lead]>>%s",hptnmc[i]->GetName()),
              dijet&&evtSel&&etaLead);

      t->Draw(Form("smpt[akPu3PF.SubLead]>>%s",hptamc[i]->GetName()),
              dijet&&evtSel&&etaSubLead);

      t->Draw(Form("abs(akPu3PF.jteta[akPu3PF.Lead])>>%s",hetanmc[i]->GetName()),
              dijet&&evtSel&&etaLead);

      t->Draw(Form("abs(akPu3PF.jteta[akPu3PF.SubLead])>>%s",hetaamc[i]->GetName()),
              dijet&&evtSel&&etaLead);

      t->Draw(Form("abs(akPu3PF.dijetEta)>>%s",hetaDijetmc[i]->GetName()),
              dijet&&evtSel);

      t->Draw(Form("track.corrLead:track.trkPt>>%s",hTrkWeightNmc[i]->GetName()),
              (
               dijet
               &&evtSel
               &&etaLead
               &&track4
               &&leadingCone
               )
              *correctionLead
              );

      t->Draw(Form("track.corrSubLead:track.trkPt>>%s",hTrkWeightAmc[i]->GetName()),
              (
               dijet
               &&evtSel
               &&etaSubLead
               &&track4
               &&subleadingCone
               )
              *correctionSubLead
              );

      t->Draw(Form("track.trkPt>>%s",hchmc[i]->GetName()),
	      (
               dijet
               &&evtSel
               &&etaLead
               &&track4
               &&leadingCone
               )
              *correctionLead
              );
      
   }

   for(  int i = 0; i < nAJ-1; ++i){
     hinmc[i]->Add(hinmc[nAJ-1]);
     hiamc[i]->Add(hiamc[nAJ-1]);
     hptnmc[i]->Add(hptnmc[nAJ-1]);
     hptamc[i]->Add(hptamc[nAJ-1]);
     hchmc[i]->Add(hchmc[nAJ-1]);
   }

   outf->cd();

   t->Draw("smpt-akPu3PF.jtpt:akPu3PF.jtpt>>hSmear","abs(akPu3PF.jteta) < 2 && akPu3PF.jtpt > 40");
   t->Draw("sAJ>>hAJmc",dijet&&evtSel);
   t->Draw("sAJ:akPu3PF.dijetEta>>hAJetamc",dijet&&evtSel);

   t->Draw("akPu3PF.jtphi[akPu3PF.Lead]-akPu3PF.jtphi[akPu3PF.SubLead]>>hDphimc",dijet&&evtSel);
   t->Draw("akPu3PF.jteta[akPu3PF.SubLead]:akPu3PF.jteta[akPu3PF.Lead]>>hetamc",dijet&&evtSel);
   hDphimc->Scale(1./hAJmc->Integral("width"));
   hetamc->Scale(1./hAJmc->Integral("width"));
   hAJmc->Scale(1./hAJmc->Integral("width"));

   t->Draw("track.tjDphiLead:track.tjDetaLead>>hCorrelationLead",correctionLead*(dijet&&leadingCone&&track4&&evtSel&&etaLead),"");

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

    hch[i]->Scale(1./hptn[i]->Integral()/binwidth);
    hchmc[i]->Scale(1./hptnmc[i]->Integral()/binwidth);

    hetan[i]->Scale(1./hptn[i]->Integral()/binwidth);
    hetaa[i]->Scale(1./hpta[i]->Integral()/binwidth);
    hetaDijet[i]->Scale(1./hptn[i]->Integral()/binwidth);

    hetanmc[i]->Scale(1./hptnmc[i]->Integral()/binwidth);
    hetaamc[i]->Scale(1./hptamc[i]->Integral()/binwidth);
    hetaDijetmc[i]->Scale(1./hptnmc[i]->Integral()/binwidth);

    if(weightScaled){

      hin[i]->Scale(1./hptn[i]->Integral()/binwidth);
      hia[i]->Scale(1./hpta[i]->Integral()/binwidth);
      hinmc[i]->Scale(1./hptnmc[i]->Integral()/binwidth);
      hiamc[i]->Scale(1./hptamc[i]->Integral()/binwidth);

      if(0){      
	hptn[i]->Scale(1./hptn[i]->Integral("width"));
	hpta[i]->Scale(1./hpta[i]->Integral("width"));
	hptnmc[i]->Scale(1./hptnmc[i]->Integral("width"));
	hptamc[i]->Scale(1./hptamc[i]->Integral("width"));
      }
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
  
   c1->cd(2);
   hpt2D->Draw("colz");
   hCorrelationLead->Draw("surf2");
   
   c1->cd(4);
   hAJ->Draw();
  }
   outf->Write();

   cout<<"Congrats!!!"<<endl;
}


void fragmentation(){

  for(int i = 0; i < 4; ++i){
    if(centralOnly){
      plotXsi(0,i);
    }else{
      plotXsi(0,i);
      plotXsi(1,i);
      plotXsi(2,i);
    }
  }



}




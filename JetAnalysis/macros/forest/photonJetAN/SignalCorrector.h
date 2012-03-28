#ifndef SignalCorrector_h
#define SignalCorrector_h
#include "TF1.h"

//---------------------------------------------------------------------
class Region
{
public:
   Region(TString regName, TString v, TCut c, TString w) :
   name(regName),var(v),cut(c),weight(w),
   n(0),nExtrap(0),normBinWidth(false)
   {}
   
   void Init(TTree * t, int nbins, float xmin, float xmax) {
      float * bins = new float[nbins+1];
      float dx = (xmax-xmin)/nbins;
      for (int i=0; i<nbins+1; ++i) bins[i] = xmin+i*dx;
      Init(t,nbins,bins);
   }
   
   void Init(TTree * t, int nbins, float *bins) {
      cut*=weight;
      h = new TH1D(name,"",nbins,bins);
      if (var!="") {
         n = t->Project(h->GetName(),var,cut);
         if (TString(cut).Contains("cBin>=0.0")&&TString(cut).Contains("Jet")) cout << "  " << h->GetName() << "  draw: " << var << " cut: " << TString(cut) << ": " << n << endl;
      }
   }
   
   void Extrapolate(float scale) {
      hExtrap = (TH1D*)h->Clone(Form("%sExtrap",h->GetName()));
      hExtrap->Scale(scale);
      nExtrap = n*scale;
   }
   
   void Normalize(float norm) {
      hExtrapNorm = (TH1D*)hExtrap->Clone(Form("%sExtrapNorm",hExtrap->GetName()));
      hExtrapNorm->Scale(norm/hExtrapNorm->Integral());
      if (normBinWidth) hExtrapNorm->Scale(1./hExtrapNorm->GetBinWidth(1));
   }
   
   TH1D * h;
   TH1D * hExtrap;
   TH1D * hExtrapNorm;
   TString name;
   TString var;
   TCut cut;
   TString weight;
   float n;
   float nExtrap;
   bool normBinWidth;
};

//---------------------------------------------------------------------
class SignalCorrector
{
public:
   SignalCorrector(TTree * tree, TString n, TString var, TCut s, TString w="(1==1)", int bin=-1, int srcType=1) : 
   name(n),
   observable(var),
   sel(s),
   rSigAllPho(n+"SignalAllPho","photonEt",s,w),
   rBkgSShapeAllPho(n+"BkgSShapeAllPho","photonEt",s,w),
   rSigAll(n+"SignalAll",var,s,w),
   rBkgDPhi(n+"BkgDPhi",var,s,w),
   rBkgSShape(n+"BkgSShape",var,s,w),
   rBkgSShapeDPhi(n+"BkgSShapeDPhi",var,s,w),
   rSubtracted(n+"Subtracted",var,s,w),
   weight(w),
   subDPhiSide(true),
   subSShapeSide(true),
   subSShapeSideDPhiSide(true),
   centBin(bin),
   dataSrcType(srcType),
   nSelPhoton(0),fracDPhiBkg(0),fracPhotonBkg(0),fracPhotonDPhiBkg(0) {
      t = tree;
      // photon purity values
      hPhotonPurity = (TH1D*)gDirectory->FindObjectAny("hPhotonPurity");
      if (!hPhotonPurity) hPhotonPurity = new TH1D("hPhotonPurity","",4,0,4);
      
      verbosity=0;
      if (TString(s).Contains("cBin>=0.0")) {
         verbosity=1;
      }
   }
   
   void SetPhotonIsolation(int isolScheme)
   {
//      bool doSys = false;
      //
      // Centrality bins: 0=0-4, 1=4-12, 2=12-20, 3=20-40
      // 
      if (isolScheme==0) { //sum isol
         nameIsol="Sum(Isol.)<1GeV";
         cutIsol = "(cc4+cr4+ct4PtCut20)/0.9 <1";
         hPhotonPurity->SetBinContent(1,0.74);
         hPhotonPurity->SetBinContent(2,0.77);
         hPhotonPurity->SetBinContent(3,0.79);
         hPhotonPurity->SetBinContent(4,0.83);
      } else if (isolScheme==1) { // cut isol
         nameIsol="3DCutIsol.";
         cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
         hPhotonPurity->SetBinContent(1,0.46);
         hPhotonPurity->SetBinContent(2,0.62);
         hPhotonPurity->SetBinContent(3,0.54);
         hPhotonPurity->SetBinContent(4,0.54);
      } else if (isolScheme==2) { // fisher isol
         nameIsol="Fisher Isol. > 0.3";
         t->SetAlias("fisherIsol","(4.6774452168946995e-01 +(cc5-cc1) *9.6796013515455164e-04 +(cc4-cc1) *-1.2788583705647016e-02 +(cc3-cc1) *1.3674667235554151e-02 +(cc2-cc1) *-7.4576842527504350e-02 +(cr5) *-1.2105656031270820e-02 +(cr4) *-1.8158418924831903e-03 +(cr3) *-1.4267772594659891e-02 +(cr2) *-3.0555858981100050e-02 +(ct5PtCut20) *6.4351309460660500e-03 +(ct4PtCut20) *-7.3308097775112357e-03 +(ct3PtCut20) *-2.2250052480332189e-03 +(ct2PtCut20) *-2.4645948244900417e-02 +(ct1PtCut20) *2.1959860851889978e-03)");
         cutIsol = "fisherIsol>0.3";
         hPhotonPurity->SetBinContent(1,0.77);
         hPhotonPurity->SetBinContent(2,0.75);
         hPhotonPurity->SetBinContent(3,0.72);
         hPhotonPurity->SetBinContent(4,0.76);
      }
//      if (doSys) {
//         for (int i=1; i<=hPhotonPurity->GetNbinsX(); ++i) hPhotonPurity->SetBinContent(i,hPhotonPurity->GetBinContent(i)*1.2);
//      }
      
      // Isolation Cut
      sel = sel&&cutIsol;
      // Photon Purity
      if (subSShapeSide) {
         if (dataSrcType==1) {
            fracPhotonBkg = 1-hPhotonPurity->GetBinContent(centBin+1);
         } else if (dataSrcType==2) { // for now use peripheral purity for pp 2.76TeV
            fracPhotonBkg = 1-hPhotonPurity->GetBinContent(4);
         } else if (dataSrcType==3) {
            if (isolScheme==0) fracPhotonBkg = 1-0.79;
            if (isolScheme==2) fracPhotonBkg = 1-0.75;
         }
      }
      if (verbosity>0) cout << nameIsol << " Purity: " << 1-fracPhotonBkg << endl;
   }
   
   void SetJetWeights(TString jetvar="inclJetPt")
   {
      //
      // Centrality bins: 0=0-4, 1=4-12, 2=12-20, 3=20-40
      //
      TString jetweight;
      if (dataSrcType<=1) {
         if (centBin==0) {
            jetweight = Form("1./(0.992966*0.5*(TMath::Erf(-0.627825+0.054612*%s)+1))",jetvar.Data());
         } else if (centBin==1) {
            jetweight = Form("1./(1.000029*0.5*(TMath::Erf(-0.571441+0.049538*%s)+1))",jetvar.Data());
         } else if (centBin==2) {
            jetweight = Form("1./(0.997227*0.5*(TMath::Erf(-0.695991+0.051474*%s)+1))",jetvar.Data());
         } else if (centBin==3) {
            jetweight = Form("1./(0.998959*0.5*(TMath::Erf(-0.898526+0.059567*%s)+1))",jetvar.Data());
         }
      } else { // for now use peripheral for pp 2.76TeV
         jetweight = Form("1./(0.998959*0.5*(TMath::Erf(-0.898526+0.059567*%s)+1))",jetvar.Data());
      }
      if (verbosity>0) cout << "Jet weight: " << jetweight << endl;
      
      rSigAll.weight += "*"+jetweight;
      rBkgSShape.weight += "*"+jetweight;
   }

   void MakeHistograms(TCut sigSel, int nbin, float xmin, float xmax) {
      float * bins = new float[nbin+1];
      float dx = (xmax-xmin)/nbin;
      for (int i=0; i<nbin+1; ++i) {
         bins[i] = xmin+i*dx;
      }
      MakeHistograms(sigSel,nbin,bins);
   }
   
   void MakeHistograms(TCut sigSel, int nbin, float * bins) {
      // setup cuts
      if (verbosity>1) cout << "Base Selection: " << sel << endl;
      rSigAllPho.cut         = sel&&cutSigAllPho;
      rBkgSShapeAllPho.cut   = sel&&cutSShapeAllPho;
      rSigAll.cut            = sel&&sigSel;
      rBkgDPhi.cut           = sel&&cutBkgDPhi;
      rBkgSShape.cut         = sel&&cutSShape;
      rBkgSShapeDPhi.cut     = sel&&cutSShapeDPhi;
      
      rSigAllPho.Init(t,80,0,400);
      rBkgSShapeAllPho.Init(t,80,0,400);
      rSigAll.Init(t,nbin,bins);
      rBkgDPhi.Init(t,nbin,bins);
      rBkgSShape.Init(t,nbin,bins);
      rBkgSShapeDPhi.Init(t,nbin,bins);
      
      // photon normalization
      nSelPhoton = t->GetEntries(rSigAllPho.cut);
      // number of events in signal region
      if (verbosity>0) cout << " ** Number of selection photons: " << rSigAllPho.n << " gamma-jets: " << rSigAll.n << " ** " << endl;
   }
   
   void Extrapolate(float dphisidescale=1) {
      // Scales
      float sssidescale = 0,ssdphisidescale=0;
      if (rBkgSShape.n>0) {
         sssidescale = rSigAllPho.n*fracPhotonBkg/rBkgSShapeAllPho.n;
         ssdphisidescale = dphisidescale*sssidescale;
      }
      if (verbosity>0) {
         cout << " Bkg scale dphi: " << dphisidescale << endl;
         cout << " Bkg scale ss: " << sssidescale << endl;
         cout << " Bkg scale ssdphi: " << ssdphisidescale << endl;
      }

      rSigAllPho.Extrapolate(1-fracPhotonBkg);
      rSigAll.Extrapolate(1.);
      rBkgSShape.Extrapolate(sssidescale);
      rBkgDPhi.Extrapolate(dphisidescale);
      rBkgSShapeDPhi.Extrapolate(ssdphisidescale);

      // Fractions
      if (rSigAll.n>0) {
         fracDPhiBkg = rBkgDPhi.n * dphisidescale/rSigAll.n;
         fracPhotonDPhiBkg = rBkgSShapeDPhi.n * ssdphisidescale/rSigAll.n;
      }
   }

   // special case for dphi
   void ExtrapolateDPhiHist(float dphiSigCut=0.7) {
      float binw = 3.1415926/20;
      float fitmin=dphiSigCut+binw;
      float fitmax=3.1415926/2+binw;
      TF1 *p0 = new TF1("p0","pol0",fitmin,fitmax);
      if (subDPhiSide&&rBkgDPhi.n>=10) {
         p0->SetParameter(0,rBkgDPhi.hExtrap->GetBinContent(rBkgDPhi.hExtrap->FindBin(3.14/2)));
         rBkgDPhi.hExtrap->Fit("p0","","",fitmin,fitmax);
         for (int i=rBkgDPhi.hExtrap->FindBin(dphiSigCut); i<=rBkgDPhi.hExtrap->GetNbinsX(); ++i) {
            rBkgDPhi.hExtrap->SetBinContent(i,p0->GetParameter(0));
            rBkgDPhi.hExtrap->SetBinError(i,p0->GetParError(0));
         }
      }
      if (subSShapeSideDPhiSide&&rBkgSShapeDPhi.n>=10) {
         rBkgSShapeDPhi.hExtrap->Fit("p0","","",fitmin,fitmax);
         for (int i=rBkgSShapeDPhi.hExtrap->FindBin(dphiSigCut); i<=rBkgSShapeDPhi.hExtrap->GetNbinsX(); ++i) {
            rBkgSShapeDPhi.hExtrap->SetBinContent(i,p0->GetParameter(0));
            rBkgSShapeDPhi.hExtrap->SetBinError(i,p0->GetParError(0));
         }
      }
   }
   
   void SubtractBkg() {
      rSubtracted.hExtrap = (TH1D*)rSigAll.h->Clone(rSubtracted.name+"Extrap");
      rSubtracted.nExtrap = rSigAll.nExtrap;
      if (verbosity>1) cout << "Raw Sig: " << rSigAll.nExtrap;
      if (subDPhiSide) {
         rSubtracted.hExtrap->Add(rBkgDPhi.hExtrap,-1);
         rSubtracted.nExtrap -= rBkgDPhi.nExtrap;
         if (verbosity>1) cout << " - " << rBkgDPhi.nExtrap;
      }
      if (subSShapeSide) {
         if (subSShapeSideDPhiSide) {
            rBkgSShape.hExtrap->Add(rBkgSShapeDPhi.hExtrap,-1);
            rBkgSShape.nExtrap -= rBkgSShapeDPhi.nExtrap;
            if (verbosity>1) cout << " + " << rBkgSShapeDPhi.nExtrap;
         }
         rSubtracted.hExtrap->Add(rBkgSShape.hExtrap,-1);
         rSubtracted.nExtrap -= rBkgSShape.nExtrap;
         if (verbosity>1) cout << " - " << rBkgSShape.nExtrap;
      }
      // store rSubtracted.nExtrap in histogram
      rSubtracted.hExtrap->SetEntries(rSubtracted.nExtrap);
      if (verbosity>1) {
         cout << " =? " << rSubtracted.nExtrap << endl;
         cout << "Check Integ:  " << rSigAll.hExtrap->Integral() << " - " << 
         rBkgDPhi.hExtrap->Integral() << " - " << rBkgSShape.hExtrap->Integral() << " + " << rBkgSShapeDPhi.hExtrap->Integral()
         << " = " << rSubtracted.hExtrap->Integral() << endl;
      }
   }
   
   void Normalize(int normMode=1) { // 0=area is signal region count, 1=unit normalization, 2=per photon normalization
      if (normMode==0) {
         rSigAll.hExtrapNorm = (TH1D*)rSigAll.hExtrap->Clone(Form("%sExtrapNorm",rSigAll.hExtrap->GetName()));
         rBkgDPhi.hExtrapNorm = (TH1D*)rBkgDPhi.hExtrap->Clone(Form("%sExtrapNorm",rBkgDPhi.hExtrap->GetName()));
         rBkgSShape.hExtrapNorm = (TH1D*)rBkgSShape.hExtrap->Clone(Form("%sExtrapNorm",rBkgSShape.hExtrap->GetName()));
         rBkgSShapeDPhi.hExtrapNorm = (TH1D*)rBkgSShapeDPhi.hExtrap->Clone(Form("%sExtrapNorm",rBkgSShapeDPhi.hExtrap->GetName()));
         rSubtracted.hExtrapNorm = (TH1D*)rSubtracted.hExtrap->Clone(Form("%sExtrapNorm",rSubtracted.hExtrap->GetName()));
      } else {
         float rawarea=1,area=1;
         if (normMode%10==2) {
            rawarea*=(rSigAll.h->Integral())/rSigAllPho.h->Integral();
            area*=(rSubtracted.hExtrap->Integral()) / (rSigAllPho.hExtrap->Integral());
         }
         rSigAll.Normalize(rawarea);
         rSubtracted.Normalize(area);
         if (normMode<10) {
            rBkgDPhi.Normalize(rawarea*fracDPhiBkg);
            rBkgSShape.Normalize(rawarea*fracPhotonBkg);
            rBkgSShapeDPhi.Normalize(rawarea*fracPhotonDPhiBkg);
         } else if (normMode>=20) {
            rBkgDPhi.Normalize(rawarea*fracDPhiBkg);
            rBkgSShape.Normalize(rawarea);
            rBkgSShapeDPhi.Normalize(rawarea*fracPhotonDPhiBkg);
         }
         if (verbosity>0) cout << "Norlamize to: " << area << " chk integ: " << rSubtracted.hExtrapNorm->Integral() << endl;
      }
   }
   
   TTree * t;
   TString name,nameIsol,observable;
   TCut sel,cutIsol;
   Region rSigAllPho;
   Region rBkgSShapeAllPho;
   Region rSigAll;
   Region rBkgDPhi;
   Region rBkgSShape;
   Region rBkgSShapeDPhi;
   Region rSubtracted;
   TString weight;
   bool subDPhiSide;
   bool subSShapeSide;
   bool subSShapeSideDPhiSide;
   TCut cutSigAllPho;
   TCut cutSShapeAllPho;
   TCut cutBkgDPhi;
   TCut cutSShape;
   TCut cutSShapeDPhi;   
   float nSelPhoton;
   float fracDPhiBkg;
   float fracPhotonBkg;
   float fracPhotonDPhiBkg;
   int centBin;
   int dataSrcType;
   TH1D * hPhotonPurity;
   int verbosity;
};

double calcMean(TH1* h){
   double tot = 0;
   double integral=  0;
   for(int i = 1; i <= h->GetNbinsX(); ++i){
      double x = h->GetBinCenter(i);
      double y = h->GetBinContent(i);
      tot += y*x;
      integral += y;
   }
   return tot/integral;
}

#endif

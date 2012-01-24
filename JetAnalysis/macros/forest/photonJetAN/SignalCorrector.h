#ifndef SignalCorrector_h
#define SignalCorrector_h
#include "TF1.h"

//---------------------------------------------------------------------
class Region
{
public:
   Region(TString regName, TString v, TCut c, TString w) :
   name(regName),var(v),cut(c),weight(w),
   n(0),nExtrap(0)
   {}
   void Init(TTree * t, int nbins, float *bins) {
      cut*=weight;
      h = new TH1D(name,"",nbins,bins);
      n = t->Project(h->GetName(),var,cut);
      cout << "  " << h->GetName() << "  draw: " << var << " cut: " << TString(cut) << ": " << n << endl;
   }
   
   void Extrapolate(float scale) {
      hExtrap = (TH1D*)h->Clone(Form("%sExtrap",h->GetName()));
      hExtrap->Scale(scale);
      nExtrap = n*scale;
   }
   
   void Normalize(float norm) {
      hExtrapNorm = (TH1D*)hExtrap->Clone(Form("%sExtrapNorm",hExtrap->GetName()));
      hExtrapNorm->Scale(norm/hExtrapNorm->Integral());
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
};

//---------------------------------------------------------------------
class SignalCorrector
{
public:
   SignalCorrector(TTree * tree, TString n, TString var, TCut s, TString w="(1==1)", int bin=-1) : 
   name(n),
   observable(var),
   sel(s),
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
   nSelPhoton(0),fracDPhiBkg(0),fracPhotonBkg(0),fracPhotonDPhiBkg(0) {
      t = tree;
      cutBkgDPhi     = "jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01";
      cutSShape      = "jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017";
      cutSShapeDPhi  = "jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017";
      // photon purity values
      hPhotonPurity = (TH1D*)gDirectory->FindObjectAny("hPhotonPurity");
      if (!hPhotonPurity) hPhotonPurity = new TH1D("hPhotonPurity","",4,0,4);
   }
   
   void SetPhotonIsolation(int isolScheme)
   {
      //
      // Centrality bins: 0=0-4, 1=4-12, 2=12-20, 3=20-40
      // 
      if (isolScheme==0) { //sum isol
         nameIsol="Sum(Isol.)<1GeV";
         cutIsol = "(cc4+cr4+ct4PtCut20)/0.9 <1";
         hPhotonPurity->SetBinContent(1,0.73);
         hPhotonPurity->SetBinContent(2,0.77);
         hPhotonPurity->SetBinContent(3,0.79);
         hPhotonPurity->SetBinContent(4,0.84);
      } else if (isolScheme==1) { // cut isol
         nameIsol="3DCutIsol.";
         cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
         hPhotonPurity->SetBinContent(1,0.46);
         hPhotonPurity->SetBinContent(2,0.62);
         hPhotonPurity->SetBinContent(3,0.54);
         hPhotonPurity->SetBinContent(4,0.54);
      } else if (isolScheme==2) { // fisher isol
         nameIsol="Fisher Isol. > 0.3";
         t->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
         cutIsol = "fisherIsol>0.3";
         hPhotonPurity->SetBinContent(1,0.76);
         hPhotonPurity->SetBinContent(2,0.77);
         hPhotonPurity->SetBinContent(3,0.74);
         hPhotonPurity->SetBinContent(4,0.78);         
      }
      // Isolation Cut
      sel = sel&&cutIsol;
      // Photon Purity
      if (subSShapeSide) fracPhotonBkg = 1-hPhotonPurity->GetBinContent(centBin+1);
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
      cout << "Base Selection: " << sel << endl;
      rSigAll.cut = sel&&sigSel;
      rBkgDPhi.cut = sel&&cutBkgDPhi;
      rBkgSShape.cut = sel&&cutSShape;
      rBkgSShapeDPhi.cut = sel&&cutSShapeDPhi;
      
      rSigAll.Init(t,nbin,bins);
      rBkgDPhi.Init(t,nbin,bins);
      rBkgSShape.Init(t,nbin,bins);
      rBkgSShapeDPhi.Init(t,nbin,bins);
      
      // photon normalization
      nSelPhoton = t->GetEntries(sel&&"sigmaIetaIeta<0.01");
      // number of events in signal region
      cout << " ** Number of selection photons: " << nSelPhoton << " gamma-jets: " << rSigAll.n << " ** " << endl;
   }
   
   void Extrapolate(float dphiSigCut=2.0944, bool doDPhiExtend=false) {
      // Scales
      float dphisidescale = (3.14159-dphiSigCut)/(3.14159/2.-0.7);
      float sssidescale = 0,ssdphisidescale=0;
      if (rBkgSShape.n>0) {
         sssidescale = rSigAll.n*fracPhotonBkg/rBkgSShape.n;
         ssdphisidescale = dphisidescale*sssidescale;
      }
      cout << " Bkg scale dphi: " << dphisidescale << endl;
      cout << " Bkg scale ss: " << sssidescale << endl;
      cout << " Bkg scale ssdphi: " << ssdphisidescale << endl;

      rSigAll.Extrapolate(1.);
      rBkgSShape.Extrapolate(sssidescale);
      if (!doDPhiExtend) {
         rBkgDPhi.Extrapolate(dphisidescale);
         rBkgSShapeDPhi.Extrapolate(ssdphisidescale);
      } else {
         rBkgDPhi.Extrapolate(1.);
         rBkgSShapeDPhi.Extrapolate(1.);
      }

      // Fractions
      if (rSigAll.n>0) {
         fracDPhiBkg = rBkgDPhi.n * dphisidescale/rSigAll.n;
         fracPhotonDPhiBkg = rBkgSShapeDPhi.n * ssdphisidescale/rSigAll.n;
      }
   }

   // special case for dphi
   void ExtrapolateDPhiHist(float dphiSigCut=0.7) {
      TF1 *p0 = new TF1("p0","pol0",dphiSigCut,3.14/2);
      if (subDPhiSide&&rBkgDPhi.n>=10) {
         rBkgDPhi.hExtrap->Fit("p0","0");
         for (int i=rBkgDPhi.hExtrap->FindBin(dphiSigCut); i<=rBkgDPhi.hExtrap->GetNbinsX(); ++i) {
            rBkgDPhi.hExtrap->SetBinContent(i,p0->GetParameter(0));
            rBkgDPhi.hExtrap->SetBinError(i,p0->GetParError(0));
         }
      }
      if (subSShapeSideDPhiSide&&rBkgSShapeDPhi.n>=10) {
         rBkgSShapeDPhi.hExtrap->Fit("p0","0");
         for (int i=rBkgSShapeDPhi.hExtrap->FindBin(dphiSigCut); i<=rBkgSShapeDPhi.hExtrap->GetNbinsX(); ++i) {
            rBkgSShapeDPhi.hExtrap->SetBinContent(i,p0->GetParameter(0));
            rBkgSShapeDPhi.hExtrap->SetBinError(i,p0->GetParError(0));
         }
      }
   }
   
   void SubtractBkg() {
      rSubtracted.hExtrap = (TH1D*)rSigAll.h->Clone(rSubtracted.name+"Extrap");
      rSubtracted.nExtrap = rSigAll.nExtrap;
      cout << "Raw Sig: " << rSigAll.nExtrap;
      if (subDPhiSide) {
         rSubtracted.hExtrap->Add(rBkgDPhi.hExtrap,-1);
         rSubtracted.nExtrap -= rBkgDPhi.nExtrap;
         cout << " - " << rBkgDPhi.nExtrap;
      }
      if (subSShapeSide) {
         rSubtracted.hExtrap->Add(rBkgSShape.hExtrap,-1);
         rSubtracted.nExtrap -= rBkgSShape.nExtrap;
         cout << " - " << rBkgSShape.nExtrap;
      }
      if (subSShapeSideDPhiSide) {
         rSubtracted.hExtrap->Add(rBkgSShapeDPhi.hExtrap,1);
         rSubtracted.nExtrap += rBkgSShapeDPhi.nExtrap;
         cout << " + " << rBkgSShapeDPhi.nExtrap;
      }
      cout << " =? " << rSubtracted.nExtrap << endl;
      cout << "Check Integ:  " << rSigAll.hExtrap->Integral() << " - " << 
      rBkgDPhi.hExtrap->Integral() << " - " << rBkgSShape.hExtrap->Integral() << " + " << rBkgSShapeDPhi.hExtrap->Integral()
      << " = " << rSubtracted.hExtrap->Integral() << endl;
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
            rawarea*=(rSigAll.n)/nSelPhoton;
            area*=(rSigAll.n - rBkgDPhi.nExtrap - rBkgSShape.nExtrap + rBkgSShapeDPhi.nExtrap) / (nSelPhoton*(1-fracPhotonBkg));
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
         cout << "Norlamize to: " << area << " chk integ: " << rSubtracted.hExtrapNorm->Integral() << endl;
      }
   }
   
   TTree * t;
   TString name,nameIsol,observable;
   TCut sel,cutIsol;
   Region rSigAll;
   Region rBkgDPhi;
   Region rBkgSShape;
   Region rBkgSShapeDPhi;
   Region rSubtracted;
   TString weight;
   bool subDPhiSide;
   bool subSShapeSide;
   bool subSShapeSideDPhiSide;
   TCut cutBkgDPhi;
   TCut cutSShape;
   TCut cutSShapeDPhi;   
   float nSelPhoton;
   float fracDPhiBkg;
   float fracPhotonBkg;
   float fracPhotonDPhiBkg;
   int centBin;
   TH1D * hPhotonPurity;
};

#endif
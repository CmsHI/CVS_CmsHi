#ifndef SignalCorrector_h
#define SignalCorrector_h

//---------------------------------------------------------------------
class Region
{
public:
   Region(TString n, TString v, TCut c, TString w) :
   name(n),var(v),cut(c),weight(w) {}
   void Init(TTree * t, int nbins, float xmin, float xmax, float frac, float area=1.) {
      fraction = frac;
      cut*=weight;
      h = new TH1D(name,"",nbins,xmin,xmax);
      cout << " ** " << h->GetName() << " with fraction: " << fraction << " area: " << area << " **" << endl;
      float nSel = t->Project(h->GetName(),var,cut);
      cout << "draw: " << var << " cut: " << TString(cut) << ": " << nSel << endl;
      hNorm = (TH1D*)h->Clone(Form("%sNorm",h->GetName()));
      if (h->Integral()>0) hNorm->Scale(area/h->Integral());
      hScaled = (TH1D*)hNorm->Clone(Form("%sScaled",hNorm->GetName()));
      cout << hScaled->GetName() << " ";
      cout << "scale by: " << area*fraction << endl;
      hScaled->Scale(fraction);
      //for (int i=1; i<=hScaled->GetNbinsX()+1 ; ++i) cout << hScaled->GetBinLowEdge(i) << " (" << hScaled->GetBinContent(i) << ") ";
      //cout << endl;
      // check
      t->Draw("cBin>>"+name+"_cbin(40,0,40)",cut,"goff");
   }
   
   TH1D * h;
   TH1D * hNorm;
   TH1D * hScaled;
   TString name;
   TString var;
   TCut cut;
   TString weight;
   float fraction;
};

//---------------------------------------------------------------------
class SignalCorrector
{
public:
   SignalCorrector(TTree * tree, TString n, TString var, TCut s, TCut sigSel, TString w="(1==1)", int nm=1) : 
   name(n),
   sel(s),
   rSigAll(n+"SignalAll",var,s&&sigSel,w),
   rBkgDPhi(n+"BkgDPhi",var,s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01",w),
   rBkgSShape(n+"BkgSShape",var,s&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011",w),
   weight(w),
   normMode(nm), // 0=area is signal region count, 1=unit normalization, 2=per photon normalization
   subDPhiSide(true),
   subSShapeSide(true),
   nSelPhoton(0),nSigAll(0),fracDPhiBkg(0),fracPhotonBkg(0) {
      t = tree;
   }
   
   void MakeHistograms(float frac2, int nbin, float xmax, float xmin) {
      fracPhotonBkg=frac2;
      // photon normalization
      nSelPhoton = t->GetEntries(sel&&"sigmaIetaIeta<0.01");
      // number of events in signal region
      nSigAll = t->GetEntries(rSigAll.cut);
      cout << "Number of selection photons: " << nSelPhoton << " gamma-jets: " << nSigAll << endl;
      float area=1.;
      if (normMode==0) area=nSigAll;
      if (normMode==2) area=nSigAll/nSelPhoton;
      rSigAll.Init(t,nbin,xmax,xmin,1.,area);
      if (subDPhiSide) {
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         fracDPhiBkg = nDPhiBkg/nSigAll;
         rBkgDPhi.Init(t,nbin,xmax,xmin,fracDPhiBkg,area);
         cout << "|dhpi| sig all = " << nSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "fracPhotonBkg: " << fracPhotonBkg << endl;
         rBkgSShape.Init(t,nbin,xmax,xmin,fracPhotonBkg,area);
      }
      
      hSubtracted = (TH1D*)rSigAll.hScaled->Clone(name+"Subtracted");
      if (subDPhiSide) hSubtracted->Add(rBkgDPhi.hScaled,-1);
      if (subSShapeSide) hSubtracted->Add(rBkgSShape.hScaled,-1);
      // Rescale after subtraction
      if (normMode==2&&subDPhiSide&&subSShapeSide) area*=(1-fracDPhiBkg-fracPhotonBkg)/(1-fracPhotonBkg);
      rSigAll.hScaled->Scale(area/rSigAll.hScaled->Integral());
      //if (subSShapeSide) rBkgSShape.hScaled->Scale(area/rBkgSShape.hScaled->Integral());
      hSubtracted->Scale(area/hSubtracted->Integral());
   }
   TTree * t;
   TString name;
   TCut sel;
   Region rSigAll;
   Region rBkgDPhi;
   Region rBkgSShape;
   TH1D * hSubtracted;
   TString weight;
   int normMode;
   bool subDPhiSide;
   bool subSShapeSide;
   float nSelPhoton;
   float nSigAll;
   float fracDPhiBkg;
   float fracPhotonBkg;
};

#endif
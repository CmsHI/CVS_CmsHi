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
      cout << "  " << h->GetName() << " with fraction: " << fraction << " area: " << area << endl;
      float nSel = t->Project(h->GetName(),var,cut);
      cout << "  draw: " << var << " cut: " << TString(cut) << ": " << nSel << endl;
      hNorm = (TH1D*)h->Clone(Form("%sNorm",h->GetName()));
      if (h->Integral()>0) hNorm->Scale(area/h->Integral());
      hScaled = (TH1D*)hNorm->Clone(Form("%sScaled",hNorm->GetName()));
      cout << "  " << hScaled->GetName() << " scale by: " << area*fraction << endl;
      hScaled->Scale(fraction);
      //for (int i=1; i<=hScaled->GetNbinsX()+1 ; ++i) cout << hScaled->GetBinLowEdge(i) << " (" << hScaled->GetBinContent(i) << ") ";
      //cout << endl;
      // check
      t->Draw("cBin>>"+name+"_cBin(40,0,40)",cut,"goff");
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
   SignalCorrector(TTree * tree, TString n, TString var, TCut s, TString w="(1==1)", int nm=1) : 
   name(n),
   sel(s),
   rSigAll(n+"SignalAll",var,s,w),
   rBkgDPhi(n+"BkgDPhi",var,s,w),
   rBkgSShape(n+"BkgSShape",var,s,w),
   weight(w),
   normMode(nm), // 0=area is signal region count, 1=unit normalization, 2=per photon normalization
   subDPhiSide(true),
   subSShapeSide(true),
   nSelPhoton(0),nSigAll(0),fracDPhiBkg(0),photonPurity(0),fracPhotonBkg(0) {
      t = tree;
   }
   
   void SetPhotonIsolation(int isolScheme, int cBin)
   {
      if (isolScheme==0) { //sum isol
         nameIsol="Sum(Isol.)";
         cutIsol = "sumIsol/0.9<5";
         if (cBin==0) photonPurity=0.50;
         if (cBin>=1&&cBin<=2) photonPurity=0.64;
         if (cBin>=3&&cBin<=4) photonPurity=0.57;
      } else if (isolScheme==1) { // cut isol
         nameIsol="3DCutIsol.";
         cutIsol = "cc4 < 6.9 && ct4PtCut20 < 3.00 && cr4<5";
         if (cBin==0) photonPurity=0.46;
         if (cBin>=1&&cBin<=2) photonPurity=0.62;
         if (cBin>=3&&cBin<=4) photonPurity=0.54;
      } else if (isolScheme==2) { // fisher isol
         nameIsol="Fisher Isol.";
         t->SetAlias("fisherIsol","(4.5536204845644690e-01 +cc5*-1.1621087258504197e-03 +cc4*-1.3139962130657250e-02 +cc3*9.8272534188056666e-03 +cc2*-7.9659880964355362e-02 +cc1*5.6661268034678275e-02 +cr5*-1.2763802967154852e-02 +cr4*-1.2594575465310987e-03 +cr3*-1.3333157740152167e-02 +cr2*-2.5518237583408113e-02 +cr1*-1.3706749407235775e-02 +ct4PtCut20*-7.9844325658248016e-03 +ct3PtCut20*-2.5276510400767658e-03 +ct2PtCut20*-2.0741636383420897e-02 +ct1PtCut20*7.1545293456054884e-04 +ct5PtCut20*7.8080659557798627e-03)");
         cutIsol = "fisherIsol>0.2";
         if (cBin==0) photonPurity=0.62;
         if (cBin>=1&&cBin<=2) photonPurity=0.66;
         if (cBin>=3&&cBin<=4) photonPurity=0.64;
      }
      fracPhotonBkg=1-photonPurity;
      // Isolation Cut
      sel = sel&&cutIsol;      
   }
   
   void MakeHistograms(TCut sigSel, int nbin, float xmax, float xmin) {
      cout << endl << "Base Selection: " << sel << endl;
      rSigAll.cut = sel&&sigSel;
      rBkgDPhi.cut = sel&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>0.7 && acos(cos(photonPhi-jetPhi))<3.14159/2. && sigmaIetaIeta<0.01";
      rBkgSShape.cut = sel&&"jetEt>30&&acos(cos(photonPhi-jetPhi))>2.0944 && sigmaIetaIeta>0.011";

      // photon normalization
      nSelPhoton = t->GetEntries(sel&&"sigmaIetaIeta<0.01");
      // number of events in signal region
      nSigAll = t->GetEntries(rSigAll.cut);
      cout << " ** Number of selection photons: " << nSelPhoton << " gamma-jets: " << nSigAll << " ** " << endl;
      float area=1.;
      if (normMode==0) area=nSigAll;
      if (normMode==2) area=nSigAll/nSelPhoton;
      rSigAll.Init(t,nbin,xmax,xmin,1.,area);
      if (subDPhiSide) {
         float nDPhiSide = t->GetEntries(rBkgDPhi.cut);
         float nDPhiBkg = nDPhiSide * (3.14159-2.0944)/(3.14159/2.-0.7);
         fracDPhiBkg = nDPhiBkg/nSigAll;
         rBkgDPhi.Init(t,nbin,xmax,xmin,fracDPhiBkg,area);
         cout << "  |dhpi| sig all = " << nSigAll << "|dphi| side = " << nDPhiSide << " bck contamination: " << nDPhiBkg << " = " << fracDPhiBkg << endl;
      }
      if (subSShapeSide) {
         cout << "  fracPhotonBkg: " << fracPhotonBkg << endl;
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
   TString name,nameIsol;
   TCut sel,cutIsol;
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
   float photonPurity;
   float fracPhotonBkg;
};

#endif
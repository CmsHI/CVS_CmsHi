#ifndef HisPhotonJet_h
#define HisPhotonJet_h

#include "TGraphAsymmErrors.h"
#include "TMath.h"
#include "TF1.h"

//-----------------------------------------------------------------
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

//-----------------------------------------------------------------
TGraphAsymmErrors * getSummary(//TString outfname,
                               //TString name,
                               int nBin,
                               float * npart,
                               const vector<TH1D*> & vh,
                               int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data, 10 = pp mc
                               int dataType, // 0=mc gen, 1=reco
                               int anaMode // 0=get mean, 1 = get fit, 2 = get area
                               )
{
   // make graph
   TGraphAsymmErrors * gAve;
   if (dataSrcType<=1) gAve = new TGraphAsymmErrors(nBin);
   else gAve = new TGraphAsymmErrors(1);
   TString gname;
   if (anaMode==0) gname = Form("dataSrc%d_reco%d_x_Summary",dataSrcType,dataType);
   if (anaMode==1) gname = Form("dataSrc%d_reco%d_dphi_Summary",dataSrcType,dataType);
   if (anaMode==2) gname = Form("dataSrc%d_reco%d_R_Summary",dataSrcType,dataType);
   gAve->SetName(gname);
   
   TF1 *fdphi = new TF1("fdphi","(TMath::Pi()/20.0)*exp(-(TMath::Pi()-x)/[0])/([0]*(1-exp(-TMath::Pi()/[0])))",2.0*TMath::Pi()/3.0,TMath::Pi());
   fdphi->SetParameter(0,0.2);

   for (int ib=0;ib<gAve->GetN();++ib)
   {
      if (dataSrcType>1&&ib>0) continue;
      float y=0, errYL=0, errYH =0;
      TH1D * hana = vh[ib];
      if (!hana) continue;
      
      if (anaMode ==0) {
         y=calcMean(hana);
         errYL = hana->GetMeanError();
         errYH = hana->GetMeanError();
      } else if (anaMode ==1 ) {
         vh[ib]->Fit("fdphi","0wl","",2.0*TMath::Pi()/3.0,TMath::Pi());
         y=fdphi->GetParameter(0);
         errYL=fdphi->GetParError(0);
         errYH=fdphi->GetParError(0);
      } else if (anaMode ==2 ) {
         int imin = hana->FindBin(0);
         int imax = hana->FindBin(10);
         y=hana->Integral(imin,imax)*hana->GetBinWidth(1);
         errYL = y/sqrt(hana->GetEntries());
         errYH = y/sqrt(hana->GetEntries());
      }
      cout << "Summary mode: " << anaMode << ", hist: " << hana->GetName() << endl;
      
      gAve->SetPointError(ib,0,0,errYL,errYH);
      if (dataSrcType<=1) {
         gAve->SetPoint(ib,npart[ib],y);
         cout <<"bin: " << ib <<" npart: "<<npart[ib]<< " y: " << y << " yerr: " << errYH << endl;
      }
      else {
         gAve->SetPoint(ib,2,y);
//         cout<<" Setting PYTHIA point to npart=2 by hand"<<endl;
         cout <<"bin: " << ib <<" npart: 2 y: " << y << " yerr: " << errYH << endl;
      }
   }
   
//   TFile* hout = new TFile(outfname,"update");
//   gAve->Write();
//   hout->Close();
//   
   return gAve;
}
#endif
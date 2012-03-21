#ifndef HisCompre_h
#define HisCompre_h

#include <iostream>
#include <vector>
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TString.h"
#include "TLegend.h"
#include "TLine.h"
using namespace std;

class HisCompare
{
public:
   HisCompare(TString myname, TString mytitle, float myxmin, float myxmax, int nm=0) :
   name(myname), title(mytitle),
   xmin(myxmin), xmax(myxmax),
   normMode(nm)
   {
      hFrame = new TH1D("hFrame"+name,title,20,xmin,xmax);
      hFrame->GetXaxis()->SetLabelSize(22);
      hFrame->GetXaxis()->SetLabelFont(43);
      hFrame->GetXaxis()->SetTitleSize(24);
      hFrame->GetXaxis()->SetTitleFont(43);
      hFrame->GetXaxis()->SetTitleOffset(1);
      hFrame->GetXaxis()->CenterTitle();
      hFrame->GetXaxis()->SetNdivisions(505,true);
      hFrame->GetYaxis()->SetLabelSize(22);
      hFrame->GetYaxis()->SetLabelFont(43);
      hFrame->GetYaxis()->SetTitleSize(22);
      hFrame->GetYaxis()->SetTitleFont(43);
      hFrame->GetYaxis()->SetTitleOffset(1.2);
      hFrame->GetYaxis()->CenterTitle();
      hFrame->GetYaxis()->SetNdivisions(505,true);

      leg = new TLegend(0.25,0.71,0.63,0.87);
      leg->SetFillStyle(0);
      leg->SetBorderSize(0);
      leg->SetTextSize(0.04);
   }
   
   TString name;
   TString title;
   float xmin,xmax;
   int normMode;
   
   TH1D * hFrame;
   vector<TH1D*> vh;
   vector<TString> vhstyle;
   TLegend * leg;
   
   void AddHist(TH1D *h, TString htitle, TString hdrawstyle, int color, int mkstyle, TString legstyle="", int lstyle=-1) {
      if (!h) {
         cout << "bad histogram" << endl;
         return;
      }

      if (normMode==1) {
         h->Scale(1./h->Integral());
      } else if (normMode==2) {
         h->Scale(1./(h->Integral()*h->GetBinWidth(1)));
      }
      h->SetMarkerColor(color);
      h->SetMarkerStyle(mkstyle);
      h->SetLineColor(color);
      if (lstyle>0) h->SetLineStyle(lstyle);

      TH1D * hnew = (TH1D*)h->Clone(Form("%s_%d",name.Data(),vh.size()));
      vh.push_back(hnew);
      vhstyle.push_back(hdrawstyle);
      
      if (legstyle!="") leg->AddEntry(hnew,htitle,legstyle);
   }
   
   void Draw(float ymin=0, float ymax=0) {
      // draw frame
      if (ymin>=ymax) {
         ymin=vh[0]->GetMinimum()*1.4;
         ymax=vh[0]->GetMaximum()*1.4;
      }
      hFrame->SetAxisRange(ymin,ymax,"Y");
      hFrame->Draw();
      
      for (int i=0; i<vh.size(); ++i) {
         vh[i]->Draw("same"+vhstyle[i]);
      }
   }
   
   void DrawLeg(TString header, float lx1=0.4, float ly1=0.18, float lx2=0.87, float ly2=0.28)
   {
      leg->SetHeader(header);
      leg->SetX1NDC(lx1);
      leg->SetY1NDC(ly1);
      leg->SetX2NDC(lx2);
      leg->SetY2NDC(ly2);
      leg->SetX1(lx1);
      leg->SetY1(ly1);
      leg->SetX2(lx2);
      leg->SetY2(ly2);
      leg->Draw();
   }
   
//   TH1D * Ratio(TString ytitle="ratio") {
//      TH1D * hr = (TH1D*)h1->Clone(name1+"_div_"+name2);
//      hr->Divide(h2);
//      hr->SetYTitle(ytitle);
//      //hr->Fit("pol1","");
//      return hr;
//   }
};

#endif
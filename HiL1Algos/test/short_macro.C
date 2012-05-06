short_macro()
{
TFile f("Minbias_digital_calib_3x3sub.root");
TFile g("Central_digital_calib_3x3sub.root");
TFile h("Jet_digital_calib_3x3sub.root");

TH1D *h1 = (TH1D*)f.Get("efficiency_curve");
h1->SetLineStyle(0);
//h1->SetTitle("RCT Minimum region subtraction algorithm"); 
TH1D *h2 = (TH1D*)g.Get("efficiency_curve");
h2->SetLineStyle(2);
TH1D *h3 = (TH1D*)h.Get("efficiency_curve");
h3->SetLineStyle(3);

TCanvas *c1 = new TCanvas("c1","c1");
//gPad->SetTitle("test title");

h1->Draw("L");
h2->Draw("L,same");
h3->Draw("L,same");

c1->BuildLegend();
}

short_macro()
{
  TCanvas *c0 = new TCanvas();
  TF1 *f1 = new TF1("f1","TMath::Gaus(x,0,0.15)",-3, 3);
  f1->SetTitle("Jet Without Background");
  f1->GetYaxis()->SetRangeUser(0,1.5);
  f1->Draw();

  TCanvas *c1 = new TCanvas();
  TF1 *f2 = new TF1("f2","TMath::Gaus(x,0,0.15)+0.4",-3, 3);
  f2->SetTitle("Jet With Background");
  f2->GetYaxis()->SetRangeUser(0,1.5);
  f2->Draw();
}

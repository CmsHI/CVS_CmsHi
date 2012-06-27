macro_doga()
{
  TH2* hmb=new TH2D();
  TFile *f1 = new TFile("/net/hisrv0001/home/dgulhan/L1Trigger/turnonmb_after_wselection.root");
  hmb = (TH2*)f1->Get("JetEt");

  TProfile* p1=hmb->ProfileX("p1",0,99);
  p1->SetTitle("Tower-Level Phi-Ring Subtracton, 5% Threshold 64 GeV");
// p1->SetTitle("Minimum bias data without event selection");
  p1->GetXaxis()->SetTitle("HLT Jet Pt (GeV)");
  p1->GetXaxis()->SetRangeUser(0,200);
  p1->GetYaxis()->SetRangeUser(0,1);
  p1->SetYTitle("Fraction Accepted");
  //p1->GetXaxis()->CenterTitle();
  //p1->GetYaxis()->CenterTitle();
  p1->Draw();
}

{
   TCanvas * c2 = new TCanvas("c2","c2",500,500);
   tgj.Draw("cc1>>hcc1","anaEvtSel");
   tgj.Draw("cc2>>hcc2","anaEvtSel","same");
   tgj.Draw("cc3>>hcc3","anaEvtSel","same");
   tgj.Draw("cc4>>hcc4","anaEvtSel","same");
   tgj.Draw("cc5>>hcc5","anaEvtSel","same");
   hcc1->SetTitle(";ECAL Isolation");
   hcc1->GetXaxis()->CenterTitle();
   hcc2->SetLineColor(kBlue);
   hcc3->SetLineColor(kGreen+2);
   hcc4->SetLineColor(kViolet);
   hcc5->SetLineColor(kRed);
   c2->Update();

   TCanvas * c3 = new TCanvas("c3","c3",500,500);
   tgj.Draw("cr1>>hcr1","anaEvtSel");
   tgj.Draw("cr2>>hcr2","anaEvtSel","same");
   tgj.Draw("cr3>>hcr3","anaEvtSel","same");
   tgj.Draw("cr4>>hcr4","anaEvtSel","same");
   tgj.Draw("cr5>>hcr5","anaEvtSel","same");
   hcr1->SetTitle(";HCAL Isolation");
   hcr1->GetXaxis()->CenterTitle();
   hcr2->SetLineColor(kBlue);
   hcr3->SetLineColor(kGreen+2);
   hcr4->SetLineColor(kViolet);
   hcr5->SetLineColor(kRed);
   
   TCanvas * c4 = new TCanvas("c4","c4",500,500);
   tgj.Draw("ct1PtCut20>>hct1","anaEvtSel");
   tgj.Draw("ct2PtCut20>>hct2","anaEvtSel","same");
   tgj.Draw("ct3PtCut20>>hct3","anaEvtSel","same");
   tgj.Draw("ct4PtCut20>>hct4","anaEvtSel","same");
   tgj.Draw("ct5PtCut20>>hct5","anaEvtSel","same");
   hct1->SetTitle(";Trk Isolation (trk p_{T} > 2. GeV/c)");
   hct1->GetXaxis()->CenterTitle();
   hct2->SetLineColor(kBlue);
   hct3->SetLineColor(kGreen+2);
   hct4->SetLineColor(kViolet);
   hct5->SetLineColor(kRed);
   
   TCanvas * c5 = new TCanvas("c5","c5",500,500);
   tgj.Draw("optIsol>>hOptIsol(40,-4,4)","anaEvtSel");
   hOptIsol->SetTitle(";combined fisher var");
   hOptIsol->GetXaxis()->CenterTitle();
   TLine * l = new TLine(0.3,0,0.3,hOptIsol->GetMaximum());
   l->SetLineColor(2);
   l->Draw();
}
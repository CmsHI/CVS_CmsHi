#include "hiForest.h"
#include "TCanvas.h"
#include <TPad.h>

void analyze2010(){

//   HiForest * t = new HiForest("dcache:/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/yjlee/hiForest/merged_HI2010_SD_Jet35_prod05_full.root");
   HiForest * t = new HiForest("merged_pp2760_AllPhysics_NoPhoyon_Prod02.root");
   // HiForest * t = new HiForest("merged_HI2010_SD_Jet35_prod05.root");

   t->sortJets(t->akPu3jetTree, t->akPu3PF, 2., 50, 1);
   t->correlateTracks(t->akPu3jetTree, t->akPu3PF);
   
   TCanvas * c1 = new TCanvas("c1","",900,400);
   c1->Divide(2,1);
   c1->cd(1);
   t->Draw("akPu3PF.AJ","akPu3PF.HasDijet","");
   c1->cd(2)->SetLogy();
   t->Draw("-log(track.zLead)","akPu3PF.HasDijet && track.tjDRlead < 0.3","");

   c1->Print("SimpleJetAnalysis.gif");

}


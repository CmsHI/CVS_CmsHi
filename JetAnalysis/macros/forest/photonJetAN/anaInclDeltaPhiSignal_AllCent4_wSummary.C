#if !defined(__CINT__) || defined(__MAKECINT__)

#include <iostream>
#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"
#include "TCut.h"

#include "commonUtility.h"
#include "SignalCorrector.h"
#include "npart.h"
#endif

TString outfname;

//---------------------------------------------------------------------
void getHistograms(TString myname, TString var, TString bkgvar,
                   vector<SignalCorrector*> & vana,
                   vector<TCut> vcutCent, TCut mycut, TCut jetSel, TCut jetBkgSel,
                   int isolScheme, int normMode,
                   TString infname,
                   TString weight,
                   int dataSrcType, // 0=mc, 1=pbpb data, 2= pp data
                   int dataType, // 0=mc gen, 1=reco
                   int subDPhiSide = 1,
                   int subSShapeSide = 1,
                   float minPhoton=60,
                   float minJet=30,
                   float sigDPhi=2.0944
                   )
{
   // open the data file
   TFile *inf = TFile::Open(infname);
   TTree *nt =(TTree*)inf->FindObjectAny("tgj");
   cout << endl << "# " << endl;
   cout << "# " << infname << endl;
   cout << "# " << myname << ": useWeight: " << weight << " dataSrcType: " << dataSrcType << " photon: " << minPhoton << " jet: " << minJet << endl;
   cout << "# " << endl;
   
   // mixing trees
   TString mixfname=infname;
   bool doMixBkg=false;
   if (dataSrcType<=1&&dataType==1) {
      doMixBkg=true;
      mixfname.ReplaceAll("_akPu3PF","_mixmb_akPu3PF");
      cout << "Mix file: " << mixfname << endl;
   }
   if (doMixBkg) nt->AddFriend("tmix=tgj",mixfname);
   
   // loop over centrality bins
   for (int ib=0; ib<vcutCent.size(); ++ib) {
      TString name = myname+Form("_dataSrc%d_reco%d_cent%d",dataSrcType,dataType,ib);
      int cBin = ib;
      if (dataSrcType>1) cBin==vcutCent.size()-1;
      // initialize ana
      vana.push_back(new SignalCorrector(nt,name,var,Form("photonEt>%.3f",minPhoton)&&mycut&&vcutCent[ib],weight,cBin,dataSrcType));
      // setup cuts
      vana[ib]->cutSigAllPho     = "sigmaIetaIeta<0.01";
      vana[ib]->cutSShapeAllPho  = "sigmaIetaIeta>0.011 && sigmaIetaIeta<0.017";
      vana[ib]->cutBkgDPhi       = vana[ib]->cutSigAllPho    && jetSel && Form("acos(cos(photonPhi-inclJetPhi))>0.7 && acos(cos(photonPhi-inclJetPhi))<3.14159/2.");
      vana[ib]->cutSShape        = vana[ib]->cutSShapeAllPho && jetSel && Form("acos(cos(photonPhi-inclJetPhi))>%f",sigDPhi);
      vana[ib]->cutSShapeDPhi    = vana[ib]->cutSShapeAllPho && jetSel && Form("acos(cos(photonPhi-inclJetPhi))>0.7 && acos(cos(photonPhi-inclJetPhi))<3.14159/2.");
      if (doMixBkg) {
         vana[ib]->cutBkgDPhi    = vana[ib]->cutSigAllPho    && jetBkgSel && Form("acos(cos(photonPhi-tmix.inclJetPhi))>%f",sigDPhi);
         vana[ib]->cutSShapeDPhi = vana[ib]->cutSShapeAllPho && jetBkgSel && Form("acos(cos(photonPhi-tmix.inclJetPhi))>%f",sigDPhi);
         vana[ib]->rBkgDPhi.var = bkgvar;
         vana[ib]->rBkgSShapeDPhi.var = bkgvar;
      }
      
      // analyze tree
      float nxbins=20, xmin=0.0001, xmax=3.1415926;
      if (dataType==0) {
         vana[ib]->subDPhiSide = false;
         vana[ib]->subSShapeSide = false;
         vana[ib]->subSShapeSideDPhiSide = false;
         vana[ib]->SetPhotonIsolation(isolScheme);
         vana[ib]->MakeHistograms(vana[ib]->cutSigAllPho&&jetSel&&Form("acos(cos(photonPhi-inclGenJetPhi))>%f",sigDPhi),nxbins,xmin,xmax);
      } else {
         vana[ib]->subDPhiSide = subDPhiSide;
         vana[ib]->subSShapeSide = subSShapeSide;
         vana[ib]->subSShapeSideDPhiSide = subDPhiSide&&subSShapeSide;
         vana[ib]->SetPhotonIsolation(isolScheme);
//         vana[ib]->SetJetWeights("inclJetPt");
         vana[ib]->MakeHistograms(vana[ib]->cutSigAllPho&&jetSel&&Form("acos(cos(photonPhi-inclJetPhi))>%f",sigDPhi),nxbins,xmin,xmax);
      }
      
      if (!doMixBkg) {
         bool doFitSideband=true;
         if (doFitSideband) {
            vana[ib]->Extrapolate(1.);
            vana[ib]->ExtrapolateDPhiHist(sigDPhi);
         }
         else {
            vana[ib]->Extrapolate((3.14159-sigDPhi)/(3.14159/2.-0.6284));
         }
      } else {
         vana[ib]->Extrapolate(1./40);
      }
      vana[ib]->SubtractBkg();
      vana[ib]->Normalize(normMode);
      
      // output histograms
      TFile* hout = new TFile(outfname,"update");
      vana[ib]->rSubtracted.hExtrapNorm->Write();
      if (vana[ib]->rSigAllPho.h) vana[ib]->rSigAllPho.h->Write();
      if (vana[ib]->rBkgSShapeAllPho.h) vana[ib]->rBkgSShapeAllPho.h->Write();
      if (vana[ib]->rSigAll.hExtrapNorm) vana[ib]->rSigAll.hExtrapNorm->Write();
      if (vana[ib]->rBkgDPhi.hExtrapNorm) vana[ib]->rBkgDPhi.hExtrapNorm->Write();
      if (vana[ib]->rBkgSShape.hExtrapNorm) vana[ib]->rBkgSShape.hExtrapNorm->Write();
      if (vana[ib]->rBkgSShapeDPhi.hExtrapNorm) vana[ib]->rBkgSShapeDPhi.hExtrapNorm->Write();
      hout->Close();
   }
//   inf->Close();
}

//---------------------------------------------------------------------
void anaInclDeltaPhiSignal_AllCent4_wSummary(
                                         int isolScheme=0, // 0=sumIsol, 1=cutIsol, 2=fisherIsol
                                         int normMode=1, // 1=unity, 2=per photon
                                         int subDPhiSide = 1,
                                         int subSShapeSide = 1,
                                         float minPhoton=60,
                                         float minJet=30,
                                         int log=0,
                                         int drawCheck = 0,
                                         TString outdir = "./fig/03.27_closure_pythia_and_data"
                                         )
{
   TH1::SetDefaultSumw2();
   float sigDPhi=3.1415926/5;
   
   outfname=Form("%s/HisOutput_Photonv7_v29_akPu3PF_InclDeltaPhi_gamma%.0fjet%.0fdphiSig%.0f_Isol%d_Norm%d.root",outdir.Data(),minPhoton,minJet,sigDPhi*1000,isolScheme,normMode);
   TFile* hout = new TFile(outfname,"RECREATE");
   hout->Close();

   const int nBin = 4;
   float m[nBin+1] = {0,4,12,20,40};

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Analysis
   ////////////////////////////////////////////////////////////////////////////////////////////////
   vector<TCut> vcutCent,vcutCentPp;
   for (int ib=0; ib<nBin; ++ib) vcutCent.push_back(Form("cBin>=%.1f&&cBin<%.1f",m[ib],m[ib+1]));
   vcutCentPp.push_back("1==1");
   
   // Data
   TString var="acos(cos(photonPhi-inclJetPhi))";
   TString varbkg="acos(cos(photonPhi-tmix.inclJetPhi))";
   TCut jetSel = Form("abs(inclJetEta)<1.6&&inclJetPt>%.3f",minJet);
   TCut jetBkgSel = Form("abs(tmix.inclJetEta)<1.6&&tmix.inclJetPt>%.03f",minJet);

  vector<SignalCorrector*> vanahi;
  getHistograms("hi",var,varbkg,vanahi, vcutCent,"anaEvtSel",jetSel,jetBkgSel,isolScheme,normMode,"../output-data-Photon-v7-noDuplicate_v29_akPu3PF.root","(1==1)",1,1,subDPhiSide,subSShapeSide,minPhoton,minJet,sigDPhi);

  // MC Reference
   TString mcweight = "((samplePtHat==30&&pthat<50)||(samplePtHat==50&&pthat<80)||(samplePtHat==80))*weight*sampleWeight";

   vector<SignalCorrector*> vanahypho;
   getHistograms("hypho",var,varbkg,vanahypho, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",jetSel,jetBkgSel,isolScheme,normMode,"../output-hy18qcdpho30and50and80v2_v30_xsec_akPu3PF.root",mcweight,0,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);

   // Closure Test
   TString inputTree="../output-hy18lopho50v2_v31_gensmear_xsec_akPu3PF.root";
//   TString inputTree="../output-hy18pyquenlopho50v2_v31_gensmear_xsec_akPu3PF.root";
   mcweight = "(1==1)";
   vector<SignalCorrector*> vanahyphoclos;
   getHistograms("hyphoclos",var,varbkg,vanahyphoclos, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",jetSel,jetBkgSel,isolScheme,normMode,inputTree,mcweight,0,1,subDPhiSide,0,minPhoton,minJet,sigDPhi);
   
   vector<SignalCorrector*> vanahyphoclosmatjet;
   getHistograms("hyphoclosmatjet",var,"",vanahyphoclosmatjet, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",jetSel&&"inclJetRefPt>0","",isolScheme,normMode,inputTree,mcweight,0,1,0,0,minPhoton,minJet,sigDPhi);
   
   TString refvar=var;
   TCut refjetSel = Form("abs(inclJetEta)<1.6&&inclJetRefPt>%.3f",minJet);
   vector<SignalCorrector*> vanahyphoclosrefjet;
   getHistograms("hyphoclosrefjet",refvar,"",vanahyphoclosrefjet, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",refjetSel,"",isolScheme,normMode,inputTree,mcweight,0,1,0,0,minPhoton,minJet,sigDPhi);
   
   vector<SignalCorrector*> vanahyphoclosgenjet;
   TString genvar="acos(cos(photonPhi-inclGenJetPhi))";
   TCut genjetSel = Form("abs(inclGenJetEta)<1.6&&inclGenJetPt>%.3f",minJet);
   getHistograms("hyphoclosgenjet",genvar,"",vanahyphoclosgenjet, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",genjetSel,"",isolScheme,normMode,inputTree,mcweight,0,0,0,0,minPhoton,minJet,sigDPhi);
   
   TString refsmearvar=var;
   TCut refjetSmearSel = Form("abs(inclJetEta)<1.6&&(inclJetRefPt*inclJetRefResp)>%.3f",minJet);
   vector<SignalCorrector*> vanahyphoclosrefjetsmear;
   getHistograms("hyphoclosrefjetsmear",refsmearvar,"",vanahyphoclosrefjetsmear, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",refjetSmearSel,"",isolScheme,normMode,inputTree,mcweight,0,1,0,0,minPhoton,minJet,sigDPhi);
   
   TString gensmearvar=genvar;
   TCut genjetSmearSel = Form("abs(inclGenJetEta)<1.6&&(inclGenJetPt*inclGenJetResp)>%.3f",minJet);
   vector<SignalCorrector*> vanahyphoclosgenjetsmear;
   getHistograms("hyphoclosgenjetsmear",gensmearvar,"",vanahyphoclosgenjetsmear, vcutCent,"offlSel&&genCalIsoDR04<5&&abs(refPhoFlavor)<=22",genjetSmearSel,"",isolScheme,normMode,inputTree,mcweight,0,0,0,0,minPhoton,minJet,sigDPhi);

}

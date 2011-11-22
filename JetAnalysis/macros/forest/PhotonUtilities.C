bool HiForest::isSpike(int j)
{
   if (photon.isEB[j]) {
      double swiss = 1-(photon.eRight[j]+photon.eLeft[j]+photon.eTop[j]+photon.eBottom[j])/photon.eMax[j];
      if (swiss>0.9) return 1;
      if (fabs(photon.seedTime[j])>3) return 1;
      if (photon.sigmaIetaIeta[j]<0.002) return 1;
      if (photon.sigmaIphiIphi[j]<0.002) return 1;
   }
   return 0;
}
bool HiForest::isGoodPhoton(int j)
{

   if (photon.isEB[j]) {
      // Barrel photon                                                                                                                                                                   
      if (photon.hadronicOverEm[j]>0.2) return 0;
      if (photon.isEle[j]) return 0;
      if ((photon.rawEnergy[j]/photon.energy[j])<0.5) return 0;
      if (photon.sigmaIetaIeta[j]>0.011) return 0;
      if ((photon.cr4[j]+photon.cc4[j]+photon.ct4PtCut20[j])>5) return 0;
   } else {
      // Endcap photon
      return 0;  // Need to update to include endcap photons
   }

   return 1;
}

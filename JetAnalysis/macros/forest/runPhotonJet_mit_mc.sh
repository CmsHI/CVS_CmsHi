#!/bin/bash -

#
# mit
#
for algo in akPu3PF; do
  # mixing classes
  #root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/jazzitup/hiForest/mergedFiles/forest_hydjetDrum_MB_20k.root","output-hy18mb_v28classes.root",0,1.,0,"","",1)'
  # mc embedded
  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton30/forest/allQCDPhoton30_50k_cent10_Merged.root","norewt-output-hy18qcdpho30merge_v28_xsec.root",0,1.59,0,"","",0)'
  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton30/forest/allQCDPhoton30_50k_cent10_Merged.root","output-hy18qcdpho30merge_v28_xsec.root",0,1.59,1,"norewt-output-hy18qcdpho30merge_v28_xsec.root","output-data-Photon-v7-noDuplicate_v28.root",0)'
  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton50/forest/allQCDPhoton50_35k_cent10_Merged.root","norewt-output-hy18qcdpho50merge_v28_xsec.root",0,0.767,0,"","",0)'
  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton50/forest/allQCDPhoton50_35k_cent10_Merged.root","output-hy18qcdpho50merge_v28_xsec.root",0,0.767,1,"norewt-output-hy18qcdpho50merge_v28_xsec.root","output-data-Photon-v7-noDuplicate_v28.root",0)'
  hadd -f output-hy18qcdpho30and50merge_v28_xsec_$algo.root output-hy18qcdpho30merge_v28_xsec_$algo.root output-hy18qcdpho50merge_v28_xsec_$algo.root

  # mc mix
#  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton30/forest/allQCDPhoton30_50k_cent10_Merged.root","norewt-output-hy18qcdpho30merge_v28_xsec_mixmb.root",0,1.59,0,"","",2,"output-hy18mb_v28classes.root")'
#  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton30/forest/allQCDPhoton30_50k_cent10_Merged.root","output-hy18qcdpho30merge_v28_xsec_mixmb.root",0,1.59,1,"norewt-output-hy18qcdpho30merge_v28_xsec_mixmb.root","output-data-Photon-v7-noDuplicate_v28.root",2,"output-hy18mb_v28classes.root")'
#  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton50/forest/allQCDPhoton50_35k_cent10_Merged.root","norewt-output-hy18qcdpho50merge_v28_xsec_mixmb.root",0,0.767,0,"","",2,"output-hy18mb_v28classes.root")'
#  root -b -q analyzePhotonJet.C+'("'$algo'","/mnt/hadoop/cms/store/user/yinglu/MC_Production/allQCDPhoton/allQCDPhoton50/forest/allQCDPhoton50_35k_cent10_Merged.root","output-hy18qcdpho50merge_v28_xsec_mixmb.root",0,0.767,1,"norewt-output-hy18qcdpho50merge_v28_xsec_mixmb.root","output-data-Photon-v7-noDuplicate_v28.root",2,"output-hy18mb_v28classes.root")'
#  hadd -f output-hy18qcdpho30and50merge_v28_xsec_mixmb_$algo.root output-hy18qcdpho30merge_v28_xsec_mixmb_$algo.root output-hy18qcdpho50merge_v28_xsec_mixmb_$algo.root
done

#root -b -q analyzePhotonJet.C+'("/d102/velicanu/forest/merged/HiForestPhoton_v4.root","output-data-Photon-v4_v15.root",1.,0)'
#root -b -q analyzePhotonJet.C+'("/d102/velicanu/forest/merged/HiForestPhoton_v2.root","output-data-Photon-v2_v15.root",1.,0)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/photon50_corrCentralityv12.root","output-hypho50v2_yongsun50k_v15_frac62.root",0.62,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/EM_enriched_Dijet80_60k.root","output-hyuq80em_yongsun60k_v15_frac38.root",0.379,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/EM_enriched_Dijet120_14k.root","output-hyuq120em_yongsun14k_v15_frac38.root",0.381,1)'
#hadd output-hypho50mixdj80emdj120em_yongsun_v15.root output-hypho50v2_yongsun50k_v15_frac62.root output-hyuq80em_yongsun60k_v15_frac38.root output-hyuq120em_yongsun14k_v15_frac38.root

root -b -q analyzePhotonJet.C+'("/mnt/hadoop/cms/store/user/yinglu/MC_Production/Photon50Q/HiForest_Tree/photon50_QuenchOn_Test.root","output-hypho50q_v15_frac62.root",0.62,1)'

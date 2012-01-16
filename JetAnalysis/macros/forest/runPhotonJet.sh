root -b -q analyzePhotonJet.C+'("/d102/yjlee/hiForest/HiForestPhoton-v7-noDuplicate.root","output-data-Photon-v7nodup_v21.root",1.,0)'
#root -b -q analyzePhotonJet.C+'("/d102/velicanu/forest/merged/HiForestPhoton_v7.root","output-data-Photon-v7_v21.root",1.,0)'

#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/photon50_37k.root","output-hy18pho50_37k_v21_frac74.root",0.74,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/emJet80_41007events.root","output-hy18uq80em_41k_v21_frac26.root",0.259,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/emJet120_25308events.root","output-hy18uq120em_25k_v21_frac26.root",0.261,1)'
#hadd -f output-hy18pho50mixdj80emdj120em_v21.root output-hy18pho50_37k_v21_frac74.root output-hy18uq80em_41k_v21_frac26.root output-hy18uq120em_25k_v21_frac26.root

#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/hydjet1.6/photon50_corrCentralityv12.root","output-hypho50v2_yongsun50k_v21_frac74.root",0.74,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/hydjet1.6/EM_enriched_Dijet80_60k.root","output-hyuq80em_yongsun60k_v21_frac26.root",0.259,1)'
#root -b -q analyzePhotonJet.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/hydjet1.6/EM_enriched_Dijet120_14k.root","output-hyuq120em_yongsun14k_v21_frac26.root",0.261,1)'
#hadd output-hypho50mixdj80emdj120em_yongsun_v21.root output-hypho50v2_yongsun50k_v21_frac74.root output-hyuq80em_yongsun60k_v21_frac26.root output-hyuq120em_yongsun14k_v21_frac26.root

#root -b -q analyzePhotonJet_gen.C+'("/d101/kimy/macro/hiPhotonAna2011/rootFiles/hydjet1.6/photon50_corrCentralityv12.root","output-hypho50v2gen_yongsun50k_v21_frac62.root",0.62,1)'
#root -b -q analyzePhotonJet.C+'("/mnt/hadoop/cms/store/user/yinglu/MC_Production/Photon50Q/HiForest_Tree/photon50_QuenchOn_Test.root","output-hypho50q_v21_frac62.root",0.62,1)'

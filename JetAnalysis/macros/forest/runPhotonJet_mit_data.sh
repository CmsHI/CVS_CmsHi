#!/bin/bash -

#
# mit
#
# data
#root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/velicanu/forest/HiForestMinBias_v2.root","output-data-MinBias-v2_v26classes.root",1,1.,0,"","",1)'
#root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/velicanu/forest/HiForestPhoton-v7-noDuplicate.root","output-data-Photon-v7-noDuplicate_v29.root",1,1.,0,"","",0)'
root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/velicanu/forest/HiForestPhoton-v7-noDuplicate.root","output-data-Photon-v7-noDuplicate_v29mixmb.root",1,1.,0,"","",2,"output-data-MinBias-v2_v26classes.root")'

#old
#root -b -q analyzePhotonJet.C+'("akPu3PF","/mnt/hadoop/cms/store/user/frankmalocal/forest/Hi2011ForestPhoton_v7.root","output-data-Photon-v7_v25.root",1,1.,0,"","",0)'

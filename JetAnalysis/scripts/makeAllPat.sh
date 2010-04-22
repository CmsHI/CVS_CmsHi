#!/bin/sh

for pthat in 50to80 80to120 120to170
do
cmsRun makePatJets.py files=rfio:/castor/cern.ch/user/y/yilmaz/share/jets/PyquenDijet${pthat}_d20100325_runs1to500.root output=pat_jets_$pthat.root
done









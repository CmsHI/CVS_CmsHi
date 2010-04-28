#!/bin/sh


root -b -q runResponse.C+'("./UnquenchedDijet50to80/UnquenchedDijet50to80_runs1to100.root","jra1.root",2096)'
root -b -q runResponse.C+'("./UnquenchedDijet80to120/UnquenchedDijet80to120_runs1to100.root","jra2.root",224.0)'
root -b -q runResponse.C+'("./UnquenchedDijet120to170/UnquenchedDijet120to170_runs1to100.root","jra3.root",28.46)'

hadd jra_all.root jra*.root


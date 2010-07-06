
datadir=$CMSSW_BASE/src/RecoHI/HiCentralityAlgos/data

input=../data/CentralityTables.root
output=../data/CentralityTables.db

cp $datadir/CentralityTables.db $output

for tag in \
HFhits40_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0 \
HFhits20_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0 \
HFhits10_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0 \
HFhits5_DataJulyExercise_Hydjet2760GeV_MC_37Y_V5_v0
do
cmsRun $CMSSW_BASE/src/RecoHI/HiCentralityAlgos/tools/makeDBFromTFile.py outputTag=$tag inputFile=$input outputFile=$output
done








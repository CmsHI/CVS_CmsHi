

input=$1
bin=$2
tag=`echo $input | sed "s/.root//g"`
output1=hist_${tag}_bin$bin.root
output2=fit_${tag}_bin$bin.root
output3=resp_${tag}_bin$bin.root

# Algorithms : icPu5calo icPu7calo akPu5calo akPu7calo ktPu4calo ktPu6calo ak5calo ak7calo kt4calo kt6calo

jet_response_analyzer_x \
-input $input \
-binspt 40 45 50 55 60 65 70 75 80 85 90 95 100 110 120 130 150 175 200 225 250 300 \
-binseta 0 1.3 3.0 5.2 \
-algs icPu5calo icPu7calo akPu5calo akPu7calo ktPu4calo ktPu6calo ak5calo ak7calo kt4calo kt6calo \
-output $output1 \
-useweight true \
-centrality $bin

#jet_response_fitter_x -input $output1 -output $output2
mv $output1 $output2

jet_response_and_resolution_x -input $output2 -output $output3 
#-variables "RelRsp_Barrel:RefPt,RelRes_Barrel:RefPt" deprecated - how to choose barrel?

#root -b -q analyze_spectrum.C\(\"$1\",\"genjets_$3\",$2\)





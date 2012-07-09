if [[ -z "$1" ]]
then
  echo "Usage: ./dmerge.sh <fileNumber>"
  exit 1
fi

ls -1 /mnt/hadoop/cms/store/user/yetkin/MC_Production/Pythia${1}_HydjetDrum_mix02/HiForest2_v21/*.root > list${1}.txt
output="test${1}.root"


rootn.exe -b <<EOF
.L /net/hisrv0001/home/dav2105/run/CMSSW_5_2_5_patch1/src/UserCode/CmsHi/HiForest/V2/mergeUtility/dynamicmerge.C+
dynamicmerge("list$1.txt","$output")
.q
EOF


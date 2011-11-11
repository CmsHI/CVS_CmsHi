menu=$1
cfg=$2
cmd="hltGetConfiguration --full --online --data $menu --type HIon --input file:/tmp/InputCollection.root --process HLT2 > $cfg"
echo $cmd
eval $cmd
sed -i 's/"source"/"sourcenew"/g' $cfg
sed -i "s/'source'/'sourcenew'/g" $cfg

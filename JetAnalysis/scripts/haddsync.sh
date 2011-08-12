dir=$1

list1=`ls $dir | grep mpa | sort`
list2=`ls $dir | grep Jet | sort`

mkdir -p $dir/merge

cmd1="hadd $dir/merge/mpa_all_0.root"
cmd2="hadd $dir/merge/JetAnaTrees_all_0.root"
for i in $list1; do
  tag=`echo $i | awk 'BEGIN { FS = "mpa_" } ; { print $2 }'`
  echo $list2 | grep -q $tag
  if [ $? -eq 0 ]; then
    cmd1+=" $dir/mpa_"$tag
    cmd2+=" $dir/JetAnaTrees_"$tag
  else echo "not in both: " $tag
  fi
done

#echo $cmd1
#echo $cmd2
eval $cmd1
eval $cmd2
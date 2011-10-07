cat $1|sed "s/\[[0-9]*]/[MaxNumber]/g">$1.1
cat $1|grep SetBranchAddress|awk '{print $1,"@@@."$2,"@@@."$3}'|sed 's/fChain/  t/g'|sed "s/@@@.\&/\&@@@./g"|sed "s/@@@/$2/g">$1.branch


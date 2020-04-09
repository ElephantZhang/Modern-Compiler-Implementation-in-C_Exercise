fileset=`ls ../testcases`
for file in $fileset
do
    echo $file
    ./parse.out '../testcases/'$file
done

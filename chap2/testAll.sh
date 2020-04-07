fileset=`ls ../testcases`
for file in $fileset
do
    echo $file >> "testResult"
    ./lextest '../testcases/'$file >> "testResult"
done

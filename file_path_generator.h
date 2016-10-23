#!/bin/sh

root_direct=$1;
#echo "$root_direct";
for f in $(find $1 -name '*.pdf' -or -name '*.doc' -or -name '*.txt');
do echo "$f"; 
echo "$f" >> "output.txt" ;
done;

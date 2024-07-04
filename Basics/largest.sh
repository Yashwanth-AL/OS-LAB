#!/bin/bash

echo "Enter array elements"
read -a arr

max=${arr[0]}

for i in ${arr[@]}
do
if [ $i -gt $max ];then
max=$i
fi
done

echo "Maximum element is : $max"
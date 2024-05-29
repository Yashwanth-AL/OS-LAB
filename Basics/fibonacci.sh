#!/bin/bash

n1=0
n2=1

echo "Enter the number n"
read n;

echo "First $n Fibonacci Numbers are : "
echo  -n $n1 $n2" "  

for ((i=2;i<$n;i++))
do
n3=$(($n1+$n2))
echo -n $n3" "

n1=$n2
n2=$n3
done
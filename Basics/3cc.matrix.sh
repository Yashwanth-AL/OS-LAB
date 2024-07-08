#!/bin/bash

echo -n "Enter number of rows : "
read n
echo -n "Enter number of columns : "
read m

echo "Enter elements of matrix A : "
for ((i=0; i<$n; i++)); do
for((j=0; j<$m; j++)); do
read "A[$i$j]"
done
done

echo "Enter elements of the Matrix B : "
for ((i=0; i<$n; i++)); do
for((j=0; j<$m; j++)); do
read "B[$i$j]"
done
done

for ((i=0; i<$n; i++)); do
for((j=0; j<$m; j++)); do
C[$i$j]=$((${A[$i$j]} + ${B[$i$j]}))
done
done

echo "After Addition"
for ((i=0; i<$n; i++)); do
for((j=0; j<$m; j++)); do
echo -n ${C[$i$j]}"  "
done
echo " "
done

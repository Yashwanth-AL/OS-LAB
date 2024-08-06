#!/bin/bash

echo "Enter the number n"
read n
echo "first $n fibonacci numbers are : "

a=0
b=1

for((i=0; i<n; i++)); do
echo -n "$a "
c=$((a+b))
a=$b
b=$c
done


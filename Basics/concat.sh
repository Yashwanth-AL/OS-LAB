#!/bin/bash
echo "Enter First String : "
read str1
echo "Enter Second String : "
read str2
str3="$str1 $str2"
len=${#str3}
echo "Concatenated String is $str3 of length $len"
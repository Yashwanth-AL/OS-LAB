#!/bin/bash

echo "Enter The Strings : "
read str1 str2

if [ "$str1" == "$str2" ]; then
echo "str1 and str2 are the same"
elif [ "$str1" \> "$str2" ]; then
  echo "$str1 is greater than $str2"
else
echo "$str2 is greater than $str1"
fi
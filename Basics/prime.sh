#!/bin/bash

echo "Enter range n"
read n

for ((i=2; i<=n; i++)); do
    flag=0
    for ((j=2; j<=i/2; j++)); do
        if ((i%j==0)); then
            flag=1
            break
        fi
    done
    if ((flag==0)); then
        echo -n $i" "
    fi
done
echo " "
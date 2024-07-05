#!/bin/bash

echo "Enter two numbers: "
read n1 n2

echo "Enter Operator: "
read op

case $op in
    '+') echo "$n1 + $n2 = $(($n1 + $n2))"
        ;;
    '-') echo "$n1 - $n2 = $(($n1 - $n2))"
        ;;
    '*') echo "$n1 * $n2 = $(($n1 * $n2))"
        ;;
    '/') echo "$n1 / $n2 = $(($n1 / $n2))"
        ;;
    *) echo "Invalid operator"
        ;;
esac
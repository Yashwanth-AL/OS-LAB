gcc -o fib child.c -lrt

gcc -o parent parent.c -lrt

./parent 10

CHILD:
0 1 1 2 3 5 8 13 21 34
PARENT: child completed
Parent printing:
0 1 1 2 3 5 8 13 21 34

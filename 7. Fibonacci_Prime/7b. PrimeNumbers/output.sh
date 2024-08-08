gcc -o child child.c -lrt

gcc -o parent parent.c -lrt

./parent 10 50

CHILD:
The prime numbers in the range 10 and 50 are:
11    13    17    19    23    29    31    37    41    43    47

Parent: child complete!
The prime numbers in the range 10 and 50 are:
11    13    17    19    23    29    31    37    41    43    47

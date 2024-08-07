gcc -o parent parent.c

gcc -o child child.c

./parent

[PARENT] Created shared memory with key = 1234, id = 32768, address = 0x7fddfc001000
[PARENT] Enter n: 5
[CHILD] Attached to shared memory with key = 1234, id = 32768. address = 0x7fddfc001000
[CHILD] Finished generating first 5 odd numbers
[PARENT] Child finished executing.
[PARENT] The first 5 odd numbers are: 
1 3 5 7 9 
[PARENT] Shared Memory Deleted

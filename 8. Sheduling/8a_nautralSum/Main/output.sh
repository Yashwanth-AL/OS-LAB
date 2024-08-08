$ gcc -o thread thread.c -pthread

$ ./thread 5

[Thread 1] Calculating the sum of natural numbers up to 5...
[Thread 1] Sum calculated: 15
[Thread 2] Calculating the factorial of 5...
[Thread 2] Factorial calculated: 120
Inside main thread
Sum of natural numbers up to 5 is: 15
Factorial of 5 is: 120

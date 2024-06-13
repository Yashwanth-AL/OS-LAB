/* Program to stimulate the grep command of the Linux operating system. It finds the required
   pattern in the given file and prints the lines with the pattern to the console. */
// Simulation of "grep" command
#include <stdio.h>
#include <string.h>

void main() {
    char fn[10], pat[10], temp[200];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", fn);
    printf("Enter pattern to be searched: ");
    scanf("%s", pat);

    fp = fopen(fn, "r");
    while (!feof(fp)) {
        // fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into
        // the string pointed to by str. It stops when either (n-1) characters are read, the newline
        // character is read, or the end-of-file is reached, whichever comes first.
        fgets(temp, 100, fp);
        if (strstr(temp, pat)) // Finds the first occurrence of the substring in the string
            printf("%s", temp);
    }
    fclose(fp);
}

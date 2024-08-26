/* Program to stimulate the grep command of the Linux operating system. It finds the required pattern in the given file and prints the lines with the pattern to the console. */

// Simulation of "grep" command

#include <stdio.h>
#include <string.h>

int main() {
    char filename[100], pattern[100], temp[200];

    printf("Enter file name: ");
    scanf("%99s", filename);  
    printf("Enter pattern to be searched: ");
    scanf("%99s", pattern); 

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file : ");
        return 1;
    }

    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pattern) != NULL) {
            printf("%s", temp);
        }
    }

    fclose(fp);
    return 0;
}

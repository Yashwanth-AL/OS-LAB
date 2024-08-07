/* Program to stimulate the ls command of the Linux operating system it lists all the files present
 in the given directory. */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("\nYou are not passing the directory\n");
        exit(1);
    }

    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        printf("\nCannot open directory %s!\n", argv[1]);
        exit(1);
    }

    struct dirent *dir_entry;
    while ((dir_entry = readdir(dir)) != NULL) {
        printf("%s\n", dir_entry->d_name);
    }

    closedir(dir);
    return 0;
}

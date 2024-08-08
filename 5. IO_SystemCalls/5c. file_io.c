//-------------use of I/O system calls for File I/O//
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 30

int main() {
    int fd = open("./file.txt", O_RDWR), n;
    char buffer[BUFFER_SIZE];
    printf("File descriptor is %d\n", fd);
    if (fd == -1) {
        printf("Failed to open file.\n");
        exit(0);
    }
    printf("Reading first 10 characters from file:\n");
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nSkipping 5 characters from current position in the file:\n");
    lseek(fd, 5, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nGoing 10 characters before the current position in the file:\n");
    lseek(fd, -10, SEEK_CUR);
    n = read(fd, buffer, 10);
    write(1, buffer, n);
    printf("\nGoing to 5th last character in the file:\n");
    lseek(fd, -5, SEEK_END);
    n = read(fd, buffer, 5);
    write(1, buffer, n);
    printf("\nGoing to the 3rd character in the file:\n");
    lseek(fd, 3, SEEK_SET);
    n = read(fd, buffer, 5);
    write(1, buffer, n);
    return 0;
}

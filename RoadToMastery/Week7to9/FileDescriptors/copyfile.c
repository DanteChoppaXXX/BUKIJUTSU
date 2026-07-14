// Write a program that: Opens a file, Reads its contents, Copies the contents to another file, Closes the files.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char buffer[BUFFER_SIZE];

// Function Prototype.
void writefile(const char *file, const char *text);
void readfile(const char *file);
void usage(char *argv);

int main(int argc, char *argv[])
{
   if (argc < 3)
   {
       usage(argv[0]);
   } 
   
   // Call readfile function.
   readfile(argv[1]);
   writefile(argv[2], buffer);

   return EXIT_SUCCESS;
}

void usage(char *argv)
{
    printf("Usage: %s <Source file> <Destination file>\nCopies content of Source file to Destination file\n", argv);
    exit(1);
}

void writefile(const char *file, const char *text)
{
    // Open the file.
    int fd = open(file, O_CREAT|O_WRONLY|O_APPEND, S_IWUSR|S_IRUSR);
    if (fd < 0) {
        fprintf(stderr, "[x] File Open! [FAILED]\n");
        exit(1);
    }

    // Reads the contents of the file.
    write(fd, text, strlen(text));
    write(fd, "\n", 1);

    // Close the file.
    close(fd);
}

void readfile(const char *file)
{
    // Open the file.
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "[x] File Open! [FAILED]\n");
        exit(1);
    }

    // Reads the contents of the file.
    read(fd, buffer, BUFFER_SIZE);

    // Close the file.
    close(fd);
}

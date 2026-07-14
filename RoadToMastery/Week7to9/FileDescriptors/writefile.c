// Write a program that: Opens a file, Writes contents to the file, Closes the file.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function Prototype.
void writefile(const char *file, const char *text);
void usage(char *argv);

int main(int argc, char *argv[])
{
   if (argc < 3)
   {
       usage(argv[0]);
   } 
   
   // Call readfile function.
   writefile(argv[1], argv[2]);

   return EXIT_SUCCESS;
}

void usage(char *argv)
{
    printf("Usage: %s <Name of file> \"String of text to write to file\"\n", argv);
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


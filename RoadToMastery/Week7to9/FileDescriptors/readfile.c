// Write a program that: Opens a file, Reads its contents, Prints them, Closes the file.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

// Function Prototype.
void readfile(const char *file);
void usage(char *argv);

int main(int argc, char *argv[])
{
   if (argc < 2 || argc > 2)
   {
       usage(argv[0]);
   } 
    
   // Call readfile function.
   readfile(argv[1]);

   return EXIT_SUCCESS;
}

void usage(char *argv)
{
    printf("Usage: %s <path-to-file>\n", argv);
    exit(1);
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
    char buffer[BUFFER_SIZE];
    read(fd, buffer, BUFFER_SIZE);

    // Print the content of the file.
    printf("%s\n", buffer);

    // Close the file.
    close(fd);
}

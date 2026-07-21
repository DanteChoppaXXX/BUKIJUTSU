// Create a pipe: Print the descriptor numbers.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    // Create a pipe.
    int fd[2];

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "[x] Pipe Creation! [FAILED]\n");
        exit(1);
    }
    // Print the descriptor numbers.
    printf("Pipe Descriptor 1 => %d\n", fd[0]);
    printf("Pipe Descriptor 2 => %d\n", fd[1]);

    return EXIT_SUCCESS;
}

// Write a program that runs 'echo hello' through execvp()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char command[] = "echo";
    char *args[] = {"echo", "hello", NULL};

    printf("Before exec\n");

    if (execvp(command, args) == -1)
    {
        fprintf(stderr, "[x] Exec! [FAILED]\n");
        exit(1);
    }
    
    printf("After exec\n");

    return EXIT_SUCCESS;
}

// Write a program that replaces itself with: 'ls' using execvp()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char command[] = "ls";
    char *args[] = {"ls", "-l", NULL};

    if (execvp(command, args) == -1)
    {
        fprintf(stderr, "[x] Exec! [FAILED]\n");
        exit(1);
    }

    return EXIT_SUCCESS;
}

// Mini Shell (LimboShell)

// #define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"
#include "../include/executor.h"

#define BUFFER_SIZE 64

int main(void)
{
    printf("Limbo Shell\n");
    while (1) 
    {
        char *args[MAX_ARGS];
        char buffer[BUFFER_SIZE];

        printf("user@shell=># ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (is_redirect(buffer))
        {
            printf("Redirect Parser Works!\n");
        }
        
        if (is_pipe(buffer))
        {
            printf("Pipe Parser Works!\n");
            run_command_with_pipe(buffer);
        }
        int argc = parse_command(buffer, args);

        executor(args);

    }
    return EXIT_SUCCESS;
}





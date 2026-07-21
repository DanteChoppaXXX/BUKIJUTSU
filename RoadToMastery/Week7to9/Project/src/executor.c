#include "../include/executor.h"
#include "../include/parser.h"
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executor(char **args)
{
    // Create a new process.
    pid_t pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            fprintf(stderr, "[x] Execvp! [FAILED]\n");
            exit(1);
        }
    }
    else {
        if (wait(NULL) == -1)
        {
            fprintf(stderr, "[x] Wait! [FAILED]\n");
            exit(1);
        }
    }
}

void run_command_with_pipe(char *buffer)
{
    // Allocate memory to commands.
    char **commands = malloc(sizeof(char *) * MAX_ARGS);
    if (commands == NULL)
    {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]\n");
        exit(1);
    }

    // Tokenize the command delimited by the "|" character.
    char *delim = "|";
    int argc = 0;
    char *token = strtok(buffer, delim);

    while (token != NULL && argc < MAX_ARGS - 1) 
    {
        commands[argc] = token;
        argc++;
        token = strtok(NULL, delim);
    }

    commands[argc] = NULL;

    // for (int i = 0; i < argc; i++)
    // {
    //     printf("%s\n", commands[i]);
    // }

    // Create argument array.
    char **argv = malloc(sizeof(char *) * MAX_ARGS);
    if (argv == NULL)
    {
        fprintf(stderr, "[x] Memory Allocation! [FAILED]\n");
        free(commands);
        exit(1);
    }
    
    int fd[2];
    int prev_read = -1;

    // Create a pipe for each command.
    for (int i = 0; i < argc; i++)
    {
        // Tokenize commands[i] from the commands array.
        char *delim = " \n\t";
        int j = 0;
        char *token = strtok(commands[i], delim);
        
        while (token != NULL && j < MAX_ARGS - 1)
        {
            argv[j] = token;
            j++;
            token = strtok(NULL, delim);
        }

        argv[j] = NULL;
        
        // Create pipe.
        if (i < argc - 1)
        {
            if (pipe(fd) == -1)
            {
                fprintf(stderr, "[x] Pipe Creation! [FAILED]\n");
                free(commands);
                free(argv);
                exit(1);   
            }
        }
        
        // Create new process.
        pid_t pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "[x] Pipe Creation! [FAILED]\n");
            free(commands);
            free(argv);
            close(fd[0]);
            close(fd[1]);
            exit(1);
        }
        if (pid == 0)
        {
            // Check if it's not the first command.
            if (prev_read != -1) 
            {
                close(fd[1]);
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }
            
            // Check if it's not the last command.
            if (i < argc - 1)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }

            // Execute the command.
            if (execvp(argv[0], argv) == -1)
            {
                free(commands);
                free(argv);
                close(fd[0]);
                close(fd[1]);
                exit(1);   
            }
        }
        else {
            if (prev_read != -1)
            {
                close(prev_read);
            }
            if (i < argc - 1)
            {
                // Set previous read to current read.
                prev_read = fd[0];
                close(fd[1]);
            }
        }

    }
    
    // Wait for all children.
    for (int i = 0; i < argc; i++)
    {
        wait(NULL);
    }
    





    
    free(commands);
    free(argv);
}


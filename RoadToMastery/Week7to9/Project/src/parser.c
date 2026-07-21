#include "../include/parser.h"
#include <string.h>

int parse_command(char *buffer, char **args)
{
    // Tokenize the input to extract the command and arguments.
    int argc = 0;
    char *delim = " \n\t";
    char *token = strtok(buffer, delim);

    while (token != NULL && argc < MAX_ARGS - 1)
    {
        args[argc] = token;
        argc++;
        token = strtok(NULL, delim);
    }
    args[argc] = NULL;

    return argc;
}

int is_redirect(char *buffer)
{
    int flag = 0;

    // Check if the ">" of ">>" character is in the buffer.
    if (strstr(buffer, ">") != NULL || strstr(buffer, ">>") != NULL)
    {
        flag = 1;
    }
    return flag;
}

int is_pipe(char *buffer)
{
    int flag = 0;
    
    // Check if the "|" character is present in the buffer.
    if (strstr(buffer, "|") != NULL)
    {
        flag = 1;
    }
    return flag;
}

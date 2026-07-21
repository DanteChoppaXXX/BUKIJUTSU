// Responsibility: Tokenizing user input, detectining piping/redirection, preparing argv.

#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 10

int parse_command(char *buffer, char **args);
int is_redirect(char *buffer);
int is_pipe(char *buffer);

#endif

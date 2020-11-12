#ifndef __STRING_HANDLER_H
#define __STRING_HANDLER_H

// Biblioteca com funções para manipulação de strings

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_COMMANDS 5

int parse_input(char **input);

char **split_string_token(char *input, const char *token);
void free_commands(char **commands);

char *ltrim(char *);
char *rtrim(char *);
char *trim(char *);

#endif

#ifndef __STRING_HANDLER_H
#define __STRING_HANDLER_H

// Biblioteca com funções para manipulação de strings

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_COMMANDS 5

int parse_input(char **input);

// Quebra string dada de acordo com token
char **split_string_token(char *input, const char *token);
// Libera vetor de strings de comandos
void free_commands(char **commands);

// Verifica a ocorrência de uma string em um vetor de strings
int occur_in_str(char **strArray, int nArgs, char *str, int remove);

// Quebra uma string de entrada com base em uma string delimitadora
char *multi_tok(char *input, char *delimiter);

// Remove caracteres no início e no final da string
char *trim(char *, const char *character);

#endif

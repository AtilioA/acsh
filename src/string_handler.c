#include "../include/string_handler.h"

int parse_input(char **input)
{
    size_t buffSize = 0;

    // Checa se existe ao menos um caractere
    int line;
    if ((line = getline(input, &buffSize, stdin)) > 0)
    {
        int lastChar = strlen(*input) - 1;
        (*input)[lastChar] = '\0'; // Remove \n da entrada

        rewind(stdin);
        return 1;
    }
    else // Se não houver caracteres
    {
        free(*input);

        rewind(stdin);
        return 0;
    }
}

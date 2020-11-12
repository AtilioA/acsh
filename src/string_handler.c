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

char **split_string_token(char *input, const char *token)
{
    char **stringsArray = malloc(MAX_COMMANDS * sizeof(char *));

    char *str = strtok(input, token); // Divide string em tokens

    for (int i = 0; i < MAX_COMMANDS; i++)
    {
        if (!str)
        {
            stringsArray[i] = NULL; // Se não houver token, saia
            break;
        }

        // Preenche stringsArray com string alocada
        int tam_str = strlen(str) + 1;
        stringsArray[i] = malloc(tam_str * sizeof(char));
        strncpy(stringsArray[i], str, tam_str);

        // Lê próxima string
        str = strtok(NULL, token);
    }

    return stringsArray;
}

void free_commands(char **commands)
{
    for (int i = 0; i < MAX_COMMANDS && commands[i]; i++)
    {
        free(commands[i]);
    }
    free(commands);
}

char *ltrim(char *s)
{
    while (isspace(*s))
    {
        s++;
    }

    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s); // Aponta para última posição da string
    while (isspace(*back))
    {
        --back; // Retorna posições enquanto existir espaço
    }
    *(back + 1) = '\0'; // Coloca '\0' no último espaço encontrado (primeiro)

    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

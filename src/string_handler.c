#include "../include/string_handler.h"

int parse_input(char **input)
{
    size_t buffSize = 0;

    // Checa se existe ao menos um caractere
    int line = getline(input, &buffSize, stdin);
    if (line > 1)
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

int occur_in_str(char **strArray, int nArgs, char *str, int remove)
{
    int i;

    for (i = 0; i < nArgs; i++)
    {
        if (strArray[i] == NULL)
        {
            break;
        }
        if (strcmp(strArray[i], str) == 0)
        {
            if (remove)
            {
                free(strArray[i]);
                strArray[i] = NULL;
            }
            return 1;
        }
    }

    return 0;
}

char *multi_tok(char *input, char *delimiter)
{
    static char *string;
    if (input != NULL)
    {
        string = input;
    }

    if (string == NULL)
    {
        return string;
    }

    char *end = strstr(string, delimiter);
    if (end == NULL)
    {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}

char **split_string_token(char *input, const char *token)
{
    char **stringsArray = malloc(MAX_COMMANDS * sizeof(char *));

    char *str = multi_tok(input, (char *)token); // Divide string em tokens

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
        str = multi_tok(NULL, (char *)token);
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

char *trim(char *s, const char *character)
{
    char *start, *end, *sp, *ep;
    size_t len;

    sp = start = s;
    ep = end = s + strlen(s) - 1;

    while (sp <= end && strchr(character, *sp))
    {
        sp++;
    }

    while (ep > sp && strchr(character, *ep))
    {
        ep--;
    }

    len = (sp > ep) ? 0 : ((ep - sp) + 1);

    if (s != sp)
    {
        memmove(s, sp, len);
    }

    s[len] = '\0';

    return s;
}

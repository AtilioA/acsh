#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <signal.h>
#include <string.h>
// #include <errno.h>
// #include <sys/time.h>
// #include <sys/wait.h>
#include <stdbool.h>

#include "include/utils.h"
#include "include/string_handler.h"
#include "include/signal_handler.h"
#include "include/internal_commands.h"
#include "include/sys_wrapper.h"

int main(/*int argc, char *argv[]*/)
{
    char *input = NULL;
    char **commands = NULL;

    system("clear");

    /* Handlers de sinais vêm aqui */

    while (true)
    {
        printf("acsh> ");

        // Caso ocorra erro na leitura, comece uma nova iteração
        if (!parse_input(&input))
        {
            continue;
        }

        int isInternal = is_internal_command(input);
        if (isInternal) // Se for comando interno
        {
            run_internal_command(isInternal);

            if (isInternal == EXIT)
            {
                free(input);
                break;
            }
        }
        else // Se for comando externo
        {
            // Obtém comandos da string de entrada
            commands = split_string_token(input, "<3");

            /* Executa ou faz algo com comandos */

            free_commands(commands);
        }

        // free_commands(commands);
        free(input);
    }

    return EXIT_SUCCESS;
}

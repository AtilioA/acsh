#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
#include "include/external_commands.h"
#include "include/sys_wrapper.h"

int main(/*int argc, char *argv[]*/)
{
    char *input = NULL;
    char **commands = NULL;

    //system("clear");

    // Instala os novos handlers de sinal (incompleto)
    struct sigaction handler_sigint = {.sa_handler = trata_SIGINT};
    struct sigaction handler_sigquit = {.sa_handler = trata_SIGQUIT};
    struct sigaction handler_sigtstp = {.sa_handler = trata_SIGTSTP};

    // Novo handler do sinal SIGINT (Ctrl+C)
    if (sigemptyset(&handler_sigint.sa_mask) == -1 ||
        sigaction(SIGINT, &handler_sigint, NULL) == -1)
    {
        perror("Falha ao definir novo handler para SIGINT");
    }

    // novo handler do SIGQUIT (Ctrl+\)
    if (sigemptyset(&handler_sigquit.sa_mask) == -1 ||
        sigaction(SIGQUIT, &handler_sigquit, NULL) == -1)
    {
        perror("Falha ao definir novo handler para SIGQUIT\n");
    }

    // Novo handler do sinal SIGTSTP (Ctrl+Z)
    if (sigemptyset(&handler_sigtstp.sa_mask) == -1 ||
        sigaction(SIGTSTP, &handler_sigtstp, NULL) == -1)
    {
        perror("Falha ao definir novo handler para SIGTSTP\n");
    }

    while (true)
    {
        printf("acsh> ");
        //scanf("[^\n]s", input);

        // Caso ocorra erro na leitura, comece uma nova iteração
        if (!parse_input(&input))
        {
            continue;
        }

        int isInternal = is_internal_command(input);
        if (isInternal) // Se for comando interno
        {
            commands = split_string_token(input, " ");
            run_internal_command(isInternal, commands);

            if (isInternal == EXIT)
            {
                free_commands(commands);
                free(input);
                break;
            }

        }
        else // Se for comando externo
        {
            // Obtém comandos da string de entrada
            commands = split_string_token(input, " <3 ");

            run_external_commands(commands);
            /* Executa ou faz algo com comandos */

            free_commands(commands);
        }

        // free_commands(commands);
        free(input);
    }

    return EXIT_SUCCESS;
}

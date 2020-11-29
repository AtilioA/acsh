#include "../include/external_commands.h"
#include "../include/string_handler.h"
#include "../include/signal_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

void run_external_commands(char **commands)
{
    // Variáveis auxiliares de fluxo
    int i;
    char *filename;
    char **argv;

    int status;
    int isBackground = 1; // Roda em background por padrão

    // Faz parse do argv dos comandos
    argv = split_string_token(commands[0], " ");
    filename = argv[0];

    // Verifica se existe "%" no input
    isBackground = !occur_in_str(argv, 4, (char *)"%", 1);

    if (!isBackground)
    {
        int pid = fork();
        if (pid == -1)
        {
            perror("Falha ao criar processo.\n");
        }
        else if (pid == 0)
        {
            // Invoca filho em foreground
            if (execvp(filename, argv) == -1) // Tenta executar processo
            {
                printf("Comando desconhecido: %s\n", argv[0]);
                filename = NULL;
                free_commands(argv);
                exit(0);
            }
        }
        else
        {
            waitpid(pid, NULL, 0);
            return;
        }

        struct sigaction handler_sigint = {.sa_handler = ignore_SIG};
        struct sigaction handler_sigquit = {.sa_handler = ignore_SIG};
        struct sigaction handler_sigtstp = {.sa_handler = ignore_SIG};
        if (sigemptyset(&handler_sigint.sa_mask) == -1 ||
            sigaction(SIGINT, &handler_sigint, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGINT");
        }
        if (sigemptyset(&handler_sigquit.sa_mask) == -1 ||
            sigaction(SIGQUIT, &handler_sigquit, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGQUIT\n");
        }
        if (sigemptyset(&handler_sigtstp.sa_mask) == -1 ||
            sigaction(SIGTSTP, &handler_sigtstp, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGTSTP\n");
        }
        wait(NULL);

        struct sigaction handler_sigint2 = {.sa_handler = trata_SIGINT};
        struct sigaction handler_sigquit2 = {.sa_handler = trata_SIGQUIT};
        struct sigaction handler_sigtstp2 = {.sa_handler = trata_SIGTSTP};
        if (sigemptyset(&handler_sigint2.sa_mask) == -1 ||
            sigaction(SIGINT, &handler_sigint2, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGINT");
        }

        // Novo handler do SIGQUIT (Ctrl+\)
        if (sigemptyset(&handler_sigquit2.sa_mask) == -1 ||
            sigaction(SIGQUIT, &handler_sigquit2, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGQUIT\n");
        }

        // Novo handler do sinal SIGTSTP (Ctrl+Z)
        if (sigemptyset(&handler_sigtstp2.sa_mask) == -1 ||
            sigaction(SIGTSTP, &handler_sigtstp2, NULL) == -1)
        {
            perror("Falha ao definir novo handler para SIGTSTP\n");
        }
    }

        // Liberando as strings
        filename = NULL;
        free_commands(argv);
    }
}

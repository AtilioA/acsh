#include "../include/external_commands.h"
#include "../include/string_handler.h"
#include "../include/signal_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

void run_external_commands(char **commands, char *input)
{
    // Variáveis auxiliares de fluxo
    int i;
    char *filename;
    char **argv;

    int status;
    int isBackground = 1; // Roda em background por padrão
    int nCommands = 0;

    // Faz parse do argv dos comandos
    argv = split_string_token(commands[0], " ");
    filename = argv[0];
    for (int i = 0; i < MAX_COMMANDS; i++)
    {
        if (commands[i] == NULL)
        {
            break;
        }
        else
        {
            nCommands++;
        }
    }

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
                free_commands(commands);
                free(input);
                exit(0);
            }
        }
        else
        {
            struct sigaction handler_sigint = {.sa_handler = ignore_SIG};
            struct sigaction handler_sigquit = {.sa_handler = ignore_SIG};
            struct sigaction handler_sigtstp = {.sa_handler = ignore_SIG};
            if (sigemptyset(&handler_sigint.sa_mask) == -1 ||
                sigaction(SIGINT, &handler_sigint, NULL) == -1)
            {
                perror("Falha ao definir novo handler para SIGINT.\n");
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
            waitpid(pid, NULL, 0);
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
            return;
        }
    }
    else
    {
        int controlProcess = fork();
        if (controlProcess == -1)
        {
            perror("Não foi possível criar um novo processo de controle.\n");
        }
        else if (controlProcess == 0) // Filho do processo de controle
        {
            setsid();

            printf("Ignorando SIGUSR1 control process...\n");
            struct sigaction handler_sigusr1 = {.sa_handler = ignore_SIG};
            if (sigemptyset(&handler_sigusr1.sa_mask) == -1 ||
                sigaction(SIGUSR1, &handler_sigusr1, NULL) == -1)
            {
                perror("Falha ao definir novo handler para SIGUSR1.\n");
            }

            int pids[MAX_COMMANDS] = {0}; // Inicializa vetor de pids
            for (i = 0; i < MAX_COMMANDS; i++)
            {
                if (commands[i] == NULL)
                {
                    break;
                }
                if (i > 0)
                {
                    argv = split_string_token(commands[i], " ");
                    filename = argv[0];
                }

                int pid = fork(); // Cria filho para executar um comando
                if (pid == -1)
                {
                    perror("Não foi possível criar um novo processo.\n");
                }
                else if (pid == 0)
                {
                    if (nCommands == 1)
                    {
                        printf("Ignorando SIGUSR1 filho...\n");
                        signal(SIGUSR1, SIG_IGN);
                        /*if (sigemptyset(&handler_sigusr1.sa_mask) == -1)
                        {
                            perror("Falha ao definir novo handler para SIGUSR1.\n");
                        }
                        if (sigaction(SIGUSR1, &handler_sigusr1, NULL) == -1)
                        {
                            perror("Falha ao definir novo handler para SIGUSR1.\n");
                        }*/
                    }
                    // Tenta executar comando externo
                    if (execvp(filename, argv) == -1)
                    {
                        // Caso falhe, libere strings da memória e feche o processo filho
                        printf("Comando desconhecido: %s\n", argv[0]);
                        filename = NULL;
                        free_commands(argv);
                        free_commands(commands);
                        free(input);
                        exit(0);
                    }
                }
                else
                {
                    pids[i] = pid; // Preenche vetor de pids com pid de filho criado na iteração
                }
            }

            int pid;
            int signaled = 0;
            // Observa se algum filho recebeu SIGUSR1
            while ((pid = waitpid(-1, &status, WNOHANG)) > -1)
            {
                if (pid > 0 && WIFSIGNALED(status))
                {
                    if (WTERMSIG(status) == SIGUSR1 && nCommands > 1)
                    {
                        signaled = 1;
                        break;
                    }
                }
            }
            // Se algum filho recebeu SIGUSR1, também mata todos os irmãos
            if (signaled)
            {
                for (int i = 0; i < MAX_COMMANDS; i++)
                {   
                    if (pids[i] != 0)
                    {
                        kill(pids[i], SIGUSR1);
                    }
                }
            }

            filename = NULL;
            free_commands(argv);
            free_commands(commands);
            free(input);
            exit(0);
        }
        filename = NULL;
        free_commands(argv);
    }
}

#include "../include/external_commands.h"
#include "../include/string_handler.h"
#include "../include/signal_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

// executa comandos externos em background
void run_external_commands(char **commands)
{
  // variaveis auxiliares de fluxo
  int i;
  char *filename;
  char **argv;
  int child;

  int status;

  int is_background = 1;

  // variavel auxiliar de grupo
  __gid_t group;

  for (i = 0; i < MAX_COMMANDS; i++)
  {
    if (commands[i] == NULL)
      break;
    argv = split_string_token(commands[i], " ");
    filename = argv[0];

    is_background = !occur_in_str(argv, 4, (char *)"%", 1);
    printf("is_bg: %d\n", is_background);

    // cria filho
    child = fork();

    if (child == -1)
    {
      printf("Falha ao inicializar o programa %s.\n", filename);
      filename = NULL;
      free_commands(argv);
      break;
    }

    // inicializa a session para o primeiro programa forkado
    if (!i && is_background)
      group = setsid();

    // fluxo do filho
    if (!child)
    {
      // adicionando o filho ao grupo da nova session criada
      if (is_background)
      {
        if (!i)
          setpgid(0, 0); // caso pai da session
        else
          setpgid(0, group); // outros casos
      }
      if (execvp(filename, argv) == -1)
      {
        printf("Erro ao encontrar o comando.\n");
        exit(0);
      }
    }

    //background ou foreground
    if (is_background)
      waitpid(child, &status, WNOHANG);
    else
    {
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

      // novo handler do SIGQUIT (Ctrl+\)
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
    // liberando as strings
    filename = NULL;
    free_commands(argv);
  }
}

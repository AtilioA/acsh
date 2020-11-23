#include "../include/external_commands.h"
#include "../include/string_handler.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
    if (!i)
      group = setsid();

    // fluxo do filho
    if (!child)
    {
      // adicionando o filho ao grupo da nova session criada
      if (!i)
        setpgid(0, 0); // caso pai da session
      else
        setpgid(0, group); // outros casos

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
      waitpid(child, &status, 0);

    // liberando as strings
    filename = NULL;
    free_commands(argv);
  }
}

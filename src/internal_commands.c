#include "../include/internal_commands.h"
// #include "../include/processList.h"
#include "../include/signal_handler.h"

#include <unistd.h>

// Comando interno da acsh "cd"
void acsh_cd(char *dir)
{
    printf("%s\n", dir);
}

// Comando interno da acsh "exit"
void acsh_exit(int status)
{
    printf("%i\n", status);
}

int is_internal_command(char *string)
{
    if (strcmp(string, "exit") == 0)
        return EXIT;

    if (strlen(string) > 2 && (string[0] == 'c' && string[1] == 'd'))
        return CD;

    return 0;
}

void run_internal_command(int command, char **argv)
{
    char *dir;
    switch (command)
    {
    case (CD):
        dir = argv[1];
        if(chdir(dir)!=0)
            perror("cd error.");
        break;

    case (EXIT):
        acsh_exit(0);
        break;

    default:
        break;
    }
}

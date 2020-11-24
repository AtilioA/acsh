#include "../include/internal_commands.h"
// #include "../include/processList.h"
#include "../include/signal_handler.h"

#include <unistd.h>

// void acsh_cd(char *dir)
// {
//     printf("%s\n", dir);
// }

void acsh_exit(int status)
{
    printf("%i\n", status);
}

int is_internal_command(char *string)
{
    if (strcmp(string, "exit") == 0)
    {
        return EXIT;
    }

    if (strcmp(string, "cd") == 0)
    {
        return CD;
    }

    return 0;
}

void run_internal_command(int command, char **argv)
{
    char *dir;
    switch (command)
    {
    case (CD):
        dir = argv[1];
        if (chdir(dir) != 0)
        {
            perror("cd error.");
        }
        break;

    case (EXIT):
        acsh_exit(0);
        break;

    default:
        break;
    }
}

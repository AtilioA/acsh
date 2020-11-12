#include "../include/internal_commands.h"
// #include "../include/processList.h"
#include "../include/signal_handler.h"

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
    if (strcmp(string, "cd") == 0)
    {
        return CD;
    }
    if (strcmp(string, "exit") == 0)
    {
        return EXIT;
    }

    return 0;
}

void run_internal_command(int command)
{
    switch (command)
    {
    case (CD):
        // acsh_cd('.');
        break;

    case (EXIT):
        acsh_exit(0);
        break;

    default:
        break;
    }
}

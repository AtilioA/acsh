#ifndef __INTERNAL_COMMANDS_H
#define __INTERNAL_COMMANDS_H

enum commands
{
    CD = 1,
    EXIT, // CLEAN_DIE
};

#include <string.h>
#include <stdio.h>
#include <wait.h>

void acsh_cd(char *dir);
void acsh_exit(int status);

// Verifica se string (entrada do usuário) é um comando interno
int is_internal_command(char *string);
// Roda comando interno
void run_internal_command(int command);

#endif

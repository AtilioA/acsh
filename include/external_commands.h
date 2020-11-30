#ifndef __EXTERNAL_COMMANDS_H
#define __EXTERNAL_COMMANDS_H

#include <unistd.h>

// Executa comandos externos em background
void run_external_commands(char **commands, char *input);

#endif

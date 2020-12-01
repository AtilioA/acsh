#ifndef __SIGNAL_HANDLER_H
#define __SIGNAL_HANDLER_H

// Biblioteca com funções para manipulação de sinais

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

void handle_signal(bool runningForeground);
void ignore_SIG();
void trata_SIGINT();
void trata_SIGTSTP();
void trata_SIGQUIT();

#endif

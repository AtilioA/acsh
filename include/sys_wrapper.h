#ifndef __SYS_WRAPPER_H
#define __SYS_WRAPPER_H

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include "string_handler.h"
// #include "processList.h"
// #include "signalHandler.h"

void exec(char **commands);
void exec_foreground(char **commands);
void exec_background(char **commands);

#endif

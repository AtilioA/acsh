#include "../include/signal_handler.h"
#include <stdbool.h>
#include <signal.h>

void handle_signal(bool runningForeground)
{
    if (runningForeground == false)
    {
        printf("Não adianta me enviar o sinal por Ctrl-... Estou vacinado!!\n");
        // Ignora sinal
    }
    else
    {
        // Processo em execução recebe sinal
    }
}

void trata_SIGINT()
{
    // raise(SIGINT);
}

void trata_SIGTSTP()
{
    // raise(SIGTSTP);
}

void trata_SIGQUIT()
{
    // raise(SIGQUIT);
}

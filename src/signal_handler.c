#include "../include/signal_handler.h"
#include <stdbool.h>
#include <signal.h>

void handle_signal(bool runningForeground)
{
    if (runningForeground == false)
    {
        printf(" Não adianta me enviar o sinal por Ctrl-... Estou vacinado!!");
        // Ignora sinal
    }
    else
    {
        // Processo em execução recebe sinal
    }
}

void ignore_SIG()
{
    return;
}

void trata_SIGINT()
{
    handle_signal(false);
    // raise(SIGINT);
}

void trata_SIGTSTP()
{
    handle_signal(false);
    // raise(SIGTSTP);
}

void trata_SIGQUIT()
{
    handle_signal(false);
    // raise(SIGQUIT);
}

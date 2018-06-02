#include "mysignal.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>


Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif
    }
    else
    {
#ifdef SA_RESTART
        act.sa_flags |= SA_RESTART;
#endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return oact.sa_handler;
}



void myp(int signo)
{
    printf("this is sig: %d\n", signo);
}

void run_signal(void)
{
    signal(SIGTERM, myp);

    while (true)
    {
        printf("---------------\n");
        sleep(1);
    }
}

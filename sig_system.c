//
// Created by liushan on 19-10-27.
//

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>


#include "myutils.h"
#include "sig_system.h"
#include "mysystem.h"
#include "mysignal.h"

static void sig_int(int signo);
static void sig_chld2(int signo);


int my_sigsystem(const char * cmdstring)
{
    pid_t pid;
    int status;
    struct sigaction ignore, saveintr, savequit;
    sigset_t chldmask, savemask;

    if (cmdstring == NULL)
        return(1);

    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (sigaction(SIGINT, &ignore, &saveintr) < 0)
        return(-1);

    if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
        return(-1);

    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
        return(-1);

    if ( (pid = fork() ) < 0)
    {
        status = -1;
    }
    else if (pid == 0)
    {
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    if (sigaction(SIGINT, &saveintr, NULL) < 0)
        return(-1);
    if (sigaction(SIGQUIT, &savequit, NULL))
        return(-1);
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
        return(-1);

    return(status);
}




void sig_test_mysystem(void)
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_exit("signal(SIGINT) error");

    if (signal(SIGCHLD, sig_chld2) == SIG_ERR)
        err_exit("signal(SIGCHLD) error");

    if (my_sigsystem("/bin/ed") < 0)
        err_exit("mysystem() error");

    exit(0);

}


static void sig_int(int signo)
{
    printf("caught SIGINT\n");
}



static void sig_chld2(int signo)
{
    printf("caught SIGCHLD\n");
}



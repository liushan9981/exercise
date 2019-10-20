#include "mysignal.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pwd.h>
#include <string.h>
#include <stdlib.h>



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



void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    // 改用waitpid，避免并发留下的僵死进程
    while ( (pid = waitpid(-1, &stat, WNOHANG) ) > 0)
        printf("child %d terminated\n", pid);
    return;
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

static void my_alarm(int signo);

static void my_alarm(int signo)
{
    struct passwd * rootptr;
    printf("in signal handler\n");
    if ( (rootptr = getpwnam("root") ) == NULL)
    {
        printf("getpwname(root) error\n");
        exit(1);
    }
    printf("222\n");
    // alarm(1);
}


void run_my_alarm(void)
{
    struct passwd * ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);

    for ( ; ; )
    {
        printf("1\n");
        if ( (ptr = getpwnam("liushan") ) == NULL)
        {
            printf("getpwname(liushan) error\n");
            exit(1);
        }

        printf("pw_name: %s\n", ptr->pw_name);

        if (strcmp(ptr->pw_name, "liushan") != 0)
        {
            printf("return value corrupted, pw_name = %s\n", ptr->pw_name);
        }
    }

}
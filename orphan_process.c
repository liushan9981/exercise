//
// Created by liushan on 19-4-14.
//

#include "orphan_process.h"
#include <errno.h>
#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <signal.h>

static void sig_hup(int signo);
static void pr_ids(char * name);


static void sig_hup(int signo)
{
    printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char * name)
{
    printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld, sid = %ld\n",
            name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO), (long)getsid(0));
    fflush(stdout);
}


void run_orphan_process(void)
{
    char c;
    pid_t pid;

    pr_ids("parent");
    if ((pid = fork()) < 0)
    {
        printf("fork error!\n");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        sleep(5);
    }
    else
    {
        pr_ids("child");
        signal(SIGHUP, sig_hup);
        kill(getpid(), SIGTSTP);
        pr_ids("child");

        if (read(STDIN_FILENO, &c, 1) != 1)
            printf("read error %d on controlling TTY\n", errno);
        else
            printf("read ok\n");

        if (tcsetpgrp(STDIN_FILENO, getpgrp()) == 0)
        {
            printf("tcsetpgrp set %ld ok\n", (long) getpgrp());
        }
        else
        {
            if (errno == EBADF)
                printf("%d\n", 1);
            else if (errno == EINVAL)
                printf("%d\n", 2);
            else if (errno == ENOTTY)
                printf("%d\n", 3);
            else if (errno == EPERM)
                printf("%d\n", 4);
            printf("tcsetpgrp set %ld failed %d\n", (long) getpgrp(), errno);
        }
        pr_ids("child");
        if (read(STDIN_FILENO, &c, 1) != 1)
            printf("read error %d on controlling TTY\n", errno);
        else
            printf("read ok\n");

    }
}
//
// Created by liushan on 19-10-20.
//

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <zconf.h>

#include "myutils.h"

#include "sig_sigpending.h"


/*
 * 运行效果如下
 *  ^\
    SIGQUIT pending
    caught SIGQUIT
    SIGQUIT unblocked


    ^\^\^\
    SIGQUIT pending
    caught SIGQUIT
    SIGQUIT unblocked
    ^\退出 (核心已转储)
 *
 */


static void sig_quit(int);




void test_sigpending(void)
{
    sigset_t newmask, oldmask, pendmask;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        err_exit("signal error");

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_exit("sigprocmask error");

    sleep(5);

    if (sigpending(&pendmask) < 0)
        err_exit("sigpending error");

    if (sigismember(&pendmask, SIGQUIT))
        printf("\nSIGQUIT pending\n");


    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_exit("SIG_SETMASK error");
    printf("SIGQUIT unblocked\n");

    sleep(5);

    exit(0);
}


static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        err_exit("can't reset SIGQUIT");
}



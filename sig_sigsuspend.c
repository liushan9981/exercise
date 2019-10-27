//
// Created by liushan on 19-10-26.
//


#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>

#include "myutils.h"
#include "mysignal.h"
#include "sig_sigsuspend.h"
#include "sig_pr_mask.h"


volatile sig_atomic_t quit_flag;
static void sig_int(int);

void test_sigsuspend_main(void)
{
    printf("quit_flag: %d\n", quit_flag);

    sigset_t newmask, oldmask, zeromask;
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_exit("signal(SIGINT) error");
    if (signal(SIGQUIT, sig_int) == SIG_ERR)
        err_exit("signal(SIGQUIT) error");

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_exit("sigprocmask SIG_BLOCK error");

    sleep(10);

    while (quit_flag == 0)
        sigsuspend(&zeromask);
    printf("mytest1\n");
    quit_flag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_exit("sigprocmask SIG_SETMASK error");

    exit(0);
}


static void sig_int(int signo)
{
    if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if (signo == SIGQUIT)
        quit_flag = 1;
}




static void sig_int2(int);

void test_sigsuspend_set(void)
{
    sigset_t newmask, oldmask, waitmask;
    pr_mask("test_sigsuspend_set start: ");

    if (signal(SIGINT, sig_int2) == SIG_ERR)
        err_exit("signal(SIGINT) error");
    sigemptyset(&waitmask);
    sigaddset(&waitmask, SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_exit("sigprocmask SIG_BLOCK error");
    pr_mask("in critical region: ");
    if (sigsuspend(&waitmask) != -1)
        err_exit("sigsuspend error");
    pr_mask("after return from sigsuspend: ");
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_exit("sigprocmask SIG_SETMASK error");

    pr_mask("program exit: ");
    exit(0);
}


static void sig_int2(int signo)
{
    pr_mask("\nin sig_int2: ");
}



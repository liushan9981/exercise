//
// Created by liushan on 19-10-26.
//

#include <stdio.h>
#include <setjmp.h>
#include <time.h>
#include <bits/types/sig_atomic_t.h>
#include <stdlib.h>
#include <zconf.h>

#include "mysignal.h"
#include "myutils.h"
#include "sig_sigsetjmp.h"
#include "sig_pr_mask.h"




static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;


/*
 * 输出如下：
    starting main:  SIGUSR2
    starting sig_usr1:  SIGUSR1 SIGUSR2
    in sig_alrm:  SIGUSR1 SIGUSR2 SIGALRM
    finishing sig_usr1:  SIGUSR1 SIGUSR2
    ending main:  SIGUSR2
*/



void test_sigsetjmp(void)
{
    sigset_t sigset;

    // 自己定义的屏蔽信号
    sigemptyset(&sigset);
    if (sigaddset(&sigset, SIGUSR2) < 0)
        err_exit("sigaddset error\n");

    if (sigprocmask(SIG_BLOCK, &sigset, NULL) < 0)
        err_exit("sigprocmask error\n");

    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
        err_exit("signal(SIGUSR1) error\n");

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_exit("signal (SIGALRM) error\n");

    pr_mask("starting main: ");

    if (sigsetjmp(jmpbuf, 1)) {
        pr_mask("ending main: ");
        exit(0);
    }

    canjump = 1;

    for (;;)
        pause();

}


static void sig_usr1(int signo)
{
    time_t starttime;

    if (canjump == 0)
        return;

    pr_mask("starting sig_usr1: ");
    alarm(3);
    starttime = time(NULL);
    for (;;)
        if (time(NULL) > starttime + 5)
            break;
    pr_mask("finishing sig_usr1: ");

    canjump = 0;
    siglongjmp(jmpbuf, 1);

}


static void sig_alrm(int signo)
{
    pr_mask("in sig_alrm: ");
}



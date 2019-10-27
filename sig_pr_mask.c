//
// Created by liushan on 19-10-20.
//

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sig_pr_mask.h"



void pr_mask(const char *str)
{
    sigset_t sigset;
    int errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
        printf("sigprocmask error\n");
        exit(1);
    }
    else
    {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGUSR2))
            printf(" SIGUSR2");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        if (sigismember(&sigset, SIGTERM))
            printf(" SIGTERM");
        printf("\n");
    }

    errno = errno_save;
}



void test_pr_mask(void)
{
    sigset_t sigset;
    bool add_sig_term = false;

    // 自己设定屏蔽信号，测试打印效果
    if (add_sig_term)
    {
        if (sigprocmask(0, NULL, &sigset) < 0)
        {
            printf("sigprocmask get error\n");
            exit(1);
        }

        if (sigaddset(&sigset, SIGTERM) < 0)
        {
            printf("sigaddset error\n");
            exit(1);
        }

        if (sigprocmask(SIG_BLOCK, &sigset, NULL) < 0)
        {
            printf("sigprocmask set error\n");
            exit(1);
        }
    }



    pr_mask("test pr_mask");
}



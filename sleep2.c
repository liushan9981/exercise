//
// Created by liushan on 19-10-19.
//

#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "sleep2.h"


static jmp_buf env_alrm;

static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}



unsigned int sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return(seconds);

    if (setjmp(env_alrm) == 0)
    {
        alarm(seconds);
        pause();
    }

    return(alarm(0));
}





static void sig_int(int);


static void sig_int(int signo)
{
    int i, j;
    volatile int k;

    printf("\nsig_int starting\n");
    for (i = 0; i < 30000; i++)
        for (j = 0; j < 4000; j++)
            k += i * j;

    printf("sig_int fin\n");

}


void test_sleep2(void)
{
    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        printf("signal(SIGINT) error");
        exit(1);
    }

    unslept = sleep2(5);
    printf("sleep2 returned: %u\n", unslept);
    exit(0);

}

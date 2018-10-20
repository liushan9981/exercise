//
// Created by liushan on 18-10-20.
//

#include "pr_exit.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>



void pr_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status: %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
        WCOREDUMP(status) ? " (core file generated)" : "");
#else
                );
#endif

    else if (WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));


}


void test_pr_exit(void)
{
    pid_t pid;
    int status;

    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
        exit(7);

    if (wait(&status) != pid)
    {
        printf("wait error\n");
    }
    else
        pr_exit(status);



    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
        abort();

    if (wait(&status) != pid)
    {
        printf("wait error\n");
    }
    else
        pr_exit(status);



    if ( (pid = fork() ) < 0)
    {
        printf("fork error, now exit\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
        printf("%d\n", 3 / 0);

    if (wait(&status) != pid)
    {
        printf("wait error\n");
    }
    else
        pr_exit(status);





}